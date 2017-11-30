#include <curses.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "EngineCommands.h"
/* Has 
void display(string input);
char* read_map(int& map_size, int& map_width, int& map_location, string map_name);
void init();
in it */
#include "Player.h"
/* Has 
 Player();
 Player(int h, int a, int d);
 int getHealth();
 int getAttack();
 int getDefense();
 void setHealth(int i);
 void setAttack(int i);
 void setDefense(int i);
 void attack(Player& p);
 void heal(int i);*/

using namespace std;



void battle(Player& p1, Player& p2){
    bool ran = false;

    if(p2.getHealth() != 0 && p1.getHealth() != 0){
    display(" 888888ba   .d888888  d888888P d888888P dP         88888888b    .d88888b  d888888P  .d888888   888888ba  d888888P\n 88    `8b d8'    88     88       88    88         88           88.     '    88    d8'    88   88    `8b    88   \na88aaaa8P' 88aaaaa88a    88       88    88        a88aaaa       `Y88888b.    88    88aaaaa88a a88aaaa8P'    88   \n 88   `8b. 88     88     88       88    88         88                 `8b    88    88     88   88   `8b.    88   \n 88    .88 88     88     88       88    88         88           d8'   .8P    88    88     88   88     88    88   \n 88888888P 88     88     dP       dP    88888888P  88888888P     Y88888P     dP    88     88   dP     dP    dP   \n");
    getch();
    clear();
   
    while(p1.getHealth() > 0 && p2.getHealth() > 0 && ran == false){
        display("The enemy has: " + to_string(p2.getHealth()) + " HP remaining.\n" + "Attack: " + to_string(p2.getAttack()) + "\n" + "Defense: " + to_string(p2.getDefense()) + "\n\n");
        display("The player has: " + to_string(p1.getHealth()) + " HP remaining.\n" + "Attack: " + to_string(p1.getAttack()) + "\n" + "Defense: " + to_string(p1.getDefense()) + "\n\n");
        display("Would you like to attack (z), defend (x), heal (c), or run (v)?\nDONT HIT ENTER, JUST PRESS THE LETTER\n\n\n\n\n\n\nThings to keep in mind:\n1)You can head an infinite amount of times, the healing factor however is random.\n2)Make sure you watch your health in relation to your enemy's damage");


        char i = getch();
        clear();
        bool correct_move = false; 

        if(p1.temp != 0){
            p1.setDefense(p1.temp);
            p1.temp = 0;
        }
        if(p2.temp != 0) {
            p2.setDefense(p2.temp);
            p2.temp = 0;
        }

        switch(i){
            default:
                display("Command not known, please enter a correct letter.\n");
                break;
            case('z'):
                p1.attack_player(p2);
                correct_move = true;
                break;
            case('x'):
                display("You braced for the next attack.\n");
                p1.temp = (p1.getDefense());
                p1.setDefense(p1.getDefense() + (rand() % p1.getDefense()));
                correct_move = true;
                break;
            case('c'):
                p1.heal(rand() % p1.getHealth());
                correct_move = true;
                break;
            case('v'):
                if(rand() % 4 == 0){
                    ran = true;
                    clear();
                    display("You ran away!\n");
                    getch();
                } else {
                    display("You couldn't ran away!\n");
                    correct_move = true;
                }
                break;
        }
        srand(time(NULL));
        int r = rand() % 2;

        if(correct_move == true){
        switch(r){
            default:
                display("ERR\n");
                break;
            case(0):
                p2.attack_player(p1);
                break;
            case(1):
                display("The enemy braced for the next attack.\n");
                p2.temp = (p2.getDefense());
                p2.setDefense(p2.getDefense() + (rand() % p2.getDefense()));
                break;
        }
        }
        getch();
        clear();
        
    } 
    }
      if(p1.getHealth() <= 0){
            display("You lose!");
            getch();
            endwin();
            exit(0);
        } else if(ran == false && p2.getXP() != 0){
            p1.setXP(p1.getXP() + p2.getXP());
            while(p1.getXP() >= (p1.getLevel() * 500)){
                p1.setXP(p1.getXP() - (p1.getLevel() * 1000));
                p1.setLevel(p1.getLevel() + 1);
                p1.levelUp();  
                display("Level UP!");
        }

    }
}


bool detect_keys(int& current_location,int size, int width, char* map, int current_level, Player &player){
    bool move_keys_pressed = false;
    //a = char value of the current key being pressed
    char a = getch();
    if(a != 27){
         //A if statement to see what key is pressed, 27 is the escape key
         if(a == 'w'){
            //If the desired location to move (UP) doesn't have a 'X', then move the location
            if(map[current_location - width] != '|' && map[current_location - width] != '-' && map[current_location - width] != '+'){
                if((current_location - width) > 0){
                    current_location -= width;
                }
            }
            move_keys_pressed = true;
        } else if (a == 's'){
            //If the desired location to move (DOWN) doesn't have a 'X', then move the location
            if(map[current_location + width] != '|' && map[current_location + width] != '-'&& map[current_location + width] != '+'){
                if((current_location + width) < size){
                    current_location += width;
                }
            }
            move_keys_pressed = true;
        } else if (a == 'a'){
            //If the desired location to move (LEFT) doesn't have a 'X', then move the location
            if(map[current_location - 1] != '+' && map[current_location - 1] != '|' && map[current_location - 1] != '-'){
                if((current_location - 1) > 0){
                    current_location -= 1;
                }
            }
            move_keys_pressed = true;  
        } else if (a == 'd'){
           //If the desired location to move (RIGHT) doesn't have a 'X', then move the location
           if(map[current_location + 1] != '+' && map[current_location + 1] != '|' && map[current_location + 1] != '-'){
               if((current_location + 1) < size){
                    current_location += 1;
               }
            }
            move_keys_pressed = true; 
        } 

        if(move_keys_pressed == true){
            srand(time(NULL));
            if(rand() % 6 == 0){
                Player enemy(current_level * (rand() % 80), ((rand() % player.getHealth()) /3)* current_level, (rand() % player.getAttack()), "Enemy", current_level, ((rand() % 5) + 1) * 100 *  current_level);
                clear();
                battle(player, enemy);
            }
        }
        return true;
        //Other code to execute here
    } else {
         //If the key is escape, return false which exits the game
        return false;
    }
}


bool map_logic(char* map, int location, int width, int size, int& level){
    bool exit_level = false;
    int side_text_count = 0;
    for(int x = 0; x < size; x++){
            string temp1 = "";
            string side_text[] = {"\tHints:" , "\tPress W,A,S,D to Move." , "\tEsc to Exit.","\tP is You." , "\tU goes up a floor (Its randomized each floor)." , "\tD goes down a floor (It isn't randomized)." ,"" ,"\tHave Fun!"};

            if(x == location){
                if(map[x] == 'U'){
                    level += 1;
                    exit_level = true;
                } else if(map[x] == 'D'){
                    level -= 1;
                    exit_level = true;
                } else if(isdigit(map[x])){
                    level = map[x] - '0';
                    exit_level = true;
                }
                temp1 = "P";
            } else {
                temp1 = string(1, map[x]);
            }

            
            string temp_to_display = "";
            if(x % width == 0 && x != 0){
                if(side_text_count < 8 && x >= (width * 3)){
                    temp_to_display =  side_text[side_text_count];
                    side_text_count += 1; 
                }
                temp_to_display += "\n" + temp1;
                display(temp_to_display);
            } else {
                temp_to_display = temp1;
                display(temp_to_display);
            }
              

        }

        if(exit_level == true){
            return true;
        } else {
            return false;
        }
}

int main(int argc, char** argv){
    init();

    string LOADING = "                                                                                                                                             \n                                                                   dddddddd                                                                  \nLLLLLLLLLLL                                                        d::::::d iiii                                                             \nL:::::::::L                                                        d::::::di::::i                                                            \nL:::::::::L                                                        d::::::d iiii                                                             \nLL:::::::LL                                                        d:::::d                                                                   \n  L:::::L                 ooooooooooo    aaaaaaaaaaaaa     ddddddddd:::::diiiiiinnnn  nnnnnnnn      ggggggggg   ggggg                        \n  L:::::L               oo:::::::::::oo  a::::::::::::a  dd::::::::::::::di:::::n:::nn::::::::nn   g:::::::::ggg::::g                        \n  L:::::L              o:::::::::::::::o aaaaaaaaa:::::ad::::::::::::::::d i::::n::::::::::::::nn g:::::::::::::::::g                        \n  L:::::L              o:::::ooooo:::::o          a::::d:::::::ddddd:::::d i::::nn:::::::::::::::g::::::ggggg::::::gg                        \n  L:::::L              o::::o     o::::o   aaaaaaa:::::d::::::d    d:::::d i::::i n:::::nnnn:::::g:::::g     g:::::g                         \n  L:::::L              o::::o     o::::o aa::::::::::::d:::::d     d:::::d i::::i n::::n    n::::g:::::g     g:::::g                         \n  L:::::L              o::::o     o::::oa::::aaaa::::::d:::::d     d:::::d i::::i n::::n    n::::g:::::g     g:::::g                         \n  L:::::L         LLLLLo::::o     o::::a::::a    a:::::d:::::d     d:::::d i::::i n::::n    n::::g::::::g    g:::::g                         \nLL:::::::LLLLLLLLL:::::o:::::ooooo:::::a::::a    a:::::d::::::ddddd::::::di::::::in::::n    n::::g:::::::ggggg:::::g                         \nL::::::::::::::::::::::o:::::::::::::::a:::::aaaa::::::ad:::::::::::::::::i::::::in::::n    n::::ng::::::::::::::::g  \nL::::::::::::::::::::::Loo:::::::::::oo a::::::::::aa:::ad:::::::::ddd::::i::::::in::::n    n::::n gg::::::::::::::g \nLLLLLLLLLLLLLLLLLLLLLLLL  ooooooooooo    aaaaaaaaaa  aaaa ddddddddd   ddddiiiiiiiinnnnnn    nnnnnn   gggggggg::::::g \n                                                                                                             g:::::g                         \n                                                                                                 gggggg      g:::::g                         \n                                                                                                 g:::::gg   gg:::::g                         \n                                                                                                  g::::::ggg:::::::g                         \n                                                                                                   gg:::::::::::::g                          \n                                                                                                     ggg::::::ggg                            \n                                                                                                        gggggg                               ";
    string LOADING1 = "                                                                                                                                             \n                                                                   dddddddd                                                                  \nLLLLLLLLLLL                                                        d::::::d iiii                                                             \nL:::::::::L                                                        d::::::di::::i                                                            \nL:::::::::L                                                        d::::::d iiii                                                             \nLL:::::::LL                                                        d:::::d                                                                   \n  L:::::L                 ooooooooooo    aaaaaaaaaaaaa     ddddddddd:::::diiiiiinnnn  nnnnnnnn      ggggggggg   ggggg                        \n  L:::::L               oo:::::::::::oo  a::::::::::::a  dd::::::::::::::di:::::n:::nn::::::::nn   g:::::::::ggg::::g                        \n  L:::::L              o:::::::::::::::o aaaaaaaaa:::::ad::::::::::::::::d i::::n::::::::::::::nn g:::::::::::::::::g                        \n  L:::::L              o:::::ooooo:::::o          a::::d:::::::ddddd:::::d i::::nn:::::::::::::::g::::::ggggg::::::gg                        \n  L:::::L              o::::o     o::::o   aaaaaaa:::::d::::::d    d:::::d i::::i n:::::nnnn:::::g:::::g     g:::::g                         \n  L:::::L              o::::o     o::::o aa::::::::::::d:::::d     d:::::d i::::i n::::n    n::::g:::::g     g:::::g                         \n  L:::::L              o::::o     o::::oa::::aaaa::::::d:::::d     d:::::d i::::i n::::n    n::::g:::::g     g:::::g                         \n  L:::::L         LLLLLo::::o     o::::a::::a    a:::::d:::::d     d:::::d i::::i n::::n    n::::g::::::g    g:::::g                         \nLL:::::::LLLLLLLLL:::::o:::::ooooo:::::a::::a    a:::::d::::::ddddd::::::di::::::in::::n    n::::g:::::::ggggg:::::g                         \nL::::::::::::::::::::::o:::::::::::::::a:::::aaaa::::::ad:::::::::::::::::i::::::in::::n    n::::ng::::::::::::::::g  ...... \nL::::::::::::::::::::::Loo:::::::::::oo a::::::::::aa:::ad:::::::::ddd::::i::::::in::::n    n::::n gg::::::::::::::g  .::::. \nLLLLLLLLLLLLLLLLLLLLLLLL  ooooooooooo    aaaaaaaaaa  aaaa ddddddddd   ddddiiiiiiiinnnnnn    nnnnnn   gggggggg::::::g  ......   \n                                                                                                             g:::::g                         \n                                                                                                 gggggg      g:::::g                         \n                                                                                                 g:::::gg   gg:::::g                         \n                                                                                                  g::::::ggg:::::::g                         \n                                                                                                   gg:::::::::::::g                          \n                                                                                                     ggg::::::ggg                            \n                                                                                                        gggggg                               ";
    string LOADING2 = "                                                                                                                                             \n                                                                   dddddddd                                                                  \nLLLLLLLLLLL                                                        d::::::d iiii                                                             \nL:::::::::L                                                        d::::::di::::i                                                            \nL:::::::::L                                                        d::::::d iiii                                                             \nLL:::::::LL                                                        d:::::d                                                                   \n  L:::::L                 ooooooooooo    aaaaaaaaaaaaa     ddddddddd:::::diiiiiinnnn  nnnnnnnn      ggggggggg   ggggg                        \n  L:::::L               oo:::::::::::oo  a::::::::::::a  dd::::::::::::::di:::::n:::nn::::::::nn   g:::::::::ggg::::g                        \n  L:::::L              o:::::::::::::::o aaaaaaaaa:::::ad::::::::::::::::d i::::n::::::::::::::nn g:::::::::::::::::g                        \n  L:::::L              o:::::ooooo:::::o          a::::d:::::::ddddd:::::d i::::nn:::::::::::::::g::::::ggggg::::::gg                        \n  L:::::L              o::::o     o::::o   aaaaaaa:::::d::::::d    d:::::d i::::i n:::::nnnn:::::g:::::g     g:::::g                         \n  L:::::L              o::::o     o::::o aa::::::::::::d:::::d     d:::::d i::::i n::::n    n::::g:::::g     g:::::g                         \n  L:::::L              o::::o     o::::oa::::aaaa::::::d:::::d     d:::::d i::::i n::::n    n::::g:::::g     g:::::g                         \n  L:::::L         LLLLLo::::o     o::::a::::a    a:::::d:::::d     d:::::d i::::i n::::n    n::::g::::::g    g:::::g                         \nLL:::::::LLLLLLLLL:::::o:::::ooooo:::::a::::a    a:::::d::::::ddddd::::::di::::::in::::n    n::::g:::::::ggggg:::::g                         \nL::::::::::::::::::::::o:::::::::::::::a:::::aaaa::::::ad:::::::::::::::::i::::::in::::n    n::::ng::::::::::::::::g  ......  ...... \nL::::::::::::::::::::::Loo:::::::::::oo a::::::::::aa:::ad:::::::::ddd::::i::::::in::::n    n::::n gg::::::::::::::g  .::::.  .::::.  \nLLLLLLLLLLLLLLLLLLLLLLLL  ooooooooooo    aaaaaaaaaa  aaaa ddddddddd   ddddiiiiiiiinnnnnn    nnnnnn   gggggggg::::::g  ......  ......  \n                                                                                                             g:::::g                         \n                                                                                                 gggggg      g:::::g                         \n                                                                                                 g:::::gg   gg:::::g                         \n                                                                                                  g::::::ggg:::::::g                         \n                                                                                                   gg:::::::::::::g                          \n                                                                                                     ggg::::::ggg                            \n                                                                                                        gggggg                               ";
    string LOADING3 = "                                                                                                                                             \n                                                                   dddddddd                                                                  \nLLLLLLLLLLL                                                        d::::::d iiii                                                             \nL:::::::::L                                                        d::::::di::::i                                                            \nL:::::::::L                                                        d::::::d iiii                                                             \nLL:::::::LL                                                        d:::::d                                                                   \n  L:::::L                 ooooooooooo    aaaaaaaaaaaaa     ddddddddd:::::diiiiiinnnn  nnnnnnnn      ggggggggg   ggggg                        \n  L:::::L               oo:::::::::::oo  a::::::::::::a  dd::::::::::::::di:::::n:::nn::::::::nn   g:::::::::ggg::::g                        \n  L:::::L              o:::::::::::::::o aaaaaaaaa:::::ad::::::::::::::::d i::::n::::::::::::::nn g:::::::::::::::::g                        \n  L:::::L              o:::::ooooo:::::o          a::::d:::::::ddddd:::::d i::::nn:::::::::::::::g::::::ggggg::::::gg                        \n  L:::::L              o::::o     o::::o   aaaaaaa:::::d::::::d    d:::::d i::::i n:::::nnnn:::::g:::::g     g:::::g                         \n  L:::::L              o::::o     o::::o aa::::::::::::d:::::d     d:::::d i::::i n::::n    n::::g:::::g     g:::::g                         \n  L:::::L              o::::o     o::::oa::::aaaa::::::d:::::d     d:::::d i::::i n::::n    n::::g:::::g     g:::::g                         \n  L:::::L         LLLLLo::::o     o::::a::::a    a:::::d:::::d     d:::::d i::::i n::::n    n::::g::::::g    g:::::g                         \nLL:::::::LLLLLLLLL:::::o:::::ooooo:::::a::::a    a:::::d::::::ddddd::::::di::::::in::::n    n::::g:::::::ggggg:::::g                         \nL::::::::::::::::::::::o:::::::::::::::a:::::aaaa::::::ad:::::::::::::::::i::::::in::::n    n::::ng::::::::::::::::g  ......  ......  ...... \nL::::::::::::::::::::::Loo:::::::::::oo a::::::::::aa:::ad:::::::::ddd::::i::::::in::::n    n::::n gg::::::::::::::g  .::::.  .::::.  .::::. \nLLLLLLLLLLLLLLLLLLLLLLLL  ooooooooooo    aaaaaaaaaa  aaaa ddddddddd   ddddiiiiiiiinnnnnn    nnnnnn   gggggggg::::::g  ......  ......  ...... \n                                                                                                             g:::::g                         \n                                                                                                 gggggg      g:::::g                         \n                                                                                                 g:::::gg   gg:::::g                         \n                                                                                                  g::::::ggg:::::::g                         \n                                                                                                   gg:::::::::::::g                          \n                                                                                                     ggg::::::ggg                            \n                                                                                                        gggggg                               ";

    for(int i = 0; i < 2; i++){
        display(LOADING);
        refresh();
        sleep(1);
        clear();
        display(LOADING1);
        refresh();
        sleep(1);
        clear();
        display(LOADING2);
        refresh();
        sleep(1);
        clear();
        display(LOADING3);
        refresh();
        sleep(1);
        clear();
    }



    int current_map_size = 0;
    int current_map_width = 0;
    int current_location = 0;

    //Title
    display(" _       __     __                             ______       \n| |     / ___  / _________  ____ ___  ___     /_  ______  _ \n| | /| / / _ \\/ / ___/ __ \\/ __ `__ \\/ _ \\     / / / __ \\(_) \n| |/ |/ /  __/ / /__/ /_/ / / / / / /  __/    / / / /_/ _   \n|__/|__/\\___/_/\\___/\\____/_/ /_/ /_/\\___/    /_/  \\____(_)  \n                                                            ");
    display("\n                                                                                                                                                                  \n8 8888888888     d888888o.       ,o888888o.           .8.          8 888888888o   8 8888888888             8888888 8888888888 8 8888        8 8 8888888888  \n8 8888         .`8888:' `88.    8888     `88.        .888.         8 8888    `88. 8 8888                         8 8888       8 8888        8 8 8888        \n8 8888         8.`8888.   Y8 ,8 8888       `8.      :88888.        8 8888     `88 8 8888                         8 8888       8 8888        8 8 8888        \n8 8888         `8.`8888.     88 8888               . `88888.       8 8888     ,88 8 8888                         8 8888       8 8888        8 8 8888        \n8 888888888888  `8.`8888.    88 8888              .8. `88888.      8 8888.   ,88' 8 888888888888                 8 8888       8 8888        8 8 888888888888\n8 8888           `8.`8888.   88 8888             .8`8. `88888.     8 888888888P'  8 8888                         8 8888       8 8888        8 8 8888        \n8 8888            `8.`8888.  88 8888            .8' `8. `88888.    8 8888         8 8888                         8 8888       8 8888888888888 8 8888        \n8 8888        8b   `8.`8888. `8 8888       .8' .8'   `8. `88888.   8 8888         8 8888                         8 8888       8 8888        8 8 8888        \n8 8888        `8b.  ;8.`8888    8888     ,88' .888888888. `88888.  8 8888         8 8888                         8 8888       8 8888        8 8 8888        \n8 888888888888 `Y8888P ,88P'     `8888888P'  .8'       `8. `88888. 8 8888         8 888888888888                 8 8888       8 8888        8 8 888888888888\n                                                                                                                                                            \n8 888888888o.      8 8888      88 b.             8     ,o888888o.    8 8888888888       ,o888888o.     b.             8                                     \n8 8888    `^888.   8 8888      88 888o.          8    8888     `88.  8 8888          . 8888     `88.   888o.          8                                     \n8 8888        `88. 8 8888      88 Y88888o.       8 ,8 8888       `8. 8 8888         ,8 8888       `8b  Y88888o.       8                                     \n8 8888         `88 8 8888      88 .`Y888888o.    8 88 8888           8 8888         88 8888        `8b .`Y888888o.    8                                     \n8 8888          88 8 8888      88 8o. `Y888888o. 8 88 8888           8 888888888888 88 8888         88 8o. `Y888888o. 8                                     \n8 8888          88 8 8888      88 8`Y8o. `Y88888o8 88 8888           8 8888         88 8888         88 8`Y8o. `Y88888o8                                     \n8 8888         ,88 8 8888      88 8   `Y8o. `Y8888 88 8888   8888888 8 8888         88 8888        ,8P 8   `Y8o. `Y8888                                     \n8 8888        ,88' ` 8888     ,8P 8      `Y8o. `Y8 `8 8888       .8' 8 8888         `8 8888       ,8P  8      `Y8o. `Y8                                     \n8 8888    ,o88P'     8888   ,d8P  8         `Y8o.`    8888     ,88'  8 8888          ` 8888     ,88'   8         `Y8o.`                                     \n8 888888888P'         `Y88888P'   8            `Yo     `8888888P'    8 888888888888     `8888888P'     8            `Yo        ");

    display("\n\n\nPress any key to continue");
    getch(); //Used to stop before the game starts

    Player* me = new Player();
    int current_level = 0;
    string levels[6] = {"lvlselect.txt","lvl1.txt","lvl2.txt", "lvl3.txt", "lvl4.txt", "lvl5.txt"};
    int max_levels = 5;


    if(argc > 1 ){
        if(argv[1][0] == '-' && argv[1][1] == 'l' && argc > 2){
            current_level = atoi(argv[2]);
        } else if(argv[1][0] == '-' && argv[1][1] == 'h' && argc > 2 ){
            me->setHealth(2);
            me->setAttack(2);
        } else if(argv[1][0] == '-' && argv[1][1] == 's'){
            current_level = max_levels;
        }
    }
    char* current_map = read_map(current_map_size, current_map_width, current_location, levels[current_level]);
    


    do{
        //Clear the screen
        clear();
        if(map_logic(current_map, current_location, current_map_width, current_map_size, current_level) == true){
            if(current_level <= max_levels){
                delete[] current_map;
                current_map = read_map(current_map_size, current_map_width, current_location, levels[current_level]);
            } else {
                clear();
                display("You encountered a bug. Error: Bad map index. Please report to the dev!");
                current_level = 0;
                getch();
            }
        }
    } while(detect_keys(current_location,current_map_size, current_map_width, current_map, current_level, *me) != false);
    endwin();
    return 0;
}