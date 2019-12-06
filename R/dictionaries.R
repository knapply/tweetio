# // Copyright (C) 2019 Brendan Knapp
# // This file is part of tweetio.
# // 
# // This program is free software: you can redistribute it and/or modify
# // it under the terms of the GNU General Public License as published by
# // the Free Software Foundation, either version 3 of the License, or
# // (at your option) any later version.
# // 
# // This program is distributed in the hope that it will be useful,
# // but WITHOUT ANY WARRANTY; without even the implied warranty of
# // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# // GNU General Public License for more details.
# // 
# // You should have received a copy of the GNU General Public License
# // along with this program.  If not, see <https://www.gnu.org/licenses/>.

build_dict <- function(dict = c("PMESSI", "ASCOPE"), lang = c("en")) {
  dict <- match.arg(dict, c("PMESSI", "ASCOPE"))
  lang <- match.arg(lang, c("en"))
  
  target_files <- dir(
    system.file(sprintf("dictionaries/%s/%s", dict, lang),
                package = "tweetio"),
    full.names = TRUE
  )

  out <- lapply(target_files, readLines, encoding = "UTF-8")
  names(out) <- sub("([^.]+)\\.[[:alnum:]]+$", "\\1", basename(target_files))
  
  out
}

