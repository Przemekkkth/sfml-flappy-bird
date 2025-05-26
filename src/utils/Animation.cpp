#include "Animation.h"

Animation::Animation(sf::Sprite &sprite, sf::Texture &texture, int frameWidth, int frameHeight, int frameCount, float frameTime)
: sprite(sprite), frameWidth(frameWidth), frameHeight(frameHeight),
  frameCount(frameCount), frameTime(frameTime), currentFrame(0), elapsed(0.f)
{
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect({0, 0}, {frameWidth, frameHeight}));
}

void Animation::Update(sf::Time deltaTime)
{
    elapsed += deltaTime.asSeconds();
    if (elapsed >= frameTime) {
        elapsed = 0.f;
        currentFrame = (currentFrame + 1) % frameCount;
        sprite.setTextureRect(sf::IntRect({currentFrame * frameWidth, 0}, {frameWidth, frameHeight}));
    }
}
