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

FRENSIE_ADD_TEST_EXECUTABLE(CutoffElasticElectronScatteringDistribution DEPENDS tstCutoffElasticElectronScatteringDistribution.cpp)
FRENSIE_ADD_TEST(CutoffElasticElectronScatteringDistribution
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt
  --test_ace_table=82000.12p
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
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt
  --test_ace_table=82000.12p)

FRENSIE_ADD_TEST_EXECUTABLE(AtomicExcitationAdjointElectronScatteringDistribution DEPENDS tstAtomicExcitationAdjointElectronScatteringDistribution.cpp)
FRENSIE_ADD_TEST(AtomicExcitationAdjointElectronScatteringDistribution
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt
  --test_ace_table=82000.12p
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(BremsstrahlungElectronScatteringDistribution DEPENDS tstBremsstrahlungElectronScatteringDistribution.cpp)
FRENSIE_ADD_TEST(BremsstrahlungElectronScatteringDistribution
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt
  --test_ace_table=82000.12p
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_13_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(BremsstrahlungAdjointElectronScatteringDistribution DEPENDS tstBremsstrahlungAdjointElectronScatteringDistribution.cpp)
FRENSIE_ADD_TEST(BremsstrahlungAdjointElectronScatteringDistribution
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml )

FRENSIE_ADD_TEST_EXECUTABLE(ElectroionizationSubshellElectronScatteringDistribution DEPENDS tstElectroionizationSubshellElectronScatteringDistribution.cpp)
FRENSIE_ADD_TEST(ElectroionizationSubshellElectronScatteringDistribution
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt
  --test_ace_table=82000.12p
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_13_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(ElectroionizationSubshellAdjointElectronScatteringDistribution DEPENDS tstElectroionizationSubshellAdjointElectronScatteringDistribution.cpp)
FRENSIE_ADD_TEST(ElectroionizationSubshellAdjointElectronScatteringDistribution
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)

##---------------------------------------------------------------------------##
## Scattering distribution factory tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(ElasticElectronScatteringDistributionACEFactory DEPENDS tstElasticElectronScatteringDistributionACEFactory.cpp)
FRENSIE_ADD_TEST(ElasticElectronScatteringDistributionACEFactory
  EXTRA_ARGS
  --test_ace12_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt
  --test_ace12_table=82000.12p
  --test_ace14_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr14_ace_file.txt
  --test_ace14_table=82000.14p)

FRENSIE_ADD_TEST_EXECUTABLE(AtomicExcitationElectronScatteringDistributionACEFactory DEPENDS tstAtomicExcitationElectronScatteringDistributionACEFactory.cpp)
FRENSIE_ADD_TEST(AtomicExcitationElectronScatteringDistributionACEFactory
  EXTRA_ARGS
  --test_ace12_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt
  --test_ace12_table=82000.12p
  --test_ace14_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr14_ace_file.txt
 --test_ace14_table=82000.14p)

FRENSIE_ADD_TEST_EXECUTABLE(BremsstrahlungElectronScatteringDistributionACEFactory DEPENDS tstBremsstrahlungElectronScatteringDistributionACEFactory.cpp)
FRENSIE_ADD_TEST(BremsstrahlungElectronScatteringDistributionACEFactory
  EXTRA_ARGS
  --test_ace12_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt
  --test_ace12_table=82000.12p
  --test_ace14_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr14_ace_file.txt
  --test_ace14_table=82000.14p)

FRENSIE_ADD_TEST_EXECUTABLE(ElectroionizationSubshellElectronScatteringDistributionACEFactory DEPENDS tstElectroionizationSubshellElectronScatteringDistributionACEFactory.cpp)
FRENSIE_ADD_TEST(ElectroionizationSubshellElectronScatteringDistributionACEFactory
  EXTRA_ARGS
  --test_ace12_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt
  --test_ace12_table=82000.12p
  --test_ace14_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr14_ace_file.txt
  --test_ace14_table=82000.14p)

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
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt
  --test_ace_table=82000.12p)

FRENSIE_ADD_TEST_EXECUTABLE(AbsorptionAdjointElectroatomicReaction DEPENDS tstAbsorptionAdjointElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(AbsorptionAdjointElectroatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(CutoffElasticElectroatomicReaction DEPENDS tstCutoffElasticElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(CutoffElasticElectroatomicReaction
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt
  --test_ace_table=82000.12p)

FRENSIE_ADD_TEST_EXECUTABLE(CutoffElasticPositronatomicReaction DEPENDS tstCutoffElasticPositronatomicReaction.cpp)
FRENSIE_ADD_TEST(CutoffElasticPositronatomicReaction
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt
  --test_ace_table=82000.12p)
 
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
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt
  --test_ace_table=82000.12p)

FRENSIE_ADD_TEST_EXECUTABLE(AtomicExcitationPositronatomicReaction DEPENDS tstAtomicExcitationPositronatomicReaction.cpp)
FRENSIE_ADD_TEST(AtomicExcitationPositronatomicReaction
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt
  --test_ace_table=82000.12p)

FRENSIE_ADD_TEST_EXECUTABLE(AtomicExcitationAdjointElectroatomicReaction DEPENDS tstAtomicExcitationAdjointElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(AtomicExcitationAdjointElectroatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(BremsstrahlungElectroatomicReaction DEPENDS tstBremsstrahlungElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(BremsstrahlungElectroatomicReaction
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt
  --test_ace_table=82000.12p)

FRENSIE_ADD_TEST_EXECUTABLE(BremsstrahlungPositronatomicReaction DEPENDS tstBremsstrahlungPositronatomicReaction.cpp)
FRENSIE_ADD_TEST(BremsstrahlungPositronatomicReaction
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt
  --test_ace_table=82000.12p)

FRENSIE_ADD_TEST_EXECUTABLE(BremsstrahlungAdjointElectroatomicReaction DEPENDS tstBremsstrahlungAdjointElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(BremsstrahlungAdjointElectroatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(ElectroionizationElectroatomicReaction DEPENDS tstElectroionizationElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(ElectroionizationElectroatomicReaction
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr14_ace_file.txt
  --test_ace_table=82000.14p)

FRENSIE_ADD_TEST_EXECUTABLE(ElectroionizationSubshellElectroatomicReaction DEPENDS tstElectroionizationSubshellElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(ElectroionizationSubshellElectroatomicReaction
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt
  --test_ace_table=82000.12p
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_6_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(PositronionizationSubshellPositronatomicReaction DEPENDS tstPositronionizationSubshellPositronatomicReaction.cpp)
FRENSIE_ADD_TEST(PositronionizationSubshellPositronatomicReaction
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt
  --test_ace_table=82000.12p
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_6_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(ElectroionizationSubshellAdjointElectroatomicReaction DEPENDS tstElectroionizationSubshellAdjointElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(ElectroionizationSubshellAdjointElectroatomicReaction
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_6_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(VoidElectroatomicReaction DEPENDS tstVoidElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(VoidElectroatomicReaction
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt
  --test_ace_table=82000.12p)

FRENSIE_ADD_TEST_EXECUTABLE(VoidAbsorptionElectroatomicReaction DEPENDS tstVoidAbsorptionElectroatomicReaction.cpp)
FRENSIE_ADD_TEST(VoidAbsorptionElectroatomicReaction)

##---------------------------------------------------------------------------##
## Reaction factory tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(ElectroatomicReactionACEFactory DEPENDS tstElectroatomicReactionACEFactory.cpp)
FRENSIE_ADD_TEST(ElectroatomicReactionACEFactory
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt
  --test_ace_table=82000.12p)

FRENSIE_ADD_TEST_EXECUTABLE(PositronatomicReactionACEFactory DEPENDS tstPositronatomicReactionACEFactory.cpp)
FRENSIE_ADD_TEST(PositronatomicReactionACEFactory
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt
  --test_ace_table=82000.12p)

FRENSIE_ADD_TEST_EXECUTABLE(ElectroatomicReactionEPR14Factory DEPENDS tstElectroatomicReactionEPR14Factory.cpp)
FRENSIE_ADD_TEST(ElectroatomicReactionEPR14Factory
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr14_ace_file.txt
  --test_ace_table=82000.14p)

FRENSIE_ADD_TEST_EXECUTABLE(PositronatomicReactionEPR14Factory DEPENDS tstPositronatomicReactionEPR14Factory.cpp)
FRENSIE_ADD_TEST(PositronatomicReactionEPR14Factory
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr14_ace_file.txt
  --test_ace_table=82000.14p)

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

FRENSIE_ADD_TEST_EXECUTABLE(ElectroatomCore DEPENDS tstElectroatomCore.cpp)
FRENSIE_ADD_TEST(ElectroatomCore
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt
  --test_ace_table=82000.12p
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(PositronatomCore DEPENDS tstPositronatomCore.cpp)
FRENSIE_ADD_TEST(PositronatomCore
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt
  --test_ace_table=82000.12p
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(AdjointElectroatomCore DEPENDS tstAdjointElectroatomCore.cpp)
FRENSIE_ADD_TEST(AdjointElectroatomCore
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)

FRENSIE_ADD_TEST_EXECUTABLE(Electroatom DEPENDS tstElectroatom.cpp)
FRENSIE_ADD_TEST(Electroatom
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt
  --test_ace_table=82000.12p
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml
  --test_epr14_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_au_epr14_ace_file.txt
  --test_epr14_table=79000.14p)

FRENSIE_ADD_TEST_EXECUTABLE(Positronatom DEPENDS tstPositronatom.cpp)
FRENSIE_ADD_TEST(Positronatom
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt
  --test_ace_table=82000.12p
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml
  --test_epr14_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_au_epr14_ace_file.txt
  --test_epr14_table=79000.14p)

FRENSIE_ADD_TEST_EXECUTABLE(AdjointElectroatom DEPENDS tstAdjointElectroatom.cpp)
FRENSIE_ADD_TEST(AdjointElectroatom
  EXTRA_ARGS
  --test_native_file=${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml)

##---------------------------------------------------------------------------##
## Scattering center factory tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(ElectroatomACEFactory DEPENDS tstElectroatomACEFactory.cpp)
FRENSIE_ADD_TEST(ElectroatomACEFactory
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt
  --test_ace_table=82000.12p)

FRENSIE_ADD_TEST_EXECUTABLE(PositronatomACEFactory DEPENDS tstPositronatomACEFactory.cpp)
FRENSIE_ADD_TEST(PositronatomACEFactory
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt
  --test_ace_table=82000.12p)

FRENSIE_ADD_TEST_EXECUTABLE(ElectroatomEPR14Factory DEPENDS tstElectroatomEPR14Factory.cpp)
FRENSIE_ADD_TEST(ElectroatomEPR14Factory
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr14_ace_file.txt
  --test_ace_table=82000.14p)

FRENSIE_ADD_TEST_EXECUTABLE(PositronatomEPR14Factory DEPENDS tstPositronatomEPR14Factory.cpp)
FRENSIE_ADD_TEST(PositronatomEPR14Factory
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr14_ace_file.txt
  --test_ace_table=82000.14p)

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

FRENSIE_ADD_TEST_EXECUTABLE(ElectroatomFactory
  DEPENDS tstElectroatomFactory.cpp
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
FRENSIE_ADD_TEST(ElectroatomFactory
  EXTRA_ARGS
  --test_database=${COLLISION_DATABASE_XML_FILE})

FRENSIE_ADD_TEST_EXECUTABLE(PositronatomFactory
  DEPENDS tstPositronatomFactory.cpp
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
FRENSIE_ADD_TEST(PositronatomFactory
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
  EXTRA_ARGS
  --test_database=${COLLISION_DATABASE_XML_FILE})

FRENSIE_ADD_TEST_EXECUTABLE(PositronMaterial
  DEPENDS tstPositronMaterial.cpp
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
FRENSIE_ADD_TEST(PositronMaterial
  EXTRA_ARGS
  --test_database=${COLLISION_DATABASE_XML_FILE})

FRENSIE_ADD_TEST_EXECUTABLE(AdjointElectronMaterial
  DEPENDS tstAdjointElectronMaterial.cpp
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
FRENSIE_ADD_TEST(AdjointElectronMaterial
  EXTRA_ARGS
  --test_database=${COLLISION_DATABASE_XML_FILE})

FRENSIE_FINALIZE_PACKAGE_TESTS(monte_carlo_collision_electron)
