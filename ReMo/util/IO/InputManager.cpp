#include "InputManager.h"

namespace remo
{
	namespace inputHandler
	{
		void DummyInputHandler::handleMouseInput(
			int screenX, 
			int screenY, 
			MouseInputButton btn, 
			MouseInputState btnState)
		{
		}

		void DummyInputHandler::handleKeyInput(
			const std::string & key,
			KeyInputState keyState)
		{
		}
	}

	// ---------------------------------------------------------

	InputManager InputManager::INSTANCE;

	InputManager & InputManager::getInstance()
	{
		return INSTANCE;
	}

	InputManager::InputManager()
	{
		registerInputHandler<inputHandler::DummyInputHandler>();
	}

	InputManager::~InputManager()
	{
	}

	void InputManager::handleMouseInput(
		int screenX, 
		int screenY, 
		inputHandler::MouseInputButton btn,
		inputHandler::MouseInputState btnState)
	{
		inputHandler.get()->handleMouseInput(screenX, screenY, btn, btnState);
	}			

	void InputManager::handleKeyInput(
		const std::string & key,
		inputHandler::KeyInputState keyState)
	{
		inputHandler.get()->handleKeyInput(key, keyState);
	}
}
