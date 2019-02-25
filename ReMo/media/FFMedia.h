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

#ifndef REMO_FFMEDIA_H
#define REMO_FFMEDIA_H

#include <string>

#include "ffdefs.h"
#include "Media.h"

namespace remo
{
  class FFMedia: public Media
  {
    public:
      FFMedia ( void );
      virtual ~FFMedia ( void ) = default;

      virtual void init ( void ) = 0;

      void setOptions ( AVDictionary* options_ ) { _options = options_; }
      void setOption ( const std::string& option_, const std::string& value_ );

      AVDictionary* getOptions ( void ) { return _options; }
      std::string getQualifier ( void ) { return _ffmpegQualifier; }

    protected:
      AVDictionary* _options;
      std::string _ffmpegQualifier;
  };
}
#endif //REMO_FFMEDIA_H
