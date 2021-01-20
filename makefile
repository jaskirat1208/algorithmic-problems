all:
	mkdir -p bin
	g++ -std=c++14 src/travelling_graphs/*.cpp -o bin/travelling_graphs
	g++ -std=c++14 src/shapes/*.cpp -o bin/shapes
	g++ -std=c++14 src/third_latest_date/*.cpp -o bin/third_latest_date
	doxygen docs/algorithmic-problems

clean:
	rm -rf bin
