#include "stateManager.hpp"

Engine::stateMan::stateMan() : m_add(false), m_replace(false), m_remove(false)
{
}

Engine::stateMan::~stateMan()
{
}

void Engine::stateMan::addState(std::unique_ptr<State> newState, bool replace)
{
    m_add = true;
    m_newState = std::move(newState);
    m_replace = replace;
}

void Engine::stateMan::popCurrent() 
{
    m_remove = true;
}

void Engine::stateMan::processStateChange()
{
    if (m_remove && (!m_stateStack.empty()))
    {
        m_stateStack.pop();

        if (!m_stateStack.empty())
        {
            m_stateStack.top()->Start();
        }

        m_remove = false;
    }

    if (m_add)
    {
        if (m_replace && (!m_stateStack.empty())) //if replace, pop top state, pause the then top state, add the new state
        {
            m_stateStack.pop();
            m_replace = false;
        }

        if (!m_stateStack.empty()) //pause the current top state if the stack is not empty
        {
            m_stateStack.top()->Pause();
        }
        
        /* 
        //alternative //better but it uses nested ifs
        //this assumes that the top stack that got replaced paused it's stack below when it was added
        //so it doesn't pause the second state when it gets replaced while the previous logic pauses it anyway
        if(!m_stateStack.empty()) 
        {
            if(m_replace) {m_stateStack.pop(); m_replace = false;}
            else { m_stateStack.top()->Pause(); }
        } 
        */

        m_stateStack.push(std::move(m_newState)); //move the ownership of the new state(unique_ptr) to the top of the stack
        m_stateStack.top()->Init();
        m_stateStack.top()->Start();
        m_add = false;
    }
}

std::unique_ptr<Engine::State> &Engine::stateMan::getCurrentState()
{
    return m_stateStack.top();
}
