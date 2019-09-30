#' @importFrom data.table := as.data.table
.read_tweets <- function(file_path, type) {
  stopifnot(file.exists(file_path))
  
  init <- read_tweets_(file_path, type = type)
  
  res <- do.call(cbind.data.frame, list(unname(init), stringsAsFactors = FALSE))
  
  out <- as.data.table(
    res[!is.na(res$status_id), ]
  )
  
  possible_dttm_cols <- c("created_at", "account_created_at",
                          "retweet_created_at", "quoted_created_at",
                          "timestamp", "timestamp_ms",
                          "traptor_timestamp", "traptor_system_timestamp",
                          "traptor_rule_date_added")
  dttm_cols <- intersect(names(out), possible_dttm_cols)
  if (length(dttm_cols)) {
    .SD <- NULL # silence R CMD Check NOTE
    out[, (dttm_cols) := lapply(.SD, format_dttm),
        .SDcols = dttm_cols]
  }

  out[]
}


#' Read tweets into a data frame
#' 
#' @param file_path Path(s) to tweet files.
#' @param type Either `"normal"` (default) for unnested data or `"nested_doc"` if the data
#'  are nested inside a JSON element named `"doc"`.
#' @param .furrr If `file_path` contains multiple files, whether to use `{furrr}`
#'  to process the files in parallel.
#' @param .progress Default: `TRUE`. `TRUE` or `FALSE` value passed to `furrr::future_map()`.
#' @param .strategy Default: `NULL`. Argument passed to `future::plan()`.
#' @param ... Other arguments passed to `future::plan()`.
#' 
#' @template author-bk
#' 
#' 
#' @importFrom data.table rbindlist
#' @export
read_tweets <- function(file_path, type = c("normal", "nested_doc"),
                        .furrr = TRUE,
                        .progress = TRUE, .strategy = NULL, ...) {
  type <- match.arg(type, c("normal", "nested_doc"))
  
  if (length(file_path) == 1L) {
    return(.read_tweets(file_path, type))
  }
  
  use_furrr <- all(.furrr,
                   requireNamespace("future", quietly = TRUE),
                   requireNamespace("furrr", quietly = TRUE))
  
  if (!use_furrr) {
    out <- rbindlist(
      lapply(file_path, .read_tweets, type = type)
    )
  
  } else {
    if (is.null(.strategy)) .strategy <- future::multiprocess
    
    future::plan(strategy = .strategy, ...)
    out <- rbindlist(
      furrr::future_map(file_path, .read_tweets, type = type,
                        .progress = .progress)
    )

  }
  
  chr_cols <- names(out)[vapply(out, is.character, FUN.VALUE = logical(1L))]
  .SD <- NULL # silence R CMD Check NOTE
  out[, (chr_cols) := lapply(.SD, function(.x) {
      .x[.x == ""] <- NA_character_
      .x
    }), 
    .SDcols = chr_cols]
  
  out[]
}



