test_that("igraph functions work", {
  test_df <- read_tweets(
    system.file("example-data/api-stream.json.gz", 
                package = "tweetio"), as_tibble = FALSE
    )[1:100]
  
  pn <- as_sna_proto_net(test_df)
  
  expect_named(
    pn,
    c("edges", "nodes")
  )
  
  expect_s3_class(
    as_sna_igraph(test_df),
    "igraph"
  )
  
  expect_s3_class(
    as_sna_igraph(pn),
    "igraph"
  )
})
