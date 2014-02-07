# Add a target to generate API documentation with Doxygen
FIND_PACKAGE(Doxygen)

IF(DOXYGEN_FOUND)
  
  # Configure the Doxygen file
  CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

  # Configure the html wrapper file
  CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/manual.html.in ${CMAKE_CURRENT_BINARY_DIR}/manual.html)

  # Add a custom doxygen build command
  FILE(GLOB DOXYGEN_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.hpp *.dox)

  IF(CMAKE_VERBOSE_CONFIGURE)
    MESSAGE("DOXYGEN_DEPENDS: ${DOXYGEN_DEPENDS}\n")
  ENDIF()
  
  ADD_CUSTOM_COMMAND(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/html
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    DEPENDS ${DOXYGEN_DEPENDS}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating FACEMC manual with Doxygen" VERBATIM)

  # Add a custom build target
  ADD_CUSTOM_TARGET(manual
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/html)
  
  # Find the index.html file if it has been created
  FIND_FILE(INDEX_HTML index.html ${CMAKE_CURRENT_BINARY_DIR}/html)
  IF(NOT ${INDEX_HTML} MATCHES NOTFOUND)
    # Install the manuals
    INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/manual.html
      DESTINATION ${CMAKE_INSTALL_PREFIX}/doc/
      PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)
  ENDIF()

ELSE()
  MESSAGE(FATAL_ERROR "The Doxygen executable could not be found!")
ENDIF()