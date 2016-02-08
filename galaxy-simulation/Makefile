all: GalaxySim

GalaxySim: main.o BlackHole.o Gas.o Star.o Galaxy.o DarkMatterHalo.o ../body.o ../system.o
	g++ -std=c++0x -O3 main.o BlackHole.o Gas.o Star.o Galaxy.o DarkMatterHalo.o ../body.o ../system.o -o GalaxySim

main.o: main.cpp
	g++ -std=c++0x -O3 -c main.cpp

../body.o: ../body.cpp
	g++ -std=c++0x -O3 -c ../body.cpp -o ../body.o

../system.o: ../system.cpp
	g++ -std=c++0x -O3 -c ../system.cpp -o ../system.o

BlackHole.o: BlackHole.cpp
	g++ -std=c++0x -O3 -c BlackHole.cpp

Star.o: Star.cpp
	g++ -std=c++0x -O3 -c Star.cpp

Gas.o: Gas.cpp
	g++ -std=c++0x -O3 -c Gas.cpp

Galaxy.o: Galaxy.cpp
	g++ -std=c++0x -O3 -c Galaxy.cpp

DarkMatterHalo.o: DarkMatterHalo.cpp
	g++ -std=c++0x -O3 -c DarkMatterHalo.cpp

clean:
	rm *.o ../*.o GalaxySim
