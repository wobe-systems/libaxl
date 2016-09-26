MESSAGE("ENTERED TEST SOURCE DIRECTORY")

set (TEST_SOURCES test_01.c)

	
source_group("Sourcefiles" FILES ${AXL_SOURCES})

#######################################################
## Windows 64 bit
#######################################################

if (${AXL_TARGET_PLATFORM} STREQUAL win_x86-64)
  if (${USE_BABEL_AND_NS} STREQUAL yes)
    set(PREPROCESSOR_DEF -DVERSION=\"${AXLVER}\" -D__axl_disable_broken_bool_def__ -DAXL_NS_SUPPORT -DAXL_BABEL_SUPPORT)
  else (${USE_BABEL_AND_NS} STREQUAL yes)  
    set(PREPROCESSOR_DEF -DVERSION=\"${AXLVER}\" -D__axl_disable_broken_bool_def__)
  endif (${USE_BABEL_AND_NS} STREQUAL yes)
  set(TARGET_TEST test_01)
  set(BUILD_STATIC false)

endif (${AXL_TARGET_PLATFORM} STREQUAL win_x86-64)

#######################################################
## Windows 32 bit
#######################################################

if (${AXL_TARGET_PLATFORM} STREQUAL win_x86-32)
  if (${USE_BABEL_AND_NS} STREQUAL yes)
    set(PREPROCESSOR_DEF -DVERSION=\"${AXLVER}\" -D__axl_disable_broken_bool_def__ -DAXL_NS_SUPPORT -DAXL_BABEL_SUPPORT)
  else (${USE_BABEL_AND_NS} STREQUAL yes)  
    set(PREPROCESSOR_DEF -DVERSION=\"${AXLVER}\" -D__axl_disable_broken_bool_def__)
  endif (${USE_BABEL_AND_NS} STREQUAL yes)
  set(TARGET_TEST test_01)
  set(BUILD_STATIC false)

endif (${AXL_TARGET_PLATFORM} STREQUAL win_x86-32)

#######################################################
## LINUX 64 bit
#######################################################

if (${AXL_TARGET_PLATFORM} STREQUAL linux_x86-64)
  if (${USE_BABEL_AND_NS} STREQUAL yes)
    set(PREPROCESSOR_DEF -Wall -g -ansi -DTEST_DIR=../test -DSHOW_DEBUG_LOG -DAXL_NS_SUPPORT -DAXL_BABEL_SUPPORT -DVERSION=\"${AXLVER}\"  -D__axl_disable_broken_bool_def__)
  else (${USE_BABEL_AND_NS} STREQUAL yes)  
    set(PREPROCESSOR_DEF -Wall -g -ansi -DTEST_DIR=../test -DSHOW_DEBUG_LOG -DVERSION=\"${AXLVER}\"  -D__axl_disable_broken_bool_def__)
  endif (${USE_BABEL_AND_NS} STREQUAL yes)
  set(TARGET_TEST test_01)
  set (EXECUTABLE_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/bin)
  set(BUILD_STATIC false)

endif (${AXL_TARGET_PLATFORM} STREQUAL linux_x86-64)

#######################################################
## LINUX 32 bit
#######################################################

if (${AXL_TARGET_PLATFORM} STREQUAL linux_x86-32)
  if (${USE_BABEL_AND_NS} STREQUAL yes)
    set(PREPROCESSOR_DEF -Wall -g -ansi -m32 -DTEST_DIR=../test -DSHOW_DEBUG_LOG -DAXL_NS_SUPPORT -DAXL_BABEL_SUPPORT -DVERSION=\"${AXLVER}\"  -D__axl_disable_broken_bool_def__)
  else (${USE_BABEL_AND_NS} STREQUAL yes)  
    set(PREPROCESSOR_DEF -Wall -g -ansi -m32 -DTEST_DIR=../test -DSHOW_DEBUG_LOG -DVERSION=\"${AXLVER}\"  -D__axl_disable_broken_bool_def__)
  endif (${USE_BABEL_AND_NS} STREQUAL yes)
  set(CMAKE_EXE_LINKER_FLAGS "-m32")
  set(TARGET_TEST test_01)
  set (EXECUTABLE_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/bin)
  set(BUILD_STATIC false)

endif (${AXL_TARGET_PLATFORM} STREQUAL linux_x86-32)

#######################################################
## LINUX ARM 32
#######################################################

if (${AXL_TARGET_PLATFORM} STREQUAL linux_arm32)
  if (${USE_BABEL_AND_NS} STREQUAL yes)
    set(PREPROCESSOR_DEF -Wall -g -ansi  -DTEST_DIR=../test -DSHOW_DEBUG_LOG -DAXL_NS_SUPPORT -DAXL_BABEL_SUPPORT -DVERSION=\"${AXLVER}\"  -D__axl_disable_broken_bool_def__)
  else (${USE_BABEL_AND_NS} STREQUAL yes)  
    set(PREPROCESSOR_DEF -Wall -g -ansi  -DTEST_DIR=../test -DSHOW_DEBUG_LOG -DVERSION=\"${AXLVER}\"  -D__axl_disable_broken_bool_def__) 
  endif (${USE_BABEL_AND_NS} STREQUAL yes)
  set(TARGET_TEST test_01)
  set (EXECUTABLE_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/bin)
  set(BUILD_STATIC false)

endif (${AXL_TARGET_PLATFORM} STREQUAL linux_arm32)

#######################################################
## FreeBSD 32
#######################################################

if (${AXL_TARGET_PLATFORM} STREQUAL freeBSD_x86-32)
  if (${USE_BABEL_AND_NS} STREQUAL yes)
    set(PREPROCESSOR_DEF -DVERSION=\"${AXLVER}\" -D__axl_disable_broken_bool_def__ -DAXL_NS_SUPPORT -DAXL_BABEL_SUPPORT)
  else (${USE_BABEL_AND_NS} STREQUAL yes)  
    set(PREPROCESSOR_DEF -DVERSION=\"${AXLVER}\" -D__axl_disable_broken_bool_def__)
  endif (${USE_BABEL_AND_NS} STREQUAL yes)
  
  ADD_DEFINITIONS ("-m32")
  set(CMAKE_CXX_FLAGS "-m32")
  set(CMAKE_SHARED_LINKER_FLAGS "-m32")

  set(TARGET_TEST test_01)
  set(BUILD_STATIC false)

endif (${AXL_TARGET_PLATFORM} STREQUAL freeBSD_x86-32)

#######################################################
## FreeBSD 64
#######################################################

if (${AXL_TARGET_PLATFORM} STREQUAL freeBSD_x86-64)
  if (${USE_BABEL_AND_NS} STREQUAL yes)
    set(PREPROCESSOR_DEF -DVERSION=\"${AXLVER}\" -D__axl_disable_broken_bool_def__ -DAXL_NS_SUPPORT -DAXL_BABEL_SUPPORT)
  else (${USE_BABEL_AND_NS} STREQUAL yes)  
    set(PREPROCESSOR_DEF -DVERSION=\"${AXLVER}\" -D__axl_disable_broken_bool_def__)
  endif (${USE_BABEL_AND_NS} STREQUAL yes)
  
  ADD_DEFINITIONS ("-m64")
  set(CMAKE_CXX_FLAGS "-m64")
  set(CMAKE_SHARED_LINKER_FLAGS "-m64")

  set(TARGET_TEST test_01)
  set(BUILD_STATIC false)

endif (${AXL_TARGET_PLATFORM} STREQUAL freeBSD_x86-64)

#######################################################
## OSX 32 bit
#######################################################
if (${AXL_TARGET_PLATFORM} STREQUAL osx_x86-32)
  if (${USE_BABEL_AND_NS} STREQUAL yes)
    set(PREPROCESSOR_DEF -DVERSION=\"${AXLVER}\" -D__axl_disable_broken_bool_def__ -DAXL_NS_SUPPORT -DAXL_BABEL_SUPPORT)
  else (${USE_BABEL_AND_NS} STREQUAL yes)  
    set(PREPROCESSOR_DEF -DVERSION=\"${AXLVER}\" -D__axl_disable_broken_bool_def__)
  endif (${USE_BABEL_AND_NS} STREQUAL yes)
  
  ADD_DEFINITIONS ("-arch i386")
  set(CMAKE_C_FLAGS "-arch i386")

  set(TARGET_TEST test_01)
  set (EXECUTABLE_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/bin)
  set(BUILD_STATIC false)

endif (${AXL_TARGET_PLATFORM} STREQUAL osx_x86-32)

#######################################################
## OSX 64 bit
#######################################################
if (${AXL_TARGET_PLATFORM} STREQUAL osx_x86-64)
  if (${USE_BABEL_AND_NS} STREQUAL yes)
    set(PREPROCESSOR_DEF -DVERSION=\"${AXLVER}\" -D__axl_disable_broken_bool_def__ -DAXL_NS_SUPPORT -DAXL_BABEL_SUPPORT)
  else (${USE_BABEL_AND_NS} STREQUAL yes)  
    set(PREPROCESSOR_DEF -DVERSION=\"${AXLVER}\" -D__axl_disable_broken_bool_def__)
  endif (${USE_BABEL_AND_NS} STREQUAL yes)
   
  ADD_DEFINITIONS ("-arch x86_64")
  set(CMAKE_C_FLAGS "-arch x86_64")
  
  set(TARGET_TEST test_01)
  set(BUILD_STATIC false)
  set (EXECUTABLE_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/bin)

endif (${AXL_TARGET_PLATFORM} STREQUAL osx_x86-64)

INCLUDE_DIRECTORIES (.)
INCLUDE_DIRECTORIES (../src)
INCLUDE_DIRECTORIES (../ns)
INCLUDE_DIRECTORIES (../babel)

ADD_EXECUTABLE (${TARGET_TEST} ${TEST_SOURCES})

ADD_DEFINITIONS (${PREPROCESSOR_DEF})

if (${BUILD_STATIC} STREQUAL true)
  LINK_DIRECTORIES (${CMAKE_BINARY_DIR}/build/static)
endif (${BUILD_STATIC} STREQUAL true)

TARGET_LINK_LIBRARIES(${TARGET_TEST} ${AXL_LIB_NAME} ${AXL_BABEL_LIB_NAME} ${AXL_NS_LIB_NAME}) 

INSTALL (TARGETS ${TARGET_TEST} DESTINATION ${CMAKE_BINARY_DIR}/bin)
