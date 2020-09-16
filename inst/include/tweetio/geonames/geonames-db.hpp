// #ifndef __TWEETIO__GEONAMES_DB_HPP__
// #define __TWEETIO__GEONAMES_DB_HPP__



// #include <any>
// #include <array>
// #include <string_view>

// #include <initializer_list>

// #include "../third-party/eternal.hpp"


// #include <unordered_map>


// namespace tweetio::geonames::db {

// using namespace std::literals::string_view_literals;

// // template <int i> constexpr auto lookup_name() {
// //   // clang-format off
// //     if constexpr (i == 1) {
// //         return std::array { "Aarde"sv, "Earth"sv, "Er shary"sv, "Erde"sv, "Foeld"sv, "Föld"sv, "Ge"sv, "Globe"sv, "Globo"sv, "Jorden"sv, "La terdi"sv, "Lurra"sv, "Maa"sv, "Monde"sv, "Mondo"sv, "Mundo"sv, "Mundua"sv, "Orbs"sv, "Pamant"sv, "Pamânt"sv, "Pianeta Terra"sv, "Planeta Tierra"sv, "Tero"sv, "Terra"sv, "Terre"sv, "Tierra"sv, "Welt"sv, "World"sv, "Ydrogeios"sv, "Yeryuezue"sv, "Yeryüzü"sv, "Zeme"sv, "Zemlja"sv, "Ziemia"sv, "el mon"sv, "el món"sv, "el planeta"sv, "nuestro planeta"sv, "prthibi"sv, "prthvi"sv, "Γη"sv, "Υδρόγειος"sv, "Ер шары"sv, "Земля"sv, "Җir shary"sv, "Җир шары"sv, "पृथ्वी"sv, "পৃথিবী"sv, "🌐"sv };
// //     }
// //   // clang-format on
// // }

// // struct db{
// //     // clang-format off
// // static constexpr std::array earth = { "Aarde"sv, "Earth"sv, "Er shary"sv, "Erde"sv, "Foeld"sv, "Föld"sv, "Ge"sv, "Globe"sv, "Globo"sv, "Jorden"sv, "La terdi"sv, "Lurra"sv, "Maa"sv, "Monde"sv, "Mondo"sv, "Mundo"sv, "Mundua"sv, "Orbs"sv, "Pamant"sv, "Pamânt"sv, "Pianeta Terra"sv, "Planeta Tierra"sv, "Tero"sv, "Terra"sv, "Terre"sv, "Tierra"sv, "Welt"sv, "World"sv, "Ydrogeios"sv, "Yeryuezue"sv, "Yeryüzü"sv, "Zeme"sv, "Zemlja"sv, "Ziemia"sv, "el mon"sv, "el món"sv, "el planeta"sv, "nuestro planeta"sv, "prthibi"sv, "prthvi"sv, "Γη"sv, "Υδρόγειος"sv, "Ер шары"sv, "Земля"sv, "Җir shary"sv, "Җир шары"sv, "पृथ्वी"sv, "পৃথিবী"sv, "🌐"sv };
// // static std::array { "Aasia"sv, "Asia"sv, "Asie"sv, "Asien"sv, "Asya"sv, "Asía"sv, "Azia"sv, "Azie"sv, "Azija"sv, "Azio"sv, "Azië"sv, "Azja"sv, "Azsia"sv, "Chau A"sv, "Châu Á"sv, "ajia"sv, "an Aise"sv, "an Áise"sv, "asia"sv, "asya"sv, "ayshya"sv, "esiya mahadvipa"sv, "xecheiy"sv, "ya zhou"sv, "Àsia"sv, "Ásia"sv, "Ázia"sv, "Ázsia"sv, "Āzija"sv, "Ασία"sv, "Азия"sv, "Азія"sv, "אסיה"sv, "آسيا"sv, "ایشیا"sv, "एशिया महाद्वीप"sv, "เอเชีย"sv, "アジア"sv, "亚洲"sv, "아시아"sv },
// //     // clang-format on
// // };


// // constexpr auto test = { "Aarde", "Earth", };
// //  auto db = std::unordered_map<std::string_view, std::initializer_list<std::string_view>>{
// auto db = std::unordered_map<std::string, std::vector<std::string_view>>{
//     {"earth",  "Er shary"sv, "Erde"sv, "Foeld"sv, "Föld"sv, "Ge"sv, "Globe"sv, "Globo"sv, "Jorden"sv, "La terdi"sv, "Lurra"sv, "Maa"sv, "Monde"sv, "Mondo"sv, "Mundo"sv, "Mundua"sv, "Orbs"sv, "Pamant"sv, "Pamânt"sv, "Pianeta Terra"sv, "Planeta Tierra"sv, "Tero"sv, "Terra"sv, "Terre"sv, "Tierra"sv, "Welt"sv, "World"sv, "Ydrogeios"sv, "Yeryuezue"sv, "Yeryüzü"sv, "Zeme"sv, "Zemlja"sv, "Ziemia"sv, "el mon"sv, "el món"sv, "el planeta"sv, "nuestro planeta"sv, "prthibi"sv, "prthvi"sv, "Γη"sv, "Υδρόγειος"sv, "Ер шары"sv, "Земля"sv, "Җir shary"sv, "Җир шары"sv, "पृथ्वी"sv, "পৃথিবী"sv, "🌐"sv } }
// };















// } // namespace tweetio::geonames::db

// #endif
