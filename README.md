
<!-- README.Rmd generates README.md. -->

# `{tweetio}`

<!-- badges: start -->

[![Lifecycle](https://img.shields.io/badge/lifecycle-experimental-orange.svg)](https://www.tidyverse.org/lifecycle/#experimental)
[![GitHub last
commit](https://img.shields.io/github/last-commit/knapply/tweetio.svg)](https://github.com/knapply/tweetio/commits/master)
[![Codecov test
coverage](https://codecov.io/gh/knapply/tweetio/branch/master/graph/badge.svg)](https://codecov.io/gh/knapply/tweetio?branch=master)
[![AppVeyor build
status](https://ci.appveyor.com/api/projects/status/github/knapply/tweetio?branch=master&svg=true)](https://ci.appveyor.com/project/knapply/tweetio)
[![Travis-CI Build
Status](https://travis-ci.org/knapply/tweetio.svg?branch=master)](https://travis-ci.org/knapply/tweetio)
[![License: GPL
v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Depends](https://img.shields.io/badge/Depends-GNU_R%3E=3.3-blue.svg)](https://www.r-project.org/)
[![GitHub code size in
bytes](https://img.shields.io/github/languages/code-size/knapply/tweetio.svg)](https://github.com/knapply/tweetio)
[![HitCount](http://hits.dwyl.io/knapply/tweetio.svg)](http://hits.dwyl.io/knapply/tweetio)
<!-- badges: end -->

# Introduction

**The [`{rtweet}`](https://rtweet.info/) package spoils R users
*rotten*… in the best possible way**. The behind-the-scenes data
carpentry is so seamless that the user doesn’t need to know anything
about the horrors of Twitter data, which is pretty amazing. If you use
`{rtweet}`, you owe Mike Kearney some serious gratitude/citations.

`{tweetio}` is **not** a competitor to `{rtweet}`, but it definitely
attempts to emulate its data frame schema because…

1.  It’s incredibly easy to use.
2.  It’s more efficient to analyze than a key-value format following the
    raw data.
3.  It’d be a waste not to maximize compatibiltiy with tools built
    specifically around `{rtweet}`’s data frames.

> ***You** bring the data, `{tweetio}` gets them into R.*

`{tweetio}` focuses on one thing: **going from raw tweets to
`{rtweet}`-style data frames (or other useful structures) as quickly and
efficiently as possible**. Whether the data came from the Twitter API, a
database dump, or some other source, `{tweetio}`’s job is to get them
into R.

## Installation

You’ll need a C++ compiler. If you’re using Windows, that means
[Rtools](https://cran.r-project.org/bin/windows/Rtools/).

``` r
# install.packages("remotes")
remotes::install_github("knapply/tweetio")
```

## Supported Data Inputs

  - [x] Twitter API streams: .json, .json.gz
  - [x] API to Elasticsearch data dump (JSON Array): .json, .json.gz
  - [x] API to Elasticsearch data dump (line-delimited JSON): .jsonl,
    .jsonl.gz

## Supported Data Outputs

  - [ ] CSV
  - [ ] .graphml via
    [`{tweetgraph}`](https://knapply.github.io/tweetgraph/) integration

## Usage

### Simple Example

First, we’ll save a stream of tweets using `rtweet::stream_tweets()`.

``` r
temp_file <- tempfile(fileext = ".json")
rtweet::stream_tweets(timeout = 15, parse = FALSE, file_name = temp_file)
```

We can then pass the file path to `tweetio::read_tweets()` to
efficiently parse the data into an `{rtweet}`-style data frame.

``` r
library(tweetio)

small_rtweet_stream <- read_tweets(temp_file)
dplyr::glimpse(small_rtweet_stream)
```

    #> Rows: 466
    #> Columns: 71
    #> $ user_id                 <chr> "979330656730861568", "1522318812", "9...
    #> $ status_id               <chr> "1179494161340407808", "11794941655303...
    #> $ created_at              <dttm> 2019-10-02 20:31:36, 2019-10-02 20:31...
    #> $ screen_name             <chr> "babiegoogie", "sako14843", "CptYakAss...
    #> $ text                    <chr> "RT @whyyy158: This was so wholesome t...
    #> $ source                  <chr> "<a href=\"http://twitter.com/download...
    #> $ reply_to_status_id      <chr> NA, NA, NA, NA, NA, "11793846211145768...
    #> $ reply_to_user_id        <chr> NA, NA, NA, NA, NA, "98613578761488793...
    #> $ reply_to_screen_name    <chr> NA, NA, NA, NA, NA, "satotomi__", NA, ...
    #> $ is_quote                <lgl> TRUE, FALSE, FALSE, FALSE, FALSE, FALS...
    #> $ is_retweeted            <lgl> FALSE, FALSE, FALSE, FALSE, FALSE, FAL...
    #> $ hashtags                <list> [<>, <>, <>, <>, <>, <>, <>, <>, <>, ...
    #> $ urls_expanded_url       <list> ["https://twitter.com/babiegoogie/sta...
    #> $ media_expanded_url      <list> [<>, <>, "https://twitter.com/puppete...
    #> $ mentions_user_id        <list> ["959246891555803137", <>, "385494953...
    #> $ mentions_screen_name    <list> ["whyyy158", <>, "puppeteer7777", <>,...
    #> $ lang                    <chr> "en", "ja", "ja", "ja", "ja", "ja", "p...
    #> $ quoted_status_id        <chr> "1178779339078414340", NA, NA, NA, NA,...
    #> $ quoted_text             <chr> "Taehyung smiled, held on a little bit...
    #> $ quoted_created_at       <dttm> 2019-09-30 21:11:09, NA, NA, NA, NA, ...
    #> $ quoted_source           <chr> "<a href=\"https://mobile.twitter.com\...
    #> $ quoted_favorite_count   <int> 37, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ quoted_retweet_count    <int> 0, NA, NA, NA, NA, NA, NA, NA, NA, NA,...
    #> $ quoted_user_id          <chr> "979330656730861568", NA, NA, NA, NA, ...
    #> $ quoted_screen_name      <chr> "babiegoogie", NA, NA, NA, NA, NA, NA,...
    #> $ quoted_name             <chr> "seemy \U0001f4cc new au on pinned", N...
    #> $ quoted_followers_count  <int> 2040, NA, NA, NA, NA, NA, NA, NA, NA, ...
    #> $ quoted_friends_count    <int> 243, NA, NA, NA, NA, NA, NA, NA, NA, N...
    #> $ quoted_statuses_count   <int> 46576, NA, NA, NA, NA, NA, NA, NA, NA,...
    #> $ quoted_location         <chr> "Baby Koo <U+2606> || 20 || She/Her", NA, NA,...
    #> $ quoted_description      <chr> "\U0001f51e nsfw minors dni \U0001f51e...
    #> $ quoted_verified         <lgl> FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, T...
    #> $ retweet_status_id       <chr> "1179485825605632000", NA, "1179349486...
    #> $ retweet_text            <chr> "This was so wholesome thank you so mu...
    #> $ retweet_created_at      <dttm> 2019-10-02 19:58:29, NA, 2019-10-02 1...
    #> $ retweet_source          <chr> "<a href=\"http://twitter.com/download...
    #> $ retweet_favorite_count  <int> 1, NA, 3264, NA, 6836, NA, NA, NA, NA,...
    #> $ retweet_retweet_count   <int> 1, NA, 678, NA, 1222, NA, NA, NA, NA, ...
    #> $ retweet_user_id         <chr> "959246891555803137", NA, "385494953",...
    #> $ retweet_screen_name     <chr> "whyyy158", NA, "puppeteer7777", NA, "...
    #> $ retweet_name            <chr> "\U0001f496\U0001f49c\U0001f499 squish...
    #> $ retweet_followers_count <int> 61, NA, 42918, NA, 220219, NA, NA, NA,...
    #> $ retweet_friends_count   <int> 61, NA, 42918, NA, 220219, NA, NA, NA,...
    #> $ retweet_statuses_count  <int> 4057, NA, 21432, NA, 12638, NA, NA, NA...
    #> $ retweet_location        <chr> "She/her", NA, "Tokyo", NA, "NAGOYA<U+F8FF>JA...
    #> $ retweet_description     <chr> "\U0001f353berry owns my heart\U0001f3...
    #> $ retweet_verified        <lgl> FALSE, TRUE, FALSE, TRUE, FALSE, TRUE,...
    #> $ place_url               <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ place_name              <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ place_full_name         <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ place_type              <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ country                 <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ country_code            <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ bbox_coords             <list> [<>, <>, <>, <>, <>, <>, <>, <>, <>, ...
    #> $ name                    <chr> "seemy \U0001f4cc new au on pinned", "...
    #> $ location                <chr> "Baby Koo <U+2606> || 20 || She/Her", NA, NA,...
    #> $ description             <chr> "\U0001f51e nsfw minors dni \U0001f51e...
    #> $ url                     <chr> "https://curiouscat.me/Seemy", NA, NA,...
    #> $ protected               <lgl> FALSE, FALSE, FALSE, FALSE, FALSE, FAL...
    #> $ followers_count         <int> 2040, 19, 68, 5, 0, 197, 387, 385, 266...
    #> $ friends_count           <int> 243, 9, 378, 0, 4, 196, 532, 130, 155,...
    #> $ listed_count            <int> 22, 0, 0, 0, 0, 5, 2, 0, 2, 1, 0, 1, 1...
    #> $ statuses_count          <int> 46577, 8752, 1487, 23393, 704, 4688, 9...
    #> $ favourites_count        <int> 94562, 2, 7118, 0, 685, 7306, 491, 935...
    #> $ account_created_at      <dttm> 2018-03-29 12:13:18, 2013-06-16 14:33...
    #> $ verified                <lgl> FALSE, FALSE, FALSE, FALSE, FALSE, FAL...
    #> $ account_lang            <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ profile_banner_url      <chr> "https://pbs.twimg.com/profile_banners...
    #> $ profile_image_url       <chr> "http://pbs.twimg.com/profile_images/1...
    #> $ timestamp_ms            <dttm> 2019-10-02 20:31:36, 2019-10-02 20:31...
    #> $ contributors_enabled    <lgl> TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TR...

### Scaling Up

In reality, we’re more interested in handling larger data sets. Here’s a
larger file obtained using `rtweet::stream_tweets()` that has been
compressed to an 18 Mb .gz file (153 Mb uncompressed).

``` r
rtweet_stream_path <- "inst/example-data/api-stream.json.gz"
big_rtweet_stream <- read_tweets(rtweet_stream_path)

tibble::as_tibble(big_rtweet_stream)
```

    #> # A tibble: 22,760 x 71
    #>    user_id status_id created_at          screen_name text  source
    #>    <chr>   <chr>     <dttm>              <chr>       <chr> <chr> 
    #>  1 807195~ 11780078~ 2019-09-28 18:05:23 ykaoi0327   "RT ~ "<a h~
    #>  2 114393~ 11780078~ 2019-09-28 18:05:23 yowasugi723 "@Di~ "<a h~
    #>  3 247059~ 11780078~ 2019-09-28 18:05:23 itsauroras~ "RT ~ "<a h~
    #>  4 822602~ 11780078~ 2019-09-28 18:05:23 Darrell894~ RT @~ "<a h~
    #>  5 797200~ 11780078~ 2019-09-28 18:05:23 NastyWoman~ @Bra~ "<a h~
    #>  6 110779~ 11780078~ 2019-09-28 18:05:23 DeshaunAwe~ met ~ "<a h~
    #>  7 110441~ 11780078~ 2019-09-28 18:05:23 diamondy_u  "RT ~ "<a h~
    #>  8 359294~ 11780078~ 2019-09-28 18:05:23 piyakat28   "RT ~ "<a h~
    #>  9 194250~ 11780078~ 2019-09-28 18:05:23 Stgo_centro RT @~ "<a h~
    #> 10 116013~ 11780078~ 2019-09-28 18:05:23 119lonwi_y~ RT @~ "<a h~
    #> # ... with 22,750 more rows, and 65 more variables:
    #> #   reply_to_status_id <chr>, reply_to_user_id <chr>,
    #> #   reply_to_screen_name <chr>, is_quote <lgl>, is_retweeted <lgl>,
    #> #   hashtags <list>, urls_expanded_url <list>, media_expanded_url <list>,
    #> #   mentions_user_id <list>, mentions_screen_name <list>, lang <chr>,
    #> #   quoted_status_id <chr>, quoted_text <chr>, quoted_created_at <dttm>,
    #> #   quoted_source <chr>, quoted_favorite_count <int>,
    #> #   quoted_retweet_count <int>, quoted_user_id <chr>,
    #> #   quoted_screen_name <chr>, quoted_name <chr>,
    #> #   quoted_followers_count <int>, quoted_friends_count <int>,
    #> #   quoted_statuses_count <int>, quoted_location <chr>,
    #> #   quoted_description <chr>, quoted_verified <lgl>,
    #> #   retweet_status_id <chr>, retweet_text <chr>,
    #> #   retweet_created_at <dttm>, retweet_source <chr>,
    #> #   retweet_favorite_count <int>, retweet_retweet_count <int>,
    #> #   retweet_user_id <chr>, retweet_screen_name <chr>, retweet_name <chr>,
    #> #   retweet_followers_count <int>, retweet_friends_count <int>,
    #> #   retweet_statuses_count <int>, retweet_location <chr>,
    #> #   retweet_description <chr>, retweet_verified <lgl>, place_url <chr>,
    #> #   place_name <chr>, place_full_name <chr>, place_type <chr>,
    #> #   country <chr>, country_code <chr>, bbox_coords <list>, name <chr>,
    #> #   location <chr>, description <chr>, url <chr>, protected <lgl>,
    #> #   followers_count <int>, friends_count <int>, listed_count <int>,
    #> #   statuses_count <int>, favourites_count <int>,
    #> #   account_created_at <dttm>, verified <lgl>, account_lang <chr>,
    #> #   profile_banner_url <chr>, profile_image_url <chr>,
    #> #   timestamp_ms <dttm>, contributors_enabled <lgl>

How long does that take?

``` r
library(microbenchmark)

big_rtweet_time <- microbenchmark(
  rtweet_stream = read_tweets(rtweet_stream_path),
  times = 3
)

big_rtweet_time
```

    #> Unit: seconds
    #>           expr      min       lq     mean   median       uq      max neval
    #>  rtweet_stream 2.100219 2.213702 2.256538 2.327185 2.334698 2.342211     3

### Data Dumps

People seem to love storing social media data in Elasticsearch
databases, meaning that the data collected from APIs is stored inside a
nested JSON object named `"doc"`. `"doc"` is typically embedded in a ton
of system metadata, most of which you probably don’t care about.

This has three unfortunate consequences:

1.  Packages that were purpose-built to work directly with the Twitter
    API aren’t going to play along with your data.
2.  You’re going to waste most of your time (and memory) getting data
    into R that you’re not going to use.
3.  The data are *very* tedious to restructure in R (lists of lists of
    lists of lists of lists…).

`{tweetio}` solves this by parsing everything at the C++ level, but only
returning the actual tweet data to R.

    #> [1] "173 Mb"

``` r
single_data_dump_time <- microbenchmark(

  single_data_dump_parsed <- read_tweets(single_data_dump) # ********************
  
  , times = 1
)

single_data_dump_time
```

    #> Unit: seconds
    #>                                                      expr      min
    #>  single_data_dump_parsed <- read_tweets(single_data_dump) 18.80873
    #>        lq     mean   median       uq      max neval
    #>  18.80873 18.80873 18.80873 18.80873 18.80873     1

### Bulk Processing

While maybe not “big” data, handling millions of lines of JSON spread
across dozens of files in R isn’t exactly a picnic, but
`read_tweets_bulk()` attempts to make this as easy as possible.

We can run `read_tweets_bulk()` either sequentially or in parallel. By
setting `in_parallel=` to `FALSE`, it will always run sequentially,
processing each file one at a time with `lapply()` before collapsing the
resulting data frames via `data.table::rbindlist()`.

``` r
sequential_bulk_files <- all_data_dumps[1:4]
sequential_bulk_file_size <- sum(sapply(sequential_bulk_files, file.size))

number_bytes(sequential_bulk_file_size)
```

    #> [1] "701 Mb"

``` r
sequential_bulk_time <- microbenchmark(
  
  sequential_bulk_parsed <- read_tweets_bulk(sequential_bulk_files, # **********
                                             in_parallel = FALSE)   # **********
  
  , times = 1
)

sequential_bulk_time
```

    #> Unit: seconds
    #>                                                                                         expr
    #>  sequential_bulk_parsed <- read_tweets_bulk(sequential_bulk_files,      in_parallel = FALSE)
    #>      min      lq    mean  median      uq     max neval
    #>  78.9772 78.9772 78.9772 78.9772 78.9772 78.9772     1

If `in_parallel=` is set to `TRUE` (the default) *and* `{future}` and
`{future.apply}` are available, `read_tweets_bulk()` can be run in
parallel via `future.apply::future_lapply()`.

``` r
parallel_bulk_file_size <- sum(sapply(all_data_dumps, file.size))

number_bytes(parallel_bulk_file_size)
```

    #> [1] "2 Gb"

``` r
parallel_bulk_time <- microbenchmark(
  
  read_tweets_bulk(all_data_dumps) # *****************************************
  
  , times = 1
)

parallel_bulk_time
```

    #> Unit: seconds
    #>                              expr      min       lq     mean   median
    #>  read_tweets_bulk(all_data_dumps) 88.43198 88.43198 88.43198 88.43198
    #>        uq      max neval
    #>  88.43198 88.43198     1

## Benchmarks

``` r
res <- microbenchmark(
  read_tweets(all_data_dumps[[1]]),
  read_tweets(all_data_dumps[[2]]),
  read_tweets(all_data_dumps[[3]]),
  read_tweets(all_data_dumps[[4]]),
  read_tweets(all_data_dumps[[5]]),
  read_tweets(all_data_dumps[[6]]),
  read_tweets(all_data_dumps[[7]]),
  read_tweets(all_data_dumps[[8]]),
  read_tweets(all_data_dumps[[9]]),
  read_tweets(all_data_dumps[[10]]),
  read_tweets(all_data_dumps[[11]]),
  read_tweets(all_data_dumps[[12]]),
  read_tweets(all_data_dumps[[13]]),
  read_tweets(all_data_dumps[[14]]),
  read_tweets(all_data_dumps[[15]]),
  
  times = 3
)

library(tidyverse)

bench_marks <- res %>% 
  as_tibble() %>% 
  mutate(file_size = expr %>% 
           str_extract("(?<=\\().*(?=\\)$)") %>% 
           map_chr(~ eval(parse(text = .x))) %>% 
           file.size()
           ) %>% 
  mutate(time = time / 1e9)

bench_marks %>% 
  ggplot(aes(x = file_size, y = time, color = factor(file_size))) +
  ggbeeswarm::geom_quasirandom() +
  guides(color = FALSE, size = FALSE) +
  labs(x = ".jsonl.gz File Size", y = "seconds") +
  scale_x_continuous(
    labels = function(.x) number_bytes(.x, symbol = "Mb", big.mark = ",")
  ) +
  coord_flip() +
  theme_minimal(base_size = 14, base_family = "serif") +
  theme(legend.position = "bottom")
```

<img src="man/figures/unnamed-chunk-13-1.png" style="display: block; margin: auto;" />

Until Rtools 4.0 hits (or the
[`simdjson`](https://github.com/lemire/simdjson) library decides to
[relax its C++17
requirement](https://github.com/lemire/simdjson/issues/307)), I’m not
sure how we can go much faster while maintaining cross-platform
compatibility. That said, if C++ is your mother tongue (and you see room
for optimization), please don’t hesitate to contribute.

## Acknowledgements

`{tweetio}` uses a combination of C++ via
[`{Rcpp}`](http://www.rcpp.org/), the
[`rapidjson`](http://rapidjson.org/) C++ library (made available by
[`{rapidjsonr}`](https://cran.r-project.org/web/packages/rapidjsonr/index.html)),
and **R’s secret weapon**:
[`{data.table}`](https://rdatatable.gitlab.io/data.table/).

Major inspiration from [{`ndjson`}](https://gitlab.com/hrbrmstr/ndjson)
was taken, including its use of
[`Gzstream`](https://www.cs.unc.edu/Research/compgeom/gzstream/).
