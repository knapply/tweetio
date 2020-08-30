#ifndef TWEETIO__JSON_HPP
#define TWEETIO__JSON_HPP


// #include <boost/lexical_cast.hpp>
// #include <boost/date_time.hpp>

#include <chrono>

#include "common.hpp"


namespace tweetio {

template <typename T, typename result_T> inline T to(result_T&& x) {
  if (!x.error()) {
    if (x.first.template is<uint64_t>() && !x.first.template is<int64_t>()) {
      Rcpp::Rcout << "uint64_t found!!!!!!!!!!!!!!!!!" << std::endl;
    }
    if constexpr (std::is_same_v<T, std::string>) {
      if (auto [res, err] = x.template get<std::string_view>(); !err) {
        return std::string(res);
      }
    } else if constexpr (std::is_same_v<T, int>) {
      if (auto [res, err] = x.template get<int64_t>(); !err) {
        return static_cast<int>(res);
      }
    } else {
      if (auto [res, err] = x.template get<T>(); !err) {
        return res;
      }
    }
  }
  return mold_na<T>();
}


inline double
to_timestamp_ms(simdjson::simdjson_result<simdjson::dom::element> x) {
  if (!x.error() && x.first.is<std::string_view>()) {
    return std::atof(x.first.get<const char*>().take_value());
  }
  return NA_REAL;
}


inline double
to_created_at(simdjson::simdjson_result<simdjson::dom::element> x) {
  if (!x.error() && x.first.is<std::string_view>()) {
    if (auto sv = x.get<std::string_view>().take_value(); sv.size() == 30) {
      std::tm            ptm{};
      std::istringstream ss(sv.data());
      //   ss.imbue(std::locale("en_US.UTF-8"));
      ss >> std::get_time(&ptm, "%a %b %d %H:%M:%S +0000 %Y");
      if (!ss.fail()) {
        return static_cast<double>(
            std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::from_time_t(std::mktime(&ptm))
                    .time_since_epoch())
                .count());
      }
    }
  }
  return NA_REAL;
}

inline std::vector<std::string>
get_entities(simdjson::dom::element  x,
             const std::string_view& entity,
             const std::string_view& inner_name) {
  for (auto loc : std::array<std::string_view, 2>{"/extended_tweet/entities",
                                                  "/entities"}) {
    if (auto [array, error] =
            x.at_pointer(loc).at_pointer(entity).get<simdjson::dom::array>();
        !error) {
      auto out = std::vector<std::string>();
      for (auto element : array) {
        out.emplace_back(to<std::string>(element.at_pointer(inner_name)));
      }
      return out;
    }
  }

  return vec_str();
}


template <typename... Ts>
inline std::string find_chr(simdjson::dom::element x, Ts... targets) {
  for (auto&& loc : {std::forward<Ts>(targets)...}) {
    if (auto [element, error] = x.at_pointer(loc); !error) {
      if (auto [res, err] = element.template get<std::string_view>(); !err) {
        return std::string(res);
      }
    }
  }
  return "";
}


// inline std::string find_chr2(simdjson::dom::element x,
//                              std::vector<std::string_view> targets) {
//   for (auto&& loc : targets) {
//     if (auto [element, error] = x.at_pointer(loc); !error) {
//       if (auto [res, err] = element.template get<std::string_view>(); !err) {
//         return std::string(res);
//       }
//     }
//   }
//   return "";
// }

// template <typename element_T, typename... Ts>
// inline std::string find_chr2(element_T x, Ts... targets) {
//   for (auto&& loc : {std::forward<Ts>(targets)...}) {
//     if (auto [element, error] = x.at_pointer(loc); !error) {
//       if (auto [res, err] = element.template get<std::string_view>(); !err) {
//         return std::string(res);
//       }
//     }
//   }
//   return "";
// }

/**
 * @brief Get the bbox object, but set up to become an R (column-major) matrix
downstream.
 *
{
  "coordinates": [ // <<<<<< `get_bbox()` starts here
    [
      [
        -74.026675,
        40.683935
      ],
      [
        -74.026675,
        40.877483
      ],
      [
        -73.910408,
        40.877483
      ],
      [
        -73.910408,
        40.3935
      ]
    ]
  ]
}
 *
 */
inline vec_dbl get_bbox(simdjson::simdjson_result<simdjson::dom::element> x) {
  if (!x.error()) {
    if (auto [array1, array1_error] = x.first.get<simdjson::dom::array>();
        !array1_error && std::size(array1) == 1) {
      if (auto [array2, array2_error] =
              (*std::begin(array1)).get<simdjson::dom::array>();
          !array2_error && std::size(array2) == 4) {
        vec_dbl     out(8);
        std::size_t j = 0;
        for (auto array3 : array2) {
          std::size_t i = 0;
          for (auto element : array3.get<simdjson::dom::array>().first) {
            out[i + j] = element.get<double>().take_value();
            i += 4;
          }
          j++;
        }
        return out;
      }
    }
  }
  return vec_dbl{NA_REAL};
}


} // namespace tweetio


#endif
