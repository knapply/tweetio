#ifndef __TWEETIO__COLUMNS__TWITTER_HPP__
#define __TWEETIO__COLUMNS__TWITTER_HPP__

#include "column.hpp"


namespace tweetio {


namespace columns {


namespace twitter {


template <typename T, typename inner_T>
constexpr auto entity_col_spec(const std::string_view col_name,
                               const std::string_view entity,
                               const std::string_view inner_name) noexcept {
  auto init = [entity, inner_name](auto x) -> T {
    for (auto loc : {"/extended_tweet/entities", "/entities"}) {
      if (auto [array, error] = x.at_pointer(loc)
                                    .at_pointer(entity)
                                    .template get<simdjson::dom::array>();
          !error) {
        if (const auto n = std::size(array); n > 0) {
          std::vector<inner_T> out;
          out.reserve(n);
          for (auto element : array) {
            out.emplace_back(to<inner_T>(element.at_pointer(inner_name)));
          }
          return out;
        }
      }
    }
    return vec_str{""};
  };

  return Column<T, decltype(init)>(col_name, init);
}


template <typename T, typename inner_T>
constexpr auto bbox_col_spec(const std::string_view col_name,
                             const std::string_view pointer) noexcept {
  auto init = [pointer](auto x) -> T {
    if (auto [array1, array1_error] =
            x.at_pointer(pointer).template get<simdjson::dom::array>();
        !array1_error && std::size(array1) == 1) {
      if (auto [array2, array2_error] =
              (*std::begin(array1)).template get<simdjson::dom::array>();
          !array2_error && std::size(array2) == 4) {
        T           out(8);
        std::size_t j = 0;
        for (auto array3 : array2) {
          std::size_t i = 0;
          for (auto element :
               array3.template get<simdjson::dom::array>().first) {
            out[i + j] = element.template get<inner_T>().first;
            i += 4;
          }
          j++;
        }
        return out;
      }
    }
    return T{mold_na<inner_T>()};
  };

  return Column<T, decltype(init)>(col_name, init);
}


// clang-format off


/* 
 * auto user_id              = col_spec<int64_t>("user_id", "/user/id");
 * auto status_id            = col_spec<int64_t>("status_id", "/id");
 */
inline auto user_id              = col_spec<std::string>("user_id", "/user/id_str");
inline auto status_id            = col_spec<std::string>("status_id", "/id_str");

inline auto created_at           = col_spec<double>("created_at", "/created_at", to_created_at);
inline auto screen_name          = col_spec<std::string>("screen_name", "/user/screen_name");
inline auto text                 = custom_col_spec<std::string>("text", "/extended_tweet/text", "/full_text", "/text");
inline auto source               = col_spec<std::string>("source", "/source");

/*
 * auto reply_to_status_id   = col_spec<int64_t>("reply_to_status_id", "/in_reply_to_status_id");
 * auto reply_to_user_id     = col_spec<int64_t>("reply_to_user_id", "/in_reply_to_user_id");
 */
inline auto reply_to_status_id   = col_spec<std::string>("reply_to_status_id", "/in_reply_to_status_id_str");
inline auto reply_to_user_id     = col_spec<std::string>("reply_to_user_id", "/in_reply_to_user_id_str");

inline auto reply_to_screen_name = col_spec<std::string>("reply_to_screen_name", "/in_reply_to_screen_name");
inline auto is_quote             = col_spec<bool>("is_quote", "/is_quote_status");
inline auto is_retweeted         = col_spec<bool>("is_retweeted", "/retweeted");
inline auto lang                 = col_spec<std::string>("lang", "/lang");
inline auto name                 = col_spec<std::string>("name", "/user/name");
inline auto location             = col_spec<std::string>("location", "/user/location");
inline auto description          = col_spec<std::string>("description", "/user/description");
inline auto url                  = col_spec<std::string>("url", "/user/url");
inline auto protected_           = col_spec<bool>("protected", "/user/protected");
inline auto followers_count      = col_spec<int>("followers_count", "/user/followers_count");
inline auto friends_count        = col_spec<int>("friends_count", "/user/friends_count");
inline auto listed_count         = col_spec<int>("listed_count", "/user/listed_count");
inline auto statuses_count       = col_spec<int>("statuses_count", "/user/statuses_count");
inline auto favourites_count     = col_spec<int>("favourites_count", "/user/favourites_count");
inline auto account_created_at   = col_spec<double>("account_created_at", "/user/created_at", to_created_at);
inline auto verified             = col_spec<bool>("verified", "/user/verified");
inline auto account_lang         = col_spec<std::string>("account_lang", "/user/lang");
inline auto profile_banner_url   = col_spec<std::string>("profile_banner_url", "/user/profile_banner_url");
inline auto profile_image_url    = col_spec<std::string>("profile_image_url", "/user/profile_image_url");
inline auto contributors_enabled = col_spec<bool>("contributors_enabled", "/user/contributors_enabled");

inline auto hashtags             = entity_col_spec<vec_str, std::string>("hashtags", "/hashtags", "/text");
inline auto urls_expanded_url   = entity_col_spec<vec_str, std::string>("urls_expanded_url", "/urls", "/expanded_url");
inline auto media_url            = entity_col_spec<vec_str, std::string>("media_url", "/media", "/media_url");
inline auto media_type           = entity_col_spec<vec_str, std::string>("media_type", "/media", "/type");
inline auto mentions_user_id     = entity_col_spec<vec_str, std::string>("mentions_user_id", "/user_mentions", "/id_str");
inline auto mentions_screen_name = entity_col_spec<vec_str, std::string>("mentions_screen_name", "/user_mentions", "/screen_name");


inline auto quoted_status_id       = col_spec<std::string>("quoted_status_id", "/quoted_status/id_str");
inline auto quoted_text            = custom_col_spec<std::string>("quoted_text", "/quoted_status/extended_tweet/text", "/quoted_status/full_text", "/quoted_status/text");
inline auto quoted_created_at      = col_spec<double>("quoted_created_at", "/quoted_status/created_at", to_created_at);
inline auto quoted_source          = col_spec<std::string>("quoted_source", "/quoted_status/source");
inline auto quoted_favorite_count  = col_spec<int>("quoted_favorite_count", "/quoted_status/favorite_count");
inline auto quoted_quoted_count    = col_spec<int>("quoted_quoted_count", "/quoted_status/retweet_count");
inline auto quoted_user_id         = col_spec<std::string>("quoted_user_id", "/quoted_status/user/id_str");
inline auto quoted_screen_name     = col_spec<std::string>("quoted_screen_name", "/quoted_status/user/screen_name");
inline auto quoted_name            = col_spec<std::string>("quoted_name", "/quoted_status/user/name");
inline auto quoted_followers_count = col_spec<int>("quoted_followers_count", "/quoted_status/user/followers_count");
inline auto quoted_friends_count   = col_spec<int>("quoted_friends_count", "/quoted_status/user/friends_count");
inline auto quoted_statuses_count  = col_spec<int>("quoted_statuses_count", "/quoted_status/user/statuses_count");
inline auto quoted_location        = col_spec<std::string>("quoted_location", "/quoted_status/user/location");
inline auto quoted_description     = col_spec<std::string>("quoted_description", "/quoted_status/user/description");


inline auto retweet_status_id       = col_spec<std::string>("retweet_status_id", "/retweeted_status/id_str");
inline auto retweet_text            = custom_col_spec<std::string>("retweet_text", "/retweeted_status/extended_tweet/text", "/retweeted_status/full_text", "/retweeted_status/text");
inline auto retweet_created_at      = col_spec<double>("retweet_created_at", "/retweeted_status/created_at", to_created_at);
inline auto retweet_source          = col_spec<std::string>("retweet_source", "/retweeted_status/source");
inline auto retweet_favorite_count  = col_spec<int>("retweet_favorite_count", "/retweeted_status/favorite_count");
inline auto retweet_retweet_count   = col_spec<int>("retweet_retweet_count", "/retweeted_status/retweet_count");
inline auto retweet_user_id         = col_spec<std::string>("retweet_user_id", "/retweeted_status/user/id_str");
inline auto retweet_screen_name     = col_spec<std::string>("retweet_screen_name", "/retweeted_status/user/screen_name");
inline auto retweet_name            = col_spec<std::string>("retweet_name", "/retweeted_status/user/name");
inline auto retweet_followers_count = col_spec<int>("retweet_followers_count", "/retweeted_status/user/followers_count");
inline auto retweet_friends_count   = col_spec<int>("retweet_friends_count", "/retweeted_status/user/friends_count");
inline auto retweet_statuses_count  = col_spec<int>("retweet_statuses_count", "/retweeted_status/user/statuses_count");
inline auto retweet_location        = col_spec<std::string>("retweet_location", "/retweeted_status/user/location");
inline auto retweet_description     = col_spec<std::string>("retweet_description", "/retweeted_status/user/description");

// inline auto retweet_verified        = col_spec<std::string>("retweet_verified", "/retweeted_status/user/verified");

inline auto place_url            = col_spec<std::string>("place_url", "/place/url");
inline auto place_name           = col_spec<std::string>("place_name", "/place/name");
inline auto place_full_name      = col_spec<std::string>("place_full_name", "/place/full_name");
inline auto place_type           = col_spec<std::string>("place_type", "/place/place_type");
inline auto country              = col_spec<std::string>("country", "/place/country");
inline auto country_code         = col_spec<std::string>("country_code", "/place/country_code");
inline auto bbox_coords          = bbox_col_spec<vec_dbl, double>("bbox_coords", "/place/bounding_box/coordinates");

inline auto quoted_place_url            = col_spec<std::string>("quoted_place_url", "/quoted_status/place/url");
inline auto quoted_place_name           = col_spec<std::string>("quoted_place_name", "/quoted_status/place/name");
inline auto quoted_place_full_name      = col_spec<std::string>("quoted_place_full_name", "/quoted_status/place/full_name");
inline auto quoted_place_type           = col_spec<std::string>("quoted_place_type", "/quoted_status/place/place_type");
inline auto quoted_country              = col_spec<std::string>("quoted_country", "/quoted_status/place/country");
inline auto quoted_country_code         = col_spec<std::string>("quoted_country_code", "/quoted_status/place/country_code");
inline auto quoted_bbox_coords          = bbox_col_spec<vec_dbl, double>("quoted_bbox_coords", "/quoted_status/place/bounding_box/coordinates");

inline auto retweet_place_url           = col_spec<std::string>("retweet_place_url", "/retweeted_status/place/url");
inline auto retweet_place_name          = col_spec<std::string>("retweet_place_name", "/retweeted_status/place/name");
inline auto retweet_place_full_name     = col_spec<std::string>("retweet_place_full_name", "/retweeted_status/place/full_name");
inline auto retweet_place_type          = col_spec<std::string>("retweet_place_type", "/retweeted_status/place/place_type");
inline auto retweet_country             = col_spec<std::string>("retweet_country", "/retweeted_status/place/country");
inline auto retweet_country_code        = col_spec<std::string>("retweet_country_code", "/retweeted_status/place/country_code");
inline auto retweet_bbox_coords         = bbox_col_spec<vec_dbl, double>("retweet_bbox_coords", "/retweeted_status/place/bounding_box/coordinates");

// clang-format on


inline auto base = std::tuple{
    user_id,
    status_id,
    created_at,
    screen_name,
    text,
    source,
    reply_to_status_id,
    reply_to_user_id,
    reply_to_screen_name,
    is_quote,
    is_retweeted,
    lang,
    name,
    location,
    description,
    url,
    protected_,
    followers_count,
    friends_count,
    listed_count,
    statuses_count,
    favourites_count,
    account_created_at,
    verified,
    account_lang,
    profile_banner_url,
    profile_image_url,
    contributors_enabled,
    hashtags,
    urls_expanded_url,
    media_url,
    media_type,
    mentions_user_id,
    mentions_screen_name,

    quoted_status_id,
    quoted_text,
    quoted_created_at,
    quoted_source,
    quoted_favorite_count,
    quoted_quoted_count,
    quoted_user_id,
    quoted_screen_name,
    quoted_name,
    quoted_followers_count,
    quoted_friends_count,
    quoted_statuses_count,
    quoted_location,
    quoted_description,

    retweet_status_id,
    retweet_text,
    retweet_created_at,
    retweet_source,
    retweet_favorite_count,
    retweet_retweet_count,
    retweet_user_id,
    retweet_screen_name,
    retweet_name,
    retweet_followers_count,
    retweet_friends_count,
    retweet_statuses_count,
    retweet_location,
    retweet_description,

    place_url,
    place_name,
    place_full_name,
    place_type,
    country,
    country_code,
    bbox_coords,

    quoted_place_url,
    quoted_place_name,
    quoted_place_full_name,
    quoted_place_type,
    quoted_country,
    quoted_country_code,
    quoted_bbox_coords,

    retweet_place_url,
    retweet_place_name,
    retweet_place_full_name,
    retweet_place_type,
    retweet_country,
    retweet_country_code,
    retweet_bbox_coords,
};


// inline auto all_qcr = std::tuple{
//     qcr::campaign_ids,
// };


} // namespace twitter
} // namespace columns
} // namespace tweetio


#endif
