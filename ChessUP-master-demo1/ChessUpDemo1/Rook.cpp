#include "Rook.h"

Rook::Rook(bool isWhite, int x_position, int y_position)
{
    this->name_ = PieceName::ROOK;
    this->isWhite_ = isWhite;
    this->x_Position_ = x_position;
    this->y_Position_ = y_position;
    isAlive_ = true;
    pieceValue_ = 50;
}

Rook::~Rook()
{
}

bool Rook::isMovementPossible(int ix, int iy)
{
    // Piece has to be on the board and be alive
    if((ix >= 0 && ix < 8) && (iy >= 0 && iy < 8) && isAlive_)
    {
        int x_movement = abs(ix - x_Position_);
        int y_movement = abs(iy - y_Position_);

        // Check the movement vertical or horizontal and end position different from the initial one
        if((x_movement == 0 || y_movement == 0) && x_movement != y_movement)
            return true;
    }
    return false;
}
