status_col_names <- function(tweet_df) {
  col_templates <- c(
    "status_id",
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
    reply_to = paste0("reply_to", col_templates),
    quoted = paste0("quoted_", col_templates)
  )
  
  out <- lapply(with_context, function(.x) {
    intersect(.x, names(tweet_df))
  })
  
  Filter(function(.x) length(.x) > 1L, out)
}

#' @importFrom data.table data.table is.data.table setcolorder setDT setnames
build_status_df <- function(tweet_df, unique_statuses = TRUE, split = FALSE, ...) {
  # silence R CMD Check NOTE
  # ..x <- NULL
  # .SD <- NULL
  # status_id <- NULL
  # created_at <- NULL
  # timestamp_ms <- NULL
  ##########################
  
  if (!is.data.table(tweet_df)) {
    tweet_df <- data.table(tweet_df)
  }
  
  split_statuses <- lapply(
    status_col_names(tweet_df),  
    function(x) standardize_cols(tweet_df[, ..x]
                                 )[!is.na(status_id)]
  )
  
  out <- rbindlist(split_statuses, use.names = TRUE, fill = TRUE)
  
  col_order <- c("status_id", setdiff(names(out), "status_id"))
  setcolorder(out, col_order)
  setnames(out, old = "created_at", new = "timestamp_ms")
  
  if (split) {
    return(split(out, by = "status_id"))
  }
  
  if (!unique_statuses) {
    return(out)
  }
  
  out[
    order(-timestamp_ms),
    lapply(.SD, function(x) {
      if (.N == 1L) x
      else if (is.atomic(x)) .subset2(x, which.min(is.na(x)))                                           
      else .subset(x, which.min( vapply(.subset2(x, 1L), length, integer(1L) ) == 0L))
    }),
    by = status_id,
    ][, timestamp_ms := as.POSIXct(timestamp_ms, origin = "1970-01-01")
      ]
  
  out[]
}
