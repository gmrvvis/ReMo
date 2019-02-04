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

#include "FFMedia.h"

namespace remo
{
  FFMedia::FFMedia ( void ): Media ( )
  {
    _description = "Basic ffmpeg/libAV video Media";
    _ffmpegQualifier = "None";
  }

  void FFMedia::setOption ( std::string option_, std::string value_ )
  {
    av_dict_set ( &_options, option_.c_str ( ), value_.c_str ( ), 0 );
  }
}
