#macro

CC = g++
EXEC = mtm_schedule
OBJS =  mtm_ex4.o RegisteredStation.o LineStation.o Line.o\
Bus.o TrainLine.o Schedule.o main.o
FLAG = -ansi -g -pedantic-errors -Wall

#Main program

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(FLAG) $(OBJS) -o $@
	
#Objects 


mtm_ex4.o: mtm_ex4.cpp mtm_ex4.h
	$(CC) $(FLAG) -c $*.cpp  -o $@
	
RegisteredStation.o: RegisteredStation.cpp RegisteredStation.h
	$(CC) $(FLAG) -c $*.cpp  -o $@
  
LineStation.o: LineStation.cpp LineStation.h RegisteredStation.h
	$(CC) $(FLAG) -c $*.cpp  -o $@

Line.o: Line.cpp Line.h LineStation.h RegisteredStation.h mtm_ex4.h \
  List.h
	$(CC) $(FLAG) -c $*.cpp  -o $@

Bus.o: Bus.cpp Bus.h Line.h mtm_ex4.h LineStation.h RegisteredStation.h \
  List.h
	$(CC) $(FLAG) -c $*.cpp -o $@

TrainLine.o: TrainLine.cpp TrainLine.h Line.h mtm_ex4.h LineStation.h RegisteredStation.h  \
List.h
	$(CC) $(FLAG) -c $*.cpp -o $@

Schedule.o: Schedule.cpp Schedule.h Bus.h TrainLine.h Line.h mtm_ex4.h LineStation.h RegisteredStation.h \
  List.h Set.h
	$(CC) $(FLAG) -c $*.cpp -o $@


main.o: main.cpp Schedule.h mtm_ex4.h
	$(CC) $(FLAG) -c $*.cpp -o $@

#clean

clean:
	rm -f $(OBJS) $(EXEC)
	


