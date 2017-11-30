#include <iostream>
#include <string>

using namespace std;

class Player{
    private:
        int health;
        int attack;
        int defense;
        int max_health;

        int level;
        int xp;
    public:
        Player();
        Player(int h, int a, int d, string n, int lvl, int xp);
        int levelUp();
        int getHealth();
        int getAttack();
        int getDefense();
        int getXP();
        void setXP(int i);
        int getLevel();
        void setLevel(int i);
        void setHealth(int i);
        void setAttack(int i);
        void setDefense(int i);

        void attack_player(Player& p);
        void heal(int i);

        int temp = 0;
        string name;
};