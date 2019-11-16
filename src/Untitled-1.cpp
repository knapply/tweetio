#include <Rcpp.h>

using namespace Rcpp;

List unroll_connections(const CharacterVector& from,
                        const List& to) {
  // set size paramaeters (exclude NAs from the 'to'-based output count)
  const int n = from.size();
  R_xlen_t len = 0;
  for (R_xlen_t i = 0; i < n; ++i) {
    const CharacterVector to_i = to[i];
    
    for (R_xlen_t j = 0; j < to_i.size(); ++j) {
      if (to_i[j].get() != R_NaString) {
        len++;
      }
    }
    
  }
  
  // use calculated lengths to initialize output character vectors
  Rcpp::CharacterVector from2(len); 
  Rcpp::CharacterVector to2(len); 
  
  // for each value of the 'from' vector, create appropriately re-sized from2
  // and to2 vectors
  R_xlen_t k = 0; // k: index of current non-NA value
  for (R_xlen_t i = 0; i < n; ++i) { // i: index of current "to"
    const CharacterVector to_i = to[i];
    
    for (int j = 0; j < to_i.size(); ++j) { // j: index of string inside to[i]
      
      if (to_i[j].get() != R_NaString) {
        from2[k] = from[i];
        to2[k] = to_i[j];
        k++;
      }
      
    }
    
  }

  Rcpp::List out = Rcpp::List::create(
    _["from"] = from2,
    _["to"] = to2
  );
  out.attr("row.names") = seq_len(len);
  out.attr("class") = "data.frame";
  
  return out;
}
