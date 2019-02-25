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

#include "StreamVideoFileOut.h"
#include "../util/Utils.h"
#include "../media/MediaVideoFile.h"

namespace remo
{
  StreamVideoFileOut::StreamVideoFileOut ( Media* outMedia_ ):
    FFStream ( outMedia_ )
  {
    _videoStream = nullptr;
    _options = nullptr;
    _description = "Out Video Stream";
  }

  void StreamVideoFileOut::init ( void )
  {
    _AVFormatContext = nullptr;
    _options = nullptr;
    int codec_id = 0;
    int value = 0;
    const char* output_file =
      static_cast<MediaVideoFile*>(_media)->getFileName ( ).c_str ( );

    _outputFormat = av_guess_format ( nullptr, output_file, nullptr );
    if ( !_outputFormat )
    {
      Utils::getInstance ( )->getErrorManager ( )
                            ->criticalError ( "Error in guessing the video "
                                              "format, try with "
                                              "correct format!." );
    }

    avformat_alloc_output_context2 ( &_AVFormatContext,
                                     nullptr,
                                     nullptr,
                                     output_file );
    if ( !_AVFormatContext )
    {
      Utils::getInstance ( )->getErrorManager ( )->criticalError (
        "Error in allocating av format output context." );
    }

    _videoStream = avformat_new_stream ( _AVFormatContext, nullptr );
    if ( !_videoStream )
    {
      avformat_close_input ( &_AVFormatContext );
      Utils::getInstance ( )->getErrorManager ( )->criticalError (
        "Error in creating a av format new Stream." );
    }

    _AVCodec = avcodec_find_encoder ( AV_CODEC_ID_MPEG4 );
    if ( !_AVCodec )
    {
      avformat_close_input ( &_AVFormatContext );
      Utils::getInstance ( )->getErrorManager ( )
                            ->criticalError (
                              "Error in finding the av codecs. try again with correct codec." );
    }

    _AVCodecContext = avcodec_alloc_context3 ( _AVCodec );
    if ( !_AVCodecContext )
    {
      avformat_close_input ( &_AVFormatContext );
      Utils::getInstance ( )->getErrorManager ( )->criticalError (
        "Error in allocating the codec contexts." );
    }


    //https://stackoverflow.com/questions/33981707/ffmpeg-copy-streams-without-transcode
    value = avcodec_parameters_to_context ( _AVCodecContext, _videoStream->codecpar);
    if (value < 0)
    {
      avcodec_free_context( &_AVCodecContext );
      Utils::getInstance ( )->getErrorManager ( )->criticalError ( "Unable to set parameters to context." );
    }

    //### deprecated!, it needs to be changed!
    _AVCodecContext = _videoStream->codec;

    //### set property of the video file multiple properties needs to be evaluated here!
    //Alternatives: AV_CODEC_ID_MPEG4; // AV_CODEC_ID_H264 //AV_CODEC_ID_MPEG1VIDEO
    _AVCodecContext->codec_id = AV_CODEC_ID_MPEG4;
    _AVCodecContext->codec_type = AVMEDIA_TYPE_VIDEO;
    _AVCodecContext->bit_rate = 4e7;
    _AVCodecContext->gop_size = 6;
    _AVCodecContext->max_b_frames = 4;
    _AVCodecContext->width = 1024;
    _AVCodecContext->height = 768;
    _AVCodecContext->pix_fmt = AV_PIX_FMT_YUV420P;
    _AVCodecContext->time_base = ( AVRational ) { 1, 30 };

    //av_codec_get_tag2(_AVFormatContext->oformat->codec_tag, _AVCodec->id, &_AVCodecContext->codec_tag);
//    value = avcodec_open2(_AVCodecContext, _AVCodec, nullptr);
//    if (value < 0)
//      Utils::getInstance ( )->getErrorManager ( )->criticalError ( "Cannot open video Encoder for Stream." );
//
//    //_AVCodecContext->sample_aspect_ratio = ->sample_aspect_ratio;
//    _AVCodecContext->sample_rate = 64e3;
//    _AVCodecContext->channels = 1;
//    av_opt_set(_AVCodecContext->priv_data, "preset", "ultrafast", 0);
//    av_opt_set(_AVCodecContext->priv_data, "tune", "zerolatency", 0);


    if ( codec_id == AV_CODEC_ID_H264 )
      av_opt_set ( _AVCodecContext->priv_data, "preset", "slow", 0 );

    //Header definition
    if ( _AVFormatContext->oformat->flags & AVFMT_GLOBALHEADER )
      _AVCodecContext->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;

    value = avcodec_open2 ( _AVCodecContext, _AVCodec, nullptr );
    if ( value < 0 )
    {
      avcodec_close ( _AVCodecContext );
      avformat_close_input ( &_AVFormatContext );
      Utils::getInstance ( )->getErrorManager ( )
                            ->criticalError ( "Error in opening the avcodec." );
    }

    if ( !( _AVFormatContext->flags & AVFMT_NOFILE ))
    {
      if ( avio_open2 ( &_AVFormatContext->pb,
                        output_file,
                        AVIO_FLAG_WRITE,
                        nullptr,
                        nullptr ) < 0 )
      {
        avcodec_close ( _AVCodecContext );
        avformat_close_input ( &_AVFormatContext );
        Utils::getInstance ( )->getErrorManager ( )->criticalError (
          "Error in creating the video file." );
      }
    }

    if ( !_AVFormatContext->nb_streams )
    {
      avcodec_close ( _AVCodecContext );
      avformat_close_input ( &_AVFormatContext );
      Utils::getInstance ( )->getErrorManager ( )->criticalError (
        "Output file dose not contain any Stream." );
    }

    value = av_dict_set ( &_options, "framerate", "30", 0 );
    if ( value < 0 )
    {
      avcodec_close ( _AVCodecContext );
      avformat_close_input ( &_AVFormatContext );
      Utils::getInstance ( )->getErrorManager ( )->criticalError (
        "Error in setting dictionary value." );
    }

    value = av_dict_set ( &_options, "preset", "medium", 0 );
    if ( value < 0 )
    {
      avcodec_close ( _AVCodecContext );
      avformat_close_input ( &_AVFormatContext );
      Utils::getInstance ( )->getErrorManager ( )
                            ->criticalError ( "Error in setting preset values." );
    }

    //###value = avformat_find_stream_info(_AVFormatContext, nullptr);
    if ( value < 0 )
    {
      avcodec_close ( _AVCodecContext );
      avformat_close_input ( &_AVFormatContext );
      Utils::getInstance ( )->getErrorManager ( )->criticalError (
        "Unable to find the Stream information." );
    }

    value = avformat_write_header ( _AVFormatContext, &_options );
    if ( value < 0 )
    {
      avcodec_close ( _AVCodecContext );
      avformat_close_input ( &_AVFormatContext );
      Utils::getInstance ( )->getErrorManager ( )->criticalError (
        "Error in writing the header context." );
    }
  }
}
