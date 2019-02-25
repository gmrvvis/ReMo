
include_directories( ${PROJECT_SOURCE_DIR}
                     ${CMAKE_CURRENT_SOURCE_DIR}
                     ${PROJECT_BINARY_DIR} )

set( DESKTOPTOVIDEO_HEADERS )
set( DESKTOPTOVIDEO_SOURCES DesktopToVideo.cpp )
set( DESKTOPTOVIDEO_LINK_LIBRARIES ReMo )
common_application( desktopToVideo )

set( WEBCAMTOVIDEO_HEADERS )
set( WEBCAMTOVIDEO_SOURCES WebCamToVideo.cpp )
set( WEBCAMTOVIDEO_LINK_LIBRARIES ReMo )
common_application( webCamToVideo )


if ( SDL_FOUND )
  set( PIPELINETEST_SOURCES PipelineSimpleTest.cpp )
  set( PIPELINETEST_HEADERS )
  set( PIPELINETEST_LINK_LIBRARIES ReMo )
  common_application( pipelineTest )

  set( SDLDESKTOPVIEWER_HEADERS )
  set( SDLDESKTOPVIEWER_SOURCES SDLDesktopViewer.cpp )
  set( SDLDESKTOPVIEWER_LINK_LIBRARIES ReMo )
  common_application( SDLDesktopViewer )

  set( SDLWEBCAMVIEWER_HEADERS )
  set( SDLWEBCAMVIEWER_SOURCES SDLWebCamViewer.cpp )
  set( SDLWEBCAMVIEWER_LINK_LIBRARIES ReMo )
  common_application( SDLWebCamViewer )

endif ( )

if ( WEBSTREAMER_FOUND )

    set ( WEBCAMTOWEBSTREAM_HEADERS )
    set ( WEBCAMTOWEBSTREAM_SOURCES WebCamToWebStream.cpp )
    set ( WEBCAMTOWEBSTREAM_LINK_LIBRARIES ReMo ${WEBSTREAMER_LIBRARIES} )
    common_application( webCamToWebStream )

    set ( DESKTOPTOWEBSTREAM_HEADERS )
    set ( DESKTOPTOWEBSTREAM_SOURCES DesktopToWebStream.cpp )
    set ( DESKTOPTOWEBSTREAM_LINK_LIBRARIES ReMo ${WEBSTREAMER_LIBRARIES} )
    common_application( desktopToWebStream )

endif ( )
