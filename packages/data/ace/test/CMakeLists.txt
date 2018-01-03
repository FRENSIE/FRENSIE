FRENSIE_INITIALIZE_PACKAGE_TESTS(data_ace)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

FRENSIE_ADD_TEST_EXECUTABLE(ACEFileHandler DEPENDS tstACEFileHandler.cpp)
FRENSIE_ADD_TEST(ACEFileHandler
  EXTRA_ARGS --test_neutron_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_h1_ace_file.txt --test_sab_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_h2o_sab_ace_file.txt)

FRENSIE_ADD_TEST_EXECUTABLE(XSSNeutronDataExtractor DEPENDS tstXSSNeutronDataExtractor.cpp)
FRENSIE_ADD_TEST(XSSNeutronDataExtractor
  EXTRA_ARGS
  --test_h1_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_h1_ace_file.txt
  --test_h1_ace_table=1001.70c
  --test_u238_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_u238_ace_file.txt
  --test_u238_ace_table=92238.70c)

FRENSIE_ADD_TEST_EXECUTABLE(XSSSabDataExtractor DEPENDS tstXSSSabDataExtractor.cpp)
FRENSIE_ADD_TEST(XSSSabDataExtractor
  EXTRA_ARGS
  --test_inelastic_only_sab_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_h2o_sab_ace_file.txt
  --test_inelastic_only_sab_ace_table=lwtr.10t
  --test_no_elastic_dist_sab_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_grph_sab_ace_file.txt
  --test_no_elastic_dist_sab_ace_table=grph.10t
  --test_full_sab_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_poly_sab_ace_file.txt
  --test_full_sab_ace_table=poly.10t)

FRENSIE_ADD_TEST_EXECUTABLE(XSSPhotonuclearDataExtractor DEPENDS tstXSSPhotonuclearDataExtractor.cpp)
FRENSIE_ADD_TEST(XSSPhotonuclearDataExtractor
  EXTRA_ARGS
  --h2_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_h2_photonuclear_ace_file.txt
  --h2_ace_table=1002.24u)

FRENSIE_ADD_TEST_EXECUTABLE(XSSPhotoatomicDataExtractor DEPENDS tstXSSPhotoatomicDataExtractor.cpp)
FRENSIE_ADD_TEST(XSSPhotoatomicDataExtractor
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_photoatomic_ace_file.txt
  --test_ace_table=82000.04p)

FRENSIE_ADD_TEST_EXECUTABLE(XSSEPRDataExtractor DEPENDS tstXSSEPRDataExtractor.cpp)
FRENSIE_ADD_TEST(XSSEPRDataExtractor
  EXTRA_ARGS
  --pb_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt
  --pb_ace_table=82000.12p
  --b_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_b_epr_ace_file.txt
  --b_ace_table=5000.12p)

FRENSIE_ADD_TEST_EXECUTABLE(XSSElectronDataExtractor DEPENDS tstXSSElectronDataExtractor.cpp)
FRENSIE_ADD_TEST(XSSElectronDataExtractor
  EXTRA_ARGS
  --pb_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_electron_ace_file.txt
  --pb_ace_table=82000.03e
  --b_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_b_electron_ace_file.txt
  --b_ace_table=5000.03e)

FRENSIE_FINALIZE_PACKAGE_TESTS(data_ace)
