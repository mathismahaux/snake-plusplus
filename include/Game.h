#ifndef GAME_H
#define GAME_H

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "AssetManager.h"
#include "StateManager.h"

enum AssetID
{
    MAIN_FONT = 0,
    GRASS,
    FOOD,
    WALL,
    SNAKE
};

struct Context
{
    std::unique_ptr<Engine::StateManager> states;
    std::unique_ptr<sf::RenderWindow> window;

    Context()
    {
        states = std::make_unique<Engine::StateManager>();
        window = std::make_unique<sf::RenderWindow>();
    }
};

class Game
{
public:
    static Game& GetInstance();

    // Deleted copy constructor and assignment operator to enforce Singleton property
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    void Run();

private:
    Game(); // Private constructor
    ~Game();

    std::shared_ptr<Context> context;
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
};

#endif // GAME_H
