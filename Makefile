build:
	g++ *.cpp -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -o main.exe

 run:
	./main

build-linux:
	g++ *.cpp -lSDL2 -o main