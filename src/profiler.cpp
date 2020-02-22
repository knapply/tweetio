#include <Rcpp.h>

using namespace Rcpp;


namespace face {

class Person {
  public:
    std::string name;
    
    Person() {};
    
    Rcpp::List to_r() {
      Rcpp::List out;
      out["name"] = this->name;
      
      return out;
    };
    

};

class Student : public Person {
  public:
    int grade;
    
    Rcpp::List to_r() {
      Rcpp::List out = Person::to_r();

      out["grade"] = this->grade;
      
      return out;
    };
  
};

}


// [[Rcpp::export]]
Rcpp::List inherit_test() {
  face::Student brendan;
  brendan.grade = 2;
  brendan.name = "brendan";
  
  return brendan.to_r();
}
