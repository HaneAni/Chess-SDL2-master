#ifndef STATES_H_INCLUDED
#define STATES_H_INCLUDED

#include "Piece.h"
#include "GameState.h"

#include <algorithm>
#include <vector>

enum class PieceStatus {EMPTY, ENEMY, ALLY};
enum class GameResult {WHITE_WINS, BLACK_WINS, DRAW, NOT_END};

struct PieceValue
{
    int index = -1;
    int x_Value_ = -1;
    int y_Value_ = -1;
};

/**@brief Class that defines states for a part
*
* Description: In this class the mechanisms of the chess game are defined
* How to transform a pawn into a queen, eat a piece, validate it is a checkmate
* Check who won the game, save the game, load the game, validate who was the winner of the match
* Here basically everything is defined logic of the chess game, thus being one of the most important classes of this code
*
*/

class States
{
public:
    States();
    ~States();

    // Vector of board pieces:
    Piece* whitePieces_[16];
    Piece* blackPieces_[16];

    // Check king castling and undo
    bool kingCastling[4];
    bool undoKingCastling;

    PieceStatus isInTheWay(Piece*, int, int);
    PieceStatus isInTheSpot(Piece*, int, int);

    // Check for valid position
    bool isPositionValid(Piece* , int, int);
    // Move the piece or eat a enemy piece if possible
    bool isMove(Piece*, bool, int, int);
    // Undo movement
    void undoMove();
    // Check is checkmate or not
    bool isCheckmate(bool, int, int);
    // Checks if pawn goes to the end of the chess board, it can transform to queen
    bool isPawnTransform(Piece*, int, int);
    void pawnTransform(Piece*, int, int);
    // King is allowed to make a special move, known as castling
    bool isKingCastling(Piece*, int, int);
    // Kill all pieces
    void killAllPieces();
    // Check the winner
    GameResult checkWhoWon();


    // Vector that keeps the best moves of each piece:
    PieceValue whiteVallues_[16];
    PieceValue blackVallues_[16];

    // Return value of movement
    int valueMove();
    // Alpha beta algorithm
    int Alpha_Beta(int, bool, int, int);
    // Get the best move for computer
    PieceValue getNextMove(bool);
    // Play computer move
    void computerMove(bool);

    // Save game mode
    void saveGame(GameMode);
    // Load game mode
    void loadGame(GameMode);

    // Set piece in this position, return false if there was another piece or outside the board
    bool setPiece(Piece*, int, int);
    // Returns piece from x,y position (returns an empty if there is no piece in the position)
    Piece* getPiece(int, int);
    // Returns index of piece from x,y position (returns -1 if there is no piece in the position)
    int getPieceIndex(int, int);

private:
    Piece* emptyPiece_ = new Piece();

    // Set the pawn's enemy
    void setPawnEnemies(bool, Piece*, int, int);
    // Kill the enemy piece in position x,y
    void eatPiece(int, int);

};

#endif // STATES_H_INCLUDED
