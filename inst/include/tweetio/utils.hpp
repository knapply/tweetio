#ifndef TWEETIO__UTILS_HPP
#define TWEETIO__UTILS_HPP

#include "common.hpp"

#include <filesystem>
namespace fs = std::filesystem;

namespace tweetio {


template <typename stream_T>
inline constexpr auto n_lines(const std::string_view& file_path) -> std::size_t {
  stream_T in_file;
  in_file.open(std::string(file_path).c_str());

  auto out = std::size_t(0ULL);
  while (std::getline(in_file, std::string())) {
    out++;
  }

  in_file.close();

  return out;
}


template <typename stream_T>
inline auto read_lines(const std::string_view& file_path) -> std::vector<simdjson::padded_string> {
  stream_T in_file;
  in_file.open(std::string(file_path).c_str());

  constexpr std::size_t n   = 100'000ULL;
  auto                  out = std::vector<simdjson::padded_string>();
  out.reserve(n);

  auto line = std::string();
  while (std::getline(in_file, line)) {
    out.emplace_back(std::move(line));
  }

  in_file.close();

  return out;
}


inline auto is_gz_file(const std::string_view& file_path) -> bool {
  return fs::path(file_path).extension() == ".gz";
}


// template <typename stream_T>
// inline auto detect_file_type(const std::string& file_path) -> File_Type {
//   stream_T in_file;
//   in_file.open(file_path.c_str());

//   auto first_char = in_file.peek();
//   if (first_char == '[') {
//     return File_Type::array_nested_doc;
//   }
//   if (first_char == '{') {
//     first_char             = in_file.get();
//     const char second_char = in_file.peek();
//     if (second_char != '"') {
//       Rcpp::stop("Unknown file schema.");
//     }
//   }

//   // can't use in_file.seekg() on igzstream, so reset if character consumed
//   in_file.close();
//   in_file.open(file_path.c_str());

//   std::string           line_string;
//   simdjson::dom::parser parser;

//   bool parse_successful(false);
//   while (std::getline(in_file, line_string)) {
//     if (!line_string.empty()) {
//       if (auto [parsed, error] = parser.parse(line_string); !error) {
//         if (auto [id, error] = parsed.at("id");
//             !error && id.type() == simdjson::dom::element_type::INT64) {
//           in_file.close();
//           return File_Type::twitter_api_stream;
//         }

//         if (auto [id, error] = parsed.at("delete/status/id");
//             !error && id.type() == simdjson::dom::element_type::INT64) {
//           in_file.close();
//           return File_Type::twitter_api_stream;
//         }

//         if (auto [id, error] = parsed.at("doc/id");
//             !error && id.type() == simdjson::dom::element_type::INT64) {
//           in_file.close();
//           return File_Type::nested_doc;
//         }

//         if (auto [id, error] = parsed.at("doc/_source/id");
//             !error && id.type() == simdjson::dom::element_type::INT64) {
//           in_file.close();
//           return File_Type::array_nested_doc;
//         }
//         parse_successful = true;
//       }
//     }
//   }

//   if (!parse_successful) {
//     in_file.close();
//     Rcpp::stop("File does not contain any valid JSON.");
//   }
//   in_file.close();
//   Rcpp::stop("Unknown file schema.");
// }


} // namespace tweetio


#endif
