# as_sna_proto_net <- function(tweet_df, relations = c("mention" ,"retweet",
#                                                      "reply_to", "quoted"),
#                              ...) {
# 
#   relations <- match.arg(relations, c("mentions" ,"retweet", "reply_to", "quoted"),
#                          several.ok = TRUE)
#   
#   targets <- intersect(paste0(relations, "_user_id"), names(tweet_df))
#   names(targets) <- targets
#   
#   if (length(relations) == 0L) {
#     stop("No `relations` columns found.", call. = FALSE)
#   }
#   
#   edges <- rbindlist(
#     lapply(targets, function(x) {
#       edge_cols <- c("user_id", x, "status_id")
#       
#       res <- na.omit(tweet_df, cols = x)[, ..edge_cols]
#       setnames(res, c("source", "target", "status_id"))
# 
#       if (is.list(res[["target"]])) {
#         res <- setDT(
#           unnest_entities_(tracker = res[["status_id"]], 
#                             source = res[["source"]],
#                             target = res[["target"]],
#                             col_names = c("source", "target", "status_id"))
#         )
#       }
# 
#       res[, relation := sub("_user_id$", "", x)]
#     }),
#     use.names = TRUE
#   )
#   
#   structure(
#     list(edges = edges[tweet_df, on = "status_id", nomatch = 0],
#          nodes = build_user_df(tweet_df)),
#     attr = "proto_net"
#   )
# }
# 
# 
# 
# 
# 
# 
# 
# graph_from_proto_net <- function(proto_net) {
#   el <- matrix(NA_integer_, nrow = 2L, ncol = nrow(proto_net$edges))
#   el[1L, ] <- match(proto_net$edges$source, proto_net$nodes$user_id)
#   el[2L, ] <- match(proto_net$edges$target, proto_net$nodes$user_id)
#   
#   
#   out <- igraph::make_empty_graph(n = nrow(proto_net$nodes), directed = TRUE)
#   
#   out <- igraph::add_edges(graph = out, edges = el)
#   
#   is_non_empty_atomic <- function(x) {
#     is.atomic(x) && any(!is.na(x))
#   }
#   
#   valid_node_attrs <- names(proto_net$nodes
#                             )[vapply(proto_net$nodes, is_non_empty_atomic, logical(1L))]
#   
#   igraph::vertex_attr(out) <- proto_net$nodes[, ..valid_node_attrs]
#   igraph::vertex_attr(out, "name") <- proto_net$nodes[, user_id]
# 
#   valid_edge_attrs <- setdiff(
#     names(proto_net$edges)[vapply(proto_net$edges, is_non_empty_atomic, logical(1L))],
#     c("source", "target",
#       grep("^(quoted|retweet|reply_to)_", names(proto_net$edges), value = TRUE))
#   )
#   
#   igraph::edge_attr(out) <- proto_net$edges[, ..valid_edge_attrs]
# }