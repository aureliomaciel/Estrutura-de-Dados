CXX = g++
CXXFLAGS = -Wall -g
TARGET = grafo
SRC = main.cpp grafo.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $(TARGET) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET)

run-bfs:
	./$(TARGET) bfs

run-dfs:
	./$(TARGET) dfs
