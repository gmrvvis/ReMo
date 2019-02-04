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

#ifndef REMO_MEDIA_IMAGEFILE_H
#define REMO_MEDIA_IMAGEFILE_H

#include "FFMedia.h"

namespace remo
{
  class MediaImage: public Media
  {
    public:
      MediaImage ( std::string imageName_ = "image.png" );
      virtual ~MediaImage ( void ) = default;

      virtual void init ( void );

      std::string getImageName ( void ) { return _imageName; }

    protected:
      std::string _imageName;
  };
}
#endif //REMO_MEDIA_IMAGEFILE_H
