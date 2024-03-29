cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

FIND_PACKAGE(VTK)
INCLUDE(${VTK_USE_FILE})

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#uncomment if you have defined messages
#rosbuild_genmsg()
#uncomment if you have defined services
#rosbuild_gensrv()

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})

rosbuild_add_executable(replay src/ImuEstimator.cpp
                               src/LandmarkParser.h
                               src/LandmarkParser.cpp
                               src/PoseParser.h
                               src/PoseParser.cpp)
                               
SET(TerrainViewSrcs src/TerrainVisualization.cpp 
                    src/TerrainViewUI.cpp)
                    
SET(TerrainViewUI src/TerrainViewUI.ui)

SET(TerrainViewHeaders src/TerrainViewUI.h)
 
QT4_WRAP_UI(UISrcs ${TerrainViewUI})
QT4_WRAP_CPP(MOCSrcs ${TerrainViewHeaders} )

SET(Widgets_sources  src/widget/RobotAttitudeWidget.cxx
                     src/widget/ElevationWidget.cxx
                     src/widget/TerrainActor.cxx
                     src/widget/RobotActor.cxx)

ADD_LIBRARY(CustomWidgets STATIC ${Widgets_sources})
rosbuild_add_executable(visualization ${TerrainViewSrcs} ${UISrcs} ${MOCSrcs})
TARGET_LINK_LIBRARIES( visualization QVTK CustomWidgets vtkHybrid vtkRendering)
