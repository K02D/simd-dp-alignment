CXX := g++
CXXFLAGS := -std=c++17

all: wavefront edit_distance

wavefront: wavefront.cpp
	$(CXX) wavefront.cpp $(CXXFLAGS) -o wavefront

edit_distance: edit_distance.cpp
	$(CXX) edit_distance.cpp $(CXXFLAGS) -o edit_distance

clean:
	rm -f wavefront edit_distance