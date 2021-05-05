#ifndef PIECE_H
#include "../include/Piece.h"
#endif // PIECE_H

#ifndef KNIGHT_H
#define KNIGHT_H

/**@brief Class of the Knight that inherits from Piece
*
*Parameters: Knight constructer and destructor, IsMovementPossible and functions inherited from Piece
*
*Description: This class defines the Knight in a standard Chess game, here are
*defined some of the basic methods for manipulating an object of this class
*
*/

class Knight : public Piece
{
public:
    Knight(bool, int, int);
    ~Knight();

    // Check all movement possible of knight
    bool isMovementPossible(int, int);

    using Piece::getName;
    using Piece::getColor;
    using Piece::getPositionX;
    using Piece::getPositionY;

};

#endif // KNIGHT_H
