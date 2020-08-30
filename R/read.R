#' @template author-bk
#' 
prep_tweets <- function(file_path, verbose, reserve, batch_size, doc_pointer, ...) {
  # silence R CMD Check NOTE =============================================================
  metadata <- NULL
  # ======================================================================================
  init <- .read_tweets(file_path, 
                       reserve = reserve, 
                       verbose = verbose, 
                       batch_size = batch_size,
                       doc_pointer = doc_pointer)
  
  data.table::setattr(init$tweets$created_at, "class", c("POSIXct", "POSIXt"))
  data.table::setattr(init$tweets$created_at, "tzone", "UTC")
  data.table::setattr(init$tweets$account_created_at, "class", c("POSIXct", "POSIXt"))
  data.table::setattr(init$tweets$account_created_at, "tzone", "UTC")
  data.table::setDT(init$tweets)
  data.table::setDT(init$metadata)
  
  out <- cbind(init$tweets, init$metadata)
  out[]
}


#' Read Tweets into a Data Frame
#' 
#' Go from a file of raw tweet data to a convenient, `{rtweet}`-style data frame.
#' 
#' @param file_path Path(s) to tweet files.
#' @template param-verbose
#' @template param-dots
#' 
#' @template return-df
#' 
#' @template author-bk
#' 
#' @examples
#' path_to_tweet_file <- example_tweet_file()
#' 
#' tweet_data.table <- read_tweets(file_path = path_to_tweet_file)
#' 
#' tweet_tibble <- read_tweets(file_path = path_to_tweet_file, as_tibble = TRUE)
#' 
#' tweet_tibble
#' 
#' @export
read_tweets <- function(file_path, 
                        as_tibble = tweetio_as_tibble(),
                        verbose = tweetio_verbose() || length(file_path) >= 3L,
                        reserve = length(file_path) * 1e5,
                        batch_size = 1e6 * 1.5,
                        doc_pointer = "",
                        ...) {
  stopifnot("`file_path` must be a character vector" = is.character(file_path))
  stopifnot("`file_path` contains paths that don't exist" = all(file.exists(file_path)))
  stopifnot("`reserve` must be a single positive number" = length(reserve) == 1L && is.numeric(reserve) && reserve > 0)
  stopifnot("`batch_size` must be a single positive number" = length(batch_size) == 1L && is.numeric(batch_size) && batch_size > 0)
  stopifnot("`doc_pointer` must be a single character starting with '/'" = 
              length(doc_pointer) == 1L && is.character(doc_pointer) && (nchar(doc_pointer) == 0L || substring(doc_pointer, 1, 1) == "/"))
  
  out <- prep_tweets(path.expand(file_path), 
                     verbose = verbose, 
                     reserve = reserve,
                     batch_size = batch_size,
                     doc_pointer = doc_pointer,
                     ...)
  out
}
