
<link rel="stylesheet" href="https://cdn.jsdelivr.net/gh/tonsky/FiraCode@1.207/distr/fira_code.css">

<style>
font-family: 'Fira Code', monospace;
</style>

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
rotten**.

The underlying data carpentry is so abstracted that the user doesn’t
need to know anything about the horrors of Twitter data, which is pretty
amazing.

`{tweetio}` focuses on one thing: **going from raw tweets to
`{rtweet}`-style data frames as fast as possible**, whether the data
came from the Twitter APIs, a vendor, or some other source. You bring
the data, `{tweetio}` gets it into R.

To accomplish this, `{tweetio}` uses a combination of C++ via `{Rcpp}`,
the `rapidjson` C++ library (made available by `{rapidjsonr}`), and
`{data.table}`.

Major inspiration from {`ndjson`} was taken, including its handling of
gzipped-files. Bulk processing of multiple files is handled by
`{future}` and `{furrr}`, if available.

# Installation

``` r
# install.packages("remotes")
remotes::install_github("knapply/tweetio")
```

# Usage

First, we’ll parse a stream obtained by `rtweet::stream_tweets()` that
has been compressed to a `json.gz` file.

``` r
library(tweetio)
library(purrr)

path_to_rtweet_stream <- "inst/example-data/api-stream.json.gz"
path_to_rtweet_stream %>%
  file.size() %>% 
  scales::number_bytes() # 153 Mb before compression
```

    #> [1] "18 Mb"

``` r
rtweet_time <- system.time(
  rtweet_parsed <- read_tweets(path_to_rtweet_stream, type = "normal")
); rtweet_time
```

    #>    user  system elapsed 
    #>    3.43    0.17    3.61

``` r
rtweet_parsed %>% 
  dim() %>% 
  scales::comma() %>% 
  set_names(c("# rows", "# columns"))
```

    #>    # rows # columns 
    #>  "22,760"      "71"

3.61 seconds for 22,760 tweets ain’t too shabby.

How about some vendor data?

``` r
path_to_vendor_data <- readRDS("path_to_vendor_data.rds")

all_vendor_files <- dir(path_to_vendor_data, pattern = "\\.jsonl\\.gz$",
                        full.names = TRUE)

all_vendor_files[[1L]] %>% 
  file.size() %>% 
  scales::number_bytes() # 1.6 Gb before compression
```

    #> [1] "173 Mb"

``` r
single_vendor_time <- system.time(
  single_vendor_parsed <- read_tweets(all_vendor_files[[1L]], 
                                      type = "nested_doc")
); single_vendor_time
```

    #>    user  system elapsed 
    #>   21.27    1.20   22.50

``` r
single_vendor_parsed %>% 
  dim() %>% 
  scales::comma() %>% 
  set_names(c("# rows", "# columns"))
```

    #>    # rows # columns 
    #>  "94,139"      "71"

22.5 seconds for 94,139 tweets seems pretty fast.

How about bulk data? While maybe not “big” data, handling millions of
lines of JSON in R isn’t exactly a picnic.

``` r
length(all_vendor_files)
all_vendor_files %>% 
  map_dbl(file.size) %>% 
  sum() %>% 
  scales::number_bytes() # 47 Gb before compression
system.time(
  bulk_parsed <- read_tweets(all_vendor_files, type = "nested_doc", 
                             .progress = FALSE)
)
bulk_parsed %>% 
  dim() %>% 
  scales::comma() %>% 
  set_names(c("# rows", "# columns"))
```

Nearly 3,000,000 tweets in a few minutes? Until Rtools 40 hits (or the
simdjson library decides to relax its C++17 requirement), I’m not
certain we can go much faster.
