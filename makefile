all:
	mkdir -p bin
	g++ src/traveling_graphs.cpp -o bin/traveling_graphs
	g++ src/shapes/*.cpp -o bin/shapes
	g++ src/third_latest_date/*.cpp -o bin/third_latest_date

clean:
	rm -rf bin
