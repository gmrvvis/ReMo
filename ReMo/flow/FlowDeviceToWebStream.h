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

#ifdef REMO_USE_WEBSTREAMER

#ifndef REMO_FLOW_DEVICETOWEBSTREAM_H
#define REMO_FLOW_DEVICETOWEBSTREAM_H

#include <memory>

#include "Flow.h"
#include "StreamDeviceIn.h"
#include "StreamWebStreamer.h"
#include "MediaWebStreamer.h"

namespace remo
{
  class FlowDeviceToWebStream: public Flow
  {
    public:
      FlowDeviceToWebStream ( Stream* inStream_,
                              Stream* outStream_);

      virtual ~FlowDeviceToWebStream ( void ) = default;

      virtual void init ( void );
      virtual void processStreams ( void );

      void loop ( );

    private:
      void releaseResources ( const std::string& msg_ );

      StreamDeviceIn* _inDevice;
      StreamWebStreamer* _outWebStreamer;

      bool _stop;
 
      AVPacket* _packet;
      AVFrame* _frame;

      AVFrame* _frameProc;
  };
}
#endif //REMO_USE_WEBSTREAMER defined

#endif //REMO_FLOW_DEVICETOWEBSTREAMER
