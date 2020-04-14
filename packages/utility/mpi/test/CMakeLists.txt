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

FRENSIE_ADD_TEST_EXECUTABLE(CommunicatorSendRecvHelper DEPENDS tstCommunicatorSendRecvHelper.cpp)
FRENSIE_ADD_TEST(CommunicatorSendRecvHelper)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(CommunicatorSendRecvHelper MPI_PROCS 2)
  FRENSIE_ADD_TEST(CommunicatorSendRecvHelper MPI_PROCS 4)
ENDIF()

FRENSIE_ADD_TEST_EXECUTABLE(CommunicatorIsendIrecvHelper DEPENDS tstCommunicatorIsendIrecvHelper.cpp)
FRENSIE_ADD_TEST(CommunicatorIsendIrecvHelper)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(CommunicatorIsendIrecvHelper MPI_PROCS 2)
  FRENSIE_ADD_TEST(CommunicatorIsendIrecvHelper MPI_PROCS 4)
ENDIF()

FRENSIE_ADD_TEST_EXECUTABLE(CommunicatorProbeHelper DEPENDS tstCommunicatorProbeHelper.cpp)
FRENSIE_ADD_TEST(CommunicatorProbeHelper)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(CommunicatorProbeHelper MPI_PROCS 2)
  FRENSIE_ADD_TEST(CommunicatorProbeHelper MPI_PROCS 4)
ENDIF()

FRENSIE_ADD_TEST_EXECUTABLE(CommunicatorIprobeHelper DEPENDS tstCommunicatorIprobeHelper.cpp)
FRENSIE_ADD_TEST(CommunicatorIprobeHelper)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(CommunicatorIprobeHelper MPI_PROCS 2)
  FRENSIE_ADD_TEST(CommunicatorIprobeHelper MPI_PROCS 4)
ENDIF()

FRENSIE_ADD_TEST_EXECUTABLE(CommunicatorAllGatherHelper DEPENDS tstCommunicatorAllGatherHelper.cpp)
FRENSIE_ADD_TEST(CommunicatorAllGatherHelper)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(CommunicatorAllGatherHelper MPI_PROCS 2)
  FRENSIE_ADD_TEST(CommunicatorAllGatherHelper MPI_PROCS 4)
ENDIF()

FRENSIE_ADD_TEST_EXECUTABLE(CommunicatorAllReduceHelper DEPENDS tstCommunicatorAllReduceHelper.cpp)
FRENSIE_ADD_TEST(CommunicatorAllReduceHelper)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(CommunicatorAllReduceHelper MPI_PROCS 2)
  FRENSIE_ADD_TEST(CommunicatorAllReduceHelper MPI_PROCS 4)
ENDIF()

FRENSIE_ADD_TEST_EXECUTABLE(CommunicatorAllToAllHelper DEPENDS tstCommunicatorAllToAllHelper.cpp)
FRENSIE_ADD_TEST(CommunicatorAllToAllHelper)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(CommunicatorAllToAllHelper MPI_PROCS 2)
  FRENSIE_ADD_TEST(CommunicatorAllToAllHelper MPI_PROCS 4)
ENDIF()

FRENSIE_ADD_TEST_EXECUTABLE(CommunicatorBroadcastHelper DEPENDS tstCommunicatorBroadcastHelper.cpp)
FRENSIE_ADD_TEST(CommunicatorBroadcastHelper)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(CommunicatorBroadcastHelper MPI_PROCS 2)
  FRENSIE_ADD_TEST(CommunicatorBroadcastHelper MPI_PROCS 4)
ENDIF()

FRENSIE_ADD_TEST_EXECUTABLE(CommunicatorGatherHelper DEPENDS tstCommunicatorGatherHelper.cpp)
FRENSIE_ADD_TEST(CommunicatorGatherHelper)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(CommunicatorGatherHelper MPI_PROCS 2)
  FRENSIE_ADD_TEST(CommunicatorGatherHelper MPI_PROCS 4)
ENDIF()

FRENSIE_ADD_TEST_EXECUTABLE(CommunicatorGathervHelper DEPENDS tstCommunicatorGathervHelper.cpp)
FRENSIE_ADD_TEST(CommunicatorGathervHelper)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(CommunicatorGathervHelper MPI_PROCS 2)
  FRENSIE_ADD_TEST(CommunicatorGathervHelper MPI_PROCS 4)
ENDIF()

FRENSIE_ADD_TEST_EXECUTABLE(CommunicatorScatterHelper DEPENDS tstCommunicatorScatterHelper.cpp)
FRENSIE_ADD_TEST(CommunicatorScatterHelper)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(CommunicatorScatterHelper MPI_PROCS 2)
  FRENSIE_ADD_TEST(CommunicatorScatterHelper MPI_PROCS 4)
ENDIF()

FRENSIE_ADD_TEST_EXECUTABLE(CommunicatorScattervHelper DEPENDS tstCommunicatorScattervHelper.cpp)
FRENSIE_ADD_TEST(CommunicatorScattervHelper)

# Commented out until scatterv bug is fixed.
#[[ IF(${FRENSIE_ENABLE_MPI})
      FRENSIE_ADD_TEST(CommunicatorScattervHelper MPI_PROCS 2)
      FRENSIE_ADD_TEST(CommunicatorScattervHelper MPI_PROCS 4)
    ENDIF() ]]

FRENSIE_ADD_TEST_EXECUTABLE(CommunicatorReduceHelper DEPENDS tstCommunicatorReduceHelper.cpp)
FRENSIE_ADD_TEST(CommunicatorReduceHelper)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(CommunicatorReduceHelper MPI_PROCS 2)
  FRENSIE_ADD_TEST(CommunicatorReduceHelper MPI_PROCS 4)
ENDIF()

FRENSIE_ADD_TEST_EXECUTABLE(CommunicatorScanHelper DEPENDS tstCommunicatorScanHelper.cpp)
FRENSIE_ADD_TEST(CommunicatorScanHelper)

IF(${FRENSIE_ENABLE_MPI})
  FRENSIE_ADD_TEST(CommunicatorScanHelper MPI_PROCS 2)
  FRENSIE_ADD_TEST(CommunicatorScanHelper MPI_PROCS 4)
ENDIF()

FRENSIE_FINALIZE_PACKAGE_TESTS(utility_mpi)
