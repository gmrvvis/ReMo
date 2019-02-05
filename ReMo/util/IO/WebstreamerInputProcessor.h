#ifdef REMO_USE_WEBSTREAMER

#ifndef __REMO_WSINPUTHANDLER_H__
#define __REMO_WSINPUTHANDLER_H__

#include <stdexcept>

#include <webstreamer/webstreamer.hpp>
#include <webstreamer/mouse_event.hpp>
#include <webstreamer/keyboard_event.hpp>

namespace remo
{
  class WebstreamerInputProcessor : public webstreamer::AsynchronousInputProcessor 
  {
    public:
      WebstreamerInputProcessor ( );
      ~WebstreamerInputProcessor ( );

      void setScreenSize ( unsigned int width_, 
                           unsigned int height_ );

    protected:
      double _screenWidth;
      double _screenHeight;
  };
}
#endif //REMO_USE_WEBSTREAMER defined
#endif
