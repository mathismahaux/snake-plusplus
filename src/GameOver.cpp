#include "GameOver.h"
#include "Gameplay.h"

#include <SFML/Window/Event.hpp>

GameOver::GameOver(std::shared_ptr<Context> &context)
    : context(context),
      isRetryButtonSelected(true),
      isRetryButtonPressed(false),
      isExitButtonSelected(false),
      isExitButtonPressed(false)
{
    if (!buttonChangeBuffer.loadFromFile("../../assets/sounds/button_change.wav"))
    {
        throw std::runtime_error("Failed to load button_change.wav");
    }

    if (!selectBuffer.loadFromFile("../../assets/sounds/select.wav"))
    {
        throw std::runtime_error("Failed to load select.wav");
    }

    buttonChangeSound.setBuffer(buttonChangeBuffer);
    selectSound.setBuffer(selectBuffer);
}

GameOver::~GameOver()
{
}

void GameOver::Init()
{
    auto& assetManager = Engine::AssetManager::GetInstance();

    // Add texture
    assetManager.AddTexture(GRASS, "../../assets/textures/grass.png", true);

    // Apply textures
    grass.setTexture(assetManager.GetTexture(GRASS));
    grass.setTextureRect(context->window->getViewport(context->window->getDefaultView()));

    // Title
    gameOverTitle.setFont(assetManager.GetFont(MAIN_FONT));
    gameOverTitle.setString("Game Over");
    gameOverTitle.setCharacterSize(100);

    sf::FloatRect gameOverBounds = gameOverTitle.getLocalBounds();
    gameOverTitle.setOrigin(gameOverBounds.width / 2, gameOverBounds.height / 2);
    gameOverTitle.setPosition(context->window->getSize().x / 2, context->window->getSize().y / 2 - 200.f);

    // Retry Button
    retryButton.setFont(assetManager.GetFont(MAIN_FONT));
    retryButton.setString("Retry");
    retryButton.setCharacterSize(50);

    sf::FloatRect retryBounds = retryButton.getLocalBounds();
    retryButton.setOrigin(retryBounds.width / 2, retryBounds.height / 2);
    retryButton.setPosition(context->window->getSize().x / 2, context->window->getSize().y / 2 - 25.f);

    // Exit Button
    exitButton.setFont(assetManager.GetFont(MAIN_FONT));
    exitButton.setString("Quit");
    exitButton.setCharacterSize(50);

    sf::FloatRect exitBounds = exitButton.getLocalBounds();
    exitButton.setOrigin(exitBounds.width / 2, exitBounds.height / 2);
    exitButton.setPosition(context->window->getSize().x / 2, context->window->getSize().y / 2 + 50.f);
}

// Process player input
void GameOver::ProcessInput()
{
    sf::Event event;
    while (context->window->pollEvent(event))
    {
        // If window closed, clear the states stack
        if (event.type == sf::Event::Closed)
        {
            context->states->PopAll();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
                // Button selection
                case sf::Keyboard::Up:
                {
                    buttonChangeSound.play();
                    if (!isRetryButtonSelected)
                    {
                        isRetryButtonSelected = true;
                        isExitButtonSelected = false;
                    }
                    break;
                }
                case sf::Keyboard::Down:
                {
                    buttonChangeSound.play();
                    if (!isExitButtonSelected)
                    {
                        isRetryButtonSelected = false;
                        isExitButtonSelected = true;
                    }
                    break;
                }
                case sf::Keyboard::Return:
                {
                    selectSound.play();
                    // Button press
                    isRetryButtonPressed = false;
                    isExitButtonPressed = false;

                    if (isRetryButtonSelected)
                    {
                        isRetryButtonPressed = true;
                    }
                    else
                    {
                        isExitButtonPressed = true;
                    }

                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }
}

// Update screen
void GameOver::Update(const sf::Time &deltaTime)
{
    // Change button colors based on selection
    if (isRetryButtonSelected)
    {
        retryButton.setFillColor(sf::Color::White);
        exitButton.setFillColor(sf::Color::Black);
    }
    else
    {
        exitButton.setFillColor(sf::Color::White);
        retryButton.setFillColor(sf::Color::Black);
    }

    // If retry button pressed
    if (isRetryButtonPressed)
    {
        // Return to gameplay
        context->states->Add(std::make_unique<Gameplay>(context), true);
    }
    // If exit button pressed
    else if (isExitButtonPressed)
    {
        context->states->PopAll();
    }
}

// Draw elements
void GameOver::Draw()
{
    context->window->draw(grass);
    context->window->draw(gameOverTitle);
    context->window->draw(retryButton);
    context->window->draw(exitButton);
    context->window->display();
}
