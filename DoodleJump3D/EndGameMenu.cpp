#include "EndGameMenu.h"

EndGameMenu::EndGameMenu(GameState& s, int width, int height, std::shared_ptr<sf::RenderWindow>& rend) : Menus(s) {
    window = rend;

    if (backToMainImage.loadFromFile("../Assets/MainMenuButton.png"))
        printf("Error loading button textures\n");

    backToMainButton.setTexture(backToMainImage, true);
    backToMainButton.setColor(sf::Color::White);

    backToMainButton.setPosition(sf::Vector2f(512.0f, 407.0f));
    font.loadFromFile("../Assets/Lato-Bold.ttf");
    sprites = { backToMainButton };
    score.setFont(font);
    score.setCharacterSize(30);
    score.setFillColor(sf::Color::Red);
    score.setPosition(sf::Vector2f(512.0f, 207.0f));
}

void EndGameMenu::MouseClicked(const sf::Vector2i& mousePos) {
    if (insideSprite(mousePos, backToMainButton))
        state = GameState::MAIN_MENU;
}

void EndGameMenu::SetScore(float sc) {
    score.setString("SCORE: " + std::to_string((int)sc * 50));
    texts = std::vector<sf::Text>();
    texts.push_back(score);
}
