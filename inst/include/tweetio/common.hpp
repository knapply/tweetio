#ifndef __TWEETIO__COMMON_HPP__
#define __TWEETIO__COMMON_HPP__


// #define SIMDJSON_EXCEPTIONS 0


#include "rcpp-compat.hpp"

#include <Rcpp.h>

#include <charconv>

#include "third-party/simdjson/simdjson.h"


#ifdef __cpp_lib_filesystem
#include <filesystem>
namespace fs = std::filesystem;
#elif defined(_WIN32)
#include <experimental/filesystem>
using fs = std::experimental::filesystem;
#else
#include "third-party/ghc/filesystem.hpp"
namespace fs = ghc::filesystem;
#endif


namespace tweetio {


static inline constexpr auto NA_INTEGER64 =
    LLONG_MIN; // std::numeric_limits<int64_t>::min();
static inline constexpr auto VERBOSE = true;
static inline constexpr auto QUIET   = false;


using vec_int64     = std::vector<int64_t>;
using vec_str       = std::vector<std::string>;
using vec_lgl       = std::vector<bool>;
using vec_dbl       = std::vector<double>;
using vec_int       = std::vector<int>;
using vec_vec_str   = std::vector<std::vector<std::string>>;
using vec_vec_int64 = std::vector<std::vector<int64_t>>;
using vec_vec_dbl   = std::vector<std::vector<double>>;


template <typename T> inline constexpr auto mold_na() {
  if constexpr (std::is_same_v<T, std::string>) {
    return std::string("");
  }
  if constexpr (std::is_same_v<T, double>) {
    return NA_REAL;
  }
  if constexpr (std::is_same_v<T, int64_t>) {
    return NA_INTEGER64;
  }
  if constexpr (std::is_same_v<T, int>) {
    return NA_INTEGER;
  }
  if constexpr (std::is_same_v<T, bool>) {
    return NA_LOGICAL;
  }
}


template <typename iter_T> inline SEXP as_dttm(iter_T first, iter_T last) {
  auto out          = Rcpp::NumericVector(first, last);
  out.attr("class") = Rcpp::CharacterVector::create("POSIXct", "POSIXt");
  out.attr("tzone") = "UTC";
  return out;
}


} // namespace tweetio


#endif
