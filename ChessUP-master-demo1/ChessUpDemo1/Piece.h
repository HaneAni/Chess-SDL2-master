#ifndef PIECE_H
#define PIECE_H

#include <string>

enum class PieceName
{
    EMPTY,
    PAWN,
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING
};

/**@brief Class that defines a part
*
Description: This class defines a generic piece, with characteristics
common to all parts in which other parts must inherit their methods
and features such as position, color and name, among others
*
*/

class Piece
{
public:
    Piece();
    ~Piece();

    // Returns the name of the part (identified by an enum)
    PieceName getName() {return name;}
    // Returns true if it is white, false if it is black
    bool getColor() {return isWhite;}
    // Returns True for alive piece, False for dead piece
    bool getIsAlive() {return isAlive;}
    // Returns the X position
    int getPositionX() {return x_Position_;}
    // Returns the Y position
    int getPositionY() {return y_Position_;}

    // Sets the X and Y position of the piece
    void setPosition(int, int);
    // Set dead state
    void setDead();
    // Revive the piece
    void reviveFromDead();

    // Returns true if movement is possible, false otherwise.
    virtual bool isMovementPossible(int, int);
    // Pawn's private variable arrow
    virtual void setPawnEnemy(bool, bool);
    // King is allowed to make a special move, known as castling
    virtual bool kingCastling(int, int);

    bool isKingCastling[4];

protected:
    // Defines what the piece is
    PieceName name;
    // Defines what the value of piece
    int pieceValue_;

    // Defines the color of the piece. NOTE: White pieces that start the game and on bottom position
    bool isWhite;
    // Check piece alive or not
    bool isAlive;

    // Defines the position of the piece with X coordinate
    int x_Position_;
    // Defines the position of the piece with Y coordinate
    int y_Position_;

};

#endif // PIECE_H
