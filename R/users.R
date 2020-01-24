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

user_col_names <- function(tweet_df) {
  col_templates <- c(
    "user_id",
    "name",
    "screen_name",
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
    "profile_url",
    "profile_expanded_url",
    "account_lang",
    "profile_banner_url",
    "profile_background_url",
    "profile_image_url",
    "bbox_coords"
  )
  
  with_context <- list(
    main = col_templates,
    retweet = paste0("retweet_", col_templates),
    reply_to = paste0("reply_to_", col_templates),
    quoted = paste0("quoted_", col_templates),
    mentions = paste0("mentions_", col_templates)
  )
  
  out <- lapply(with_context, function(.x) {
    c("created_at", intersect(.x, names(tweet_df)))
  })
  
  .keep(out, function(.x) length(.x) > 1L)
}




#' Extract All Users
#' 
#' Extract all users and relevant data, including retweeters, quoters, repliers, and mentions.
#' 
#' @template param-tweet_df
#' @param summarize `logical(1L)`, Default: `TRUE`. Whether to aggregate all users data to
#' a single row containing the most recent non-missing values.
#' @param split `logical(1L)`, Default: `FALSE`. Whether to split users into separate data
#' frames and return a list of those data frames, retaining all instances where each user
#' was observed. Ignored if `summarize` is `TRUE`.
#' @template param-as_tibble
#' @template param-dots
#' 
#' @template author-bk
#' 
#' @examples 
#' path_to_tweet_file <- example_tweet_file()
#' tweet_df <- read_tweets(path_to_tweet_file)
#'
#' extract_users(tweet_df, as_tibble = TRUE) 
#' 
#' extract_users(tweet_df, summarize = FALSE, as_tibble = TRUE) 
#' 
#' split_users <- extract_users(tweet_df, summarize = FALSE, split = TRUE, as_tibble = TRUE)
#' 
#' # first 3 users with more than 5 observations.
#' split_users[vapply(split_users, function(.x) nrow(.x) > 5, logical(1L))][1:3]
#' 
#' @importFrom data.table data.table is.data.table setcolorder setDT setnames
#' 
#' @export
extract_users <- function(tweet_df, summarize = TRUE, split = FALSE, 
                          as_tibble = getOption("tweetio.as_tibble", FALSE),
                          ...) {
  # silence R CMD Check NOTE =============================================================
  .N <- NULL
  .SD <- NULL
  ..col <- NULL
  user_id <- NULL
  created_at <- NULL
  timestamp_ms <- NULL
  observation_type <- NULL
  # ======================================================================================
  
  if (!.is_dt(tweet_df)) {
    tweet_df <- data.table(tweet_df)
  }
  
  split_users <- lapply(user_col_names(tweet_df), 
                        function(.x) standardize_cols(tweet_df[, .x, with = FALSE]))
  split_users <- .map_at(split_users, c("main", "retweet", "quoted", "reply_to"), 
                         function(.x) .x[!is.na(user_id)])
  
  split_users$mentions <- setDT(
    unnest_entities2_impl(
      tracker = split_users$mentions$created_at,
      source = split_users$mentions$user_id,
      target = split_users$mentions$screen_name,
      col_names = c("user_id", "screen_name", "created_at")
    )
  )
  
  if (!summarize && split) {
    split_users <- .imap(split_users, function(.x, .y) {
      .x[, observation_type := .y]
    })
  }
  
  
  out <- rbindlist(split_users, use.names = TRUE, fill = TRUE)
  
  col_order <- intersect(
    c("user_id", "observation_type", setdiff(names(out), "user_id")), 
    names(out)
  )
  setcolorder(out, col_order)
  setnames(out, old = "created_at", new = "timestamp_ms")
  
  if (!summarize) {
    if (split) {
      out <- split(out[order(timestamp_ms)], by = "user_id")
    
      if (as_tibble && requireNamespace("tibble", quietly = TRUE)) {
        out <- lapply(out, tibble::as_tibble)
      }
      return(out)
    }
    
    return(.finalize_df(out, as_tibble = as_tibble))
  }
  
  out <- out[
    order(-timestamp_ms),
    lapply(.SD, function(x) {
      if (.N == 1L) x
      else if (is.atomic(x)) .subset2(x, which.min(is.na(x))) # which.min() return first `FALSE` here if any not-NA                                           
      else .subset(x, which.min( vapply(.subset2(x, 1L), length, integer(1L)) == 0L))
    }),
    by = user_id
  ][, timestamp_ms := .as_posixct(timestamp_ms)
    ][order(timestamp_ms)]
  
  .finalize_df(out, as_tibble = as_tibble)
}
