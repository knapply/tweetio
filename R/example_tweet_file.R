#' Path to an Example File
#'
#' @param small `logical(1L)`, Default: `TRUE`.
#'
#' @return `character(1L)` file path
#'
#' @template author-bk
#'
#' @examples
#' example_tweet_file()
#'
#' @export
example_tweet_file <- function(small = TRUE) {
  if (small) {
    system.file("example-data/api-stream-small.json.gz",
                package = "tweetio")
  } else {
    system.file("example-data/api-stream.json.gz",
                package = "tweetio")
  }
}
