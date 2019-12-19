#include "EndGameMenu.h"

EndGameMenu::EndGameMenu(GameState& s, int width, int height, std::shared_ptr<sf::RenderWindow>& rend) : Menus(s) {
    window = rend;

    if (backToMainImage.loadFromFile("../Assets/MainMenuButton.png"))
        printf("Error loading button textures\n");

    backToMainButton.setTexture(backToMainImage, true);
    backToMainButton.setColor(sf::Color::White);

    backToMainButton.setPosition(sf::Vector2f(512.0f, 407.0f));

    sprites = { backToMainButton };
}

void EndGameMenu::MouseClicked(const sf::Vector2i& mousePos) {
    if (insideSprite(mousePos, backToMainButton))
        state = GameState::MAIN_MENU;
}
