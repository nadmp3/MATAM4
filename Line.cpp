#include "Line.h"
#include "mtm_ex4.h"
namespace MTM {
    using MTM::PointerCollections::List;
    using MTM::PointerCollections::ListIterator;
    using MTM::LineType;
  //create Line with data
  Line::Line(int Line_number, double price, LineType linet) :
	  Line_Number(Line_number), Price_Rate(price), line_t(linet) {}
  LineType Line::getLineType () const {return line_t;}//get line type
  //copmre operator <
  bool Line::operator<(const Line& other) const 
                                          {return Line_Number < other.Line_Number;}
  //get line number
  int Line::getLine_Number() const { return Line_Number; }

  bool Line::IsStationIn(string stationName)//check if station is in Track
  {
       for(ListIterator<LineStation> iterator = Track.begin();
            iterator != Track.end(); ++iterator) {//loop throw track
                     RegisteredStation *station_temp = (**iterator).getptr_Station();
                     if ((*station_temp).getStation_Name() == stationName) return true; 
                                                           //check if station is match
            }
       return false;
  }
  LineStation Line::getptr_First_Station() const//get first station
   { 
       ListIterator<LineStation> iterator = Track.begin();
       return **iterator;
   }
   
  LineStation Line::getptr_Last_Station() const//get last station
   { 
       ListIterator<LineStation> iterator = Track.last();
       return **iterator;
   }
   //add new station at the end of list
  void Line::addStation(RegisteredStation *Station, int Time_From_First_Station)
   {
       LineStation temp(Time_From_First_Station, Station);
       Track.insert(Track.end(),new LineStation(Time_From_First_Station,Station) );
   }
   //remove station acording to index
  void Line::removeStation(int index)
   {
       int counter = index;
       if ((Track.getSize() <= index) || (index < -1)) throw MTM::Exceptions::InvalidStationIndex();
       if (index == -1)
       {
             counter = Track.getSize() -1;    
       }
       ListIterator<LineStation> iterator = Track.begin();//go to first station
       for (int i=0; i < counter; ++i)//go to index
       {
           ++iterator;
       }
       RegisteredStation *station_ptr = (**iterator).getptr_Station();
       (*station_ptr).decLines_Use();//decrease line use
       Track.remove(iterator);//remove station
   }//end of remove
   void Line::printStations(ostream& outputStream)//print  station
   {
        for(ListIterator<LineStation> iterator = Track.begin();
            iterator != Track.end(); ++iterator) {
                     RegisteredStation *station_temp = (**iterator).getptr_Station();
                     MTM::printLineStation(outputStream,(*station_temp).getStation_Name(),(**iterator).getTime_First_Station());
            }
   }
   int Line::countStations () const //count station in line
   {
   	return Track.getSize();
   }
   void Line::removeAllStationFromLine()//remove all station of line
   {
        ListIterator<LineStation> iterator = Track.begin();//go to first station
        RegisteredStation *station_ptr;//RegisteredStation pointer  
     while (iterator != Track.end())//while not the end
     {
           station_ptr = (**iterator).getptr_Station();
           (*station_ptr).decLines_Use();//decrese line use
           ++iterator;
     }
   }
   double Line::calcPrice() const {return 0;}
   
   bool Line::check_empty() const//check if line empty of station
   {
   	if (Track.getSize() == 0) return true;
   	return false;
   }
   string Line::getDescription() const {return "";}
   bool Line::check_track(string from, string to, double price) {
   	int i =0;//check if the line holds the track from-to and return true if it does
   	if (from == to) {i++;}
   	for(ListIterator<LineStation> iterator = Track.begin();
            iterator != Track.end(); ++iterator) {//through all the List
                     RegisteredStation *station_temp = (**iterator).getptr_Station(); //get station
                     if (i == 0) {
                     	if ((*station_temp).getStation_Name() == from) i++; //found station
                     }
                     else {
                     	if (i == 1) {
                     		if ((*station_temp).getStation_Name() == to) { //found station
                     			if (price < 0) {return true;}
                     			if ((*this).calcPrice() <= price) {return true;}
                     			else {return false;}
                     		}
                     	}
                     }
            }
        return false;
   }
}
//print opertor
using std::string;
using MTM::LineType;
std::ostream& operator<<(std::ostream& os, const MTM::Line& Line) {//print line
    string first_st = "\0";
    string last_st = "\0";
    MTM::RegisteredStation *station_ptr;
    if ((Line).check_empty() == false)  { //if there is stations
    	MTM::LineStation lstation = Line.getptr_First_Station();
    	station_ptr = lstation.getptr_Station();
    	first_st = (*station_ptr).getStation_Name();
    	lstation = Line.getptr_Last_Station();
    	station_ptr = lstation.getptr_Station();
    	last_st = (*station_ptr).getStation_Name();
    	if (Line.getLineType() == MTM::LINE_BUS) {
    		MTM::printBusLine(os,Line.getLine_Number(),Line.getDescription(),Line.calcPrice(),first_st,last_st);
    	}//print bus
    	else {
    		MTM::printTrainLine(os,Line.getLine_Number(),Line.getType(),Line.calcPrice(),first_st,last_st);
    	}//print train
    }
    else { //if the list of stations is empty in this line
    	if (Line.getLineType() == MTM::LINE_BUS) {
    		MTM::printBusLine(os,Line.getLine_Number(),Line.getDescription(),Line.calcPrice());//print bus
    	}
    	else {
    	MTM::printTrainLine(os,Line.getLine_Number(),Line.getType(),Line.calcPrice());//print train
    	}
    }
    return os;
}
 
