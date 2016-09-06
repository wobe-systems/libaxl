MESSAGE("ENTERED TEST SOURCE DIRECTORY")

set (TEST_SOURCES test_01.c)

	
source_group("Sourcefiles" FILES ${AXL_SOURCES})

#######################################################
## Windows 64 bit
#######################################################

if (${AXL_TARGET_PLATFORM} STREQUAL win_x86-64)
  
  set(PREPROCESSOR_DEF -DVERSION=\"0.7.2\" -D__axl_disable_broken_bool_def__ -DAXL_NS_SUPPORT -DAXL_BABEL_SUPPORT)

  set(TARGET_TEST test_01)
  set(BUILD_STATIC false)

endif (${AXL_TARGET_PLATFORM} STREQUAL win_x86-64)

#######################################################
## Windows 32 bit
#######################################################

if (${AXL_TARGET_PLATFORM} STREQUAL win_x86-32)
  
  set(PREPROCESSOR_DEF -DVERSION=\"0.7.2\" -D__axl_disable_broken_bool_def__ -DAXL_NS_SUPPORT -DAXL_BABEL_SUPPORT)

  set(TARGET_TEST test_01)
  set(BUILD_STATIC false)

endif (${AXL_TARGET_PLATFORM} STREQUAL win_x86-32)

#######################################################
## LINUX 64 bit
#######################################################

if (${AXL_TARGET_PLATFORM} STREQUAL linux_x86-64)
  
  set(PREPROCESSOR_DEF -Wall -g -ansi -DTEST_DIR=../test -DSHOW_DEBUG_LOG -DAXL_NS_SUPPORT -DAXL_BABEL_SUPPORT -DVERSION=\"0.7.1.b3508\"  -D__axl_disable_broken_bool_def__) 
  set(TARGET_TEST test_01)
  set (EXECUTABLE_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/bin)

endif (${AXL_TARGET_PLATFORM} STREQUAL linux_x86-64)

#######################################################
## LINUX 32 bit
#######################################################

if (${AXL_TARGET_PLATFORM} STREQUAL linux_x86-32)
  
  set(PREPROCESSOR_DEF -Wall -g -ansi -m32 -DTEST_DIR=../test -DSHOW_DEBUG_LOG -DAXL_NS_SUPPORT -DAXL_BABEL_SUPPORT -DVERSION=\"0.7.2\"  -D__axl_disable_broken_bool_def__) 
  set(CMAKE_EXE_LINKER_FLAGS "-m32")
  set(TARGET_TEST test_01)
  set (EXECUTABLE_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/bin)

endif (${AXL_TARGET_PLATFORM} STREQUAL linux_x86-32)

#######################################################
## LINUX ARM 32
#######################################################

if (${AXL_TARGET_PLATFORM} STREQUAL linux_arm32)
  
  set(PREPROCESSOR_DEF -Wall -g -ansi  -DTEST_DIR=../test -DSHOW_DEBUG_LOG -DAXL_NS_SUPPORT -DAXL_BABEL_SUPPORT -DVERSION=\"0.7.2\"  -D__axl_disable_broken_bool_def__) 
  set(TARGET_TEST test_01)
  set (EXECUTABLE_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/bin)

endif (${AXL_TARGET_PLATFORM} STREQUAL linux_arm32)

INCLUDE_DIRECTORIES (.)
INCLUDE_DIRECTORIES (../src)
INCLUDE_DIRECTORIES (../ns)
INCLUDE_DIRECTORIES (../babel)

ADD_EXECUTABLE (${TARGET_TEST} ${TEST_SOURCES})

ADD_DEFINITIONS (${PREPROCESSOR_DEF})

#LINK_DIRECTORIES (${CMAKE_BINARY_DIR}/build/static)

TARGET_LINK_LIBRARIES(${TARGET_TEST} ${AXL_LIB_NAME} ${AXL_BABEL_LIB_NAME} ${AXL_NS_LIB_NAME}) 

INSTALL (TARGETS ${TARGET_TEST} DESTINATION ${CMAKE_BINARY_DIR}/bin)
