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

if ( WEBSTREAMER_DIR )

    SET ( ReMo_DesktopToVideo_src DesktopToVideo.cpp )
    ADD_EXECUTABLE( Desktop_To_Video ${ReMo_DesktopToVideo_src} )
    target_link_libraries ( Desktop_To_Video  ReMo
                                              ${WEBSTREAMER_LIBRARIES}
                                              )

    SET ( ReMo_PipelineTest_src PipelineSimpleTest.cpp )
    ADD_EXECUTABLE( Pipeline_Test ${ReMo_PipelineTest_src} )
    target_link_libraries ( Pipeline_Test   ReMo
                                            ${WEBSTREAMER_LIBRARIES}
                                            ${SDL_LIBRARY} 
                                            )

    SET ( ReMo_SDLDesktopViewer_src SDLDesktopViewer.cpp )
    ADD_EXECUTABLE( SDL_Desktop_Viewer ${ReMo_SDLDesktopViewer_src} )
    target_link_libraries ( SDL_Desktop_Viewer  ReMo
                                                Threads::Threads
                                                ${WEBSTREAMER_LIBRARIES}
                                                ${SDL_LIBRARY} 
                                                )

    SET ( ReMo_SDLWebCamViewer_src SDLWebCamViewer.cpp )
    ADD_EXECUTABLE( SDL_WebCam_Viewer ${ReMo_SDLWebCamViewer_src} )
    target_link_libraries ( SDL_WebCam_Viewer ReMo
                                              ${WEBSTREAMER_LIBRARIES}
                                              ${SDL_LIBRARY} 
                                              )

    SET ( ReMo_WebCamToVideo_src WebCamToVideo.cpp )
    ADD_EXECUTABLE( WebCam_To_Video ${ReMo_WebCamToVideo_src} )
    target_link_libraries ( WebCam_To_Video ReMo
                                            ${WEBSTREAMER_LIBRARIES}
                                            )

    SET ( ReMo_DesktopToWebStream_src DesktopToWebStream.cpp )
    ADD_EXECUTABLE( Desktop_To_WebStream ${ReMo_DesktopToWebStream_src} )
    target_link_libraries ( Desktop_To_WebStream ReMo
                                                 ${WEBSTREAMER_LIBRARIES}
                                                 )

    SET ( ReMo_WebCamToWebStream_src WebCamToWebStream.cpp )
    ADD_EXECUTABLE( WebCam_To_WebStream ${ReMo_WebCamToWebStream_src} )
    target_link_libraries ( WebCam_To_WebStream ReMo
                                                ${WEBSTREAMER_LIBRARIES}
                                                )

     set_target_properties( Desktop_To_Video Pipeline_Test SDL_Desktop_Viewer
                            SDL_WebCam_Viewer WebCam_To_Video Desktop_To_WebStream
                            WebCam_To_WebStream
                            PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

else ( WEBSTREAMER_DIR )

    set( DESKTOP_TO_VIDEO_HEADERS )
    set( DESKTOP_TO_VIDEO_SOURCES DesktopToVideo.cpp )
    set( DESKTOP_TO_VIDEO_LINK_LIBRARIES ReMo ${SDL_LIBRARY} )
    common_application( Desktop_To_Video )

    set( PIPELINE_TEST_SOURCES PipelineSimpleTest.cpp )
    set( PIPELINE_TEST_HEADERS )
    set( PIPELINE_TEST_LINK_LIBRARIES ReMo )
    common_application( Pipeline_Test )

    set( SDL_DESKTOP_VIEWER_HEADERS )
    set( SDL_DESKTOP_VIEWER_SOURCES SDLDesktopViewer.cpp )
    set( SDL_DESKTOP_VIEWER_LINK_LIBRARIES ReMo )
    common_application( SDL_Desktop_Viewer ${SDL_LIBRARY} )

    set( SDL_WEBCAM_VIEWER_HEADERS )
    set( SDL_WEBCAM_VIEWER_SOURCES SDLWebCamViewer.cpp )
    set( SDL_WEBCAM_VIEWER_LINK_LIBRARIES ReMo )
    common_application( SDL_WebCam_Viewer ${SDL_LIBRARY} )

    set( WEBCAM_TO_VIDEO_HEADERS )
    set( WEBCAM_TO_VIDEO_SOURCES WebCamToVideo.cpp )
    set( WEBCAM_TO_VIDEO_LINK_LIBRARIES ReMo )
    common_application( WebCam_To_Video )

endif ( WEBSTREAMER_DIR )
