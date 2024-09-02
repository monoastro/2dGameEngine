#include "splashState.hpp"
#include "definitions.hpp"

#include <SFML/Window/Event.hpp>


namespace Engine
{
	splashState::splashState(std::shared_ptr<gameData> &data) : m_data(data)
	{
	}

	splashState::~splashState()
	{
	}

	void splashState::Init() 
	{

		this->m_data->timeAccumulator = 0;

		//load and put required assests for this state in the map
		this->m_data->m_assets->loadFont(mainFONT, fontPATH);
		this->m_data->m_assets->loadTexture(splashSCREEN, splashScreenPATH);

		//setting background and font with text
		m_background.setTexture(this->m_data->m_assets->getTexture(splashSCREEN));
		bgWidthScaler = (float)m_data->size.x/(float)m_background.getGlobalBounds().width;
		bgHeightScaler =  (float)m_data->size.y/(float)m_background.getGlobalBounds().height;
		m_background.scale(bgWidthScaler, bgHeightScaler); //default position is (0, 0)

		m_gameTitle.setFont(this->m_data->m_assets->getFont(mainFONT));
		m_gameTitle.setString("capybara");
		m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2, m_gameTitle.getLocalBounds().height / 2);
		m_gameTitle.setPosition(m_data->size.x / 2, m_data->size.y / 2 - 300.f);

		//add sounds and stuff
	}

	void splashState::processInput() //converts user input into numbers mostly boolean
	{
		//you can put these methods inside input Manager also 
		//ultimately these managers/machines are here to make your life easier so do whatever you're comfortable with
		//but generally, put global processes in input Manager and state specific processes here
		//use logic, do whatever makes more sense in that context 
		sf::Event event;
		while(this->m_data->m_window->pollEvent(event)) //processes that take priority over doing everything else
		{
			if(event.type == sf::Event::Closed || m_data->escAccumulator > 4)
			{
				this->m_data->m_window->close();
			}
			else if(event.type == sf::Event::Resized)
			{
				this->m_data->m_inputs->getLetterBoxView(this->m_data->view, event.size.width, event.size.height);
			}
			if(event.type == sf::Event::MouseMoved)
			{
				this->m_data->mousePos.x = event.mouseMove.x;
				this->m_data->mousePos.y = event.mouseMove.y;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) { m_isEnterButtonPressed = true; } 

		//global process
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {this->m_data->m_isEscButtonPressed = true;}//alternative scuffed approach escAccumulator += 0.000000001 if(non-zero escAccu) {//add deltatime}
		else {this->m_data->m_isEscButtonPressed = false; m_data->escAccumulator = 0;}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F4)) { this->m_data->m_isFullScreen = 1;} 

		//mouse coords relative to the view
		//std::cout<<m_data->m_window->mapPixelToCoords(sf::Mouse::getPosition(*this->m_data->m_window)).x<<", "<<m_data->m_window->mapPixelToCoords(sf::Mouse::getPosition(*this->m_data->m_window)).y<<"\n";

	}

	void splashState::Update(const float& deltaTime)
	{
		//global processes - send off the Input to the input manager to update
		//this->m_data->m_inputs->switchFullScreen(this->m_data->m_isFullScreen);

		//state specific processes - update it here //haven't used the .restart() method because time from construction till here corresponds to real world time
		if((this->m_clock.getElapsedTime().asSeconds() > transitionTime || m_isEnterButtonPressed))
		{
			//goto or transition to main menu or the next state
			// this->m_data->m_states->addState(std::make_unique</*instantiate newState*/>(/*specify parameters here*/), true);
		}
		if(this->m_data->m_isEscButtonPressed) 
		{
			m_data->escAccumulator+= deltaTime;
		}
	}

	void splashState::Draw()
	{
		m_data->m_window->setView(this->m_data->view); //when we do this, this becomes our window so anything we draw is relative to it
		m_data->m_window->draw(m_background);
		m_data->m_window->draw(m_gameTitle);
	}
}
