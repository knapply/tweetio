#ifndef __TWEETIO__RCPP_COMPAT_HPP__
#define __TWEETIO__RCPP_COMPAT_HPP__

#include <Rcpp.h>

namespace Rcpp {

// FIXME why are values still being truncated???
// template <> SEXP wrap(const std::vector<int64_t>& obj) {
//   const auto          n = std::size(obj);
//   std::vector<double> temp(n);
//   std::memcpy(&(temp[0]), &(obj[0]), n * sizeof(double));
//   Rcpp::NumericVector out(std::cbegin(temp), std::cend(temp));
// //   std::memcpy(&(out[0]), &(obj[0]), n * sizeof(double));
//   out.attr("class") = Rcpp::CharacterVector::create("integer64");
//   return out;
// }


template <>
inline SEXP
wrap<std::vector<std::string>>(const std::vector<std::string>& obj) {
  return Rcpp::CharacterVector(std::begin(obj), std::end(obj), [](auto x) {
    if (!x.empty()) {
      if (x.erase(std::remove_if(std::begin(x), std::end(x),
                                 [](char c) { return c == 0x04; }),
                  std::end(x));
          std::count_if(std::cbegin(x), std::cend(x),
                        [](char c) { return c != ' '; }) > 0) {
        return Rcpp::String(x.data());
      }
    }

    return Rcpp::String(NA_STRING);
    //   return out;
    // }
    // return !x.empty() ? Rcpp::String(x.c_str()) : NA_STRING;
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
