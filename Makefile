CXX=g++
CXXFLAGS=-Wall -std=c++20 -O2
SRC=main.cpp grep.cpp
HEADER=grep.hpp
OUT=grep

$(OUT): $(SRC) $(HEADER)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)
clean: $(OUT)
	rm $(OUT)
