#include "TrainLine.h"
#include "mtm_ex4.h"
namespace MTM {
    using MTM::PointerCollections::List;
    using MTM::PointerCollections::ListIterator;
    using MTM::LineType;
  //create Line with this data
  TrainLine::TrainLine(int number,double price, int type) :
	  Line(number,price,LINE_TRAIN),type(type) {}
  //copmre operator <
  bool TrainLine::operator<(const TrainLine& other) const 
                                          {return type < other.type;}
  
   double TrainLine::calcPrice() const //calc price
   {
          int Count_Station = Track.getSize();//get number of station
          if (type == 2)//if type is
          {
               return Price_Rate*Count_Station;
          }
          else 
            {
             if (type == 1)//if type is
              {
               return (Count_Station*Price_Rate*2);
              }
             else
               {
                  return (1+Price_Rate*2*Count_Station);//if type is
               }
            }
          return Count_Station;
   } 
  TrainType TrainLine::getType() const//get traintype
  {
  	MTM::TrainType tr_type = (MTM::TrainType)type;
  	return tr_type;
  }
  string TrainLine::getDescription() const //get description
  {
         if (type == 0)
          {
               return "direct";
          }
          else if (type == 1)
          {
               return "intercity";
          }
          else 
          {
               return "suburban";
          }
          return "all"; 
  }
   
}
//print opertor
using std::string;
std::ostream& operator<<(std::ostream& os, const MTM::TrainLine& train) {
    /*MTM::LineStation lstation = train.getptr_First_Station();
    string first_st = (lstation.getptr_Station()).getStation_Name();
    lstation = train.getptr_Last_Station();
    string last_st = (lstation.getptr_Station()).getStation_Name();
    MTM::printTrainLine(os,train.getLine_Number(),train.getType(),train.calcPrice(),first_st,last_st);*/
    return os;
}
