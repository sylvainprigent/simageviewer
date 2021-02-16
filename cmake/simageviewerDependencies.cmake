############################################################
#
# $Id$
#
# Copyright (c) SImageViewer 2020
#
# AUTHOR:
# Sylvain Prigent
# 

## #################################################################
## Qt
## #################################################################
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)

#set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(Threads REQUIRED)
find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

set (SL_LIBRARIES ${SL_LIBRARIES} Qt6::Core Qt6::Widgets)

## ##################################################################
## score
## ##################################################################
find_package (score REQUIRED)
if ( score_FOUND )
  message(STATUS "Using score")
  set (SL_INCLUDE_DIRS ${SL_INCLUDE_DIRS} ${score_INCLUDE_DIRS})
  set (SL_LIBRARY_DIRS ${SL_LIBRARY_DIRS} ${score_LIBRARY_DIRS})
  set (SL_LIBRARIES ${SL_LIBRARIES} ${score_LIBRARIES})
  message(STATUS "score_LIBRARY_DIRS=" ${score_LIBRARY_DIRS})
  set(simageviewer_HAVE_score 1)
else( score_FOUND )
  message(STATUS "NOT Using score")
endif( score_FOUND )

## ##################################################################
## sdata
## ##################################################################
find_package (sdata REQUIRED)
if ( sdata_FOUND )
  message(STATUS "Using sdata")
  set (SL_INCLUDE_DIRS ${SL_INCLUDE_DIRS} ${sdata_INCLUDE_DIRS})
  set (SL_LIBRARY_DIRS ${SL_LIBRARY_DIRS} ${sdata_LIBRARY_DIRS})
  set (SL_LIBRARIES ${SL_LIBRARIES} ${sdata_LIBRARIES})
  message(STATUS "score_LIBRARY_DIRS=" ${sdata_LIBRARY_DIRS})
  set(simageviewer_HAVE_sdata 1)
else( sdata_FOUND )
  message(STATUS "NOT Using sdata")
endif( sdata_FOUND )

## ##################################################################
## simage
## ##################################################################
find_package (simage REQUIRED)
if ( simage_FOUND )
  message(STATUS "Using simage")
  set (SL_INCLUDE_DIRS ${SL_INCLUDE_DIRS} ${simage_INCLUDE_DIRS})
  set (SL_LIBRARY_DIRS ${SL_LIBRARY_DIRS} ${simage_LIBRARY_DIRS})
  set (SL_LIBRARIES ${SL_LIBRARIES} ${simage_LIBRARIES})
  message(STATUS "simage_LIBRARY_DIRS=" ${simage_LIBRARY_DIRS})
  set(simageviewer_HAVE_simage 1)
else( simage_FOUND )
  message(STATUS "NOT Using simage")
endif( simage_FOUND )

## ##################################################################
## simageio
## ##################################################################
find_package (simageio REQUIRED)
if ( simageio_FOUND )
  message(STATUS "Using simage")
  set (SL_INCLUDE_DIRS ${SL_INCLUDE_DIRS} ${simageio_INCLUDE_DIRS})
  set (SL_LIBRARY_DIRS ${SL_LIBRARY_DIRS} ${simageio_LIBRARY_DIRS})
  set (SL_LIBRARIES ${SL_LIBRARIES} ${simageio_LIBRARIES})
  message(STATUS "simage_LIBRARY_DIRS=" ${simageio_LIBRARY_DIRS})
  set(simageviewer_HAVE_simageio 1)
else( simageio_FOUND )
  message(STATUS "NOT Using simage")
endif( simageio_FOUND )

## #################################################################
## libtiff
## #################################################################

find_package (TIFF REQUIRED)
if (TIFF_FOUND)
  set (SL_INCLUDE_DIRS ${SL_INCLUDE_DIRS} ${TIFF_INCLUDE_DIR})
  set (SL_LIBRARIES ${SL_LIBRARIES} ${TIFF_LIBRARIES})
  message(STATUS "TIFF found")
else (TIFF_FOUND)
  message(STATUS "TIFF NOT found.")
  message (FATAL_ERROR "You need libtiff to compile this program. Please install libs and developpement headers")
endif (TIFF_FOUND)

## #################################################################
## Doxygen
## #################################################################

find_package(Doxygen QUIET)
if(${DOXYGEN_FOUND})
  set(SL_USE_DOXYGEN 1)
endif(${DOXYGEN_FOUND})

if(${SL_USE_OPENMP})
  find_package(OpenMP REQUIRED)
endif(${SL_USE_OPENMP})  

## #################################################################
## definitions
## #################################################################
add_definitions (${SL_DEFINITIONS})
include_directories (${SL_INCLUDE_DIRS})
link_directories(${SL_LIBRARY_DIRS})
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SL_C_FLAGS}")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SL_CXX_FLAGS}")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set (SL_INCLUDE_DIRS ${SL_INCLUDE_DIRS} CACHE STRING "include directories for spartion dependancies")
set (SL_LIBRARIES ${SL_LIBRARIES} CACHE STRING "spartion required and optional 3rd party libraries")
set (SL_DEFINITIONS ${SL_DEFINITIONS} CACHE STRING "SL_USE_XXX defines")
set (SL_C_FLAGS ${SL_C_FLAGS}  CACHE STRING "c flags for cimg")
set (SL_CXX_FLAGS ${SL_CXX_FLAGS} CACHE STRING "c++ flags for cimg")
 
