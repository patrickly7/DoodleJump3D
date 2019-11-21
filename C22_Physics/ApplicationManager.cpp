#include "ApplicationManager.h"
ApplicationManager::ApplicationManager() {


    state = GameState::MAIN_MENU;
}
ApplicationManager::~ApplicationManager() {}


void ApplicationManager::Run(const std::string& name, int size,
    bool fullscreen, bool borderless) {
    using namespace Simplex;
    //Application* app = new Application();
    MainMenu* main = new MainMenu(state, 1260, 780);
    //app->Init(name, size, fullscreen, borderless);
    while (state != GameState::CLOSE) {
        GameState previous = state;
        switch (state)
        {
        case GameState::MAIN_MENU:
            main->Update();
            break;
        case GameState::GAME:
            //state = app->RunFrame();
            break;
        case GameState::PAUSE_MENU:
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