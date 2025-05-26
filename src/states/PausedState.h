#ifndef PAUSEDSTATE_H
#define PAUSEDSTATE_H
#include "BaseState.h"

class PausedState : public BaseState
{
public:
    PausedState(StateManager* stateManager);
    ~PausedState();

    virtual void OnCreate() override;
    virtual void OnDestroy() override;
    virtual void Activate() override;
    virtual void Deactivate() override;
    virtual void Update(const sf::Time &time) override;
    virtual void Draw() override;
    virtual void HandlePlayerInput(const std::optional<sf::Event> &event) override;

private:
    sf::Text m_title;
    sf::Text m_hintText;
    sf::Font m_font;
    sf::Time m_blinkInterval;
    sf::Time m_blinkTimer;
    sf::Texture m_backgroundTexture;
    bool m_isVisible;
};

#endif // PAUSEDSTATE_H
