// #include <tweetio.hpp>
// #include <tweetio/third-party/eta_progress_bar.hpp>


// // [[ffRcpp::export(.read_telegram)]]
// SEXP read_telegram(const std::vector<std::string>& file_paths,
//                    const bool                      verbose    = true,
//                    double                          batch_size = 1000000) {
//   using namespace tweetio;

//   if (batch_size < simdjson::dom::DEFAULT_BATCH_SIZE) {
//     batch_size = simdjson::dom::DEFAULT_BATCH_SIZE;
//   }

//   const auto n_files = std::size(file_paths);

//   soa::SoA statuses(columns::telegram::base);
//   statuses.reserve(n_files * 100'000);

//   soa::SoA metadata(columns::qcr::qcr);
//   metadata.reserve(n_files * 100'000);


//   ETAProgressBar eta_pb;
//   Progress       progress(n_files, verbose, eta_pb);

//   simdjson::dom::parser parser;

//   for (auto&& file : file_paths) {
//     if (!Progress::check_abort()) {

//       if (auto contents = tweetio::read_file(file);
//           contents.has_value() && contents->size() > 0) {
//         if (auto lines = tweetio::split<'\n'>(*contents);
//             std::size(lines) > 0) {

//           for (auto&& l : lines) {
//             if (auto [parsed, error] = parser.parse(l); !error) {
//               if (auto [type, error] =
//                       parsed.at_pointer("/type").get<std::string_view>();
//                   !error && type == "telegram_message") {
//                 if (auto [message, error] = parsed.at_pointer("/doc"); !error) {
//                   {
//                     statuses.bind_row(message);
//                     metadata.bind_row(parsed);
//                   }
//                 }
//               }
//             }
//           }
//         }
//       }
//     }
//     progress.increment();
//   }

//   using Rcpp::_;
//   return Rcpp::List::create(_["messages"] = statuses.as_list(),
//                             _["metadata"] = metadata.as_list());
// }
