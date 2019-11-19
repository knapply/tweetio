# // Copyright (C) 2019 Brendan Knapp
# // This file is part of tweetio
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


# write_graphml <- function(g, path, na_numbers_as = -1, 
#                           na_characters_as = "", drop_na_attrs = TRUE) {
#   if (!inherits(g, "igraph")) {
#     stop("`g` must be an <igraph>.", call. = FALSE)
#   }
#   if (!is.character(path) | length(path) != 1L) {
#     stop("`path` must be a <character> scalar.", call. = FALSE)
#   }
#   if (!is.null(na_numbers_as)) {
#     if (!is.numeric(na_numbers_as) | length(na_numbers_as) != 1L) {
#       stop("`na_numbers_as` must be `NULL` or a scalar <numeric>.", 
#            call. = FALSE)
#     }
#   }
#   if (!is.null(na_characters_as)) {
#     if (!is.character(na_characters_as) | length(na_characters_as) != 1L) {
#       stop("`na_characters_as` must be `NULL` or a scalar <character>.", 
#            call. = FALSE)
#     }
#   }
#   
#   node_attrs_to_delete <- intersect(
#     c("profile_banner_url", "profile_image_url", "protected"),
#     vertex_attr_names(g)
#   )
#   for (i in seq_along(node_attrs_to_delete)) {
#     g <- delete_vertex_attr(g, name = node_attrs_to_delete[[i]])
#   }
#   
#   edge_attrs_to_delete <- intersect(
#     c("ist_metadata", "contributors_enabled", "account_lang",
#       "timestamp_ms", 
#       grep("^(quoted|reply_to|retweet)", edge_attr_names(g), value = TRUE)),
#     edge_attr_names(g)
#   )
#   for (i in seq_along(edge_attrs_to_delete)) {
#     g <- delete_edge_attr(g, name = edge_attrs_to_delete[[i]])
#   }
#   
# 
#   node_list_attrs <- names(which(purrr::map_lgl(vertex_attr(g), is.list)))
#   for (i in seq_along(node_list_attrs)) {
#     g <- delete_vertex_attr(g, node_list_attrs[[i]])
#   }
#   
#   edge_list_attrs <- names(which(purrr::map_lgl(edge_attr(g), is.list)))
#   for (i in seq_along(edge_list_attrs)) {
#     g <- delete_edge_attr(g, edge_list_attrs[[i]])
#   }
#   
#   if (drop_na_attrs) {
#     node_all_na_attrs <- which(
#       purrr::map_lgl(vertex_attr(g), function(.x) all(is.na(.x)))
#     )
#     if (!purrr::is_empty(node_all_na_attrs)) {
#       g <- delete_vertex_attr(g, name = names(node_all_na_attrs))
#     }
#     
#     edge_all_na_attrs <- which(
#       purrr::map_lgl(edge_attr(g), function(.x) all(is.na(.x)))
#     )
#     if (!purrr::is_empty(edge_all_na_attrs)) {
#       g <- delete_vertex_attr(g, name = names(edge_all_na_attrs))
#     }
#   }
#   
#   if (!is.null(na_numbers_as)) {
#     vertex_attr(g) <- lapply(vertex_attr(g), function(.x) {
#       if (!is.numeric(.x)) return(.x)
#       .x[is.na(.x)] <- na_numbers_as
#       .x
#     })
#   }
#   
#   if (!is.null(na_characters_as)) {
#     vertex_attr(g) <- lapply(vertex_attr(g), function(.x) {
#       if (!is.character(.x)) return(.x)
#       .x[is.na(.x)] <- na_characters_as
#       
#       gsub("[[:cntrl:]]", "", .x)
#     })
#   }
#   
#   write_graph(g, file = path, format = "graphml")
# }
# 
