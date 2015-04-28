
#include "MouseExtra.h"
namespace sf
{
	bool MouseExtra::buttonPressed[] = {0,0,0,0,0};

	MouseExtra::MouseExtra()
	{
	}

	MouseExtra::~MouseExtra()
	{
		delete[] buttonPressed;
	}

	bool MouseExtra::isButtonReleased( sf::Mouse::Button button)
	{
		if(sf::Mouse::isButtonPressed(button))
		{
			buttonPressed[button] = true;
			return false;
		}

		if(!buttonPressed[button])
			return false;
		else if(sf::Mouse::isButtonPressed(button))
			return false;
		else
		{
			buttonPressed[button] = false;
			return true;
		}
	}
}