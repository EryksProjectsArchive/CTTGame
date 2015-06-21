CXX=g++
CXXFLAGS=-c -g -w -O2 -Wall -DDEBUG -std=c++0x -fpermissive -I./
LDFLAGS=-ldl
CXXSOURCE=$(wildcard *.cpp)
CXXSOURCE+=$(wildcard core/*.cpp)
CXXSOURCE+=$(wildcard math/*.cpp)
CXXSOURCE+=$(wildcard os/*.cpp)
CXXSOURCE+=$(wildcard os/linux/*.cpp)
CXXSOURCE+=$(wildcard sound/*.cpp)
CXXSOURCE+=$(wildcard sound/openal/*.cpp)
CXXSOURCE+=$(wildcard video/*.cpp)
CXXSOURCE+=$(wildcard video/renderer/*.cpp)
CXXSOURCE+=$(wildcard video/renderer/opengl/*.cpp)
CXXOBJECTS=$(CXXSOURCE:.cpp=.o)
EXECUTABLE=../../../bin/cttgame

all: $(CSOURCE) $(CXXSOURCE) $(EXECUTABLE)

$(EXECUTABLE): $(CXXOBJECTS) $(COBJECTS)
	$(CXX) $(CXXOBJECTS) $(LDFLAGS) -g -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@

.c.o:
	$(CC) $(CXXFLAGS) $< -o $@

clean:
	rm -Rf $(CXXOBJECTS) $(EXECUTABLE)
