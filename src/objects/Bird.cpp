#include "Bird.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

Bird::Bird()
{
    if(!m_birdTex.loadFromFile("assets/sprites/bird.png"))
    {
        std::exit(EXIT_FAILURE);
    }
    m_birdSprite = new sf::Sprite(m_birdTex);
    m_birdSprite->setPosition({m_x, m_y});
    m_birdSprite->setOrigin({WIDTH / 2.0f, HEIGHT / 2.0f});

    m_anim = new Animation(*m_birdSprite, m_birdTex, WIDTH, HEIGHT, 3, 0.1);

    if(!pushSFXBuffer.loadFromFile("assets/sfx/wing.wav"))
    {
        std::exit(EXIT_FAILURE);
    }
    m_pushSFX = new sf::Sound(pushSFXBuffer);
}

Bird::~Bird()
{
    delete m_anim;
    delete m_pushSFX;
}

void Bird::HandlePlayerInput(const std::optional<sf::Event> &event)
{
    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
        {
            Push();
            if(m_pushSFX){
                m_pushSFX->play();
            }
        }
    }
}

void Bird::Render(sf::RenderWindow &window)
{
    window.draw(*m_birdSprite);
}

void Bird::Update(const sf::Time time)
{
    m_anim->Update(time);
    m_acceleration += (m_gravity * time.asSeconds());
    if(m_acceleration > m_gravity) {
        m_acceleration = m_gravity;
    }

    m_velocity +=  (m_acceleration * time.asSeconds());
    m_y += (m_velocity * time.asSeconds());

    if (m_velocity > 0.0) {
        m_birdSprite->setRotation(sf::degrees(45.0f));
    }
    else {
        m_birdSprite->setRotation(sf::degrees(-45.0f));
    }
    CheckYBoundary();
    m_birdSprite->setPosition({m_x, m_y});
}

void Bird::Reset()
{
    m_y = GLOBALS::WINDOW_HEIGHT / 2.0f;
    m_velocity = 0.0f;
    m_acceleration = 0.0f;
    m_birdSprite->setRotation(sf::degrees(0.0f));
}

void Bird::SetGravity(float newGravity)
{
    m_gravity = newGravity;
}

void Bird::CheckYBoundary()
{
    if (m_y < 0.0f) {
        m_y = 0.0f;
    }
}

void Bird::Push()
{
    m_acceleration = 0.0f;
    m_velocity = -130.f;
}

