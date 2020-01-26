
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

    #> # A tibble: 750 x 93
    #>    user_id status_id created_at          screen_name text  source reply_to_status… reply_to_user_id reply_to_screen… is_quote is_retweet hashtags
    #>    <chr>   <chr>     <dttm>              <chr>       <chr> <chr>  <chr>            <chr>            <chr>            <lgl>    <lgl>      <list>  
    #>  1 215098… 12215702… 2020-01-26 23:07:01 zaitakude1  明日、１… "twit… <NA>             <NA>             <NA>             FALSE    FALSE      <chr [1…
    #>  2 106924… 12215702… 2020-01-26 23:07:01 mijinko_uw  いや、コ… "Twit… <NA>             <NA>             <NA>             FALSE    FALSE      <chr [1…
    #>  3 217262… 12215702… 2020-01-26 23:07:01 Ryan_Reill… @juv… "Twit… 122156955637381… 1915837086       juventutemDC     FALSE    FALSE      <chr [1…
    #>  4 330393… 12215702… 2020-01-26 23:07:01 TERBULA     RT @… "Twit… <NA>             <NA>             <NA>             FALSE    TRUE       <chr [1…
    #>  5 886384… 12215702… 2020-01-26 23:07:01 myIightJin  yo N… "Twit… <NA>             <NA>             <NA>             FALSE    FALSE      <chr [1…
    #>  6 114423… 12215702… 2020-01-26 23:07:01 su35thunde… @ind… "Twit… 122156700086389… 118427070431889… indian_XD        FALSE    FALSE      <chr [1…
    #>  7 723986… 12215702… 2020-01-26 23:07:01 JvmesHoover RT @… "Twee… <NA>             <NA>             <NA>             FALSE    TRUE       <chr [1…
    #>  8 637250… 12215702… 2020-01-26 23:07:01 nishi_akas… RT @… "feat… <NA>             <NA>             <NA>             FALSE    TRUE       <chr [1…
    #>  9 122609… 12215702… 2020-01-26 23:07:01 j_rosas88   RT @… "Twit… <NA>             <NA>             <NA>             FALSE    TRUE       <chr [1…
    #> 10 739489… 12215702… 2020-01-26 23:07:01 El_Juanico_ Ya m… "Twit… <NA>             <NA>             <NA>             FALSE    FALSE      <chr [1…
    #> # … with 740 more rows, and 81 more variables: urls_expanded_url <list>, media_url <list>, media_expanded_url <list>, media_type <list>,
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

  - Note: `tweetio::as_tweet_network()` requires a not-yet-accepted PR
    to [statnet/network](https://github.com/statnet/network), but the
    functionality is available via the
    [knapply/network](https://github.com/knapply/network) fork.
      - If you installed `{tweetio}` via
        `remotes::install_github("knapply/tweetio")`, it *should* have
        also installed the required version of `{network}`.
      - If for some reason you didn’t, you can get the required
        `{network}` fork via
        `remotes::install_github("knapply/network")`.

<!-- end list -->

``` r
tweet_net <- tweet_df[1:5000, ]
as_tweet_igraph(tweet_net)
```

    #> IGRAPH fab68bf DN-- 8788 9181 -- 
    #> + attr: name (v/c), status_id (e/c), relation (e/c)
    #> + edges from fab68bf (vertex names):
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
as_tweet_network(tweet_net)
```

    #>  Network attributes:
    #>   vertices = 8788 
    #>   directed = TRUE 
    #>   hyper = FALSE 
    #>   loops = TRUE 
    #>   multiple = TRUE 
    #>   bipartite = FALSE 
    #>   total edges= 9181 
    #>     missing edges= 0 
    #>     non-missing edges= 9181 
    #> 
    #>  Vertex attribute names: 
    #>     vertex.names 
    #> 
    #>  Edge attribute names not shown

If you want to take advantage of all the metadata available, you can set
`all_status_data` and/or `all_user_data` to `TRUE`

``` r
as_tweet_igraph(tweet_net,
                all_user_data = TRUE, all_status_data = TRUE)
```

    #> IGRAPH 60a8a82 DN-- 8788 9181 -- 
    #> + attr: name (v/c), timestamp_ms (v/n), name.y (v/c), screen_name (v/c), location (v/c), description (v/c), url (v/c), protected
    #> | (v/l), followers_count (v/n), friends_count (v/n), listed_count (v/n), statuses_count (v/n), favourites_count (v/n),
    #> | account_created_at (v/n), verified (v/l), profile_url (v/c), account_lang (v/c), profile_banner_url (v/c), profile_image_url (v/c),
    #> | bbox_coords (v/x), status_id (e/c), relation (e/c), created_at (e/n), text (e/c), status_url (e/c), source (e/c), is_quote (e/l),
    #> | is_retweeted (e/l), media_url (e/x), media_type (e/x), place_url (e/c), place_name (e/c), place_full_name (e/c), place_type (e/c),
    #> | country (e/c), country_code (e/c), bbox_coords (e/x), status_type (e/c)
    #> + edges from 60a8a82 (vertex names):
    #>  [1] 781269778107248640 ->247653244           781269778107248640 ->247653244           3231805274         ->1151537584352288768
    #>  [4] 3231805274         ->1151537584352288768 885853778582282240 ->1122135766472118272 885853778582282240 ->1122135766472118272
    #>  [7] 802405748563030017 ->431633459           802405748563030017 ->431633459           802405748563030017 ->1033152632527892480
    #> + ... omitted several edges

``` r
as_tweet_network(tweet_net,
                 all_user_data = TRUE, all_status_data = TRUE)
```

    #>  Network attributes:
    #>   vertices = 8788 
    #>   directed = TRUE 
    #>   hyper = FALSE 
    #>   loops = TRUE 
    #>   multiple = TRUE 
    #>   bipartite = FALSE 
    #>   total edges= 9181 
    #>     missing edges= 0 
    #>     non-missing edges= 9181 
    #> 
    #>  Vertex attribute names: 
    #>     account_created_at account_lang bbox_coords description favourites_count followers_count friends_count listed_count location name.y profile_banner_url profile_image_url profile_url protected screen_name statuses_count timestamp_ms url verified vertex.names 
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
as_tweet_igraph(tweet_net, target_class = "hashtag")
```

    #> IGRAPH e500f03 UN-B 1997 1746 -- 
    #> + attr: name (v/c), type (v/l), status_id (e/c), relation (e/c)
    #> + edges from e500f03 (vertex names):
    #>  [1] 359294371          --got7_kconth2019          933502505115377665 --investigatebiden         981315512956268545 --셔누                    
    #>  [4] 767835057620918272 --therookie                781414129          --أحد_المسارحه             781414129          --اليوم_الوطني89          
    #>  [7] 781414129          --همه_حتى_القمه            1868079872         --wicklowecotrail          1177957168869298177--naamkarannke3saal       
    #> [10] 2162617110         --watch                    1169328651222913024--श्राद्ध_मत_करना            3112061905         --bardofbloodwinninghearts
    #> [13] 977237285048668162 --abdl                     307278565          --sampdoriainter           218889555          --sooners                 
    #> [16] 1173877389241323521--qualitedair              1173877389241323521--qai                      1173877389241323521--pollutionair            
    #> [19] 861240546316222465 --كلاب_الاحزاب_الفاسدة     4655212832         --ntrundisputedkingoftfi   4655212832         --ntrboxofficeemperor     
    #> [22] 4655212832         --jaintr                   886236627235999744 --halamadrid               811714585103171584 --mpn                     
    #> + ... omitted several edges

``` r
as_tweet_network(tweet_net, target_class = "hashtag")
```

    #>  Network attributes:
    #>   vertices = 1997 
    #>   directed = FALSE 
    #>   hyper = FALSE 
    #>   loops = FALSE 
    #>   multiple = TRUE 
    #>   bipartite = 758 
    #>   total edges= 1746 
    #>     missing edges= 0 
    #>     non-missing edges= 1746 
    #> 
    #>  Vertex attribute names: 
    #>     is_actor vertex.names 
    #> 
    #>  Edge attribute names not shown

### Users to URLs

``` r
as_tweet_igraph(tweet_net, target_class = "url")
```

    #> IGRAPH 5843930 UN-B 1055 546 -- 
    #> + attr: name (v/c), type (v/l), status_id (e/c), relation (e/c)
    #> + edges from 5843930 (vertex names):
    #> [1] 930455277488562176 --https://twitter.com/valsnudes/status/1177292877946212352                                                                                                                   
    #> [2] 1111005122543472640--https://twitter.com/LVPibai/status/1177063381607550976                                                                                                                     
    #> [3] 767835057620918272 --https://www.distractify.com/p/does-officer-bradford-die-in-the-rookie                                                                                                      
    #> [4] 863499610676973569 --https://twitter.com/sacramentokings/status/1177736590799470592                                                                                                             
    #> [5] 3859220422         --http://blog.pianetadonna.it/mybeautyblog/tips-tricks-cosmetica-maschera-al-rhum-per-capelli-sfibrati/?utm_source=ReviveOldPost&utm_medium=social&utm_campaign=ReviveOldPost
    #> [6] 1011668178504540160--https://headlines.yahoo.co.jp/hl?a=20190928-00000148-dal-base                                                                                                              
    #> + ... omitted several edges

``` r
as_tweet_network(tweet_net, target_class = "url")
```

    #>  Network attributes:
    #>   vertices = 1055 
    #>   directed = FALSE 
    #>   hyper = FALSE 
    #>   loops = FALSE 
    #>   multiple = TRUE 
    #>   bipartite = 529 
    #>   total edges= 546 
    #>     missing edges= 0 
    #>     non-missing edges= 546 
    #> 
    #>  Vertex attribute names: 
    #>     is_actor vertex.names 
    #> 
    #>  Edge attribute names: 
    #>     relation status_id

### Users to Media

``` r
as_tweet_igraph(tweet_net, target_class = "media")
```

    #> IGRAPH abcc5b6 UN-B 2289 1185 -- 
    #> + attr: name (v/c), type (v/l), status_id (e/c), relation (e/c)
    #> + edges from abcc5b6 (vertex names):
    #>  [1] 247059655          --http://pbs.twimg.com/ext_tw_video_thumb/1177253381737525248/pu/img/tV_OqBoqoueVWHh7.jpg
    #>  [2] 359294371          --http://pbs.twimg.com/ext_tw_video_thumb/1177999900102950914/pu/img/v28CK1AWPeicgfgN.jpg
    #>  [3] 1056020503993888768--http://pbs.twimg.com/ext_tw_video_thumb/1177431694372044805/pu/img/N2RNs1VHUxvbUOZZ.jpg
    #>  [4] 933502505115377665 --http://pbs.twimg.com/ext_tw_video_thumb/1177677156245225473/pu/img/LVpzibdI_HYb-YNU.jpg
    #>  [5] 84458315           --http://pbs.twimg.com/tweet_video_thumb/EFkfnXkXUAEWd9z.jpg                             
    #>  [6] 2259128973         --http://pbs.twimg.com/media/EFkWlRwUwAEylYU.jpg                                         
    #>  [7] 199369785          --http://pbs.twimg.com/media/EFkf2xcX0AAZtWG.png                                         
    #>  [8] 977619299413168129 --http://pbs.twimg.com/media/EFkf0zdWsAYvlKb.jpg                                         
    #> + ... omitted several edges

``` r
as_tweet_network(tweet_net, target_class = "media")
```

    #>  Network attributes:
    #>   vertices = 2289 
    #>   directed = FALSE 
    #>   hyper = FALSE 
    #>   loops = FALSE 
    #>   multiple = TRUE 
    #>   bipartite = 1138 
    #>   total edges= 1185 
    #>     missing edges= 0 
    #>     non-missing edges= 1185 
    #> 
    #>  Vertex attribute names: 
    #>     is_actor vertex.names 
    #> 
    #>  Edge attribute names not shown

## `<proto_net>`

You’re not stuck with going directly to `<igraph>`s or `<network>`s
though. Underneath the hood, `as_tweet_igraph()` and
`as_tweet_network()` use `as_proto_net()` to build a `<proto_net>`, a
list of edge and node data frames.

``` r
as_proto_net(tweet_net,
             all_status_data = TRUE, all_user_data = TRUE)
```

    #> $edges
    #> # A tibble: 9,181 x 20
    #>    from  to    status_id relation created_at          text  status_url source is_quote is_retweeted media_url media_type place_url place_name
    #>    <chr> <chr> <chr>     <chr>    <dttm>              <chr> <chr>      <chr>  <lgl>    <lgl>        <list>    <list>     <chr>     <chr>     
    #>  1 7812… 2476… 11780083… retweet  2019-09-28 18:07:29 RT @… https://t… Twitt… FALSE    FALSE        <chr [1]> <chr [1]>  <NA>      <NA>      
    #>  2 7812… 2476… 11780083… mentions 2019-09-28 18:07:29 RT @… https://t… Twitt… FALSE    FALSE        <chr [1]> <chr [1]>  <NA>      <NA>      
    #>  3 3231… 1151… 11780083… retweet  2019-09-28 18:07:29 RT @… https://t… Twitt… FALSE    FALSE        <chr [1]> <chr [1]>  <NA>      <NA>      
    #>  4 3231… 1151… 11780083… mentions 2019-09-28 18:07:29 RT @… https://t… Twitt… FALSE    FALSE        <chr [1]> <chr [1]>  <NA>      <NA>      
    #>  5 8858… 1122… 11780083… retweet  2019-09-28 18:07:29 RT @… https://t… Twitt… FALSE    FALSE        <chr [1]> <chr [1]>  <NA>      <NA>      
    #>  6 8858… 1122… 11780083… mentions 2019-09-28 18:07:29 RT @… https://t… Twitt… FALSE    FALSE        <chr [1]> <chr [1]>  <NA>      <NA>      
    #>  7 8024… 4316… 11780083… retweet  2019-09-28 18:07:29 RT @… https://t… Twitt… FALSE    FALSE        <chr [1]> <chr [1]>  <NA>      <NA>      
    #>  8 8024… 4316… 11780083… mentions 2019-09-28 18:07:29 RT @… https://t… Twitt… FALSE    FALSE        <chr [1]> <chr [1]>  <NA>      <NA>      
    #>  9 8024… 1033… 11780083… mentions 2019-09-28 18:07:29 RT @… https://t… Twitt… FALSE    FALSE        <chr [1]> <chr [1]>  <NA>      <NA>      
    #> 10 1082… 2949… 11780083… reply_to 2019-09-28 18:07:29 @BNr… https://t… Twitt… FALSE    FALSE        <chr [1]> <chr [1]>  <NA>      <NA>      
    #> # … with 9,171 more rows, and 6 more variables: place_full_name <chr>, place_type <chr>, country <chr>, country_code <chr>, bbox_coords <list>,
    #> #   status_type <chr>
    #> 
    #> $nodes
    #> # A tibble: 8,788 x 20
    #>    name  timestamp_ms        name.y screen_name location description url   protected followers_count friends_count listed_count statuses_count
    #>    <chr> <dttm>              <chr>  <chr>       <chr>    <chr>       <chr> <lgl>               <int>         <int>        <int>          <int>
    #>  1 1000… 2019-09-28 18:07:15 flore… florence__t  <NA>    <NA>        <NA>  FALSE                 580           455            3           7629
    #>  2 1000… 2019-09-28 18:05:37 Lela🍯 Daniela12x  "Guimar… ig: x.dani… <NA>  NA                   1162           185           NA           8248
    #>  3 1000… 2019-09-28 18:06:39 Léa    Lea_Lefebv… "bsm "   on s’était… <NA>  FALSE                 224           126            0           7348
    #>  4 1000… 2019-09-28 18:06:11 joana… aoliveira02 "Lagoa,… since 2002… <NA>  NA                   1914          1914           NA           2566
    #>  5 1000… 2019-09-28 18:06:51 Laura  tbhidegadfb  <NA>    i wanna ro… <NA>  FALSE                 186           142            0           1015
    #>  6 1000… 2019-09-28 18:06:34 ✨Xand… AAlexandre…  <NA>    28/03/2019… <NA>  NA                    354           354           NA           6399
    #>  7 1000… 2019-09-28 18:06:01 <NA>   B_hundred_…  <NA>    <NA>        <NA>  NA                     NA            NA           NA             NA
    #>  8 1000… 2019-09-28 18:06:53 <NA>   promos4dom…  <NA>    <NA>        <NA>  NA                     NA            NA           NA             NA
    #>  9 1000… 2019-09-28 18:06:52 momoi… kur0p0p     "Ochako… I’m Rose!!… <NA>  FALSE                 168           212            5           7503
    #> 10 1000… 2019-09-28 18:05:46 LokiD… LDrake666   "Greens… (Male/stra… <NA>  FALSE                 181          5001            0          27831
    #> # … with 8,778 more rows, and 8 more variables: favourites_count <int>, account_created_at <dttm>, verified <lgl>, profile_url <chr>,
    #> #   account_lang <chr>, profile_banner_url <chr>, profile_image_url <chr>, bbox_coords <list>
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
  - [ ] Tweet networks via `{network}`: currently requires
    [knapply/network](https://github.com/knapply/network) instead of the
    CRAN or [official development
    version](https://github.com/statnet/network) of `{network}`.

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
