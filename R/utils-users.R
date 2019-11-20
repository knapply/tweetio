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
    reply_to = paste0("reply_to", col_templates),
    quoted = paste0("quoted_", col_templates),
    mentions = paste0("mentions_", col_templates)
  )
  
  out <- lapply(with_context, function(.x) {
    c("created_at", intersect(.x, names(tweet_df)))
  })
  
  Filter(function(.x) length(.x) > 1L, out)
}


#' @importFrom data.table data.table is.data.table setcolorder setDT setnames
build_user_df <- function(tweet_df, unique_users = TRUE, split = FALSE, ...) {
  # silence R CMD Check NOTE
  ..col <- NULL
  .SD <- NULL
  user_id <- NULL
  created_at <- NULL
  timestamp_ms <- NULL
  .N <- NULL
  #########################
  
  if (!is.data.table(tweet_df)) {
    tweet_df <- data.table(tweet_df)
  }
  split_users <- lapply(user_col_names(tweet_df), 
                        function(.x) standardize_cols(tweet_df[, .x, with = FALSE])
  )
  split_users[c("main", "retweet", "quoted")] <- lapply(
    split_users[c("main", "retweet", "quoted")], function(.x) {
      .x[!is.na(user_id)]
    })
  
  split_users$mentions <- setDT(
    unnest_entities2_impl(
      tracker = split_users$mentions$created_at,
      source = split_users$mentions$user_id,
      target = split_users$mentions$screen_name,
      col_names = c("user_id", "screen_name", "created_at")
    )
  )
  
  out <- rbindlist(split_users, use.names = TRUE, fill = TRUE)
  
  col_order <- c("user_id", setdiff(names(out), "user_id"))
  setcolorder(out, col_order)
  setnames(out, old = "created_at", new = "timestamp_ms")
  
  if (unique_users && !split) {
    out <- out[
      order(-timestamp_ms),
      lapply(.SD, function(x) {
        if (.N == 1L) x
        else if (is.atomic(x)) .subset2(x, which.min(is.na(x)))                                           
        else .subset(x, which.min( vapply(.subset2(x, 1L), length, integer(1L)) == 0L))
      }),
      keyby = user_id
    ][, timestamp_ms := .as_posixct(timestamp_ms)
      ][order(timestamp_ms)]
  }
  
  if (split) {
    out <- split(out, by = "user_id")
  }
  
  out[]
}
