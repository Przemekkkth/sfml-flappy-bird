#include "IntroState.h"
#include "StateManager.h"
#include "../Globals.h"
#include <iostream>
#include <SFML/Window/Event.hpp>

IntroState::IntroState(StateManager *stateManager)
    : BaseState(stateManager), m_title(m_font), m_hintText(m_font), m_authorName(m_font),
    blinkInterval(sf::seconds(0.35f)), blinkTimer(sf::Time::Zero), isVisible(true)
{
    if(!m_font.openFromFile("assets/fonts/04B_19.ttf"))
    {
        exit(EXIT_FAILURE);
    }

    if(!m_backgroundTexture.loadFromFile("assets/sprites/background-day.png"))
    {
        exit(EXIT_FAILURE);
    }

    if(!m_avatarTexture.loadFromFile("assets/sprites/avatar.png"))
    {
        exit(EXIT_FAILURE);
    }

    if(!m_sfmlLogoTexture.loadFromFile("assets/sprites/sfml-logo-small.png"))
    {
        exit(EXIT_FAILURE);
    }

    m_title.setFont(m_font);
    m_title.setString("SFML Flappy Bird");
    m_title.setCharacterSize(50);
    m_title.setFillColor(sf::Color::White);
    m_title.setOrigin( sf::Vector2f(m_title.getLocalBounds().size.x / 2, m_title.getLocalBounds().size.y / 2));
    m_title.setPosition(sf::Vector2f(GLOBALS::WINDOW_WIDTH/2.0f, 50));

    m_authorName.setFont(m_font);
    m_authorName.setString("by Przemekkkth");
    m_authorName.setCharacterSize(35);
    m_authorName.setFillColor(sf::Color::White);
    m_authorName.setOrigin( sf::Vector2f(m_authorName.getLocalBounds().size.x / 2.0f, m_authorName.getLocalBounds().size.y / 2.0f));
    m_authorName.setPosition(sf::Vector2f(GLOBALS::WINDOW_WIDTH/2.0f, 150));

    m_hintText.setFont(m_font);
    m_hintText.setString("Press any key to continue...");
    m_hintText.setCharacterSize(25);
    m_hintText.setFillColor(sf::Color::White);
    m_hintText.setOrigin( sf::Vector2f(m_hintText.getLocalBounds().size.x / 2, m_hintText.getLocalBounds().size.y / 2));
    m_hintText.setPosition(sf::Vector2f(GLOBALS::WINDOW_WIDTH/2.0f, 500));
}

IntroState::~IntroState()
{

}

void IntroState::OnCreate()
{

}

void IntroState::OnDestroy()
{

}

void IntroState::Activate()
{
}

void IntroState::Deactivate()
{

}

void IntroState::Update(const sf::Time &time)
{
    blinkTimer += time;

    if (blinkTimer >= blinkInterval)
    {
        blinkTimer = sf::Time::Zero;

        isVisible = !isVisible;
    }
}

void IntroState::Draw()
{
    sf::Sprite bgSprite(m_backgroundTexture);
    GetStateManager()->GetContext()->m_window->Draw(bgSprite);
    GetStateManager()->GetContext()->m_window->Draw(m_title);
    GetStateManager()->GetContext()->m_window->Draw(m_authorName);

    sf::Sprite avatarSprite(m_avatarTexture);
    avatarSprite.setPosition({125.0f, 200.0f});
    GetStateManager()->GetContext()->m_window->Draw(avatarSprite);

    sf::Sprite logoSprite(m_sfmlLogoTexture);
    logoSprite.setPosition({425.0f, 275.0f});
    GetStateManager()->GetContext()->m_window->Draw(logoSprite);

    if(isVisible)
    {
        GetStateManager()->GetContext()->m_window->Draw(m_hintText);
    }
}

void IntroState::HandlePlayerInput(const std::optional<sf::Event> &event)
{
    if (event->getIf<sf::Event::KeyPressed>())
    {
        m_stateMgr->SwitchTo(StateType::Game);
        m_stateMgr->Remove(StateType::Intro);
    }
}
