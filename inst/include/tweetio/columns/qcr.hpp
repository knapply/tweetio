#ifndef __TWEETIO__COLUMNS__QCR_HPP__
#define __TWEETIO__COLUMNS__QCR_HPP__

#include "column.hpp"


namespace tweetio::columns::qcr {


template <typename T, typename inner_T>
inline constexpr auto campaign_tags_col_spec(const std::string_view col_name,
                                             const std::string_view pointer) {
  auto init = [pointer](auto x) -> T {
    if (auto [array, error] =
            x.at_pointer("/campaign_tags").template get<simdjson::dom::array>();
        !error) {
      if (const R_xlen_t n = std::size(array); n > 0) {
        std::vector<std::string> out(n);
        std::size_t              i = 0;
        for (auto&& val : array) {
          out[i++] = to<inner_T>(val.at_pointer(pointer));
        }
        return out;
      }
    }

    return T{mold_na<inner_T>()};
  };

  return Column<T, decltype(init)>(col_name, init);
}

// clang-format off
inline auto campaign_ids = campaign_tags_col_spec<vec_str, std::string>("campaign_ids", "/campaignId");
inline auto emotion_confidence = col_spec<double>("emotion_confidence", "/meta/emotion/0/results/0/confidence");
inline auto emotion_value = col_spec<std::string>("emotion_value", "/meta/emotion/0/results/0/value");

inline auto geo_point_type = col_spec<std::string>("geo_point_type", "/meta/geo_point/0/attrbs/type");
inline auto geo_point_confidence = col_spec<double>("geo_point_confidence", "/meta/geo_point/0/results/0/confidence");
inline auto geo_point_lat = col_spec<double>("geo_point_lat", "/meta/geo_point/0/results/0/value/lat");
inline auto geo_point_lon = col_spec<double>("geo_point_lon", "/meta/geo_point/0/results/0/value/lon");

inline auto sentiment_type = col_spec<std::string>("sentiment_type", "/meta/sentiment/0/attribs/type");
inline auto sentiment_confidence = col_spec<double>("sentiment_confidence", "/meta/sentiment/0/results/0/confidence");
inline auto sentiment_value = col_spec<std::string>("sentiment_value", "/meta/sentiment/0/results/0/value");
// clang-format on


inline auto qcr = std::tuple{
    campaign_ids,

    geo_point_confidence, geo_point_lat,        geo_point_lon,

    sentiment_type,       sentiment_confidence, sentiment_value,

    emotion_confidence,   emotion_value,
};


} // namespace tweetio::columns::qcr


#endif
