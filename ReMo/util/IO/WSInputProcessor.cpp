#ifdef WEBSTREAMER

#include <iostream>
#include "WSInputProcessor.h"

namespace remo
{
	WSInputProcessor::WSInputProcessor()
		: screenWidth(0)
		, screenHeight(0)
	{

	}

	WSInputProcessor::~WSInputProcessor()
	{

	}

	void WSInputProcessor::setScreenSize(int width, int height)
	{
		screenWidth = width;
		screenHeight = height;
	}

	void WSInputProcessor::ProcessMouseInput(const webstreamer::MouseEvent & evt) 
	{
		int realPosX = static_cast<int>(evt.x() * static_cast<double>(screenWidth));
		int realPosY = static_cast<int>(evt.y() * static_cast<double>(screenHeight));
		inputHandler::MouseInputButton mib = WSButtonToDSButton(evt.button());
		inputHandler::MouseInputState mis = WSBtnActionToDSButtonState(evt.action());

		InputManager::getInstance().handleMouseInput(realPosX, realPosY, mib, mis);
	}

	void WSInputProcessor::ProcessKeyboardInput(const webstreamer::KeyboardEvent & evt) 
	{
		std::string key = evt.key();
		
		if(key.empty())
		{
			return;
		}

		inputHandler::KeyInputState kis = WSKeyStateToDSKeyState(evt.action());
		
		InputManager::getInstance().handleKeyInput(key, kis);
	}

	inputHandler::MouseInputButton WSInputProcessor::WSButtonToDSButton(webstreamer::MouseButton mb)
	{
		inputHandler::MouseInputButton result = inputHandler::MouseInputButton::MIB_UNKNOWN;

		switch(mb)
		{
  		case webstreamer::MouseButton::MAIN:
				result = inputHandler::MouseInputButton::MIB_BUTTON_0;
				break;
		  case webstreamer::MouseButton::AUXILIARY:
				result = inputHandler::MouseInputButton::MIB_BUTTON_1;
				break;
  		case webstreamer::MouseButton::SECONDARY:
				result = inputHandler::MouseInputButton::MIB_BUTTON_2;
				break;
  		case webstreamer::MouseButton::FOURTH:
				break;
  		case webstreamer::MouseButton::FIFTH:
				break;
		}

		return result;
	}

	inputHandler::MouseInputState WSInputProcessor::WSBtnActionToDSButtonState(webstreamer::MouseAction ma)
	{
		inputHandler::MouseInputState result = inputHandler::MouseInputState::MIS_DUMMY;

		switch(ma)
		{
			case webstreamer::MouseAction::BUTTON_DOWN:
				result = inputHandler::MouseInputState::MIS_BUTTON_DOWN;
				break;
  		case webstreamer::MouseAction::BUTTON_UP:
				result = inputHandler::MouseInputState::MIS_BUTTON_UP;
				break;
  		case webstreamer::MouseAction::DOUBLE_CLICK:
				result = inputHandler::MouseInputState::MIS_BUTTON_DBL_CLICK;
				break;
		}

		return result;
	}

	inputHandler::KeyInputState WSInputProcessor::WSKeyStateToDSKeyState(webstreamer::KeyboardAction ka)
	{
		inputHandler::KeyInputState result = inputHandler::KeyInputState::KIS_KEY_UNKNOWN;

		switch(ka)
		{
			case webstreamer::KeyboardAction::KEY_DOWN:
				result = inputHandler::KeyInputState::KIS_KEY_DOWN;
				break;
			case webstreamer::KeyboardAction::KEY_UP:
				result = inputHandler::KeyInputState::KIS_KEY_UP;
				break;
			case webstreamer::KeyboardAction::KEY_PRESS:
				result = inputHandler::KeyInputState::KIS_KEY_PRESS;
				break;
		}

		return result;
	}
}
#endif //WEBSTREAMER defined