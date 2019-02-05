include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/flow)
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/media)
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/stream)
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/pipeline)
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/util)
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/util/IO)

set( REMO_SOURCES   media/Media.cpp
                    media/MediaDesktop.cpp
                    media/MediaImage.cpp
                    media/MediaSDLViewer.cpp
                    media/MediaVideoFile.cpp
                    media/MediaWebCam.cpp
                    media/FFMedia.cpp

                    stream/FFStream.cpp
                    stream/Stream.cpp
                    stream/StreamDeviceIn.cpp
                    stream/StreamSDLViewerOut.cpp
                    stream/StreamVideoFileOut.cpp

                    flow/Flow.cpp
                    flow/FlowDeviceToSDLViewer.cpp
                    flow/FlowDeviceToVideoFile.cpp

                    pipeline/Decoder.cpp
                    pipeline/Encoder.cpp
                    pipeline/Filter.cpp
                    pipeline/Gauss.cpp
                    pipeline/ImgProc.cpp
                    pipeline/Muxer.cpp
                    pipeline/Operation.cpp
                    pipeline/Pipeline.cpp
                    pipeline/FFOperation.cpp
                    pipeline/FFPipeline.cpp
                    pipeline/AbstractImageSampler.cpp
                    pipeline/ImageConverter.cpp

                    util/ErrorManager.cpp
                    util/Logger.hpp
                    util/Utils.cpp
)

set( REMO_PUBLIC_HEADERS    media/Media.h
                            media/FFMedia.h
                            media/MediaDesktop.h
                            media/MediaImage.h
                            media/MediaSDLViewer.h
                            media/MediaVideoFile.h
                            media/MediaWebCam.h

                            stream/FFStream.h
                            stream/StreamDeviceIn.h
                            stream/Stream.h
                            stream/StreamSDLViewerOut.h
                            stream/StreamVideoFileOut.h

                            flow/Flow.h
                            flow/FlowDeviceToSDLViewer.h
                            flow/FlowDeviceToVideoFile.h

                            pipeline/Decoder.h
                            pipeline/Encoder.h
                            pipeline/Filter.h
                            pipeline/Gauss.h
                            pipeline/ImgProc.h
                            pipeline/Muxer.h
                            pipeline/Operation.h
                            pipeline/Pipeline.h
                            pipeline/FFOperation.h
                            pipeline/FFPipeline.h
                            pipeline/AbstractImageSampler.h
                            pipeline/ImageConverter.h

                            util/ErrorManager.h
                            util/ffdefs.h
                            util/Utils.h
        )

set(REMO_NAMESPACE remo)
set(REMO_INCLUDE_NAMES ReMo )

set(REMO_LINK_LIBRARIES Threads::Threads
                        ${FFMPEG_LIBRARIES}
                        ${SDL_LIBRARY} )

if ( WEBSTREAMER_FOUND )

    list( APPEND REMO_PUBLIC_HEADERS    media/MediaWebStreamer.h
                                        flow/FlowDeviceToWebStream.h
                                        stream/StreamWebStreamer.h
                                        util/IO/WebstreamerInputProcessor.h
                                        util/IO/WebstreamerInputProcessor.h
            )
    
    list( APPEND REMO_SOURCES   media/MediaWebStreamer.cpp
                                stream/StreamWebStreamer.cpp
                                flow/FlowDeviceToWebStream.cpp
                                util/IO/WebstreamerInputProcessor.cpp
                                util/IO/WebstreamerInputProcessor.cpp
            )
    
    list( APPEND REMO_LINK_LIBRARIES ${WEBSTREAMER_LIBRARIES} )
    
endif ( )

common_library(ReMo)
