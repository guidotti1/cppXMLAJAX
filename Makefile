
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

all: testClient 

xmlParser.o: xmlParser.cpp xmlParser.h
	g++ -c xmlParser.cpp

testClient.o: testClient.cpp xmlParser.h 
	$(CC) -c testClient.cpp 

testClient: testClient.o xmlParser.o
	$(CC) testClient.o xmlParser.o -o testClient -L/usr/local/lib

clean:
	rm -f *.o  testClient
