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
  
  ADD_DEFINITIONS ("-m64")
  set(CMAKE_CXX_FLAGS "-m64")
  set(PREPROCESSOR_DEF -DGCC4)
  
  set(TARGET_BABEL axl-babel)

  set(IS64BIT true)

  set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)

message (STATUS "CMAKE PROJECT_SOURCE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}")
MESSAGE (STATUS "CMAKE_BINARY_DIR:           ${CMAKE_BINARY_DIR}" )
#MESSAGE(STATUS "CMAKE_PREFIX_PATH:         " ${CMAKE_PREFIX_PATH} )
MESSAGE (STATUS "LIBRARY_OUTPUT_DIRECTORY:   ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
MESSAGE (STATUS "CMAKE_FIND_LIBRARY_PREFIXES:${CMAKE_FIND_LIBRARY_PREFIXES} ")
MESSAGE (STATUS "CMAKE_FIND_LIBRARY_SUFFIXES:${CMAKE_FIND_LIBRARY_SUFFIXES} ")



endif (${AXL_TARGET_PLATFORM} STREQUAL linux_x86-64)

ADD_LIBRARY( ${TARGET_BABEL} SHARED ${AXL_BABEL_SOURCES_HEADER} ${AXL_BABEL_SOURCES})
set_target_properties(${TARGET_BABEL} PROPERTIES PREFIX "lib")

INCLUDE_DIRECTORIES (.)
INCLUDE_DIRECTORIES (../src)

ADD_DEFINITIONS (${PREPROCESSOR_DEF})

TARGET_LINK_LIBRARIES(${TARGET_BABEL}) 
INSTALL (TARGETS ${TARGET_BABEL} DESTINATION ${CMAKE_BINARY_DIR}/build/lib)








