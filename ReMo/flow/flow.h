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

#ifndef REMO_FLOW_H
#define REMO_FLOW_H

#include <memory>

#include "ffPipeline.h"
#include "streamDeviceIn.h"
#include "streamVideoFileOut.h"

namespace remo
{
  class flow
  {
    public:
      flow ( stream* inStream_, stream* outStream_ );
      virtual ~flow ( ) = default;

      virtual void init ( ) = 0;
      virtual void processStreams ( ) = 0;

      std::string getDescription ( );
      void setPipeline ( ffPipeline* ffPipeline_ = nullptr );
      ffPipeline* getPipeline ( ) { return _ffPipeline; };

    protected:

      std::string _description;

      stream* _inStream;
      stream* _outStream;
      
      ffPipeline* _ffPipeline;
  };
}

#endif //REMO_FLOW_H
