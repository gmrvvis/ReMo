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
#ifdef REMO_USE_SDL

#include <thread>
#include <libavformat/version.h>

#include "FlowDeviceToSDLViewer.h"
#include "../util/Utils.h"

namespace remo
{
  FlowDeviceToSDLViewer::FlowDeviceToSDLViewer ( Stream* inStream_,
                                                 Stream* outStream_,
                                                 bool continuousExecution_,
                                                 unsigned int numFrames_ )
    : Flow ( inStream_, outStream_ ),
    _continuousExecution ( continuousExecution_ ),
    _numFrames ( numFrames_ ),
    _stop ( false )
  {
    _inDevice = static_cast<StreamDeviceIn*>( _inStream );
    _outViewer = static_cast<StreamSDLViewerOut*>( _outStream );

    init ( );
  }

  void FlowDeviceToSDLViewer::init ( void )
  {
    Utils::getInstance ( )->getLog ( ) ( LOG_LEVEL::INFO,
                                         "Init FFmpeg/libAV functionality on on device to viewer Flow",
                                         this->getDescription ( ));

#if LIBAVFORMAT_VERSION_INT < AV_VERSION_INT(58, 9, 100)
    av_register_all ( );
    avcodec_register_all ( );
#endif

    avdevice_register_all ( );
    Utils::getInstance ( )->getLog ( ) ( LOG_LEVEL::INFO,
                                         "All required functions are registered successfully." );

    Utils::getInstance ( )
      ->getLog ( ) ( LOG_LEVEL::INFO, "Init in Stream Flow." );
    if ( _inStream != nullptr )
    {
      _inDevice->init ( );
    }
    else
    {
      Utils::getInstance ( )->getErrorManager ( )
                            ->criticalError ( "Error init in Stream." );
    }

    Utils::getInstance ( )
      ->getLog ( ) ( LOG_LEVEL::INFO, "Init out Stream Flow." );
    if ( _outStream != nullptr )
    {
      _outViewer->init ( );
    }
    else
    {
      Utils::getInstance ( )->getErrorManager ( )
                            ->criticalError ( "Error init out Stream." );
    }

    Utils::getInstance ( )->getLog ( ) ( LOG_LEVEL::INFO,
                                         "All streams has been init succesfully." );

    if ( _ffPipeline != nullptr )
    {
      _ffPipeline->connectFramesAndPackages ( _frame, _frameYUV, _packet );
    }
  }

  void FlowDeviceToSDLViewer::releaseResources ( const std::string& msg_ )
  {
    av_packet_unref ( _packet );
    av_packet_free ( &_packet );

    av_frame_unref ( _frame );
    av_frame_free ( &_frame );

    av_frame_unref ( _frameYUV );
    av_frame_free ( &_frameYUV );

    sws_freeContext ( _swsCtx );

    Utils::getInstance ( )->getErrorManager ( )->criticalError ( msg_ );
  }

  void FlowDeviceToSDLViewer::processStreams ( void )
  {
    if ( _continuousExecution )
    {
      std::thread th_ ( &FlowDeviceToSDLViewer::loop, this );
      th_.detach ( ); 

      Utils::getInstance ( )->getLog ( ) ( LOG_LEVEL::WARNING,
                                           "Press any key to finish the thread!." );
      std::cin.get ( );
      _stop = true;
    }
    else
    {
      loop ( );
    }
  }

  void FlowDeviceToSDLViewer::loop ( void )
  {
    int value = 0;

    avformat_version ( );

    _packet = av_packet_alloc ( );
    if ( !_packet )
    {
      Utils::getInstance ( )->getErrorManager ( )->criticalError ( "Unable to"
                                                                   "reserve "
                                                                   "resources "
                                                                   "fo working "
                                                                   "packet." );
    }

    _frame = av_frame_alloc ( );
    if ( !_frame )
    {
      av_packet_unref ( _packet );
      av_packet_free ( &_packet );
      Utils::getInstance ( )->getErrorManager ( )->criticalError ( "Unable to "
                                                                   "reserve "
                                                                   "resources "
                                                                   "for "
                                                                   "working "
                                                                   "frame." );
    }

    _frameYUV = av_frame_alloc ( );
    if ( !_frameYUV )
    {
      av_packet_unref ( _packet );
      av_packet_free ( &_packet );
      av_frame_unref ( _frame );
      av_frame_free ( &_frame );
      Utils::getInstance ( )->getErrorManager ( )->criticalError ( "Unable to "
                                                                   "reserve "
                                                                   "resources "
                                                                   "for "
                                                                   "working "
                                                                   "YUVframe.");
    }

    MediaSDLViewer
      * vMedia_ = static_cast<MediaSDLViewer*>(_outViewer->getMedia ( ));

    _swsCtx = sws_getContext ( _inDevice->getCodecContext ( )->width,
                               _inDevice->getCodecContext ( )->height,
                               _inDevice->getCodecContext ( )->pix_fmt,
                               vMedia_->getOverlayWidth ( ),
                               vMedia_->getOverlayHeigh ( ),
                               AV_PIX_FMT_YUV420P,
                               SWS_BILINEAR,
                               nullptr,
                               nullptr,
                               nullptr );
    if ( !_swsCtx )
    {
      av_packet_unref ( _packet );
      av_packet_free ( &_packet );
      av_frame_unref ( _frame );
      av_frame_free ( &_frame );
      av_frame_unref ( _frameYUV );
      av_frame_free ( &_frameYUV );
      Utils::getInstance ( )->getErrorManager ( )->criticalError ( "Unable to "
                                                                   "reserve "
                                                                   "resources "
                                                                   "for "
                                                                   "context. " );
    }

    int actNumFrames = 0;
    int how_many_packets_to_process = 8;

    while ((( _continuousExecution ) && ( !_stop )) || ( _numFrames > 0 ))
    {
      if ( !_continuousExecution )
        --_numFrames;
      if ( av_read_frame ( _inDevice->getFormatContext ( ), _packet ) >= 0 )
      {
        if (( _packet->stream_index == _inDevice->getVideoStreamIndx ( ))
          && ( --how_many_packets_to_process < 0 ))
        {
          value = avcodec_send_packet ( _inDevice->getCodecContext ( ), _packet );
          if ( value < 0 )
          {
            releaseResources ( "Unable to decode video." );
          }

          value = avcodec_receive_frame ( _inDevice->getCodecContext ( ), _frame );

          if ( value == AVERROR( EAGAIN ) || value == AVERROR_EOF)
          {
            Utils::getInstance ( )
              ->getLog ( ) ( LOG_LEVEL::INFO, "Error receiving frame." );
            break;
          }
          else if ( value < 0 )
          {
            Utils::getInstance ( )->getLog ( ) ( LOG_LEVEL::INFO,
                                                 "Legitimate decoding error:",
                                                 value );
          }
          else
          {
            if ( _ffPipeline != nullptr )
            {
              _ffPipeline->process ( );
            }

            vMedia_->draw ( _frameYUV );
            sws_scale ( _swsCtx,
                        _frame->data,
                        _frame->linesize,
                        0,
                        _inDevice->getCodecContext ( )->height,
                        _frameYUV->data,
                        _frameYUV->linesize );
            ++actNumFrames;
          }
        }
      }
      av_packet_unref ( _packet );
    }
    av_packet_free ( &_packet );

    av_frame_unref ( _frame );
    av_frame_free ( &_frame );

    av_frame_unref ( _frameYUV );
    av_frame_free ( &_frameYUV );

    sws_freeContext ( _swsCtx );
  }
}

#endif //REMO_USE_SDL
