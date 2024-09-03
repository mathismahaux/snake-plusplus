#include "StateManager.h"

Engine::StateManager::StateManager() : add(false), replace(false), remove(false), removeAll(false)
{
}

Engine::StateManager::~StateManager()
{
}

// Ajouter etat
void Engine::StateManager::Add(std::unique_ptr<State> toAdd, bool replace)
{
    add = true;
    newState = std::move(toAdd);

    replace = replace;
}

// Effacer état courant
void Engine::StateManager::PopCurrent()
{
    remove = true;
}

// Effacer tous les états
void Engine::StateManager::PopAll()
{
    removeAll = true;
    remove = false;
}

// Changement d'état
void Engine::StateManager::ProcessStateChange()
{
    if (removeAll)
    {
        while (!stateStack.empty())
        {
            stateStack.pop();
        }
        removeAll = false;
    }
    else if (remove && (!stateStack.empty()))
    {
        stateStack.pop();

        if (!stateStack.empty())
        {
            stateStack.top()->Start();
        }

        remove = false;
    }

    if (add)
    {
        if (replace && (!stateStack.empty()))
        {
            stateStack.pop();
            replace = false;
        }

        if (!stateStack.empty())
        {
            stateStack.top()->Pause();
        }

        stateStack.push(std::move(newState));
        stateStack.top()->Init();
        stateStack.top()->Start();
        add = false;
    }
}

std::unique_ptr<Engine::State> &Engine::StateManager::GetCurrent()
{
    return stateStack.top();
}

bool Engine::StateManager::IsEmpty() const
{
    return stateStack.empty();
}

