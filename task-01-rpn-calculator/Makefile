CXX = g++
CXXFLAGS = -std=c++14 -Wall
TARGET = rpn_calculator

SRCS = main.cpp RPNCalculator.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET) input.txt output.txt

.PHONY: all clean run