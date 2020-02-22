#ifndef TWEETIO_TWEETDF_H
#define TWEETIO_TWEETDF_H

#include "main.hpp"
// #include <tweetio/json.hpp>

namespace tweetio {

class TweetDF {
    public:
    R_xlen_t i_all = 0;

    vec_int quoted_favorite_count;
    vec_int quoted_retweet_count;
    vec_int quoted_followers_count;
    vec_int quoted_friends_count;
    vec_int quoted_statuses_count;

    vec_int retweet_followers_count;
    vec_int retweet_friends_count;
    vec_int retweet_statuses_count;
    vec_int retweet_favorite_count;
    vec_int retweet_retweet_count;

    vec_int followers_count;
    vec_int friends_count;
    vec_int listed_count;
    vec_int statuses_count;
    vec_int favourites_count;

    vec_lgl is_quote;
    vec_lgl is_retweeted;

    vec_lgl retweet_verified;

    vec_lgl quoted_verified;
    vec_lgl protected_;                           // `protected` is a C++ reserved keyword
    vec_lgl verified;
    vec_lgl contributors_enabled;

    vec_chr user_id;
    vec_chr status_id;
    vec_chr created_at;
    vec_chr screen_name;
    vec_chr text;
    vec_chr source;

    vec_chr reply_to_status_id;
    vec_chr reply_to_user_id;
    vec_chr reply_to_screen_name;
    
    vec_chr lang;
    vec_chr retweet_status_id;

    vec_chr place_url;
    vec_chr place_name;
    vec_chr place_full_name;
    vec_chr place_type;
    vec_chr country;
    vec_chr country_code;

    vec_chr retweet_text;
    vec_chr retweet_created_at;
    vec_chr retweet_source;
    vec_chr retweet_user_id;
    vec_chr retweet_screen_name;
    vec_chr retweet_name;
    vec_chr retweet_location;
    vec_chr retweet_description;
    vec_chr retweet_place_url;
    vec_chr retweet_place_name;
    vec_chr retweet_place_full_name;
    vec_chr retweet_place_type;
    vec_chr retweet_country;
    vec_chr retweet_country_code;

    vec_chr quoted_status_id;
    vec_chr quoted_text;
    vec_chr quoted_created_at;
    vec_chr quoted_source;
    vec_chr quoted_user_id;
    vec_chr quoted_screen_name;
    vec_chr quoted_name;
    vec_chr quoted_location;
    vec_chr quoted_description;
    vec_chr quoted_place_url;
    vec_chr quoted_place_name;
    vec_chr quoted_place_full_name;
    vec_chr quoted_place_type;
    vec_chr quoted_country;
    vec_chr quoted_country_code;

    vec_chr name;
    vec_chr location;
    vec_chr description;
    vec_chr url;
    vec_chr account_created_at;
    vec_chr account_lang;
    vec_chr profile_banner_url;
    vec_chr profile_image_url;
    vec_dbl timestamp_ms;

    Rcpp::List hashtags;
    Rcpp::List urls_expanded_url;
    Rcpp::List media_url;
    Rcpp::List media_expanded_url;
    Rcpp::List media_type;
    Rcpp::List mentions_user_id;
    Rcpp::List mentions_screen_name;
    Rcpp::List bbox_coords;
    Rcpp::List quoted_bbox_coords;
    Rcpp::List retweet_bbox_coords;

    // public:
    TweetDF();
    // ~TweetDF() {};

    R_xlen_t get_i_all() { return i_all; };


    TweetDF(const R_xlen_t& n_vals) {
        user_id                      = vec_chr(n_vals, NA_STRING);
        status_id                    = vec_chr(n_vals, NA_STRING);
        created_at                   = vec_chr(n_vals, NA_STRING);
        screen_name                  = vec_chr(n_vals, NA_STRING);
        text                         = vec_chr(n_vals, NA_STRING);
        source                       = vec_chr(n_vals, NA_STRING);
        reply_to_status_id           = vec_chr(n_vals, NA_STRING);
        reply_to_user_id             = vec_chr(n_vals, NA_STRING);
        reply_to_screen_name         = vec_chr(n_vals, NA_STRING);
        is_quote                     = vec_lgl(n_vals, NA_LOGICAL);
        is_retweeted                 = vec_lgl(n_vals, NA_LOGICAL);

        hashtags                     = Rcpp::List( n_vals);
        urls_expanded_url            = Rcpp::List( n_vals);

        media_expanded_url           = Rcpp::List( n_vals);
        media_url                    = Rcpp::List( n_vals);
        media_expanded_url           = Rcpp::List( n_vals);
        media_type                   = Rcpp::List(n_vals);

        mentions_user_id             = Rcpp::List( n_vals);
        mentions_screen_name         = Rcpp::List( n_vals);

        lang                         = vec_chr(n_vals, NA_STRING);

        quoted_status_id             = vec_chr(n_vals, NA_STRING); 
        quoted_text                  = vec_chr(n_vals, NA_STRING); 
        quoted_created_at            = vec_chr(n_vals, NA_STRING); 
        quoted_source                = vec_chr(n_vals, NA_STRING); 
        quoted_favorite_count        = vec_int(n_vals, NA_INTEGER); 
        quoted_retweet_count         = vec_int(n_vals, NA_INTEGER); 
        quoted_user_id               = vec_chr(n_vals, NA_STRING); 
        quoted_screen_name           = vec_chr(n_vals, NA_STRING); 
        quoted_name                  = vec_chr(n_vals, NA_STRING); 
        quoted_followers_count       = vec_int(n_vals, NA_INTEGER); 
        quoted_friends_count         = vec_int(n_vals, NA_INTEGER); 
        quoted_statuses_count        = vec_int(n_vals, NA_INTEGER); 
        quoted_location              = vec_chr(n_vals, NA_STRING);
        quoted_description           = vec_chr(n_vals, NA_STRING);
        quoted_verified              = vec_lgl(n_vals, NA_LOGICAL);

        retweet_status_id            = vec_chr(n_vals, NA_STRING);
        retweet_text                 = vec_chr(n_vals, NA_STRING);
        retweet_created_at           = vec_chr(n_vals, NA_STRING);
        retweet_source               = vec_chr(n_vals, NA_STRING);
        retweet_favorite_count       = vec_int(n_vals, NA_INTEGER);
        retweet_retweet_count        = vec_int(n_vals, NA_INTEGER);
        retweet_user_id              = vec_chr(n_vals, NA_STRING);
        retweet_screen_name          = vec_chr(n_vals, NA_STRING);
        retweet_name                 = vec_chr(n_vals, NA_STRING);
        retweet_followers_count      = vec_int(n_vals, NA_INTEGER);
        retweet_friends_count        = vec_int(n_vals, NA_INTEGER);
        retweet_statuses_count       = vec_int(n_vals, NA_INTEGER);
        retweet_location             = vec_chr(n_vals, NA_STRING);
        retweet_description          = vec_chr(n_vals, NA_STRING);
        retweet_verified             = vec_lgl(n_vals, NA_LOGICAL);

        place_url                    = vec_chr(n_vals, NA_STRING);
        place_name                   = vec_chr(n_vals, NA_STRING);
        place_full_name              = vec_chr(n_vals, NA_STRING);
        place_type                   = vec_chr(n_vals, NA_STRING);
        country                      = vec_chr(n_vals, NA_STRING);
        country_code                 = vec_chr(n_vals, NA_STRING);
        bbox_coords                  = Rcpp::List( n_vals);

        retweet_place_url            = vec_chr(n_vals, NA_STRING);
        retweet_place_name           = vec_chr(n_vals, NA_STRING);
        retweet_place_full_name      = vec_chr(n_vals, NA_STRING);
        retweet_place_type           = vec_chr(n_vals, NA_STRING);
        retweet_country              = vec_chr(n_vals, NA_STRING);
        retweet_country_code         = vec_chr(n_vals, NA_STRING);
        retweet_bbox_coords          = Rcpp::List( n_vals);

        quoted_place_url            = vec_chr(n_vals, NA_STRING);
        quoted_place_name           = vec_chr(n_vals, NA_STRING);
        quoted_place_full_name      = vec_chr(n_vals, NA_STRING);
        quoted_place_type           = vec_chr(n_vals, NA_STRING);
        quoted_country              = vec_chr(n_vals, NA_STRING);
        quoted_country_code         = vec_chr(n_vals, NA_STRING);
        quoted_bbox_coords          = Rcpp::List( n_vals);

        name                         = vec_chr(n_vals, NA_STRING);
        location                     = vec_chr(n_vals, NA_STRING);
        description                  = vec_chr(n_vals, NA_STRING);
        url                          = vec_chr(n_vals, NA_STRING);
        protected_                   = vec_lgl(n_vals, NA_LOGICAL);
        followers_count              = vec_int(n_vals, NA_INTEGER);
        friends_count                = vec_int(n_vals, NA_INTEGER);
        listed_count                 = vec_int(n_vals, NA_INTEGER);
        statuses_count               = vec_int(n_vals, NA_INTEGER);
        favourites_count             = vec_int(n_vals, NA_INTEGER);
        account_created_at           = vec_chr(n_vals, NA_STRING);
        verified                     = vec_lgl(n_vals, NA_LOGICAL);
        account_lang                 = vec_chr(n_vals, NA_STRING);
        profile_banner_url           = vec_chr(n_vals, NA_STRING);
        profile_image_url            = vec_chr(n_vals, NA_STRING);
        timestamp_ms                 = vec_dbl(n_vals, NA_REAL);
        contributors_enabled         = vec_lgl(n_vals, NA_LOGICAL);

    };


    void push(const rapidjson::Value& x) {
        // status_id[i_all]  =   get_chr2(status_id[i_all], x["id_str"] );
        // user_id[i_all]  =   get_chr2(user_id[i_all], x["user"]["id_str"] );
        // created_at[i_all] = get_chr2(created_at[i_all], x["created_at"] );

        user_id[i_all]                     = get_chr( x["user"]["id_str"] );
        status_id[i_all]                   = get_chr( x["id_str"] );
        created_at[i_all]                  = get_chr( x["created_at"] );
        screen_name[i_all]                 = get_chr( x["user"]["screen_name"] );
        text[i_all]                        = get_chr_check( x["extended_tweet"]["full_text"], x["text"] );
        source[i_all]                      = get_chr( x["source"] );
        reply_to_status_id[i_all]          = get_chr( x["in_reply_to_status_id_str"] );
        reply_to_user_id[i_all]            = get_chr( x["in_reply_to_user_id_str"] );
        reply_to_screen_name[i_all]        = get_chr( x["in_reply_to_screen_name"] );
        is_quote[i_all]                    = get_lgl( x["is_quote_status"] );
        is_retweeted[i_all]                = get_lgl( x["retweeted"] );

        hashtags[i_all]                    = map_entities(x, "hashtags", "text");
        urls_expanded_url[i_all]           = map_entities(x, "urls", "expanded_url");

        media_expanded_url[i_all]          = map_entities(x, "media", "expanded_url");
        media_url[i_all]                   = map_entities(x, "media", "media_url");
        media_type[i_all]                  = map_entities(x, "media", "type");

        mentions_user_id[i_all]            = map_entities(x, "user_mentions", "id_str");
        mentions_screen_name[i_all]        = map_entities(x, "user_mentions", "screen_name");

        lang[i_all]                        = get_chr( x["lang"] );

        quoted_status_id[i_all]            = get_chr( x["quoted_status_id_str"] );
        quoted_text[i_all]                 = get_chr_check( x["quoted_status"]["extended_tweet"]["full_text"], x["quoted_status"]["text"] );
        quoted_created_at[i_all]           = get_chr( x["quoted_status"]["created_at"] );
        quoted_source[i_all]               = get_chr( x["quoted_status"]["source"] );
        quoted_favorite_count[i_all]       = get_int( x["quoted_status"]["favorite_count"] );
        // get_int2( quoted_favorite_count[i_all], x["quoted_status"]["favorite_count"] );
        quoted_retweet_count[i_all]        = get_int( x["quoted_status"]["retweet_count"] );
        // get_int2( quoted_retweet_count[i_all], x["quoted_status"]["retweet_count"] );
        quoted_user_id[i_all]              = get_chr( x["quoted_status"]["user"]["id_str"] );
        quoted_screen_name[i_all]          = get_chr( x["quoted_status"]["user"]["screen_name"] );
        quoted_name[i_all]                 = get_chr( x["quoted_status"]["user"]["name"] );
        quoted_followers_count[i_all]      = get_int( x["quoted_status"]["user"]["followers_count"] );
        // get_int2( quoted_followers_count[i_all], x["quoted_status"]["user"]["followers_count"] );
        quoted_friends_count[i_all]        = get_int( x["quoted_status"]["user"]["friends_count"] );
        // get_int2( quoted_friends_count[i_all], x["quoted_status"]["user"]["friends_count"] );
        quoted_statuses_count[i_all]       = get_int( x["quoted_status"]["user"]["statuses_count"] );
        // get_int2( quoted_statuses_count[i_all], x["quoted_status"]["user"]["statuses_count"] );
        quoted_location[i_all]             = get_chr( x["quoted_status"]["user"]["location"] );
        quoted_description[i_all]          = get_chr( x["quoted_status"]["user"]["description"] );
        quoted_verified[i_all]             = get_lgl( x["quoted_status"]["user"]["verified"] );

        retweet_status_id[i_all]           = get_chr( x["retweeted_status"]["id_str"] );
        retweet_text[i_all]                = get_chr_check( x["retweeted_status"]["extended_tweet"]["full_text"], x["retweeted_status"]["text"] );
        retweet_created_at[i_all]          = get_chr( x["retweeted_status"]["created_at"] );
        retweet_source[i_all]              = get_chr( x["retweeted_status"]["source"] );
        retweet_favorite_count[i_all]      = get_int( x["retweeted_status"]["favorite_count"] );
        // get_int2(retweet_favorite_count[i_all], x["retweeted_status"]["favorite_count"] );
        retweet_retweet_count[i_all]       = get_int( x["retweeted_status"]["retweet_count"] );
        // get_int2( retweet_retweet_count[i_all], x["retweeted_status"]["retweet_count"] );
        retweet_user_id[i_all]             = get_chr( x["retweeted_status"]["user"]["id_str"] );
        retweet_screen_name[i_all]         = get_chr( x["retweeted_status"]["user"]["screen_name"] );
        retweet_name[i_all]                = get_chr( x["retweeted_status"]["user"]["name"] );
        retweet_followers_count[i_all]     = get_int( x["retweeted_status"]["user"]["followers_count"] );
        // get_int2( retweet_followers_count[i_all], x["retweeted_status"]["user"]["followers_count"] );
        retweet_friends_count[i_all]       = get_int( x["retweeted_status"]["user"]["followers_count"] );
        // get_int2( retweet_friends_count[i_all], x["retweeted_status"]["user"]["followers_count"] );
        retweet_statuses_count[i_all]      = get_int( x["retweeted_status"]["user"]["statuses_count"] );
        // get_int2( retweet_statuses_count[i_all], x["retweeted_status"]["user"]["statuses_count"] );
        retweet_location[i_all]            = get_chr( x["retweeted_status"]["user"]["location"] );
        retweet_description[i_all]         = get_chr( x["retweeted_status"]["user"]["description"] );
        retweet_verified[i_all]            = get_lgl( x["retweeted_status"]["user"]["verified"] );

        place_url[i_all]                   = get_chr( x["place"]["url"] );
        place_name[i_all]                  = get_chr( x["place"]["name"] );
        place_full_name[i_all]             = get_chr( x["place"]["full_name"] );
        place_type[i_all]                  = get_chr( x["place"]["place_type"] );
        country[i_all]                     = get_chr( x["place"]["country"] );
        country_code[i_all]                = get_chr( x["place"]["country_code"] );
        bbox_coords[i_all]                 = get_bbox( x["place"]["bounding_box"]["coordinates"] );
        // get_bbox2( bbox_coords[i_all], x["place"]["bounding_box"]["coordinates"] );

        retweet_place_url[i_all]           = get_chr( x["retweeted_status"]["place"]["url"] );
        retweet_place_name[i_all]          = get_chr( x["retweeted_status"]["place"]["name"] );
        retweet_place_full_name[i_all]     = get_chr( x["retweeted_status"]["place"]["full_name"] );
        retweet_place_type[i_all]          = get_chr( x["retweeted_status"]["place"]["place_type"] );
        retweet_country[i_all]             = get_chr( x["retweeted_status"]["place"]["country"] );
        retweet_country_code[i_all]        = get_chr( x["retweeted_status"]["place"]["country_code"] );
        retweet_bbox_coords[i_all]         = get_bbox( x["retweeted_status"]["place"]["bounding_box"]["coordinates"] );
        // get_bbox2( retweet_bbox_coords[i_all], x["retweeted_status"]["place"]["bounding_box"]["coordinates"] );

        quoted_place_url[i_all]            = get_chr( x["quoted_status"]["place"]["url"] );
        quoted_place_name[i_all]           = get_chr( x["quoted_status"]["place"]["name"] );
        quoted_place_full_name[i_all]      = get_chr( x["quoted_status"]["place"]["full_name"] );
        quoted_place_type[i_all]           = get_chr( x["quoted_status"]["place"]["place_type"] );
        quoted_country[i_all]              = get_chr( x["quoted_status"]["place"]["country"] );
        quoted_country_code[i_all]         = get_chr( x["quoted_status"]["place"]["country_code"] );
        quoted_bbox_coords[i_all]          = get_bbox( x["quoted_status"]["place"]["bounding_box"]["coordinates"] );
        // get_bbox2( quoted_bbox_coords[i_all], x["quoted_status"]["place"]["bounding_box"]["coordinates"] );

        name[i_all]                        = get_chr( x["user"]["name"] );
        location[i_all]                    = get_chr( x["user"]["location"] );
        description[i_all]                 = get_chr( x["user"]["description"] );
        url[i_all]                         = get_chr( x["user"]["url"] );
        protected_[i_all]                  = get_lgl( x["user"]["protected"] );
        followers_count[i_all]             = get_int( x["user"]["followers_count"] );
        friends_count[i_all]               = get_int( x["user"]["friends_count"] );
        listed_count[i_all]                = get_int( x["user"]["listed_count"] );
        statuses_count[i_all]              = get_int( x["user"]["statuses_count"] );
        favourites_count[i_all]            = get_int( x["user"]["favourites_count"] );
        account_created_at[i_all]          = get_chr( x["user"]["created_at"] );
        verified[i_all]                    = get_lgl( x["user"]["verified"] );
        account_lang[i_all]                = get_chr( x["user"]["lang"] );
        profile_banner_url[i_all]          = get_chr( x["user"]["profile_banner_url"] );
        profile_image_url[i_all]           = get_chr( x["user"]["profile_image_url"] );
        timestamp_ms[i_all]                = get_timestamp_ms( x["timestamp_ms"] );
        contributors_enabled[i_all]        = get_lgl( x["user"]["countributors_enabled"] );



        i_all++;
    }; // TweetDF.push()

    vec_int get_seq_out() {
        vec_int seq_out(i_all);
        std::iota( std::begin(seq_out), std::end(seq_out), 0);

        return seq_out;
    } // TweetDF.get_seq_out()


    Rcpp::List build_list() {
        const auto seq_out = get_seq_out();

        Rcpp::List cols;
        
        cols["user_id"]                          = user_id[seq_out];
        cols["status_id"]                        = status_id[seq_out];
        cols["created_at"]                       = created_at[seq_out];
        cols["screen_name"]                      = screen_name[seq_out];
        cols["text"]                             = text[seq_out];
        cols["lang"]                             = lang[seq_out];

        cols["source"]                           = source[seq_out];
        cols["reply_to_status_id"]               = reply_to_status_id[seq_out];
        cols["reply_to_user_id"]                 = reply_to_user_id[seq_out];
        cols["reply_to_screen_name"]             = reply_to_screen_name[seq_out];
        cols["is_quote"]                         = is_quote[seq_out];
        cols["is_retweeted"]                     = is_retweeted[seq_out];

        cols["hashtags"]                         = hashtags[seq_out];
        cols["urls_expanded_url"]                = urls_expanded_url[seq_out];
        cols["media_expanded_url"]               = media_expanded_url[seq_out];
        cols["media_url"]                        = media_url[seq_out];
        cols["media_type"]                       = media_type[seq_out];
        cols["mentions_user_id"]                 = mentions_user_id[seq_out];
        cols["mentions_screen_name"]             = mentions_screen_name[seq_out];

        cols["quoted_status_id"]                 = quoted_status_id[seq_out];
        cols["quoted_text"]                      = quoted_text[seq_out];
        cols["quoted_created_at"]                = quoted_created_at[seq_out];
        cols["quoted_source"]                    = quoted_source[seq_out];
        cols["quoted_favorite_count"]            = quoted_favorite_count[seq_out];
        cols["quoted_retweet_count"]             = quoted_retweet_count[seq_out];
        cols["quoted_user_id"]                   = quoted_user_id[seq_out];
        cols["quoted_screen_name"]               = quoted_screen_name[seq_out];
        cols["quoted_name"]                      = quoted_name[seq_out];
        cols["quoted_followers_count"]           = quoted_followers_count[seq_out];
        cols["quoted_friends_count"]             = quoted_friends_count[seq_out];
        cols["quoted_statuses_count"]            = quoted_statuses_count[seq_out];
        cols["quoted_location"]                  = quoted_location[seq_out];
        cols["quoted_description"]               = quoted_description[seq_out];
        cols["quoted_verified"]                  = quoted_verified[seq_out];

        cols["retweet_status_id"]                = retweet_status_id[seq_out];
        cols["retweet_text"]                     = retweet_text[seq_out];
        cols["retweet_created_at"]               = retweet_created_at[seq_out];
        cols["retweet_source"]                   = retweet_source[seq_out];
        cols["retweet_favorite_count"]           = retweet_favorite_count[seq_out];
        cols["retweet_retweet_count"]            = retweet_retweet_count[seq_out];
        cols["retweet_user_id"]                  = retweet_user_id[seq_out];
        cols["retweet_screen_name"]              = retweet_screen_name[seq_out];
        cols["retweet_name"]                     = retweet_name[seq_out];
        cols["retweet_followers_count"]          = retweet_followers_count[seq_out];
        cols["retweet_friends_count"]            = retweet_friends_count[seq_out];
        cols["retweet_statuses_count"]           = retweet_statuses_count[seq_out];
        cols["retweet_location"]                 = retweet_location[seq_out];
        cols["retweet_description"]              = retweet_description[seq_out];
        cols["retweet_verified"]                 = retweet_verified[seq_out];

        cols["place_url"]                        = place_url[seq_out];
        cols["place_name"]                       = place_name[seq_out];
        cols["place_full_name"]                  = place_full_name[seq_out];
        cols["place_type"]                       = place_type[seq_out];
        cols["country"]                          = country[seq_out];
        cols["country_code"]                     = country_code[seq_out];
        cols["bbox_coords"]                      = bbox_coords[seq_out];

        cols["retweet_place_url"]                = retweet_place_url[seq_out];
        cols["retweet_place_name"]               = retweet_place_name[seq_out];
        cols["retweet_place_full_name"]          = retweet_place_full_name[seq_out];
        cols["retweet_place_type"]               = retweet_place_type[seq_out];
        cols["retweet_country"]                  = retweet_country[seq_out];
        cols["retweet_country_code"]             = retweet_country_code[seq_out];
        cols["retweet_bbox_coords"]              = retweet_bbox_coords[seq_out];

        cols["quoted_place_url"]                 = quoted_place_url[seq_out];
        cols["quoted_place_name"]                = quoted_place_name[seq_out];
        cols["quoted_place_full_name"]           = quoted_place_full_name[seq_out];
        cols["quoted_place_type"]                = quoted_place_type[seq_out];
        cols["quoted_country"]                   = quoted_country[seq_out];
        cols["quoted_country_code"]              = quoted_country_code[seq_out];
        cols["quoted_bbox_coords"]               = quoted_bbox_coords[seq_out];

        cols["name"]                             = name[seq_out];
        cols["location"]                         = location[seq_out];
        cols["description"]                      = description[seq_out];
        cols["url"]                              = url[seq_out];
        cols["protected"]                        = protected_[seq_out];
        cols["followers_count"]                  = followers_count[seq_out];
        cols["friends_count"]                    = friends_count[seq_out];
        cols["listed_count"]                     = listed_count[seq_out];
        cols["statuses_count"]                   = statuses_count[seq_out];
        cols["favourites_count"]                 = favourites_count[seq_out];
        cols["account_created_at"]               = account_created_at[seq_out];
        cols["verified"]                         = verified[seq_out];
        cols["account_lang"]                     = account_lang[seq_out];
        cols["profile_banner_url"]               = profile_banner_url[seq_out];
        cols["profile_image_url"]                = profile_image_url[seq_out];

        cols["contributors_enabled"]             = contributors_enabled[seq_out];

        timestamp_ms.attr("class") = Rcpp::CharacterVector{"POSIXct", "POSIXt"};
        timestamp_ms.attr("tzone") = "UTC";
        cols["timestamp_ms"]                     = timestamp_ms[seq_out]; 

        return cols;
    }; // TweetDF.build_list()

    Rcpp::List to_r() {
        Rcpp::List cols = build_list();

        const int n_digits = count_digits(i_all);
        vec_chr row_names(i_all);
        for (int i = 0; i < i_all; ++i) {
            char name[n_digits];
            sprintf(&(name[0]), "%d", i);
            row_names[i] = name;
        }

        cols.attr("row.names") = row_names;
        cols.attr("class") = vec_chr{"data.frame"};

        return cols;
    }; // TweetDF.to_r()

}; // TweetDF


} // namespace tweetio


#endif
