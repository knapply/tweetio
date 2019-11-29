test_that("extract_statuses() works", {
  test_df <- read_tweets(example_tweet_file())
  
  expect_s3_class(
    extract_statuses(test_df),
    "data.table"
  )

})
