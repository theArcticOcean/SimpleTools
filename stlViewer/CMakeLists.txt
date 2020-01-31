cmake_minimum_required(VERSION 2.8)

project(stlViewer)
find_package( VTK REQUIRED )
include( ${VTK_USE_FILE} )

file( GLOB SourceFiles Source/*.cpp )

file( GLOB HeaderFiles Header/*.h )

set( ResourceFiles Resource/imagea.qrc )

file(GLOB UI_FILES Resource/*.ui)

include_directories(
    ./Header/
    ${CMAKE_BINARY_DIR}
    )

qt5_wrap_ui(UISrcs ${UI_FILES} )
# CMAKE_AUTOMOC in ON so the MOC headers will be automatically wrapped.
set( CMAKE_AUTOMOC ON )

# NOTE: Don't include the path in MACOSX_BUNDLE_ICON_FILE -- this is
# the property added to Info.plist
#     <key>CFBundleIconFile</key>
#     <string>logo</string>
set(MACOSX_BUNDLE_ICON_FILE logo)

# And this part tells CMake where to find and install the file itself
set(myApp_ICON ${CMAKE_CURRENT_SOURCE_DIR}/Images/logo.icns)
# set_source_files_properties would create Resources folder to store icns
# The folder is at same path where Info.plist located
set_source_files_properties(${myApp_ICON} PROPERTIES
     MACOSX_PACKAGE_LOCATION "Resources")

add_executable(
    ${PROJECT_NAME}
    MACOSX_BUNDLE
    ${SourceFiles}
    ${HeaderFiles}
    ${ResourceFiles}
    ${UISrcs}
    ${myApp_ICON}   # Add icon file to see in IDE.
    )

qt5_use_modules(${PROJECT_NAME} Gui)

target_link_libraries(${PROJECT_NAME} ${VTK_LIBRARIES})

message("CMAKE_BINARY_DIR is "${CMAKE_BINARY_DIR})
