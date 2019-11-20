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


as_sna_proto_net <- function(tweet_df, relations = c("mention" ,"retweet",
                                                     "reply_to", "quoted"),
                             jsonify_list_cols = TRUE,
                             ...) {
  
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

    res <- na.omit(tweet_df, cols = x
                   )[, ..edge_cols]

    setnames(res, c("source", "target", "status_id"))

    if (is.list(res[["target"]])) {
      res <- setDT(
        unnest_entities_impl(tracker = res[["status_id"]],
                             source = res[["source"]],
                             target = res[["target"]],
                             col_names = c("source", "target", "status_id"))
      )
    }

    res[, relation := sub("_user_id$", "", x)]
  })

  edges <- rbindlist(edge_by_status_type, use.names = TRUE, fill = TRUE
                     )[tweet_df, on = "status_id", nomatch = 0]
  
  # edges <- jsonify_list_cols(edges, copy = FALSE)
  # nodes <- jsonify_list_cols(build_user_df(tweet_df, copy = FALSE))
  nodes <- build_user_df(tweet_df)
  
  structure(
    list(edges = edges, nodes = nodes),
    attr = "proto_net"
  )
}







as_sna_igraph <- function(proto_net) {
  if (!requireNamespace("igraph", quietly = TRUE)) {
    stop("{igraph} package is required for this functionality.", call. = FALSE)
  }

  el <- matrix(NA_integer_, nrow = 2L, ncol = nrow(proto_net$edges))
  el[1L, ] <- match(proto_net$edges$source, proto_net$nodes$user_id)
  el[2L, ] <- match(proto_net$edges$target, proto_net$nodes$user_id)


  out <- igraph::make_empty_graph(n = nrow(proto_net$nodes), directed = TRUE)

  out <- igraph::add_edges(graph = out, edges = el)

  
  
  node_dttm_cols <- .match_col_names(proto_net$nodes, inherits, "POSIXct")
  proto_net$nodes <- proto_net$nodes[, (node_dttm_cols) := lapply(.SD, as.character),
                                     .SDcols = node_dttm_cols]
  if ("name" %in% names(proto_net$nodes)) {
    setnames(proto_net$nodes, old = "name", new = "name_on_profile")
  }
  # valid_node_attrs <- .match_col_names(proto_net$nodes, .is_atomic_with_non_nas)
  proto_net$nodes <- jsonify_list_cols(proto_net$nodes)
  igraph::vertex_attr(out) <- proto_net$nodes #[, ..valid_node_attrs]
  igraph::vertex_attr(out, "name") <- proto_net$nodes$user_id


  

  edge_dttm_cols <- .match_col_names(proto_net$edges, inherits, "POSIXct")
  proto_net$edges <- proto_net$edges[, (edge_dttm_cols) := lapply(.SD, as.character),
                                     .SDcols = edge_dttm_cols]
  # valid_edge_attrs <- .match_col_names(proto_net$edges, !valid_edge_attrs)
  # valid_edge_attrs <- setdiff(
  #   .match_col_names(proto_net$edges, .is_atomic_with_non_nas),
  #   c("source", "target",
  #     grep("^(quoted|retweet|reply_to)_", names(proto_net$edges), value = TRUE))
  # )
  valid_edge_attrs <- names(proto_net$edges
                            )[!grepl("^(quoted|retweet|reply_to)_", names(proto_net$edges))]
  proto_net$edges <- jsonify_list_cols(proto_net$edges)[, ..valid_edge_attrs]
  igraph::edge_attr(out) <- proto_net$edges

  out
}