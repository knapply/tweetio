#' Path to an Example File
#' 
#' @return `<character>` file path
#' 
#' @export
example_tweet_file <- function() {
  system.file("example-data/api-stream.json.gz", 
              package = "tweetio")
}