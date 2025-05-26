#include "PausedState.h"
#include "../Globals.h"
#include "StateManager.h"
#include <iostream>

PausedState::PausedState(StateManager *stateManager)
    : BaseState(stateManager), m_title(m_font), m_hintText(m_font), m_blinkInterval(sf::seconds(0.35f)),
    m_blinkTimer(sf::Time::Zero), m_isVisible(true)
{
    SetTransparent(true);

    if(!m_font.openFromFile("assets/fonts/04B_19.ttf"))
    {
        exit(EXIT_FAILURE);
    }

    if(!m_backgroundTexture.loadFromFile("assets/sprites/background-day.png"))
    {
        exit(EXIT_FAILURE);
    }

    m_title.setFont(m_font);
    m_title.setString("PAUSED");
    m_title.setCharacterSize(50);
    m_title.setFillColor(sf::Color::White);
    m_title.setOrigin( sf::Vector2f(m_title.getLocalBounds().size.x / 2, m_title.getLocalBounds().size.y / 2));
    m_title.setPosition(sf::Vector2f(GLOBALS::WINDOW_WIDTH/2.0f, 150));

    m_hintText.setFont(m_font);
    m_hintText.setString("Press 'P' key to continue...");
    m_hintText.setCharacterSize(25);
    m_hintText.setFillColor(sf::Color::White);
    m_hintText.setOrigin( sf::Vector2f(m_hintText.getLocalBounds().size.x / 2, m_hintText.getLocalBounds().size.y / 2));
    m_hintText.setPosition(sf::Vector2f(GLOBALS::WINDOW_WIDTH/2.0f, 400));
}

PausedState::~PausedState()
{

}

void PausedState::OnCreate()
{

}

void PausedState::OnDestroy()
{

}

void PausedState::Activate()
{

}

void PausedState::Deactivate()
{

}

void PausedState::Update(const sf::Time &time)
{
    m_blinkTimer += time;

    if (m_blinkTimer >= m_blinkInterval)
    {
        m_blinkTimer = sf::Time::Zero;

        m_isVisible = !m_isVisible;
    }
}

void PausedState::Draw()
{
    GetStateManager()->GetContext()->m_window->Draw(m_title);
    if(m_isVisible)
    {
        GetStateManager()->GetContext()->m_window->Draw(m_hintText);
    }
}

void PausedState::HandlePlayerInput(const std::optional<sf::Event> &event)
{
    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
    {

        if (keyPressed->scancode == sf::Keyboard::Scancode::P)
        {
            m_stateMgr->SwitchTo(StateType::Game);
        }
    }
}
