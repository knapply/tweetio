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


#ifndef TWEETIO_UTILS_H
#define TWEETIO_UTILS_H

namespace tweetio {

template<typename stream_T>
R_xlen_t count_lines(const std::string& file_path) {
  stream_T in_file;
  in_file.open( file_path.c_str() );
  
  std::size_t out = 0;
  std::string line;

  while (std::getline(in_file, line) ) {
    ++out;
  }

  in_file.close();

  return out;
}


int count_digits(const int x) {
  if (x < 0) {
    return count_digits(-x);
  }

  constexpr int x1  = 1e1;
  constexpr int x2  = 1e2;
  constexpr int x3  = 1e3;
  constexpr int x4  = 1e4;
  constexpr int x5  = 1e5;
  constexpr int x6  = 1e6;
  constexpr int x7  = 1e7;
  constexpr int x8  = 1e8;
  constexpr int x9  = 1e9;
  // constexpr R_xlen_t x10 = 1e10;
  // constexpr R_xlen_t x11 = 1e11;
  // constexpr R_xlen_t x12 = 1e12;
  // constexpr R_xlen_t x13 = 1e13;
  // constexpr R_xlen_t x14 = 1e14;
  // constexpr R_xlen_t x15 = 1e15;
  // constexpr R_xlen_t x16 = 1e16;
  // constexpr R_xlen_t x17 = 1e17;
  // constexpr R_xlen_t x18 = 1e18;  


  if (x < x1) {
    return 1;
  } else if (x < x2) {
    return 2;
  } else if (x < x3) {
    return 3;
  } else if (x < x4) {
    return 4;
  } else if (x < x5) {
    return 5;
  } else if (x < x6) {
    return 6;
  } else if (x < x7) {
    return 7;
  } else if (x < x8) {
    return 8;
  } else if (x < x9) {
    return 9;
  } else {
    return 10;
  }
  // else if (x < x10) {
  //   return 10;
  // } else if (x < x11) {
  //   return 11;
  // } else if (x < x12) {
  //   return 12;
  // } else if (x < x13) {
  //   return 13;
  // } else if (x < x14) {
  //   return 14;
  // } else if (x < x15) {
  //   return 15;
  // } else if (x < x16) {
  //   return 16;
  // } else if (x < x17) {
  //   return 17;
  // } else if (x < x18) {
  //   return 18;
  // } else {
  //   return 19;
  // }
}


void finalize_df(Rcpp::List& x, const int& n_rows) {
  const int n_digits = count_digits(n_rows);

  vec_chr row_names(n_rows);
  for (int i = 0; i < n_rows; ++i) {
      char name[n_digits];
      sprintf(&(name[0]), "%d", i);
      row_names[i] = name;
  }

  x.attr("row.names") = row_names;
  x.attr("class") = vec_chr{"data.table", "data.frame"};
}


} // namesapce tweetio



#endif
