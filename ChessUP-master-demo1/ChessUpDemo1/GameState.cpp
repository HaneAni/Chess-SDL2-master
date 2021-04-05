#include "GameState.h"

#include "ChessBoard.h"
#include "Piece.h"
#include "States.h"

GameState::GameState()
{
    isPause = 0;
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
        t_MainMenu.renderBackground();
        // Render main menu
        for(int i = 0; i < TOTAL_MENU / 2; i++)
            g_Menu[ i ].render();

        // Update screen
        updateScreen(g_Window, g_Renderer);
    }
}

void GameState::renderPVP()
{
    bool showHint = true;
    int x = -1, y = -1;

    ChessBoard *board = new ChessBoard();
    States *states = new States();
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
                case SDLK_z:
                    states->undoMove();
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
                {
                    // If King move
                    if(board->focusedPiece_ == states->blackPieces_[12])
                    {
                        states->kingCastling[0] = false;
                        states->kingCastling[1] = false;
                    }
                    else if(board->focusedPiece_ == states->whitePieces_[12])
                    {
                        states->kingCastling[2] = false;
                        states->kingCastling[3] = false;
                    }

                    // If Rook move or be eaten
                    else if(board->focusedPiece_ == states->blackPieces_[15] || states->getPiece(board->focus_.x, board->focus_.y) == states->blackPieces_[15])
                        states->kingCastling[0] = false;
                    else if(board->focusedPiece_ == states->blackPieces_[8] || states->getPiece(board->focus_.x, board->focus_.y) == states->blackPieces_[8])
                        states->kingCastling[1] = false;
                    else if(board->focusedPiece_ == states->whitePieces_[8] || states->getPiece(board->focus_.x, board->focus_.y) == states->blackPieces_[8])
                        states->kingCastling[2] = false;
                    else if(board->focusedPiece_ == states->whitePieces_[15] || states->getPiece(board->focus_.x, board->focus_.y) == states->blackPieces_[15])
                        states->kingCastling[3] = false;

                    // If moved set focused piece as nullptr
                    board->focusedPiece_ = nullptr;
                }
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

        // Render chess background
        t_Background.renderBackground();
        // Render chess board
        board->renderChessBoard();

        // If white king was checked
        if(states->isCheckmate(true, states->whitePieces_[12]->getPositionX(), states->whitePieces_[12]->getPositionY()))
        {
            // Set color of king checked
            SDL_SetRenderDrawColor(g_Renderer, 128, 0, 0, 255);
            // Render
            board->renderOnePiece(board->indexToPixel(states->whitePieces_[12]->getPositionX(), true),
                                  board->indexToPixel(states->whitePieces_[12]->getPositionY(), false));
        }
        // If black king was checked
        if(states->isCheckmate(false, states->blackPieces_[12]->getPositionX(), states->blackPieces_[12]->getPositionY()))
        {
            // Set color of king checked
            SDL_SetRenderDrawColor(g_Renderer, 128, 0, 0, 255);
            // Render
            board->renderOnePiece(board->indexToPixel(states->blackPieces_[12]->getPositionX(), true),
                                  board->indexToPixel(states->blackPieces_[12]->getPositionY(), false));
        }
        // Render focused piece
        if(board->focusedPiece_ != nullptr)
        {
            // Render the piece selected
            if((board->focusedPiece_->getName() != PieceName::EMPTY) && (board->focusedPiece_->getColor() == states->getPieceTurn()))
            {
                // Set color of piece selected
                SDL_SetRenderDrawColor(g_Renderer, 255, 105, 180, 255);
                // Render
                board->renderOnePiece(board->indexToPixel(board->focus_.x, true), board->indexToPixel(board->focus_.y, false));
            }

            // Render all possible moves of the focus piece
            if(showHint && (board->focusedPiece_->getColor() == states->getPieceTurn()))
                board->renderPossibleMoves(states);
        }
        // Render all the pieces
        board->renderAllPieces(states);

        // Check game result
        gameResult = states->checkWhoWon();
        if(gameResult != GameResult::NOT_END)
        {
            // Render endgame
            t_EndGame[(int) gameResult].render(board->getXboard(), board->getYboard(), BOARD_HEIGHT, BOARD_WIDTH);

            // Update screen
            updateScreen(g_Window, g_Renderer);

            // Set game mode
            gameState_ = GameMode::GAME_MODE_MAIN_MENU;
            while (true)
            {
                if (SDL_WaitEvent(&e) != 0 && e.type == SDL_QUIT)
                {
                    gameState_ = GameMode::GAME_MODE_QUIT;
                    break;
                }
                if (e.type == SDL_KEYDOWN)
                    break;
            }
            break;
        }

        // Update screen
        updateScreen(g_Window, g_Renderer);
    }
    delete board;
    delete states;
}

void GameState::renderCPU()
{
    bool showHint = true;
    int x = -1, y = -1;

    ChessBoard *board = new ChessBoard();
    States *states = new States();
    GameResult gameResult = GameResult::NOT_END;

    // Set player turn is white piece
    bool player = true;
    bool CPU = false;

    // Player chooses his piece
    player = board->choosePieceTurn(this, states);
    states->setPieceTurn(player);

    // Player plays first
    CPU = false;

    while (gameState_ == GameMode::GAME_MODE_CPU)
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
                case SDLK_z:
                    states->undoMove();
                    break;
                default:
                    break;
                }
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                if(!CPU)
                {
                    // Gets mouse position
                    SDL_GetMouseState(&x, &y);
                    // Updates the index of the focused matrix
                    board->updateFocus((int) x, (int) y);

                    // If there was a move, update the tile vectors and zero the focused tile
                    if(board->checkMovement(states))
                    {
                        // If King move
                        if(board->focusedPiece_ == states->blackPieces_[12])
                        {
                            states->kingCastling[0] = false;
                            states->kingCastling[1] = false;
                        }
                        else if(board->focusedPiece_ == states->whitePieces_[12])
                        {
                            states->kingCastling[2] = false;
                            states->kingCastling[3] = false;
                        }

                        // If Rook move
                        else if(board->focusedPiece_ == states->blackPieces_[15])
                            states->kingCastling[0] = false;
                        else if(board->focusedPiece_ == states->blackPieces_[8])
                            states->kingCastling[1] = false;
                        else if(board->focusedPiece_ == states->whitePieces_[8])
                            states->kingCastling[2] = false;
                        else if(board->focusedPiece_ == states->whitePieces_[15])
                            states->kingCastling[4] = false;

                        // If moved set focused piece as nullptr
                        board->focusedPiece_ = nullptr;
                    }
                    else
                        // If there was no move, the focused piece is the current piece
                        board->focusedPiece_ = states->getPiece(board->focus_.x, board->focus_.y);

                    CPU = true;
                }
            }
        }

        // If save
        if(gameState_ == GameMode::GAME_MODE_SAVE)
        {
            states->saveGame(GameMode::GAME_MODE_CPU);
            gameState_ = GameMode::GAME_MODE_CPU;
        }

        // If load
        if(gameState_ == GameMode::GAME_MODE_LOAD)
        {
            states->loadGame(GameMode::GAME_MODE_CPU);
            gameState_ = GameMode::GAME_MODE_CPU;
        }

        // Clear screen
        SDL_SetRenderDrawColor(g_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(g_Renderer);

        // Render chess background
        t_Background.renderBackground();
        // Render chess board
        board->renderChessBoard();

        // Check game result
        gameResult = states->checkWhoWon();
        if(gameResult == GameResult::NOT_END)
        {
            // CPU play
            if(CPU)
            {
                states->computerMove(!player);
                CPU = false;
            }
        }

        // If white king was checked
        if(states->isCheckmate(true, states->whitePieces_[12]->getPositionX(), states->whitePieces_[12]->getPositionY()))
        {
            // Set color of king checked
            SDL_SetRenderDrawColor(g_Renderer, 128, 0, 0, 255);
            // Render
            board->renderOnePiece(board->indexToPixel(states->whitePieces_[12]->getPositionX(), true),
                                  board->indexToPixel(states->whitePieces_[12]->getPositionY(), false));
        }
        // If black king was checked
        if(states->isCheckmate(false, states->blackPieces_[12]->getPositionX(), states->blackPieces_[12]->getPositionY()))
        {
            // Set color of king checked
            SDL_SetRenderDrawColor(g_Renderer, 128, 0, 0, 255);
            // Render
            board->renderOnePiece(board->indexToPixel(states->blackPieces_[12]->getPositionX(), true),
                                  board->indexToPixel(states->blackPieces_[12]->getPositionY(), false));
        }
        // Render focused piece
        if(board->focusedPiece_ != nullptr)
        {
            // Render the piece selected
            if((board->focusedPiece_->getName() != PieceName::EMPTY) && (board->focusedPiece_->getColor() == states->getPieceTurn()))
            {
                // Set color of piece selected
                SDL_SetRenderDrawColor(g_Renderer, 255, 105, 180, 255);
                // Render
                board->renderOnePiece(board->indexToPixel(board->focus_.x, true), board->indexToPixel(board->focus_.y, false));
            }

            // Render all possible moves of the focus piece
            if(showHint && (board->focusedPiece_->getColor() == states->getPieceTurn()))
                board->renderPossibleMoves(states);
        }
        // Render all the pieces
        board->renderAllPieces(states);

        if(gameResult != GameResult::NOT_END)
        {
            // Render endgame
            t_EndGame[(int) gameResult].render(board->getXboard(), board->getYboard(), BOARD_HEIGHT, BOARD_WIDTH);

            // Update screen
            updateScreen(g_Window, g_Renderer);

            // Set game mode
            gameState_ = GameMode::GAME_MODE_MAIN_MENU;
            while (true)
            {
                if (SDL_WaitEvent(&e) != 0 && e.type == SDL_QUIT)
                {
                    gameState_ = GameMode::GAME_MODE_QUIT;
                    break;
                }
                if (e.type == SDL_KEYDOWN)
                    break;
            }
            break;
        }

        // Update screen
        updateScreen(g_Window, g_Renderer);
    }
    delete board;
    delete states;
}

void GameState::renderChessupMode()
{
    /******************************************************************* todo *******************************************************************/
}

void GameState::renderPauseMenu()
{
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
                isPause = 0;
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
        t_MainMenu.renderBackground();
        // Render main menu
        for(int i = TOTAL_MENU/2; i < TOTAL_MENU; i++)
            g_Menu[ i ].render();

        // Update screen
        updateScreen(g_Window, g_Renderer);
    }
}
