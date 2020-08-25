# Configure the SWIG options that will be required in this project. The
# following variables will be set
# 1.)
MACRO(ENABLE_SWIG_SUPPORT)

  SET(SWIG_MIN_VERSION 3.0.0)

  # Add the user supplied SWIG prefix to help find SWIG
  IF(DEFINED SWIG_PREFIX)
    SET(CMAKE_PREFIX_PATH ${SWIG_PREFIX} ${CMAKE_PREFIX_PATH})
  ENDIF()

  # Find the SWIG package available on this system
  FIND_PACKAGE(SWIG ${SWIG_MIN_VERSION} REQUIRED)
  
  # Find the python package available on this system
  FIND_PACKAGE(PythonInterp 2.7 REQUIRED)
  FIND_PACKAGE(PythonLibs 2.7 REQUIRED)

  # Find the numpy package available on this system
  FIND_PACKAGE(NumPy 1.8 REQUIRED)

  IF(CMAKE_VERBOSE_CONFIGURE)
    MESSAGE("Found Python Interpreter! Here are the details: ")
    MESSAGE("  PYTHON_EXECUTABLE = ${PYTHON_EXECUTABLE}")
    MESSAGE("  PYTHON_VERSION = ${PYTHON_VERSION_STRING}")
    MESSAGE("End of Python Interpreter details\n")
    MESSAGE("Found Python Libraries! Here are the details: ")
    MESSAGE("  PYTHON_LIBRARIES = ${PYTHON_LIBRARIES}")
    MESSAGE("  PYTHON_INCLUDE_DIRS = ${PYTHON_INCLUDE_DIRS}")
    MESSAGE("  PYTHONLIBS_VERSION_STRING = ${PYTHONLIBS_VERSION_STRING}")
    MESSAGE("End of Python Library details\n")
    MESSAGE("Found SWIG! Here are the details: ")
    MESSAGE("  SWIG_DIR = ${SWIG_DIR}")
    MESSAGE("  SWIG_EXECUTABLE = ${SWIG_EXECUTABLE}")
    MESSAGE("  SWIG_VERSION = ${SWIG_VERSION}")
    MESSAGE("End of SWIG details\n")
  ENDIF()

ENDMACRO()
