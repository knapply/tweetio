#include "typedefs.hpp"

#include "json.hpp"

namespace knapply { // knapply

class TweetDF {
    vec_chr user_id;
    vec_chr status_id;
    vec_chr created_at;
    vec_chr screen_name;
    vec_chr text;
    vec_chr source;

    vec_chr reply_to_status_id;
    vec_chr reply_to_user_id;
    vec_chr reply_to_screen_name;

    vec_lgl is_quote;
    vec_lgl is_retweeted;

    Rcpp::List hashtags;
    Rcpp::List urls_expanded_url;

    Rcpp::List media_url;
    Rcpp::List media_expanded_url;
    Rcpp::List media_type;

    Rcpp::List mentions_user_id;
    Rcpp::List mentions_screen_name;
    
    vec_chr lang;

    vec_chr quoted_status_id;
    vec_chr quoted_text;
    vec_chr quoted_created_at;
    vec_chr quoted_source;
    vec_int quoted_favorite_count;
    vec_int quoted_retweet_count;
    vec_chr quoted_user_id;
    vec_chr quoted_screen_name;
    vec_chr quoted_name;
    vec_int quoted_followers_count;
    vec_int quoted_friends_count;
    vec_int quoted_statuses_count;
    vec_chr quoted_location;
    vec_chr quoted_description;
    vec_lgl quoted_verified;

    vec_chr retweet_status_id;
    vec_chr retweet_text;
    vec_chr retweet_created_at;
    vec_chr retweet_source;
    vec_int retweet_favorite_count;
    vec_int retweet_retweet_count;
    vec_chr retweet_user_id;
    vec_chr retweet_screen_name;
    vec_chr retweet_name;
    vec_int retweet_followers_count;
    vec_int retweet_friends_count;
    vec_int retweet_statuses_count;
    vec_chr retweet_location;
    vec_chr retweet_description;
    vec_lgl retweet_verified;

    vec_chr place_url;
    vec_chr place_name;
    vec_chr place_full_name;
    vec_chr place_type;
    vec_chr country;
    vec_chr country_code;
    Rcpp::List bbox_coords;

    vec_chr    retweet_place_url;
    vec_chr    retweet_place_name;
    vec_chr    retweet_place_full_name;
    vec_chr    retweet_place_type;
    vec_chr    retweet_country;
    vec_chr    retweet_country_code;
    Rcpp::List retweet_bbox_coords;

    vec_chr    quoted_place_url;
    vec_chr    quoted_place_name;
    vec_chr    quoted_place_full_name;
    vec_chr    quoted_place_type;
    vec_chr    quoted_country;
    vec_chr    quoted_country_code;
    Rcpp::List quoted_bbox_coords;

    vec_chr status_url;
    vec_chr name;
    vec_chr location;
    vec_chr description;
    vec_chr url;
    vec_lgl protected_;                           // `protected` is a C++ reserved keyword
    vec_int followers_count;
    vec_int friends_count;
    vec_int listed_count;
    vec_int statuses_count;
    vec_int favourites_count;
    vec_chr account_created_at;
    vec_lgl verified;
    vec_chr account_lang;
    vec_chr profile_banner_url;
    vec_chr profile_image_url;
    vec_chr timestamp_ms;
    vec_lgl contributors_enabled;

    public:
    TweetDF() {};

    TweetDF(const i64 n_vals) {
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


        // this->status_url                   = vec_chr(n_vals, NA_STRING);
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
        this->timestamp_ms                 = vec_chr(n_vals, NA_STRING);
        this->contributors_enabled         = vec_lgl(n_vals, NA_LOGICAL);

    };

    void push(const rapidjson::Value& x, i64 i) {
        this->user_id[i]                     = get_chr( x["user"]["id_str"] );
        this->status_id[i]                   = get_chr( x["id_str"] );
        this->created_at[i]                  = get_chr( x["created_at"] );
        this->screen_name[i]                 = get_chr( x["user"]["screen_name"] );
        this->text[i]                        = get_chr_check( x["extended_tweet"]["full_text"], x["text"] );
        this->source[i]                      = get_chr( x["source"] );
        this->reply_to_status_id[i]          = get_chr( x["in_reply_to_status_id_str"] );
        this->reply_to_user_id[i]            = get_chr( x["in_reply_to_user_id_str"] );
        this->reply_to_screen_name[i]        = get_chr( x["in_reply_to_screen_name"] );
        this->is_quote[i]                    = get_lgl( x["is_quote_status"] );
        this->is_retweeted[i]                = get_lgl( x["retweeted"] );

        this->hashtags[i]                    = map_entities(x, "hashtags", "text");
        this->urls_expanded_url[i]           = map_entities(x, "urls", "expanded_url");

        this->media_expanded_url[i]          = map_entities(x, "media", "expanded_url");
        this->media_url[i]                   = map_entities(x, "media", "media_url");
        this->media_type[i]                  = map_entities(x, "media", "type");

        this->mentions_user_id[i]            = map_entities(x, "user_mentions", "id_str");
        this->mentions_screen_name[i]        = map_entities(x, "user_mentions", "screen_name");

        this->lang[i]                        = get_chr( x["lang"] );

        this->quoted_status_id[i]            = get_chr( x["quoted_status_id_str"] );
        this->quoted_text[i]                 = get_chr_check( x["quoted_status"]["extended_tweet"]["full_text"], x["quoted_status"]["text"] );
        this->quoted_created_at[i]           = get_chr( x["quoted_status"]["created_at"] );
        this->quoted_source[i]               = get_chr( x["quoted_status"]["source"] );
        this->quoted_favorite_count[i]       = get_int( x["quoted_status"]["favorite_count"] );
        this->quoted_retweet_count[i]        = get_int( x["quoted_status"]["retweet_count"] );
        this->quoted_user_id[i]              = get_chr( x["quoted_status"]["user"]["id_str"] );
        this->quoted_screen_name[i]          = get_chr( x["quoted_status"]["user"]["screen_name"] );
        this->quoted_name[i]                 = get_chr( x["quoted_status"]["user"]["name"] );
        this->quoted_followers_count[i]      = get_int( x["quoted_status"]["user"]["followers_count"] );
        this->quoted_friends_count[i]        = get_int( x["quoted_status"]["user"]["friends_count"] );
        this->quoted_statuses_count[i]       = get_int( x["quoted_status"]["user"]["statuses_count"] );
        this->quoted_location[i]             = get_chr( x["quoted_status"]["user"]["location"] );
        this->quoted_description[i]          = get_chr( x["quoted_status"]["user"]["description"] );
        this->quoted_verified[i]             = get_lgl( x["quoted_status"]["user"]["verified"] );

        this->retweet_status_id[i]           = get_chr( x["retweeted_status"]["id_str"] );
        this->retweet_text[i]                = get_chr_check( x["retweeted_status"]["extended_tweet"]["full_text"], x["retweeted_status"]["text"] );
        this->retweet_created_at[i]          = get_chr( x["retweeted_status"]["created_at"] );
        this->retweet_source[i]              = get_chr( x["retweeted_status"]["source"] );
        this->retweet_favorite_count[i]      = get_int( x["retweeted_status"]["favorite_count"] );
        this->retweet_retweet_count[i]       = get_int( x["retweeted_status"]["retweet_count"] );
        this->retweet_user_id[i]             = get_chr( x["retweeted_status"]["user"]["id_str"] );
        this->retweet_screen_name[i]         = get_chr( x["retweeted_status"]["user"]["screen_name"] );
        this->retweet_name[i]                = get_chr( x["retweeted_status"]["user"]["name"] );
        this->retweet_followers_count[i]     = get_int( x["retweeted_status"]["user"]["followers_count"] );
        this->retweet_friends_count[i]       = get_int( x["retweeted_status"]["user"]["followers_count"] );
        this->retweet_statuses_count[i]      = get_int( x["retweeted_status"]["user"]["statuses_count"] );
        this->retweet_location[i]            = get_chr( x["retweeted_status"]["user"]["location"] );
        this->retweet_description[i]         = get_chr( x["retweeted_status"]["user"]["description"] );
        this->retweet_verified[i]            = get_lgl( x["retweeted_status"]["user"]["verified"] );

        this->place_url[i]                   = get_chr( x["place"]["url"] );
        this->place_name[i]                  = get_chr( x["place"]["name"] );
        this->place_full_name[i]             = get_chr( x["place"]["full_name"] );
        this->place_type[i]                  = get_chr( x["place"]["place_type"] );
        this->country[i]                     = get_chr( x["place"]["country"] );
        this->country_code[i]                = get_chr( x["place"]["country_code"] );
        this->bbox_coords[i]                 = get_bbox( x["place"]["bounding_box"]["coordinates"] );

        this->retweet_place_url[i]          = get_chr( x["retweeted_status"]["place"]["url"] );
        this->retweet_place_name[i]         = get_chr( x["retweeted_status"]["place"]["name"] );
        this->retweet_place_full_name[i]    = get_chr( x["retweeted_status"]["place"]["full_name"] );
        this->retweet_place_type[i]         = get_chr( x["retweeted_status"]["place"]["place_type"] );
        this->retweet_country[i]            = get_chr( x["retweeted_status"]["place"]["country"] );
        this->retweet_country_code[i]       = get_chr( x["retweeted_status"]["place"]["country_code"] );
        this->retweet_bbox_coords[i]        = get_bbox( x["retweeted_status"]["place"]["bounding_box"]["coordinates"] );

        this->quoted_place_url[i]           = get_chr( x["quoted_status"]["place"]["url"] );
        this->quoted_place_name[i]          = get_chr( x["quoted_status"]["place"]["name"] );
        this->quoted_place_full_name[i]     = get_chr( x["quoted_status"]["place"]["full_name"] );
        this->quoted_place_type[i]          = get_chr( x["quoted_status"]["place"]["place_type"] );
        this->quoted_country[i]             = get_chr( x["quoted_status"]["place"]["country"] );
        this->quoted_country_code[i]        = get_chr( x["quoted_status"]["place"]["country_code"] );
        this->quoted_bbox_coords[i]         = get_bbox( x["quoted_status"]["place"]["bounding_box"]["coordinates"] );

        // this->status_url                     = get_chr( x[""][""] );
        this->name[i]                        = get_chr( x["user"]["name"] );
        this->location[i]                    = get_chr( x["user"]["location"] );
        this->description[i]                 = get_chr( x["user"]["description"] );
        this->url[i]                         = get_chr( x["user"]["url"] );
        this->protected_[i]                  = get_lgl( x["user"]["protected"] );
        this->followers_count[i]             = get_int( x["user"]["followers_count"] );
        this->friends_count[i]               = get_int( x["user"]["friends_count"] );
        this->listed_count[i]                = get_int( x["user"]["listed_count"] );
        this->statuses_count[i]              = get_int( x["user"]["statuses_count"] );
        this->favourites_count[i]            = get_int( x["user"]["favourites_count"] );
        this->account_created_at[i]          = get_chr( x["user"]["created_at"] );
        this->verified[i]                    = get_lgl( x["user"]["verified"] );
        this->account_lang[i]                = get_chr( x["user"]["lang"] );
        this->profile_banner_url[i]          = get_chr( x["user"]["profile_banner_url"] );
        this->profile_image_url[i]           = get_chr( x["user"]["profile_image_url"] );
        this->timestamp_ms[i]                = get_chr( x["timestamp_ms"] );
        this->contributors_enabled[i]        = get_lgl( x["user"]["countributors_enabled"] );
    };


    Rcpp::List to_r(const i32& max_length) {
        using Rcpp::_;

        vec_int seq_out(max_length);
        vec_chr row_names(max_length);
        for (i32 i = 0; i < seq_out.size(); ++i) {
            seq_out[i] = i;
            row_names[i] = Rcpp::String(i + 1);
        }
        
        Rcpp::List main = Rcpp::List::create(
            _["user_id"]              = this->user_id[seq_out],
            _["status_id"]            = this->status_id[seq_out],
            _["created_at"]           = this->created_at[seq_out],
            _["screen_name"]          = this->screen_name[seq_out],
            _["text"]                 = this->text[seq_out],
            _["source"]               = this->source[seq_out],
            _["reply_to_status_id"]   = this->reply_to_status_id[seq_out],
            _["reply_to_user_id"]     = this->reply_to_user_id[seq_out],
            _["reply_to_screen_name"] = this->reply_to_screen_name[seq_out],
            _["is_quote"]             = this->is_quote[seq_out],
            _["is_retweeted"]         = this->is_retweeted[seq_out]
        );
        main.attr("class") = "data.frame";
        main.attr("row.names") = row_names;


        Rcpp::List entities = Rcpp::List::create(
            _["hashtags"]             = this->hashtags[seq_out],
            _["urls_expanded_url"]    = this->urls_expanded_url[seq_out],

            _["media_expanded_url"]   = this->media_expanded_url[seq_out],
            _["media_url"]            = this->media_url[seq_out],
            _["media_type"]           = this->media_type[seq_out],

            _["mentions_user_id"]     = this->mentions_user_id[seq_out],
            _["mentions_screen_name"] = this->mentions_screen_name[seq_out]
        );
        entities.attr("class") = "data.frame";
        entities.attr("row.names") = row_names;


        Rcpp::List meta = Rcpp::List::create(
            _["lang"]                 = this->lang[seq_out]
        );
        meta.attr("class") = "data.frame";
        meta.attr("row.names") = row_names;


        Rcpp::List quoted = Rcpp::List::create(
            _["quoted_status_id"]          = this->quoted_status_id[seq_out],
            _["quoted_text"]               = this->quoted_text[seq_out],
            _["quoted_created_at"]         = this->quoted_created_at[seq_out],
            _["quoted_source"]             = this->quoted_source[seq_out],
            _["quoted_favorite_count"]     = this->quoted_favorite_count[seq_out],
            _["quoted_retweet_count"]      = this->quoted_retweet_count[seq_out],
            _["quoted_user_id"]            = this->quoted_user_id[seq_out],
            _["quoted_screen_name"]        = this->quoted_screen_name[seq_out],
            _["quoted_name"]               = this->quoted_name[seq_out],
            _["quoted_followers_count"]    = this->quoted_followers_count[seq_out],
            _["quoted_friends_count"]      = this->quoted_friends_count[seq_out],
            _["quoted_statuses_count"]     = this->quoted_statuses_count[seq_out],
            _["quoted_location"]           = this->quoted_location[seq_out],
            _["quoted_description"]        = this->quoted_description[seq_out],
            _["quoted_verified"]           = this->quoted_verified[seq_out]
        );
        quoted.attr("class") = "data.frame";
        quoted.attr("row.names") = row_names;


        Rcpp::List retweet = Rcpp::List::create(
            _["retweet_status_id"]         = this->retweet_status_id[seq_out],
            _["retweet_text"]              = this->retweet_text[seq_out],
            _["retweet_created_at"]        = this->retweet_created_at[seq_out],
            _["retweet_source"]            = this->retweet_source[seq_out],
            _["retweet_favorite_count"]    = this->retweet_favorite_count[seq_out],
            _["retweet_retweet_count"]     = this->retweet_retweet_count[seq_out],
            _["retweet_user_id"]           = this->retweet_user_id[seq_out],
            _["retweet_screen_name"]       = this->retweet_screen_name[seq_out],
            _["retweet_name"]              = this->retweet_name[seq_out],
            _["retweet_followers_count"]   = this->retweet_followers_count[seq_out],
            _["retweet_friends_count"]     = this->retweet_friends_count[seq_out],
            _["retweet_statuses_count"]    = this->retweet_statuses_count[seq_out],
            _["retweet_location"]          = this->retweet_location[seq_out],
            _["retweet_description"]       = this->retweet_description[seq_out],
            _["retweet_verified"]          = this->retweet_verified[seq_out]
        );
        retweet.attr("class") = "data.frame";
        retweet.attr("row.names") = row_names;


        Rcpp::List geo1 = Rcpp::List::create(
            _["place_url"]                 = this->place_url[seq_out],
            _["place_name"]                = this->place_name[seq_out],
            _["place_full_name"]           = this->place_full_name[seq_out],
            _["place_type"]                = this->place_type[seq_out],
            _["country"]                   = this->country[seq_out],
            _["country_code"]              = this->country_code[seq_out],
            _["bbox_coords"]               = this->bbox_coords[seq_out]
        );
        geo1.attr("class") = "data.frame";
        geo1.attr("row.names") = row_names;

        Rcpp::List geo2 = Rcpp::List::create(
            _["retweet_place_url"]         = this->retweet_place_url[seq_out],
            _["retweet_place_name"]        = this->retweet_place_name[seq_out],
            _["retweet_place_full_name"]   = this->retweet_place_full_name[seq_out],
            _["retweet_place_type"]        = this->retweet_place_type[seq_out],
            _["retweet_country"]           = this->retweet_country[seq_out],
            _["retweet_country_code"]      = this->retweet_country_code[seq_out],
            _["retweet_bbox_coords"]       = this->retweet_bbox_coords[seq_out],
            _["quoted_place_url"]          = this->quoted_place_url[seq_out],
            _["quoted_place_name"]         = this->quoted_place_name[seq_out],
            _["quoted_place_full_name"]    = this->quoted_place_full_name[seq_out],
            _["quoted_place_type"]         = this->quoted_place_type[seq_out],
            _["quoted_country"]            = this->quoted_country[seq_out],
            _["quoted_country_code"]       = this->quoted_country_code[seq_out],
            _["quoted_bbox_coords"]        = this->quoted_bbox_coords[seq_out]
        );
        geo2.attr("class") = "data.frame";
        geo2.attr("row.names") = row_names;

        Rcpp::List other = Rcpp::List::create(
            _["name"]                      = this->name[seq_out],
            _["location"]                  = this->location[seq_out],
            _["description"]               = this->description[seq_out],
            _["url"]                       = this->url[seq_out],
            _["protected"]                 = this->protected_[seq_out],
            _["followers_count"]           = this->followers_count[seq_out],
            _["friends_count"]             = this->friends_count[seq_out],
            _["listed_count"]              = this->listed_count[seq_out],
            _["statuses_count"]            = this->statuses_count[seq_out],
            _["favourites_count"]          = this->favourites_count[seq_out],
            _["account_created_at"]        = this->account_created_at[seq_out],
            _["verified"]                  = this->verified[seq_out],
            _["account_lang"]              = this->account_lang[seq_out],
            _["profile_banner_url"]        = this->profile_banner_url[seq_out],
            _["profile_image_url"]         = this->profile_image_url[seq_out],
            _["timestamp_ms"]              = this->timestamp_ms[seq_out],
            _["contributors_enabled"]      = this->contributors_enabled[seq_out]
        );
        other.attr("class") = "data.frame";
        other.attr("row.names") = row_names;


        return Rcpp::List::create(
            _["main"] = main,
            _["entities"] = entities,
            _["meta"] = meta,
            _["quoted"] = quoted,
            _["retweet"] = retweet,
            _["geo1"] = geo1,
            _["geo2"] = geo2,
            _["other"] = other
        );
    };

};


class TraptorMeta {
    // Rcpp::List images_results;
    // Rcpp::List links_results;
    
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
    TraptorMeta() {};

    TraptorMeta(const int n_vals) {
        
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


    void push(const rapidjson::Value& x, const int i) {
        const rapidjson::Value& meta = x["meta"];
        if (meta.Size() == 0) {
            return;
        }

        // this->images_results[i]                  = get_meta_results(meta, "images");
        // this->links_results[i]                   = get_meta_results(meta, "links");
        
        this->rule_type[i]                       = get_nested_meta_results(meta, "rule_matcher", "rule_type");
        this->rule_tag[i]                        = get_nested_meta_results(meta, "rule_matcher", "rule_tag");
        this->description[i]                     = get_nested_meta_results(meta, "rule_matcher", "description");

        this->value[i]                           = get_nested_meta_results(meta, "rule_matcher", "value");

        this->appid[i]                           = get_nested_meta_results(meta, "rule_matcher", "appid");
        this->campaign_id[i]                     = get_nested_meta_results(meta, "rule_matcher", "campaign_id");
        this->campaign_title[i]                  = get_nested_meta_results(meta, "rule_matcher", "campaign_title", true);
        this->project_id[i]                      = get_nested_meta_results(meta, "rule_matcher", "project_id");
        this->project_title[i]                   = get_nested_meta_results(meta, "rule_matcher", "project_title", true);

        this->complex_value[i]                   = get_nested_meta_results(meta, "rule_matcher", "complex_value", true);
        
        
    }


     Rcpp::List to_r(const int max_length) {
        using Rcpp::_;

        vec_int seq_out(max_length);
        vec_chr row_names(max_length);
        for (int i = 0; i < max_length; ++i) {
            seq_out[i] = i;
            row_names[i] = Rcpp::String(i + 1);
        }
        
        // Rcpp::List links = Rcpp::List::create(
        //     _["links_results"]              = this->links_results[seq_out],
        //     _["images_results"]             = this->images_results[seq_out]
        // );

        Rcpp::List out(max_length);
        for (int i = 0; i < max_length; ++i) {
            Rcpp::List out_row = Rcpp::List::create(
                // _["ist_links_results"]             = this->links_results[i],
                // _["ist_images_results"]            = this->images_results[i],

                _["ist_rule_type"]                 = this->rule_type[i],
                _["ist_rule_tag"]                  = this->rule_tag[i],
                _["ist_rule_value"]                = this->value[i],
                _["ist_description"]               = this->description[i],
                
                _["ist_appid"]                     = this->appid[i],
                _["ist_campaign_id"]               = this->campaign_id[i],
                _["ist_campaign_title"]            = this->campaign_title[i],
                _["ist_project_id"]                = this->project_id[i],
                _["ist_project_title"]             = this->project_title[i],

                _["ist_complex_value"]             = this->complex_value[i]
            );

            vec_chr temp(this->rule_type[i]);

            out_row.attr("class")     = "data.frame";
            out_row.attr("row.names") = Rcpp::seq_len( temp.length() );

            out[i] = out_row;
        }

        return out;
     };
};


} // knapply
