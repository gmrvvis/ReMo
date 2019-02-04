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

#ifndef REMO_MEDIA_WEBSTREAMER_H
#define REMO_MEDIA_WEBSTREAMER_H

#include <webstreamer/webstreamer.hpp>
#include <WebstreamerInputProcessor.h>
#include <ImageConverter.h>

#include "FFMedia.h"

namespace remo
{
  class MediaWebStreamer: public FFMedia
  {
    public:
      MediaWebStreamer ( unsigned int image_width_ = 1280, unsigned int image_height_ = 720 );
      virtual ~MediaWebStreamer ( void ) = default;

      virtual void init ( void );

      void pushImage ( ImageConverter* imageConverter_ );

      void changeResolution ( unsigned int new_image_width_, unsigned int new_image_height_ );

      unsigned int getImageWidth ( void ) { return _image_width; };
      unsigned int getImageHeigh ( void ) { return _image_height; };

      webstreamer::WebStreamer & getWebStreamer ( void ) {return _webStreamer;};

      void setInputProcessor ( WebstreamerInputProcessor & WSInputProcessor_ );

    private:

      unsigned int _image_width;
      unsigned int _image_height;

      webstreamer::WebStreamer _webStreamer;
  };
}
#endif //REMO_USE_WEBSTREAMER defined

#endif //REMO_MEDIA_WEBSTREAMER_H
