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

#ifndef REMO_STREAM_VIDEOFILEOUT_H
#define REMO_STREAM_VIDEOFILEOUT_H

#include "ffStream.h"

namespace remo
{
  class streamVideoFileOut: public ffStream
  {
    public:
      streamVideoFileOut ( media* outMedia_ );
      virtual ~streamVideoFileOut ( ) = default;

      virtual void init ( );

      std::string getDescription ( );
      AVStream* getVideoStream ( ) { return _videoStream; }

    private:

      AVOutputFormat* _outputFormat;
      AVStream* _videoStream;
      AVDictionary* _options;
  };
}
#endif //REMO_STREAM_VIDEOFILEOUT_H
