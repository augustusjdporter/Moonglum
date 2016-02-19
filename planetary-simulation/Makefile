all: SolarSystem

SolarSystem: main.o ProtoplanetaryCloud.o ../body.o ../system.o ../Utilities/Utilities.o ../Universe.o
	g++ -std=c++0x -O3 main.o ../body.o ../system.o ../Utilities/Utilities.o ../Universe.o ProtoplanetaryCloud.o -o SolarSystem

main.o: main.cpp
	g++ -std=c++0x -O3 -c main.cpp

../body.o: ../body.cpp
	g++ -std=c++0x -O3 -c ../body.cpp -o ../body.o

../system.o: ../system.cpp
	g++ -std=c++0x -O3 -c ../system.cpp -o ../system.o

ProtoplanetaryCloud.o: ProtoplanetaryCloud.cpp
	g++ -std=c++0x -O3 -c ProtoplanetaryCloud.cpp

../Utilities/Utilities.o: ../Utilities/Utilities.cpp
	g++ -std=c++0x -O3 -c ../Utilities/Utilities.cpp -o ../Utilities/Utilities.o

../Universe.o: ../Universe.cpp
	g++ -std=c++0x -O3 -c ../Universe.cpp -o ../Universe.o

clean:
	rm *.o ../*.o SolarSystem