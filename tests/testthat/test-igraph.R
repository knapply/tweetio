test_that("igraph functions work", {
  test_df <- read_tweets(
    example_tweet_file()
    )[1:100]
  
  expect_s3_class(
    as_igraph(test_df),
    "igraph"
  )
  
})
