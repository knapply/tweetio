test_that("detecting data type works", {
  temp_file <- tempfile()
  
  normal1 <- "{\"delete\":{\"status\":{\"id\":565342480917602305,\"id_str\":\"565342480917602305\",\"user_id\":1666065217,\"user_id_str\":\"1666065217\"},\"timestamp_ms\":\"1569693799718\"}}"
  write(normal1, temp_file)
  
  expect_equal(
    nrow(read_tweets(temp_file)),
    0
  )
  

  normal2 <- '{"id_str":"1178007813257388032"}'
  write(normal2, temp_file)
  expect_error(
    nrow(read_tweets(temp_file)),
    NA
  )

  
  nested_doc <- '{"doc":{"id_str":"1178007813257388032"}}'
  write(nested_doc, temp_file)
  expect_equal(
    nrow(read_tweets(temp_file)),
    1
  )
  
  nested_doc <- '{"junk":[],"doc":{"kind":"test"}}'
  write(nested_doc, temp_file)
  expect_equal(
    nrow(read_tweets(temp_file)),
    0
  )
})