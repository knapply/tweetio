#ifndef __TWEETIO__REGEX_HPP__
#define __TWEETIO__REGEX_HPP__


#include "third-party/ctre.hpp"

namespace tweetio::rgx::countries {


// clang-format off
static constexpr auto afghanistan = ctll::fixed_string(R"(afghan)");
static constexpr auto albania = ctll::fixed_string(R"(albania)");
static constexpr auto algeria = ctll::fixed_string(R"(algeria)");
static constexpr auto andorra = ctll::fixed_string(R"(andorra)");
static constexpr auto angola = ctll::fixed_string(R"(angola)");
static constexpr auto antigua_barbuda = ctll::fixed_string(R"(antigua)");
static constexpr auto argentina = ctll::fixed_string(R"(argentin)");
static constexpr auto armenia = ctll::fixed_string(R"(armenia)");
static constexpr auto australia = ctll::fixed_string(R"(australia)");
static constexpr auto austria = ctll::fixed_string(R"(^(?!.*hungary).*austria|\baustri.*\bemp)");
static constexpr auto austria_hungary = ctll::fixed_string(R"(austria-hungary)");
static constexpr auto azerbaijan = ctll::fixed_string(R"(azerbaijan)");
static constexpr auto baden = ctll::fixed_string(R"(baden)");
static constexpr auto bahamas = ctll::fixed_string(R"(bahamas)");
static constexpr auto bahrain = ctll::fixed_string(R"(bahrain)");
static constexpr auto bangladesh = ctll::fixed_string(R"(bangladesh|^(?=.*east).*paki?stan)");
static constexpr auto barbados = ctll::fixed_string(R"(barbados)");
static constexpr auto bavaria = ctll::fixed_string(R"(bavaria)");
static constexpr auto belarus = ctll::fixed_string(R"(belarus|byelo)");
static constexpr auto belgium = ctll::fixed_string(R"(^(?!.*luxem).*belgium)");
static constexpr auto belize = ctll::fixed_string(R"(belize|^(?=.*british).*honduras)");
static constexpr auto benin = ctll::fixed_string(R"(benin|dahome)");
static constexpr auto bhutan = ctll::fixed_string(R"(bhutan)");
static constexpr auto bolivia = ctll::fixed_string(R"(bolivia)");
static constexpr auto bosnia_herzegovina = ctll::fixed_string(R"(herzegovina|bosnia)");
static constexpr auto botswana = ctll::fixed_string(R"(botswana|bechuana)");
static constexpr auto brazil = ctll::fixed_string(R"(brazil)");
static constexpr auto brunei = ctll::fixed_string(R"(brunei)");
static constexpr auto brunswick = ctll::fixed_string(R"(brunswick)");
static constexpr auto bulgaria = ctll::fixed_string(R"(bulgaria)");
static constexpr auto burkina_faso = ctll::fixed_string(R"(burkina|\bfaso|upper.?volta)");
static constexpr auto burundi = ctll::fixed_string(R"(burundi)");
static constexpr auto cambodia = ctll::fixed_string(R"(cambodia|kampuchea|khmer)");
static constexpr auto cameroon = ctll::fixed_string(R"(cameroon)");
static constexpr auto canada = ctll::fixed_string(R"(canada)");
static constexpr auto cape_verde = ctll::fixed_string(R"(verde)");
static constexpr auto central_african_republic = ctll::fixed_string(R"(\bcentral.african.rep)");
static constexpr auto chad = ctll::fixed_string(R"(\bchad)");
static constexpr auto chile = ctll::fixed_string(R"(\bchile)");
static constexpr auto china = ctll::fixed_string(R"(^(?!.*\bmac)(?!.*\bhong)(?!.*\btai)(?!.*\brep).*china|^(?=.*peo)(?=.*rep).*china)");
static constexpr auto colombia = ctll::fixed_string(R"(colombia)");
static constexpr auto comoros = ctll::fixed_string(R"(comoro)");
static constexpr auto congo_brazzaville = ctll::fixed_string(R"(^(?!.*\bdem)(?!.*\bd[\.]?r)(?!.*kinshasa)(?!.*zaire)(?!.*belg)(?!.*l.opoldville)(?!.*free).*\bcongo)");
static constexpr auto congo_kinshasa = ctll::fixed_string(R"(\bdem.*congo|congo.*\bdem|congo.*\bd[\.]?r|\bd[\.]?r.*congo|belgian.?congo|congo.?free.?state|kinshasa|zaire|l.opoldville|drc|droc|rdc)");
static constexpr auto costa_rica = ctll::fixed_string(R"(costa.?rica)");
static constexpr auto cote_d_ivoire = ctll::fixed_string(R"(ivoire|ivory)");
static constexpr auto croatia = ctll::fixed_string(R"(croatia)");
static constexpr auto cuba = ctll::fixed_string(R"(\bcuba)");
static constexpr auto cyprus = ctll::fixed_string(R"(cyprus)");
static constexpr auto czechia = ctll::fixed_string(R"(^(?=.*rep).*czech|czechia|bohemia)");
static constexpr auto czechoslovakia = ctll::fixed_string(R"(czechoslovakia)");
static constexpr auto denmark = ctll::fixed_string(R"(denmark)");
static constexpr auto djibouti = ctll::fixed_string(R"(djibouti)");
static constexpr auto dominica = ctll::fixed_string(R"(dominica(?!n))");
static constexpr auto dominican_republic = ctll::fixed_string(R"(dominican.rep)");
static constexpr auto ecuador = ctll::fixed_string(R"(ecuador)");
static constexpr auto egypt = ctll::fixed_string(R"(egypt)");
static constexpr auto el_salvador = ctll::fixed_string(R"(el.?salvador)");
static constexpr auto equatorial_guinea = ctll::fixed_string(R"(guine.*eq|eq.*guine|^(?=.*span).*guinea)");
static constexpr auto eritrea = ctll::fixed_string(R"(eritrea)");
static constexpr auto estonia = ctll::fixed_string(R"(estonia)");
static constexpr auto eswatini = ctll::fixed_string(R"(swaziland|eswatini)");
static constexpr auto ethiopia = ctll::fixed_string(R"(ethiopia|abyssinia)");
static constexpr auto fiji = ctll::fixed_string(R"(fiji)");
static constexpr auto finland = ctll::fixed_string(R"(finland)");
static constexpr auto france = ctll::fixed_string(R"(^(?!.*\bdep)(?!.*martinique).*france|french.?republic|\bgaul)");
static constexpr auto gabon = ctll::fixed_string(R"(gabon)");
static constexpr auto gambia = ctll::fixed_string(R"(gambia)");
static constexpr auto georgia = ctll::fixed_string(R"(^(?!.*south).*georgia)");
static constexpr auto german_democratic_republic = ctll::fixed_string(R"(german.?democratic.?rep|democratic.?rep.*germany|east.germany|germany.*east)");
static constexpr auto germany = ctll::fixed_string(R"(^(?!.*east).*germany|^(?=.*\bfed.*\brep).*german)");
static constexpr auto ghana = ctll::fixed_string(R"(ghana|gold.?coast)");
static constexpr auto greece = ctll::fixed_string(R"(greece|hellenic|hellas)");
static constexpr auto grenada = ctll::fixed_string(R"(grenada)");
static constexpr auto guatemala = ctll::fixed_string(R"(guatemala)");
static constexpr auto guinea = ctll::fixed_string(R"(^(?!.*eq)(?!.*span)(?!.*bissau)(?!.*portu)(?!.*new).*guinea)");
static constexpr auto guinea_bissau = ctll::fixed_string(R"(bissau|^(?=.*portu).*guinea)");
static constexpr auto guyana = ctll::fixed_string(R"(guyana|british.?guiana)");
static constexpr auto haiti = ctll::fixed_string(R"(haiti)");
static constexpr auto hamburg = ctll::fixed_string(R"(hamburg)");
static constexpr auto hanover = ctll::fixed_string(R"(hanover)");
static constexpr auto hesse_electoral = ctll::fixed_string(R"(hesse.*lectoral)");
static constexpr auto hesse_grand_ducal = ctll::fixed_string(R"(hess.*gran.*ducal)");
static constexpr auto hesse_darmstadt = ctll::fixed_string(R"(hesse.darmstadt)");
static constexpr auto hesse_kassel = ctll::fixed_string(R"(hesse.kassel)");
static constexpr auto honduras = ctll::fixed_string(R"(^(?!.*brit).*honduras)");
static constexpr auto hong_kong_sar_china = ctll::fixed_string(R"(hong.?kong)");
static constexpr auto hungary = ctll::fixed_string(R"(^(?!.*austr).*hungary)");
static constexpr auto iceland = ctll::fixed_string(R"(iceland)");
static constexpr auto india = ctll::fixed_string(R"(india(?!.*ocea))");
static constexpr auto indonesia = ctll::fixed_string(R"(indonesia)");
static constexpr auto iran = ctll::fixed_string(R"(\biran|persia)");
static constexpr auto iraq = ctll::fixed_string(R"(\biraq|mesopotamia)");
static constexpr auto ireland = ctll::fixed_string(R"(^(?!.*north).*\bireland)");
static constexpr auto israel = ctll::fixed_string(R"(israel)");
static constexpr auto italy = ctll::fixed_string(R"(italy)");
static constexpr auto jamaica = ctll::fixed_string(R"(jamaica)");
static constexpr auto japan = ctll::fixed_string(R"(japan)");
static constexpr auto jordan = ctll::fixed_string(R"(jordan)");
static constexpr auto kazakhstan = ctll::fixed_string(R"(kazak)");
static constexpr auto kenya = ctll::fixed_string(R"(kenya|british.?east.?africa|east.?africa.?prot)");
static constexpr auto kiribati = ctll::fixed_string(R"(kiribati)");
static constexpr auto kosovo = ctll::fixed_string(R"(kosovo)");
static constexpr auto kuwait = ctll::fixed_string(R"(kuwait)");
static constexpr auto kyrgyzstan = ctll::fixed_string(R"(kyrgyz|kirghiz)");
static constexpr auto laos = ctll::fixed_string(R"(\blaos?\b)");
static constexpr auto latvia = ctll::fixed_string(R"(latvia)");
static constexpr auto lebanon = ctll::fixed_string(R"(lebanon)");
static constexpr auto lesotho = ctll::fixed_string(R"(lesotho|basuto)");
static constexpr auto liberia = ctll::fixed_string(R"(liberia)");
static constexpr auto libya = ctll::fixed_string(R"(libya)");
static constexpr auto liechtenstein = ctll::fixed_string(R"(liechtenstein)");
static constexpr auto lithuania = ctll::fixed_string(R"(lithuania)");
static constexpr auto luxembourg = ctll::fixed_string(R"(^(?!.*belg).*luxem)");
static constexpr auto madagascar = ctll::fixed_string(R"(madagascar|malagasy)");
static constexpr auto malawi = ctll::fixed_string(R"(malawi|nyasa)");
static constexpr auto malaysia = ctll::fixed_string(R"(malaysia)");
static constexpr auto maldives = ctll::fixed_string(R"(maldive)");
static constexpr auto mali = ctll::fixed_string(R"(\bmali\b)");
static constexpr auto malta = ctll::fixed_string(R"(\bmalta)");
static constexpr auto marshall_islands = ctll::fixed_string(R"(marshall)");
static constexpr auto mauritania = ctll::fixed_string(R"(mauritania)");
static constexpr auto mauritius = ctll::fixed_string(R"(mauritius)");
static constexpr auto mecklenburg_schwerin = ctll::fixed_string(R"(mecklenbur.*schwerin)");
static constexpr auto mexico = ctll::fixed_string(R"(\bmexic)");
static constexpr auto micronesia_federated_states_of = ctll::fixed_string(R"(fed.*micronesia|micronesia.*fed)");
static constexpr auto modena = ctll::fixed_string(R"(modena)");
static constexpr auto moldova = ctll::fixed_string(R"(moldov|b(a|e)ssarabia)");
static constexpr auto monaco = ctll::fixed_string(R"(monaco)");
static constexpr auto mongolia = ctll::fixed_string(R"(mongolia)");
static constexpr auto montenegro = ctll::fixed_string(R"(^(?!.*serbia).*montenegro)");
static constexpr auto morocco = ctll::fixed_string(R"(morocco|\bmaroc)");
static constexpr auto mozambique = ctll::fixed_string(R"(mozambique)");
static constexpr auto myanmar_burma = ctll::fixed_string(R"(myanmar|burma)");
static constexpr auto namibia = ctll::fixed_string(R"(namibia)");
static constexpr auto nassau = ctll::fixed_string(R"(nassau)");
static constexpr auto nauru = ctll::fixed_string(R"(nauru)");
static constexpr auto nepal = ctll::fixed_string(R"(nepal)");
static constexpr auto netherlands = ctll::fixed_string(R"(^(?!.*\bant)(?!.*\bcarib).*netherlands)");
static constexpr auto new_zealand = ctll::fixed_string(R"(new.?zealand)");
static constexpr auto nicaragua = ctll::fixed_string(R"(nicaragua)");
static constexpr auto niger = ctll::fixed_string(R"(\bniger(?!ia))");
static constexpr auto nigeria = ctll::fixed_string(R"(nigeria)");
static constexpr auto north_korea = ctll::fixed_string(R"(dprk|d.p.r.k|korea.+(d.p.r|dpr|north|dem.*peo.*rep.*)|(d.p.r|dpr|north|dem.*peo.*rep.*).+korea)");
static constexpr auto north_macedonia = ctll::fixed_string(R"(macedonia|fyrom)");
static constexpr auto norway = ctll::fixed_string(R"(norway)");
static constexpr auto oldenburg = ctll::fixed_string(R"(oldenburg)");
static constexpr auto oman = ctll::fixed_string(R"(\boman|trucial)");
static constexpr auto orange_free_state = ctll::fixed_string(R"(orange.free.state)");
static constexpr auto pakistan = ctll::fixed_string(R"(^(?!.*east).*paki?stan)");
static constexpr auto palau = ctll::fixed_string(R"(palau)");
static constexpr auto palestinian_territories = ctll::fixed_string(R"(palestin|\bgaza|west.?bank)");
static constexpr auto panama = ctll::fixed_string(R"(panama)");
static constexpr auto papua_new_guinea = ctll::fixed_string(R"(papua|new.?guinea)");
static constexpr auto paraguay = ctll::fixed_string(R"(paraguay)");
static constexpr auto parma = ctll::fixed_string(R"(parma)");
static constexpr auto peru = ctll::fixed_string(R"(peru)");
static constexpr auto philippines = ctll::fixed_string(R"(philippines)");
static constexpr auto piedmont_sardinia = ctll::fixed_string(R"(piedmont.sardinia)");
static constexpr auto poland = ctll::fixed_string(R"(poland)");
static constexpr auto portugal = ctll::fixed_string(R"(portugal)");
static constexpr auto prussia = ctll::fixed_string(R"(prussia)");
static constexpr auto qatar = ctll::fixed_string(R"(qatar)");
static constexpr auto republic_of_vietnam = ctll::fixed_string(R"((?!social).*republic.of.viet.?nam|south.viet.?nam|viet.?nam.south)");
static constexpr auto romania = ctll::fixed_string(R"(r(o|u|ou)mania)");
static constexpr auto russia = ctll::fixed_string(R"(\brussia|soviet.?union|u\.?s\.?s\.?r|socialist.?republics)");
static constexpr auto rwanda = ctll::fixed_string(R"(rwanda)");
static constexpr auto samoa = ctll::fixed_string(R"(^(?!.*amer).*samoa)");
static constexpr auto san_marino = ctll::fixed_string(R"(san.?marino)");
static constexpr auto sao_tome_principe = ctll::fixed_string(R"(\bs(a|ã)o.?tom(e|é))");
static constexpr auto sardinia = ctll::fixed_string(R"(^(?!.*piedmont)(?!.*italy).*\bsardinia)");
static constexpr auto saudi_arabia = ctll::fixed_string(R"(\bsa\w*.?arabia)");
static constexpr auto saxe_weimar_eisenach = ctll::fixed_string(R"(saxe.weimar.eisenach)");
static constexpr auto saxony = ctll::fixed_string(R"(saxony)");
static constexpr auto senegal = ctll::fixed_string(R"(senegal)");
static constexpr auto serbia = ctll::fixed_string(R"(^(?!.*monte).*serbia)");
static constexpr auto serbia_and_montenegro = ctll::fixed_string(R"(serbia.and.montenegro)");
static constexpr auto seychelles = ctll::fixed_string(R"(seychell)");
static constexpr auto sierra_leone = ctll::fixed_string(R"(sierra)");
static constexpr auto singapore = ctll::fixed_string(R"(singapore)");
static constexpr auto slovakia = ctll::fixed_string(R"(^(?!.*cze).*slovak)");
static constexpr auto slovenia = ctll::fixed_string(R"(slovenia)");
static constexpr auto solomon_islands = ctll::fixed_string(R"(solomon)");
static constexpr auto somalia = ctll::fixed_string(R"(somalia)");
static constexpr auto somaliland = ctll::fixed_string(R"(somaliland)");
static constexpr auto south_africa = ctll::fixed_string(R"(south.africa|s\\..?africa)");
static constexpr auto south_korea = ctll::fixed_string(R"(^(?!.*d.*p.*r)(?!.*democrat)(?!.*people)(?!.*north).*\bkorea(?!.*d.*p.*r))");
static constexpr auto south_sudan = ctll::fixed_string(R"(\bs\w*.?sudan)");
static constexpr auto spain = ctll::fixed_string(R"(spain)");
static constexpr auto sri_lanka = ctll::fixed_string(R"(sri.?lanka|ceylon)");
static constexpr auto st_kitts_nevis = ctll::fixed_string(R"(kitts|\bnevis)");
static constexpr auto st_lucia = ctll::fixed_string(R"(\blucia)");
static constexpr auto st_vincent_grenadines = ctll::fixed_string(R"(vincent)");
static constexpr auto sudan = ctll::fixed_string(R"(^(?!.*\bs(?!u)).*sudan)");
static constexpr auto suriname = ctll::fixed_string(R"(surinam|dutch.?guiana)");
static constexpr auto sweden = ctll::fixed_string(R"(sweden)");
static constexpr auto switzerland = ctll::fixed_string(R"(switz|swiss)");
static constexpr auto syria = ctll::fixed_string(R"(syria)");
static constexpr auto taiwan = ctll::fixed_string(R"(taiwan|taipei|formosa|^(?!.*peo)(?=.*rep).*china)");
static constexpr auto tajikistan = ctll::fixed_string(R"(tajik)");
static constexpr auto tanzania = ctll::fixed_string(R"(tanzania)");
static constexpr auto thailand = ctll::fixed_string(R"(thailand|\bsiam)");
static constexpr auto timor_leste = ctll::fixed_string(R"(^(?=.*leste).*timor|^(?=.*east).*timor)");
static constexpr auto togo = ctll::fixed_string(R"(togo)");
static constexpr auto tonga = ctll::fixed_string(R"(tonga)");
static constexpr auto trinidad_tobago = ctll::fixed_string(R"(trinidad|tobago)");
static constexpr auto tunisia = ctll::fixed_string(R"(tunisia)");
static constexpr auto turkey = ctll::fixed_string(R"(turkey)");
static constexpr auto turkmenistan = ctll::fixed_string(R"(turkmen)");
static constexpr auto tuscany = ctll::fixed_string(R"(tuscany)");
static constexpr auto tuvalu = ctll::fixed_string(R"(tuvalu)");
static constexpr auto two_sicilies = ctll::fixed_string(R"(two.?sicilies)");
static constexpr auto uganda = ctll::fixed_string(R"(uganda)");
static constexpr auto ukraine = ctll::fixed_string(R"(ukrain)");
static constexpr auto united_arab_emirates = ctll::fixed_string(R"(emirates|^u\.?a\.?e\.?$|united.?arab.?em)");
static constexpr auto united_kingdom = ctll::fixed_string(R"(united.?kingdom|britain|^u\.?k\.?$)");
static constexpr auto united_province_ca = ctll::fixed_string(R"(united.province.ca)");
static constexpr auto united_states = ctll::fixed_string(R"(united.?states\b(?!.*islands)|\bu\.?s\.?a\.?\b|^\s*u\.?s\.?\b(?!.*islands))");
static constexpr auto uruguay = ctll::fixed_string(R"(uruguay)");
static constexpr auto uzbekistan = ctll::fixed_string(R"(uzbek)");
static constexpr auto vanuatu = ctll::fixed_string(R"(vanuatu|new.?hebrides)");
static constexpr auto vatican_city = ctll::fixed_string(R"(holy.?see|vatican|papal.?st)");
static constexpr auto venezuela = ctll::fixed_string(R"(venezuela)");
static constexpr auto vietnam = ctll::fixed_string(R"(^(?!south)(?!republic).*viet.?nam(?!.*south)|socialist.republic.of.viet.?nam|north.viet.?nam|viet.?nam.north)");
static constexpr auto wuerttemburg = ctll::fixed_string(R"(w(ue|ü)rttemburg)");
static constexpr auto wurtemberg = ctll::fixed_string(R"(w.rtemberg)");
static constexpr auto yemen = ctll::fixed_string(R"(^(?!.*arab)(?!.*north)(?!.*sana)(?!.*peo)(?!.*dem)(?!.*south)(?!.*aden)(?!.*\bp\.?d\.?r).*yemen)");
static constexpr auto yemen_arab_republic = ctll::fixed_string(R"(^(?=.*arab).*yemen|^(?=.*north).*yemen|^(?=.*sana).*yemen)");
static constexpr auto yemen_peoples_republic = ctll::fixed_string(R"(^(?=.*peo).*yemen|^(?!.*rep)(?=.*dem).*yemen|^(?=.*south).*yemen|^(?=.*aden).*yemen|^(?=.*\bp\.?d\.?r).*yemen)");
static constexpr auto yugoslavia = ctll::fixed_string(R"(yugoslavia)");
static constexpr auto zambia = ctll::fixed_string(R"(zambia|northern.?rhodesia)");
static constexpr auto zanzibar = ctll::fixed_string(R"(zanzibar)");
static constexpr auto zimbabwe = ctll::fixed_string(R"(zimbabwe|^(?!.*northern).*rhodesia)");
// clang-format on


} // namespace tweetio::rgx::countries


namespace tweetio::rgx {

template <auto& pattern>
inline constexpr bool detect(const std::string_view s) {
  return ctre::search<pattern>(s);
}
static_assert(detect<countries::zimbabwe>("zimbabwe"));



} // namespace tweetio::rgx


#endif
