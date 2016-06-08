#include <string>
#include <ostream>
#include <iostream>
#include "mtm_ex4.h"
#include "Schedule.h"
#include "Line.h"
#include "Bus.h"
#include "TrainLine.h"
#define MAX_LINE 9999
namespace MTM {
  using MTM::LineType;
  using std::cout;
  class Track_Wanted {//will hold the wanted track from-to for the Schedule ReportBetweenStations
    	public:
    		string from_dest;
    		string to_dest;
    		double max_price;
    		Track_Wanted(string from, string to, double price) : from_dest(from),to_dest(to), max_price(price) {}
    };
  class StationPredicate : public MatchByKeyPredicate<RegisteredStation,string> {
    public://for finding stations in the set stations
        StationPredicate(string key) : MatchByKeyPredicate<RegisteredStation,string> (key) {}
        bool operator()(RegisteredStation* station) const { 
            assert(station != NULL);
            return station->getStation_Name() == getKey(); 
        }
   };
   class LineNumberPredicate : public MatchByKeyPredicate<Line,int> {
    public:// will help us find line by line number
        LineNumberPredicate(int key) : MatchByKeyPredicate<Line,int> (key) {}
        bool operator()(Line* line_ptr) const { 
            assert(line_ptr != NULL);
            return line_ptr->getLine_Number() == getKey(); 
        }
   };
   class LineMatchingPredicate : 
        public MatchByKeyPredicate<Line,LineType> {//for getting only trains or only buses
    public:
        LineMatchingPredicate(LineType key) : 
          MatchByKeyPredicate<Line,LineType> (key) {}
        bool operator()(Line* line) const { 
            assert(line != NULL);
            return line->getLineType() == getKey(); 
        }
    };
    class TrackMatchingPredicate : 
        public MatchByKeyPredicate<Line,Track_Wanted> {//find lines with track matching
    public:
        TrackMatchingPredicate(Track_Wanted key) : 
          MatchByKeyPredicate<Line,Track_Wanted> (key) {}
        bool operator()(Line* line) const { 
            assert(line != NULL);
            return line->check_track(getKey().from_dest,getKey().to_dest,getKey().max_price); 
        }
    };
   class LessThanByType : 
        public MTM::PointerCollections::BinaryPredicate<Line> {//sort by type and then by line number
         bool operator()(Line* line1, Line* line2) const {
                if (line1->getDescription() != line2->getDescription()){
                    return line1->getDescription() < line2->getDescription();
                }
                return line1->getLine_Number() < line2->getLine_Number();

            }
    };
    class LessThanByPrice : 
        public MTM::PointerCollections::BinaryPredicate<Line> {//sort by price and then by line number
         bool operator()(Line* line1, Line* line2) const {
                if (line1->calcPrice() != line2->calcPrice()){
                    return line1->calcPrice() < line2->calcPrice();
                }
                return line1->getLine_Number() < line2->getLine_Number();

            }
    };
    
  const int Schedule::END_INDEX(-1); //define end index
  Schedule::Schedule(double tariffForBuses, double tariffForTrains) {//constractor - get rate prices
	  if (tariffForBuses < 0 || tariffForTrains < 0) throw MTM::Exceptions::InvalidPrice();
      rateForBuses = tariffForBuses;
      rateForTrains = tariffForTrains;
   }
  void Schedule::registerStation(string stationName)  {//register station into set. if exist throw
       RegisteredStation station_temp(stationName);
       if (Station_List.isIn(&station_temp) == true) throw MTM::Exceptions::StationAlreadyExist();
       if (Station_List.add(new RegisteredStation(stationName)) == 0) throw MTM::Exceptions::StationAlreadyExist();
  }
  void Schedule::unregisterStation(string stationName) {//unregister station if in use throw and if doesnt exist also
       RegisteredStation station_temp(stationName);
       if (Station_List.isIn(&station_temp) != true) throw MTM::Exceptions::StationDoesntExist();
       RegisteredStation* station_ptr = Station_List.find(StationPredicate(station_temp.getStation_Name()));
       if (station_ptr->getLines_Use() > 0) throw MTM::Exceptions::StationIsUsed();
       Station_List.remove(&station_temp);
  }
  void Schedule::addBusLine(int number, string company)
  {//add bus line - new line - new bus with line number and company. throw if line number invalid or line exist
       Bus bus_temp(number,rateForBuses,company);
       if ((number > MAX_LINE) || (number < 1)) throw MTM::Exceptions::InvalidLineNumber();
       if (Line_List.isIn(&bus_temp) == true) throw MTM::Exceptions::LineAlreadyExist();
       Line_List.add(new Bus(number,rateForBuses,company));
  }	  
  
  void Schedule::addTrainLine(int number, TrainType trainType)
  {//add train line - new line - new train with line number and train type. throw if line number invalid or line exist
       TrainLine train_temp(number,rateForTrains,trainType);
       if ((number > MAX_LINE) || (number < 1)) throw MTM::Exceptions::InvalidLineNumber();
       if (Line_List.isIn(&train_temp) == true) throw MTM::Exceptions::LineAlreadyExist();
       Line_List.add(new TrainLine(number,rateForTrains,trainType));
  }
  
  void Schedule::removeLine(LineType type, int number)
  {// remove line by line type, if line type wrong throw, if line number wrong throw and if line doesnt exist
       if (type != LINE_BUS && type != LINE_TRAIN) throw MTM::Exceptions::InvalidLineType();
       if ((number > MAX_LINE) || (number < 1)) throw MTM::Exceptions::InvalidLineNumber();
       if (type == LINE_BUS) {// remove bus line
                Line* bus_ptr = Line_List.find(LineNumberPredicate(number)); //find line
                if (bus_ptr == NULL) throw MTM::Exceptions::LineDoesntExist();
                if ((*bus_ptr).getLineType() != LINE_BUS) throw MTM::Exceptions::LineDoesntExist();;
                (*bus_ptr).removeAllStationFromLine();
                Line_List.remove(bus_ptr);
       }
       if (type == LINE_TRAIN) {//remove train line
                Line* train_ptr = Line_List.find(LineNumberPredicate(number)); //find line
                if (train_ptr == NULL) throw MTM::Exceptions::LineDoesntExist();
                if ((*train_ptr).getLineType() != LINE_TRAIN) throw MTM::Exceptions::LineDoesntExist();;
                (*train_ptr).removeAllStationFromLine();
                Line_List.remove(train_ptr);
       }
  }
  void Schedule::addStationToLine(LineType type, int number, string stationName, int time) 
  {//add new station to line if if exist throw, if time invalid also throw
       if ((type != LINE_TRAIN) && (type != LINE_BUS)) throw MTM::Exceptions::InvalidLineType(); //invalif line type
       if ((number > MAX_LINE) || (number < 1)) throw MTM::Exceptions::InvalidLineNumber();
       Line* line_ptr = Line_List.find(LineNumberPredicate(number)); //find the line
       if (line_ptr == NULL) throw MTM::Exceptions::LineDoesntExist();
       if ((*line_ptr).getLineType() != type) throw MTM::Exceptions::LineDoesntExist(); //line doesnt exist
       RegisteredStation* station_ptr = Station_List.find(StationPredicate(stationName));
       if (station_ptr == NULL) throw MTM::Exceptions::StationDoesntExist();
       if ((*line_ptr).IsStationIn(stationName) == true) throw MTM::Exceptions::StationAlreadyExist();
       if ((*line_ptr).check_empty() == false) { //if the line isnt empty check stuff
       		LineStation line_station_ptr = (*line_ptr).getptr_Last_Station();
       		if ((line_station_ptr.getTime_First_Station() > time) || (time < 0)) throw MTM::Exceptions::InvalidTime();
       }
       (*station_ptr).incLines_Use(); //increase station use
       (*line_ptr).addStation(station_ptr,time); //add station
  }
  void Schedule::removeStationFromLine(LineType type, int number, int index) 
  {//remove station from line and decrease the use on the station
       if ((type != LINE_TRAIN) && (type != LINE_BUS)) throw MTM::Exceptions::InvalidLineType(); //line ype
       if ((number > MAX_LINE) || (number < 1)) throw MTM::Exceptions::InvalidLineNumber();
       Line* line_ptr = Line_List.find(LineNumberPredicate(number)); //find line
       if (line_ptr == NULL) throw MTM::Exceptions::LineDoesntExist();
       if ((*line_ptr).getLineType() != type) throw MTM::Exceptions::LineDoesntExist();
       if ((*line_ptr).countStations() == 0) throw MTM::Exceptions::InvalidStationIndex(); //if no stations
       else {
       		
       		(*line_ptr).removeStation(index); //remove the station
       }
  }
  void Schedule::reportRegisteredStations(ostream& outputStream) const
  {//print all registered stations
       int num_all = Station_List.getSize(); //get the size
       if (num_all == 0) throw MTM::Exceptions::NoStations(); //if there isnt stations
       Station_List.print(outputStream,num_all); //print all
  }
  void Schedule::reportStationsForLine(ostream& outputStream, int number) const
  {// print line with stations
  	if ((number > MAX_LINE) || (number < 1)) throw MTM::Exceptions::InvalidLineNumber();
        Line* line_ptr = Line_List.find(LineNumberPredicate(number)); //find line
        if (line_ptr == NULL) throw MTM::Exceptions::LineDoesntExist(); //if doesnt exist
        Set<Line>* tmp_set = Line_List.filter(LineNumberPredicate(number)); //new filter by line
        (*tmp_set).print(cout,LessThanByType()); //print line
        delete tmp_set; //delete the tmp filter
        (*line_ptr).printStations(outputStream); //print the stations
  }
  void Schedule::reportLines(ostream& outputStream,LineType type) const
  {//report lines by Line Type - print them out
	int num_all = Line_List.getSize(); //size of lines
	if (num_all == 0) throw MTM::Exceptions::NoLines(); //if there isnt lines
	if ((type == LINE_TRAIN) || (type == LINE_ALL)) { //if print train or all
		Set<Line>* tmp_set = Line_List.filter(LineMatchingPredicate(LINE_TRAIN)); //help filter
		(*tmp_set).print(cout,LessThanByType());
		delete tmp_set;
	}
	if ((type == LINE_BUS) || (type == LINE_ALL)) { //if print bus or all
		Set<Line>* tmp_set = Line_List.filter(LineMatchingPredicate(LINE_BUS)); //help filter
		(*tmp_set).print(cout,LessThanByType());
		delete tmp_set;
	}
  }
  void Schedule::reportLinesBetweenStations(ostream& outputStream,
                                        string from, string to, 
                                        double maximumPrice) 
                                        const

  {//print all lines with the wanted track and maximum price given
  	if (maximumPrice < 0) throw MTM::Exceptions::InvalidPrice(); //invalid price
  	RegisteredStation station_temp1(from); //help station
  	RegisteredStation station_temp2(to);
        if ((Station_List.isIn(&station_temp1) != true) || (Station_List.isIn(&station_temp2) != true)) throw MTM::Exceptions::StationDoesntExist(); //if doesnt exist in set stations
        double price_tmp; //help price
        if (maximumPrice == std::numeric_limits<double>::max()) {price_tmp = -1;} //print all lines no price
        else {price_tmp = maximumPrice;}
        Track_Wanted track_w(from,to,price_tmp); //help class to find wanted track
        Set<Line>* tmp_set = Line_List.filter(TrackMatchingPredicate(track_w)); //filter with lines by wanted track
        if ((*tmp_set).getSize() == 0) { //if no lines
        	delete tmp_set; //delete
        	throw MTM::Exceptions::NoLines();
        }
        (*tmp_set).print(cout,LessThanByPrice()); //print
        delete tmp_set; //delete the filter
     
  } 
}


