test_df <- read_tweets(example_tweet_file())


test_that("extract_statuses() works", {
  expect_s3_class(
    extract_statuses(test_df),
    "data.table"
  )

  if (requireNamespace("tibble", quietly = TRUE)) {
    expect_s3_class(
      extract_statuses(tibble::as_tibble(test_df)),
      "data.table"
    )
  }
})


test_that("extract_users() works", {
  expect_s3_class(
    extract_users(test_df),
    "data.table"
  )

  if (requireNamespace("tibble", quietly = TRUE)) {
    expect_s3_class(
      extract_users(tibble::as_tibble(test_df)),
      "data.table"
    )
  }
})
