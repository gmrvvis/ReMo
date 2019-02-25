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

#ifndef REMO_FLOW_DEVICETOVIDEOFILE_H
#define REMO_FLOW_DEVICETOVIDEOFILE_H

#include <memory>

#include "Flow.h"
#include "../stream/StreamDeviceIn.h"
#include "../stream/StreamVideoFileOut.h"

namespace remo
{
  class FlowDeviceToVideoFile: public Flow
  {
    public:
      FlowDeviceToVideoFile ( Stream* inStream_,
                              Stream* outStream_,
                              bool continuousExecution_ = false,
                              unsigned int numFrames_ = 128 );
      virtual ~FlowDeviceToVideoFile ( void ) = default;;

      virtual void init ( void );
      virtual void processStreams ( void );

      void setNumFramesToCapture ( unsigned int numFrames_ )
      {
        _numFrames = numFrames_;
      };

    private:
      void releaseResources ( const std::string& msg_ );

      unsigned int _continuousExecution;
      unsigned int _numFrames;
      uint8_t* _videoOutBuffer;

      SwsContext* _swsCtx;

      StreamDeviceIn* _inDevice;
      StreamVideoFileOut* _outFile;

      AVPacket* _inAVPacket;
      AVPacket* _outAVPacket;
      AVFrame* _inAVFrame;
      AVFrame* _outAVFrame;
  };
}

#endif //REMO_FLOW_DEVICETOVIDEOFILE_H
