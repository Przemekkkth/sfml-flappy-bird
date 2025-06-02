#include "World.h"
#include "Globals.h"
#include "Game.h"
#include "SharedContext.h"
#include <iostream>
#include <cstdlib>

World::World(SharedContext *sharedContext)
    : m_sharedContext(sharedContext)
{

    if(!m_bgTex.loadFromFile("assets/sprites/background-day.png"))
    {
        std::exit(EXIT_FAILURE);
    }
    m_backgroundSprite = new sf::Sprite(m_bgTex);

    if(!m_baseTex.loadFromFile("assets/sprites/base.png"))
    {
        std::exit(EXIT_FAILURE);
    }
    m_baseSprite = new sf::Sprite(m_baseTex);

    if(!m_pipeTex.loadFromFile("assets/sprites/pipe-red.png"))
    {
        std::exit(EXIT_FAILURE);
    }
    m_pipeSprite = new sf::Sprite(m_pipeTex);

    if(!m_invertedPipeTex.loadFromFile("assets/sprites/pipe-red-i.png"))
    {
        std::exit(EXIT_FAILURE);
    }
    m_invertedPipeSprite = new sf::Sprite(m_invertedPipeTex);

    if(!scoreSFXBuffer.loadFromFile("assets/sfx/point.wav"))
    {
        std::exit(EXIT_FAILURE);
    }
    m_scoreSFX = new sf::Sound(scoreSFXBuffer);

    if(!hitSFXBuffer.loadFromFile("assets/sfx/hit.wav"))
    {
        std::exit(EXIT_FAILURE);
    }
    m_hitSFX = new sf::Sound(hitSFXBuffer);
    m_mainFont = &sharedContext->mainFont;
}

World::~World()
{
    delete m_backgroundSprite;
    delete m_baseSprite;
    delete m_pipeSprite;
    delete m_invertedPipeSprite;
    delete m_scoreSFX;
    delete m_hitSFX;
}

void World::HandlePlayerInput(const std::optional<sf::Event> &event)
{
    if(!bHasCollided) {
        m_bird.HandlePlayerInput(event);
    }
}

void World::Update(const sf::Time time)
{
    if (bHasCollided) {
        return;
    }
    m_bird.Update(time);

    fLevelPosition += (14.0f * time.asSeconds() * GLOBALS::UNIT_SIZE);
    if (fLevelPosition > fSectionWidth) {
        fLevelPosition -= fSectionWidth;
        listSections.pop_front();
        unsigned int pipeY = rand() % (GLOBALS::WINDOW_HEIGHT - (20 * GLOBALS::UNIT_SIZE));
        if (pipeY < 10*GLOBALS::UNIT_SIZE) {
            pipeY = 0;
        }
        listSections.push_back(pipeY);
    }
    checkCollision();
}

void World::Render(sf::RenderWindow& window)
{
    drawBackground(window);
    drawSections(window);
    drawBase(window);
    m_bird.Render(window);
    drawScore(window);
}

bool World::isGameOver()
{
    return bHasCollided;
}

void World::ResetStatus()
{
    fLevelPosition = 550.0f;
    fSectionWidth = GLOBALS::WINDOW_WIDTH / 5;
    bHasCollided = false;
    nScore = 0;
    m_bird.Reset();
    listSections.clear();
    listSections.push_back(0);
    listSections.push_back(0);
    listSections.push_back(0);
    listSections.push_back(0);
    listSections.push_back(0);
}

void World::drawBackground(sf::RenderWindow &window)
{
    window.draw(*m_backgroundSprite);
}

void World::drawBase(sf::RenderWindow &window)
{
    const unsigned int baseHeight = m_baseSprite->getTexture().getSize().y;
    m_baseSprite->setPosition(sf::Vector2f(0.0f, GLOBALS::WINDOW_HEIGHT - baseHeight));
    window.draw(*m_baseSprite);
}

void World::drawSections(sf::RenderWindow &window)
{
    int nSection = 0;
    float nGapSize = 8.0f * GLOBALS::UNIT_SIZE;
    for(auto& listSection : listSections) {
        if (listSection != 0) {
            float xPos = nSection * fSectionWidth + 10 * GLOBALS::UNIT_SIZE - fLevelPosition;
            sf::Sprite pipe(m_pipeTex);
            pipe.setPosition({xPos, float(GLOBALS::WINDOW_HEIGHT - listSection)});
            window.draw(pipe);

            float yPos = GLOBALS::WINDOW_HEIGHT - listSection - nGapSize - m_invertedPipeTex.getSize().y;
            sf::Sprite invertedPipe(m_invertedPipeTex);
            invertedPipe.setPosition({xPos, yPos});
            window.draw(invertedPipe);

            if(int(xPos + m_pipeTex.getSize().x / 2) == int(m_bird.m_x))
            {
                m_scoreSFX->play();
                nScore++;
                if ((nScore%5) == 0) {
                    unsigned int pipeY = rand() % (GLOBALS::WINDOW_HEIGHT - (20 * GLOBALS::UNIT_SIZE));
                    if (pipeY < 10*GLOBALS::UNIT_SIZE) {
                        pipeY = 0;
                    }
                    listSections.push_back(pipeY);
                }
            }
        }
        nSection += 1;
    }
}

void World::drawScore(sf::RenderWindow &window)
{
    sf::Text text{*m_mainFont, "Score: " + std::to_string(nScore)};
    text.setCharacterSize(20);
    text.setPosition({10.0f, 10.0f});
    window.draw(text);
}

void World::checkCollision()
{
    const float groundLevel = GLOBALS::WINDOW_HEIGHT - m_baseTex.getSize().y;
    if (m_bird.m_y + m_bird.HEIGHT / 2.0f >= groundLevel)
    {
        m_hitSFX->play();
        bHasCollided = true;
        return;
    }

    const float gapSize = 8.0f * GLOBALS::UNIT_SIZE;
    const int pipeWidth = m_pipeTex.getSize().x;
    const int bottomPipeHeight = m_pipeTex.getSize().y;
    const int topPipeHeight = m_invertedPipeTex.getSize().y;

    int sectionIndex = 0;

    for (const auto& sectionHeight : listSections)
    {
        if (sectionHeight != 0)
        {
            float pipeX = sectionIndex * fSectionWidth + 10 * GLOBALS::UNIT_SIZE - fLevelPosition;
            float bottomPipeY = GLOBALS::WINDOW_HEIGHT - sectionHeight;
            float topPipeY = bottomPipeY - gapSize - topPipeHeight;

            if (isBirdCollidingWithPipe(pipeX, bottomPipeY, pipeWidth, bottomPipeHeight) ||
                isBirdCollidingWithPipe(pipeX, topPipeY, pipeWidth, topPipeHeight))
            {
                m_hitSFX->play();
                bHasCollided = true;
                return;
            }
        }
        ++sectionIndex;
    }
}

bool World::isBirdCollidingWithPipe(float pipeX, float pipeY, float pipeWidth, float pipeHeight) const
{
    float pipeLeft   = pipeX;
    float pipeRight  = pipeX + pipeWidth;
    float pipeTop    = pipeY;
    float pipeBottom = pipeY + pipeHeight;

    const float birdRadius = std::sqrt((m_bird.WIDTH * 0.5f) * (m_bird.WIDTH * 0.5f) + (m_bird.HEIGHT * 0.5f) * (m_bird.HEIGHT * 0.5f)) * 0.5f;
    float birdX = m_bird.m_x;
    float birdY = m_bird.m_y;

    float closestX = std::clamp(birdX, pipeLeft, pipeRight);
    float closestY = std::clamp(birdY, pipeTop, pipeBottom);

    float dx = birdX - closestX;
    float dy = birdY - closestY;

    return (dx * dx + dy * dy) < (birdRadius * birdRadius);
}

