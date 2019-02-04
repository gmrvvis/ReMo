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

#ifndef REMO_STREAM_WEBSTREAMER_H
#define REMO_STREAM_WEBSTREAMER_H

#include "FFStream.h"
#include "MediaWebStreamer.h"

namespace remo
{
  class StreamWebStreamer: public FFStream
  {
    public:
      StreamWebStreamer ( Media* outMedia_ );
      virtual ~StreamWebStreamer ( void );

      std::string getDescription ( void );

      virtual void init ( void );

      bool isSync ( void );

      void pushFrame ( AVFrame* frame_ );

      Media* getMedia ( ) { return _media; };

    private:
      MediaWebStreamer * _mediaWebStreamer;
      ImageConverter* _imageConverter;

      webstreamer::StopWatch<> frame_stopwatch;
      std::chrono::microseconds frame_interval;

  };
}
#endif //REMO_USE_WEBSTREAMER defined
#endif //REMO_STREAM_WEBSTREAMER_H
