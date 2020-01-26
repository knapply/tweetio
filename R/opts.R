#' `{tweetio}` Options
#' 
#' @template author-bk
#' 
#' @examples 
#' tweetio_options()
#' 
#' @export
tweetio_options <- function() {
  list(
    tweetio.as_tibble = tweetio_as_tibble(),
    tweetio.verbose = tweetio_verbose()
  )
}

#' @rdname tweetio_options
#' 
#' @export
tweetio_as_tibble <- function() {
  getOption("tweetio.as_tibble", FALSE)
}


#' @rdname tweetio_options
#' 
#' @export
tweetio_verbose <- function() {
  getOption("tweetio.verbose", FALSE)
}
