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

#ifdef WEBSTREAMER

#ifndef REMO_FLOW_DEVICETOWEBSTREAM_H
#define REMO_FLOW_DEVICETOWEBSTREAM_H

#include <memory>

#include "flow.h"
#include "streamDeviceIn.h"
#include "streamWebStreamer.h"
#include "mediaWebStreamer.h"

namespace remo
{
  class flowDeviceToWebStream: public flow
  {
    public:
      flowDeviceToWebStream ( stream* inStream_,
                              stream* outStream_);

      virtual ~flowDeviceToWebStream ( ) = default;

      virtual void init ( );
      virtual void processStreams ( );

      void loop ( );

    private:
      void releaseResources ( const std::string& msg_ );

      streamDeviceIn* _inDevice;
      streamWebStreamer* _outWebStreamer;

      bool _stop;
 
      AVPacket* _packet;
      AVFrame* _frame;

      AVFrame* _frameProc;
  };
}
#endif //WEBSTREAMER defined

#endif //REMO_FLOW_DEVICETOWEBSTREAMER
