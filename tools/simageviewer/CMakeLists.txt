############################################################
#
# $Id$
#
# Copyright (c) SImageViewer 2021
#
# AUTHOR:
# Sylvain Prigent
# 

# Project name
project(SImageViewerDemo)

## #################################################################
## Define files
## #################################################################
include_directories(${simageviewer_SRC_INCLUDE_DIR})

SET(SRC_FILES 
	)

## #################################################################
## Exe generation
## #################################################################
SET(NAME demo)
SET(FILE ${SRC_FILES} DemoWindow.cpp DemoWindow.h demo.cpp )
add_executable( ${NAME} ${FILE} )
target_link_libraries(${NAME} simageviewer ${SL_LIBRARIES})
