#ifndef TWEETIO_UTILS_H
#define TWEETIO_UTILS_H


#include <stringi.cpp>

#include <boost/date_time.hpp>
#include <boost/date_time/local_time_adjustor.hpp>
#include <boost/date_time/c_local_time_adjustor.hpp>
#include <boost/lexical_cast.hpp>


namespace tweetio {

template<typename stream_T>
std::size_t count_lines(const std::string& file_path) {
  stream_T in_file;
  in_file.open( file_path.c_str() );
  
  std::size_t out = 0;
  std::string line;

  while (std::getline(in_file, line) ) {
    ++out;
  }

  in_file.close();

  return out;
}


int count_digits(const int x) {
  if (x < 0) {
    return count_digits(-x);
  }

  constexpr int x1  = 1e1;
  constexpr int x2  = 1e2;
  constexpr int x3  = 1e3;
  constexpr int x4  = 1e4;
  constexpr int x5  = 1e5;
  constexpr int x6  = 1e6;
  constexpr int x7  = 1e7;
  constexpr int x8  = 1e8;
  constexpr int x9  = 1e9;
  // constexpr R_xlen_t x10 = 1e10;
  // constexpr R_xlen_t x11 = 1e11;
  // constexpr R_xlen_t x12 = 1e12;
  // constexpr R_xlen_t x13 = 1e13;
  // constexpr R_xlen_t x14 = 1e14;
  // constexpr R_xlen_t x15 = 1e15;
  // constexpr R_xlen_t x16 = 1e16;
  // constexpr R_xlen_t x17 = 1e17;
  // constexpr R_xlen_t x18 = 1e18;  

  if (x < x1) {
    return 1;
  } else if (x < x2) {
    return 2;
  } else if (x < x3) {
    return 3;
  } else if (x < x4) {
    return 4;
  } else if (x < x5) {
    return 5;
  } else if (x < x6) {
    return 6;
  } else if (x < x7) {
    return 7;
  } else if (x < x8) {
    return 8;
  } else if (x < x9) {
    return 9;
  } else {
    return 10;
  }
  // else if (x < x10) {
  //   return 10;
  // } else if (x < x11) {
  //   return 11;
  // } else if (x < x12) {
  //   return 12;
  // } else if (x < x13) {
  //   return 13;
  // } else if (x < x14) {
  //   return 14;
  // } else if (x < x15) {
  //   return 15;
  // } else if (x < x16) {
  //   return 16;
  // } else if (x < x17) {
  //   return 17;
  // } else if (x < x18) {
  //   return 18;
  // } else {
  //   return 19;
  // }
}


void finalize_df(Rcpp::List& x, const vec_chr& col_names, const int& n_rows) {
  const int n_digits = count_digits(n_rows);

  vec_chr row_names(n_rows);
  for (int i = 0; i < n_rows; ++i) {
      char name[n_digits];
      sprintf(&(name[0]), "%d", i);
      row_names[i] = name;
  }

  x.attr("names") = col_names;
  x.attr("row.names") = row_names;
  x.attr("class") = vec_chr{"data.frame"};
}


vec_chr strip_controls(vec_chr x) {
  return stri_replace_all_regex(
    x, vec_chr("[[:cntrl:]]"), vec_chr("")
  );
}


vec_chr extract_source(vec_chr x) {
  return stri_extract_first_regex(
    x, vec_chr("(?<=>).*?(?=</a>$)")
  );
}



// adapted from https://gallery.rcpp.org/articles/parsing-datetimes/
namespace bt = boost::posix_time;

const std::locale tweet_dttm_formats[] = {
  std::locale(std::locale::classic(), new bt::time_input_facet("%a %b %d %T %z %Y")),
  std::locale(std::locale::classic(), new bt::time_input_facet("%a %b %d %H:%M:%S %z %Y")),
  std::locale(std::locale::classic(), new bt::time_input_facet("%a, %d %b %Y %H:%M:%S +0000")),
  std::locale(std::locale::classic(), new bt::time_input_facet("%a %b %d %H:%M:%S +0000 %Y")),
  std::locale(std::locale::classic(), new bt::time_input_facet("%Y-%m-%dT%H:%M:%OS+00:00")),
  std::locale(std::locale::classic(), new bt::time_input_facet("%Y-%m-%d %H:%M:%S")),
  std::locale(std::locale::classic(), new bt::time_input_facet("%a %b %d %T %z %Y"))
};

constexpr int nformats = sizeof(tweet_dttm_formats) / sizeof(tweet_dttm_formats[0]);


double parse_dttm(const Rcpp::String s) {
  bt::ptime pt, ptbase;

  for (int i=0; pt == ptbase && i < nformats; ++i) {
    std::istringstream is(s);
    is.imbue( tweet_dttm_formats[i] );
    is >> pt;
  }

  if (pt == ptbase) {
    return NAN;
  } 

  const bt::ptime timet_start( boost::gregorian::date(1970, 1, 1) );
  bt::time_duration tdiff = pt - timet_start;
        
  return tdiff.total_microseconds() / 1.0e6;
}


Rcpp::NumericVector toPOSIXct(const vec_chr& sv) {
  int n = sv.size();
  Rcpp::NumericVector pv(n);
  pv.attr("class") = Rcpp::CharacterVector::create("POSIXct", "POSIXt");
  pv.attr("tzone") = "UTC";
    
  for (int i = 0; i < n; ++i) {
    if (sv[i].get() == NA_STRING) {
      pv[i] = NA_REAL;
      continue;
    }

    std::string s = boost::lexical_cast<std::string>(sv[i]);
    pv[i] = parse_dttm(s);
  }

  return pv;
}


} // namesapce tweetio



#endif
