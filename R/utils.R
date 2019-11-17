#' @importFrom data.table setnames
standardize_cols <- function(df) {
  prototype_regex <- "^(retweet|reply_to|quoted|mentions)_"
  setnames(df, old = names(df), new =  sub(
    pattern = prototype_regex, replacement = "", x = names(df)
  )
  )[]
}

.map_chr <- function(.x, .f, ...) {
  vapply(X = .x, FUN = .f, FUN.VALUE = character(1L), ...)
}

.map_lgl <- function(.x, .f, ...) {
  vapply(X = .x, FUN = .f, FUN.VALUE = logical(1L), ...)
}

.keep <- function(.x, .f, ...) {
  .x[.map_lgl(.x, .f, ...)]
}

.discard <- function(.x, .f, ...) {
  .x[!.map_lgl(.x, .f, ...)]
}