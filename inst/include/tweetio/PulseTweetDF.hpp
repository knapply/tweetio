#ifndef TWEETIO_PULSETWEETDF_H
#define TWEETIO_PULSETWEETDF_H

// #include "TweetDF.hpp"

namespace tweetio {

class PulseTweetDF : public TweetDF {

    public:
    
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

    // public:
    // PulseTweetDF() {};
    ~PulseTweetDF() {};

    PulseTweetDF(const R_xlen_t& n_vals) {
        rule_type                          = Rcpp::List(n_vals);
        rule_tag                           = Rcpp::List(n_vals);
        description                        = Rcpp::List(n_vals);
        value                              = Rcpp::List(n_vals);
        description                        = Rcpp::List(n_vals);

        appid                              = Rcpp::List(n_vals);
        campaign_id                        = Rcpp::List(n_vals);
        campaign_title                     = Rcpp::List(n_vals);
        project_id                         = Rcpp::List(n_vals);
        project_title                      = Rcpp::List(n_vals);
        
        complex_value                      = Rcpp::List(n_vals);
    };


    void push(const rapidjson::Value& x) {
        TweetDF::push(x);

        const rapidjson::Value& meta = x["meta"];
        if (meta.Size() == 0) {
            return;
        }

        rule_type[i_all]                       = get_nested_meta_results(meta, "rule_matcher", "rule_type");
        rule_tag[i_all]                        = get_nested_meta_results(meta, "rule_matcher", "rule_tag");
        description[i_all]                     = get_nested_meta_results(meta, "rule_matcher", "description");

        value[i_all]                           = get_nested_meta_results(meta, "rule_matcher", "value");

        appid[i_all]                           = get_nested_meta_results(meta, "rule_matcher", "appid");
        campaign_id[i_all]                     = get_nested_meta_results(meta, "rule_matcher", "campaign_id");
        campaign_title[i_all]                  = get_nested_meta_results(meta, "rule_matcher", "campaign_title", true);
        project_id[i_all]                      = get_nested_meta_results(meta, "rule_matcher", "project_id");
        project_title[i_all]                   = get_nested_meta_results(meta, "rule_matcher", "project_title", true);

        complex_value[i_all]                   = get_nested_meta_results(meta, "rule_matcher", "complex_value", true);
    }; // PulseTweetDF.push()

   Rcpp::List build_list() {
       Rcpp::List out = TweetDF::build_list();
       const auto seq_out = get_seq_out();

       out["ist_rule_type"]      = rule_type[seq_out];
       out["ist_rule_tag"]       = rule_tag[seq_out];
       out["ist_description"]    = description[seq_out];
       out["ist_value"]          = value[seq_out];
       out["ist_appid"]          = appid[seq_out];
       out["ist_campaign_id"]    = campaign_id[seq_out];
       out["ist_campaign_title"] = campaign_title[seq_out];
       out["project_id"]         = project_id[seq_out];
       out["ist_project_title"]  = project_title[seq_out];
       out["ist_complex_value"]  = complex_value[seq_out];

       return out;
   } // PulseTweetDF.build_list()

    Rcpp::List to_r() {
        Rcpp::List cols = build_list();

        const int n_digits = count_digits(i_all);
        vec_chr row_names(i_all);
        for (int i = 0; i < i_all; ++i) {
            char name[n_digits];
            sprintf(&(name[0]), "%d", i);
            row_names[i] = name;
        }

        cols.attr("row.names") = row_names;
        cols.attr("class") = vec_chr{"data.frame"};

        return cols;
    }; // PulseTweetDF.to_r()
};




} // namespace tweetio


#endif