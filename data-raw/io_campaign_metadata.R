metadata_path <- "inst/twitter-info-ops-metadata/metadata.csv"

col_classes <- c(
  date_released = "Date",
  entities = "character",
  dataset_date = "Date",
  tweet_info_url = "character",
  account_info_url = "character",
  media_url = "character",
  readme_url = "character",
  set_number = "integer"
)

io_campaign_metadata <- data.table::fread(
  file = metadata_path, 
  sep = ",",
  colClasses = col_classes,
  encoding = "UTF-8"
)

io_campaign_metadata[, campaign_name := stringi::stri_replace_first_fixed(
  basename(tweet_info_url),
  "_tweets_csv_hashed.zip", ""
)]

io_campaign_metadata[, entities := strsplit(entities, split = "/")]

data.table::setcolorder(io_campaign_metadata, 
                        c("campaign_name", names(col_classes)))

usethis::use_data(io_campaign_metadata, overwrite = TRUE)
