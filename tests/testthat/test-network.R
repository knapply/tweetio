test_that("network functions work", {
  test_df <- read_tweets(
    example_tweet_file()
  )[1:100, ]
  
  expect_s3_class(
    as_tweet_network(test_df),
    "network"
  )
  
  expect_s3_class(
    as_tweet_network(as.data.frame(test_df)),
    "network"
  )
  
  expect_s3_class(
    as_tweet_network(test_df, target_class = "url"),
    "network"
  )
  
  expect_s3_class(
    as_tweet_network(test_df, target_class = "hashtag", 
                     all_status_data = TRUE, all_user_data = TRUE),
    "network"
  )
  
})
