
#MakeFile to build and deploy the Sample US CENSUS Name Data using ajax
# For CSC3004 Software Development

# Put your user name below:
USER= guidotti1

CC= g++

#For Optimization
#CFLAGS= -O2
#For debugging
CFLAGS= -g

RM= /bin/rm -f

all: testClient xmlTesting figureOut

xmlParser.o: xmlParser.cpp xmlParser.h
	g++ -c xmlParser.cpp

testClient.o: testClient.cpp xmlParser.h 
	$(CC) -c testClient.cpp 

testClient: testClient.o xmlParser.o
	$(CC) testClient.o xmlParser.o -o testClient -L/usr/local/lib
	
xmlTesting.o: xmlTesting.cpp xmlParser.h
	$(CC) -c xmlTesting.cpp
	
xmlTesting: xmlTesting.o xmlParser.o
	$(CC) xmlTesting.o xmlParser.o -o xmlTesting -L/usr/local/lib
	
figuringOutXML.o: figuringOutXML.cpp xmlParser.h
	$(CC) -c figuringOutXML.cpp
	
figureOut: figuringOutXML.o xmlParser.o
	$(CC) figuringOutXML.o xmlParser.o -o figureOut -L/usr/local/lib

clean:
	rm -f *.o  testClient xmlTesting
