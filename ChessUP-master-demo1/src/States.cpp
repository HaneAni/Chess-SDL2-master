#include "../include/Piece.h"
#include "../include/States.h"
#include "../include/King.h"
#include "../include/Queen.h"
#include "../include/Rook.h"
#include "../include/Knight.h"
#include "../include/Bishop.h"
#include "../include/Pawn.h"

#include <algorithm>
#include <bits/stdc++.h>

States::States()
{
    // Set piece turn
    pieceTurn_ = true;

    // King can castling and undo move
    for(int i = 0; i < 4; i++)
    {
        kingCastling[i] = true;
    }
    undoKingCastling = false;

    // Initialization pawns
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

    // Initialization black pieces
    blackPieces_[8]  = new Rook(false, 0, 0);
    blackPieces_[9]  = new Knight(false, 1, 0);
    blackPieces_[10] = new Bishop(false, 2, 0);
    blackPieces_[11] = new Queen(false, 3, 0);
    blackPieces_[12] = new King(false, 4, 0);
    blackPieces_[13] = new Bishop(false, 5, 0);
    blackPieces_[14] = new Knight(false, 6, 0);
    blackPieces_[15] = new Rook(false, 7, 0);
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
    // Set the pawn's enemy
    setPawnEnemies(true, piece, -1, -1);
    PieceStatus is_In_The_Spot = isInTheSpot(piece, x_pos, y_pos);

    if(piece->getName() == PieceName::KING)
    {
        if(isCheckmate(piece->getColor(), x_pos, y_pos))
            return false;
        if(isKingCastling(piece, x_pos, y_pos))
            return true;
    }
    if(piece->isMovementPossible(x_pos, y_pos) && isInTheWay(piece, x_pos, y_pos) == PieceStatus::EMPTY && is_In_The_Spot != PieceStatus::ALLY)
    {
        // Remove the pawn's enemy
        setPawnEnemies(false, piece, -1, -1);

        if(piece->getName() == PieceName::PAWN && is_In_The_Spot == PieceStatus::ENEMY)
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

bool States::isMove(Piece* piece, bool turn, int x_pos, int y_pos)
{
    PieceStatus is_In_The_Spot = isInTheSpot(piece, x_pos, y_pos);
    bool color = piece->getColor();

    // Set the pawn's enemy
    setPawnEnemies(true, piece, -1, -1);

    if(isPositionValid(piece, x_pos, y_pos) && isInTheWay(piece, x_pos, y_pos) == PieceStatus::EMPTY &&
       is_In_The_Spot != PieceStatus::ALLY && turn == color)
    {
        // Remove the pawn's enemy
        setPawnEnemies(false, piece, -1, -1);

        // Push in stack
        int index1 = -1, index2 = -1;
        int x_piece, y_piece;
        x_piece = piece->getPositionX();
        y_piece = piece->getPositionY();

        // Get index of focused piece and eaten piece
        index1 = getPieceIndex(x_piece, y_piece);
        if(is_In_The_Spot == PieceStatus::ENEMY)
        {
            index2 = getPieceIndex(x_pos, y_pos);
        }

        // Push focused piece into stack
        index_stack.push(index1);
        // Push focused piece color into stack
        color_stack.push(color);
        // Push old position into stack
        x_position_stack.push(x_piece);
        y_position_stack.push(y_piece);
        // Push new position into stack
        x_position_stack.push(x_pos);
        y_position_stack.push(y_pos);


        if(index1 == 8 || index1 == 12 || index1 == 15 || index2 == 8 || index2 == 12 || index2 == 15)
        {
            kingCastling_stack.push(kingCastling[0]);
            kingCastling_stack.push(kingCastling[1]);
            kingCastling_stack.push(kingCastling[2]);
            kingCastling_stack.push(kingCastling[3]);
        }

        // Set piece's new position
        // Check if king castling
        if(piece->getName() == PieceName::KING)
        {
            if(isKingCastling(piece, x_pos, y_pos))
            {
                // Push 100 to stack if king castling
                index_stack.push(100);

                // Set new position of Rook
                if(x_pos == 6 && y_pos == 0)
                    blackPieces_[15]->setPosition(5, 0);
                else if(x_pos == 2 && y_pos == 0)
                    blackPieces_[8]->setPosition(3, 0);
                else if(x_pos == 2 && y_pos == 7)
                    whitePieces_[8]->setPosition(3, 7);
                else if(x_pos == 6 && y_pos == 7)
                    whitePieces_[15]->setPosition(5, 7);
            }
        }

        if(piece->getName() == PieceName::PAWN)
        {
            if(is_In_The_Spot == PieceStatus::ENEMY && (x_pos - piece->getPositionX() == 0))
                return false;

            if(isPawnTransform(piece, x_pos, y_pos))
            {
                // Push 99 into stack if pawn transform
                index_stack.push(99);
            }
        }

        // Check if piece be eaten
        if(is_In_The_Spot == PieceStatus::ENEMY)
        {
            // Push into stack
            index_stack.push(index2);
            color_stack.push(!color);

            x_position_stack.push(x_pos);
            y_position_stack.push(y_pos);

            x_position_stack.push(-1);
            y_position_stack.push(-1);

            // Eat enemy's piece
            eatPiece(x_pos, y_pos);
        }

        piece->setPosition(x_pos, y_pos);

        // Check if pawn transform
        if(isPawnTransform(piece, x_pos, y_pos))
        {
            pawnTransform(piece, x_pos, y_pos);
        }

        //pieceTurn_ = !pieceTurn_;
        return true;
    }
    // Remove the pawn's enemy
    setPawnEnemies(false, piece, -1, -1);
    return false;
}

void States::undoMove()
{
    Piece **aux;
    int index = -1;
    bool color = true;
    int x_newPos = -1, y_newPos = -1, x_oldPos = -1, y_oldPos = -1;

    // Check stack empty or not
    if(index_stack.empty() || color_stack.empty() || x_position_stack.empty() || y_position_stack.empty())
        return;

    // Get piece to be undone

    // Index of the piece
    index = index_stack.top();
    index_stack.pop();
    // Color of the piece
    color = color_stack.top();
    color_stack.pop();
    // New position x of the piece
    x_newPos = x_position_stack.top();
    x_position_stack.pop();
    // New position y of the piece
    y_newPos = y_position_stack.top();
    y_position_stack.pop();
    // Old position x of the piece
    x_oldPos = x_position_stack.top();
    x_position_stack.pop();
    // Old position y of the piece
    y_oldPos = y_position_stack.top();
    y_position_stack.pop();

    // Check color of the piece
    color ? (aux = whitePieces_) : (aux = blackPieces_);

    // Check if pawn transform
    if(index == 99)
    {
        index = index_stack.top();
        index_stack.pop();

        aux[index] = new Pawn(color, x_oldPos, y_oldPos);
    }

    // Check if king castling
    if(index == 8 || index == 12 || index == 15)
    {
        if(!kingCastling_stack.empty())
        {
            // Get state of king castling
            kingCastling[3] = kingCastling_stack.top();
            kingCastling_stack.pop();
            kingCastling[2] = kingCastling_stack.top();
            kingCastling_stack.pop();
            kingCastling[1] = kingCastling_stack.top();
            kingCastling_stack.pop();
            kingCastling[0] = kingCastling_stack.top();
            kingCastling_stack.pop();
        }
    }
    else if(index == 100)
    {
        // Get index of the piece
        index = index_stack.top();
        index_stack.pop();
        // Get state of king castling
        kingCastling[3] = kingCastling_stack.top();
        kingCastling_stack.pop();
        kingCastling[2] = kingCastling_stack.top();
        kingCastling_stack.pop();
        kingCastling[1] = kingCastling_stack.top();
        kingCastling_stack.pop();
        kingCastling[0] = kingCastling_stack.top();
        kingCastling_stack.pop();

        if(x_newPos == 2)
        {
            aux[8]->setPosition(0, y_oldPos);
        }
        else if(x_newPos == 6)
        {
            aux[15]->setPosition(7, y_oldPos);
        }
    }

    // Revive dead piece
    if(!aux[index]->getIsAlive())
        aux[index]->reviveFromDead();

    aux[index]->setPosition(x_oldPos, y_oldPos);

    if(x_newPos == -1 && y_newPos == -1)
    {
        undoMove();
    }
}

bool States::isCheckmate(bool kingColor, int x_pos, int y_pos)
{
    Piece **aux;
    kingColor ? aux = blackPieces_ : aux = whitePieces_;

    for(int i = 0; i < 16; i++)
    {
        // Check if enemies can go to the King, and if the way to go to the King is clear.
        if(aux[i]->getName() == PieceName::PAWN)
        {
            if(abs(aux[i]->getPositionX() - x_pos) == 1)
            {
                if((kingColor && aux[i]->getPositionY() - y_pos == -1) || (!kingColor && aux[i]->getPositionY() - y_pos == 1) )
                    return true;
            }
        }
        else if(aux[i]->isMovementPossible(x_pos, y_pos) && isInTheWay(aux[i], x_pos, y_pos) == PieceStatus::EMPTY)
            return true;
    }
    return false;
}

bool States::isPawnTransform(Piece* piece, int x_pos, int y_pos)
{
    bool color = piece->getColor();

    if(piece->getName() == PieceName::PAWN)
        if((color && y_pos == 0) || (!color && y_pos == 7))
            return true;
    return false;
}

void States::pawnTransform(Piece* piece, int x_pos, int y_pos)
{
    Piece **aux;
    bool color = piece->getColor();
    int index = 0;

    color ? (aux = whitePieces_) : (aux = blackPieces_);
    index = getPieceIndex(piece->getPositionX(), piece->getPositionY());

    aux[index] = new Queen(color, x_pos, y_pos);
}

bool States::isKingCastling(Piece* piece, int x_pos, int y_pos)
{
    if(piece->getName() == PieceName::KING)
    {
        if(piece->kingCastling(x_pos, y_pos) && isInTheSpot(piece, x_pos, y_pos) == PieceStatus::EMPTY)
        {
            if(!piece->getColor())
            {
                if(x_pos == 6 && y_pos == 0 && kingCastling[0] && isInTheSpot(piece, 5, 0) == PieceStatus::EMPTY)
                    return true;
                if(x_pos == 2 && y_pos == 0 && kingCastling[1] && isInTheSpot(piece, 3, 0) == PieceStatus::EMPTY && isInTheSpot(piece, 1, 0) == PieceStatus::EMPTY)
                    return true;
            }
            else
            {
                if(x_pos == 2 && y_pos == 7 && kingCastling[2] && isInTheSpot(piece, 3, 7) == PieceStatus::EMPTY && isInTheSpot(piece, 1, 7) == PieceStatus::EMPTY)
                    return true;
                if(x_pos == 6 && y_pos == 7 && kingCastling[3] && isInTheSpot(piece, 5, 7) == PieceStatus::EMPTY)
                    return true;
            }
        }
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
    white = !whitePieces_[12]->getIsAlive();
    black = !blackPieces_[12]->getIsAlive();

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
        }
        return GameResult::DRAW;
    }
    return GameResult::NOT_END;
}

int States::valueMove()
{
    int value = 0;

    for(int i = 0; i < 16; i++)
    {
        if(whitePieces_[i]->getPositionX() != -1 && whitePieces_[i]->getPositionY() != -1)
            value += whitePieces_[i]->getPieceValue();
        if(blackPieces_[i]->getPositionX() != -1 && blackPieces_[i]->getPositionY() != -1)
            value -= blackPieces_[i]->getPieceValue();
    }
    return value;
}

int States::Alpha_Beta(int depth, bool color, int alpha, int beta)
{
    Piece **aux;
    int bestMove = 0;

    if(depth == 0)
        return valueMove();

    if(color)
    {
        aux = whitePieces_;
        bestMove = -10000; // Gia tri ban dau
        for(int i = 0; i < 16; i++)
        {
            if(aux[i]->getPositionX() == -1 || aux[i]->getPositionY() == -1)
                continue;

            for(int ix = 0; ix < 8; ix++)
            {
                for(int iy = 0; iy < 8; iy++)
                {
                    if(isMove(aux[i], color, ix, iy))
                    {
                        bestMove = std::max(bestMove, Alpha_Beta(depth-1, !color, alpha, beta));
                        // Undo
                        undoMove();
                        alpha = std::max(alpha, bestMove);
                        if(beta <= alpha)
                        {
                            return bestMove;
                        }
                    }
                }
            }
        }
        return bestMove;
    }
    else
    {
        aux = blackPieces_;
        bestMove = 10000; // Gia tri ban dau
        for(int i = 0; i < 16; i++)
        {
            if(aux[i]->getPositionX() == -1 || aux[i]->getPositionY() == -1)
                continue;

            for(int ix = 0; ix < 8; ix++)
            {
                for(int iy = 0; iy < 8; iy++)
                {
                    if(isMove(aux[i], color, ix, iy))
                    {
                        bestMove = std::min(bestMove, Alpha_Beta(depth-1, !color, alpha, beta));
                        // Undo
                        undoMove();
                        beta = std::min(beta, bestMove);
                        if(beta <= alpha)
                        {
                            return bestMove;
                        }
                    }
                }
            }
        }
        return bestMove;
    }
}

SDL_Point States::getNextMove(bool color)
{
    Piece **aux;
    SDL_Point newPos, newPosTemp;
    int minimax = 10000, minimaxTemp = 10000;
    int index = 0;

    aux = blackPieces_;
    for(int i = 0; i < 16; i++)
    {
        if(aux[i]->getPositionX() == -1 || aux[i]->getPositionY() == -1)
            continue;

        for(int ix = 0; ix < 8; ix++)
        {
            for(int iy = 0; iy < 8; iy++)
            {
                if(isMove(aux[i], color, ix, iy))
                {
                    int alpha = -9999, beta = 9999;
                    int temp = Alpha_Beta(3, color, alpha, beta);
                    if(minimaxTemp > temp)
                    {
                        minimaxTemp = temp;
                        newPosTemp.x = ix;
                        newPosTemp.y = iy;
                    }
                    undoMove();
                }
            }
        }
        if(minimax > minimaxTemp)
        {
            minimax = minimaxTemp;
            index = i;
            newPos = newPosTemp;
        }
    }

    index_stack.push(index);
    return newPos;
}

void States::computerMove(bool color)
{
    Piece **aux;
    SDL_Point newPos;
    int index = 0;
    int x_newPos = 0, y_newPos = 0;

    newPos = getNextMove(color);
    // Get index
    index = index_stack.top();
    index_stack.pop();
    // Get new position
    x_newPos = newPos.x;
    y_newPos = newPos.y;

    color ? (aux = whitePieces_) : (aux = blackPieces_);

    isMove(aux[index], color, x_newPos, y_newPos);
}

void States::saveGame(GameMode mode)
{
    FILE *fp = NULL;
    Piece **aux;
    int i, j;
    char print;

    if(mode == GameMode::GAME_MODE_PVP)
        fp = fopen(outputPVP,"w");
    if(mode == GameMode::GAME_MODE_CPU)
        fp = fopen(outputCPU,"w");
    if(mode == GameMode::GAME_MODE_EDIT)
        fp = fopen(outputEDIT,"w");

    if(fp == NULL)
        return;

    fprintf(fp, "%s", "[Piece Turn]:");
    fprintf(fp, "%c%c", pieceTurn_ ? 'w' : 'b', '\n');
    fprintf(fp, "%s", "[White Piece Board]:");
    aux = whitePieces_;
    for(j = 0; j < 2; j++)
    {
        for(i = 0; i < 16; i++)
        {
            if(aux[i]->getIsAlive())
            {
                switch (aux[i]->getName())
                {
                case PieceName::PAWN:
                    print = 'P';
                    break;
                case PieceName::BISHOP:
                    print = 'B';
                    break;
                case PieceName::ROOK:
                    print = 'R';
                    break;
                case PieceName::KNIGHT:
                    print = 'N';
                    break;
                case PieceName::QUEEN:
                    print = 'Q';
                    break;
                case PieceName::KING:
                    print = 'K';
                    break;
                default:
                    break;
                }
            fprintf(fp, "%c,%d,%d,%c", print, aux[i]->getPositionX(), aux[i]->getPositionY(), '|');
            }
            else
            {
                fprintf(fp, "%c%c", 'x', '|');
            }
        }
        if(j == 0)
        {
            fprintf(fp, "%c", '\n');
            fprintf(fp, "%s", "[Black Piece Board]:");
            aux = blackPieces_;
        }
    }
    fclose(fp);
}

void States::loadGame(GameMode mode)
{
    FILE *fp = NULL;
    Piece **aux;
    int i, j;
    char read[86];

    if(mode == GameMode::GAME_MODE_PVP)
        fp = fopen(outputPVP,"r");
    if(mode == GameMode::GAME_MODE_CPU)
        fp = fopen(outputCPU,"r");
    if(mode == GameMode::GAME_MODE_EDIT)
        fp = fopen(outputEDIT,"r");

    if(fp == NULL)
        return;

    fscanf(fp, "%86[^\n].", read);

    read[13] == 'w' ? pieceTurn_ = true : pieceTurn_ = false;

    aux = whitePieces_;
    for(j = 0; j < 2; j++)
    {
        fscanf(fp, "%86[^:].", read);
        read[0] = fgetc(fp);

        for(i = 0; i < 16; i++)
        {
            fscanf(fp, "%86[^|].", read);
            if(read[0] != 'x')
            {
                aux[i]->reviveFromDead();
                aux[i]->setPosition(atoi(&read[2]), atoi(&read[4]));
            }
            else
                aux[i]->setDead();

            read[0] = fgetc(fp);
        }
        aux = blackPieces_;
    }
    fclose(fp);
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

int States::getPieceIndex(int x_pos, int y_pos)
{
    // Piece has to be on the board
    if((x_pos >= 0 && x_pos < 8) && (y_pos >= 0 && y_pos < 8))
    {
        for(int i = 0; i < 16; i++)
        {
            if(whitePieces_[i]->getPositionX() == x_pos && whitePieces_[i]->getPositionY() == y_pos)
                return i;
            if(blackPieces_[i]->getPositionX() == x_pos && blackPieces_[i]->getPositionY() == y_pos)
                return i;
        }
    }
    return -1;
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
            if(aux[j]->getPositionX() == x_pos && aux[j]->getPositionY() == y_pos)
                aux[j]->setDead();
        }
        aux = blackPieces_;
    }
}
