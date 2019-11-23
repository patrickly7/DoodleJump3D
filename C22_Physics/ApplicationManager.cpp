#include "ApplicationManager.h"
ApplicationManager::ApplicationManager() {


    state = GameState::PAUSE_MENU;
}
ApplicationManager::~ApplicationManager() {}


void ApplicationManager::Run(const std::string& name, int size,
    bool fullscreen, bool borderless) {
    using namespace Simplex;
    std::unique_ptr<MainMenu> mainMenu = std::make_unique<MainMenu>(state, 1260, 780);
    std::unique_ptr<PauseMenu> pauseMenu = std::make_unique<PauseMenu>(state, 1260, 780);
    //std::unique_ptr<ExitMenu> mainMenu = std::make_unique<ExitMenu>();
    //Application* app = new Application();
    //app->Init(name, size, fullscreen, borderless);
    while (state != GameState::CLOSE) {
        GameState previous = state;
        switch (state)
        {
        case GameState::MAIN_MENU:
            mainMenu->Update();
            break;
        case GameState::GAME:
            //state = app->RunFrame();
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
            if (previous == GameState::MAIN_MENU && state == GameState::GAME) {

            }
        }
    }
    //SafeDelete(app);
}