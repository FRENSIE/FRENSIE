# Configure the Boost options that will be required in this project. The
# following variables will be set:
# 1.)
MACRO(ENABLE_BOOST_SUPPORT)

    # No multithreading
    SET(Boost_USE_MULTITHREAD ON)

    # Use the user supplied prefix to find the Boost libraries and include dirs.
    IF(DEFINED BOOST_PREFIX)
      SET(BOOST_ROOT ${BOOST_PREFIX})
      SET(Boost_NO_SYSTEM_PATHS ON)
    ENDIF()

    # Find the Boost test component
    FIND_PACKAGE(Boost 1.54.0 REQUIRED COMPONENTS test_exec_monitor)

    IF(${CMAKE_BUILD_TYPE} EQUAL RELEASE)
      SET(BOOST_TEST_LIBRARY ${Boost_TEST_EXEC_MONITOR_LIBRARY_RELEASE})
    ELSE()
      SET(BOOST_TEST_LIBRARY ${Boost_TEST_EXEC_MONITOR_LIBRARY_DEBUG})
    ENDIF()
    
    UNSET(Boost_LIBRARIES)
    UNSET(Boost_INCLUDE_DIRS)

    # Find the Boost package and the required components
    FIND_PACKAGE(Boost 1.54.0 REQUIRED COMPONENTS log program_options serialization)

    # Set the include paths for Boost
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

    # Echo the Boost details if a verbose configure was requested
    IF(CMAKE_VERBOSE_CONFIGURE)
      MESSAGE("Found BOOST! Here are the details: ")
      MESSAGE("  BOOST_PREFIX = ${BOOST_ROOT}")
      MESSAGE("  BOOST_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}")
      MESSAGE("  BOOST_LIBRARY_DIRS = ${Boost_LIBRARY_DIRS}")
      MESSAGE("  BOOST_LIBRARIES = ${Boost_LIBRARIES}")
      MESSAGE("  BOOST_TEST_LIBRARY = ${BOOST_TEST_LIBRARY}")
      MESSAGE("End of BOOST details\n")
    ENDIF()

ENDMACRO(ENABLE_BOOST_SUPPORT)

