MESSAGE("ENTERED AXL SOURCE DIRECTORY")

set (AXL_SOURCES	axl.c
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


if (${AXL_TARGET_PLATFORM} STREQUAL linux_x86-64)
  
  ADD_DEFINITIONS ("-m64")
  set(CMAKE_CXX_FLAGS "-m64")
  set(PREPROCESSOR_DEF -DGCC4)
  
  set(AXL_LOCAL axl)
  set(AXL_LIB_NAME ${AXL_LOCAL} PARENT_SCOPE)
  set(IS64BIT true)

  set (INST_LIB_PATH /var/lib/jenkins/workspace/AXL_LIBRARY_LINUX_x64/build/lib)
  set (INST_INCLUDE_PATH /var/lib/jenkins/workspace/AXL_LIBRARY_LINUX_x64/build/include)

  set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)

message (STATUS "CMAKE PROJECT_SOURCE_DIR    ${CMAKE_CURRENT_SOURCE_DIR}")
MESSAGE (STATUS "CMAKE_BINARY_DIR:           ${CMAKE_BINARY_DIR}" )
#MESSAGE(STATUS "CMAKE_PREFIX_PATH:         " ${CMAKE_PREFIX_PATH} )
MESSAGE (STATUS "LIBRARY_OUTPUT_DIRECTORY:   ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
MESSAGE (STATUS "CMAKE_FIND_LIBRARY_PREFIXES:${CMAKE_FIND_LIBRARY_PREFIXES} ")
MESSAGE (STATUS "CMAKE_FIND_LIBRARY_SUFFIXES:${CMAKE_FIND_LIBRARY_SUFFIXES} ")

endif (${AXL_TARGET_PLATFORM} STREQUAL linux_x86-64)

ADD_LIBRARY( ${AXL_LOCAL} SHARED ${AXL_SOURCES_HEADER} ${AXL_SOURCES})
set_target_properties(${AXL_LOCAL} PROPERTIES PREFIX "lib")

INCLUDE_DIRECTORIES (.)


ADD_DEFINITIONS (${PREPROCESSOR_DEF})

TARGET_LINK_LIBRARIES(${AXL_LOCAL}) 
INSTALL (TARGETS ${AXL_LOCAL} DESTINATION ${CMAKE_BINARY_DIR}/build/lib)








