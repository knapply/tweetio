#include <rapidjson/filereadstream.h>

#include <knapply/structures.hpp>
#include <knapply/utils.hpp>

#include "gzstream.h"

#include <progress.hpp>
#include <progress_bar.hpp>


// returns "type" and # of lines in file
std::pair<std::string, int> inspect_data(const std::string& file_path) {
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

  if (!ok) {
    in_file.close();
    Rcpp::stop("parsing error");
  }

  if ( parsed_json["id_str"].IsString() || parsed_json["delete"]["status"]["id_str"].IsString() ) {
    type = "normal";
  }


  // const rapidjson::Value& doc( parsed_json["doc"] );
  // if ( doc.IsObject() ) {
  if ( parsed_json["doc"].IsObject() ) {
    type = "nested_doc";
  }

  if (type == "unknown") {
    return std::make_pair<std::string, int>("unknown", 0);
  }

  i32 n_lines = 1; // already consumed a line
  while ( std::getline(in_file, line_string) ) {
    n_lines++;
  }
  

  in_file.close();

  return std::pair<std::string, int>(type, n_lines);
}


Rcpp::List read_tweets_nested_doc(const std::string& file_path, const i32& n_lines) {
  Progress progress(n_lines, true);

  knapply::TweetDF res(n_lines);
  
  std::string line_string;

  igzstream in_file;
  in_file.open( file_path.c_str() );
  
  rapidjson::Document parsed_json;

  i32 i = 0;
  while ( std::getline(in_file, line_string) ) {
    rapidjson::StringStream stream( line_string.c_str() );
    
    parsed_json.ParseStream(stream);
    
    progress.increment();
    
    const rapidjson::Value& doc( parsed_json["doc"] );
    
    if ( !doc["id_str"].IsString() ) {
      continue;
    }
    
    res.push(doc, i++);
  }

  in_file.close();

  return res.to_r(i);
}


Rcpp::List read_tweets_normal(const std::string& file_path, const i32& n_lines) {
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

  i32 n( parsed_json.Size() );
  knapply::TweetDF res(n);
  Progress progress(n, true);

  i32 i = 0;
  for ( auto& val : parsed_json.GetArray() ) {
    const rapidjson::Value& doc( val["_source"]["doc"] );
    
    if ( !doc["id_str"].IsString() ) {
      continue;
    }

    res.push(doc, i++);
  }

  return res.to_r(i);
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


//fff [[Rcpp::export]]
// void read_tweets_test(const std::string& file_path) {
//   igzstream in_file;
//   in_file.open( file_path.c_str() );

//   std::string line_text;
//   std::string raw_text("[");

//   while (std::getline(in_file, line_text)) {
//     if (line_text.at(0) != '{' || line_text.at( line_text.size() - 1 ) != '}') {
//       continue;
//     }
//     if (line_text.at( line_text.size() - 1 ) == '\n') {
//       raw_text.pop_back();
//     }
//     raw_text += line_text + ",";
//   }
//   raw_text.pop_back();
//   raw_text += "]";

//   // return raw_text;
//   // raw_text.insert(raw_text.size(), "]");

//   rapidjson::StringStream stream( raw_text.c_str() );
//   rapidjson::Document parsed_json;
//   rapidjson::ParseResult ok = parsed_json.ParseStream(stream);

//   if (!ok) {
//     Rcpp::stop("parsing error");
//   }

//   Rcpp::Rcout << parsed_json.Size() << std::endl;
// }

// Rcpp::List read_tweets_big_array(const std::string& file_path) {
//   FILE* in_file = fopen(file_path.c_str(), "rb");
//   char read_buffer[1000000];

//   rapidjson::FileReadStream stream( in_file, read_buffer, sizeof(read_buffer) );
//   rapidjson::Document parsed_json;

//   rapidjson::ParseResult ok = parsed_json.ParseStream(stream);
//   if (!ok) {
//     fclose(in_file);
//     Rcpp::stop("parsing error");
//   }

//   i32 n( parsed_json.Size() );
//   knapply::TweetDF res(n);
//   Progress progress(n, true);

//   i32 i = 0;
//   for ( auto& val : parsed_json.GetArray() ) {
//     const rapidjson::Value& doc( val["_source"]["doc"] );

//     if ( !doc["id_str"].IsString() ) {
//       continue;
//     }

//     res.push(doc, i++);
//   }

//   fclose(in_file);

//   return res.to_r(i);
// }


/*** R

*/
