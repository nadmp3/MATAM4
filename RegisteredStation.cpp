#include "RegisteredStation.h"
#include "mtm_ex4.h"
namespace MTM {
  //create RegisteredStation with this data
  RegisteredStation::RegisteredStation(string station_name) :
	  Line_Use(0),Station_Name(station_name) {}
  //compre opertor <
  bool RegisteredStation::operator<(const RegisteredStation& other) const 
                                          { return Station_Name < other.Station_Name; }
  //get line use
  int RegisteredStation::getLines_Use() const { return Line_Use; }
  //get station name
  string RegisteredStation::getStation_Name() const { return Station_Name; }
  //dec line use
  void RegisteredStation::decLines_Use() {Line_Use--;}
  //inc line use
  void RegisteredStation::incLines_Use() {Line_Use++;}

}
//print opertor
std::ostream& operator<<(std::ostream& os, const MTM::RegisteredStation& station) {
    MTM::printStationName(os,station.getStation_Name());
    return os;
}
