CXX := g++
CXXFLAGS := -std=c++17

all: wavefront edit_distance data_generation

wavefront: wavefront.cpp
	$(CXX) wavefront.cpp $(CXXFLAGS) -o wavefront

edit_distance: edit_distance.cpp
	$(CXX) edit_distance.cpp $(CXXFLAGS) -o edit_distance

data_generation: data_generation.cpp
	$(CXX) data_generation.cpp $(CXXFLAGS) -o data_generation

clean:
	rm -f wavefront edit_distance data_generation