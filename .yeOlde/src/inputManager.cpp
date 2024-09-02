#include "inputManager.hpp"

//aight i'mma try it this way as well

namespace Engine
{
    inputMan::inputMan()
    {
    }

    inputMan::~inputMan()
    {
    }

    bool inputMan::isHover(sf::Sprite &object, sf::RenderWindow &window, const sf::Vector2i &mousePosCache)
    {
        sf::Vector2f mousePosition = window.mapPixelToCoords(mousePosCache);
        return object.getGlobalBounds().contains(mousePosition);
    }

    /* v2 
    bool inputMan::isHover(sf::Sprite &object, sf::RenderWindow &window)
    {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        return object.getGlobalBounds().contains(mousePos);
    } */
    
    /* v1
    bool inputMan::isHover(sf::Sprite &object, sf::RenderWindow &window)
    {
        sf::Vector2i pixel = window.mapCoordsToPixel(object.getPosition());
        sf::Vector2i bounds = window.mapCoordsToPixel(sf::Vector2f(object.getPosition().x + object.getGlobalBounds().width, object.getPosition().y + object.getGlobalBounds().height));
        //rectangle is made relative to the window than to the view
        sf::IntRect temRect
        (
            pixel.x, pixel.y,
            bounds.x - pixel.x, bounds.y-pixel.y
        );

        return temRect.contains(sf::Mouse::getPosition(window)))
    } */

    void inputMan::getLetterBoxView(sf::View &view, int windowWidth, int windowHeight) 
    {

        // Compares the aspect ratio of the window to the aspect ratio of the view,
        // and sets the view's viewport accordingly in order to archieve a letterbox effect.
        // A new view (with a new viewport set) is returned.

        float windowRatio = windowWidth / (float) windowHeight;          //if you increase height windowRatio decreases and if you increase width window ratio increases
        float viewRatio = view.getSize().x / (float) view.getSize().y;
        float sizeX = 1;
        float sizeY = 1;
        float posX = 0;
        float posY = 0;

        bool horizontalSpacing = true;                                   // If width is increased, the black bars will appear on the left and right side.
        if (windowRatio < viewRatio) { horizontalSpacing = false; }      // Otherwise, the black bars will appear on the top and bottom.

        if (horizontalSpacing) 
        {
            sizeX = viewRatio / windowRatio;
            posX = (1 - sizeX) / 2.f;
        }
        else 
        {
            sizeY = windowRatio / viewRatio;
            posY = (1 - sizeY) / 2.f;
        }

        view.setViewport( sf::FloatRect(posX, posY, sizeX, sizeY) );
    }

    void inputMan::switchFullScreen(sf::RenderWindow &m_window)
    {
        if (isFullScreen)
        {
            m_window.create(sf::VideoMode::getFullscreenModes()[0], "Snek");
            isFullScreen = false;
        }
        else if (!isFullScreen)
        {
            m_window.create(sf::VideoMode::getFullscreenModes()[0], "Snek", sf::Style::Fullscreen);
            isFullScreen = true;
        }
    }

/*     void inputMan::onEvent(sf::Event &event)
    {

    } */
}
