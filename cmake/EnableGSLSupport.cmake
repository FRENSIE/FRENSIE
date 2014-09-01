
MACRO(ENABLE_GSL_SUPPORT)

  # Add the user supplied GSL prefix to help find GSL
  SET(CMAKE_PREFIX_PATH ${GSL_PREFIX} ${CMAKE_PREFIX_PATH})

  # Find the GSL package available on this system
  FIND_PACKAGE(GSL 1.16.0 REQUIRED)

  # Set the include paths for GSL
  INCLUDE_DIRECTORIES(${GSL_INCLUDE_DIRS})

  # Set the link paths for GSL
  LINK_DIRECTORIES(${GSL_LINK_DIRECTORIES})

  # Find the gsl library
  FIND_LIBRARY(GSL_LIBRARY gsl ${GSL_LINK_DIRECTORIES})
  IF(${GSL_LIBRARY} MATCHES NOTFOUND)
    MESSAGE(FATAL_ERROR "The gsl library could not be found")
  ENDIF()

  # Find the gsl cblas library
  FIND_LIBRARY(GSL_CBLAS_LIBRARY gslcblas ${GSL_LINK_DIRECTORIES})
  IF(${GSL_CBLAS_LIBRARY} MATCHES NOTFOUND)
    MESSAGE(FATAL_ERROR "The gsl cblas library could not be found")
  ENDIF()

  # Echo Trilinos build info if a verbose configure is requested
  IF(CMAKE_VERBOSE_CONFIGURE)
    MESSAGE("\nFound GSL! Here are the details: ")
    MESSAGE("   GSL_INCLUDE_DIRS = ${GSL_INCLUDE_DIRS}")
    MESSAGE("   GSL_LIBRARY_DIRS = ${GSL_LIBRARY_DIRS}")
    MESSAGE("   GSL_LIBRARY = ${GSL_LIBRARY}")
    MESSAGE("   GSL_CBLAS_LIBRARY = ${GSL_CBLAS_LIBRARY}")
    MESSAGE("End of GSL details\n")
  ENDIF()

ENDMACRO(ENABLE_GSL_SUPPORT)