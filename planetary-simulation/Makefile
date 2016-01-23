all: SolarSystem

SolarSystem: SolarSystem.o ProtoplanetaryCloud.o ../body.o ../system.o
	g++ -std=c++0x SolarSystem.o body.o system.o  ProtoplanetaryCloud.o -o SolarSystem

SolarSystem.o: SolarSystem.cpp
	g++ -std=c++0x -c SolarSystem.cpp

../body.o: ../body.cpp
	g++ -std=c++0x -c ../body.cpp

../system.o: ../system.cpp
	g++ -std=c++0x -c ../system.cpp

ProtoplanetaryCloud.o: ProtoplanetaryCloud.cpp
	g++ -std=c++0x -c ProtoplanetaryCloud.cpp

clean:
	rm *.o SolarSystem