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