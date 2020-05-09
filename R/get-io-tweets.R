# # .io_download_data <- function(data_url, dest_file = tempfile(fileext = ".zip")) {
# #   if (!tweetio:::.is_scalar_chr(data_url)) {
# #     stop("`data_url` must be a scalar character.", call. = FALSE)
# #   }
# # 
# #   download.file(url = data_url, destfile = dest_file)
# # 
# #   dest_file
# # }
# # 
# # .io_unzip_data <- function(file_path, url_col) {
# #   if (!tweetio:::.is_scalar_chr(file_path)) {
# #     stop("`file_path` must be a scalar character.")
# #   }
# #   if (!file.exists(file_path)) {
# #     stop("`file_path` does not exist.")
# #   }
# # 
# #   temp_dir <- tempdir(check = TRUE)
# #   unzip(file_path, exdir = temp_dir)
# # 
# #   file_infix <- switch(
# #     url_col,
# #     tweet_info_url = "tweets",
# #     account_info_url = "users"
# #     ,
# #     stop('something went wrong')
# #   )
# # 
# #   dir(temp_dir, full.names = TRUE,
# #       pattern = sprintf("_%s_csv_hashed\\.csv$", file_infix))
# # }
# 
# 
# 
# 
# 
# 
# .io_recode_col_names <- function(df) {
#   `%chin%` <- data.table::`%chin%`
#   
#   cols_kv <- c(
#     status_id = "tweetid",
#     user_id = "userid",
#     name = "user_display_name",
#     screen_name = "user_screen_name",
#     location = "user_reported_location",
#     description = "user_profile_description",
#     url = "user_profile_url",
#     followers_count = "follower_count",
#     following_count = "following_count",
#     account_created_at = "account_creation_date",
#     account_lang = "account_language",
#     lang = "tweet_language",
#     text = "tweet_text",
#     created_at = "tweet_time",
#     source = "tweet_client_name",
#     reply_to_user_id = "in_reply_to_userid",
#     reply_to_status_id = "in_reply_to_tweetid",
#     quoted_status_id = "quoted_tweet_tweetid",
#     is_retweet = "is_retweet",
#     retweet_user_id = "retweet_userid",
#     retweet_status_id = "retweet_tweetid",
#     # latitude = "latitude",
#     # longitude = "longitude",
#     quote_count = "quote_count",
#     reply_count = "reply_count",
#     like_count = "like_count",
#     retweet_count = "retweet_count",
#     hashtags = "hashtags",
#     urls_url = "urls",
#     mentions_user_id = "user_mentions"
#     # poll_choices = "poll_choices"
#   )
#   
#   target_cols <- cols_kv[cols_kv %chin% names(df)]
#   if (length(target_cols)) {
#     df <- data.table::setnames(df, old = target_cols, new = names(target_cols))
#     out_cols <- names(target_cols)
#     df <- data.table::setcolorder(df, neworder = out_cols)
#   }
#   
#   df
# }
# 
# .io_finish_df <- function(out) { 
#   `%chin%` <- data.table::`%chin%`
#   
#   if (is.null(out)) return(NULL)
#   
#   out[, (names(out)) := lapply(.SD, function(.x) {
#     data.table::fifelse(.x %chin% c("", "[]"), NA_character_, .x)
#     })
#     ]
#   
#   col_classes <- list(
#     character = c("tweetid", "userid", "user_display_name", 
#                   "user_screen_name", "user_reported_location", "user_profile_description", 
#                   "user_profile_url", "account_language", "tweet_language", "tweet_text", 
#                   "tweet_client_name", "in_reply_to_userid", "in_reply_to_tweetid", 
#                   "quoted_tweet_tweetid", "retweet_userid", "retweet_tweetid", 
#                   "hashtags", "urls", "user_mentions"), 
#     integer = c("follower_count", "following_count", "quote_count", "reply_count",
#                 "like_count", "retweet_count"), 
#     logical = "is_retweet", 
#     POSIXct = c("account_creation_date", "tweet_time"),
#     list = c("hashtags", "user_mentions", "urls")
#   )
#   
#   out[, (col_classes$integer) := lapply(.SD, as.integer),
#       .SDcols = col_classes$integer]
#   
#   out[, (col_classes$logical) := lapply(.SD, as.logical),
#       .SDcols = col_classes$logical]
#   
#   out[, (col_classes$POSIXct) := lapply(.SD, as.POSIXct, tz = "UTC"),
#       .SDcols = col_classes$POSIXct]
#   
#   out[, (col_classes$list) := lapply(.SD, function(.x) {
#       init <- stringi::stri_replace_all_regex(
#         .x, pattern = "^\\[|\\]$|'|\"", replacement = ""
#         )
#       out <- stringi::stri_split_regex(init, pattern = "\\s?,\\s?")
#       lapply(out, function(.y) unique(.y[.y != "0"]))
#     }),
#     .SDcols = col_classes$list]
#   
#   .io_recode_col_names(out)
#   
#   hash_cols <- c("name", "screen_name")
#   out[, (hash_cols) := lapply(.SD, function(.x) {
#     data.table::fifelse(user_id == name, NA_character_, .x)
#     }), .SDcols = hash_cols]
#   
#   out[]
# }
# 
# 
# .io_get_data <- function(urls) {
#   temp_dir <- tempdir(check = TRUE)
#   dest_dir <- paste0(temp_dir, "/TWEETIO-DATA") 
#   dir.create(dest_dir)
# 
#   for (i in seq_along(urls)) {
#     download.file(
#       urls[[i]], 
#       destfile = paste0(dest_dir, "/", basename(urls[[i]]))
#     )
#   }
#   
#   zip_files <- dir(dest_dir, pattern = "\\.zip$", full.names = TRUE)
#   for (i in seq_along(zip_files)) {
#     unzip(zip_files[[i]], exdir = dest_dir)
#   }
#   
#   csv_files <- dir(dest_dir, pattern = "\\.csv$", full.names = TRUE)
#   names(csv_files) <- sub("\\.csv$", "", basename(csv_files))
#   init <- data.table::rbindlist(
#     lapply(csv_files, function(.x) {
#       data.table::fread(
#         file = .x,
#         header = TRUE,
#         sep = ",",
#         colClasses = "character",
#         drop = c("longitude", "latitude", "poll_choices"),
#         encoding = "UTF-8"
#       )
#     }),
#     idcol = "campaign"
#   )
#   
#   .io_finish_df(init)
# }
# 
# 
# china_urls <- tweetio::io_campaign_metadata[grepl("china", campaign_name),
#                                             tweet_info_url]
# 
# china_io_tweets <- .io_get_data(china_urls)


# get_real_url <- function(url) {
#   tryCatch(httr::GET(url)$url,
#            error = function(e) url)
# }
# get_real_url("http://goo.gl/YxAIzR")
# get_real_url("facealfnalnfoljiln1ln.com")
