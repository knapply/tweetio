# .onLoad <- function(libname, pkgname) {
#   tweetio_opts <- c("tweetio.as_tibble" = "FALSE")
#   
#   opts_to_set <- setdiff(names(tweetio_opts), names(options()))
#   for (i in opts_to_set) {
#     eval(
#       parse(
#         text = paste0("options(", i, "=", tweetio_opts[[i]], ")")
#       )
#     )
#   }
#   
#   invisible()
# }