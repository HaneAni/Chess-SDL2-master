#include "ChessBoard.h"
#include "GameState.h"
#include "States.h"


/// The window we'll be rendering to
SDL_Window* g_Window = nullptr;

/// The window renderer
SDL_Renderer* g_Renderer = nullptr;

/// Event handler
SDL_Event e;

/// Menu objects
Menu g_Menu[ TOTAL_MENU ];

/// Menu sprites
SDL_Rect g_SpriteClips[(int) MenuSprite::MENU_SPRITE_TOTAL ];
Texture g_CheckTexture;
Texture g_MenuSpriteSheetTexture;

/// Scene textures
Texture g_Board;
Texture whitePieces[7];
Texture blackPieces[7];
//Texture gBishop;
Texture possibleMoves;
Texture pieceSelected;
//Texture bestMove;
Texture endGame[3];
//Texture selection;


ChessBoard::ChessBoard()
{
}

ChessBoard::~ChessBoard()
{
}

bool ChessBoard::init()
{
    initSDL(g_Window, g_Renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    return ((g_Window != nullptr) && (g_Renderer != nullptr));
}

bool ChessBoard::loadImage()
{
    bool success = true;

    // Loads the texture
    if(!g_Board.loadFromFile(chess_board))
        success = false;

    if(!pieceSelected.loadFromFile(piece_selected))
        success = false;

    if(!possibleMoves.loadFromFile(possible_moves))
        success = false;

    // End game textures
    // White wins
    if(!endGame[(int) GameResult::WHITE_WINS].loadFromFile(white_win))
        success = false;

    // Black wins
    if(!endGame[(int) GameResult::BLACK_WINS].loadFromFile(black_win))
        success = false;

    // Draw
    if(!endGame[(int) GameResult::DRAW].loadFromFile(draw))
        success = false;

    // Chess pieces

    // White pieces

    if(!whitePieces[(int) PieceName::KING].loadFromFile(king_white))
        success = false;

    if(!whitePieces[(int) PieceName::QUEEN].loadFromFile(queen_white))
        success = false;

    if(!whitePieces[(int) PieceName::BISHOP].loadFromFile(bishop_white))
        success = false;

    if(!whitePieces[(int) PieceName::KNIGHT].loadFromFile(knight_white))
        success = false;

    if(!whitePieces[(int) PieceName::ROOK].loadFromFile(rook_white))
        success = false;

    if(!whitePieces[(int) PieceName::PAWN].loadFromFile(pawn_white))
        success = false;

    // Black pieces

    if(!blackPieces[(int) PieceName::KING].loadFromFile(king_black))
        success = false;

    if(!blackPieces[(int) PieceName::QUEEN].loadFromFile(queen_black))
        success = false;

    if(!blackPieces[(int) PieceName::BISHOP].loadFromFile(bishop_black))
        success = false;

    if(!blackPieces[(int) PieceName::KNIGHT].loadFromFile(knight_black))
        success = false;

    if(!blackPieces[(int) PieceName::ROOK].loadFromFile(rook_black))
        success = false;

    if(!blackPieces[(int) PieceName::PAWN].loadFromFile(pawn_black))
        success = false;

    // Loads menu sprite

    if(!g_MenuSpriteSheetTexture.loadFromFile(menu_box))
    {
        logSDLError(std::cout, "Failed to load menu sprite texture", true);
        success = false;
    }
    else
    {
        // Sets sprite
        for(int i = 0; i < (int) MenuSprite::MENU_SPRITE_TOTAL; i++)
        {
            g_SpriteClips[ i ].x = 0;
            g_SpriteClips[ i ].y = i * MENU_HEIGHT;
            g_SpriteClips[ i ].w = MENU_WIDTH;
            g_SpriteClips[ i ].h = MENU_HEIGHT;
        }

        // Sets menu position
        g_Menu[ 0 ].setPosition(0, 0);
        g_Menu[ 1 ].setPosition(MENU_WIDTH, 0);
        g_Menu[ 2 ].setPosition(0, MENU_HEIGHT);
        g_Menu[ 3 ].setPosition(MENU_WIDTH, MENU_HEIGHT);
        g_Menu[ 4 ].setPosition(0, 0);
        g_Menu[ 5 ].setPosition(MENU_WIDTH, 0);
        g_Menu[ 6 ].setPosition(0, MENU_HEIGHT);
        g_Menu[ 7 ].setPosition(MENU_WIDTH, MENU_HEIGHT);
    }

    if(!success)
        logSDLError(std::cout, "Failed to load texture", true);

    return success;
}

void ChessBoard::close()
{
    // Deallocates memory
    g_Board.freeTexture();

    // Free chess pieces
    for(int i = 0; i < 7; i++)
    {
        blackPieces[i].freeTexture();
        whitePieces[i].freeTexture();
    }

    // Destroy window
    SDL_DestroyWindow(g_Window);
    SDL_DestroyRenderer(g_Renderer);
    g_Window = NULL;
    g_Renderer = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

void ChessBoard::updateFocus(int x, int y)
{
    // Check outside the edges of the board
    if( (x < BOARD_PADDING) || (x > BOARD_WIDTH - BOARD_PADDING) || (y < BOARD_PADDING) || (y > BOARD_HEIGHT - BOARD_PADDING) )
    {
        focus_.x = -1;
        focus_.y = -1;
        return;
    }
    focus_.x = (int) (x - BOARD_PADDING) / CELL_SIZE;
    focus_.y = (int) (y - BOARD_PADDING) / CELL_SIZE;
}

int ChessBoard::indexToPixel(int index)
{
    if( (index < 0) || (index > 7) )
    {
        logSDLError(std::cout, "Invalid index", true);
        return -1;
    }
    return (index * CELL_SIZE + BOARD_PADDING);
}

void ChessBoard::renderPieceOnBoard(PieceName piece, int color, int x_pos, int y_pos)
{
    if( (x_pos < 0) || (y_pos < 0) )
        return;

    if(color)
        whitePieces[(int) piece].render(indexToPixel(x_pos), indexToPixel(y_pos));
    else
        blackPieces[(int) piece].render(indexToPixel(x_pos), indexToPixel(y_pos));
}

void ChessBoard::renderAllPieces(States* states)
{
    for(int i = 0; i < 16; i++)
    {
        // Render white pieces
        renderPieceOnBoard(states->whitePieces_[i]->getName(), 1, states->whitePieces_[i]->getPositionX(), states->whitePieces_[i]->getPositionY());

        // Render black pieces
        renderPieceOnBoard(states->blackPieces_[i]->getName(), 0, states->blackPieces_[i]->getPositionX(), states->blackPieces_[i]->getPositionY());
    }
}

bool ChessBoard::checkMovement(States* states)
{
    bool move = false;
    if(focusedPiece_ != nullptr)
        if(focusedPiece_->getName() != PieceName::EMPTY)
            move = states->isMove(focusedPiece_, focus_.x, focus_.y);
    return move;
}

void ChessBoard::renderPossibleMoves(States *states)
{
    int x = 0, y = 0;
    if(focusedPiece_)
    {
        if(focusedPiece_->getName() != PieceName::EMPTY)
        {
            for(int i = 0; i < 8; i++)
            {
                for(int j = 0; j < 8; j++)
                {
                    if(states->isPositionValid(focusedPiece_, i, j))
                    {
                        possibleMoves.render(indexToPixel(i),indexToPixel(j));
                    }
                }
            }
        }
    }
}

void ChessBoard::renderBestMove(States *states)
{
    /******************************************************************* todo *******************************************************************/
}

bool ChessBoard::choosePieceTurn(GameState *gm, States* states)
{
    /******************************************************************* todo *******************************************************************/
    return true;
}

void ChessBoard::editBoard(GameState *gm, States* states)
{
    bool done = false;
    Piece *currentPiece = nullptr;
    states->killAllPieces();
    int indexPiece = 1;
    bool isWhite = false;
    int x = -1, y = -1;

    while(!done)
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                gm->setGameState(GameMode::GAME_MODE_QUIT);
                break;
            }
            if(e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEMOTION)
            {
                switch (e.type)
                {
                case SDL_MOUSEBUTTONDOWN:
                    // Gets mouse position
                    SDL_GetMouseState(&x, &y);
                    // Updates the index of the focused matrix
                    updateFocus((int) x, (int) y);
                    if(isWhite)
                        states->setPiece(states->whitePieces_[indexPiece], focus_.x, focus_.y);
                    else
                        states->setPiece(states->blackPieces_[indexPiece], focus_.x, focus_.y);
                    break;
                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&x, &y);
                    break;
                default:
                    break;
                }
            }
            else if(e.type == SDL_KEYDOWN)
            {
                switch (e.type)
                {
                case SDLK_UP:
                    isWhite = true;
                    break;
                case SDLK_DOWN:
                    isWhite = false;
                    break;
                case SDLK_LEFT:
                    if(indexPiece > 0)
                        indexPiece --;
                    else
                        indexPiece = 15;
                    break;
                case SDLK_RIGHT:
                    if(indexPiece < 15)
                        indexPiece ++;
                    else
                        indexPiece = 0;
                    break;
                case SDLK_d:
                    done = true;
                    break;
                default:
                    break;
                }
            }
            // Clear screen
            SDL_SetRenderDrawColor(g_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(g_Renderer);

            // Render board
            g_Board.render(0, 0);

            if(isWhite)
                whitePieces[(int) states->whitePieces_[indexPiece]->getName()].render(x, y);
            else
                blackPieces[(int) states->blackPieces_[indexPiece]->getName()].render(x, y);

            renderAllPieces(states);

            // Update screen
            SDL_RenderPresent(g_Renderer);
        }
    }
    return;
}
