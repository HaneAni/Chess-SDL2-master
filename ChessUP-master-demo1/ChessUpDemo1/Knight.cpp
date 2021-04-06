#include "Knight.h"

Knight::Knight(bool isWhite, int x_position, int y_position)
{
    this->name_ = PieceName::KNIGHT;
    this->isWhite_ = isWhite;
    this->x_Position_ = x_position;
    this->y_Position_ = y_position;
    isAlive_ = true;
    pieceValue_ = 30;
}

Knight::~Knight()
{
}

bool Knight::isMovementPossible(int ix, int iy)
{
    // Piece has to be on the board and be alive
    if((ix >= 0 && ix < 8) && (iy >= 0 && iy < 8) && isAlive_)
    {
        int x_movement = abs(ix - x_Position_);
        int y_movement = abs(iy - y_Position_);

        // Knight can move L-shaped
        if((x_movement == 1 && y_movement == 2) || (x_movement == 2 && y_movement == 1))
            return true;
    }
    return false;
}
