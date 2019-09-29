
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
*rotten*… in the best possible way**. The behind-the-scenes data
carpentry is so seamless that the user doesn’t need to know anything
about the horrors of Twitter data, which is pretty amazing. If you use
`{rtweet}`, you owe Mike Kearney some serious gratitude/citations.

`{tweetio}` is **not** a competitor to `{rtweet}`, but it definitely
attempts to emulate its data frame schema because…

1.  It’s incredibly easy to use.
2.  It’d be a waste not to maximize compatibiltiy with tools built
    specifically around `{rtweet}`’s data frames.

> ***You** bring the data, `{tweetio}` gets them into R.*

`{tweetio}` only focuses on one thing: **going from raw tweets to
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

    #> Rows: 640
    #> Columns: 71
    #> $ user_id                 <chr> "1159392630595211265", "78249062825700...
    #> $ status_id               <chr> "1178356510889365504", "11783565108977...
    #> $ created_at              <dttm> 2019-09-29 17:10:59, 2019-09-29 17:10...
    #> $ screen_name             <chr> "6BOF7EBKpWnS3kI", "zuma2513", "noonam...
    #> $ text                    <chr> "RT @FRANKYOUNG1995: <U+6027><U+6B32><U+5F88><U+5F3A><U+7684><U+8584><U+808C><U+4F53><U+80B2><U+751F><U+5BBF><U+820D><U+731B><U+64CD><U+98DE><U+673A><U+676F>...
    #> $ source                  <chr> "<a href=\"http://twitter.com/download...
    #> $ reply_to_status_id      <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, "1...
    #> $ reply_to_user_id        <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, "1...
    #> $ reply_to_screen_name    <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, "D...
    #> $ is_quote                <lgl> FALSE, FALSE, FALSE, FALSE, FALSE, FAL...
    #> $ is_retweeted            <lgl> FALSE, FALSE, FALSE, FALSE, FALSE, FAL...
    #> $ hashtags                <list> [NA, <"HondaATfunfestXKristSingto", "...
    #> $ urls_expanded_url       <list> [NA, NA, NA, NA, "https://www.yodobas...
    #> $ media_expanded_url      <list> ["https://twitter.com/FRANKYOUNG1995/...
    #> $ mentions_user_id        <list> ["1031411155481198592", "77742516", "...
    #> $ mentions_screen_name    <list> ["FRANKYOUNG1995", "__crazyray", "pro...
    #> $ lang                    <chr> "zh", "th", "tl", "ja", "ja", "th", "p...
    #> $ quoted_status_id        <chr> NA, NA, NA, NA, NA, NA, NA, "117818380...
    #> $ quoted_text             <chr> NA, NA, NA, NA, NA, NA, NA, "deenikant...
    #> $ quoted_created_at       <dttm> NA, NA, NA, NA, NA, NA, NA, 2019-09-2...
    #> $ quoted_source           <chr> NA, NA, NA, NA, NA, NA, NA, "<a href=\...
    #> $ quoted_favorite_count   <int> NA, NA, NA, NA, NA, NA, NA, 580, NA, N...
    #> $ quoted_retweet_count    <int> NA, NA, NA, NA, NA, NA, NA, 187, NA, N...
    #> $ quoted_user_id          <chr> NA, NA, NA, NA, NA, NA, NA, "113983922...
    #> $ quoted_screen_name      <chr> NA, NA, NA, NA, NA, NA, NA, "Only_Mani...
    #> $ quoted_name             <chr> NA, NA, NA, NA, NA, NA, NA, ",", NA, N...
    #> $ quoted_followers_count  <int> NA, NA, NA, NA, NA, NA, NA, 1861, NA, ...
    #> $ quoted_friends_count    <int> NA, NA, NA, NA, NA, NA, NA, 358, NA, N...
    #> $ quoted_statuses_count   <int> NA, NA, NA, NA, NA, NA, NA, 45434, NA,...
    #> $ quoted_location         <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ quoted_description      <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ quoted_verified         <lgl> TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TR...
    #> $ retweet_status_id       <chr> "1177802236635664384", "11783408364314...
    #> $ retweet_text            <chr> "<U+6027><U+6B32><U+5F88><U+5F3A><U+7684><U+8584><U+808C><U+4F53><U+80B2><U+751F><U+5BBF><U+820D><U+731B><U+64CD><U+98DE><U+673A><U+676F>,<U+55B7><U+5230><U+7B2C><U+4E94><U+80A1><U+65F6><U+820D><U+53CB><U+63A8><U+95E8><U+800C><U+5165><U+3002>(fake ...
    #> $ retweet_created_at      <dttm> 2019-09-28 04:28:30, 2019-09-29 16:08...
    #> $ retweet_source          <chr> "<a href=\"http://twitter.com/download...
    #> $ retweet_favorite_count  <int> 2986, 61, 0, 76, 1725, 12, 7, 294, NA,...
    #> $ retweet_retweet_count   <int> 973, 110, 1, 25, 13463, 9, 1, 141, NA,...
    #> $ retweet_user_id         <chr> "1031411155481198592", "77742516", "29...
    #> $ retweet_screen_name     <chr> "FRANKYOUNG1995", "__crazyray", "produ...
    #> $ retweet_name            <chr> "Frankyoung1995\u26bd<U+FE0F>", "c R A z Y", ...
    #> $ retweet_followers_count <int> 94350, 8946, 56701, 1427, 388226, 418,...
    #> $ retweet_friends_count   <int> 94350, 8946, 56701, 1427, 388226, 418,...
    #> $ retweet_statuses_count  <int> 46, 35040, 111903, 3019, 12735, 82031,...
    #> $ retweet_location        <chr> "Beijing,China", "BKK, TH", "RULES:", ...
    #> $ retweet_description     <chr> "<U+5317><U+4EAC> 182 70 24 10<U+4E0D><U+5206> \u26bd<U+FE0F> Say hi with...
    #> $ retweet_verified        <lgl> FALSE, FALSE, FALSE, FALSE, TRUE, FALS...
    #> $ place_url               <chr> NA, NA, NA, NA, NA, NA, NA, NA, "https...
    #> $ place_name              <chr> NA, NA, NA, NA, NA, NA, NA, NA, "Penaf...
    #> $ place_full_name         <chr> NA, NA, NA, NA, NA, NA, NA, NA, "Penaf...
    #> $ place_type              <chr> NA, NA, NA, NA, NA, NA, NA, NA, "city"...
    #> $ country                 <chr> NA, NA, NA, NA, NA, NA, NA, NA, "Portu...
    #> $ country_code            <chr> NA, NA, NA, NA, NA, NA, NA, NA, "PT", ...
    #> $ bbox_coords             <list> [<>, <>, <>, <>, <>, <>, <>, <>, <1.7...
    #> $ name                    <chr> "Chrissy", "Blueheart", "L I A", "<U+6C41>", ...
    #> $ location                <chr> NA, NA, NA, NA, NA, NA, "es", NA, "Pen...
    #> $ description             <chr> "<U+7535><U+5F71>", NA, "JUNG HOSEOK's \U0001f4ab", ...
    #> $ url                     <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ protected               <lgl> FALSE, FALSE, FALSE, FALSE, FALSE, FAL...
    #> $ followers_count         <int> 0, 59, 59, 54, 490, 58, 1487, 10, 2451...
    #> $ friends_count           <int> 105, 255, 85, 163, 4390, 459, 2635, 32...
    #> $ listed_count            <int> 0, 0, 0, 0, 4, 0, 0, 0, 2, 3, 0, 2, 3,...
    #> $ statuses_count          <int> 119, 131612, 2006, 1600, 89469, 37585,...
    #> $ favourites_count        <int> 23, 189863, 74, 6391, 114961, 2866, 23...
    #> $ account_created_at      <dttm> 2019-08-08 09:15:18, 2016-10-02 08:01...
    #> $ verified                <lgl> FALSE, FALSE, FALSE, FALSE, FALSE, FAL...
    #> $ account_lang            <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ profile_banner_url      <chr> NA, "https://pbs.twimg.com/profile_ban...
    #> $ profile_image_url       <chr> "http://pbs.twimg.com/profile_images/1...
    #> $ timestamp_ms            <dttm> 2019-09-29 17:10:59, 2019-09-29 17:10...
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
    #>  expr      min       lq     mean   median       uq     max neval
    #>  .153 3.417068 3.440061 3.558801 3.463055 3.629668 3.79628     3

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
returning the actual tweet data to R.

The only difference between reading data following this nested `"doc"`
convention and `"normal"` data is that the user must set `type=` to
`"nested_doc"`. This will likely be simplified to auto-detect the schema
in the future.

``` r
single_vendor_parsed <- read_tweets(single_vendor_file, type = "nested_doc")
dim(single_vendor_parsed)
```

    #> [1] 94139    71

That’s 94,139 tweets, but about how long does that take?

``` r
single_vendor_time <- microbenchmark::microbenchmark(
  "1.6" = read_tweets(single_vendor_file, type = "nested_doc"),
  times = 3
)
single_vendor_time
```

    #> Unit: seconds
    #>  expr      min      lq     mean   median       uq      max neval
    #>   1.6 19.64517 20.1786 20.56491 20.71203 21.02478 21.33752     3

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
    #>  expr      min       lq     mean   median       uq      max neval
    #>    47 223.1532 223.1532 223.1532 223.1532 223.1532 223.1532     1

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
[`{Rcpp}`](http://www.rcpp.org/), the
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
