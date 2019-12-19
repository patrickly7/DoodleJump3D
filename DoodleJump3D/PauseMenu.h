#ifndef _PAUSE_MENU_H
#define _PAUSE_MENU_H

#include "Menus.h"

class PauseMenu : public Menus
{
public:
    PauseMenu(GameState& s, int width, int height, std::shared_ptr<sf::RenderWindow>& wind);
private:
    sf::Sprite continueButton;
    sf::Sprite backToMainButton;
    sf::Texture continueImage;
    sf::Texture backToMainImage;
    void MouseClicked(const sf::Vector2i& mousePos);
};


#endif // !_PAUSE_MENU_H


