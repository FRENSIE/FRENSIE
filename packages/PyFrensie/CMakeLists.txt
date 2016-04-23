# Set the PyFrensie Version
SET(PyFrensie_VERSION ${FRENSIE_VERSION})

# Set the PyFrensie Install directory
SET(PyFrensie_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib/python2.7/site-packages/PyFrensie")

# Use the local UseSWIG.cmake file
#INCLUDE(${CMAKE_SOURCE_DIR}/cmake/UseSWIG.cmake)

# Use the Trilinos UseSWIG.cmake file
INCLUDE(${PYTRILINOS_CMAKE_DIR_PATH}/UseSWIG.cmake) 

# Find the python package available on this system
FIND_PACKAGE(PythonInterp 2.7 REQUIRED)
FIND_PACKAGE(PythonLibs 2.7 REQUIRED)

# Find the numpy package available on this system
FIND_PACKAGE(NumPy 1.8 REQUIRED)

# Set up the include paths
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})
INCLUDE_DIRECTORIES(${NUMPY_INCLUDE_DIRS})

# Set up the directory hierarchy
ADD_SUBDIRECTORY(src)