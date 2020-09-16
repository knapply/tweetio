fs <- data.table::data.table(
  url = c(
    "http://download.geonames.org/export/dump/admin1CodesASCII.txt",
    "http://download.geonames.org/export/dump/admin2Codes.txt"
  )
)
fs[, file_path := sprintf("inst/extdata/geonames/%s", basename(urls))]


missing <- fs[!file.exists(file_path)]
if (nrow(missing) > 0) {
  download.file(missing$url, missing$file_path, headers = c(`Accept-Encoding` = "gzip"))
}


col_names <- c("code", "name", "name_ascii", "geonameid")

geonames_admin <- data.table::rbindlist(
  lapply(fs$file_path, data.table::fread, col.names = col_names, na.strings = ""),
  idcol = "admin_level"
)
