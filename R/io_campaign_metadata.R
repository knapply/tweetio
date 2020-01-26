#' Twitter-released IO Campaign Metadata
#' 
#' Metadata describing data archives that Twitter believes are part of potentially
#' state-backed information operations campaigns.
#' 
#' @details 
#' Twitter updates the data archives available on a regular basis, so these
#' may be out of date. You can help by filing issues at
#' \url{https://github.com/knapply/tweetio/issues}.
#' 
#' The following information is from Twitter:
#' 
#' * _"Note that by downloading these files, you are accepting the [Twitter Developer Agreement and Policy](https://t.co/devpolicy)."_
#' * _"These datasets are of a size that a degree of capability for large dataset analysis is required, we hope to support broad analysis by making a public version of these datasets (with some account-specific information hashed) available. You can download the datasets below. No content has been redacted. Specialist researchers can request access to an unhashed version of these datasets, which will be governed by a data use agreement that will include provisions to ensure the data is used within appropriate legal and ethical parameters."_
#' * _"These datasets include all public, nondeleted Tweets and media (e.g., images and videos) from accounts we believe are connected to state-backed information operations. Tweets deleted by these users prior to their suspension (which are not included in these datasets) generally comprise less than 1% of their overall activity. Note that not all of the accounts we identified as connected to these campaigns actively Tweeted, so the number of accounts represented in the datasets may be less than the total number of accounts listed here."_
#' 
#' @source 
#' \url{https://transparency.twitter.com/en/information-operations.html}
#' 
#' @template author-bk
#' 
#' @examples
#' io_campaign_metadata[, .(campaign_name, date_released, entities)]
"io_campaign_metadata"