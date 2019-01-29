#ifdef REMO_USE_WEBSTREAMER

#ifndef __REMO_WSINPUTHANDLER_H__
#define __REMO_WSINPUTHANDLER_H__

#include <stdexcept>

#include <webstreamer/webstreamer.hpp>
#include <webstreamer/mouse_event.hpp>
#include <webstreamer/keyboard_event.hpp>

#include "inputManager.h"
#include "abstractInputhandler.h"

namespace remo
{
  class webstreamerInputProcessor : public webstreamer::AsynchronousInputProcessor 
  {
    public:
      webstreamerInputProcessor ( );
      ~webstreamerInputProcessor ( );

      void setScreenSize ( unsigned int width_, 
                           unsigned int height_ );

      void ProcessMouseInput ( const webstreamer::MouseEvent & me_ ) override;
      void ProcessKeyboardInput ( const webstreamer::KeyboardEvent & ke_ ) override;

    private:
      inputHandler::TMouseInputButton WSButtonToDSButton ( webstreamer::MouseButton );
      inputHandler::TMouseInputState WSBtnActionToDSButtonState ( webstreamer::MouseAction );
      inputHandler::TKeyInputState WSKeyStateToDSKeyState ( webstreamer::KeyboardAction );

      double _screenWidth;
      double _screenHeight;
  };
}
#endif //REMO_USE_WEBSTREAMER defined
#endif
