#' @importFrom data.table setattr setDT
prep_tweets <- function(file_path, verbose, reserve, batch_size, ...) {
  stopifnot("`reserve` must be a single positive number" = length(reserve) == 1L && is.numeric(reserve) && reserve > 0)
  stopifnot("`batch_size` must be a single positive number" = length(batch_size) == 1L && is.numeric(batch_size) && batch_size > 0)

  init <- .read_tweets(file_path,
                       reserve = reserve,
                       verbose = verbose,
                       batch_size = batch_size)

  for (dttm_col in intersect(c("created_at", "account_created_at", "quoted_created_at", "retweet_created_at"),
                             names(init$tweets))) {
      setattr(init$tweets[[dttm_col]], "class", c("POSIXct", "POSIXt"))
      setattr(init$tweets[[dttm_col]], "tzone", "UTC")
  }

  setDT(init$tweets)
  setDT(init$metadata)

  cbind(init$tweets, init$metadata)
}


#' Read Tweets into a Data Frame
#'
#' Go from a file of raw tweet data to a convenient, `{rtweet}`-style data frame.
#'
#' @param file_path Path(s) to tweet files.
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
                        as_tibble = tweetio_as_tibble(),
                        verbose = tweetio_verbose() || length(file_path) >= 3L,
                        ...) {
  stopifnot("`file_path` must be a character vector" = is.character(file_path))
  stopifnot("`file_path` contains paths that don't exist" = all(file.exists(file_path)))

  out <- prep_tweets(path.expand(file_path),
                     verbose = verbose,
                     reserve = length(file_path) * 1e5,
                     batch_size = 1e7,
                     ...)
  .finalize_df(out, as_tibble = as_tibble)
}

