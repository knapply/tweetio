#ifndef __TWEETIO__COLUMNS__COLUMN_HPP__
#define __TWEETIO__COLUMNS__COLUMN_HPP__


#include "../common.hpp"

#include "../json.hpp"


#include <tuple>

namespace tweetio {


namespace columns {


// using namespace std::literals::string_view_literals;


template <typename T, typename F, typename... Args> struct Column {
  std::vector<T>   data_;
  std::string_view col_name;
  F                get_val;

  constexpr Column(std::string_view _col_name, F _get_val)
      : col_name(_col_name), get_val(_get_val){};

  constexpr void reserve(std::size_t n) { data_.reserve(n); }

  void emplace_back(simdjson::dom::element x) {
    data_.emplace_back(get_val(x));
  }
};


template <typename T>
constexpr auto val_getter(const std::string_view pointer) noexcept {
  return [pointer](auto x) -> T { return to<T>(x.at_pointer(pointer)); };
}

template <typename T, typename F>
constexpr auto val_getter(const std::string_view pointer,
                          F                      custom_getter) noexcept {
  return [pointer, custom_getter](auto x) -> T {
    return custom_getter(x.at_pointer(pointer));
  };
}


template <typename T>
constexpr auto col_spec(const std::string_view col_name,
                        const std::string_view pointer) noexcept {
  return Column<T, decltype(val_getter<T>(pointer))>(col_name,
                                                     val_getter<T>(pointer));
}


template <typename T, typename F>
constexpr auto col_spec(const std::string_view col_name,
                        const std::string_view pointer,
                        F                      custom_getter) {
  return Column<T, decltype(val_getter<T>(pointer, custom_getter))>(
      col_name, val_getter<T>(pointer, custom_getter));
}


template <typename T, typename F, typename... Args>
constexpr auto
col_spec(const std::string_view col_name, std::tuple<Args...> args, F getter) {
  return Column<T, F, Args...>(col_name, val_getter<T, F>(getter, args));
}


template <typename T, typename... Ts>
constexpr auto custom_col_spec(const std::string_view col_name,
                               Ts... targets) noexcept {
  auto init = [targets...](auto x) -> T {
    for (auto&& loc : {targets...}) {
      if (auto res = to<T>(x.at_pointer(loc)); res != mold_na<T>()) {
        return res;
      }
    }
    return mold_na<T>();
  };
  return Column<T, decltype(init)>(col_name, init);
}


} // namespace columns


} // namespace tweetio


#endif
