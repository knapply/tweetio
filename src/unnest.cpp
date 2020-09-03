#include <Rcpp.h>

template <int RTYPE>
SEXP unnest_entities2(const Rcpp::Vector<RTYPE>&   tracker,
                      const Rcpp::List&            source,
                      const Rcpp::List&            target,
                      const Rcpp::CharacterVector& col_names) {
  R_xlen_t out_n = 0;
  for (Rcpp::CharacterVector target_i : target) {
    for (Rcpp::String val : target_i) {
      if (val != NA_STRING) {
        out_n++;
      }
    }
  }

  Rcpp::CharacterVector source2(out_n);
  Rcpp::CharacterVector target2(out_n);
  Rcpp::Vector<RTYPE>   tracker2(out_n);
  tracker2.attr("class") = tracker.attr("class");
  tracker2.attr("tz")    = tracker.attr("tz");

  R_xlen_t k = 0;
  for (R_xlen_t i = 0; i < std::size(tracker); ++i) {
    const Rcpp::CharacterVector source_i = source[i];
    const Rcpp::CharacterVector target_i = target[i];

    for (R_xlen_t j = 0; j < target_i.size(); ++j) {
      if (target_i[j].get() != NA_STRING) {
        source2[k]  = source_i[j];
        target2[k]  = target_i[j];
        tracker2[k] = tracker[i];
        k++;
      }
    }
  }

  auto out          = Rcpp::List::create(source2, target2, tracker2);
  out.attr("names") = col_names;
  return out;
}


// [[Rcpp::export]]
SEXP unnest_entities2_impl(const SEXP&                  tracker,
                           const Rcpp::List&            source,
                           const Rcpp::List&            target,
                           const Rcpp::CharacterVector& col_names) {
  switch (TYPEOF(tracker)) {
    case STRSXP:
      return unnest_entities2<STRSXP>(tracker, source, target, col_names);
    case REALSXP:
      return unnest_entities2<REALSXP>(tracker, source, target, col_names);
  }
  return R_NilValue;
}


// [[Rcpp::export(.unnest_edges)]]
SEXP unnest_edges(const Rcpp::CharacterVector&               user_id,
                  const Rcpp::ListOf<Rcpp::CharacterVector>& target,
                  const Rcpp::CharacterVector&               status_id,
                  const Rcpp::NumericVector&                 created_at) {
  R_xlen_t out_n = 0;
  for (Rcpp::CharacterVector outer : target) {
    for (Rcpp::String val : outer) {
      if (val != NA_STRING) {
        out_n++;
      }
    }
  }

  Rcpp::CharacterVector out_user_id(out_n);
  Rcpp::CharacterVector out_status_id(out_n);
  Rcpp::NumericVector   out_created_at(out_n);
  out_created_at.attr("class") = created_at.attr("class");
  out_created_at.attr("tz")    = created_at.attr("tz");
  Rcpp::CharacterVector out_target(out_n);

  R_xlen_t k = 0;
  R_xlen_t j = 0;
  for (Rcpp::CharacterVector outer : target) {
    for (Rcpp::String val : outer) {
      if (val != NA_STRING) {
        out_user_id[k]    = user_id[j];
        out_status_id[k]  = status_id[j];
        out_created_at[k] = created_at[j];
        out_target[k]     = val;
        k++;
      }
    }
    j++;
  }

  return Rcpp::List::create(out_user_id, out_target, out_status_id,
                            out_created_at);
}
