# This macro adds a custom build command and a custom build target for
# processing the root geometry (*.c -> *.root) if root has been enabled in
# FRENSIE. Otherwise, this macro does nothing
MACRO(FRENSIE_PROCESS_ROOT_GEOM FILE_NAME_BASE)
  SET(options)
  SET(oneValueArgs TARGET_NAME PACKAGE_NAME FILE_NAME_SUFFIX)
  SET(multiValueArgs)
  CMAKE_PARSE_ARGUMENTS(FRENSIE_PROCESS_ROOT_GEOM "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  IF(FRENSIE_ENABLE_ROOT)
    # Check for unused parameters
    IF(NOT "${FRENSIE_PROCESS_ROOT_GEOM_UNPARSED_ARGUMENTS}" STREQUAL "")
      MESSAGE(WARNING "root geom processing unused parameters = ${FRENSIE_PROCESS_ROOT_GEOM_UNPARSED_ARGUMENTS}")
    ENDIF()

    # Check that the target name has been specified
    IF("${FRENSIE_PROCESS_ROOT_GEOM_TARGET_NAME}" STREQUAL "")
      MESSAGE(ERROR "The TARGET_NAME must be specified!" )
    ENDIF()

    # Check that the package name has been specified
    IF("${FRENSIE_PROCESS_ROOT_GEOM_PACKAGE_NAME}" STREQUAL "" )
      MESSAGE(ERROR "The PACKAGE_NAME must be specified!" )
    ENDIF()

    # Construct the file name
    IF(NOT "${FRENSIE_PROCESS_ROOT_GEOM_FILE_NAME_SUFFIX}" STREQUAL "")
      SET(LOCAL_FILE_NAME "${FILE_NAME_BASE}.${FRENSIE_PROCESS_ROOT_GEOM_FILE_NAME_SUFFIX}")
    ELSE()
      SET(LOCAL_FILE_NAME "${FILE_NAME_BASE}.c")
    ENDIF()

    FIND_FILE(FILE_NAME ${LOCAL_FILE_NAME}
      HINTS ${CMAKE_CURRENT_SOURCE_DIR})
    
    # Construct the output name
    SET(LOCAL_OUTPUT_FILE_NAME "${FILE_NAME_BASE}.root")
    
    ADD_CUSTOM_COMMAND(OUTPUT ${LOCAL_OUTPUT_FILE_NAME}
      DEPENDS ${LOCAL_FILE_NAME} ${FRENSIE_PROCESS_ROOT_GEOM_PACKAGE_NAME}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMAND ${ROOT_EXE} ${FILE_NAME})

    ADD_CUSTOM_TARGET(${FRENSIE_PROCESS_ROOT_GEOM_TARGET_NAME} ALL
      DEPENDS ${LOCAL_OUTPUT_FILE_NAME})
   
    UNSET(LOCAL_FILE_NAME)
    UNSET(FILE_NAME CACHE)
    UNSET(LOCAL_OUTPUT_FILE_NAME)

  ENDIF()
    
ENDMACRO(FRENSIE_PROCESS_ROOT_GEOM)
