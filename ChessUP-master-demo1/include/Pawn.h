#ifndef PIECE_H
#include "../include/Piece.h"
#endif // PIECE_H

#ifndef PAWN_H
#define PAWN_H

/**@brief Class of the Pawn that inherits from Piece
*
*Parameters: Pawn constructer and destructor, IsMovementPossible and functions inherited from Piece
*
*Description: This class defines the Pawn in a standard Chess game, here are
*defined some of the basic methods for manipulating an object of this class
*
*/

class Pawn : public Piece
{
public:
    Pawn(bool, int, int);
    ~Pawn();

    // Check all movement possible of Pawn
    bool isMovementPossible(int, int);
    // Check pawn's enemy
    void setPawnEnemy(bool, bool);

    using Piece::getName;
    using Piece::getColor;
    using Piece::getPositionX;
    using Piece::getPositionY;

private:
    bool hasEnemyLeft = false;
    bool hasEnemyRight = false;

};

#endif // PAWN_H
