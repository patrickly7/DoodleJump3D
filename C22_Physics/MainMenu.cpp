#include "MainMenu.h"

MainMenu::MainMenu(GameState& s, int width, int height) : Menus(s) {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), "DoodleJump3D");
    
    if (!(playImage.loadFromFile("../Assets/PlayButton.png") &&
          exitImage.loadFromFile("../Assets/ExitButton.png"))) 
        printf("Error loading button textures\n");
    
    playButton.setTexture(playImage, true);
    exitButton.setTexture(exitImage, true);
    playButton.setColor(sf::Color::White);
    exitButton.setColor(sf::Color::White);


    playButton.setPosition(sf::Vector2f(512.0f, 207.0f));
    exitButton.setPosition(sf::Vector2f(512.0f, 407.0f));

}

void MainMenu::DrawButtons() {
    window->draw(playButton);
    window->draw(exitButton);
}

void MainMenu::MouseClicked(const sf::Vector2i& mousePos) {
    if (insideSprite(mousePos, playButton))
        state = GameState::GAME;

    if (insideSprite(mousePos, exitButton))
        state = GameState::CLOSE;
}

void MainMenu::HighlightBoxes(const sf::Vector2i& mousePos) {
    sf::IntRect playButtonArea = playButton.getTextureRect();
    sf::IntRect exitButtonArea = exitButton.getTextureRect();
    printf("%d\n", mousePos.x);
    if (insideSprite(mousePos, playButton))
        playButton.setColor(sf::Color::Blue);
    else
        playButton.setColor(sf::Color::White);

    if (insideSprite(mousePos, exitButton))
        exitButton.setColor(sf::Color::Blue);
    else
        exitButton.setColor(sf::Color::White);

}