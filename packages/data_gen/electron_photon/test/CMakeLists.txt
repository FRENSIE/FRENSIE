FRENSIE_INITIALIZE_PACKAGE_TESTS(data_gen_electron_photon)

# Add FormFactorEvaluator
FRENSIE_ADD_TEST_EXECUTABLE(FormFactorEvaluator DEPENDS tstFormFactorEvaluator.cpp)
FRENSIE_ADD_TEST(FormFactorEvaluator
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_pb_ace_file=82000.12p:filepath
  --test_pb_ace_file_start_line=82000.12p:filestartline)

# Add ScatteringFunctionEvaluator
FRENSIE_ADD_TEST_EXECUTABLE(ScatteringFunctionEvaluator DEPENDS tstScatteringFunctionEvaluator.cpp)
FRENSIE_ADD_TEST(ScatteringFunctionEvaluator
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_pb_ace_file=82000.12p:filepath
  --test_pb_ace_file_start_line=82000.12p:filestartline)

# Add OccupationNumberEvaluator
FRENSIE_ADD_TEST_EXECUTABLE(OccupationNumberEvaluator DEPENDS tstOccupationNumberEvaluator.cpp)
FRENSIE_ADD_TEST(OccupationNumberEvaluator
  ACE_LIB_DEPENDS 1000.12p 82000.12p
  EXTRA_ARGS
  --test_h_ace_file=1000.12p:filepath
  --test_h_ace_file_start_line=1000.12p:filestartline
  --test_pb_ace_file=82000.12p:filepath
  --test_pb_ace_file_start_line=82000.12p:filestartline)

# Add DefaultComptonProfileGenerator
FRENSIE_ADD_TEST_EXECUTABLE(DefaultComptonProfileGenerator DEPENDS tstDefaultComptonProfileGenerator.cpp)
FRENSIE_ADD_TEST(DefaultComptonProfileGenerator)

# Add ElectronElasticDataEvaluator
FRENSIE_ADD_TEST_EXECUTABLE(ElectronElasticDataEvaluator
  DEPENDS tstElectronElasticDataEvaluator.cpp
  TARGET_DEPENDS ${TEST_H_ENDL_NATIVE_FILE_TARGET} ${TEST_C_ENDL_NATIVE_FILE_TARGET})
FRENSIE_ADD_TEST(ElectronElasticDataEvaluator
  EXTRA_ARGS
  --test_endl_file=${TEST_H_ENDL_NATIVE_FILE}
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_1_native.xml)

# Add ENDLElectronPhotonRelaxationDataGenerator
FRENSIE_ADD_TEST_EXECUTABLE(ENDLElectronPhotonRelaxationDataGenerator
  DEPENDS tstENDLElectronPhotonRelaxationDataGenerator.cpp
  TARGET_DEPENDS ${TEST_H_ENDL_NATIVE_FILE_TARGET} ${TEST_C_ENDL_NATIVE_FILE_TARGET})
FRENSIE_ADD_TEST(ENDLElectronPhotonRelaxationDataGenerator
  EXTRA_ARGS
  --test_h_endl_file=${TEST_H_ENDL_NATIVE_FILE}
  --test_c_endl_file=${TEST_C_ENDL_NATIVE_FILE})

# Add ACEAndENDLElectronPhotonRelaxationDataGenerator
FRENSIE_ADD_TEST_EXECUTABLE(ACEAndENDLElectronPhotonRelaxationDataGenerator
  DEPENDS tstACEAndENDLElectronPhotonRelaxationDataGenerator.cpp
  TARGET_DEPENDS ${TEST_H_ENDL_NATIVE_FILE_TARGET} ${TEST_C_ENDL_NATIVE_FILE_TARGET})
FRENSIE_ADD_TEST(ACEAndENDLElectronPhotonRelaxationDataGenerator
  ACE_LIB_DEPENDS 1000.12p 6000.12p
  EXTRA_ARGS
  --test_h_ace_file=1000.12p:filepath
  --test_h_ace_file_start_line=1000.12p:filestartline
  --test_h_endl_file=${TEST_H_ENDL_NATIVE_FILE}
  --test_c_ace_file=6000.12p:filepath
  --test_c_ace_file_start_line=6000.12p:filestartline
  --test_c_endl_file=${TEST_C_ENDL_NATIVE_FILE})

# Add AdjointElectronGridGenerator
FRENSIE_ADD_TEST_EXECUTABLE(AdjointElectronGridGenerator DEPENDS tstAdjointElectronGridGenerator.cpp)
FRENSIE_ADD_TEST(AdjointElectronGridGenerator
  EXTRA_ARGS
  --test_native_h_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_1_native.xml
  --test_native_si_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_14_native.xml)

# Add AdjointPairProductionEnergyDistributionNormConstantEvaluator
FRENSIE_ADD_TEST_EXECUTABLE(AdjointPairProductionEnergyDistributionNormConstantEvaluator DEPENDS tstAdjointPairProductionEnergyDistributionNormConstantEvaluator.cpp)
FRENSIE_ADD_TEST(AdjointPairProductionEnergyDistributionNormConstantEvaluator
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml)

# Add AdjointIncoherentCrossSectionHelpers
FRENSIE_ADD_TEST_EXECUTABLE(AdjointIncoherentCrossSectionHelpers DEPENDS tstAdjointIncoherentCrossSectionHelpers.cpp)
FRENSIE_ADD_TEST(AdjointIncoherentCrossSectionHelpers)

# Add AdjointIncoherentGridGenerator
FRENSIE_ADD_TEST_EXECUTABLE(AdjointIncoherentGridGenerator DEPENDS tstAdjointIncoherentGridGenerator.cpp)
FRENSIE_ADD_TEST(AdjointIncoherentGridGenerator
  EXTRA_ARGS
  --test_native_h_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_1_native.xml
  --test_native_pb_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml)

# Add ElasticElectronMomentsEvaluator
FRENSIE_ADD_TEST_EXECUTABLE(ElasticElectronMomentsEvaluator DEPENDS tstElasticElectronMomentsEvaluator.cpp)
FRENSIE_ADD_TEST(ElasticElectronMomentsEvaluator
  EXTRA_ARGS
  --test_native_pb_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml
  --test_native_al_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_13_native.xml)

# Add StandardMomentPreservingElectronDataGenerator
FRENSIE_ADD_TEST_EXECUTABLE(StandardMomentPreservingElectronDataGenerator DEPENDS tstStandardMomentPreservingElectronDataGenerator.cpp)
FRENSIE_ADD_TEST(StandardMomentPreservingElectronDataGenerator
  EXTRA_ARGS
  --test_h_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_1_native.xml
  --test_pb_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml
  --test_al_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_13_native.xml)

# Add StandardAdjointElectronPhotonRelaxationDataGenerator
FRENSIE_ADD_TEST_EXECUTABLE(StandardAdjointElectronPhotonRelaxationDataGenerator DEPENDS tstStandardAdjointElectronPhotonRelaxationDataGenerator.cpp)
FRENSIE_ADD_TEST(StandardAdjointElectronPhotonRelaxationDataGenerator
  EXTRA_ARGS
  --test_h_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_1_native.xml)

FRENSIE_FINALIZE_PACKAGE_TESTS(data_gen_electron_photon)
