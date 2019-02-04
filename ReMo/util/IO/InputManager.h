#ifndef __REMO_INPUTMANAGER_H__
#define __REMO_INPUTMANAGER_H__

#include <memory>

#include "AbstractInputhandler.h"
#include "Utils.h"

namespace remo
{
  namespace inputHandler
  {
    class DummyInputHandler : public AbstractInputHandler
    {
      public:
        void handleMouseInput( int screenX_, 
                               int screenY_, 
                               TMouseInputButton btn_, 
                               TMouseInputState btnState_ );

        void handleKeyInput( const std::string & key_ = nullptr,
                             TKeyInputState keyState_ = TKeyInputState::KIS_KEY_UNKNOWN );
    };
  }

  class InputManager
  {
    public:
      ~InputManager ( );

      static InputManager & getInstance ( );

      template<class T>
      void registerInputHandler ( )
      {
        if( !std::is_base_of< inputHandler::AbstractInputHandler, T >::value )
        {
          Utils::getInstance ( )->getErrorManager ( )->criticalError ( "Unable to "
                                                                      "register "
                                                                      "a non abstractinputhandler "
                                                                      "for webstreamer input." );
        }

        _inputHandler = std::make_unique<T> ( );
      }

      void handleMouseInput ( int screenX_, 
                              int screenY_, 
                              inputHandler::TMouseInputButton btn_,
                              inputHandler::TMouseInputState btnState_ );

      void handleKeyInput ( const std::string & key_,
                            inputHandler::TKeyInputState keyState_ );

    private:
      InputManager ( );

      static InputManager _INSTANCE;
      std::unique_ptr<inputHandler::AbstractInputHandler> _inputHandler;
  };
}

#endif
