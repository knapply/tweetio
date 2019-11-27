# // Copyright (C) 2019 Brendan Knapp
# // This file is part of tweetio.
# // 
# // This program is free software: you can redistribute it and/or modify
# // it under the terms of the GNU General Public License as published by
# // the Free Software Foundation, either version 3 of the License, or
# // (at your option) any later version.
# // 
# // This program is distributed in the hope that it will be useful,
# // but WITHOUT ANY WARRANTY; without even the implied warranty of
# // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# // GNU General Public License for more details.
# // 
# // You should have received a copy of the GNU General Public License
# // along with this program.  If not, see <https://www.gnu.org/licenses/>.

#' Build an `sf` Object of Tweets
#' 
#' @template param-tweet_df
#' @param geom_col Which column to use as the active `geometry` column in result:
#' `"bbox_coords"`, `"quoted_bbox_coords"`,`"retweet_bbox_coords"`, or `"all"`.
#' @template param-as_tibble
#' @param .geometry Name of output's geometry column. Intended for internal use only. 
#' @template param-dots
#' 
#' @return [sf::st_sf()] 
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
#'
#' @importFrom data.table %chin% data.table is.data.table
#' 
#' @export
as_tweet_sf <- function(tweet_df, 
                        geom_col = c("bbox_coords", "quoted_bbox_coords",
                                     "retweet_bbox_coords",
                                     "ist_complex_value",  "all"), as_tibble = FALSE,
                        .geometry = NULL,
                        ...) {
  # silence R CMD Check NOTE
  geometry <- NULL
  ..geom_col <- NULL
  metadata <- NULL
  ##########################
  
  
  if (!requireNamespace("sf", quietly = TRUE)) {
    stop("The {sf} package is required for this functionality", call. = FALSE)
  }
  
  geom_col <- match.arg(geom_col, c("bbox_coords", "quoted_bbox_coords",
                                    "retweet_bbox_coords", "ist_complex_value",
                                    "all"))
  
  if (is.null(.geometry)) {
    .geometry <- geom_col
  }

  if (!is.data.table(tweet_df)) {
    tweet_df <- data.table(tweet_df)
  }
  
  if (geom_col == "all") {
    valid_cols <- c(
      intersect(c("bbox_coords", "quoted_bbox_coords", "retweet_bbox_coords"),
                names(tweet_df)),
      "ist_complex_value"
    )
  
    out <- lapply(valid_cols, function(.x) {
      res <- as_tweet_sf(tweet_df, .x, as_tibble = as_tibble, .geometry = "geometry", ...)
      if (!is.null(res) && nrow(res) > 0L) {
        res[["which_geom"]] <- .x
      }
      res
    })
    
    # any_multipolygons <- .map_lgl(out, function(.x) {
    #   "MULTIPOLYGON" %in% sf::st_geometry(.x)
    # })
    # 
    # if (any_multipolygons) {
    #   out <- lapply(out, sf::st_cast("MULTIPOLYGON"))
    # }

    return(do.call(rbind, .discard(.compact(out), function(.x) nrow(.x) == 0L)))
  }
  
  if (geom_col == "ist_complex_value") {
    if (!"metadata" %in% names(tweet_df)) {
      return(NULL)
    } else if (!"ist_complex_value" %in% names(tweet_df$metadata[[1L]])) {
        return(NULL)
    }
    
    if (!requireNamespace("geojsonsf", quietly = TRUE)) {
      stop("{geojsonsf} is required for this functionality.", call. = FALSE)
    }
    
    rows_to_keep <- .map_lgl(tweet_df$metadata, function(.x) {
      length(
        unique( .x$ist_complex_value[ !is.na(.x$ist_complex_value) ] )
        ) == 1L
    })
    
    if (length(rows_to_keep) == 0L) {
      return(NULL)
    }
    
    filtered_rows <- tweet_df[rows_to_keep]
    
    with_sfc_col <- filtered_rows[
      , (.geometry) := sf::st_sfc(
        
        unlist(
          
          lapply(metadata, function(.x) {
            val <- unique( .x$ist_complex_value[ !is.na(.x$ist_complex_value) ] )
            geojsonsf::geojson_sfc(val)
          }),
          
          recursive = FALSE,
          use.names = FALSE
        ),
        
      crs = 4326L
    )]
    
    out <- sf::st_sf(with_sfc_col, stringsAsFactors = FALSE)
    
    return(.finalize_df(out, as_tibble = as_tibble))
  }
  
  if (!geom_col %chin% names(tweet_df)) {
    stop(geom_col, " is not a valid column in `tweet_df`.", call. = FALSE)
  }
  
  rows_to_keep <- is_valid_bbox(tweet_df[[geom_col]]) 
  init <- tweet_df[rows_to_keep]

  if (nrow(init) == 0L) {
    return(NULL)
  }
  
  init[, (.geometry) := sf::st_sfc(prep_bbox(init[[geom_col]]), crs = 4326L)]
  
  out <- sf::st_sf(init, stringsAsFactors = FALSE)
  
  .finalize_df(out, as_tibble = as_tibble)
}

