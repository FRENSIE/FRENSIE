ADD_EXECUTABLE(tstParticleStateCore
  tstParticleStateCore.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstParticleStateCore monte_carlo_core)
ADD_TEST(ParticleStateCore_test tstParticleStateCore)

ADD_EXECUTABLE(tstParticleState
  tstParticleState.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstParticleState monte_carlo_core)
ADD_TEST(ParticleState_test tstParticleState)

ADD_EXECUTABLE(tstPhotonState
  tstPhotonState.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPhotonState monte_carlo_core)
ADD_TEST(PhotonState_test tstPhotonState)

ADD_EXECUTABLE(tstAdjointPhotonState
  tstAdjointPhotonState.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstAdjointPhotonState monte_carlo_core)
ADD_TEST(AdjointPhotonState_test tstAdjointPhotonState)

ADD_EXECUTABLE(tstAdjointPhotonProbeState
  tstAdjointPhotonProbeState.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstAdjointPhotonProbeState monte_carlo_core)
ADD_TEST(AdjointPhotonProbeState_test tstAdjointPhotonProbeState)

ADD_EXECUTABLE(tstNeutronState
  tstNeutronState.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstNeutronState monte_carlo_core)
ADD_TEST(NeutronState_test tstNeutronState)

ADD_EXECUTABLE(tstElectronState
  tstElectronState.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstElectronState monte_carlo_core)
ADD_TEST(ElectronState_test tstElectronState)

ADD_EXECUTABLE(tstParticleBank
  tstParticleBank.cpp)
TARGET_LINK_LIBRARIES(tstParticleBank monte_carlo_core)
ADD_TEST(ParticleBank_test tstParticleBank)

IF(${FRENSIE_ENABLE_OPENMP})
  ADD_TEST(SharedParallelParticleBank_2_test
    tstParticleBank --threads=2)
  ADD_TEST(SharedParallelParticleBank_4_test
    tstParticleBank --threads=4)
ENDIF()

IF(${FRENSIE_ENABLE_MPI})
  ADD_TEST(DistributedParallelParticleBank_2_test
    ${MPIEXEC} -n 2 tstParticleBank)
  ADD_TEST(DistributedParallelParticleBank_4_test
    ${MPIEXEC} -n 4 tstParticleBank)
ENDIF()

IF( ${FRENSIE_ENABLE_OPENMP} AND ${FRENSIE_ENABLE_MPI})
  ADD_TEST(HybridParallelParticleBank_2_2_test
    ${MPIEXEC} -n 2 tstParticleBank --threads=2)
ENDIF()

ADD_EXECUTABLE(tstSimulationProperties 
  tstSimulationProperties.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSimulationProperties monte_carlo_core)
ADD_TEST(SimulationProperties_test tstSimulationProperties)

ADD_EXECUTABLE(tstSimulationGeneralProperties 
  tstSimulationGeneralProperties.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSimulationGeneralProperties monte_carlo_core)
ADD_TEST(SimulationGeneralProperties_test tstSimulationGeneralProperties)

ADD_EXECUTABLE(tstSimulationNeutronProperties 
  tstSimulationNeutronProperties.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSimulationNeutronProperties monte_carlo_core)
ADD_TEST(SimulationNeutronProperties_test tstSimulationNeutronProperties)

ADD_EXECUTABLE(tstSimulationPhotonProperties 
  tstSimulationPhotonProperties.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSimulationPhotonProperties monte_carlo_core)
ADD_TEST(SimulationPhotonProperties_test tstSimulationPhotonProperties)

ADD_EXECUTABLE(tstSimulationElectronProperties 
  tstSimulationElectronProperties.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSimulationElectronProperties monte_carlo_core)
ADD_TEST(SimulationElectronProperties_test tstSimulationElectronProperties)

ADD_EXECUTABLE(tstSimulationPropertiesFactory 
  tstSimulationPropertiesFactory.cpp)
TARGET_LINK_LIBRARIES(tstSimulationPropertiesFactory monte_carlo_core)
ADD_TEST(SimulationPropertiesFactory_test tstSimulationPropertiesFactory --test_properties_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_properties.xml")

ADD_EXECUTABLE(tstParticleModeType 
  tstParticleModeType.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstParticleModeType monte_carlo_core)
ADD_TEST(ParticleModeType_test tstParticleModeType)
