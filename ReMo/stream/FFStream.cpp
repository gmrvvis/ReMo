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

#include "FFStream.h"
#include "Utils.h"

namespace remo
{
  FFStream::FFStream ( Media* inMedia_ )
    : Stream ( inMedia_ ),
    _videoStreamIndx ( -1 ),
    _AVFormatContext ( nullptr ),
    _AVInputFormat ( nullptr ),
    _AVCodec ( nullptr ),
    _AVCodecContext ( nullptr )
  {
    _description = "Video Stream";
  }

  FFStream::~FFStream ( void )
  {
    avformat_close_input ( &_AVFormatContext );
    if ( !_AVFormatContext )
    {
      Utils::getInstance ( )->getLog ( ) ( remo::LOG_LEVEL::INFO,
                                           "Audio-Video Stream closed sucessfully." );
    }
    else
    {
      Utils::getInstance ( )->getErrorManager ( )->criticalError (
        "Unable to close the Audio-Video Stream." );
    }

    avformat_free_context ( _AVFormatContext );
    if ( !_AVFormatContext )
    {
      Utils::getInstance ( )->getLog ( ) ( remo::LOG_LEVEL::INFO,
                                           "Audio-Video format successfully free." );
    }
    else
    {
      Utils::getInstance ( )->getErrorManager ( )->criticalError (
        "Unable to free audio Audio-Video format context." );
    }
  }
}
