#include <rapidjson/document.h>

namespace knapply {  // knapply

inline Rcpp::String get_chr(const rapidjson::Value& x) {
  return x.IsString() ? Rcpp::String( x.GetString() ) : NA_STRING;
}

inline Rcpp::String get_chr_check(const rapidjson::Value& a, const rapidjson::Value& b) {
  if (a.IsString()) {
    return Rcpp::String( a.GetString() );
  }
  if (b.IsString()) {
    return Rcpp::String( b.GetString() );
  }
  return NA_STRING;
}


inline int get_int(const rapidjson::Value& x) {
  return x.IsInt() ? x.GetInt() : NA_INTEGER;
}

inline double get_dbl(const rapidjson::Value& x) {
  return x.IsNumber() ? x.GetDouble() : NA_REAL;
}


inline bool get_lgl(const rapidjson::Value& x) {
  return x.IsBool() ? x.GetBool() : NA_LOGICAL;
}


inline vec_chr map_entities(const rapidjson::Value& x, const std::string& entity, const std::string& inner_name) {
  const int ext_n = x["extended_tweet"]["entities"][ entity.c_str() ].Size();
  const int reg_n = x["entities"][ entity.c_str() ].Size();

  if (ext_n == 0 && reg_n == 0) {
    return vec_chr{NA_STRING};
  }

  if (ext_n != 0) {
    const rapidjson::Value& entities = x["extended_tweet"]["entities"][ entity.c_str() ];
    vec_chr out(ext_n);
    for (int i = 0; i < ext_n; ++i) {
      out[i] = get_chr( entities[i][ inner_name.c_str() ] );
    }

    return out;
  } 
  
  const rapidjson::Value& entities = x["entities"][ entity.c_str() ];
  vec_chr out(reg_n);
  for (int i = 0; i < reg_n; ++i) {
    out[i] = get_chr( entities[i][ inner_name.c_str() ] );
  }

  return out;
}


inline vec_dbl get_bbox(const rapidjson::Value& x) {
  if (x.Size() == 0) {
    return vec_dbl(0);
  }

  const auto bbox = x.GetArray();
  vec_dbl out(8);

  out[0] = bbox[0].GetArray()[0].GetArray()[0].GetDouble();
  out[1] = bbox[0].GetArray()[0].GetArray()[1].GetDouble();

  out[2] = bbox[0].GetArray()[1].GetArray()[0].GetDouble();
  out[3] = bbox[0].GetArray()[1].GetArray()[1].GetDouble();

  out[4] = bbox[0].GetArray()[2].GetArray()[0].GetDouble();
  out[5] = bbox[0].GetArray()[2].GetArray()[1].GetDouble();

  out[6] = bbox[0].GetArray()[3].GetArray()[0].GetDouble();
  out[7] = bbox[0].GetArray()[3].GetArray()[1].GetDouble();


  return out;
}


inline Rcpp::List get_meta_results(const rapidjson::Value& x, const std::string& outer_name) {
  const auto default_val = Rcpp::List(vec_chr{NA_STRING});

  const auto top_level = x[outer_name.c_str()].GetArray();
  if (top_level.Size() == 0) {
    return default_val;
  }
  const auto target = top_level[0].GetObject();

  const auto results = target.FindMember("results");
  if (results == target.MemberEnd()) {
    return default_val;
  }

  const auto res = results->value.GetArray();
  const int out_n = res.Size();
  if (out_n == 0) {
    return default_val;
  }

  vec_chr out(out_n);
  for (int i = 0; i < out_n; ++i) {
    out[i] = get_chr( res[i] );
  }

  return Rcpp::List(out);
}


inline vec_chr get_nested_meta_results(const rapidjson::Value& x, 
                                       const std::string& outer_name, 
                                       const std::string& inner_name, 
                                       const bool is_metadata = false) {
  const auto default_val = vec_chr{NA_STRING};

  const auto& top_level = x[outer_name.c_str()];

  if (!top_level.IsArray() || top_level.GetArray().Size() == 0) {
    return default_val;
  }
  
  const auto& target = top_level[0].GetObject()["results"];
  if (!target.IsArray() || target.GetArray().Size() == 0) {
    return default_val;
  }

  if ( !target.IsArray() ) {
    return default_val;
  }

  const auto& results = target.GetArray();
  const int out_n = results.Size();
  if (out_n == 0) {
    return default_val;
  }

  vec_chr out(out_n);

  for (int i = 0; i < out_n; ++i) {
    const auto& results_obj = target[i];

    if (is_metadata) {
      if ( !results_obj["metadata"].IsObject() ) {
        out[i] = NA_STRING;
        continue;
      }

      const auto& metadata = results_obj["metadata"].GetObject();
      out[i] = get_chr( metadata[ inner_name.c_str() ] );
      continue;
    }

    if ( !results_obj.IsObject() ) {
      out[i] = NA_STRING;
      continue;
    } 
    
    if (results_obj.FindMember( inner_name.c_str() ) == results_obj.MemberEnd()) {
      out[i] = NA_STRING;
      continue;
    }

    out[i] = get_chr( results_obj[inner_name.c_str()] );
  }

  return out;
}


} // knapply

