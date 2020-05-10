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
#' bbox_coords <- as_tweet_sf(tweet_df)
#'
#' rwtweet_bbox_cooords <- as_tweet_sf(tweet_df, geom_col = "retweet_bbox_coords")
#'
#' tweet_sf <- as_tweet_sf(tweet_df, geom_col = "all", as_tibble = TRUE)
#'
#' tweet_sf[, c("created_at", "text", "which_geom", "geometry")]
#' @export
as_tweet_sf <- function(tweet_df,
                        geom_col = c(
                          "bbox_coords", "quoted_bbox_coords",
                          "retweet_bbox_coords", "geo_coords",
                          "all"
                        ),
                        combine = TRUE,
                        as_tibble = tweetio_as_tibble(),
                        ...) {
  UseMethod("as_tweet_sf")
}

#' @rdname as_tweet_sf
#'
#' @importFrom data.table as.data.table
#' @export
as_tweet_sf.data.frame <- function(tweet_df,
                                   geom_col = c(
                                     "bbox_coords", "quoted_bbox_coords",
                                     "retweet_bbox_coords", "geo_coords",
                                     "all"
                                   ),
                                   combine = TRUE,
                                   as_tibble = tweetio_as_tibble(),
                                   ...) {
  as_tweet_sf(
    .as_dt(tweet_df),
    geom_col = geom_col,
    combine = combine,
    as_tibble = as_tibble,
    ...
  )
}

#' @rdname as_tweet_sf
#'
#' @export
as_tweet_sf.data.table <- function(tweet_df,
                                   geom_col = c(
                                     "bbox_coords", "quoted_bbox_coords",
                                     "retweet_bbox_coords", "geo_coords",
                                     "all"
                                   ),
                                   combine = TRUE,
                                   as_tibble = tweetio_as_tibble(),
                                   ...) {
  if (nrow(tweet_df) == 0L) {
    return(NULL)
    # .stop("`tweet_df` has no rows.")
  }
  if (!requireNamespace("sf", quietly = TRUE)) {
    .stop("The {sf} package is required for this functionality")
  }

  all_geoms <- c(
    "bbox_coords", "quoted_bbox_coords",
    "retweet_bbox_coords", "geo_coords"
  )

  geom_col <- match.arg(geom_col, c(all_geoms, "all"))

  if (geom_col == "all") {
    geom_col <- intersect(all_geoms, names(tweet_df))
  }
  if (.is_empty(geom_col)) {
    .stop("`tweet_df` does not have requested any of the requested `geom_col`s.")
  }
  names(geom_col) <- geom_col

  out <- .compact(
    lapply(geom_col, function(.x) {
      init <- .as_tweet_sf(tweet_df, geom_col = .x)

      if (is.null(init)) {
        NULL
      } else {
        .finalize_df(
          sf::st_sf(init, stringsAsFactors = FALSE),
          as_tibble = as_tibble
        )
      }
    })
  )

  if (combine) {
    out <- do.call(rbind, out)
  }

  out
}


.as_point <- function(point_coords) {
  structure(point_coords[2L:1L], class = c("XY", "POINT", "sfg"))
}


.prep_sf_points <- function(tweet_df, geom_col) {
  # silence R CMD Check NOTE ===================================================
  geometry <- NULL
  # ============================================================================
  
  valid_rows <- .map_lgl(
    tweet_df[[geom_col]],
    function(.x) length(.x) == 2L && is.double(.x) && !any(is.na(.x))
  )

  if (!any(valid_rows)) {
    return(NULL)
  }

  # styler: off
  init <- tweet_df[valid_rows
                   ][, geometry := get(geom_col)
                     ]
  # styler: on

  out <- init[, geometry := sf::st_sfc(
    lapply(geometry, .as_point),
    crs = 4326L
  )]
}

.as_bbox_polygon <- function(bbox_coords) {
  structure(
    list(
      structure(
        bbox_coords[c(1L, 2L, 3L, 4L, 1L, 5L, 6L, 7L, 8L, 8L)],
        .Dim = c(5L, 2L)
      )
    ),
    class = c("XY", "POLYGON", "sfg")
  )
}

.prep_sf_polygons <- function(tweet_df, geom_col) {
  # silence R CMD Check NOTE ===================================================
  geometry <- NULL
  # ============================================================================
  
  valid_rows <- .map_lgl(
    tweet_df[[geom_col]],
    function(.x) length(.x) == 8L && is.double(.x) && !any(is.na(.x))
  )

  # styler: off
  init <- tweet_df[valid_rows
                   ][, geometry := get(geom_col)
                     ]
  # styler: on

  init[, geometry := sf::st_sfc(
    lapply(geometry, .as_bbox_polygon),
    crs = 4326L
  )]
}


#' @importFrom data.table := setDF
.as_tweet_sf <- function(tweet_df, geom_col) {
  # silence R CMD Check NOTE ===================================================
  geometry <- NULL
  which_geom <- NULL
  ..geom_col <- NULL
  # ============================================================================

  if (geom_col == "geo_coords") {
    out <- .prep_sf_points(tweet_df, geom_col)
  } else {
    out <- .prep_sf_polygons(tweet_df, geom_col)
  }

  out[, which_geom := ..geom_col]
  setDF(out)

  out
}
