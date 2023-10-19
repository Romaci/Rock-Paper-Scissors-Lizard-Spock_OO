#ifndef JUDGE_H
#define JUDGE_H
#include <vector>

//Player options
#define ROCK 0
#define PAPER 1
#define SCISSORS 2
#define LIZARD 3
#define SPOCK 4

class Judge {
public: 
    void evaluate(std::vector<int> &results, int playerAChoice, int playerBChoice);
};
#endif
