cmake_minimum_required(VERSION 2.8)

project(3DFilesConverter)

find_package( VTK REQUIRED )
include( ${VTK_USE_FILE} )

find_package(Qt5 COMPONENTS Core REQUIRED QUIET )

set(OpenCTMDir thirdparty/OpenCTMLib)
#set(ZLIBDir thirdparty/zlib_1_2_11)



include_directories(
    ${OpenCTMDir}
#    ${ZLIBDir}
#    ${ZLIBDir}/make/include
#    ${ZLIBDir}/contrib/minizip
    )

link_directories(
    ${OpenCTMDir}
    ${ZLIBDir}
    ${ZLIBDir}/make/${CMAKE_BUILD_TYPE}
    )

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
    "vtkIO.h"
    "vtkIO.cpp"
    "filesManager.h"
    "filesManager.cpp"
    "facetIO.h"
    "facetIO.cpp"
    "point.hpp"
    "ctmIO.h"
    "ctmIO.cpp"
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

qt5_use_modules( ${PROJECT_NAME} Core )

#set_property(TARGET zlib PROPERTY IMPORTED_LOCATION_RELEASE ${ZLibBuildPath}/lib/zlib.lib)
#set_property(TARGET zlib PROPERTY IMPORTED_LOCATION_DEBUG   ${ZLibBuildPath}/lib/zlibd.lib)

target_link_libraries( ${PROJECT_NAME} ${VTK_LIBRARIES} openctm )

#add_library(zlib STATIC IMPORTED)

