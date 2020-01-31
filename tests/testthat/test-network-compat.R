context("as.network")

suppressPackageStartupMessages(library(network))



test_that("simple networks are built correctly", {
  simple_edge_df <- data.frame(.tail = c("b", "c", "c", "d", "d", "e"),
                               .head = c("a", "b", "a", "a", "b", "a"),
                               time = 1:6,
                               stringsAsFactors = FALSE)
  simple_vertex_df <- data.frame(vertex.names = letters[1:5],
                                 type = letters[1:5],
                                 stringsAsFactors = FALSE)
  expect_s3_class(
    .as.network.data.frame(x = simple_edge_df),
    "network"
  )
  expect_s3_class(
    .as.network.data.frame(x = simple_edge_df, vertices = simple_vertex_df),
    "network"
  )
  
  expect_true(
    is.directed(.as.network.data.frame(x = simple_edge_df))
  )
  expect_false(
    is.directed(.as.network.data.frame(x = simple_edge_df, directed = FALSE))
  )
  expect_false(
    has.loops(.as.network.data.frame(x = simple_edge_df))
  )
  expect_false(
    is.multiplex(.as.network.data.frame(x = simple_edge_df))
  )
  
  expect_equal(
    network.edgecount(.as.network.data.frame(x = simple_edge_df)),
    nrow(simple_edge_df)
  )
  expect_equal(
    network.size(.as.network.data.frame(x = simple_edge_df)),
    nrow(simple_vertex_df)
  )
  
  simple_g <- .as.network.data.frame(x = simple_edge_df, vertices = simple_vertex_df)
  delete.edges(simple_g, 2)
  expect_identical(
    `rownames<-`(simple_edge_df[-2, ], NULL),
    as.data.frame(simple_g)
  )
  
  delete.vertices(simple_g, 2)
  expect_identical(
    `rownames<-`(simple_vertex_df[-2, , drop = FALSE], NULL),
    as.data.frame(simple_g, unit = "vertices")
  )

})


test_that("simple and complex edge/vertex/R-object attributes are safely handled", {
  vertex_df <- data.frame(name = letters[5:1],
                          lgl_attr = c(TRUE, FALSE, TRUE, FALSE, TRUE),
                          int_attr = as.integer(seq_len(5)),
                          dbl_attr = as.double(seq_len(5)),
                          chr_attr = LETTERS[1:5],
                          date_attr = seq.Date(as.Date("2019-12-22"),
                                               as.Date("2019-12-26"),
                                               by = 1),
                          dttm_attr = as.POSIXct(
                            seq.Date(as.Date("2019-12-22"), as.Date("2019-12-26"), by = 1)
                          ),
                          stringsAsFactors = FALSE)
  attr(vertex_df$date_attr, "tzone") <- "PST"
  attr(vertex_df$dttm_attr, "tzone") <- "EST"
  vertex_df$list_attr <- replicate(5, LETTERS, simplify = FALSE)
  vertex_df$mat_list_attr <- replicate(5, as.matrix(mtcars), simplify = FALSE)
  vertex_df$df_list_attr <- replicate(5, mtcars, simplify = FALSE)
  vertex_df$sfg_attr <- list(
    structure(c(1, 2, 3), class = c("XY", "POINT", "sfg")),
    structure(1:10, .Dim = c(5L, 2L), class = c("XY", "MULTIPOINT", "sfg")),
    structure(1:10, .Dim = c(5L, 2L), class = c("XY", "LINESTRING", "sfg")),
    structure(list(structure(c(0, 10, 10, 0, 0, 0, 0, 10, 10, 0), .Dim = c(5L, 2L)), 
                   structure(c(1, 1, 2, 2, 1, 1, 2, 2, 1, 1), .Dim = c(5L, 2L)), 
                   structure(c(5, 5, 6, 6, 5, 5, 6, 6, 5, 5), .Dim = c(5L, 2L))), 
              class = c("XY", "MULTILINESTRING", "sfg")),
    structure(list(structure(c(0, 10, 10, 0, 0, 0, 0, 10, 10, 0),.Dim = c(5L, 2L)), 
                   structure(c(1, 1, 2, 2, 1, 1, 2, 2, 1, 1), .Dim = c(5L, 2L)),
                   structure(c(5, 5, 6, 6, 5, 5, 6, 6, 5, 5), .Dim = c(5L, 2L))), 
              class = c("XY", "POLYGON", "sfg"))
  )
  
  edge_df <- data.frame(from = c("b", "c", "c", "d", "d", "e"),
                        to = c("a", "b", "a", "a", "b", "a"),
                        lgl_attr = c(TRUE, FALSE, TRUE, FALSE, TRUE, FALSE),
                        int_attr = as.integer(seq_len(6)),
                        dbl_attr = as.double(seq_len(6)),
                        chr_attr = LETTERS[1:6],
                        date_attr = seq.Date(as.Date("2019-12-22"), as.Date("2019-12-27"),
                                             by = 1),
                        dttm_attr = as.POSIXct(
                          seq.Date(as.Date("2019-12-22"), as.Date("2019-12-27"), by = 1)
                        ),
                        stringsAsFactors = FALSE)
  attr(edge_df$date_attr, "tzone") <- "PST"
  attr(edge_df$dttm_attr, "tzone") <- "EST"
  edge_df$list_attr <- replicate(6, LETTERS, simplify = FALSE)
  edge_df$mat_list_attr <- replicate(6, as.matrix(mtcars), simplify = FALSE)
  edge_df$df_list_attr <- replicate(6, mtcars, simplify = FALSE)
  edge_df$sfg_attr <- list(
    structure(c(1, 2, 3), class = c("XY", "POINT", "sfg")),
    structure(1:10, .Dim = c(5L, 2L), class = c("XY", "MULTIPOINT", "sfg")),
    structure(1:10, .Dim = c(5L, 2L), class = c("XY", "LINESTRING", "sfg")),
    structure(list(structure(c(0, 10, 10, 0, 0, 0, 0, 10, 10, 0), .Dim = c(5L, 2L)), 
                   structure(c(1, 1, 2, 2, 1, 1, 2, 2, 1, 1), .Dim = c(5L, 2L)), 
                   structure(c(5, 5, 6, 6, 5, 5, 6, 6, 5, 5), .Dim = c(5L, 2L))), 
              class = c("XY", "MULTILINESTRING", "sfg")),
    structure(list(structure(c(0, 10, 10, 0, 0, 0, 0, 10, 10, 0),.Dim = c(5L, 2L)), 
                   structure(c(1, 1, 2, 2, 1, 1, 2, 2, 1, 1), .Dim = c(5L, 2L)),
                   structure(c(5, 5, 6, 6, 5, 5, 6, 6, 5, 5), .Dim = c(5L, 2L))), 
              class = c("XY", "POLYGON", "sfg")),
    structure(list(list(structure(c(0, 10, 10, 0, 0, 0, 0, 10, 10, 0), .Dim = c(5L, 2L)), 
                        structure(c(1, 1, 2, 2, 1, 1, 2, 2, 1, 1), .Dim = c(5L, 2L)), 
                        structure(c(5, 5, 6, 6, 5, 5, 6, 6, 5, 5), .Dim = c(5L, 2L))), 
                   list(structure(c(12, 22, 22, 12, 12, 12, 12, 22, 22, 12), .Dim = c(5L, 2L)), 
                        structure(c(13, 13, 14, 14, 13, 13, 14, 14, 13, 13), .Dim = c(5L, 2L))), 
                   list(structure(c(24, 34, 34, 24, 24, 24, 24, 34, 34, 24), .Dim = c(5L, 2L)))), 
              class = c("XY", "MULTIPOLYGON", "sfg"))
  )
  
  g_many_attrs <- .as.network.data.frame(edge_df, vertices = vertex_df)
  
  # edge attributes ======================================================================
  # bare atomic vectors
  expect_identical(
    get.edge.attribute(g_many_attrs, "lgl_attr"),
    edge_df$lgl_attr
  )
  expect_identical(
    get.edge.attribute(g_many_attrs, "int_attr"),
    edge_df$int_attr
  )
  expect_identical(
    get.edge.attribute(g_many_attrs, "dbl_attr"),
    edge_df$dbl_attr
  )
  expect_identical(
    get.edge.attribute(g_many_attrs, "chr_attr"),
    edge_df$chr_attr
  )
  # atomic vectors w/ attributes
  # TODO is there a way to get atomic vectors back while preserving attributes?
  # `c()` `v/sapply()` strip attributes
  edge_date_attr <- get.edge.attribute(g_many_attrs, "date_attr", unlist = FALSE)
  edge_date_attr_to_test <- `attributes<-`(unlist(edge_date_attr),
                                           attributes(edge_date_attr[[1]]))
  expect_identical(
    edge_date_attr_to_test,
    edge_df$date_attr
  )
  edge_dttm_attr <- get.edge.attribute(g_many_attrs, "dttm_attr", unlist = FALSE)
  edge_dttm_attr_to_test <- `attributes<-`(unlist(edge_dttm_attr),
                                           attributes(edge_dttm_attr[[1]]))
  expect_identical(
    edge_dttm_attr_to_test,
    edge_df$dttm_attr
  )
  # list of bare atomic vectors
  expect_identical(
    get.edge.attribute(g_many_attrs, "list_attr", unlist = FALSE),
    edge_df$list_attr
  )
  # list of vectors with attributes
  expect_identical(
    get.edge.attribute(g_many_attrs, "mat_list_attr", unlist = FALSE),
    edge_df$mat_list_attr
  )
  # recursive lists
  expect_identical(
    get.edge.attribute(g_many_attrs, "df_list_attr", unlist = FALSE),
    edge_df$df_list_attr
  )
  # sf objects
  expect_identical(
    get.edge.attribute(g_many_attrs, "sfg_attr", unlist = FALSE),
    edge_df$sfg_attr
  )
  
  # vertex attributes ====================================================================
  # bare atomic vectors
  expect_identical(
    get.vertex.attribute(g_many_attrs, "vertex.names"),
    vertex_df[[1]]
  )
  expect_identical(
    get.vertex.attribute(g_many_attrs, "lgl_attr"),
    vertex_df$lgl_attr
  )
  expect_identical(
    get.vertex.attribute(g_many_attrs, "int_attr"),
    vertex_df$int_attr
  )
  expect_identical(
    get.vertex.attribute(g_many_attrs, "dbl_attr"),
    vertex_df$dbl_attr
  )
  expect_identical(
    get.vertex.attribute(g_many_attrs, "chr_attr"),
    vertex_df$chr_attr
  )
  # atomic vectors w/ attributes
  # TODO is there a way to get atomic vectors back while preserving attributes?
  # `c()` `v/sapply()` strip attributes
  vertex_date_attr <- get.vertex.attribute(g_many_attrs, "date_attr", unlist = FALSE)
  vertex_date_attr_to_test <- `attributes<-`(unlist(vertex_date_attr),
                                             attributes(vertex_date_attr[[1]]))
  expect_identical(
    vertex_date_attr_to_test,
    vertex_df$date_attr
    
  )
  vertex_dttm_attr <- get.vertex.attribute(g_many_attrs, "dttm_attr", unlist = FALSE)
  vertex_dttm_attr_to_test <- `attributes<-`(unlist(vertex_dttm_attr),
                                             attributes(vertex_dttm_attr[[1]]))
  expect_identical(
    vertex_dttm_attr_to_test,
    vertex_df$dttm_attr
  )
  # list of bare atomic vectors
  expect_identical(
    get.vertex.attribute(g_many_attrs, "list_attr", unlist = FALSE),
    vertex_df$list_attr
  )
  # list of vectors with attributes
  expect_identical(
    get.vertex.attribute(g_many_attrs, "mat_list_attr", unlist = FALSE),
    vertex_df$mat_list_attr
  )
  # recursive lists
  expect_identical(
    get.vertex.attribute(g_many_attrs, "df_list_attr", unlist = FALSE),
    vertex_df$df_list_attr
  )
  # sf objects
  expect_identical(
    get.vertex.attribute(g_many_attrs, "sfg_attr", unlist = FALSE),
    vertex_df$sfg_attr
  )
  
  # conversion back to data.frame ========================================================
  names(edge_df)[[1]] <- ".tail"
  names(edge_df)[[2]] <- ".head"
  edge_df$sfc_attr <- NULL
  
  names(vertex_df)[[1]] <- "vertex.names"
  vertex_df$sfc_attr <- NULL
  
  g_many_attrs <- delete.vertex.attribute(g_many_attrs, "sfc_attr")
  g_many_attrs <- delete.edge.attribute(g_many_attrs, "sfc_attr")
  
  expect_identical(
    edge_df,
    as.data.frame(g_many_attrs)
  )
  expect_identical(
    vertex_df,
    as.data.frame(g_many_attrs, unit = "vertices")
)

})


test_that("`multiple` arguments work", {
  dir_parallel_edge_df <- data.frame(from = c("a", "a"),
                                     to = c("b", "b"),
                                     stringsAsFactors = FALSE)
  expect_error(
    .as.network.data.frame(dir_parallel_edge_df),
    "`multiple` is `FALSE`, but `x` contains parallel edges."
  )
  expect_s3_class(
    .as.network.data.frame(dir_parallel_edge_df, multiple = TRUE),
    "network"
  )
  expect_true(
    is.multiplex(.as.network.data.frame(dir_parallel_edge_df, multiple = TRUE))
  )
  expect_true(
    is.directed(.as.network.data.frame(dir_parallel_edge_df, multiple = TRUE))
  )
  
  undir_parallel_edge_df <- data.frame(from = c("a", "b"),
                                       to = c("b", "a"),
                                       stringsAsFactors = FALSE)
  expect_s3_class(
    .as.network.data.frame(undir_parallel_edge_df),
    "network"
  )
  expect_error(
    .as.network.data.frame(undir_parallel_edge_df, directed = FALSE),
    "`multiple` is `FALSE`, but `x` contains parallel edges."
  )
  expect_s3_class(
    .as.network.data.frame(undir_parallel_edge_df, directed = FALSE, multiple = TRUE),
    "network"
  )
  expect_true(
    is.multiplex(.as.network.data.frame(undir_parallel_edge_df, directed = FALSE, multiple = TRUE))
  )
  expect_false(
    is.directed(.as.network.data.frame(undir_parallel_edge_df, directed = FALSE, multiple = TRUE))
  )
})

test_that("`loops` works", {
  df_with_loops <- data.frame(from = c("b", "c", "c", "d", "d", "e", "f"),
                              to = c("a", "b", "a", "a", "b", "a", "f"),
                              stringsAsFactors = FALSE)
  expect_error(
    .as.network.data.frame(df_with_loops),
    "`loops` is `FALSE`"
  )
  expect_s3_class(
    .as.network.data.frame(df_with_loops, loops = TRUE),
    "network"
  )
})

test_that("missing vertex names are caught", {
  missing_vertex_df <- data.frame(name = letters[1:5],
                                  stringsAsFactors = FALSE)
  
  missing_edge_df <- data.frame(from = c("b", "c", "c", "d", "d", "e", "f"),
                                to = c("a", "b", "a", "a", "b", "a", "g"),
                                stringsAsFactors = FALSE)
  
  expect_error(
    .as.network.data.frame(missing_edge_df, vertices = missing_vertex_df),
    "The following vertices are in `x`, but not in `vertices`:\n\t- f\n\t- g", fixed = TRUE
  )
})

test_that("duplicate vertex names are caught", {
  dup_vertex_df <- data.frame(name = c("a", "a", "b", "c", "d", "e"),
                              stringsAsFactors = FALSE)
  
  dup_edge_df <- data.frame(from = c("b", "c", "c", "d", "d", "e"),
                            to = c("a", "b", "a", "a", "b", "a"),
                            stringsAsFactors = FALSE)
  
  expect_error(
    .as.network.data.frame(dup_edge_df, vertices = dup_vertex_df),
    "The following vertex names are duplicated in `vertices`:\n\t- a", fixed = TRUE
  )
})

test_that("bad data frames are caught", {
  edge_df_with_NAs1 <- data.frame(from = c(letters, NA),
                                  to = c("a", letters),
                                  stringsAsFactors = FALSE)
  edge_df_with_NAs2 <- data.frame(from = c(letters, "a"),
                                  to = c(NA, letters),
                                  stringsAsFactors = FALSE)
  empty_vertex_df <- data.frame()
  
  expect_error(
    .as.network.data.frame(edge_df_with_NAs2),
    "The first two columns of `x` cannot contain `NA` values.", fixed = TRUE
  )
  expect_error(
    .as.network.data.frame(edge_df_with_NAs2),
    "The first two columns of `x` cannot contain `NA` values.", fixed = TRUE
  )
  
  expect_error(
    .as.network.data.frame(edge_df_with_NAs1[0, 0]),
    "`x` should be a data frame with at least two columns and one row.",
    fixed = TRUE
  )
  expect_error(
    .as.network.data.frame(na.omit(edge_df_with_NAs1), vertices = empty_vertex_df, loops = TRUE),
    "`vertices` should contain at least one column and row.", fixed = TRUE
  )
  
  incompat_edge_types <- data.frame(
    from = c("a", "b"),
    to = c(1, 2),
    stringsAsFactors = FALSE
  )
  expect_error(
    .as.network.data.frame(incompat_edge_types),
    "The first two columns of `x` must be of the same type.",
    fixed = TRUE
  )
  
  non_df_vertices_edge_df <- data.frame(from = 1, to = 2)
  non_df_vertices <- list(name = 1:2)
  expect_error(
    .as.network.data.frame(non_df_vertices_edge_df, vertices = non_df_vertices),
    "If provided, `vertices` should be a data frame.",
    fixed = TRUE
  )
  
  bad_vertex_names_col <- data.frame(name = I(list(1)))
  expect_error(
    .as.network.data.frame(non_df_vertices_edge_df, vertices = bad_vertex_names_col),
    "The first column of `vertices` must be an atomic vector.",
    fixed = TRUE
  )
  
  incompat_types_edge_df <- data.frame(from = 1:3, to = 4:6)
  incompat_types_vertex_df <- data.frame(name = paste(1:6), stringsAsFactors = FALSE)
  expect_error(
    .as.network.data.frame(incompat_types_edge_df, vertices = incompat_types_vertex_df),
    "The first column of `vertices` must be the same type as the value with which they are referenced in `x`'s first two columns.",
    fixed = TRUE
  )
  
  recursive_edge_df <- data.frame(from = I(list(1:2)), to = 3)
  expect_error(
    .as.network.data.frame(recursive_edge_df),
    "If `hyper` is `FALSE`, the first two columns of `x` should be atomic vectors.",
    fixed = TRUE
  )
})


test_that("bipartite networks work", {
  bip_edge_df <- data.frame(.tail = c("a", "a", "b", "b", "c", "d", "d", "e"),
                            .head = c("e1", "e2", "e1", "e3", "e3", "e2", "e3", "e1"),
                            an_edge_attr = letters[1:8],
                            stringsAsFactors = FALSE)
  bip_node_df <- data.frame(vertex.names = c("a", "e1", "b", "e2", "c", "e3", "d", "e"),
                            node_type = c("person", "event", "person", "event", "person",
                                          "event", "person", "person"),
                            color = c("red", "blue", "red", "blue", "red", "blue",
                                      "red", "red"),
                            stringsAsFactors = FALSE)
  
  expect_warning(
    .as.network.data.frame(bip_edge_df, vertices = bip_node_df, 
               bipartite = TRUE),
    "If `bipartite` is `TRUE`, edges are interpreted as undirected.", fixed = TRUE
  )
  
  expect_warning(
    .as.network.data.frame(bip_edge_df, directed = FALSE, vertices = bip_node_df, 
               bipartite = TRUE, loops = TRUE),
    "If `bipartite` is `TRUE`, `loops` must be `FALSE`.", fixed = TRUE
  )
  
  bip_g <- .as.network.data.frame(bip_edge_df, directed = FALSE, vertices = bip_node_df, 
                      loops = FALSE, bipartite = TRUE)
  
  expect_identical(
    bip_edge_df,
    as.data.frame(bip_g)
  )
  expect_identical(
    # tracking modes by vertex order means we have to reorder the data frame
    # and reset row.names to test
    `rownames<-`( 
      bip_node_df[order(bip_node_df$node_type == "person", decreasing = TRUE), ], 
      NULL
    ),
    as.data.frame(bip_g, unit = "vertices")
  )
  
  expect_s3_class(
    bip_g,
    "network"
  )
  
  expect_true(
    is.bipartite(bip_g)
  )
  expect_false(
    has.loops(bip_g)
  )
  expect_false(
    is.directed(bip_g)
  )
  
  expect_identical(
    get.network.attribute(bip_g, "bipartite"),
    5L
  )
  
  expect_identical(
    get.vertex.attribute(bip_g, attrname = "node_type"),
    c(rep("person", 5), rep("event", 3))
  )
  
  expect_identical(
    get.vertex.attribute(bip_g, attrname = "vertex.names"),
    c("a", "b", "c", "d", "e", "e1", "e2", "e3")
  )
  
  expect_identical(
    get.edge.attribute(bip_g, attrname = "an_edge_attr"),
    letters[1:8]
  )
  
  # check if bipartite networks with isolates are caught 
  bip_isolates_node_df <- data.frame(
    vertex.names = c("a", "e1", "b", "e2", "c", "e3", "d", "e", "f", "g"),
    stringsAsFactors = FALSE
  )
  
  expect_error(
    .as.network.data.frame(x = bip_edge_df, directed = FALSE, vertices = bip_isolates_node_df,
               bipartite = TRUE),
    "`bipartite` is `TRUE`, but the `vertices` you provided contain names that are not present in `x`"
  )
  
  bip_isolates_node_df$is_actor <- !grepl("^e\\d$", bip_isolates_node_df$vertex.names)
  bip_isoaltes_g <- .as.network.data.frame(x = bip_edge_df, directed = FALSE, 
                               vertices = bip_isolates_node_df,
                               bipartite = TRUE)
  expect_s3_class(
    bip_isoaltes_g,
    "network"
  )
  expect_identical(
    bip_edge_df,
    as.data.frame(bip_isoaltes_g)
  )
  expect_identical(
    `rownames<-`(
      bip_isolates_node_df[order(bip_isolates_node_df$is_actor, decreasing = TRUE), ],
      NULL
    ),
    as.data.frame(bip_isoaltes_g, unit = "vertices")
  )  
  
  bip_isolates_node_df$is_actor <- as.integer(bip_isolates_node_df$is_actor)
  expect_error(
    .as.network.data.frame(x = bip_edge_df, directed = FALSE, vertices = bip_isolates_node_df,
               bipartite = TRUE),
    "`bipartite` is `TRUE` and vertex types are specified via a column in `vertices` named `\"is_actor\"`.\n\t- If provided, all values in `vertices[[\"is_actor\"]]` must be `TRUE` or `FALSE`.",
    fixed = TRUE
  )
  
  
  # check if nodes that appear in both of the first 2 `edge` columns are caught
  bip_confused_edge_df <- data.frame(
    actor = c("a", "a", "b", "b", "c", "d", "d", "e", "e1"),
    event = c("e1", "e2", "e1", "e3", "e3", "e2", "e3", "e1", "e2"),
    stringsAsFactors = FALSE
  )
  
  expect_error(
    .as.network.data.frame(x = bip_confused_edge_df, directed = FALSE, bipartite = TRUE),
    "`bipartite` is `TRUE`, but there are vertices that appear in both of the first two columns of `x`."
  )
})

test_that("hyper-edges work", {
  hyper_edge_df <- structure(
    list(.tail = list(1:4, 3:5, 4:7, 6:10),
         .head = list(1:4, 3:5, 4:7, 6:10),
         value = as.double(5:8)),
    row.names = 1:4,
    class = "data.frame"
  )
  
  hyper_target_net <- network.initialize(10, directed = FALSE, hyper = TRUE, loops = TRUE)
  hyper_target_net <- add.edge(hyper_target_net, 1:4, 1:4, "value", list(5))
  hyper_target_net <- add.edge(hyper_target_net, 3:5, 3:5, "value", list(6))
  hyper_target_net <- add.edge(hyper_target_net, 4:7, 4:7, "value", list(7))
  hyper_target_net <- add.edge(hyper_target_net, 6:10, 6:10, "value", list(8))
  
  expect_identical(
    .as.network.data.frame(hyper_edge_df, directed = FALSE, hyper = TRUE, loops = TRUE),
    hyper_target_net
  )
  
  expect_identical(
    hyper_edge_df,
    as.data.frame(hyper_target_net)
  )
  
  
  MtSHbyloc_edge_df <- structure(
    list(
      .tail = list(
        as.integer(c(1, 14, 15, 16, 17, 18, 19, 21, 22, 23, 24, 25, 26, 27)),
        as.integer(c(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 20, 26, 27))
      ), 
      .head = list(
        as.integer(c(1, 14, 15, 16, 17, 18, 19, 21, 22, 23, 24, 25, 26, 27)), 
        as.integer(c(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 20, 26, 27))
      )
    ),
    row.names = 1:2,
    class = "data.frame"
  )
  MtSHbyloc_vertex_df <- data.frame(
    vertex.names = 1:27
  )
  
  data("emon")
  MtSHloc <- emon$MtStHelens %v% "Location"
  MtSHimat <- cbind(MtSHloc %in% c("L", "B"), MtSHloc %in% c("NL", "B"))
  MtSHbyloc <- network(MtSHimat, matrix = "incidence", hyper = TRUE,
                       directed = FALSE, loops = TRUE)
  expect_identical(
    .as.network.data.frame(MtSHbyloc_edge_df, directed = FALSE, vertices = MtSHbyloc_vertex_df,
               loops = TRUE, hyper = TRUE),
    MtSHbyloc
  )
  expect_identical(
    MtSHbyloc_edge_df,
    as.data.frame(MtSHbyloc)
  )
  expect_identical(
    MtSHbyloc_vertex_df,
    as.data.frame(MtSHbyloc, unit = "vertices")
  )
  
  delete.edges(MtSHbyloc, 2)
  expect_identical(
    `rownames<-`(MtSHbyloc_edge_df[-2, ], NULL),
    as.data.frame(MtSHbyloc)
  )
  
  delete.vertices(MtSHbyloc, 2)
  expect_identical(
    `rownames<-`(MtSHbyloc_vertex_df[-2, , drop = FALSE], NULL),
    as.data.frame(MtSHbyloc, unit = "vertices")
  )
  
  
  hyper_edges_with_NA <- data.frame(
    from = I(list(c(NA, "a", "b"))),
    to = I(list(c("c", "d")))
  )
  expect_error(
    .as.network.data.frame(hyper_edges_with_NA, hyper = TRUE),
    "`x`'s first two columns contain invalid values."
  )
  
  non_hyper_edges <- data.frame(
    from = 1:3,
    to = 4:6
  )
  expect_error(
    .as.network.data.frame(non_hyper_edges, hyper = TRUE),
    "If `hyper` is `TRUE`, the first two columns of `x` should be list columns."
  )
  
  incompat_type_hyper_edges <- data.frame(
    from = I(list(letters[1:5], 1:5)),
    to = I(list(letters[6:10], letters[11:15]))
  )
  expect_error(
    .as.network.data.frame(incompat_type_hyper_edges, hyper = T),
    "The values in the first two columns of `x` must be of the same type and cannot be `NULL`, `NA`, or recursive values."
  )
  
  loop_hyper_edges <- data.frame(
    from = I(list(c("a", "b"))),
    to = I(list(c("a", "b")))
  )
  expect_error(
    .as.network.data.frame(loop_hyper_edges, hyper = TRUE),
    "`loops` is `FALSE`, but `x` contains loops."
  )

})

test_that("edge/vertex-less networks return empty data frames", {

  empty_g <- network.initialize(0)
  expect_identical(
    nrow(as.data.frame(empty_g)),
    0L
  )
  expect_identical(
    ncol(as.data.frame(empty_g)),
    2L
  )
  expect_identical(
    ncol(as.data.frame(empty_g, attrs_to_ignore = NULL)),
    3L
  )
  
  expect_identical(
    nrow(as.data.frame(empty_g, unit = "vertices")),
    0L
  )
  expect_identical(
    ncol(as.data.frame(empty_g, unit = "vertices")),
    1L
  )
  expect_identical(
    ncol(as.data.frame(empty_g, unit = "vertices", attrs_to_ignore = NULL)),
    2L
  )

})

test_that("deleted edges/vertices and na attributes are handled correctly", {

  na_edge_df <- data.frame(.tail = c("b", "c", "c", "d", "d", "e"),
                           .head = c("a", "b", "a", "a", "b", "a"),
                           na = c(rep(FALSE, 5), TRUE),
                           stringsAsFactors = FALSE)
  na_vertex_df <- data.frame(vertex.names = letters[1:5],
                             na = c(rep(FALSE, 4), TRUE),
                             stringsAsFactors = FALSE)
  
  na_g <- .as.network.data.frame(na_edge_df, vertices = na_vertex_df)
  
  expect_identical(
    as.data.frame(na_g, na.rm = FALSE, attrs_to_ignore = NULL),
    na_edge_df
  )
  expect_identical(
    as.data.frame(na_g, unit = "vertices", na.rm = FALSE, attrs_to_ignore = NULL),
    na_vertex_df
  )
  
  delete.edges(na_g, 1)
  expect_identical(
    `rownames<-`(na_edge_df[-c(1, which(na_edge_df$na)), ], NULL),
    as.data.frame(na_g, attrs_to_ignore = NULL)
  )
  delete.vertices(na_g, 1)
  expect_identical(
    `rownames<-`(na_vertex_df[-c(1, which(na_vertex_df$na)), ], NULL),
    as.data.frame(na_g, unit = "vertices", attrs_to_ignore = NULL)
  )

})
