cmake_minimum_required(VERSION 3.16)

set(TARGET valor-std)
project(${TARGET})

# Global vars
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(OUTPUT_LIB_DIR $<1:${LIB_DIR}>) # $<1:> to remove Debug/Release subdirs
set(LIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CMAKE_BUILD_TYPE "")

# Check for library type [STATIC | SHARED]
if(NOT DEFINED LIB_TYPE)
	message("LIB_TYPE variable is not defined. Setting STATIC by default")
	# If library type is not defined, then set static by default
	set(LIB_TYPE STATIC)
else()
	string(TOUPPER ${LIB_TYPE} LIB_TYPE) # Convert to upper case
	if(NOT (${LIB_TYPE} MATCHES STATIC OR ${LIB_TYPE} MATCHES SHARED) )
		message("\'${LIB_TYPE}\' is not currently supported")
	endif()
endif()

# Set flags according to the OS
if(WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++20 /Zc:preprocessor")
elseif(UNIX AND NOT APPLE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++2a")
else()
	message(FATAL_ERROR "Current OS is not supported!")
endif()

# Reserved for future
include_directories(${LIB_INCLUDE_DIR})

# Change output directory for library
if(${LIB_TYPE} MATCHES STATIC)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_LIB_DIR})
else()
	# On Windows RUNTIME_OUTPUT_DIRECTORY should be used for shared libraries
	if(WIN32)
		set(CMAKE_PDB_OUTPUT_DIRECTORY ${OUTPUT_LIB_DIR})
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_LIB_DIR})
	else()
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_LIB_DIR})
	endif()
endif()

add_subdirectory(src)
add_subdirectory(tests)