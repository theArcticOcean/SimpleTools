cmake_minimum_required(VERSION 3.16)

project(3DFilesConverter)

find_package( VTK REQUIRED )
include( ${VTK_USE_FILE} )

add_executable(${PROJECT_NAME}
    "main.cpp"
    "ULog.h"
    "IOBase.h"
    "IOBase.cpp"
    "stlIO.h"
    "stlIO.cpp"
    "objIO.h"
    "objIO.cpp"
    )

target_link_libraries( ${PROJECT_NAME} ${VTK_LIBRARIES} )
