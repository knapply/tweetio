test_that("reading/writing spreadsheets works", {
  test_df <- read_tweets(
    example_tweet_file()
  )[1:100, ]

  csv_temp_file <- tempfile(fileext = ".csv")

  expect_error(
    write_tweet_csv(test_df, csv_temp_file),
    NA
  )

  expect_error(
    write_tweet_csv(as.data.frame(test_df), csv_temp_file),
    NA
  )

  expect_error(
    read.csv(csv_temp_file),
    NA
  )
})
