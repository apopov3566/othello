#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
#include <array>
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    int getScore(Board *testBoard);
    int checkCorners(Board *board);
    int checkStables(Board *board);
    int checkStableSide(Board *board, Side side);
    bool stableCell(int x, int y, Board *board, bool stable[][8], bool checked[][8], Side side);
    int checkMobility(Board *board);
    Move *minimax(Board *b, int depth);
    int minimaxScore(Board *b, int depth);
    int getPosition(Board *testBoard);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    Board *board;
    Side playerSide;
    Side opponentSide;
};

#endif
