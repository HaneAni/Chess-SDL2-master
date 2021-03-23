#include "SDL_utils.h"
#include "Texture.h"
#include "Piece.h"
#include "States.h"

#include "common.h"

#ifndef CHESSBOARD_H
#define CHESSBOARD_H


class ChessBoard
{
public:
    ChessBoard();
    ~ChessBoard();

    bool init();
    bool loadImage();
    void close();

    // Render chess board
    void renderChessBoard();
    // Update clicked position
    void updateFocus(int x, int y);
    // From the index returns the position in pixels of the board
    int indexToPixel(int index, bool xORy);
    // Color = 1 = white, color = 0 = black
    // Render piece on the board
    void renderPieceOnBoard(PieceName piece, bool color, int ix, int iy);
    // Render all the piece on the board
    void renderAllPieces(States* states);
    // Check if there is any move, condition: use move Piece if the last clicked piece is not empty
    bool checkMovement(States* states);
    // Render posible moves
    void renderPossibleMoves(States *states);
    // Chooses piece turn
    bool choosePieceTurn(GameState *gm, States* states);
    // Edits the board
    void editBoard(GameState *gm, States* states);

    // Matrix of board
    SDL_Rect mBoard[8][8];
    // Position clicked
    SDL_Point focus_;
    // Last piece clicked
    Piece* focusedPiece_;

    void setXboard(int x) {x_board_ = x;}
    int getXboard() {return x_board_;}

    void setYboard(int y) {x_board_ = y;}
    int getYboard() {return y_board_;}

private:
    int x_board_;
    int y_board_;

};


#endif // CHESSBOARD_H
