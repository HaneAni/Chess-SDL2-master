#ifndef PIECE_H
#include "../include/Piece.h"
#endif // PIECE_H

#ifndef ROOK_H
#define ROOK_H

/**@brief Class of the Rook that inherits from Piece
*
*Parameters: Rook constructer and destructor, IsMovementPossible and functions inherited from Piece
*
*Description: This class defines the Rook in a standard Chess game, here are
*defined some of the basic methods for manipulating an object of this class
*
*/

class Rook : public Piece
{
public:
    Rook(bool, int, int);
    ~Rook();

    // Check all movement possible of Rook
    bool isMovementPossible(int, int);

    using Piece::getName;
    using Piece::getColor;
    using Piece::getPositionX;
    using Piece::getPositionY;

};

#endif // ROOK_H
