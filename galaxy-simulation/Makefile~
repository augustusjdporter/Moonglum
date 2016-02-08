all: GalaxySim

GalaxySim: main.o BlackHole.o Gas.o Star.o Galaxy.o DarkMatterHalo.o ../body.o ../system.o
	g++ -std=c++0x main.o BlackHole.o Gas.o Star.o Galaxy.o DarkMatterHalo.o ../body.o ../system.o -o GalaxySim

main.o: main.cpp
	g++ -std=c++0x -c main.cpp

../body.o: ../body.cpp
	g++ -std=c++0x -c ../body.cpp -o ../body.o

../system.o: ../system.cpp
	g++ -std=c++0x -c ../system.cpp -o ../system.o

BlackHole.o: BlackHole.cpp
	g++ -std=c++0x -c BlackHole.cpp

Star.o: Star.cpp
	g++ -std=c++0x -c Star.cpp

Gas.o: Gas.cpp
	g++ -std=c++0x -c Gas.cpp

Galaxy.o: Galaxy.cpp
	g++ -std=c++0x -c Galaxy.cpp

DarkMatterHalo.o: DarkMatterHalo.cpp
	g++ -std=c++0x -c DarkMatterHalo.cpp

clean:
	rm *.o ../*.o GalaxySim