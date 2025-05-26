#include "GameOverState.h"
#include "StateManager.h"
GameOverState::GameOverState(StateManager *stateManager)
    : BaseState(stateManager), m_hintText(m_font), m_blinkInterval(sf::seconds(0.35f)), m_blinkTimer(sf::Time::Zero),
    m_isVisible(true)
{
    SetTransparent(true);
    if(!m_gameOverTex.loadFromFile("assets/sprites/gameOver_bg.png"))
    {
        exit(EXIT_FAILURE);
    }

    if(!m_font.openFromFile("assets/fonts/04B_19.ttf"))
    {
        exit(EXIT_FAILURE);
    }

    m_hintText.setFont(m_font);
    m_hintText.setString("Press any key to continue...");
    m_hintText.setCharacterSize(25);
    m_hintText.setFillColor(sf::Color::White);
    m_hintText.setOrigin( sf::Vector2f(m_hintText.getLocalBounds().size.x / 2, m_hintText.getLocalBounds().size.y / 2));
    m_hintText.setPosition(sf::Vector2f(GLOBALS::WINDOW_WIDTH/2.0f, 500));
}

GameOverState::~GameOverState()
{

}

void GameOverState::OnCreate()
{

}

void GameOverState::OnDestroy()
{

}

void GameOverState::Activate()
{

}

void GameOverState::Deactivate()
{

}

void GameOverState::Update(const sf::Time &time)
{
    m_blinkTimer += time;

    if (m_blinkTimer >= m_blinkInterval)
    {
        m_blinkTimer = sf::Time::Zero;

        m_isVisible = !m_isVisible;
    }
}

void GameOverState::Draw()
{
    sf::Sprite sprite{m_gameOverTex};
    sprite.setOrigin({m_gameOverTex.getSize().x/2.0f, m_gameOverTex.getSize().y/2.0f});
    sprite.setPosition({GLOBALS::WINDOW_WIDTH/2.0f, GLOBALS::WINDOW_HEIGHT/2.0f});
    GetStateManager()->GetContext()->m_window->GetRenderWindow()->draw(sprite);
    if(m_isVisible)
    {
        GetStateManager()->GetContext()->m_window->Draw(m_hintText);
    }
}

void GameOverState::HandlePlayerInput(const std::optional<sf::Event> &event)
{
    if (event->getIf<sf::Event::KeyPressed>())
    {
        m_stateMgr->SwitchTo(StateType::Game);
    }
}
