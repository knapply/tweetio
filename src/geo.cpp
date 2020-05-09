#include <Rcpp.h>

typedef Rcpp::Vector<STRSXP> vec_chr;
typedef Rcpp::Vector<LGLSXP> vec_lgl;
typedef Rcpp::Vector<INTSXP> vec_int;
typedef Rcpp::Vector<REALSXP> vec_dbl;

bool has_valid_coords(const vec_dbl& bbox, const bool lon_lat = true) {
  // Not only are these problematic to visualize, but bounding boxes exceeding
  // these limits never make sense in the context of the author's metadata and
  // content of the tweet. My impression is that these are simply bad data.
  if (bbox.length() != 8) {
    return false;
  }

  constexpr double min_lon = -179;
  constexpr double max_lon = 179;
  constexpr double min_lat = -89;
  constexpr double max_lat = 89;

  if (lon_lat) {
    return bbox[0] >= min_lon && bbox[0] <= max_lon && bbox[1] >= min_lat &&
           bbox[1] <= max_lat && bbox[2] >= min_lon && bbox[2] <= max_lon &&
           bbox[3] >= min_lat && bbox[3] <= max_lat && bbox[4] >= min_lon &&
           bbox[4] <= max_lon && bbox[5] >= min_lat && bbox[5] <= max_lat &&
           bbox[6] >= min_lon && bbox[6] <= max_lon && bbox[7] >= min_lat &&
           bbox[7] <= max_lat;
  } else {
    return bbox[0] >= min_lon && bbox[0] <= max_lon &&  //
           bbox[1] >= min_lon && bbox[1] <= max_lon &&  //
           bbox[2] >= min_lon && bbox[2] <= max_lon &&  //
           bbox[3] >= min_lon && bbox[3] <= max_lon &&  //
           bbox[4] >= min_lat && bbox[4] <= max_lat &&  //
           bbox[5] >= min_lat && bbox[5] <= max_lat &&  //
           bbox[6] >= min_lat && bbox[6] <= max_lat &&  //
           bbox[7] >= min_lat && bbox[7] <= max_lat;
  }
}

// [[Rcpp::export]]
Rcpp::LogicalVector is_valid_bbox(const Rcpp::List& bbox_coords,
                                  const bool lon_lat = true) {
  const auto n(bbox_coords.length());
  vec_lgl out(n);

  for (R_xlen_t i = 0; i < n; ++i) {
    if (TYPEOF(bbox_coords[i]) != REALSXP) {
      out[i] = false;
    } else {
      vec_dbl current_bbox = bbox_coords[i];
      out[i] = has_valid_coords(current_bbox, lon_lat);
    }
  }

  return out;
}

// [[Rcpp::export]]
Rcpp::List prep_bbox(const Rcpp::List& bbox_coords, const bool lon_lat = true) {
  const int n(bbox_coords.length());
  const auto current_out_class = vec_chr::create("XY", "POLYGON", "sfg");

  Rcpp::List out = Rcpp::List(n);

  // vec_dbl current_in;

  for (R_xlen_t i = 0; i < n; ++i) {
    vec_dbl current_in = bbox_coords[i];

    if (current_in.length() != 8) {
      Rcpp::List empty_geom;
      empty_geom.attr("class") = current_out_class;
      out[i] = empty_geom;
      continue;
    }

    Rcpp::NumericMatrix current_mat(5, 2);

    if (lon_lat) {
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
    } else {
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
    }

    Rcpp::List current_out = Rcpp::List::create(current_mat);
    current_out.attr("class") = current_out_class;

    out[i] = current_out;
  }

  return out;
}
