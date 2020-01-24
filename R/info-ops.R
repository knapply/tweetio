#' @importFrom data.table fread
io_campaign_metadata <- function(as_tibble = FALSE, ...) {
  metadata_path <- system.file(
    "twitter-info-ops-metadata/metadata.csv",
    package = "tweetio",
    mustWork = TRUE
  )
  
  col_classes <- c(
    date_released = "Date",
    states_or_organizations = "character",
    dataset_date = "Date",
    tweet_info_url = "character",
    account_info_url = "character",
    media_url = "character",
    readme_url = "character",
    set_number = "integer"
  )
  
  out <- fread(
    file = metadata_path, 
    select = names(col_classes),
    colClasses = col_classes,
    encoding = "UTF-8",
    ...
  )
  
  .finalize_df(out, as_tibble = as_tibble)
}

