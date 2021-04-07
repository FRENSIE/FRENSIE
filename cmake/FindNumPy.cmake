# - Find the NumPy libraries
# This module finds if NumPy is installed, and sets the following variables
# indicating where it is.
#
#  NUMPY_FOUND               - was NumPy found
#  NUMPY_VERSION             - the version of NumPy found as a string
#  NUMPY_INCLUDE_DIRS        - path to the NumPy include files

# Finding NumPy involves calling the Python interpreter
IF(NumPy_FIND_REQUIRED)
    IF(NOT PYTHON_EXECUTABLE)
      MESSAGE(FATAL_ERROR "The Python executable needs to be found before NumPy can be found!")
    ENDIF()
ENDIF()

EXECUTE_PROCESS(COMMAND "${PYTHON_EXECUTABLE}" "-c"
  "import numpy as n; print(n.__version__); print(n.get_include());"
  RESULT_VARIABLE _NUMPY_SEARCH_SUCCESS
  OUTPUT_VARIABLE _NUMPY_VALUES_OUTPUT
  ERROR_VARIABLE _NUMPY_ERROR_VALUE
  OUTPUT_STRIP_TRAILING_WHITESPACE)

IF(NOT _NUMPY_SEARCH_SUCCESS MATCHES 0)
  IF(NumPy_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Numpy could not be found! NumPy import failure:\n${_NUMPY_ERROR_VALUE}")
  ENDIF()
  
  SET(NUMPY_FOUND FALSE)
  RETURN()
ENDIF()

# Convert the process output into a list
STRING(REGEX REPLACE ";" "\\\\;" _NUMPY_VALUES ${_NUMPY_VALUES_OUTPUT})
STRING(REGEX REPLACE "\n" ";" _NUMPY_VALUES ${_NUMPY_VALUES})
# Just in case there is unexpected output from the Python command.
LIST(GET _NUMPY_VALUES -2 NUMPY_VERSION)
LIST(GET _NUMPY_VALUES -1 NUMPY_INCLUDE_DIRS)

STRING(REGEX MATCH "^[0-9]+\\.[0-9]+\\.[0-9]+" _VER_CHECK "${NUMPY_VERSION}")
IF("${_VER_CHECK}" STREQUAL "")
  # The output from Python was unexpected. Raise an error always
  # here, because we found NumPy, but it appears to be corrupted somehow.
  MESSAGE(FATAL_ERROR "Numpy could not be found! Requested version and include path from NumPy, got instead:\n${_NUMPY_VALUES_OUTPUT}\n")
  RETURN()
ENDIF()

# Make sure all directory separators are '/'
STRING(REGEX REPLACE "\\\\" "/" NUMPY_INCLUDE_DIRS ${NUMPY_INCLUDE_DIRS})

# Get the version
STRING(REGEX REPLACE "\\." ";" _NUMPY_VERSION_LIST ${NUMPY_VERSION})

# Check that the version is acceptable
IF(NumPy_FIND_VERSION)
  IF(${NUMPY_VERSION} VERSION_LESS ${NumPy_FIND_VERSION})
    MESSAGE(FATAL_ERROR "Numpy version " ${NUMPY_VERSION} " is less than the required version " ${NumPy_FIND_VERSION} "!")
  ENDIF()
ENDIF()

INCLUDE(FindPackageMessage)
FIND_PACKAGE_MESSAGE(NUMPY
  "Found NumPy: version \"${NUMPY_VERSION}\" ${NUMPY_INCLUDE_DIRS}"
  "${NUMPY_INCLUDE_DIRS}${NUMPY_VERSION}")

set(NUMPY_FOUND TRUE)
