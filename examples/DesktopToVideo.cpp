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

#include <flow/flowDeviceToVideoFile.h>
#include <media/mediaDesktop.h>
#include <media/mediaVideoFile.h>
#include <util/Utils.h>

using namespace std;

int main ( )
{
  remo::Utils::getInstance ( )
    ->getLog ( ) ( remo::LOG_LEVEL::INFO, "Init logging." );

  //Define the input media and stream
  std::unique_ptr < remo::media > im =
          std::unique_ptr < remo::mediaDesktop > ( new remo::mediaDesktop ( 1024, //1680
                                                                            768 )); //1050
  std::unique_ptr < remo::stream >
    is = std::unique_ptr < remo::streamDeviceIn > ( new remo::streamDeviceIn ( im.get ( )));

  //Define the output media and stream
  std::unique_ptr < remo::media > om =
    std::unique_ptr < remo::mediaVideoFile > ( new remo::mediaVideoFile ( ));
  std::unique_ptr < remo::stream >
    os = std::unique_ptr < remo::streamVideoFileOut > ( new
      remo::streamVideoFileOut ( om.get ( )));

  //Define the flow and process
  remo::flowDeviceToVideoFile f ( is.get ( ), os.get ( ));

  f.processStreams ( );

  remo::Utils::getInstance ( )->getLog ( ) ( remo::LOG_LEVEL::INFO,
                                             "Desktop to video successfully executed." );
  return 0;
}
