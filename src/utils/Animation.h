#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
class Animation
{
public:
    Animation(sf::Sprite& sprite, sf::Texture& texture,
              int frameWidth, int frameHeight, int frameCount, float frameTime);

    void Update(sf::Time deltaTime);
private:
    sf::Sprite& sprite;
    int frameWidth, frameHeight;
    int frameCount;
    float frameTime;
    int currentFrame;
    float elapsed;
};

#endif // ANIMATION_H

