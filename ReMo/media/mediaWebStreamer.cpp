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

#include "mediaWebStreamer.h"
#include "Utils.h"

namespace remo
{
  mediaWebStreamer::mediaWebStreamer (  unsigned int image_width_, unsigned int image_height_ )
  : ffMedia ( ), _image_width ( image_width_ ), _image_height ( image_height_ )
    {
    _description = "WebStreamer media sender.";
    _ffmpegQualifier = "none";
  }

  void mediaWebStreamer::init ( ) {}

  void mediaWebStreamer::setInputProcessor ( webstreamerInputProcessor & WSInputProcessor_ )
  {
    _webStreamer.RegisterInputProcessor ( &WSInputProcessor_ );
  }

  void mediaWebStreamer::changeResolution ( unsigned int new_image_width_, unsigned int new_image_heigh_ )
  {
    _image_width = new_image_width_,
    _image_height = new_image_heigh_;
  }

  void mediaWebStreamer::pushImage ( ImageConverter* imageConverter_ )
  {
    _webStreamer.PushFrame( _image_width,
                            _image_height,
                            imageConverter_->getImage().data( ),
                            imageConverter_->getImage().size( ) );
  }
}
#endif //REMO_USE_WEBSTREAMER
