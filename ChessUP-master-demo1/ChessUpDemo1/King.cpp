#include "King.h"

King::King(bool isWhite, int x_position, int y_position)
{
    this->name = PieceName::KING;
    this->isWhite = isWhite;
    this->x_Position_ = x_position;
    this->y_Position_ = y_position;
    isAlive = true;
    pieceValue_ = 6;
}

King::~King()
{
}

bool King::isMovementPossible(int ix, int iy)
{
    // Piece has to be on the board and be alive
    if((ix >= 0 && ix < 8) && (iy >= 0 && iy < 8) && isAlive)
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
