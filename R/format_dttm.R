format_dttm <- function(x, time_zone = "UTC", warn = TRUE) {
  if (inherits(x, "POSIXct")) {
    return(x)
  }
  out <- structure(rep(NA_real_, length(x)),
                   class = c("POSIXct", "POSIXt"),
                   tzone = "UTC")
    # rep(NA_real_, length(x) as.POSIXct(NA, tz = time_zone,
                        # origin = structure(0, class = c("POSIXct", "POSIXt"))), 
             # length(x))
  if (all(is.na(x))) {
    return(out)
  }
  
  out[is.na(out) & !is.na(x)] <- as.POSIXct(
    x[is.na(out) & !is.na(x)], 
    format = "%a %b %d %T %z %Y",
    tz = time_zone
  )
  
  if (any(is.na(out) & !is.na(x))) {
    out[is.na(out) & !is.na(x)] <- as.POSIXct(
      x[is.na(out) & !is.na(x)], 
      format = "%a %b %d %H:%M:%S %z %Y",
      tz = time_zone
    )
  } else {
    attr(out, "tzone") <- time_zone
    return(out)
  }
  
  if (any(is.na(out) & !is.na(x))) {
    out[is.na(out) & !is.na(x)] <- as.POSIXct(
      x[is.na(out) & !is.na(x)],
      format = "%a, %d %b %Y %H:%M:%S +0000",
      tz = time_zone
    )
  } else {
    attr(out, "tzone") <- time_zone
    return(out)
  }

  if (any(is.na(out) & !is.na(x))) {
    out[is.na(out) & !is.na(x)] <- as.POSIXct(
      x[is.na(out) & !is.na(x)],
      format = "%a %b %d %H:%M:%S +0000 %Y",
      tz = time_zone
    )
  } else {
    attr(out, "tzone") <- time_zone
    return(out)
  }

  if (any(is.na(out) & !is.na(x))) {
    out[is.na(out) & !is.na(x)] <- as.POSIXct(
      x[is.na(out) & !is.na(x)],
      format = "%Y-%m-%dT%H:%M:%OS+00:00",
      tz = time_zone
    )
  } else {
    attr(out, "tzone") <- time_zone
    return(out)
  }


  if (any(is.na(out) & !is.na(x))) {
    out[is.na(out) & !is.na(x)] <- as.POSIXct(
      x[is.na(out) & !is.na(x)],
      format = "%Y-%m-%d %H:%M:%S",
      tz = time_zone
    )
  } else {
    attr(out, "tzone") <- time_zone
    return(out)
  }



  # always do last
  if (any(is.na(out) & !is.na(x))) {
    out[is.na(out) & !is.na(x)] <- as.POSIXct(
      as.double(x[is.na(out) & !is.na(x)]) / 1000,
      origin = structure(0, class = c("POSIXct", "POSIXt"),
                         tzone = time_zone)
    )
  } else {
    attr(out, "tzone") <- time_zone
    return(out)
  }

  attr(out, "tzone") <- time_zone
  
  out
}
