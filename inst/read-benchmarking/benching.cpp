
// [[Rcpp::depends(rapidjsonr)]]
// [[Rcpp::depends(RcppProgress)]]

// [[Rcpp::plugins(cpp17)]]
// [[Rcpp::plugins(openmp)]]
#include <rapidjson/document.h>

#define STRICT_R_HEADERS
#include <Rcpp.h>


#include "../../src/gzstream.h"
#include "../include/tweetio/progressbar.hpp"

#include <algorithm>
#include <numeric>
#include <cstring>
#include <iostream>

#include <fstream>

// for mmap:
// #include <fcntl.h>
// #include <sys/mman.h>
// #include <sys/stat.h>

// #include <boost/iostreams/device/mapped_file.hpp>  // for mmap

// #include <algorithm>  // for std::find
// #include <iostream>   // for std::cout
// #include <cstring>





// #include <fstream>
// #include <iostream>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>


#ifdef _OPENMP
#include <omp.h>
#else
#warning "OpenMP was not detected."
#endif




using namespace Rcpp;

// [[Rcpp::export]]
int count_lines_1(const std::string& file_path) {
  igzstream in_file;
  in_file.open(file_path.c_str());
  
//   static const std::size_t BUFFER_SIZE = 10^9;
  
  std::string line_string;
//   line_string.reserve(BUFFER_SIZE);

  int n_lines = 0;
  while (std::getline(in_file, line_string)) {
    ++n_lines;
  }

  return n_lines;
}


// [[Rcpp::export]]
int count_lines_1_multi(const std::vector<std::string>& file_paths) {
  int n_total_lines = 0;
  const auto n_files = file_paths.size();
  
  #pragma omp parallel for shared(file_paths) reduction(+: n_total_lines)
  for (std::size_t i = 0; i < n_files; ++i) {
    // n_lines[i] = count_lines(file_path[i]);
    n_total_lines += count_lines_1(file_paths[i]);
  }
  
  return n_total_lines;
}





// [[Rcpp::export]]
std::vector<std::string> read_lines_1(const std::string& file_path) {
  igzstream in_file;
  in_file.open(file_path.c_str());
  
  std::vector<std::string> out;
  
  std::string line_string;
  while (std::getline(in_file, line_string)) {
    out.push_back(line_string);  
  }
  
  in_file.close();
  
  return out;
}


// [[Rcpp::export]]
std::vector<std::string> read_lines_multi_1(const std::vector<std::string>& file_paths) {
  int n_total_lines = 0;
  const int n_files = file_paths.size();
  std::vector<int> n_lines(n_files + 1, 0);
  
  Rcpp::Rcout << "- preprocessing..." << std::endl;
  #pragma omp parallel for shared(file_paths) reduction(+: n_total_lines)
  for (int i = 0; i < n_files ; ++i) {
    n_lines[i + 1] = count_lines_1(file_paths[i]);
    n_total_lines += n_lines[i + 1];
  }
  Rcpp::Rcout << "- # of lines found: " << n_total_lines << std::endl;
  
  Rcpp::Rcout << "- calculating memory layout..." << std::endl;
  std::vector<int> offsets(n_files + 1);
  std::partial_sum(n_lines.begin(), n_lines.end(), offsets.begin());
  
  Rcpp::Rcout << "- allocating memory..." << std::endl;
  std::vector<std::string> out(n_total_lines);

  Rcpp::Rcout << "- starting read..." << std::endl;
  tweetio::Progress progress(n_total_lines, true);

  #pragma omp parallel for
  for (int i = 0; i < n_files; ++i) {
    igzstream in_file;
    in_file.open(file_paths[i].c_str());
    
    std::string line_string;
    // Rcpp::String line_string;
    for (int j = offsets[i]; j < offsets[i + 1]; ++j) {
        progress.increment();

        std::getline(in_file, line_string);
        // out[j] = line_string;
        
        // progress.increment();
        rapidjson::Document parsed_json;
        parsed_json.Parse(line_string.c_str());
    }

    in_file.close();
  }


//   for (int i = 0; i < n_total_lines; ++i) {
//       progress.increment();
//       rapidjson::Document parsed_json;
//       parsed_json.Parse(out[i].c_str());
//   }
  out.clear();
  return out;
}
  

// [[Rcpp::export]]
std::vector<std::string> test_empty() {
  std::vector<std::string> out;
  return out;
}
  


/*** R
if (FALSE) {
  tweet_multi_file <- dir("~/Insync/brendan.knapp@nps.edu/OneDrive Biz/tweet-week/open/datasets/pulse/",
                          pattern = "jsonl\\.gz$",
                          full.names = TRUE)
  
  test_file <- tweet_multi_file[[1L]]
  # target_test_file <- length(readLines(test_file))
  
  count_lines_1(test_file)
  count_lines_1_multi(tweet_multi_file[1:8])
  
  read_file_res_1 <- read_lines_1(test_file)
  read_file_res_2 <- readLines("inst/example-data/elasticsearch-dump-example.jsonl")
  
  target_multi_test <- unlist(lapply(tweet_multi_file[1:3], readLines), use.names = FALSE)
  read_lines_multi_1_test <- read_lines_multi_1(tweet_multi_file)
  # identical(target_multi_test, read_lines_multi_1_test)
  
  
  
  res <- bench::mark(
    test = read_lines_multi_1_test <- read_lines_multi_1(tweet_multi_file)
  )
  res
  
}


*/