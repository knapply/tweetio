#include <Rcpp.h>


constexpr double min_lon = -179;
constexpr double max_lon = 179;
constexpr double min_lat = -89;
constexpr double max_lat = 89;


// [[Rcpp::export(.is_valid_point)]]
Rcpp::LogicalVector
is_valid_point(const Rcpp::ListOf<Rcpp::NumericVector>& geo_coords) {
  return Rcpp::LogicalVector(std::cbegin(geo_coords), std::cend(geo_coords),
                             [](Rcpp::NumericVector point) {
                               return std::size(point) == 2 && //
                                      point[0] >= min_lon &&
                                      point[0] <= max_lon && //
                                      point[1] >= min_lat &&
                                      point[1] <= max_lat;
                             });
}


// [[Rcpp::export(.is_valid_bbox)]]
Rcpp::LogicalVector
is_valid_bbox(const Rcpp::ListOf<Rcpp::NumericVector>& bbox_coords) {
  return Rcpp::LogicalVector(
      std::cbegin(bbox_coords), std::cend(bbox_coords),
      [](Rcpp::NumericVector bbox) {
        constexpr R_xlen_t valid_length = 8;
        return std::size(bbox) == valid_length &&
               /* longitudes */
               bbox[0] >= min_lon && bbox[0] <= max_lon && //
               bbox[1] >= min_lon && bbox[1] <= max_lon && //
               bbox[2] >= min_lon && bbox[2] <= max_lon && //
               bbox[3] >= min_lon && bbox[3] <= max_lon && //

               /* latitudes */
               bbox[4] >= min_lat && bbox[4] <= max_lat && //
               bbox[5] >= min_lat && bbox[5] <= max_lat && //
               bbox[6] >= min_lat && bbox[6] <= max_lat && //
               bbox[7] >= min_lat && bbox[7] <= max_lat;
      });
}


// [[Rcpp::export(.prep_bbox)]]
Rcpp::List prep_bbox(const Rcpp::ListOf<Rcpp::NumericVector>& bbox_coords) {
  return Rcpp::List(std::cbegin(bbox_coords), std::cend(bbox_coords),
                    [](Rcpp::NumericVector coords) {
                      Rcpp::NumericMatrix temp(5, 2);
                      temp[0] = coords[0]; /* longitudes */
                      temp[1] = coords[1];
                      temp[2] = coords[2];
                      temp[3] = coords[3];
                      temp[4] = coords[0]; /* close longitude */

                      temp[5] = coords[4]; /* latitudes */
                      temp[6] = coords[5];
                      temp[7] = coords[6];
                      temp[8] = coords[7];
                      temp[9] = coords[4]; /* close latitude */

                      auto poly = Rcpp::List::create(temp);
                      poly.attr("class") =
                          Rcpp::CharacterVector::create("XY", "POLYGON", "sfg");
                      return poly;
                    });
}
