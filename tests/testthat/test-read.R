test_that("reading rtweet stream works", {
  target_schema <- list(
    user_id = "character", status_id = "character", created_at = c("POSIXct", "POSIXt"),
    screen_name = "character", text = "character", source = "character", 
    reply_to_status_id = "character", reply_to_user_id = "character", 
    reply_to_screen_name = "character", is_quote = "logical", 
    is_retweet = "logical", hashtags = "list", urls_expanded_url = "list", 
    media_url = "list", media_expanded_url = "list", media_type = "list", 
    mentions_user_id = "list", mentions_screen_name = "list", 
    lang = "character", quoted_status_id = "character", quoted_text = "character", 
    quoted_created_at = c("POSIXct", "POSIXt"), quoted_source = "character", 
    quoted_favorite_count = "integer", quoted_retweet_count = "integer", 
    quoted_user_id = "character", quoted_screen_name = "character", 
    quoted_name = "character", quoted_followers_count = "integer", 
    quoted_friends_count = "integer", quoted_statuses_count = "integer", 
    quoted_location = "character", quoted_description = "character", 
    quoted_verified = "logical", retweet_status_id = "character", 
    retweet_text = "character", retweet_created_at = c("POSIXct", "POSIXt"), 
    retweet_source = "character", retweet_favorite_count = "integer", 
    retweet_retweet_count = "integer", retweet_user_id = "character", 
    retweet_screen_name = "character", retweet_name = "character", 
    retweet_followers_count = "integer", retweet_friends_count = "integer", 
    retweet_statuses_count = "integer", retweet_location = "character", 
    retweet_description = "character", retweet_verified = "logical", 
    place_url = "character", place_name = "character", place_full_name = "character", 
    place_type = "character", country = "character", country_code = "character", 
    bbox_coords = "list", status_url = "character", name = "character", 
    location = "character", description = "character", url = "character", 
    protected = "logical", followers_count = "integer", friends_count = "integer", 
    listed_count = "integer", statuses_count = "integer", favourites_count = "integer", 
    account_created_at = c("POSIXct", "POSIXt"), verified = "logical", 
    profile_url = "character", profile_url2 = "character", account_lang = "character", 
    profile_banner_url = "character", profile_image_url = "character", 
    is_retweeted = "logical", retweet_place_url = "character", 
    retweet_place_name = "character", retweet_place_full_name = "character", 
    retweet_place_type = "character", retweet_country = "character", 
    retweet_country_code = "character", retweet_bbox_coords = "list", 
    quoted_place_url = "character", quoted_place_name = "character", 
    quoted_place_full_name = "character", quoted_place_type = "character", 
    quoted_country = "character", quoted_country_code = "character", 
    quoted_bbox_coords = "list", timestamp_ms = c("POSIXct", "POSIXt"),
    contributors_enabled = "logical"
  )
    
  
  test_df <- read_tweets(example_tweet_file())

  expect_true(
    identical(
      lapply(test_df, class),
      target_schema
    )
  )

})
