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


#' Convert Various Objects to `network` graphs.
#' 
#' @param x Tweet data frame or `proto_net`.
#' @template param-target_class
#' @template param-all_status_data
#' @template param-all_user_data
#' @template param-dots
#' 
#' @seealso [as_proto_net()], [as_tweet_igraph()]
#' 
#' @template author-bk
#' 
#' @examples 
#' path_to_tweet_file <- example_tweet_file()
#' tweet_df <- read_tweets(path_to_tweet_file)
#' 
#' tweet_df %>% 
#'   as_tweet_network()
#'   
#' tweet_df %>% 
#'   as_proto_net() %>% 
#'   as_tweet_network()
#'   
#' tweet_df %>% 
#'   as_tweet_network(all_status_data = TRUE)
#'   
#' tweet_df %>% 
#'   as_tweet_network(all_user_data = TRUE)
#' 
#' @export
as_tweet_network <- function(x, 
                             target_class = target_class,
                             all_status_data = all_status_data,
                             all_user_data = all_user_data, 
                             ...) {
  UseMethod("as_tweet_network")
}


#' @rdname as_tweet_network
#' 
#' @importFrom data.table := %chin%
#' @importFrom utils getFromNamespace
#' 
#' @export
as_tweet_network.proto_net <- function(x, ...) {
  if (!requireNamespace("network", quietly = TRUE)) {
    stop("The {network} package is required for this funcitonality.", 
         call. = FALSE)
  }
  
  as_nw <- tryCatch(
    getFromNamespace("as.network.data.frame", ns = "network"),
    error = function(e) .as.network.data.frame
  )
  
  # silence R CMD Check NOTE =============================================================
  name <- NULL
  is_actor <- NULL
  # ======================================================================================
  
  if (attr(x, "target_class", exact = TRUE) != "user") {
    if (!.is_dt(x$nodes)) {
      x$nodes <- .as_dt(x$nodes)
    }
    
    x$nodes[, is_actor := name %chin% x$edges$from]
    is_bipartite <- TRUE
  } else {
    is_bipartite <- FALSE
  }
  
  as_nw(
    x = x[["edges"]], 
    vertices = x[["nodes"]],
    directed = !is_bipartite,
    loops = !is_bipartite,
    multiple = TRUE,
    bipartite = is_bipartite
  )
}


#' @rdname as_tweet_network
#' 
#' @export
as_tweet_network.data.frame <- function(x, 
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
  
  as_tweet_network(init)
}

