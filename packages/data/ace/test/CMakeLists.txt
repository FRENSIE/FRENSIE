FRENSIE_INITIALIZE_PACKAGE_TESTS(data_ace)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

FRENSIE_ADD_TEST_EXECUTABLE(XSSNeutronDataExtractorSort DEPENDS tstXSSNeutronDataExtractorSort.cpp)
# possibly add the isotope that initially broke everything (18040.710nc)
# find where this executable is stored

FRENSIE_ADD_TEST_EXECUTABLE(ACEFileHandlerNeutron DEPENDS tstACEFileHandlerNeutron.cpp)
FRENSIE_ADD_TEST(ACEFileHandlerNeutron
  ACE_LIB_DEPENDS 1001.70c
  EXTRA_ARGS
  --test_neutron_ace_file=1001.70c:filepath
  --test_neutron_ace_file_start_line=1001.70c:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(ACEFileHandlerSab DEPENDS tstACEFileHandlerSab.cpp)
FRENSIE_ADD_TEST(ACEFileHandlerSab
  ACE_LIB_DEPENDS lwtr.10t
  EXTRA_ARGS
  --test_sab_ace_file=lwtr.10t:filepath
  --test_sab_ace_file_start_line=lwtr.10t:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(XSSNeutronDataExtractorH1 DEPENDS tstXSSNeutronDataExtractorH1.cpp)
FRENSIE_ADD_TEST(XSSNeutronDataExtractorH1
  ACE_LIB_DEPENDS 1001.70c
  EXTRA_ARGS
  --test_h1_ace_table=1001.70c
  --test_h1_ace_file=1001.70c:filepath
  --test_h1_ace_file_start_line=1001.70c:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(XSSNeutronDataExtractorU238 DEPENDS tstXSSNeutronDataExtractorU238.cpp)
FRENSIE_ADD_TEST(XSSNeutronDataExtractorU238
  ACE_LIB_DEPENDS 92238.70c
  EXTRA_ARGS
  --test_u238_ace_table=92238.70c
  --test_u238_ace_file=92238.70c:filepath
  --test_u238_ace_file_start_line=92238.70c:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(XSSSabDataExtractorLwtr DEPENDS tstXSSSabDataExtractorLwtr.cpp)
FRENSIE_ADD_TEST(XSSSabDataExtractorLwtr
  ACE_LIB_DEPENDS lwtr.10t
  EXTRA_ARGS
  --test_lwtr_sab_ace_table=lwtr.10t
  --test_lwtr_sab_ace_file=lwtr.10t:filepath
  --test_lwtr_sab_ace_file_start_line=lwtr.10t:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(XSSSabDataExtractorGrph DEPENDS tstXSSSabDataExtractorGrph.cpp)
FRENSIE_ADD_TEST(XSSSabDataExtractorGrph
  ACE_LIB_DEPENDS grph.10t
  EXTRA_ARGS
  --test_grph_sab_ace_table=grph.10t
  --test_grph_sab_ace_file=grph.10t:filepath
  --test_grph_sab_ace_file_start_line=grph.10t:filestartline)
  

FRENSIE_ADD_TEST_EXECUTABLE(XSSSabDataExtractorPoly DEPENDS tstXSSSabDataExtractorPoly.cpp)
FRENSIE_ADD_TEST(XSSSabDataExtractorPoly
  ACE_LIB_DEPENDS poly.10t
  EXTRA_ARGS
  --test_poly_sab_ace_table=poly.10t
  --test_poly_sab_ace_file=poly.10t:filepath
  --test_poly_sab_ace_file_start_line=poly.10t:filestartline)  

FRENSIE_ADD_TEST_EXECUTABLE(XSSPhotonuclearDataExtractor DEPENDS tstXSSPhotonuclearDataExtractor.cpp)
FRENSIE_ADD_TEST(XSSPhotonuclearDataExtractor
  ACE_LIB_DEPENDS 1002.24u
  EXTRA_ARGS
  --h2_ace_table=1002.24u
  --h2_ace_file=1002.24u:filepath
  --h2_ace_file_start_line=1002.24u:filestartline)  

FRENSIE_ADD_TEST_EXECUTABLE(XSSPhotoatomicDataExtractor DEPENDS tstXSSPhotoatomicDataExtractor.cpp)
FRENSIE_ADD_TEST(XSSPhotoatomicDataExtractor
  ACE_LIB_DEPENDS 82000.04p
  EXTRA_ARGS
  --test_ace_table=82000.04p
  --test_ace_file=82000.04p:filepath
  --test_ace_file_start_line=82000.04p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(XSSElectronDataExtractorB DEPENDS tstXSSElectronDataExtractorB.cpp)
FRENSIE_ADD_TEST(XSSElectronDataExtractorB
  ACE_LIB_DEPENDS 5000.03e
  EXTRA_ARGS
  --b_ace_table=5000.03e
  --b_ace_file=5000.03e:filepath
  --b_ace_file_start_line=5000.03e:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(XSSElectronDataExtractorPb DEPENDS tstXSSElectronDataExtractorPb.cpp)
FRENSIE_ADD_TEST(XSSElectronDataExtractorPb
  ACE_LIB_DEPENDS 82000.03e
  EXTRA_ARGS
  --pb_ace_table=82000.03e
  --pb_ace_file=82000.03e:filepath
  --pb_ace_file_start_line=82000.03e:filestartline)
  
FRENSIE_ADD_TEST_EXECUTABLE(XSSEPRDataExtractorB DEPENDS tstXSSEPRDataExtractorB.cpp)
FRENSIE_ADD_TEST(XSSEPRDataExtractorB
  ACE_LIB_DEPENDS 5000.12p
  EXTRA_ARGS
  --b_ace_table=5000.12p
  --b_ace_file=5000.12p:filepath
  --b_ace_file_start_line=5000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(XSSEPRDataExtractorPbv12 DEPENDS tstXSSEPRDataExtractorPbv12.cpp)
FRENSIE_ADD_TEST(XSSEPRDataExtractorPbv12
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --pb_ace_table=82000.12p
  --pb_ace_file=82000.12p:filepath
  --pb_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(XSSEPRDataExtractorPbv14 DEPENDS tstXSSEPRDataExtractorPbv14.cpp)
FRENSIE_ADD_TEST(XSSEPRDataExtractorPbv14
  ACE_LIB_DEPENDS 82000.14p 
  EXTRA_ARGS
  --pb_ace14_table=82000.14p
  --pb_ace14_file=82000.14p:filepath
  --pb_ace14_file_start_line=82000.14p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(XSSSabDataExtractor_Continuous DEPENDS tstXSSSabDataExtractor_Continuous.cpp)
FRENSIE_ADD_TEST(XSSSabDataExtractor_Continuous 
ACE_LIB_DEPENDS lwtr.20t grph.20t poly.20t
EXTRA_ARGS
--test_inelastic_only_sab_ace_file="test_h2o_sab_ace_file.txt" 
--test_inelastic_only_sab_ace_table="lwtr.20t" 
--test_no_elastic_dist_sab_ace_file="test_grph_sab_ace_file.txt" 
--test_no_elastic_dist_sab_ace_table="grph.20t" 
--test_full_sab_ace_file="test_poly_sab_ace_file.txt" 
--test_full_sab_ace_table="poly.20t")

FRENSIE_ADD_TEST_EXECUTABLE(XSSSabDataExtractor_Discrete DEPENDS tstXSSSabDataExtractor_Discrete.cpp)
FRENSIE_ADD_TEST(XSSSabDataExtractor_Discrete 
ACE_LIB_DEPENDS lwtr.60t grph.60t poly.60t
EXTRA_ARGS
--test_inelastic_only_sab_ace_file="lwtr.60t" 
--test_inelastic_only_sab_ace_table="lwtr.60t" 
--test_no_elastic_dist_sab_ace_file="grph.60t" 
--test_no_elastic_dist_sab_ace_table="grph.60t" 
--test_full_sab_ace_file="poly.60t" 
--test_full_sab_ace_table="poly.60t")

FRENSIE_ADD_TEST_EXECUTABLE(ACETableName DEPENDS tstACETableName.cpp)
FRENSIE_ADD_TEST(ACETableName)

FRENSIE_ADD_TEST_EXECUTABLE(ACENuclearDataProperties DEPENDS tstACENuclearDataProperties.cpp)
FRENSIE_ADD_TEST(ACENuclearDataProperties)

FRENSIE_ADD_TEST_EXECUTABLE(ACEThermalNuclearDataProperties DEPENDS tstACEThermalNuclearDataProperties.cpp)
FRENSIE_ADD_TEST(ACEThermalNuclearDataProperties)

FRENSIE_ADD_TEST_EXECUTABLE(ACEPhotonuclearDataProperties DEPENDS tstACEPhotonuclearDataProperties.cpp)
FRENSIE_ADD_TEST(ACEPhotonuclearDataProperties)

FRENSIE_ADD_TEST_EXECUTABLE(ACEPhotoatomicDataProperties DEPENDS tstACEPhotoatomicDataProperties.cpp)
FRENSIE_ADD_TEST(ACEPhotoatomicDataProperties)

FRENSIE_ADD_TEST_EXECUTABLE(ACEElectroatomicDataProperties DEPENDS tstACEElectroatomicDataProperties.cpp)
FRENSIE_ADD_TEST(ACEElectroatomicDataProperties)

FRENSIE_FINALIZE_PACKAGE_TESTS(data_ace)
