MESSAGE("ENTERED AXL SOURCE DIRECTORY")

set (AXL_SOURCES axl.c
		 axl_decl.c
		 axl_doc.c
		 axl_dtd.c
		 axl_error.c
		 axl_factory.c
		 axl_hash.c
		 axl_list.c
		 axl_log.c
		 axl_node.c
		 axl_stack.c
		 axl_stream.c)

set (AXL_SOURCES_HEADER axl_config.h
			axl_config_win32.h
			axl_config_win64.h
			axl_decl.h
			axl_doc.h
			axl_dtd.h
			axl_error.h
			axl_factory.h
			axl.h
			axl_hash.h
			axl_list.h
			axl_log.h
			axl_node.h
			axl_stack.h
			axl_stream.h)
	
source_group("Headerfiles" FILES ${AXL_SOURCES_HEADER})
source_group("Sourcefiles" FILES ${AXL_SOURCES})

#######################################################
## Windows 64 bit
#######################################################

if (${AXL_TARGET_PLATFORM} STREQUAL win_x86-64)

  set(PREPROCESSOR_DEF -DVERSION=\"0.7.2\" -D__axl_disable_broken_bool_def__ -DPIC -DHAVE_VSCPRINTF)
  # Additional library definition file in case of Visual Studio:
  set(AXL_DEF libaxl.def)

  set(AXL_LOCAL libaxl)
  set(AXL_LOCAL_STATIC libaxl_static)
  set(AXL_LIB_NAME ${AXL_LOCAL} PARENT_SCOPE)
  set(BUILD_STATIC false)

  MESSAGE (STATUS "CMAKE PROJECT_SOURCE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}")
  MESSAGE (STATUS "CMAKE_BINARY_DIR:           ${CMAKE_BINARY_DIR}" )
  MESSAGE (STATUS "LIBRARY_OUTPUT_DIRECTORY:   ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

endif (${AXL_TARGET_PLATFORM} STREQUAL win_x86-64)

#######################################################
## Windows 32 bit
#######################################################

if (${AXL_TARGET_PLATFORM} STREQUAL win_x86-32)
  
  set(PREPROCESSOR_DEF -DVERSION=\"0.7.2\" -D__axl_disable_broken_bool_def__ -DPIC -DHAVE_VSCPRINTF)
  # Additional library definition file in case of Visual Studio:
  set(AXL_DEF libaxl.def)

  set(AXL_LOCAL libaxl)
  set(AXL_LOCAL_STATIC libaxl_static)
  set(AXL_LIB_NAME ${AXL_LOCAL} PARENT_SCOPE)
  set(BUILD_STATIC false)

  MESSAGE (STATUS "CMAKE PROJECT_SOURCE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}")
  MESSAGE (STATUS "CMAKE_BINARY_DIR:           ${CMAKE_BINARY_DIR}" )
  MESSAGE (STATUS "LIBRARY_OUTPUT_DIRECTORY:   ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

endif (${AXL_TARGET_PLATFORM} STREQUAL win_x86-32)

#######################################################
## LINUX 64 bit
#######################################################

if (${AXL_TARGET_PLATFORM} STREQUAL linux_x86-64)
  
  set(PREPROCESSOR_DEF -Wall -Werror -g -O2 -ansi -DVERSION=\"0.7.2\" -DPACKAGE_DTD_DIR=\"/usr/local/share\" -DPACKAGE_TOP_DIR=\"..\" -D__axl_disable_broken_bool_def__ -DSHOW_DEBUG_LOG -DPIC)
  set(CMAKE_SHARED_LINKER_FLAGS -O2)
  set(AXL_LOCAL axl)
  set(AXL_LOCAL_STATIC axl_static)
  set(AXL_LIB_NAME ${AXL_LOCAL} PARENT_SCOPE)
  set(BUILD_STATIC false)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/static)

  MESSAGE (STATUS "CMAKE PROJECT_SOURCE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}")
  MESSAGE (STATUS "CMAKE_BINARY_DIR:           ${CMAKE_BINARY_DIR}" )
  MESSAGE (STATUS "LIBRARY_OUTPUT_DIRECTORY:   ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

endif (${AXL_TARGET_PLATFORM} STREQUAL linux_x86-64)

#######################################################
## LINUX 32 bit
#######################################################

if (${AXL_TARGET_PLATFORM} STREQUAL linux_x86-32)
  
  set(PREPROCESSOR_DEF -Wall -Werror -g -O2 -ansi -m32 -DVERSION=\"0.7.2\" -DPACKAGE_DTD_DIR=\"/usr/local/share\" -DPACKAGE_TOP_DIR=\"..\" -D__axl_disable_broken_bool_def__ -DSHOW_DEBUG_LOG -DPIC)
  set(CMAKE_SHARED_LINKER_FLAGS -O2)
  set(CMAKE_SHARED_LINKER_FLAGS "-m32")
  set(AXL_LOCAL axl)
  set(AXL_LOCAL_STATIC axl_static)
  set(AXL_LIB_NAME ${AXL_LOCAL} PARENT_SCOPE)
  set(BUILD_STATIC false)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/static)

  MESSAGE (STATUS "CMAKE PROJECT_SOURCE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}")
  MESSAGE (STATUS "CMAKE_BINARY_DIR:           ${CMAKE_BINARY_DIR}" )
  MESSAGE (STATUS "LIBRARY_OUTPUT_DIRECTORY:   ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

endif (${AXL_TARGET_PLATFORM} STREQUAL linux_x86-32)

#######################################################
## LINUX ARM 32
#######################################################

if (${AXL_TARGET_PLATFORM} STREQUAL linux_arm32)
  
  set(PREPROCESSOR_DEF -Wall -Werror -g -O2 -ansi -DVERSION=\"0.7.2\" -DPACKAGE_DTD_DIR=\"/usr/local/share\" -DPACKAGE_TOP_DIR=\"..\" -D__axl_disable_broken_bool_def__ -DSHOW_DEBUG_LOG -DPIC)
  set(CMAKE_SHARED_LINKER_FLAGS -O2)
  set(AXL_LOCAL axl)
  set(AXL_LOCAL_STATIC axl_static)
  set(AXL_LIB_NAME ${AXL_LOCAL} PARENT_SCOPE)
  set(BUILD_STATIC false)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/static)

  MESSAGE (STATUS "CMAKE PROJECT_SOURCE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}")
  MESSAGE (STATUS "CMAKE_BINARY_DIR:           ${CMAKE_BINARY_DIR}" )
  MESSAGE (STATUS "LIBRARY_OUTPUT_DIRECTORY:   ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

endif (${AXL_TARGET_PLATFORM} STREQUAL linux_arm32)

#######################################################

INCLUDE_DIRECTORIES (.)
INCLUDE_DIRECTORIES (..)
ADD_DEFINITIONS (${PREPROCESSOR_DEF})

ADD_LIBRARY( ${AXL_LOCAL}        SHARED ${AXL_SOURCES_HEADER} ${AXL_SOURCES} ${AXL_DEF})
if (${BUILD_STATIC} STREQUAL true)
  ADD_LIBRARY( ${AXL_LOCAL_STATIC} STATIC ${AXL_SOURCES_HEADER} ${AXL_SOURCES} ${AXL_DEF})
  set_target_properties(${AXL_LOCAL_STATIC}  PROPERTIES OUTPUT_NAME ${AXL_LOCAL})
endif (${BUILD_STATIC} STREQUAL true)


INSTALL (TARGETS ${AXL_LOCAL}        DESTINATION ${CMAKE_BINARY_DIR}/build/lib)
if (${BUILD_STATIC} STREQUAL true)
  INSTALL (TARGETS ${AXL_LOCAL_STATIC} DESTINATION ${CMAKE_BINARY_DIR}/build/static)
endif (${BUILD_STATIC} STREQUAL true)

