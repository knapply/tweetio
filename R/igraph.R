#' Convert Various Objects to `igraph` graphs.
#' 
#' @param x Tweet data frame or `proto_net`.
#' @template param-target_class
#' @template param-all_status_data
#' @template param-all_user_data
#' @template param-dots
#' 
#' @seealso [as_proto_net()], [as_tweet_network()]
#' 
#' @template author-bk
#' 
#' @examples 
#' path_to_tweet_file <- example_tweet_file()
#' tweet_df <- read_tweets(path_to_tweet_file)
#' 
#' tweet_df %>% 
#'   as_tweet_igraph()
#'   
#' tweet_df %>% 
#'   as_proto_net() %>% 
#'   as_tweet_igraph()
#' 
#' tweet_df %>% 
#'   as_tweet_igraph(all_status_data = TRUE)
#'   
#' tweet_df %>% 
#'   as_tweet_igraph(all_user_data = TRUE)
#'
#' @export
as_tweet_igraph <- function(x,
                            target_class = c("user", "hashtag", "url", "media"),
                            all_status_data = FALSE,
                            all_user_data = FALSE,
                            ...) {
  UseMethod("as_tweet_igraph")
}

# TODO deprecate `as_igraph()` in favor of `as_tweet_igraph()`
#' @rdname as_tweet_igraph
#' 
#' @export
as_igraph <- as_tweet_igraph 

#' @rdname as_tweet_igraph
#' 
#' @importFrom data.table %chin%
#' 
#' @export
as_tweet_igraph.proto_net <- function(x, ...) {
  if (!requireNamespace("igraph", quietly = TRUE)) {
    stop("{igraph} package is required for this funcitonality.", call. = FALSE)
  }
  
  is_directed <- attr(x, "target_class", exact = TRUE) == "user"

  el <- matrix(
    match(c(x$edges$from, x$edges$to), x$nodes$name),
    nrow = 2L, byrow = TRUE
  )
  
  out <- igraph::add_edges(
    igraph::make_empty_graph(n = nrow(x$nodes),
                             directed = is_directed),
    el
  )

  igraph::edge_attr(out) <- as.list(x$edges[, -(1L:2L)])
  igraph::vertex_attr(out) <- as.list(x$nodes)
  
  # add bipartite attr if targets aren't users
  if (!is.null(attr(x, "target_class")) && attr(x, "target_class") != "user") {
    igraph::vertex_attr(out, "type"
                        ) <- igraph::vertex_attr(out, "name") %chin% x$edges$from
  }

  out
}


#' @rdname as_tweet_igraph
#' 
#' @export
as_tweet_igraph.data.frame <- function(x,
                                       target_class = c("user", "hashtag", 
                                                        "url", "media"),
                                       all_status_data = FALSE,
                                       all_user_data = FALSE,
                                       ...) {
  init <- as_proto_net(x, 
                       target_class = target_class,
                       all_status_data = all_status_data,
                       all_user_data = all_user_data,
                       as_tibble = FALSE,
                       ...)
  
  as_tweet_igraph(init)
}

