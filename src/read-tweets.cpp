#include <knapply/structures.hpp>
#include <knapply/utils.hpp>

#include <gzstream/gzstream.h>

#include <progress.hpp>
#include <progress_bar.hpp>

Rcpp::List read_tweets_nested_doc(const std::string& file_path) {
  i32 n_lines = knapply::count_lines<igzstream>(file_path);
  
  Progress progress(n_lines, true);

  knapply::TweetDF res(n_lines);
  
  std::string line_string;
  igzstream in_file;
  in_file.open(file_path.c_str());
  
  rapidjson::Document parsed_json;

  i32 i = 0;
  while (std::getline(in_file, line_string)) {
    rapidjson::StringStream stream( line_string.c_str() );
    
    parsed_json.ParseStream(stream);
    
    progress.increment();
    
    const rapidjson::Value& doc(parsed_json["doc"]);
    
    if ( !doc["id_str"].IsString() ) {
      continue;
    }
    
    res.push(doc, i++);
  }

  in_file.close();

  return res.to_r();
}




Rcpp::List read_tweets_normal(const std::string& file_path) {
  i32 n_lines = knapply::count_lines<igzstream>(file_path);
  
  Progress progress(n_lines, true);

  knapply::TweetDF res(n_lines);
  
  std::string line_string;
  igzstream in_file;
  in_file.open(file_path.c_str());

  i32 i = 0;
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

  return res.to_r();
}




// [[Rcpp::export]]
SEXP read_tweets_(const std::string& file_path, const std::string& type) {
  if (type == "nested_doc") {
    return read_tweets_nested_doc(file_path);
  }

  if (type == "normal") {
    return read_tweets_normal(file_path);
  }

  Rcpp::warning("Unknown `type`.");
  return R_NilValue;
}





/*** R

*/
