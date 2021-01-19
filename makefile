all:
	mkdir -p bin
	g++ src/travelling_graphs/*.cpp -o bin/travelling_graphs
	g++ src/shapes/*.cpp -o bin/shapes
	g++ src/third_latest_date/*.cpp -o bin/third_latest_date

clean:
	rm -rf bin
