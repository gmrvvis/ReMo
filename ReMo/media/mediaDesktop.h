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

#ifndef REMO_MEDIA_DESKTOP_H
#define REMO_MEDIA_DESKTOP_H

#include "ffMedia.h"

namespace remo
{
  //This object needs libxcb installed on your system!!!
  class mediaDesktop: public ffMedia
  {
    public:
      mediaDesktop ( unsigned int desktop_width_ = 1280,
                     unsigned int desktop_heigh_ = 720 );

      virtual ~mediaDesktop ( ) = default;

      virtual void init ( );

      std::string getDesktopSizeAsString ( ) { return _desktopSizeAsString; }
      void setDesktopSizeAsString ( const std::string& desktopSize_ )
      {
        _desktopSizeAsString = desktopSize_;
      }

      void setDesktopConfigAsString ( const std::string& desktopConfig_ )
      {
        _desktopConfigAsString = desktopConfig_;
      }
      std::string getDesktopConfigAsString ( ) { return _desktopConfigAsString; }

      void setDesktopSize ( unsigned int desktop_width_ = 1280,
                            unsigned int desktop_heigh_ = 720 );

    private:
      unsigned int _desktop_width;
      unsigned int _desktop_heigh;

      std::string _desktopSizeAsString;
      std::string _desktopConfigAsString;
  };
}
#endif //REMO_MEDIA_DESKTOP_H
