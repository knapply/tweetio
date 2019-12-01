raw_lines <- readLines("inst/example-data/api-stream.json.gz")

clean_lines <- raw_lines[
  vapply(raw_lines, function(.x) {
    nchar(.x) > 0L && 
      grepl('^\\{"created_at"', .x) && 
      grepl('bounding_box', .x) &&
      jsonify::validate_json(.x)
    }, logical(1L))
  ]


dest_path <- "inst/example-data/api-stream-small.json"
writeLines(clean_lines, dest_path)
