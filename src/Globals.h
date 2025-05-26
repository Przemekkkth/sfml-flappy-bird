#ifndef GLOBALS_H
#define GLOBALS_H
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/String.hpp>

namespace GLOBALS {
    const unsigned int UNIT_SIZE = 12;
    const unsigned int WINDOW_WIDTH = 80*UNIT_SIZE;
    const unsigned int WINDOW_HEIGHT = 48*UNIT_SIZE;
    const sf::Vector2u WINDOW_SIZE(WINDOW_WIDTH, WINDOW_HEIGHT);
    const sf::String WINDOW_TITLE("SFML FLAPPY BIRD");
}

#endif // GLOBALS_H
