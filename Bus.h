#ifndef MTM_Bus_H
#define MTM_Bus_H
#include <string>
#include <ostream>
#include "Line.h"
#include <iostream>
namespace MTM {
    using std::string;
    using std::ostream;
    using MTM::PointerCollections::List;
    
    class Bus : public Line {    
    private:
      string Company_Name;   //keep private company name
    public:
      Bus(int number, double price, string companyName);//create Bus line

      bool operator<(const Bus& other) const;//compre operator <
           
      double calcPrice() const;//calculate price for ride
      string getDescription() const; //return description of Bus company name

    };    
}

std::ostream& operator<<(std::ostream& os, const MTM::Bus& bus);  //print operator

#endif /* MTM_Bus_H */
