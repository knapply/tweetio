#' Build a `sf` Object of Tweets
#' 
#' @param tweet_df A data frame of tweets, as obtained by `{rtweet}` or `tweetio::read_tweets()`.
#' @param ... Arguments passed to or from other methods.
#' 
#' @return `sf`
#' 
#' @details 
#' `as_tweet_sf()` uses the `bbox_coords` to build `POLYGON`s. Rows without a valid 
#' bounding box are discarded.
#' 
#' @template author-bk
#'
#' @importFrom data.table data.table is.data.table
#' 
#' @export
as_tweet_sf <- function(tweet_df, ...) {
  if (!requireNamespace("sf", quietly = TRUE)) {
    stop("The {sf} package is required for this functionality. Get it with...",
         "\n\t install.packages(\"sf\")")
  }
  
  # silence R CMD Check NOTE
  geometry <- NULL
  bbox_coords <- NULL
  ##########################
  
  original_class <- class(tweet_df)
  if (!"data.table" %in% original_class) {
    tweet_df <- data.table(tweet_df)
  }

  init <- tweet_df[
    vapply(bbox_coords, function(.x) length(.x[!is.na(.x)]) != 0L, logical(1L))
  ]
  
  if (nrow(init) == 0L) {
    return(NULL)
  }

  if (all(class(init$bbox_coords[[1L]]) == c("XY", "POLYGON", "sfg"))) {
    geometry <- sf::st_sfc(init[["bbox_coords"]])
  } else {
    geometry <- sf::st_sfc(prep_bbox_(init[["bbox_coords"]]))
  }
  
  out <- sf::st_sf(init, stringsAsFactors = FALSE, crs = 4326L,
                   geometry = geometry)
  
  class(out) <- unique(c("sf", original_class))
  
  out
}

