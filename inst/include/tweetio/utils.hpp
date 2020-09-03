#ifndef TWEETIO__UTILS_HPP
#define TWEETIO__UTILS_HPP

#include "common.hpp"

#include <zlib.h>

#ifdef __unix__
#include <fcntl.h>
#include <unistd.h>
#endif

namespace tweetio {

inline std::optional<std::string> read_file(const std::string& file_path) {
  if (const std::size_t file_size = fs::file_size(file_path);
      file_size > 10 && file_size < std::numeric_limits<ssize_t>::max()) {

    if (fs::path(file_path).extension() == ".gz") {
      if (gzFile in_file = gzopen(file_path.c_str(), "rb");
          in_file != nullptr) {
        constexpr std::size_t buffer_size = 1024 * 3;
        char                  buffer[buffer_size];

        std::string out;
        out.reserve(fs::file_size(file_path) * 4);
        while (gzgets(in_file, buffer, buffer_size) != nullptr) {
          out.append(std::string(buffer));
        }

        if (gzclose(in_file) == Z_OK) {
          return out;
        }
      }

    } else {
      std::string out;
      out.resize(file_size);
#ifdef __unix__
      if (auto f = open(file_path.c_str(), O_RDONLY); f > 0) {
        if (read(f, out.data(), file_size) == static_cast<ssize_t>(file_size)) {
#else
      if (std::FILE* fp = std::fopen(file_path.c_str(), "rb"); fp != nullptr) {
        if (auto bytes_read = std::fread(out.data(), 1, file_size, fp);
            std::fclose(fp) == 0 && bytes_read == file_size) {
#endif
          return out;
        }
      }
    }
  }

  return std::nullopt;
}

enum class File_Type {
  unknown,
  twitter_api_stream,
  nested_doc,
  nested_array,
  bad_parse,
};

inline File_Type detect_file_type(const std::string_view contents,
                                  simdjson::dom::parser& parser) {
  char first_char = *std::cbegin(contents);

  if (first_char == '[') {
    return File_Type::nested_array;
  }

  const auto* left = std::cbegin(contents);
  for (const auto* right =
           std::char_traits<char>::find(left, std::size(contents), '\n');
       static_cast<std::size_t>(right - std::cbegin(contents)) <
       std::size(contents);
       right = std::char_traits<char>::find(left, std::cend(contents) - left,
                                            '\n')) {
    if (auto line = std::string_view(left, right - left); !line.empty()) {
      if (auto [test_parse, error] = parser.parse(line); !error) {
        if (auto [test, err] = test_parse.at_pointer("/id_str");
            !err && test.is<std::string_view>()) {
          return File_Type::twitter_api_stream;
        }

        if (auto [test, err] = test_parse.at_pointer("/delete/status/id_str");
            !err && test.is<std::string_view>()) {
          return File_Type::twitter_api_stream;
        }

        if (auto [test, err] = test_parse.at_pointer("/doc");
            !err && test.is<simdjson::dom::object>()) {
          return File_Type::nested_doc;

        } else {
          break;
        }
      } else {
        return File_Type::bad_parse;
      }
    }

    left = right + 1;
  }
  return File_Type::unknown;
}

template <char delim>
inline std::vector<std::string_view> split(const std::string_view s) noexcept {
  std::vector<std::string_view> out;
  const char*                   left = std::cbegin(s);

  for (const char* right =
           std::char_traits<char>::find(left, std::size(s), delim);
       static_cast<std::size_t>(right - std::cbegin(s)) < std::size(s);
       right = std::char_traits<char>::find(left, std::cend(s) - left, delim)) {
    out.emplace_back(left, right - left);
    left = right + 1;
  }

  out.emplace_back(left, std::cend(s) - left);

  return out;
}

} // namespace tweetio

#endif
