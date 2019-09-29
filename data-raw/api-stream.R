rtweet_api_stream <- rtweet::stream_tweets(
  timeout = 60L * 10L, 
  parse = FALSE,
  file_name = "~/tweetio/inst/example-data/api-stream.json"
)