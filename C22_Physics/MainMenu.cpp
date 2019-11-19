#include "MainMenu.h"

MainMenu::MainMenu(int width, int height) {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), "DoodleJump3D");
    
    if (!(playImage.loadFromFile("../Assets/PlayButton.png") &&
          exitImage.loadFromFile("../Assets/ExitButton.png"))) 
        printf("Error loading button textures\n");
    
    playButton.setTexture(playImage, true);
    exitButton.setTexture(exitImage, true);

    playButton.setPosition(sf::Vector2f(512.0f, 207.0f));
    exitButton.setPosition(sf::Vector2f(512.0f, 407.0f));

}

void MainMenu::Update() {
    window->clear();
    window->draw(playButton);
    window->draw(exitButton);
    window->display();
}