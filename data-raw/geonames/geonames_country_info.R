country_info_file_path <- "inst/extdata/geonames/countryInfo.txt"
if (!file.exists(country_info_file_path)) {
  country_info_url <- "http://download.geonames.org/export/dump/countryInfo.txt"
  download.file(country_info_url, country_info_file_path,
                headers = c(`Accept-Encoding` = "gzip"))
}

build_schema <- function(cols, target_col_names = names(cols)) {
  target_col_indices <- match(target_col_names, names(cols))
  `names<-`(cols, sprintf("V%d", seq_along(cols)))[target_col_indices]
}

cols <- c(
  iso = "character",
  iso3 = "character",
  iso_numeric = "integer",
  fips = "character",
  country = "character",
  capital = "character",
  area_sq_km = "double",
  population = "integer",
  continent = "character",
  tld = "character",
  currency_code = "character",
  currency_name = "character",
  phone = "character",
  postal_code_format = "character",
  postal_code_regex = "character",
  languages = "character",
  geonameid = "integer",
  neighbours = "character",
  equivalent_fips_code = "character"
)

geonames_country_info <- data.table::fread(
  file = country_info_file_path,
  skip = 50,
  col.names = names(cols),
  colClasses = build_schema(cols),
  na.strings = ""
)
geonames_country_info[, neighbours := strsplit(neighbours, ",", fixed = TRUE)]
geonames_country_info[, languages := strsplit(languages, ",", fixed = TRUE)]


















# unique(countrycode::codelist_panel$country.name.de.regex)
#
# dt <- unique(
#   data.table::as.data.table(countrycode::codelist_panel)[, .(country.name.en, country.name.en.regex, country.name.de.regex)]
# )
#
# dt <- unique(data.table::as.data.table(MagicMerge:::.MagicMerge___DICT___))
#
# countries <- dt$name
# regex <- dt$regex
#
# glue::glue(
#   'static constexpr auto {janitor:::make_clean_names(countries)} = ctll::fixed_string(R"({regex})");'
# )
#
# cat(paste(glue::glue('"{regex}"'), collapse = ", "))


