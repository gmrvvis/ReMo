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

#include "FlowDeviceToVideoFile.h"
#include "Utils.h"

namespace remo
{
  FlowDeviceToVideoFile::FlowDeviceToVideoFile ( Stream* inStream_,
                                                 Stream* outStream_,
                                                 bool continuousExecution_,
                                                 unsigned int numFrames_ )
    : Flow ( inStream_, outStream_ ),
    _continuousExecution ( continuousExecution_ ),
    _numFrames ( numFrames_ )
  {
    _inDevice = static_cast<StreamDeviceIn*>( _inStream );
    _outFile = static_cast<StreamVideoFileOut*>( _outStream );

    init ( );
  }

  void FlowDeviceToVideoFile::init ( void )
  {
    Utils::getInstance ( )->getLog ( ) ( LOG_LEVEL::INFO,
                                         "Init FFmpeg/libAV functionality on device to video file Flow.",
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
      _outFile->init ( );
    }
    else
    {
      Utils::getInstance ( )->getErrorManager ( )
                            ->criticalError ( "Error init out Stream." );
    }

    Utils::getInstance ( )->getLog ( ) ( LOG_LEVEL::INFO,
                                         "All streams has been init succesfully." );
  }

  void FlowDeviceToVideoFile::releaseResources ( const std::string& msg_ )
  {
    av_packet_unref ( _inAVPacket );
    av_packet_free ( &_inAVPacket );

    av_packet_unref ( _outAVPacket );
    av_packet_free ( &_outAVPacket );

    av_frame_unref ( _inAVFrame );
    av_frame_free ( &_inAVFrame );

    av_frame_unref ( _outAVFrame );
    av_frame_free ( &_outAVFrame );

    sws_freeContext ( _swsCtx );

    av_free ( _videoOutBuffer );

    Utils::getInstance ( )->getErrorManager ( )->criticalError ( msg_ );
  }

  void FlowDeviceToVideoFile::processStreams ( void )
  {
    int value = 0;

    _inAVPacket = av_packet_alloc ( );
    if ( !_inAVPacket )
    {
      Utils::getInstance ( )->getErrorManager ( )->criticalError ( "Unable to "
                                                                   "reserve "
                                                                   "working "
                                                                   "package." );
    }

    _outAVPacket = av_packet_alloc ( );
    if ( !_outAVPacket )
    {
      av_packet_unref ( _inAVPacket );
      av_packet_free ( &_inAVPacket );
      Utils::getInstance ( )->getErrorManager ( )->criticalError ( "Unable to "
                                                                   "reserve "
                                                                   "working "
                                                                   "package." );
    }

    _inAVFrame = av_frame_alloc ( );
    if ( !_inAVFrame )
    {
      av_packet_unref ( _inAVPacket );
      av_packet_free ( &_inAVPacket );

      av_packet_unref ( _outAVPacket );
      av_packet_free ( &_outAVPacket );

      Utils::getInstance ( )->getErrorManager ( )->criticalError ( "Unable to "
                                                                   "reserve "
                                                                   "working "
                                                                   "package." );
    }

    _outAVFrame = av_frame_alloc ( );
    if ( !_outAVFrame )
    {
      av_packet_unref ( _inAVPacket );
      av_packet_free ( &_inAVPacket );

      av_packet_unref ( _outAVPacket );
      av_packet_free ( &_outAVPacket );

      av_frame_unref ( _inAVFrame );
      av_frame_free ( &_inAVFrame );

      Utils::getInstance ( )->getErrorManager ( )->criticalError ( "Unable to "
                                                                   "reserve "
                                                                   "working "
                                                                   "frame." );
    }

    int nbytes =
      av_image_get_buffer_size ( _outFile->getCodecContext ( )->pix_fmt,
                                 _outFile->getCodecContext ( )->width,
                                 _outFile->getCodecContext ( )->height, 32 );

    _videoOutBuffer = ( uint8_t* ) av_malloc ( nbytes );
    if ( !_videoOutBuffer )
    {
      av_packet_unref ( _inAVPacket );
      av_packet_free ( &_inAVPacket );

      av_packet_unref ( _outAVPacket );
      av_packet_free ( &_outAVPacket );

      av_frame_unref ( _inAVFrame );
      av_frame_free ( &_inAVFrame );

      av_frame_unref ( _outAVFrame );
      av_frame_free ( &_outAVFrame );

      Utils::getInstance ( )->getErrorManager ( )->criticalError ( "Unable to "
                                                                   "reserve "
                                                                   "output "
                                                                   "video "
                                                                   "buffer. " );
    }

    value = av_image_fill_arrays ( _outAVFrame->data,
                                   _outAVFrame->linesize,
                                   _videoOutBuffer,
                                   AV_PIX_FMT_YUV420P,
                                   _outFile->getCodecContext ( )->width,
                                   _outFile->getCodecContext ( )->height,
                                   1 );
    if ( value < 0 )
    {
      av_packet_unref ( _inAVPacket );
      av_packet_free ( &_inAVPacket );

      av_packet_unref ( _outAVPacket );
      av_packet_free ( &_outAVPacket );

      av_frame_unref ( _inAVFrame );
      av_frame_free ( &_inAVFrame );

      av_frame_unref ( _outAVFrame );
      av_frame_free ( &_outAVFrame );

      av_free ( _videoOutBuffer );

      Utils::getInstance ( )->getErrorManager ( )
                            ->criticalError ( "Error filling image array. " );
    }

    _swsCtx = sws_getContext ( _inDevice->getCodecContext ( )->width,
                               _inDevice->getCodecContext ( )->height,
                               _inDevice->getCodecContext ( )->pix_fmt,
                               _outFile->getCodecContext ( )->width,
                               _outFile->getCodecContext ( )->height,
                               _outFile->getCodecContext ( )->pix_fmt,
                               SWS_BICUBIC, nullptr, nullptr, nullptr );
    if ( value < 0 )
    {
      av_packet_unref ( _inAVPacket );
      av_packet_free ( &_inAVPacket );

      av_packet_unref ( _outAVPacket );
      av_packet_free ( &_outAVPacket );

      av_frame_unref ( _inAVFrame );
      av_frame_free ( &_inAVFrame );

      av_frame_unref ( _outAVFrame );
      av_frame_free ( &_outAVFrame );

      sws_freeContext ( _swsCtx );

      av_free ( _videoOutBuffer );

      Utils::getInstance ( )->getErrorManager ( )->criticalError ( "Unable to "
                                                                   "reserve "
                                                                   "resources "
                                                                   "for "
                                                                   "context. " );
    }

    //#Packages could need multiple reading until a frame is generated (under testing)
    //int how_many_packets_to_process = 8;
    unsigned int j = 0;
    while (
      ( av_read_frame ( _inDevice->getFormatContext ( ), _inAVPacket ) >= 0 )
        && ( _numFrames > 0 ))
    {
      if ( !_continuousExecution )
      {
        --_numFrames;
      }

      if ( _inAVPacket->stream_index == _inDevice->getVideoStreamIndx ( ))
        //&& (--how_many_packets_to_process < 0)
      {
        value = avcodec_send_packet ( _inDevice->getCodecContext ( ), _inAVPacket );
        if ( value < 0 )
        {
          releaseResources ( "Unable to decode video." );
        }

        value = avcodec_receive_frame ( _inDevice->getCodecContext ( ), _inAVFrame );
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
          sws_scale ( _swsCtx,
                      _inAVFrame->data,
                      _inAVFrame->linesize,
                      0,
                      _inDevice->getCodecContext ( )->height,
                      _outAVFrame->data,
                      _outAVFrame->linesize );

          av_init_packet ( _outAVPacket );
          _outAVPacket->data = nullptr;
          _outAVPacket->size = 0;

          //###Old style -> looks less agressive!
          //avcodec_encode_video2 ( _pOutFile->getCodecContext ( ), _outAVPacket, _outAVFrame, &got_picture );

          avcodec_send_frame ( _outFile->getCodecContext ( ), _outAVFrame );
          avcodec_receive_packet ( _outFile->getCodecContext ( ), _outAVPacket );

          if ( _outAVPacket->pts != AV_NOPTS_VALUE)
          {
            _outAVPacket->pts = av_rescale_q ( _outAVPacket->pts,
                                               _outFile->getCodecContext ( )
                                                        ->time_base,
                                               _outFile->getVideoStream ( )
                                                        ->time_base );
          }
          if ( _outAVPacket->dts != AV_NOPTS_VALUE)
          {
            _outAVPacket->dts = av_rescale_q ( _outAVPacket->dts,
                                               _outFile->getCodecContext ( )
                                                        ->time_base,
                                               _outFile->getVideoStream ( )
                                                        ->time_base );
          }
          Utils::getInstance ( )
            ->getLog ( ) ( LOG_LEVEL::INFO,
                           "Write frame ",
                           ++j,
                           " -> size: ",
                           _outAVPacket->size/1000 );

          if ( av_write_frame ( _outFile->getFormatContext ( ), _outAVPacket ) != 0 )
          {
            releaseResources ( "Error writing video frame." );
          }

          av_packet_unref ( _outAVPacket );
          av_packet_unref ( _outAVPacket );
        }
      }
    }

    //### Progressive video writing could be better option! -> Use av_encodeframe progresively
    value = av_write_trailer ( _outFile->getFormatContext ( ));
    if ( value < 0 )
    {
      releaseResources ( "Error writing output file." );
    }

    av_packet_unref ( _inAVPacket );
    av_packet_free ( &_inAVPacket );

    av_packet_unref ( _outAVPacket );
    av_packet_free ( &_outAVPacket );

    av_frame_unref ( _inAVFrame );
    av_frame_free ( &_inAVFrame );

    av_frame_unref ( _outAVFrame );
    av_frame_free ( &_outAVFrame );

    sws_freeContext ( _swsCtx );

    av_free ( _videoOutBuffer );

//    //Full video information!
//    std::cout<<"Output file information :"<<std::endl;
//    av_dump_format(_pOutFile->getFormatContext ( ) , 0 ,"output.mp4" ,1);
  }
}
