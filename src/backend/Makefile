CC = g++
CFLAGS = -lcurl

Test: Test.o Controller.o Model.o Connection.o MSCUrl.o MSCParser.o pugixml.o
	$(CC) -o $@ $^ $(CFLAGS)

Test.o: Controller.h Model.h
	$(CC) -c Test.cpp Controller.cpp Model.cpp

Controller.o: Controller.h Model.h MSCUrl.h 
	$(CC) -c Controller.cpp Model.cpp MSCUrl.cpp 

Model.o: Model.h Connection.h MSCParser.h
	$(CC) -c Model.cpp Connection.cpp MSCParser.cpp

Connection.o: Connection.h
	$(CC) -c Connection.cpp $(CFLAGS)

MSCParser.o: MSCParser.h pugixml-1.9/pugixml.hpp
	$(CC) -c MSCParser.cpp pugixml-1.9/pugixml.cpp

MSCUrl.o: MSCUrl.h pugixml-1.9/pugixml.hpp
	$(CC) -c MSCUrl.cpp pugixml-1.9/pugixml.cpp

pugixml.o: pugixml-1.9/pugixml.hpp
	$(CC) -c pugixml-1.9/pugixml.cpp

clean:
	@rm -f *.o
