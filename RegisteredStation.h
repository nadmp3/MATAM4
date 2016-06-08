#ifndef MTM_RegisteredStation_H
#define MTM_RegisteredStation_H
#include <string>
#include <ostream>

namespace MTM {
    using std::string;
    using std::ostream;

    class RegisteredStation {
    public:
      RegisteredStation(string station_name);//create RegisteredStation
      
      bool operator<(const RegisteredStation& other) const;//copmre opertor
      int getLines_Use() const;//get line use
      string getStation_Name() const;//get station name
      void decLines_Use ();//dec line use
      void incLines_Use ();//inc line use

    private:
      int Line_Use;//keep private line use and station name
      string Station_Name;
    };    
}
//print operetor
std::ostream& operator<<(std::ostream& os, const MTM::RegisteredStation& station);

#endif /* MTM_RegisteredStation_H */
