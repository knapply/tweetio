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

  return x < 1e1
             ? 1
             : x < 1e2
                   ? 2
                   : x < 1e3
                         ? 3
                         : x < 1e4
                               ? 4
                               : x < 1e5
                                     ? 5
                                     : x < 1e6
                                           ? 6
                                           : x < 1e7
                                                 ? 7
                                                 : x < 1e8 ? 8
                                                           : x < 1e9 ? 9 : 10;
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
