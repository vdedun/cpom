cmake_minimum_required( VERSION 3.0 FATAL_ERROR )

project( CPOM VERSION 0.1 LANGUAGES CXX )

# Set compilation option where supported
if ( "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" OR CMAKE_COMPILER_IS_GNUCXX )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic" )
	set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3" )
endif ()

# Add a target to generate API documentation with Doxygen
find_package( Doxygen )
if ( DOXYGEN_FOUND )
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doc/Doxyfile @ONLY)
    add_custom_target( doc
    				   ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doc/Doxyfile
    				   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Doc
                       COMMENT "Generating API documentation with Doxygen" VERBATIM )
endif ( DOXYGEN_FOUND )

# External header-only dependencies
include_directories( extern )

# Support Cmake Tools Integration
include(CMakeToolsHelpers OPTIONAL)

# Library target
add_library( cpom STATIC src/ClosestPointQuery.cpp )

# Define headers for the library
target_include_directories(cpom
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

# Require a C++11 compiler
target_compile_features(cpom PUBLIC cxx_constexpr PRIVATE cxx_auto_type)

# Test target
enable_testing()

add_executable( cpom_ut test/ClosestPointQuery.ut.cpp
                        test/OctreeNode.ut.cpp
                        test/TestDriver.cpp )
target_link_libraries( cpom_ut cpom )

add_test( NAME cpom_test
          COMMAND ${CMAKE_BINARY_DIR}/cpom_ut
          WORKING_DIRECTORY ${CMAKE_BINARY_DIR} )

# Install to the correct location
install(TARGETS cpom
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

install(DIRECTORY include/ DESTINATION include)
