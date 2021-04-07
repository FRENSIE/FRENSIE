# Set the PyFrensie Version
SET(PyFrensie_VERSION ${FRENSIE_VERSION})

# Set the PyFrensie Install directory
SET(PyFrensie_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib/python2.7/site-packages/PyFrensie")

# Use the Trilinos UseSWIG.cmake file
INCLUDE(${CMAKE_SOURCE_DIR}/cmake/UseSWIG.cmake)

# Set up the include paths
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})
INCLUDE_DIRECTORIES(${NUMPY_INCLUDE_DIRS})
  
# Set up the directory hierarchy
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)
