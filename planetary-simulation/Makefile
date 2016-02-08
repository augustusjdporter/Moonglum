all: SolarSystem

SolarSystem: main.o ProtoplanetaryCloud.o ../body.o ../system.o ../Utilities/Utilities.o
	g++ -std=c++0x -O3 main.o ../body.o ../system.o ../Utilities/Utilities.o ProtoplanetaryCloud.o -o SolarSystem

main.o: main.cpp
	g++ -std=c++0x -O3 -c main.cpp

../body.o: ../body.cpp
	g++ -std=c++0x -O3 -c ../body.cpp -o ../body.o

../system.o: ../system.cpp
	g++ -std=c++0x -O3 -c ../system.cpp -o ../system.o

ProtoplanetaryCloud.o: ProtoplanetaryCloud.cpp
	g++ -std=c++0x -O3 -c ProtoplanetaryCloud.cpp

Utilities.o: ../Utilities/Utilities.cpp
	g++ -std=c++0x -O3 -c ../Utilities/Utilities.cpp

clean:
	rm *.o ../*.o SolarSystem