#include "inputManager.h"

namespace remo
{
  namespace inputHandler
  {
    void dummyInputHandler::handleMouseInput( int screenX_, 
                                              int screenY_, 
                                              TMouseInputButton btn_, 
                                              TMouseInputState btnState_ )
    {
      (void)screenX_; (void)screenY_; (void)btn_; (void)btnState_;
    }

    void dummyInputHandler::handleKeyInput( const std::string & key_,
                                            TKeyInputState keyState_ )
    {
      (void)key_; (void)keyState_;
    }
  }

// ---------------------------------------------------------

  inputManager inputManager::_INSTANCE;

  inputManager & inputManager::getInstance ( )
  {
    return _INSTANCE;
  }

  inputManager::inputManager ( )
  {
    registerInputHandler<inputHandler::dummyInputHandler> ( );
  }

  inputManager::~inputManager ( )
  {
  }

  void inputManager::handleMouseInput( int screenX_, 
                                       int screenY_, 
                                       inputHandler::TMouseInputButton btn_,
                                       inputHandler::TMouseInputState btnState_ )
  {
    _inputHandler.get ( )->handleMouseInput ( screenX_, 
                                              screenY_, 
                                              btn_, 
                                              btnState_ );
  }

  void inputManager::handleKeyInput( const std::string & key_,
                                     inputHandler::TKeyInputState keyState_ )
  {
    _inputHandler.get ( )->handleKeyInput ( key_, keyState_ );
  }
}
