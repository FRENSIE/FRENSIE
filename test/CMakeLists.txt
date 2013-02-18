SET(SOURCES
  tstAssertion.cpp
  tstContractException.cpp
  ${SOURCES}
  )

IF(CMAKE_VERBOSE_CONFIGURE)
  MESSAGE("SOURCES = ${SOURCES}")
ENDIF()

ADD_EXECUTABLE(tstAssertion tstAssertion.cpp)
ADD_EXECUTABLE(tstContractException tstContractException.cpp)

TARGET_LINK_LIBRARIES(tstAssertion ${TEUCHOS})
TARGET_LINK_LIBRARIES(tstContractException ${TEUCHOS})

ADD_TEST(Assertion_test tstAssertion)
ADD_TEST(ContractException_test tstContractException)