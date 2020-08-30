#include <tweetio.hpp>

#include <tweetio/third-party/eta_progress_bar.hpp>


// [[Rcpp::export(.read_tweets)]]
SEXP read_tweets(const std::vector<std::string>& file_paths,
                 const double                    reserve,
                 const bool                      verbose,
                 double                          batch_size,
                 const std::string               doc_pointer = "") {
  using namespace tweetio;

  if (batch_size < simdjson::dom::DEFAULT_BATCH_SIZE) {
    batch_size = simdjson::dom::DEFAULT_BATCH_SIZE;
  }

  soa::SoA proto_df(columns::base);

  soa::SoA metadata(columns::all_qcr);

  proto_df.reserve(reserve);

  const auto n_files = std::size(file_paths);


  ETAProgressBar eta_pb;
  Progress       progress(n_files, verbose, eta_pb);

  simdjson::dom::parser parser;

  //   omp_set_num_threads(n_threads);
  // #pragma omp parallel for private(parser)
  for (std::size_t i = 0; i < n_files; ++i) {
    if (!Progress::check_abort()) {
      for (auto&& [x, error] : parser.load_many(file_paths[i], batch_size)) {
        if (error) {
          Rcpp::warning(simdjson::error_message(error));
          continue;
        } else if (auto&& [doc, error] = x.at_pointer(doc_pointer);
                   !error && doc.at_pointer("/user/id").is<int64_t>()) {
          // #pragma omp critical                //
          {                         //
            proto_df.bind_row(doc); //
            metadata.bind_row(x);   //
          }                         //
        }
      }
      progress.increment();
    }
  }

  using Rcpp::_;
  return Rcpp::List::create(_["tweets"]   = proto_df.as_list(),
                            _["metadata"] = metadata.as_list());
}
