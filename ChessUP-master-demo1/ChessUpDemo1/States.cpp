#include "States.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Pawn.h"

States::States()
{
    // Initialized pawns
    for(int i = 0; i < 8; i++)
    {
        whitePieces_[i] = new Pawn(true, i, 6);
        blackPieces_[i] = new Pawn(false, i, 1);
    }

    // Initialization white pieces
    whitePieces_[8]  = new Rook(true, 0, 7);
    whitePieces_[9]  = new Knight(true, 1, 7);
    whitePieces_[10] = new Bishop(true, 2, 7);
    whitePieces_[11] = new Queen(true, 3, 7);
    whitePieces_[12] = new King(true, 4, 7);
    whitePieces_[13] = new Bishop(true, 5, 7);
    whitePieces_[14] = new Knight(true, 6, 7);
    whitePieces_[15] = new Rook(true, 7, 7);

    //Inicialização das peças pretas
    blackPieces_[8]  = new Rook(false, 0, 0);
    blackPieces_[9]  = new Knight(false, 1, 0);
    blackPieces_[10] = new Bishop(false, 2, 0);
    blackPieces_[11] = new Queen(false, 3, 0);
    blackPieces_[12] = new King(false, 4, 0);
    blackPieces_[13] = new Bishop(false, 5, 0);
    blackPieces_[14] = new Knight(false, 6, 0);
    blackPieces_[15] = new Rook(false, 7, 0);

    pieceTurn = true;
}

States::~States()
{
}

PieceStatus States::isInTheWay(Piece* piece, int x_pos, int y_pos)
{
    Piece **aux;

    switch (piece->getName())
    {
    case PieceName::KNIGHT:
        return PieceStatus::EMPTY;
        break;
    default:
        int x_displacement = x_pos - piece->getPositionX();
        int y_displacement = y_pos - piece->getPositionY();
        int displacement_loop, vertical, horizontal;

        for(int i = 0; i < 16; i++)
        {
            aux = whitePieces_;
            for(int j = 0; j < 2; j++)
            {
                displacement_loop = 0;
                vertical = 0;
                horizontal = 0;

                (x_displacement != 0) ? (displacement_loop = x_displacement) : (displacement_loop = y_displacement);
                displacement_loop = abs(displacement_loop);

                while (displacement_loop > 1)
                {
                    if(abs(x_displacement) != abs(y_displacement))
                    {
                        (x_displacement > 0) ? horizontal++ : ((x_displacement < 0) ? horizontal-- : horizontal = 0);
                        (y_displacement > 0) ? vertical++ : ((y_displacement < 0) ? vertical-- : vertical = 0);
                    }
                    else
                    {
                        (x_displacement > 0) ? horizontal++ : ((x_displacement < 0) ? horizontal-- : horizontal = 0);
                        (y_displacement > 0) ? vertical++ : ((y_displacement < 0) ? vertical-- : vertical = 0);
                    }

                    if((aux[i]->getPositionX() == (piece->getPositionX() + horizontal)) &&
                       (aux[i]->getPositionY() == (piece->getPositionY() + vertical)))
                    {
                        if((aux[i]->getColor() && piece->getColor()) || (!aux[i]->getColor() && !piece->getColor()))
                            return PieceStatus::ALLY;
                        else
                            return PieceStatus::ENEMY;
                    }
                    displacement_loop--;
                }
                aux = blackPieces_;
            }
        }
        return PieceStatus::EMPTY;
        break;
    }
}

PieceStatus States::isInTheSpot(Piece* piece, int x_pos, int y_pos)
{
    Piece **aux;

    for(int i = 0; i < 16; i++)
    {
        aux = whitePieces_;
        for(int j = 0; j < 2; j++)
        {
            if((aux[i]->getPositionX() == x_pos) && (aux[i]->getPositionY() == y_pos))
            {
                if((aux[i]->getColor() && piece->getColor()) || (!aux[i]->getColor() && !piece->getColor()))
                    return PieceStatus::ALLY;
                else
                    return PieceStatus::ENEMY;
            }
            aux = blackPieces_;
        }
    }
    return PieceStatus::EMPTY;
}

bool States::isPositionValid(Piece* piece, int x_pos, int y_pos)
{
    PieceStatus obstacle;
    if(piece->getName() == PieceName::KING)
    {
        if(isCheck(piece->getColor(), x_pos, y_pos))
            return false;
    }
    // Set the pawn's enemy
    setPawnEnemies(true, piece, -1, -1);
    obstacle = isInTheSpot(piece, x_pos, y_pos);

    if(piece->isMovementPossible(x_pos, y_pos) && isInTheWay(piece, x_pos, y_pos) == PieceStatus::EMPTY && obstacle != PieceStatus::ALLY)
    {
        // Remove the pawn's enemy
        setPawnEnemies(false, piece, -1, -1);

        if(piece->getName() == PieceName::PAWN && obstacle == PieceStatus::ENEMY)
        {
            if(piece->getPositionX() - x_pos != 0)
                return true;
        }
        else
            return true;
    }
    // Remove the pawn's enemy
    setPawnEnemies(false, piece, -1, -1);
    return false;
}

bool States::isMove(Piece* piece, int x_pos, int y_pos)
{
    // Set the pawn's enemy
    setPawnEnemies(true, piece, -1, -1);
    PieceStatus is_In_The_Spot = isInTheSpot(piece, x_pos, y_pos);
    if(piece->isMovementPossible(x_pos, y_pos) &&
       isInTheWay(piece, x_pos, y_pos) == PieceStatus::EMPTY &&
       is_In_The_Spot != PieceStatus::ALLY)
    {
        // Remove the pawn's enemy
        setPawnEnemies(false, piece, -1, -1);

        if(piece->getName() == PieceName::KING)
            if(isCheck(piece->getColor(), x_pos, y_pos))
                return false;

        if(piece->getName() == PieceName::PAWN)
            if(is_In_The_Spot == PieceStatus::ENEMY && (x_pos - piece->getPositionX() == 0))
                return false;

        if(is_In_The_Spot == PieceStatus::ENEMY)
            eatPiece(x_pos, y_pos);

        piece->setPosition(x_pos, y_pos);
        pawnTransform(piece);
        pieceTurn = !pieceTurn;
        return true;
    }
    // Remove the pawn's enemy
    setPawnEnemies(false, piece, -1, -1);
    return false;
}

bool States::isCheck(bool kingColor, int x_pos, int y_pos)
{
    Piece **aux;
    kingColor ? aux = blackPieces_ : aux = whitePieces_;

    for(int i = 0; i < 16; i++)
    {
        // Set the pawn's enemy
        setPawnEnemies(true, aux[i], x_pos, y_pos);
        // Check if enemies can go to the King, and if the way to go to the King is clear.
        if(aux[i]->isMovementPossible(x_pos, y_pos) && isInTheWay(aux[i], x_pos, y_pos) == PieceStatus::EMPTY)
            return true;
        // Remove the pawn's enemy
        setPawnEnemies(false, aux[i], -1, -1);
    }
    return false;
}

bool States::isCheckMate(bool kingColor)
{
    Piece **aux;
    Piece **aux2;
    int x, y;

    if(kingColor)
    {
        aux = whitePieces_;
        aux2 = blackPieces_;
    }
    else
    {
        aux = blackPieces_;
        aux2 = whitePieces_;
    }

    // Set position x, y of the King
    x = aux[12]->getPositionX();
    y = aux[12]->getPositionY();

    if(isCheck(kingColor, x, y))
    {
        // Possible move of the King
        for(int i = -1; i < 2; i++)
            for(int j = -1; j < 2; j++)
                for(int k = 0; k < 16; k++)
                    if(!isCheck(kingColor, x+i, y+j) && isInTheSpot(aux[12], x+i, y+j) != PieceStatus::ALLY &&
                       (!aux2[k]->isMovementPossible(x+i, y+j) || isInTheWay(aux2[k], x+i, y+j) != PieceStatus::EMPTY) &&
                       aux[12]->isMovementPossible(x+i, y+j) )
                        return false;
        return true;
    }
    return false;
}

void States::killAllPieces()
{
    for(int i = 0; i < 16; i++)
    {
        whitePieces_[i]->setDead();
        blackPieces_[i]->setDead();
    }
}

GameResult States::checkWhoWon()
{
    bool white = false, black = false;
    white = !whitePieces_[12]->getIsAlive() || isCheckMate(true);
    black = !blackPieces_[12]->getIsAlive() || isCheckMate(false);

    if(white && black)
        return GameResult::DRAW;

    if(white)
        return GameResult::BLACK_WINS;

    if(black)
        return GameResult::WHITE_WINS;

    if(!white && !black)
    {
        for(int i = 0; i < 16; i++)
        {
            if((whitePieces_[i]->getIsAlive() && whitePieces_[i]->getName() != PieceName::KING) ||
               (blackPieces_[i]->getIsAlive() && blackPieces_[i]->getName() != PieceName::KING))
            {
                return GameResult::NOT_END;
            }
            return GameResult::DRAW;
        }
    }
    return GameResult::NOT_END;
}

void States::playBestMove(bool, Level)
{
    /******************************************************************* todo *******************************************************************/
}

void States::updateBestMoves(void)
{
    /******************************************************************* todo *******************************************************************/
}

PieceValue States::getPieceBestMove(Piece* )
{
    /******************************************************************* todo *******************************************************************/
}

bool States::setPiece(Piece* piece, int x_pos, int y_pos)
{
    // Piece has to be on the board
    if((x_pos >= 0 && x_pos < 8) && (y_pos >= 0 && y_pos < 8))
    {
        if(isInTheSpot(piece, x_pos, y_pos) == PieceStatus::EMPTY)
        {
            piece->reviveFromDead();
            piece->setPosition(x_pos, y_pos);
            return true;
        }
    }
    return false;
}

Piece* States::getPiece(int x_pos, int y_pos)
{
    // Piece has to be on the board
    if((x_pos >= 0 && x_pos < 8) && (y_pos >= 0 && y_pos < 8))
    {
        for(int i = 0; i < 16; i++)
        {
            if(whitePieces_[i]->getPositionX() == x_pos && whitePieces_[i]->getPositionY() == y_pos)
                return whitePieces_[i];
            if(blackPieces_[i]->getPositionX() == x_pos && blackPieces_[i]->getPositionY() == y_pos)
                return blackPieces_[i];
        }
    }
    return emptyPiece_;
}

void States::setPieceTurn(bool pieceTurn)
{
    this->pieceTurn = pieceTurn;
}

bool States::getPieceTurn()
{
    return this->pieceTurn;
}

void States::saveGame(GameMode)
{
    /******************************************************************* todo *******************************************************************/
}

void States::loadGame(GameMode)
{
    /******************************************************************* todo *******************************************************************/
}

void States::setPawnEnemies(bool check, Piece* piece, int x_enemyPosition, int y_enemyPosition)
{
    int verticalDirection, horizontalDirection;
    bool leftEnemy = false, rightEnemy = false;

    if(piece->getName() == PieceName::PAWN)
    {
        if(check)
        {
            piece->getColor() ? (verticalDirection = piece->getPositionY() - 1) : (verticalDirection = piece->getPositionY() + 1);
            horizontalDirection = piece->getPositionX() + 1;

            for(int i = 0; i < 2; i++)
            {
                if(isInTheSpot(piece, horizontalDirection, verticalDirection) == PieceStatus::ENEMY)
                {
                    piece->getColor() ? ((i == 0) ? rightEnemy = true : leftEnemy = true) : ((i == 0) ? leftEnemy = true : rightEnemy = true);
                }
                horizontalDirection = piece->getPositionX() - 1;
            }
            if(abs(x_enemyPosition - piece->getPositionX() == 1) && (x_enemyPosition != -1) &&
               abs(y_enemyPosition - piece->getPositionY() == 1) && (y_enemyPosition != -1))
            {
                piece->getColor() ? ((x_enemyPosition - piece->getPositionX() == 1) ? rightEnemy = true : leftEnemy = true) :
                                    ((x_enemyPosition - piece->getPositionX() == -1) ? rightEnemy = true : leftEnemy = true);
            }
        }
        piece->setPawnEnemy(leftEnemy, rightEnemy);
    }
}

void States::eatPiece(int x_pos, int y_pos)
{
    Piece **aux;
    aux = whitePieces_;

    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 16; j++)
        {
            if(aux[i]->getPositionX() == x_pos && aux[i]->getPositionY() == y_pos)
                aux[i]->setDead();
        }
        aux = blackPieces_;
    }
}

void States::pawnTransform(Piece* piece)
{
    int x, y;
    bool color;
    Piece **aux;

    if(piece->getName() == PieceName::PAWN)
    {
        color = piece->getColor();
        y = piece->getPositionY();
        if((color && y == 0) || (!color && y == 7))
        {
            x = piece->getPositionX();
            color ? (aux = whitePieces_) : (aux = blackPieces_);
            for(int i = 0; i < 16; i++)
            {
                if(aux[i]->getPositionX() == x && aux[i]->getPositionY() == y)
                {
                    aux[i] = new Queen(color, x, y);
                    return;
                }
            }
        }
    }
}

