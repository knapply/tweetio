test_that("igraph functions work", {
  test_df <- read_tweets(
    example_tweet_file()
    )[1:100, ]
  
  expect_s3_class(
    as_igraph(test_df),
    "igraph"
  )
  
  expect_s3_class(
    as_igraph(as.data.frame(test_df)),
    "igraph"
  )
  
  expect_s3_class(
    as_igraph(test_df, target_class = "url"),
    "igraph"
  )
  
  expect_s3_class(
    as_igraph(test_df, target_class = "hashtag", 
              all_status_data = TRUE, all_user_data = TRUE),
    "igraph"
  )
  
  expect_true(
    igraph::is_bipartite(
      as_igraph(test_df, target_class = "media")
    )
  )
  
})
