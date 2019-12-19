#include "PauseMenu.h"

PauseMenu::PauseMenu(GameState& s, int width, int height, std::shared_ptr<sf::RenderWindow>& rend) : Menus(s) {
    window = rend;

    if (!(continueImage.loadFromFile("../Assets/ContinueButton.png") &&
        backToMainImage.loadFromFile("../Assets/MainMenuButton.png")))
        printf("Error loading button textures\n");

    continueButton.setTexture(continueImage, true);
    backToMainButton.setTexture(backToMainImage, true);
    continueButton.setColor(sf::Color::White);
    backToMainButton.setColor(sf::Color::White);


    continueButton.setPosition(sf::Vector2f(512.0f, 207.0f));
    backToMainButton.setPosition(sf::Vector2f(512.0f, 407.0f));

    sprites = { continueButton, backToMainButton };
}

void PauseMenu::MouseClicked(const sf::Vector2i& mousePos) {
    if (insideSprite(mousePos, continueButton))
        state = GameState::GAME;

    if (insideSprite(mousePos, backToMainButton))
        state = GameState::MAIN_MENU;
}
