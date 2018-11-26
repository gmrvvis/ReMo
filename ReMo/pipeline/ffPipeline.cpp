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

#include "ffPipeline.h"
#include "Utils.h"

namespace remo
{
  ffPipeline::ffPipeline ( stream* inStream_, stream* outStream_ )
    : pipeline ( )
  {
    _description = "Basic pipeline";

    _inAVFrame = nullptr;
    _outAVFrame = nullptr;
    _inAVPacket = nullptr;
    _outAVPacket = nullptr;    
    
    _inStream = inStream_;
    _outStream =outStream_;
  }

  ffPipeline::ffPipeline ( AVFrame* inAVFrame_, AVFrame* outAVFrame_,
                             AVPacket* inAVPacket_, AVPacket* outAVPacket_ )
    : pipeline ( ),
    _inAVFrame ( inAVFrame_ ),
    _outAVFrame ( outAVFrame_ ),
    _inAVPacket ( inAVPacket_ ),
    _outAVPacket ( outAVPacket_ )
  {
    _description = "Basic pipeline";
    
    _inStream = nullptr;
    _outStream = nullptr;
  }

  void ffPipeline::connectFramesAndPackages ( AVFrame* inAVFrame_,
                                               AVFrame* outAVFrame_,
                                               AVPacket* inAVPacket_,
                                               AVPacket* outAVPacket_ )
  {
    _inAVFrame = inAVFrame_;
    _outAVFrame = outAVFrame_;
    _inAVPacket = inAVPacket_;
    _outAVPacket = outAVPacket_;
  }

  void ffPipeline::init ( )
  {
    if (( _inAVFrame != nullptr )
      || ( _outAVFrame != nullptr )
      || ( _inAVPacket != nullptr )
      || ( _outAVPacket != nullptr ))
    {
      for ( auto& it_ : _ops )
      {
        it_->setFrames ( _inAVFrame, _outAVFrame );
        it_->setPackages ( _inAVPacket, _outAVPacket );
      }
    }
    else
      Utils::getInstance ( )
        ->getErrorManager ( )
        ->criticalError ( "Error on  pipeline. All objects are "
                          "nullptr." );
  }

  void ffPipeline::process ( )
  {
    for ( auto& it_ : _ops )
    {
      it_->apply ( );
      //### frames and packages needs to be swaped
    }
  }
}
