#include "ApplicationManager.h"
ApplicationManager::ApplicationManager() {


    state = GameState::MAIN_MENU;
}
ApplicationManager::~ApplicationManager() {}


void ApplicationManager::Run(const std::string& name, int size,
    bool fullscreen, bool borderless) {
    using namespace Simplex;
    auto mainMenu = std::make_unique<MainMenu>(state, 1260, 780);
    auto menuWindow = mainMenu->GetWindow();
    auto pauseMenu = std::make_unique<PauseMenu>(state, 1260, 780, menuWindow);
    auto endMenu = std::make_unique<EndGameMenu>(state, 1260, 780, menuWindow);
    auto app = std::make_unique<Application>(state);
    app->Init(name, size, fullscreen, borderless);
    auto gameWindow = app->GetWindow();
    gameWindow->setVisible(false);
    while (state != GameState::CLOSE) {
        GameState previous = state;
        switch (state)
        {
        case GameState::MAIN_MENU:
            mainMenu->Update();
            break;
        case GameState::GAME:
            app->RunFrame();
            break;
        case GameState::PAUSE_MENU:
            pauseMenu->Update();
            break;
        case GameState::END_MENU:
            endMenu->Update();
            break;
        default:
            break;
        }
        if (previous != state) {
            if (state == GameState::GAME) {
                if(previous == GameState::PAUSE_MENU)
                    gameWindow->setVisible(true);
				else if (previous == GameState::MAIN_MENU)
				{
					app->m_timePlaying = 0;
					app->ResetStartingPosition();
					gameWindow->setVisible(true);
				}
                else { //starting new game
                    /*app.reset(new Application(state));
                    app->Init(name, size, fullscreen, borderless);
                    gameWindow = app->GetWindow();*/
                    gameWindow->setVisible(true);
                }
                menuWindow->close();
            }
            if (previous == GameState::GAME) {
                menuWindow->create(sf::VideoMode(gameWindow->getSize().x, gameWindow->getSize().y), "DoodleJump3D");
                gameWindow->setVisible(false);
                if (state == GameState::END_MENU) {
                    float sc = app->m_timePlaying;
                    endMenu->SetScore(sc);
					scores.push_back(sc);
					endMenu->SetHighScore(*max_element(std::begin(scores), std::end(scores)));
					app->m_timePlaying = 0;
                }
            }
        }
    }
    //SafeDelete(app);
}