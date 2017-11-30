#include <iostream>
#include "Player.h"
#include "EngineCommands.h"
#include <string>

using namespace std;

Player::Player(){
    this->attack = 20;
    this->defense = 15;
    this->health = 120;
    this->max_health = this->health;
    this->name = "Player";

    this->level = 1;
    this->xp = 0;
}

Player::Player(int h, int a, int d, string n, int lvl, int xp){
    this->health = h;
    this->max_health = h;
    this->attack = a;
    this->defense = d;
    this->name = n;

    this->level = lvl;
    this->xp = xp;
}

int Player::levelUp(){
    this->level += 1;
    this->attack += (10 * this->level - 1);
    this->health += (50 * this->level - 1);
    this->max_health += (50 * this->level - 1);
    this->defense += (20 * this->level - 1);
}

int Player::getXP(){
    return this->xp;
}
void Player::setXP(int i){
    this->xp = i;
}

int Player::getLevel(){
    return this->level;
}
void Player::setLevel(int i){
    this->level = i;
}

int Player::getHealth(){
    return this->health;
}
int Player::getAttack(){
    return this->attack;
}
int Player::getDefense(){
    return this->defense;
}
void Player::setHealth(int i){
    this->health = i;
}
void Player::setAttack(int i){
    this->attack = i;
}
void Player::setDefense(int i){
    this->defense = i;
}

void Player::attack_player(Player& p){
    display(this->name + " attacked " + p.name + "\n");
    int t;
    t = this->attack - p.getDefense();

    if(t > 0){
        t = p.getHealth() - (this->attack - p.getDefense());
        p.setHealth(t);
    }
}
void Player::heal(int i){
    
    
    if(this->health + i <= this->max_health){
        this->health += i;
        display("The " + this->name + " healed for " + to_string(i) + " HP.\n");
    } else {
        this->health = this->max_health;
    }
}