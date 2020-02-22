test_that("as_tweet_sf() works", {
  tweet_df <- read_tweets(example_tweet_file(small = TRUE))
  
  expect_s3_class(
    as_tweet_sf(tweet_df),
    "sf"
  )
  
  expect_s3_class(
    as_tweet_sf(tweet_df, as_tibble = TRUE),
    "sf"
  )
  
  expect_null(
    as_tweet_sf(tweet_df[0, ])
  )
  
  expect_error(
    as_tweet_sf(tweet_df, geom_col = "bad col")
  )
  
  expect_identical(
    attr(as_tweet_sf(tweet_df), "sf_column"),
    "geometry"
  )
  
  expect_identical(
    attr(as_tweet_sf(as.data.frame(tweet_df)), "sf_column"),
    "geometry"
  )
  
  expect_identical(
    attr(as_tweet_sf(tweet_df, geom_col = "quoted_bbox_coords"), "sf_column"),
    "geometry"
  )
  
  expect_identical(
    attr(as_tweet_sf(tweet_df, geom_col = "retweet_bbox_coords"), "sf_column"),
    "geometry"
  )
  
  expect_identical(
    attr(as_tweet_sf(tweet_df, geom_col = "all"), "sf_column"),
    "geometry"
  )
  
})