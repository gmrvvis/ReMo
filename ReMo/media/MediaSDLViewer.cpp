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
#ifdef REMO_USE_SDL

#include "MediaSDLViewer.h"
#include "Utils.h"

namespace remo
{
  MediaSDLViewer::MediaSDLViewer ( void ): FFMedia ( )
  {
    _description = "Desktop Media grabber.";
    _ffmpegQualifier = "none";
    _overlayWidth = 1280;
    _overlayHeigh = 720;
  }

  void MediaSDLViewer::init ( void )
  {
    if ( SDL_Init ( SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER ))
    {
      Utils::getInstance ( )->getErrorManager ( )
                            ->criticalError ( "Could not initialize SDL" );
    }

    SDL_WM_SetCaption ( "Desktop Capture.", nullptr );

    const SDL_VideoInfo* vi = SDL_GetVideoInfo ( );
    unsigned int screen_w, screen_h;

    _rect.x = _rect.y = 0;
    screen_w = vi->current_w;
    screen_h = vi->current_h;

    _surface = SDL_SetVideoMode ( screen_w/2, screen_h/2, 0, 0 );

    if ( !_surface )
    {
      Utils::getInstance ( )->getErrorManager ( )->criticalError (
        "SDL: could not set video mode - exiting." );
    }

    _overlay = SDL_CreateYUVOverlay ( _overlayWidth,
                                      _overlayHeigh,
                                      SDL_YV12_OVERLAY,
                                      _surface );

    _rect.w = vi->current_w;
    _rect.h = vi->current_h;
  }

  void MediaSDLViewer::draw ( AVFrame* frameYUV_ )
  {
    SDL_LockYUVOverlay ( _overlay );

    frameYUV_->data[0] = _overlay->pixels[0];
    frameYUV_->data[1] = _overlay->pixels[2];
    frameYUV_->data[2] = _overlay->pixels[1];

    frameYUV_->linesize[0] = _overlay->pitches[0];
    frameYUV_->linesize[1] = _overlay->pitches[2];
    frameYUV_->linesize[2] = _overlay->pitches[1];

    SDL_UnlockYUVOverlay ( _overlay );
    SDL_DisplayYUVOverlay ( _overlay, &_rect );
  }
}

#endif //REMO_USE_SDL
