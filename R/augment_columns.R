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

#' Augment a `tweet_df` with Columns Containg Extracted Keywords
#' 
#' @template param-tweet_df
#' @param target_col `character(1L)`, Default: `"text"`. The name of the column
#' in `tweet_df` from which to extract key words.
#' @param dict `character(1L)`, Default: `"PMESSI"`. A dictionary of key words 
#' to extract from `tweet_df`'s `text` column. Currently one of `"PMESSI"` or
#' `"ASCOPE"`.
#' @param lang `character(1L)`, Default: `"en"`. Which dictionary language to 
#' use. Currently only `"en"` (English).
#' @param unique `logical(1L)`, Default: `TRUE`. Whether to only keep unique 
#' terms extracted from `target_col`.
#' @param add_counts `logical(1L)`, Default: `FALSE`. Whether to add columns
#' containing the number of terms extracted from `target_col`. 
#' @param copy `logical(1L)`, Default: `TRUE`. Whether `tweet_df` should be 
#' copied or modified in place.
#' @param opts_regex `list()`, Default: `stringi::stri_opts_regex(case_insensitive = TRUE)`.
#' A named list of options to pass to `stringi::stri_extract_all_regex()`'s 
#' `opts_regex` parameter.
#' @template param-dots
#' 
#' @template author-bk
#' 
#' @importFrom data.table := %chin%
#' @importFrom stringi stri_flatten stri_extract_all_regex stri_opts_regex
#' 
#' @export
augment_columns <- function(tweet_df, 
  target_col = "text",
  dict = c("PMESSI", "ASCOPE"),
  lang = c("en"),
  unique = TRUE,
  add_counts = FALSE,
  copy = TRUE,
  opts_regex = stri_opts_regex(case_insensitive = TRUE),
  ...
  ) {
  
  is_valid_target_col <- is.character(target_col) && 
      length(target_col) == 1L &&
      target_col %chin% names(tweet_df) &&
      is.character(tweet_df[[target_col]])
  
  if (!is_valid_target_col) {
    stop("`target_col` must be a single character referring to the name of a column in `tweet_df` that is of type <character>", call. = FALSE)
  }
  
  dict <- match.arg(dict, c("PMESSI", "ASCOPE"))
  lang <- match.arg(lang, c("en"))
  
  terms <- lapply(build_dict(dict, lang), function(.x) {
    paste0("(", stri_flatten(.x, collapse = "|"), ")")
  })
  
  if (!.is_dt(tweet_df)) {
    out <- .as_dt(tweet_df)
  } else if (copy) {
    out <- copy(tweet_df)
  } else {
    out <- tweet_df
  }
  
  out[, (names(terms)) := lapply(terms, function(.x) {
    stri_extract_all_regex(get(target_col), .x, opts_regex = opts_regex,
                           omit_no_match = TRUE)
    })
  ]
  
  if (add_counts) {
    count_names <- paste0("n_", names(terms), "_terms")
    out[, (count_names) := lapply(.SD, .map_int, length),
        .SDcols = names(terms)]
  }
  
  if (unique) {
    out[, (names(terms)) := lapply(.SD, lapply, unique),
        .SDcols = names(terms)]
  }
  
  out
}

