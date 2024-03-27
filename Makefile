all:  
	g++ -Isrc/include -Lsrc/lib -o main main.cpp Game.cpp Spaceship.cpp Laser.cpp Dunas.cpp Block.cpp Alien.cpp -lmingw32 -lSDL2main -lSDL2