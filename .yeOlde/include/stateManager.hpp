#pragma once

#include <stack>
#include <memory>

#include "state.hpp"

namespace Engine
{
    //typedef std::unique_ptr<State> stateRef; for easier use
    class stateMan
    {
    public:
        stateMan();
        ~stateMan();


        void addState(std::unique_ptr<State> newState, bool replace = false);
        void popCurrent();
        void processStateChange();
        std::unique_ptr<State> &getCurrentState();

    private:
        std::stack<std::unique_ptr<State>> m_stateStack;
        std::unique_ptr<State> m_newState;

        bool m_add;
        bool m_replace;
        bool m_remove;
    };

}
