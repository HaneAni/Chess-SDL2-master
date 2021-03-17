#ifndef STATES_H_INCLUDED
#define STATES_H_INCLUDED

#include "Piece.h"
#include "GameState.h"

enum class PieceStatus {EMPTY, ENEMY, ALLY};
enum class GameResult {WHITE_WINS, BLACK_WINS, DRAW, NOT_END};
enum class Level {EASY, MEDIUM, HARD};

struct PieceValue
{
    int x_maxValue_ = -1;
    int y_maxValue_ = -1;
    int value_ = -20;
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

    // Vector that keeps the best moves of each piece:
    struct PieceValue whiteVallues_[16];
    struct PieceValue blackVallues_[16];
    // Vector of board pieces:
    Piece* whitePieces_[16];
    Piece* blackPieces_[16];

    PieceStatus isInTheWay(Piece* , int, int);
    PieceStatus isInTheSpot(Piece* , int, int);

    // Check for valid position
    bool isPositionValid(Piece* , int, int);
    // Move the piece or eat a enemy piece if possible
    bool isMove(Piece* , int, int);
    // Check is checkmate or not
    bool isCheck(bool, int, int);
    // Check when checkmate, is the King can move
    bool isCheckMate(bool);
    // Kill all pieces
    void killAllPieces();
    // Check the winner
    GameResult checkWhoWon();

    /// Chức năng phát chuyển động tốt nhất của màu sắc của mảnh được chuyển cho nó (theo Mức độ khó. Khó, trung bình, dễ)
    void playBestMove(bool, Level);
    /// Hàm cập nhật các chuyển động tốt nhất cho các miếng trắng và đen.
    void updateBestMoves(void);
    /// Function receives a piece and returns the best move for the piece. If an x, y -1 and -1 position is returned, the piece cannot move (there are no moves for it)
    PieceValue getPieceBestMove(Piece* );

    // Save game mode
    void saveGame(GameMode);
    // Load game mode
    void loadGame(GameMode);

    // Set piece in this position, return false if there was another piece or outside the board
    bool setPiece(Piece* , int, int);
    // Returns piece from x,y position (returns an empty if there is no piece in the position)
    Piece* getPiece(int, int);
    // Set the turn of the piece to be played (for the Load function)
    void setPieceTurn(bool);
    // Get the turn of the piece to be played
    bool getPieceTurn();

private:
    Piece* emptyPiece_ = new Piece();
    // Check black turn (false) or white turn (true)
    bool pieceTurn;

    // Set the pawn's enemy
    void setPawnEnemies(bool, Piece* , int, int);
    // Kill the enemy piece in position x,y
    void eatPiece(int, int);
    // Checks if pawn goes to the end of the chess board, it can transform to any piece except king
    void pawnTransform(Piece* piece);

};

#endif // STATES_H_INCLUDED
