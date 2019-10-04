test_that("detecting data type works", {
  temp_file <- tempfile()
  
  # deleted status from API stream
  normal1 <- "{\"delete\":{\"status\":{\"id\":565342480917602305,\"id_str\":\"565342480917602305\",\"user_id\":1666065217,\"user_id_str\":\"1666065217\"},\"timestamp_ms\":\"1569693799718\"}}"
  write(normal1, temp_file)
  
  expect_equal(
    nrow(read_tweets(temp_file)),
    0
  )
  
  # "regular" status from API stream
  normal2 <- '{"id_str":"1178007813257388032"}'
  write(normal2, temp_file)
  expect_error(
    nrow(read_tweets(temp_file)),
    NA
  )

  # Elasticsearch .jsonl tweet
  nested_doc <- '{"doc":{"id_str":"1178007813257388032"}}'
  write(nested_doc, temp_file)
  expect_equal(
    nrow(read_tweets(temp_file)),
    1
  )
  
  # Elasticsearch .jsonl non-tweet
  nested_doc <- '{"junk":[],"doc":{"kind":"test"}}'
  write(nested_doc, temp_file)
  expect_equal(
    nrow(read_tweets(temp_file)),
    0
  )
  
  # Elasticsearch .json array tweet
  nested_doc <- '[{"_source":{"doc":{"id_str":"1178007813257388032"}}},{"_source":{"doc":{"id_str":"1178007813257388032"}}}]'
  write(nested_doc, temp_file)
  expect_equal(
    nrow(read_tweets(temp_file)),
    2
  )
  

  # Elasticsearch .json array non-tweet
  nested_doc <- '[{"junk":[],"doc":{"kind":"test"}},{"junk":[],"doc":{"kind":"test"}}]'
  write(nested_doc, temp_file)
  expect_equal(
    nrow(read_tweets(temp_file)),
    0
  )
  
  nested_doc <- '{"junk":[],"doc":{"kind":"test"}}.'
  write(nested_doc, temp_file)
  expect_error(
    nrow(read_tweets(temp_file)),
    "parsing error"
  )
  
})