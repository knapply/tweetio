#ifndef __TWEETIO__RCPP_COMPAT_HPP__
#define __TWEETIO__RCPP_COMPAT_HPP__

#include <Rcpp.h>


namespace Rcpp {


template <>
inline SEXP wrap<std::vector<int64_t>>(const std::vector<int64_t>& obj) {
  const R_xlen_t      n = std::size(obj);
  Rcpp::NumericVector out(n);
  std::memcpy(&(out[0]), &(obj[0]), n * sizeof(double));
  out.attr("class") = "integer64";
  return out;
}

template <>
inline SEXP
wrap<std::vector<std::string>>(const std::vector<std::string>& obj) {
  return Rcpp::CharacterVector(std::cbegin(obj), std::cend(obj), [](auto x) {
    return !x.empty() ? Rcpp::String(x.c_str()) : NA_STRING;
  });
}


} // namespace Rcpp


namespace tweetio {


inline SEXP as_dttm(std::vector<double>& x) {
  const R_xlen_t      n = std::size(x);
  Rcpp::NumericVector out(n);
  std::memcpy(&(out[0]), x.data(), n * sizeof(double));
  out.attr("class") = Rcpp::CharacterVector::create("POSIXct", "POSIXt");
  out.attr("tzone") = "UTC";
  return out;
}


} // namespace tweetio


#endif