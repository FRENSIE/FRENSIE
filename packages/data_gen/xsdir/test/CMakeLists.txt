ADD_EXECUTABLE(tstXsdirEntry 
  tstXsdirEntry.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstXsdirEntry data_gen_xsdir)
ADD_TEST(XsdirEntry_test tstXsdirEntry)
SET_PROPERTY(TEST XsdirEntry_test PROPERTY LABELS data_gen_xsdir xsdir)

ADD_EXECUTABLE(tstContinuousEnergyNeutronXsdirEntry 
  tstContinuousEnergyNeutronXsdirEntry.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstContinuousEnergyNeutronXsdirEntry data_gen_xsdir)
ADD_TEST(ContinuousEnergyNeutronXsdirEntry_test tstContinuousEnergyNeutronXsdirEntry)
SET_PROPERTY(TEST ContinuousEnergyNeutronXsdirEntry_test PROPERTY LABELS data_gen_xsdir xsdir neutron)

ADD_EXECUTABLE(tstSAlphaBetaXsdirEntry 
  tstSAlphaBetaXsdirEntry.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstSAlphaBetaXsdirEntry data_gen_xsdir)
ADD_TEST(SAlphaBetaXsdirEntry_test tstSAlphaBetaXsdirEntry)
SET_PROPERTY(TEST SAlphaBetaXsdirEntry_test PROPERTY LABELS data_gen_xsdir xsdir sab)

ADD_EXECUTABLE(tstElectronPhotonRelaxationXsdirEntry 
  tstElectronPhotonRelaxationXsdirEntry.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstElectronPhotonRelaxationXsdirEntry data_gen_xsdir)
ADD_TEST(ElectronPhotonRelaxationXsdirEntry_test tstElectronPhotonRelaxationXsdirEntry)
SET_PROPERTY(TEST ElectronPhotonRelaxationXsdirEntry_test PROPERTY LABELS data_gen_xsdir xsdir electron photon relaxation)

ADD_EXECUTABLE(tstPhotonuclearXsdirEntry 
  tstPhotonuclearXsdirEntry.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPhotonuclearXsdirEntry data_gen_xsdir)
ADD_TEST(PhotonuclearXsdirEntry_test tstPhotonuclearXsdirEntry)
SET_PROPERTY(TEST PhotonuclearXsdirEntry_test PROPERTY LABELS data_gen_xsdir xsdir photon)

ADD_EXECUTABLE(tstXsdirEntryFactory 
  tstXsdirEntryFactory.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstXsdirEntryFactory data_gen_xsdir)
ADD_TEST(XsdirEntryFactory_test tstXsdirEntryFactory)
SET_PROPERTY(TEST XsdirEntryFactory_test PROPERTY LABELS data_gen_xsdir xsdir)

ADD_EXECUTABLE(tstXsdir tstXsdir.cpp )
TARGET_LINK_LIBRARIES(tstXsdir data_gen_xsdir)
ADD_TEST(Xsdir_test tstXsdir --test_xsdir_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_xsdir")
SET_PROPERTY(TEST Xsdir_test PROPERTY LABELS data_gen_xsdir xsdir)
