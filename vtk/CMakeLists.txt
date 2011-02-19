cmake_minimum_required(VERSION 2.6)
 
PROJECT(TriangulateTerrainMap)
 
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

SET(CMAKE_CXX_FLAGS "-std=gnu++0x -D_GLIBCXX_USE_NANOSLEEP")
 
ADD_EXECUTABLE(TriangulateTerrainMap TriangulateTerrainMap.cxx)
TARGET_LINK_LIBRARIES(TriangulateTerrainMap vtkHybrid)
