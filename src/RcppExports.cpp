// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// is_valid_bbox
Rcpp::LogicalVector is_valid_bbox(const Rcpp::List& bbox_coords, const bool lon_lat);
RcppExport SEXP _tweetio_is_valid_bbox(SEXP bbox_coordsSEXP, SEXP lon_latSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::List& >::type bbox_coords(bbox_coordsSEXP);
    Rcpp::traits::input_parameter< const bool >::type lon_lat(lon_latSEXP);
    rcpp_result_gen = Rcpp::wrap(is_valid_bbox(bbox_coords, lon_lat));
    return rcpp_result_gen;
END_RCPP
}
// prep_bbox
Rcpp::List prep_bbox(const Rcpp::List& bbox_coords, const bool lon_lat);
RcppExport SEXP _tweetio_prep_bbox(SEXP bbox_coordsSEXP, SEXP lon_latSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Rcpp::List& >::type bbox_coords(bbox_coordsSEXP);
    Rcpp::traits::input_parameter< const bool >::type lon_lat(lon_latSEXP);
    rcpp_result_gen = Rcpp::wrap(prep_bbox(bbox_coords, lon_lat));
    return rcpp_result_gen;
END_RCPP
}
// inherit_test
Rcpp::List inherit_test();
RcppExport SEXP _tweetio_inherit_test() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(inherit_test());
    return rcpp_result_gen;
END_RCPP
}
// read_tweets_impl
Rcpp::List read_tweets_impl(const std::string& file_path, const bool verbose);
RcppExport SEXP _tweetio_read_tweets_impl(SEXP file_pathSEXP, SEXP verboseSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type file_path(file_pathSEXP);
    Rcpp::traits::input_parameter< const bool >::type verbose(verboseSEXP);
    rcpp_result_gen = Rcpp::wrap(read_tweets_impl(file_path, verbose));
    return rcpp_result_gen;
END_RCPP
}
// unnest_entities_impl
SEXP unnest_entities_impl(const SEXP& tracker, const Rcpp::CharacterVector& source, const Rcpp::List& target, const Rcpp::CharacterVector& col_names);
RcppExport SEXP _tweetio_unnest_entities_impl(SEXP trackerSEXP, SEXP sourceSEXP, SEXP targetSEXP, SEXP col_namesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const SEXP& >::type tracker(trackerSEXP);
    Rcpp::traits::input_parameter< const Rcpp::CharacterVector& >::type source(sourceSEXP);
    Rcpp::traits::input_parameter< const Rcpp::List& >::type target(targetSEXP);
    Rcpp::traits::input_parameter< const Rcpp::CharacterVector& >::type col_names(col_namesSEXP);
    rcpp_result_gen = Rcpp::wrap(unnest_entities_impl(tracker, source, target, col_names));
    return rcpp_result_gen;
END_RCPP
}
// unnest_entities2_impl
SEXP unnest_entities2_impl(const SEXP& tracker, const Rcpp::List& source, const Rcpp::List& target, const Rcpp::CharacterVector& col_names);
RcppExport SEXP _tweetio_unnest_entities2_impl(SEXP trackerSEXP, SEXP sourceSEXP, SEXP targetSEXP, SEXP col_namesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const SEXP& >::type tracker(trackerSEXP);
    Rcpp::traits::input_parameter< const Rcpp::List& >::type source(sourceSEXP);
    Rcpp::traits::input_parameter< const Rcpp::List& >::type target(targetSEXP);
    Rcpp::traits::input_parameter< const Rcpp::CharacterVector& >::type col_names(col_namesSEXP);
    rcpp_result_gen = Rcpp::wrap(unnest_entities2_impl(tracker, source, target, col_names));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_tweetio_is_valid_bbox", (DL_FUNC) &_tweetio_is_valid_bbox, 2},
    {"_tweetio_prep_bbox", (DL_FUNC) &_tweetio_prep_bbox, 2},
    {"_tweetio_inherit_test", (DL_FUNC) &_tweetio_inherit_test, 0},
    {"_tweetio_read_tweets_impl", (DL_FUNC) &_tweetio_read_tweets_impl, 2},
    {"_tweetio_unnest_entities_impl", (DL_FUNC) &_tweetio_unnest_entities_impl, 4},
    {"_tweetio_unnest_entities2_impl", (DL_FUNC) &_tweetio_unnest_entities2_impl, 4},
    {NULL, NULL, 0}
};

RcppExport void R_init_tweetio(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
