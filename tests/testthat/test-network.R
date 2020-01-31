test_that("network functions work", {
  test_df <- read_tweets(
    example_tweet_file()
  )[1:100, ]
  
  user_nw <- as_tweet_network(test_df)
  expect_true(
    user_nw$gal$directed
  )
  expect_false(
    user_nw$gal$bipartite
  )
  expect_true(
    user_nw$gal$loops
  )
  
  url_nw <- as_tweet_network(test_df, target_class = "url")
  expect_s3_class(
    as_tweet_network(test_df, target_class = "url"),
    "network"
  )
  expect_true(
    is.integer(url_nw$gal$bipartite)
  )
  expect_false(
    url_nw$gal$directed
  )
  expect_false(
    url_nw$gal$loops
  )
})
