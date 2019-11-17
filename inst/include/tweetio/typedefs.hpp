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