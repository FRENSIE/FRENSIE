ADD_EXECUTABLE(tstOccupationNumberEvaluator tstOccupationNumberEvaluator.cpp)
TARGET_LINK_LIBRARIES(tstOccupationNumberEvaluator data_gen_photon)
ADD_TEST(OccupatioNumberEvaluator_test tstOccupationNumberEvaluator --test_h_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h_epr_ace_file.txt" --test_h_ace_table="1000.12p" --test_pb_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_pb_ace_table="82000.12p")

ADD_EXECUTABLE(tstSubshellIncoherentCrossSectionEvaluator tstSubshellIncoherentCrossSectionEvaluator.cpp)
TARGET_LINK_LIBRARIES(tstSubshellIncoherentCrossSectionEvaluator data_gen_photon)
ADD_TEST(SubshellIncoherentCrossSectionEvaluator_test tstSubshellIncoherentCrossSectionEvaluator --test_h_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h_epr_ace_file.txt" --test_h_ace_table="1000.12p" --test_b_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_b_epr_ace_file.txt" --test_b_ace_table="5000.12p")