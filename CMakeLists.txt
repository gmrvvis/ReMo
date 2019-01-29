cmake_minimum_required ( VERSION 3.10 )
project ( ReMo VERSION 0.0.2)
set( ReMo_VERSION_ABI 1 )

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

#TODO: Eliminate -Wno-deprecated-declarations This is needed because the use of some ffmpeg functions and objects.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")

if( "${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}" )
    message( FATAL "no in source building allowed." )
endif( )

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
common_find_package(Poco REQUIRED COMPONENTS Foundation Net Zip JSON Util)

common_find_package( webstreamer SYSTEM )

common_find_package_post( )

add_subdirectory(ReMo)
add_subdirectory(examples)

if ( WEBSTREAMER_FOUND )
    #TODO: Change ${WEBSTREAMER_CMAKE_DIR} when cmake target rule will be incorportaed into webstreamer!
    file(GLOB WS_CLIENT "${WEBSTREAMER_CMAKE_DIR}/../client/*")
    file(COPY ${WS_CLIENT} DESTINATION "${CMAKE_BINARY_DIR}/bin/client")

    file(GLOB WS_CFG "${WEBSTREAMER_CMAKE_DIR}/../webstreamer_config.json")
    file(COPY ${WS_CFG} DESTINATION "${CMAKE_BINARY_DIR}/bin")

endif ( )
    
set(DOCS README.md LICENSE.txt)
install(FILES ${DOCS} DESTINATION share/ReMo COMPONENT dev)

set(DOXYGEN_MAINPAGE_MD README.md)
set(DOXYGEN_EXTRA_INPUT ${PROJECT_SOURCE_DIR}/README.md)
include(DoxygenRule)

include(CPackConfig)
include(CTest)
