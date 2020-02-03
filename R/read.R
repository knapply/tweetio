# // Copyright (C) 2019 Brendan Knapp
# // This file is part of tweetio.
# // 
# // This program is free software: you can redistribute it and/or modify
# // it under the terms of the GNU General Public License as published by
# // the Free Software Foundation, either version 3 of the License, or
# // (at your option) any later version.
# // 
# // This program is distributed in the hope that it will be useful,
# // but WITHOUT ANY WARRANTY; without even the implied warranty of
# // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# // GNU General Public License for more details.
# // 
# // You should have received a copy of the GNU General Public License
# // along with this program.  If not, see <https://www.gnu.org/licenses/>.



#' @template author-bk
#' 
#' @importFrom data.table := setDT
.read_tweets <- function(file_path, verbose, ...) {
  # silence R CMD Check NOTE =============================================================
  metadata <- NULL
  # ======================================================================================
  
  stopifnot(is.character(file_path) && length(file_path) == 1L)
  stopifnot(file.exists(file_path))

  if (grepl("\\.csv$", file_path, ignore.case = TRUE)) {
    stop("Tweets in CSV files are not yet supported.",
         call. = FALSE)
  }
  
  if (grepl("\\.zip$", file_path, ignore.case = TRUE)) {
    if (!requireNamespace("utils", quietly = TRUE)) {
      stop("`file_path` points to a .zip file. The {utils} package is required in order to
           unzip it.", call. = FALSE)
    } 

    temp_dir <- tempdir()
    target_dir <- paste0(temp_dir, "/tweetio")
    dir.create(target_dir)
    on.exit(unlink(target_dir, recursive = TRUE, force = TRUE))

    utils::unzip(zipfile = file_path, exdir = target_dir)
    unzipped <- dir(target_dir, full.names = TRUE)
    if (.is_empty(unzipped)) {
      stop("`file_path` is a ZIP archive, but it's empty.")
    }
    if (length(unzipped) > 1L) {
      stop("`file_path` is a ZIP archive with multiple files. Only ZIP archives
           with one file are supported.")
    }

    file_path <- unzipped
  }
  
  file_path <- path.expand(file_path)
  
  init <- read_tweets_impl(file_path, verbose)

  if (attr(init, "has_metadata", exact = TRUE)) {
    setDT(init$tweets
          )[, metadata := init[["metadata"]]
            ][]
  } else {
    setDT(init)[]
  }
}


#' Read Tweets into a Data Frame
#' 
#' Go from a file of raw tweet data to a convenient, `{rtweet}`-style data frame.
#' 
#' @param file_path Path(s) to tweet files.
#' @template param-verbose
#' @template param-dots
#' 
#' @template return-df
#' 
#' @template author-bk
#' 
#' @examples
#' path_to_tweet_file <- example_tweet_file()
#' 
#' tweet_data.table <- read_tweets(file_path = path_to_tweet_file)
#' 
#' tweet_tibble <- read_tweets(file_path = path_to_tweet_file, as_tibble = TRUE)
#' 
#' tweet_tibble
#' 
#' @export
read_tweets <- function(file_path, 
                        as_tibble = tweetio_as_tibble(),
                        verbose = tweetio_verbose(),
                        ...) {
  out <- .read_tweets(file_path, verbose, ...)

  out <- .finalize_cols(out)

  .finalize_df(out, as_tibble = as_tibble)
}



#' @rdname read_tweets
#' 
#' @param in_parallel Default: `TRUE`. Whether to use `future.apply::future_lapply()`
#'  to process the files in parallel. Ignored if `{future}` or `{future.apply}` are not installed.
#' @param strategy Default: `NULL`. argument passed to `future::plan()`'s `strategy` parameter.
#'   If `NULL`, `future::multiprocess` is used. Ignored if `{future}` or `{future.apply}` are not installed.
#' @template param-as_tibble
#' 
#' @importFrom data.table rbindlist
#' @export
read_tweets_bulk <- function(file_path, 
                             as_tibble = tweetio_as_tibble(),
                             verbose = tweetio_verbose(), 
                             in_parallel = TRUE, strategy = NULL, ...) {
  if (length(file_path) == 1L) {
    return(read_tweets(file_path))
  }
  
  use_future <- in_parallel &&
                  requireNamespace("future", quietly = TRUE) &&
                  requireNamespace("future.apply", quietly = TRUE)
  
  if (use_future) {
    .strategy <- if (is.null(strategy)) future::multiprocess else strategy
    future::plan(strategy = .strategy, ...)

    init <- future.apply::future_lapply(file_path, .read_tweets, verbose = verbose)
  } else {
    init <- lapply(file_path, .read_tweets, verbose = verbose)
  }
  
  out <- rbindlist(init, use.names = TRUE, fill = TRUE)
  
  out <- .finalize_cols(out)
  
  .finalize_df(out, as_tibble = as_tibble)
}


#' @importFrom data.table setcolorder
.set_col_order <- function(proto_tweet_df) {
  rtweet_order <- c(
    "user_id", "status_id", "created_at", "screen_name", "text", 
    "source", "display_text_width", "reply_to_status_id", "reply_to_user_id", 
    "reply_to_screen_name", "is_quote", "is_retweet", "favorite_count", 
    "retweet_count", "quote_count", "reply_count", "hashtags", "symbols", 
    "urls_url", "urls_t.co", "urls_expanded_url", "media_url", "media_t.co", 
    "media_expanded_url", "media_type", "ext_media_url", "ext_media_t.co", 
    "ext_media_expanded_url", "ext_media_type", "mentions_user_id", 
    "mentions_screen_name", "lang", "quoted_status_id", "quoted_text", 
    "quoted_created_at", "quoted_source", "quoted_favorite_count", 
    "quoted_retweet_count", "quoted_user_id", "quoted_screen_name", 
    "quoted_name", "quoted_followers_count", "quoted_friends_count", 
    "quoted_statuses_count", "quoted_location", "quoted_description", 
    "quoted_verified", "retweet_status_id", "retweet_text", "retweet_created_at", 
    "retweet_source", "retweet_favorite_count", "retweet_retweet_count", 
    "retweet_user_id", "retweet_screen_name", "retweet_name", "retweet_followers_count", 
    "retweet_friends_count", "retweet_statuses_count", "retweet_location", 
    "retweet_description", "retweet_verified", "place_url", "place_name", 
    "place_full_name", "place_type", "country", "country_code", "geo_coords", 
    "coords_coords", "bbox_coords", "status_url", "name", "location", 
    "description", "url", "protected", "followers_count", "friends_count", 
    "listed_count", "statuses_count", "favourites_count", "account_created_at", 
    "verified",
    "profile_url", "profile_url2", # profile_url2 not in rtweet, but makes more sense here
    "profile_expanded_url", "account_lang", 
    "profile_banner_url", "profile_background_url", "profile_image_url"
  )

  rtweet_cols <- intersect(rtweet_order, names(proto_tweet_df))
  
  non_rtweet_cols <- setdiff(names(proto_tweet_df), rtweet_order)
  
  new_col_order <- c(rtweet_cols, non_rtweet_cols)
  setcolorder(proto_tweet_df, new_col_order)
  proto_tweet_df
}


#' @importFrom data.table .SD
#' @importFrom stringi stri_extract_first_regex stri_replace_all_regex
.finalize_cols <- function(proto_tweet_df, clean_source_cols = TRUE, ...) {
  # silence R CMD Check NOTE =============================================================
  bbox_coords <- NULL
  is_retweet <- NULL
  retweet_status_id <- NULL
  status_url <- NULL
  profile_url <- NULL
  profile_url2 <- NULL
  screen_name <- NULL
  status_id <- NULL
  user_id <- NULL
  urls_expanded_url <- NULL
  # ======================================================================================
  
  # convert date-times to POSIXct
  possible_dttm_cols <- c("created_at", "account_created_at",
                          "retweet_created_at", "quoted_created_at")
  dttm_cols <- intersect(names(proto_tweet_df), possible_dttm_cols)
  if (length(dttm_cols)) {
    proto_tweet_df[, (dttm_cols) := lapply(.SD, format_dttm),
                   .SDcols = dttm_cols]
  }
  
  # there are some occasional control characters that end up in the strings.
  # AFAIK, they are always `\0`, which aren't allowed in XML files.
  # To be on the safe side, all control characters are stripped here.
  possible_control_char_cols <- c(
    "text", "quoted_text", "quoted_source", "quoted_name", "quoted_location",
    "quoted_description", "retweet_text", "retweet_source", "retweet_location",
    "retweet_description", "name", "location", "description"
  )
  col_with_control_chars <- intersect(names(proto_tweet_df),
                                      possible_control_char_cols)
  if (!.is_empty(col_with_control_chars)) {
    proto_tweet_df <- proto_tweet_df[
      , (col_with_control_chars) := lapply(.SD, stri_replace_all_regex,
                                           "[[:cntrl:]]", ""),
      .SDcols = col_with_control_chars
      ]
  }
  
  if ("retweet_status_id" %chin% names(proto_tweet_df)) {
    proto_tweet_df[, is_retweet := !is.na(retweet_status_id)]
  }
  
  if ("user_id" %chin% names(proto_tweet_df)) {
    proto_tweet_df[, profile_url := paste0("https://twitter.com/i/user/", user_id)]
  }
  
  # add status URL columns
  status_url_cols <- c(status_id = "status_url",
                       retweet_status_id = "retweet_status_url",
                       quoted_status_id = "quoted_tweet_url", 
                       reply_to_status_id = "reply_to_status_url") 
  status_url_cols <- status_url_cols[names(status_url_cols) %chin% names(proto_tweet_df)]
  if (!.is_empty(status_url_cols)) {
    proto_tweet_df <- proto_tweet_df[, (status_url_cols) := lapply(
      .SD, function(.x) paste0("https://twitter.com/i/web/status/", .x)
      ),
      .SDcols = names(status_url_cols)
    ]
  }
  
  # first urls_expanded_url may be the status_url... drop it if so
  if (all(c("urls_expanded_url", "status_url") %chin% names(proto_tweet_df))) {
    proto_tweet_df[, urls_expanded_url := .map2(
      urls_expanded_url, status_url, 
      function(.x, .y) {
        if (!is.na(.x[[1L]]) && .x[[1L]] == .y) .x[-1L]
        else .x
      })
    ]
  }

  # follow {rtweet}'s behavior and strip HTML from `*_source`s
  if (clean_source_cols) {
    source_cols <- intersect(
      names(proto_tweet_df),
      c("source", "retweet_source", "quoted_source")
    )
    if (!.is_empty(source_cols)) {
      proto_tweet_df[
        , (source_cols) := lapply(.SD, stri_extract_first_regex,
                                  '(?<=">).*?(?=</a>$)'),
        .SDcols = source_cols
      ]
    }
  }
  
  .set_col_order(proto_tweet_df)[]
}

