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

#ifndef REMO_FLOW_DEVICETOSDLVIEWER_H
#define REMO_FLOW_DEVICETOSDLVIEWER_H

#include <memory>

#include "Flow.h"
#include "../stream/StreamDeviceIn.h"
#include "../stream/StreamSDLViewerOut.h"
#include "../media/MediaSDLViewer.h"

namespace remo
{
  class FlowDeviceToSDLViewer: public Flow
  {
    public:
      FlowDeviceToSDLViewer ( Stream* inStream_,
                              Stream* outStream_,
                              bool continuousExecution_ = false,
                              unsigned int numFrames_ = 128 );

      virtual ~FlowDeviceToSDLViewer ( void ) = default;

      virtual void init ( void );
      virtual void processStreams ( void );

      void loop ( );

      void setNumFramesToCapture ( unsigned int numFrames_ )
      {
        _numFrames = numFrames_;
      };

    private:
      void releaseResources ( const std::string& msg_ );

      StreamDeviceIn* _inDevice;
      StreamSDLViewerOut* _outViewer;

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

#endif //REMO_USE_SDL
