#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
     board = new Board();
     playerSide = side;
     if(playerSide == WHITE){
         opponentSide = BLACK;
     }
     else if(playerSide == BLACK){
         opponentSide = WHITE;
     }
}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete board;
}

int Player::getScore(Move *move){
    int score = 0;
    Board* testBoard = board->copy();
    testBoard->doMove(move, playerSide);

    int playerCount = testBoard->count(playerSide);
    int opponentCount = testBoard->count(opponentSide);

    //if(playerCount + opponentCount > 30){
    score += (playerCount - opponentCount);
    //}
    //else{
    //    score -= opponentCount;
    //}

    //score += this->checkStables(testBoard);
    score += 2*this->checkStables(testBoard);
    score += 3*this->checkCorners(testBoard);
    score += 2*this->checkMobility(testBoard);

    std::cerr << score << std::endl;
    return score;

}

int Player::checkCorners(Board *board){
    int score = 0;

    if(board->get(playerSide,0,0)){
        score += 1;
    }
    if(board->get(playerSide,0,7)){
        score += 1;
    }
    if(board->get(playerSide,7,0)){
        score += 1;
    }
    if(board->get(playerSide,7,7)){
        score += 1;
    }

    return score;
}

int Player::checkStables(Board *board){
    int count = 0;
    bool stable[8][8];
    bool checked[8][8];
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            checked[i][j] = false;
        }
    }
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(this->stableCell(i, j, board, stable, checked)){
                count++;
            }
        }
    }
    return count;
}

bool Player::stableCell(int x, int y, Board *board, bool stable[][8], bool checked[][8]){
    if(checked[x][y]){
        return stable[x][y];
    }
    checked[x][y] = true;
    if(!board->get(playerSide,x,y)){
        checked[x][y] = true;
        stable[x][y] = false;
        return false;
    }

    //check row stability
    bool lStable = true;
    bool rStable = true;
    for(int i = x+1; i < 8; i++){
        if(!stableCell(i, y, board, stable, checked)) rStable = false;
    }
    for(int i = x-1; i >= 0; i--){
        if(!stableCell(i, y, board, stable, checked)) lStable = false;
    }

    //check column stability
    bool uStable = true;
    bool dStable = true;
    for(int i = y+1; i < 8; i++){
        if(!stableCell(x, i, board, stable, checked)) uStable = false;
    }
    for(int i = y-1; i >= 0; i--){
        if(!stableCell(x, i, board, stable, checked)) dStable = false;
    }

    //check right-up/left-down diagonal stability
    bool urStable = true;
    bool dlStable = true;

    int tx = x+1;
    int ty = y+1;
    while(tx < 8 && ty < 8){
        if(!stableCell(tx, ty, board, stable, checked)) urStable = false;
        tx++;
        ty++;
    }

    tx = x-1;
    ty = y-1;
    while(tx > 0 && ty > 0){
        if(!stableCell(tx, ty, board, stable, checked)) dlStable = false;
        tx--;
        ty--;
    }

    //check right-down/left-up diagonal stability
    bool ulStable = true;
    bool drStable = true;

    tx = x+1;
    ty = y-1;
    while(tx < 8 && ty > 0){
        if(!stableCell(tx, ty, board, stable, checked)) drStable = false;
        tx++;
        ty--;
    }

    tx = x-1;
    ty = y+1;
    while(tx > 0 && ty < 8){
        if(!stableCell(tx, ty, board, stable, checked)) ulStable = false;
        tx--;
        ty++;
    }


    checked[x][y] = true;
    stable[x][y] = (lStable || rStable) && (uStable || dStable) &&
            (dlStable || urStable) && (ulStable || drStable);
    //std::cerr << stable[x][y] << std::endl;
    return stable[x][y];
}

int Player::checkMobility(Board *board)
{
  int diff = 0;
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      Move *move = new Move(i, j);
      if (board->checkMove(move, playerSide))
      {
        diff++;
      }
      if (board->checkMove(move, opponentSide))
      {
        diff--;
      }
    }
  }
  return diff;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */

     board->doMove(opponentsMove, opponentSide);

     Move *best = nullptr;
     int bestScore = -9999999;
     for (int i = 0; i < 8; i++) {
         for (int j = 0; j < 8; j++) {
             Move *move = new Move(i, j);
             if (board->checkMove(move, playerSide)){
                 int score = this->getScore(move);
                 if(score > bestScore){
                     bestScore = score;
                     best = move;
                 }
                 else{
                     delete move;
                 }
             }
         }
     }
     board->doMove(best, playerSide);
     return best;

}
