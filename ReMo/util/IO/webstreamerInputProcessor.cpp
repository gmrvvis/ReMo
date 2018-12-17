#ifdef WEBSTREAMER

#include "webstreamerInputProcessor.h"

namespace remo
{
  webstreamerInputProcessor::webstreamerInputProcessor ( )
    : _screenWidth ( 0 )
    , _screenHeight ( 0 )
  {
  }

  webstreamerInputProcessor::~webstreamerInputProcessor ( )
  {
  }

  void webstreamerInputProcessor::setScreenSize ( unsigned int width_, 
                                                  unsigned int height_ )
  {
    _screenWidth = static_cast < double > ( width_ );
    _screenHeight = static_cast < double > ( height_ );
  }

  void 
  webstreamerInputProcessor::ProcessMouseInput ( const webstreamer::MouseEvent & evt_ ) 
  {
    int realPosX = static_cast<int> ( evt_.x() * _screenWidth );
    int realPosY = static_cast<int> ( evt_.y() * _screenHeight );

    inputHandler::TMouseInputButton 
      mib = WSButtonToDSButton ( evt_.button() );
    inputHandler::TMouseInputState 
      mis = WSBtnActionToDSButtonState ( evt_.action() );

    inputManager::getInstance().handleMouseInput( realPosX, 
                                                  realPosY, 
                                                  mib, 
                                                  mis );
  }

  void 
  webstreamerInputProcessor::ProcessKeyboardInput( const webstreamer::KeyboardEvent & evt_ ) 
  {
    std::string key = evt_.key();

    if(key.empty())
    {
      return;
    }

    inputHandler::TKeyInputState kis = WSKeyStateToDSKeyState( evt_.action() );

    inputManager::getInstance().handleKeyInput ( key, kis );
  }

  inputHandler::TMouseInputButton 
  webstreamerInputProcessor::WSButtonToDSButton( webstreamer::MouseButton mb_ )
  {
    inputHandler::TMouseInputButton 
      result = inputHandler::TMouseInputButton::MIB_UNKNOWN;

    switch ( mb_ )
    {
      case webstreamer::MouseButton::MAIN:
        result = inputHandler::TMouseInputButton::MIB_BUTTON_0;
        break;
      case webstreamer::MouseButton::AUXILIARY:
        result = inputHandler::TMouseInputButton::MIB_BUTTON_1;
        break;
      case webstreamer::MouseButton::SECONDARY:
        result = inputHandler::TMouseInputButton::MIB_BUTTON_2;
        break;
      case webstreamer::MouseButton::FOURTH:
        break;
      case webstreamer::MouseButton::FIFTH:
        break;
    }

    return result;
  }

  inputHandler::TMouseInputState 
  webstreamerInputProcessor::WSBtnActionToDSButtonState ( webstreamer::MouseAction ma_ )
  {
    inputHandler::TMouseInputState 
      result = inputHandler::TMouseInputState::MIS_DUMMY;

    switch( ma_ )
    {
      case webstreamer::MouseAction::BUTTON_DOWN:
        result = inputHandler::TMouseInputState::MIS_BUTTON_DOWN;
        break;
      case webstreamer::MouseAction::BUTTON_UP:
        result = inputHandler::TMouseInputState::MIS_BUTTON_UP;
        break;
      case webstreamer::MouseAction::DOUBLE_CLICK:
        result = inputHandler::TMouseInputState::MIS_BUTTON_DBL_CLICK;
        break;
    }

    return result;
  }

  inputHandler::TKeyInputState 
  webstreamerInputProcessor::WSKeyStateToDSKeyState ( webstreamer::KeyboardAction ka_ )
  {
    inputHandler::TKeyInputState 
      result = inputHandler::KeyInputState::KIS_KEY_UNKNOWN;

    switch ( ka_ )
    {
      case webstreamer::KeyboardAction::KEY_DOWN:
        result = inputHandler::TKeyInputState::KIS_KEY_DOWN;
        break;
      case webstreamer::KeyboardAction::KEY_UP:
        result = inputHandler::TKeyInputState::KIS_KEY_UP;
        break;
      case webstreamer::KeyboardAction::KEY_PRESS:
        result = inputHandler::TKeyInputState::KIS_KEY_PRESS;
        break;
    }

    return result;
  }
}
#endif //WEBSTREAMER defined
