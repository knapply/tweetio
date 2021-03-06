% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/graphml.R
\name{write_graphml}
\alias{write_graphml}
\title{Write Gephi-Friendly .graphml Files}
\usage{
write_graphml(g, file_path, na_numbers_as = -1, na_characters_as = "", ...)
}
\arguments{
\item{g}{\code{igraph::graph()} object}

\item{file_path}{File path to which to write or from which to read.}

\item{na_numbers_as}{\code{numeric(1L)}, Default: \code{-1}. Value to replace
\code{NA_real_}/\code{NA_integer_}s in the resulting file.}

\item{na_characters_as}{\code{character(1L)}, Default: \code{""}. Value to replace
\code{NA_character_}s in the resulting file.}

\item{...}{Arguments passed to or from other methods.}
}
\description{
Simple, safe transformation of attributes to values with which Gephi will cooperate.
}
\examples{
path_to_tweet_file <- example_tweet_file()

tweet_df <- read_tweets(file_path = path_to_tweet_file)

tweet_graph <- as_igraph(tweet_df)
tweet_graph

graphml_path <- tempfile(fileext = ".graphml")
graphml_path

write_graphml(tweet_graph, file_path = graphml_path) 

}
\author{
Brendan Knapp \email{brendan.g.knapp@nps.edu}
}
