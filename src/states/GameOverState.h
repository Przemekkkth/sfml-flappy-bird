#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H
#include "BaseState.h"
class GameOverState : public BaseState
{
public:
    GameOverState(StateManager* stateManager);
    virtual ~GameOverState();
    // BaseState interface
public:
    virtual void OnCreate() override;
    virtual void OnDestroy() override;
    virtual void Activate() override;
    virtual void Deactivate() override;
    virtual void Update(const sf::Time &time) override;
    virtual void Draw() override;
    virtual void HandlePlayerInput(const std::optional<sf::Event> &event) override;
private:
    sf::Texture m_gameOverTex;
    sf::Text m_hintText;
    sf::Font m_font;
    sf::Time m_blinkInterval;
    sf::Time m_blinkTimer;
    sf::Texture m_m_backgroundTexture;
    bool m_isVisible;
};

#endif // GAMEOVERSTATE_H
