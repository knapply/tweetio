
<!-- README.Rmd generates README.md. -->

# `{tweetio}`

<!-- badges: start -->

[![CRAN
status](https://www.r-pkg.org/badges/version/tweetio)](https://cran.r-project.org/package=tweetio)
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

# Progress

### Supported Data Inputs

  - [x] Twitter API streams: .json, .json.gz
  - [x] API to Elasticsearch data dump (JSON Array): .json, .json.gz
  - [x] API to Elasticsearch data dump (line-delimited JSON): .jsonl,
    .jsonl.gz

### Supported Data Outputs

  - [x] .graphml, currently available in
    [`{tweetgraph}`](https://knapply.github.io/tweetgraph/)
  - [ ] CSV (will likely be CSVY once `{data.table}`’s `fread(yaml =
    TRUE)` feature stabilizes)

### Extras

  - [x] Spatial Tweets via `tweetio::as_tweet_sf()`

# Introduction

`{tweetio}` (mainly) focuses on one thing: **going from raw tweets to
`{rtweet}`-style data frames and other useful structures) as quickly as
possible**. Whether the data came from the Twitter API, a database dump,
or some other source, `{tweetio}`’s job is to get them into R.

`{tweetio}` is **not** a competitor to `{rtweet}`; it is not interested
in collecting Twitter data. That said, it definitely attempts to emulate
its data frame schema because…

1.  It’s incredibly easy to use.
2.  It’s more efficient to analyze than a key-value format following the
    raw data.
3.  It’d be a waste not to maximize compatibiltiy with tools built
    specifically around `{rtweet}`’s data frames.

# Installation

You’ll need a C++ compiler. If you’re using Windows, you’ll need
[Rtools](https://cran.r-project.org/bin/windows/Rtools/).

You probably want to follow the page’s advice and select the recommended
version, which is currently Rtools35.exe. When you’re installing Rtools,
you need to make sure you check the box stating “Add rtools to system
PATH” and reboot when you’re finished.

Once you’re done, reboot. Then you can install `{tweetio}`.

``` r
# install.packages("remotes")
remotes::install_github("knapply/tweetio")
```

# Usage

## Simple Example

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

tibble::as_tibble(small_rtweet_stream)
```

    #> # A tibble: 500 x 88
    #>    user_id status_id created_at          screen_name text  source reply_to_status~ reply_to_user_id
    #>    <chr>   <chr>     <dttm>              <chr>       <chr> <chr>  <chr>            <chr>           
    #>  1 247833~ 11958876~ 2019-11-17 02:13:40 bota_dasso  "<U+30D1><U+30F3><U+30C0>~ "<a h~ <NA>             <NA>            
    #>  2 116847~ 11958876~ 2019-11-17 02:13:40 shi_na_bd   "RT ~ "<a h~ <NA>             <NA>            
    #>  3 104198~ 11958876~ 2019-11-17 02:13:40 ryo09q      RT @~ "<a h~ <NA>             <NA>            
    #>  4 118719~ 11958876~ 2019-11-17 02:13:40 jannyyy20   "RT ~ "<a h~ <NA>             <NA>            
    #>  5 627279~ 11958876~ 2019-11-17 02:13:40 winoahkate  Grab~ "<a h~ <NA>             <NA>            
    #>  6 294145~ 11958876~ 2019-11-17 02:13:40 stephakwn   "RT ~ "<a h~ <NA>             <NA>            
    #>  7 840012~ 11958876~ 2019-11-17 02:13:40 okhmmmmmm   @Alt~ "<a h~ 119587443069556~ 2206366166      
    #>  8 793423~ 11958876~ 2019-11-17 02:13:40 jeerachxya  "RT ~ "<a h~ <NA>             <NA>            
    #>  9 875281~ 11958876~ 2019-11-17 02:13:40 yoksemanga~ @urn~ "<a h~ 119588051448317~ 113946041537135~
    #> 10 298855~ 11958876~ 2019-11-17 02:13:40 sas_0515    <U+79C1><U+304C><U+9078><U+3093>~ "<a h~ <NA>             <NA>            
    #> # ... with 490 more rows, and 80 more variables: reply_to_screen_name <chr>, is_quote <lgl>,
    #> #   is_retweet <lgl>, hashtags <list>, urls_expanded_url <list>, media_url <list>,
    #> #   media_expanded_url <list>, media_type <list>, mentions_user_id <list>,
    #> #   mentions_screen_name <list>, quoted_status_id <chr>, quoted_text <chr>,
    #> #   quoted_created_at <dttm>, quoted_source <chr>, quoted_favorite_count <int>,
    #> #   quoted_retweet_count <int>, quoted_user_id <chr>, quoted_screen_name <chr>, quoted_name <chr>,
    #> #   quoted_followers_count <int>, quoted_friends_count <int>, quoted_statuses_count <int>,
    #> #   quoted_location <chr>, quoted_description <chr>, quoted_verified <lgl>,
    #> #   retweet_status_id <chr>, retweet_text <chr>, retweet_created_at <dttm>, retweet_source <chr>,
    #> #   retweet_favorite_count <int>, retweet_retweet_count <int>, retweet_user_id <chr>,
    #> #   retweet_screen_name <chr>, retweet_name <chr>, retweet_followers_count <int>,
    #> #   retweet_friends_count <int>, retweet_statuses_count <int>, retweet_location <chr>,
    #> #   retweet_description <chr>, retweet_verified <lgl>, place_url <chr>, place_name <chr>,
    #> #   place_full_name <chr>, place_type <chr>, country <chr>, country_code <chr>, bbox_coords <list>,
    #> #   status_url <chr>, name <chr>, location <chr>, description <chr>, url <chr>, protected <lgl>,
    #> #   followers_count <int>, friends_count <int>, listed_count <int>, statuses_count <int>,
    #> #   favourites_count <int>, account_created_at <dttm>, verified <lgl>, account_lang <chr>,
    #> #   profile_banner_url <chr>, profile_image_url <chr>, is_retweeted <lgl>, retweet_place_url <chr>,
    #> #   retweet_place_name <chr>, retweet_place_full_name <chr>, retweet_place_type <chr>,
    #> #   retweet_country <chr>, retweet_country_code <chr>, retweet_bbox_coords <list>,
    #> #   quoted_place_url <chr>, quoted_place_name <chr>, quoted_place_full_name <chr>,
    #> #   quoted_place_type <chr>, quoted_country <chr>, quoted_country_code <chr>,
    #> #   quoted_bbox_coords <list>, timestamp_ms <dttm>, contributors_enabled <lgl>

## Scaling Up

We’re more interested in handling much larger data sets, like this one
that was also obtained using `rtweet::stream_tweets()`. The JSON has
been compressed to an 124 Mb .gz file (1.2 Gb uncompressed).

Currently, `{rtweet}` may fail parsing streams because the data returned
may not be valid JSON.

``` r
rtweet_stream_path <- "~/ufc-tweet-stream.json"

rtweet::parse_stream(rtweet_stream_path)
```

    #> Error: parse error: unallowed token at this point in JSON text
    #>           lW1XoltIuSwkW1T.mp4?tag=10"},,{"bitrate":832000,"content_typ
    #>                      (right here) ------^

The only way around this is to read the entire file into memory and run
some validation routine before parsing.

Fortunately, `{tweetio}` can handle these situations by dropping invalid
JSON on the fly.

``` r
big_rtweet_stream <- read_tweets(rtweet_stream_path)

tibble::as_tibble(big_rtweet_stream)
```

    #> # A tibble: 140,368 x 88
    #>    user_id status_id created_at          screen_name text  source reply_to_status~ reply_to_user_id
    #>    <chr>   <chr>     <dttm>              <chr>       <chr> <chr>  <chr>            <chr>           
    #>  1 340165~ 11908502~ 2019-11-03 04:36:36 M_Ahmad07   RT @~ "<a h~ <NA>             <NA>            
    #>  2 502298~ 11908502~ 2019-11-03 04:36:36 Willcan     RT @~ "<a h~ <NA>             <NA>            
    #>  3 111335~ 11908502~ 2019-11-03 04:36:36 heroXclass  RT @~ "<a h~ <NA>             <NA>            
    #>  4 112082~ 11908502~ 2019-11-03 04:36:36 alicea561   Man ~ "<a h~ <NA>             <NA>            
    #>  5 294507~ 11908502~ 2019-11-03 04:36:36 JustinCull~ Brut~ "<a h~ <NA>             <NA>            
    #>  6 250392~ 11908502~ 2019-11-03 04:36:36 jppppppxo   the ~ "<a h~ <NA>             <NA>            
    #>  7 342703~ 11908502~ 2019-11-03 04:36:36 JonasParad~ RT @~ "<a h~ <NA>             <NA>            
    #>  8 242656~ 11908502~ 2019-11-03 04:36:36 js_cuellar  RT @~ "<a h~ <NA>             <NA>            
    #>  9 104913~ 11908502~ 2019-11-03 04:36:36 SHREWDCOLTS RT @~ "<a h~ <NA>             <NA>            
    #> 10 245455~ 11908502~ 2019-11-03 04:36:36 PaulWhittl~ WoW ~ "<a h~ <NA>             <NA>            
    #> # ... with 140,358 more rows, and 80 more variables: reply_to_screen_name <chr>, is_quote <lgl>,
    #> #   is_retweet <lgl>, hashtags <list>, urls_expanded_url <list>, media_url <list>,
    #> #   media_expanded_url <list>, media_type <list>, mentions_user_id <list>,
    #> #   mentions_screen_name <list>, quoted_status_id <chr>, quoted_text <chr>,
    #> #   quoted_created_at <dttm>, quoted_source <chr>, quoted_favorite_count <int>,
    #> #   quoted_retweet_count <int>, quoted_user_id <chr>, quoted_screen_name <chr>, quoted_name <chr>,
    #> #   quoted_followers_count <int>, quoted_friends_count <int>, quoted_statuses_count <int>,
    #> #   quoted_location <chr>, quoted_description <chr>, quoted_verified <lgl>,
    #> #   retweet_status_id <chr>, retweet_text <chr>, retweet_created_at <dttm>, retweet_source <chr>,
    #> #   retweet_favorite_count <int>, retweet_retweet_count <int>, retweet_user_id <chr>,
    #> #   retweet_screen_name <chr>, retweet_name <chr>, retweet_followers_count <int>,
    #> #   retweet_friends_count <int>, retweet_statuses_count <int>, retweet_location <chr>,
    #> #   retweet_description <chr>, retweet_verified <lgl>, place_url <chr>, place_name <chr>,
    #> #   place_full_name <chr>, place_type <chr>, country <chr>, country_code <chr>, bbox_coords <list>,
    #> #   status_url <chr>, name <chr>, location <chr>, description <chr>, url <chr>, protected <lgl>,
    #> #   followers_count <int>, friends_count <int>, listed_count <int>, statuses_count <int>,
    #> #   favourites_count <int>, account_created_at <dttm>, verified <lgl>, account_lang <chr>,
    #> #   profile_banner_url <chr>, profile_image_url <chr>, is_retweeted <lgl>, retweet_place_url <chr>,
    #> #   retweet_place_name <chr>, retweet_place_full_name <chr>, retweet_place_type <chr>,
    #> #   retweet_country <chr>, retweet_country_code <chr>, retweet_bbox_coords <list>,
    #> #   quoted_place_url <chr>, quoted_place_name <chr>, quoted_place_full_name <chr>,
    #> #   quoted_place_type <chr>, quoted_country <chr>, quoted_country_code <chr>,
    #> #   quoted_bbox_coords <list>, timestamp_ms <dttm>, contributors_enabled <lgl>

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
    #>                             expr      min       lq     mean   median       uq      max neval
    #>  read_tweets(rtweet_stream_path) 13.48611 14.02401 14.58772 14.56191 15.13853 15.71514     3

## Data Dumps

Using Elasticsearch seems to be the most common practice for handling
social media data at scale, but it’s (unfortunately) possible that
you’ll need to work with data dumps.

The data collected from APIs are stored inside a nested JSON object
named `"doc"`. `"doc"` is typically embedded in a ton of system
metadata, most of which you probably don’t care about.

I’ve encountered two flavors of these schema:

1.  .jsonl: newline-delimited JSON
2.  .json: the complete contents of a database dump packed in a JSON
    array

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

And the .json structure looks something like this:

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
            "more_metadata6": "blahblahblah"
        }
    },
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
            "more_metadata6": "blahblahblah"
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

`{tweetio}` solves this by parsing everything and building the data
frames at the C++ level.

Here’s a benchmark for reading a 890 Mb JSON array data dump.

``` r
res <- microbenchmark(

  read_tweets(data_dump) # *****************************************************
  
  , times = 3
)

res
```

    #> Unit: seconds
    #>                    expr      min       lq     mean   median       uq      max neval
    #>  read_tweets(data_dump) 4.389449 4.514836 4.617916 4.640224 4.732149 4.824074     3

# Spatial Tweets

Tweet JSON contains an object called `"place"` that is set aside for
location information. If present, it looks something like the following.

``` json
{
    "text": "#rstats4lyfe",
    "place": {
      "id": "00d546b224a6764d",
      "url": "https://api.twitter.com/1.1/geo/id/blahblah.json",
      "place_type": "city",
      "name": "General Pico",
      "full_name": "General Pico, Argentina",
      "country_code": "AR",
      "country": "Argentina",
      "bounding_box": {
          "type": "Polygon",
          "coordinates": [
              [
                  [
                      -63.784544,
                      -35.689402
                  ],
                  [
                      -63.784544,
                      -35.641737
                  ],
                  [
                      -63.724717,
                      -35.641737
                  ],
                  [
                      -63.724717,
                      -35.689402
                  ]
              ]
          ]
      },
      "attributes": {}
    }
}
```

In `{rtweet}`-style data frames, this corresponds to the `bbox_coords`
column.

If you have `{sf}` installed, you can use `as_tweet_sf()` to filter the
tweets for those that contain valid coordinates and build their bounding
box polygons.

``` r
tweet_sf <- as_tweet_sf(tweet_df = big_rtweet_stream) 

tweet_sf[, "bbox_coords"]
```

    #> Simple feature collection with 2215 features and 0 fields
    #> geometry type:  GEOMETRY
    #> dimension:      XY
    #> bbox:           xmin: -180 ymin: -50.35726 xmax: 180 ymax: 71.43436
    #> epsg (SRID):    4326
    #> proj4string:    +proj=longlat +datum=WGS84 +no_defs
    #> # A tibble: 2,215 x 1
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
    #> # ... with 2,205 more rows

There are currently three columns that can potentially hold bounding
boxes:

1.  `bbox_coords`
2.  `quoted_bbox_coords`
3.  `retweet_bbox_coords`

You can select which one to use to build your `sf` object by modifying
the `geom_col=` parameter (default: `"bbox_coords"`)

``` r
as_tweet_sf(big_rtweet_stream, geom_col = "quoted_bbox_coords"
            )[, "quoted_bbox_coords"]
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
    #> # ... with 1,244 more rows

You can also build *all* the supported bounding boxes by setting
`geom_col=` to `"all"`.

``` r
all_bboxes <- as_tweet_sf(big_rtweet_stream, geom_col = "all")
all_bboxes[, c("geometry", "which_geom")]
```

    #> Simple feature collection with 7441 features and 1 field
    #> geometry type:  GEOMETRY
    #> dimension:      XY
    #> bbox:           xmin: -180 ymin: -50.35726 xmax: 180 ymax: 71.43436
    #> epsg (SRID):    4326
    #> proj4string:    +proj=longlat +datum=WGS84 +no_defs
    #> # A tibble: 7,441 x 2
    #>                                                                                  geometry which_geom
    #>                                                                             <POLYGON [°]> <chr>     
    #>  1 ((-90.23761 29.96836, -90.23761 30.03413, -90.11965 30.03413, -90.11965 29.96836, -90~ bbox_coor~
    #>  2 ((-80.20811 26.08094, -80.20811 26.2198, -80.09024 26.2198, -80.09024 26.08094, -80.2~ bbox_coor~
    #>  3 ((17.08005 59.73069, 17.08005 60.18611, 18.47324 60.18611, 18.47324 59.73069, 17.0800~ bbox_coor~
    #>  4 ((-80.51985 39.7198, -80.51985 42.51607, -74.68952 42.51607, -74.68952 39.7198, -80.5~ bbox_coor~
    #>  5 ((-80.34364 25.59918, -80.34364 25.64553, -80.2875 25.64553, -80.2875 25.59918, -80.3~ bbox_coor~
    #>  6 ((-118.6684 33.70454, -118.6684 34.33704, -118.1554 34.33704, -118.1554 33.70454, -11~ bbox_coor~
    #>  7 ((-122.0662 37.92423, -122.0662 38.02242, -121.931 38.02242, -121.931 37.92423, -122.~ bbox_coor~
    #>  8 ((-118.4485 33.97688, -118.4485 34.03514, -118.3695 34.03514, -118.3695 33.97688, -11~ bbox_coor~
    #>  9 ((-97.66262 27.57851, -97.66262 27.89579, -97.20223 27.89579, -97.20223 27.57851, -97~ bbox_coor~
    #> 10 ((-118.6684 33.70454, -118.6684 34.33704, -118.1554 34.33704, -118.1554 33.70454, -11~ bbox_coor~
    #> # ... with 7,431 more rows

``` r
unique(all_bboxes$which_geom)
```

    #> [1] "bbox_coords"         "quoted_bbox_coords"  "retweet_bbox_coords"

From there, you can easily use the data like any other `{sf}` object.

``` r
library(ggplot2)

world <- rnaturalearth::ne_countries(returnclass = "sf")
world <- world[world$continent != "Antarctica", ]

ggplot(all_bboxes) +
  geom_sf(fill = "white", color = "lightgray", data = world) +
  geom_sf(aes(fill = which_geom, color = which_geom), alpha = 0.15, size = 1, show.legend = TRUE) +
  coord_sf(crs = 3857) +
  scale_fill_viridis_d() +
  scale_color_viridis_d() +
  theme(legend.title = element_blank(), legend.position = "top",
        panel.background = element_rect(fill = "#daf3ff"))
```

<img src="man/figures/unnamed-chunk-16-1.png" style="display: block; margin: auto;" />

# How can we go faster?

Until Rtools 4.0 hits (or the
[`simdjson`](https://github.com/lemire/simdjson) library decides to
[relax its C++17
requirement](https://github.com/lemire/simdjson/issues/307)), I’m not
sure how we can go much faster while maintaining cross-platform
compatibility. That said, if C++ is your mother tongue (and you see room
for optimization), please don’t hesitate to contribute.

# Acknowledgements

`{tweetio}` uses a combination of C++ via
[`{Rcpp}`](http://www.rcpp.org/), the
[`rapidjson`](http://rapidjson.org/) C++ library (made available by
[`{rapidjsonr}`](https://cran.r-project.org/web/packages/rapidjsonr/index.html)),
and **R’s secret weapon**:
[`{data.table}`](https://rdatatable.gitlab.io/data.table/).

Major inspiration from [{`ndjson`}](https://gitlab.com/hrbrmstr/ndjson)
was taken, particularly its use of
[`Gzstream`](https://www.cs.unc.edu/Research/compgeom/gzstream/).
