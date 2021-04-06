#include "King.h"

King::King(bool isWhite, int x_position, int y_position)
{
    this->name_ = PieceName::KING;
    this->isWhite_ = isWhite;
    this->x_Position_ = x_position;
    this->y_Position_ = y_position;
    isAlive_ = true;
    pieceValue_ = 10000;
}

King::~King()
{
}

bool King::isMovementPossible(int ix, int iy)
{
    // Piece has to be on the board and be alive
    if((ix >= 0 && ix < 8) && (iy >= 0 && iy < 8) && isAlive_)
    {
        int x_movement = abs(ix - x_Position_);
        int y_movement = abs(iy - y_Position_);

        // King can move only 1 index
        if(x_movement == 1 || y_movement == 1)
        {
            // Check the movement diagonally and end position different from the initial one
            if(x_movement == y_movement)
                return true;
            // Check the movement vertical or horizontal and end position different from the initial one
            if(x_movement == 0 || y_movement == 0)
                return true;
        }
    }
    return false;
}

bool King::kingCastling(int ix, int iy)
{
    // Piece has to be on the board and be alive
    if((ix >= 0 && ix < 8) && (iy >= 0 && iy < 8) && isAlive_)
    {
        if(x_Position_ == 4 && (ix == 2 || ix == 6) && (y_Position_ == iy))
            return true;
    }
    return false;
}
