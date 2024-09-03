#include "Game.h"
#include "MainMenu.h"

// Initialize the static member
Game& Game::GetInstance()
{
    static Game instance;
    return instance;
}

// Private constructor
Game::Game() : context(std::make_shared<Context>())
{
    // Création de la fenêtre + faire apparaître le menu principal
    context->window->create(sf::VideoMode(1920, 1024), "Snake++", sf::Style::Close);
    context->states->Add(std::make_unique<MainMenu>(context));
}

Game::~Game()
{
}

void Game::Run()
{
    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;

    while (context->window->isOpen())
    {
        // FPS
        timeSinceLastFrame += clock.restart();

        while (timeSinceLastFrame > TIME_PER_FRAME)
        {
            timeSinceLastFrame -= TIME_PER_FRAME;

            context->states->ProcessStateChange();

            // Si le pile des etats n'est pas vide => Mettre à jour le jeu
            if (!context->states->IsEmpty())
            {
                context->states->GetCurrent()->ProcessInput();
                context->states->GetCurrent()->Update(TIME_PER_FRAME);
                context->states->GetCurrent()->Draw();
            }
            else
            {
                context->window->close();
            }
        }
    }
}
