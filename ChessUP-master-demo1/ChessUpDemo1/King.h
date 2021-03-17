#ifndef PIECE_H
#include "Piece.h"
#endif // PIECE_H

#ifndef KING_H
#define KING_H

/**@brief Class of the King that inherits from Piece
*
*Parameters: King constructer and destructor, IsMovementPossible and functions inherited from Piece
*
*Description: This class defines the King in a standard Chess game, here are
*defined some of the basic methods for manipulating an object of this class
*
*/

class King : public Piece
{
public:
    King(bool, int, int);
    ~King();

    // Check all movement possible of king
    bool isMovementPossible(int, int);

    using Piece::getName;
    using Piece::getColor;
    using Piece::getPositionX;
    using Piece::getPositionY;

};

#endif // KING_H
