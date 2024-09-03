#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <memory>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>

#include "State.h"
#include "Game.h"

class GameOver : public Engine::State
{
public:
    GameOver(std::shared_ptr<Context> &context);
    ~GameOver();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;

private:
    sf::Sprite grass;

    std::shared_ptr<Context> context;
    sf::Text gameOverTitle;
    sf::Text retryButton;
    sf::Text exitButton;

    bool isRetryButtonSelected;
    bool isRetryButtonPressed;

    bool isExitButtonSelected;
    bool isExitButtonPressed;

    sf::SoundBuffer buttonChangeBuffer;
    sf::Sound buttonChangeSound;

    sf::SoundBuffer selectBuffer;
    sf::Sound selectSound;
};

#endif // GAMEOVER_H
