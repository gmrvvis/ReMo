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

#include "streamDeviceIn.h"
#include "Utils.h"

namespace remo
{
  streamDeviceIn::streamDeviceIn ( media* inMedia_ )
    : ffStream ( inMedia_ )
  {
    _description = "DeviceIn Stream";
  }

  void streamDeviceIn::init ( )
  {
    _media->init ( );

    int value = 0;
    _AVFormatContext = avformat_alloc_context ( );
    if ( !_AVFormatContext )
    {
      Utils::getInstance ( )->getErrorManager ( )->criticalError ( "Unable to"
                                                                   "create "
                                                                   "format "
                                                                   "context " );
    }

    //Both media could be treated as the same media!
    if ( mediaDesktop* vMediaD_ = dynamic_cast<mediaDesktop*>(_media))
    {
      _AVInputFormat =
        av_find_input_format ( vMediaD_->getQualifier ( ).c_str ( ));
      AVDictionary* aux = vMediaD_->getOptions ( );
      value = avformat_open_input ( &_AVFormatContext,
                                    vMediaD_->getDesktopConfigAsString ( )
                                           .c_str ( ),
                                    _AVInputFormat,
                                    &aux );
      if ( value != 0 )
      {
        avformat_close_input ( &_AVFormatContext );
        Utils::getInstance ( )->getErrorManager ( )
                              ->criticalError (
                                "Couldn't open input stream for desktop grabber." );
      }
    }
    else if ( mediaWebCam* vMediaWC_ = dynamic_cast<mediaWebCam*>(_media))
    {
      _AVInputFormat =
        av_find_input_format ( vMediaWC_->getQualifier ( ).c_str ( ));
      value = avformat_open_input ( &_AVFormatContext,
                                    vMediaWC_->getPhysicalMedia ( ).c_str ( ),
                                    _AVInputFormat,
                                    nullptr );
      if ( value != 0 )
      {
        avformat_close_input ( &_AVFormatContext );
        Utils::getInstance ( )->getErrorManager ( )->criticalError (
          "Couldn't open input stream for web cam." );
      }

    }
    else
    {
      avformat_close_input ( &_AVFormatContext );
      Utils::getInstance ( )->getErrorManager ( )->criticalError (
        "Media not supported for input stream." );
    }

    if ( value != 0 )
    {
      avformat_close_input ( &_AVFormatContext );
      Utils::getInstance ( )->getErrorManager ( )
                            ->criticalError ( "Error in opening input device." );
    }

    if ( avformat_find_stream_info ( _AVFormatContext, nullptr ) < 0 )
    {
      avformat_close_input ( &_AVFormatContext );
      Utils::getInstance ( )->getErrorManager ( )->criticalError (
        "Couldn't find stream information." );
    }

    _videoStreamIndx = -1;
    for ( unsigned int i = 0; i < _AVFormatContext->nb_streams;
          ++i ) // find video stream posistion/index.
    {
      if ( _AVFormatContext->streams[i]->codecpar->codec_type
        == AVMEDIA_TYPE_VIDEO )
      {
        _videoStreamIndx = i;
        break;
      }
    }

    if ( _videoStreamIndx == -1 )
    {
      avformat_close_input ( &_AVFormatContext );
      Utils::getInstance ( )->getErrorManager ( )->criticalError (
        "Unable to find the video stream index." );
    }

    _AVCodecContext =
      avcodec_alloc_context3 ( avcodec_find_decoder ( _AVFormatContext
                                                        ->streams[_videoStreamIndx]
                                                        ->codecpar
                                                        ->codec_id ));
    if ( avcodec_parameters_to_context ( _AVCodecContext,
                                         _AVFormatContext
                                           ->streams[_videoStreamIndx]
                                           ->codecpar ) < 0 )
    {
      avcodec_close ( _AVCodecContext );
      avformat_close_input ( &_AVFormatContext );
      Utils::getInstance ( )->getErrorManager ( )->criticalError (
        "Unable to ser parameters to context." );
    }

    _AVCodec = avcodec_find_decoder ( _AVCodecContext->codec_id );
    if ( _AVCodec == nullptr )
    {
      avcodec_close ( _AVCodecContext );
      avformat_close_input ( &_AVFormatContext );
      Utils::getInstance ( )->getErrorManager ( )
                            ->criticalError ( "Codec not found." );
    }

    value = avcodec_open2 ( _AVCodecContext,
                            _AVCodec,
                            nullptr );//Initialize the AVCodecContext to use the given AVCodec.
    if ( value < 0 )
    {
      avcodec_close ( _AVCodecContext );
      avformat_close_input ( &_AVFormatContext );
      Utils::getInstance ( )->getErrorManager ( )
                            ->criticalError ( "Unable to open the av codec." );
    }
  }
}
