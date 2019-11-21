#ifndef _MAIN_MENU_H
#define _MAIN_MENU_H

#include "Menus.h"

class MainMenu : public Menus{
public:
    MainMenu(GameState& s, int width, int height);
private:
    sf::Sprite playButton;
    sf::Sprite exitButton;
    sf::Texture playImage;
    sf::Texture exitImage;
    void DrawButtons();
    void HighlightBoxes(const sf::Vector2i& mousePos);
    void MouseClicked(const sf::Vector2i& mousePos);
};

#endif // !_MAIN_MENU_H

