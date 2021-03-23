#include "Piece.h"

Piece::Piece()
{
    // Sets the piece default is empty
    name = PieceName::EMPTY;

    isWhite = false;
    isAlive = false;

    // Sets default coordinate is out of the chessboard
    x_Position_ = -1;
    y_Position_ = -1;

    // King can castling to
    for(int i = 0; i < 4; i++)
    {
        isKingCastling[i] = true;
    }
}

Piece::~Piece()
{
}

void Piece::setPosition(int x, int y)
{
    if(isAlive)
    {
        x_Position_ = x;
        y_Position_ = y;
    }
}

void Piece::setDead()
{
    isAlive = false;
    x_Position_ = -1;
    y_Position_ = -1;
}

void Piece::reviveFromDead()
{
    isAlive = true;
}

bool Piece::isMovementPossible(int x_finalPosition, int y_finalPosition)
{
}

void Piece::setPawnEnemy(bool hasEnemyLeft, bool hasEnemyRight)
{
}

bool Piece::kingCastling(int x_finalPosition, int y_finalPosition)
{
}
