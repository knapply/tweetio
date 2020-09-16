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


template <int RTYPE> constexpr auto make_na() {
  if constexpr (RTYPE == STRSXP) {
    return Rcpp::String(NA_STRING);
  }
  if constexpr (RTYPE == INTSXP) {
    return NA_INTEGER;
  }
  if constexpr (RTYPE == REALSXP) {
    return NA_REAL;
  }
  if constexpr (RTYPE == LGLSXP) {
    return NA_LOGICAL;
  }
  if constexpr (RTYPE == NILSXP) {
    return NA_LOGICAL;
  }
}


template <int RTYPE, typename na_T>
bool any_not_na(Rcpp::Vector<RTYPE> x, na_T NA) {
  if constexpr (RTYPE != NILSXP) {
    for (R_xlen_t i = 0; i < std::size(x); ++i) {
      if (x[i] != NA) {
        return true;
      }
    }
  }
  return false;
}

bool any_not_na_impl(SEXP x) {
  switch (TYPEOF(x)) {
    case REALSXP:
      return any_not_na<REALSXP>(x, make_na<REALSXP>());

    case STRSXP:
      return any_not_na<STRSXP>(x, make_na<STRSXP>());

    case INTSXP:
      return any_not_na<INTSXP>(x, make_na<INTSXP>());


    case LGLSXP:
      return any_not_na<LGLSXP>(x, make_na<LGLSXP>());

    case NILSXP:
      return false;

    default:
      return false;
  }
}

template <int RTYPE> SEXP coalesce_list(Rcpp::List x) {
  const auto na = make_na<RTYPE>();
  for (R_xlen_t i = 0; i < std::size(x); ++i) {
    if (any_not_na<RTYPE>(x[i], na)) {
      return Rcpp::List::create(x[i]);
    }
  }
  return Rcpp::List::create(na);
}

SEXP coalesce_list_impl(Rcpp::List x) {
  switch (TYPEOF(x[0])) {
    case STRSXP:
      return coalesce_list<STRSXP>(x);

    case REALSXP:
      return coalesce_list<REALSXP>(x);

    case NILSXP:
      return coalesce_list<NILSXP>(x);

    default:
      Rcpp::stop("wtf");
      return R_NilValue;
  }
}

template <int RTYPE> Rcpp::Vector<RTYPE> coalesce_vec(Rcpp::Vector<RTYPE> x) {
  if constexpr (RTYPE == VECSXP) {
    return coalesce_list_impl(x);
  } else {
    const auto na = make_na<RTYPE>();
    for (R_xlen_t i = 0; i < std::size(x); ++i) {
      if (x[i] != na) {
        return Rcpp::Vector<RTYPE>::create(x[i]);
      }
    }
    return Rcpp::Vector<RTYPE>::create(na);
  }
}

// [[Rcpp::export(.coalesce_impl)]]
SEXP coalesce_impl(Rcpp::List& sub_df) {
  if (const R_xlen_t n = Rf_xlength(sub_df[0]); n > 1) {
    Rcpp::List out(sub_df.size());
    out.attr("names") = sub_df.attr("names");

    for (R_xlen_t i = 0; i < sub_df.size(); ++i) {
      switch (TYPEOF(sub_df[i])) {
        case STRSXP:
          out[i] = coalesce_vec<STRSXP>(sub_df[i]);
          break;

        case INTSXP:
          out[i] = coalesce_vec<INTSXP>(sub_df[i]);
          break;

        case REALSXP:
          out[i] = coalesce_vec<REALSXP>(sub_df[i]);
          break;

        case LGLSXP:
          out[i] = coalesce_vec<LGLSXP>(sub_df[i]);
          break;

        case VECSXP:
          out[i] = coalesce_vec<VECSXP>(sub_df[i]);
          break;

        default:
          Rcpp::stop("wtf");
      }
    }
    return out;
  }
  return sub_df;
}


// [[Rcpp::export(.null_to_na_dbl)]]
void null_to_na_dbl(Rcpp::List& x) {
  const R_xlen_t n = std::size(x);
  for (R_xlen_t i = 0; i < n; ++i) {
    if (TYPEOF(x[i]) == NILSXP) {
      x[i] = Rcpp::NumericVector::create(NA_REAL);
    }
  }
}


// [[Rcpp::export(.null_to_na_chr)]]
void null_to_na_chr(Rcpp::List& x) {
  const R_xlen_t n = std::size(x);
  for (R_xlen_t i = 0; i < n; ++i) {
    if (TYPEOF(x[i]) == NILSXP) {
      x[i] = Rcpp::CharacterVector::create(Rcpp::String(NA_STRING));
    }
  }
}
