.stop <- function(...) {
  stop(..., call. = FALSE)
}
# .stop <- function(msg, ...) {
#   msg <- sprintf(msg, ...)
#   stop(msg, call. = FALSE)
# }
# 
# .sin_scalar_chr <- function(x) {
#   if (!.is_scalar_chr(x)) {
#     var <- deparse(substitute(x))
#     .stop("`%s` must be a scalar <character>.", var)
#   }
# }
# 
# .sin_file_exists <- function(x) {
#   if (!file.exists(x)) {
#     var <- deparse(substitute(x))
#     .stop("`%s` does not exist.", var)
#   }
# }
# 
# 
