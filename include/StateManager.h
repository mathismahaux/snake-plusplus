#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <stack>
#include <memory>

#include "State.h"

namespace Engine
{
    class StateManager
    {
    public:
        StateManager();
        ~StateManager();

        void Add(std::unique_ptr<State> toAdd, bool replace = false);
        void PopCurrent();
        void PopAll();
        void ProcessStateChange();
        std::unique_ptr<State> &GetCurrent();
        bool IsEmpty() const;

    private:
        std::stack<std::unique_ptr<State>> stateStack;
        std::unique_ptr<State> newState;

        bool add;
        bool replace;
        bool remove;
        bool removeAll;
    };

}

#endif // STATEMANAGER_H
