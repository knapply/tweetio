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

.finalize_df <- function(df, as_tibble) {
  if (!as_tibble || !requireNamespace("tibble", quietly = TRUE)) {
    return(df)
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


.imap <- function(.x, .f, ...) {
  nm <- names(.x) %||% seq_along(.x)
  Map(f = .f, .x, nm, ...)
}


.map_if <- function(.x, .p, .f, ...) {
  targets <- .map_lgl(.x, .p)
  .x[targets] <- lapply(.x[targets], .f, ...)
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


.is_atomic_with_non_nas <- function(x) {
  is.atomic(x) && any(!is.na(x))
}

.set_names <- function(x, y = x) {
  `names<-`(x, y)
}

.is_empty <- function(x) {
  length(x) == 0L 
}

.is_dt <- function(x) {
  inherits(x, "data.table")
}

#' @importFrom data.table as.data.table
.as_dt <- as.data.table

#' @importFrom data.table copy
#' @importFrom jsonify to_json
jsonify_list_cols <- function(df, copy = TRUE) {
  # silence R CMD Check NOTE =============================================================
  .SD <- NULL
  # ======================================================================================
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
standarize_cols <- function(df) {
  prototype_regex <- "^(retweet|reply_to|quoted|mentions)_"
  setnames(df, old = names(df), new =  sub(
    pattern = prototype_regex, replacement = "", x = names(df)
  )
  )[]
}





