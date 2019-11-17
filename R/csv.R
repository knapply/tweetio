list_col_names <- function(x) {
  potential_list_cols <- c(
    "hashtags", "urls_expanded_url", "media_url", "media_expanded_url",
    "media_type", "mentions_user_id", "mentions_screen_name", "bbox_coords",
    "retweet_bbox_coords", "quoted_bbox_coords", "metadata"
  )
  intersect(names(x), potential_list_cols)
}

#' @importFrom stringi stri_split_fixed
peak_csv_col_classes <- function(file_path) {
  col_classes <- c(
    user_id = "character", status_id = "character", screen_name = "character",
    text = "character", source = "character", reply_to_status_id = "character",
    reply_to_user_id = "character", reply_to_screen_name = "character",
    is_quote = "logical", is_retweet = "logical", hashtags = "character",
    urls_expanded_url = "character", media_url = "character",
    media_expanded_url = "character",
    media_type = "character", mentions_user_id = "character",
    mentions_screen_name = "character",
    quoted_status_id = "character", quoted_text = "character", quoted_source = "character",
    quoted_favorite_count = "integer", quoted_retweet_count = "integer",
    quoted_user_id = "character", quoted_screen_name = "character",
    quoted_name = "character", quoted_followers_count = "integer",
    quoted_friends_count = "integer", quoted_statuses_count = "integer",
    quoted_location = "character", quoted_description = "character",
    quoted_verified = "logical", retweet_status_id = "character",
    retweet_text = "character", retweet_source = "character",
    retweet_favorite_count = "integer",
    retweet_retweet_count = "integer", retweet_user_id = "character",
    retweet_screen_name = "character", retweet_name = "character",
    retweet_followers_count = "integer", retweet_friends_count = "integer",
    retweet_statuses_count = "integer", retweet_location = "character",
    retweet_description = "character", retweet_verified = "logical",
    place_url = "character", place_name = "character", place_full_name = "character",
    place_type = "character", country = "character", country_code = "character",
    bbox_coords = "character", status_url = "character", name = "character",
    location = "character", description = "character", url = "character",
    protected = "logical", followers_count = "integer", friends_count = "integer",
    listed_count = "integer", statuses_count = "integer", favourites_count = "integer",
    verified = "logical", profile_url = "character", account_lang = "character",
    profile_banner_url = "character", profile_image_url = "character",
    is_retweeted = "logical", retweet_place_url = "character",
    retweet_place_name = "character",
    retweet_place_full_name = "character", retweet_place_type = "character",
    retweet_country = "character", retweet_country_code = "character",
    retweet_bbox_coords = "character", quoted_place_url = "character",
    quoted_place_name = "character", quoted_place_full_name = "character",
    quoted_place_type = "character", quoted_country = "character",
    quoted_country_code = "character", quoted_bbox_coords = "character",
    contributors_enabled = "logical", metadata = "character", profile_url2 = "character"
  )
  
  header_peak <- stri_split_fixed(readLines(file_path, n = 1), ",")[[1L]]
  col_classes[names(col_classes) %in% intersect(header_peak, names(col_classes))]
}

#' @importFrom data.table copy
#' @importFrom jsonify to_json
jsonify_list_cols <- function(tweet_df) {
  out <- copy(tweet_df)

  list_cols <- names(out)[.map_lgl(out, is.list)]

  out[, (list_cols) := lapply(.SD, .map_chr, to_json),
      .SDcols = list_cols
      ]
}

#' @importFrom data.table fwrite
#' 
# @export
write_tweet_csv <- function(tweet_df, file_path) {
  fwrite(jsonify_list_cols(tweet_df), file_path)
}


#' @importFrom data.table fread
#' @importFrom jsonify from_json
#' @importFrom stringi stri_detect_regex stri_replace_all_fixed
read_tweet_csv <- function(file_path) {
  col_classes <- peak_csv_col_classes(file_path)
  # TODO: note exactly which col_classes are totally ignored...
  out <- fread(file_path, colClasses = col_classes,
               na.strings = "", encoding = "UTF-8",
               strip.white = FALSE)

  lgl_cols <- names(col_classes)[col_classes == "logical"]
  if (length(lgl_cols) > 0L) {
    out <- out[, (lgl_cols) := lapply(.SD, as.logical),
               .SDcols = lgl_cols]
  }

  int_cols <- names(col_classes)[col_classes == "integer"]
  if (length(int_cols) > 0L) {
    out <- out[, (int_cols) := lapply(.SD, as.integer),
               .SDcols = int_cols]
  }


  dttm_cols <- intersect(
    names(out),
    c("created_at", "quoted_created_at", "retweet_created_at",
      "account_created_at", "timestamp_ms")
  )
  if (length(dttm_cols) > 0L) {
    out <- out[, (dttm_cols) := lapply(.SD, as.POSIXct,
                                       format = "%Y-%m-%dT%H:%M:%S", tz = "UTC"),
               .SDcols = dttm_cols]
  }
  
  chr_cols <- names(out)[.map_lgl(out, is.character)]
  out <- out[, (chr_cols) := lapply(.SD, stri_replace_all_fixed, '""', '"'),
             .SDcols = chr_cols]

  list_cols <- list_col_names(out)

  if (length(list_cols) > 0L) {
    out <- out[
      , (list_cols) := lapply(.SD, lapply, from_json),
      .SDcols = list_cols
    ][]
  }
  
  chr_list_cols <- intersect(
    names(out),
    c("hashtags", "urls_expanded_url", "media_url", "media_expanded_url", 
      "media_type", "mentions_user_id", "mentions_screen_name")
  )
  if (length(chr_list_cols) > 0L) {
    out <- out[
      , (chr_list_cols) := lapply(.SD, lapply, as.character),
      .SDcols = chr_list_cols
    ][]
  }
  
  
  dbl_list_cols <- intersect(
    names(out),
    c("bbox_coords", "retweet_bbox_coords", "quoted_bbox_coords")
  )
  if (length(dbl_list_cols) > 0L) {
    out <- out[
      , (dbl_list_cols) := lapply(.SD, lapply, as.double),
      .SDcols = dbl_list_cols
    ][]
  }
  
  if ("metadata" %in% names(out)) {
    out <- out[, metadata := lapply(metadata, lapply, as.character)]
  }
  
  out[]
}


# 
# 
# file_path <-  "~/test-csv.csv"
# 
# write_tweet_csv(res_pulse_zip, file_path)
# test_read <- read_tweet_csv(file_path)
# 
# 
# all.equal(test_read, res_pulse_zip,
#           check.attributes = FALSE)
#> [1] TRUE
