library(data.table)

print.data.table <- function(x, ...) print(tibble::as_tibble(x), ...)


MINIMUM_POPULATION <- 0L
MINIMUM_CHARACTERS <- 2L
MAXIMUM_CHARACTERS <- 30L


all_countries_file_path <- "inst/extdata/geonames/allCountries.txt"
if (!file.exists(all_countries_file_path)) {
  all_countries_url <- "http://download.geonames.org/export/dump/allCountries.zip"
  temp_file <- tempfile()
  download.file(all_countries_url, temp_file)
  unzip(temp_file, exdir =  "inst/extdata/geonames/")
}




cols <- c(
  geonameid = "integer",        # integer id of record in geonames database
  name = "character",           # name of geographical point (utf8) varchar(200)
  asciiname = "character",      # name of geographical point in plain ascii characters, varchar(200)
  alternatenames = "character", # alternatenames, comma separated, ascii names automatically transliterated, convenience attribute from alternatename table, varchar(10000)
  latitude = "double",          # latitude in decimal degrees (wgs84)
  longitude = "double",         # longitude in decimal degrees (wgs84)
  feature_class = "character",  # see http://www.geonames.org/export/codes.html, char(1)
  feature_code = "character",   # see http://www.geonames.org/export/codes.html, varchar(10)
  country_code = "character",   # ISO-3166 2-letter country code, 2 characters
  cc2 = "character",            # alternate country codes, comma separated, ISO-3166 2-letter country code, 200 characters
  admin1 = "character",         # fipscode (subject to change to iso code), see exceptions below, see file admin1Codes.txt for display names of this code; varchar(20)
  admin2 = "character",         # code for the second administrative division, a county in the US, see file admin2Codes.txt; varchar(80)
  admin3 = "character",         # code for third level administrative division, varchar(20)
  admin4 = "character",         # code for fourth level administrative division, varchar(20)
  population = "integer64",     # bigint (8 byte int)
  elevation = "integer",        # in meters, integer
  dem = "integer",              # digital elevation model, srtm3 or gtopo30, average elevation of 3''x3'' (ca 90mx90m) or 30''x30'' (ca 900mx900m) area in meters, integer. srtm processed by cgiar/ciat.
  timezone = "character",       # the iana timezone id (see file timeZone.txt) varchar(40)
  modification_date = "Date"    # date of last modification in yyyy-MM-dd format
)

# target_col_names <- c("geonameid", "name", "asciiname", "alternatenames",
#                       "admin1", "admin2", "admin3", "admin4",
#                       "country_code",
#                       "latitude", "longitude",
#                       "population")
cols_to_skip <- c("feature_class", "feature_code", "elevation", "dem",
                  "timezone", "modification_date")
target_col_names <- setdiff(names(cols), cols_to_skip)
target_col_indices <- match(target_col_names, names(cols))
target_cols <- `names<-`(cols, sprintf("V%d", seq_along(cols)))[target_col_indices]

geonames_all_countries <- data.table::fread(
  file = all_countries_file_path,
  select = target_cols,
  col.names = target_col_names,
  na.strings = "",
  sep = "\t",
  quote = ""
)[population > MINIMUM_POPULATION & name != "Earth"
  ][, alternatenames := stringi::stri_split_fixed(alternatenames, ",")
    ][, cc2 := stringi::stri_split_fixed(cc2, ",")
      ][, admin_lvl := data.table::fcase(!is.na(admin4), 4L,
                                         !is.na(admin3), 3L,
                                         !is.na(admin2), 2L,
                                         !is.na(admin1), 1L)
        ][, -c("admin1", "admin2", "admin3", "admin4")
          ][!is.na(admin_lvl)
            ][order(population, decreasing = TRUE)
              ]



# geonames_all_countries <- geonames_all_countries[country_code == "BY"]

# alt_names ==============================================================================
alt_names_file_path <- "inst/extdata/geonames/alternateNamesV2.txt"
if (!file.exists(alt_names_file_path)) {
  alt_names_url <- "http://download.geonames.org/export/dump/alternateNamesV2.zip"
  temp_file <- tempfile()
  download.file(alt_names_url, temp_file)
  unzip(temp_file, exdir =  "inst/extdata/geonames/")
}


alt_names_cols <- c(
  alternateNameId = "integer",   # : the id of this alternate name, int
  geonameid = "integer",         # : geonameId referring to id in table 'geoname', int
  isolanguage = "character",     # : iso 639 language code 2- or 3-characters; 4-characters 'post' for postal codes and 'iata','icao' and faac for airport codes, fr_1793 for French Revolution names,  abbr for abbreviation, link to a website (mostly to wikipedia), wkdt for the wikidataid, varchar(7)
  alternate_name = "character",  # : alternate name or name variant, varchar(400)
  isPreferredName = "integer",   # : '1', if this alternate name is an official/preferred name
  isShortName = "integer",       # : '1', if this is a short name like 'California' for 'State of California'
  isColloquial = "integer",      # : '1', if this alternate name is a colloquial or slang term. Example: 'Big Apple' for 'New York'.
  isHistoric = "integer",        # : '1', if this alternate name is historic and was used in the past. Example 'Bombay' for 'Mumbai'.
  from = "character",            # : from period when the name was used
  to = "character"		           # : to period when the name was used
)
alt_names_target_col_names <- names(alt_names_cols)[1:8]
alt_names_target_cols <- `names<-`(
  alt_names_cols, sprintf("V%d", seq_along(alt_names_cols))
  )[match(alt_names_target_col_names, names(alt_names_cols))]

lgl_cols <- names(alt_names_cols)[grepl("^is[A-Z]", names(alt_names_cols))]

geonames_alt_names <- data.table::fread(
  file = alt_names_file_path,
  col.names = alt_names_target_col_names,
  select = alt_names_target_cols,
  sep = "\t",
  na.strings = "",
  quote = ""
  )[, n_char := nchar(alternate_name)
    ][n_char >= MINIMUM_CHARACTERS &
        n_char <= MAXIMUM_CHARACTERS &
        !grepl("^https?://", alternate_name) &
        geonameid %in% geonames_all_countries$geonameid
      ][, (lgl_cols) := lapply(.SD, Negate(is.na)),
        .SDcols = lgl_cols
        ]



# hierarchy ==============================================================================
hierarchy_file_path <- "inst/extdata/geonames/hierarchy.txt"
if (!file.exists(hierarchy_file_path)) {
  hierarchy_url <- "http://download.geonames.org/export/dump/hierarchy.zip"
  temp_file <- tempfile()
  download.file(hierarchy_url, temp_file)
  unzip(temp_file, exdir = "inst/extdata/geonames")
}

geonames_hierarchy <- data.table::fread(
  file = hierarchy_file_path,
  select = c(V1 = "integer", V2 = "integer"), # , V3 = "character"),
  col.names = c("parent", "child"), # , "ADM"),
  na.strings = ""
)[parent %in% geonames_all_countries$geonameid &
    child %in% geonames_all_countries$geonameid &
    parent %in% geonames_alt_names$geonameid &
    child %in% geonames_alt_names$geonameid
  ]


### tree graph ===========================================================================
build_ancestors <- function(el) {
  g <- igraph::graph_from_data_frame(el)
  geoids <- as.integer(igraph::V(g)$name)

  lapply(as.double(seq_len(igraph::vcount(g)) - 1), function(.root) {
    geoids[.Call(igraph:::C_R_igraph_subcomponent, g, .root, 1) + 1]
  })
}


ancestors <- build_ancestors(geonames_hierarchy)

# cartesian_product(ancestors[[999]])



# purrr::cross(ancestors[[500]])

init <- purrr::compact(
  lapply(ancestors[[1000]], function(.x) {
    c(NA_integer_,
      geonames_alt_names[geonameid == .x, alternateNameId]
    )
}))
init
cp <- cartesian_product(init)
cp[, 1:20]
t(cp)

small_cp <- cp[, 1:20]
colnames(small_cp) <- rep("alternateNameId", ncol(small_cp))

build_query <- function(cp) {
  all_strings <- vapply(seq_len(ncol(cp)), function(.col) {
    strings <- geonames_alt_names[
      data.table::data.table(alternateNameId = cp[, .col]),
      alternate_name,
      on = "alternateNameId"
    ]
    paste0(strings[!is.na(strings)], collapse = " ")
  }, character(1L))

  all_strings[nchar(all_strings) > 0L]
}


test <- build_query(cp)













geonames_alt_names[alternateNameId == as.vector(small_cp)]

cp[, 500L]

geonames_alt_names[data.table::data.table(alternateNameId = small_cp[, 2L]),
                   .(alternateNameId, alternate_name),
                   on = "alternateNameId"]


merge(
  data.table::data.table(alternateNameId = small_cp[, 2L]),
  geonames_alt_names[, .(alternateNameId, alternate_name)],
  by = "alternateNameId"
)

vapply(seq_len(ncol(small_cp)), function(.x) {
  geonames_alt_names[alternateNameId == small_cp[, .x], alternate_name]
}, character(nrow(small_cp)))

small_cp[] <- geonames_alt_names[]

geonames_alt_names$alternateNameId[geonames_alt_names$alternateNameId == small_cp]


names(init) <- seq_along(init)

do.call(expand.grid, init)




.l <- init

.cross <- function(.l) {
  n <- length(.l)
  lengths <- lapply(.l, length)
  # names <- names(.l)
  factors <- cumprod(lengths)
  total_length <- factors[n]
  factors <- c(1, factors[-n])
  out <- replicate(total_length, vector("list", n), simplify = FALSE)
  for (i in seq_along(out)) {
    for (j in seq_len(n)) {
      index <- floor((i - 1) / factors[j]) %% length(.l[[j]]) + 1
      out[[i]][[j]] <- .l[[j]][[index]]
    }
  }
  do.call(rbind, out)
}



cumprod(init)
# do.call(data.table::CJ, init) #, sorted = FALSE)

purrr::cross_df(init)

test <- do.call(data.table::CJ, `names<-`(init, seq_along(init)))

dplyr::bind_cols(lapply(init, data.table::as.data.table))



tester <- geonames_hierarchy

g <- igraph::graph_from_data_frame(tester)

library(furrr)
future::plan(future::multisession)
test <- future_map(seq_len(igraph::vcount(g)), function(.root) {
  as.integer(names(igraph::subcomponent(g, .root, mode = "out")))
}, .progress = TRUE)


test2 <- build_ancestors(geonames_hierarchy)
identical(test, test2)





str(test)
max(purrr::map_int(test, length))
test


build_ancestors <- function(el) {
  g <- igraph::graph_from_data_frame(el)
  geoids <- as.integer(igraph::V(g)$name)

  lapply(as.double(seq_len(igraph::vcount(g)) - 1), function(.root) {
    geoids[.Call(igraph:::C_R_igraph_subcomponent, g, .root, 1) + 1]
  })
}


test3 <- build_ancestors(geonames_hierarchy[1:10000])




geoids <- as.integer(igraph::V(g)$name)

test2 <- lapply(as.double(seq_len(20) - 1), function(.root) {
  geoids[.Call(igraph:::C_R_igraph_subcomponent, g, .root, 1) + 1]
})
# names(test) <- c("p", "c")

merge(
  tester, tester
  ,
  by.x = "child", by.y = "parent", nomatch = 0
)


for (i in seq_len(3)) {
  # names(tester) <- c(i - 1, i)
  tester <- merge(tester, tester,
                  by.x = names(tester)[ncol(tester) - 1L],
                  by.y = names(tester)[ncol(tester)],
                  all.x = TRUE,
                  all = TRUE,
                  allow.cartesian = TRUE)
}

lapply(1:10, function(.x) {

})


tester[tester, on.x = "child", on.y = "parent", nomatch = 0]

lapply(seq_len(nrow(tester)), function(.x) {
  split(tester, by = "parent")
})


[, child := expand.grid(parent, child, stringsAsFactors = FALSE), by = parent]

nodes <- data.table::copy(geonames_all_countries)
data.table::setnames(nodes, "name", "geoname")
# data.table::setnames(nodes, "geonameid", "name")
edges <- geonames_hierarchy[parent %in% nodes$geonameid & child %in% nodes$geonameid]

g <- igraph::graph_from_data_frame(
  d = geonames_hierarchy
  # vertices = nodes[, .(geonameid)]
)





.adj_list <- lapply(.Call(igraph:::C_R_igraph_get_adjlist, g, 1),
                    function(.x) as.integer(.x) + 1L)

.adj_list[1:5]











adj_list <- data.tree::as.igraph.Node(edges)
# tg <- tidygraph::as_tbl_graph(g)

# all_paths <-
igraph::all_simple_paths(g, 1, to = 4, mode = "out")
from <- 1:2
to <- 1:10
res <- .Call(igraph:::C_R_igraph_get_all_simple_paths, g, from - 1, to - 1, 1)

res <- igraph:::get.all.simple.paths.pp(
  .Call(igraph:::C_R_igraph_get_all_simple_paths, g, from - 1, to - 1, 1)
)
lapply(res, function(.x) nodes$geoname[.x])


tweetio_all_simple_paths <- function(g) {
  seq_nodes <- seq_len(igraph::vcount(g))
  sapply(seq_nodes, function(.from) {
    igraph:::get.all.simple.paths.pp(
      .Call(igraph:::C_R_igraph_get_all_simple_paths, g, .from - 1, seq_nodes - 1, 1)
    )
  })
}

res <- tweetio_all_simple_paths(igraph::as.directed(igraph::graph("Diamond")))


.adj_list <- lapply(.Call(igraph:::C_R_igraph_get_adjlist, g, 1),
                    function(.x) as.integer(.x) + 1L)

tree <- data.tree::as.Node(.adj_list)

test <- data.table::data.table(
  parent = seq_along(.adj_list),
  children = .adj_list
)



names(.adj_list) <- igraph::V(g)$name
.adj_list <- purrr::compact(.adj_list)

test <- purrr::imap(.adj_list[1:1000], ~ {
  # parent <- nodes[geonameid == as.integer(.y)]$geoname
  # return(parent)
  # children <- nodes$geoname[.x]
  sprintf("%s, %s", nodes$geoname[.x], nodes[geonameid == as.integer(.y)]$geoname)
})


all_shortest_paths <- igraph::all_shortest_paths(g, from = 1)

max_order <- max(igraph::neighborhood.size(g, order = igraph::vcount(g), mode = "out"))
all_egos <- igraph::ego(g, order = max_order)



geoname_attr <- igraph::V(g)$geoname
adj_list <- lapply(.adj_list, function(.x) geoname_attr[.x])
max(purrr::map_int(.adj_list, length))


### testing ==============================================================================
test <- data.table::copy(geonames_all_countries)[
  # , .(geonameid, name, asciiname, alternatenames, latitude, longitude, population)
  ][, alternate_name := mapply(function(.name, .asciiname, .alternatenames) {
    init <- unique(c(.name, .asciiname, unlist(.alternatenames, use.names = FALSE)))
    if (length(init) == 1L && is.na(init)) init else init[!is.na(init)]
  },
  name, asciiname, alternatenames,
  SIMPLIFY = FALSE, USE.NAMES = FALSE)
  ][, name := NULL
    ][, asciiname := NULL
      ][, alternatenames := NULL
        ]

test2 <- data.table::setDT(
  tidyr::unnest(
    tidyr::unnest(test, cols = alternate_name),
    cols = cc2
  )
)


test3 <- merge(
  test2,
  geonames_country_info[, .(country, iso)],
  by.x = "country_code",
  by.y = "iso",
  all = TRUE
)

test3[!is.na(country_code)]


tidyr::expand(
  test2[admin_lvl == 2L][1:20]
)


alt_names_full <- merge(
  test2,
  geonames_alt_names[, .(alternateNameId, geonameid, alternate_name)],
  by = c("geonameid", "alternate_name"),
  nomatch = 0
  )[,  .(geonameid, alternate_name, latitude, longitude, population)
    ][, alternate_name := stringi::stri_trans_tolower(alternate_name)
      ]

geo_db <- unique(
  alt_names_full[,  .(geonameid, alternate_name, latitude, longitude, population)]
)

# geo_db[, score := nchar(alternate_name) * population * data.table::fifelse(isPreferredName, 2L, 1L)
#                ]
# alt_names_full[
#   geonameid != 6295630L
# ][score == max(score), .(geonameid, alternate_name, latitude, longitude, population, score)]
t <- data.table::data.table(
  geonameid = geo_db$geonameid,
  name = geo_db$alternate_name,
  lat = geo_db$latitude,
  lon = geo_db$longitude,
  pop = geo_db$population,
  string_dist = as.vector(adist("monterey, ca", geo_db$alternate_name))
)[order(string_dist)]
t


# geo_db[which.max(



adist





# [parent %in% geonames_all_countries$geonameid &
#     child %in% geonames_all_countries$geonameid
#   ][order(parent, child)]
# geonames_hierarchy_edges <- t(as.matrix(geonames_hierarchy))


# [, alternatenames := stringi::stri_split_fixed(alternatenames, ",")
# ]

# merge(
#   geo_names[1:10],
#   hierarchy,
#   by.x = "geonameid",
#   by.y = "parent"
# )

`%||%` <- function(lhs, rhs) {
  if (length(lhs)) lhs else rhs
}

geo_infer <- function(location = "ordino") {
  db <- geo_names[1:10]

  data.table::data.table(
    # geonameid = db$geonameid,
    res = mapply(function(alt_name, pop) min(adist(alt_name, location)), # / as.double(pop),
                 c("افریقا", "Africa")
                 ,
                 1:2)
    #] %||% NA_character_,
    # double(1L))
  )
}

which.min(vapply(`names<-`(geo_names$alternatenames[1:10], geo_names$geonameid[1:10]),
                 function(.x) min(`row.names<-`(adist(.x, "Ordino"), .x)),
                 double(1L)), na.rm = TRUE)

adist(c("Monterey", "Monterrey"), c("Monterey", "Monterrey, CA"))

geo_names[name == "Monterrey"][order(population, decreasing = TRUE)]

test


# )
[, alternatenames := stringi::stri_split_fixed(alternatenames, ",")]
filtered_feature_classes <- geo_names[
  data.table::`%chin%`(geo_names$feature_class, target_feature_classes),
]

has_pop <- geo_names[geo_names$population > 0L, ]

unique(has_pop$feature_class)

geo_names$alternatenames



geo_names[!is.na(V16)]
geo_names$V4[1]
