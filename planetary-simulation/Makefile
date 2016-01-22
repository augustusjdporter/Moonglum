g++ -std=c++0x -O3 -o SolarSystem.out -I. SolarSystem.cpp ../body.cpp ../system.cpp

all: SolarSystem

SolarSystem: SolarSystem.o ../body.o ../system.o
	g++ -std=c++0x SolarSystem.o body.o system.o -o SolarSystem

SolarSystem.o: SolarSystem.cpp
	g++ -std=c++0x -c SolarSystem.cpp

../body.o: ../body.cpp
	g++ -std=c++0x -c ../body.cpp

../system.o: ../system.cpp
	g++ -std=c++0x -c ../system.cpp

clean:
	rm ../*.o *.o SolarSystem