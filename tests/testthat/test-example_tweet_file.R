test_that("example_tweet_file()s exist", {
  expect_true(
    file.exists(example_tweet_file())
  )
  
  expect_true(
    file.exists(example_tweet_file(small = FALSE))
  )
})