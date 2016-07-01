all: Moonglum

Moonglum: main.o planetary-simulation/ProtoplanetaryCloud.o galaxy-simulation/BlackHole.o galaxy-simulation/Gas.o galaxy-simulation/Star.o galaxy-simulation/Galaxy.o galaxy-simulation/DarkMatterHalo.o baseClasses/body.o baseClasses/system.o Utilities/Utilities.o Utilities/XmlReader.o baseClasses/Universe.o baseClasses/barnesHut/BarnesHutTree.o baseClasses/barnesHut/BarnesHutTree3D.o baseClasses/barnesHut/Quadrant.o baseClasses/barnesHut/Quadrant3D.o
	g++  -std=c++14 -m64 -O3 main.o baseClasses/body.o baseClasses/system.o Utilities/Utilities.o baseClasses/Universe.o planetary-simulation/ProtoplanetaryCloud.o galaxy-simulation/BlackHole.o galaxy-simulation/Gas.o galaxy-simulation/Star.o galaxy-simulation/Galaxy.o galaxy-simulation/DarkMatterHalo.o Utilities/XmlReader.o baseClasses/barnesHut/BarnesHutTree.o baseClasses/barnesHut/BarnesHutTree3D.o baseClasses/barnesHut/Quadrant.o baseClasses/barnesHut/Quadrant3D.o -lpthread -o Moonglum

main.o: main.cpp
	g++  -std=c++14 -m64 -O3 -c main.cpp -o main.o

baseClasses/body.o: baseClasses/body.cpp
	g++  -std=c++14 -m64 -O3 -c baseClasses/body.cpp -o baseClasses/body.o

baseClasses/system.o: baseClasses/system.cpp
	g++  -std=c++14 -m64 -O3 -c baseClasses/system.cpp -o baseClasses/system.o

planetary-simulation/ProtoplanetaryCloud.o: planetary-simulation/ProtoplanetaryCloud.cpp
	g++  -std=c++14 -m64 -O3 -c planetary-simulation/ProtoplanetaryCloud.cpp -o planetary-simulation/ProtoplanetaryCloud.o

Utilities/Utilities.o: Utilities/Utilities.cpp
	g++  -std=c++14 -m64 -O3 -c Utilities/Utilities.cpp -o Utilities/Utilities.o

baseClasses/Universe.o: baseClasses/Universe.cpp
	g++  -std=c++14 -m64 -O3 -c baseClasses/Universe.cpp -o baseClasses/Universe.o
	
baseClasses/barnesHut/BarnesHutTree.o: baseClasses/barnesHut/BarnesHutTree.cpp
	g++  -std=c++14 -m64 -O3 -c baseClasses/barnesHut/BarnesHutTree.cpp -o baseClasses/barnesHut/BarnesHutTree.o
	
baseClasses/barnesHut/BarnesHutTree3D.o: baseClasses/barnesHut/BarnesHutTree3D.cpp
	g++  -std=c++14 -m64 -O3 -c baseClasses/barnesHut/BarnesHutTree3D.cpp -o baseClasses/barnesHut/BarnesHutTree3D.o
	
baseClasses/barnesHut/Quadrant.o: baseClasses/barnesHut/Quadrant.cpp
	g++  -std=c++14 -m64 -O3 -c baseClasses/barnesHut/Quadrant.cpp -o baseClasses/barnesHut/Quadrant.o
	
baseClasses/barnesHut/Quadrant3D.o: baseClasses/barnesHut/Quadrant3D.cpp
	g++  -std=c++14 -m64 -O3 -c baseClasses/barnesHut/Quadrant3D.cpp -o baseClasses/barnesHut/Quadrant3D.o

galaxy-simulation/BlackHole.o: galaxy-simulation/BlackHole.cpp
	g++  -std=c++14 -m64 -O3 -c galaxy-simulation/BlackHole.cpp -o galaxy-simulation/BlackHole.o

galaxy-simulation/Star.o: galaxy-simulation/Star.cpp
	g++  -std=c++14 -m64 -O3 -c galaxy-simulation/Star.cpp -o galaxy-simulation/Star.o

galaxy-simulation/Gas.o: galaxy-simulation/Gas.cpp
	g++  -std=c++14 -m64 -O3 -c galaxy-simulation/Gas.cpp -o galaxy-simulation/Gas.o

galaxy-simulation/Galaxy.o: galaxy-simulation/Galaxy.cpp
	g++  -std=c++14 -m64 -O3 -c galaxy-simulation/Galaxy.cpp -o galaxy-simulation/Galaxy.o

galaxy-simulation/DarkMatterHalo.o: galaxy-simulation/DarkMatterHalo.cpp
	g++  -std=c++14 -m64 -O3 -c galaxy-simulation/DarkMatterHalo.cpp -o galaxy-simulation/DarkMatterHalo.o

Utilities/XmlReader.o: Utilities/XmlReader.cpp
	g++  -std=c++14 -m64 -O3 -c Utilities/XmlReader.cpp -o Utilities/XmlReader.o

clean:
	rm *.o baseClasses/barnesHut/*.o baseClasses/*.o planetary-simulation/*.o galaxy-simulation/*.o Utilities/*.o Moonglum