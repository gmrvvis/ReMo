
include_directories( ${PROJECT_SOURCE_DIR}
                     ${PROJECT_SOURCE_DIR}/ReMo
                     ${PROJECT_SOURCE_DIR}/ReMo/flow
                     ${PROJECT_SOURCE_DIR}/ReMo/media
                     ${PROJECT_SOURCE_DIR}/ReMo/stream
                     ${PROJECT_SOURCE_DIR}/ReMo/pipeline
                     ${PROJECT_SOURCE_DIR}/ReMo/util
                     ${PROJECT_SOURCE_DIR}/ReMo/util/IO
                     ${CMAKE_CURRENT_SOURCE_DIR}
                     ${PROJECT_BINARY_DIR} )

set( DESKTOP_TO_VIDEO_HEADERS )
set( DESKTOP_TO_VIDEO_SOURCES DesktopToVideo.cpp )
set( DESKTOP_TO_VIDEO_LINK_LIBRARIES ReMo )
common_application( Desktop_To_Video )

set( PIPELINE_TEST_SOURCES PipelineSimpleTest.cpp )
set( PIPELINE_TEST_HEADERS )
set( PIPELINE_TEST_LINK_LIBRARIES ReMo )
common_application( Pipeline_Test )

set( SDL_DESKTOP_VIEWER_HEADERS )
set( SDL_DESKTOP_VIEWER_SOURCES SDLDesktopViewer.cpp )
set( SDL_DESKTOP_VIEWER_LINK_LIBRARIES ReMo )
common_application( SDL_Desktop_Viewer )

set( SDL_WEBCAM_VIEWER_HEADERS )
set( SDL_WEBCAM_VIEWER_SOURCES SDLWebCamViewer.cpp )
set( SDL_WEBCAM_VIEWER_LINK_LIBRARIES ReMo )
common_application( SDL_WebCam_Viewer )

set( WEBCAM_TO_VIDEO_HEADERS )
set( WEBCAM_TO_VIDEO_SOURCES WebCamToVideo.cpp )
set( WEBCAM_TO_VIDEO_LINK_LIBRARIES ReMo )
common_application( WebCam_To_Video )

if ( WEBSTREAMER_FOUND )

    SET ( WEBCAMTOWEBSTREAM_HEADERS )
    SET ( WEBCAMTOWEBSTREAM_SOURCES WebCamToWebStream.cpp )
    SET ( WEBCAMTOWEBSTREAM_LINK_LIBRARIES ReMo ${WEBSTREAMER_LIBRARIES} )
    common_application( WebCamToWebStream )

    SET ( DESKTOPTOWEBSTREAM_HEADERS )
    SET ( DESKTOPTOWEBSTREAM_SOURCES DesktopToWebStream.cpp )
    SET ( DESKTOPTOWEBSTREAM_LINK_LIBRARIES ReMo ${WEBSTREAMER_LIBRARIES} )
    common_application( DesktopToWebStream )

endif ( )
