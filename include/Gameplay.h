#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#pragma once

#include <memory>
#include <array>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio.hpp>

#include "Game.h"
#include "State.h"
#include "Snake.h"
#include "SnakeObserver.h"

class Gameplay : public Engine::State, SnakeObserver
{
public:
    Gameplay(std::shared_ptr<Context> &context);
    ~Gameplay();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;
    void Pause() override;
    void Start() override;
    int getScore();

    virtual void onNotifyEatFood() override {
        score += 1;
        scoreText.setString("Score : " + std::to_string(score));
        if(moveInterval >= 0.01)
        {
            moveInterval -= 0.01;
        }
    }

private:
    std::shared_ptr<Context> context;
    sf::Sprite grass;
    sf::Sprite food;
    std::array<sf::Sprite, 4> walls;
    Snake snake;

    sf::Text scoreText;
    int score;
    float moveInterval;

    sf::Vector2f snakeDirection;
    sf::Time elapsedTime;

    bool isPaused;

    sf::SoundBuffer gameOverBuffer;
    sf::Sound gameOverSound;

    sf::SoundBuffer eatBuffer;
    sf::Sound eatSound;

    sf::SoundBuffer selectBuffer;
    sf::Sound selectSound;
};
#endif // GAMEPLAY_H
