CC = g++ -std=c++11 

default: All Clean

All: Game EngineCommands Player Compile Clean
	./Game

Compile: Game.o EngineCommands.o Player.o 
	CC Game.o EngineCommands.o Player.o -o Game -lcurses

Game: Game.cpp EngineCommands.o
	CC -c Game.cpp -lcurses

EngineCommands: EngineCommands.cpp EngineCommands.h
	CC -c EngineCommands.cpp -lcurses

Player: Player.cpp Player.h
	CC -c Player.cpp

Clean:
	rm EngineCommands.o Game.o Player.o
