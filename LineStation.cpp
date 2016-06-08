#include "LineStation.h"
#include "mtm_ex4.h"
#include <string>
namespace MTM {
  //create LineStation station this data
  LineStation::LineStation(int Time_First_Station,RegisteredStation *ptr_Station) :
	  Time_First_Station(Time_First_Station),ptr_Station(ptr_Station) {}
  //copmre operator <
  bool LineStation::operator<(const LineStation& other) const 
                                          {return Time_First_Station < other.Time_First_Station;}
  //get time from first station
  int LineStation::getTime_First_Station() const { return Time_First_Station; }
  //get station
  RegisteredStation* LineStation::getptr_Station() const { return ptr_Station; }


}
//print opertor
std::ostream& operator<<(std::ostream& os, const MTM::LineStation& Linestation) {
    MTM::RegisteredStation* station_ptr = Linestation.getptr_Station();
    MTM::printLineStation(os,(*station_ptr).getStation_Name(),Linestation.getTime_First_Station());
    return os;
}
