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

#ifndef REMO_FFOPERATION_H
#define REMO_FFOPERATION_H

#include <string>

#include "../util/ffdefs.h"
#include "../pipeline/Operation.h"

namespace remo
{
  class FFOperation: public Operation
  {
    public:
      FFOperation ( void );
      virtual ~FFOperation ( void ) = default;

      virtual void init ( void ) = 0;
      virtual void apply ( void ) = 0;

      void setOptions ( AVDictionary* options_ ) { _options = options_; }
      void setOption ( std::string option_, std::string value_ );
      AVDictionary* getOptions ( ) { return _options; }

      void setFrames ( AVFrame* inAVFrame_, AVFrame* outAVFrame_ = nullptr );
      void setPackages ( AVPacket* inAVPacket_,
                         AVPacket* outAVPacket_ = nullptr );

    protected:
      AVDictionary* _options;

      AVFrame* _inAVFrame;
      AVFrame* _outAVFrame;

      AVPacket* _inAVPacket;
      AVPacket* _outAVPacket;
  };
}
#endif //REMO_FFOPERATION_H
