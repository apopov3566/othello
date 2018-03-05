#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    int getScore(Move *move);
    int checkCorners(Board *board);
    int checkStables(Board *board);
    bool stableCell(int x, int y, Board *board, bool stable[][8], bool checked[][8]);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    Board *board;
    Side playerSide;
    Side opponentSide;
};

#endif
