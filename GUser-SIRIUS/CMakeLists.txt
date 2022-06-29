#------------------------------------ 
# CMake file for Gru User online program
#
# Author: Rikel CHAKMA and Luc LEGEARD 
# Date: 24/06/2022
#-------------------------------------
cmake_minimum_required(VERSION 2.8.12)
project(GUser)
#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)
#---------------------
#  C++ compiler
#---------------------
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++ support. Use another C++ compiler.")
endif()

#----------------------------------------------------------
# Cmake install prefix = install directory used by install
#-----------------------------------------------------------
if(CMAKE_INSTALL_PREFIX)
   message (STATUS "CMAKE_INSTALL_PREFIX found : ${CMAKE_INSTALL_PREFIX} ")
else()
   message (WARNING "CMAKE_INSTALL_PREFIX not found !!! ")
endif()

#------------
# GRU and MFM
#--------------
set(GRULIBDIR  $ENV{GRUDIR}/build/)
set(GRUINCDIR   $ENV{GRUDIR}/include/) 
set(VIGRUDIR    $ENV{GRUDIR}/vigru/)
set(GSOAPDIR    $ENV{GRUDIR}/gsoap/)
set(MFM_DIR     $ENV{MFMDIR})
set(MFMINCDIR   $ENV{MFMDIR}/include/)

Set (GRUFLAGS     -I${GRUINCDIR} -I${CMAKE_SOURCE_DIR}  -I${VIGRUDIR}   -I${GSOAPDIR} -I${MFM_DIR} -I${MFMINCDIR})

include_directories(${CMAKE_SOURCE_DIR}  ${GRUINCDIR} ${MFMINCDIR})

set (INCLIST  ${GRUINCDIR}/General.h  ${GRUINCDIR}/GAcq.h  ${GRUINCDIR}/GDevice.h )

#----------------------------
# Source and header files
#--------------------------
set(SOURCES  GUserDict.C GUser.C global.cc dssdData.cc  digitalFilters.cc digitalCFD.cc Calibration.cc DataPoint.cc EventPoint.cc )

set(HEADERS GUserDict.h GUser.h global.h dssdData.h  digitalFilters.h digitalCFD.h Calibration.h DataPoint.h EventPoint.h )

#----------------------------------
# ROOT
#---------------------------------
#set(ROOT_DIR /home/global/root/root_v5.34.38_C7)
#list(APPEND CMAKE_PREFIX_PATH ${ROOT_DIR})
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED)
if(ROOT_FOUND)
	message(STATUS "ROOT found ...")
else()
	message(FATAL_ERROR "!!! ROOT not found. !!! Aborting...")
endif()

include_directories(${ROOT_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${ROOT_CXX_FLAGS}")
set(CMAKE_C_FLAGS "${ROOT_CC_FLAGS}")

#--------------------------
# Create shared object
#-------------------------
add_library(GUser SHARED ${SOURCES})
set_target_properties(GUser PROPERTIES OUTPUT_NAME GUser_C)
set_target_properties(GUser PROPERTIES PREFIX "")
target_link_libraries(GUser ${ROOT_LIBRARIES})

#--------------------------------
# Dictionary Generation
#-------------------------
set(rootcommand rootcint -f GUserDict.C -c -p ${GRUFLAGS} ${CMAKE_SOURCE_DIR}/GUser.h ${CMAKE_SOURCE_DIR}/GUser_linkdef.h)
add_custom_command(OUTPUT GUserDict.C GUserDict.h GUser_C.d
			COMMAND ${rootcommand}
			DEPENDS ${INCLIST} ${CMAKE_SOURCE_DIR}/GUser.h ${CMAKE_SOURCE_DIR}/GUser_linkdef.h
			COMMENT "Generating GUser dictionary..."
		)

install(TARGETS GUser     DESTINATION bin
		LIBRARY   DESTINATION lib
	        ARCHIVE   DESTINATION lib
	        INCLUDES  DESTINATION include
		COMPONENT libraries)
		
install(FILES ${HEADERS}  DESTINATION include)

