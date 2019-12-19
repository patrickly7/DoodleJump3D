#ifndef _END_GAME_MENU_H
#define _END_GAME_MENU_H

#include "Menus.h"

class EndGameMenu : public Menus {
public:
    EndGameMenu(GameState& s, int width, int height, std::shared_ptr<sf::RenderWindow>& wind);
private:
    sf::Sprite backToMainButton;
    sf::Texture backToMainImage;
    void MouseClicked(const sf::Vector2i& mousePos);
};

#endif // !_END_GAME_MENU_H

