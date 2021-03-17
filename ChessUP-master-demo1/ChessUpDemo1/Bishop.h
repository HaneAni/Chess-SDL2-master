#ifndef PIECE_H
#include "Piece.h"
#endif // PIECE_H

#ifndef BISHOP_H
#define BISHOP_H

/**@brief Class of the Bishop that inherits from Piece
*
*Parameters: Bishop constructer and destructor, IsMovementPossible and functions inherited from Piece
*
*Description: This class defines the Bishop in a standard Chess game, here are
*defined some of the basic methods for manipulating an object of this class
*
*/

class Bishop : public Piece
{
public:
    Bishop(bool, int, int);
    ~Bishop();

    // Check all movement possible of Bishop
    bool isMovementPossible(int, int);

    using Piece::getName;
    using Piece::getColor;
    using Piece::getPositionX;
    using Piece::getPositionY;

};

#endif // BISHOP_H
