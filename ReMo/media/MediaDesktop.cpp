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

#include "MediaDesktop.h"

namespace remo
{
  MediaDesktop::MediaDesktop ( unsigned int desktop_width_,
                               unsigned int desktop_heigh_ ): FFMedia ( )
  {
    _description = "Desktop Media grabber.";
    _options = nullptr;

#ifdef _WIN32
    _ffmpegQualifier = "ddshow";
    _desktopConfigAsString="video=screen-capture-recorder";
#elif __APPLE__
    _ffmpegQualifier = "avfoundation";
    _desktopConfigAsString="1";
#else //X Systems
    _ffmpegQualifier = "x11grab";
    _desktopConfigAsString = ":0.0";
#endif

    setDesktopSize ( desktop_width_, desktop_heigh_ );
  }

  void MediaDesktop::setDesktopSize ( unsigned int desktop_width_,
                                      unsigned int desktop_heigh_ )
  {
    _desktop_width = desktop_width_;
    _desktop_heigh = desktop_heigh_;
    _desktopSizeAsString = std::to_string ( _desktop_width ) + "x"
      + std::to_string ( _desktop_heigh );
  }

  void MediaDesktop::init ( void )
  {
    av_dict_set ( &_options, "video_size", _desktopSizeAsString.c_str ( ), 0 );
  }
}
