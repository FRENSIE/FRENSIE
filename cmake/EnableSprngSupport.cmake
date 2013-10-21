# Configure the Sprng options that will be required in this project. The
# following variables will be set:
# 1.)
MACRO(ENABLE_SPRNG_SUPPORT)

  # Use the user supplied prefix to find the Sprng library and include dir
  SET(SPRNG_INCLUDE_DIRS ${SPRNG_PREFIX}/include)
  SET(SPRNG_LIBRARY_DIRS ${SPRNG_PREFIX}/lib)

  # Set the include paths for Sprng
  INCLUDE_DIRECTORIES(${SPRNG_INCLUDE_DIRS})
  
  # Set the link paths for Sprng
  LINK_DIRECTORIES(${SPRNG_LIBRARY_DIRS})

  # Echo the Sprng details if a verbose configure was requested
  IF(CMAKE_VERBOSE_CONFIGURE)
    MESSAGE("Found SPRNG! Here are the details: ")
    MESSAGE(" SPRNG_PREFIX = ${SPRNG_PREFIX}")
    MESSAGE(" SPRNG_INCLUDE_DIRS = ${SPRNG_INCLUDE_DIRS}")
    MESSAGE(" SPRNG_LIBRARY_DIRS = ${SPRNG_LIBRARY_DIRS}")
    MESSAGE("End of SPRNG details\n")
  ENDIF()

ENDMACRO(ENABLE_SPRNG_SUPPORT)