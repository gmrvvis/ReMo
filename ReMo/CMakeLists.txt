#include_directories( ${PROJECT_SOURCE_DIR}/ReMo/flow)
#include_directories( ${PROJECT_SOURCE_DIR}/ReMo/media)
#include_directories( ${PROJECT_SOURCE_DIR}/ReMo/stream)
#include_directories( ${PROJECT_SOURCE_DIR}/ReMo/pipeline)
#include_directories( ${PROJECT_SOURCE_DIR}/ReMo/util)
#include_directories( ${PROJECT_SOURCE_DIR}/ReMo/util/IO)

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
                    util/Config.cpp )

set( REMO_PUBLIC_HEADERS    media/Media.h
                            media/FFMedia.h
                            media/MediaDesktop.h
                            media/MediaImage.h
                            media/MediaVideoFile.h
                            media/MediaWebCam.h

                            stream/FFStream.h
                            stream/StreamDeviceIn.h
                            stream/Stream.h
                            stream/StreamVideoFileOut.h

                            flow/Flow.h
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
                            util/Config.h )

set( REMO_NAMESPACE remo )
set( REMO_INCLUDE_NAMES ReMo )

set( REMO_LINK_LIBRARIES Threads::Threads
                        ${FFMPEG_LIBRARIES} )

if ( SDL_FOUND )
    list( APPEND REMO_PUBLIC_HEADERS    media/MediaSDLViewer.h
                                        stream/StreamSDLViewerOut.h
                                        flow/FlowDeviceToSDLViewer.h )

    list( APPEND REMO_SOURCES   media/MediaSDLViewer.cpp
                                stream/StreamSDLViewerOut.cpp
                                flow/FlowDeviceToSDLViewer.cpp )
    
    list( APPEND REMO_LINK_LIBRARIES ${SDL_LIBRARY} )
endif ( )

if ( Poco_FOUND )
    list( APPEND REMO_PUBLIC_HEADERS    util/net/ByteBuffer.h
                                        util/net/Client.h
                                        util/net/Connection.h
                                        util/net/Packet.h
                                        util/net/PacketHandler.h
                                        util/net/Runnable.h
                                        util/net/SelectorThread.h
                                        util/net/Server.h
                                        util/net/ThreadPool.h )

    list( APPEND REMO_SOURCES   util/net/ByteBuffer.cpp
                                util/net/Client.cpp
                                util/net/Connection.cpp
                                util/net/Packet.cpp
                                util/net/PacketHandler.cpp
                                util/net/SelectorThread.cpp
                                util/net/Server.cpp )

    list( APPEND REMO_LINK_LIBRARIES ${Poco_LIBRARIES} )
endif ( )


if ( WEBSTREAMER_FOUND )
    list( APPEND REMO_PUBLIC_HEADERS    media/MediaWebStreamer.h
                                        flow/FlowDeviceToWebStream.h
                                        stream/StreamWebStreamer.h
                                        util/IO/WebstreamerInputProcessor.h
                                        util/IO/WebstreamerInputProcessor.h )
    
    list( APPEND REMO_SOURCES   media/MediaWebStreamer.cpp
                                stream/StreamWebStreamer.cpp
                                flow/FlowDeviceToWebStream.cpp
                                util/IO/WebstreamerInputProcessor.cpp
                                util/IO/WebstreamerInputProcessor.cpp )
    
    list( APPEND REMO_LINK_LIBRARIES ${WEBSTREAMER_LIBRARIES} )
endif ( )

common_library( ReMo )
