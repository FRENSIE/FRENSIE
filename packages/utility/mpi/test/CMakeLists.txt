FRENSIE_INITIALIZE_PACKAGE_TESTS(utility_mpi)

FRENSIE_ADD_TEST_EXECUTABLE(SerialCommunicator DEPENDS tstSerialCommunicator.cpp)
FRENSIE_ADD_TEST(SerialCommunicator)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST_EXECUTABLE(MPICommunicator DEPENDS tstMPICommunicator.cpp)
  FRENSIE_ADD_TEST(MPICommunicator)
  FRENSIE_ADD_TEST(MPICommunicator MPI_PROCS 2)
  FRENSIE_ADD_TEST(MPICommunicator MPI_PROCS 4)

  FRENSIE_ADD_TEST_EXECUTABLE(MPICommunicatorSequenceContainer DEPENDS tstMPICommunicatorSequenceContainer.cpp)
  FRENSIE_ADD_TEST(MPICommunicatorSequenceContainer)
  FRENSIE_ADD_TEST(MPICommunicatorSequenceContainer MPI_PROCS 2)
  FRENSIE_ADD_TEST(MPICommunicatorSequenceContainer MPI_PROCS 4)

  FRENSIE_ADD_TEST_EXECUTABLE(MPICommunicatorAssociativeContainer DEPENDS tstMPICommunicatorAssociativeContainer.cpp)
  FRENSIE_ADD_TEST(MPICommunicatorAssociativeContainer)
  FRENSIE_ADD_TEST(MPICommunicatorAssociativeContainer MPI_PROCS 2)
  FRENSIE_ADD_TEST(MPICommunicatorAssociativeContainer MPI_PROCS 4)
ENDIF()

FRENSIE_ADD_TEST_EXECUTABLE(Communicator DEPENDS tstCommunicator.cpp)
FRENSIE_ADD_TEST(Communicator)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(Communicator MPI_PROCS 2)
  FRENSIE_ADD_TEST(Communicator MPI_PROCS 4)
ENDIF()

FRENSIE_FINALIZE_PACKAGE_TESTS(utility_mpi)
