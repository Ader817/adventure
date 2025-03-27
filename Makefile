CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = adventure
SOURCES = $(wildcard *.cpp)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

rebuild: clean $(TARGET)

.PHONY: clean rebuild
