server: main.o FileHandling.o HTML_Parser.o JsonToStringConverter.o routes.o
	g++ main.o ./src/FileHandling.o ./src/HTML_Parser.o ./src/JsonToStringConverter.o ./src/routes.o -o server -lpthread

main.o:
	echo "Compiling main.cpp"
	g++ -c main.cpp -o main.o

FileHandling.o:
	echo "Compiling FileHandling.cpp"
	g++ -c ./src/FileHandling.cpp -o ./src/FileHandling.o

HTML_Parser.o:
	echo "Compiling HTML_Parser.cpp"
	g++ -c ./src/HTML_Parser.cpp -o ./src/HTML_Parser.o

JsonToStringConverter.o:
	echo "Compiling JsonToStringConverter.cpp"
	g++ -c ./src/JsonToStringConverter.cpp -o ./src/JsonToStringConverter.o

routes.o:
	echo "Compiling routes.cpp"
	g++ -c ./src/routes.cpp -o ./src/routes.o

clean:
	rm -f ./src/*.o server
	