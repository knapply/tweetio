test_that("network functions work (data.table)", {
  if (requireNamespace("network", package = TRUE)) {

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

    expect_s3_class(
      as_tweet_network(test_df, all_status_data = TRUE, all_user_data = TRUE),
      "network"
    )
    expect_s3_class(
      as_tweet_network(test_df, target_class = "hashtag",
                       all_status_data = TRUE, all_user_data = TRUE),
      "network"
    )
    expect_s3_class(
      as_tweet_network(test_df, target_class = "media",
                       all_status_data = TRUE, all_user_data = TRUE),
      "network"
    )

  }
})


test_that("network functions work (tibble)", {
  if (requireNamespace("network", package = TRUE)) {

    test_df <- read_tweets(
      example_tweet_file(), as_tibble = TRUE
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

    expect_s3_class(
      as_tweet_network(test_df, all_status_data = TRUE, all_user_data = TRUE),
      "network"
    )
    expect_s3_class(
      as_tweet_network(test_df, target_class = "hashtag",
                       all_status_data = TRUE, all_user_data = TRUE),
      "network"
    )
    expect_s3_class(
      as_tweet_network(test_df, target_class = "media",
                       all_status_data = TRUE, all_user_data = TRUE),
      "network"
    )

  }
})
