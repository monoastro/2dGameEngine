#pragma once

#include <SFML/System/Time.hpp>

namespace Engine
{
    class State
    {
    public:
        State(){};
        virtual ~State(){};

        virtual void Init() = 0;
        virtual void processInput() = 0; //converts user input into numbers, mostly boolean; use kmap
        virtual void Update(const float& deltaTime) = 0; //if it is a process repeated in every state, the data's sent off to the inputManager else updated here
        virtual void Draw() = 0; //draws the frame based on the updated data

        //non-pure virtual function = doesn't necessarily need to be implemented, like imagine if you needed to implement pause function for main menu wtf does that even mean
        virtual void Pause(){};
        virtual void Start(){};//except the first state, every state that comes after  has this method called so it can be used for transitioning if so desired
    };
}
