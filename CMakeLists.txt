cmake_minimum_required (VERSION 3.1)

project (gphoto2pp)
set (CMAKE_CXX_STANDARD 11)

set(GPHOTO2PP_VERSION_MAJOR 0)
set(GPHOTO2PP_VERSION_MINOR 1)
set(GPHOTO2PP_VERSION_PATCH 2)
set(GPHOTO2PP_VERSION "${GPHOTO2PP_VERSION_MAJOR}.${GPHOTO2PP_VERSION_MINOR}.${GPHOTO2PP_VERSION_PATCH}")
set(GPHOTO2PP_VERSION_STRING "${GPHOTO2PP_VERSION}")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules/)

find_package( Gphoto2 REQUIRED )

include_directories(${Gphoto2_INCLUDE_DIRS})

# base path of where binaries should be built
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
# where the library will be built to
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/libs)

############
# gphoto2pp
############
FILE(GLOB GPHOTO2PP_SOURCE_FILES "src/*.cpp")
FILE(GLOB GPHOTO2PP_HPPHEADER_FILES "include/gphoto2pp/*.hpp")
FILE(GLOB GPHOTO2PP_HEADER_FILES "include/gphoto2pp/*.h")

set(GPHOTO2PP_SOURCES ${GPHOTO2PP_SOURCE_FILES})
set(GPHOTO2PP_HEADERS ${GPHOTO2PP_HPPHEADER_FILES} ${GPHOTO2PP_HEADER_FILES})

add_library( gphoto2pp SHARED ${GPHOTO2PP_SOURCES})

target_link_libraries( gphoto2pp ${Gphoto2_LIBRARIES} )
include_directories("include")

# sets the shared library version
# http://cmake.3232098.n2.nabble.com/Version-in-name-of-shared-library-td7581530.html
set_target_properties( gphoto2pp PROPERTIES VERSION ${GPHOTO2PP_VERSION_STRING} SOVERSION ${GPHOTO2PP_VERSION_MAJOR} )

install( TARGETS gphoto2pp DESTINATION lib )
install( FILES ${GPHOTO2PP_HEADERS} DESTINATION include/gphoto2pp )

###########
# Examples
###########
add_subdirectory( examples )

#############
# Unit Tests
#############
# for now only add unit tests in dev mode
if(CMAKE_BUILD_TYPE MATCHES "DEBUG")
    enable_testing()
    add_subdirectory( tests )
endif(CMAKE_BUILD_TYPE MATCHES "DEBUG")

###############################
# Docs generation with Doxygen
###############################
    find_package( Doxygen )
    if( DOXYGEN_FOUND )
        add_custom_target (docs ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Generating source code documentation with Doxygen." VERBATIM)
    endif()

###################
# uninstall target
###################
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
