#ifndef __TWEETIO__SOAS__UTILS_HPP__
#define __TWEETIO__SOAS__UTILS_HPP__


#include "../common.hpp"


#include "../columns/column.hpp"


namespace tweetio::soa {


template <class Tuple1, class Tuple2, class F, std::size_t... I>
F for_each2_impl(Tuple1&& t1, Tuple2&& t2, F&& f, std::index_sequence<I...>) {
  return (void)std::initializer_list<int>{
             (std::forward<F>(f)(std::get<I>(std::forward<Tuple1>(t1)),
                                 std::get<I>(std::forward<Tuple2>(t2))),
              0)...},
         f;
}

template <class Tuple1, class Tuple2, class F>
constexpr decltype(auto) for_each2(Tuple1&& t1, Tuple2&& t2, F&& f) {
  return for_each2_impl(
      std::forward<Tuple1>(t1), std::forward<Tuple2>(t2), std::forward<F>(f),
      std::make_index_sequence<
          std::tuple_size<std::remove_reference_t<Tuple1>>::value>{});
}


template <typename... Ts> struct SoA {
  std::tuple<Ts...>                           cols_;
  std::array<std::string_view, sizeof...(Ts)> col_names_;

  constexpr explicit SoA(std::tuple<Ts...> cols) noexcept : cols_(cols) {
    std::size_t i = 0;
    std::apply(
        [=, &i](auto&&... args) {
          ((this->col_names_[i++] = args.col_name), ...);
        },
        cols_);
  }


  constexpr void reserve(std::size_t n) noexcept {
    std::apply([&n](auto&&... args) { ((args.reserve(n)), ...); }, cols_);
  }


  template <typename T> constexpr void bind_row(T x) noexcept {
    std::apply([&x](auto&&... args) { ((args.emplace_back(x)), ...); }, cols_);
  }


  void bind_rows(SoA<Ts...> soa2) noexcept {
    for_each2(this->cols_, soa2.cols_, [](auto&& x, auto&& y) {
      x.data_.reserve(std::size(x.data_) + std::size(y.data_));
      x.data_.insert(std::end(x.data_),
                     std::make_move_iterator(std::begin(y.data_)),
                     std::make_move_iterator(std::end(y.data_)));
    });
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
}; // namespace tweetio::soa

template <typename... T1s, typename... T2s>
inline constexpr auto bind(SoA<T1s...>&& soa1, SoA<T2s...>&& soa2) {
  return std::tuple_cat(soa1.cols_, soa2.cols_);
}


template <typename... Ts> inline SEXP as_list(std::tuple<Ts...> x) {
  Rcpp::List out(sizeof...(Ts));

  R_xlen_t i = 0;
  std::apply([&out, &i](auto&&... args) { ((out[i++] = args.data_), ...); }, x);

  i = 0;
  Rcpp::CharacterVector col_names(sizeof...(Ts));
  std::apply(
      [&col_names, &i](auto&&... args) {
        ((col_names[i++] = std::string(args.col_name)), ...);
      },
      x);

  out.attr("names") = col_names;

  return out;
}


} // namespace tweetio::soa


#endif
