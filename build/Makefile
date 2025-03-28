CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = ../adventure
SRCDIR = ../scripts
SOURCES = $(wildcard $(SRCDIR)/*.cpp)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

rebuild: clean $(TARGET)

.PHONY: clean rebuild
