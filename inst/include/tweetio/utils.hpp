#ifndef TWEETIO__UTILS_HPP
#define TWEETIO__UTILS_HPP

#include "common.hpp"

#include <zlib.h>


#ifdef __unix__
#  include <fcntl.h>
#  include <unistd.h>
#endif

#include "third-party/LZ4/lz4frame.h"


namespace tweetio {


inline std::optional<std::string> read_lz4(const std::string& file_path) {
  //   Rcpp::Rcout << 'a' << std::endl;

  if (std::size_t file_size = fs::file_size(file_path);
      file_size > 10 && file_size < std::numeric_limits<int>::max()) {
    // Rcpp::Rcout << 'b' << std::endl;

    // std::vector<char> in_buff(file_size);
    // char* in_buff = (char*)std::malloc(file_size);

    if (std::FILE* fp = std::fopen(file_path.c_str(), "rb"); fp != nullptr) {
      //   Rcpp::Rcout << 'c' << std::endl;
      auto              src_size = file_size + 1;
      std::vector<char> src(src_size);

      if (std::size_t bytes_read = std::fread(src.data(), 1, file_size, fp);
          std::fclose(fp) == 0 && bytes_read == file_size) {
        // Rcpp::Rcout << 'd' << std::endl;

        LZ4F_dctx* dctx;
        {
          size_t const dctxStatus =
              LZ4F_createDecompressionContext(&dctx, LZ4F_VERSION);
          if (LZ4F_isError(dctxStatus)) {
            Rcpp::stop("LZ4F_dctx creation error: %s\n",
                       LZ4F_getErrorName(dctxStatus));
          }
        }

        // constexpr std::size_t max_decomp_size =
        // std::numeric_limits<int>::max();
        auto              dst_size = file_size * 10;
        std::vector<char> dst(dst_size);

        if (const auto test = LZ4F_decompress(dctx, dst.data(), &dst_size,
                                              src.data(), &src_size, nullptr);
            !LZ4F_isError(test)) {
          //   Rcpp::Rcout << 'e' << std::endl;
          return std::string(std::string_view(dst.data(), dst_size));
        }
      }
    }
  }
  return std::nullopt;
}


inline std::optional<std::string> read_gz(const std::string& file_path) {
  if (const std::size_t file_size = fs::file_size(file_path);
      file_size > 10 && file_size < std::numeric_limits<ssize_t>::max()) {
    if (gzFile in_file = gzopen(file_path.c_str(), "rb"); in_file != nullptr) {
      constexpr std::size_t         buffer_size = 1'000'000;
      std::array<char, buffer_size> buffer;

      std::string out;
      out.reserve(fs::file_size(file_path) * 8);

      while (gzgets(in_file, buffer.data(), buffer_size) != nullptr) {
        out.append(buffer.data());
      }

      if (gzclose(in_file) == Z_OK) {
        return out;
      }
    }
  }
  return std::nullopt;
}


inline std::optional<std::string> read_file(const std::string& file_path) {
  const auto ext = fs::path(file_path).extension();

  if (ext == ".lz4") {
    return read_lz4(file_path);

  } else if (ext == ".gz") {
    return read_gz(file_path);

  } else if (const std::size_t file_size = fs::file_size(file_path);
             file_size > 10 &&
             file_size < std::numeric_limits<ssize_t>::max()) {
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

  return std::nullopt;
}


template <char delim>
inline std::vector<std::string_view> split(const std::string_view s) {
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
