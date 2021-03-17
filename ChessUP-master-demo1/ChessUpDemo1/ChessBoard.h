#include "SDL_utils.h"
#include "Texture.h"
#include "Piece.h"
#include "States.h"

#include "common.h"

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

//#include <string>

class ChessBoard
{
public:
    ChessBoard();
    ~ChessBoard();

    bool init();
    bool loadImage();
    void close();

    // Update clicked position
    void updateFocus(int x, int y);
    // From the index returns the position in pixels of the board
    int indexToPixel(int index);
    // Color = 1 = white, color = 0 = black
    // Render piece on the board
    void renderPieceOnBoard(PieceName piece, int color, int ix, int iy);
    void renderAllPieces(States* states);
    // Check if there is any move, condition: use move Piece if the last clicked piece is not empty
    bool checkMovement(States* states);
    // Render posible moves
    void renderPossibleMoves(States *states);
    // Render best move
    void renderBestMove(States *states);
    // Chooses piece turn
    bool choosePieceTurn(GameState *gm, States* states);
    // Edits the board
    void editBoard(GameState *gm, States* states);

    // Matrix of board
    SDL_Rect mBoard[8][8];
    // Position clicked
    SDL_Point focus_ = {-1,-1};
    // Last piece clicked
    Piece* focusedPiece_ = nullptr;

};


#endif // CHESSBOARD_H
