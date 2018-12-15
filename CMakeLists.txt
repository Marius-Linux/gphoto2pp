cmake_minimum_required (VERSION 3.1)

project (gphoto2pp)
set (CMAKE_CXX_STANDARD 11)

set(GPHOTO2PP_VERSION_MAJOR 0)
set(GPHOTO2PP_VERSION_MINOR 3)
set(GPHOTO2PP_VERSION_PATCH 0)
set(GPHOTO2PP_VERSION "${GPHOTO2PP_VERSION_MAJOR}.${GPHOTO2PP_VERSION_MINOR}.${GPHOTO2PP_VERSION_PATCH}")
set(GPHOTO2PP_VERSION_STRING "${GPHOTO2PP_VERSION}")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules/)

find_package( Gphoto2 REQUIRED )


set(DEST_DIR ${CMAKE_INSTALL_PREFIX})
CONFIGURE_FILE("libgphoto2pp.pc.in" "libgphoto2pp.pc" @ONLY)

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
target_include_directories(gphoto2pp PUBLIC "include")

set_target_properties( gphoto2pp PROPERTIES VERSION ${GPHOTO2PP_VERSION_STRING} SOVERSION ${GPHOTO2PP_VERSION_MAJOR} )
set_target_properties(gphoto2pp PROPERTIES PUBLIC_HEADER "${GPHOTO2PP_HEADERS}")

include_directories(${Gphoto2_INCLUDE_DIRS})

install( TARGETS gphoto2pp DESTINATION lib
		 PUBLIC_HEADER DESTINATION include/gphoto2pp)
install(FILES ${CMAKE_BINARY_DIR}/libgphoto2pp.pc DESTINATION share/pkgconfig)

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
