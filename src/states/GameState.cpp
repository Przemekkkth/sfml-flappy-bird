#include "GameState.h"
#include "StateManager.h"
#include "../Globals.h"
#include "../Game.h"
#include <SFML/Window/Event.hpp>


GameState::GameState(StateManager *stateManager)
    : BaseState(stateManager)
{

}

GameState::~GameState()
{

}

void GameState::OnCreate()
{
    m_world = new World(GetStateManager()->GetContext());

}

void GameState::OnDestroy()
{
    delete m_world;
}

void GameState::Activate()
{
    if(!m_isPaused) {
        m_world->ResetStatus();
    }
    else {
        m_isPaused = false;
    }
}

void GameState::Deactivate()
{

}

void GameState::Update(const sf::Time &time)
{
    m_world->Update(time);
    if (m_world->isGameOver())
    {
        m_stateMgr->SwitchTo(StateType::GameOver);
    }
}

void GameState::Draw()
{
    sf::RenderWindow* window = GetStateManager()->GetContext()->m_window->GetRenderWindow();
    m_world->Render(*window);
}

void GameState::HandlePlayerInput(const std::optional<sf::Event> &event)
{
    if (!m_isPaused) {
        m_world->HandlePlayerInput(event);
    }
    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->scancode == sf::Keyboard::Scancode::P)
        {
            m_isPaused = true;
            m_stateMgr->SwitchTo(StateType::Paused);
        }
    }
}
