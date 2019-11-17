test_that("reading/writing CSVs works", {
  test_df <- read_tweets(system.file("example-data/api-stream.json.gz", 
                                     package = "tweetio"))[1:100]
  temp_file <- tempfile(fileext = ".csv")
  
  write_tweet_csv(test_df, temp_file)
  
  round_trip <- read_tweet_csv(temp_file)
  
  expect_true(
    isTRUE(
      all.equal(test_df, round_trip,
                check.attributes = FALSE)
    )
  )
  
})