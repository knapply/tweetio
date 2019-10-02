
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
vendor, or some other source, `{tweetio}`’s job is to get them into R.

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

    #> Rows: 507
    #> Columns: 71
    #> $ user_id                 <chr> "483273973", "1160529558518370306", "5...
    #> $ status_id               <chr> "1179487978936324096", "11794879831429...
    #> $ created_at              <dttm> 2019-10-02 20:07:02, 2019-10-02 20:07...
    #> $ screen_name             <chr> "jschwabish", "hakataanchiba", "linemo...
    #> $ text                    <chr> "@SYoungLaura @infowetrust @Jasonforre...
    #> $ source                  <chr> "<a href=\"https://mobile.twitter.com\...
    #> $ reply_to_status_id      <chr> "1179470291178790914", NA, NA, "117948...
    #> $ reply_to_user_id        <chr> "2939811821", NA, NA, "969079130544398...
    #> $ reply_to_screen_name    <chr> "SYoungLaura", NA, NA, "kyojaeminx", N...
    #> $ is_quote                <lgl> FALSE, FALSE, FALSE, FALSE, FALSE, FAL...
    #> $ is_retweeted            <lgl> FALSE, FALSE, FALSE, FALSE, FALSE, FAL...
    #> $ hashtags                <list> [<>, <>, <>, <>, "<U+0E02><U+0E1A><U+0E27><U+0E19><U+0E40><U+0E2A><U+0E14><U+0E47><U+0E08>", <>, <>,...
    #> $ urls_expanded_url       <list> ["https://twitter.com/i/web/status/11...
    #> $ media_expanded_url      <list> ["https://twitter.com/jschwabish/stat...
    #> $ mentions_user_id        <list> [<"2939811821", "1912054296", "102392...
    #> $ mentions_screen_name    <list> [<"SYoungLaura", "infowetrust", "Jaso...
    #> $ lang                    <chr> "en", "ja", "ja", "th", "th", "en", "k...
    #> $ quoted_status_id        <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ quoted_text             <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ quoted_created_at       <dttm> NA, NA, NA, NA, NA, NA, NA, NA, NA, N...
    #> $ quoted_source           <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ quoted_favorite_count   <int> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ quoted_retweet_count    <int> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ quoted_user_id          <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ quoted_screen_name      <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ quoted_name             <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ quoted_followers_count  <int> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ quoted_friends_count    <int> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ quoted_statuses_count   <int> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ quoted_location         <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ quoted_description      <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ quoted_verified         <lgl> TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TR...
    #> $ retweet_status_id       <chr> NA, NA, NA, NA, "1179208164392108033",...
    #> $ retweet_text            <chr> NA, NA, NA, NA, "<U+0E19><U+0E49><U+0E33><U+0E15><U+0E32><U+0E44><U+0E2B><U+0E25><U+0E1E><U+0E23><U+0E32><U+0E01> \n<U+0E2D><U+0E22><U+0E39><U+0E48><U+0E20><U+0E32>...
    #> $ retweet_created_at      <dttm> NA, NA, NA, NA, 2019-10-02 01:35:09, ...
    #> $ retweet_source          <chr> NA, NA, NA, NA, "<a href=\"http://twit...
    #> $ retweet_favorite_count  <int> NA, NA, NA, NA, 4854, 353, NA, NA, 3, ...
    #> $ retweet_retweet_count   <int> NA, NA, NA, NA, 16440, 44, NA, NA, 2, ...
    #> $ retweet_user_id         <chr> NA, NA, NA, NA, "2228170369", "2152079...
    #> $ retweet_screen_name     <chr> NA, NA, NA, NA, "parnerii", "kurteiche...
    #> $ retweet_name            <chr> NA, NA, NA, NA, "<U+0E19><U+0E31><U+0E07><U+0E23><U+0E35><U+0E48> \U0001f353\U00...
    #> $ retweet_followers_count <int> NA, NA, NA, NA, 79, 460217, NA, NA, 21...
    #> $ retweet_friends_count   <int> NA, NA, NA, NA, 79, 460217, NA, NA, 21...
    #> $ retweet_statuses_count  <int> NA, NA, NA, NA, 226, 75920, NA, NA, 25...
    #> $ retweet_location        <chr> NA, NA, NA, NA, NA, NA, NA, NA, "<U+062D><U+0627><U+0626><U+0644>,...
    #> $ retweet_description     <chr> NA, NA, NA, NA, "<U+0E2B><U+0E32><U+0E2A><U+0E32><U+0E23><U+0E30><U+0E2D><U+0E30><U+0E44><U+0E23><U+0E44><U+0E21><U+0E48><U+0E44><U+0E14><U+0E49><U+0E19><U+0E2D><U+0E01><U+0E08><U+0E32>...
    #> $ retweet_verified        <lgl> TRUE, TRUE, TRUE, TRUE, FALSE, TRUE, T...
    #> $ place_url               <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ place_name              <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ place_full_name         <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ place_type              <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ country                 <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ country_code            <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ bbox_coords             <list> [<>, <>, <>, <>, <>, <>, <>, <>, <>, ...
    #> $ name                    <chr> "Jon Schwabish", "<U+96A0><U+308C><U+5BB6><U+500B><U+5BA4> <U+306F><U+304B><U+305F><U+5EB5> <U+5343><U+8449><U+99C5><U+524D><U+5E97>", "...
    #> $ location                <chr> "Washington, DC", NA, NA, "#liveinkyoh...
    #> $ description             <chr> "Economist, DataViz & Presentations | ...
    #> $ url                     <chr> "http://www.PolicyViz.com", NA, NA, NA...
    #> $ protected               <lgl> FALSE, FALSE, FALSE, FALSE, FALSE, FAL...
    #> $ followers_count         <int> 11778, 2, 8, 223, 192, 530, 4, 1029, 2...
    #> $ friends_count           <int> 977, 0, 56, 172, 691, 187, 4, 1743, 46...
    #> $ listed_count            <int> 771, 0, 0, 1, 3, 37, 0, 1, 23, 16, 7, ...
    #> $ statuses_count          <int> 13691, 1238, 541, 20216, 54003, 171906...
    #> $ favourites_count        <int> 3465, 0, 0, 1722, 645, 218300, 1, 0, 4...
    #> $ account_created_at      <dttm> 2012-02-04 20:44:17, 2019-08-11 12:33...
    #> $ verified                <lgl> TRUE, FALSE, FALSE, FALSE, FALSE, FALS...
    #> $ account_lang            <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ profile_banner_url      <chr> "https://pbs.twimg.com/profile_banners...
    #> $ profile_image_url       <chr> "http://pbs.twimg.com/profile_images/1...
    #> $ timestamp_ms            <dttm> 2019-10-02 20:07:02, 2019-10-02 20:07...
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
    #>  rtweet_stream 2.190256 2.279855 2.327818 2.369454 2.396599 2.423744     3

### Vendor Data

Vendors seem to love storing social media data in Elasticsearch
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
single_vendor_time <- microbenchmark(

  single_vendor_parsed <- read_tweets(single_vendor_file) # ********************
  
  , times = 1
)

single_vendor_time
```

    #> Unit: seconds
    #>                                                     expr      min       lq
    #>  single_vendor_parsed <- read_tweets(single_vendor_file) 18.69416 18.69416
    #>      mean   median       uq      max neval
    #>  18.69416 18.69416 18.69416 18.69416     1

### Bulk Processing

While maybe not “big” data, handling millions of lines of JSON spread
across dozens of files in R isn’t exactly a picnic, but
`read_tweets_bulk()` attempts to make this as easy as possible.

We can run `read_tweets_bulk()` either sequentially or in parallel. By
setting `in_parallel=` to `FALSE`, it will always run sequentially,
processing each file one at a time with `lapply()` before collapsing the
resulting data frames via `data.table::rbindlist()`.

``` r
sequential_bulk_files <- all_vendor_files[1:4]
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
    #>       min       lq     mean   median       uq      max neval
    #>  76.76723 76.76723 76.76723 76.76723 76.76723 76.76723     1

If `in_parallel=` is set to `TRUE` (the default) *and* `{future}` and
`{future.apply}` are available, `read_tweets_bulk()` can be run in
parallel via `future.apply::future_lapply()`.

``` r
parallel_bulk_file_size <- sum(sapply(all_vendor_files, file.size))

number_bytes(parallel_bulk_file_size)
```

    #> [1] "2 Gb"

``` r
parallel_bulk_time <- microbenchmark(
  
  read_tweets_bulk(all_vendor_files) # *****************************************
  
  , times = 1
)

parallel_bulk_time
```

    #> Unit: seconds
    #>                                expr      min       lq     mean   median
    #>  read_tweets_bulk(all_vendor_files) 91.17387 91.17387 91.17387 91.17387
    #>        uq      max neval
    #>  91.17387 91.17387     1

## Benchmarks

``` r
res <- microbenchmark(
  read_tweets(all_vendor_files[[1]]),
  read_tweets(all_vendor_files[[2]]),
  read_tweets(all_vendor_files[[3]]),
  read_tweets(all_vendor_files[[4]]),
  read_tweets(all_vendor_files[[5]]),
  read_tweets(all_vendor_files[[6]]),
  read_tweets(all_vendor_files[[7]]),
  read_tweets(all_vendor_files[[8]]),
  read_tweets(all_vendor_files[[9]]),
  read_tweets(all_vendor_files[[10]]),
  read_tweets(all_vendor_files[[11]]),
  read_tweets(all_vendor_files[[12]]),
  read_tweets(all_vendor_files[[13]]),
  read_tweets(all_vendor_files[[14]]),
  read_tweets(all_vendor_files[[15]]),
  
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
  ggplot(aes(x = file_size, y = time,
             color = factor(file_size), size = file_size)) +
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
