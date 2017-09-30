FRENSIE_INITIALIZE_PACKAGE_TESTS(utility_mpi)

# FRENSIE_ADD_TEST_EXECUTABLE(SerialCommHelpers
#   tstSerialCommHelpers.cpp
#   ${FRENSIE_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstSerialCommHelpers utility_core)
# ADD_TEST(SerialCommHelpers_test tstSerialCommHelpers)
# SET_PROPERTY(TEST SerialCommHelpers_test PROPERTY LABELS utility_core)

# IF(${FRENSIE_ENABLE_MPI})
#   FRENSIE_ADD_TEST_EXECUTABLE(MpiCommHelpers
#     tstMpiCommHelpers.cpp
#     ${FRENSIE_STD_UNIT_TEST_MAIN})
#   TARGET_LINK_LIBRARIES(tstMpiCommHelpers utility_core)
#   ADD_TEST(MpiCommHelpers_2_test ${MPIEXEC} -n 2 tstMpiCommHelpers)
#   ADD_TEST(MpiCommHelpers_4_test ${MPIEXEC} -n 4 tstMpiCommHelpers)
#   SET_PROPERTY(TEST MpiCommHelpers_2_test PROPERTY LABELS utility_core mpi no_threads)
#   SET_PROPERTY(TEST MpiCommHelpers_4_test PROPERTY LABELS utility_core mpi no_threads)
# ENDIF()

FRENSIE_FINALIZE_PACKAGE_TESTS(utility_mpi)
