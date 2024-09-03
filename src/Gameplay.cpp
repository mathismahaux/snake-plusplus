#include "Gameplay.h"
#include "GameOver.h"
#include "PauseGame.h"

#include <SFML/Window/Event.hpp>

#include <stdexcept>
#include <stdlib.h>
#include <time.h>

Gameplay::Gameplay(std::shared_ptr<Context> &context) : context(context), score(0), snakeDirection({32.f, 0.f}), elapsedTime(sf::Time::Zero), isPaused(false)
{
    srand(time(nullptr));

    if (!gameOverBuffer.loadFromFile("../../assets/sounds/game_over.wav"))
    {
        throw std::runtime_error("Failed to load game_over.wav");
    }

    if (!eatBuffer.loadFromFile("../../assets/sounds/eat.wav"))
    {
        throw std::runtime_error("Failed to load eat.wav");
    }

    if (!selectBuffer.loadFromFile("../../assets/sounds/select.wav"))
    {
        throw std::runtime_error("Failed to load select.wav");
    }

    // Set sound buffers to sounds
    gameOverSound.setBuffer(gameOverBuffer);
    eatSound.setBuffer(eatBuffer);
    selectSound.setBuffer(selectBuffer);

    moveInterval = 0.1;
}

Gameplay::~Gameplay()
{
}

void Gameplay::Init()
{
    auto& assetManager = Engine::AssetManager::GetInstance();

    // Add textures
    assetManager.AddTexture(GRASS, "../../assets/textures/grass.png", true);
    assetManager.AddTexture(FOOD, "../../assets/textures/food.png");
    assetManager.AddTexture(WALL, "../../assets/textures/wall.png", true);
    assetManager.AddTexture(SNAKE, "../../assets/textures/snake.png");

    // Apply textures
    grass.setTexture(assetManager.GetTexture(GRASS));
    grass.setTextureRect(context->window->getViewport(context->window->getDefaultView()));

    for (auto &wall : walls)
    {
        wall.setTexture(assetManager.GetTexture(WALL));
    }

    walls[0].setTextureRect({0, 0, (int)context->window->getSize().x, 32});
    walls[1].setTextureRect({0, 0, (int)context->window->getSize().x, 32});
    walls[1].setPosition(0, context->window->getSize().y - 32);

    walls[2].setTextureRect({0, 0, 32, (int)context->window->getSize().y});
    walls[3].setTextureRect({0, 0, 32, (int)context->window->getSize().y});
    walls[3].setPosition(context->window->getSize().x - 32, 0);

    food.setTexture(assetManager.GetTexture(FOOD));
    food.setPosition(context->window->getSize().x / 2, context->window->getSize().y / 2);

    snake.Init(assetManager.GetTexture(SNAKE));
    snake.addObserver(this);

    // Display score
    scoreText.setFont(assetManager.GetFont(MAIN_FONT));
    scoreText.setString("Score : " + std::to_string(score));
    scoreText.setPosition(37, 32);
    scoreText.setCharacterSize(40);
}

// Process player input
void Gameplay::ProcessInput()
{
    sf::Event event;
    while (context->window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            context->states->PopAll();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            sf::Vector2f newDirection = snakeDirection;
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
                newDirection = {0.f, -32.f};
                break;
            case sf::Keyboard::Down:
                newDirection = {0.f, 32.f};
                break;
            case sf::Keyboard::Left:
                newDirection = {-32.f, 0.f};
                break;
            case sf::Keyboard::Right:
                newDirection = {32.f, 0.f};
                break;
            case sf::Keyboard::Escape:
                selectSound.play();
                context->states->Add(std::make_unique<PauseGame>(context));
                break;

            default:
                break;
            }

            // Check for valid new direction
            if (std::abs(snakeDirection.x) != std::abs(newDirection.x) || std::abs(snakeDirection.y) != std::abs(newDirection.y))
            {
                snakeDirection = newDirection;
            }
        }
    }
}

void Gameplay::Update(const sf::Time &deltaTime)
{
    if (!isPaused)
    {
        elapsedTime += deltaTime;

        if (elapsedTime.asSeconds() > moveInterval)
        {
            for (auto &wall : walls)
            {
                // If player hits wall, game over
                if (snake.IsOn(wall))
                {
                    gameOverSound.play();
                    context->states->Add(std::make_unique<GameOver>(context), true);
                    break;
                }
            }

            // If player hits food
            if (snake.IsOn(food))
            {
                eatSound.play();
                // Grow snake
                snake.Grow(snakeDirection);

                // Generate food at another position
                int x = 0, y = 0;
                x = std::clamp<int>(rand() % context->window->getSize().x, 64, (context->window->getSize().x - 1) * 32);
                y = std::clamp<int>(rand() % context->window->getSize().y, 64, (context->window->getSize().y - 1) * 32);

                food.setPosition(x, y);

                onNotifyEatFood();
            }
            else
            {
                // Move snake
                snake.Move(snakeDirection);
            }

            // If player collides with itself, game over
            if (snake.IsSelfIntersecting())
            {
                context->states->Add(std::make_unique<GameOver>(context), true);
            }

            elapsedTime = sf::Time::Zero;
        }
    }
}

// Draw elements
void Gameplay::Draw()
{
    context->window->clear();
    context->window->draw(grass);

    for (auto &wall : walls)
    {
        context->window->draw(wall);
    }
    context->window->draw(food);
    context->window->draw(snake);
    context->window->draw(scoreText);

    context->window->display();
}

void Gameplay::Pause()
{
    isPaused = true;
}

void Gameplay::Start()
{
    isPaused = false;
}

int Gameplay::getScore()
{
    return score;
}
