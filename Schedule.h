#ifndef SCHEDULE_H_
#define SCHEDULE_H_
#include "mtm_ex4.h"
#include "Set.h"
#include "Line.h"
#include "RegisteredStation.h"
#include <limits>
#include <iostream>
namespace MTM {
    using std::ostream;
    using namespace MTM::PointerCollections;
    class Schedule {
    public:
      
      
      static const int END_INDEX; // must be defined in Schedule.cpp as -1
       /*
        * Schedule constructor
        *
        *  Parameters:
        *      tariffForBuses - the common tariff for Buses
        *      tariffForTrains - the common tariff for Trains
        *  Exceptions:
        *      InvalidPrice - if one of the tariffs is less than 0
        */
        Schedule(double tariffForBuses, double tariffForTrains);
        
        /*
        * registerStation
        *
        *  Description:
        *      Registers a new station in the stations pool
        *  Parameters:
        *      stationName - The name of the new station.
        *  Exceptions:
        *      StationAlreadyExist - If a station with this name already exists.
        */

        void registerStation(string stationName);

        /*
        * unregisterStation
        *
        *  Description:
        *      Unregisters an existing station from the stations pool 
        *      The function should fail if it appears in one or more lines.
        *  Parameters:
        *      stationName - The name of the station.
        *  Exceptions:
        *      StationDoesntExist - If a station with this name does not exist.
        *      StationIsUsed - If the station is used in at least one of the 
        *                      lines.
        *
        */
        void unregisterStation(string stationName);

        /*
        * addBusLine
        *
        *  Description:
        *      Adds new bus line to Schedule.
        *  Parameters:
        *      number - The number of the line,
        *      must be in the inclusive range [1 ... 9999].
        *      company - the company of the line
        *  Exceptions:
        *      InvalidLineNumber - If number is invalid.
        *      LineAlreadyExist - If a line with this number already exists.
        *
        */
        void addBusLine(int number, string company);

        /*
        * addTrainLine
        *
        *  Description:
        *      Adds new train line to Schedule.
        *  Parameters:
        *      number - The number of the line,
        *	        must be in the inclusive range [1 ... 9999].
        *      trainType - the type of the train
        *  Exceptions:
        *      InvalidLineNumber - If number is invalid.
        *      LineAlreadyExist - If a line with this number already exists.
        *
        */
        void addTrainLine(int number, TrainType trainType);

        /*
        * removeLine
        *
        *  Description:
        *      Removes an existing line from Schedule.
        *  Parameters:
        *      type - The type of the line.
        *      number - The number of the line,
        *		must be in the inclusive range [1 ... 9999].
        *  Exceptions:
        *      InvalidLineType - If type is invalid.
        *      InvalidLineNumber - If number is invalid.
        *      LineDoesntExist - If a line with thie number already exists.
        *
        */
        void removeLine(LineType type, int number);

        /*
        * addStationToLine
        *
        *  Description:
        *      Adds station at the end of a given line.
        *      The function throws Exception if the station doesn't exists in
        *      the pool
        *  Parameters:
        *      type - The type of the line.
        *      number - The number of the line,
        *		must be in the inclusive range [1 ... 9999].
        *      stationName - The name of the station.
        *      time - The time, in minutes, from the beginning of the journey 
        *	      to this station. The time must be bigger or equal to 
        *	      the time of the previous station.
        *  Exceptions:
        *      InvalidLineType - If type is invalid.
        *      InvalidLineNumber - If number is invalid.
        *      LineDoesntExist - If a line with this number does not exist.
        *      StationDoesntExist - If the station ins not registered in 
        *                           Schedule.
        *      StationAlreadyExist - If a station with this name already 
        *                            appears in the line.
        *      InvalidTime - If time is negative or smaller than time of the 
        *                    previous station.
        *
        */
        void addStationToLine(LineType type, int number, string stationName, 
                              int time);

        /*
        * removeStationFromLine
        *
        *  Description:
        *      Removes a station from a given line.
        *  Parameters:
        *      type - The type of the line.
        *      number - The number of the line,
        *	        must be in the inclusive range [1 ... 9999].
        *      index - The index of the station to be removed.
        *	       Can be any number in the inclusive range [-1 ... N-1],
        *	       where N is the number of stations in the line.
        *	       0 means the 1st station, 1 means the 2nd station, etc.
        *	       -1 means the last station.
        *              if index is omitted - the last station is removed
        *  Exceptions:
        *      InvalidLineType - If type is invalid.
        *      InvalidLineNumber - If number is invalid.
        *      LineDoesntExist - If the line doesn't exist.
        *      InvalidStationIndex - If index is invalid.
        */
        void removeStationFromLine(LineType type, int number, 
                                   int index = END_INDEX);

        /*
        * reportRegisteredStations
        *
        *  Description:
        *      Prints the names of the registered stations in Schedule, in 
        *      ascending lexicographic order.
        *  Parameters:
        *      outputStream - output stream to print the report
        *  Exceptions:
        *      NoStations - If there are no registered stations in Schedule.
        */
        void reportRegisteredStations(ostream& outputStream) const;

        /*
        * reportStationsForLine
        *
        *  Description:
        *       Prints the stations of a given line.
        *	First the line details are printed.
        *	For bus line - <line type> <line number> <company name>
        *		       <first station> <last station> <price>
        *	For train line - <line type> <line number> <train type>
        *					<first station> <last station> <price>
        *	Then the list of the stations will be printed, 
        *       in ascending time arrival.
        *  Parameters:
        *       outputStream - output stream to print the report
        *		number - The number of the line, integer in the inclusive range 
        *       [1 ... 9999].
        *  Exceptions:
        *       InvalidLineNumber - If number is invalid.
        *       LineDoesntExist - If the line doesn't exist.
        */
        void reportStationsForLine(ostream& outputStream, int number) const;

        /*
        * reportLines
        *
        *  Description:
        *       Prints the lines in Schedule. If type != MTM_LINE_ALL, then only 
        *	lines of the specific type will be printed.
        *	For bus line the following details will be printed:
        *	line type, line number, company name, first station, last 
        *       station and price.
        *	For train line the following details will be printed:
        *	line type, line number, train type, first station, last 
        *       station and price.
        *	For lines with no stations at all "N/A" will be printed as  
        *       first and last stations.
        *  Parameters:
        *       outputStream - output stream to print the report
        *       type - The type of the lines.
        *  Exceptions:
        *       NoLines - If there are no such lines in the Schedule.
        */
        void reportLines(ostream& outputStream,LineType type) const;

        /*
        * reportLinesBetweenStations
        *
        *  Description:
        *       Prints all the lines in Schedule, that pass in station "to" 
        *       AFTER they passed in station "from". Note that the order of the
        *       journey matters.
        *       If maximumPrice parameter is given and it is >= 0,
        *       only lines with price <= maximumPrice will be printed.
        *	If maximumPrice parameter is omitted, all the appropriate lines
        *       will be printed.
        *	The lines will be sorted in ascending price order. Lines with 
        *	equal price will be sorted in ascending line number order.
        *	For bus line the following details will be printed:
        *	line type, line number, company name, first station, last  
        *       station and price.
        *	For train line the following details will be printed:
        *	line type, line number, train type, first station, last 
        *       station and price.
        *	If "from" == "to", all the lines will be printed,
        *	as long as their price <= maximumPrice).
        *  Parameters:
        *       outputStream - output stream to print the report
        *       from - The origin station.
        *       to - The destination station.
        *       maximumPrice - The maximum price to the journey. maximumPrice 
        *					  must be bigger or equal zero.
        *  Exceptions:
        *       InvalidPrice - If maximumPrice < 0.
        *       StationDoesntExist - If any of the station aren't registered.
        *       NoLines - If there're no appropriate lines in Schedule.
        */
        void reportLinesBetweenStations(ostream& outputStream,
                                        string from, string to, 
                                        double maximumPrice = 
                                        std::numeric_limits<double>::max()) 
                                        const;
       /* void reportLinesBetweenStations(ostream& outputStream,
                                        string from, string to) 
                                        const;            */            
        double get_tariffForBuses() const;
        double get_tariffForTrains() const;
    private:
	double rateForBuses;
	double rateForTrains;
	Set<RegisteredStation> Station_List;
	Set<Line> Line_List;
    };
 
}
#endif /* SCHEDULE_H_ */
