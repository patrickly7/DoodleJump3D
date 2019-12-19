#include "MainMenu.h"

MainMenu::MainMenu(GameState& s, int width, int height) : Menus(s) {
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), "DoodleJump3D");

	font.loadFromFile("../Assets/Lato-Bold.ttf");
	gameTitle.setFont(font);
	gameTitle.setCharacterSize(50);
	gameTitle.setFillColor(sf::Color::White);
	gameTitle.setPosition(sf::Vector2f(462.0f, 77.0f));

	gameTitle.setString("SCRIBBLE HOP");
	texts.push_back(gameTitle);

    if (!(playImage.loadFromFile("../Assets/PlayButton.png") &&
          exitImage.loadFromFile("../Assets/ExitButton.png"))) 
        printf("Error loading button textures\n");
    
    playButton.setTexture(playImage, true);
    exitButton.setTexture(exitImage, true);
    playButton.setColor(sf::Color::White);
    exitButton.setColor(sf::Color::White);

    playButton.setPosition(sf::Vector2f(512.0f, 207.0f));
    exitButton.setPosition(sf::Vector2f(512.0f, 407.0f));

    sprites = { playButton, exitButton };
}

void MainMenu::MouseClicked(const sf::Vector2i& mousePos) {
    if (insideSprite(mousePos, playButton))
        state = GameState::GAME;

    if (insideSprite(mousePos, exitButton))
        state = GameState::CLOSE;
}
