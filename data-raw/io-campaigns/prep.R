# utils ==================================================================================
.io_col_classes <- function() {
  c(
    tweetid = "integer64",
    userid = "character",
    user_display_name = "character", 
    user_screen_name = "character",
    user_reported_location = "character", 
    user_profile_description = "character",
    user_profile_url = "character", 
    follower_count = "integer",
    following_count = "integer",
    account_creation_date = "POSIXct", 
    account_language = "character",
    tweet_language = "character", 
    tweet_text = "character", 
    tweet_time = "POSIXct",
    tweet_client_name = "character", 
    in_reply_to_userid = "character",
    in_reply_to_tweetid = "integer64", 
    quoted_tweet_tweetid = "integer64",
    is_retweet = "logical",
    retweet_userid = "character", 
    retweet_tweetid = "integer64",
    latitude = "NULL",
    longitude = "NULL",
    quote_count = "integer",
    reply_count = "integer", 
    like_count = "integer", 
    retweet_count = "integer",
    hashtags = "character",
    urls = "character", 
    user_mentions = "character",
    poll_choices = "NULL"
  )
}

.io_read_csv <- function(file_path) {
  col_classes <- .io_col_classes()

  data.table::fread(
    file = file_path, 
    sep = ",",
    colClasses = col_classes, 
    encoding = "UTF-8"
  )
}

read_clean_save <- function(file_path) {
  # message(file_path)
  
  temp_dir <- tempdir(check = TRUE)
  random_seq <- paste0(sample(1:1000, size = 10), collapse = "")
  unzip_dir <- paste0(temp_dir, "/UNZIP_DIR-", 
                      basename(file_path),
                      random_seq)
  
  dir.create(unzip_dir, showWarnings = FALSE)
  on.exit(unlink(unzip_dir, force = TRUE))
  
  unzip(file_path, exdir = unzip_dir)
  
  csv_files <- dir(unzip_dir, full.names = TRUE,
                   pattern = "\\.csv$", ignore.case = TRUE)
  names(csv_files) <- sub("\\.csv$", "", basename(csv_files))
  
  data.table::rbindlist(
    lapply(csv_files, .io_read_csv)
  )
  
  # init <- lapply(csv_files, function(.x) {
  #   tweetio:::.io_clean_df(
  #     data.table::fread(.x, colClasses = col_classes, encoding = "UTF-8")
  #   )
  # })
  # 
  # # options(warn = 2)
  # # on.exit(options(warn = 0))
  # data.table::rbindlist(init)
  
  # rm(init); gc()
  # message("\n\n")
  # NULL
  
  # split_by <- (0:nrow(res) %/% 1e6)
  # split_dfs <- suppressWarnings(split(res, split_by))
  # names(split_dfs) <- paste0("df_", unique(split_by))
  # 
  # campaign_name <- sub("_tweets_csv_hashed\\.zip", "", basename(file_path))
  # out_dir <- paste0(
  #   "io-campaigns-twitter/",
  #   campaign_name
  # )
  # dir.create(out_dir)
  # 
  # file_names <- names(split_dfs)
  # for (i in seq_along(file_names)) {
  #   out_path <- paste0(out_dir, "/", campaign_name, "_", file_names[[i]], ".rds")
  #   saveRDS(split_dfs[[file_names[[i]]]], out_path, compress = "xz")
  # }
}


# main ===================================================================================
# devtools::load_all()
# library(tweetio)
print.data.table <- function(x) print(tibble::as_tibble(x))
raw_dir <- "~/Documents/IO_FILES"
raw_files <- dir(raw_dir, full.names = TRUE)
names(raw_files) <- basename(raw_files)

fread_res <- read_clean_save(raw_files[4])

# bench1 <- bench::mark(
#   fread_res <- read_clean_save(raw_files[5]),
#   check = FALSE
# )
# 
# 
# bench1
# plot(bench)  
#   # data.table::rbindlist(
#   # lapply(raw_files[5], read_clean_save)
# # )
# 
# library(data.table)
# # missing_vroom <- vroom_res[!tweetid %in% fread_res$tweetid, ]
# fread_res[is.na(tweetid)]
