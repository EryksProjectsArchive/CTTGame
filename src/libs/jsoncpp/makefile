CXX=g++
CXXFLAGS=-c -g -w -I./include/ -static
LDFLAGS=-ldl -lpthread -static
SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=../libs/jsoncpp.a

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	ar rcs $@ $(OBJECTS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -Rf $(OBJECTS) $(EXECUTABLE)
