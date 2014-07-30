 ADD_EXECUTABLE(tstACEFileHandler
  tstACEFileHandler.cpp)
TARGET_LINK_LIBRARIES(tstACEFileHandler data_ace)
ADD_TEST(ACEFileHandler_test tstACEFileHandler --test_neutron_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h1_ace_file.txt" --test_sab_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h2o_sab_ace_file.txt")

ADD_EXECUTABLE(tstXSSNeutronDataExtractor
  tstXSSNeutronDataExtractor.cpp)
TARGET_LINK_LIBRARIES(tstXSSNeutronDataExtractor data_ace)
ADD_TEST(XSSNeutronDataExtractor_test tstXSSNeutronDataExtractor --test_h1_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h1_ace_file.txt" --test_h1_ace_table="1001.70c")

ADD_EXECUTABLE(tstXSSSabDataExtractor
  tstXSSSabDataExtractor.cpp)
TARGET_LINK_LIBRARIES(tstXSSSabDataExtractor data_ace)
ADD_TEST(XSSSabDataExtractor_test tstXSSSabDataExtractor --test_inelastic_only_sab_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h2o_sab_ace_file.txt" --test_inelastic_only_sab_ace_table="lwtr.10t" --test_no_elastic_dist_sab_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_grph_sab_ace_file.txt" --test_no_elastic_dist_sab_ace_table="grph.10t" --test_full_sab_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_poly_sab_ace_file.txt" --test_full_sab_ace_table="poly.10t")

ADD_EXECUTABLE(tstXSSPhotoatomicDataExtractor
  tstXSSPhotoatomicDataExtractor.cpp)
TARGET_LINK_LIBRARIES(tstXSSPhotoatomicDataExtractor data_ace)
ADD_TEST(XSSPhotoatomicDataExtractor_test tstXSSPhotoatomicDataExtractor --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_photoatomic_ace_file.txt" --test_ace_table="82000.04p")
