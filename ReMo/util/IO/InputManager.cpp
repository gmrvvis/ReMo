#include "InputManager.h"

namespace remo
{
  namespace inputHandler
  {
    void DummyInputHandler::handleMouseInput( int screenX_,
                                              int screenY_, 
                                              TMouseInputButton btn_, 
                                              TMouseInputState btnState_ )
    {
      (void)screenX_; (void)screenY_; (void)btn_; (void)btnState_;
    }

    void DummyInputHandler::handleKeyInput( const std::string & key_,
                                            TKeyInputState keyState_ )
    {
      (void)key_; (void)keyState_;
    }
  }

// ---------------------------------------------------------

  InputManager InputManager::_INSTANCE;

  InputManager & InputManager::getInstance ( )
  {
    return _INSTANCE;
  }

  InputManager::InputManager ( )
  {
    registerInputHandler<inputHandler::DummyInputHandler> ( );
  }

  InputManager::~InputManager ( )
  {
  }

  void InputManager::handleMouseInput( int screenX_, 
                                       int screenY_, 
                                       inputHandler::TMouseInputButton btn_,
                                       inputHandler::TMouseInputState btnState_ )
  {
    _inputHandler.get ( )->handleMouseInput ( screenX_, 
                                              screenY_, 
                                              btn_, 
                                              btnState_ );
  }

  void InputManager::handleKeyInput( const std::string & key_,
                                     inputHandler::TKeyInputState keyState_ )
  {
    _inputHandler.get ( )->handleKeyInput ( key_, keyState_ );
  }
}
