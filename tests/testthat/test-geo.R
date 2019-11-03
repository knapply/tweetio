test_that("as_tweet_sf() works", {
  bbox_prepped <- read_tweets(system.file("example-data/api-stream.json.gz", 
                                          package = "tweetio"))
  
  bbox_not_prepped <- read_tweets(system.file("example-data/api-stream.json.gz", 
                                              package = "tweetio"),
                                  prep_bbox = FALSE)
  
  expect_s3_class(
    as_tweet_sf(bbox_prepped),
    "sf"
  )
  expect_null(
    as_tweet_sf(bbox_prepped[0, ])
  )
  
  expect_s3_class(
    as_tweet_sf(bbox_not_prepped),
    "sf"
  )
  expect_null(
    as_tweet_sf(bbox_not_prepped[0, ])
  )

})