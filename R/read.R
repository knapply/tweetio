#' @template author-bk
#' 
#' @importFrom data.table := setDT
#' @importFrom utils unzip
.read_tweets <- function(file_path, ...) {
  # silence R CMD Check NOTE =============================================================
  ist_metadata <- NULL
  # ======================================================================================
  
  stopifnot(is.character(file_path) && length(file_path) == 1L)
  stopifnot(file.exists(file_path))

  if (grepl("\\.csv$", file_path, ignore.case = TRUE)) {
    stop("Tweets in CSV files are not yet supported.",
         call. = FALSE)
  }
  
  if (grepl("\\.zip$", file_path)) {
    temp_dir <- tempdir(check = TRUE)
    target_dir <- paste0(temp_dir, "/tweetio")
    dir.create(target_dir)
    on.exit(unlink(target_dir, force = TRUE))

    unzip(zipfile = file_path, exdir = target_dir)
    unzipped <- dir(target_dir, full.names = TRUE)
    if (length(unzipped) == 0L) {
      stop("`file_path` is a ZIP archive, but it's empty.")
    }
    if (length(unzipped) > 1L) {
      stop("`file_path` is a ZIP archive with multiple files. Only ZIP archives
           with one file are supported.")
    }

    file_path <- unzipped
  }
  
  file_path <- path.expand(file_path)
  
  init <- read_tweets_impl(file_path)
  
  if (is.null(init$metadata)) {
    return( setDT(init)[] )
  }
  
  setDT(init$tweets
        )[, ist_metadata := init[["metadata"]]
          ][]
}


#' Read tweets into a data frame
#' 
#' @param file_path Path(s) to tweet files.
#' @param ... Arguments passed to or from other methods.
#' 
#' @return `data.table`
#' 
#' @template author-bk
#' 
#' @export
read_tweets <- function(file_path, ...) {
  out <- .read_tweets(file_path, ...)

  .finalize_cols(out)[]
}



#' @rdname read_tweets
#' 
#' @param in_parallel Default: `TRUE`. Whether to use `future.apply::future_lapply()`
#'  to process the files in parallel. Ignored if `{future}` or `{future.apply}` are not installed.
#' @param .strategy Default: `NULL`. argument passed to `future::plan()`'s `strategy` parameter.
#'   If `NULL`, `future::multiprocess` is used. Ignored if `{future}` or `{future.apply}` are not installed.
#' 
#' @importFrom data.table rbindlist
#' @export
read_tweets_bulk <- function(file_path, in_parallel = TRUE, .strategy = NULL, ...) {
  if (length(file_path) == 1L) {
    return(read_tweets(file_path))
  }
  
  use_future <- in_parallel &&
                  requireNamespace("future", quietly = TRUE) &&
                  requireNamespace("future.apply", quietly = TRUE)
  
  if (use_future) {
    .strategy <- if (is.null(.strategy)) future::multiprocess else .strategy
    future::plan(strategy = .strategy, ...)

    init <- future.apply::future_lapply(file_path, .read_tweets)
  } else {
    init <- lapply(file_path, .read_tweets)
  }
  
  out <- rbindlist(init)
  
  .finalize_cols(out)[]
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
    "verified", "profile_url", "profile_expanded_url", "account_lang", 
    "profile_banner_url", "profile_background_url", "profile_image_url"
  )

  rtweet_cols <- intersect(rtweet_order, names(proto_tweet_df))
  
  non_rtweet_cols <- setdiff(names(proto_tweet_df), rtweet_order)
  
  new_col_order <- c(rtweet_cols, non_rtweet_cols)
  setcolorder(proto_tweet_df, new_col_order)
  proto_tweet_df
}


.finalize_cols <- function(proto_tweet_df, ...) {
  # silence R CMD Check NOTE =============================================================
  .SD <- NULL
  bbox_coords <- NULL
  is_retweet <- NULL
  retweet_status_id <- NULL
  # ======================================================================================
  
  chr_cols <- names(proto_tweet_df
                    )[vapply(proto_tweet_df, is.character, FUN.VALUE = logical(1L))]
  
  proto_tweet_df[,
    (chr_cols) := lapply(.SD, function(.x) {
      .x[.x == ""] <- NA_character_
      .x
    }), 
    .SDcols = chr_cols
  ]
  
  # convert date-times to POSIXct
  possible_dttm_cols <- c("created_at", "account_created_at",
                          "retweet_created_at", "quoted_created_at",
                          "timestamp", "timestamp_ms",
                          "traptor_timestamp", "traptor_system_timestamp",
                          "traptor_rule_date_added")
  dttm_cols <- intersect(names(proto_tweet_df), possible_dttm_cols)
  if (length(dttm_cols)) {
    proto_tweet_df[, (dttm_cols) := lapply(.SD, format_dttm),
                   .SDcols = dttm_cols]
  }
  
  # add `is_retweet*` column
  proto_tweet_df[, is_retweet := !is.na(retweet_status_id)]
  
  # add `status_url` column
  proto_tweet_df[
    , status_url := paste0("https://twitter.com/", screen_name, "/status/", status_id)
  ]
  
  .set_col_order(proto_tweet_df)[]
}




