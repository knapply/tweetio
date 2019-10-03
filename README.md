
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

> ***You** bring the tweets, `{tweetio}` gets them into R.*

`{tweetio}` focuses on one thing: **going from raw tweets to
`{rtweet}`-style data frames (or other useful structures) as quickly and
efficiently as possible**. Whether the data came from the Twitter API, a
database dump, or some other source, `{tweetio}`’s job is to get them
into R.

## Installation

You’ll need a C++ compiler. You can check if you’re ready to go by
running the following code:

``` r
# install.packages("pkgbuild")
pkgbuild::check_build_tools()
```

If you don’t have a compiler and you’re using Windows, you’ll need
[Rtools](https://cran.r-project.org/bin/windows/Rtools/).

You probably want to follow the page’s advice and select the recommended
version, which is currently Rtools35.exe. When you’re installing Rtools,
you need to make sure you check the box stating “Add rtools to system
PATH”. It looks something like this:

<!-- <img src="inst/www/rtools-path-checkbox.jpg" width="300" /> -->

<img src="inst/www/rtools-path-checkbox.jpg" style="display: block; margin: auto;" />

<br>

I have needed to reboot every computer on which I’ve installed Rtools
before I could compile an R package.

Once you’re done, you can install `{tweetio}`.

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

    #> Rows: 725
    #> Columns: 71
    #> $ user_id                 <chr> "189405724", "1168620106156519424", "1...
    #> $ status_id               <chr> "1179791340344758277", "11797913403447...
    #> $ created_at              <dttm> 2019-10-03 16:12:29, 2019-10-03 16:12...
    #> $ screen_name             <chr> "dtdwtd", "DeranT5", "black_chocopie_"...
    #> $ text                    <chr> "<U+3057><U+3093><U+3069><U+3044><U+308F><U+306D>", "RT @mixcoacgay: Miércoles G...
    #> $ source                  <chr> "<a href=\"http://twitter.com/download...
    #> $ reply_to_status_id      <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ reply_to_user_id        <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ reply_to_screen_name    <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ is_quote                <lgl> FALSE, FALSE, FALSE, FALSE, FALSE, FAL...
    #> $ is_retweeted            <lgl> FALSE, FALSE, FALSE, FALSE, FALSE, FAL...
    #> $ hashtags                <list> [<>, <>, <"<U+30E4><U+30D0><U+3044><U+305D><U+308D><U+305D><U+308D><U+98A8><U+90AA><U+3072><U+304F><U+304B><U+306A>", "<U+30A4><U+30F3><U+30D5><U+30EB><U+3082><U+6D41><U+884C><U+308A><U+3060>...
    #> $ urls_expanded_url       <list> [<>, <>, <>, <>, <>, <>, <>, <>, <>, ...
    #> $ media_expanded_url      <list> [<>, <>, <>, <>, <>, "https://twitter...
    #> $ mentions_user_id        <list> [<>, "901840595932520448", <>, <>, <>...
    #> $ mentions_screen_name    <list> [<>, "mixcoacgay", <>, <>, <>, "moszs...
    #> $ lang                    <chr> "ja", "es", "ja", "ja", "en", "th", "j...
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
    #> $ retweet_status_id       <chr> NA, "1179514361745948674", NA, NA, NA,...
    #> $ retweet_text            <chr> NA, "Miércoles Godinez \nQuédate con a...
    #> $ retweet_created_at      <dttm> NA, 2019-10-02 21:51:52, NA, NA, NA, ...
    #> $ retweet_source          <chr> NA, "<a href=\"http://twitter.com/down...
    #> $ retweet_favorite_count  <int> NA, 60, NA, NA, NA, 1035, 517, NA, 334...
    #> $ retweet_retweet_count   <int> NA, 23, NA, NA, NA, 1850, 89, NA, 301,...
    #> $ retweet_user_id         <chr> NA, "901840595932520448", NA, NA, NA, ...
    #> $ retweet_screen_name     <chr> NA, "mixcoacgay", NA, NA, NA, "moszsee...
    #> $ retweet_name            <chr> NA, "Mixcoac Gay", NA, NA, NA, "MM <U+10DA> C...
    #> $ retweet_followers_count <int> NA, 16900, NA, NA, NA, 15282, 894, NA,...
    #> $ retweet_friends_count   <int> NA, 16900, NA, NA, NA, 15282, 894, NA,...
    #> $ retweet_statuses_count  <int> NA, 2923, NA, NA, NA, 61633, 1256, NA,...
    #> $ retweet_location        <chr> NA, "Metro Mixcoac", NA, NA, NA, NA, "...
    #> $ retweet_description     <chr> NA, "Somos un grupo que promueve la re...
    #> $ retweet_verified        <lgl> TRUE, FALSE, TRUE, TRUE, TRUE, FALSE, ...
    #> $ place_url               <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ place_name              <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ place_full_name         <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ place_type              <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ country                 <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ country_code            <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ bbox_coords             <list> [<>, <>, <>, <>, <>, <>, <>, <>, <>, ...
    #> $ name                    <chr> "<U+6A58>", "Derían,T", "<U+3061><U+3087><U+3053><U+3071><U+3044>", "\U0001f334<U+305F>...
    #> $ location                <chr> NA, NA, NA, "<U+30A2><U+30B8><U+30A2>", NA, NA, "<U+30CF><U+30EB><U+30D0><U+30F3><U+770C><U+2192><U+30EC><U+30C7><U+30A3><U+30AF>...
    #> $ description             <chr> "<U+51E6><U+4E16><U+306E><U+614B><U+5EA6><U+3068><U+3057><U+3066><U+751A><U+3060><U+554F><U+984C><U+304C><U+3042><U+308B><U+3002>", NA, "<U+30AD><U+30E3><U+30B9><U+57A2> <U+4E3B><U+306B><U+30AD><U+30E3><U+30B9><U+7528><U+306B>"...
    #> $ url                     <chr> "http://dtdwtd.hatenablog.com/", NA, N...
    #> $ protected               <lgl> FALSE, FALSE, FALSE, FALSE, FALSE, FAL...
    #> $ followers_count         <int> 329, 23, 8, 265, 118, 181, 775, 171, 4...
    #> $ friends_count           <int> 288, 94, 22, 162, 0, 293, 869, 224, 10...
    #> $ listed_count            <int> 22, 0, 0, 7, 16, 0, 15, 3, 4, 0, 2, 12...
    #> $ statuses_count          <int> 32031, 796, 889, 3669, 127684, 16216, ...
    #> $ favourites_count        <int> 166, 652, 388, 1535, 0, 653, 34879, 0,...
    #> $ account_created_at      <dttm> 2010-09-11 04:46:43, 2019-09-02 20:22...
    #> $ verified                <lgl> FALSE, FALSE, FALSE, FALSE, FALSE, FAL...
    #> $ account_lang            <chr> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA...
    #> $ profile_banner_url      <chr> "https://pbs.twimg.com/profile_banners...
    #> $ profile_image_url       <chr> "http://pbs.twimg.com/profile_images/1...
    #> $ timestamp_ms            <dttm> 2019-10-03 16:12:29, 2019-10-03 16:12...
    #> $ contributors_enabled    <lgl> TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TR...

### Scaling Up

We’re more interested in handling much larger data sets, like this one
that was also obtained using `rtweet::stream_tweets()`. The file has
been compressed to an 18 Mb .gz file (153 Mb uncompressed).

Currently, `{rtweet}` may fail parsing streams because the data returned
may not be valid JSON.

``` r
rtweet_stream_path <- "inst/example-data/api-stream.json.gz"

rtweet::parse_stream(rtweet_stream_path)
```

    #> Error: parse error: after array element, I expect ',' or ']'
    #>           736405012481"},"timestamp_ms":"1569693801061"}}{"created_at"
    #>                      (right here) ------^

This is unfortunate because I originally wanted to compare benchmarks
since `{tweetio}` can handle these situations.

``` r
big_rtweet_stream <- read_tweets(rtweet_stream_path)
```

How long does that take?

``` r
library(microbenchmark)

big_rtweet_time <- microbenchmark(
  read_tweets(rtweet_stream_path),
  times = 3
)

big_rtweet_time
```

    #> Unit: seconds
    #>                             expr      min       lq     mean  median
    #>  read_tweets(rtweet_stream_path) 2.570393 2.574951 2.693699 2.57951
    #>        uq      max neval
    #>  2.755352 2.931194     3

### Data Dumps

Using Elasticsearch seems to be the most common practice for handling
social media data at scale, but it’s (unfortunately) possible that
you’ll need to work with data dumps.

The data collected from APIs are stored inside a nested JSON object
named `"doc"`. `"doc"` is typically embedded in a ton of system
metadata, most of which you probably don’t care about.

I’ve encountered two flavors of these schema:

1.  .jsonl: line-delimited JSON (which is nearly the same as NDJSON).
2.  .json: the complete contents of an Elasticsearch index, which is a
    JSON array.

The .jsonl structure looks something like this:

``` json
{"system_metadata_you_dont_care_about":"blahblahblah","more_metadata1":"blahblahblah","more_metadata2":"blahblahblah","more_metadata3":"blahblahblah","more_metadata4":"blahblahblah","more_metadata5":"blahblahblah","doc":{"text":"********************HERE'S THE DATA YOU ACTUALLY WANT********************","id":92108498098018010401,"id_str":"92108498098018010401"},"more_metadata6":"blahblahblah","more_metadata7":"blahblahblah","more_metadata8":"blahblahblah","more_metadata9":"blahblahblah","more_metadata10":"blahblahblah"}
{"system_metadata_you_dont_care_about":"blahblahblah","more_metadata1":"blahblahblah","more_metadata2":"blahblahblah","more_metadata3":"blahblahblah","more_metadata4":"blahblahblah","more_metadata5":"blahblahblah","doc":{"text":"********************HERE'S THE DATA YOU ACTUALLY WANT********************","id":92108498098018010401,"id_str":"92108498098018010401"},"more_metadata6":"blahblahblah","more_metadata7":"blahblahblah","more_metadata8":"blahblahblah","more_metadata9":"blahblahblah","more_metadata10":"blahblahblah"}
{"system_metadata_you_dont_care_about":"blahblahblah","more_metadata1":"blahblahblah","more_metadata2":"blahblahblah","more_metadata3":"blahblahblah","more_metadata4":"blahblahblah","more_metadata5":"blahblahblah","doc":{"text":"********************HERE'S THE DATA YOU ACTUALLY WANT********************","id":92108498098018010401,"id_str":"92108498098018010401"},"more_metadata6":"blahblahblah","more_metadata7":"blahblahblah","more_metadata8":"blahblahblah","more_metadata9":"blahblahblah","more_metadata10":"blahblahblah"}
```

Each line contains a single JSON object resembling the following:

``` json
{
    "system_metadata_you_dont_care_about": "blahblahblah",
    "more_metadata1": "blahblahblah",
    "more_metadata2": "blahblahblah",
    "more_metadata3": "blahblahblah",
    "more_metadata4": "blahblahblah",
    "more_metadata5": "blahblahblah",
    "doc": {
        "text": "********************HERE'S THE DATA YOU ACTUALLY WANT********************",
        "id": 92108498098018010401,
        "id_str": "92108498098018010401"
    },
    "more_metadata6": "blahblahblah",
    "more_metadata7": "blahblahblah",
    "more_metadata8": "blahblahblah",
    "more_metadata9": "blahblahblah",
    "more_metadata10": "blahblahblah"
}
```

The .json structure looks something like this:

``` json
[
    {
        "_id": "e5daf1467d2438e31b11b44a82cbd7f5758ba5a1f1d3ecbcc6e1fc04dc9c7c4d-3016858092318",
        "_index": "org-77f135f331153568ab7eb0e4c24623a7-default-3769a33b9e88598e38317591e2ee31c3-default-030009",
        "_score": null,
        "_source": {
            "system_metadata_you_dont_care_about": "blahblahblah",
            "more_metadata1": "blahblahblah",
            "doc": {
                "text": "********************HERE'S THE DATA YOU ACTUALLY WANT********************",
                "id": 92108498098018010401,
                "id_str": "92108498098018010401"
            },
            "more_metadata6": "blahblahblah",
            "more_metadata7": "blahblahblah",
            "more_metadata8": "blahblahblah",
            "more_metadata9": "blahblahblah",
            "more_metadata10": "blahblahblah"
        }
    }
]
```

This has three unfortunate consequences:

1.  Packages that were purpose-built to work directly with `{rtweet}`’s
    data frames can’t play along with your data.
2.  You’re going to waste most of your time (and memory) getting data
    into R that you’re not going to use.
3.  The data are *very* tedious to restructure in R (lists of lists of
    lists of lists of lists…).

`{tweetio}` solves this by parsing everything at the C++ level, but only
returning the actual tweet data to R.

Finally, here’s a benchmark for reading a 890 Mb JSON array data dump.

``` r
res <- microbenchmark(

  read_tweets(data_dump) # *****************************************************
  
  , times = 5
)

res
```

    #> Unit: seconds
    #>                    expr      min       lq     mean   median       uq
    #>  read_tweets(data_dump) 4.343148 4.532619 4.624562 4.702861 4.710573
    #>      max neval
    #>  4.83361     5

<!-- ### Bulk Processing -->

<!-- While maybe not "big" data, handling millions of lines of JSON spread across dozens of files in R isn't exactly a picnic, but `read_tweets_bulk()` attempts to make this as easy as possible. -->

<!-- We can run `read_tweets_bulk()` either sequentially or in parallel. By setting `in_parallel=` to `FALSE`, it will always run sequentially, processing each file one at a time with `lapply()` before collapsing the resulting data frames via `data.table::rbindlist()`. -->

<!-- ```{r} -->

<!-- sequential_bulk_files <- all_data_dumps[1:4] -->

<!-- sequential_bulk_file_size <- sum(sapply(sequential_bulk_files, file.size)) -->

<!-- number_bytes(sequential_bulk_file_size) -->

<!-- ``` -->

<!-- ```{r} -->

<!-- sequential_bulk_time <- microbenchmark( -->

<!--   sequential_bulk_parsed <- read_tweets_bulk(sequential_bulk_files, # ********** -->

<!--                                              in_parallel = FALSE)   # ********** -->

<!--   , times = 1 -->

<!-- ) -->

<!-- sequential_bulk_time -->

<!-- ``` -->

<!-- If `in_parallel=` is set to `TRUE` (the default) _and_ `{future}` and `{future.apply}` are available, `read_tweets_bulk()` can be run in parallel via `future.apply::future_lapply()`. -->

<!-- ```{r} -->

<!-- parallel_bulk_file_size <- sum(sapply(all_data_dumps, file.size)) -->

<!-- number_bytes(parallel_bulk_file_size) -->

<!-- ``` -->

<!-- ```{r} -->

<!-- parallel_bulk_time <- microbenchmark( -->

<!--   read_tweets_bulk(all_data_dumps) # ***************************************** -->

<!--   , times = 1 -->

<!-- ) -->

<!-- parallel_bulk_time -->

<!-- ``` -->

<!-- ## Benchmarks -->

<!-- ```{r} -->

<!-- res <- microbenchmark( -->

<!--   read_tweets(rtweet_stream_path), -->

<!--   read_tweets(all_data_dumps[[1]]), -->

<!--   read_tweets(all_data_dumps[[2]]), -->

<!--   read_tweets(all_data_dumps[[3]]), -->

<!--   read_tweets(all_data_dumps[[4]]), -->

<!--   read_tweets(all_data_dumps[[5]]), -->

<!--   read_tweets(all_data_dumps[[6]]), -->

<!--   read_tweets(all_data_dumps[[7]]), -->

<!--   read_tweets(all_data_dumps[[8]]), -->

<!--   read_tweets(all_data_dumps[[9]]), -->

<!--   read_tweets(all_data_dumps[[10]]), -->

<!--   read_tweets(all_data_dumps[[11]]), -->

<!--   read_tweets(all_data_dumps[[12]]), -->

<!--   read_tweets(all_data_dumps[[13]]), -->

<!--   read_tweets(all_data_dumps[[14]]), -->

<!--   read_tweets(all_data_dumps[[15]]), -->

<!--   times = 3 -->

<!-- ) -->

<!-- library(tidyverse) -->

<!-- bench_marks <- res %>%  -->

<!--   as_tibble() %>%  -->

<!--   filter(expr != "read_tweets(rtweet_stream_path)") %>%  -->

<!--   mutate(file_size = expr %>%  -->

<!--            str_extract("(?<=\\().*(?=\\)$)") %>%  -->

<!--            map_chr(~ eval(parse(text = .x))) %>%  -->

<!--            file.size() -->

<!--            ) %>%  -->

<!--   mutate(time = time / 1e9) -->

<!-- bench_marks %>% -->

<!--   ggplot(aes(x = file_size, y = time, fill = as_factor(file_size))) + -->

<!--   stat_ydensity(adjust = 10) + -->

<!--   # geom_line() + -->

<!--   # ggbeeswarm::geom_beeswarm() + -->

<!--   # scale_y_log10() + -->

<!--   # scale_x_log10() + -->

<!--   guides(fill = FALSE, size = FALSE) + -->

<!--   labs(x = "File Size", y = "seconds") + -->

<!--   scale_x_continuous( -->

<!--     labels = function(.x) number_bytes(.x, symbol = "Mb", big.mark = ",") -->

<!--     # breaks = unique(bench_marks$time) -->

<!--   ) + -->

<!--   coord_flip() + -->

<!--   theme_minimal(base_size = 14, base_family = "serif") + -->

<!--   theme(legend.position = "bottom") -->

<!-- ``` -->

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
