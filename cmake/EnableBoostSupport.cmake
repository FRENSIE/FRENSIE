# Configure the Boost options that will be required in this project. The
# following variables will be set:
# 1.)
MACRO(ENABLE_BOOST_SUPPORT)

    # Only use static libraries
    SET(Boost_USE_STATIC_LIBS ON)
    SET(Boost_USE_STATIC_RUNTIME ON)

    # No multithreading
    SET(Boost_USE_MULTITHREAD OFF)

    # Use the user supplied prefix to find the Boost libraries and include dirs.
    SET(BOOST_ROOT ${BOOST_PREFIX})
    SET(Boost_NO_SYSTEM_PATHS ON)

    # Check if boost needs to be found
    IF(NOT DEFINED BOOST_FOUND)
      SET(FIND_BOOST TRUE)
    ELSEIF(NOT ${BOOST_FOUND})
      SET(FIND_BOOST TRUE)
    ELSEIF(${BOOST_FOUND})
      STRING(COMPARE NOTEQUAL "${FOUND_BOOST_LIBS}" "${ARGN}" FIND_BOOST)
    ENDIF()
    
    # Find the boost package
    IF(FIND_BOOST)
      FIND_PACKAGE(Boost 1.54.0 REQUIRED COMPONENTS ${ARGN})

      # Cache to boost found boolean
      SET(BOOST_FOUND ON
	CACHE BOOL "Indicates that boost has been found")

      # Cache the libraries that were found
      SET(FOUND_BOOST_LIBS "${ARGN}"
	CACHE STRING "The boost libraries that were found" FORCE)
      
      # Cache the library names
      SET(Boost_LIBRARIES ${Boost_LIBRARIES}
	CACHE STRING "The boost libraries requested" FORCE)
    ENDIF()

    # Set the include paths for Boost
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

    # Echo the Boost details if a verbose configure was requested
    IF(CMAKE_VERBOSE_CONFIGURE)
      MESSAGE("Found BOOST! Here are the details: ")
      MESSAGE("  BOOST_PREFIX = ${BOOST_ROOT}")
      MESSAGE("  BOOST_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}")
      MESSAGE("  BOOST_LIBRARY_DIRS = ${Boost_LIBRARY_DIRS}")
      MESSAGE("  BOOST_LIBRARIES = ${Boost_LIBRARIES}")
      MESSAGE("End of BOOST details\n")
    ENDIF()

ENDMACRO(ENABLE_BOOST_SUPPORT)
    
