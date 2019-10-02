test_that("reading rtweet stream works", {
  expect_error(
    read_tweets(system.file("example-data/api-stream.json.gz", 
                            package = "tweetio")),
    NA
  )
  
})
