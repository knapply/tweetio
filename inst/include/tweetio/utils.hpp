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

template <typename stream_T>
inline size_t count_lines(const std::string& file_path) {
  stream_T in_file;
  in_file.open(file_path.c_str());

  std::size_t out = 0;
  std::string line;

  while (std::getline(in_file, line)) {
    ++out;
  }

  in_file.close();

  return out;
}

template <typename T>
inline int count_digits(const T x) {
  if (x < 0) {
    return count_digits(-x);
  }

  constexpr T x1 = 1e1;
  constexpr T x2 = 1e2;
  constexpr T x3 = 1e3;
  constexpr T x4 = 1e4;
  constexpr T x5 = 1e5;
  constexpr T x6 = 1e6;
  constexpr T x7 = 1e7;
  constexpr T x8 = 1e8;
  constexpr T x9 = 1e9;

  return x < x1
             ? 1
             : x < x2
                   ? 2
                   : x < x3
                         ? 3
                         : x < x4
                               ? 4
                               : x < x5
                                     ? 5
                                     : x < x6
                                           ? 6
                                           : x < x7
                                                 ? 7
                                                 : x < x8 ? 8 : x < x9 ? 9 : 10;
}

void finalize_df(Rcpp::List& x, const vec_chr& col_names, const int n_rows) {
  const int n_digits = count_digits(n_rows);

  vec_chr row_names(n_rows);
  for (int i = 0; i < n_rows; ++i) {
    char name[n_digits];
    sprintf(&(name[0]), "%d", i);
    row_names[i] = name;
  }

  x.attr("names") = col_names;
  x.attr("row.names") = row_names;
  x.attr("class") = "data.frame";
}

// vec_chr strip_controls(vec_chr x) {
//   return stri_replace_all_regex(
//     x, vec_chr("[[:cntrl:]]"), vec_chr("")
//   );
// }

// vec_chr extract_source(vec_chr x) {
//   return stri_extract_first_regex(
//     x, vec_chr("(?<=>).*?(?=</a>$)")
//   );
// }

}  // namespace tweetio

#endif
