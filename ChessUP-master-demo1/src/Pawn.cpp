#include "../include/Pawn.h"

Pawn::Pawn(bool isWhite, int x_position, int y_position)
{
    this->name_ = PieceName::PAWN;
    this->isWhite_ = isWhite;
    this->x_Position_ = x_position;
    this->y_Position_ = y_position;
    isAlive_ = true;
    pieceValue_ = 10;
}

Pawn::~Pawn()
{
}

bool Pawn::isMovementPossible(int ix, int iy)
{
    // Piece has to be on the board and be alive
    if((ix >= 0 && ix < 8) && (iy >= 0 && iy < 8) && isAlive_)
    {
        // New move
        int x_movement = ix - x_Position_;
        int y_movement = iy - y_Position_;

        // Check to the left or right if the pawn has an enemy
        if(x_movement == 0 || (x_movement == -1 && hasEnemyLeft) || (x_movement == 1 && hasEnemyRight))
        {
            // Check that pawn does not move backward
            if((isWhite_ && y_movement < 0) || (!isWhite_ && y_movement > 0))
            {
                y_movement = abs(y_movement);
                // Move index twice
                if(y_movement == 2 && x_movement == 0)
                {
                    // Check if it is white and if it is the first move
                    if(isWhite_ && y_Position_ == 6)
                        return true;
                    // Check if it is black and if it is the first move
                    if(!isWhite_ && y_Position_ == 1)
                        return true;
                    // If it is not the first move, pawn cannot walks twice
                    return false;
                }
                // Check if pawn only moves 1 index
                else if(y_movement == 1)
                    return true;
            }
        }
    }
    return false;
}

void Pawn::setPawnEnemy(bool hasEnemyLeft, bool hasEnemyRight)
{
    if(isWhite_)
    {
        this->hasEnemyLeft = hasEnemyLeft;
        this->hasEnemyRight = hasEnemyRight;
    }
    else
    {
        this->hasEnemyLeft = hasEnemyRight;
        this->hasEnemyRight = hasEnemyLeft;
    }
}
