cmake_minimum_required ( VERSION 3.10 )
project ( ReMo VERSION 0.0.1)
set( ReMo_VERSION_ABI 1 )

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

#-Wno-deprecated-declarations: This is needed because the use of some ffmpeg functions and objects.
#It will be removed in the next versions.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wno-deprecated-declarations")

if( "${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}" )
    message( FATAL "no in source building allowed." )
endif( )

#set WebStreamer build dir.
if ( WEBSTREAMER_DIR )

    list( APPEND CMAKE_MODULE_PATH
     ${PROJECT_SOURCE_DIR}/CMake )
     
    set (CMAKE_PREFIX_PATH "${WEBSTREAMER_DIR}" ${CMAKE_PREFIX_PATH})

    find_package( webstreamer REQUIRED )
    find_package( SDL REQUIRED )
    find_package( FFmpeg REQUIRED )
    find_package( Poco REQUIRED COMPONENTS Foundation Net Zip JSON Util )

    link_directories ( ${WEBSTREAMER_LIB_DIRS} )

    #add_compile_definitions ( WEBSTREAMER )
    add_definitions ( -DWEBSTREAMER )

else ( WEBSTREAMER_DIR )

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC ")

    if( NOT EXISTS ${CMAKE_SOURCE_DIR}/CMake/common/Common.cmake )
        message( FATAL_ERROR "CMake/common missing, run: git submodule update --init")
    endif( )

    list( APPEND CMAKE_MODULE_PATH
     ${PROJECT_SOURCE_DIR}/CMake
     ${CMAKE_SOURCE_DIR}/CMake/common )

    include( GitExternal )

    set( REMO_DESCRIPTION "ReMo: RenderMovie is a video syntesis framework for different tasks." )
    set( REMO_LICENSE LGPL )
    set( COMMON_PROJECT_DOMAIN es.gmrv )

    include( Common )

    common_find_package(OpenGL SYSTEM REQUIRED)
    common_find_package(GLUT SYSTEM REQUIRED)
    common_find_package(GLEW SYSTEM REQUIRED)
    common_find_package(Threads SYSTEM REQUIRED)

    common_find_package(SDL SYSTEM REQUIRED)
    common_find_package(FFmpeg REQUIRED)

    common_find_package_post( )

endif ( WEBSTREAMER_DIR )

add_subdirectory(ReMo)
add_subdirectory(examples)

if ( WEBSTREAMER_DIR )

    #WebStreamer content copy
    file(GLOB WS_CLIENT "${WEBSTREAMER_DIR}/../client/*")
    file(COPY ${WS_CLIENT} DESTINATION "${CMAKE_BINARY_DIR}/bin/client")

    file(GLOB WS_CFG "${WEBSTREAMER_DIR}/../webstreamer_config.json")
    file(COPY ${WS_CFG} DESTINATION "${CMAKE_BINARY_DIR}/bin")

else( WEBSTREAMER_DIR )

    set(DOCS README.md LICENSE.txt)
    install(FILES ${DOCS} DESTINATION share/ReMo COMPONENT dev)

    set(DOXYGEN_MAINPAGE_MD README.md)
    set(DOXYGEN_EXTRA_INPUT ${PROJECT_SOURCE_DIR}/README.md)
    include(DoxygenRule)

    include(CPackConfig)
    include(CTest)

endif ( WEBSTREAMER_DIR )
