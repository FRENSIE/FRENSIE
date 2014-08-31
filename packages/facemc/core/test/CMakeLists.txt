ADD_EXECUTABLE(tstParticleStateCore
  tstParticleStateCore.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstParticleStateCore facemc_core)
ADD_TEST(ParticleStateCore_test tstParticleStateCore)

ADD_EXECUTABLE(tstParticleState
  tstParticleState.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstParticleState facemc_core)
ADD_TEST(ParticleState_test tstParticleState)

ADD_EXECUTABLE(tstPhotonState
  tstPhotonState.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPhotonState facemc_core)
ADD_TEST(PhotonState_test tstPhotonState)

ADD_EXECUTABLE(tstNeutronState
  tstNeutronState.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstNeutronState facemc_core)
ADD_TEST(NeutronState_test tstNeutronState)

ADD_EXECUTABLE(tstParticleBank
  tstParticleBank.cpp)
TARGET_LINK_LIBRARIES(tstParticleBank facemc_core)
ADD_TEST(ParticleBank_test tstParticleBank)
