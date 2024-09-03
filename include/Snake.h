#ifndef SNAKE_H
#define SNAKE_H

#pragma once

#include <list>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "SnakeObserver.h"
#include "Subject.h"


class Snake : public sf::Drawable
{
public:
    Snake();
    ~Snake();

    void Init(const sf::Texture &texture);
    void Move(const sf::Vector2f &direction);
    bool IsOn(const sf::Sprite &other) const;
    void Grow(const sf::Vector2f &direction);
    bool IsSelfIntersecting() const;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void addObserver(SnakeObserver* observer) {
        observers.push_back(observer);
    }

    void notifyObserversEatFood() {
        for (auto observer : observers) {
            observer->onNotifyEatFood();
        }
    }

private:
    std::list<sf::Sprite> body;
    std::list<sf::Sprite>::iterator head;
    std::list<sf::Sprite>::iterator tail;

    std::list<SnakeObserver*> observers;
};

#endif // SNAKE_H
