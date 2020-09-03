#' Build an `sf` Object of Tweets
#'
#' @template param-tweet_df
#' @param geom_col Which column to use as the active `geometry` column in result:
#' `"bbox_coords"`, `"quoted_bbox_coords"`,`"retweet_bbox_coords"`, `"geo_coords"`,
#' or `"all"`.
#' @param combine logical(1L), Default: `TRUE`.
#' Whether to row-bind all geometries into a single [sf::st_sf()] object. If `FALSE`,
#' a `list()` of [sf::st_sf()] objects are returned.
#' @template param-as_tibble
#' @template param-dots
#'
#' @return [sf::st_sf()], or `list()` of [sf::st_sf()] objects if `combine = FALSE`
#'
#' @template author-bk
#'
#' @examples
#' path_to_tweet_file <- example_tweet_file()
#'
#' tweet_df <- read_tweets(file_path = path_to_tweet_file)
#'
#' if (requireNamespace("sf", quietly = TRUE)) {
#'   bbox_coords <- as_tweet_sf(tweet_df)
#'
#'   rwtweet_bbox_cooords <- as_tweet_sf(tweet_df, geom_col = "retweet_bbox_coords")
#'
#'   tweet_sf <- as_tweet_sf(tweet_df, geom_col = "all", as_tibble = TRUE)
#'
#'   tweet_sf[, c("created_at", "text", "which_geom", "geometry")]
#' }
#'
#' @export
as_tweet_sf <- function(tweet_df,
                        geom_col = c("bbox_coords", "quoted_bbox_coords",
                                     "retweet_bbox_coords", "geo_coords",
                                     "all"),
                        combine = TRUE,
                        as_tibble = tweetio_as_tibble(),
                        ...) {
  if (!requireNamespace("sf", quietly = TRUE)) {
    stop("The {sf} package is required for this functionality", call. = FALSE) # nocov
  }

  if (!.is_dt(tweet_df)) {
    tweet_df <- .as_dt(tweet_df)
  }

  all_geoms <- c("bbox_coords", "quoted_bbox_coords",
                 "retweet_bbox_coords", "geo_coords")

  geom_col <- match.arg(geom_col, c(all_geoms, "all"))

  if (geom_col == "all") {

    geom_col <- all_geoms
  }
  names(geom_col) <- geom_col

  out <- .compact(
    lapply(geom_col, function(.x) {
      init <- .as_tweet_sf(tweet_df, geom_col = .x)
      if (is.null(init)) {
        return(NULL)
      }

      .finalize_df(
        sf::st_sf(init, stringsAsFactors = FALSE),
        as_tibble = as_tibble
      )
    })
  )

  if (combine) {
    out <- do.call(rbind, out)
  }

  out
}

#' @importFrom data.table :=
.as_tweet_sf <- function(tweet_df, geom_col) {
  # silence R CMD Check NOTE =============================================================
  geometry <- NULL
  which_geom <- NULL
  ..geom_col <- NULL
  # ======================================================================================

  is_point_geom <- geom_col == "geo_coords"

  if (is_point_geom) {
    valid_rows <- .is_valid_point(tweet_df[[geom_col]])
  } else {
    valid_rows <- .is_valid_bbox(tweet_df[[geom_col]])
  }

  if (all(!valid_rows)) {
    return(NULL)
  }

  init <- tweet_df[valid_rows
                   ][, geometry := get(geom_col)
                     ]

  if (is_point_geom) {
    out <- init[, geometry := sf::st_sfc(
      lapply(geometry, function(.x) sf::st_point(c(.x[2L:1L]))),
      crs = 4326L
      )]

  } else {
    out <- init[, geometry := sf::st_sfc(.prep_bbox(geometry), crs = 4326L)]
  }

  out[, which_geom := ..geom_col]

  sf::st_sf(out, sf_column_name = "geometry")
}
