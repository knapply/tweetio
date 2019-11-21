test_that("reading/writing spreadsheets works", {
  test_df <- read_tweets(
    system.file("example-data/api-stream.json.gz", package = "tweetio"), 
    as_tibble = FALSE
  )[1:100]

  csv_temp_file <- tempfile(fileext = ".csv")
  xl_temp_file <- tempfile(fileext = ".xlsx")
  
  expect_error(
    write_tweet_csv(test_df, csv_temp_file),
    NA
  )
  
  expect_error(
    write_tweet_xlsx(test_df, xl_temp_file),
    NA
  )
})