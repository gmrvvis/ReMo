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

#include <iostream>

#include <FlowDeviceToSDLViewer.h>
#include <MediaDesktop.h>
#include <MediaVideoFile.h>
#include <Gauss.h>
#include <Utils.h>

using namespace std;

int main ( )
{
  remo::Utils::getInstance ( )
    ->getLog ( ) ( remo::LOG_LEVEL::INFO, "Init logging." );

  //Define the input Media and Stream
  std::unique_ptr < remo::Media >
    im = std::unique_ptr < remo::MediaDesktop > ( new remo::MediaDesktop ( ));
  std::unique_ptr < remo::Stream >
    is = std::unique_ptr < remo::StreamDeviceIn > ( new remo::StreamDeviceIn ( im.get ( )));

  //Define the output Media and Stream
  std::unique_ptr < remo::Media > om =
    std::unique_ptr < remo::MediaSDLViewer > ( new remo::MediaSDLViewer ( ));
  std::unique_ptr < remo::Stream >
    os = std::unique_ptr < remo::StreamSDLViewerOut > ( new
      remo::StreamSDLViewerOut ( om.get ( )));

  //Define one Pipeline
  std::unique_ptr < remo::Filter >
    g = std::unique_ptr < remo::Gauss > ( new remo::Gauss ( ));
  remo::FFPipeline pipe ( is.get ( ), os.get ( ));
  pipe.addOperation ( g.get ( ));

  //Define the Flow and process
  remo::FlowDeviceToSDLViewer f ( is.get ( ), os.get ( ));
  f.setPipeline ( &pipe );
  f.processStreams ( );

  remo::Utils::getInstance ( )->getLog ( ) ( remo::LOG_LEVEL::INFO,
                                             "Pipeline test successfully executed." );
  return 0;
}
