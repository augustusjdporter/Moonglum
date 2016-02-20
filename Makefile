all: NBodySims

NBodySims: main.o planetary-simulation/ProtoplanetaryCloud.o galaxy-simulation/BlackHole.o galaxy-simulation/Gas.o galaxy-simulation/Star.o galaxy-simulation/Galaxy.o galaxy-simulation/DarkMatterHalo.o body.o system.o Utilities/Utilities.o Utilities/XmlReader.o Universe.o
	g++ -std=c++0x -O3 main.o body.o system.o Utilities/Utilities.o Universe.o planetary-simulation/ProtoplanetaryCloud.o galaxy-simulation/BlackHole.o galaxy-simulation/Gas.o galaxy-simulation/Star.o galaxy-simulation/Galaxy.o galaxy-simulation/DarkMatterHalo.o Utilities/XmlReader.o -o NBodySims

main.o: main.cpp
	g++ -std=c++0x -O3 -c main.cpp

body.o: body.cpp
	g++ -std=c++0x -O3 -c body.cpp -o body.o

system.o: system.cpp
	g++ -std=c++0x -O3 -c system.cpp -o system.o

planetary-simulation/ProtoplanetaryCloud.o: planetary-simulation/ProtoplanetaryCloud.cpp
	g++ -std=c++0x -O3 -c planetary-simulation/ProtoplanetaryCloud.cpp -o planetary-simulation/ProtoplanetaryCloud.o

Utilities/Utilities.o: Utilities/Utilities.cpp
	g++ -std=c++0x -O3 -c Utilities/Utilities.cpp -o Utilities/Utilities.o

Universe.o: Universe.cpp
	g++ -std=c++0x -O3 -c Universe.cpp -o Universe.o

galaxy-simulation/BlackHole.o: galaxy-simulation/BlackHole.cpp
	g++ -std=c++0x -O3 -c galaxy-simulation/BlackHole.cpp -o galaxy-simulation/BlackHole.o

galaxy-simulation/Star.o: galaxy-simulation/Star.cpp
	g++ -std=c++0x -O3 -c galaxy-simulation/Star.cpp -o galaxy-simulation/Star.o

galaxy-simulation/Gas.o: galaxy-simulation/Gas.cpp
	g++ -std=c++0x -O3 -c galaxy-simulation/Gas.cpp -o galaxy-simulation/Gas.o

galaxy-simulation/Galaxy.o: galaxy-simulation/Galaxy.cpp
	g++ -std=c++0x -O3 -c galaxy-simulation/Galaxy.cpp -o galaxy-simulation/Galaxy.o

galaxy-simulation/DarkMatterHalo.o: galaxy-simulation/DarkMatterHalo.cpp
	g++ -std=c++0x -O3 -c galaxy-simulation/DarkMatterHalo.cpp -o galaxy-simulation/DarkMatterHalo.o

Utilities/XmlReader.o: Utilities/XmlReader.cpp
	g++ -std=c++0x -O3 -c Utilities/XmlReader.cpp -o Utilities/XmlReader.o

clean:
	rm *.o planetary-simulation/*.o galaxy-simulation/*.o Utilities/*.o NBodySims