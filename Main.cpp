#include "Game.h"
#include "Judge.h"
#include "Player.h"
#include <vector>
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>

#define TOTAL_MATCHS 100 

int main() {
    int setupChoice;
    std::cout << "Select the setup (1 or 2): ";
    std::cin >> setupChoice;

    if (setupChoice != 1 && setupChoice != 2) {
        std::cout << "Invalid setup choice. Exiting." << std::endl;
        return 1;
    }
    
    Game aGame(setupChoice, 100);
    aGame.play();
    // aGame.print_result();
    
    return 0;
}





































































