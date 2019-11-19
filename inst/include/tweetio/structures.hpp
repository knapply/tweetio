// Copyright (C) 2019 Brendan Knapp
// This file is part of tweetio
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.


#ifndef TWEETIO_STRUCTURES_H
#define TWEETIO_STRUCTURES_H

// #include <vector>
#include "main.hpp"

namespace tweetio {

class TweetDF {
    int current_index = 0;

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



    public:
    // TweetDF() {};
    ~TweetDF() {};

    int get_current_index() {
        return this->current_index;
    };


    TweetDF(const int n_vals) {
        this->user_id                      = vec_chr(n_vals, NA_STRING);
        this->status_id                    = vec_chr(n_vals, NA_STRING);
        this->created_at                   = vec_chr(n_vals, NA_STRING);
        this->screen_name                  = vec_chr(n_vals, NA_STRING);
        this->text                         = vec_chr(n_vals, NA_STRING);
        this->source                       = vec_chr(n_vals, NA_STRING);
        this->reply_to_status_id           = vec_chr(n_vals, NA_STRING);
        this->reply_to_user_id             = vec_chr(n_vals, NA_STRING);
        this->reply_to_screen_name         = vec_chr(n_vals, NA_STRING);
        this->is_quote                     = vec_lgl(n_vals, NA_LOGICAL);
        this->is_retweeted                 = vec_lgl(n_vals, NA_LOGICAL);

        this->hashtags                     = Rcpp::List( n_vals, vec_chr(0) );
        this->urls_expanded_url            = Rcpp::List( n_vals, vec_chr(0) );

        this->media_expanded_url           = Rcpp::List( n_vals, vec_chr(0) );
        this->media_url                    = Rcpp::List( n_vals, vec_chr(0) );
        this->media_expanded_url           = Rcpp::List( n_vals, vec_chr(0) );
        this->media_type                   = Rcpp::List(n_vals, NA_STRING);

        this->mentions_user_id             = Rcpp::List( n_vals, vec_chr(0) );
        this->mentions_screen_name         = Rcpp::List( n_vals, vec_chr(0) );

        this->lang                         = vec_chr(n_vals, NA_STRING);

        this->quoted_status_id             = vec_chr(n_vals, NA_STRING); 
        this->quoted_text                  = vec_chr(n_vals, NA_STRING); 
        this->quoted_created_at            = vec_chr(n_vals, NA_STRING); 
        this->quoted_source                = vec_chr(n_vals, NA_STRING); 
        this->quoted_favorite_count        = vec_int(n_vals, NA_INTEGER); 
        this->quoted_retweet_count         = vec_int(n_vals, NA_INTEGER); 
        this->quoted_user_id               = vec_chr(n_vals, NA_STRING); 
        this->quoted_screen_name           = vec_chr(n_vals, NA_STRING); 
        this->quoted_name                  = vec_chr(n_vals, NA_STRING); 
        this->quoted_followers_count       = vec_int(n_vals, NA_INTEGER); 
        this->quoted_friends_count         = vec_int(n_vals, NA_INTEGER); 
        this->quoted_statuses_count        = vec_int(n_vals, NA_INTEGER); 
        this->quoted_location              = vec_chr(n_vals, NA_STRING);
        this->quoted_description           = vec_chr(n_vals, NA_STRING);
        this->quoted_verified              = vec_lgl(n_vals, NA_LOGICAL);

        this->retweet_status_id            = vec_chr(n_vals, NA_STRING);
        this->retweet_text                 = vec_chr(n_vals, NA_STRING);
        this->retweet_created_at           = vec_chr(n_vals, NA_STRING);
        this->retweet_source               = vec_chr(n_vals, NA_STRING);
        this->retweet_favorite_count       = vec_int(n_vals, NA_INTEGER);
        this->retweet_retweet_count        = vec_int(n_vals, NA_INTEGER);
        this->retweet_user_id              = vec_chr(n_vals, NA_STRING);
        this->retweet_screen_name          = vec_chr(n_vals, NA_STRING);
        this->retweet_name                 = vec_chr(n_vals, NA_STRING);
        this->retweet_followers_count      = vec_int(n_vals, NA_INTEGER);
        this->retweet_friends_count        = vec_int(n_vals, NA_INTEGER);
        this->retweet_statuses_count       = vec_int(n_vals, NA_INTEGER);
        this->retweet_location             = vec_chr(n_vals, NA_STRING);
        this->retweet_description          = vec_chr(n_vals, NA_STRING);
        this->retweet_verified             = vec_lgl(n_vals, NA_LOGICAL);

        this->place_url                    = vec_chr(n_vals, NA_STRING);
        this->place_name                   = vec_chr(n_vals, NA_STRING);
        this->place_full_name              = vec_chr(n_vals, NA_STRING);
        this->place_type                   = vec_chr(n_vals, NA_STRING);
        this->country                      = vec_chr(n_vals, NA_STRING);
        this->country_code                 = vec_chr(n_vals, NA_STRING);
        this->bbox_coords                  = Rcpp::List( n_vals, vec_dbl(0) );

        this->retweet_place_url            = vec_chr(n_vals, NA_STRING);
        this->retweet_place_name           = vec_chr(n_vals, NA_STRING);
        this->retweet_place_full_name      = vec_chr(n_vals, NA_STRING);
        this->retweet_place_type           = vec_chr(n_vals, NA_STRING);
        this->retweet_country              = vec_chr(n_vals, NA_STRING);
        this->retweet_country_code         = vec_chr(n_vals, NA_STRING);
        this->retweet_bbox_coords          = Rcpp::List( n_vals, vec_dbl(0) );

        this->quoted_place_url            = vec_chr(n_vals, NA_STRING);
        this->quoted_place_name           = vec_chr(n_vals, NA_STRING);
        this->quoted_place_full_name      = vec_chr(n_vals, NA_STRING);
        this->quoted_place_type           = vec_chr(n_vals, NA_STRING);
        this->quoted_country              = vec_chr(n_vals, NA_STRING);
        this->quoted_country_code         = vec_chr(n_vals, NA_STRING);
        this->quoted_bbox_coords          = Rcpp::List( n_vals, vec_dbl(0) );

        this->name                         = vec_chr(n_vals, NA_STRING);
        this->location                     = vec_chr(n_vals, NA_STRING);
        this->description                  = vec_chr(n_vals, NA_STRING);
        this->url                          = vec_chr(n_vals, NA_STRING);
        this->protected_                   = vec_lgl(n_vals, NA_LOGICAL);
        this->followers_count              = vec_int(n_vals, NA_INTEGER);
        this->friends_count                = vec_int(n_vals, NA_INTEGER);
        this->listed_count                 = vec_int(n_vals, NA_INTEGER);
        this->statuses_count               = vec_int(n_vals, NA_INTEGER);
        this->favourites_count             = vec_int(n_vals, NA_INTEGER);
        this->account_created_at           = vec_chr(n_vals, NA_STRING);
        this->verified                     = vec_lgl(n_vals, NA_LOGICAL);
        this->account_lang                 = vec_chr(n_vals, NA_STRING);
        this->profile_banner_url           = vec_chr(n_vals, NA_STRING);
        this->profile_image_url            = vec_chr(n_vals, NA_STRING);
        this->timestamp_ms                 = vec_dbl(n_vals, NA_REAL);
        this->contributors_enabled         = vec_lgl(n_vals, NA_LOGICAL);

    };


    void push(const rapidjson::Value& x) {
        // this->status_id[this->current_index]  =   get_chr2(this->status_id[this->current_index], x["id_str"] );
        // this->user_id[this->current_index]  =   get_chr2(this->user_id[this->current_index], x["user"]["id_str"] );
        // this->created_at[this->current_index] = get_chr2(this->created_at[this->current_index], x["created_at"] );

        this->user_id[this->current_index]                     = get_chr( x["user"]["id_str"] );
        this->status_id[this->current_index]                   = get_chr( x["id_str"] );
        this->created_at[this->current_index]                  = get_chr( x["created_at"] );
        this->screen_name[this->current_index]                 = get_chr( x["user"]["screen_name"] );
        this->text[this->current_index]                        = get_chr_check( x["extended_tweet"]["full_text"], x["text"] );
        this->source[this->current_index]                      = get_chr( x["source"] );
        this->reply_to_status_id[this->current_index]          = get_chr( x["in_reply_to_status_id_str"] );
        this->reply_to_user_id[this->current_index]            = get_chr( x["in_reply_to_user_id_str"] );
        this->reply_to_screen_name[this->current_index]        = get_chr( x["in_reply_to_screen_name"] );
        this->is_quote[this->current_index]                    = get_lgl( x["is_quote_status"] );
        this->is_retweeted[this->current_index]                = get_lgl( x["retweeted"] );

        this->hashtags[this->current_index]                    = map_entities(x, "hashtags", "text");
        this->urls_expanded_url[this->current_index]           = map_entities(x, "urls", "expanded_url");

        this->media_expanded_url[this->current_index]          = map_entities(x, "media", "expanded_url");
        this->media_url[this->current_index]                   = map_entities(x, "media", "media_url");
        this->media_type[this->current_index]                  = map_entities(x, "media", "type");

        this->mentions_user_id[this->current_index]            = map_entities(x, "user_mentions", "id_str");
        this->mentions_screen_name[this->current_index]        = map_entities(x, "user_mentions", "screen_name");

        this->lang[this->current_index]                        = get_chr( x["lang"] );

        this->quoted_status_id[this->current_index]            = get_chr( x["quoted_status_id_str"] );
        this->quoted_text[this->current_index]                 = get_chr_check( x["quoted_status"]["extended_tweet"]["full_text"], x["quoted_status"]["text"] );
        this->quoted_created_at[this->current_index]           = get_chr( x["quoted_status"]["created_at"] );
        this->quoted_source[this->current_index]               = get_chr( x["quoted_status"]["source"] );
        this->quoted_favorite_count[this->current_index]       = get_int( x["quoted_status"]["favorite_count"] );
        this->quoted_retweet_count[this->current_index]        = get_int( x["quoted_status"]["retweet_count"] );
        this->quoted_user_id[this->current_index]              = get_chr( x["quoted_status"]["user"]["id_str"] );
        this->quoted_screen_name[this->current_index]          = get_chr( x["quoted_status"]["user"]["screen_name"] );
        this->quoted_name[this->current_index]                 = get_chr( x["quoted_status"]["user"]["name"] );
        this->quoted_followers_count[this->current_index]      = get_int( x["quoted_status"]["user"]["followers_count"] );
        this->quoted_friends_count[this->current_index]        = get_int( x["quoted_status"]["user"]["friends_count"] );
        this->quoted_statuses_count[this->current_index]       = get_int( x["quoted_status"]["user"]["statuses_count"] );
        this->quoted_location[this->current_index]             = get_chr( x["quoted_status"]["user"]["location"] );
        this->quoted_description[this->current_index]          = get_chr( x["quoted_status"]["user"]["description"] );
        this->quoted_verified[this->current_index]             = get_lgl( x["quoted_status"]["user"]["verified"] );

        this->retweet_status_id[this->current_index]           = get_chr( x["retweeted_status"]["id_str"] );
        this->retweet_text[this->current_index]                = get_chr_check( x["retweeted_status"]["extended_tweet"]["full_text"], x["retweeted_status"]["text"] );
        this->retweet_created_at[this->current_index]          = get_chr( x["retweeted_status"]["created_at"] );
        this->retweet_source[this->current_index]              = get_chr( x["retweeted_status"]["source"] );
        this->retweet_favorite_count[this->current_index]      = get_int( x["retweeted_status"]["favorite_count"] );
        this->retweet_retweet_count[this->current_index]       = get_int( x["retweeted_status"]["retweet_count"] );
        this->retweet_user_id[this->current_index]             = get_chr( x["retweeted_status"]["user"]["id_str"] );
        this->retweet_screen_name[this->current_index]         = get_chr( x["retweeted_status"]["user"]["screen_name"] );
        this->retweet_name[this->current_index]                = get_chr( x["retweeted_status"]["user"]["name"] );
        this->retweet_followers_count[this->current_index]     = get_int( x["retweeted_status"]["user"]["followers_count"] );
        this->retweet_friends_count[this->current_index]       = get_int( x["retweeted_status"]["user"]["followers_count"] );
        this->retweet_statuses_count[this->current_index]      = get_int( x["retweeted_status"]["user"]["statuses_count"] );
        this->retweet_location[this->current_index]            = get_chr( x["retweeted_status"]["user"]["location"] );
        this->retweet_description[this->current_index]         = get_chr( x["retweeted_status"]["user"]["description"] );
        this->retweet_verified[this->current_index]            = get_lgl( x["retweeted_status"]["user"]["verified"] );

        this->place_url[this->current_index]                   = get_chr( x["place"]["url"] );
        this->place_name[this->current_index]                  = get_chr( x["place"]["name"] );
        this->place_full_name[this->current_index]             = get_chr( x["place"]["full_name"] );
        this->place_type[this->current_index]                  = get_chr( x["place"]["place_type"] );
        this->country[this->current_index]                     = get_chr( x["place"]["country"] );
        this->country_code[this->current_index]                = get_chr( x["place"]["country_code"] );
        this->bbox_coords[this->current_index]                 = get_bbox( x["place"]["bounding_box"]["coordinates"] );

        this->retweet_place_url[this->current_index]          = get_chr( x["retweeted_status"]["place"]["url"] );
        this->retweet_place_name[this->current_index]         = get_chr( x["retweeted_status"]["place"]["name"] );
        this->retweet_place_full_name[this->current_index]    = get_chr( x["retweeted_status"]["place"]["full_name"] );
        this->retweet_place_type[this->current_index]         = get_chr( x["retweeted_status"]["place"]["place_type"] );
        this->retweet_country[this->current_index]            = get_chr( x["retweeted_status"]["place"]["country"] );
        this->retweet_country_code[this->current_index]       = get_chr( x["retweeted_status"]["place"]["country_code"] );
        this->retweet_bbox_coords[this->current_index]        = get_bbox( x["retweeted_status"]["place"]["bounding_box"]["coordinates"] );

        this->quoted_place_url[this->current_index]           = get_chr( x["quoted_status"]["place"]["url"] );
        this->quoted_place_name[this->current_index]          = get_chr( x["quoted_status"]["place"]["name"] );
        this->quoted_place_full_name[this->current_index]     = get_chr( x["quoted_status"]["place"]["full_name"] );
        this->quoted_place_type[this->current_index]          = get_chr( x["quoted_status"]["place"]["place_type"] );
        this->quoted_country[this->current_index]             = get_chr( x["quoted_status"]["place"]["country"] );
        this->quoted_country_code[this->current_index]        = get_chr( x["quoted_status"]["place"]["country_code"] );
        this->quoted_bbox_coords[this->current_index]         = get_bbox( x["quoted_status"]["place"]["bounding_box"]["coordinates"] );

        this->name[this->current_index]                        = get_chr( x["user"]["name"] );
        this->location[this->current_index]                    = get_chr( x["user"]["location"] );
        this->description[this->current_index]                 = get_chr( x["user"]["description"] );
        this->url[this->current_index]                         = get_chr( x["user"]["url"] );
        this->protected_[this->current_index]                  = get_lgl( x["user"]["protected"] );
        this->followers_count[this->current_index]             = get_int( x["user"]["followers_count"] );
        this->friends_count[this->current_index]               = get_int( x["user"]["friends_count"] );
        this->listed_count[this->current_index]                = get_int( x["user"]["listed_count"] );
        this->statuses_count[this->current_index]              = get_int( x["user"]["statuses_count"] );
        this->favourites_count[this->current_index]            = get_int( x["user"]["favourites_count"] );
        this->account_created_at[this->current_index]          = get_chr( x["user"]["created_at"] );
        this->verified[this->current_index]                    = get_lgl( x["user"]["verified"] );
        this->account_lang[this->current_index]                = get_chr( x["user"]["lang"] );
        this->profile_banner_url[this->current_index]          = get_chr( x["user"]["profile_banner_url"] );
        this->profile_image_url[this->current_index]           = get_chr( x["user"]["profile_image_url"] );
        this->timestamp_ms[this->current_index]                = get_timestamp_ms( x["timestamp_ms"] );
        this->contributors_enabled[this->current_index]        = get_lgl( x["user"]["countributors_enabled"] );



        this->current_index++;
    }; // push


    Rcpp::List to_r() {
        const auto max_length = this->current_index;

        vec_int seq_out(max_length);
        std::iota( std::begin(seq_out), std::end(seq_out), 0);

        vec_chr col_names{
            "user_id", 
            "status_id", 
            "created_at", 
            "screen_name", 
            "text",
            "source", 
            "reply_to_status_id", 
            "reply_to_user_id", 
            "reply_to_screen_name", 
            "is_quote", 
            "is_retweeted",

            "hashtags",
            "urls_expanded_url",
            "media_expanded_url",
            "media_url",
            "media_type",
            "mentions_user_id",
            "mentions_screen_name",

            "quoted_status_id",
            "quoted_text",
            "quoted_created_at",
            "quoted_source",
            "quoted_favorite_count",
            "quoted_retweet_count",
            "quoted_user_id",
            "quoted_screen_name",
            "quoted_name",
            "quoted_followers_count",
            "quoted_friends_count",
            "quoted_statuses_count",
            "quoted_location",
            "quoted_description",
            "quoted_verified",

            "retweet_status_id",
            "retweet_text",
            "retweet_created_at",
            "retweet_source",
            "retweet_favorite_count",
            "retweet_retweet_count",
            "retweet_user_id",
            "retweet_screen_name",
            "retweet_name",
            "retweet_followers_count",
            "retweet_friends_count",
            "retweet_statuses_count",
            "retweet_location",
            "retweet_description",
            "retweet_verified",

            "place_url",
            "place_name",
            "place_full_name",
            "place_type",
            "country",
            "country_code",
            "bbox_coords",

            "retweet_place_url",
            "retweet_place_name",
            "retweet_place_full_name",
            "retweet_place_type",
            "retweet_country",
            "retweet_country_code",
            "retweet_bbox_coords",
            "quoted_place_url",
            "quoted_place_name",
            "quoted_place_full_name",
            "quoted_place_type",
            "quoted_country",
            "quoted_country_code",
            "quoted_bbox_coords",

            "name",
            "location",
            "description",
            "url",
            "protected",
            "followers_count",
            "friends_count",
            "listed_count",
            "statuses_count",
            "favourites_count",
            "account_created_at",
            "verified",
            "account_lang",
            "profile_banner_url",
            "profile_image_url",
            "timestamp_ms",
            "contributors_enabled"
        };

        constexpr int n_cols = 86;
        Rcpp::List columns(n_cols);
        columns[0]   = this->user_id[seq_out];
        columns[1]   = this->status_id[seq_out];
        columns[2]   = this->created_at[seq_out];
        columns[3]   = this->screen_name[seq_out];
        columns[4]   = this->text[seq_out];

        columns[5]   = this->source[seq_out];
        columns[6]   = this->reply_to_status_id[seq_out];
        columns[7]   = this->reply_to_user_id[seq_out];
        columns[8]   = this->reply_to_screen_name[seq_out];
        columns[9]   = this->is_quote[seq_out];
        columns[10]  = this->is_retweeted[seq_out];

        columns[11]  = this->hashtags[seq_out];
        columns[12]  = this->urls_expanded_url[seq_out];
        columns[13]  = this->media_expanded_url[seq_out];
        columns[14]  = this->media_url[seq_out];
        columns[15]  = this->media_type[seq_out];
        columns[16]  = this->mentions_user_id[seq_out];
        columns[17]  = this->mentions_screen_name[seq_out];

        columns[18]  = this->quoted_status_id[seq_out];
        columns[19]  = this->quoted_text[seq_out];
        columns[20]  = this->quoted_created_at[seq_out];
        columns[21]  = this->quoted_source[seq_out];
        columns[22]  = this->quoted_favorite_count[seq_out];
        columns[23]  = this->quoted_retweet_count[seq_out];
        columns[24]  = this->quoted_user_id[seq_out];
        columns[25]  = this->quoted_screen_name[seq_out];
        columns[26]  = this->quoted_name[seq_out];
        columns[27]  = this->quoted_followers_count[seq_out];
        columns[28]  = this->quoted_friends_count[seq_out];
        columns[29]  = this->quoted_statuses_count[seq_out];
        columns[30]  = this->quoted_location[seq_out];
        columns[31]  = this->quoted_description[seq_out];
        columns[32]  = this->quoted_verified[seq_out];

        columns[33]  = this->retweet_status_id[seq_out];
        columns[34]  = this->retweet_text[seq_out];
        columns[35]  = this->retweet_created_at[seq_out];
        columns[36]  = this->retweet_source[seq_out];
        columns[37]  = this->retweet_favorite_count[seq_out];
        columns[38]  = this->retweet_retweet_count[seq_out];
        columns[39]  = this->retweet_user_id[seq_out];
        columns[40]  = this->retweet_screen_name[seq_out];
        columns[41]  = this->retweet_name[seq_out];
        columns[42]  = this->retweet_followers_count[seq_out];
        columns[43]  = this->retweet_friends_count[seq_out];
        columns[44]  = this->retweet_statuses_count[seq_out];
        columns[45]  = this->retweet_location[seq_out];
        columns[46]  = this->retweet_description[seq_out];
        columns[47]  = this->retweet_verified[seq_out];

        columns[48]  = this->place_url[seq_out];
        columns[49]  = this->place_name[seq_out];
        columns[50]  = this->place_full_name[seq_out];
        columns[51]  = this->place_type[seq_out];
        columns[52]  = this->country[seq_out];
        columns[53]  = this->country_code[seq_out];
        columns[54]  = this->bbox_coords[seq_out];

        columns[55]  = this->retweet_place_url[seq_out];
        columns[56]  = this->retweet_place_name[seq_out];
        columns[57]  = this->retweet_place_full_name[seq_out];
        columns[58]  = this->retweet_place_type[seq_out];
        columns[59]  = this->retweet_country[seq_out];
        columns[60]  = this->retweet_country_code[seq_out];
        columns[61]  = this->retweet_bbox_coords[seq_out];

        columns[62]  = this->quoted_place_url[seq_out];
        columns[63]  = this->quoted_place_name[seq_out];
        columns[64]  = this->quoted_place_full_name[seq_out];
        columns[65]  = this->quoted_place_type[seq_out];
        columns[66]  = this->quoted_country[seq_out];
        columns[67]  = this->quoted_country_code[seq_out];
        columns[68]  = this->quoted_bbox_coords[seq_out];

        columns[69]  = this->name[seq_out];
        columns[70]  = this->location[seq_out];
        columns[71]  = this->description[seq_out];
        columns[72]  = this->url[seq_out];
        columns[73]  = this->protected_[seq_out];
        columns[74]  = this->followers_count[seq_out];
        columns[75]  = this->friends_count[seq_out];
        columns[76]  = this->listed_count[seq_out];
        columns[77]  = this->statuses_count[seq_out];
        columns[78]  = this->favourites_count[seq_out];
        columns[79]  = this->account_created_at[seq_out];
        columns[80]  = this->verified[seq_out];
        columns[81]  = this->account_lang[seq_out];
        columns[82]  = this->profile_banner_url[seq_out];
        columns[83]  = this->profile_image_url[seq_out];

        this->timestamp_ms.attr("class") = Rcpp::CharacterVector::create("POSIXct", "POSIXt");
        this->timestamp_ms.attr("tzone") = "UTC";

        columns[84]  = this->timestamp_ms[seq_out]; 


        columns[85]  = this->contributors_enabled[seq_out];
        

        const int n_rows = max_length;
        finalize_df(columns, col_names, n_rows);

        return columns;
    }; // TweetDF.to_r()

}; // TweetDF


class PulseMeta {
    // Rcpp::List images_results;
    // Rcpp::List links_results;

    int current_index = 0;
    
    Rcpp::List rule_type;
    Rcpp::List rule_tag;
    Rcpp::List description;
    Rcpp::List value;
    
    Rcpp::List appid;
    Rcpp::List campaign_id;
    Rcpp::List campaign_title;
    Rcpp::List project_id;
    Rcpp::List project_title;

    Rcpp::List complex_value;

    public:
    // PulseMeta() {};

    PulseMeta(const int n_vals) {
        
        // this->links_results                      = Rcpp::List(n_vals, vec_chr(0));
        // this->images_results                     = Rcpp::List(n_vals, vec_chr(0));

        this->rule_type                          = Rcpp::List(n_vals, vec_chr(0));
        this->rule_tag                           = Rcpp::List(n_vals, vec_chr(0));
        this->description                        = Rcpp::List(n_vals, vec_chr(0));
        this->value                              = Rcpp::List(n_vals, vec_chr(0));
        this->description                        = Rcpp::List(n_vals, vec_chr(0));

        this->appid                              = Rcpp::List(n_vals, vec_chr(0));
        this->campaign_id                        = Rcpp::List(n_vals, vec_chr(0));
        this->campaign_title                     = Rcpp::List(n_vals, vec_chr(0));
        this->project_id                         = Rcpp::List(n_vals, vec_chr(0));
        this->project_title                      = Rcpp::List(n_vals, vec_chr(0));
        
        this->complex_value                      = Rcpp::List(n_vals, vec_chr(0));
    };


    void push(const rapidjson::Value& x) {
        const rapidjson::Value& meta = x["meta"];
        if (meta.Size() == 0) {
            return;
        }

        // this->images_results[this->current_index]                  = get_meta_results(meta, "images");
        // this->links_results[this->current_index]                   = get_meta_results(meta, "links");


        this->rule_type[this->current_index]                       = get_nested_meta_results(meta, "rule_matcher", "rule_type");
        this->rule_tag[this->current_index]                        = get_nested_meta_results(meta, "rule_matcher", "rule_tag");
        this->description[this->current_index]                     = get_nested_meta_results(meta, "rule_matcher", "description");

        this->value[this->current_index]                           = get_nested_meta_results(meta, "rule_matcher", "value");

        this->appid[this->current_index]                           = get_nested_meta_results(meta, "rule_matcher", "appid");
        this->campaign_id[this->current_index]                     = get_nested_meta_results(meta, "rule_matcher", "campaign_id");
        this->campaign_title[this->current_index]                  = get_nested_meta_results(meta, "rule_matcher", "campaign_title", true);
        this->project_id[this->current_index]                      = get_nested_meta_results(meta, "rule_matcher", "project_id");
        this->project_title[this->current_index]                   = get_nested_meta_results(meta, "rule_matcher", "project_title", true);

        this->complex_value[this->current_index]                   = get_nested_meta_results(meta, "rule_matcher", "complex_value", true);
        
        this->current_index++;   
    } // PulseMeta.push()
    

     Rcpp::List to_r() {
        using Rcpp::_;

        const auto max_length = this->current_index;

        vec_int seq_out(max_length);
        std::iota( std::begin(seq_out), std::end(seq_out), 0);

        
        // Rcpp::List links = Rcpp::List::create(
        //     _["links_results"]              = this->links_results[seq_out],
        //     _["images_results"]             = this->images_results[seq_out]
        // );

        const vec_chr col_names {
            "ist_rule_type",
            "ist_rule_tag",
            "ist_rule_value",
            "ist_description",
            "ist_appid",
            "ist_campaign_id",
            "ist_campaign_title",
            "ist_project_id",
            "ist_project_title",
            "ist_complex_value"
        };

        Rcpp::List out(max_length);
        
        for (int i = 0; i < max_length; ++i) {
            Rcpp::List out_row(10);

            out_row[0] = this->rule_type[i];
            out_row[1] = this->rule_tag[i];
            out_row[2] = this->value[i];
            out_row[3] = this->description[i];
            
            out_row[4] = this->appid[i];
            out_row[5] = this->campaign_id[i];
            out_row[6] = this->campaign_title[i];
            out_row[7] = this->project_id[i];
            out_row[8] = this->project_title[i];
            
            out_row[9] = this->complex_value[i];


            // out_row.attr("names") = col_names;

            vec_chr length_tester(this->rule_type[i]);
            const int n_rows = length_tester.length();
            finalize_df(out_row, col_names, n_rows);

            out[i] = out_row;
        }

        return out;
     }; // PulseMeta.to_r()

}; // PulseMeta














//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class TweetDF2 {
    // int current_index = 0;

    vec_int2 quoted_favorite_count;
    vec_int2 quoted_retweet_count;
    vec_int2 quoted_followers_count;
    vec_int2 quoted_friends_count;
    vec_int2 quoted_statuses_count;

    vec_int2 retweet_followers_count;
    vec_int2 retweet_friends_count;
    vec_int2 retweet_statuses_count;
    vec_int2 retweet_favorite_count;
    vec_int2 retweet_retweet_count;

    vec_int2 followers_count;
    vec_int2 friends_count;
    vec_int2 listed_count;
    vec_int2 statuses_count;
    vec_int2 favourites_count;

    vec_bool is_quote;
    vec_bool is_retweeted;

    vec_bool retweet_verified;

    vec_bool quoted_verified;
    vec_bool protected_;                           // `protected` is a C++ reserved keyword
    vec_bool verified;
    vec_bool contributors_enabled;

    vec_str user_id;
    vec_str status_id;
    vec_str created_at;
    vec_str screen_name;
    vec_str text;
    vec_str source;

    vec_str reply_to_status_id;
    vec_str reply_to_user_id;
    vec_str reply_to_screen_name;
    
    vec_str lang;
    vec_str retweet_status_id;

    vec_str place_url;
    vec_str place_name;
    vec_str place_full_name;
    vec_str place_type;
    vec_str country;
    vec_str country_code;

    vec_str retweet_text;
    vec_str retweet_created_at;
    vec_str retweet_source;
    vec_str retweet_user_id;
    vec_str retweet_screen_name;
    vec_str retweet_name;
    vec_str retweet_location;
    vec_str retweet_description;
    vec_str retweet_place_url;
    vec_str retweet_place_name;
    vec_str retweet_place_full_name;
    vec_str retweet_place_type;
    vec_str retweet_country;
    vec_str retweet_country_code;

    vec_str quoted_status_id;
    vec_str quoted_text;
    vec_str quoted_created_at;
    vec_str quoted_source;
    vec_str quoted_user_id;
    vec_str quoted_screen_name;
    vec_str quoted_name;
    vec_str quoted_location;
    vec_str quoted_description;
    vec_str quoted_place_url;
    vec_str quoted_place_name;
    vec_str quoted_place_full_name;
    vec_str quoted_place_type;
    vec_str quoted_country;
    vec_str quoted_country_code;

    vec_str name;
    vec_str location;
    vec_str description;
    vec_str url;
    vec_str account_created_at;
    vec_str account_lang;
    vec_str profile_banner_url;
    vec_str profile_image_url;
    vec_dbl2 timestamp_ms;

    list_str hashtags;
    list_str urls_expanded_url;
    list_str media_url;
    list_str media_expanded_url;
    list_str media_type;
    list_str mentions_user_id;
    list_str mentions_screen_name;
    list_dbl bbox_coords;
    list_dbl quoted_bbox_coords;
    list_dbl retweet_bbox_coords;



    public:
    // TweetDF() {};
    // ~TweetDF() {};

    // int get_current_index() {
    //     return this->current_index;
    // };


    TweetDF2(const int n_vals) {
        this->user_id                      = vec_str(n_vals);
        this->status_id                    = vec_str(n_vals);
        this->created_at                   = vec_str(n_vals);
        this->screen_name                  = vec_str(n_vals);
        this->text                         = vec_str(n_vals);
        this->source                       = vec_str(n_vals);
        this->reply_to_status_id           = vec_str(n_vals);
        this->reply_to_user_id             = vec_str(n_vals);
        this->reply_to_screen_name         = vec_str(n_vals);
        this->is_quote                     = vec_bool(n_vals);
        this->is_retweeted                 = vec_bool(n_vals);

        this->hashtags                     = list_str(n_vals);
        this->urls_expanded_url            = list_str(n_vals);

        this->media_expanded_url           = list_str(n_vals);
        this->media_url                    = list_str(n_vals);
        this->media_expanded_url           = list_str(n_vals);
        this->media_type                   = list_str(n_vals);

        this->mentions_user_id             = list_str(n_vals);
        this->mentions_screen_name         = list_str(n_vals);

        this->lang                         = vec_str(n_vals);

        this->quoted_status_id             = vec_str(n_vals); 
        this->quoted_text                  = vec_str(n_vals); 
        this->quoted_created_at            = vec_str(n_vals); 
        this->quoted_source                = vec_str(n_vals); 
        this->quoted_favorite_count        = vec_int2(n_vals, INT_MIN); 
        this->quoted_retweet_count         = vec_int2(n_vals, INT_MIN); 
        this->quoted_user_id               = vec_str(n_vals); 
        this->quoted_screen_name           = vec_str(n_vals); 
        this->quoted_name                  = vec_str(n_vals); 
        this->quoted_followers_count       = vec_int2(n_vals, INT_MIN); 
        this->quoted_friends_count         = vec_int2(n_vals, INT_MIN); 
        this->quoted_statuses_count        = vec_int2(n_vals, INT_MIN); 
        this->quoted_location              = vec_str(n_vals);
        this->quoted_description           = vec_str(n_vals);
        this->quoted_verified              = vec_bool(n_vals, NA_LOGICAL);

        this->retweet_status_id            = vec_str(n_vals);
        this->retweet_text                 = vec_str(n_vals);
        this->retweet_created_at           = vec_str(n_vals);
        this->retweet_source               = vec_str(n_vals);
        this->retweet_favorite_count       = vec_int2(n_vals, INT_MIN);
        this->retweet_retweet_count        = vec_int2(n_vals, INT_MIN);
        this->retweet_user_id              = vec_str(n_vals);
        this->retweet_screen_name          = vec_str(n_vals);
        this->retweet_name                 = vec_str(n_vals);
        this->retweet_followers_count      = vec_int2(n_vals, INT_MIN);
        this->retweet_friends_count        = vec_int2(n_vals, INT_MIN);
        this->retweet_statuses_count       = vec_int2(n_vals, INT_MIN);
        this->retweet_location             = vec_str(n_vals);
        this->retweet_description          = vec_str(n_vals);
        this->retweet_verified             = vec_bool(n_vals, NA_LOGICAL);

        this->place_url                    = vec_str(n_vals);
        this->place_name                   = vec_str(n_vals);
        this->place_full_name              = vec_str(n_vals);
        this->place_type                   = vec_str(n_vals);
        this->country                      = vec_str(n_vals);
        this->country_code                 = vec_str(n_vals);
        this->bbox_coords                  = list_dbl(n_vals);

        this->retweet_place_url            = vec_str(n_vals);
        this->retweet_place_name           = vec_str(n_vals);
        this->retweet_place_full_name      = vec_str(n_vals);
        this->retweet_place_type           = vec_str(n_vals);
        this->retweet_country              = vec_str(n_vals);
        this->retweet_country_code         = vec_str(n_vals);
        this->retweet_bbox_coords          = list_dbl(n_vals);

        this->quoted_place_url            = vec_str(n_vals);
        this->quoted_place_name           = vec_str(n_vals);
        this->quoted_place_full_name      = vec_str(n_vals);
        this->quoted_place_type           = vec_str(n_vals);
        this->quoted_country              = vec_str(n_vals);
        this->quoted_country_code         = vec_str(n_vals);
        this->quoted_bbox_coords          = list_dbl(n_vals);

        this->name                         = vec_str(n_vals);
        this->location                     = vec_str(n_vals);
        this->description                  = vec_str(n_vals);
        this->url                          = vec_str(n_vals);
        this->protected_                   = vec_bool(n_vals);
        this->followers_count              = vec_int2(n_vals, INT_MIN);
        this->friends_count                = vec_int2(n_vals, INT_MIN);
        this->listed_count                 = vec_int2(n_vals, INT_MIN);
        this->statuses_count               = vec_int2(n_vals, INT_MIN);
        this->favourites_count             = vec_int2(n_vals, INT_MIN);
        this->account_created_at           = vec_str(n_vals);
        this->verified                     = vec_bool(n_vals);
        this->account_lang                 = vec_str(n_vals);
        this->profile_banner_url           = vec_str(n_vals);
        this->profile_image_url            = vec_str(n_vals);
        this->timestamp_ms                 = vec_dbl2(n_vals, na_dbl);
        this->contributors_enabled         = vec_bool(n_vals);

    };


    void push(const rapidjson::Value& x, int current_index) {
        // this->status_id[this->current_index]  =   get_str2(this->status_id[this->current_index], x["id_str"] );
        // this->user_id[this->current_index]  =   get_str2(this->user_id[this->current_index], x["user"]["id_str"] );
        // this->created_at[this->current_index] = get_str2(this->created_at[this->current_index], x["created_at"] );

        this->user_id[current_index]                     = get_str( x["user"]["id_str"] );
        this->status_id[current_index]                   = get_str( x["id_str"] );
        this->created_at[current_index]                  = get_str( x["created_at"] );
        this->screen_name[current_index]                 = get_str( x["user"]["screen_name"] );
        this->text[current_index]                        = get_str_check( x["extended_tweet"]["full_text"], x["text"] );
        this->source[current_index]                      = get_str( x["source"] );
        this->reply_to_status_id[current_index]          = get_str( x["in_reply_to_status_id_str"] );
        this->reply_to_user_id[current_index]            = get_str( x["in_reply_to_user_id_str"] );
        this->reply_to_screen_name[current_index]        = get_str( x["in_reply_to_screen_name"] );
        this->is_quote[current_index]                    = get_bool( x["is_quote_status"] );
        this->is_retweeted[current_index]                = get_bool( x["retweeted"] );

        this->hashtags[current_index]                    = map_entities2(x, "hashtags", "text");
        this->urls_expanded_url[current_index]           = map_entities2(x, "urls", "expanded_url");

        this->media_expanded_url[current_index]          = map_entities2(x, "media", "expanded_url");
        this->media_url[current_index]                   = map_entities2(x, "media", "media_url");
        this->media_type[current_index]                  = map_entities2(x, "media", "type");

        this->mentions_user_id[current_index]            = map_entities2(x, "user_mentions", "id_str");
        this->mentions_screen_name[current_index]        = map_entities2(x, "user_mentions", "screen_name");

        this->lang[current_index]                        = get_str( x["lang"] );

        this->quoted_status_id[current_index]            = get_str( x["quoted_status_id_str"] );
        this->quoted_text[current_index]                 = get_str_check( x["quoted_status"]["extended_tweet"]["full_text"], x["quoted_status"]["text"] );
        this->quoted_created_at[current_index]           = get_str( x["quoted_status"]["created_at"] );
        this->quoted_source[current_index]               = get_str( x["quoted_status"]["source"] );
        this->quoted_favorite_count[current_index]       = get_int( x["quoted_status"]["favorite_count"] );
        this->quoted_retweet_count[current_index]        = get_int( x["quoted_status"]["retweet_count"] );
        this->quoted_user_id[current_index]              = get_str( x["quoted_status"]["user"]["id_str"] );
        this->quoted_screen_name[current_index]          = get_str( x["quoted_status"]["user"]["screen_name"] );
        this->quoted_name[current_index]                 = get_str( x["quoted_status"]["user"]["name"] );
        this->quoted_followers_count[current_index]      = get_int( x["quoted_status"]["user"]["followers_count"] );
        this->quoted_friends_count[current_index]        = get_int( x["quoted_status"]["user"]["friends_count"] );
        this->quoted_statuses_count[current_index]       = get_int( x["quoted_status"]["user"]["statuses_count"] );
        this->quoted_location[current_index]             = get_str( x["quoted_status"]["user"]["location"] );
        this->quoted_description[current_index]          = get_str( x["quoted_status"]["user"]["description"] );
        this->quoted_verified[current_index]             = get_bool( x["quoted_status"]["user"]["verified"] );

        this->retweet_status_id[current_index]           = get_str( x["retweeted_status"]["id_str"] );
        this->retweet_text[current_index]                = get_str_check( x["retweeted_status"]["extended_tweet"]["full_text"], x["retweeted_status"]["text"] );
        this->retweet_created_at[current_index]          = get_str( x["retweeted_status"]["created_at"] );
        this->retweet_source[current_index]              = get_str( x["retweeted_status"]["source"] );
        this->retweet_favorite_count[current_index]      = get_int( x["retweeted_status"]["favorite_count"] );
        this->retweet_retweet_count[current_index]       = get_int( x["retweeted_status"]["retweet_count"] );
        this->retweet_user_id[current_index]             = get_str( x["retweeted_status"]["user"]["id_str"] );
        this->retweet_screen_name[current_index]         = get_str( x["retweeted_status"]["user"]["screen_name"] );
        this->retweet_name[current_index]                = get_str( x["retweeted_status"]["user"]["name"] );
        this->retweet_followers_count[current_index]     = get_int( x["retweeted_status"]["user"]["followers_count"] );
        this->retweet_friends_count[current_index]       = get_int( x["retweeted_status"]["user"]["followers_count"] );
        this->retweet_statuses_count[current_index]      = get_int( x["retweeted_status"]["user"]["statuses_count"] );
        this->retweet_location[current_index]            = get_str( x["retweeted_status"]["user"]["location"] );
        this->retweet_description[current_index]         = get_str( x["retweeted_status"]["user"]["description"] );
        this->retweet_verified[current_index]            = get_bool( x["retweeted_status"]["user"]["verified"] );

        this->place_url[current_index]                   = get_str( x["place"]["url"] );
        this->place_name[current_index]                  = get_str( x["place"]["name"] );
        this->place_full_name[current_index]             = get_str( x["place"]["full_name"] );
        this->place_type[current_index]                  = get_str( x["place"]["place_type"] );
        this->country[current_index]                     = get_str( x["place"]["country"] );
        this->country_code[current_index]                = get_str( x["place"]["country_code"] );
        this->bbox_coords[current_index]                 = get_bbox2( x["place"]["bounding_box"]["coordinates"] );

        this->retweet_place_url[current_index]          = get_str( x["retweeted_status"]["place"]["url"] );
        this->retweet_place_name[current_index]         = get_str( x["retweeted_status"]["place"]["name"] );
        this->retweet_place_full_name[current_index]    = get_str( x["retweeted_status"]["place"]["full_name"] );
        this->retweet_place_type[current_index]         = get_str( x["retweeted_status"]["place"]["place_type"] );
        this->retweet_country[current_index]            = get_str( x["retweeted_status"]["place"]["country"] );
        this->retweet_country_code[current_index]       = get_str( x["retweeted_status"]["place"]["country_code"] );
        this->retweet_bbox_coords[current_index]        = get_bbox2( x["retweeted_status"]["place"]["bounding_box"]["coordinates"] );

        this->quoted_place_url[current_index]           = get_str( x["quoted_status"]["place"]["url"] );
        this->quoted_place_name[current_index]          = get_str( x["quoted_status"]["place"]["name"] );
        this->quoted_place_full_name[current_index]     = get_str( x["quoted_status"]["place"]["full_name"] );
        this->quoted_place_type[current_index]          = get_str( x["quoted_status"]["place"]["place_type"] );
        this->quoted_country[current_index]             = get_str( x["quoted_status"]["place"]["country"] );
        this->quoted_country_code[current_index]        = get_str( x["quoted_status"]["place"]["country_code"] );
        this->quoted_bbox_coords[current_index]         = get_bbox2( x["quoted_status"]["place"]["bounding_box"]["coordinates"] );

        this->name[current_index]                        = get_str( x["user"]["name"] );
        this->location[current_index]                    = get_str( x["user"]["location"] );
        this->description[current_index]                 = get_str( x["user"]["description"] );
        this->url[current_index]                         = get_str( x["user"]["url"] );
        this->protected_[current_index]                  = get_bool( x["user"]["protected"] );
        this->followers_count[current_index]             = get_int( x["user"]["followers_count"] );
        this->friends_count[current_index]               = get_int( x["user"]["friends_count"] );
        this->listed_count[current_index]                = get_int( x["user"]["listed_count"] );
        this->statuses_count[current_index]              = get_int( x["user"]["statuses_count"] );
        this->favourites_count[current_index]            = get_int( x["user"]["favourites_count"] );
        this->account_created_at[current_index]          = get_str( x["user"]["created_at"] );
        this->verified[current_index]                    = get_bool( x["user"]["verified"] );
        this->account_lang[current_index]                = get_str( x["user"]["lang"] );
        this->profile_banner_url[current_index]          = get_str( x["user"]["profile_banner_url"] );
        this->profile_image_url[current_index]           = get_str( x["user"]["profile_image_url"] );
        this->timestamp_ms[current_index]                = get_timestamp_ms( x["timestamp_ms"] );
        this->contributors_enabled[current_index]        = get_bool( x["user"]["countributors_enabled"] );



        // this->current_index++;
    }; // push


    Rcpp::List to_r(int max_length) {
        // const auto max_length = this->current_index;

        vec_int seq_out(max_length);
        std::iota( std::begin(seq_out), std::end(seq_out), 0);

        vec_chr col_names{
            "user_id", 
            "status_id", 
            "created_at", 
            "screen_name", 
            "text",
            "source", 
            "reply_to_status_id", 
            "reply_to_user_id", 
            "reply_to_screen_name", 
            "is_quote", 
            "is_retweeted",

            "hashtags",
            "urls_expanded_url",
            "media_expanded_url",
            "media_url",
            "media_type",
            "mentions_user_id",
            "mentions_screen_name",

            "quoted_status_id",
            "quoted_text",
            "quoted_created_at",
            "quoted_source",
            "quoted_favorite_count",
            "quoted_retweet_count",
            "quoted_user_id",
            "quoted_screen_name",
            "quoted_name",
            "quoted_followers_count",
            "quoted_friends_count",
            "quoted_statuses_count",
            "quoted_location",
            "quoted_description",
            "quoted_verified",

            "retweet_status_id",
            "retweet_text",
            "retweet_created_at",
            "retweet_source",
            "retweet_favorite_count",
            "retweet_retweet_count",
            "retweet_user_id",
            "retweet_screen_name",
            "retweet_name",
            "retweet_followers_count",
            "retweet_friends_count",
            "retweet_statuses_count",
            "retweet_location",
            "retweet_description",
            "retweet_verified",

            "place_url",
            "place_name",
            "place_full_name",
            "place_type",
            "country",
            "country_code",
            "bbox_coords",

            "retweet_place_url",
            "retweet_place_name",
            "retweet_place_full_name",
            "retweet_place_type",
            "retweet_country",
            "retweet_country_code",
            "retweet_bbox_coords",
            "quoted_place_url",
            "quoted_place_name",
            "quoted_place_full_name",
            "quoted_place_type",
            "quoted_country",
            "quoted_country_code",
            "quoted_bbox_coords",

            "name",
            "location",
            "description",
            "url",
            "protected",
            "followers_count",
            "friends_count",
            "listed_count",
            "statuses_count",
            "favourites_count",
            "account_created_at",
            "verified",
            "account_lang",
            "profile_banner_url",
            "profile_image_url",
            "timestamp_ms",
            "contributors_enabled"
        };

        constexpr int n_cols = 86;
        Rcpp::List columns(n_cols);
        columns[0]   = this->user_id;
        columns[1]   = this->status_id;
        columns[2]   = this->created_at;
        columns[3]   = this->screen_name;
        columns[4]   = this->text;

        columns[5]   = this->source;
        columns[6]   = this->reply_to_status_id;
        columns[7]   = this->reply_to_user_id;
        columns[8]   = this->reply_to_screen_name;
        columns[9]   = this->is_quote;
        columns[10]  = this->is_retweeted;

        columns[11]  = this->hashtags;
        columns[12]  = this->urls_expanded_url;
        columns[13]  = this->media_expanded_url;
        columns[14]  = this->media_url;
        columns[15]  = this->media_type;
        columns[16]  = this->mentions_user_id;
        columns[17]  = this->mentions_screen_name;

        columns[18]  = this->quoted_status_id;
        columns[19]  = this->quoted_text;
        columns[20]  = this->quoted_created_at;
        columns[21]  = this->quoted_source;
        columns[22]  = this->quoted_favorite_count;
        columns[23]  = this->quoted_retweet_count;
        columns[24]  = this->quoted_user_id;
        columns[25]  = this->quoted_screen_name;
        columns[26]  = this->quoted_name;
        columns[27]  = this->quoted_followers_count;
        columns[28]  = this->quoted_friends_count;
        columns[29]  = this->quoted_statuses_count;
        columns[30]  = this->quoted_location;
        columns[31]  = this->quoted_description;
        columns[32]  = this->quoted_verified;

        columns[33]  = this->retweet_status_id;
        columns[34]  = this->retweet_text;
        columns[35]  = this->retweet_created_at;
        columns[36]  = this->retweet_source;
        columns[37]  = this->retweet_favorite_count;
        columns[38]  = this->retweet_retweet_count;
        columns[39]  = this->retweet_user_id;
        columns[40]  = this->retweet_screen_name;
        columns[41]  = this->retweet_name;
        columns[42]  = this->retweet_followers_count;
        columns[43]  = this->retweet_friends_count;
        columns[44]  = this->retweet_statuses_count;
        columns[45]  = this->retweet_location;
        columns[46]  = this->retweet_description;
        columns[47]  = this->retweet_verified;

        columns[48]  = this->place_url;
        columns[49]  = this->place_name;
        columns[50]  = this->place_full_name;
        columns[51]  = this->place_type;
        columns[52]  = this->country;
        columns[53]  = this->country_code;
        columns[54]  = this->bbox_coords;

        columns[55]  = this->retweet_place_url;
        columns[56]  = this->retweet_place_name;
        columns[57]  = this->retweet_place_full_name;
        columns[58]  = this->retweet_place_type;
        columns[59]  = this->retweet_country;
        columns[60]  = this->retweet_country_code;
        columns[61]  = this->retweet_bbox_coords;

        columns[62]  = this->quoted_place_url;
        columns[63]  = this->quoted_place_name;
        columns[64]  = this->quoted_place_full_name;
        columns[65]  = this->quoted_place_type;
        columns[66]  = this->quoted_country;
        columns[67]  = this->quoted_country_code;
        columns[68]  = this->quoted_bbox_coords;

        columns[69]  = this->name;
        columns[70]  = this->location;
        columns[71]  = this->description;
        columns[72]  = this->url;
        columns[73]  = this->protected_;
        columns[74]  = this->followers_count;
        columns[75]  = this->friends_count;
        columns[76]  = this->listed_count;
        columns[77]  = this->statuses_count;
        columns[78]  = this->favourites_count;
        columns[79]  = this->account_created_at;
        columns[80]  = this->verified;
        columns[81]  = this->account_lang;
        columns[82]  = this->profile_banner_url;
        columns[83]  = this->profile_image_url;

        // this->timestamp_ms.attr("class") = Rcpp::CharacterVector::create("POSIXct", "POSIXt");
        // this->timestamp_ms.attr("tzone") = "UTC";

        columns[84]  = this->timestamp_ms; 


        columns[85]  = this->contributors_enabled;
        

        const int n_rows = max_length;
        finalize_df(columns, col_names, n_rows);

        return columns;
    }; // TweetDF2.to_r()

}; // TweetDF2


} // namespace tweetio

#endif