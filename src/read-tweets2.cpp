#include <tweetio.hpp>
#include <tweetio/third-party/eta_progress_bar.hpp>


enum class Schema {
  _source__doc,
  api_array,
  statuses,
  unknown,
  api_stream,
  doc,
};


inline Schema detect_schema(const std::string_view content,
                            simdjson::dom::parser& parser) noexcept {
  if (*(std::cbegin(content)) == '[') {
    if (parser.parse(content)
            .at_pointer("/0/_source/doc/user/id_str")
            .is<std::string_view>()) {
      return Schema::_source__doc;
    } else if (parser.parse(content)
                   .at_pointer("/0/user/id_str")
                   .is<std::string_view>()) {
      return Schema::api_array;
    }
  } else if (*(std::cbegin(content)) == '{') {
    if (parser.parse(content)
            .at_pointer("/statuses/0/user/id_str")
            .is<std::string_view>()) {
      return Schema::statuses;
    }
  }

  return Schema::unknown;
}


inline Schema detect_multi_schema(const std::string_view line,
                                  simdjson::dom::parser& parser) noexcept {
  if (auto [test, error] = parser.parse(line); !error) {
    if (test.at_pointer("/delete/status/id_str").is<std::string_view>()) {
      return Schema::api_stream;
    } else if (test.at_pointer("/user/id_str").is<std::string_view>()) {
      return Schema::api_stream;
    } else if (test.at_pointer("/doc/user/id_str").is<std::string_view>()) {
      return Schema::doc;
    }

  } else if (parser.parse(line)
                 .at_pointer("/delete/status/id_str")
                 .is<std::string_view>()) {
    return Schema::api_stream;
  } else if (parser.parse(line).at_pointer("/id_str").is<std::string_view>()) {
    return Schema::api_stream;
  }

  return Schema::unknown;
}


SEXP read_auto_schema(const std::vector<std::string>& file_paths,
                      const bool                      verbose) {
  using namespace tweetio;

  const auto n_files = std::size(file_paths);
  const auto reserve = n_files * 100'000;

  soa::SoA statuses(columns::twitter::base);
  statuses.reserve(reserve);

  ETAProgressBar eta_pb;
  Progress       progress(n_files, verbose, eta_pb);

  simdjson::dom::parser parser;

  for (auto&& file : file_paths) {
    if (!Progress::check_abort()) {

      if (auto contents = tweetio::read_file(file);
          contents.has_value() && contents->size() > 0) {

        if (auto schema = detect_schema(*contents, parser);
            schema != Schema::unknown) {

          auto parsed = parser.parse(*contents).first;

          switch (schema) {
            case Schema::_source__doc: {
              for (auto&& status : parsed.get<simdjson::dom::array>().first) {
                if (status.at_pointer("/_source/doc/user/id_str")
                        .is<std::string_view>()) {
                  statuses.bind_row(status.at_pointer("/_source/doc").first);
                }
              }
              break;
            }

            case Schema::api_array: {
              for (auto&& status : parsed.get<simdjson::dom::array>().first) {
                if (status.at_pointer("/user/id_str").is<std::string_view>()) {
                  statuses.bind_row(status);
                }
              }
              break;
            }

            case Schema::statuses: {
              for (auto&& status : parsed.at_pointer("/statuses")
                                       .get<simdjson::dom::array>()
                                       .first) {
                if (status.at_pointer("/user/id_str").is<std::string_view>()) {
                  statuses.bind_row(status);
                }
              }
            }

            default:
              break;
          }


        } else if (auto lines = tweetio::split<'\n'>(*contents);
                   std::size(lines) > 0) {
          const auto first_non_empty_line =
              std::find_if(std::cbegin(lines), std::cend(lines),
                           [](auto x) { return !x.empty(); });

          switch (detect_multi_schema(*first_non_empty_line, parser)) {
            case Schema::doc: {
              for (auto&& l : lines) {
                if (auto [parsed, error] = parser.parse(l); !error) {
                  if (auto&& [doc, _] = parsed.at_pointer("/doc");
                      !error &&
                      doc.at_pointer("/user/id_str").is<std::string_view>()) {
                    {
                      statuses.bind_row(doc);
                    }
                  }
                }
              }
              break;
            }

            case Schema::api_stream: {
              for (auto&& l : lines) {
                if (auto [parsed, error] = parser.parse(l); !error) {
                  if (auto [t, e] = parsed.at_pointer("/id_str");
                      !e && t.is<std::string_view>()) {
                    {
                      statuses.bind_row(parsed);
                    }
                  }
                }
              }
              break;
            }

            default:
              break;
          }
        }
      }
    }
    progress.increment();
  }

  return statuses.as_list();
}


SEXP read_qcr_schema(const std::vector<std::string>& file_paths,
                     const bool                      verbose) {
  using namespace tweetio;

  const auto            n_files    = std::size(file_paths);
  constexpr auto        batch_size = simdjson::dom::DEFAULT_BATCH_SIZE * 1.5;
  constexpr std::size_t reserve_per_file = 100'000;
  const auto            reserve          = n_files * reserve_per_file;

  //   soa::SoA statuses(columns::twitter::base);
  //   statuses.reserve(reserve);
  //   soa::SoA metadata(columns::qcr::qcr);
  //   metadata.reserve(reserve);

  ETAProgressBar eta_pb;
  Progress       progress(n_files, verbose, eta_pb);

  simdjson::dom::parser parser;

  soa::SoA out_statuses(columns::twitter::base);
  out_statuses.reserve(reserve);
  soa::SoA out_metadata(columns::qcr::qcr);
  out_metadata.reserve(reserve);

  for (auto&& f : file_paths) {
    if (!Progress::check_abort()) {

      //   if (auto contents = tweetio::read_file(f);
      if (auto contents = tweetio::read_file(f);
          contents.has_value() && contents->size() > 0) {

        for (auto&& parsed : parser.parse_many(*contents, batch_size).first) {
          if (auto [doc, error] = parsed.at_pointer("/doc");
              !error && doc.at_pointer("/id_str").is<std::string_view>()) {
            out_statuses.bind_row(doc);
            out_metadata.bind_row(parsed.first);
          }
        }
      }
    }
    progress.increment();
  }

  return soa::as_list(
      soa::bind(std::move(out_statuses), std::move(out_metadata)));
}


// [[Rcpp::export(.read_tweets)]]
SEXP read_tweets(const std::vector<std::string>& file_paths,
                 const int                       schema,
                 const bool                      verbose) {

  switch (schema) {
    case 0: // auto
      return read_auto_schema(file_paths, verbose);

    case 1: /* QCR */
      return read_qcr_schema(file_paths, verbose);


    default:
      return R_NilValue;
  }

  return R_NilValue;
}


// [[Rcpp::export(.detect_belarus)]]
SEXP detect_belarus(const Rcpp::CharacterVector x) {
  return Rcpp::LogicalVector(std::cbegin(x), std::cend(x), [](auto val) {
    return tweetio::rgx::detect<tweetio::rgx::countries::belarus>(
        std::string_view(val));
  });
}
