#ifdef REMO_USE_WEBSTREAMER

#include "WebstreamerInputProcessor.h"

namespace remo
{
  WebstreamerInputProcessor::WebstreamerInputProcessor ( )
    : _screenWidth ( 0 )
    , _screenHeight ( 0 )
  {
  }

  WebstreamerInputProcessor::~WebstreamerInputProcessor ( )
  {
  }

  void WebstreamerInputProcessor::setScreenSize ( unsigned int width_, 
                                                  unsigned int height_ )
  {
    _screenWidth = static_cast < double > ( width_ );
    _screenHeight = static_cast < double > ( height_ );
  }
}
#endif //REMO_USE_WEBSTREAMER defined
