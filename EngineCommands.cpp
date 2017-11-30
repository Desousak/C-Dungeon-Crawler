#include <iostream>
#include <string>
#include "EngineCommands.h"
#include <curses.h>
#include <fstream>

using namespace std;


void init(){
    //Initlize the screen
    initscr();
    cbreak();
}

void display(string input){
    //Use printw to print the desired string
    printw(input.c_str());
}

char* read_map(int& map_size, int& map_width, int& map_location, string map_name){
    ifstream myStream (map_name);

    char* map;

    if(myStream.is_open()){
        myStream >> map_size;
        myStream >> map_width;

        map = new char[map_size];
        myStream >> map;

        for(int x = 0; x < map_size; x++){
            if(map[x] == 'X'){
                map[x] = ' ';
            }
            if(map[x] == 'P'){
                map_location = x;
                map[x] = ' ';
            }
        }
    }
    myStream.close();


    if(map_name != "lvlselect.txt"){
        //Generate a random location for the next level stairs
        int x;
        srand(time(NULL));

        do{
            x = rand() % map_size;
        }while(map[x] == '|' || map[x] == '-' || map[x] == '+' || map[x] == 'D');
        map[x] = 'U';
    }
    return map;
}
