test_that("options work", {
  expect_identical(
    tweetio_options(),
    list(tweetio.as_tibble = FALSE, tweetio.verbose = FALSE)
  )
})
