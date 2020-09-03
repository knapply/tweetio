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
                            simdjson::dom::parser& parser) {
  if (*(std::cbegin(content)) == '[') {
    if (auto [test, error] =
            parser.parse(content).at_pointer("/0/_source/doc/user/id_str");
        !error) {
      return Schema::_source__doc;
    } else if (auto [test, error] =
                   parser.parse(content).at_pointer("/0/user/id_str");
               !error) {
      return Schema::api_array;
    }
  } else if (*(std::cbegin(content)) == '{') {
    if (auto [test, error] =
            parser.parse(content).at_pointer("/statuses/0/user/id_str");
        !error) {
      return Schema::statuses;
    }
  }

  return Schema::unknown;
}


inline Schema detect_multi_schema(const std::string_view line,
                                  simdjson::dom::parser& parser) {
  if (auto [test, error] = parser.parse(line); !error) {
    if (auto [t, error] =
            test.at_pointer("/delete/status/id_str").get<std::string_view>();
        !error) {
      return Schema::api_stream;
    } else if (auto [t, error] =
                   test.at_pointer("/user/id_str").get<std::string_view>();
               !error) {
      return Schema::api_stream;
    } else if (auto [t, error] =
                   test.at_pointer("/doc/user/id_str").get<std::string_view>();
               !error) {
      return Schema::doc;
    }

  } else if (auto [test, error] = parser.parse(line)
                                      .at_pointer("/delete/status/id_str")
                                      .get<std::string_view>();
             !error) {
    return Schema::api_stream;
  } else if (auto [test, error] = parser.parse(line)
                                      .at_pointer("/id_str")
                                      .get<std::string_view>();
             !error) {
    return Schema::api_stream;
  }

  return Schema::unknown;
}


// [[Rcpp::export(.read_tweets)]]
SEXP read_tweets(const std::vector<std::string>& file_paths,
                 const bool                      verbose,
                 double                          batch_size,
                 const double                    reserve) {
  using namespace tweetio;

  if (batch_size < simdjson::dom::DEFAULT_BATCH_SIZE) {
    batch_size = simdjson::dom::DEFAULT_BATCH_SIZE;
  }

  soa::SoA proto_df(columns::base);

  soa::SoA metadata(columns::all_qcr);

  proto_df.reserve(reserve);

  const auto     n_files = std::size(file_paths);
  ETAProgressBar eta_pb;
  Progress       progress(n_files, verbose, eta_pb);

  simdjson::dom::parser parser;

  for (auto&& file : file_paths) {
    if (!Progress::check_abort()) {

      if (auto contents = tweetio::read_file(file);
          contents.has_value() && contents->size() > 0) {

        if (auto schema = detect_schema(*contents, parser);
            schema != Schema::unknown) {

          auto [parsed, _] = parser.parse(*contents);

          switch (schema) {
            case Schema::_source__doc: {
              for (auto&& status : parsed.get<simdjson::dom::array>()) {
                if (status.at_pointer("/_source/doc/user/id_str")
                        .is<std::string_view>()) {
                  proto_df.bind_row(status.at_pointer("/_source/doc").first);
                  metadata.bind_row(status);
                }
              }
              break;
            }

            case Schema::api_array: {
              for (auto&& status : parsed.get<simdjson::dom::array>()) {
                if (status.at_pointer("/user/id_str").is<std::string_view>()) {
                  proto_df.bind_row(status);
                  metadata.bind_row(status);
                }
              }
              break;
            }


            case Schema::statuses: {
              for (auto&& status :
                   parsed.at_pointer("/statuses").get<simdjson::dom::array>()) {
                if (status.at_pointer("/user/id_str").is<std::string_view>()) {
                  proto_df.bind_row(status);
                  metadata.bind_row(status);
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
                  if (auto&& [doc, error] = parsed.at_pointer("/doc");
                      !error &&
                      doc.at_pointer("/user/id_str").is<std::string_view>()) {
                    {
                      proto_df.bind_row(doc);
                      metadata.bind_row(parsed);
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
                      proto_df.bind_row(parsed);
                      metadata.bind_row(parsed);
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

  using Rcpp::_;
  return Rcpp::List::create(_["tweets"]   = proto_df.as_list(),
                            _["metadata"] = metadata.as_list());
}
