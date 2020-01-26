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
#' @param ... Arguments passed to `as_proto_net()`.
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
as_tweet_network <- function(x, ...) {
  UseMethod("as_tweet_network")
}


#' @rdname as_tweet_network
#' 
#' @export
as_tweet_network.proto_net <- function(x, ...) {
  if (!requireNamespace("network", quietly = TRUE)) {
    stop("The {network} package is required for this funcitonality.", 
         call. = FALSE)
  }
  
  network::as.network(x = x[["edges"]], vertices = x[["nodes"]],
                      loops = TRUE, multiple = TRUE)
}


#' @rdname as_tweet_network
#' 
#' @export
as_tweet_network.data.frame <- function(x, ...) {
  as_tweet_network(as_proto_net(x, ...))
}

