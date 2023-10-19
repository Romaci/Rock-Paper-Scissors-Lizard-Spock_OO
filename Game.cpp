#include "Game.h"
#include "Judge.h"
#include "Player.h"
#include <vector>
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>


#define PLAYERS 2 
#define PLAYER_A_ID 0
#define PLAYER_B_ID 1

//Player options
#define ROCK 0
#define PAPER 1
#define SCISSORS 2
#define LIZARD 3
#define SPOCK 4


Game::Game(int set_up, int total_matchs) {
    set_up_id =  set_up;
    matchs = total_matchs;
    total_matchs_evaluated = 0;

    // A two-dimensional vector to store player choices for multiple matches
    for (size_t i = 0; i < PLAYERS; i++)
    {
        std::vector<int> temp(matchs, -1);
        players_choices.push_back(temp);

    }

    // A vector to store the results (0: Player A wins, 1: Player B wins, 2: Ties)
    for (size_t i = 0; i < 3; i++)
    {
        results.push_back(0);
    }

    

}

void Game::print_choices() {
    for (int i = 0; i < matchs; i++) {
        int playerAChoice = players_choices[PLAYER_A_ID][i];
        int playerBChoice = players_choices[PLAYER_B_ID][i];
        std::cout << "Match " << i + 1 << ": Player A chose " << playerAChoice << ", Player B chose " << playerBChoice << std::endl;
    }
}

// Player actions
void Game::activate_player(Player& aPlayer) {
    for (int i = 0; i < 100; i++) {
        int player_choice;
        // Setup 1: Player A always chooses PAPER, Player B is random
        if(set_up_id == 1 && aPlayer.player_id == PLAYER_A_ID){
            player_choice = PAPER;
        } else {
            player_choice = aPlayer.getRandomChoice();
        }
        std::lock_guard<std::mutex> lock(mtx);
        
        players_choices[aPlayer.player_id][i] = player_choice;

        if (players_choices[0][i] != -1 && players_choices[1][i] != -1) {
            matchsToEvaluete.push(i);
        }
    }
}

// Player actions
void Game::activate_judge(Judge& aJudge) {
        
        while (total_matchs_evaluated < matchs) {
        std::lock_guard<std::mutex> lock(mtx);
        if (!matchsToEvaluete.empty()) {
            int pos = matchsToEvaluete.front();
            matchsToEvaluete.pop();
            int playerAChoice = players_choices[PLAYER_A_ID][pos];
            int playerBChoice = players_choices[PLAYER_B_ID][pos];
            aJudge.evaluate(results, playerAChoice, playerBChoice);
            total_matchs_evaluated++;
        }
    }
}


void Game::print_result(){
        // Display the results of the game
    std::cout << "Player A wins " << results[0] << " of " << results[2] + results[1] + results[0] << " games" << std::endl;
    std::cout << "Player B wins " << results[1] << " of " << results[2] + results[1] + results[0] << " games" << std::endl;
    std::cout << "Tie: " << results[2] << " of " << results[2] + results[1] + results[0] << " games" << std::endl;
   
    if (results[0] > results[1]) {
        std::cout << "Winner is: Player A" << " (" << results[0] << " to " << results[1] << " wins)" << std::endl;
    } else if (results[1] > results[0]) {
        std::cout << "Winner is: Player B" << " (" << results[1] << " to " << results[0] << " wins)" << std::endl;
    } else {
        std::cout << "It's a tie! No clear winner." << std::endl;
    }

}
void Game::play(){
    // A queue to keep track of matches that haven't been evaluated and are prepared for evaluation.
    
    Player playerA(PLAYER_A_ID);
    Player playerB(PLAYER_B_ID);

    Judge judge1;
    Judge judge2;
    Judge judge3;
    
    std::thread threadPlayerA(&Game::activate_player, this, std::ref(playerA));
    std::thread threadPlayerB(&Game::activate_player, this, std::ref(playerB));
    std::thread threadJudge1(&Game::activate_judge, this, std::ref(judge1));
    std::thread threadJudge2(&Game::activate_judge, this, std::ref(judge2));
    std::thread threadJudge3(&Game::activate_judge, this, std::ref(judge3));

    threadPlayerA.join();
    threadPlayerB.join();

    threadJudge1.join();
    threadJudge2.join();
    threadJudge3.join();

    print_result();



};