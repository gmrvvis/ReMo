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

#include <flowDeviceToSDLViewer.h>
#include <mediaDesktop.h>
#include <mediaVideoFile.h>
#include <gauss.h>
#include <Utils.h>

using namespace std;

int main ( )
{
  remo::Utils::getInstance ( )
    ->getLog ( ) ( remo::LOG_LEVEL::INFO, "Init logging." );

  //Define the input media and stream
  std::unique_ptr < remo::media >
    im = std::unique_ptr < remo::mediaDesktop > ( new remo::mediaDesktop ( ));
  std::unique_ptr < remo::stream >
    is = std::unique_ptr < remo::streamDeviceIn > ( new remo::streamDeviceIn ( im.get ( )));

  //Define the output media and stream
  std::unique_ptr < remo::media > om =
    std::unique_ptr < remo::mediaSDLViewer > ( new remo::mediaSDLViewer ( ));
  std::unique_ptr < remo::stream >
    os = std::unique_ptr < remo::streamSDLViewerOut > ( new
      remo::streamSDLViewerOut ( om.get ( )));

  //Define one pipeline
  std::unique_ptr < remo::filter >
    g = std::unique_ptr < remo::gauss > ( new remo::gauss ( ));
  remo::ffPipeline pipe ( is.get ( ), os.get ( ));
  pipe.addOperation ( g.get ( ));

  //Define the flow and process
  remo::flowDeviceToSDLViewer f ( is.get ( ), os.get ( ));
  f.setPipeline ( &pipe );
  f.processStreams ( );

  remo::Utils::getInstance ( )->getLog ( ) ( remo::LOG_LEVEL::INFO,
                                             "Pipeline test successfully executed." );
  return 0;
}
