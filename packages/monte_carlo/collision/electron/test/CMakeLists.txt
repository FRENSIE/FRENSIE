FRENSIE_INITIALIZE_PACKAGE_TESTS(monte_carlo_collision_electron)

##---------------------------------------------------------------------------##
## Scattering distribution test
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

##      electron distribution ace factory tests

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

##      electron distribution native factory tests

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

ADD_EXECUTABLE(tstPositronionizationSubshellPositronatomicReaction
  tstPositronionizationSubshellPositronatomicReaction.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPositronionizationSubshellPositronatomicReaction monte_carlo_collision_native)
ADD_TEST(PositronionizationSubshellPositronatomicReaction_test tstPositronionizationSubshellPositronatomicReaction --test_ace_file="${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p --test_native_file="${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_6_native.xml")
SET_PROPERTY(TEST PositronionizationSubshellPositronatomicReaction_test PROPERTY LABELS positron)

ADD_EXECUTABLE(tstElectroionizationSubshellAdjointElectroatomicReaction
  tstElectroionizationSubshellAdjointElectroatomicReaction.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstElectroionizationSubshellAdjointElectroatomicReaction monte_carlo_collision_native)
ADD_TEST(ElectroionizationSubshellAdjointElectroatomicReaction_test tstElectroionizationSubshellAdjointElectroatomicReaction --test_native_file="${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_6_native.xml")
SET_PROPERTY(TEST ElectroionizationSubshellAdjointElectroatomicReaction_test PROPERTY LABELS electron adjoint)

ADD_EXECUTABLE(tstVoidElectroatomicReaction
  tstVoidElectroatomicReaction.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstVoidElectroatomicReaction monte_carlo_collision_native)
ADD_TEST(VoidElectroatomicReaction_test tstVoidElectroatomicReaction --test_ace_file="${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)
SET_PROPERTY(TEST VoidElectroatomicReaction_test PROPERTY LABELS electron)

ADD_EXECUTABLE(tstVoidAbsorptionElectroatomicReaction
  tstVoidAbsorptionElectroatomicReaction.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstVoidAbsorptionElectroatomicReaction monte_carlo_collision_native)
ADD_TEST(VoidAbsorptionElectroatomicReaction_test tstVoidAbsorptionElectroatomicReaction )
SET_PROPERTY(TEST VoidAbsorptionElectroatomicReaction_test PROPERTY LABELS electron)

ADD_EXECUTABLE(tstElectroatomicReactionACEFactory
  tstElectroatomicReactionACEFactory.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstElectroatomicReactionACEFactory monte_carlo_collision_native)
ADD_TEST(ElectroatomicReactionACEFactory_test tstElectroatomicReactionACEFactory --test_ace_file="${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)
SET_PROPERTY(TEST ElectroatomicReactionACEFactory_test PROPERTY LABELS electron ace)

ADD_EXECUTABLE(tstPositronatomicReactionACEFactory
  tstPositronatomicReactionACEFactory.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPositronatomicReactionACEFactory monte_carlo_collision_native)
ADD_TEST(PositronatomicReactionACEFactory_test tstPositronatomicReactionACEFactory --test_ace_file="${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)
SET_PROPERTY(TEST PositronatomicReactionACEFactory_test PROPERTY LABELS Positron ace)

ADD_EXECUTABLE(tstElectroatomicReactionEPR14Factory
  tstElectroatomicReactionEPR14Factory.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstElectroatomicReactionEPR14Factory monte_carlo_collision_native)
ADD_TEST(ElectroatomicReactionEPR14Factory_test tstElectroatomicReactionEPR14Factory --test_ace_file="${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr14_ace_file.txt" --test_ace_table=82000.14p)
SET_PROPERTY(TEST ElectroatomicReactionEPR14Factory_test PROPERTY LABELS electron ace14)

ADD_EXECUTABLE(tstPositronatomicReactionEPR14Factory
  tstPositronatomicReactionEPR14Factory.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPositronatomicReactionEPR14Factory monte_carlo_collision_native)
ADD_TEST(PositronatomicReactionEPR14Factory_test tstPositronatomicReactionEPR14Factory --test_ace_file="${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr14_ace_file.txt" --test_ace_table=82000.14p)
SET_PROPERTY(TEST PositronatomicReactionEPR14Factory_test PROPERTY LABELS positron ace14)

ADD_EXECUTABLE(tstElectroatomicReactionNativeFactory
  tstElectroatomicReactionNativeFactory.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstElectroatomicReactionNativeFactory monte_carlo_collision_native)
ADD_TEST(ElectroatomicReactionNativeFactory_test tstElectroatomicReactionNativeFactory --test_native_file="${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml" )
SET_PROPERTY(TEST ElectroatomicReactionNativeFactory_test PROPERTY LABELS electron native)

ADD_EXECUTABLE(tstPositronatomicReactionNativeFactory
  tstPositronatomicReactionNativeFactory.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPositronatomicReactionNativeFactory monte_carlo_collision_native)
ADD_TEST(PositronatomicReactionNativeFactory_test tstPositronatomicReactionNativeFactory --test_native_file="${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml" )
SET_PROPERTY(TEST PositronatomicReactionNativeFactory_test PROPERTY LABELS positron native)

ADD_EXECUTABLE(tstAdjointElectroatomicReactionNativeFactory
  tstAdjointElectroatomicReactionNativeFactory.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstAdjointElectroatomicReactionNativeFactory monte_carlo_collision_native)
ADD_TEST(AdjointElectroatomicReactionNativeFactory_test tstAdjointElectroatomicReactionNativeFactory --test_native_file="${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml" )
SET_PROPERTY(TEST AdjointElectroatomicReactionNativeFactory_test PROPERTY LABELS electron native adjoint)

ADD_EXECUTABLE(tstElectroatomicReactionNativeFactoryHelpers
  tstElectroatomicReactionNativeFactoryHelpers.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstElectroatomicReactionNativeFactoryHelpers monte_carlo_collision_native)
ADD_TEST(ElectroatomicReactionNativeFactoryHelpers_test tstElectroatomicReactionNativeFactoryHelpers --test_native_file="${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml" )
SET_PROPERTY(TEST ElectroatomicReactionNativeFactoryHelpers_test PROPERTY LABELS electron native)

##---------------------------------------------------------------------------##
## Scattering center tests
##---------------------------------------------------------------------------##

ADD_EXECUTABLE(tstElectroatomCore
  tstElectroatomCore.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstElectroatomCore monte_carlo_collision_native)
ADD_TEST(ElectroatomCore_test tstElectroatomCore --test_ace_file="${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p --test_native_file="${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml")
SET_PROPERTY(TEST ElectroatomCore_test PROPERTY LABELS electron)

ADD_EXECUTABLE(tstPositronatomCore
  tstPositronatomCore.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPositronatomCore monte_carlo_collision_native)
ADD_TEST(PositronatomCore_test tstPositronatomCore --test_ace_file="${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p --test_native_file="${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml")
SET_PROPERTY(TEST PositronatomCore_test PROPERTY LABELS positron)

ADD_EXECUTABLE(tstAdjointElectroatomCore
  tstAdjointElectroatomCore.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstAdjointElectroatomCore monte_carlo_collision_native)
ADD_TEST(AdjointElectroatomCore_test tstAdjointElectroatomCore --test_native_file="${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml")
SET_PROPERTY(TEST AdjointElectroatomCore_test PROPERTY LABELS electron adjoint)

ADD_EXECUTABLE(tstElectroatom
  tstElectroatom.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstElectroatom monte_carlo_collision_native)
ADD_TEST(Electroatom_test tstElectroatom --test_ace_file="${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p --test_native_file="${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml" --test_epr14_file="${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_au_epr14_ace_file.txt" --test_epr14_table=79000.14p)
SET_PROPERTY(TEST Electroatom_test PROPERTY LABELS electron)

ADD_EXECUTABLE(tstPositronatom
  tstPositronatom.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPositronatom monte_carlo_collision_native)
ADD_TEST(Positronatom_test tstPositronatom --test_ace_file="${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p --test_native_file="${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml" --test_epr14_file="${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_au_epr14_ace_file.txt" --test_epr14_table=79000.14p)
SET_PROPERTY(TEST Positronatom_test PROPERTY LABELS positron)

ADD_EXECUTABLE(tstAdjointElectroatom
  tstAdjointElectroatom.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstAdjointElectroatom monte_carlo_collision_native)
ADD_TEST(AdjointElectroatom_test tstAdjointElectroatom --test_native_file="${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml")
SET_PROPERTY(TEST AdjointElectroatom_test PROPERTY LABELS electron adjoint)

ADD_EXECUTABLE(tstElectroatomACEFactory
  tstElectroatomACEFactory.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstElectroatomACEFactory monte_carlo_collision_native)
ADD_TEST(ElectroatomACEFactory_test tstElectroatomACEFactory --test_ace_file="${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)
SET_PROPERTY(TEST ElectroatomACEFactory_test PROPERTY LABELS electron ace)

ADD_EXECUTABLE(tstPositronatomACEFactory
  tstPositronatomACEFactory.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPositronatomACEFactory monte_carlo_collision_native)
ADD_TEST(PositronatomACEFactory_test tstPositronatomACEFactory --test_ace_file="${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)
SET_PROPERTY(TEST PositronatomACEFactory_test PROPERTY LABELS positron ace)

ADD_EXECUTABLE(tstElectroatomEPR14Factory
  tstElectroatomEPR14Factory.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstElectroatomEPR14Factory monte_carlo_collision_native)
ADD_TEST(ElectroatomEPR14Factory_test tstElectroatomEPR14Factory --test_ace_file="${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr14_ace_file.txt" --test_ace_table=82000.14p)
SET_PROPERTY(TEST ElectroatomEPR14Factory_test PROPERTY LABELS electron ace14)

ADD_EXECUTABLE(tstPositronatomEPR14Factory
  tstPositronatomEPR14Factory.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPositronatomEPR14Factory monte_carlo_collision_native)
ADD_TEST(PositronatomEPR14Factory_test tstPositronatomEPR14Factory --test_ace_file="${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_pb_epr14_ace_file.txt" --test_ace_table=82000.14p)
SET_PROPERTY(TEST PositronatomEPR14Factory_test PROPERTY LABELS positron ace14)

ADD_EXECUTABLE(tstElectroatomNativeFactory
  tstElectroatomNativeFactory.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstElectroatomNativeFactory monte_carlo_collision_native)
ADD_TEST(ElectroatomNativeFactory_test tstElectroatomNativeFactory --test_native_file="${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml")
SET_PROPERTY(TEST ElectroatomNativeFactory_test PROPERTY LABELS electron native)

ADD_EXECUTABLE(tstPositronatomNativeFactory
  tstPositronatomNativeFactory.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPositronatomNativeFactory monte_carlo_collision_native)
ADD_TEST(PositronatomNativeFactory_test tstPositronatomNativeFactory --test_native_file="${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_epr_82_native.xml")
SET_PROPERTY(TEST PositronatomNativeFactory_test PROPERTY LABELS positron native)

ADD_EXECUTABLE(tstAdjointElectroatomNativeFactory
  tstAdjointElectroatomNativeFactory.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstAdjointElectroatomNativeFactory monte_carlo_collision_native)
ADD_TEST(AdjointElectroatomNativeFactory_test tstAdjointElectroatomNativeFactory --test_native_file="${GLOBAL_NATIVE_TEST_DATA_SOURCE_DIR}/test_aepr_1_native.xml")
SET_PROPERTY(TEST AdjointElectroatomNativeFactory_test PROPERTY LABELS electron native adjoint)

ADD_EXECUTABLE(tstElectroatomFactory
  tstElectroatomFactory.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstElectroatomFactory monte_carlo_collision_native)
ADD_TEST(ElectroatomFactory_test tstElectroatomFactory --test_cross_sections_xml_directory="${GLOBAL_TEST_DATA_SOURCE_DIR}/")
SET_PROPERTY(TEST ElectroatomFactory_test PROPERTY LABELS electron)

ADD_EXECUTABLE(tstPositronatomFactory
  tstPositronatomFactory.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPositronatomFactory monte_carlo_collision_native)
ADD_TEST(PositronatomFactory_test tstPositronatomFactory --test_cross_sections_xml_directory="${GLOBAL_TEST_DATA_SOURCE_DIR}/")
SET_PROPERTY(TEST PositronatomFactory_test PROPERTY LABELS positron)

ADD_EXECUTABLE(tstAdjointElectroatomFactory
  tstAdjointElectroatomFactory.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstAdjointElectroatomFactory monte_carlo_collision_native)
ADD_TEST(AdjointElectroatomFactory_test tstAdjointElectroatomFactory --test_cross_sections_xml_directory="${GLOBAL_TEST_DATA_SOURCE_DIR}/")
SET_PROPERTY(TEST AdjointElectroatomFactory_test PROPERTY LABELS electron adjoint)

##---------------------------------------------------------------------------##
## Material tests
##---------------------------------------------------------------------------##

ADD_EXECUTABLE(tstElectronMaterial tstElectronMaterial.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstElectronMaterial monte_carlo_collision_native)
ADD_TEST(ElectronMaterial_test tstElectronMaterial --test_cross_sections_xml_directory="${GLOBAL_TEST_DATA_SOURCE_DIR}/")
SET_PROPERTY(TEST ElectronMaterial_test PROPERTY LABELS electron)

ADD_EXECUTABLE(tstPositronMaterial tstPositronMaterial.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstPositronMaterial monte_carlo_collision_native)
ADD_TEST(PositronMaterial_test tstPositronMaterial --test_cross_sections_xml_directory="${GLOBAL_TEST_DATA_SOURCE_DIR}/")
SET_PROPERTY(TEST PositronMaterial_test PROPERTY LABELS positron)

ADD_EXECUTABLE(tstAdjointElectronMaterial tstAdjointElectronMaterial.cpp
  ${FRENSIE_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstAdjointElectronMaterial monte_carlo_collision_native)
ADD_TEST(AdjointElectronMaterial_test tstAdjointElectronMaterial --test_cross_sections_xml_directory="${GLOBAL_TEST_DATA_SOURCE_DIR}/")
SET_PROPERTY(TEST AdjointElectronMaterial_test PROPERTY LABELS electron adjoint)

FRENSIE_FINALIZE_PACKAGE_TESTS(monte_carlo_collision_electron)
