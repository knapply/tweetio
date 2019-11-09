#' Build a `sf` Object of Tweets
#' 
#' @param tweet_df A data frame of tweets, as obtained by `{rtweet}` or `tweetio::read_tweets()`.
#' @param geom_col Which column to use as the active `geometry` column in result.
#' @param tibble_sf Whether to return a `tibble` `sf` data frame. Requires `{tibble}`.
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
#' @importFrom data.table %chin% data.table is.data.table
#' 
#' @export
as_tweet_sf <- function(tweet_df, 
                        geom_col = c("bbox_coords", "quoted_bbox_coords",
                                     "retweet_bbox_coords", "all"),
                        tibble_sf = TRUE,
                        ...) {
  if (!requireNamespace("sf", quietly = TRUE)) {
    stop("The {sf} package is required for this functionality. Get it with...",
         "\n\t install.packages(\"sf\")")
  }
  
  geom_col <- match.arg(geom_col, c("bbox_coords", "quoted_bbox_coords",
                                    "retweet_bbox_coords", "all"))

  
  # silence R CMD Check NOTE
  geometry <- NULL
  ..geom_col <- NULL
  ##########################

  if (!inherits(tweet_df, "data.table")) {
    tweet_df <- data.table(tweet_df)
  }
  
  if (geom_col == "all") {
    valid_cols <- intersect(c("bbox_coords", "quoted_bbox_coords", "retweet_bbox_coords"),
                            names(tweet_df))
    names(valid_cols) <- valid_cols
    
    out <- lapply(valid_cols, function(.x) {
      res <- as_tweet_sf(tweet_df, .x, tibble_sf = tibble_sf, ...)
      res[["which_geom"]] <- .x
      res
    })

    return(do.call(rbind, out))
  }
  
  if (!geom_col %chin% names(tweet_df)) {
    stop(geom_col, " is not a valid column in `tweet_df`.", call. = FALSE)
  }

  init <- tweet_df[
    vapply(get(geom_col), function(.x) length(.x[!is.na(.x)]) != 0L, logical(1L)),
  ]
  
  if (nrow(init) == 0L) {
    return(NULL)
  }
  
  if (all(class(init[[geom_col]][[1L]]) == c("XY", "POLYGON", "sfg"))) {
    geometry <- sf::st_sfc(init[[geom_col]], crs = 4326L)
    
  } else {
    geometry <- sf::st_sfc(prep_bbox_(init[[geom_col]]), crs = 4326L)

  }
  
  out <- sf::st_sf(init, stringsAsFactors = FALSE,
                   geometry = sf::st_wrap_dateline(geometry))
  
  if (tibble_sf && requireNamespace("tibble", quietly = TRUE)) {
    out <- sf::st_as_sf(tibble::as_tibble(out))
  }
  
  out
}

