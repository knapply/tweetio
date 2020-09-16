#ifndef __TWEETIO__COLUMNS__TELEGRAM_HPP__
#define __TWEETIO__COLUMNS__TELEGRAM_HPP__


#include "column.hpp"


namespace tweetio {


namespace columns {

namespace telegram {


constexpr const char* rformats[] = {"%Y-%m-%d %H:%M:%OS", "%Y-%m-%d %H%M%OS"};

inline double
to_date(simdjson::simdjson_result<simdjson::dom::element> x) noexcept {
  if (!x.error() && x.first.is<std::string_view>()) {
    if (auto sv = x.get<std::string_view>().first; sv.size() < 30) {
      std::tm            ptm{};
      std::istringstream ss(sv.data());
      ss >> std::get_time(&ptm, "%Y-%m-%dT%H:%M:%S"); /* 2020-07-17T09:11:56 */
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

// clang-format off
inline auto date = col_spec<double>("date", "/message/date", to_date);
/*  inline auto fwd_from = col_spec<std::string>("fwd_from", "/message/fwd_from"); */
inline auto id = col_spec<std::string>("id", "/message/id");
inline auto media_clazz = col_spec<std::string>("media_clazz", "/message/media/clazz");
inline auto media_type = col_spec<std::string>("media_type", "/message/media/type");
inline auto media_url = col_spec<std::string>("media_url", "/message/media/url");
inline auto reply_to_msg_id = col_spec<std::string>("reply_to_msg_id", "/message/reply_to_msg_id");
inline auto sender = col_spec<std::string>("sender", "/message/sender");
inline auto text = col_spec<std::string>("text", "/message/text");
inline auto to_id = col_spec<int>("to_id", "/message/to/id");
inline auto to_title = col_spec<std::string>("to_title", "/message/to/title");
inline auto to_username = col_spec<std::string>("to_username", "/message/to/username");
inline auto views = col_spec<int>("views", "/message/views");
// clang-format on


inline auto base = std::tuple{
    date,   id,   media_clazz, media_type, media_url,   reply_to_msg_id,
    sender, text, to_id,       to_title,   to_username, views,
};


} // namespace telegram


} // namespace columns


} // namespace tweetio


#endif
