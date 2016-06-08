#ifndef MTM_Line_H
#define MTM_Line_H
#include <string>
#include <ostream>
#include "LineStation.h"
#include <iostream>
#include "List.h"
#include "mtm_ex4.h"
namespace MTM {
    using std::string;
    using std::ostream;
    using MTM::PointerCollections::List;
    using MTM::LineType;
    using MTM::TrainType;
    class Line { 
          protected:
      int Line_Number;   //keep protected line number, list of LineStation, price and line type 
      List<LineStation> Track;
      double Price_Rate;
      LineType line_t; 
    public:
      Line(int Line_Number, double price, LineType linet);//create line
      virtual ~Line() {}//virtual destractor
      LineType getLineType () const;//get line type
      
      
      
      
      virtual TrainType getType() const {return TRAIN_DIRECT;}//virtual get train type
      
      
      
      
      
      bool operator<(const Line& other) const;//compre operator <
      int getLine_Number() const;  //get line number
      bool IsStationIn(string stationName);//check if station is in
      LineStation getptr_First_Station() const;//get finrst station
      LineStation getptr_Last_Station() const; //get last station
      void printStations(ostream& outputStream);
      
      //add station at the end of list
      void addStation(RegisteredStation *Station, int Time_From_First_Station);
      void removeStation(int index);//reomve station acording to index
      void removeAllStationFromLine();//remove all station from line
      bool check_track(string from, string to, double price);//check if track "from" "to"
      bool check_empty() const;
      int countStations () const;//count station
      virtual double calcPrice() const;//calculate price for ride
      virtual string getDescription() const;//return description of line
    
    };    
}

std::ostream& operator<<(std::ostream& os, const MTM::Line& station);  //print operator

#endif /* MTM_Line_H */
