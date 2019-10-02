#' @importFrom data.table := as.data.table
#' @importFrom utils unzip
.read_tweets <- function(file_path, ...) {
  stopifnot(is.character(file_path) && length(file_path) == 1L)
  stopifnot(file.exists(file_path))

  if (grepl("\\.csv$", file_path, ignore.case = TRUE)) {
    stop("Tweets in CSV files are not yet supported.",
         call. = FALSE)
  }
  
  if (grepl("\\.zip$", file_path)) {
    temp_dir <- tempdir(check = TRUE)
    target_dir <- paste0(temp_dir, "/tweetio")
    dir.create(target_dir)
    on.exit(unlink(target_dir, force = TRUE))

    unzip(zipfile = file_path, exdir = target_dir)
    unzipped <- dir(target_dir, full.names = TRUE)
    if (length(unzipped) == 0L) {
      stop("`file_path` is a ZIP archive, but it's empty.")
    }
    if (length(unzipped) > 1L) {
      stop("`file_path` is a ZIP archive with multiple files. Only ZIP archives
           with one file are supported.")
    }

    file_path <- unzipped
  }
  
  init <- read_tweets_(file_path)
  
  res <- do.call(cbind.data.frame, list(unname(init), stringsAsFactors = FALSE))
  
  out <- as.data.table(
    res[!is.na(res$status_id), ]
  )
  
  out
}


#' Read tweets into a data frame
#' 
#' @param file_path Path to tweet files.
#' @param file_paths Paths to multiple tweet files.
#' @param ... Arguments passed to or from other methods.
#' 
#' @return `data.table`
#' 
#' @template author-bk
#' 
#' @export
read_tweets <- function(file_path, ...) {
  out <- .read_tweets(file_path, ...)
  
  finalize_cols(out)
}



#' @rdname read_tweets
#' 
#' @param in_parallel Default: `TRUE`. Whether to use `future.apply::future_lapply()`
#'  to process the files in parallel. Ignored if `{future}` or `{future.apply}` are not installed.
#' @param .strategy Default: `NULL`. argument passed to `future::plan()`'s `strategy` parameter.
#'   If `NULL`, `future::multiprocess` is used. Ignored if `{future}` or `{future.apply}` are not installed.
#' 
#' @importFrom data.table rbindlist
#' @export
read_tweets_bulk <- function(file_paths, in_parallel = TRUE, .strategy = NULL, ...) {
  if (length(file_paths) == 1L) {
    return(read_tweets(file_paths))
  }
  
  use_future <- all(in_parallel,
                    requireNamespace("future", quietly = TRUE),
                    requireNamespace("future.apply", quietly = TRUE))
  
  if (use_future) {
    if (is.null(.strategy)) .strategy <- future::multiprocess
    future::plan(strategy = .strategy, ...)

    init <- future.apply::future_lapply(file_paths, .read_tweets)
  } else {
    init <- lapply(file_paths, .read_tweets)
  }
  
  out <- rbindlist(init)
  
  finalize_cols(out)
}


finalize_cols <- function(x, ...) {
  .SD <- NULL # silence R CMD Check NOTE
  
  chr_cols <- names(x)[vapply(x, is.character, FUN.VALUE = logical(1L))]
  
  x[, (chr_cols) := lapply(.SD, function(.x) {
    .x[.x == ""] <- NA_character_
    .x
  }), 
  .SDcols = chr_cols]
  
  
  possible_dttm_cols <- c("created_at", "account_created_at",
                          "retweet_created_at", "quoted_created_at",
                          "timestamp", "timestamp_ms",
                          "traptor_timestamp", "traptor_system_timestamp",
                          "traptor_rule_date_added")
  dttm_cols <- intersect(names(x), possible_dttm_cols)
  if (length(dttm_cols)) {
    x[, (dttm_cols) := lapply(.SD, format_dttm),
        .SDcols = dttm_cols]
  }
  
  x[]
}
