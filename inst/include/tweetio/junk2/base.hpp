#ifndef TWEETIO__DFS_BASE_HPP
#define TWEETIO__DFS_BASE_HPP

#include "rcpp-compat.hpp"

#include "common.hpp"
#include "json.hpp"
#include "utils.hpp"

// #include <omp.h>

#include <progress.hpp>

namespace tweetio {


class Base_DF {
  vec_str user_id;
  vec_str status_id;
  //   vec_str created_at;
  vec_dbl created_at;
  vec_str screen_name;
  vec_str text;
  vec_str source;
  vec_str reply_to_status_id;
  vec_str reply_to_user_id;
  vec_str reply_to_screen_name;
  vec_lgl is_quote;
  vec_lgl is_retweeted;
  vec_str lang;

  //   vec_dbl timestamp_ms;
  vec_str timestamp_ms;

  vec_str name;
  vec_str location;
  vec_str description;
  vec_str url;
  vec_lgl protected_;
  vec_int followers_count;
  vec_int friends_count;
  vec_int listed_count;
  vec_int statuses_count;
  vec_int favourites_count;
  vec_str account_created_at;
  vec_lgl verified;
  vec_str account_lang;
  vec_str profile_banner_url;
  vec_str profile_image_url;
  vec_lgl contributors_enabled;

  vec_vec_str hashtags;
  vec_vec_str urls_expanded_urls;

  vec_vec_str media_expanded_url;
  vec_vec_str media_url;
  vec_vec_str media_type;

  vec_vec_str mentions_user_id;
  vec_vec_str mentions_screen_name;

  vec_str quoted_status_id;
  vec_str quoted_text;
  vec_str quoted_created_at;
  vec_str quoted_source;
  vec_int quoted_favorite_count;
  vec_int quoted_retweet_count;
  vec_str quoted_user_id;
  vec_str quoted_screen_name;
  vec_str quoted_name;
  vec_int quoted_followers_count;
  vec_int quoted_friends_count;
  vec_int quoted_statuses_count;
  vec_str quoted_location;
  vec_str quoted_description;
  vec_lgl quoted_verified;

  vec_str retweet_status_id;
  vec_str retweet_text;
  vec_str retweet_created_at;
  vec_str retweet_source;
  vec_int retweet_favorite_count;
  vec_int retweet_retweet_count;
  vec_str retweet_user_id;
  vec_str retweet_screen_name;
  vec_str retweet_name;
  vec_int retweet_followers_count;
  vec_int retweet_friends_count;
  vec_int retweet_statuses_count;
  vec_str retweet_location;
  vec_str retweet_description;
  vec_lgl retweet_verified;

  vec_str place_url;
  vec_str place_name;
  vec_str place_full_name;
  vec_str place_type;
  vec_str country;
  vec_str country_code;
  std::vector<std::vector<double>> bbox_coords;

  vec_str retweet_place_url;
  vec_str retweet_place_name;
  vec_str retweet_place_full_name;
  vec_str retweet_place_type;
  vec_str retweet_country;
  vec_str retweet_country_code;
  std::vector<std::vector<double>> retweet_bbox_coords;

  vec_str quoted_place_url;
  vec_str quoted_place_name;
  vec_str quoted_place_full_name;
  vec_str quoted_place_type;
  vec_str quoted_country;
  vec_str quoted_country_code;
  std::vector<std::vector<double>> quoted_bbox_coords;


public:
  Base_DF() = default;

  explicit Base_DF(const std::size_t n)
      : user_id(n),                 // main status
        status_id(n),               //
        created_at(n),              //
        screen_name(n),             //
        text(n),                    //
        source(n),                  //
        reply_to_status_id(n),      //
        reply_to_user_id(n),        //
        reply_to_screen_name(n),    //
        is_quote(n),                //
        is_retweeted(n),            //
        lang(n),                    //
                                    //
        timestamp_ms(n),            // stream timestamp... not status creation
                                    //
        name(n),                    // main user
        location(n),                //
        description(n),             //
        url(n),                     //
        protected_(n),              //
        followers_count(n),         //
        friends_count(n),           //
        listed_count(n),            //
        statuses_count(n),          //
        favourites_count(n),        //
        account_created_at(n),      //
        verified(n),                //
        account_lang(n),            //
        profile_banner_url(n),      //
        profile_image_url(n),       //
        contributors_enabled(n),    //
                                    //
        hashtags(n),                // entities
        urls_expanded_urls(n),      //
        media_expanded_url(n),      //
        media_url(n),               //
        media_type(n),              //
        mentions_user_id(n),        // mentions user
        mentions_screen_name(n),    //
                                    //
        quoted_status_id(n),        // quoted status
        quoted_text(n),             //
        quoted_created_at(n),       //
        quoted_source(n),           //
        quoted_favorite_count(n),   //
        quoted_retweet_count(n),    //
        quoted_user_id(n),          // quoted user
        quoted_screen_name(n),      //
        quoted_name(n),             //
        quoted_followers_count(n),  //
        quoted_friends_count(n),    //
        quoted_statuses_count(n),   //
        quoted_location(n),         //
        quoted_description(n),      //
        quoted_verified(n),         //
                                    //
        retweet_status_id(n),       // retweet status
        retweet_text(n),            //
        retweet_created_at(n),      //
        retweet_source(n),          //
        retweet_favorite_count(n),  //
        retweet_retweet_count(n),   //
        retweet_user_id(n),         // retweet user
        retweet_screen_name(n),     //
        retweet_name(n),            //
        retweet_followers_count(n), //
        retweet_friends_count(n),   //
        retweet_statuses_count(n),  //
        retweet_location(n),        //
        retweet_description(n),     //
        retweet_verified(n),        //
                                    //
        place_url(n),               // main geo
        place_name(n),              //
        place_full_name(n),         //
        place_type(n),              //
        country(n),                 //
        country_code(n),            //
        bbox_coords(n),             //
                                    //
        retweet_place_url(n),       // retweet geo
        retweet_place_name(n),      //
        retweet_place_full_name(n), //
        retweet_place_type(n),      //
        retweet_country(n),         //
        retweet_country_code(n),    //
        retweet_bbox_coords(n),     //
                                    //
        quoted_place_url(n),        // quoted geo
        quoted_place_name(n),       //
        quoted_place_full_name(n),  //
        quoted_place_type(n),       //
        quoted_country(n),          //
        quoted_country_code(n),     //
        quoted_bbox_coords(n)       //
                                    //
        {};                         //

  void reserve(const std::size_t n) {
    user_id.reserve(n);
    status_id.reserve(n);
    created_at.reserve(n);
    screen_name.reserve(n);
    text.reserve(n);
    source.reserve(n);
    reply_to_status_id.reserve(n);
    reply_to_user_id.reserve(n);
    reply_to_screen_name.reserve(n);
    is_quote.reserve(n);
    is_retweeted.reserve(n);
    lang.reserve(n);

    timestamp_ms.reserve(n);

    name.reserve(n);
    location.reserve(n);
    description.reserve(n);
    url.reserve(n);
    protected_.reserve(n);
    followers_count.reserve(n);
    friends_count.reserve(n);
    listed_count.reserve(n);
    statuses_count.reserve(n);
    favourites_count.reserve(n);
    account_created_at.reserve(n);
    verified.reserve(n);
    account_lang.reserve(n);
    profile_banner_url.reserve(n);
    profile_image_url.reserve(n);
    contributors_enabled.reserve(n);

    hashtags.reserve(n);
    urls_expanded_urls.reserve(n);
    media_expanded_url.reserve(n);
    media_url.reserve(n);
    media_type.reserve(n);
    mentions_user_id.reserve(n);
    mentions_screen_name.reserve(n);

    place_url.reserve(n);
    place_name.reserve(n);
    place_full_name.reserve(n);
    place_type.reserve(n);
    country.reserve(n);
    country_code.reserve(n);
    bbox_coords.reserve(n);

    quoted_place_url.reserve(n);
    quoted_place_name.reserve(n);
    quoted_place_full_name.reserve(n);
    quoted_place_type.reserve(n);
    quoted_country.reserve(n);
    quoted_country_code.reserve(n);
    quoted_bbox_coords.reserve(n);
  };

  template <typename element_T> void push(element_T x) {
    // clang-format off
    user_id.emplace_back(/*                  */ to<std::string>(x.at_pointer("/user/id_str")) /*                                             */);
    status_id.emplace_back(/*                */ to<std::string>(x.at_pointer("/id_str")) /*                                                  */);
    created_at.emplace_back(/*               */ to_created_at(x.at_pointer("/created_at")) /*                                            */);
    screen_name.emplace_back(/*              */ to<std::string>(x.at_pointer("/user/screen_name")) /*                                      */);
    text.emplace_back(/*                     */ find_chr(x, "/text", "/full_text", "/extended_tweet/text") /*               */);
    source.emplace_back(/*                   */ to<std::string>(x.at_pointer("/source")) /*                                                */);
    reply_to_status_id.emplace_back(/*       */ to<std::string>(x.at_pointer("/in_reply_to_status_id_str")) /*                               */);
    reply_to_user_id.emplace_back(/*         */ to<std::string>(x.at_pointer("/in_reply_to_user_id_str")) /*                                 */);
    reply_to_screen_name.emplace_back(/*     */ to<std::string>(x.at_pointer("/in_reply_to_screen_name")) /*                               */);
    is_quote.emplace_back(/*                 */ to<bool>(x.at_pointer("/is_quote_status")) /*                                       */);
    is_retweeted.emplace_back(/*             */ to<bool>(x.at_pointer("/retweeted")) /*                                             */);
    lang.emplace_back(/*                     */ to<std::string>(x.at_pointer("/lang")) /*                                                  */);
 

// Rcpp::Rcout << "b" << std::endl;

    timestamp_ms.emplace_back(/*             */ to<std::string>(x.at_pointer("/timestamp_ms")) /*                                 */);
 
    name.emplace_back(/*                     */ to<std::string>(x.at_pointer("/user/name")) /*                                             */);
    location.emplace_back(/*                 */ to<std::string>(x.at_pointer("/user/location")) /*                                         */);
    description.emplace_back(/*              */ to<std::string>(x.at_pointer("/user/description")) /*                                      */);
    url.emplace_back(/*                      */ to<std::string>(x.at_pointer("/user/url")) /*                                              */);
    protected_.emplace_back(/*               */ to<bool>(x.at_pointer("/user/protected")) /*                                        */);
    followers_count.emplace_back(/*          */ to<int>(x.at_pointer("/user/followers_count")) /*                                  */);
    friends_count.emplace_back(/*            */ to<int>(x.at_pointer("/user/friends_count")) /*                                    */);
    listed_count.emplace_back(/*             */ to<int>(x.at_pointer("/user/listed_count")) /*                                     */);
    statuses_count.emplace_back(/*           */ to<int>(x.at_pointer("/user/statuses_count")) /*                                   */);
    favourites_count.emplace_back(/*         */ to<int>(x.at_pointer("/user/favourites_count")) /*                                 */);
    account_created_at.emplace_back(/*       */ to<std::string>(x.at_pointer("/user/created_at")) /*                                       */);
    verified.emplace_back(/*                 */ to<bool>(x.at_pointer("/user/verified")) /*                                         */);
    account_lang.emplace_back(/*             */ to<std::string>(x.at_pointer("/user/lang")) /*                                             */);
    profile_banner_url.emplace_back(/*       */ to<std::string>(x.at_pointer("/user/profile_banner_url")) /*                               */);
    profile_image_url.emplace_back(/*        */ to<std::string>(x.at_pointer("/user/profile_image_url")) /*                                */);
    contributors_enabled.emplace_back(/*     */ to<bool>(x.at_pointer("/user/contributors_enabled")) /*                             */);
 
    hashtags.emplace_back(/*                 */ get_entities(x, "/hashtags", "/text") /*                                   */);
    urls_expanded_urls.emplace_back(/*       */ get_entities(x, "/urls", "/expanded_url") /*                               */);
 
    media_expanded_url.emplace_back(/*       */ get_entities(x, "/media", "/expanded_url") /*                              */);
    media_url.emplace_back(/*                */ get_entities(x, "/media", "/media_url") /*                                 */);
    media_type.emplace_back(/*               */ get_entities(x, "/media", "/type") /*                                      */);
    mentions_user_id.emplace_back(/*         */ get_entities(x, "/user_mentions", "/id_str") /*                          */);
    mentions_screen_name.emplace_back(/*     */ get_entities(x, "/user_mentions", "/screen_name") /*                       */);

    // Rcpp::Rcout << "c" << std::endl;

    if (auto [e, error] = x.at_pointer("/quoted_status"); !error) {
        quoted_status_id.emplace_back(/*         */ to<std::string>(e.at_pointer("/quoted_status_id_str"))            /*                                 */);
        quoted_text.emplace_back(/*              */ find_chr(e.at_pointer("/full_text"), "/extended_tweet/full_text", "/text") /* */);
        quoted_created_at.emplace_back(/*        */ to<std::string>(e.at_pointer("/created_at")) /*                                         */);
        quoted_source.emplace_back(/*            */ to<std::string>(e.at_pointer("/source")) /*                                             */);
        quoted_favorite_count.emplace_back(/*    */ to<int>(e.at_pointer("/favorite_count")) /*                                     */);
        quoted_retweet_count.emplace_back(/*     */ to<int>(e.at_pointer("/retweet_count")) /*                                      */);
        quoted_user_id.emplace_back(/*           */ to<std::string>(e.at_pointer("/user/id_str")) /*                                          */);
        quoted_screen_name.emplace_back(/*       */ to<std::string>(e.at_pointer("/user/screen_name")) /*                                   */);
        quoted_name.emplace_back(/*              */ to<std::string>(e.at_pointer("/user/name")) /*                                          */);
        quoted_followers_count.emplace_back(/*   */ to<int>(e.at_pointer("/user/followers_count")) /*                               */);
        quoted_friends_count.emplace_back(/*     */ to<int>(e.at_pointer("/user/friends_count")) /*                                 */);
        quoted_statuses_count.emplace_back(/*    */ to<int>(e.at_pointer("/user/statuses_count")) /*                                */);
        quoted_location.emplace_back(/*          */ to<std::string>(e.at_pointer("/user/location")) /*                                      */);
        quoted_description.emplace_back(/*       */ to<std::string>(e.at_pointer("/user/description")) /*                                   */);
        quoted_verified.emplace_back(/*          */ to<bool>(e.at_pointer("/user/verified")) /*                                      */);
    } else {
        quoted_status_id.emplace_back("");
        quoted_text.emplace_back("");
        quoted_created_at.emplace_back("");
        quoted_source.emplace_back("");
        quoted_favorite_count.emplace_back(NA_INTEGER);
        quoted_retweet_count.emplace_back(NA_INTEGER);
        quoted_user_id.emplace_back("");
        quoted_screen_name.emplace_back("");
        quoted_name.emplace_back("");
        quoted_followers_count.emplace_back(NA_INTEGER);
        quoted_friends_count.emplace_back(NA_INTEGER);
        quoted_statuses_count.emplace_back(NA_INTEGER);
        quoted_location.emplace_back("");
        quoted_description.emplace_back("");
        quoted_verified.emplace_back(NA_LOGICAL);
    }

// // Rcpp::Rcout << "d" << std::endl;

    if (auto [e, error] = x.at_pointer("/retweeted_status"); !error) {
        retweet_status_id.emplace_back(/*        */ to<std::string>(e.at_pointer("/id_str")) /*                                 */);
        retweet_text.emplace_back(/*             */ find_chr(e, "/full_text", "/extended_tweet/full_text", "/text") /* */);
        retweet_created_at.emplace_back(/*       */ to<std::string>(e.at_pointer("/created_at")) /*                           */);
        retweet_source.emplace_back(/*           */ to<std::string>(e.at_pointer("/source")) /*                               */);
        retweet_favorite_count.emplace_back(/*   */ to<int>(e.at_pointer("/favorite_count")) /*                       */);
        retweet_retweet_count.emplace_back(/*    */ to<int>(e.at_pointer("/retweet_count")) /*                        */);
        retweet_user_id.emplace_back(/*          */ to<std::string>(e.at_pointer("/user/id_str")) /*                            */);
        retweet_screen_name.emplace_back(/*      */ to<std::string>(e.at_pointer("/user/screen_name")) /*                     */);
        retweet_name.emplace_back(/*             */ to<std::string>(e.at_pointer("/user/name")) /*                            */);
        retweet_followers_count.emplace_back(/*  */ to<int>(e.at_pointer("/user/followers_count")) /*                 */);
        retweet_friends_count.emplace_back(/*    */ to<int>(e.at_pointer("/user/friends_count")) /*                   */);
        retweet_statuses_count.emplace_back(/*   */ to<int>(e.at_pointer("/user/statuses_count")) /*                  */);
        retweet_location.emplace_back(/*         */ to<std::string>(e.at_pointer("/user/location")) /*                        */);
        retweet_description.emplace_back(/*      */ to<std::string>(e.at_pointer("/user/description")) /*                     */);
        retweet_verified.emplace_back(/*         */ to<bool>(e.at_pointer("/user/verified")) /*                        */);
    } else {
        retweet_status_id.emplace_back("");
        retweet_text.emplace_back("");
        retweet_created_at.emplace_back("");
        retweet_source.emplace_back("");
        retweet_favorite_count.emplace_back(NA_INTEGER);
        retweet_retweet_count.emplace_back(NA_INTEGER);
        retweet_user_id.emplace_back("");
        retweet_screen_name.emplace_back("");
        retweet_name.emplace_back("");
        retweet_followers_count.emplace_back(NA_INTEGER);
        retweet_friends_count.emplace_back(NA_INTEGER);
        retweet_statuses_count.emplace_back(NA_INTEGER);
        retweet_location.emplace_back("");
        retweet_description.emplace_back("");
        retweet_verified.emplace_back(NA_LOGICAL);
    }

// // Rcpp::Rcout << "e" << std::endl;

    if (auto [e, error] = x.at_pointer("/place"); !error) {
        place_url.emplace_back(/*                */ to<std::string>(e.at_pointer("/url")) /*                             */);
        place_name.emplace_back(/*               */ to<std::string>(e.at_pointer("/name")) /*                            */);
        place_full_name.emplace_back(/*          */ to<std::string>(e.at_pointer("/full_name")) /*                       */);
        place_type.emplace_back(/*               */ to<std::string>(e.at_pointer("/place_type")) /*                      */);
        country.emplace_back(/*                  */ to<std::string>(e.at_pointer("/country")) /*                         */);
        country_code.emplace_back(/*             */ to<std::string>(e.at_pointer("/country_code")) /*                    */);
        bbox_coords.emplace_back(/*              */ get_bbox(e.at_pointer("/bounding_box/coordinates")) /*               */);
    } else {
        place_url.emplace_back("");
        place_name.emplace_back("");
        place_full_name.emplace_back("");
        place_type.emplace_back("");
        country.emplace_back("");
        country_code.emplace_back("");
        bbox_coords.emplace_back(std::vector<double>(8, NA_REAL));
    }


// // Rcpp::Rcout << "f" << std::endl;

    if (auto [e, error] = x.at_pointer("/retweeted_status/place"); !error) {
        retweet_place_url.emplace_back(/*        */ to<std::string>(e.at_pointer("/url")) /*                            */);
        retweet_place_name.emplace_back(/*       */ to<std::string>(e.at_pointer("/name")) /*                           */);
        retweet_place_full_name.emplace_back(/*  */ to<std::string>(e.at_pointer("/full_name")) /*                      */);
        retweet_place_type.emplace_back(/*       */ to<std::string>(e.at_pointer("/place_type")) /*                     */);
        retweet_country.emplace_back(/*          */ to<std::string>(e.at_pointer("/country")) /*                        */);
        retweet_country_code.emplace_back(/*     */ to<std::string>(e.at_pointer("/country_code")) /*                   */);
        retweet_bbox_coords.emplace_back(/*      */ get_bbox(e.at_pointer("/bounding_box/coordinates")) /*     */);
    } else {
        retweet_place_url.emplace_back("");
        retweet_place_name.emplace_back("");
        retweet_place_full_name.emplace_back("");
        retweet_place_type.emplace_back("");
        retweet_country.emplace_back("");
        retweet_country_code.emplace_back("");
        retweet_bbox_coords.emplace_back(std::vector<double>(8, NA_REAL));
    }


// Rcpp::Rcout << "g" << std::endl;

    if (auto [e, error] = x.at_pointer("/quoted_status/place"); !error) {
        quoted_place_url.emplace_back(/*         */ to<std::string>(e.at_pointer("/url")) /*                               */);
        quoted_place_name.emplace_back(/*        */ to<std::string>(e.at_pointer("/name")) /*                              */);
        quoted_place_full_name.emplace_back(/*   */ to<std::string>(e.at_pointer("/full_name")) /*                         */);
        quoted_place_type.emplace_back(/*        */ to<std::string>(e.at_pointer("/place_type")) /*                        */);
        quoted_country.emplace_back(/*           */ to<std::string>(e.at_pointer("/country")) /*                           */);
        quoted_country_code.emplace_back(/*      */ to<std::string>(e.at_pointer("/country_code")) /*                      */);
        quoted_bbox_coords.emplace_back(/*       */ get_bbox(e.at_pointer("/bounding_box/coordinates")) /*        */);
    } else {
        quoted_place_url.emplace_back("");
        quoted_place_name.emplace_back("");
        quoted_place_full_name.emplace_back("");
        quoted_place_type.emplace_back("");
        quoted_country.emplace_back("");
        quoted_country_code.emplace_back("");
        quoted_bbox_coords.emplace_back(std::vector<double>(8, NA_REAL));
    }

    // clang-format on
  }

  [[nodiscard]] Rcpp::List as_list() {
    Rcpp::List out;

    out["user_id"] = user_id;
    out["status_id"] = status_id;
    out["created_at"] = as_dttm(created_at);
    out["screen_name"] = screen_name;
    out["text"] = text;
    out["source"] = source;
    out["reply_to_status_id"] = reply_to_status_id;
    out["reply_to_user_id"] = reply_to_user_id;
    out["reply_to_screen_name"] = reply_to_screen_name;
    out["is_quote"] = is_quote;
    out["is_retweeted"] = is_retweeted;
    out["lang"] = lang;

    out["timestamp_ms"] = timestamp_ms; // as_dttm(std::begin(timestamp_ms),
                                        // std::end(timestamp_ms));

    out["name"] = name;
    out["location"] = location;
    out["description"] = description;
    out["url"] = url;
    out["protected"] = protected_;
    out["followers_count"] = followers_count;
    out["friends_count"] = friends_count;
    out["listed_count"] = listed_count;
    out["statuses_count"] = statuses_count;
    out["favourites_count"] = favourites_count;
    out["account_created_at"] = account_created_at;
    out["verified"] = verified;
    out["account_lang"] = account_lang;
    out["profile_banner_url"] = profile_banner_url;
    out["profile_image_url"] = profile_image_url;
    out["contributors_enabled"] = contributors_enabled;

    out["hashtags"] = hashtags;
    out["urls_expanded_url"] = urls_expanded_urls;
    out["media_expanded_url"] = media_expanded_url;
    out["media_url"] = media_url;
    out["media_type"] = media_type;
    out["mentions_user_id"] = mentions_user_id;
    out["mentions_screen_name"] = mentions_screen_name;

    out["quoted_status_id"] = quoted_status_id;
    out["quoted_text"] = quoted_text;
    out["quoted_created_at"] = quoted_created_at;
    out["quoted_source"] = quoted_source;
    out["quoted_favorite_count"] = quoted_favorite_count;
    out["quoted_retweet_count"] = quoted_retweet_count;
    out["quoted_user_id"] = quoted_user_id;
    out["quoted_screen_name"] = quoted_screen_name;
    out["quoted_name"] = quoted_name;
    out["quoted_followers_count"] = quoted_followers_count;
    out["quoted_friends_count"] = quoted_friends_count;
    out["quoted_statuses_count"] = quoted_statuses_count;
    out["quoted_location"] = quoted_location;
    out["quoted_description"] = quoted_description;
    out["quoted_verified"] = quoted_verified;

    out["retweet_status_id"] = retweet_status_id;
    out["retweet_text"] = retweet_text;
    out["retweet_created_at"] = retweet_created_at;
    out["retweet_source"] = retweet_source;
    out["retweet_favorite_count"] = retweet_favorite_count;
    out["retweet_retweet_count"] = retweet_retweet_count;
    out["retweet_user_id"] = retweet_user_id;
    out["retweet_screen_name"] = retweet_screen_name;
    out["retweet_name"] = retweet_name;
    out["retweet_followers_count"] = retweet_followers_count;
    out["retweet_friends_count"] = retweet_friends_count;
    out["retweet_statuses_count"] = retweet_statuses_count;
    out["retweet_location"] = retweet_location;
    out["retweet_description"] = retweet_description;
    out["retweet_verified"] = retweet_verified;

    out["place_url"] = place_url;
    out["place_name"] = place_name;
    out["place_full_name"] = place_full_name;
    out["place_type"] = place_type;
    out["country"] = country;
    out["country_code"] = country_code;
    out["bbox_coords"] = bbox_coords;

    out["retweet_place_url"] = retweet_place_url;
    out["retweet_place_name"] = retweet_place_name;
    out["retweet_place_full_name"] = retweet_place_full_name;
    out["retweet_place_type"] = retweet_place_type;
    out["retweet_country"] = retweet_country;
    out["retweet_country_code"] = retweet_country_code;
    out["retweet_bbox_coords"] = retweet_bbox_coords;

    out["quoted_place_url"] = quoted_place_url;
    out["quoted_place_name"] = quoted_place_name;
    out["quoted_place_full_name"] = quoted_place_full_name;
    out["quoted_place_type"] = quoted_place_type;
    out["quoted_country"] = quoted_country;
    out["quoted_country_code"] = quoted_country_code;
    out["quoted_bbox_coords"] = quoted_bbox_coords;

    return out;
  }

  // template <File_Type, bool is_clean, typename stream_T, bool verbose>
  // static auto from_file(const std::string& file_path) -> Base_DF;

  //   template <File_Type, bool>
  //   static auto from_clean_file(const std::string&) -> Base_DF;

  //   template <typename stream_T, File_Type, bool>
  //   static auto from_dirty_file(const std::string&) -> Base_DF;

//   static Base_DF
//   from_file(const std::vector<std::string>&, const bool, const double);
};


// inline Base_DF Base_DF::from_file(const std::vector<std::string>& file_paths,
//                                   const bool verbose,
//                                   const double reserve) {
//   const auto n_files = std::size(file_paths);
//   Base_DF out;
//   out.reserve(reserve);

//   Progress progress(n_files, verbose);
//   simdjson::dom::parser parser;
//   for (auto&& f : file_paths) {
//     for (auto&& [x, error] : parser.load_many(f)) {
//       if (error) {
//         Rcpp::warning(simdjson::error_message(error));
//         continue;
//       }

//       if (auto [doc, error] = x.at_pointer("/doc"); !error) {
//         out.push(std::move(doc));
//       }
//     }
//     progress.increment();
//   }

//   return out;
// }


} // namespace tweetio

#endif
