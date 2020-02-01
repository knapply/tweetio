
<!-- README.Rmd generates README.md. -->

# `{tweetio}`

<!-- badges: start -->

[![Gitter](https://badges.gitter.im/tweetio/community.svg)](https://gitter.im/tweetio/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge)
[![Lifecycle](https://img.shields.io/badge/lifecycle-experimental-orange.svg)](https://www.tidyverse.org/lifecycle/#experimental)
[![AppVeyor build
status](https://ci.appveyor.com/api/projects/status/github/knapply/tweetio?branch=master&svg=true)](https://ci.appveyor.com/project/knapply/tweetio)
[![Travis-CI Build
Status](https://travis-ci.org/knapply/tweetio.svg?branch=master)](https://travis-ci.org/knapply/tweetio)
[![Codecov test
coverage](https://codecov.io/gh/knapply/tweetio/branch/master/graph/badge.svg)](https://codecov.io/gh/knapply/tweetio?branch=master)
[![GitHub last
commit](https://img.shields.io/github/last-commit/knapply/tweetio.svg)](https://github.com/knapply/tweetio/commits/master)
[![License: GPL
v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Depends](https://img.shields.io/badge/Depends-GNU_R%3E=3.3-blue.svg)](https://www.r-project.org/)
[![CRAN
status](https://www.r-pkg.org/badges/version/tweetio)](https://cran.r-project.org/package=tweetio)
[![GitHub code size in
bytes](https://img.shields.io/github/languages/code-size/knapply/tweetio.svg)](https://github.com/knapply/tweetio)
[![HitCount](http://hits.dwyl.io/knapply/tweetio.svg)](http://hits.dwyl.io/knapply/tweetio)
<!-- badges: end -->

<!-- [![R build status](https://github.com/knapply/tweetio/workflows/R-CMD-check/badge.svg)](https://github.com/knapply/tweetio/actions?workflow=R-CMD-check) -->

# Introduction

`{tweetio}`’s goal is to enable safe, efficient I/O and transformation
of Twitter data. Whether the data came from the Twitter API, a database
dump, or some other source, `{tweetio}`’s job is to get them into R and
ready for analysis.

`{tweetio}` is **not** a competitor to
[`{rtweet}`](https://rtweet.info/): it is not interested in collecting
Twitter data. That said, it definitely attempts to compliment it by
emulating its data frame schema because…

1.  It’s incredibly easy to use.
2.  It’s more efficient to analyze than a key-value format following the
    raw data.
3.  It’d be a waste not to maximize compatibility with tools built
    specifically around `{rtweet}`’s data frames.

# Installation

You’ll need a C++ compiler. If you’re using Windows, that means
[Rtools](https://cran.r-project.org/bin/windows/Rtools/).

``` r
if (!requireNamespace("remotes", quietly = TRUE)) install.packages("remotes")
remotes::install_github("knapply/tweetio")
```

# Usage

``` r
library(tweetio)
```

`{tweetio}` uses
[`{data.table}`](https://rdatatable.gitlab.io/data.table/) internally
for performance and stability reasons, but if you’re a
[`{tidyverse}`](https://www.tidyverse.org/) fan who’s accustomed to
dealing with `tibble`s, you can set an option so that `tibble`s are
*always* returned.

Because `tibble`s have an incredibly informative and user-friendly
`print()` method, we’ll set the option for examples. Note that if the
`{tibble}` package is not installed, this option is ignored.

``` r
options(tweetio.as_tibble = TRUE)
```

You can check on all available `{tweetio}` options using
`tweetio_options()`.

``` r
tweetio_options()
```

    #> $tweetio.as_tibble
    #> [1] TRUE
    #> 
    #> $tweetio.verbose
    #> [1] FALSE

<!-- # What's New? -->

<!-- ## Easy Access to Twitter-disclosed Information Operations Archives -->

<!-- ```{r} -->

<!-- io_campaign_metadata -->

<!-- ``` -->

## Simple Example

First, we’ll save a stream of tweets using `rtweet::stream_tweets()`.

``` r
temp_file <- tempfile(fileext = ".json")
rtweet::stream_tweets(timeout = 15, parse = FALSE,
                      file_name = temp_file)
```

We can then pass the file path to `tweetio::read_tweets()` to
efficiently parse the data into an `{rtweet}`-style data frame.

``` r
small_rtweet_stream <- read_tweets(temp_file)
small_rtweet_stream
```

    #> # A tibble: 896 x 93
    #>    user_id status_id created_at          screen_name text  source reply_to_status… reply_to_user_id reply_to_screen… is_quote is_retweet hashtags
    #>    <chr>   <chr>     <dttm>              <chr>       <chr> <chr>  <chr>            <chr>            <chr>            <lgl>    <lgl>      <list>  
    #>  1 633650… 12232610… 2020-01-31 15:05:31 twitkovska  RT @… Twitt… <NA>             <NA>             <NA>             FALSE    TRUE       <chr [1…
    #>  2 168140… 12232610… 2020-01-31 15:05:31 kirayosika… ドッピオ… twitt… <NA>             <NA>             <NA>             FALSE    FALSE      <chr [1…
    #>  3 215392… 12232610… 2020-01-31 15:05:31 ss3_i       null… twitt… <NA>             <NA>             <NA>             FALSE    FALSE      <chr [1…
    #>  4 745387… 12232610… 2020-01-31 15:05:31 fignoodles  Bussy twitt… <NA>             <NA>             <NA>             FALSE    FALSE      <chr [1…
    #>  5 117758… 12232610… 2020-01-31 15:05:31 japan397    え、優心… Twitt… <NA>             <NA>             <NA>             FALSE    FALSE      <chr [1…
    #>  6 857213… 12232610… 2020-01-31 15:05:31 CikkBungaaa RT @… Twitt… <NA>             <NA>             <NA>             FALSE    TRUE       <chr [1…
    #>  7 105623… 12232610… 2020-01-31 15:05:31 hyosminaa   RT @… Twitt… <NA>             <NA>             <NA>             FALSE    TRUE       <chr [1…
    #>  8 244649… 12232610… 2020-01-31 15:05:31 reall_pcy92 RT @… Twitt… <NA>             <NA>             <NA>             FALSE    TRUE       <chr [1…
    #>  9 176276… 12232610… 2020-01-31 15:05:31 arayamas    @Gui… Twitt… 122324827626850… 119613535164083… Guiller32301474  FALSE    FALSE      <chr [1…
    #> 10 111472… 12232610… 2020-01-31 15:05:31 GbzGuada    @reb… Twitt… 122301598922439… 714876006        rebemariiel      FALSE    FALSE      <chr [1…
    #> # … with 886 more rows, and 81 more variables: urls_expanded_url <list>, media_url <list>, media_expanded_url <list>, media_type <list>,
    #> #   mentions_user_id <list>, mentions_screen_name <list>, lang <chr>, quoted_status_id <chr>, quoted_text <chr>, quoted_created_at <dttm>,
    #> #   quoted_source <chr>, quoted_favorite_count <int>, quoted_retweet_count <int>, quoted_user_id <chr>, quoted_screen_name <chr>, quoted_name <chr>,
    #> #   quoted_followers_count <int>, quoted_friends_count <int>, quoted_statuses_count <int>, quoted_location <chr>, quoted_description <chr>,
    #> #   quoted_verified <lgl>, retweet_status_id <chr>, retweet_text <chr>, retweet_created_at <dttm>, retweet_source <chr>,
    #> #   retweet_favorite_count <int>, retweet_retweet_count <int>, retweet_user_id <chr>, retweet_screen_name <chr>, retweet_name <chr>,
    #> #   retweet_followers_count <int>, retweet_friends_count <int>, retweet_statuses_count <int>, retweet_location <chr>, retweet_description <chr>,
    #> #   retweet_verified <lgl>, place_url <chr>, place_name <chr>, place_full_name <chr>, place_type <chr>, country <chr>, country_code <chr>,
    #> #   bbox_coords <list>, status_url <chr>, name <chr>, location <chr>, description <chr>, url <chr>, protected <lgl>, followers_count <int>,
    #> #   friends_count <int>, listed_count <int>, statuses_count <int>, favourites_count <int>, account_created_at <dttm>, verified <lgl>,
    #> #   profile_url <chr>, account_lang <chr>, profile_banner_url <chr>, profile_image_url <chr>, is_retweeted <lgl>, retweet_place_url <chr>,
    #> #   retweet_place_name <chr>, retweet_place_full_name <chr>, retweet_place_type <chr>, retweet_country <chr>, retweet_country_code <chr>,
    #> #   retweet_bbox_coords <list>, quoted_place_url <chr>, quoted_place_name <chr>, quoted_place_full_name <chr>, quoted_place_type <chr>,
    #> #   quoted_country <chr>, quoted_country_code <chr>, quoted_bbox_coords <list>, timestamp_ms <dttm>, contributors_enabled <lgl>,
    #> #   retweet_status_url <chr>, quoted_tweet_url <chr>, reply_to_status_url <chr>

## Scaling Up

We’re more interested in handling much larger data sets, but for
demonstration we’ll use a file of a reasonable size that was obtained
using `rtweet::stream_tweets()`.

``` r
rtweet_stream_path <- "inst/example-data/api-stream.json.gz"
```

Unfortunately, `rtweet::parse_stream()` may fail parsing streams because
the data returned may not be valid JSON.

``` r
rtweet::parse_stream(rtweet_stream_path)
```

    #> Error: parse error: after array element, I expect ',' or ']'
    #>           736405012481"},"timestamp_ms":"1569693801061"}}{"created_at"
    #>                      (right here) ------^

The only way around this is to read the entire file into memory and run
some validation routine before parsing.

Fortunately, `{tweetio}` can handle these situations by validating the
JSON before it gets anywhere near R.

``` r
tweet_df <- read_tweets(rtweet_stream_path)
tweet_df
```

    #> # A tibble: 22,760 x 93
    #>    user_id status_id created_at          screen_name text  source reply_to_status… reply_to_user_id reply_to_screen… is_quote is_retweet hashtags
    #>    <chr>   <chr>     <dttm>              <chr>       <chr> <chr>  <chr>            <chr>            <chr>            <lgl>    <lgl>      <list>  
    #>  1 807195… 11780078… 2019-09-28 18:05:23 ykaoi0327   "RT … Twitt… <NA>             <NA>             <NA>             FALSE    TRUE       <chr [1…
    #>  2 114393… 11780078… 2019-09-28 18:05:23 yowasugi723 "@Di… Twitt… 117771450591824… 113811437998190… DiNozzo_123      FALSE    FALSE      <chr [1…
    #>  3 247059… 11780078… 2019-09-28 18:05:23 itsauroras… "RT … Twitt… <NA>             <NA>             <NA>             FALSE    TRUE       <chr [1…
    #>  4 822602… 11780078… 2019-09-28 18:05:23 Darrell894… "RT … Twitt… <NA>             <NA>             <NA>             FALSE    TRUE       <chr [1…
    #>  5 797200… 11780078… 2019-09-28 18:05:23 NastyWoman… "@Br… Twitt… 117796816033668… 21833728         Brasilmagic      FALSE    FALSE      <chr [1…
    #>  6 110779… 11780078… 2019-09-28 18:05:23 DeshaunAwe… "met… twitt… <NA>             <NA>             <NA>             FALSE    FALSE      <chr [1…
    #>  7 110441… 11780078… 2019-09-28 18:05:23 diamondy_u  "RT … Twitt… <NA>             <NA>             <NA>             FALSE    TRUE       <chr [1…
    #>  8 359294… 11780078… 2019-09-28 18:05:23 piyakat28   "RT … Twitt… <NA>             <NA>             <NA>             FALSE    TRUE       <chr [1…
    #>  9 194250… 11780078… 2019-09-28 18:05:23 Stgo_centro "RT … Twitt… <NA>             <NA>             <NA>             FALSE    TRUE       <chr [1…
    #> 10 116013… 11780078… 2019-09-28 18:05:23 119lonwi_y… "RT … Twitt… <NA>             <NA>             <NA>             FALSE    TRUE       <chr [1…
    #> # … with 22,750 more rows, and 81 more variables: urls_expanded_url <list>, media_url <list>, media_expanded_url <list>, media_type <list>,
    #> #   mentions_user_id <list>, mentions_screen_name <list>, lang <chr>, quoted_status_id <chr>, quoted_text <chr>, quoted_created_at <dttm>,
    #> #   quoted_source <chr>, quoted_favorite_count <int>, quoted_retweet_count <int>, quoted_user_id <chr>, quoted_screen_name <chr>, quoted_name <chr>,
    #> #   quoted_followers_count <int>, quoted_friends_count <int>, quoted_statuses_count <int>, quoted_location <chr>, quoted_description <chr>,
    #> #   quoted_verified <lgl>, retweet_status_id <chr>, retweet_text <chr>, retweet_created_at <dttm>, retweet_source <chr>,
    #> #   retweet_favorite_count <int>, retweet_retweet_count <int>, retweet_user_id <chr>, retweet_screen_name <chr>, retweet_name <chr>,
    #> #   retweet_followers_count <int>, retweet_friends_count <int>, retweet_statuses_count <int>, retweet_location <chr>, retweet_description <chr>,
    #> #   retweet_verified <lgl>, place_url <chr>, place_name <chr>, place_full_name <chr>, place_type <chr>, country <chr>, country_code <chr>,
    #> #   bbox_coords <list>, status_url <chr>, name <chr>, location <chr>, description <chr>, url <chr>, protected <lgl>, followers_count <int>,
    #> #   friends_count <int>, listed_count <int>, statuses_count <int>, favourites_count <int>, account_created_at <dttm>, verified <lgl>,
    #> #   profile_url <chr>, account_lang <chr>, profile_banner_url <chr>, profile_image_url <chr>, is_retweeted <lgl>, retweet_place_url <chr>,
    #> #   retweet_place_name <chr>, retweet_place_full_name <chr>, retweet_place_type <chr>, retweet_country <chr>, retweet_country_code <chr>,
    #> #   retweet_bbox_coords <list>, quoted_place_url <chr>, quoted_place_name <chr>, quoted_place_full_name <chr>, quoted_place_type <chr>,
    #> #   quoted_country <chr>, quoted_country_code <chr>, quoted_bbox_coords <list>, timestamp_ms <dttm>, contributors_enabled <lgl>,
    #> #   retweet_status_url <chr>, quoted_tweet_url <chr>, reply_to_status_url <chr>

With bigger files, using `rtweet::parse_stream()` is no longer
realistic, but that’s where `tweetio::read_tweets()` can help.

``` r
big_tweet_stream_path <- "~/ufc-tweet-stream.json.gz"
big_tweet_df <- read_tweets(big_tweet_stream_path)
big_tweet_df
```

    #> # A tibble: 140,368 x 93
    #>    user_id status_id created_at          screen_name text  source reply_to_status… reply_to_user_id reply_to_screen… is_quote is_retweet hashtags
    #>    <chr>   <chr>     <dttm>              <chr>       <chr> <chr>  <chr>            <chr>            <chr>            <lgl>    <lgl>      <list>  
    #>  1 340165… 11908502… 2019-11-03 04:36:36 M_Ahmad07   RT @… Twitt… <NA>             <NA>             <NA>             FALSE    TRUE       <chr [1…
    #>  2 502298… 11908502… 2019-11-03 04:36:36 Willcan     RT @… Twitt… <NA>             <NA>             <NA>             FALSE    TRUE       <chr [2…
    #>  3 111335… 11908502… 2019-11-03 04:36:36 heroXclass  RT @… Twitt… <NA>             <NA>             <NA>             FALSE    TRUE       <chr [1…
    #>  4 112082… 11908502… 2019-11-03 04:36:36 alicea561   Man … Twitt… <NA>             <NA>             <NA>             FALSE    FALSE      <chr [1…
    #>  5 294507… 11908502… 2019-11-03 04:36:36 JustinCull… Brut… Twitt… <NA>             <NA>             <NA>             FALSE    FALSE      <chr [1…
    #>  6 250392… 11908502… 2019-11-03 04:36:36 jppppppxo   the … Twitt… <NA>             <NA>             <NA>             FALSE    FALSE      <chr [1…
    #>  7 342703… 11908502… 2019-11-03 04:36:36 JonasParad… RT @… Twitt… <NA>             <NA>             <NA>             FALSE    TRUE       <chr [1…
    #>  8 242656… 11908502… 2019-11-03 04:36:36 js_cuellar  RT @… Twitt… <NA>             <NA>             <NA>             FALSE    TRUE       <chr [1…
    #>  9 104913… 11908502… 2019-11-03 04:36:36 SHREWDCOLTS RT @… Twitt… <NA>             <NA>             <NA>             FALSE    TRUE       <chr [1…
    #> 10 245455… 11908502… 2019-11-03 04:36:36 PaulWhittl… WoW … Twitt… <NA>             <NA>             <NA>             FALSE    FALSE      <chr [1…
    #> # … with 140,358 more rows, and 81 more variables: urls_expanded_url <list>, media_url <list>, media_expanded_url <list>, media_type <list>,
    #> #   mentions_user_id <list>, mentions_screen_name <list>, lang <chr>, quoted_status_id <chr>, quoted_text <chr>, quoted_created_at <dttm>,
    #> #   quoted_source <chr>, quoted_favorite_count <int>, quoted_retweet_count <int>, quoted_user_id <chr>, quoted_screen_name <chr>, quoted_name <chr>,
    #> #   quoted_followers_count <int>, quoted_friends_count <int>, quoted_statuses_count <int>, quoted_location <chr>, quoted_description <chr>,
    #> #   quoted_verified <lgl>, retweet_status_id <chr>, retweet_text <chr>, retweet_created_at <dttm>, retweet_source <chr>,
    #> #   retweet_favorite_count <int>, retweet_retweet_count <int>, retweet_user_id <chr>, retweet_screen_name <chr>, retweet_name <chr>,
    #> #   retweet_followers_count <int>, retweet_friends_count <int>, retweet_statuses_count <int>, retweet_location <chr>, retweet_description <chr>,
    #> #   retweet_verified <lgl>, place_url <chr>, place_name <chr>, place_full_name <chr>, place_type <chr>, country <chr>, country_code <chr>,
    #> #   bbox_coords <list>, status_url <chr>, name <chr>, location <chr>, description <chr>, url <chr>, protected <lgl>, followers_count <int>,
    #> #   friends_count <int>, listed_count <int>, statuses_count <int>, favourites_count <int>, account_created_at <dttm>, verified <lgl>,
    #> #   profile_url <chr>, account_lang <chr>, profile_banner_url <chr>, profile_image_url <chr>, is_retweeted <lgl>, retweet_place_url <chr>,
    #> #   retweet_place_name <chr>, retweet_place_full_name <chr>, retweet_place_type <chr>, retweet_country <chr>, retweet_country_code <chr>,
    #> #   retweet_bbox_coords <list>, quoted_place_url <chr>, quoted_place_name <chr>, quoted_place_full_name <chr>, quoted_place_type <chr>,
    #> #   quoted_country <chr>, quoted_country_code <chr>, quoted_bbox_coords <list>, timestamp_ms <dttm>, contributors_enabled <lgl>,
    #> #   retweet_status_url <chr>, quoted_tweet_url <chr>, reply_to_status_url <chr>

## Data Dumps

A common practice for handling social media data at scale is to store
them in search engine databases like Elasticsearch, but it’s
(unfortunately) possible that you’ll need to work with data dumps.

I’ve encountered two flavors of these schema (that may be in .gzip files
or ZIP archives):

1.  .jsonl: newline-delimited JSON
2.  .json: the complete contents of a database dump packed in a JSON
    array

This has three unfortunate consequences:

1.  Packages that were purpose-built to work directly with `{rtweet}`’s
    data frames can’t play along with your data.
2.  You’re going to waste most of your time (and memory) getting data
    into R that you’re not going to use.
3.  The data are *very* tedious to restructure in R (lists of lists of
    lists of lists of lists…).

`{tweetio}` solves this by parsing everything and building the data
frames at the C++ level. It even takes care of decompression of
compressed data fro you.

# Spatial Tweets

If you have `{sf}` installed, you can use `as_tweet_sf()` to only keep
those tweets that contain valid bounding box polygons.

``` r
tweet_sf <- as_tweet_sf(big_tweet_df)
tweet_sf[, "bbox_coords"]
```

    #> Simple feature collection with 2204 features and 0 fields
    #> geometry type:  POLYGON
    #> dimension:      XY
    #> bbox:           xmin: -158.048 ymin: -50.35726 xmax: 175.5507 ymax: 61.4262
    #> epsg (SRID):    4326
    #> proj4string:    +proj=longlat +datum=WGS84 +no_defs
    #> # A tibble: 2,204 x 1
    #>                                                                                     bbox_coords
    #>                                                                                   <POLYGON [°]>
    #>  1 ((-90.23761 29.96836, -90.23761 30.03413, -90.11965 30.03413, -90.11965 29.96836, -90.237...
    #>  2 ((-80.20811 26.08094, -80.20811 26.2198, -80.09024 26.2198, -80.09024 26.08094, -80.20811...
    #>  3 ((17.08005 59.73069, 17.08005 60.18611, 18.47324 60.18611, 18.47324 59.73069, 17.08005 59...
    #>  4 ((-80.51985 39.7198, -80.51985 42.51607, -74.68952 42.51607, -74.68952 39.7198, -80.51985...
    #>  5 ((-80.34364 25.59918, -80.34364 25.64553, -80.2875 25.64553, -80.2875 25.59918, -80.34364...
    #>  6 ((-118.6684 33.70454, -118.6684 34.33704, -118.1554 34.33704, -118.1554 33.70454, -118.66...
    #>  7 ((-122.0662 37.92423, -122.0662 38.02242, -121.931 38.02242, -121.931 37.92423, -122.0662...
    #>  8 ((-118.4485 33.97688, -118.4485 34.03514, -118.3695 34.03514, -118.3695 33.97688, -118.44...
    #>  9 ((-97.66262 27.57851, -97.66262 27.89579, -97.20223 27.89579, -97.20223 27.57851, -97.662...
    #> 10 ((-118.6684 33.70454, -118.6684 34.33704, -118.1554 34.33704, -118.1554 33.70454, -118.66...
    #> # … with 2,194 more rows

There are currently three columns that can potentially hold bounding
boxes:

1.  `bbox_coords`
2.  `quoted_bbox_coords`
3.  `retweet_bbox_coords`

You can select which one to use to build your `sf` object by modifying
the `geom_col=` parameter (default: `"bbox_coords"`)

``` r
as_tweet_sf(big_tweet_df,
            geom_col = "quoted_bbox_coords")[, "quoted_bbox_coords"]
```

    #> Simple feature collection with 1254 features and 0 fields
    #> geometry type:  POLYGON
    #> dimension:      XY
    #> bbox:           xmin: -124.849 ymin: -27.76744 xmax: 153.3179 ymax: 60.29791
    #> epsg (SRID):    4326
    #> proj4string:    +proj=longlat +datum=WGS84 +no_defs
    #> # A tibble: 1,254 x 1
    #>                                                                              quoted_bbox_coords
    #>                                                                                   <POLYGON [°]>
    #>  1 ((-73.99354 40.75075, -73.99354 40.75075, -73.99354 40.75075, -73.99354 40.75075, -73.993...
    #>  2 ((-73.99354 40.75075, -73.99354 40.75075, -73.99354 40.75075, -73.99354 40.75075, -73.993...
    #>  3 ((-73.99354 40.75075, -73.99354 40.75075, -73.99354 40.75075, -73.99354 40.75075, -73.993...
    #>  4 ((-73.99354 40.75075, -73.99354 40.75075, -73.99354 40.75075, -73.99354 40.75075, -73.993...
    #>  5 ((-73.99354 40.75075, -73.99354 40.75075, -73.99354 40.75075, -73.99354 40.75075, -73.993...
    #>  6 ((-73.99354 40.75075, -73.99354 40.75075, -73.99354 40.75075, -73.99354 40.75075, -73.993...
    #>  7 ((-73.99354 40.75075, -73.99354 40.75075, -73.99354 40.75075, -73.99354 40.75075, -73.993...
    #>  8 ((-73.99354 40.75075, -73.99354 40.75075, -73.99354 40.75075, -73.99354 40.75075, -73.993...
    #>  9 ((-73.99354 40.75075, -73.99354 40.75075, -73.99354 40.75075, -73.99354 40.75075, -73.993...
    #> 10 ((-73.99354 40.75075, -73.99354 40.75075, -73.99354 40.75075, -73.99354 40.75075, -73.993...
    #> # … with 1,244 more rows

You can also build *all* the supported bounding boxes by setting
`geom_col=` to `"all"`.

``` r
all_bboxes <- as_tweet_sf(big_tweet_df, geom_col = "all")
all_bboxes[, c("which_geom", "geometry")]
```

    #> Simple feature collection with 7428 features and 1 field
    #> geometry type:  POLYGON
    #> dimension:      XY
    #> bbox:           xmin: -158.048 ymin: -50.35726 xmax: 175.5507 ymax: 61.4262
    #> epsg (SRID):    4326
    #> proj4string:    +proj=longlat +datum=WGS84 +no_defs
    #> # A tibble: 7,428 x 2
    #>    which_geom                                                                                      geometry
    #>    <chr>                                                                                      <POLYGON [°]>
    #>  1 bbox_coords ((-90.23761 29.96836, -90.23761 30.03413, -90.11965 30.03413, -90.11965 29.96836, -90.237...
    #>  2 bbox_coords ((-80.20811 26.08094, -80.20811 26.2198, -80.09024 26.2198, -80.09024 26.08094, -80.20811...
    #>  3 bbox_coords ((17.08005 59.73069, 17.08005 60.18611, 18.47324 60.18611, 18.47324 59.73069, 17.08005 59...
    #>  4 bbox_coords ((-80.51985 39.7198, -80.51985 42.51607, -74.68952 42.51607, -74.68952 39.7198, -80.51985...
    #>  5 bbox_coords ((-80.34364 25.59918, -80.34364 25.64553, -80.2875 25.64553, -80.2875 25.59918, -80.34364...
    #>  6 bbox_coords ((-118.6684 33.70454, -118.6684 34.33704, -118.1554 34.33704, -118.1554 33.70454, -118.66...
    #>  7 bbox_coords ((-122.0662 37.92423, -122.0662 38.02242, -121.931 38.02242, -121.931 37.92423, -122.0662...
    #>  8 bbox_coords ((-118.4485 33.97688, -118.4485 34.03514, -118.3695 34.03514, -118.3695 33.97688, -118.44...
    #>  9 bbox_coords ((-97.66262 27.57851, -97.66262 27.89579, -97.20223 27.89579, -97.20223 27.57851, -97.662...
    #> 10 bbox_coords ((-118.6684 33.70454, -118.6684 34.33704, -118.1554 34.33704, -118.1554 33.70454, -118.66...
    #> # … with 7,418 more rows

From there, you can easily use the data like any other `{sf}` object.

``` r
library(ggplot2)

world <- rnaturalearth::ne_countries(returnclass = "sf")
world <- world[world$continent != "Antarctica", ]

sf_for_gg <- sf::st_wrap_dateline(all_bboxes)

ggplot(sf_for_gg) +
  geom_sf(fill = "white", color = "lightgray", data = world) +
  geom_sf(aes(fill = which_geom, color = which_geom), 
          alpha = 0.15, size = 1, show.legend = TRUE) +
  coord_sf(crs = 3857) +
  scale_fill_viridis_d() +
  scale_color_viridis_d() +
  theme(legend.title = element_blank(), legend.position = "top",
        panel.background = element_rect(fill = "#daf3ff"))
```

<img src="man/figures/unnamed-chunk-15-1.png" style="display: block; margin: auto;" />

# Tweet Networks

If you want to analyze tweet networks and have `{igraph}` or `{network}`
installed, you can get started immediately using
`tweetio::as_tweet_igraph()` or `tweetio::as_tweet_network()`.

``` r
as_tweet_igraph(tweet_df)
```

    #> IGRAPH c7ec1fa DN-- 37519 42191 -- 
    #> + attr: name (v/c), status_id (e/c), relation (e/c)
    #> + edges from c7ec1fa (vertex names):
    #>  [1] 807195027403259904 ->938662230052052992  247059655          ->609647782           822602638231535617 ->701750402786717696 
    #>  [4] 1104415177603133444->1108885040862121985 359294371          ->1034795669645447168 194250838          ->340309688          
    #>  [7] 1160132819114287105->3251156738          1064053347164930048->2430693075          1056020503993888768->1017892758063702016
    #> [10] 1103702847378604032->414928075           817820347806478341 ->817820347806478341  1046542408438046720->799246741174386688 
    #> [13] 933502505115377665 ->729676086632656900  145779984          ->451032248           981315512956268545 ->611972802          
    #> [16] 84458315           ->19317261            785436504743145472 ->1159057465750818816 2259128973         ->1094486703744606208
    #> [19] 997536087978455041 ->1157842598855417856 930455277488562176 ->1135749044213436417 1111005122543472640->1015912878518493184
    #> [22] 863499610676973569 ->162219630           1177957168869298177->1074311333070266369 1071397841623347200->738529042186440708 
    #> + ... omitted several edges

``` r
as_tweet_network(tweet_df)
```

    #>  Network attributes:
    #>   vertices = 37519 
    #>   directed = TRUE 
    #>   hyper = FALSE 
    #>   loops = TRUE 
    #>   multiple = TRUE 
    #>   bipartite = FALSE 
    #>   total edges= 42191 
    #>     missing edges= 0 
    #>     non-missing edges= 42191 
    #> 
    #>  Vertex attribute names: 
    #>     vertex.names 
    #> 
    #>  Edge attribute names not shown

If you want to take advantage of all the metadata available, you can set
`all_status_data` and/or `all_user_data` to `TRUE`

``` r
as_tweet_igraph(tweet_df,
                all_user_data = TRUE, all_status_data = TRUE)
```

    #> IGRAPH ad821ec DN-- 37519 42191 -- 
    #> + attr: name (v/c), status_id (e/c), relation (e/c)
    #> + edges from ad821ec (vertex names):
    #>  [1] 807195027403259904 ->938662230052052992  247059655          ->609647782           822602638231535617 ->701750402786717696 
    #>  [4] 1104415177603133444->1108885040862121985 359294371          ->1034795669645447168 194250838          ->340309688          
    #>  [7] 1160132819114287105->3251156738          1064053347164930048->2430693075          1056020503993888768->1017892758063702016
    #> [10] 1103702847378604032->414928075           817820347806478341 ->817820347806478341  1046542408438046720->799246741174386688 
    #> [13] 933502505115377665 ->729676086632656900  145779984          ->451032248           981315512956268545 ->611972802          
    #> [16] 84458315           ->19317261            785436504743145472 ->1159057465750818816 2259128973         ->1094486703744606208
    #> [19] 997536087978455041 ->1157842598855417856 930455277488562176 ->1135749044213436417 1111005122543472640->1015912878518493184
    #> [22] 863499610676973569 ->162219630           1177957168869298177->1074311333070266369 1071397841623347200->738529042186440708 
    #> + ... omitted several edges

``` r
as_tweet_network(tweet_df,
                 all_user_data = TRUE, all_status_data = TRUE)
```

    #>  Network attributes:
    #>   vertices = 37519 
    #>   directed = TRUE 
    #>   hyper = FALSE 
    #>   loops = TRUE 
    #>   multiple = TRUE 
    #>   bipartite = FALSE 
    #>   total edges= 42191 
    #>     missing edges= 0 
    #>     non-missing edges= 42191 
    #> 
    #>  Vertex attribute names: 
    #>     vertex.names 
    #> 
    #>  Edge attribute names not shown

## Two-Mode Networks

You can also build two-mode networks by specifying the `target_class` as
`"hashtag"`s, `"url"`s, or `"media"`.

  - Returned `<igraph>`s will be set as bipartite following `{igraph}`’s
    convention of a `logical` vertex attribute specifying each
    partition. Accounts are always `TRUE`.
  - Returned `<network>`s will be set as bipartite following
    `{network}`’s convention of ordering the “actors” first, and
    setting the network-level attribute of “bipartite” as the number of
    “actors”. Accounts are always the “actors”.

If bipartite, the returned objects are always set as undirected.

### Users to Hashtags

``` r
as_tweet_igraph(tweet_df, target_class = "hashtag")
```

    #> IGRAPH 348122b DN-- 37519 42191 -- 
    #> + attr: name (v/c), status_id (e/c), relation (e/c)
    #> + edges from 348122b (vertex names):
    #>  [1] 807195027403259904 ->938662230052052992  247059655          ->609647782           822602638231535617 ->701750402786717696 
    #>  [4] 1104415177603133444->1108885040862121985 359294371          ->1034795669645447168 194250838          ->340309688          
    #>  [7] 1160132819114287105->3251156738          1064053347164930048->2430693075          1056020503993888768->1017892758063702016
    #> [10] 1103702847378604032->414928075           817820347806478341 ->817820347806478341  1046542408438046720->799246741174386688 
    #> [13] 933502505115377665 ->729676086632656900  145779984          ->451032248           981315512956268545 ->611972802          
    #> [16] 84458315           ->19317261            785436504743145472 ->1159057465750818816 2259128973         ->1094486703744606208
    #> [19] 997536087978455041 ->1157842598855417856 930455277488562176 ->1135749044213436417 1111005122543472640->1015912878518493184
    #> [22] 863499610676973569 ->162219630           1177957168869298177->1074311333070266369 1071397841623347200->738529042186440708 
    #> + ... omitted several edges

``` r
as_tweet_network(tweet_df, target_class = "hashtag")
```

    #>  Network attributes:
    #>   vertices = 37519 
    #>   directed = TRUE 
    #>   hyper = FALSE 
    #>   loops = TRUE 
    #>   multiple = TRUE 
    #>   bipartite = FALSE 
    #>   total edges= 42191 
    #>     missing edges= 0 
    #>     non-missing edges= 42191 
    #> 
    #>  Vertex attribute names: 
    #>     vertex.names 
    #> 
    #>  Edge attribute names not shown

### Users to URLs

``` r
as_tweet_igraph(tweet_df, target_class = "url")
```

    #> IGRAPH 4cefdbd DN-- 37519 42191 -- 
    #> + attr: name (v/c), status_id (e/c), relation (e/c)
    #> + edges from 4cefdbd (vertex names):
    #>  [1] 807195027403259904 ->938662230052052992  247059655          ->609647782           822602638231535617 ->701750402786717696 
    #>  [4] 1104415177603133444->1108885040862121985 359294371          ->1034795669645447168 194250838          ->340309688          
    #>  [7] 1160132819114287105->3251156738          1064053347164930048->2430693075          1056020503993888768->1017892758063702016
    #> [10] 1103702847378604032->414928075           817820347806478341 ->817820347806478341  1046542408438046720->799246741174386688 
    #> [13] 933502505115377665 ->729676086632656900  145779984          ->451032248           981315512956268545 ->611972802          
    #> [16] 84458315           ->19317261            785436504743145472 ->1159057465750818816 2259128973         ->1094486703744606208
    #> [19] 997536087978455041 ->1157842598855417856 930455277488562176 ->1135749044213436417 1111005122543472640->1015912878518493184
    #> [22] 863499610676973569 ->162219630           1177957168869298177->1074311333070266369 1071397841623347200->738529042186440708 
    #> + ... omitted several edges

``` r
as_tweet_network(tweet_df, target_class = "url")
```

    #>  Network attributes:
    #>   vertices = 37519 
    #>   directed = TRUE 
    #>   hyper = FALSE 
    #>   loops = TRUE 
    #>   multiple = TRUE 
    #>   bipartite = FALSE 
    #>   total edges= 42191 
    #>     missing edges= 0 
    #>     non-missing edges= 42191 
    #> 
    #>  Vertex attribute names: 
    #>     vertex.names 
    #> 
    #>  Edge attribute names not shown

### Users to Media

``` r
as_tweet_igraph(tweet_df, target_class = "media")
```

    #> IGRAPH f4c25ec DN-- 37519 42191 -- 
    #> + attr: name (v/c), status_id (e/c), relation (e/c)
    #> + edges from f4c25ec (vertex names):
    #>  [1] 807195027403259904 ->938662230052052992  247059655          ->609647782           822602638231535617 ->701750402786717696 
    #>  [4] 1104415177603133444->1108885040862121985 359294371          ->1034795669645447168 194250838          ->340309688          
    #>  [7] 1160132819114287105->3251156738          1064053347164930048->2430693075          1056020503993888768->1017892758063702016
    #> [10] 1103702847378604032->414928075           817820347806478341 ->817820347806478341  1046542408438046720->799246741174386688 
    #> [13] 933502505115377665 ->729676086632656900  145779984          ->451032248           981315512956268545 ->611972802          
    #> [16] 84458315           ->19317261            785436504743145472 ->1159057465750818816 2259128973         ->1094486703744606208
    #> [19] 997536087978455041 ->1157842598855417856 930455277488562176 ->1135749044213436417 1111005122543472640->1015912878518493184
    #> [22] 863499610676973569 ->162219630           1177957168869298177->1074311333070266369 1071397841623347200->738529042186440708 
    #> + ... omitted several edges

``` r
as_tweet_network(tweet_df, target_class = "media")
```

    #>  Network attributes:
    #>   vertices = 37519 
    #>   directed = TRUE 
    #>   hyper = FALSE 
    #>   loops = TRUE 
    #>   multiple = TRUE 
    #>   bipartite = FALSE 
    #>   total edges= 42191 
    #>     missing edges= 0 
    #>     non-missing edges= 42191 
    #> 
    #>  Vertex attribute names: 
    #>     vertex.names 
    #> 
    #>  Edge attribute names not shown

## `<proto_net>`

You’re not stuck with going directly to `<igraph>`s or `<network>`s
though. Underneath the hood, `as_tweet_igraph()` and
`as_tweet_network()` use `as_proto_net()` to build a `<proto_net>`, a
list of edge and node data frames.

``` r
as_proto_net(tweet_df,
             all_status_data = TRUE, all_user_data = TRUE)
```

    #> $edges
    #> # A tibble: 42,191 x 4
    #>    from                to                  status_id           relation
    #>    <chr>               <chr>               <chr>               <chr>   
    #>  1 807195027403259904  938662230052052992  1178007813257187328 retweet 
    #>  2 247059655           609647782           1178007813232025601 retweet 
    #>  3 822602638231535617  701750402786717696  1178007813236244481 retweet 
    #>  4 1104415177603133444 1108885040862121985 1178007813236252672 retweet 
    #>  5 359294371           1034795669645447168 1178007813248806912 retweet 
    #>  6 194250838           340309688           1178007813257388032 retweet 
    #>  7 1160132819114287105 3251156738          1178007813257224192 retweet 
    #>  8 1064053347164930048 2430693075          1178007813244608513 retweet 
    #>  9 1056020503993888768 1017892758063702016 1178007813244604417 retweet 
    #> 10 1103702847378604032 414928075           1178007813253206017 retweet 
    #> # … with 42,181 more rows
    #> 
    #> $nodes
    #> # A tibble: 37,519 x 1
    #>    name               
    #>    <chr>              
    #>  1 807195027403259904 
    #>  2 247059655          
    #>  3 822602638231535617 
    #>  4 1104415177603133444
    #>  5 359294371          
    #>  6 194250838          
    #>  7 1160132819114287105
    #>  8 1064053347164930048
    #>  9 1056020503993888768
    #> 10 1103702847378604032
    #> # … with 37,509 more rows
    #> 
    #> attr(,"class")
    #> [1] "proto_net"
    #> attr(,"target_class")
    #> [1] "user"

# Progress

### Supported Data Inputs

  - [x] Twitter API streams: .json, .json.gz
  - [x] API to Elasticsearch data dump (JSON Array): .json, .json.gz
  - [x] API to Elasticsearch data dump (line-delimited JSON): .jsonl,
    .jsonl.gz

### Supported Data Outputs

  - [x] CSV
  - [x] Excel
  - [x] Gephi-friendly GraphML

### Structures

  - [x] `{rtweet}`-style data frames
  - [x] Spatial Tweets via `{sf}`
  - [x] Tweet networks via `{igraph}`
  - [x] Tweet networks via `{network}`

# Shout Outs

The [`{rtweet}`](https://rtweet.info/) package **spoils R users
rotten**, in the best possible way. The underlying data carpentry is so
seamless that the user doesn’t need to know anything about the horrors
of Twitter data, which is pretty amazing. If you use `{rtweet}`, you
probably owe [Michael Kearney](https://twitter.com/kearneymw) some
[citations](https://github.com/mkearney/rtweet_citations). If he hadn’t
developed a way to sensibly structure tweet data frames in R,
`{tweetio}` would’ve never happened.

`{tweetio}` uses a combination of C++ via
[`{Rcpp}`](http://www.rcpp.org/), the
[`rapidjson`](http://rapidjson.org/) C++ library (made available by
[`{rapidjsonr}`](https://cran.r-project.org/web/packages/rapidjsonr/index.html)),
[`{jsonify}`](https://cran.r-project.org/web/packages/jsonify/index.html))
for an R-level interface to `rapidjson`,
[`{RcppProgress}`](https://cran.r-project.org/web/packages/RcppProgress/index.html)),
and **R’s not-so-secret super weapon**:
[`{data.table}`](https://rdatatable.gitlab.io/data.table/).

Major inspiration from [`{ndjson}`](https://gitlab.com/hrbrmstr/ndjson)
was taken, particularly its use of
[`Gzstream`](https://www.cs.unc.edu/Research/compgeom/gzstream/).
