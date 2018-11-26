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

#ifndef REMO_FFPIPELINE_H
#define REMO_FFPIPELINE_H

#include <string>
#include <vector>

#include "ffdefs.h"
#include "stream.h"
#include "pipeline.h"
#include "ffOperation.h"

namespace remo
{
  class ffPipeline: public pipeline
  {
    public:
      //###Multistreams needs to be added!
      ffPipeline ( stream* inStream_ = nullptr,
                    stream* outStream_ = nullptr );

      ffPipeline ( AVFrame* inAVFrame_ = nullptr,
                    AVFrame* outAVFrame_ = nullptr,
                    AVPacket* inAVPacket_ = nullptr,
                    AVPacket* outAVPacket_ = nullptr );

      virtual ~ffPipeline ( ) = default;

      virtual void init ( );
      virtual void process ( );

      void addOperation ( ffOperation* op_ ) { _ops.push_back ( op_ ); };
      void connectFramesAndPackages ( AVFrame* inAVFrame_ = nullptr,
                                      AVFrame* outAVFrame_ = nullptr,
                                      AVPacket* inAVPacket_ = nullptr,
                                      AVPacket* outAVPacket_ = nullptr );

    protected:
      std::vector < ffOperation* > _ops;

      stream* _inStream;
      stream* _outStream;

      AVFrame* _inAVFrame;
      AVFrame* _outAVFrame;

      AVPacket* _inAVPacket;
      AVPacket* _outAVPacket;
  };
}
#endif //REMO_FFPIPELINE_H
