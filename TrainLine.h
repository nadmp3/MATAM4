#ifndef MTM_TrainLine_H
#define MTM_TrainLine_H
#include <string>
#include <ostream>
#include "Line.h"
#include "mtm_ex4.h"
#include <iostream>
namespace MTM {
    using std::string;
    using std::ostream;
    using MTM::PointerCollections::List;
    using MTM::TrainType;
    
    class TrainLine : public Line {    
    public:
      TrainLine(int number,double price, int type);//create Train line
      
      bool operator<(const TrainLine& other) const;//compre operator <
           
      double calcPrice() const;//calculate price for ride
      string getDescription() const;//get description
      TrainType getType() const;
    private:
            
            
            
      int type;   //keep private type
    
    
    };    
}

std::ostream& operator<<(std::ostream& os, const MTM::TrainLine& train);  //print operator

#endif /* MTM_TrainLine_H */
