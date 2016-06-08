#include "Bus.h"
#include "mtm_ex4.h"
#include <string>
#include <ostream>
#include "LineStation.h"
namespace MTM {
    using MTM::PointerCollections::List;
    using MTM::PointerCollections::ListIterator;
    using MTM::LineType;
  
  Bus::Bus(int number,double price, string companyName) ://create Bus Line with data
	  Line(number,price,LINE_BUS),Company_Name(companyName) {}


  //copmre operator <
  bool Bus::operator<(const Bus& other) const 
                                          {return Company_Name < other.Company_Name;}
  
   double Bus::calcPrice() const //calc price
   {
          int  Time = 0;
          ListIterator<LineStation> iterator = Track.last();//point to last station 
          if (*iterator != NULL)//if pointer is not null
             {
                Time = (**iterator).getTime_First_Station();
             }
         
          return Time*Price_Rate;
   } 
   
  string Bus::getDescription() const {return Company_Name; }//get description
   
}
//print opertor
using std::string;
std::ostream& operator<<(std::ostream& os, const MTM::Bus& bus) {
    /*MTM::LineStation lstation = bus.getptr_First_Station();
    string first_st = (lstation.getptr_Station()).getStation_Name();
    lstation = bus.getptr_Last_Station();
    string last_st = (lstation.getptr_Station()).getStation_Name();
    MTM::printBusLine(os,bus.getLine_Number(),bus.getDescription(),bus.calcPrice(),first_st,last_st);*/
    return os;
}
 
