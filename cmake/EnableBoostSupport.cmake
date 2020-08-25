# Configure the Boost options that will be required in this project. The
# following variables will be set:
# 1.)
MACRO(ENABLE_BOOST_SUPPORT)

    SET(BOOST_MIN_VERSION 1.72.0)

    # Enable multithreading in boost (used by the log component)
    SET(Boost_USE_MULTITHREAD ON)

    # Use the user supplied prefix to find the Boost libraries and include
    # dirs (custom boost installs).
    IF(DEFINED BOOST_PREFIX)
      SET(BOOST_ROOT ${BOOST_PREFIX})
      SET(Boost_NO_SYSTEM_PATHS ON)
    ENDIF()

    # Find the Boost test component: This component will only be used to
    # create unit tests so there is no need to include it in the list of
    # boost components that the FRENSIE packages will link with. Unfortunately,
    # we will have to run the FIND_PACKAGE macro twice to prevent this
    # component from being appended to the list. Unit tests that have been
    # written using the boost unit test API need to add ${BOOST_TEST_LIBRARY}
    # to the TARGET_LINK_LIBRARIES macro call.
    FIND_PACKAGE(Boost ${BOOST_MIN_VERSION} REQUIRED COMPONENTS test_exec_monitor)

    IF(${CMAKE_BUILD_TYPE} EQUAL RELEASE)
      SET(BOOST_TEST_LIBRARY ${Boost_TEST_EXEC_MONITOR_LIBRARY_RELEASE})
    ELSE()
      SET(BOOST_TEST_LIBRARY ${Boost_TEST_EXEC_MONITOR_LIBRARY_DEBUG})
    ENDIF()
    
    UNSET(Boost_LIBRARIES)
    UNSET(Boost_INCLUDE_DIRS)

    # Find the Boost package and the required components
    SET(BOOST_COMPONENTS_LIST log program_options serialization system thread unit_test_framework)

    IF(FRENSIE_ENABLE_MPI)
      SET(BOOST_COMPONENTS_LIST ${BOOST_COMPONENTS_LIST} mpi)
    ENDIF()
    
    FIND_PACKAGE(Boost ${BOOST_MIN_VERSION} REQUIRED COMPONENTS ${BOOST_COMPONENTS_LIST})

    # Set the include paths for Boost
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

    # NOTE: Boost still uses the std::auto_ptr class, which is now depricated.
    #       The newer GNU C++ compilers will generate a large number of warning
    #       messages regarding this usage of the std::auto_ptr class. To avoid
    #       these warning messages that are not direcly related to FRENSIE we
    #       will simply turn them off
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations -DBOOST_LOG_DYN_LINK -DBOOST_PROGRAM_OPTIONS_DYN_LINK")

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

