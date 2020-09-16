#' Convert Various Objects to `proto_net`s
#'
#' A `proto_net` is a `list` containing two data frames named `edges` and `nodes`.
#'
#'
#' @template param-tweet_df
#' @template param-target_class
#' @template param-all_status_data
#' @template param-all_user_data
#' @template param-as_tibble
#' @template param-dots
#'
#' @details
#' * In a `proto_net`, users are always to source/from/tail side of dyads. `target_class`
#' defaults to `"user"`, which creates edges where users on both sides of dyads.
#'   + However users can also share edges with `"hashtag"`s, `"url"`s, or `"media"`, so
#'   those values are also valid to provide to `target_class` to create two-mode/bipartite
#'   `proto_net`s.
#' * The edges of a `proto_net` represent the statuses that form each tie, and status-specific
#' columns are attached to the edges.
#' * Casing
#'   + Twitter hashtags are not case-sensitive, so if `target_class` is `"hashtag"` they will
#' be cast to lower-case so they can represent the same node in downstream tasks.
#'   + URLs (after the domain) can be case-sensitive, so they are left as-is.
#'     + If you decide to cast URLs to lower-case yourself, exercise caution with Twitter's
#'     media URLs, as they contain a case-sensitive hash.
#' * `all_status_data` and `all_user_data` default to `FALSE` as they can be performance
#' bottlenecks for large data sets, but they provide a way of building richly decorated
#' networks with the maximum amount of attribute data embedded in the graph structure.
#'
#' @template author-bk
#'
#' @examples
#' path_to_tweet_file <- example_tweet_file()
#'
#' tweet_df <- read_tweets(path_to_tweet_file)
#'
#' as_proto_net(tweet_df, as_tibble = TRUE)
#'
#' as_proto_net(tweet_df, target_class = "hashtag", as_tibble = TRUE)
#'
#' as_proto_net(tweet_df, target_class = "url", as_tibble = TRUE)
#'
#' as_proto_net(tweet_df, target_class = "media", as_tibble = TRUE)
#'
#' as_proto_net(tweet_df, all_status_data = TRUE, all_user_data = TRUE, as_tibble = TRUE)
#'
#' @export
as_proto_net <- function(tweet_df,
                         target_class = c("user", "hashtag", "url", "media"),
                         all_status_data = FALSE,
                         all_user_data = FALSE,
                         as_tibble = tweetio_as_tibble(),
                         ...) {
  UseMethod("as_proto_net")
}


#' @rdname as_proto_net
#'
#' @export
as_proto_net.data.frame <- function(tweet_df,
                                    target_class = c("user", "hashtag", "url", "media"),
                                    all_status_data = FALSE,
                                    all_user_data = FALSE,
                                    as_tibble = tweetio_as_tibble(),
                                    ...) {
  as_proto_net(
    .as_dt(tweet_df),
    target_class = target_class,
    all_status_data = all_status_data,
    all_user_data = all_user_data,
    as_tibble = as_tibble,
    ...
  )
}


#' @rdname as_proto_net
#'
#' @importFrom data.table %chin% rbindlist setcolorder setDT setnames
#'
#' @export
as_proto_net.data.table <- function(tweet_df,
                                    target_class = c("user", "hashtag", "url", "media"),
                                    all_status_data = FALSE,
                                    all_user_data = FALSE,
                                    as_tibble = tweetio_as_tibble(),
                                    ...) {
  # silence R CMD Check NOTE =============================================================
  relation <- NULL
  to <- NULL
  # ======================================================================================
  target_class <- match.arg(target_class, c("user", "hashtag", "url", "media"))

  target <- switch(
    target_class
    ,
    user = "user_id",
    hashtag = "hashtags",
    url = "urls_expanded_url",
    media = "media_url"
    ,
    stop("unknown `target_class`", call. = FALSE)
  )

  targets <- list(
    main = if (target_class == "user") NULL else target,
    retweet = sprintf("retweet_%s", target),
    reply_to = sprintf("reply_to_%s", target),
    quoted = sprintf("quoted_%s", target),
    mentions = sprintf("mentions_%s", target)
  )
  targets <- .keep(.compact(targets),
                   function(.x) .x %chin% names(tweet_df))

  edge_by_status_type <- .imap(targets, function(.x, .y) {
    edge_cols <- c("user_id", .x, "status_id", "created_at")

    res <- tweet_df[!is.na(get(.x)), edge_cols, with = FALSE]

    if (is.list(res[[.x]])) {
      res <- .unnest_edges(
        user_id = res[["user_id"]],
        target = res[[.x]],
        status_id = res[["status_id"]],
        created_at = res[["created_at"]]
      )
      res <- data.table::setDT(res)
    }

    data.table::setnames(res, c("from", "to", "status_id", "created_at"))
    unique(res[, relation := if (.y == "main")
      "uses"
      else
        .y])
  })

  edges <- rbindlist(edge_by_status_type, use.names = TRUE)

  if (all_status_data) {
    edges <- edges[extract_statuses(tweet_df, as_tibble = FALSE),
                   on = "status_id", nomatch = 0L]
  }

  setcolorder(edges, intersect(
    names(edges),
    c("from", "to", "relation", "status_id", "created_at", "text")
  ))

  if (target_class == "hashtag") {
    edges[, to := tolower(to)]
  }

  nodes <- data.table(name = unique(c(edges$from, edges$to)))

  if (all_user_data) {
    nodes <- merge(
      x = nodes,
      y = extract_users(tweet_df),
      by.x = "name",
      by.y = "user_id",
      all.x = TRUE
    )
  }

  structure(
    list(
      edges = .finalize_df(edges, as_tibble),
      nodes = .finalize_df(nodes, as_tibble)
    ),
    class = "proto_net",
    target_class = target_class
  )
}
