#-----------------------------------
# Makefile
#
# author  : Tatenda Muvhu
# version : 07-05-17
#___________________________________

CC=g++
CCFLAGS=-std=c++11
LIBS=-I./lib

imageops: driver.o Image.o
	$(CC) $(CCFLAGS) driver.o Image.o -o imageops $(LIBS)

Image.o: ./lib/Image.cpp 
	$(CC) $(CCFLAGS) ./lib/Image.cpp -c $(LIBS)

driver.o:  driver.cpp
	$(CC) $(CCFLAGS) driver.cpp -c $(LIBS)

clean:
	rm -f *.o imageops test

test: Image.o unit_tests.o
	$(CC) $(CCFLAGS) Image.o unit_tests.o -o test $(LIBS)

unit_tests.o: unit_tests.cpp
	$(CC) $(CCFLAGS) unit_tests.cpp -c $(LIBS)



