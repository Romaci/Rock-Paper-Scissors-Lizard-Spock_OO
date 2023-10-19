#include "Player.h"
#include <random>

Player::Player(int id){
 
    player_id = id;

}

int Player::getRandomChoice(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dist(0, 4);
    return dist(gen);
}
