#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H

#include "Texture.h"
#include "Menu.h"

/*********** Constant ***********/

/// Screen parameter
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;
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
const int OFFSET = 20;

/// Image
static const char main_menu[]   = {"../image/Main_Chess.jpg"};
static const char chess_background[]  = {"../image/006.png"};

static const char chess_board[]  = {"../image/Chess_Board_Wood.png"};
static const char piece_selected[]  = {"../image/Piece_Selected_80px.png"};
static const char possible_moves[]  = {"../image/Possible_Moves_25px.png"};
static const char menu_box[]  = {"../image/Menus.png"};

static const char black_win[]  = {"../image/Black_Win.png"};
static const char white_win[]  = {"../image/White_Win.png"};
static const char draw[]  = {"../image/Draw.png"};

static const char king_black[]   = {"../image/Chessman1/Black_King.png"};
static const char queen_black[]  = {"../image/Chessman1/Black_Queen.png"};
static const char rook_black[]   = {"../image/Chessman1/Black_Rook.png"};
static const char knight_black[] = {"../image/Chessman1/Black_Knight.png"};
static const char bishop_black[] = {"../image/Chessman1/Black_Bishop.png"};
static const char pawn_black[]   = {"../image/Chessman1/Black_Pawn.png"};

static const char king_white[]   = {"../image/Chessman1/White_King.png"};
static const char queen_white[]  = {"../image/Chessman1/White_Queen.png"};
static const char rook_white[]   = {"../image/Chessman1/White_Rook.png"};
static const char knight_white[] = {"../image/Chessman1/White_Knight.png"};
static const char bishop_white[] = {"../image/Chessman1/White_Bishop.png"};
static const char pawn_white[]   = {"../image/Chessman1/White_pawn.png"};


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
extern SDL_Rect g_SpriteClips[ TOTAL_MENU ];
extern Texture t_MenuSpriteSheetTexture;

/// Scene textures
extern Texture t_Board;
extern Texture t_MainMenu;
extern Texture t_Background;
extern Texture t_WhitePieces[7];
extern Texture t_BlackPieces[7];
extern Texture t_PossibleMoves;
extern Texture t_PieceSelected;
extern Texture t_EndGame[3];

/*********** RGB Color ***********/
/**
Black               #000000     (0, 0, 0)
White               #FFFFFF     (255, 255, 255)
Red                 #FF0000     (255, 0, 0)
Green               #00FF00     (0, 255, 0)
Blue                #0000FF     (0, 0, 255)
Yellow              #FFFF00     (255, 255, 0)
Cyan / Aqua         #00FFFF     (0, 255, 255)
Magenta / Fuchsia   #FF00FF     (255, 0, 255)
Silver              #C0C0C0     (192, 192, 192)
Gray                #808080     (128, 128, 128)
Maroon              #800000     (128, 0, 0)
Olive               #808000     (128, 128, 0)
Lime                #008000     (0, 128, 0)
Purple              #800080     (128, 0, 128)
Teal                #008080     (0, 128, 128)
Navy                #000080     (0, 0, 128)

deep pink	        #FF1493	    (255,20,147)
hot pink	        #FF69B4	    (255,105,180)
light pink	        #FFB6C1	    (255,182,193)
pink	            #FFC0CB	    (255,192,203)
**/

#endif // GLOBAL_VARIABLE_H
