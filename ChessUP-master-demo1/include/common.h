#ifndef GLOBAL_VARIABLE_H
#define GLOBAL_VARIABLE_H

#include "../include/Texture.h"
#include "../include/Button.h"

#include <stack>

/*********** Constant ***********/

#define SDL_ERROR 1
#define IMG_ERROR 2
#define MIX_ERROR 3
#define TTF_ERROR 4

#define MIX_CHANNEL -1
#define IS_REPEATITIVE -1
#define NOT_REPEATITIVE 0

#define SMALL_BUTTON 1
#define COMMON_BUTTON 2

/// Screen parameter
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;
const char WINDOW_TITLE[] = "This is HaneAni's game!";

/// Menu constants
const int MENU_WIDTH = 310;
const int MENU_HEIGHT = 70;
const int TOTAL_MAIN_MENU = 4;
const int TOTAL_PAUSE_MENU = 4;
const int MENU_TEXT_SIZE = 35;

/// Board constants
const int CELL_SIZE = 70;
const int BOARD_WIDTH = 680;
const int BOARD_HEIGHT = 680;
const int BOARD_PADDING = 20;
const int OFFSET = 20;

/// Button constants
const int COMMON_BUTTON_WIDTH = 150;
const int COMMON_BUTTON_HEIGHT = 98;
const int SMALL_BUTTON_WIDTH = 22;
const int SMALL_BUTTON_HEIGHT = 34;

/// Images
static const char main_menu[]   = {"../res/textures/Main_Chess.jpg"};
static const char chess_background[]  = {"../res/textures/136.png"};

static const char chess_board[]  = {"../res/textures/Chess_Board_Wood.png"};
static const char piece_selected[]  = {"../res/textures/Piece_Selected_80px.png"};
static const char possible_moves[]  = {"../res/textures/Possible_Moves_25px.png"};
static const char menu_box[]  = {"../res/textures/Menus.png"};

static const char black_win[]  = {"../res/textures/Black_Win.png"};
static const char white_win[]  = {"../res/textures/White_Win.png"};
static const char draw[]  = {"../res/textures/Draw.png"};

static const char king_black[]   = {"../res/textures/Chessman1/Black_King.png"};
static const char queen_black[]  = {"../res/textures/Chessman1/Black_Queen.png"};
static const char rook_black[]   = {"../res/textures/Chessman1/Black_Rook.png"};
static const char knight_black[] = {"../res/textures/Chessman1/Black_Knight.png"};
static const char bishop_black[] = {"../res/textures/Chessman1/Black_Bishop.png"};
static const char pawn_black[]   = {"../res/textures/Chessman1/Black_Pawn.png"};

static const char king_white[]   = {"../res/textures/Chessman1/White_King.png"};
static const char queen_white[]  = {"../res/textures/Chessman1/White_Queen.png"};
static const char rook_white[]   = {"../res/textures/Chessman1/White_Rook.png"};
static const char knight_white[] = {"../res/textures/Chessman1/White_Knight.png"};
static const char bishop_white[] = {"../res/textures/Chessman1/White_Bishop.png"};
static const char pawn_white[]   = {"../res/textures/Chessman1/White_pawn.png"};

/// Fonts
static const char text_fonts[]   = {"../res/fonts/cocogoose.ttf"};


/******** Global Variable ********/

/// The window we'll be rendering to
extern SDL_Window* g_Window;

/// The window renderer
extern SDL_Renderer* g_Renderer;

/// Event handler
extern SDL_Event e;

/// Font
extern TTF_Font* g_Font;

/// Button objects
extern Button g_Button[ (int) ButtonSprite::BUTTON_SPRITE_TOTAL ];
extern Button m_Button[ TOTAL_MAIN_MENU + TOTAL_PAUSE_MENU ];

/// Button sprites
extern SDL_Rect g_SpriteClips[ (int) ButtonSprite::BUTTON_SPRITE_TOTAL ];
extern SDL_Rect m_SpriteClips[ TOTAL_MAIN_MENU + TOTAL_PAUSE_MENU ];
extern Texture t_ButtonSpriteSheetTexture;

/// Scene textures
extern Texture t_Board;
extern Texture t_MainMenu;
extern Texture t_Background;

extern Texture t_WhitePieces[7];
extern Texture t_BlackPieces[7];
extern Texture t_PossibleMoves;
extern Texture t_PieceSelected;
extern Texture t_EndGame[3];

extern Texture t_Text;


/************* Stack *************/
/// Stack save movement
extern std::stack<int> x_position_stack;
extern std::stack<int> y_position_stack;
extern std::stack<int> index_stack;
extern std::stack<bool> color_stack;
extern std::stack<bool> kingCastling_stack;


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
