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

#' Write Gephi-Friendly .graphml Files
#' 
#' Simple, safe transformation of attributes to values with which Gephi will cooperate.
#' 
#' @param g `igraph::graph()` object
#' @template param-file_path
#' @param na_numbers_as `numeric(1L)`, Default: `-1`. Value to replace
#'  `NA_real_`/`NA_integer_`s in the resulting file.
#' @param na_characters_as `character(1L)`, Default: `""`. Value to replace 
#' `NA_character_`s in the resulting file.
#' @template param-dots
#' 
#' @template author-bk
#' 
#' @examples 
#' path_to_tweet_file <- example_tweet_file()
#' 
#' tweet_df <- read_tweets(file_path = path_to_tweet_file)
#' 
#' tweet_graph <- as_igraph(tweet_df)
#' tweet_graph
#' 
#' graphml_path <- tempfile(fileext = ".graphml")
#' graphml_path
#' 
#' write_graphml(tweet_graph, file_path = graphml_path) 
#' 
#' @importFrom data.table fifelse
#' 
#' @export
write_graphml <- function(g, file_path, na_numbers_as = -1,
                          na_characters_as = "", ...) {
  if (!requireNamespace("igraph", quietly = TRUE)) {
    stop("{igraph} package is required for this functionality.", call. = FALSE)
  }

  if (!inherits(g, "igraph")) {
    stop("`g` must be an <igraph>.", call. = FALSE)
  }
  if (!is.character(file_path) || length(file_path) != 1L) {
    stop("`path` must be a <character> scalar.", call. = FALSE)
  }
  if (!is.numeric(na_numbers_as) || length(na_numbers_as) != 1L) {
    stop("`na_numbers_as` must be `NULL` or a scalar <numeric>.",
         call. = FALSE)
  }
  if (!is.null(na_characters_as)) {
    if (!is.character(na_characters_as) || length(na_characters_as) != 1L) {
      stop("`na_characters_as` must be `NULL` or a scalar <character>.",
           call. = FALSE)
    }
  }
  
  node_attrs_to_drop <- intersect(
    igraph::vertex_attr_names(g),
    c(names(which(.map_lgl(igraph::vertex_attr(g), is.list))),
      "profile_banner_url", "profile_image_url", "bbox_coords")
  )
  for (i in seq_along(node_attrs_to_drop)) {
    g <- igraph::delete_vertex_attr(g, node_attrs_to_drop[[i]])
  }
  
  igraph::vertex_attr(g) <- .map_if(
    igraph::vertex_attr(g), is.numeric, 
    function(.x) fifelse(is.na(.x), na_numbers_as, .x)
  )
  igraph::vertex_attr(g) <- .map_if(
    igraph::vertex_attr(g), is.character, 
    function(.x) fifelse(is.na(.x) | .x %chin% c("{}", "[]"), na_characters_as, .x)
  )
  igraph::vertex_attr(g) <- .map_if(igraph::vertex_attr(g),
                                    function(.x) inherits(.x, "POSIXct"), 
                                    function(.x) {
                                      .x <- as.character(.x)
                                      .x[is.na(.x)] <- na_characters_as
                                      .x
                                    })
  
  
  edge_attrs_to_drop <- intersect(
    igraph::edge_attr_names(g),
    c(names(which(.map_lgl(igraph::edge_attr(g), is.list))),
      "status_type")
  )
  for (i in seq_along(edge_attrs_to_drop)) {
    g <- igraph::delete_edge_attr(g, edge_attrs_to_drop[[i]])
  }
  
  igraph::edge_attr(g) <- .map_if(
    igraph::edge_attr(g), is.numeric, 
    function(.x) fifelse(is.na(.x), na_numbers_as, .x)
  )
  igraph::edge_attr(g) <- .map_if(
    igraph::edge_attr(g), is.character, 
    function(.x) fifelse(is.na(.x) | .x %chin% c("{}", "[]"), na_characters_as, .x)
  )
  igraph::edge_attr(g) <- .map_if(igraph::edge_attr(g),
                                  function(.x) inherits(.x, "POSIXct"), 
                                  function(.x) {
                                    .x <- as.character(.x)
                                    .x[is.na(.x)] <- ""
                                    .x
                                  })
  
  
  igraph::write_graph(g, file = path.expand(file_path), format = "graphml")
}


