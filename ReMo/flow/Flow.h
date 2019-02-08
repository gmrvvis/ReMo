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

#include "FFPipeline.h"
#include "StreamDeviceIn.h"
#include "StreamVideoFileOut.h"

namespace remo
{
  class Flow
  {
    public:
      Flow ( Stream* inStream_, Stream* outStream_ );
      virtual ~Flow ( void ) = default;

      virtual void init ( void ) = 0;
      virtual void processStreams ( void ) = 0;
      virtual void finish ( void );

      std::string getDescription ( void );
      void setPipeline ( FFPipeline* ffPipeline_ = nullptr );
      FFPipeline* getPipeline ( ) { return _ffPipeline; };

    protected:

      std::string _description;

      Stream* _inStream;
      Stream* _outStream;
      
      FFPipeline* _ffPipeline;
  };
}

#endif //REMO_FLOW_H
