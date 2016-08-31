# Compare two compilers to make sure that they are the same
# SAME_VENDOR will store whether the compilers have the same vendor - 0 (false)
#   or 1 (true)
# SAME_VERSION will store whether the compilers have the same version -
#   0 (false) or 1 (true)
FUNCTION(COMPARE_COMPILERS LANG COMPILER1 COMPILER2)

  DETERMINE_COMPILER_ID(${LANG} ${COMPILER1})
  SET(ID1 ${ID})
  SET(VERSION1 ${VERSION})

  DETERMINE_COMPILER_ID(${LANG} ${COMPILER2})
  SET(ID2 ${ID})
  SET(VERSION2 ${VERSION})

  IF(ID1 STREQUAL ID2)
    SET(SAME_VENDOR 1)
  ELSE()
    SET(SAME_VENDOR 0)
  ENDIF()

  IF(VERSION1 STREQUAL VERSION2)
    SET(SAME_VERSION 1)
  ELSEIF(NOT VERSION1 AND NOT VERSION2)
    SET(SAME_VERSION 1)
  ELSE()
    SET(SAME_VERSION 0)
  ENDIF()

  # Return the results of the comparison
  SET(SAME_VENDOR ${SAME_VENDOR} PARENT_SCOPE)
  SET(SAME_VERSION ${SAME_VERSION} PARENT_SCOPE)

ENDFUNCTION(COMPARE_COMPILERS)

FUNCTION(DETERMINE_COMPILER_ID LANG COMPILER)

  # Reset the ID and VERSION variables
  UNSET(ID)
  UNSET(VERSION)

  SET(CMAKE_${LANG}_COMPILER_ID_DIR "${CMAKE_PLATFORM_INFO_DIR}/CompilerId${LANG}")
  IF(LANG STREQUAL "CXX")
    SET(EXT "cpp")
  ELSEIF(LANG STREQUAL "C")
    SET(EXT "c")
  ELSEIF(LANG STREQUAL "Fortran")
    SET(EXT "F")
  ELSE()
    MESSAGE(FATAL_ERROR "Invalid language found while attempting to determine ${COMPILER} compiler info!")
  ENDIF()

  SET(TEST_SRC "CMake${LANG}CompilerId.${EXT}")
  SET(TEST_EXE "test.o")
  SET(TEST_FLAGS "-o")

  SET(CMAKE_${LANG}_COMPILER_ID_OUTPUT)
  SET(CMAKE_${LANG}_COMPILER_ID_ERROR)
  SET(CMAKE_${LANG}_COMPILER_ID_RESULT)
  EXECUTE_PROCESS(COMMAND ${COMPILER} ${TEST_FLAGS} ${TEST_EXE} ${TEST_SRC}
                  WORKING_DIRECTORY ${CMAKE_${LANG}_COMPILER_ID_DIR}
		  OUTPUT_VARIABLE CMAKE_${LANG}_COMPILER_ID_OUTPUT
		  ERROR_VARIABLE CMAKE_${LANG}_COMPILER_ID_ERROR
		  RESULT_VARIABLE CMAKE_${LANG}_COMPILER_ID_RESULT)

  # Check the result of compilation
  IF(CMAKE_${LANG}_COMPILER_ID_RESULT)
    MESSAGE(FATAL_ERROR "Unable to determine ${COMPILER} compiler info!")
  ENDIF()

  SET(TEST_EXE "${CMAKE_${LANG}_COMPILER_ID_DIR}/${TEST_EXE}")

  # Check the executable for the compiler info
  FILE(STRINGS ${TEST_EXE}
       ${LANG}_COMPILER_ID_STRINGS LIMIT_COUNT 4 REGEX "INFO:")
  FOREACH(INFO ${${LANG}_COMPILER_ID_STRINGS})
    # Get the compiler info
    IF("${INFO}" MATCHES ".*INFO:compiler\\[([^]\"]*)\\].*")
      IF(ID)
	SET(COMPILER_ID_TWICE 1)
      ENDIF()
      STRING(REGEX REPLACE ".*INFO:compiler\\[([^]]*)\\].*" "\\1"
    	     ID "${INFO}")
    ENDIF()

    # Get the version info
    IF("${INFO}" MATCHES ".*INFO:compiler_version\\[([^]\"]*)\\].*")
       STRING(REGEX REPLACE ".*INFO:compiler_version\\[([^]]*)\\].*" "\\1" VERSION "${INFO}")
       STRING(REGEX REPLACE "^0+([0-9])" "\\1" VERSION "${VERSION}")
       STRING(REGEX REPLACE "\\.0+([0-9])" ".\\1" VERSION "${VERSION}")
    ENDIF()
  ENDFOREACH()

  # Check if a valid compiler was found
  IF(NOT ID OR COMPILER_ID_TWICE)
    MESSAGE(FATAL_ERROR "Unable to determine ${COMPILER} compiler info!")
  ENDIF()

  # Return the ID and VERSION
  SET(ID ${ID} PARENT_SCOPE)
  SET(VERSION ${VERSION} PARENT_SCOPE)

ENDFUNCTION(DETERMINE_COMPILER_ID)

# ELSE()
    # Find the executables produced by the compiler
    # FILE(GLOB COMPILER_FILES
    #     ${CMAKE_${LANG}_COMPILER_ID_DIR}/*)
    # LIST(REMOVE_ITEM COMPILER_FILES "${CMAKE_${LANG}_COMPILER_ID_DIR}/${TEST_SRC}")

    # FOREACH(FILE ${COMPILER_FILES})
    #   IF(IS_DIRECTORY ${CMAKE_${LANG}_COMPILER_ID_DIR}/${FILE})
    #     LIST(REMOVE_ITEM COMPILER_FILES ${FILE})
    #   ENDIF()
    # ENDFOREACH()

    # IF(NOT COMPILER_FILES)
    #   MESSAGE(FATAL_ERROR "Unable to determine ${COMPILER} compiler info!")
    # ENDIF()

# FOREACH(FILE ${COMPILER_FILES})
    # IF(NOT ID)
   # ENDIF()
  # ENDFOREACH()