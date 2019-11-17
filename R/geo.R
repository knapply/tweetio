#' Build a `sf` Object of Tweets
#' 
#' @param tweet_df A data frame of tweets, as obtained by `{rtweet}` or `tweetio::read_tweets()`.
#' @param geom_col Which column to use as the active `geometry` column in result.
#' @param .geometry Name of output's geometry column. Intended for internal use only. 
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
                        .geometry = NULL,
                        ...) {
  # silence R CMD Check NOTE
  geometry <- NULL
  ..geom_col <- NULL
  ##########################
  
  
  if (!requireNamespace("sf", quietly = TRUE)) {
    stop("The {sf} package is required for this functionality. Get it with...",
         "\n\t install.packages(\"sf\")")
  }
  
  geom_col <- match.arg(geom_col, c("bbox_coords", "quoted_bbox_coords",
                                    "retweet_bbox_coords", "all"))
  
  if (is.null(.geometry)) {
    .geometry <- geom_col
  }

  if (!is.data.table(tweet_df)) {
    tweet_df <- data.table(tweet_df)
  }
  
  if (geom_col == "all") {
    valid_cols <- intersect(c("bbox_coords", "quoted_bbox_coords", "retweet_bbox_coords"),
                            names(tweet_df))
  
    out <- lapply(valid_cols, function(.x) {
      res <- as_tweet_sf(tweet_df, .x, .geometry = "geometry", ...)
      if (!is.null(res)) {
        res[["which_geom"]] <- .x
      }
      res
    })

    return(do.call(rbind, out))
  }
  
  if (!geom_col %chin% names(tweet_df)) {
    stop(geom_col, " is not a valid column in `tweet_df`.", call. = FALSE)
  }
  
  rows_to_keep <- vapply(tweet_df[[geom_col]],
                         function(.x) length(.x[!is.na(.x)]) != 0L,
                         logical(1L))

  init <- tweet_df[rows_to_keep, ]

  if (nrow(init) == 0L) {
    return(NULL)
  }
  
  if (all(class(init[[geom_col]][[1L]]) == c("XY", "POLYGON", "sfg"))) {
    init[[.geometry]] <- sf::st_sfc(init[[geom_col]], crs = 4326L)
    
  } else {
    init[[.geometry]] <- sf::st_sfc(prep_bbox_(init[[geom_col]]), crs = 4326L)
    
  }
  
  sf::st_sf(init, stringsAsFactors = FALSE)
}

