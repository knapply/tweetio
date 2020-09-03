test_that("write_graphml() works", {
  if (requireNamespace("igraph", quietly = TRUE)) {

    tweet_df <- read_tweets(example_tweet_file())
    tweet_g <- as_igraph(tweet_df, all_user_data = TRUE, all_status_data = TRUE)

    temp_file <- tempfile(fileext = ".graphml")
    expect_error(
      write_graphml(tweet_g, temp_file),
      NA
    )

  }
})
