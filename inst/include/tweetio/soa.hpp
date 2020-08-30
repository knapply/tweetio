// #ifndef __TWEETIO__SOA_HPP__
// #define __TWEETIO__SOA_HPP__


// #include "common.hpp"
// #include "json.hpp"


// #include <progress.hpp>


// namespace tweetio::soa {


// template <typename... Ts> class SoA {
//   std::tuple<Ts...> cols_;
//   std::vector<std::string_view> col_names_;
//   std::size_t n_rows = 0;

// public:
//   explicit SoA(std::tuple<Ts...> cols) : cols_(cols) {
//     std::apply(
//         [=](auto&&... args) {
//           ((this->col_names_.emplace_back(args.col_name)), ...);
//         },
//         cols_);
//   }

//   constexpr void reserve(std::size_t n) {
//     std::apply([&n](auto&&... args) { ((args.reserve(n)), ...); }, cols_);
//   }

//   template <typename T> void push(T x) {
//     std::apply([&x](auto&&... args) { ((args.push(x)), ...); }, cols_);
//     n_rows++;
//   }

//   SEXP as_list() const {
//     Rcpp::List out;
//     std::apply([&out](auto&&... args) { ((out.push_back(args.data_)), ...); },
//                cols_);
//     out.attr("names") =
//         Rcpp::CharacterVector(std::cbegin(col_names_), std::cend(col_names_),
//                               [](auto x) { return std::string(x); });
//     return out;
//   }

//   SEXP as_data_frame() const {
//     auto out = this->as_list();
//     out.attr("class") = "data.frame";
//     out.attr("row.names") = Rcpp::seq(1, n_rows);
//     return out;
//   }
// };


// template <typename T, typename F> struct Column {
//   std::vector<T> data_;
//   std::string_view col_name;
//   F get_val;
//   bool enabled_;

//   constexpr Column(std::string_view _col_name, F _get_val, const bool enabled)
//       : col_name(_col_name), get_val(_get_val), enabled_(enabled){};

//   constexpr void reserve(std::size_t n) { data_.reserve(n); }
//   void push(simdjson::dom::element x) { data_.emplace_back(get_val(x)); }
// };


// template <typename F>
// constexpr auto column_spec(const std::string_view& col_name,
//                            F value_getter,
//                            const bool enabled) {
//   return Column<std::invoke_result_t<F, simdjson::dom::element>,
//                 decltype(value_getter)>(col_name, value_getter, enabled);
// }


// template <typename... Ts>
// inline constexpr auto filter_tuple(std::tuple<Ts...> tup) {
//   constexpr auto out = std::apply(
//       [](auto... ts) {
//         return std::tuple_cat(
//             std::conditional_t<(decltype(ts)::value > 3),
//                                std::tuple<decltype(ts)>, std::tuple<>>{}...);
//       },
//       tup);
//   return out;
// }


// } // namespace tweetio::soa

// #endif
