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

#include "Flow.h"
#include "../util/Utils.h"

namespace remo
{
  Flow::Flow ( Stream* inStream_, Stream* outStream_ ):
    _description ( "Base Flow" ),
    _inStream ( inStream_ ),
    _outStream ( outStream_ ),
    _ffPipeline ( nullptr ) {}

  std::string Flow::getDescription ( void )
  {
    return _description;
  }

  void Flow::setPipeline ( FFPipeline* stdPipeline_ )
  {
    if ( stdPipeline_ == nullptr )
    {
      Utils::getInstance ( )
        ->getLog ( ) ( remo::LOG_LEVEL::INFO, "Pipeline not connected." );
    }
    else
    {
      _ffPipeline = stdPipeline_;
    }
  }

  void Flow::finish ( void )
  {
    
  }
}
