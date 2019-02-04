/*
 * Copyright (c) 2018 CCS/UPM - GMRV/URJC.
 *
 * Authors: Juan Pedro Brito Méndez <juanpedro.brito@upm.es>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifdef REMO_USE_WEBSTREAMER

#include "StreamWebStreamer.h"

namespace remo
{
  StreamWebStreamer::StreamWebStreamer ( Media* outMedia_ ):
    FFStream ( outMedia_ )
  {
    _description = "Web Stream";
  }

  StreamWebStreamer::~StreamWebStreamer ( void )
  {
    delete _imageConverter;
  }

  void StreamWebStreamer::init ( void )
  {
    _media->init ( );
    _mediaWebStreamer = static_cast<MediaWebStreamer*>(_media);
    _imageConverter = new ImageConverter( _mediaWebStreamer->getImageWidth (), _mediaWebStreamer->getImageHeigh ());

    unsigned int fps = 0;
    frame_interval = fps == 0 ? std::chrono::microseconds(0)
                                : std::chrono::microseconds(static_cast<unsigned int>(
                                     1000.0 * 1000.0 / static_cast<double>(fps)));
    frame_stopwatch.Start ();
  }

  bool StreamWebStreamer::isSync ( void )
  {
    bool sync_=false;
    if (frame_stopwatch.elapsed_time() < frame_interval)
    {
      sync_=true;
      frame_stopwatch.Subtract(frame_interval);
    }
    return sync_;
  }

  void StreamWebStreamer::pushFrame ( AVFrame* frame_ )
  {
    _imageConverter->convert(frame_->data, frame_->width, frame_->height);
    _mediaWebStreamer->pushImage (_imageConverter);
  }
}
#endif //REMO_USE_WEBSTREAMER defined