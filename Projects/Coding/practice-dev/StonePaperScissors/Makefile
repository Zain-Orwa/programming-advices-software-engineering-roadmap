CXX = clang++
CXXFLAGS = -Iinclude -std=c++17 -Wall

TARGET = stone_paper_scissors
SRCS = src/GameLogic.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^


clean: 
	rm -f $(OBJS) $(TARGET) 


.PHONY: all clean

