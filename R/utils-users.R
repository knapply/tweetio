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
  # ..x <- NULL
  # .SD <- NULL
  # user_id <- NULL
  # created_at <- NULL
  # timestamp_ms <- NULL
  ##########################
  
  if (!is.data.table(tweet_df)) {
    tweet_df <- data.table(tweet_df)
  }
  split_users <- lapply(user_col_names(tweet_df), 
                        function(x) standardize_cols(tweet_df[, ..x])
  )
  split_users[c("main", "retweet", "quoted")] <- lapply(
    split_users[c("main", "retweet", "quoted")], function(.x) {
      .x[!is.na(user_id)]
  })

  split_users$mentions <- setDT(
    unnest_entities2_(
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
      by = user_id
    ][, timestamp_ms := as.POSIXct(timestamp_ms, origin = "1970-01-01")
      ]
  }

  if (split) {
    out <- split(out, by = "user_id")
  }
  
  out[]
}
