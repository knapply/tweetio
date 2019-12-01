# # // Copyright (C) 2019 Brendan Knapp
# # // This file is part of tweetio.
# # // 
# # // This program is free software: you can redistribute it and/or modify
# # // it under the terms of the GNU General Public License as published by
# # // the Free Software Foundation, either version 3 of the License, or
# # // (at your option) any later version.
# # // 
# # // This program is distributed in the hope that it will be useful,
# # // but WITHOUT ANY WARRANTY; without even the implied warranty of
# # // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# # // GNU General Public License for more details.
# # // 
# # // You should have received a copy of the GNU General Public License
# # // along with this program.  If not, see <https://www.gnu.org/licenses/>.
# 
# 
# write_graphml <- function(g, file_path, na_numbers_as = -1,
#                           na_characters_as = "", drop_na_attrs = TRUE) {
#   if (!requireNamespace("igraph", quietly = TRUE)) {
#     stop("{igraph} package is required for this functionality.", call. = FALSE)
#   }
# 
#   if (!inherits(g, "igraph")) {
#     stop("`g` must be an <igraph>.", call. = FALSE)
#   }
#   if (!is.character(file_path) || length(file_path) != 1L) {
#     stop("`path` must be a <character> scalar.", call. = FALSE)
#   }
#   if (!is.numeric(na_numbers_as) || length(na_numbers_as) != 1L) {
#     stop("`na_numbers_as` must be `NULL` or a scalar <numeric>.",
#          call. = FALSE)
#   }
#   if (!is.null(na_characters_as)) {
#     if (!is.character(na_characters_as) || length(na_characters_as) != 1L) {
#       stop("`na_characters_as` must be `NULL` or a scalar <character>.",
#            call. = FALSE)
#     }
#   }
#   
#   proto_net <-.igraph_as_data_frame(g)
#   # return(proto_net)
#   
#   
# 
#   edge_attrs_to_delete <- intersect(
#     c("contributors_enabled", "account_lang",
#       grep("^(quoted|reply_to|retweet)", names(proto_net$edges), value = TRUE)),
#     names(proto_net$edges)
#   )
#   
#   proto_net$edges[, (edge_attrs_to_delete) := NULL]
#   # return(proto_net$edges)
#   
#   # return(edge_attrs_to_delete)
#   for (i in seq_along(edge_attrs_to_delete)) {
#     g <- igraph::delete_edge_attr(g, name = edge_attrs_to_delete[[i]])
#   }
#   
#   
#   # TODO figure out why I was able to add POSIXct attributes but then cannot change them
#   # maybe related... https://github.com/igraph/rigraph/issues/251
#   
#   # possible_dttm_cols <- c("timestamp_ms", "created_at", "account_created_at",
#   #                         "retweet_created_at", "quoted_created_at")
#   # node_dttm_cols <- intersect(igraph::vertex_attr_names(g), possible_dttm_cols)
#   # if (!.is_empty(node_dttm_cols)) {
#   #   for (i in seq_along(node_dttm_cols)) {
#   #     # igraph won't replace date times...
#   #     temp <- as.character(igraph::vertex_attr(g, node_dttm_cols[[i]]))
#   #     g <- igraph::delete_vertex_attr(g, node_dttm_cols[[i]])
#   #     igraph::vertex_attr(g, node_dttm_cols[[i]]) <- temp
#   #   }
#   # }
#   # edge_dttm_cols <- intersect(igraph::edge_attr_names(g), possible_dttm_cols)
#   # if (.is_empty(edge_dttm_cols)) {
#   #   for (i in seq_along(node_dttm_cols)) {
#   #     temp <- as.character(igraph::edge_attr(g, edge_dttm_cols[[i]]))
#   #     g <- igraph::delete_edge_attr(g, edge_dttm_cols[[i]])
#   #     igraph::edge_attr(g, edge_dttm_cols[[i]]) <- temp
#   #   }
#   # }
#   
#   
#   if (!is.null(na_characters_as)) {
#     igraph::vertex_attr(g) <- lapply(igraph::vertex_attr(g), function(.x) {
#       if (!is.character(.x)) return(.x)
#       .x[is.na(.x)] <- na_characters_as
#       .x
#     })
#     igraph::edge_attr(g) <- lapply(igraph::edge_attr(g), function(.x) {
#       if (!is.character(.x)) return(.x)
#       .x[is.na(.x)] <- na_characters_as
#       .x
#     })
#   }
# 
#   if (drop_na_attrs) {
#     node_all_na_attrs <- which(
#       .map_lgl(igraph::vertex_attr(g), function(.x) all(is.na(.x)))
#     )
#     if (!.is_empty(node_all_na_attrs)) {
#       g <- igraph::delete_vertex_attr(g, name = names(node_all_na_attrs))
#     }
# 
#     edge_all_na_attrs <- which(
#       .map_lgl(igraph::edge_attr(g), function(.x) all(is.na(.x)))
#     )
# 
#     if (!.is_empty(edge_all_na_attrs)) {
#       g <- igraph::delete_vertex_attr(g, name = names(edge_all_na_attrs))
#     }
#   }
# 
#   if (!is.null(na_numbers_as)) {
#     igraph::vertex_attr(g) <- lapply(igraph::vertex_attr(g), function(.x) {
#       if (!is.numeric(.x)) return(.x)
#       .x[is.na(.x)] <- na_numbers_as
#       .x
#     })
#   }
# 
#   igraph::write_graph(g, file = path.expand(file_path), format = "graphml")
# }
# 
# 
