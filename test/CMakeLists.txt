SET(SRC ${CMAKE_SOURCE_DIR}/src)

ADD_EXECUTABLE(tstAssertion 
  tstAssertion.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstContractException 
  tstContractException.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstEPDL97ProcessingPolicy
  tstEPDL97ProcessingPolicy.cpp
  ${SRC}/EPDL97DataProcessor.cpp
  ${SRC}/HDF5FileHandler.cpp
  ${SRC}/Types.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstEPDL97DataProcessor
  tstEPDL97DataProcessor.cpp
  ${SRC}/EPDL97DataProcessor.cpp
  ${SRC}/HDF5FileHandler.cpp
  ${SRC}/Types.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstHDF5FileHandler
  tstHDF5FileHandler.cpp
  ${SRC}/HDF5FileHandler.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstPhotonDataProcessor
  tstPhotonDataProcessor.cpp
  ${SRC}/EPDL97DataProcessor.cpp
  ${SRC}/HDF5FileHandler.cpp
  ${SRC}/PhotonDataProcessor.cpp
  ${SRC}/Types.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})

TARGET_LINK_LIBRARIES(tstAssertion ${TEUCHOS})
TARGET_LINK_LIBRARIES(tstContractException ${TEUCHOS})
TARGET_LINK_LIBRARIES(tstEPDL97ProcessingPolicy ${TEUCHOS} ${HDF5})
TARGET_LINK_LIBRARIES(tstEPDL97DataProcessor ${TEUCHOS} ${HDF5})
TARGET_LINK_LIBRARIES(tstHDF5FileHandler ${TEUCHOS} ${HDF5})
TARGET_LINK_LIBRARIES(tstPhotonDataProcessor ${TEUCHOS} ${HDF5})

ADD_TEST(Assertion_test tstAssertion)
ADD_TEST(ContractException_test tstContractException)
ADD_TEST(EPDL97ProcessingPolicy_test tstEPDL97ProcessingPolicy)
ADD_TEST(EPDL97DataProcessor_test tstEPDL97DataProcessor)
ADD_TEST(HDF5FileHandler_test tstHDF5FileHandler)
ADD_TEST(PhotonDataProcessor_test tstPhotonDataProcessor)

# Install test files for the EPDL97DataProcessor_test
FILE(GLOB TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/test_files/*.txt)
MESSAGE("TEST_FILES = ${TEST_FILES}")
INSTALL(FILES ${TEST_FILES}
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
  PERMISSIONS OWNER_READ GROUP_READ WORLD_READ)