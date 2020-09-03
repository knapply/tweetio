#ifndef __TWEETIO__QCR_HPP__
#define __TWEETIO__QCR_HPP__


#include "base.hpp"


namespace tweetio {


// template <typename element_T>
inline vec_str
to_campaign_ids(simdjson::simdjson_result<simdjson::dom::element> x) {
  if (!x.error()) {
    if (auto [array, error] = x.first.get<simdjson::dom::array>(); !error) {
      if (const R_xlen_t n = std::size(array); n > 0) {
        std::vector<std::string> out(n);
        std::size_t i = 0;
        for (auto&& val : array) {
          out[i++] = to<std::string>(val.at_pointer("/campaignId"));
        }
        return out;
      }
    }
  }
  return vec_str{""};
}


class QCR : public Base_DF {

  vec_vec_str campaign_ids;


public:
  QCR() = default;

  explicit QCR(const std::size_t n) : Base_DF(n), campaign_ids(n){};

  void reserve(const std::size_t n) {
    Base_DF::Base_DF::reserve(n);
    campaign_ids.reserve(n);
  }


  void push(simdjson::dom::element x) {
    // clang-format off
    Base_DF::Base_DF::push(x.at_pointer("/doc").first); /*    /doc/id_str already checked    */
    campaign_ids.emplace_back(/* */ to_campaign_ids(x.at_pointer("/campaign_tags")) /*    */);
    // clang-format on
  }

  [[nodiscard]] SEXP as_list() {
    auto out = Base_DF::Base_DF::as_list();
    out["campaign_ids"] = campaign_ids;

    return out;
  }
};


} // namespace tweetio

#endif
