#include <rapidjson/filereadstream.h>

#include <knapply/structures.hpp>
#include <knapply/utils.hpp>

#include "gzstream.h"

#include <progress.hpp>
#include <progress_bar.hpp>



std::pair<std::string, int> inspect_data(const std::string& file_path) {
  // returns "type" and # of lines in file

  igzstream in_file;
  in_file.open( file_path.c_str() );

  const char first_char = in_file.peek();
  if (first_char == '[') {
    in_file.close();
    return std::make_pair<std::string, int>("big_array", 0);
  }
  
  std::string type = "unknown";
  std::string line_string;
  rapidjson::Document parsed_json;

  std::getline(in_file, line_string);
  rapidjson::StringStream stream( line_string.c_str() );
  rapidjson::ParseResult ok = parsed_json.ParseStream(stream);

  if (!ok) { // try second line...
    std::getline(in_file, line_string);
    rapidjson::StringStream stream( line_string.c_str() );
    rapidjson::ParseResult ok = parsed_json.ParseStream(stream);
    if (!ok) {
      in_file.close();
      Rcpp::stop("parsing error");
    }
  }

  if ( parsed_json["id_str"].IsString() || parsed_json["delete"]["status"]["id_str"].IsString() ) {
    type = "normal";
  }


  if ( parsed_json["doc"].IsObject() ) {
    type = "nested_doc";
  }

  if (type == "unknown") {
    return std::make_pair<std::string, int>("unknown", 0);
  }

  int n_lines = 1; // already consumed a line
  while ( std::getline(in_file, line_string) ) {
    n_lines++;
  }

  in_file.close();

  return std::pair<std::string, int>(type, n_lines);
}


Rcpp::List read_tweets_nested_doc(const std::string& file_path, const int& n_lines) {
  Progress progress(n_lines, true);

  knapply::TweetDF tweets(n_lines);
  knapply::TraptorMeta metadata(n_lines);
  
  std::string line_string;

  igzstream in_file;
  in_file.open( file_path.c_str() );
  
  rapidjson::Document parsed_json;

  int i = 0;
  while ( std::getline(in_file, line_string) ) {
    rapidjson::StringStream stream( line_string.c_str() );
    parsed_json.ParseStream(stream);
    
    progress.increment();
    
    const rapidjson::Value& doc( parsed_json["doc"] );
    
    if ( !doc["id_str"].IsString() ) {
      continue;
    }
    
    tweets.push(doc, i);
    metadata.push(parsed_json, i);

    i++;
  }

  in_file.close();

  using Rcpp::_;
  return Rcpp::List::create(
    _["tweets"] = tweets.to_r(i),
    _["metadata"] = metadata.to_r(i)
  );
}


Rcpp::List read_tweets_normal(const std::string& file_path, const int& n_lines) {
  Progress progress(n_lines, true);

  knapply::TweetDF res(n_lines);
  
  std::string line_string;
  igzstream in_file;
  in_file.open(file_path.c_str());

  int i = 0;
  while ( std::getline(in_file, line_string) ) {
    rapidjson::StringStream stream( line_string.c_str() );
    rapidjson::Document parsed_json;
    parsed_json.ParseStream(stream);
    
    progress.increment();
    
    if ( !parsed_json["id_str"].IsString() ) {
      continue;
    }
    
    res.push(parsed_json, i++);
  }

  in_file.close();

  return res.to_r(i);
}


Rcpp::List read_tweets_big_array(const std::string& file_path) {
  std::ifstream in_file;
  in_file.open(file_path);

  std::string content;
  in_file.seekg(0, std::ios::end);
  content.resize( in_file.tellg() );
  in_file.seekg(0, std::ios::beg);
  in_file.read( &content[0], content.size() );
  in_file.close();

  rapidjson::StringStream stream( content.c_str() );
  rapidjson::Document parsed_json;
  
  rapidjson::ParseResult ok = parsed_json.ParseStream(stream);
  if (!ok) {
    Rcpp::stop("parsing error");
  }

  const int n( parsed_json.Size() );
  knapply::TweetDF tweets(n);
  knapply::TraptorMeta metadata(n);
  Progress progress(n, true);

  int i = 0;
  for ( auto& val : parsed_json.GetArray() ) {
    const rapidjson::Value& doc( val["_source"]["doc"] );
    
    if ( !doc["id_str"].IsString() ) {
      continue;
    }

    tweets.push(doc, i++);
    metadata.push(doc, i);

  }

  in_file.close();

  using Rcpp::_;
  return Rcpp::List::create(
    _["tweets"] = tweets.to_r(i),
    _["metadata"] = metadata.to_r(i)
  );
}



// [[Rcpp::export]]
SEXP read_tweets_(const std::string& file_path) {
  const auto inspection( inspect_data(file_path) );

  if (inspection.first == "nested_doc") {
    return read_tweets_nested_doc(file_path, inspection.second);
  }

  if (inspection.first == "normal") {
    return read_tweets_normal(file_path, inspection.second);
  }

  if (inspection.first == "big_array") {
    return read_tweets_big_array(file_path);
  }

  Rcpp::warning("Unknown data type`.");
  return R_NilValue;
}


// [[Rcpp::export]]
Rcpp::List prep_bbox_(const Rcpp::List& bbox_coords) {
  const int n( bbox_coords.length() );

  Rcpp::List out = Rcpp::List(n);

  vec_dbl current_in;

  const vec_chr current_out_class = vec_chr{"XY", "POLYGON", "sfg"};
  constexpr int valid_length = 8;

  for (int i = 0; i < n; ++i) {
    current_in = bbox_coords[i];
    if (Rcpp::na_omit(current_in).length() != valid_length) {
      out[i] = vec_dbl(0);
      continue;
    }

    Rcpp::NumericMatrix current_mat(5, 2);

    current_mat[0] = current_in[0];
    current_mat[1] = current_in[2];
    current_mat[2] = current_in[4];
    current_mat[3] = current_in[6];
    current_mat[4] = current_in[0];

    current_mat[5] = current_in[1];
    current_mat[6] = current_in[3];
    current_mat[7] = current_in[5];
    current_mat[8] = current_in[7];
    current_mat[9] = current_in[1];

    Rcpp::List current_out = Rcpp::List::create(current_mat);
    current_out.attr("class") = current_out_class;

    out[i] = current_out;
  }

  return out;
}


/*** R

*/
