#ifndef _MENUS_H
#define _MENUS_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include <memory>
#include <vector>

#include "Definitions.h"

class Menus {
protected:
    GameState& state;
    std::vector<sf::Sprite> sprites;
    std::shared_ptr<sf::RenderWindow> window;
    void HighlightBoxes(const sf::Vector2i& mousePos);
    void DrawButtons();
    virtual void MouseClicked(const sf::Vector2i& mousePos) {};
    bool insideSprite(const sf::Vector2i& mousePos, const sf::Sprite& sp);
public:
    Menus(GameState& s);
    ~Menus() {};
    virtual void Update();
};

#endif // !_MENUS_H
