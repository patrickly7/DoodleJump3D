#include "ApplicationManager.h"
ApplicationManager::ApplicationManager() {


    state = GameState::MAIN_MENU;
}
ApplicationManager::~ApplicationManager() {}


void ApplicationManager::Run(const std::string& name, int size,
    bool fullscreen, bool borderless) {
    using namespace Simplex;
    std::unique_ptr<MainMenu> mainMenu = std::make_unique<MainMenu>(state, 1260, 780);
    auto menuWindow = mainMenu->GetWindow();
    std::unique_ptr<PauseMenu> pauseMenu = std::make_unique<PauseMenu>(state, 1260, 780, menuWindow);
    //std::unique_ptr<EndMenu> endMenu = std::make_unique<EndMenu>();
    std::unique_ptr<Application> app = std::make_unique<Application>(state);
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
            break;
        default:
            break;
        }
        if (previous != state) {
            if (state == GameState::GAME) {
                menuWindow->close();
                gameWindow->setVisible(true);
            }
            if (previous == GameState::GAME) {
                menuWindow->create(sf::VideoMode(gameWindow->getSize().x, gameWindow->getSize().y), "DoodleJump3D");
                gameWindow->setVisible(false);
            }
        }
    }
    //SafeDelete(app);
}