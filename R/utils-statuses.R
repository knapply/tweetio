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


status_col_names <- function(tweet_df) {
  col_templates <- c(
    "status_id",
    "status_url",
    "created_at",
    "text",
    "source",
    "is_quote",
    "is_retweeted",
    "media_url",
    "media_type",
    "place_url",
    "place_name",
    "place_full_name",
    "place_type",
    "country",
    "country_code",
    "bbox_coords",
    "ist_metadata"
  )
  
  with_context <- list(
    main = col_templates,
    retweet = paste0("retweet_", col_templates),
    reply_to = paste0("reply_to_", col_templates),
    quoted = paste0("quoted_", col_templates)
  )
  
  out <- lapply(with_context, function(.x) {
    intersect(.x, names(tweet_df))
  })
  
  Filter(function(.x) length(.x) >= 1L, out)
}


#' Extract All Statuses
#' 
#' Build a data frame of statuses where each is summarized in a single row. The values of
#' each column hold the most recent non-`NA`/non-empty value.
#' 
#' @template param-tweet_df
#' @template param-as_tibble
#' @template param-dots
#' 
#' @template author-bk
#' 
#' @examples 
#' path_to_tweet_file <- example_tweet_file()
#' tweet_df <- read_tweets(path_to_tweet_file)
#'
#' extract_statuses(tweet_df, as_tibble = TRUE) 
#' 
#' @importFrom data.table as.data.table setcolorder setDT setnames
#' 
#' @export
extract_statuses <- function(tweet_df, as_tibble = FALSE, ...) {
  # silence R CMD Check NOTE =============================================================
  ..x <- NULL
  .SD <- NULL
  status_id <- NULL
  created_at <- NULL
  timestamp_ms <- NULL
  .N <- NULL
  status_type <- NULL
  # ======================================================================================
  
  if (!.is_dt(tweet_df)) {
    tweet_df <- as.data.table(tweet_df)
  }
  
  split_statuses <- .imap(
    status_col_names(tweet_df),  
    function(.x, .y) {
      standardize_cols(tweet_df[, .x, with = FALSE]
                       )[!is.na(status_id)
                         ][, status_type := .y
                           ]
    }
  )
  
  out <- rbindlist(split_statuses, use.names = TRUE, fill = TRUE)
  
  
  # if (drop_empty_cols) {
  #   empty_col_test <- .map_lgl(out, function(.x) {
  #     if (is.list(.x)) all(.map_lgl(.x, .is_empty)) else all(is.na(.x))
  #   })
  #   
  #   empty_cols <- names(out)[empty_col_test]
  #   if (!.is_empty(empty_cols)) {
  #     out <- out[, !..empty_cols]
  #   }
  # }
  
  # if (split) {
  #   out <- split(out, by = "status_id")
  #   if (!as_tibble || !requireNamespace("tibble", quietly = TRUE)) {
  #     return(out)
  #   }
  #   return(lapply(out, tibble::as_tibble))
  # }
  
  sd_cols <- setdiff(names(out), "status_id")
  out <- out[
    order(-created_at),
    lapply(.SD, function(x) {
      if (.N == 1L) x
      else if (is.atomic(x)) .subset2(x, which.min(is.na(x)))                                           
      else .subset(x, which.min( vapply(.subset2(x, 1L), length, integer(1L) ) == 0L))
    }),
    by = status_id, .SDcols = sd_cols
    ][, created_at := as.POSIXct(created_at, origin = "1970-01-01")
      ]
  
  .finalize_df(out, as_tibble = as_tibble)
}
