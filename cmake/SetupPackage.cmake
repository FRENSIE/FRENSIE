##---------------------------------------------------------------------------##
## Setup a FRENSIE package
##---------------------------------------------------------------------------##
## Usage examples:
##
##   FRENSIE_SETUP_PACKAGE(utility_core
##     MPI_LIBRARIES ${MPI_CXX_LIBRARIES}
##     NON_MPI_LIBRARIES ${Boost_LIBRARIES}
##     SET_VERBOSE ${CMAKE_VERBOSE_CONFIGURE})
##
##   FRENSIE_SETUP_PACKAGE(utility_core
##     MPI_LIBRARIES ${MPI_CXX_LIBRARIES}
##     NON_MPI_LIBRARIES ${Boost_LIBRARIES}
##     VERBOSE)
##
##   FRENSIE_SETUP_PACKAGE(utility_core
##     MPI_LIBRARIES ${MPI_CXX_LIBRARIES}
##     NON_MPI_LIBRARIES ${Boost_LIBRARIES})
##
##   FRENSIE_SETUP_PACKAGE(utility_core
##     NON_MPI_LIBRARIES ${Boost_LIBRARIES})
## 
MACRO(FRENSIE_SETUP_PACKAGE PACKAGE_NAME)
  SET(options VERBOSE)
  SET(oneValueArgs SET_VERBOSE)
  SET(multiValueArgs MPI_LIBRARIES NON_MPI_LIBRARIES)
  CMAKE_PARSE_ARGUMENTS(FRENSIE_SETUP_PACKAGE "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  # Check for unused parameters
  IF(NOT "${FRENSIE_SETUP_PACKAGE_UNPARSED_ARGUMENTS}" STREQUAL "")
    MESSAGE(WARNING "${PACKAGE_NAME} unused parameters = ${FRENSIE_SETUP_PACKAGE_UNPARSED_ARGUMENTS}")
  ENDIF()

  # Gather the headers and source files present in the package directory
  FILE(GLOB ${PACKAGE_NAME}_HEADERS *.hpp)
  FILE(GLOB ${PACKAGE_NAME}_SOURCES *.cpp *.F90)

  # Display details if a verbose configure has been requested
  SET(VERBOSE_CONFIGURE_REQUIRED ${FRENSIE_SETUP_PACKAGE_VERBOSE})

  IF(NOT "${FRENSIE_SETUP_PACKAGE_SET_VERBOSE}" STREQUAL "")
    IF(${FRENSIE_SETUP_PACKAGE_SET_VERBOSE})
      SET(VERBOSE_CONFIGURE_REQUIRED ${FRENSIE_SETUP_PACKAGE_SET_VERBOSE})
    ENDIF()
  ENDIF()

  IF(${VERBOSE_CONFIGURE_REQUIRED})
    MESSAGE("${PACKAGE_NAME} details...")
    
    SET(INDEX 0)
    MESSAGE("  ${PACKAGE_NAME} mpi libraries:")
    FOREACH(mpi_library ${FRENSIE_SETUP_PACKAGE_MPI_LIBRARIES})
      MESSAGE("    ${INDEX}.) ${mpi_library}")
      MATH(EXPR INDEX "${INDEX}+1")
    ENDFOREACH()

    SET(INDEX 0)
    MESSAGE("  ${PACKAGE_NAME} non-mpi libraries:")
    FOREACH(non_mpi_library ${FRENSIE_SETUP_PACKAGE_NON_MPI_LIBRARIES})
      MESSAGE("    ${INDEX}.) ${non_mpi_library}")
      MATH(EXPR INDEX "${INDEX}+1")
    ENDFOREACH()

    SET(INDEX 0)
    MESSAGE("  ${PACKAGE_NAME} headers:")
    FOREACH(header_file ${${PACKAGE_NAME}_HEADERS})
      MESSAGE("    ${INDEX}.) ${header_file}")
      MATH(EXPR INDEX "${INDEX}+1")
    ENDFOREACH()

    SET(INDEX 0)
    MESSAGE("  ${PACKAGE_NAME} sources:")
    FOREACH(source_file ${${PACKAGE_NAME}_SOURCES})
      MESSAGE("    ${INDEX}.) ${source_file}")
      MATH(EXPR INDEX "${INDEX}+1")
    ENDFOREACH()

    UNSET(INDEX)
  ENDIF()

  UNSET(VERBOSE_CONFIGURE_REQUIRED)

  # Create the package library from the package sources
  ADD_LIBRARY(${PACKAGE_NAME} ${${PACKAGE_NAME}_SOURCES})

  # Only link the non-MPI libraries if they are specified
  IF(NOT "${FRENSIE_SETUP_PACKAGE_NON_MPI_LIBRARIES}" STREQUAL "")
    TARGET_LINK_LIBRARIES(${PACKAGE_NAME} ${FRENSIE_SETUP_PACKAGE_NON_MPI_LIBRARIES})
  ENDIF()

  # Only link the MPI libraries if they are specified
  IF(NOT "${FRENSIE_SETUP_PACKAGE_MPI_LIBRARIES}" STREQUAL "")
    TARGET_LINK_LIBRARIES(${PACKAGE_NAME} ${MPI_LIBRARIES})
  ENDIF()

  # Set install paths for the package targets
  INSTALL(TARGETS ${PACKAGE_NAME}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
  INSTALL(FILES ${${PACKAGE_NAME}_HEADERS}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include
    PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)

ENDMACRO(FRENSIE_SETUP_PACKAGE)
