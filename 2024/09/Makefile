CXX=g++
FILE=example.txt

default: pt1.cpp
	@echo "Selected file: ${FILE}"
	$(CXX) pt1.cpp -o pt1
	./pt1 $(FILE) -d

1: pt1.cpp
	$(CXX) pt1.cpp -o pt1
	./pt1 $(FILE)

2: pt2.cpp
	$(CXX) pt2.cpp -o pt2
	./pt2 $(FILE)

2g: pt2.cpp
	$(CXX) pt2.cpp -o pt2 -g
