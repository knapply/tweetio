# utils ==================================================================================
# .io_col_classes <- function(x = NULL) {
#   out <- c(
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
#   if (is.null(x)) {
#     return(out)
#   }
#   
#   out[names(out) %chin% names(x)]
# }
# 
.io_recode_col_names <- function(df) {
  cols_kv <- c(
    status_id = "tweetid",
    user_id = "userid",
    name = "user_display_name",
    screen_name = "user_screen_name",
    location = "user_reported_location",
    description = "user_profile_description",
    url = "user_profile_url",
    followers_count = "follower_count",
    following_count = "following_count",
    account_created_at = "account_creation_date",
    account_lang = "account_language",
    lang = "tweet_language",
    text = "tweet_text",
    created_at = "tweet_time",
    source = "tweet_client_name",
    reply_to_user_id = "in_reply_to_userid",
    reply_to_status_id = "in_reply_to_tweetid",
    quoted_status_id = "quoted_tweet_tweetid",
    is_retweet = "is_retweet",
    retweet_user_id = "retweet_userid",
    retweet_status_id = "retweet_tweetid",
    # latitude = "latitude",
    # longitude = "longitude",
    quote_count = "quote_count",
    reply_count = "reply_count",
    like_count = "like_count",
    retweet_count = "retweet_count",
    hashtags = "hashtags",
    urls_url = "urls",
    mentions_user_id = "user_mentions"
    # poll_choices = "poll_choices"
  )

  target_cols <- cols_kv[cols_kv %chin% names(df)]
  if (length(target_cols)) {
    df <- data.table::setnames(df, old = target_cols, new = names(target_cols))
    out_cols <- names(target_cols)
    df <- data.table::setcolorder(df, neworder = out_cols)
  }

  df
}
# 
# 
# .io_coerce_cols <- function(x, cols, type, coercer, ...) {
#   cols <- intersect(names(x), cols)
#   target_cols <- .match_col_names(x[, ..cols], function(.x) !inherits(.x, type))
#   if (.is_empty(target_cols)) {
#     return(x)
#   }
#   
#   if (type == "list") {
#     x[, (target_cols) := lapply(.SD, function(.x) {
#       stringi::stri_split_fixed(
#         stringi::stri_replace_all_regex(.x, pattern = "'|\\[|\\]",
#                                         replacement = ""),
#         pattern = ","
#       )
#     }),
#     .SDcols = target_cols]
#   } else {
#     x[, (target_cols) := lapply(.SD, coercer, ...),
#       .SDcols = target_cols]
#   }
# 
#   x
# }
# 
# .io_clean_df <- function(x) {
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
#   x <- .io_coerce_cols(x, col_classes$character, "character", as.character)
#   
#   chr_cols <- .match_col_names(x, is.character)
#   if (!.is_empty(chr_cols)) {
#     x[, (chr_cols) := lapply(.SD, function(.x) {
#         data.table::fifelse(nchar(.x) == 0L | .x == "[]", NA_character_, .x)
#       }),
#     .SDcols = chr_cols]
#   }
#   
#   x <- .io_coerce_cols(x, col_classes$integer, "integer", as.integer)
#   x <- .io_coerce_cols(x, col_classes$logical, "logical", as.logical)
#   x <- .io_coerce_cols(x, col_classes$POSIXct, "POSIXct", as.POSIXct, 
#                        origin = "1970-01-01")
# 
#   .io_recode_col_names(x)
# }
# 
# # .io_read_csv <- function(file_path) {
# #   col_classes <- .io_col_classes()
# # 
# #   data.table::fread(
# #     file = file_path, 
# #     sep = ",",
# #     colClasses = col_classes, 
# #     encoding = "UTF-8"
# #   )
# # }
# 
# 
# 
# read_clean_save <- function(file_path) {
#   temp_dir <- tempdir(check = TRUE)
#   random_seq <- paste0(sample(1:10, size = 10), collapse = "")
#   unzip_dir <- paste0(temp_dir, "/UNZIP_DIR-", 
#                       basename(file_path),
#                       random_seq)
#   
#   dir.create(unzip_dir, showWarnings = FALSE)
#   on.exit(unlink(unzip_dir, force = TRUE))
#   
#   unzip(file_path, exdir = unzip_dir)
#   
#   csv_files <- dir(unzip_dir, full.names = TRUE,
#                    pattern = "\\.csv$", ignore.case = TRUE)
#   names(csv_files) <- sub("\\.csv$", "", basename(csv_files))
#   
#   out <- data.table::rbindlist(
#     lapply(csv_files, function(.x) {
#       data.table::fread(.x,
#                         drop = c("longitude", "latitude", "poll_choices"),
#                         # colClasses = .io_col_classes(),
#                         encoding = "UTF-8")
#     })
#   )
#   
#   # out <- .io_clean_df(out)
#   
#   # hash_cols <- c("name", "screen_name")
#   # out[, is_hashed := user_id == name
#   #     ][, (hash_cols) := lapply(.SD, function(.x) {
#   #       data.table::fifelse(is_hashed, NA_character_, .x)
#   #       }),
#   #       .SDcols = hash_cols
#   #       ][, is_hashed := NULL
#   #         ]
#   
#   out[]
# }
# 
# 
# # main ===================================================================================
# # library(furrr)
# # plan(multiprocess, workers = 12)
# # devtools::load_all(path = "~/Documents/tweetio")
# # library(tweetio)
# # library(data.table)
# print.data.table <- function(x) print(tibble::as_tibble(x))
# raw_dir <- "~/Documents/IO_FILES"
# raw_files <- dir(raw_dir, full.names = TRUE)
# names(raw_files) <- stringi::stri_replace_first_fixed(basename(raw_files), "_tweets_csv_hashed.zip", "")
# 
# 
# library(data.table)
# read1 <- function(x) {
#   temp_dir <- tempdir(check = TRUE)
#   random_seq <- paste0(sample(1:10, size = 10), collapse = "")
#   unzip_dir <- paste0(temp_dir, "/UNZIP_DIR-", 
#                       basename(x),
#                       random_seq)
#   
#   dir.create(unzip_dir, showWarnings = FALSE)
#   on.exit(unlink(unzip_dir, force = TRUE))
#   
#   unzip(x, exdir = unzip_dir)
#   
#   csv_files <- dir(unzip_dir, full.names = TRUE,
#                    pattern = "\\.csv$", ignore.case = TRUE)
#   
#   rbindlist(
#     lapply(csv_files, vroom::vroom, 
#            col_types = "ccccccciiTcccTcccclcc--iiiiccc-")
#   )
# }
# 
# read2 <- function(x) {
#   command <- sprintf("unzip -p %s", x)
#   
#   out <- fread(
#     cmd = command, sep = ",",
#     colClasses = "character",
#     drop = c("longitude", "latitude", "poll_choices"),
#     encoding = "UTF-8",
#     verbose = FALSE
#   )
#   
#   out[tweetid != "tweetid"]
# }

.fread <- function(x, nrows) {
  suppressWarnings(
    data.table::fread(
      x,
      nrows = nrows,
      header = TRUE,
      sep = ",",
      colClasses = "character",
      select = "userid",
      # drop = c("longitude", "latitude", "poll_choices"),
      encoding = "UTF-8",
      verbose = FALSE
    )
  )
}

read3 <- function(x, nrows = Inf) {
  temp_dir <- tempdir(check = TRUE)
  random_seq <- paste0(sample(1:10, size = 10), collapse = "")
  unzip_dir <- paste0(temp_dir, "/UNZIP_DIR-", 
                      basename(x),
                      random_seq)
  
  dir.create(unzip_dir, showWarnings = FALSE)
  on.exit(unlink(unzip_dir, force = TRUE))
  
  suppressWarnings(unzip(x, exdir = unzip_dir))
  
  csv_files <- dir(unzip_dir, full.names = TRUE,
                   pattern = "\\.csv$", ignore.case = TRUE)
  if (!length(csv_files)) {
    return(NULL)
  } else if (length(csv_files) == 1L) {
    out <- .fread(csv_files, nrows = nrows)
  } else {
    out <- rbindlist(
      lapply(csv_files, .fread, nrows = nrows)
    )
  }
  
  out
}

finish_df <- function(out) { 
  if (is.null(out)) return(NULL)
  
  out[
    ,
    (names(out)) := lapply(
      .SD, function(.x) fifelse(.x %chin% c("", "[]"), NA_character_, .x)
    )
  ]
  
  col_classes <- list(
    character = c("tweetid", "userid", "user_display_name", 
                  "user_screen_name", "user_reported_location", "user_profile_description", 
                  "user_profile_url", "account_language", "tweet_language", "tweet_text", 
                  "tweet_client_name", "in_reply_to_userid", "in_reply_to_tweetid", 
                  "quoted_tweet_tweetid", "retweet_userid", "retweet_tweetid", 
                  "hashtags", "urls", "user_mentions"), 
    integer = c("follower_count", "following_count", "quote_count", "reply_count",
                "like_count", "retweet_count"), 
    logical = "is_retweet", 
    POSIXct = c("account_creation_date", "tweet_time"),
    list = c("hashtags", "user_mentions", "urls")
  )
  
  out[, (col_classes$integer) := lapply(.SD, as.integer),
      .SDcols = col_classes$integer
      ][, (col_classes$logical) := lapply(.SD, as.logical),
        .SDcols = col_classes$logical
        ][, (col_classes$POSIXct) := lapply(.SD, as.POSIXct, tz = "UTC"),
          .SDcols = col_classes$POSIXct
          ][, (col_classes$list) := lapply(.SD, function(.x) {
            init <- stringi::stri_replace_all_regex(.x, pattern = "^\\[|\\]$",
                                                    replacement = "")
            out <- stringi::stri_split_regex(init, pattern = "\\s?,\\s?")
            lapply(out, function(.y) {
              unique(.y[.y != "0"])
            })
          }),
          .SDcols = col_classes$list
          ]
  
  .io_recode_col_names(out)
  
  hash_cols <- c("name", "screen_name")
  out[, (hash_cols) := lapply(.SD, function(.x) {
    fifelse(user_id == name, NA_character_, .x)
   }), 
   .SDcols = hash_cols]

  out
}

suppressMessages(library(furrr, quietly = TRUE, warn.conflicts = FALSE))
plan(multiprocess)
suppressMessages(library(data.table, warn.conflicts = FALSE))

print.data.table <- function(x, ...) print(tibble::as_tibble(x), ...)
raw_dir <- "~/Documents/IO_FILES"
raw_files <- dir(raw_dir, full.names = TRUE)
names(raw_files) <- stringi::stri_replace_first_fixed(basename(raw_files), 
                                                      "_tweets_csv_hashed.zip", "")

cat(sprintf("\t- start: %s", start <- Sys.time()),
    "-", future::availableCores(), "cores spinning up...",
    "\n")

suppressMessages(
  big_init <- future_map(raw_files, read3, .progress = TRUE)
)
big_test <- #finish_df(
  rbindlist(big_init, use.names = TRUE, idcol = ".campaign")
# )#[order(screen_name)]

cat(sprintf("\t- end: %s", end <- Sys.time()), "-", capture.output(end - start), "...\n")

options(width = 240)
# cat(paste("\t-", unique(big_test$.campaign), collapse = "\n"))
cat("\n")
print(big_test)
cat("\n")
cat("Tweets per IO campaign:\n")
print(big_test[, .N, by = .campaign][order(-N)], n = Inf, width = Inf)
cat("\n")
cat("Tweets per Account:\n")
print(big_test[, .N, by = userid][order(-N)], n = 10, width = Inf)
# dplyr::glimpse(big_test)


########################
# test <- finish_df(
#   read3(raw_files[names(raw_files) == "ira"], nrows = Inf)
# )
# 
# cleaned <- copy(test)
# 
# proto_net <- tweetio::as_proto_net(cleaned, all_status_data = TRUE, all_user_data = TRUE)
# # pn2 <- copy(proto_net)
# # pn2$edges <- pn2$edges[to != "0"]
# # pn2$nodes <- pn2$nodes[name != "0"]
# lapply(proto_net, tibble::as_tibble)
# ig <- tweetio::as_tweet_igraph(proto_net)
# igraph::V(ig)$is_bad_guy <- igraph::V(ig)$name %chin% test$user_id
# length(which(igraph::V(ig)$is_bad_guy))



# data.table::fread('a,b,c\na,1,""\n"[]",2,a', 
#                   header = TRUE,
#                   sep = ",",
#                   na.strings = c("", ',"",', '\"\"', '\\"\\"', '""', NA, 
#                                  '"\\[\\]"',
#                                  '"[]"', "\\[\\]", "absent"),
#                   verbose = TRUE)


# tester <- raw_files[[2]]
# 
# test <- read3(tester)
# dplyr::glimpse(test)
# 
# cat(test[[7]])
# 
# res <- bench::mark(
#   t1 <- read1(tester)
#   ,
#   t2 <- read2(tester)
#   ,
#   check = FALSE
# ); res
# 
# 
# identical(names(t1), names(t2))
# identical(nrow(t1), nrow(t2))
# 
# is_missing_row <- !t2$tweetid %chin% t1$tweetid
# length(which(is_missing_row))
# 
# t2[, .N, by = tweetid
#    ][order(-N)]
# 
# 
# test <- fread(file = raw_files[[2]],
#               drop = c("longitude", "latitude", "poll_choices"),
#               encoding = "UTF-8")
# 
# 
# 
# test2
# 
# 
# # profvis::profvis(
#   # test <- read_clean_save(raw_files[[2]])
# # )
# # test
# 
# 
# 
# test <- #data.table::rbindlist(
#   purrr::imap(raw_files[1:4], ~ {
#     out <- tryCatch(
#       read_clean_save(.x),
#       error = function(e) {
#         print(e)
#         NULL
#       },
#       warning = function(e) {
#         print(w)
#         NA
#       }
#     )
#     if (is.null(out) || is.na(out)) print(.y)
#     out
#   }
#   )#,
#   # idcol = ".campaign"
# # )
# 
# # options(width = 100)
# purrr::map(test, tibble::as_tibble)
# purrr::keep(test, ~ is.null(.x) || is.na(.x))
# dplyr::glimpse(test)
# # init <- data.table::copy(fread_res)
# # bench1 <- bench::mark(
# #   fread_res <- read_clean_save(raw_files[5]),
# #   check = FALSE
# # )
# # 
# # 
# # bench1
# # plot(bench)  
# #   # data.table::rbindlist(
# #   # lapply(raw_files[5], read_clean_save)
# # # )
# # 
# # library(data.table)
# # missing_vroom <- vroom_res[!tweetid %in% fread_res$tweetid, ]
# fread_res[is.na(tweetid)]
