# 
# # io_download_campaign <- function()
# 
# 
# #' @importFrom data.table %chin% setcolorder setnames
# .io_recode_col_names <- function(df) {
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
#     mentions_user_id = "user_mentions",
#     poll_choices = "poll_choices"
#   )
#   
#   target_cols <- cols_kv[cols_kv %chin% names(df)]
#   if (!.is_empty(target_cols)) {
#     setnames(df, old = target_cols, new = names(target_cols))
#     out_cols <- names(target_cols)
#     setcolorder(df, neworder = out_cols)
#   }
#   
#   df
# }
# 
# 
# #' @importFrom stringi stri_replace_all_regex stri_split_fixed
# .io_clean_list_cols <- function(x) {
#   empty_strings <- is.na(x) | nchar(x) == 0L | x == "[]"
#   
#   x[empty_strings] <- NA_character_
# 
#   x[!empty_strings] <- stri_replace_all_regex(
#     x[!empty_strings],
#     pattern = "'|\\[|\\]", 
#     replacement = ""
#   )
# 
#   stri_split_fixed(x, pattern = ",")
# }
# 
# 
# #' @importFrom data.table := %chin% fifelse setcolorder
# #' @importFrom stringi stri_detect_regex
# .io_clean_df <- function(x) {
#   # silence R CMD Check NOTE =============================================================
#   .SD <- NULL
#   user_id <- NULL
#   screen_name <- NULL
#   name <- NULL
#   is_user_hashed <- NULL
#   # ======================================================================================
#   count_cols <- stri_detect_regex(names(x), "_count$")
#   bad_int_cols <- .match_col_names(x[, ..count_cols], is.double)
#   if (!.is_empty(bad_int_cols)) {
#     x[, (bad_int_cols) := lapply(.SD, as.integer),
#       .SDcols = bad_int_cols]
#   }
#   
#   if (!is.logical(x[["is_retweet"]])) {
#     x[, is_retweet := as.logical(is_retweet)]
#   }
#   
#   chr_cols <- .match_col_names(x, is.character)
#   if (!.is_empty(chr_cols)) {
#     x[, (chr_cols) := lapply(.SD, function(.x) {
#       fifelse(nchar(.x) == 0L, NA_character_, .x)
#     }),
#     .SDcols = chr_cols]
#   }
#   
#   list_cols <- intersect(names(x), c("hashtags", "user_mentions", "urls"))
#   if (!.is_empty(list_cols)) {
#     x[, (list_cols) := lapply(.SD, .io_clean_list_cols), 
#       .SDcols = list_cols]
#   }
#   
#   x <- .io_recode_col_names(x)
#   
#   name_cols <- c("screen_name", "name")
#   if (all(name_cols %chin% names(x))) {
#     x[, is_user_hashed := user_id == screen_name & user_id == name
#       ][, (name_cols) := lapply(.SD, function(.x) {
#           fifelse(is_user_hashed, NA_character_, .x)
#         }),
#         .SDcols = name_cols
#         ]
#   }
#   
#   first_cols <- c("user_id", "is_user_hashed")
#   col_order <- c(first_cols, setdiff(names(x), first_cols))
#   
#   setcolorder(x, neworder = col_order)[]
# }
# 
# 
# #' @importFrom stringi stri_detect_regex stri_extract_first_regex
# #' @importFrom utils download.file
# .io_download_data <- function(data_url, dest_file = tempfile(fileext = ".zip")) {
#   if (!.is_scalar_chr(data_url)) {
#     stop("`data_url` must be a scalar character.", call. = FALSE)
#   }
#   
#   download.file(url = data_url, destfile = dest_file)
#   
#   dest_file
# }
# 
# 
# #' @importFrom stringi stri_extract_first_regex
# #' @importFrom utils unzip
# .io_unzip_data <- function(file_path, url_col) {
#   if (!.is_scalar_chr(file_path)) {
#     .stop("`file_path` must be a scalar character.")
#   }
#   if (!.file_exists(file_path)) {
#     .stop("`file_path` does not exist.")
#   }
# 
#   temp_dir <- tempdir(check = TRUE)
#   unzip(file_path, exdir = temp_dir)
#   
#   file_infix <- switch(
#     url_col,
#     tweet_info_url = "tweets",
#     account_info_url = "users"
#     ,
#     .stop('something went wrong')
#   )
# 
#   dir(temp_dir, full.names = TRUE, 
#       pattern = sprintf("_%s_csv_hashed\\.csv$", file_infix))
# }
# 
# 
# #' @importFrom data.table fread rbindlist
# .io_read_clean <- function(file_path, rbind = TRUE, ...) {
#   do_files_exist <- .file_exists(file_path)
#   if (!all(do_files_exist)) {
#     bad_files <- file_path[!do_files_exist]
#     .stop("The following `file_path`s do not exist:",
#           paste("\n\t-", bad_files))
#   }
#   
#   col_classes <- c(
#     tweetid = "character",
#     userid = "character",
#     user_display_name = "character", 
#     user_screen_name = "character",
#     user_reported_location = "character", 
#     user_profile_description = "character",
#     user_profile_url = "character", 
#     follower_count = "integer",
#     following_count = "integer",
#     account_creation_date = "POSIXct", 
#     account_language = "character",
#     tweet_language = "character", 
#     tweet_text = "character", 
#     tweet_time = "POSIXct",
#     tweet_client_name = "character", 
#     in_reply_to_userid = "character",
#     in_reply_to_tweetid = "character", 
#     quoted_tweet_tweetid = "character",
#     is_retweet = "logical",
#     retweet_userid = "character", 
#     retweet_tweetid = "character",
#     latitude = "NULL",
#     longitude = "NULL",
#     quote_count = "integer",
#     reply_count = "integer", 
#     like_count = "integer", 
#     retweet_count = "integer",
#     hashtags = "character",
#     urls = "character", 
#     user_mentions = "character",
#     poll_choices = "NULL"
#   )
#   
#   .io_clean_df(
#     rbindlist(
#       lapply(file_path, function(.x) {
#         fread(.x, encoding = "UTF-8", colClasses = col_classes, 
#               na.strings = c("", '""', '"\\[\\]"'))
#       })
#     )
#   )
# }
# 
# 
# io_get_data <- function(campaign_name, 
#                         unit = c("statuses", "accounts"),
#                         as_tibble = tweetio_as_tibble(), 
#                         ...) {
#   if (!.is_scalar_chr(campaign_name)) {
#     .stop("`campaign_name` must be a scalar <character>.")
#   }
#   
#   url_col <- switch(match.arg(unit, c("statuses", "accounts")),
#     statuses = "tweet_info_url",
#     accounts = "account_info_url"
#     ,
#     .stop('something went wrong')
#   )
# 
#   target_row <- which(io_campaign_metadata$campaign_name == campaign_name)
#   
#   if (.is_empty(target_row)) {
#     suggestions <- agrep(campaign_name, all_meta$campaign_name, value = TRUE)
#     .stop("`campaign_name` is not valid. Did you mean one of these?",
#           paste0('\n\t- "', suggestions, '"'))
#   }
#   
#   target_url <- all_meta[target_row, get(url_col)]
#   
#   # return(target_url)
# 
# 
#   target_file_path <- .io_download_data(target_url)
# 
#   unzipped_file_path <- .io_unzip_data(target_file, url_col = url_col)
# 
#   out <- .io_read_clean(unzipped_file_path)
# 
#   .finalize_df(out, as_tibble = as_tibble)
# }
# 

