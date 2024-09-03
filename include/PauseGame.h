#ifndef PAUSEGAME_H
#define PAUSEGAME_H

#include <memory>

#include <SFML/Graphics/Text.hpp>

#include "State.h"
#include "Game.h"

class PauseGame : public Engine::State
{
public:
    PauseGame(std::shared_ptr<Context> &context);
    ~PauseGame();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;

private:
    std::shared_ptr<Context> context;
    sf::Text pauseTitle;
};

#endif // PAUSEGAME_H
