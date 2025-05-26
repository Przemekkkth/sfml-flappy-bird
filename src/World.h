#ifndef WORLD_H
#define WORLD_H
#include <optional>
#include <deque>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Globals.h"
#include "objects/Bird.h"

class SharedContext;
class World
{
public:
    World(SharedContext* sharedContext = nullptr);
    ~World();
    void HandlePlayerInput(const std::optional<sf::Event>& event);
    void Update(const sf::Time time);
    void Render(sf::RenderWindow& window);
    int Level();
    bool isGameOver();
    void ResetStatus();
private:
    void drawBackground(sf::RenderWindow& window);
    void drawBase(sf::RenderWindow& window);
    void drawSections(sf::RenderWindow& window);
    void drawScore(sf::RenderWindow& window);
    void checkCollision();
    bool isBirdCollidingWithPipe(float pipeX, float pipeY, float pipeWidth, float pipeHeight) const;
    SharedContext* m_sharedContext;
    sf::Font* m_mainFont;

    sf::Texture m_bgTex;
    sf::Sprite* m_backgroundSprite;

    sf::Texture m_baseTex;
    sf::Sprite* m_baseSprite;

    sf::Texture m_pipeTex;
    sf::Sprite* m_pipeSprite;

    sf::Texture m_invertedPipeTex;
    sf::Sprite* m_invertedPipeSprite;

    float fLevelPosition = 500.0f;

    std::deque<int> listSections;
    float fSectionWidth = GLOBALS::WINDOW_WIDTH / 5;

    bool bHasCollided = false;
    int nScore = 0;

    Bird m_bird;

    sf::Sound* m_scoreSFX{nullptr};
    sf::SoundBuffer scoreSFXBuffer;
    sf::Sound* m_hitSFX{nullptr};
    sf::SoundBuffer hitSFXBuffer;
};

#endif // WORLD_H
