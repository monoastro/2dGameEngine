#include "game.hpp"
#include "splashState.hpp"

namespace Engine
{
	//                                                                                //this is kinda the genesis
	Game::Game(bool Fullscreen, std::string title,int width, int height) 
	: 
		m_gameData(std::make_shared<gameData>())
	{
		if (!Fullscreen)
		{
			this->m_gameData->m_window->create(sf::VideoMode(width, height), title , (sf::Style::Resize + sf::Style::Close + sf::Style::Titlebar));
			//window->setMouseCursorVisible(false); //depends on the game
		}
		else
		{
			this->m_gameData->m_window->create(sf::VideoMode::getFullscreenModes()[0], title, sf::Style::Fullscreen);
			//window->setMouseCursorVisible(false); //same reason as above
		}

		m_gameData->m_isFullScreen = Fullscreen;
		this->m_gameData->size.x = width;
		this->m_gameData->size.y = height;

		//view for letterbox effect
		m_gameData->view.setSize(width, height);
		m_gameData->view.setCenter( width/ 2, height/ 2 );
		// this->m_gameData->m_inputs->getLetterBoxView(m_gameData->view, width, height); not necessary if the view is the same size as the window

		this->m_gameData->m_states->addState(std::make_unique<splashState>(m_gameData));  //add first state otherwise shit hits the fan

		//other first states like mainMenu or straight to the game
		// m_gameData->m_states->addState(std::make_unique<mainMenu>(m_gameData));

		//this->Run(); if you want it to run as soon as setup finishes
	}

	Game::~Game()
	{
	}

	void Game::Run()
	{

		sf::Clock clock;
		float delta = 0;

		while (this->m_gameData->m_window->isOpen())
		{
			clock.restart();

			this->m_gameData->m_states->processStateChange();
			this->m_gameData->m_states->getCurrentState()->processInput();//optimal to put delta then restart clock before the update function; that way we have a way to keep track of how much real world time has passed for each frame
			this->m_gameData->m_states->getCurrentState()->Update(delta);
			this->m_gameData->m_window->clear(sf::Color::Black);
			this->m_gameData->m_states->getCurrentState()->Draw();
			this->m_gameData->m_window->display();

			delta = clock.getElapsedTime().asSeconds();
			// std::cout<<"FPS: "<<1.0/delta<<"\n";
		}
	}

	//for games with discrete steps like snake, put here or just in the game state's update

	/* //inside the loop
	   delta += clock.getElapsedTime().asSeconds(); //go through the loop until frameRate amount of seconds have passed
	   clock.restart();

	   while (delta >= frameRate) //uncomment frameRate in header 
	   {
	   delta -= frameRate; //or just straight up = 0

	//game code to process and update changes 
	}   
	*/
}
