include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/flow)
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/media)
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/stream)
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/pipeline)
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/util)
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/util/IO)

if ( WEBSTREAMER_DIR )

    file (GLOB_RECURSE ReMo_SDK_src "*.cpp")
    file (GLOB_RECURSE ReMo_SDK__h "*.h")

    ###Compiled with webstreamer requires static
    add_library (ReMo #SHARED
            ${ReMo_SDK_src}
            ${ReMo_SDK_h} )

    target_include_directories(ReMo PUBLIC ${WEBSTREAMER_INCLUDE_DIRS} webstreamer)
    target_link_libraries(ReMo Threads::Threads ${WEBSTREAMER_LIBRARIES} ${SDL_LIBRARY})

else ( WEBSTREAMER_DIR )

    set(REMO_SOURCES  media/media.cpp
                      media/mediaDesktop.cpp
                      media/mediaImage.cpp
                      media/mediaSDLViewer.cpp
                      media/mediaVideoFile.cpp
                      media/mediaWebCam.cpp
                      media/ffMedia.cpp

                      stream/ffStream.cpp
                      stream/stream.cpp
                      stream/streamDeviceIn.cpp
                      stream/streamSDLViewerOut.cpp
                      stream/streamVideoFileOut.cpp

                      flow/flow.cpp
                      flow/flowDeviceToSDLViewer.cpp
                      flow/flowDeviceToVideoFile.cpp

                      pipeline/decoder.cpp
                      pipeline/encoder.cpp
                      pipeline/filter.cpp
                      pipeline/gauss.cpp
                      pipeline/imgProc.cpp
                      pipeline/muxer.cpp
                      pipeline/operation.cpp
                      pipeline/pipeline.cpp
                      pipeline/ffOperation.cpp
                      pipeline/ffPipeline.cpp

                      util/errorManager.cpp
                      util/logger.hpp
                      util/Utils.cpp
    )

    set(REMO_PUBLIC_HEADERS  media/media.h
                             media/ffMedia.h
                             media/mediaDesktop.h
                             media/mediaImage.h
                             media/mediaSDLViewer.h
                             media/mediaVideoFile.h
                             media/mediaWebCam.h

                             stream/ffStream.h
                             stream/streamDeviceIn.h
                             stream/stream.h
                             stream/streamSDLViewerOut.h
                             stream/streamVideoFileOut.h

                             flow/flow.h
                             flow/flowDeviceToSDLViewer.h
                             flow/flowDeviceToVideoFile.h

                             pipeline/decoder.h
                             pipeline/encoder.h
                             pipeline/filter.h
                             pipeline/gauss.h
                             pipeline/imgProc.h
                             pipeline/muxer.h
                             pipeline/operation.h
                             pipeline/pipeline.h
                             pipeline/ffOperation.h
                             pipeline/ffPipeline.h

                             util/errorManager.h
                             util/ffdefs.h
                             util/Utils.h
    )

    set(REMO_NAMESPACE remo)
    set(REMO_INCLUDE_NAMES ReMo )

    set(REMO_LINK_LIBRARIES Threads::Threads
                             ${FFMPEG_LIBRARIES}
                            ${SDL_LIBRARY} )

    add_definitions(-DREMO_SHARED)
    common_library(ReMo)

endif ( WEBSTREAMER_DIR )
