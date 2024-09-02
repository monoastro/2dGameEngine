#include "globalState.hpp"

namespace Engine
{
	imguiUI::imguiUI(std::shared_ptr<applicationData> &data)
		:
			m_data(data)
	{
	}

	imguiUI::~imguiUI()
	{
		ImGui::SFML::Shutdown();
	}

	void imguiUI::Init()
	{
		if(!ImGui::SFML::Init(*(m_data->m_window)))
		{
			//std::cout<<"ImGui done goofed up\n";
			exit(-1);
		}

		//Font Configs
		ImGuiIO& io = ImGui::GetIO();
		ImFontAtlas* fontAtlas = io.Fonts;
		ImFontConfig fontConfig;
		fontConfig.FontDataOwnedByAtlas = false;  // Ensure font data is not deleted by ImFontAtlas
		fontConfig.PixelSnapH = true;             // Enable pixel snapping for sharper text rendering

		//load font
		fontAtlas->AddFontFromFileTTF(hack_ttfPATH, fontSize, &fontConfig);
		fontAtlas->AddFontFromFileTTF(arialPATH, fontSize, &fontConfig);
		io.FontDefault = fontAtlas->Fonts.back(); 
		// Set the custom font as the default font
		if (!io.Fonts->IsBuilt()) {
			if(!ImGui::SFML::UpdateFontTexture())
			{
				//std::cout<<"ImGui done goofed up\n";
			}
		}
	}

	void imguiUI::processInput()
	{
		ImGui::SFML::ProcessEvent(this->m_data->m_inputs->m_event);

		//for SFML window
		if(this->m_data->escAccumulator > transitionTime)
		{
			this->m_data->m_window->close();
		}
		if(this->m_data->m_inputs->m_event.type == sf::Event::Resized)
		{
			this->m_data->size.x = this->m_data->m_inputs->m_event.size.width;
			this->m_data->size.y = this->m_data->m_inputs->m_event.size.height;
			this->m_data->m_inputs->getLetterBoxView(this->m_data->view, this->m_data->size.x, this->m_data->size.y);
		}

		//move and click; not click and move
		if(this->m_data->m_inputs->m_event.type == sf::Event::MouseMoved)
		{
			this->m_data->mousePosition.x = this->m_data->m_inputs->m_event.mouseMove.x;
			this->m_data->mousePosition.y = this->m_data->m_inputs->m_event.mouseMove.y;
		}

	}

	void imguiUI::Update(const sf::Time& deltaTime)
	{
		//global SFML window updates;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
		{
			this->m_data->m_isEscButtonPressed = true;
			this->m_data->escAccumulator+= deltaTime.asSeconds();
		}
		else 
		{
			this->m_data->m_isEscButtonPressed = false; 
			this->m_data->escAccumulator = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F4)) { this->m_data->m_isFullScreen = 1;} 

		//ImGui's stuff
		ImGui::SFML::Update(*(this->m_data->m_window), deltaTime);
		//All immediate mode stuff and their consequences are updated here
		//just list them as you please
		renderBasicUI();
		ImGui::ShowDemoWindow();
	}

	void imguiUI::Draw()
	{
		if(m_data->m_isEscButtonPressed) 
		{
			//flag for drawing exit animation on here
			//m_data->m_window->draw(m_exit);
		}

		ImGui::SFML::Render(*(this->m_data->m_window));
	}

	void imguiUI::renderBasicUI()
	{
		ImGui::Begin("Settings");
		ImGui::Button("Hello");
		static float value;
		ImGui::DragFloat("Value", &value);
		ImGui::End();
	}
}
