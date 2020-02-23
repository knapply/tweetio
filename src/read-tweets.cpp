// Copyright (C) 2019 Brendan Knapp
// This file is part of tweetio.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <tweetio.hpp>
#include "gzstream.h"

 #ifdef _OPENMP
 #include <omp.h>
 #endif
 

enum class TweetFileType {
  unknown,
  twitter_api_stream,
  pulse_nested_doc,
  pulse_array
};

R_xlen_t count_lines(const std::string& file_path) {
  igzstream in_file;
  in_file.open(file_path.c_str());

  std::string line_string;
  R_xlen_t out = 0;
  while (std::getline(in_file, line_string)) {
    if (!line_string.empty()) {
      out++;
    }
  }
  in_file.close();

  return out;
}

TweetFileType detect_file_type(const std::string& file_path) {
  igzstream in_file;
  in_file.open(file_path.c_str());

  char first_char = in_file.peek();
  if (first_char == '[') {
    in_file.close();
    return TweetFileType::pulse_array;
  }
  if (first_char == '{') {
    first_char = in_file.get();
    const char second_char = in_file.peek();
    if (second_char != '"') {
      Rcpp::stop("Unknown file schema.");
    }
  }

  // can't use in_file.seekg() on igzstream, so reset if character consumed
  in_file.close();
  in_file.open(file_path.c_str());

  std::string line_string;
  rapidjson::Document test_parse;
  rapidjson::ParseResult parse_successful;
  while (std::getline(in_file, line_string)) {
    if (!line_string.empty()) {
      parse_successful = test_parse.Parse(line_string.c_str());
      if (parse_successful) {
        break;
      }
    }
  }
  in_file.close();

  if (!parse_successful) {
    Rcpp::stop("File does not contain any valid JSON.");
  }

  if (test_parse["id_str"].IsString() ||
      test_parse["delete"]["status"]["id_str"].IsString()) {
    return TweetFileType::twitter_api_stream;
  }

  if (test_parse["doc"].IsObject()) {
    return TweetFileType::pulse_nested_doc;
  }

  Rcpp::stop("Unknown file schema.");
}

template <TweetFileType>
Rcpp::List read_tweets(const std::string&, const bool);

template <>
Rcpp::List read_tweets<TweetFileType::pulse_nested_doc>(
    const std::string& file_path,
    const bool verbose) {
  if (verbose) tweetio::msg("- schema detected: Pulse, nested-doc");

  const auto n_lines = count_lines(file_path);
  if (verbose) tweetio::msg("- # of lines found: " + std::to_string(n_lines) + "\n");

  tweetio::Progress progress(n_lines, verbose);

  std::string line_string;
  igzstream in_file;
  in_file.open(file_path.c_str());

  tweetio::PulseTweetDF tweets(n_lines);

  while (std::getline(in_file, line_string)) {
    progress.increment();

    if (line_string.empty()) {
      continue;
    }

    rapidjson::Document parsed_json;
    parsed_json.Parse(line_string.c_str());
    const auto& doc = parsed_json["doc"];

    if (doc.FindMember("id_str") == doc.MemberEnd()) {
      continue;
    }

    const auto& meta = parsed_json["meta"];

    tweets.push(doc, meta);
  }

  return tweets.to_r();
}

template <>
Rcpp::List read_tweets<TweetFileType::pulse_array>(const std::string& file_path,
                                                   const bool verbose) {
  if (verbose)
    tweetio::msg("schema detected: Pulse, array\n");

  igzstream in_file;
  in_file.open(file_path.c_str());

  const std::string content(std::istreambuf_iterator<char>{in_file},
                            std::istreambuf_iterator<char>());
  in_file.close();

  rapidjson::Document parsed_json;

  rapidjson::ParseResult ok = parsed_json.ParseInsitu((char*)content.c_str());
  if (!ok) {
    Rcpp::stop("parsing error");
  }

  const R_xlen_t n(parsed_json.Size());

  tweetio::PulseTweetDF tweets(n);
  tweetio::Progress progress(n, verbose);

  for (const auto& val : parsed_json.GetArray()) {
    progress.increment();

    const auto& doc = val["_source"]["doc"];

    if (!doc["id_str"].IsString()) {
      continue;
    }

    const auto& meta = val["_source"]["meta"];

    tweets.push(doc, meta);
  }

  return tweets.to_r();
}

template <>
Rcpp::List read_tweets<TweetFileType::twitter_api_stream>(
    const std::string& file_path,
    const bool verbose) {
  if (verbose)
    tweetio::msg("schema detected: Twitter API\n");

  std::string line_string;
  std::vector<std::string> raw_json;

  igzstream in_file;
  in_file.open(file_path.c_str());
  while (std::getline(in_file, line_string)) {
    if (!line_string.empty()) {
      raw_json.push_back(line_string);
    }
  }
  in_file.close();

  const R_xlen_t n = raw_json.size();

  tweetio::TweetDF tweets(n);
  tweetio::Progress progress(n, verbose);

  for (const auto& line : raw_json) {
    progress.increment();

    rapidjson::Document parsed_json;
    parsed_json.Parse(line.c_str());
    if (parsed_json.FindMember("id_str") == parsed_json.MemberEnd()) {
      continue;
    }

    tweets.push(parsed_json);
  }

  return tweets.to_r();
}

// [[Rcpp::export]]
Rcpp::List read_tweets_impl(const std::string& file_path,
                            const bool verbose = false) {
  const TweetFileType file_type = detect_file_type(file_path);

  switch (file_type) {
    case TweetFileType::twitter_api_stream:
      return read_tweets<TweetFileType::twitter_api_stream>(file_path, verbose);

    case TweetFileType::pulse_nested_doc:
      return read_tweets<TweetFileType::pulse_nested_doc>(file_path, verbose);

    case TweetFileType::pulse_array:
      return read_tweets<TweetFileType::pulse_array>(file_path, verbose);

    case TweetFileType::unknown:
      Rcpp::stop("Unknown file schema.");
      return R_NilValue;
  }

  Rcpp::stop("Something went wrong.");
  return R_NilValue;
}


// [[Rcpp::export]]
Rcpp::List read_tweets_bulk2(const std::vector<std::string>& file_path,
                            const bool verbose = false) {
  TweetFileType tracker = TweetFileType::unknown;
  for (const auto& v : file_path) {
    const auto temp = detect_file_type(v);
    if (tracker != TweetFileType::unknown && temp != tracker) {
      Rcpp::stop("bad file");
    } else {
      tracker = temp;
    }
  }

  int n_files = file_path.size();
  int n_lines = 0;
  #pragma omp parallel for shared(file_path) reduction(+: n_lines)
  for (int i = 0; i < n_files; ++i) {
    n_lines += count_lines(file_path[i]);
  }
  
  if (verbose) tweetio::msg("- # of lines found: " + std::to_string(n_lines) + "\n");

  tweetio::Progress progress(n_lines, verbose);

  if (tracker != TweetFileType::twitter_api_stream) {

    tweetio::PulseTweetDF tweets(n_lines);

    #pragma omp for simd
    for (int i = 0; i < n_files; ++i) {
      igzstream in_file;
      std::string line_string;
      in_file.open(file_path[i].c_str());
      
      // Rcpp::Rcout << f << std::endl;

      while (std::getline(in_file, line_string)) {
        progress.increment();
        

        if (line_string.empty()) {
          continue;
        }

        rapidjson::Document parsed_json;
        parsed_json.Parse(line_string.c_str());
        const auto& doc = parsed_json["doc"];

        if (doc.FindMember("id_str") == doc.MemberEnd()) {
          continue;
        }

        const auto& meta = parsed_json["meta"];

        tweets.push(doc, meta);
      }

      in_file.close();
    }

    return tweets.to_r();
  }

  return Rcpp::List::create();
}

/*** R

*/
