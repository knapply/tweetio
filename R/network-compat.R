isFALSE <- function(x) {
  is.logical(x) && length(x) == 1L && !is.na(x) && !x
}

.head <- function(x, n = 6) {
  # rather than import `utils::head()`
  # `.head()` is used to limit the number of diagnostic lines that are printed in 
  # error messages that tell users which values are invalid
  n <- min(length(x), n)
  x[seq_len(n)]
}

.validate_edge_df <- function(edges, directed, hyper, loops, multiple, bipartite, ...) {
  # confirm edge data frame has valid dimensions
  if (ncol(edges) < 2L || nrow(edges) == 0L) {
    stop("`x` should be a data frame with at least two columns and one row.",
         call. = FALSE)
  }
  
  el <- edges[, 1:2]
  sources <- edges[[1L]]
  targets <- edges[[2L]]
  
  # validate edge column types
  if (hyper) {
    # confirm that hyper-edges are list columns
    if (!is.list(sources) || !is.list(targets)) {
      stop("If `hyper` is `TRUE`, the first two columns of `x` should be list columns.",
           call. = FALSE)
    }
    # first edge type is the `target_type`, against which all other values are tested
    target_type <- typeof(sources[[1L]])
    # confirm that target_type is itself valid
    if (any(is.na(sources[[1L]])) || target_type %in% c("NULL", "list")) {
      stop("`x`'s first two columns contain invalid values.",
           "\n\t- `x[[1]][[1]]` is `NULL`, recursive, or it contains `NA` values.",
           call. = FALSE)
    }
    # Iterate through edge columns, testing that they're not `NA` and are of the same type
    # as `target_type`. `incompat_types` is a logical matrix of the test results.
    incompat_types <- vapply(el, function(.x) {
      vapply(.x, function(.y) any(is.na(.y)) || typeof(.y) != target_type, logical(1L))
    }, 
    logical(nrow(el))
    )
    # if any values are incompatible, throw error pointing user to the problem values
    if (any(incompat_types)) {
      incompat_rows <- row(incompat_types)[incompat_types]
      incompat_cols <- col(incompat_types)[incompat_types]
      stop("The values in the first two columns of `x` must be of the same type and cannot be `NULL`, `NA`, or recursive values.",
           "\nThe following values are incompatible:",
           paste("\n\t-", sprintf("`x[%d, %d]`",
                                  .head(incompat_rows), .head(incompat_cols))),
           call. = FALSE)
    }
    
  } else { # for non-hyper edges...
    # ... confirm edge columns are atomic vectors
    if (!is.atomic(sources) || !is.atomic(targets)) {
      stop("If `hyper` is `FALSE`, the first two columns of `x` should be atomic vectors.",
           call. = FALSE)
    }
    # confirm that edge columns are of the same type
    if (typeof(sources) != typeof(targets)) {
      stop("The first two columns of `x` must be of the same type.",
           call. = FALSE)
    }
    # confirm edge columns don't contain `NA`s
    if (any(is.na(el))) {
      stop("The first two columns of `x` cannot contain `NA` values.",
           call. = FALSE)
    }
  }
  
  # if `loops` is `FALSE`, confirm that edge columns don't contain loops
  if (!loops) {
    # if hyper, test if each intersection's length is not 0
    if (hyper) {
      loop_rows <- which(
        mapply(
          function(.x, .y) length(intersect(.x, .y)) != 0L,
          sources, targets,
          USE.NAMES = FALSE
        )
      )
      
    } else { # if not hyper...
      # ... test via simple vector comparison
      loop_rows <- which(sources == targets)
    }
    # if loops are found, throw error pointing user to the edge rows that contain them 
    if (length(loop_rows) > 0L) {
      stop("`loops` is `FALSE`, but `x` contains loops.",
           "\nThe following values are affected:",
           paste("\n\t-", sprintf("`x[%d, 1:2]`", .head(loop_rows))),
           call. = FALSE)
    }
  }
  
  # TODO does network support bipartite hypergraphs?
  if (!hyper && bipartite) {
    # check for intersection between edge columns
    confused_nodes <- intersect(sources, targets)
    # if there's an intersection, throw error informing users which nodes are in both columns
    if (length(confused_nodes) > 0L) {
      stop("`bipartite` is `TRUE`, but there are vertices that appear in both of the",
           " first two columns of `x`.\n",
           "The following vertices appear in both columns:",
           paste("\n\t-", .head(confused_nodes)),
           call. = FALSE)
    }
  }
  
  # TODO does network support multiplex hypergraphs?
  if (!hyper && !multiple) {
    if (directed) {
      test_el <- el
    } else {
      test_el <- t(apply(el, 1L, sort))
    }
    
    if (anyDuplicated(test_el) != 0L) {
      parallel_edges <- which(duplicated(test_el))
      stop("`multiple` is `FALSE`, but `x` contains parallel edges.\n",
           "The following rows in `x` are duplicated:",
           paste("\n\t-", sprintf("`x[%d, ]`", .head(parallel_edges))),
           call. = FALSE)
    }
  }
}


.validate_vertex_df <- function(vertices, el_vert_ids) {
  # confirm `vertices` is a data frame
  if (!is.data.frame(vertices)) {
    stop("If provided, `vertices` should be a data frame.",
         call. = FALSE)
  }
  # confirm `vertices` has valid dimensions
  if (nrow(vertices) == 0L || ncol(vertices) == 0L) {
    stop("`vertices` should contain at least one column and row.",
         call. = FALSE)
  }
  
  vertex_ids <- vertices[[1L]]
  if (!is.atomic(vertex_ids)) {
    stop("The first column of `vertices` must be an atomic vector.",
         call. = FALSE)
  }
  # confirm vertex IDs match type used in edges
  if (typeof(vertex_ids) != typeof(el_vert_ids)) {
    stop("The first column of `vertices` must be the same type as the value with which",
         " they are referenced in `x`'s first two columns.",
         call. = FALSE)
  }
  # check for vertex names that are in the edges, but are missing from `vertices` 
  missing_vertex_names <- setdiff(el_vert_ids, vertex_ids)
  if (length(missing_vertex_names) != 0L) {
    stop("The following vertices are in `x`, but not in `vertices`:",
         paste("\n\t-", .head(missing_vertex_names)),
         call. = FALSE)
  }
  # check if any of the `vertices` have duplicate names
  if (anyDuplicated(vertex_ids) != 0L) {
    stop("The following vertex names are duplicated in `vertices`:",
         paste("\n\t-", .head(vertex_ids[duplicated(vertex_ids)])),
         call. = FALSE)
  }
}


.prep_bipartite_vertices <- function(vertices, el_vert_ids) {
  # use "is_actor" column if provided
  if ("is_actor" %in% names(vertices)) {
    # check if `"is_actor"` column is valid
    if (!is.logical(vertices[["is_actor"]]) || any(is.na(vertices[["is_actor"]]))) {
      stop("`bipartite` is `TRUE` and vertex types are specified via a column in `vertices` named `\"is_actor\"`.", 
           "\n\t- If provided, all values in `vertices[[\"is_actor\"]]` must be `TRUE` or `FALSE`.")
    }
    # actors (`TRUE`) go before non-actors (`FALSE`)
    vertex_order <- order(vertices[["is_actor"]], decreasing = TRUE)
    
  } else { # if no "is_actor" column is provided...
    vertex_ids <- vertices[[1L]]
    # ... check for isolates... 
    isolates <- setdiff(vertex_ids, el_vert_ids)
    # ... and throw error informing user of which vertices are isolates
    if (length(isolates) > 0L) {
      stop("`bipartite` is `TRUE`, but the `vertices` you provided contain names that are not present in `x` (i.e. you have isolates).",
           "\nIf you have isolates, `vertices` must have a `logical` column named \"is_actor\" indicating each vertex's type.",
           "\nThe following vertex names are in `vertices`, but not in `x`:",
           paste("\n\t-", .head(isolates)))
    }
    # if there are no isolates, follow order of vertices as they appear in the edges
    vertex_order <- match(el_vert_ids, vertex_ids)
  }
  
  # reorder the vertex rows to match the actor/non-actor order of the final network
  vertices[vertex_order, , drop = FALSE]
}


.distribute_vec_attrs <- function(x) {
  lapply(x, function(.x) {
    if (is.atomic(.x)) lapply(.x, `attributes<-`, attributes(.x))
    else .x
  })
}

.prep_edge_attrs <- function(edges) {
  edge_attr_names <- names(edges)[-(1:2)]
  
  init_vals_eval <- .distribute_vec_attrs(edges[, edge_attr_names, drop = FALSE])
  
  list(
    names_eval = rep(list(as.list(edge_attr_names)), times = nrow(edges)),
    vals_eval = .mapply(list, init_vals_eval, NULL)
  )
}

.prep_vertex_attrs <- function(vertices) {
  vertices[-1L] <- .distribute_vec_attrs(vertices[-1L])
  vertices
}


.as.network.data.frame <- function(x, directed = TRUE, vertices = NULL,
                                  hyper = FALSE, loops = FALSE, multiple = FALSE, 
                                  bipartite = FALSE, ...) {
  # validate network type args
  invalid_network_args <- vapply(list(directed = directed, hyper = hyper, loops = loops, 
                                      multiple = multiple, bipartite = bipartite), 
                                 function(.x) is.na(.x) || !is.logical(.x),
                                 logical(1L))
  if (any(invalid_network_args)) {
    stop("The following arguments must be either `TRUE` or `FALSE`:",
         paste("\n\t-", names(invalid_network_args)[invalid_network_args]))
  }
  
  # handle incompatible network type args
  if (bipartite && directed) {
    warning("If `bipartite` is `TRUE`, edges are interpreted as undirected.")
    directed <- FALSE
  }
  if (bipartite && loops) {
    warning("If `bipartite` is `TRUE`, `loops` must be `FALSE`.")
    loops <- FALSE
  }
  if (hyper && !directed && !loops) {
    warning("If `hyper` is `TRUE` and `directed` is `FALSE`, `loops` must be `TRUE`")
    loops <- TRUE
  }
  if (hyper && bipartite) {
    stop("Both `hyper` and `bipartite` are `TRUE`, but bipartite hypergraphs are not supported.")
  }
  
  # validate edges
  .validate_edge_df(edges = x, directed = directed, hyper = hyper, loops = loops,
                    multiple = multiple, bipartite = bipartite)
  # create reference variables to reduce amount of code requiring brackets
  sources <- x[[1L]]
  targets <- x[[2L]]
  # create variable containing vertex IDs in the order they appear in the edges
  vertex_ids_in_el <- unique(unlist(x[, 1:2], use.names = FALSE))
  
  # validate vertices
  if (!is.null(vertices)) {
    .validate_vertex_df(vertices, el_vert_ids = vertex_ids_in_el)
  }
  
  # if vertices aren't provided, use the order in which they appear in the edges
  if (is.null(vertices)) {
    vertex_names <- vertex_ids_in_el
    
  } else { # if vertices are provided, use that order
    if (bipartite) { 
      # if bipartite, first reorder vertices so actors come before non-actors
      vertices <- .prep_bipartite_vertices(vertices, el_vert_ids = vertex_ids_in_el)
    }
    vertex_names <- vertices[[1L]]
  }
  
  # out_sources/out_targets consist of the numerical indices to add to the final network
  out_sources <- lapply(sources, match, vertex_names)
  out_targets <- lapply(targets, match, vertex_names)
  
  # prep edge attributes
  if (ncol(x) == 2L) {
    edge_attrs <- list(names_eval = NULL, vals_eval = NULL)
  } else {
    edge_attrs <- .prep_edge_attrs(x)
  }
  
  # start building the network to return
  out <- network::network.initialize(
    n = length(vertex_names),
    directed = directed,
    hyper = hyper,
    loops = loops,
    multiple = multiple,
    bipartite = if (bipartite) length(unique(sources)) else FALSE
  )
  
  # add edges (and any edge attributes)
  out <- network::add.edges.network(
    x = out,
    tail = out_sources,
    head = out_targets,
    names.eval = edge_attrs$names_eval,
    vals.eval = edge_attrs$vals_eval,
    ...
  )
  
  # set vertex attributes
  if (is.null(vertices)) {
    # if vertices aren't provided, set "vertex.names" as the values used in edges
    out <- network::set.vertex.attribute(out, attrname = "vertex.names", value = vertex_names)
  } else if (ncol(vertices) == 1L) {
    out <- network::set.vertex.attribute(out, attrname = "vertex.names", value = vertices[[1L]])
  } else {
    out <- network::set.vertex.attribute(
      x = out,
      attrname = c("vertex.names",        # first column is always "vertex.names"
                   names(vertices)[-1L]), 
      value = .prep_vertex_attrs(vertices)
    )
  }
  
  out
}
