#pragma once

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

#include "assetManager.hpp" 
#include "stateManager.hpp"
#include "inputManager.hpp"
#include "definitions.hpp"

namespace Engine
{
	struct gameData
	{
		std::unique_ptr<Engine::assetMan> m_assets;
		std::unique_ptr<Engine::inputMan> m_inputs;
		std::unique_ptr<Engine::stateMan> m_states;
		std::unique_ptr<sf::RenderWindow> m_window;


		gameData() : 
			m_assets(std::make_unique<Engine::assetMan>()),
			m_inputs(std::make_unique<Engine::inputMan>()),
			m_states(std::make_unique<Engine::stateMan>()),
			m_window(std::make_unique<sf::RenderWindow>())
		{
		}

		//info about the game required by many states
		bool m_isFullScreen = false, m_isEscButtonPressed = false;
		float escAccumulator = 0;
		sf::View view;
		sf::Vector2i size, mousePos;
		std::string owariState;
	};

	class Game //this refers to this class
	{
		public:
			Game(bool Fullscreen = fullscreen, std::string title = Title, int width = WIDTH, int height = HEIGHT);
			~Game();
			void Run();

		private:
			//float frameRate = 1.f / 60.0f; for discrete games
			std::shared_ptr<gameData> m_gameData;
	};
}
