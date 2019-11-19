#ifndef _MAIN_MENU_H
#define _MAIN_MENU_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include <memory>

class MainMenu {
public:
    void Update();
    void MakeMenu();
    MainMenu(int width, int height);
    ~MainMenu();
private:
    sf::Sprite playButton;
    sf::Sprite exitButton;
    sf::Texture playImage;
    sf::Texture exitImage;
    std::unique_ptr<sf::RenderWindow> window;
};

#endif // !_MAIN_MENU_H

