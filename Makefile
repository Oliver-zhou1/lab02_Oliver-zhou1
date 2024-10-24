CXX = g++

CXXFLAGS = -Wall -g

TARGET = test_intbst

SRCS = intbst.cpp test_intbst.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

intbst.o: intbst.cpp intbst.h
	$(CXX) $(CXXFLAGS) -c intbst.cpp

test_intbst.o: test_intbst.cpp intbst.h
	$(CXX) $(CXXFLAGS) -c test_intbst.cpp

clean:
	rm -f $(OBJS) $(TARGET)