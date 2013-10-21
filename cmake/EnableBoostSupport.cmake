# Configure the Boost options that will be required in this project. The
# following variables will be set:
# 1.)
MACRO(ENABLE_BOOST_SUPPORT)

  # Usethe user supplied prefix to find the Boost libraries and include dirs.
  SET(BOOST_INCLUDE_DIRS ${BOOST_PREFIX}/include/boost)
  SET(BOOST_LIBRARY_DIRS ${BOOST_PREFIX}/lib)

  # Set the include paths for Boost
  INCLUDE_DIRECTORIES(${BOOST_INCLUDE_DIRS})
  
  # Set the link paths for Boost
  LINK_DIRECTORIES(${BOOST_LIBRARY_DIRS})
  
  # Echo the Boost details if a verbose configure was requested
  IF(CMAKE_VERBOSE_CONFIGURE)
    MESSAGE("Found BOOST! Here are the details: ")
    MESSAGE(" BOOST_PREFIX = ${BOOST_PREFIX}")
    MESSAGE(" BOOST_INCLUDE_DIRS = ${BOOST_INCLUDE_DIRS}")
    MESSAGE(" BOOST_LIBRARY_DIRS = ${BOOST_LIBRARY_DIRS}")
    MESSAGE("End of BOOST details\n")
  ENDIF()

ENDMACRO(ENABLE_BOOST_SUPPORT)