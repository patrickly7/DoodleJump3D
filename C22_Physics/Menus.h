#ifndef _MENUS_H
#define _MENUS_H

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include <memory>

#include "Definitions.h"

class Menus {
protected:
    GameState& state;
    std::unique_ptr<sf::RenderWindow> window;
    virtual void HighlightBoxes(const sf::Vector2i& mousePos) {};
    virtual void DrawButtons() {};
    virtual void MouseClicked(const sf::Vector2i& mousePos) {};
    virtual bool insideSprite(const sf::Vector2i& mousePos, const sf::Sprite& sp);
public:
    Menus(GameState& s);
    ~Menus() {};
    virtual void Update();
};

#endif // !_MENUS_H
