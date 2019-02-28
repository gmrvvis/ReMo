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

#ifndef REMO_FFSTREAM_H
#define REMO_FFSTREAM_H

#include "Stream.h"
#include "../util/ffdefs.h"

namespace remo
{
  class FFStream: public Stream
  {
    public:
      FFStream ( Media* media_ );
      virtual ~FFStream ( void );

      AVFormatContext* getFormatContext ( void ) { return _AVFormatContext; }
      AVCodecContext* getCodecContext ( void ) { return _AVCodecContext; }
      int getVideoStreamIndx ( void ) { return _videoStreamIndx; }

      virtual void init ( void ) = 0;

    protected:
      int _videoStreamIndx;

      AVFormatContext* _AVFormatContext;
      AVInputFormat* _AVInputFormat;

      AVCodec* _AVCodec;
      AVCodecContext* _AVCodecContext;

  };
}

#endif //REMO_STDSTREAM_H
