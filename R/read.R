#' @importFrom data.table setattr setDT
prep_tweets <- function(file_path, schema, verbose, ...) {
  out <- .read_tweets(file_paths = file_path,
                      schema = schema,
                      verbose = verbose)

  for (dttm_col in intersect(c("created_at", "account_created_at", "quoted_created_at", "retweet_created_at"),
                             names(out))) {
      setattr(out[[dttm_col]], "class", c("POSIXct", "POSIXt"))
      setattr(out[[dttm_col]], "tzone", "UTC")
  }

  setDT(out)

  out
}


#' Read Tweets into a Data Frame
#'
#' Go from a file of raw tweet data to a convenient, `{rtweet}`-style data frame.
#'
#' @param file_path Path(s) to tweet files.
#' @param schema Select a known file schema. Default: `"auto"`.
#' @template param-as_tibble
#' @template param-verbose
#' @template param-dots
#'
#' @template return-df
#'
#' @template author-bk
#'
#' @examples
#' (path_to_tweet_file <- example_tweet_file())
#'
#' tweet_data.table <- read_tweets(file_path = path_to_tweet_file)
#' print(tweet_data.table, class = TRUE, trunc.cols = TRUE)
#'
#' if (requireNamespace("tibble", quietly = TRUE)) {
#'   read_tweets(file_path = path_to_tweet_file, as_tibble = TRUE)
#' }
#'
#' @export
read_tweets <- function(file_path,
                        schema = c("auto", "qcr"),
                        as_tibble = tweetio_as_tibble(),
                        verbose = tweetio_verbose() || length(file_path) >= 3L,
                        ...) {
  stopifnot("`file_path` must be a character vector" = is.character(file_path))
  stopifnot("`file_path` contains paths that don't exist" = all(file.exists(file_path)))

  schema <- switch(
    match.arg(schema, choices = c("auto", "qcr")),
    auto = 0,
    qcr = 1,
    stop("unknown `schema`", call. = FALSE)
  )

  file_path <- path.expand(file_path)

  out <- prep_tweets(file_path,
                     schema = schema,
                     verbose = verbose,
                     ...)
  .finalize_df(out, as_tibble = as_tibble)
}

