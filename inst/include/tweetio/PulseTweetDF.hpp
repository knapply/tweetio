#ifndef TWEETIO_PULSETWEETDF_H
#define TWEETIO_PULSETWEETDF_H

#include "TweetDF.hpp"

namespace tweetio {

class PulseTweetDF : protected TweetDF {

    protected:
    Rcpp::List rule_type;
    Rcpp::List rule_tag;
    Rcpp::List description;
    Rcpp::List value;
    
    Rcpp::List appid;
    Rcpp::List campaign_id;
    Rcpp::List campaign_title;
    Rcpp::List project_id;
    Rcpp::List project_title;

    Rcpp::List complex_value;

    public:
    PulseTweetDF() {;};
    ~PulseTweetDF() {};

    PulseTweetDF(const R_xlen_t& n_vals): TweetDF(n_vals) {
        rule_type                          = Rcpp::List(n_vals, vec_chr(0));
        rule_tag                           = Rcpp::List(n_vals, vec_chr(0));
        description                        = Rcpp::List(n_vals, vec_chr(0));
        value                              = Rcpp::List(n_vals, vec_chr(0));
        description                        = Rcpp::List(n_vals, vec_chr(0));
        appid                              = Rcpp::List(n_vals, vec_chr(0));
        campaign_id                        = Rcpp::List(n_vals, vec_chr(0));
        campaign_title                     = Rcpp::List(n_vals, vec_chr(0));
        project_id                         = Rcpp::List(n_vals, vec_chr(0));
        project_title                      = Rcpp::List(n_vals, vec_chr(0));
        complex_value                      = Rcpp::List(n_vals, vec_chr(0));
    };


    void push(const rapidjson::Value& doc, const rapidjson::Value& meta) {
        const auto i = TweetDF::push(doc) - 1;

        if (meta.Size() == 0) return;

        rule_type[i]                       = get_nested_meta_results(meta, "rule_matcher", "rule_type");
        rule_tag[i]                        = get_nested_meta_results(meta, "rule_matcher", "rule_tag");
        description[i]                     = get_nested_meta_results(meta, "rule_matcher", "description");

        value[i]                           = get_nested_meta_results(meta, "rule_matcher", "value");

        appid[i]                           = get_nested_meta_results(meta, "rule_matcher", "appid");
        campaign_id[i]                     = get_nested_meta_results(meta, "rule_matcher", "campaign_id");
        campaign_title[i]                  = get_nested_meta_results(meta, "rule_matcher", "campaign_title", true);
        project_id[i]                      = get_nested_meta_results(meta, "rule_matcher", "project_id");
        project_title[i]                   = get_nested_meta_results(meta, "rule_matcher", "project_title", true);

        complex_value[i]                   = get_nested_meta_results(meta, "rule_matcher", "complex_value", true);

    }; // PulseTweetDF.push()

    Rcpp::List to_r() {
        Rcpp::List cols = TweetDF::build_list();
        Rcpp::List meta_col = Rcpp::List(i_all);
        Rcpp::List out_row(i_all);

        for (int i = 0; i < i_all; ++i) {
            vec_chr length_tester = rule_type[i];
            const auto n_rows = length_tester.length();
            
            if (n_rows == 0) {
                meta_col[i] = R_NilValue;
                continue;
            }

            Rcpp::List out_row;

            out_row["ist_rule_type"]           = rule_type[i];
            out_row["ist_rule_tag"]            = rule_tag[i];
            out_row["ist_rule_value"]          = value[i];
            out_row["ist_description"]         = description[i];
            out_row["ist_appid"]               = appid[i];
            out_row["ist_campaign_id"]         = campaign_id[i];
            out_row["ist_campaign_title"]      = campaign_title[i];
            out_row["ist_project_id"]          = project_id[i];
            out_row["ist_project_title"]       = project_title[i];
            out_row["ist_complex_value"]       = complex_value[i];

            finalize_df(out_row, n_rows);
            meta_col[i] = out_row;
        }

        cols["metadata"] = meta_col;

        finalize_df(cols, i_all);

        return cols;

    }; // PulseTweetDF.to_r()
};




} // namespace tweetio


#endif