#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/View.hpp>

#include "state.hpp"
#include "game.hpp" //for assets manager and state manager in it

namespace Engine
{
    class splashState : public Engine::State
    {
    public:
        splashState(std::shared_ptr<gameData> &data);
        ~splashState();

        void Init() override;
        void processInput() override;
        void Update(const float& deltaTime) override;
        void Draw() override;
    
    private:
        private:
        std::shared_ptr<gameData> m_data;
        sf::Text m_gameTitle;
        sf::Clock m_clock;
        sf::Sprite m_background;

        bool m_isEnterButtonPressed = false;

        //remove these if the background is the same size as the window
        float bgHeightScaler = 1, bgWidthScaler = 1;
    };
}