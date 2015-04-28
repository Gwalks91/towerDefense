#pragma once

#include <SFML\Graphics.hpp>

namespace sf
{
	class MouseExtra : sf::Mouse
	{
	public:
		MouseExtra();
		~MouseExtra();
		static bool isButtonReleased( sf::Mouse::Button button);
	private:
		static bool buttonPressed[5];
	};
}

