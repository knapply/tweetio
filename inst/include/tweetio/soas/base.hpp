#ifndef __TWEETIO__SOAS__UTILS_HPP__
#define __TWEETIO__SOAS__UTILS_HPP__


#include "../common.hpp"


#include "../columns/column.hpp"


namespace tweetio::soa {


template <typename... Ts> class SoA {
  std::tuple<Ts...>                           cols_;
  std::array<std::string_view, sizeof...(Ts)> col_names_;

public:
  constexpr explicit SoA(std::tuple<Ts...> cols) : cols_(cols) {
    std::size_t i = 0;
    std::apply(
        [=, &i](auto&&... args) {
          ((this->col_names_[i++] = args.col_name), ...);
        },
        cols_);
  }

  constexpr void reserve(std::size_t n) {
    std::apply([&n](auto&&... args) { ((args.reserve(n)), ...); }, cols_);
  }

  template <typename T> constexpr void bind_row(T x) {
    std::apply([&x](auto&&... args) { ((args.emplace_back(x)), ...); }, cols_);
  }

  Rcpp::List as_list() const {
    Rcpp::List out(sizeof...(Ts));

    R_xlen_t i = 0;
    std::apply([&out, &i](auto&&... args) { ((out[i++] = args.data_), ...); },
               cols_);

    out.attr("names") =
        Rcpp::CharacterVector(std::cbegin(col_names_), std::cend(col_names_),
                              [](auto x) { return std::string(x); });

    return out;
  }
};


} // namespace tweetio::soa


#endif
