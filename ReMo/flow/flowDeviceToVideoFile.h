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

#include "flow.h"
#include "streamDeviceIn.h"
#include "streamVideoFileOut.h"

namespace remo
{
  class flowDeviceToVideoFile: public flow
  {
    public:
      flowDeviceToVideoFile ( stream* inStream_,
                              stream* outStream_,
                              bool continuousExecution_ = false,
                              unsigned int numFrames_ = 128 );
      virtual ~flowDeviceToVideoFile ( ) = default;;

      virtual void init ( );
      virtual void processStreams ( );

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

      streamDeviceIn* _inDevice;
      streamVideoFileOut* _outFile;

      AVPacket* _inAVPacket;
      AVPacket* _outAVPacket;
      AVFrame* _inAVFrame;
      AVFrame* _outAVFrame;
  };
}

#endif //REMO_FLOW_DEVICETOVIDEOFILE_H
