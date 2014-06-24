ADD_EXECUTABLE(tstFissionableIsotopes 
  tstFissionableIsotopes.cpp )
TARGET_LINK_LIBRARIES(tstFissionableIsotopes transmutation)
ADD_TEST(FissionableIsotopes_test tstFissionableIsotopes)

ADD_EXECUTABLE(tstAllIsotopes 
  tstAllIsotopes.cpp )
TARGET_LINK_LIBRARIES(tstAllIsotopes transmutation)
ADD_TEST(AllIsotopes_test tstAllIsotopes --z_number="49")

ADD_EXECUTABLE(tstIsotopesForDepletion 
  tstIsotopesForDepletion.cpp )
TARGET_LINK_LIBRARIES(tstIsotopesForDepletion transmutation)
ADD_TEST(IsotopesForDepletion_test tstIsotopesForDepletion
--xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/endf7.dk.xml"
--endf_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/U_235.txt"
--zaid_name="92235")
