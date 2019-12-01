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


#' Convert Various Objects to `igraph` graphs.
#' 
#' @param x Tweet data frame or `proto_net`.
#' @param ... Arguments passed to `as_proto_net()`.
#' 
#' @template author-bk
#' 
#' @examples 
#' path_to_tweet_file <- example_tweet_file()
#' tweet_df <- read_tweets(path_to_tweet_file)
#' 
#' tweet_df %>% 
#'   as_igraph()
#'   
#' tweet_df %>% 
#'   as_proto_net() %>% 
#'   as_igraph()
#' 
#' @export
as_igraph <- function(x, ...) {
  UseMethod("as_igraph")
}


#' @rdname as_igraph
#' 
#' @importFrom data.table %chin%
#' 
#' @export
as_igraph.proto_net <- function(x, ...) {
  if (!requireNamespace("igraph", quietly = TRUE)) {
    stop("{igraph} package is required for this funcitonality.", call. = FALSE)
  }

  el <- matrix(
    match(c(x$edges$from, x$edges$to), x$nodes$name),
    nrow = 2L, byrow = TRUE
  )
  
  out <- igraph::add_edges(
    igraph::make_empty_graph(n = nrow(x$nodes)),
    el
  )
  
  # x$edges[, -(1:2L)]
  
  igraph::edge_attr(out) <- as.list(x$edges[, -(1L:2L)])
  igraph::vertex_attr(out) <- as.list(x$nodes)
  
  # add bipartite attr if targets aren't users
  if (!is.null(attr(x, "target_class")) && attr(x, "target_class") != "user") {
    igraph::vertex_attr(out, "type"
                        ) <- igraph::vertex_attr(out, "name") %chin% x$edges$from
  }

  out
}


#' @rdname as_igraph
#' 
#' @export
as_igraph.data.frame <- function(x, ...) {
  as_igraph(as_proto_net(x, ...))
}

