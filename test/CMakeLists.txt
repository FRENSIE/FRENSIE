SET(SRC ${CMAKE_SOURCE_DIR}/src)

ADD_EXECUTABLE(tstAssertion 
  tstAssertion.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstContractException 
  tstContractException.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstENDLIB97FileHandler
  tstENDLIB97FileHandler.cpp
  ${SRC}/ENDLIB97FileHandler.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstHDF5FileHandler
  tstHDF5FileHandler.cpp
  ${SRC}/HDF5FileHandler.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstDataProcessor
  tstDataProcessor.cpp
  ${SRC}/DataProcessor.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstPhotonDataProcessorShellMap
  tstPhotonDataProcessorShellMap.cpp
  ${SRC}/DataProcessor.cpp
  ${SRC}/ENDLIB97FileHandler.cpp
  ${SRC}/HDF5FileHandler.cpp
  ${SRC}/PhotonDataProcessor.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstPhotonDataProcessor
  tstPhotonDataProcessor.cpp
  ${SRC}/DataProcessor.cpp
  ${SRC}/ENDLIB97FileHandler.cpp
  ${SRC}/HDF5FileHandler.cpp
  ${SRC}/PhotonDataProcessor.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstBinarySearch
  tstBinarySearch.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstPhotonDataBasic
  tstPhotonDataBasic.cpp
  ${SRC}/PhotonDataBasic.cpp
  ${SRC}/HDF5FileHandler.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstPhotonDataFluorescence
  tstPhotonDataFluorescence.cpp
  ${SRC}/PhotonDataFluorescence.cpp
  ${SRC}/HDF5FileHandler.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstPhotonDataDopplerBroadening
  tstPhotonDataDopplerBroadening.cpp
  ${SRC}/PhotonDataDopplerBroadening.cpp
  ${SRC}/HDF5FileHandler.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstPhotonData
  tstPhotonData.cpp
  ${SRC}/PhotonDataBasic.cpp
  ${SRC}/PhotonDataFluorescence.cpp
  ${SRC}/PhotonDataDopplerBroadening.cpp
  ${SRC}/HDF5FileHandler.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstLinearAlgebra
  tstLinearAlgebra.cpp
  ${SRC}/LinearAlgebraAlgorithms.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstSurface
  tstSurface.cpp
  ${SRC}/Surface.cpp
  ${SRC}/LinearAlgebraAlgorithms.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstSetOperationFunctor
  tstSetOperationFunctor.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstBooleanCellFunctor
  tstBooleanCellFunctor.cpp
  ${SRC}/BooleanCellFunctor.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})

TARGET_LINK_LIBRARIES(tstAssertion ${TEUCHOS})
TARGET_LINK_LIBRARIES(tstContractException ${TEUCHOS})
TARGET_LINK_LIBRARIES(tstENDLIB97FileHandler ${TEUCHOS})
TARGET_LINK_LIBRARIES(tstHDF5FileHandler ${TEUCHOS} ${HDF5})
TARGET_LINK_LIBRARIES(tstDataProcessor ${TEUCHOS})
TARGET_LINK_LIBRARIES(tstPhotonDataProcessorShellMap ${TEUCHOS} ${HDF5})
TARGET_LINK_LIBRARIES(tstPhotonDataProcessor ${TEUCHOS} ${HDF5})
TARGET_LINK_LIBRARIES(tstBinarySearch ${TEUCHOS})
TARGET_LINK_LIBRARIES(tstPhotonDataBasic ${TEUCHOS} ${HDF5})
TARGET_LINK_LIBRARIES(tstPhotonDataFluorescence ${TEUCHOS} ${HDF5})
TARGET_LINK_LIBRARIES(tstPhotonDataDopplerBroadening ${TEUCHOS} ${HDF5})
TARGET_LINK_LIBRARIES(tstPhotonData ${TEUCHOS} ${HDF5})
TARGET_LINK_LIBRARIES(tstLinearAlgebra ${TEUCHOS})
TARGET_LINK_LIBRARIES(tstSurface ${TEUCHOS})
TARGET_LINK_LIBRARIES(tstSetOperationFunctor ${TEUCHOS})
TARGET_LINK_LIBRARIES(tstBooleanCellFunctor ${TEUCHOS})

ADD_TEST(Assertion_test tstAssertion)
ADD_TEST(ContractException_test tstContractException)
ADD_TEST(ENDLIB97FileHandler_test tstENDLIB97FileHandler)
ADD_TEST(HDF5FileHandler_test tstHDF5FileHandler)
ADD_TEST(DataProcessor_test tstDataProcessor)
ADD_TEST(PhotonDataProcessorShellMap_test tstPhotonDataProcessorShellMap)
ADD_TEST(PhotonDataProcessor_test tstPhotonDataProcessor)
ADD_TEST(BinarySearch_test tstBinarySearch)
ADD_TEST(PhotonDataBasic_test tstPhotonDataBasic)
ADD_TEST(PhotonDataFluorescence_test tstPhotonDataFluorescence)
ADD_TEST(PhotonDataDopplerBroadening_test tstPhotonDataDopplerBroadening)
ADD_TEST(PhotonData_test tstPhotonData)
ADD_TEST(LinearAlgebra_test tstLinearAlgebra)
ADD_TEST(Surface_test tstSurface)
ADD_TEST(SetOperationFunctor_test tstSetOperationFunctor)
ADD_TEST(BooleanCellFunctor_test tstBooleanCellFunctor)

# Install test files for the EPDL97DataProcessor_test
FILE(GLOB TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/test_files/*.txt)
MESSAGE("TEST_FILES = ${TEST_FILES}")
INSTALL(FILES ${TEST_FILES}
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
  PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)