#ifndef BIRD_H
#define BIRD_H
#include "../utils/Animation.h"
#include "../Globals.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

class Bird
{
public:
    Bird();
    ~Bird();
    void HandlePlayerInput(const std::optional<sf::Event>& event);
    void Render(sf::RenderWindow& window);
    void Update(const sf::Time time);
    void Reset();
    void SetGravity(float newGravity);
    const float m_x = GLOBALS::WINDOW_WIDTH / 3.0f;
    float m_y = GLOBALS::WINDOW_HEIGHT / 2.0f;
    const uint WIDTH = 34;
    const uint HEIGHT = 24;
private:
    void Push();
    void CheckYBoundary();
    sf::Texture m_birdTex;
    sf::Sprite* m_birdSprite;
    Animation* m_anim;

    float m_velocity = 0.0f;
    float m_acceleration = 0.0f;
    float m_gravity = 1000.0f;

    sf::Sound* m_pushSFX{nullptr};
    sf::SoundBuffer pushSFXBuffer;
};

#endif // BIRD_H
