
#include "Judge.h"
#include "Player.h"
#include <mutex>
#include <queue>
#include <vector>


class Game {
public:
    Game(int set_up, int total_matchs);
    void play();
    void print_result();
private: 
    int matchs;
    int set_up_id;

    // A two-dimensional vector to store player choices for multiple matches
    std::vector< std::vector<int> > players_choices;

    // A vector to store the results (0: Player A wins, 1: Player B wins, 2: Ties)
    std::vector<int> results;

    // A queue to keep track of matches that haven't been evaluated and are prepared for evaluation.
    std::queue<int> matchsToEvaluete;

    // Mutex for thread synchronization
    std::mutex mtx;

    // Counter for the total number of matches evaluated
    int total_matchs_evaluated;

    void activate_player(Player& aPlayer);
    void activate_judge(Judge& aJudge);
    void print_choices();
};

