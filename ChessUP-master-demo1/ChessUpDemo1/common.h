#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H

#include "Texture.h"
#include "Menu.h"


/// Screen parameter
const int SCREEN_WIDTH = 680;
const int SCREEN_HEIGHT = 680;
const char WINDOW_TITLE[] = "This is HaneAni's game!";

/// Menu constants
const int MENU_WIDTH = 340;
const int MENU_HEIGHT = 340;
const int TOTAL_MENU = 8;

/// Board constants
const int CELL_SIZE = 80;
const int BOARD_WIDTH = 680;
const int BOARD_HEIGHT = 680;
const int BOARD_PADDING = 20;

/// Image
static const char main_background[]   = {"../image/Main_Chess.jpg"};
static const char chess_background[]  = {"../image/026.png"};

static const char chess_board[]  = {"../image/Chess_Board_Wood.png"};
static const char piece_selected[]  = {"../image/Piece_Selected.png"};
static const char possible_moves[]  = {"../image/Possible_Moves.png"};
static const char menu_box[]  = {"../image/Menus.png"};

static char black_win[]  = {"../image/Black_Win.png"};
static char white_win[]  = {"../image/White_Win.png"};
static char draw[]  = {"../image/Draw.png"};

static char king_black[]   = {"../image/Chessman2/Black_King.png"};
static char queen_black[]  = {"../image/Chessman2/Black_Queen.png"};
static char rook_black[]   = {"../image/Chessman2/Black_Rook.png"};
static char knight_black[] = {"../image/Chessman2/Black_Knight.png"};
static char bishop_black[] = {"../image/Chessman2/Black_Bishop.png"};
static char pawn_black[]   = {"../image/Chessman2/Black_Pawn.png"};

static char king_white[]   = {"../image/Chessman2/White_King.png"};
static char queen_white[]  = {"../image/Chessman2/White_Queen.png"};
static char rook_white[]   = {"../image/Chessman2/White_Rook.png"};
static char knight_white[] = {"../image/Chessman2/White_Knight.png"};
static char bishop_white[] = {"../image/Chessman2/White_Bishop.png"};
static char pawn_white[]   = {"../image/Chessman2/White_pawn.png"};


/******** Global Variable ********/

/// The window we'll be rendering to
extern SDL_Window* g_Window;

/// The window renderer
extern SDL_Renderer* g_Renderer;

/// Event handler
extern SDL_Event e;

/// Menu objects
extern Menu g_Menu[ TOTAL_MENU ];

/// Menu sprites
extern SDL_Rect g_SpriteClips[(int) MenuSprite::MENU_SPRITE_TOTAL ];
extern Texture g_CheckTexture;
extern Texture g_MenuSpriteSheetTexture;

/// Scene textures
extern Texture g_Board;
extern Texture whitePieces[7];
extern Texture blackPieces[7];
//extern Texture gBishop;
//extern Texture casaVerde;
extern Texture pieceSelected;
//extern Texture bestMove;
extern Texture endGame[3];
//extern Texture selection;


#endif // GLOBAL_VARIABLE_H
