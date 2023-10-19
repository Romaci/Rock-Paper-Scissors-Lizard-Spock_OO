#include "Judge.h"



void Judge::evaluate(std::vector<int> &results, int playerAChoice, int playerBChoice){
    if (playerAChoice == playerBChoice) {
                results[2]++;
            } else {
                if ((playerAChoice == SCISSORS && (playerBChoice == PAPER || playerBChoice == LIZARD)) ||
                    (playerAChoice == ROCK && (playerBChoice == SCISSORS || playerBChoice == LIZARD)) ||
                    (playerAChoice == PAPER && (playerBChoice == ROCK || playerBChoice == SPOCK)) ||
                    (playerAChoice == LIZARD && (playerBChoice == SPOCK || playerBChoice == PAPER)) ||
                    (playerAChoice == SPOCK && (playerBChoice == SCISSORS || playerBChoice == ROCK))) {
                    results[0]++;
                } else {
                    results[1]++;
                }
            }
}