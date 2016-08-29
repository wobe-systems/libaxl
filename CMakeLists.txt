#  libTML:  A BEEP based Messaging Suite
#  Copyright (C) 2015 wobe-systems GmbH
#
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU Lesser General Public License
#  as published by the Free Software Foundation; either version 2.1
#  of the License, or (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#  Lesser General Public License for more details.
#
#  You should have received a copy of the GNU Lesser General Public
#  License along with this program; if not, write to the Free
#  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
#  02111-1307 USA
#  
#  You may find a copy of the license under this software is released
#  at COPYING file. This is LGPL software: you are welcome to develop
#  proprietary applications using this library without any royalty or
#  fee but returning back any change, improvement or addition in the
#  form of source code, project image, documentation patches, etc.
#
#  Homepage:
#    http://www.libtml.org
#
#  For professional support contact us:
#
#    wobe-systems GmbH
#    support@libtml.org
#  
# Contributors:
#    wobe-systems GmbH

set(CMAKE_VERBOSE_MAKEFILE on)

#######################################################
## minimum required cmake version 
cmake_minimum_required(VERSION 3.1)

#######################################################
## set build parameter
#######################################################
SET (AXL_TARGET_PLATFORM win_x86-64 CACHE STRING "set the build target")

#######################################################
## set version parameter
#######################################################
set (AXL_MAJOR_VERSION 0)
set (AXL_MINOR_VERSION 7)
set (AXL_MICRO_VERSION 1)

set (CPACK_PACKAGE_VERSION_MAJOR "${AXL_MAJOR_VERSION}")
set (CPACK_PACKAGE_VERSION_MINOR "${AXL_MINOR_VERSION}")
set (CPACK_PACKAGE_VERSION_PATCH "${AXL_MICRO_VERSION}")
set (PLATFORM_FOUND false)

#######################################################
## set paths to look up binaries, libraries and includes
#######################################################
set (CMAKE_PREFIX_PATH  /usr)
set (CMAKE_PREFIX_PATH  ${CMAKE_PREFIX_PATH} /usr/local)

#######################################################
## LINUX 64 bit
#######################################################
if (${AXL_TARGET_PLATFORM} STREQUAL linux_x86-64)

  set(PROJECT linux_x86-64)

  #Platform specific defines for Linux
  set(OSPLATFORM "AXL_OS_UNIX (1)")  
  set(VASPRINTF  "AXL_HAVE_VASPRINTF (1)")

  configure_file (
   "${CMAKE_SOURCE_DIR}/src/axl_config.h.in"
   "${CMAKE_SOURCE_DIR}/src/axl_config.h")

  set(IS64BIT true)
  set(CPACK_SET_DESTDIR ON)
  set(CPACK_RESOURCE_FILE_LICENSE ../COPYING)
  
  include (CPack)

  set (PLATFORM_FOUND true)  

endif (${AXL_TARGET_PLATFORM} STREQUAL linux_x86-64)

#######################################################
## LINUX 32 bit
#######################################################
if (${AXL_TARGET_PLATFORM} STREQUAL linux_x86-32)

  set(PROJECT linux_x86-32)

  set(OSPLATFORM "AXL_OS_UNIX (1)")  
  set(VASPRINTF  "AXL_HAVE_VASPRINTF (1)")

  configure_file (
   "${CMAKE_SOURCE_DIR}/src/axl_config.h.in"
   "${CMAKE_SOURCE_DIR}/src/axl_config.h")

  set(IS64BIT false)
  set(CPACK_SET_DESTDIR ON)
  set(CPACK_RESOURCE_FILE_LICENSE ../COPYING)
  
  include (CPack)

  set (PLATFORM_FOUND true)  

endif (${AXL_TARGET_PLATFORM} STREQUAL linux_x86-32)

#######################################################

if (${PLATFORM_FOUND} STREQUAL true)

  MESSAGE(PLATFORM FOUND)

  #######################################################
  ## Project / Solution- File:
  #######################################################
  PROJECT( axl )
  
  #######################################################
  ## Source and destination directories:
  #######################################################
  ADD_SUBDIRECTORY( src   ${PROJECT}/axl)
  ADD_SUBDIRECTORY( babel ${PROJECT}/babel)
  ADD_SUBDIRECTORY( ns    ${PROJECT}/ns)
  ADD_SUBDIRECTORY( test  ${PROJECT}/test)
 
else (${PLATFORM_FOUND} STREQUAL true)
  message( SEND_ERROR "Unknown target platform / please check \"AXL_TARGET_PLATFORM\"" )
endif (${PLATFORM_FOUND} STREQUAL true)

