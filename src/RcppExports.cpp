// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// prep_bbox_
Rcpp::List prep_bbox_(const Rcpp::List& bbox_coords);
RcppExport SEXP _tweetio_prep_bbox_(SEXP bbox_coordsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::List& >::type bbox_coords(bbox_coordsSEXP);
    rcpp_result_gen = Rcpp::wrap(prep_bbox_(bbox_coords));
    return rcpp_result_gen;
END_RCPP
}
// read_tweets_impl
Rcpp::List read_tweets_impl(const std::string& file_path);
RcppExport SEXP _tweetio_read_tweets_impl(SEXP file_pathSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type file_path(file_pathSEXP);
    rcpp_result_gen = Rcpp::wrap(read_tweets_impl(file_path));
    return rcpp_result_gen;
END_RCPP
}
// unnest_entities_
SEXP unnest_entities_(const SEXP& tracker, const Rcpp::CharacterVector& source, const Rcpp::List& target, const Rcpp::CharacterVector& col_names, const bool is_dttm);
RcppExport SEXP _tweetio_unnest_entities_(SEXP trackerSEXP, SEXP sourceSEXP, SEXP targetSEXP, SEXP col_namesSEXP, SEXP is_dttmSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const SEXP& >::type tracker(trackerSEXP);
    Rcpp::traits::input_parameter< const Rcpp::CharacterVector& >::type source(sourceSEXP);
    Rcpp::traits::input_parameter< const Rcpp::List& >::type target(targetSEXP);
    Rcpp::traits::input_parameter< const Rcpp::CharacterVector& >::type col_names(col_namesSEXP);
    Rcpp::traits::input_parameter< const bool >::type is_dttm(is_dttmSEXP);
    rcpp_result_gen = Rcpp::wrap(unnest_entities_(tracker, source, target, col_names, is_dttm));
    return rcpp_result_gen;
END_RCPP
}
// unnest_entities2_
SEXP unnest_entities2_(const SEXP& tracker, const Rcpp::List& source, const Rcpp::List& target, const Rcpp::CharacterVector& col_names);
RcppExport SEXP _tweetio_unnest_entities2_(SEXP trackerSEXP, SEXP sourceSEXP, SEXP targetSEXP, SEXP col_namesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const SEXP& >::type tracker(trackerSEXP);
    Rcpp::traits::input_parameter< const Rcpp::List& >::type source(sourceSEXP);
    Rcpp::traits::input_parameter< const Rcpp::List& >::type target(targetSEXP);
    Rcpp::traits::input_parameter< const Rcpp::CharacterVector& >::type col_names(col_namesSEXP);
    rcpp_result_gen = Rcpp::wrap(unnest_entities2_(tracker, source, target, col_names));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_tweetio_prep_bbox_", (DL_FUNC) &_tweetio_prep_bbox_, 1},
    {"_tweetio_read_tweets_impl", (DL_FUNC) &_tweetio_read_tweets_impl, 1},
    {"_tweetio_unnest_entities_", (DL_FUNC) &_tweetio_unnest_entities_, 5},
    {"_tweetio_unnest_entities2_", (DL_FUNC) &_tweetio_unnest_entities2_, 4},
    {NULL, NULL, 0}
};

RcppExport void R_init_tweetio(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
