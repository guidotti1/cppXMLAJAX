
#MakeFile to build and deploy the Sample US CENSUS Name Data using ajax
# For CSC3004 Software Development

# Put your user name below:
USER= skon

CC= g++

#For Optimization
#CFLAGS= -O2
#For debugging
CFLAGS= -g

RM= /bin/rm -f

all: books PutCGI PutHTML

xmlParser.o: xmlParser.cpp xmlParser.h
	g++ -c xmlParser.cpp

books.o: books.cpp 
	$(CC) -c $(CFLAGS) books.cpp

books: books.o xmlParser.o
	$(CC) books.o xmlParser.o -o books -L/usr/local/lib -lcgicc

testClient.o: testClient.cpp xmlParser.h 
	$(CC) -c testClient.cpp 

testClient: testClient.o xmlParser.o
	$(CC) testClient.o xmlParser.o -o testClient -L/usr/local/lib

PutCGI: books
	chmod 757 books
	cp books /usr/lib/cgi-bin/$(USER)_books.cgi 

	echo "Current contents of your cgi-bin directory: "
	ls -l /usr/lib/cgi-bin/

PutHTML:
	cp books.html /var/www/html/class/softdev/$(USER)

	echo "Current contents of your HTML directory: "
	ls -l /var/www/html/class/softdev/$(USER)

clean:
	rm -f *.o books testClient
