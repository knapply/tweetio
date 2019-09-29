
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
[![Depends](https://img.shields.io/badge/Depends-GNU_R%3E=3.6-blue.svg)](https://www.r-project.org/)
[![GitHub code size in
bytes](https://img.shields.io/github/languages/code-size/knapply/tweetio.svg)](https://github.com/knapply/tweetio)
[![HitCount](http://hits.dwyl.io/knapply/tweetio.svg)](http://hits.dwyl.io/knapply/tweetio)
<!-- badges: end -->

# Introduction

**The [`{rtweet}`](https://rtweet.info/) package spoils R users
*rotten*, in the best possible way**. The behind-the-scenes data
carpentry is so seamless that the user doesn’t need to know anything
about the horrors of Twitter data, which is pretty amazing. If you use
`{rtweet}`, you owe Mike Kearney some serious gratitude/citations.

`{tweetio}` is **not** a competitor to `{rtweet}`, but it definitely
attempts to emulate its data frame schema because…

1.  It’s incredibly easy to use.
2.  It’d be a waste not to maximize compatibiltiy with tools built
    specifically around `{rtweet}`’s data frames.

<center>

<h4>

<i> *You* bring the data, `{tweetio}` gets it into R. </i>

</h4>

</center>

`{tweetio}` only focuses on one thing: **going from raw tweets to
`{rtweet}`-style data frames (or other useful structures) as quickly and
efficiently as possible**. Whether the data came from the Twitter API, a
vendor, or some other source, `{tweetio}`’s job is to get into R.

## Installation

You’ll need a C++ compiler. If you’re using Windows, that means
[Rtools](https://cran.r-project.org/bin/windows/Rtools/).

``` r
# install.packages("remotes")
remotes::install_github("knapply/tweetio")
```

## Usage

### Simple Example

First, we’ll save a stream of tweets using `rtweet::stream_tweets()`.
We’ll set `timeout=` to `15` seconds here, but in a real scenario you
would likely be streaming for *much* longer.

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

    #> Rows: 703
    #> Columns: 71
    #> $ user_id                 <chr> "1123949520579112962", "350969837", "8...
    #> $ status_id               <chr> "1178346209695715328", "11783462222911...
    #> $ created_at              <dttm> 2019-09-29 16:30:03, 2019-09-29 16:30...
    #> $ screen_name             <chr> "wtfpurple1", "ACR_POKER", "jiyarsiexx...
    #> $ text                    <chr> "RT @wabiars: Non esiste età per diven...
    #> $ source                  <chr> "<a href=\"http://twitter.com/download...
    #> $ reply_to_status_id      <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ reply_to_user_id        <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ reply_to_screen_name    <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ is_quote                <lgl> TRUE, FALSE, FALSE, FALSE, FALSE, FALS...
    #> $ is_retweeted            <lgl> FALSE, FALSE, FALSE, FALSE, FALSE, FAL...
    #> $ hashtags                <list> [NA, <"ACR", "Poker", "HighFive", "Po...
    #> $ urls_expanded_url       <list> [NA, "http://ow.ly/VCI150w93Qr", NA, ...
    #> $ media_expanded_url      <list> [NA, "https://twitter.com/ACR_POKER/s...
    #> $ mentions_user_id        <list> ["1159086388953976832", NA, NA, NA, N...
    #> $ mentions_screen_name    <list> ["wabiars", NA, NA, NA, NA, "pentagra...
    #> $ lang                    <chr> "it", "en", "tl", "ja", "ja", "und", "...
    #> $ quoted_status_id        <chr> "1178317071819649025", NA, NA, NA, NA,...
    #> $ quoted_text             <chr> "Siete proprio degli incoerenti, se un...
    #> $ quoted_created_at       <dttm> 2019-09-29 14:34:16, NA, NA, NA, NA, ...
    #> $ quoted_source           <chr> "<a href=\"http://twitter.com/download...
    #> $ quoted_favorite_count   <int> 17, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ quoted_retweet_count    <int> 1, NA, NA, NA, NA, NA, NA, NA, NA, NA,...
    #> $ quoted_user_id          <chr> "1000007406892601344", NA, NA, NA, NA,...
    #> $ quoted_screen_name      <chr> "vxrtigini", NA, NA, NA, NA, NA, NA, N...
    #> $ quoted_name             <chr> "rob\U0001f981", NA, NA, NA, NA, NA, N...
    #> $ quoted_followers_count  <int> 1651, NA, NA, NA, NA, NA, NA, NA, NA, ...
    #> $ quoted_friends_count    <int> 1545, NA, NA, NA, NA, NA, NA, NA, NA, ...
    #> $ quoted_statuses_count   <int> 3771, NA, NA, NA, NA, NA, NA, NA, NA, ...
    #> $ quoted_location         <chr> "Sesto San Giovanni, Lombardia", NA, N...
    #> $ quoted_description      <chr> "sono una diciassettenne, locals, disl...
    #> $ quoted_verified         <lgl> FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, T...
    #> $ retweet_status_id       <chr> "1178336866006949889", NA, NA, NA, NA,...
    #> $ retweet_text            <chr> "Non esiste età per diventare genitori...
    #> $ retweet_created_at      <dttm> 2019-09-29 15:52:55, NA, NA, NA, NA, ...
    #> $ retweet_source          <chr> "<a href=\"http://twitter.com/download...
    #> $ retweet_favorite_count  <int> 2, NA, NA, NA, NA, 218, 1350, NA, 15, ...
    #> $ retweet_retweet_count   <int> 1, NA, NA, NA, NA, 68, 312, NA, 6, 541...
    #> $ retweet_user_id         <chr> "1159086388953976832", NA, NA, NA, NA,...
    #> $ retweet_screen_name     <chr> "wabiars", NA, NA, NA, NA, "pentagram6...
    #> $ retweet_name            <chr> "<U+263E>", NA, NA, NA, NA, "PENTAGRAM", "<U+6708><U+520A><U+30A8>...
    #> $ retweet_followers_count <int> 788, NA, NA, NA, NA, 29686, 43048, NA,...
    #> $ retweet_friends_count   <int> 788, NA, NA, NA, NA, 29686, 43048, NA,...
    #> $ retweet_statuses_count  <int> 4044, NA, NA, NA, NA, 1682, 9012, NA, ...
    #> $ retweet_location        <chr> "Italy \U0001f1ee\U0001f1f9", NA, NA, ...
    #> $ retweet_description     <chr> "<U+21B3> \U0001d4d3\U0001d4f2\U0001d4ec\U000...
    #> $ retweet_verified        <lgl> FALSE, TRUE, TRUE, TRUE, TRUE, FALSE, ...
    #> $ place_url               <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ place_name              <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ place_full_name         <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ place_type              <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ country                 <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ country_code            <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ bbox_coords             <list> [<>, <>, <>, <>, <>, <>, <>, <>, <>, ...
    #> $ name                    <chr> "\U0001d4d2\U0001d4fb\U0001d4f2", "Ame...
    #> $ location                <chr> "Roma, Lazio", NA, "PH", NA, NA, NA, "...
    #> $ description             <chr> "italian girl // 18 // books // make u...
    #> $ url                     <chr> "https://www.instagram.com/_ccriistina...
    #> $ protected               <lgl> FALSE, FALSE, FALSE, FALSE, FALSE, FAL...
    #> $ followers_count         <int> 271, 16322, 82, 90, 7, 0, 210, 365, 21...
    #> $ friends_count           <int> 454, 327, 432, 74, 36, 63, 187, 318, 1...
    #> $ listed_count            <int> 0, 101, 0, 4, 0, 0, 13, 0, 16, 0, 0, 5...
    #> $ statuses_count          <int> 2380, 14441, 1502, 1412, 1838, 1875, 6...
    #> $ favourites_count        <int> 3823, 4826, 1305, 2860, 13, 1419, 9116...
    #> $ account_created_at      <dttm> 2019-05-02 13:57:02, 2011-08-08 15:59...
    #> $ verified                <lgl> FALSE, FALSE, FALSE, FALSE, FALSE, FAL...
    #> $ account_lang            <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ profile_banner_url      <chr> "https://pbs.twimg.com/profile_banners...
    #> $ profile_image_url       <chr> "http://pbs.twimg.com/profile_images/1...
    #> $ timestamp_ms            <dttm> 2019-09-29 16:30:03, 2019-09-29 16:30...
    #> $ contributors_enabled    <lgl> TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TR...

### Scaling Up

In reality, we’re more interested in handling larger data sets. Here’s a
larger file obtained using `rtweet::stream_tweets()` that has been
compressed to an 18 Mb .gz file (153 Mb uncompressed).

``` r
big_rtweet_stream <- read_tweets("inst/example-data/api-stream.json.gz")
dim(big_rtweet_stream)
```

    #> [1] 22760    71

That’s 22,760 tweets, but how long does that take?

``` r
big_rtweet_time <- microbenchmark::microbenchmark(
  ".153" = read_tweets("inst/example-data/api-stream.json.gz"),
  times = 3
)
big_rtweet_time
```

    #> Unit: seconds
    #>  expr      min       lq     mean   median       uq      max neval
    #>  .153 2.928574 2.942927 2.976011 2.957281 2.999729 3.042177     3

### Vendor Data

It seems that the trend for third-party data vendors is to embed what
the APIs provide inside a JSON object named `"doc"`, which is typically
embedded in a ton of platform metadata (that you probably don’t care
about).

This has three unfortunate consequences:

1.  Packages that were purpose-built to work directly with the Twitter
    API aren’t going to play along with your data.
2.  You’re going to waste most of your time and computational resources
    on getting data into R that you’re not going to use.
3.  The data are *very* tedious to restructure in R (lists of lists of
    lists of lists of lists…).

`{tweetio}` solves this by parsing everything at the C++ level, but only
returning the actual tweet data to R. Here’s an example.

The only difference between reading data following this nested `"doc"`
convention and `"normal"` data is that the user must set `type=` to
`"nested_doc"`. This will likely be simplified to auto-detect the data’s
structure in the future.

``` r
single_vendor_parsed <- read_tweets(single_vendor_file, type = "nested_doc")
dim(single_vendor_parsed)
```

    #> [1] 94139    71

That’s 94,139, but about how long does that take?

``` r
single_vendor_time <- microbenchmark::microbenchmark(
  "1.6" = read_tweets(single_vendor_file, type = "nested_doc"),
  times = 3
)
single_vendor_time
```

    #> Unit: seconds
    #>  expr      min       lq     mean   median       uq      max neval
    #>   1.6 19.24221 19.45889 19.71331 19.67558 19.94887 20.22216     3

### Bulk Processing

While maybe not “big” data, handling millions of lines of JSON spread
across dozens of files in R isn’t exactly a picnic. To handle this
situation, the current implementation uses `furrr::future_map()` to
process each file in parallel before collapsing the resulting data
frames via `data.table::rbindlist()`.

`all_vendor_files` consists of 6 Gb (47 Gb uncompressed) spread across
30 files, which we can still process using `tweetio::read_tweets()`.

``` r
bulk_parsed <- read_tweets(all_vendor_files, type = "nested_doc", 
                           .progress = FALSE)
dim(bulk_parsed)
```

    #> [1] 2626381      71

How long does that take?

``` r
bulk_time <- microbenchmark::microbenchmark(
  "47" = read_tweets(all_vendor_files, type = "nested_doc", 
                           .progress = FALSE),
  times = 1
)
bulk_time
```

    #> Unit: seconds
    #>  expr     min      lq    mean  median      uq     max neval
    #>    47 167.197 167.197 167.197 167.197 167.197 167.197     1

## Benchmarks

``` r
res <- do.call(rbind, list(big_rtweet_time, single_vendor_time, bulk_time))

library(dplyr)
library(ggplot2)

res %>% 
  mutate(file_size = paste(expr, "Gb"),
         time = time / 1e+09,
         `parallel?` = expr == "47") %>% 
  ggplot(aes(x = file_size, y = time, 
             color = file_size, size = as.numeric(expr), shape = `parallel?`)) +
  ggbeeswarm::geom_quasirandom() +
  scale_y_log10() +
  guides(color = FALSE, size = FALSE) +
  labs(x = "Size (uncompressed)", y = "seconds") +
  coord_flip() +
  theme_minimal(base_size = 14, base_family = "serif") +
  theme(legend.position = "bottom")
```

<img src="man/figures/unnamed-chunk-12-1.png" style="display: block; margin: auto;" />

Until Rtools 4.0 hits (or the
[`simdjson`](https://github.com/lemire/simdjson) library decides to
[relax its C++17
requirement](https://github.com/lemire/simdjson/issues/307)), I’m not
sure how we can go much faster while maintaining cross-platform
compatibility. That said, if C++ is your mother tongue (and you see room
for optimization), please don’t hesitate to contribute.

## Acknowledgements

`{tweetio}` uses a combination of C++ via
[`{Rcpp}`](http://www.rcpp.org/l), the
[`rapidjson`](http://rapidjson.org/) C++ library (made available by
[`{rapidjsonr}`](https://cran.r-project.org/web/packages/rapidjsonr/index.html)),
and **R’s secret weapon**:
[`{data.table}`](https://rdatatable.gitlab.io/data.table/).

Major inspiration from [{`ndjson`}](https://gitlab.com/hrbrmstr/ndjson)
was taken, including its use of
[`Gzstream`](https://www.cs.unc.edu/Research/compgeom/gzstream/).

Parallel processing of multiple files is (currently) handled by
[`{future}`](https://cran.r-project.org/web/packages/future/index.html)
and [`{furrr}`](https://davisvaughan.github.io/furrr/), if available.
