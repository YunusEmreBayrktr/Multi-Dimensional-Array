output: main.o Game.o
	g++ -std=c++11 main.o Game.o -o findtreasure 

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

Game.o: Game.cpp Game.h
	g++ -std=c++11 -c Game.cpp Game.h

clean:
	rm *.o