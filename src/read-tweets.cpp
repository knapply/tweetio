#include <rapidjson/filereadstream.h>
#include <regex>
#include <knapply/structures.hpp>
#include <knapply/utils.hpp>

#include "gzstream.h"

#include <progress.hpp>
#include <progress_bar.hpp>


// [[Rcpp::export]]
Rcpp::List prep_bbox_(const Rcpp::List& bbox_coords) {
  const int n( bbox_coords.length() );
  const vec_chr current_out_class = vec_chr{"XY", "POLYGON", "sfg"};

  vec_dbl test_coords = bbox_coords[0];
  const bool col_major = test_coords[0] == test_coords[1];

  Rcpp::List out = Rcpp::List(n);

  vec_dbl current_in;

  constexpr int valid_length = 8;

  for (int i = 0; i < n; ++i) {
    current_in = bbox_coords[i];
    if (Rcpp::na_omit(current_in).length() != valid_length) {
      out[i] = vec_dbl(0);
      continue;
    }

    Rcpp::NumericMatrix current_mat(5, 2);

    if (col_major) {
      current_mat[0] = current_in[0];
      current_mat[1] = current_in[1];
      current_mat[2] = current_in[2];
      current_mat[3] = current_in[3];
      current_mat[4] = current_in[0];

      current_mat[5] = current_in[4];
      current_mat[6] = current_in[5];
      current_mat[7] = current_in[6];
      current_mat[8] = current_in[7];
      current_mat[9] = current_in[4];

    } else {
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

    }

    Rcpp::List current_out = Rcpp::List::create(current_mat);
    current_out.attr("class") = current_out_class;

    out[i] = current_out;
  }

  return out;
}


// Rcpp::List flatten_date_users_(const Rcpp::DoubleVector& date, 
//                                std::vector< std::vector <std::string> > user_id, 
//                                std::vector< std::vector<std::string> > screen_name) {
//   const R_xlen_t n = date.size();

//   R_xlen_t out_n = 0; 
//   for (R_xlen_t i = 0; i < n; ++i) {
//     for (R_xlen_t v : user_id[i]) {
//       if (v != "NA") {
//         out_n++;
//       }
//     }
//   }

//   std::vector<double> out_date; 
//   out_date.reserve(out_n);
  
//   std::vector<std::string> out_uid;
//   out_uid.reserve(out_n);

//   std::vector<std::string> out_sn;
//   out_sn.reserve(out_n);


//   for (R_xlen_t i = 0; i < n; ++i) {
//     for (R_xlen_t j = 0; j < user_id[i].size(); ++j) {
//       if (user_id[i][j] != "NA") {
//         out_date.push_back( date[i] );
//         out_uid.push_back( user_id[i][j] );
//         out_sn.push_back( screen_name[i][j] );
//       }
//     }
//   }

//   using Rcpp::_;
//   Rcpp::List out = Rcpp::List::create(
//     _["created_at"] = out_date,
//     _["user_id"] = out_uid,
//     _["screen_name"] = out_sn
//   );
//   out.attr("row.names") = Rcpp::seq_len(out_n);
//   out.attr("class") = "data.frame";

//   return out;
// }


template <typename T>
SEXP unnest_entities_impl(const T& tracker,
                                const Rcpp::CharacterVector& source,
                                const Rcpp::List& target,
                                const Rcpp::CharacterVector& col_names) {
 const R_xlen_t n = tracker.length(); 
  R_xlen_t out_n = 0;

  for (R_xlen_t i = 0; i < n; ++i) {
    const vec_chr target_i = target[i];

    for (int j = 0; j < target_i.length(); ++j) {
      if (target_i[j].get() != NA_STRING) {
        out_n++;
      }
    }

  }

  vec_chr source2(out_n); 
  vec_chr target2(out_n); 
  T tracker2(out_n);
  tracker2.attr("class") = tracker.attr("class");

  R_xlen_t k = 0;
  for (R_xlen_t i = 0; i < n; ++i) {
    const vec_chr target_i = target[i];

    for (R_xlen_t j = 0; j < target_i.size(); ++j) {

      if (target_i[j].get() != NA_STRING) {
        source2[k] = source[i];
        target2[k] = target_i[j];
        tracker2[k] = tracker[i];
        k++;
      }

    }

  }

  using Rcpp::_;
  Rcpp::List out = Rcpp::List::create(
    source2,
    target2,
    tracker2
  );
  out.attr("names") = col_names;
  out.attr("row.names") = Rcpp::seq_len(out_n);
  out.attr("class") = "data.frame";

  return out;
}



// [[Rcpp::export]]
SEXP unnest_entities_(const SEXP& tracker,
                      const Rcpp::CharacterVector& source,
                      const Rcpp::List& target,
                      const Rcpp::CharacterVector& col_names,
                      const bool is_dttm = true) {
  switch ( TYPEOF(tracker) ) {
    case STRSXP:
      return unnest_entities_impl<Rcpp::CharacterVector>(tracker, source, target, col_names);
    case REALSXP:
      return unnest_entities_impl<Rcpp::NumericVector>(tracker, source, target, col_names);
  }
  return R_NilValue;
}







template <typename T>
SEXP unnest_entities2_impl(const T& tracker,
                           const Rcpp::List& source,
                           const Rcpp::List& target,
                           const Rcpp::CharacterVector& col_names) {
 const R_xlen_t n = tracker.length(); 
  R_xlen_t out_n = 0;

  for (R_xlen_t i = 0; i < n; ++i) {
    const vec_chr target_i = target[i];

    for (int j = 0; j < target_i.length(); ++j) {
      if (target_i[j].get() != NA_STRING) {
        out_n++;
      }
    }

  }

  vec_chr source2(out_n); 
  vec_chr target2(out_n); 
  T tracker2(out_n);
  tracker2.attr("class") = tracker.attr("class");

  R_xlen_t k = 0;
  for (R_xlen_t i = 0; i < n; ++i) {
    const vec_chr source_i = source[i];
    const vec_chr target_i = target[i];

    for (R_xlen_t j = 0; j < target_i.size(); ++j) {

      if (target_i[j].get() != NA_STRING) {
        source2[k] = source_i[j];
        target2[k] = target_i[j];
        tracker2[k] = tracker[i];
        k++;
      }

    }

  }

  using Rcpp::_;
  Rcpp::List out = Rcpp::List::create(
    source2,
    target2,
    tracker2
  );
  out.attr("names") = col_names;
  out.attr("row.names") = Rcpp::seq_len(out_n);
  out.attr("class") = "data.frame";

  return out;
}



// [[Rcpp::export]]
SEXP unnest_entities2_(const SEXP& tracker,
                      const Rcpp::List& source,
                      const Rcpp::List& target,
                      const Rcpp::CharacterVector& col_names) {
  switch (TYPEOF(tracker)) {
    case STRSXP:
      return unnest_entities2_impl<vec_chr>(tracker, source, target, col_names);
    case REALSXP:
      return unnest_entities2_impl<vec_dbl>(tracker, source, target, col_names);
  }
  return R_NilValue;
}


















////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OVERHAUL
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

  knapply::TweetDF tweets(n_lines);
  knapply::TraptorMeta metadata(n_lines);

  
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
  return Rcpp::List::create(
    _["tweets"] = tweets.to_r(),
    _["metadata"] = metadata.to_r()
  );
}


template<>
Rcpp::List read_tweets<TweetFileType::pulse_array>(const std::string& file_path) {
  std::ifstream in_file;
  in_file.open(file_path);

  std::string content;
  in_file.seekg(0, std::ios::end);
  content.resize( in_file.tellg() );
  in_file.seekg(0, std::ios::beg);
  in_file.read( &content[0], content.size() );
  in_file.close();

  rapidjson::Document parsed_json;
  
  rapidjson::ParseResult ok = parsed_json.Parse( content.c_str() );
  if (!ok) {
    Rcpp::stop("parsing error");
  }

  const int n( parsed_json.Size() );
  knapply::TweetDF tweets(n);
  knapply::TraptorMeta metadata(n);
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
  return Rcpp::List::create(
    _["tweets"] = tweets.to_r(),
    _["metadata"] = metadata.to_r()
  );
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

  knapply::TweetDF tweets( raw_json.size() );
  knapply::TraptorMeta metadata( raw_json.size() );
  Progress progress(raw_json.size(), true);

  for ( const auto& line : raw_json) {
    progress.increment();

    rapidjson::Document parsed_json;
    rapidjson::ParseResult ok = parsed_json.Parse( line.c_str() );
    if (!ok || parsed_json.FindMember("id_str") == parsed_json.MemberEnd() ) {
      continue;
    }
    
    tweets.push(parsed_json);

  }

  return tweets.to_r();
}


// [[Rcpp::export]]
Rcpp::List read_tweets_impl(const std::string& file_path) {
  const TweetFileType file_type = detect_file_type(file_path);

  switch (file_type) {
    case TweetFileType::pulse_nested_doc:
      return read_tweets<TweetFileType::pulse_nested_doc>(file_path);

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
