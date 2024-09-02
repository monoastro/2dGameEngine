#pragma once

#include <SFML/System/Time.hpp>

#include "state.hpp"
#include "application.hpp" //for assets manager and state manager in it
#include "definitions.hpp"

#include "imgui.h"
#include "imgui-SFML.h"

namespace Engine
{
	//wrapper for imgui as a state
	class imguiUI : public Engine::State
	{
	public:
		imguiUI(std::shared_ptr<Engine::applicationData> &data);
		~imguiUI();

		void Init() override;
		void processInput() override;
		void Update(const sf::Time& deltaTime) override;
		void Draw() override;

	private:
		void renderBasicUI();

		ImGuiWindowFlags windowFlags;
		ImVec4 hexToRGBA(const std::string& hexColor);
		std::shared_ptr<Engine::applicationData> m_data;
	};
}
