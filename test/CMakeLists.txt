SET(SRC ${CMAKE_SOURCE_DIR}/src)

ADD_EXECUTABLE(tstAssertion 
  tstAssertion.cpp 
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstContractException 
  tstContractException.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
ADD_EXECUTABLE(tstEPDL97DataProcessor
  tstEPDL97DataProcessor.cpp
  ${SRC}/EPDL97DataProcessor.cpp
  ${SRC}/HDF5FileHandler.cpp
  ${SRC}/Types.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})

TARGET_LINK_LIBRARIES(tstAssertion ${TEUCHOS})
TARGET_LINK_LIBRARIES(tstContractException ${TEUCHOS})
TARGET_LINK_LIBRARIES(tstEPDL97DataProcessor ${TEUCHOS} ${HDF5} ${ZLIB})

ADD_TEST(Assertion_test tstAssertion)
ADD_TEST(ContractException_test tstContractException)
ADD_TEST(EPDL97DataProcessor_test tstEPDL97DataProcessor)