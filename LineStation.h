#ifndef MTM_LineStation_H
#define MTM_LineStation_H
#include <string>
#include <ostream>
#include "RegisteredStation.h"
namespace MTM {
    using std::string;
    using std::ostream;

    class LineStation {    
    public:
      LineStation(int Time_First_Station , RegisteredStation *ptr_Station);//create line station
      
      bool operator<(const LineStation& other) const;//compre operator <
      int getTime_First_Station() const;  //get time from first station
      RegisteredStation* getptr_Station() const;//get RegisteredStation
      
    private:
      int Time_First_Station;   //keep private time and pointer to RegisteredStation 
      RegisteredStation *ptr_Station;
    };    
}

std::ostream& operator<<(std::ostream& os, const MTM::LineStation& station);  //print operator

#endif /* MTM_LineStation_H */
