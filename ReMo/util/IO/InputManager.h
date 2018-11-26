#ifndef __REMO_INPUTMANAGER_H__
#define __REMO_INPUTMANAGER_H__

#include <memory>
#include <stdexcept>

#include "Abstractinputhandler.h"

namespace remo
{
	namespace inputHandler
	{
		class DummyInputHandler : public AbstractInputHandler
		{
			public:
				void handleMouseInput(
					int screenX, 
					int screenY, 
					MouseInputButton btn, 
					MouseInputState btnState);

				void handleKeyInput(
					const std::string & key,
					KeyInputState keyState);		
		};
	}

	class InputManager
	{
		private:
			static InputManager INSTANCE;
		public:
			static InputManager & getInstance();
		private:
			std::unique_ptr<inputHandler::AbstractInputHandler> inputHandler;
		private:
			InputManager();
		public:
			~InputManager();
		
			template<class T>
			void registerInputHandler()
			{
				if(!std::is_base_of<inputHandler::AbstractInputHandler, T>::value)
				{
					throw std::runtime_error("InputManager: Attempted to register a non AbstractInputHandler derived class as input handler");
				}

				inputHandler = std::make_unique<T>();
			}

			void handleMouseInput(
				int screenX, 
				int screenY, 
				inputHandler::MouseInputButton btn,
				inputHandler::MouseInputState btnState);

			void handleKeyInput(
				const std::string & key,
				inputHandler::KeyInputState keyState);
	};
}

#endif
