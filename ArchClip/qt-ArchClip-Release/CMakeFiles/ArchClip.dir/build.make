# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.10.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.10.0/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/weiyang/pro/ArchClip

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/weiyang/pro/ArchClip/qt-ArchClip-Release

# Include any dependencies generated for this target.
include CMakeFiles/ArchClip.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ArchClip.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ArchClip.dir/flags.make

ui_widget.h: ../widget.ui
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/weiyang/pro/ArchClip/qt-ArchClip-Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating ui_widget.h"
	/Users/weiyang/Downloads/Qt5.11.2/5.11.2/clang_64/bin/uic -o /Users/weiyang/pro/ArchClip/qt-ArchClip-Release/ui_widget.h /Users/weiyang/pro/ArchClip/widget.ui

CMakeFiles/ArchClip.dir/main.o: CMakeFiles/ArchClip.dir/flags.make
CMakeFiles/ArchClip.dir/main.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/weiyang/pro/ArchClip/qt-ArchClip-Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ArchClip.dir/main.o"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ArchClip.dir/main.o -c /Users/weiyang/pro/ArchClip/main.cpp

CMakeFiles/ArchClip.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ArchClip.dir/main.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/weiyang/pro/ArchClip/main.cpp > CMakeFiles/ArchClip.dir/main.i

CMakeFiles/ArchClip.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ArchClip.dir/main.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/weiyang/pro/ArchClip/main.cpp -o CMakeFiles/ArchClip.dir/main.s

CMakeFiles/ArchClip.dir/main.o.requires:

.PHONY : CMakeFiles/ArchClip.dir/main.o.requires

CMakeFiles/ArchClip.dir/main.o.provides: CMakeFiles/ArchClip.dir/main.o.requires
	$(MAKE) -f CMakeFiles/ArchClip.dir/build.make CMakeFiles/ArchClip.dir/main.o.provides.build
.PHONY : CMakeFiles/ArchClip.dir/main.o.provides

CMakeFiles/ArchClip.dir/main.o.provides.build: CMakeFiles/ArchClip.dir/main.o


CMakeFiles/ArchClip.dir/widget.o: CMakeFiles/ArchClip.dir/flags.make
CMakeFiles/ArchClip.dir/widget.o: ../widget.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/weiyang/pro/ArchClip/qt-ArchClip-Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ArchClip.dir/widget.o"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ArchClip.dir/widget.o -c /Users/weiyang/pro/ArchClip/widget.cpp

CMakeFiles/ArchClip.dir/widget.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ArchClip.dir/widget.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/weiyang/pro/ArchClip/widget.cpp > CMakeFiles/ArchClip.dir/widget.i

CMakeFiles/ArchClip.dir/widget.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ArchClip.dir/widget.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/weiyang/pro/ArchClip/widget.cpp -o CMakeFiles/ArchClip.dir/widget.s

CMakeFiles/ArchClip.dir/widget.o.requires:

.PHONY : CMakeFiles/ArchClip.dir/widget.o.requires

CMakeFiles/ArchClip.dir/widget.o.provides: CMakeFiles/ArchClip.dir/widget.o.requires
	$(MAKE) -f CMakeFiles/ArchClip.dir/build.make CMakeFiles/ArchClip.dir/widget.o.provides.build
.PHONY : CMakeFiles/ArchClip.dir/widget.o.provides

CMakeFiles/ArchClip.dir/widget.o.provides.build: CMakeFiles/ArchClip.dir/widget.o


CMakeFiles/ArchClip.dir/ArchClip_autogen/mocs_compilation.o: CMakeFiles/ArchClip.dir/flags.make
CMakeFiles/ArchClip.dir/ArchClip_autogen/mocs_compilation.o: ArchClip_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/weiyang/pro/ArchClip/qt-ArchClip-Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ArchClip.dir/ArchClip_autogen/mocs_compilation.o"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ArchClip.dir/ArchClip_autogen/mocs_compilation.o -c /Users/weiyang/pro/ArchClip/qt-ArchClip-Release/ArchClip_autogen/mocs_compilation.cpp

CMakeFiles/ArchClip.dir/ArchClip_autogen/mocs_compilation.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ArchClip.dir/ArchClip_autogen/mocs_compilation.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/weiyang/pro/ArchClip/qt-ArchClip-Release/ArchClip_autogen/mocs_compilation.cpp > CMakeFiles/ArchClip.dir/ArchClip_autogen/mocs_compilation.i

CMakeFiles/ArchClip.dir/ArchClip_autogen/mocs_compilation.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ArchClip.dir/ArchClip_autogen/mocs_compilation.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/weiyang/pro/ArchClip/qt-ArchClip-Release/ArchClip_autogen/mocs_compilation.cpp -o CMakeFiles/ArchClip.dir/ArchClip_autogen/mocs_compilation.s

CMakeFiles/ArchClip.dir/ArchClip_autogen/mocs_compilation.o.requires:

.PHONY : CMakeFiles/ArchClip.dir/ArchClip_autogen/mocs_compilation.o.requires

CMakeFiles/ArchClip.dir/ArchClip_autogen/mocs_compilation.o.provides: CMakeFiles/ArchClip.dir/ArchClip_autogen/mocs_compilation.o.requires
	$(MAKE) -f CMakeFiles/ArchClip.dir/build.make CMakeFiles/ArchClip.dir/ArchClip_autogen/mocs_compilation.o.provides.build
.PHONY : CMakeFiles/ArchClip.dir/ArchClip_autogen/mocs_compilation.o.provides

CMakeFiles/ArchClip.dir/ArchClip_autogen/mocs_compilation.o.provides.build: CMakeFiles/ArchClip.dir/ArchClip_autogen/mocs_compilation.o


# Object files for target ArchClip
ArchClip_OBJECTS = \
"CMakeFiles/ArchClip.dir/main.o" \
"CMakeFiles/ArchClip.dir/widget.o" \
"CMakeFiles/ArchClip.dir/ArchClip_autogen/mocs_compilation.o"

# External object files for target ArchClip
ArchClip_EXTERNAL_OBJECTS =

ArchClip.app/Contents/MacOS/ArchClip: CMakeFiles/ArchClip.dir/main.o
ArchClip.app/Contents/MacOS/ArchClip: CMakeFiles/ArchClip.dir/widget.o
ArchClip.app/Contents/MacOS/ArchClip: CMakeFiles/ArchClip.dir/ArchClip_autogen/mocs_compilation.o
ArchClip.app/Contents/MacOS/ArchClip: CMakeFiles/ArchClip.dir/build.make
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkIOInfovis-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkRenderingContextOpenGL2-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkTestingRendering-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkViewsContext2D-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkFiltersGeneric-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkTestingGenericBridge-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkDomainsChemistryOpenGL2-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkIOAMR-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkIOExodus-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkRenderingVolumeOpenGL2-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkFiltersFlowPaths-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkFiltersHyperTree-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkImagingStencil-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkFiltersParallelImaging-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkFiltersPoints-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkFiltersProgrammable-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/lib/libpython2.7.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkWrappingTools-8.1.a
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkFiltersPython-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkFiltersSMP-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkFiltersSelection-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkFiltersVerdict-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkIOParallel-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkFiltersTopology-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkGUISupportQtOpenGL-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkGUISupportQtSQL-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkGeovisCore-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkIOEnSight-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkIOExportOpenGL2-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkInteractionImage-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkIOImport-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkIOLSDyna-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkIOMINC-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkIOMovie-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkIOPLY-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkIOParallelXML-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkTestingIOSQL-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkIOTecplotTable-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkIOVideo-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkImagingStatistics-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkRenderingImage-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkImagingMorphological-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkRenderingLOD-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkRenderingQt-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkViewsQt-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtklibxml2-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkDomainsChemistry-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkFiltersAMR-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkImagingMath-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkWrappingPython27Core-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkverdict-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkIOGeometry-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkexoIIc-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkFiltersParallel-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkIONetCDF-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtknetcdfcpp-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkjsoncpp-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkIOSQL-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtksqlite-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /Users/weiyang/Downloads/Qt5.11.2/5.11.2/clang_64/lib/QtSql.framework/QtSql
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkproj4-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkIOExport-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkRenderingGL2PSOpenGL2-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkgl2ps-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtklibharu-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkNetCDF-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkhdf5_hl-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkhdf5-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkoggtheora-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkParallelCore-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkIOLegacy-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkFiltersTexture-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkGUISupportQt-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkRenderingOpenGL2-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkglew-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkViewsInfovis-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkChartsCore-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkRenderingContext2D-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkViewsCore-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkInteractionWidgets-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkFiltersHybrid-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkInteractionStyle-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkRenderingAnnotation-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkImagingColor-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkRenderingVolume-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkIOXML-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkIOXMLParser-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkIOCore-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtklz4-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkexpat-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkFiltersImaging-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkImagingGeneral-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkImagingSources-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkRenderingLabel-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkRenderingFreeType-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkRenderingCore-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkCommonColor-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkFiltersGeometry-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkfreetype-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkInfovisLayout-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkInfovisCore-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkFiltersExtraction-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkFiltersStatistics-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkImagingFourier-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkalglib-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkFiltersModeling-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkFiltersSources-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkFiltersGeneral-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkCommonComputationalGeometry-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkFiltersCore-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkImagingHybrid-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkImagingCore-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkIOImage-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkCommonExecutionModel-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkCommonDataModel-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkCommonMisc-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkCommonSystem-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtksys-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkCommonTransforms-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkCommonMath-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkCommonCore-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkDICOMParser-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkmetaio-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkpng-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtktiff-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkzlib-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/local/lib/libvtkjpeg-8.1.1.dylib
ArchClip.app/Contents/MacOS/ArchClip: /usr/lib/libm.dylib
ArchClip.app/Contents/MacOS/ArchClip: /Users/weiyang/Downloads/Qt5.11.2/5.11.2/clang_64/lib/QtWidgets.framework/QtWidgets
ArchClip.app/Contents/MacOS/ArchClip: /Users/weiyang/Downloads/Qt5.11.2/5.11.2/clang_64/lib/QtGui.framework/QtGui
ArchClip.app/Contents/MacOS/ArchClip: /Users/weiyang/Downloads/Qt5.11.2/5.11.2/clang_64/lib/QtCore.framework/QtCore
ArchClip.app/Contents/MacOS/ArchClip: CMakeFiles/ArchClip.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/weiyang/pro/ArchClip/qt-ArchClip-Release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable ArchClip.app/Contents/MacOS/ArchClip"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ArchClip.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ArchClip.dir/build: ArchClip.app/Contents/MacOS/ArchClip

.PHONY : CMakeFiles/ArchClip.dir/build

CMakeFiles/ArchClip.dir/requires: CMakeFiles/ArchClip.dir/main.o.requires
CMakeFiles/ArchClip.dir/requires: CMakeFiles/ArchClip.dir/widget.o.requires
CMakeFiles/ArchClip.dir/requires: CMakeFiles/ArchClip.dir/ArchClip_autogen/mocs_compilation.o.requires

.PHONY : CMakeFiles/ArchClip.dir/requires

CMakeFiles/ArchClip.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ArchClip.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ArchClip.dir/clean

CMakeFiles/ArchClip.dir/depend: ui_widget.h
	cd /Users/weiyang/pro/ArchClip/qt-ArchClip-Release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/weiyang/pro/ArchClip /Users/weiyang/pro/ArchClip /Users/weiyang/pro/ArchClip/qt-ArchClip-Release /Users/weiyang/pro/ArchClip/qt-ArchClip-Release /Users/weiyang/pro/ArchClip/qt-ArchClip-Release/CMakeFiles/ArchClip.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ArchClip.dir/depend

