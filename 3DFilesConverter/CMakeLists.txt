cmake_minimum_required(VERSION 3.11)

project(3DFilesConverter)

find_package( VTK REQUIRED )
include( ${VTK_USE_FILE} )

set( OPENCTM_LIB_DIR "../OpenCTM-1.0.3/lib" )
include_directories( ${OPENCTM_LIB_DIR} )
link_directories( ${OPENCTM_LIB_DIR} )

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
    "zipManager.h"
    "zipManager.cpp"
    "facetIO.h"
    "facetIO.cpp"
    "point.hpp"
    "ctmIO.h"
    "ctmIO.cpp"
    )

target_link_libraries( ${PROJECT_NAME} ${VTK_LIBRARIES} openctm )
