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

#include <Rcpp.h>

typedef Rcpp::Vector<STRSXP> vec_chr;
typedef Rcpp::Vector<LGLSXP> vec_lgl;
typedef Rcpp::Vector<INTSXP> vec_int;
typedef Rcpp::Vector<REALSXP> vec_dbl;

// [[Rcpp::export]]
Rcpp::List prep_bbox_(const Rcpp::List& bbox_coords) {
  const int n( bbox_coords.length() );
  const vec_chr current_out_class = vec_chr{"XY", "POLYGON", "sfg"};

  vec_dbl test_coords = bbox_coords[0];
  const bool col_major = test_coords[0] != test_coords[2];

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