#include "GameState.h"

#include "ChessBoard.h"
#include "Piece.h"
#include "States.h"

GameState::GameState()
{
    // Sets game state default: Main menu
    gameState_ = GameMode::GAME_MODE_MAIN_MENU;
}

GameState::~GameState()
{
}

void GameState::startGameState(GameMode gameMode)
{
    gameState_ = gameMode;

    while (gameState_ != GameMode::GAME_MODE_QUIT)
    {
        switch (gameState_)
        {
        case GameMode::GAME_MODE_MAIN_MENU:
            renderMainMenu();
            break;
        case GameMode::GAME_MODE_PVP:
            renderPVP();
            break;
        case GameMode::GAME_MODE_CPU:
            renderCPU();
            break;
        case GameMode::GAME_MODE_CHESSUP:
            renderChessupMode();
            break;
        default:
            break;
        }
    }
}

void GameState::renderMainMenu()
{
    bool isQuit = false;

    // Sets menu 0 to menu 3 sprite
    for(int i = 0; i < TOTAL_MENU / 2; i++)
        g_Menu[ i ].setCurrentSprite((MenuSprite) i);

    // Render main menu
    while (gameState_ == GameMode::GAME_MODE_MAIN_MENU)
    {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            // User requests quit
            if(e.type == SDL_QUIT)
            {
                gameState_ = GameMode::GAME_MODE_QUIT;
                break;
            }
            // Handle button events
            for(int i = 0; i < TOTAL_MENU / 2; i++)
                g_Menu[ i ].handleEvent(&e, this);
        }
        // Clear screen
        SDL_SetRenderDrawColor(g_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(g_Renderer);

        // Render main menu
        for(int i = 0; i < TOTAL_MENU / 2; i++)
            g_Menu[ i ].render();

        // Update screen
        SDL_RenderPresent(g_Renderer);
    }
}

void GameState::renderPVP()
{
    bool isQuit = false;
    bool showHint = true;
    int x = -1, y = -1;

    States *states = new States();
    ChessBoard *board = new ChessBoard();
    GameResult gameResult = GameResult::NOT_END;

    states->setPieceTurn(board->choosePieceTurn(this, states));

    while (gameState_ == GameMode::GAME_MODE_PVP)
    {
        // Handles the event queue
        while (SDL_PollEvent(&e))
        {
            // User requests quit
            if(e.type == SDL_QUIT)
            {
                gameState_ = GameMode::GAME_MODE_QUIT;
                break;
            }
            else if(e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    renderPauseMenu();
                    break;
                default:
                    break;
                }
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                // Gets mouse position
                SDL_GetMouseState(&x, &y);
                // Updates the index of the focused matrix
                board->updateFocus((int) x, (int) y);

                // If there was a move, update the tile vectors and zero the focused tile
                if(board->checkMovement(states))
                    board->focusedPiece_ = nullptr;
                else
                    // If there was no move, the focused piece is the current piece
                    board->focusedPiece_ = states->getPiece(board->focus_.x, board->focus_.y);
            }
        }
        // If save
        if(gameState_ == GameMode::GAME_MODE_SAVE)
        {
            states->saveGame(GameMode::GAME_MODE_PVP);
            gameState_ = GameMode::GAME_MODE_PVP;
        }

        // If load
        if(gameState_ == GameMode::GAME_MODE_LOAD)
        {
            states->loadGame(GameMode::GAME_MODE_PVP);
            gameState_ = GameMode::GAME_MODE_PVP;
        }

        // Clear screen
        SDL_SetRenderDrawColor(g_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(g_Renderer);

        // Render chess board
        g_Board.render(0, 0);

        gameResult = states->checkWhoWon();
        if(gameResult == GameResult::NOT_END)
        {
            if(board->focusedPiece_ != nullptr)
            {
                // Render the piece selected
                if((board->focusedPiece_->getName() != PieceName::EMPTY) && (board->focusedPiece_->getColor() == states->getPieceTurn()))
                    pieceSelected.render(board->indexToPixel(board->focus_.x), board->indexToPixel(board->focus_.y));

                // Render all possible moves of the focus piece
                if(showHint && (board->focusedPiece_->getColor() == states->getPieceTurn()))
                    board->renderPossibleMoves(states);
            }
            // Render all the pieces
            board->renderAllPieces(states);
        }
        else
        {
            endGame[(int) gameResult].render(0, 0);
        }
        // Update screen
        SDL_RenderPresent(g_Renderer);
    }
    delete states;
    delete board;
}

void GameState::renderCPU()
{
    /******************************************************************* todo *******************************************************************/
}

void GameState::renderChessupMode()
{
    /******************************************************************* todo *******************************************************************/
}

void GameState::renderPauseMenu()
{
    bool isQuit = false;
    isPause = 1;

    // Sets menu 4 to menu 7
    for(int i = TOTAL_MENU/2; i < TOTAL_MENU; i++)
        g_Menu[ i ].setCurrentSprite((MenuSprite) i);

    while (isPause)
    {
        // Handle events on queue
        while (SDL_PollEvent(&e))
        {
            // User requests
            if(e.type == SDL_QUIT)
            {
                gameState_ = GameMode::GAME_MODE_QUIT;
                break;
            }
            else if(e.type == SDL_KEYDOWN)
            {
                if(e.key.keysym.sym == SDLK_ESCAPE)
                {
                    isPause = 0;
                    break;
                }
            }
            // Handle button events
            for(int i = TOTAL_MENU/2; i < TOTAL_MENU; i++)
                g_Menu[ i ].handleEvent(&e, this);
        }
        // Clear screen
        SDL_SetRenderDrawColor(g_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(g_Renderer);

        // Render main menu
        for(int i = TOTAL_MENU/2; i < TOTAL_MENU; i++)
            g_Menu[ i ].render();

        // Update screen
        SDL_RenderPresent(g_Renderer);
    }
}
