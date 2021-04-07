# Turns ZAID.xxA to ZAID_XXA (only to be used locally
MACRO(__PARSE_ACE_LIBRARY_NAME ACE_LIBRARY_NAME CACHED_ACE_LIBRARY_NAME)
  STRING(REPLACE "." "_" ${CACHED_ACE_LIBRARY_NAME} "__${ACE_LIBRARY_NAME}")
ENDMACRO()

# Set the ACE library availability (only to be used locally)
#  If the availability is true, the library file path and file start line must
#  also be specified.
#
#  Sets the variable ZAID_##A_AVAILABLE. If ZAID_##A_AVAILABLE is TRUE,
#  ZAID_##A_FILE_PATH and ZAID_##A_FILE_START_LINE will also be set.
MACRO(__SET_ACE_LIBRARY_AVAILABILITY ACE_LIBRARY_NAME ACE_LIBRARY_AVAILABLE)
  SET(options)
  SET(oneValueArgs ACE_LIBRARY_FILE_PATH ACE_LIBRARY_FILE_START_LINE)
  SET(multiValueArgs)
  CMAKE_PARSE_ARGUMENTS(__SET_ACE_LIBRARY_AVAILABILITY "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  # Check for unused parameters
  IF(NOT "${__SET_ACE_LIBRARY_AVAILABILITY_UNPARSED_ARGUMENTS}" STREQUAL "")
    MESSAGE(WARNING "__SET_ACE_LIBRARY_AVAILABILITY unused parameters = ${__SET_ACE_LIBRARY_AVAILABILITY_UNPARSED_ARGUMENTS}")
  ENDIF()

  # Parse the ACE library name
  __PARSE_ACE_LIBRARY_NAME("${ACE_LIBRARY_NAME}" CACHED_ACE_LIBRARY_NAME)

  IF(${ACE_LIBRARY_AVAILABLE})
    # Check that the file path and file start line have been specified if the
    # library is available
    IF("${__SET_ACE_LIBRARY_AVAILABILITY_ACE_LIBRARY_FILE_PATH}" STREQUAL "")
      MESSAGE(FATAL_ERROR "ACE library ${ACE_LIBRARY_NAME} has been specified as available - the file path must be specified!")
    ENDIF()

    IF("${__SET_ACE_LIBRARY_AVAILABILITY_ACE_LIBRARY_FILE_START_LINE}" STREQUAL "")
      MESSAGE(FATAL_ERROR "ACE library ${ACE_LIBRARY_NAME} has been specified as available - the file start line must be specified!")
    ELSEIF(${__SET_ACE_LIBRARY_AVAILABILITY_ACE_LIBRARY_FILE_START_LINE} LESS 1)
      MESSAGE(FATAL_ERROR "ACE library ${ACE_LIBRARY_NAME} has an invalid file start line (must be >= 1)!")
    ENDIF()

    SET(${CACHED_ACE_LIBRARY_NAME}_AVAILABLE TRUE CACHE BOOL "Availability of requested ACE library ${ACE_LIBRARY_NAME}")
    SET(${CACHED_ACE_LIBRARY_NAME}_FILE_PATH "${__SET_ACE_LIBRARY_AVAILABILITY_ACE_LIBRARY_FILE_PATH}" CACHE STRING "Name and path of the file that contains requested ACE library ${ACE_LIBRARY_NAME}")
    SET(${CACHED_ACE_LIBRARY_NAME}_FILE_START_LINE "${__SET_ACE_LIBRARY_AVAILABILITY_ACE_LIBRARY_FILE_START_LINE}" CACHE STRING "Line in the file where the requested ACE library ${ACE_LIBRARY_NAME} starts")
  ELSE()
    SET(${CACHED_ACE_LIBRARY_NAME}_AVAILABLE FALSE CACHE BOOL "Availability of requested ACE library ${ACE_LIBRARY_NAME}")
  ENDIF()
  
ENDMACRO()

# Replace ACE placeholder arguments in a string. Placeholder arguments are
# acelibname:available, acelibname:filepath and acelibname:filestartline.
# If the requested ACE library is available the placeholder arguments will
# be replaced as follows:
#  1001.70c:available     -> true
#  1001.70c:filepath      -> /home/usr/mcnpdata/neutron/H.txt
#  1001.70c:filestartline -> 1
# If a requested library is not available the placeholder arguments will be
# replaced as follows:
#  1001.70c:available     -> false
#  1001.70c:filepath      -> ''
#  1001.70c:filestartline -> -1
#
# Example usage:
#
#  SET(MY_TARGET_STRING "--program_arg=1001.70c:filepath")
#  REPLACE_ACE_PLACEHOLDER_ARGS(MY_TARGET_STRING)
#
#  SET(MY_TARGET_STRING "--program_arg=1001.70c:filepath")
#  REPLACE_ACE_PLACEHOLDER_ARGS(MY_TARGET_STRING
#    LIBRARY_NAMES 1001.70c)
#   
MACRO(REPLACE_ACE_PLACEHOLDER_ARGS TARGET_STRING)
  SET(options)
  SET(oneValueArgs)
  SET(multiValueArgs LIBRARY_NAMES)
  CMAKE_PARSE_ARGUMENTS(REPLACE_ACE_PLACEHOLDER_ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  # Check for unused parameters
  IF(NOT "${REPLACE_ACE_PLACEHOLDER_ARGS_UNPARSED_ARGUMENTS}" STREQUAL "")
    MESSAGE(WARNING "REPLACE_ACE_PLACEHOLDER_ARGS unused parameters = ${REPLACE_ACE_PLACEHOLDER_ARGS_UNPARSED_ARGUMENTS}")
  ENDIF()

  # Check if specific library names were specified
  IF(NOT "${REPLACE_ACE_PLACEHOLDER_ARGS_LIBRARY_NAMES}" STREQUAL "")
    SET(LIBRARY_NAMES_TO_USE ${REPLACE_ACE_PLACEHOLDER_ARGS_LIBRARY_NAMES})
  ELSE()
    SET(LIBRARY_NAMES_TO_USE ${CACHED_REQUESTED_ACE_LIBRARY_NAMES})
  ENDIF()

  FOREACH(LIBRARY_NAME ${LIBRARY_NAMES_TO_USE})
    IS_ACE_LIBRARY_AVAILABLE(${LIBRARY_NAME} IS_LIB_AVAILABLE)
    #MESSAGE("${LIBRARY_NAME}:${IS_LIB_AVAILABLE}")
    STRING(TOLOWER ${IS_LIB_AVAILABLE} IS_LIB_AVAILABLE)
    GET_ACE_LIBRARY_FILE_PATH(${LIBRARY_NAME} ACE_LIB_FILE_PATH)
    GET_ACE_LIBRARY_FILE_START_LINE(${LIBRARY_NAME} ACE_LIB_FILE_START_LINE)

    STRING(REPLACE "${LIBRARY_NAME}:available" "${IS_LIB_AVAILABLE}" ${TARGET_STRING} "${${TARGET_STRING}}")
    STRING(REPLACE "${LIBRARY_NAME}:filepath" "${ACE_LIB_FILE_PATH}" ${TARGET_STRING} "${${TARGET_STRING}}")
    STRING(REPLACE "${LIBRARY_NAME}:filestartline" "${ACE_LIB_FILE_START_LINE}" ${TARGET_STRING} "${${TARGET_STRING}}")
  ENDFOREACH()
ENDMACRO()

# Find the location of the requested ACE libraries by parsing the specified
# xsdir file. If a requested library is found the following variables will be
# set and cached (library name = 1001.70c):
#  __1001_70c_AVAILABLE__:BOOL=TRUE
#  __1001_70c_FILE_PATH__:STRING=/home/usr/mcnpdata/neutron/H.txt
#  __1001_70c_FILE_START_LINE__:STRING=1
# If a requested library is not found a warning will be displayed and the
# following variable will be set and cached (library name = 1001.70c):
#  __1001_70c_AVAILABLE__:BOOL=FALSE
#
# Example usage:
#
#  FIND_ACE_LIBRARIES("/home/usr/mcnpdata/xsdir"
#    LIBRARY_NAMES 1001.70c 1002.80c 8016.70c 82208.80c lwtr.10t)
#
MACRO(FIND_ACE_LIBRARIES XSDIR)
  SET(options)
  SET(oneValueArgs)
  SET(multiValueArgs LIBRARY_NAMES)
  CMAKE_PARSE_ARGUMENTS(FIND_ACE_LIBRARIES "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  # Check for unused parameters
  IF(NOT "${FIND_ACE_LIBRARIES_UNPARSED_ARGUMENTS}" STREQUAL "")
    MESSAGE(WARNING "FIND_ACE_LIBRARIES unused parameters = ${FIND_ACE_LIBRARIES_UNPARSED_ARGUMENTS}")
  ENDIF()

  # Check if this xsdir file has already been parsed
  IF(NOT DEFINED XSDIR_CHECK)
    
    # Check if the user specified xsdir file exists
    MESSAGE("-- Checking if xsdir file ${XSDIR} exists")
    GET_FILENAME_COMPONENT(XSDIR_DIR ${XSDIR} DIRECTORY CACHE)
    GET_FILENAME_COMPONENT(XSDIR_FILE ${XSDIR} NAME CACHE)
    FIND_FILE(XSDIR_CHECK ${XSDIR_FILE} ${XSDIR_DIR})
    MESSAGE("-- Checking if xsdir file ${XSDIR} exists - done")

    IF(NOT EXISTS ${XSDIR_CHECK})
      MESSAGE(WARNING "The xsdir file ${XSDIR} does not exist!")
    ENDIF()
  ENDIF()

  # Remove duplicates library names from the list
  LIST(REMOVE_DUPLICATES FIND_ACE_LIBRARIES_LIBRARY_NAMES)

  # Create a copy of the list that is sorted
  SET(REQUESTED_ACE_LIBRARY_NAMES ${FIND_ACE_LIBRARIES_LIBRARY_NAMES})
  LIST(SORT REQUESTED_ACE_LIBRARY_NAMES)

  # Check if this list has been requested before
  IF(NOT DEFINED CACHED_REQUESTED_ACE_LIBRARY_NAMES OR NOT "${REQUESTED_ACE_LIBRARY_NAMES}" STREQUAL "${CACHED_REQUESTED_ACE_LIBRARY_NAMES}")

    # Cache the requested library names
    SET(CACHED_REQUESTED_ACE_LIBRARY_NAMES "${REQUESTED_ACE_LIBRARY_NAMES}" CACHE STRING "requested ACE library names" FORCE)

    IF(EXISTS ${XSDIR_CHECK})
      
      # Load the xsdir file
      FILE(READ ${XSDIR_DIR}/${XSDIR_FILE} XSDIR_FILE_CONTENTS)
      
      # Split the lines into individual elements
      STRING(REGEX REPLACE ";" "\\\\;" XSDIR_FILE_CONTENTS "${XSDIR_FILE_CONTENTS}")
      STRING(REGEX REPLACE "\n" ";" XSDIR_FILE_CONTENTS "${XSDIR_FILE_CONTENTS}")
      
      # Loop through each line and check if the line describes one of the
      # required libraries
      FOREACH(XSDIR_LINE ${XSDIR_FILE_CONTENTS})
        STRING(STRIP "${XSDIR_LINE}" XSDIR_LINE)
        STRING(REGEX REPLACE "[ \t\r]+" ";" XSDIR_LINE "${XSDIR_LINE}")
        
        LIST(GET XSDIR_LINE 0 XSDIR_LINE_FRONT)
        LIST(FIND FIND_ACE_LIBRARIES_LIBRARY_NAMES "${XSDIR_LINE_FRONT}" MATCHED_LIBRARY_NAME_INDEX)
        
        # One of the requested libraries was found
        IF(MATCHED_LIBRARY_NAME_INDEX GREATER "-1")
          
          LIST(GET XSDIR_LINE 2 XSDIR_LINE_RELATIVE_FILE_PATH)
          LIST(GET XSDIR_LINE 5 XSDIR_LINE_FILE_START_LINE)
          
          __SET_ACE_LIBRARY_AVAILABILITY("${XSDIR_LINE_FRONT}" TRUE
            ACE_LIBRARY_FILE_PATH "${XSDIR_DIR}/${XSDIR_LINE_RELATIVE_FILE_PATH}"
            ACE_LIBRARY_FILE_START_LINE ${XSDIR_LINE_FILE_START_LINE})
          
          LIST(REMOVE_AT FIND_ACE_LIBRARIES_LIBRARY_NAMES ${MATCHED_LIBRARY_NAME_INDEX})
        ENDIF()
      ENDFOREACH()
    ENDIF()
    
    # Any remaining libraries are unavailable
    FOREACH(UNAVAILABLE_LIBRARY ${FIND_ACE_LIBRARIES_LIBRARY_NAMES})
      MESSAGE(WARNING "Requested ACE Library ${UNAVAILABLE_LIBRARY} could not be found in the xsdir file ${XSDIR}")
      __SET_ACE_LIBRARY_AVAILABILITY("${UNAVAILABLE_LIBRARY}" FALSE)
    ENDFOREACH()

  ENDIF()
ENDMACRO()

# Check if the requested ACE library is available
MACRO(IS_ACE_LIBRARY_AVAILABLE ACE_LIBRARY_NAME IS_AVAILABLE)
  __PARSE_ACE_LIBRARY_NAME(${ACE_LIBRARY_NAME} CACHED_ACE_LIBRARY_NAME)

  IF(NOT DEFINED ${CACHED_ACE_LIBRARY_NAME}_AVAILABLE)
    SET(${IS_AVAILABLE} FALSE)
  ELSE()
    SET(${IS_AVAILABLE} ${${CACHED_ACE_LIBRARY_NAME}_AVAILABLE})
  ENDIF()

  UNSET(CACHED_ACE_LIBRARY_NAME)
ENDMACRO()

# Get the requested ACE Library file path
MACRO(GET_ACE_LIBRARY_FILE_PATH ACE_LIBRARY_NAME FILE_PATH)
  __PARSE_ACE_LIBRARY_NAME(${ACE_LIBRARY_NAME} CACHED_ACE_LIBRARY_NAME)

  IF(NOT DEFINED ${CACHED_ACE_LIBRARY_NAME}_AVAILABLE)
    SET(${FILE_PATH} "undefined")
  ELSEIF(NOT ${CACHED_ACE_LIBRARY_NAME}_AVAILABLE)
    SET(${FILE_PATH} "undefined")
  ELSE()
    SET(${FILE_PATH} ${${CACHED_ACE_LIBRARY_NAME}_FILE_PATH})
  ENDIF()

  UNSET(CACHED_ACE_LIBRARY_NAME)
ENDMACRO()

# Get the requested ACE Library file start line
MACRO(GET_ACE_LIBRARY_FILE_START_LINE ACE_LIBRARY_NAME FILE_START_LINE)
  __PARSE_ACE_LIBRARY_NAME(${ACE_LIBRARY_NAME} CACHED_ACE_LIBRARY_NAME)

  IF(NOT DEFINED ${CACHED_ACE_LIBRARY_NAME}_AVAILABLE)
    SET(${FILE_START_LINE} "-1")
  ELSEIF(NOT ${CACHED_ACE_LIBRARY_NAME}_AVAILABLE)
    SET(${FILE_START_LINE} "-1")
  ELSE()
    SET(${FILE_START_LINE} ${${CACHED_ACE_LIBRARY_NAME}_FILE_START_LINE})
  ENDIF()

  UNSET(CACHED_ACE_LIBRARY_NAME)
ENDMACRO()


