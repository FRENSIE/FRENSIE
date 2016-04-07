# Add a target to generate API documentation with Doxygen
IF(NOT ${DOXYGEN_PREFIX} EQUAL "")
  FIND_FILE(DOXYGEN_EXECUTABLE doxygen
    PATHS ${DOXYGEN_PREFIX} ${DOXYGEN_PREFIX}/bin)
  IF(${DOXYGEN_EXECUTABLE} MATCHES NOTFOUND)
    SET(DOXYGEN_FOUND 0)
    MESSAGE(WARNING "The doxygen executable could not be found in the user "
      "supplied DOXYGEN_PREFIX (${DOXYGEN_PREFIX};${DOXYGEN_PREFIX}/bin). The "
      "system will be searched for the doxygen executable.")
  ELSE()
    SET(DOXYGEN_FOUND 1)
  ENDIF()
ELSE()
  SET(DOXYGEN_FOUND 0)
ENDIF()

IF(NOT DOXYGEN_FOUND)
  FIND_PACKAGE(Doxygen 1.8.0 REQUIRED)
ENDIF()

IF(DOXYGEN_FOUND)

  # Find doxygen depends
  FILE(GLOB_RECURSE DOXYGEN_DEPENDS ${CMAKE_SOURCE_DIR}/packages/*.cpp ${CMAKE_SOURCE_DIR}/packages/*.hpp ${CMAKE_SOURCE_DIR}/packages/*.F90 ${CMAKE_SOURCE_DIR}/packages/*.dox ${CMAKE_SOURCE_DIR}/tools/*.cpp ${CMAKE_SOURCE_DIR}/tools/*.dox *.dox *.in *.bib DoxygenLayout.xml ${CMAKE_SOURCE_DIR}/README.md ${CMAKE_SOURCE_DIR}/LICENSE.md)
  
  # Configure the Doxygen file
  CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

  # Configure the html wrapper file
  CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/manual.html.in ${CMAKE_CURRENT_BINARY_DIR}/manual.html)

  # Configure the IEEEtran_custom format file
  CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/IEEEtran_custom.bst.in ${CMAKE_CURRENT_BINARY_DIR}/IEEEtran_custom.bst)

  # Add a custom doxygen build command
  IF(CMAKE_VERBOSE_CONFIGURE)
    MESSAGE("DOXYGEN_DEPENDS: ${DOXYGEN_DEPENDS}\n")
  ENDIF()
  
  ADD_CUSTOM_COMMAND(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/html
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    DEPENDS ${DOXYGEN_DEPENDS}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating FRENSIE manual with Doxygen" VERBATIM)

  # Add a custom build target
  ADD_CUSTOM_TARGET(manual 
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/html)

  # Install the manuals
  INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/manual.html
    DESTINATION ${CMAKE_INSTALL_PREFIX}/doc/
    PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)

ELSE()
  MESSAGE(FATAL_ERROR "The Doxygen executable could not be found!")
ENDIF()
