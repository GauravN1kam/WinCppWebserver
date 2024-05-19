server: main.o FileHandling.o HTML_Parser.o JsonToStringConverter.o routes.o
	g++ main.o FileHandling.o HTML_Parser.o JsonToStringConverter.o routes.o -o server -lpthread

main.o:
	echo "Compiling main.cpp"
	g++ -c main.cpp -o main.o

FileHandling.o:
	echo "Compiling FileHandling.cpp"
	g++ -c FileHandling.cpp -o FileHandling.o

HTML_Parser.o:
	echo "Compiling HTML_Parser.cpp"
	g++ -c HTML_Parser.cpp -o HTML_Parser.o

JsonToStringConverter.o:
	echo "Compiling JsonToStringConverter.cpp"
	g++ -c JsonToStringConverter.cpp -o JsonToStringConverter.o

routes.o:
	echo "Compiling routes.cpp"
	g++ -c routes.cpp -o routes.o

clean:
	rm -f *.o server
	