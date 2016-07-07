MESSAGE("ENTERED AXL-BABEL SOURCE DIRECTORY")

set (AXL_BABEL_SOURCES	axl_babel.c
			axl_babel_iso885915.c
			axl_babel_iso88591.c
			axl_babel_iso88592.c
			axl_babel_iso88593.c
			axl_babel_iso88594.c
			axl_babel_iso88595.c
			axl_babel_iso88596.c
			axl_babel_iso88597.c
			axl_babel_iso88598.c
			axl_babel_iso88599.c
			)

set (AXL_BABEL_SOURCES_HEADER 	axl_babel.h
				axl_babel_iso885915.h
				axl_babel_iso88591.h
				axl_babel_iso88592.h
				axl_babel_iso88593.h
				axl_babel_iso88594.h
				axl_babel_iso88595.h
				axl_babel_iso88596.h
				axl_babel_iso88597.h
				axl_babel_iso88598.h
				axl_babel_iso88599.h)
	
source_group("Headerfiles" FILES ${AXL_SOURCES_HEADER})
source_group("Sourcefiles" FILES ${AXL_SOURCES})






if (${AXL_TARGET_PLATFORM} STREQUAL linux_x86-64)
  
  set(PREPROCESSOR_DEF -Wall -Werror -g -ansi -DVERSION=\"0.7.1.b3508\" -DPACKAGE_DTD_DIR=\"/usr/local/share\" -DPACKAGE_TOP_DIR=\"..\" -D__axl_disable_broken_bool_def__ -DSHOW_DEBUG_LOG -DPIC)
  set(CMAKE_SHARED_LINKER_FLAGS -O2)
  set(AXL_BABEL_LOCAL axl-babel)
  set(AXL_BABEL_LOCAL_STATIC axl-babel_static)
  set(AXL_BABEL_LIB_NAME ${AXL_BABEL_LOCAL} PARENT_SCOPE)
  set(IS64BIT true)

  set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)
  set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/static)

  MESSAGE (STATUS "CMAKE PROJECT_SOURCE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}")
  MESSAGE (STATUS "CMAKE_BINARY_DIR:           ${CMAKE_BINARY_DIR}" )
  MESSAGE (STATUS "LIBRARY_OUTPUT_DIRECTORY:   ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

endif (${AXL_TARGET_PLATFORM} STREQUAL linux_x86-64)

INCLUDE_DIRECTORIES (.)
INCLUDE_DIRECTORIES (../src)
ADD_DEFINITIONS (${PREPROCESSOR_DEF})

ADD_LIBRARY( ${AXL_BABEL_LOCAL}        SHARED ${AXL_BABEL_SOURCES_HEADER} ${AXL_BABEL_SOURCES})
ADD_LIBRARY( ${AXL_BABEL_LOCAL_STATIC} STATIC ${AXL_BABEL_SOURCES_HEADER} ${AXL_BABEL_SOURCES})

set_target_properties(${AXL_BABEL_LOCAL_STATIC}  PROPERTIES OUTPUT_NAME ${AXL_BABEL_LOCAL})

INSTALL (TARGETS ${AXL_BABEL_LOCAL} DESTINATION ${CMAKE_BINARY_DIR}/build/lib)
INSTALL (TARGETS ${AXL_BABEL_LOCAL_STATIC} DESTINATION ${CMAKE_BINARY_DIR}/build/static)





