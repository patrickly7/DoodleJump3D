#include "Menus.h"

Menus::Menus(GameState& s) : state(s) {}

void Menus::Update() {
    sf::Event event;
    window->clear(sf::Color(0, 128, 128));
    while (window->pollEvent(event)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
        if (event.type == sf::Event::MouseMoved) HighlightBoxes(mousePos);
        else if (event.type == sf::Event::MouseButtonReleased &&
            event.mouseButton.button == sf::Mouse::Left)  MouseClicked(mousePos);
    }
    DrawButtons();
    DrawTexts();
    window->display();
}

bool Menus::insideSprite(const sf::Vector2i& mousePos, const sf::Sprite& sp) {
    sf::IntRect area = sp.getTextureRect();
    sf::Vector2f spPos = sp.getPosition(); //top-left
    bool a = mousePos.x >= spPos.x && mousePos.x <= spPos.x + area.width;
    bool b = mousePos.y >= spPos.y && mousePos.y <= spPos.y + area.height;
    return a && b;
}

void Menus::HighlightBoxes(const sf::Vector2i& mousePos) {
    for (auto& sp : sprites) {
        if (insideSprite(mousePos, sp))
            sp.setColor(sf::Color::Blue);
        else
            sp.setColor(sf::Color::White);
    }
}

void Menus::DrawButtons() {
    for (auto& sp : sprites) window->draw(sp);
}

void Menus::DrawTexts() {
    for (auto& t : texts) {
        window->draw(t);
    }
}