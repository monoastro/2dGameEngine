#pragma once
#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

#include "assetManager.hpp" 
#include "stateManager.hpp"
#include "inputManager.hpp"
#include "definitions.hpp"


namespace Engine
{
	struct applicationData
	{
		std::unique_ptr<Engine::assetManager> m_assets;
		std::unique_ptr<Engine::inputManager> m_inputs;
		std::unique_ptr<Engine::stateManager> m_states;

		std::unique_ptr<sf::RenderWindow> m_window;


		applicationData() : 
			m_assets(std::make_unique<Engine::assetManager>()),
			m_inputs(std::make_unique<Engine::inputManager>()),
			m_states(std::make_unique<Engine::stateManager>()),
			m_window(std::make_unique<sf::RenderWindow>())
		{
		}

		//info and variables about the game required by many states
		bool m_isFullScreen = false, m_isEscButtonPressed = false;
		float escAccumulator = 0;
		float timeAccumulator = 0;
		sf::Vector2i size, mousePosition;
		sf::Clock m_clock;
		sf::View view;
	};
	
	class Application 
	{
	public:
		Application(bool Fullscreen = fullscreen, std::string title = Title, int width = WIDTH, int height = HEIGHT);
		~Application();

		void Run();
	private:
		//const float frameRate = 1.f / 60.0f; for discrete games
		std::shared_ptr<Engine::applicationData> m_applicationData;
		sf::Time m_delta;
	};
}
