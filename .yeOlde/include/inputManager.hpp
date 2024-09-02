#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

namespace Engine
{
    class inputMan
    {
    public:
        inputMan();
        ~inputMan();

        void getLetterBoxView(sf::View &view, int windowWidth, int windowHeight);
        void switchFullScreen(sf::RenderWindow &m_window);
        // bool isHover(sf::Sprite &object, sf::RenderWindow &window);
        bool isHover(sf::Sprite &object, sf::RenderWindow &window, const sf::Vector2i &mousePosCache);

        // bool check(unsigned x, unsigned y, int dx, int dy);


        /* void onEvent(sf::Event &event);
        void qolCheck(); */ //quality of life checks - implement this
        //inline bool isKeyDown(KeyCode keyCode){return keyStates[keycode];}
        //void dispatchEventToCallbacks(Even &e); 
    private:
        bool isFullScreen = 0;

        /*
        bool onKeyPressed(KeyPressedEvent &e);
        bool onKeyReleased(KeyReleasedEvent &e)
        */
    };
}