#ifndef PIECE_H
#include "Piece.h"
#endif // PIECE_H

#ifndef QUEEN_H
#define QUEEN_H

/**@brief Class of the Queen that inherits from Piece
*
*Parameters: Queen constructer and destructor, IsMovementPossible and functions inherited from Piece
*
*Description: This class defines the Queen in a standard Chess game, here are
*defined some of the basic methods for manipulating an object of this class
*
*/

class Queen : public Piece
{
public:
    Queen(bool, int, int);
    ~Queen();

    // Check all movement possible of Queen
    bool isMovementPossible(int, int);

    using Piece::getName;
    using Piece::getColor;
    using Piece::getPositionX;
    using Piece::getPositionY;

};

#endif // QUEEN_H
