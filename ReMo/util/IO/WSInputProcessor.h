#ifdef WEBSTREAMER

#ifndef __REMO_WSINPUTHANDLER_H__
#define __REMO_WSINPUTHANDLER_H__

#include <stdexcept>

#include <webstreamer/webstreamer.hpp>
#include <webstreamer/mouse_event.hpp>
#include <webstreamer/keyboard_event.hpp>

#include "InputManager.h"
#include "Abstractinputhandler.h"

namespace remo
{
	class WSInputProcessor : public webstreamer::AsynchronousInputProcessor 
	{
	private:
		int screenWidth, screenHeight;

	public:
		WSInputProcessor();
		~WSInputProcessor();

		void setScreenSize(int width, int height);

		void ProcessMouseInput(const webstreamer::MouseEvent &) override;
		void ProcessKeyboardInput(const webstreamer::KeyboardEvent &) override;
	
	private:
		inputHandler::MouseInputButton WSButtonToDSButton(webstreamer::MouseButton);
		inputHandler::MouseInputState WSBtnActionToDSButtonState(webstreamer::MouseAction);
		inputHandler::KeyInputState WSKeyStateToDSKeyState(webstreamer::KeyboardAction);
	};
}
#endif //WEBSTREAMER defined
#endif
