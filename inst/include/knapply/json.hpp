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


inline i32 get_int(const rapidjson::Value& x) {
  return x.IsInt() ? x.GetInt() : NA_INTEGER;
}

inline f64 get_dbl(const rapidjson::Value& x) {
  return x.IsNumber() ? x.GetDouble() : NA_REAL;
}


inline bool get_lgl(const rapidjson::Value& x) {
  return x.IsBool() ? x.GetBool() : NA_LOGICAL;
}


inline vec_chr map_entities(const rapidjson::Value& x, const std::string& entity, const std::string& inner_name) {
  const i32 ext_n = x["extended_tweet"]["entities"][ entity.c_str() ].Size();
  const i32 reg_n = x["entities"][ entity.c_str() ].Size();

  if (ext_n == 0 && reg_n == 0) {
    return vec_chr(0);
  }

  if (ext_n != 0) {
    const rapidjson::Value& entities = x["extended_tweet"]["entities"][ entity.c_str() ];
    vec_chr out(ext_n);
    for (i32 i = 0; i < ext_n; ++i) {
      out[i] = get_chr( entities[i][ inner_name.c_str() ] );
    }

    return out;
  } 
  
  const rapidjson::Value& entities = x["entities"][ entity.c_str() ];
  vec_chr out(reg_n);
  for (i32 i = 0; i < reg_n; ++i) {
    out[i] = get_chr( entities[i][ inner_name.c_str() ] );
  }

  return out;
}


inline vec_dbl get_bbox(const rapidjson::Value& x) {
  if (x.Size() == 0) {
    return vec_dbl(0);
  }

  auto bbox = x.GetArray();
  auto corner1 = bbox[0].GetArray()[0].GetArray();
  auto corner2 = bbox[0].GetArray()[1].GetArray();
  auto corner3 = bbox[0].GetArray()[2].GetArray();
  auto corner4 = bbox[0].GetArray()[3].GetArray();
  // auto corner2 = bbox[1].GetArray();
  // auto corner3 = bbox[2].GetArray();
  // auto corner4 = bbox[3].GetArray();

  vec_dbl out = vec_dbl(8);
  // out[0] = corner1[0].GetDouble();
  // out[1] = corner1[1].GetDouble();

  // out[2] = corner2[0].GetDouble();
  // out[3] = corner2[1].GetDouble();

  // out[4] = corner3[0].GetDouble();
  // out[5] = corner3[1].GetDouble();

  // out[6] = corner4[0].GetDouble();
  // out[7] = corner4[1].GetDouble();
  
  out[0] = corner1[0].GetDouble();
  out[1] = corner1[1].GetDouble();

  out[2] = corner2[0].GetDouble();
  out[3] = corner2[1].GetDouble();

  out[4] = corner3[0].GetDouble();
  out[5] = corner3[1].GetDouble();

  out[6] = corner4[0].GetDouble();
  out[7] = corner4[1].GetDouble();
  


  return out;
}


} // knapply