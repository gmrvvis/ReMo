#ifndef __REMO_INPUTHANDLER_ABSTRACTINPUTHANDLER_H__
#define __REMO_INPUTHANDLER_ABSTRACTINPUTHANDLER_H__

#include <cstdint>
#include <string>

namespace remo
{
  namespace inputHandler
  {
    typedef enum class MouseInputButton : std::uint8_t
    {
      MIB_BUTTON_0 = 0,
      MIB_BUTTON_1 = 1,
      MIB_BUTTON_2 = 2,
      MIB_WHEEL = 3,
      MIB_UNKNOWN = 4
    } TMouseInputButton;

    typedef enum class MouseInputState : std::uint8_t
    {
      MIS_BUTTON_DOWN = 0,
      MIS_BUTTON_UP = 1,
      MIS_BUTTON_DBL_CLICK = 2,
      MIS_DUMMY = 3
    } TMouseInputState;

    typedef enum class KeyInputState : std::uint8_t
    {
      KIS_KEY_DOWN = 0,
      KIS_KEY_UP = 1,
      KIS_KEY_PRESS = 2,
      KIS_KEY_UNKNOWN = 3
    } TKeyInputState;

    class abstractInputHandler
    {
      public:
        virtual void handleMouseInput ( int screenX_,
                                        int screenY_,
                                        TMouseInputButton btn_,
                                        TMouseInputState btnState_ ) = 0;

        virtual void handleKeyInput ( const std::string & key_,
                                      TKeyInputState keyState_ ) = 0;
    };
  }
}

#endif
