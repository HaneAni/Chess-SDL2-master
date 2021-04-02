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

    // Matrix of board
    SDL_Rect mBoard[8][8];
    // Position clicked
    SDL_Point focus_;
    // Last piece clicked
    Piece* focusedPiece_;

    bool init();
    bool loadImage();
    void close();

    // Render chess board
    void renderChessBoard();
    // Color white = true, color black = false
    // Render piece on the board
    void renderPieceOnBoard(PieceName piece, bool color, int x_pos, int y_pos);
    // Render all the piece on the board
    void renderAllPieces(States* states);
    // Render one piece on board
    void renderOnePiece(int x_pos, int y_pos);
    // Render posible moves
    void renderPossibleMoves(States *states);

    // Update clicked position
    void updateFocus(int x_pos, int y_pos);
    // From the index returns the position in pixels of the board
    int indexToPixel(int index, bool xORy);
    // Chooses piece turn
    bool choosePieceTurn(GameState *gm, States* states);
    // Check if there is any move, condition: use move Piece if the last clicked piece is not empty
    bool checkMovement(States* states);
    // Edits the board
    void editBoard(GameState *gm, States* states);

    // Set and get x position of the board
    void setXboard(int x) {x_board_ = x;}
    int getXboard() {return x_board_;}
    // Set and get y position of the board
    void setYboard(int y) {x_board_ = y;}
    int getYboard() {return y_board_;}

private:
    int x_board_;
    int y_board_;

};


#endif // CHESSBOARD_H
