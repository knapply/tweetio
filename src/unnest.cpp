#include <Rcpp.h>

typedef Rcpp::Vector<STRSXP> vec_chr;
typedef Rcpp::Vector<LGLSXP> vec_lgl;
typedef Rcpp::Vector<INTSXP> vec_int;
typedef Rcpp::Vector<REALSXP> vec_dbl;

template <int RTYPE>
SEXP unnest_entities(const Rcpp::Vector<RTYPE>& tracker,
                     const vec_chr& source,
                     const Rcpp::List& target,
                     const vec_chr& col_names) {
  const R_xlen_t n = tracker.length();
  R_xlen_t out_n = 0;

  for (R_xlen_t i = 0; i < n; ++i) {
    vec_chr target_i = target[i];

    for (R_xlen_t j = 0; j < target_i.length(); ++j) {
      if (target_i[j].get() != NA_STRING) {
        out_n++;
      }
    }
  }

  vec_chr source2(out_n);
  vec_chr target2(out_n);

  Rcpp::Vector<RTYPE> tracker2(out_n);
  tracker2.attr("class") = tracker.attr("class");
  tracker2.attr("tz") = tracker.attr("tzone");

  R_xlen_t k = 0;
  for (R_xlen_t i = 0; i < n; ++i) {
    vec_chr target_i = target[i];

    for (R_xlen_t j = 0; j < target_i.size(); ++j) {
      if (target_i[j].get() != NA_STRING) {
        source2[k] = source[i];
        target2[k] = target_i[j];
        tracker2[k] = tracker[i];
        k++;
      }
    }
  }

  using Rcpp::_;
  Rcpp::List out = Rcpp::List::create(source2, target2, tracker2);
  out.attr("names") = col_names;
  out.attr("row.names") = Rcpp::seq_len(out_n);
  out.attr("class") = "data.frame";

  return out;
}

// [[Rcpp::export]]
SEXP unnest_entities_impl(const SEXP& tracker,
                          const Rcpp::CharacterVector& source,
                          const Rcpp::List& target,
                          const Rcpp::CharacterVector& col_names) {
  switch (TYPEOF(tracker)) {
    case STRSXP:
      return unnest_entities<STRSXP>(tracker, source, target, col_names);
    case REALSXP:
      return unnest_entities<REALSXP>(tracker, source, target, col_names);
  }

  return R_NilValue;
}

template <int RTYPE>
SEXP unnest_entities2(const Rcpp::Vector<RTYPE>& tracker,
                      const Rcpp::List& source,
                      const Rcpp::List& target,
                      const vec_chr& col_names) {
  const R_xlen_t n = tracker.length();
  R_xlen_t out_n = 0;

  for (R_xlen_t i = 0; i < n; ++i) {
    const vec_chr target_i = target[i];

    for (int j = 0; j < target_i.length(); ++j) {
      if (target_i[j].get() != NA_STRING) {
        out_n++;
      }
    }
  }

  vec_chr source2(out_n);
  vec_chr target2(out_n);
  Rcpp::Vector<RTYPE> tracker2(out_n);
  tracker2.attr("class") = tracker.attr("class");
  tracker2.attr("tz") = tracker.attr("tz");

  R_xlen_t k = 0;
  for (R_xlen_t i = 0; i < n; ++i) {
    const vec_chr source_i = source[i];
    const vec_chr target_i = target[i];

    for (R_xlen_t j = 0; j < target_i.size(); ++j) {
      if (target_i[j].get() != NA_STRING) {
        source2[k] = source_i[j];
        target2[k] = target_i[j];
        tracker2[k] = tracker[i];
        k++;
      }
    }
  }

  // using Rcpp::_;
  Rcpp::List out = Rcpp::List::create(source2, target2, tracker2);
  out.attr("names") = col_names;
  out.attr("row.names") = Rcpp::seq_len(out_n);
  out.attr("class") = "data.frame";

  return out;
}

// [[Rcpp::export]]
SEXP unnest_entities2_impl(const SEXP& tracker,
                           const Rcpp::List& source,
                           const Rcpp::List& target,
                           const Rcpp::CharacterVector& col_names) {
  switch (TYPEOF(tracker)) {
    case STRSXP:
      return unnest_entities2<STRSXP>(tracker, source, target, col_names);
    case REALSXP:
      return unnest_entities2<REALSXP>(tracker, source, target, col_names);
  }
  return R_NilValue;
}
