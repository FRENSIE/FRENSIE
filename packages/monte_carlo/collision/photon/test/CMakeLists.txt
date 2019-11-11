FRENSIE_INITIALIZE_PACKAGE_TESTS(monte_carlo_collision_photon)

##---------------------------------------------------------------------------##
## Support class tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(PhotoatomicReactionType DEPENDS tstPhotoatomicReactionType.cpp)
FRENSIE_ADD_TEST(PhotoatomicReactionType)

FRENSIE_ADD_TEST_EXECUTABLE(PhotonuclearReactionType DEPENDS tstPhotonuclearReactionType.cpp)
FRENSIE_ADD_TEST(PhotonuclearReactionType)

FRENSIE_ADD_TEST_EXECUTABLE(AdjointPhotoatomicReactionType DEPENDS tstAdjointPhotoatomicReactionType.cpp)
FRENSIE_ADD_TEST(AdjointPhotoatomicReactionType)

FRENSIE_ADD_TEST_EXECUTABLE(PhotonKinematicsHelpers DEPENDS tstPhotonKinematicsHelpers.cpp)
FRENSIE_ADD_TEST(PhotonKinematicsHelpers)

FRENSIE_ADD_TEST_EXECUTABLE(AdjointPhotonKinematicsHelpers DEPENDS tstAdjointPhotonKinematicsHelpers.cpp)
FRENSIE_ADD_TEST(AdjointPhotonKinematicsHelpers)

FRENSIE_ADD_TEST_EXECUTABLE(BasicComptonProfileSubshellConverter DEPENDS tstBasicComptonProfileSubshellConverter.cpp)
FRENSIE_ADD_TEST(BasicComptonProfileSubshellConverter)

FRENSIE_ADD_TEST_EXECUTABLE(StandardComptonProfileSubshellConverter DEPENDS tstStandardComptonProfileSubshellConverter.cpp)
FRENSIE_ADD_TEST(StandardComptonProfileSubshellConverter)



FRENSIE_ADD_TEST_EXECUTABLE(ComptonProfileHelpers DEPENDS tstComptonProfileHelpers.cpp)
FRENSIE_ADD_TEST(ComptonProfileHelpers)

FRENSIE_ADD_TEST_EXECUTABLE(StandardComptonProfile DEPENDS tstStandardComptonProfile.cpp)
FRENSIE_ADD_TEST(StandardComptonProfile)

FRENSIE_ADD_TEST_EXECUTABLE(StandardOccupationNumber DEPENDS tstStandardOccupationNumber.cpp)
FRENSIE_ADD_TEST(StandardOccupationNumber)

FRENSIE_ADD_TEST_EXECUTABLE(StandardScatteringFunction DEPENDS tstStandardScatteringFunction.cpp)
FRENSIE_ADD_TEST(StandardScatteringFunction)

FRENSIE_ADD_TEST_EXECUTABLE(StandardFormFactor DEPENDS tstStandardFormFactor.cpp)
FRENSIE_ADD_TEST(StandardFormFactor)

FRENSIE_ADD_TEST_EXECUTABLE(StandardFormFactorSquared DEPENDS tstStandardFormFactorSquared.cpp)
FRENSIE_ADD_TEST(StandardFormFactorSquared)

FRENSIE_ADD_TEST_EXECUTABLE(CoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution DEPENDS tstCoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution.cpp)
FRENSIE_ADD_TEST(CoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution DEPENDS tstDecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution.cpp)
FRENSIE_ADD_TEST(DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(StandardSubshellDopplerBroadenedPhotonEnergyDistribution DEPENDS tstStandardSubshellDopplerBroadenedPhotonEnergyDistribution.cpp)
FRENSIE_ADD_TEST(StandardSubshellDopplerBroadenedPhotonEnergyDistribution
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml)

##---------------------------------------------------------------------------##
## Scattering distribution tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(IncoherentAdjointPhotonScatteringDistribution DEPENDS tstIncoherentAdjointPhotonScatteringDistribution.cpp)
FRENSIE_ADD_TEST(IncoherentAdjointPhotonScatteringDistribution)

FRENSIE_ADD_TEST_EXECUTABLE(KleinNishinaPhotonScatteringDistribution DEPENDS tstKleinNishinaPhotonScatteringDistribution.cpp)
FRENSIE_ADD_TEST(KleinNishinaPhotonScatteringDistribution)

FRENSIE_ADD_TEST_EXECUTABLE(KleinNishinaAdjointPhotonScatteringDistribution DEPENDS tstKleinNishinaAdjointPhotonScatteringDistribution.cpp)
FRENSIE_ADD_TEST(KleinNishinaAdjointPhotonScatteringDistribution)

FRENSIE_ADD_TEST_EXECUTABLE(DetailedWHIncoherentPhotonScatteringDistribution DEPENDS tstDetailedWHIncoherentPhotonScatteringDistribution.cpp)
FRENSIE_ADD_TEST(DetailedWHIncoherentPhotonScatteringDistribution
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(WHIncoherentAdjointPhotonScatteringDistribution DEPENDS tstWHIncoherentAdjointPhotonScatteringDistribution.cpp)
FRENSIE_ADD_TEST(WHIncoherentAdjointPhotonScatteringDistribution
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(DopplerBroadenedHybridIncoherentPhotonScatteringDistribution DEPENDS tstDopplerBroadenedHybridIncoherentPhotonScatteringDistribution.cpp)
FRENSIE_ADD_TEST(DopplerBroadenedHybridIncoherentPhotonScatteringDistribution
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(SubshellIncoherentPhotonScatteringDistribution DEPENDS tstSubshellIncoherentPhotonScatteringDistribution.cpp)
FRENSIE_ADD_TEST(SubshellIncoherentPhotonScatteringDistribution
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(SubshellIncoherentAdjointPhotonScatteringDistribution DEPENDS tstSubshellIncoherentAdjointPhotonScatteringDistribution.cpp)
FRENSIE_ADD_TEST(SubshellIncoherentAdjointPhotonScatteringDistribution
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(DopplerBroadenedSubshellIncoherentPhotonScatteringDistribution DEPENDS tstDopplerBroadenedSubshellIncoherentPhotonScatteringDistribution.cpp)
FRENSIE_ADD_TEST(DopplerBroadenedSubshellIncoherentPhotonScatteringDistribution
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution DEPENDS tstDopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution.cpp)
FRENSIE_ADD_TEST(DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(ThompsonScatteringDistribution DEPENDS tstThompsonScatteringDistribution.cpp)
FRENSIE_ADD_TEST(ThompsonScatteringDistribution)

FRENSIE_ADD_TEST_EXECUTABLE(BasicCoherentScatteringDistribution DEPENDS tstBasicCoherentScatteringDistribution.cpp)
FRENSIE_ADD_TEST(BasicCoherentScatteringDistribution
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(EfficientCoherentScatteringDistribution DEPENDS tstEfficientCoherentScatteringDistribution.cpp)
FRENSIE_ADD_TEST(EfficientCoherentScatteringDistribution
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(LineEnergyAdjointPhotonScatteringDistribution DEPENDS tstLineEnergyAdjointPhotonScatteringDistribution.cpp)
FRENSIE_ADD_TEST(LineEnergyAdjointPhotonScatteringDistribution
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_14_native.xml)

##---------------------------------------------------------------------------##
## Scattering distribution factory tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(IncoherentPhotonScatteringDistributionACEFactory DEPENDS tstIncoherentPhotonScatteringDistributionACEFactory.cpp)
FRENSIE_ADD_TEST(IncoherentPhotonScatteringDistributionACEFactory
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(IncoherentPhotonScatteringDistributionNativeFactory DEPENDS tstIncoherentPhotonScatteringDistributionNativeFactory.cpp)
FRENSIE_ADD_TEST(IncoherentPhotonScatteringDistributionNativeFactory
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(IncoherentAdjointPhotonScatteringDistributionNativeFactory DEPENDS tstIncoherentAdjointPhotonScatteringDistributionNativeFactory.cpp)
FRENSIE_ADD_TEST(IncoherentAdjointPhotonScatteringDistributionNativeFactory
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_14_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(LineEnergyAdjointPhotonScatteringDistributionNativeFactory DEPENDS tstLineEnergyAdjointPhotonScatteringDistributionNativeFactory.cpp)
FRENSIE_ADD_TEST(LineEnergyAdjointPhotonScatteringDistributionNativeFactory
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_14_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(CoherentScatteringDistributionACEFactory DEPENDS tstCoherentScatteringDistributionACEFactory.cpp)
FRENSIE_ADD_TEST(CoherentScatteringDistributionACEFactory
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(CoherentScatteringDistributionNativeFactory DEPENDS tstCoherentScatteringDistributionNativeFactory.cpp)
FRENSIE_ADD_TEST(CoherentScatteringDistributionNativeFactory
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(PhotonuclearScatteringDistributionACEFactory DEPENDS tstPhotonuclearScatteringDistributionACEFactory.cpp)
FRENSIE_ADD_TEST(PhotonuclearScatteringDistributionACEFactory
  ACE_LIB_DEPENDS 6012.24u
  EXTRA_ARGS
  --test_ace_file=6012.24u:filepath
  --test_ace_file_start_line=6012.24u:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(PhotonuclearNeutronScatteringDistributionACEFactory DEPENDS tstPhotonuclearNeutronScatteringDistributionACEFactory.cpp)
FRENSIE_ADD_TEST(PhotonuclearNeutronScatteringDistributionACEFactory
  ACE_LIB_DEPENDS 1002.24u
  EXTRA_ARGS
  --test_ace_file=1002.24u:filepath
  --test_ace_file_start_line=1002.24u:filestartline)

##---------------------------------------------------------------------------##
## Reaction tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(StandardPhotoatomicReaction DEPENDS tstStandardPhotoatomicReaction.cpp)
FRENSIE_ADD_TEST(StandardPhotoatomicReaction
  ACE_LIB_DEPENDS 82000.04p
  EXTRA_ARGS
  --test_ace_file=82000.04p:filepath
  --test_ace_file_start_line=82000.04p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(PairProductionPhotoatomicReaction DEPENDS tstPairProductionPhotoatomicReaction.cpp)
FRENSIE_ADD_TEST(PairProductionPhotoatomicReaction
  ACE_LIB_DEPENDS 82000.04p
  EXTRA_ARGS
  --test_ace_file=82000.04p:filepath
  --test_ace_file_start_line=82000.04p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(TripletProductionPhotoatomicReaction DEPENDS tstTripletProductionPhotoatomicReaction.cpp)
FRENSIE_ADD_TEST(TripletProductionPhotoatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(IncoherentPhotoatomicReaction DEPENDS tstIncoherentPhotoatomicReaction.cpp)
FRENSIE_ADD_TEST(IncoherentPhotoatomicReaction
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(IncoherentAdjointPhotoatomicReaction DEPENDS tstIncoherentAdjointPhotoatomicReaction.cpp)
FRENSIE_ADD_TEST(IncoherentAdjointPhotoatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_14_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(SubshellIncoherentPhotoatomicReaction DEPENDS tstSubshellIncoherentPhotoatomicReaction.cpp)
FRENSIE_ADD_TEST(SubshellIncoherentPhotoatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(SubshellIncoherentAdjointPhotoatomicReaction DEPENDS tstSubshellIncoherentAdjointPhotoatomicReaction.cpp)
FRENSIE_ADD_TEST(SubshellIncoherentAdjointPhotoatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_14_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(CoherentPhotoatomicReaction DEPENDS tstCoherentPhotoatomicReaction.cpp)
FRENSIE_ADD_TEST(CoherentPhotoatomicReaction
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(CoherentAdjointPhotoatomicReaction DEPENDS tstCoherentAdjointPhotoatomicReaction.cpp)
FRENSIE_ADD_TEST(CoherentAdjointPhotoatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_14_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(PhotoelectricPhotoatomicReaction DEPENDS tstPhotoelectricPhotoatomicReaction.cpp)
FRENSIE_ADD_TEST(PhotoelectricPhotoatomicReaction
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(SubshellPhotoelectricPhotoatomicReaction DEPENDS tstSubshellPhotoelectricPhotoatomicReaction.cpp)
FRENSIE_ADD_TEST(SubshellPhotoelectricPhotoatomicReaction
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(LineEnergyAdjointPhotoatomicReaction DEPENDS tstLineEnergyAdjointPhotoatomicReaction.cpp)
FRENSIE_ADD_TEST(LineEnergyAdjointPhotoatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_14_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(AbsorptionPhotoatomicReaction DEPENDS tstAbsorptionPhotoatomicReaction.cpp)
FRENSIE_ADD_TEST(AbsorptionPhotoatomicReaction
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(StandardPhotonuclearReactionH2 DEPENDS tstStandardPhotonuclearReactionH2.cpp)
FRENSIE_ADD_TEST(StandardPhotonuclearReactionH2
  ACE_LIB_DEPENDS 1002.24u
  EXTRA_ARGS
  --h2_ace_file=1002.24u:filepath
  --h2_ace_file_start_line=1002.24u:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(StandardPhotonuclearReactionC12 DEPENDS tstStandardPhotonuclearReactionC12.cpp)
FRENSIE_ADD_TEST(StandardPhotonuclearReactionC12
  ACE_LIB_DEPENDS 6012.24u
  EXTRA_ARGS
  --c12_ace_file=6012.24u:filepath
  --c12_ace_file_start_line=6012.24u:filestartline)

##---------------------------------------------------------------------------##
## Reaction factory tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(PhotoatomicReactionACEFactory DEPENDS tstPhotoatomicReactionACEFactory.cpp)
FRENSIE_ADD_TEST(PhotoatomicReactionACEFactory
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(PhotoatomicReactionNativeFactory DEPENDS tstPhotoatomicReactionNativeFactory.cpp)
FRENSIE_ADD_TEST(PhotoatomicReactionNativeFactory
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(AdjointPhotoatomicReactionNativeFactory DEPENDS tstAdjointPhotoatomicReactionNativeFactory.cpp)
FRENSIE_ADD_TEST(AdjointPhotoatomicReactionNativeFactory
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_14_native.xml)

##---------------------------------------------------------------------------##
## Scattering center tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(PhotoatomCore DEPENDS tstPhotoatomCore.cpp)
FRENSIE_ADD_TEST(PhotoatomCore
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(AdjointPhotoatomCore DEPENDS tstAdjointPhotoatomCore.cpp)
FRENSIE_ADD_TEST(AdjointPhotoatomCore
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_14_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(Photoatom DEPENDS tstPhotoatom.cpp)
FRENSIE_ADD_TEST(Photoatom
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(AdjointPhotoatom DEPENDS tstAdjointPhotoatom.cpp)
FRENSIE_ADD_TEST(AdjointPhotoatom
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_14_native.xml)

##---------------------------------------------------------------------------##
## Scattering center factory tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(PhotoatomACEFactory DEPENDS tstPhotoatomACEFactory.cpp)
FRENSIE_ADD_TEST(PhotoatomACEFactory
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(AdjointPhotoatomNativeFactory DEPENDS tstAdjointPhotoatomNativeFactory.cpp)
  FRENSIE_ADD_TEST(AdjointPhotoatomNativeFactory
    EXTRA_ARGS
    --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_14_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(PhotoatomFactory
  DEPENDS tstPhotoatomFactory.cpp
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
FRENSIE_ADD_TEST(PhotoatomFactory
  ACE_LIB_DEPENDS 1000.12p 82000.12p
  EXTRA_ARGS
  --test_database=${COLLISION_DATABASE_XML_FILE})

FRENSIE_ADD_TEST_EXECUTABLE(AdjointPhotoatomFactory
  DEPENDS tstAdjointPhotoatomFactory.cpp
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
FRENSIE_ADD_TEST(AdjointPhotoatomFactory
  EXTRA_ARGS
  --test_database=${COLLISION_DATABASE_XML_FILE})

##---------------------------------------------------------------------------##
## Material tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(PhotonMaterial
  DEPENDS tstPhotonMaterial.cpp
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
FRENSIE_ADD_TEST(PhotonMaterial
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_database=${COLLISION_DATABASE_XML_FILE})

FRENSIE_ADD_TEST_EXECUTABLE(AdjointPhotonMaterial
  DEPENDS tstAdjointPhotonMaterial.cpp
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
FRENSIE_ADD_TEST(AdjointPhotonMaterial
  EXTRA_ARGS
  --test_database=${COLLISION_DATABASE_XML_FILE})

FRENSIE_FINALIZE_PACKAGE_TESTS(monte_carlo_collision_photon)
