// Copyright (C) 2019 Brendan Knapp
// This file is part of tweetio
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

#include <progress.hpp>
#include <progress_bar.hpp>

#include "rapidjson/filereadstream.h"
#include <rapidjson/istreamwrapper.h>

#include <boost/algorithm/string.hpp>

#include <omp.h>


typedef Rcpp::Vector<STRSXP> vec_chr;
typedef Rcpp::Vector<LGLSXP> vec_lgl;
typedef Rcpp::Vector<INTSXP> vec_int;
typedef Rcpp::Vector<REALSXP> vec_dbl;


enum class TweetFileType: int8_t {
  unknown,
  twitter_api_stream,
  pulse_nested_doc,
  pulse_array
};

int count_lines(const std::string& file_path) {
  igzstream in_file;
  in_file.open( file_path.c_str() );
  
  std::string line_string;
  int out = 0;
  while ( std::getline(in_file, line_string) ) {
    if ( !line_string.empty() ) {
      out++;
    }
  }
  in_file.close();

  return out;
}

TweetFileType detect_file_type(const std::string& file_path) {
  igzstream in_file;
  in_file.open( file_path.c_str() );

  const char first_char = in_file.peek();
  if (first_char == '[') {
    in_file.close();
    return TweetFileType::pulse_array;
  }
  
  std::string line_string;
  rapidjson::Document test_parse;
  rapidjson::ParseResult parse_successful;
  while ( std::getline(in_file, line_string) ) {
    if ( !line_string.empty() ) {
      parse_successful = test_parse.ParseInsitu( (char*)line_string.c_str() );
      if (parse_successful) {
        break;
      }
    }
  }
  in_file.close();

  if ( !parse_successful ) {
    Rcpp::stop("File does not contain any valid JSON.");
  }

  if ( test_parse["id_str"].IsString() || test_parse["delete"]["status"]["id_str"].IsString() ) {
    return TweetFileType::twitter_api_stream;
  }

  if ( test_parse["doc"].IsObject() ) {
    return TweetFileType::pulse_nested_doc;
  }

  return TweetFileType::unknown;
}


template<TweetFileType>
Rcpp::List read_tweets(const std::string&);


template<>
Rcpp::List read_tweets<TweetFileType::pulse_nested_doc>(const std::string& file_path) {
  const int n_lines = count_lines(file_path);
  Progress progress(n_lines, true);

  std::string line_string;
  igzstream in_file;
  in_file.open( file_path.c_str() );

  tweetio::TweetDF tweets(n_lines);
  tweetio::PulseMeta metadata(n_lines);

  
  while ( std::getline(in_file, line_string) ) {
    progress.increment();

    if ( line_string.empty() ) {
      continue;
    }

    rapidjson::Document parsed_json;
    parsed_json.Parse( line_string.c_str() );

    if ( parsed_json["doc"].FindMember("id_str") == parsed_json["doc"].MemberEnd() ) {
      continue;
    }
    
    tweets.push( parsed_json["doc"] );
    metadata.push(parsed_json);
  }

  using Rcpp::_;
  Rcpp::List out = Rcpp::List::create(
    _["tweets"] = tweets.to_r(),
    _["metadata"] = metadata.to_r()
  );  

  out.attr("has_metadata") = true;

  return out;
}


template<>
Rcpp::List read_tweets<TweetFileType::pulse_array>(const std::string& file_path) {
  // FILE* fp = fopen(file_path.c_str(), FILE_MODE);
  // char readBuffer[65536];
  // rapidjson::FileReadStream is( fp, readBuffer, sizeof(readBuffer) );

  std::ifstream in_file;
  in_file.open(file_path);

  std::string content;
  in_file.seekg(0, std::ios::end);
  content.resize( in_file.tellg() );
  in_file.seekg(0, std::ios::beg);
  in_file.read( &content[0], content.size() );
  in_file.close();

  rapidjson::Document parsed_json;
  
  rapidjson::ParseResult ok = parsed_json.Parse(content.c_str());
  if (!ok) {
    Rcpp::stop("parsing error");
  }

  const int n( parsed_json.Size() );
  tweetio::TweetDF tweets(n);
  tweetio::PulseMeta metadata(n);
  Progress progress(n, true);

  for ( const auto& val : parsed_json.GetArray() ) {
    progress.increment();
  
    if ( !val["_source"]["doc"]["id_str"].IsString() ) {
      continue;
    }

    tweets.push(val["_source"]["doc"]);
    metadata.push(val["_source"]);

  }

  using Rcpp::_;
  Rcpp::List out = Rcpp::List::create(
    _["tweets"] = tweets.to_r(),
    _["metadata"] = metadata.to_r()
  );  

  out.attr("has_metadata") = true;

  return out;
}


template<>
Rcpp::List read_tweets<TweetFileType::twitter_api_stream>(const std::string& file_path) {
  std::string line_string;
  std::vector<std::string> raw_json;
  
  igzstream in_file;
  in_file.open( file_path.c_str() );
  while ( std::getline(in_file, line_string) ) {
    if ( !line_string.empty() ) {
      raw_json.push_back(line_string);
    }
  }
  in_file.close();

  tweetio::TweetDF tweets( raw_json.size() );
  tweetio::PulseMeta metadata( raw_json.size() );
  Progress progress(raw_json.size(), true);

  for (const auto& line : raw_json) {
    progress.increment();

    rapidjson::Document parsed_json;
    parsed_json.Parse( line.c_str() );
    if (parsed_json.FindMember("id_str") == parsed_json.MemberEnd() ) {
      continue;
    }
    
    tweets.push(parsed_json);

  }

  using Rcpp::_;
  Rcpp::List out = tweets.to_r();
  out.attr("has_metadata") = false;

  return out;
}





// [[Rcpp::export]]
Rcpp::List fast_read(const std::string& file_path) {
  igzstream in_file;
  in_file.open( file_path.c_str() );

  std::string content( std::istreambuf_iterator<char>{in_file}, 
                       std::istreambuf_iterator<char>() );

  constexpr auto new_line = '\n';

  std::vector<std::string> raw_lines;
  boost::split(raw_lines, content, [](char c) { return c == new_line; } );

  const int n_lines = raw_lines.size();

  std::vector<const rapidjson::Value&> docs(n_lines);
  // docs.reserve(n_lines);
  // for (auto v : docs) {
    // v = new rapidjson::Value;
  // }

  tweetio::TweetDF2 tweets(n_lines);
  // tweetio::PulseMeta metadata(n_lines);

  // std::vector<std::string> text(n_lines);
  // vec_chr text(n_lines);


  Progress progress(n_lines, true);
  
  omp_set_num_threads( 15 );

#pragma omp parallel for
  for (int i = 0; i < n_lines; ++i) {
    progress.increment();
    
    rapidjson::Document parsed_json;
    parsed_json.Parse( raw_lines[i].c_str() );
    const rapidjson::Value& val = parsed_json;
    docs[i] = val;
    // docs[i].Parse( raw_lines[i].c_str() );

    // if ( parsed_json["doc"].FindMember("id_str") == parsed_json["doc"].MemberEnd() ) {
    //   continue;
    // }
    
    // tweets.push( parsed_json["doc"], i);

  }

  // vec_chr text2(n_lines, NA_STRING);
  // for (int i = 0; i < n_lines; ++i) {
  //   if ( text[i] != "") {
  //     text2[i] = Rcpp::String( text[i] );
  //   }
  // }


  // using Rcpp::_;
  // Rcpp::List out = Rcpp::List::create(
  //   _["text"] = text2
  //   // _["metadata"] = metadata.to_r()
  // );  

  // out.attr("has_metadata") = true;

  return tweets.to_r(n_lines);
}


  // rapidjson::Document parsed_json;
  // rapidjson::StringStream stream( content.c_str() );
  // while ( !parsed_json.ParseStream<rapidjson::kParseStopWhenDoneFlag>(stream).HasParseError() ) {
  //   progress.increment();
  //   tweets.push( parsed_json["doc"] );
  // }
  // // int i = 0;
  // for (auto& line_string : raw_lines)


// [[Rcpp::export]]
Rcpp::List read_tweets_impl(const std::string& file_path) {
  const TweetFileType file_type = detect_file_type(file_path);

  switch (file_type) {
    case TweetFileType::pulse_nested_doc:
      return read_tweets<TweetFileType::pulse_nested_doc>(file_path);
      // return fast_read(file_path);

    case TweetFileType::pulse_array:
      return read_tweets<TweetFileType::pulse_array>(file_path);
    
    case TweetFileType::twitter_api_stream:
      return read_tweets<TweetFileType::twitter_api_stream>(file_path);
    
    
    case TweetFileType::unknown:
      Rcpp::warning("Unknown data type`.");
      return R_NilValue;
  }

  Rcpp::warning("Unknown data type`.");
  return R_NilValue;
}
/*** R

*/
