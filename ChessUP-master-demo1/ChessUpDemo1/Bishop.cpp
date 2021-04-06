#include "Bishop.h"

Bishop::Bishop(bool isWhite, int x_position, int y_position)
{
    this->name_ = PieceName::BISHOP;
    this->isWhite_ = isWhite;
    this->x_Position_ = x_position;
    this->y_Position_ = y_position;
    isAlive_ = true;
    pieceValue_ = 30;
}

Bishop::~Bishop()
{
}

bool Bishop::isMovementPossible(int ix, int iy)
{
    // Piece has to be on the board and be alive
    if((ix >= 0 && ix < 8) && (iy >= 0 && iy < 8) && isAlive_)
    {
        int x_movement = abs(ix - x_Position_);
        int y_movement = abs(iy - y_Position_);

        // Check the movement diagonally and end position different from the initial one
        if(x_movement == y_movement && x_movement != 0)
            return true;
    }
    return false;
}
