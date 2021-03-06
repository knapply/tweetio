% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/read.R
\name{read_tweets}
\alias{read_tweets}
\alias{read_tweets_bulk}
\title{Read Tweets into a Data Frame}
\usage{
read_tweets(
  file_path,
  as_tibble = tweetio_as_tibble(),
  verbose = tweetio_verbose(),
  ...
)

read_tweets_bulk(
  file_path,
  as_tibble = tweetio_as_tibble(),
  verbose = tweetio_verbose(),
  in_parallel = TRUE,
  strategy = NULL,
  ...
)
}
\arguments{
\item{file_path}{Path(s) to tweet files.}

\item{as_tibble}{\verb{<logical>}, Default: \code{tweetio_as_tibble()}.
Whether a \code{\link[tibble:tibble]{tibble::tibble()}} should be returned. Ignored if the \code{{tibble}}
package is not installed.}

\item{verbose}{\verb{<logical>}, Default: \code{tweetio_verbose()}.
Whether to show diagnostic or progress messages.}

\item{...}{Arguments passed to or from other methods.}

\item{in_parallel}{Default: \code{TRUE}. Whether to use \code{future.apply::future_lapply()}
to process the files in parallel. Ignored if \code{{future}} or \code{{future.apply}} are not installed.}

\item{strategy}{Default: \code{NULL}. argument passed to \code{future::plan()}'s \code{strategy} parameter.
If \code{NULL}, \code{future::multiprocess} is used. Ignored if \code{{future}} or \code{{future.apply}} are not installed.}
}
\value{
\itemize{
\item Data Frame
\itemize{
\item default: \code{\link[data.table:data.table]{data.table::data.table()}}
\item \code{\link[tibble:tibble]{tibble::tibble()}} if \code{as_tibble} is \code{TRUE} and \code{{tibble}} is installed.
}
}
}
\description{
Go from a file of raw tweet data to a convenient, \code{{rtweet}}-style data frame.
}
\examples{
path_to_tweet_file <- example_tweet_file()

tweet_data.table <- read_tweets(file_path = path_to_tweet_file)

tweet_tibble <- read_tweets(file_path = path_to_tweet_file, as_tibble = TRUE)

tweet_tibble

}
\author{
Brendan Knapp \email{brendan.g.knapp@nps.edu}
}
