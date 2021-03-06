cmake_minimum_required(VERSION 3.11)

project(3DFilesConverter)

find_package( VTK REQUIRED )
include( ${VTK_USE_FILE} )

set( USER_INCLUDE_DIR "/usr/local/include" )
set( USER_LIB_DIR "/usr/local/lib" )
include_directories( ${OPENCTM_LIB_DIR} )
include_directories( ${USER_INCLUDE_DIR} )
link_directories( ${OPENCTM_LIB_DIR} )
link_directories( ${USER_LIB_DIR} )

add_executable(${PROJECT_NAME}
    "main.cpp"
    "ULog.h"
    "IOBase.h"
    "IOBase.cpp"
    "stlIO.h"
    "stlIO.cpp"
    "objIO.h"
    "objIO.cpp"
    "plyIO.h"
    "plyIO.cpp"
    "vtpIO.h"
    "vtpIO.cpp"
    "gltfIO.h"
    "gltfIO.cpp"
    "vtkIO.h"
    "vtkIO.cpp"
    "filesManager.h"
    "filesManager.cpp"
    "facetIO.h"
    "facetIO.cpp"
    "point.hpp"
    "ctmIO.h"
    "ctmIO.cpp"
    "byuIO.h"
    "byuIO.cpp"
    "demIO.h"
    "demIO.cpp"
    "tiffIO.h"
    "tiffIO.cpp"
    "3DSIO.h"
    "3DSIO.cpp"
    "x3dIO.h"
    "x3dIO.cpp"
    "wrlIO.h"
    "wrlIO.cpp"
    )

target_link_libraries( ${PROJECT_NAME} ${VTK_LIBRARIES} openctm Zipper)
