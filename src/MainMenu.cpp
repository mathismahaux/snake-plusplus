#include "MainMenu.h"
#include "Gameplay.h"

#include <SFML/Window/Event.hpp>

MainMenu::MainMenu(std::shared_ptr<Context> &context)
    : context(context),
      isPlayButtonSelected(true),
      isPlayButtonPressed(false),
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

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
    auto& assetManager = Engine::AssetManager::GetInstance();

    // Add font
    assetManager.AddFont(MAIN_FONT, "../../assets/fonts/AkaashNormal.ttf");

    // Add texture
    assetManager.AddTexture(GRASS, "../../assets/textures/grass.png", true);

    // Apply textures
    grass.setTexture(assetManager.GetTexture(GRASS));
    grass.setTextureRect(context->window->getViewport(context->window->getDefaultView()));

    // Title
    gameTitle.setFont(assetManager.GetFont(MAIN_FONT));
    gameTitle.setString("SNAKE++");
    gameTitle.setCharacterSize(300);

    sf::FloatRect titleBounds = gameTitle.getLocalBounds();
    gameTitle.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    gameTitle.setPosition(context->window->getSize().x / 2, context->window->getSize().y / 2 - 300.f);

    // Play Button
    playButton.setFont(assetManager.GetFont(MAIN_FONT));
    playButton.setString("Play");
    playButton.setCharacterSize(50);

    sf::FloatRect playBounds = playButton.getLocalBounds();
    playButton.setOrigin(playBounds.width / 2, playBounds.height / 2);
    playButton.setPosition(context->window->getSize().x / 2, context->window->getSize().y / 2 - 25.f);

    // Exit Button
    exitButton.setFont(assetManager.GetFont(MAIN_FONT));
    exitButton.setString("Quit");
    exitButton.setCharacterSize(50);

    sf::FloatRect exitBounds = exitButton.getLocalBounds();
    exitButton.setOrigin(exitBounds.width / 2, exitBounds.height / 2);
    exitButton.setPosition(context->window->getSize().x / 2, context->window->getSize().y / 2 + 50.f);
}

// Process player input
void MainMenu::ProcessInput()
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
            // Button selection
            switch (event.key.code)
            {
                case sf::Keyboard::Up:
                {
                    buttonChangeSound.play();
                    if (!isPlayButtonSelected)
                    {
                        isPlayButtonSelected = true;
                        isExitButtonSelected = false;
                    }
                    break;
                }
                case sf::Keyboard::Down:
                {
                    buttonChangeSound.play();
                    if (!isExitButtonSelected)
                    {
                        isPlayButtonSelected = false;
                        isExitButtonSelected = true;
                    }
                    break;
                }
                case sf::Keyboard::Return:
                {
                    selectSound.play();
                    // Button press
                    isPlayButtonPressed = false;
                    isExitButtonPressed = false;

                    if (isPlayButtonSelected)
                    {
                        isPlayButtonPressed = true;
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
void MainMenu::Update(const sf::Time &deltaTime)
{
    // Change button colors based on selection
    if (isPlayButtonSelected)
    {
        playButton.setFillColor(sf::Color::White);
        exitButton.setFillColor(sf::Color::Black);
    }
    else
    {
        exitButton.setFillColor(sf::Color::White);
        playButton.setFillColor(sf::Color::Black);
    }

    // If play button pressed
    if (isPlayButtonPressed)
    {
        context->states->Add(std::make_unique<Gameplay>(context), true);
    }
    // If exit button pressed
    else if (isExitButtonPressed)
    {
        context->states->PopAll();
    }
}

// Draw elements
void MainMenu::Draw()
{
    context->window->draw(grass);
    context->window->draw(gameTitle);
    context->window->draw(playButton);
    context->window->draw(exitButton);
    context->window->display();
}
