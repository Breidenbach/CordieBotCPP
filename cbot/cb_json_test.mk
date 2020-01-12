# Makefile to generate msgTest

CXX=g++
CXXFLAGS = -I ../lib -ljsoncpp -std=c++11

msgtest: msgtest.o \
            messages.o
	$(CXX) $(CXXFLAGS) -o msgTest \
                          msgtest.o \
                          messages.o

msgtest.o: msgtest.cpp \
            ../lib/messages.h
	$(CXX) $(CXXFLAGS) -c msgtest.cpp
            
messages.o: ../lib/messages.cpp \
                        ../lib/messages.h
	$(CXX) $(CXXFLAGS) -c ../lib/messages.cpp
	