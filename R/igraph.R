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

#' @importFrom data.table data.table rbindlist setcolorder setnames
as_sna_proto_net <- function(tweet_df, relations = c("mention" ,"retweet",
                                                     "reply_to", "quoted"),
                             as_tibble = FALSE,
                             ...) {
  # silence R CMD Check NOTE #############################################################
  relation <- NULL
  ########################################################################################
  if (!.is_dt(tweet_df)) {
    tweet_df <- as.data.table(tweet_df)
  }
  
  relations <- match.arg(relations, c("mentions" ,"retweet", "reply_to", "quoted"),
                         several.ok = TRUE)
  
  targets <- .set_names(
    intersect(paste0(relations, "_user_id"), names(tweet_df))
  )
  
  if (length(relations) == 0L) {
    stop("No `relations` columns found.", call. = FALSE)
  }
  
  edge_by_status_type <- lapply(targets, function(x) {
    edge_cols <- c("user_id", x, "status_id")

    res <- tweet_df[!is.na(get(x)), edge_cols, with = FALSE]

    setnames(res, c("from", "to", "status_id"))

    if (is.list(res[["to"]])) {
      res <- setDT(
        unnest_entities_impl(tracker = res[["status_id"]],
                             source = res[["from"]],
                             target = res[["to"]],
                             col_names = c("from", "to", "status_id"))
      )
    }

    res[, relation := sub("_user_id$", "", x)]
  })

  edges <- rbindlist(edge_by_status_type, use.names = TRUE, fill = TRUE
                     )[tweet_df, on = "status_id", nomatch = 0]
  first_edge_cols <- c("from", "to", "relation", "status_id")
  new_edge_col_order <- c(first_edge_cols, setdiff(first_edge_cols, names(edges)))
  setcolorder(edges, new_edge_col_order)
  
  # edges <- jsonify_list_cols(edges, copy = FALSE)
  # nodes <- jsonify_list_cols(build_user_df(tweet_df, copy = FALSE))
  nodes <- extract_users(tweet_df)
  
  structure(
    list(edges = .finalize_df(edges, as_tibble = as_tibble), 
         nodes = .finalize_df(nodes, as_tibble = as_tibble)),
    class = "proto_net"
  )
}




as_sna_igraph <- function(x, ...) {
  UseMethod("as_sna_igraph")
}

as_sna_igraph.default <- function(x, relations = c("mention" ,"retweet",
                                                   "reply_to", "quoted"),
                                  ...) {
  as_sna_igraph(
    as_sna_proto_net(x, relations = relations, ...)
  )
}

#' @importFrom data.table copy setDT
#' @importFrom stringi stri_detect_regex
as_sna_igraph.proto_net <- function(proto_net, copy = TRUE) {
  # silence R CMD Check NOTE #############################################################
  .SD <- NULL
  ########################################################################################
  if (!requireNamespace("igraph", quietly = TRUE)) {
    stop("{igraph} package is required for this functionality.", call. = FALSE)
  }
  
  # edges <- as.data.frame(proto_net$edges)
  # nodes <- as.data.frame(proto_net$nodes)
  
  if (copy) {
    proto_net <- copy(proto_net)
  }
  
  if (!is.data.table(proto_net$edges)) {
    setDT(proto_net$edges)
  }
  if (!is.data.table(proto_net$nodes)) {
    setDT(proto_net$nodes)
  }

  el <- matrix(NA_integer_, nrow = 2L, ncol = nrow(proto_net$edges))
  el[1L, ] <- match(proto_net$edges$from, proto_net$nodes$user_id)
  el[2L, ] <- match(proto_net$edges$to, proto_net$nodes$user_id)
  proto_net$edges[, c("from", "to") := NULL]
  
  edge_dttm_cols <- .match_col_names(proto_net$edges, inherits, "POSIXct")
  proto_net$edges <- proto_net$edges[, (edge_dttm_cols) := lapply(.SD, as.character),
                                     .SDcols = edge_dttm_cols]
  
  node_dttm_cols <- .match_col_names(proto_net$nodes, inherits, "POSIXct")
  proto_net$nodes <- proto_net$nodes[, (node_dttm_cols) := lapply(.SD, as.character),
                                     .SDcols = node_dttm_cols]
  
  if ("name" %in% names(proto_net$nodes)) {
    setnames(proto_net$nodes, old = "name", new = "name_on_profile")
  }
  proto_net$nodes <- jsonify_list_cols(proto_net$nodes)

  valid_edge_attrs <- names(proto_net$edges
                            )[!stri_detect_regex(names(proto_net$edges),
                                                 "^(quoted|retweet|reply_to)_")]
  # proto_net$edges <- jsonify_list_cols(proto_net$edges)[, ..valid_edge_attrs]
  
  
  out <- igraph::make_empty_graph(n = nrow(proto_net$nodes), directed = TRUE)
  out <- igraph::add_edges(graph = out, edges = el)
  igraph::vertex_attr(out) <- as.list(proto_net$nodes)
  # igraph::vertex_attr(out, "name") <- proto_net$nodes$user_id
  igraph::edge_attr(out) <- as.list(proto_net$edges)

  out
}

#' @importFrom data.table as.data.table setDT
.igraph_as_data_frame <- function(g, edges_are_named = FALSE, ...) {
  if (!requireNamespace("igraph", quietly = TRUE)) {
    stop("{igraph} package is required for this functionality.", call. = FALSE)
  }

  el <- igraph::as_edgelist(g, names = edges_are_named)
  colnames(el) <- c("from", "to")

  edges <- cbind(as.data.table(el), setDT(igraph::edge_attr(g)))
  nodes <- setDT(igraph::vertex_attr(g))

  list(edges = edges, nodes = nodes)
}
