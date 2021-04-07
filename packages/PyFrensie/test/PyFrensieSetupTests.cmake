##
MACRO(PyFrensie_INITIALIZE_PACKAGE_TESTS)
  SET(PACKAGE_TEST_EXECS)
ENDMACRO()

## Macro for making a PyFrensie python test
MACRO(PyFrensie_MAKE_TEST TEST_NAME)
  SET(options)
  SET(oneValueArgs)
  SET(multiValueArgs TARGET_DEPENDS)
  CMAKE_PARSE_ARGUMENTS(PyFrensie_MAKE_TEST "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  # Check or unused parameters
  IF(NOT "${PyFrensie_MAKE_TEST_UNPARSED_ARGUMENTS}" STREQUAL "")
    MESSAGE(WARNING "PyFrensie_MAKE_TEST_UNPARSED_ARGUMENTS ${TEST_NAME} unused parameters = ${PyFrensie_MAKE_TEST_UNPARSED_ARGUMENTS}")
  ENDIF()

  ADD_CUSTOM_COMMAND(OUTPUT ${TEST_NAME}.py
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/copyWithCMakeSubstitutions.py
            ${CMAKE_CURRENT_SOURCE_DIR}/tst${TEST_NAME}.py.in
	    ${CMAKE_CURRENT_BINARY_DIR}/tst${TEST_NAME}.py
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/tst${TEST_NAME}.py.in)

  ADD_CUSTOM_TARGET(pyfrensie_${TEST_NAME} ALL
    DEPENDS pyfrensie ${CMAKE_CURRENT_BINARY_DIR}/${TEST_NAME}.py)

  IF(NOT "${PyFrensie_MAKE_TEST_TARGET_DEPENDS}" STREQUAL "")
    ADD_DEPENDENCIES(pyfrensie_${TEST_NAME} ${PyFrensie_MAKE_TEST_TARGET_DEPENDS})
  ENDIF()

  # Add this test exec to the list of package test execs
  LIST(APPEND PACKAGE_TEST_EXECS pyfrensie_${TEST_NAME})
ENDMACRO()

## Macro for adding a PyFrensie python test
MACRO(PyFrensie_ADD_TEST TEST_NAME_ROOT)
  SET(options OPENMP_TEST)
  SET(oneValueArgs TEST_EXEC_NAME_ROOT MPI_PROCS)
  SET(multiValueArgs EXTRA_ARGS EXTRA_LABELS ACE_LIB_DEPENDS)
  CMAKE_PARSE_ARGUMENTS(PyFrensie_ADD_TEST "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  # Check for unused parameters
  IF(NOT "${PyFrensie_ADD_TEST_UNPARSED_ARGUMENTS}" STREQUAL "")
    MESSAGE(WARNING "PyFrensie_ADD_TEST ${TEST_NAME_ROOT} unused parameters = ${PyFrensie_ADD_TEST_UNPARSED_ARGUMENTS}")
  ENDIF()

  # Set the test labels
  SET(TEST_LABELS PyFrensie)
  LIST(APPEND TEST_LABELS ${PyFrensie_ADD_TEST_EXTRA_LABELS})

  # Add the openmp label if this test has been specified as an openmp test
  IF(${PyFrensie_ADD_TEST_OPENMP_TEST})
    LIST(APPEND TEST_LABELS openmp)
  ENDIF()

  # Set the test name and preamble
  IF("${PyFrensie_ADD_TEST_MPI_PROCS}" STREQUAL "" OR
     "${PyFrensie_ADD_TEST_MPI_PROCS}" STREQUAL "1" )
    SET(TEST_NAME PyFrensie.${TEST_NAME_ROOT}_test)
    SET(TEST_PREAMBLE "")
  ELSE()
    SET(TEST_NAME PyFrensie.${TEST_NAME_ROOT}_${PyFrensie_ADD_TEST_MPI_PROCS}_test)
    SET(TEST_PREAMBLE ${MPIEXEC} ${MPIEXEC_FLAGS} ${MPIEXEC_NUMPROC_FLAG} ${PyFrensie_ADD_TEST_MPI_PROCS})
    LIST(APPEND TEST_LABELS mpi)
  ENDIF()

  # Set the test exec name
  IF(NOT "${PyFrensie_ADD_TEST_TEST_EXEC_NAME_ROOT}" STREQUAL "")
    SET(TEST_EXEC_NAME tst${PyFrensie_ADD_TEST_TEST_EXEC_NAME_ROOT}.py)
  ELSE()
    SET(TEST_EXEC_NAME tst${TEST_NAME_ROOT}.py)
  ENDIF()

  SET(UNAVAILABLE_ACE_LIB_DEPENDS ${PyFrensie_ADD_TEST_ACE_LIB_DEPENDS})

  IF(NOT "${PyFrensie_ADD_TEST_ACE_LIB_DEPENDS}" STREQUAL "")
    FOREACH(ACE_LIB_DEPEND ${PyFrensie_ADD_TEST_ACE_LIB_DEPENDS})
      IS_ACE_LIBRARY_AVAILABLE(${ACE_LIB_DEPEND} IS_LIB_AVAILABLE)

      IF(${IS_LIB_AVAILABLE})
        LIST(REMOVE_ITEM UNAVAILABLE_ACE_LIB_DEPENDS ${ACE_LIB_DEPEND})
      ENDIF()
    ENDFOREACH()
  ENDIF()

  LIST(LENGTH UNAVAILABLE_ACE_LIB_DEPENDS NUM_UNAVAILABLE_ACE_LIB_DEPENDS)

  IF(NUM_UNAVAILABLE_ACE_LIB_DEPENDS EQUAL "0")
    # Replace ACE placeholder arguments in the extra args with the
    # corresponding values
    IF(NOT "${PyFrensie_ADD_TEST_ACE_LIB_DEPENDS}" STREQUAL "")
      REPLACE_ACE_PLACEHOLDER_ARGS(PyFrensie_ADD_TEST_EXTRA_ARGS
        LIBRARY_NAMES ${PyFrensie_ADD_TEST_ACE_LIB_DEPENDS})
    ENDIF()

    # Add the test
    ADD_TEST(${TEST_NAME} ${TEST_PREAMBLE} ${TEST_EXEC_NAME} ${PyFrensie_ADD_TEST_EXTRA_ARGS})

    # Assign the test labels
    SET_PROPERTY(TEST ${TEST_NAME} PROPERTY LABELS ${TEST_LABELS})
  ELSE()
    STRING(REPLACE ";" ", " UNAVAILABLE_ACE_LIB_DEPENDS "${UNAVAILABLE_ACE_LIB_DEPENDS}")
    
    MESSAGE(WARNING "Test suite ${TEST_NAME} will be disabled because it requires the following unavailable ACE libraries: ${UNAVAILABLE_ACE_LIB_DEPENDS}.")
  ENDIF()

  # Cleanup
  UNSET(TEST_LABELS)
  UNSET(TEST_NAME)
  UNSET(TEST_PREAMBLE)
  UNSET(TEST_EXEC_NAME)
  
ENDMACRO()

##
MACRO(PyFrensie_FINALIZE_PACKAGE_TESTS)
  # Add a custom build target for all PyFrensie test execs
  ADD_CUSTOM_TARGET(pyfrensie_tests
    DEPENDS ${PACKAGE_TEST_EXECS})

  # Add a custom test target for all package tests
  ADD_CUSTOM_TARGET(test-pyfrensie
    COMMAND ctest -L pyfrensie
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

  ADD_CUSTOM_TARGET(test-pyfrensie2
    COMMAND ctest -L pyfrensie -j2
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

  ADD_CUSTOM_TARGET(test-pyfrensie4
    COMMAND ctest -L pyfrensie -j4
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

  ADD_CUSTOM_TARGET(test-pyfrensie8
    COMMAND ctest -L pyfrensie -j8
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

  ADD_CUSTOM_TARGET(test-pyfrensie12
    COMMAND ctest -L pyfrensie -j12
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

  UNSET(PACKAGE_TEST_EXECS)
ENDMACRO()
