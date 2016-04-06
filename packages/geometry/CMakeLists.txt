# Configure the Geometry_Config.hpp file
SET(CMAKEDEFINE \#cmakedefine)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Geometry_Config.hpp.in
  ${CMAKE_BINARY_DIR}/Geometry_Config.hpp.in)

CONFIGURE_FILE(${CMAKE_BINARY_DIR}/Geometry_Config.hpp.in
  ${CMAKE_BINARY_DIR}/Geometry_Config.hpp)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

# Set up the geometry package directory hierarchy
ADD_SUBDIRECTORY(core)
INCLUDE_DIRECTORIES(core/src)

IF(FRENSIE_ENABLE_ROOT)
  ADD_SUBDIRECTORY(root)
  INCLUDE_DIRECTORIES(root/src)
ENDIF()

IF(FRENSIE_ENABLE_DAGMC)
  ADD_SUBDIRECTORY(dagmc)	
  INCLUDE_DIRECTORIES(damgc/src)
ENDIF()

#ADD_SUBDIRECTORY(native)
#INCLUDE_DIRECTORIES(native/src)

ADD_SUBDIRECTORY(interface)
