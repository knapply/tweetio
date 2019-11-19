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

#ifndef TWEETIO_TYPEDEFS_H
#define TWEETIO_TYPEDEFS_H

#include <Rcpp.h>

namespace tweetio {

typedef Rcpp::Vector<REALSXP> vec_dbl;
typedef Rcpp::Vector<STRSXP>  vec_chr;
typedef Rcpp::Vector<LGLSXP>  vec_lgl;
typedef Rcpp::Vector<INTSXP>  vec_int;

} // namespace tweetio

#endif