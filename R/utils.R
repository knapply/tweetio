.finalize_df <- function(df, as_tibble) {
  if (!as_tibble || !requireNamespace("tibble", quietly = TRUE)) {
    return(df[])
  }
  
  original_class <- class(df)
  df <- tibble::as_tibble(df)

  if (original_class[[1L]] == "sf" && requireNamespace("sf", quietly = TRUE)) {
    df <- sf::st_as_sf(df)
  }
  
  df
}

`%||%` <- function(lhs, rhs) {
  if (is.null(lhs)) rhs else lhs
}

.as_posixct <- function(x, .tz = "UTC", .class = c("POSIXct", "POSIXt")) {
  structure(x, class = .class, tzone = .tz)
}

.map_template <- function(.x, .f, .template, ...) {
  vapply(.x, .f, .template, ...)
}

.map_chr <- function(.x, .f, ...) {
  .map_template(.x, .f, character(1L), ...)
}
.map_lgl <- function(.x, .f, ...) {
  .map_template(.x, .f, logical(1L), ...)
}

.map2 <- function(.x, .y, .f, ...) {
  mapply(.f, .x, .y, MoreArgs = list(...), SIMPLIFY = FALSE)
}

.map2_lgl <- function(.x, .y, .f, ...) {
  as.vector(.map2(.x, .y, .f, ...), mode = "logical")
}

# .map3 <- function(.x, .y, .z, .f, ...) {
  # mapply(.f, .x, .y, .z, MoreArgs = list(...), SIMPLIFY = FALSE)
# }

# .map3_lgl <- function(.x, .y, .z, .f, ...) {
  # as.vector(.map3(.x, .y, .z, .f, ...), "logical")
# }

.imap <- function(.x, .f, ...) {
  nm <- names(.x) %||% seq_along(.x)
  Map(f = .f, .x, nm, ...)
}


.map_if <- function(.x, .p, .f, ...) {
  targets <- .map_lgl(.x, .p)
  .x[targets] <- lapply(.x[targets], .f, ...)
  .x
}

.map_at <- function(.x, .at, .f, ...) {
  .x[.at] <- lapply(.x[.at], .f, ...)
  .x
}


.keep <- function(.x, .f, ...) {
  .x[.map_lgl(.x, .f, ...)]
}
.discard <- function(.x, .f, ...) {
  .x[!.map_lgl(.x, .f, ...)]
}


.keep2 <- function(.x, .y, .f, ...) {
  .x[.map_lgl(.y, .f, ...)]
}
.discard2 <- function(.x, .y, .f, ...) {
  .x[!.map_lgl(.y, .f, ...)]
}

.compact <- function(.x) {
  Filter(length, .x)
}

.match_col_names <- function(.x, .p, ...) {
  .keep2(names(.x), .x, .p, ...)
}


# .is_atomic_with_non_nas <- function(x) {
  # is.atomic(x) && any(!is.na(x))
# }

.set_names <- function(x, y = x) {
  `names<-`(x, y)
}

.is_empty <- function(x) {
  length(x) == 0L 
}

.is_dt <- function(x) {
  inherits(x, "data.table")
}

.file_exists <- function(x) {
  if (.is_empty(x)) {
    .stop("`x` is empty, so `file.exists()` doesn't have anything to check.")
  }
  file.exists(x)
}

.is_scalar_atomic <- function(x, template = is.atomic) {
  template(x) && length(x) == 1L
}

.is_scalar_chr <- function(x) {
  .is_scalar_atomic(x, template = is.character)
}


#' @importFrom data.table as.data.table
.as_dt <- as.data.table

#' @importFrom data.table .SD copy
#' @importFrom jsonify to_json
jsonify_list_cols <- function(df, copy = TRUE) {
  list_cols <- .match_col_names(df, is.list)
  
  if (.is_empty(list_cols)) {
    return(df)
  }
  
  if (copy) {
    df <- copy(df)
  }

  df[, (list_cols) := lapply(.SD, .map_chr, function(.x) {
    .x[is.na(.x)] <- ""
    to_json(.x, unbox = TRUE)
    }),
    .SDcols = list_cols
  ]
}


#' @importFrom data.table setnames
standardize_cols <- function(df) {
  prototype_regex <- "^(retweet|reply_to|quoted|mentions)_"
  setnames(df, old = names(df), new =  sub(
    pattern = prototype_regex, replacement = "", x = names(df)
  )
  )[]
}





