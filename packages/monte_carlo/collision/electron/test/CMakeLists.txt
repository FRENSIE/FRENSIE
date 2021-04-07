FRENSIE_INITIALIZE_PACKAGE_TESTS(monte_carlo_collision_electron)

##---------------------------------------------------------------------------##
## Support class tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(ElectroatomicReactionType DEPENDS tstElectroatomicReactionType.cpp)
FRENSIE_ADD_TEST(ElectroatomicReactionType)

FRENSIE_ADD_TEST_EXECUTABLE(AdjointElectroatomicReactionType DEPENDS tstAdjointElectroatomicReactionType.cpp)
FRENSIE_ADD_TEST(AdjointElectroatomicReactionType)

FRENSIE_ADD_TEST_EXECUTABLE(PositronatomicReactionType DEPENDS tstPositronatomicReactionType.cpp)
FRENSIE_ADD_TEST(PositronatomicReactionType)

FRENSIE_ADD_TEST_EXECUTABLE(ElasticElectronTraits DEPENDS tstElasticElectronTraits.cpp)
FRENSIE_ADD_TEST(ElasticElectronTraits)

FRENSIE_ADD_TEST_EXECUTABLE(CoupledElasticDistribution DEPENDS tstCoupledElasticDistribution.cpp)
FRENSIE_ADD_TEST(CoupledElasticDistribution)

FRENSIE_ADD_TEST_EXECUTABLE(LinLinLinCoupledElasticBasicBivariateDistribution DEPENDS tstLinLinLinCoupledElasticBasicBivariateDistribution.cpp)
FRENSIE_ADD_TEST(LinLinLinCoupledElasticBasicBivariateDistribution)

FRENSIE_ADD_TEST_EXECUTABLE(LogLogLogCoupledElasticBasicBivariateDistribution DEPENDS tstLogLogLogCoupledElasticBasicBivariateDistribution.cpp)
FRENSIE_ADD_TEST(LogLogLogCoupledElasticBasicBivariateDistribution)

FRENSIE_ADD_TEST_EXECUTABLE(LogLogLogCutoffElasticBasicBivariateDistribution DEPENDS tstLogLogLogCutoffElasticBasicBivariateDistribution.cpp)
FRENSIE_ADD_TEST(LogLogLogCutoffElasticBasicBivariateDistribution)

##---------------------------------------------------------------------------##
## Scattering distribution tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(CutoffElasticElectronScatteringDistributionACE DEPENDS tstCutoffElasticElectronScatteringDistributionACE.cpp)
FRENSIE_ADD_TEST(CutoffElasticElectronScatteringDistributionACE
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(CutoffElasticElectronScatteringDistributionNative DEPENDS tstCutoffElasticElectronScatteringDistributionNative.cpp)
FRENSIE_ADD_TEST(CutoffElasticElectronScatteringDistributionNative
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(ScreenedRutherfordElasticElectronScatteringDistribution DEPENDS tstScreenedRutherfordElasticElectronScatteringDistribution.cpp)
FRENSIE_ADD_TEST(ScreenedRutherfordElasticElectronScatteringDistribution
  EXTRA_ARGS
  --test_native_pb_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml
  --test_native_al_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_13_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(CoupledElasticElectronScatteringDistribution DEPENDS tstCoupledElasticElectronScatteringDistribution.cpp)
FRENSIE_ADD_TEST(CoupledElasticElectronScatteringDistribution
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_1_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(MomentPreservingElasticElectronScatteringDistribution DEPENDS tstMomentPreservingElasticElectronScatteringDistribution.cpp)
FRENSIE_ADD_TEST(MomentPreservingElasticElectronScatteringDistribution
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_13_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(HybridElasticElectronScatteringDistribution DEPENDS tstHybridElasticElectronScatteringDistribution.cpp)
FRENSIE_ADD_TEST(HybridElasticElectronScatteringDistribution
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_13_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(AtomicExcitationElectronScatteringDistribution DEPENDS tstAtomicExcitationElectronScatteringDistribution.cpp)
FRENSIE_ADD_TEST(AtomicExcitationElectronScatteringDistribution
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(AtomicExcitationAdjointElectronScatteringDistributionACE DEPENDS tstAtomicExcitationAdjointElectronScatteringDistributionACE.cpp)
FRENSIE_ADD_TEST(AtomicExcitationAdjointElectronScatteringDistributionACE
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(AtomicExcitationAdjointElectronScatteringDistributionNative DEPENDS tstAtomicExcitationAdjointElectronScatteringDistributionNative.cpp)
FRENSIE_ADD_TEST(AtomicExcitationAdjointElectronScatteringDistributionNative
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(BremsstrahlungElectronScatteringDistributionACE DEPENDS tstBremsstrahlungElectronScatteringDistributionACE.cpp)
FRENSIE_ADD_TEST(BremsstrahlungElectronScatteringDistributionACE
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(BremsstrahlungElectronScatteringDistributionNative DEPENDS tstBremsstrahlungElectronScatteringDistributionNative.cpp)
FRENSIE_ADD_TEST(BremsstrahlungElectronScatteringDistributionNative
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_13_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(BremsstrahlungAdjointElectronScatteringDistribution DEPENDS tstBremsstrahlungAdjointElectronScatteringDistribution.cpp)
FRENSIE_ADD_TEST(BremsstrahlungAdjointElectronScatteringDistribution
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml )

FRENSIE_ADD_TEST_EXECUTABLE(ElectroionizationSubshellElectronScatteringDistributionACE DEPENDS tstElectroionizationSubshellElectronScatteringDistributionACE.cpp)
FRENSIE_ADD_TEST(ElectroionizationSubshellElectronScatteringDistributionACE
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(ElectroionizationSubshellElectronScatteringDistributionNative DEPENDS tstElectroionizationSubshellElectronScatteringDistributionNative.cpp)
FRENSIE_ADD_TEST(ElectroionizationSubshellElectronScatteringDistributionNative
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_13_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(ElectroionizationSubshellAdjointElectronScatteringDistribution DEPENDS tstElectroionizationSubshellAdjointElectronScatteringDistribution.cpp)
FRENSIE_ADD_TEST(ElectroionizationSubshellAdjointElectronScatteringDistribution
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)

##---------------------------------------------------------------------------##
## Scattering distribution factory tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(ElasticElectronScatteringDistributionACEFactoryV12 DEPENDS tstElasticElectronScatteringDistributionACEFactoryV12.cpp)
FRENSIE_ADD_TEST(ElasticElectronScatteringDistributionACEFactoryV12
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace12_file=82000.12p:filepath
  --test_ace12_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(ElasticElectronScatteringDistributionACEFactoryV14 DEPENDS tstElasticElectronScatteringDistributionACEFactoryV14.cpp)
FRENSIE_ADD_TEST(ElasticElectronScatteringDistributionACEFactoryV14
  ACE_LIB_DEPENDS 82000.14p
  EXTRA_ARGS
  --test_ace14_file=82000.14p:filepath
  --test_ace14_file_start_line=82000.14p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(AtomicExcitationElectronScatteringDistributionACEFactoryV12 DEPENDS tstAtomicExcitationElectronScatteringDistributionACEFactoryV12.cpp)
FRENSIE_ADD_TEST(AtomicExcitationElectronScatteringDistributionACEFactoryV12
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace12_file=82000.12p:filepath
  --test_ace12_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(AtomicExcitationElectronScatteringDistributionACEFactoryV14 DEPENDS tstAtomicExcitationElectronScatteringDistributionACEFactoryV14.cpp)
FRENSIE_ADD_TEST(AtomicExcitationElectronScatteringDistributionACEFactoryV14
  ACE_LIB_DEPENDS 82000.14p
  EXTRA_ARGS
  --test_ace14_file=82000.14p:filepath
  --test_ace14_file_start_line=82000.14p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(BremsstrahlungElectronScatteringDistributionACEFactoryV12 DEPENDS tstBremsstrahlungElectronScatteringDistributionACEFactoryV12.cpp)
FRENSIE_ADD_TEST(BremsstrahlungElectronScatteringDistributionACEFactoryV12
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace12_file=82000.12p:filepath
  --test_ace12_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(BremsstrahlungElectronScatteringDistributionACEFactoryV14 DEPENDS tstBremsstrahlungElectronScatteringDistributionACEFactoryV14.cpp)
FRENSIE_ADD_TEST(BremsstrahlungElectronScatteringDistributionACEFactoryV14
  ACE_LIB_DEPENDS 82000.14p
  EXTRA_ARGS
  --test_ace14_file=82000.14p:filepath
  --test_ace14_file_start_line=82000.14p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(ElectroionizationSubshellElectronScatteringDistributionACEFactoryV12 DEPENDS tstElectroionizationSubshellElectronScatteringDistributionACEFactoryV12.cpp)
FRENSIE_ADD_TEST(ElectroionizationSubshellElectronScatteringDistributionACEFactoryV12
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace12_file=82000.12p:filepath
  --test_ace12_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(ElectroionizationSubshellElectronScatteringDistributionACEFactoryV14 DEPENDS tstElectroionizationSubshellElectronScatteringDistributionACEFactoryV14.cpp)
FRENSIE_ADD_TEST(ElectroionizationSubshellElectronScatteringDistributionACEFactoryV14
  ACE_LIB_DEPENDS 82000.14p
  EXTRA_ARGS
  --test_ace14_file=82000.14p:filepath
  --test_ace14_file_start_line=82000.14p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(ElasticElectronScatteringDistributionNativeFactory DEPENDS tstElasticElectronScatteringDistributionNativeFactory.cpp)
FRENSIE_ADD_TEST(ElasticElectronScatteringDistributionNativeFactory
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml --test_adjoint_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(AtomicExcitationElectronScatteringDistributionNativeFactory DEPENDS tstAtomicExcitationElectronScatteringDistributionNativeFactory.cpp)
FRENSIE_ADD_TEST(AtomicExcitationElectronScatteringDistributionNativeFactory
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(BremsstrahlungElectronScatteringDistributionNativeFactory DEPENDS tstBremsstrahlungElectronScatteringDistributionNativeFactory.cpp)
FRENSIE_ADD_TEST(BremsstrahlungElectronScatteringDistributionNativeFactory
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml )

FRENSIE_ADD_TEST_EXECUTABLE(ElectroionizationSubshellElectronScatteringDistributionNativeFactory DEPENDS tstElectroionizationSubshellElectronScatteringDistributionNativeFactory.cpp)
FRENSIE_ADD_TEST(ElectroionizationSubshellElectronScatteringDistributionNativeFactory
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml )

FRENSIE_ADD_TEST_EXECUTABLE(AtomicExcitationAdjointElectronScatteringDistributionNativeFactory DEPENDS tstAtomicExcitationAdjointElectronScatteringDistributionNativeFactory.cpp)
FRENSIE_ADD_TEST(AtomicExcitationAdjointElectronScatteringDistributionNativeFactory
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(BremsstrahlungAdjointElectronScatteringDistributionNativeFactory DEPENDS tstBremsstrahlungAdjointElectronScatteringDistributionNativeFactory.cpp)
FRENSIE_ADD_TEST(BremsstrahlungAdjointElectronScatteringDistributionNativeFactory
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory DEPENDS tstElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory.cpp)
FRENSIE_ADD_TEST(ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)


##---------------------------------------------------------------------------##
## Reaction tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(PositronatomicReaction DEPENDS tstPositronatomicReaction.cpp)
FRENSIE_ADD_TEST(PositronatomicReaction)

FRENSIE_ADD_TEST_EXECUTABLE(AbsorptionElectroatomicReaction DEPENDS tstAbsorptionElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(AbsorptionElectroatomicReaction
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(AbsorptionAdjointElectroatomicReaction DEPENDS tstAbsorptionAdjointElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(AbsorptionAdjointElectroatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(CutoffElasticElectroatomicReaction DEPENDS tstCutoffElasticElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(CutoffElasticElectroatomicReaction
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(CutoffElasticPositronatomicReaction DEPENDS tstCutoffElasticPositronatomicReaction.cpp)
FRENSIE_ADD_TEST(CutoffElasticPositronatomicReaction
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(CutoffElasticAdjointElectroatomicReaction DEPENDS tstCutoffElasticAdjointElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(CutoffElasticAdjointElectroatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(ScreenedRutherfordElasticElectroatomicReaction DEPENDS tstScreenedRutherfordElasticElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(ScreenedRutherfordElasticElectroatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_13_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(ScreenedRutherfordElasticPositronatomicReaction DEPENDS tstScreenedRutherfordElasticPositronatomicReaction.cpp)
FRENSIE_ADD_TEST(ScreenedRutherfordElasticPositronatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_13_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(ScreenedRutherfordElasticAdjointElectroatomicReaction DEPENDS tstScreenedRutherfordElasticAdjointElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(ScreenedRutherfordElasticAdjointElectroatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(CoupledElasticElectroatomicReaction DEPENDS tstCoupledElasticElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(CoupledElasticElectroatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_1_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(CoupledElasticPositronatomicReaction DEPENDS tstCoupledElasticPositronatomicReaction.cpp)
FRENSIE_ADD_TEST(CoupledElasticPositronatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_1_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(CoupledElasticAdjointElectroatomicReaction DEPENDS tstCoupledElasticAdjointElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(CoupledElasticAdjointElectroatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(DecoupledElasticElectroatomicReaction DEPENDS tstDecoupledElasticElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(DecoupledElasticElectroatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_1_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(DecoupledElasticPositronatomicReaction DEPENDS tstDecoupledElasticPositronatomicReaction.cpp)
FRENSIE_ADD_TEST(DecoupledElasticPositronatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_1_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(DecoupledElasticAdjointElectroatomicReaction DEPENDS tstDecoupledElasticAdjointElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(DecoupledElasticAdjointElectroatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(HybridElasticElectroatomicReaction DEPENDS tstHybridElasticElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(HybridElasticElectroatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_13_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(HybridElasticPositronatomicReaction DEPENDS tstHybridElasticPositronatomicReaction.cpp)
FRENSIE_ADD_TEST(HybridElasticPositronatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_13_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(HybridElasticAdjointElectroatomicReaction DEPENDS tstHybridElasticAdjointElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(HybridElasticAdjointElectroatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(MomentPreservingElasticElectroatomicReaction DEPENDS tstMomentPreservingElasticElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(MomentPreservingElasticElectroatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_13_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(MomentPreservingElasticPositronatomicReaction DEPENDS tstMomentPreservingElasticPositronatomicReaction.cpp)
FRENSIE_ADD_TEST(MomentPreservingElasticPositronatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_13_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(MomentPreservingElasticAdjointElectroatomicReaction DEPENDS tstMomentPreservingElasticAdjointElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(MomentPreservingElasticAdjointElectroatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(AtomicExcitationElectroatomicReaction DEPENDS tstAtomicExcitationElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(AtomicExcitationElectroatomicReaction
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(AtomicExcitationPositronatomicReaction DEPENDS tstAtomicExcitationPositronatomicReaction.cpp)
FRENSIE_ADD_TEST(AtomicExcitationPositronatomicReaction
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(AtomicExcitationAdjointElectroatomicReaction DEPENDS tstAtomicExcitationAdjointElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(AtomicExcitationAdjointElectroatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(BremsstrahlungElectroatomicReaction DEPENDS tstBremsstrahlungElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(BremsstrahlungElectroatomicReaction
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(BremsstrahlungPositronatomicReaction DEPENDS tstBremsstrahlungPositronatomicReaction.cpp)
FRENSIE_ADD_TEST(BremsstrahlungPositronatomicReaction
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(BremsstrahlungAdjointElectroatomicReaction DEPENDS tstBremsstrahlungAdjointElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(BremsstrahlungAdjointElectroatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(ElectroionizationElectroatomicReaction DEPENDS tstElectroionizationElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(ElectroionizationElectroatomicReaction
  ACE_LIB_DEPENDS 82000.14p
  EXTRA_ARGS
  --test_ace_file=82000.14p:filepath
  --test_ace_file_start_line=82000.14p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(ElectroionizationSubshellElectroatomicReactionACE DEPENDS tstElectroionizationSubshellElectroatomicReactionACE.cpp)
FRENSIE_ADD_TEST(ElectroionizationSubshellElectroatomicReactionACE
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(ElectroionizationSubshellElectroatomicReactionNative DEPENDS tstElectroionizationSubshellElectroatomicReactionNative.cpp)
FRENSIE_ADD_TEST(ElectroionizationSubshellElectroatomicReactionNative
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_6_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(PositronionizationSubshellPositronatomicReactionACE DEPENDS tstPositronionizationSubshellPositronatomicReactionACE.cpp)
FRENSIE_ADD_TEST(PositronionizationSubshellPositronatomicReactionACE
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(PositronionizationSubshellPositronatomicReactionNative DEPENDS tstPositronionizationSubshellPositronatomicReactionNative.cpp)
FRENSIE_ADD_TEST(PositronionizationSubshellPositronatomicReactionNative
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_6_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(ElectroionizationSubshellAdjointElectroatomicReaction DEPENDS tstElectroionizationSubshellAdjointElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(ElectroionizationSubshellAdjointElectroatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_6_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(VoidElectroatomicReaction DEPENDS tstVoidElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(VoidElectroatomicReaction
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(VoidAbsorptionElectroatomicReaction DEPENDS tstVoidAbsorptionElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(VoidAbsorptionElectroatomicReaction)

##---------------------------------------------------------------------------##
## Reaction factory tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(ElectroatomicReactionACEFactory DEPENDS tstElectroatomicReactionACEFactory.cpp)
FRENSIE_ADD_TEST(ElectroatomicReactionACEFactory
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(PositronatomicReactionACEFactory DEPENDS tstPositronatomicReactionACEFactory.cpp)
FRENSIE_ADD_TEST(PositronatomicReactionACEFactory
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(ElectroatomicReactionEPR14Factory DEPENDS tstElectroatomicReactionEPR14Factory.cpp)
FRENSIE_ADD_TEST(ElectroatomicReactionEPR14Factory
  ACE_LIB_DEPENDS 82000.14p
  EXTRA_ARGS
  --test_ace_file=82000.14p:filepath
  --test_ace_file_start_line=82000.14p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(PositronatomicReactionEPR14Factory DEPENDS tstPositronatomicReactionEPR14Factory.cpp)
FRENSIE_ADD_TEST(PositronatomicReactionEPR14Factory
  ACE_LIB_DEPENDS 82000.14p
  EXTRA_ARGS
  --test_ace_file=82000.14p:filepath
  --test_ace_file_start_line=82000.14p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(ElectroatomicReactionNativeFactory DEPENDS tstElectroatomicReactionNativeFactory.cpp)
FRENSIE_ADD_TEST(ElectroatomicReactionNativeFactory
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(PositronatomicReactionNativeFactory DEPENDS tstPositronatomicReactionNativeFactory.cpp)
FRENSIE_ADD_TEST(PositronatomicReactionNativeFactory
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(AdjointElectroatomicReactionNativeFactory DEPENDS tstAdjointElectroatomicReactionNativeFactory.cpp)
FRENSIE_ADD_TEST(AdjointElectroatomicReactionNativeFactory
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(ElectroatomicReactionNativeFactoryHelpers DEPENDS tstElectroatomicReactionNativeFactoryHelpers.cpp)
FRENSIE_ADD_TEST(ElectroatomicReactionNativeFactoryHelpers
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml)

##---------------------------------------------------------------------------##
## Scattering center tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(ElectroatomCoreACE DEPENDS tstElectroatomCoreACE.cpp)
FRENSIE_ADD_TEST(ElectroatomCoreACE
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(ElectroatomCoreNative DEPENDS tstElectroatomCoreNative.cpp)
FRENSIE_ADD_TEST(ElectroatomCoreNative
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(PositronatomCoreACE DEPENDS tstPositronatomCoreACE.cpp)
FRENSIE_ADD_TEST(PositronatomCoreACE
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(PositronatomCoreNative DEPENDS tstPositronatomCoreNative.cpp)
FRENSIE_ADD_TEST(PositronatomCoreNative
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(AdjointElectroatomCore DEPENDS tstAdjointElectroatomCore.cpp)
FRENSIE_ADD_TEST(AdjointElectroatomCore
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(ElectroatomACE DEPENDS tstElectroatomACE.cpp)
FRENSIE_ADD_TEST(ElectroatomACE
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(ElectroatomEPR14 DEPENDS tstElectroatomEPR14.cpp)
FRENSIE_ADD_TEST(ElectroatomEPR14
  ACE_LIB_DEPENDS 79000.14p
  EXTRA_ARGS
  --test_epr14_file=79000.14p:filepath
  --test_epr14_file_start_line=79000.14p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(ElectroatomNative DEPENDS tstElectroatomNative.cpp)
FRENSIE_ADD_TEST(ElectroatomNative
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(PositronatomACE DEPENDS tstPositronatomACE.cpp)
FRENSIE_ADD_TEST(PositronatomACE
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(PositronatomEPR14 DEPENDS tstPositronatomEPR14.cpp)
FRENSIE_ADD_TEST(PositronatomEPR14
  ACE_LIB_DEPENDS 79000.14p
  EXTRA_ARGS
  --test_epr14_file=79000.14p:filepath
  --test_epr14_file_start_line=79000.14p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(PositronatomNative DEPENDS tstPositronatomNative.cpp)
FRENSIE_ADD_TEST(PositronatomNative
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(AdjointElectroatom DEPENDS tstAdjointElectroatom.cpp)
FRENSIE_ADD_TEST(AdjointElectroatom
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)

##---------------------------------------------------------------------------##
## Scattering center factory tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(ElectroatomACEFactory DEPENDS tstElectroatomACEFactory.cpp)
FRENSIE_ADD_TEST(ElectroatomACEFactory
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(PositronatomACEFactory DEPENDS tstPositronatomACEFactory.cpp)
FRENSIE_ADD_TEST(PositronatomACEFactory
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_ace_file=82000.12p:filepath
  --test_ace_file_start_line=82000.12p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(ElectroatomEPR14Factory DEPENDS tstElectroatomEPR14Factory.cpp)
FRENSIE_ADD_TEST(ElectroatomEPR14Factory
  ACE_LIB_DEPENDS 82000.14p
  EXTRA_ARGS
  --test_ace_file=82000.14p:filepath
  --test_ace_file_start_line=82000.14p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(PositronatomEPR14Factory DEPENDS tstPositronatomEPR14Factory.cpp)
FRENSIE_ADD_TEST(PositronatomEPR14Factory
  ACE_LIB_DEPENDS 82000.14p
  EXTRA_ARGS
  --test_ace_file=82000.14p:filepath
  --test_ace_file_start_line=82000.14p:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(ElectroatomNativeFactory DEPENDS tstElectroatomNativeFactory.cpp)
FRENSIE_ADD_TEST(ElectroatomNativeFactory
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(PositronatomNativeFactory DEPENDS tstPositronatomNativeFactory.cpp)
FRENSIE_ADD_TEST(PositronatomNativeFactory
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(AdjointElectroatomNativeFactory DEPENDS tstAdjointElectroatomNativeFactory.cpp)
FRENSIE_ADD_TEST(AdjointElectroatomNativeFactory
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(ElectroatomFactoryV12
  DEPENDS tstElectroatomFactoryV12.cpp
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
FRENSIE_ADD_TEST(ElectroatomFactoryV12
  ACE_LIB_DEPENDS 1000.12p 82000.12p
  EXTRA_ARGS
  --test_database=${COLLISION_DATABASE_XML_FILE})

FRENSIE_ADD_TEST_EXECUTABLE(ElectroatomFactoryV14
  DEPENDS tstElectroatomFactoryV14.cpp
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
FRENSIE_ADD_TEST(ElectroatomFactoryV14
  ACE_LIB_DEPENDS 82000.14p
  EXTRA_ARGS
  --test_database=${COLLISION_DATABASE_XML_FILE})

FRENSIE_ADD_TEST_EXECUTABLE(ElectroatomFactoryNative
  DEPENDS tstElectroatomFactoryNative.cpp
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
FRENSIE_ADD_TEST(ElectroatomFactoryNative
  EXTRA_ARGS
  --test_database=${COLLISION_DATABASE_XML_FILE})

FRENSIE_ADD_TEST_EXECUTABLE(PositronatomFactoryV12
  DEPENDS tstPositronatomFactoryV12.cpp
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
FRENSIE_ADD_TEST(PositronatomFactoryV12
  ACE_LIB_DEPENDS 1000.12p 82000.12p
  EXTRA_ARGS
  --test_database=${COLLISION_DATABASE_XML_FILE})

FRENSIE_ADD_TEST_EXECUTABLE(PositronatomFactoryV14
  DEPENDS tstPositronatomFactoryV14.cpp
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
FRENSIE_ADD_TEST(PositronatomFactoryV14
  ACE_LIB_DEPENDS 82000.14p
  EXTRA_ARGS
  --test_database=${COLLISION_DATABASE_XML_FILE})

FRENSIE_ADD_TEST_EXECUTABLE(PositronatomFactoryNative
  DEPENDS tstPositronatomFactoryNative.cpp
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
FRENSIE_ADD_TEST(PositronatomFactoryNative
  EXTRA_ARGS
  --test_database=${COLLISION_DATABASE_XML_FILE})

FRENSIE_ADD_TEST_EXECUTABLE(AdjointElectroatomFactory DEPENDS tstAdjointElectroatomFactory.cpp)
FRENSIE_ADD_TEST(AdjointElectroatomFactory
  EXTRA_ARGS
  --test_database=${COLLISION_DATABASE_XML_FILE})

##---------------------------------------------------------------------------##
## Material tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(ElectronMaterial
  DEPENDS tstElectronMaterial.cpp
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
FRENSIE_ADD_TEST(ElectronMaterial
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_database=${COLLISION_DATABASE_XML_FILE})

FRENSIE_ADD_TEST_EXECUTABLE(PositronMaterial
  DEPENDS tstPositronMaterial.cpp
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
FRENSIE_ADD_TEST(PositronMaterial
  ACE_LIB_DEPENDS 82000.12p
  EXTRA_ARGS
  --test_database=${COLLISION_DATABASE_XML_FILE})

FRENSIE_ADD_TEST_EXECUTABLE(AdjointElectronMaterial
  DEPENDS tstAdjointElectronMaterial.cpp
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
FRENSIE_ADD_TEST(AdjointElectronMaterial
  EXTRA_ARGS
  --test_database=${COLLISION_DATABASE_XML_FILE})

FRENSIE_FINALIZE_PACKAGE_TESTS(monte_carlo_collision_electron)
