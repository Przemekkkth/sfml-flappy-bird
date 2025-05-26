#ifndef SHAREDCONTEXT_H
#define SHAREDCONTEXT_H

#include "Window.h"
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <iostream>
#include <cstdlib>

struct SharedContext{
    SharedContext()
        : m_window(nullptr)
    {
        if (!mainFont.openFromFile("assets/fonts/04B_19.ttf"))
        {
            exit(EXIT_FAILURE);
        }
    }

    ~SharedContext()
    {

    }

    Window* m_window;
    sf::Font mainFont;
};

#endif // SHAREDCONTEXT_H
