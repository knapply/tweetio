#' Write Tweets to Spreadsheets
#' 
#' @template param-tweet_df
#' @template param-file_path
#' @template param-dots 
#' 
#' @template author-bk
#' 
#' @seealso [data.table::fwrite()]
#' 
#' @examples 
#' path_to_tweet_file <- example_tweet_file()
#'                                                        # first 5 rows
#' tweet_df <- read_tweets(file_path = path_to_tweet_file)[1:5, ]
#' 
#' # write comma-separated values files ==================================================
#' target_csv_file <- tempfile(fileext = ".csv")
#' target_csv_file
#' 
#' write_tweet_csv(tweet_df, file_path = target_csv_file) 
#' 
#' @importFrom data.table fwrite
#' 
#' @export
write_tweet_csv <- function(tweet_df, file_path, ...) {
  if (!.is_dt(tweet_df)) {
    tweet_df <- .as_dt(tweet_df)
  }

  fwrite(
    x = jsonify_list_cols(tweet_df), 
    file = file_path,
    bom = TRUE,
    ...
  )
}


#' @rdname write_tweet_csv
#' 
#' @param asTable `<logical>`, default: `TRUE`.
#' 
#' @aliases write_tweet_excel
#' 
#' @seealso [openxlsx::write.xlsx()]
#' 
#' @examples 
#' # write Microsoft Excel files =========================================================
#' target_excel_file <- tempfile(fileext = ".xlsx")
#' target_excel_file
#' 
#' write_tweet_xlsx(tweet_df, file_path = target_excel_file)
#' 
#' # same as `write_tweet_xlsx()`
#' write_tweet_excel(tweet_df, file_path = target_excel_file)
#' 
#' @export
write_tweet_xlsx <- function(tweet_df, file_path, asTable = TRUE, ...) {
  if (!requireNamespace("openxlsx", quietly = TRUE)) {
    stop("{openxlsx} package is required for this functionality.", call. = FALSE)
  }

  if (!.is_dt(tweet_df)) {
    tweet_df <- .as_dt(tweet_df)
  }

  openxlsx::write.xlsx(
    x = jsonify_list_cols(tweet_df),
    file = file_path, 
    colNames = TRUE, 
    asTable = asTable, 
    ...
  )
}


#' @rdname  write_tweet_csv
#' 
#' @export
write_tweet_excel <- write_tweet_xlsx



