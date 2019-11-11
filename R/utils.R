#' @importFrom data.table setnames
standardize_cols <- function(df) {
  prototype_regex <- "^(retweet|reply_to|quoted|mentions)_"
  setnames(df, old = names(df), new =  sub(
    pattern = prototype_regex, replacement = "", x = names(df)
  )
  )[]
}