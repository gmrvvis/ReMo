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

#ifndef REMO_FLOW_DEVICETOSDLVIEWER_H
#define REMO_FLOW_DEVICETOSDLVIEWER_H

#include <memory>

#include "flow.h"
#include "streamDeviceIn.h"
#include "streamSDLViewerOut.h"
#include "mediaSDLViewer.h"

namespace remo
{
  class flowDeviceToSDLViewer: public flow
  {
    public:
      flowDeviceToSDLViewer ( stream* inStream_,
                              stream* outStream_,
                              bool continuousExecution_ = false,
                              unsigned int numFrames_ = 128 );

      virtual ~flowDeviceToSDLViewer ( ) = default;

      virtual void init ( );
      virtual void processStreams ( );

      void loop ( );

      void setNumFramesToCapture ( unsigned int numFrames_ )
      {
        _numFrames = numFrames_;
      };

    private:
      void releaseResources ( const std::string& msg_ );

      streamDeviceIn* _inDevice;
      streamSDLViewerOut* _outViewer;

      bool _continuousExecution;
      unsigned int _numFrames;
      bool _stop;
 
      AVPacket* _packet;
      AVFrame* _frame;
      AVFrame* _frameYUV;
      
      SwsContext* _swsCtx;
  };
}

#endif //REMO_FLOW_DEVICETOSDLVIEWER_H
