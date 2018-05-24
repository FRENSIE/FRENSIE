FRENSIE_INITIALIZE_PACKAGE_TESTS(monte_carlo_collision_neutron)

##---------------------------------------------------------------------------##
## Support class tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(NuclearReactionType DEPENDS tstNuclearReactionType.cpp)
FRENSIE_ADD_TEST(NuclearReactionType)

##---------------------------------------------------------------------------##
## Scattering distribution tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(ElasticNeutronNuclearScatteringDistribution DEPENDS tstElasticNeutronNuclearScatteringDistribution.cpp)
FRENSIE_ADD_TEST(ElasticNeutronNuclearScatteringDistribution)

FRENSIE_ADD_TEST_EXECUTABLE(InelasticLevelNeutronScatteringDistribution DEPENDS tstInelasticLevelNeutronScatteringDistribution.cpp)
FRENSIE_ADD_TEST(InelasticLevelNeutronScatteringDistribution)

FRENSIE_ADD_TEST_EXECUTABLE(FissionNeutronMultiplicityDistribution DEPENDS tstFissionNeutronMultiplicityDistribution.cpp)
FRENSIE_ADD_TEST(FissionNeutronMultiplicityDistribution
  EXTRA_ARGS
  --test_u238_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_u238_ace_file.txt
  --test_u238_ace_table=92238.70c)

FRENSIE_ADD_TEST_EXECUTABLE(DelayedNeutronEmissionDistribution DEPENDS tstDelayedNeutronEmissionDistribution.cpp)
FRENSIE_ADD_TEST(DelayedNeutronEmissionDistribution
  EXTRA_ARGS
  --test_u238_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_u238_ace_file.txt
  --test_u238_ace_table=92238.70c)

##---------------------------------------------------------------------------##
## Scattering distribution factory tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(NeutronNuclearScatteringDistributionACEFactory DEPENDS tstNeutronNuclearScatteringDistributionACEFactory.cpp)
FRENSIE_ADD_TEST(NeutronNuclearScatteringDistributionACEFactory
  EXTRA_ARGS
  --test_basic_h1_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_h1_ace_file.txt
  --test_basic_h1_ace_table=1001.70c
  --test_basic_o16_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_o16_ace_file.txt
  --test_basic_o16_ace_table=8016.70c)

FRENSIE_ADD_TEST_EXECUTABLE(FissionNeutronMultiplicityDistributionACEFactory DEPENDS tstFissionNeutronMultiplicityDistributionACEFactory.cpp)
FRENSIE_ADD_TEST(FissionNeutronMultiplicityDistributionACEFactory
  EXTRA_ARGS
  --test_u238_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_u238_ace_file.txt
  --test_u238_ace_table=92238.70c)

FRENSIE_ADD_TEST_EXECUTABLE(DelayedNeutronEmissionDistributionACEFactory DEPENDS tstDelayedNeutronEmissionDistributionACEFactory.cpp)
FRENSIE_ADD_TEST(DelayedNeutronEmissionDistributionACEFactory
  EXTRA_ARGS
  --test_u238_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_u238_ace_file.txt
  --test_u238_ace_table=92238.70c)

##---------------------------------------------------------------------------##
## Reaction tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(NeutronNuclearReaction DEPENDS tstNeutronNuclearReaction.cpp)
FRENSIE_ADD_TEST(NeutronNuclearReaction
  EXTRA_ARGS
  --test_basic_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_h1_ace_file.txt
  --test_basic_ace_table=1001.70c)

FRENSIE_ADD_TEST_EXECUTABLE(NeutronScatteringReaction DEPENDS tstNeutronScatteringReaction.cpp)
FRENSIE_ADD_TEST(NeutronScatteringReaction
  EXTRA_ARGS
  --test_basic_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_h1_ace_file.txt
  --test_basic_ace_table=1001.70c)

FRENSIE_ADD_TEST_EXECUTABLE(EnergyDependentNeutronMultiplicityReaction DEPENDS tstEnergyDependentNeutronMultiplicityReaction.cpp)
FRENSIE_ADD_TEST(EnergyDependentNeutronMultiplicityReaction
  EXTRA_ARGS
  --test_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_o16_ace_file.txt
  --test_ace_table=8016.70c)

FRENSIE_ADD_TEST_EXECUTABLE(NeutronAbsorptionReaction DEPENDS tstNeutronAbsorptionReaction.cpp)
FRENSIE_ADD_TEST(NeutronAbsorptionReaction
  EXTRA_ARGS
  --test_basic_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_h1_ace_file.txt
  --test_basic_ace_table=1001.70c)

FRENSIE_ADD_TEST_EXECUTABLE(DecoupledPhotonProductionReaction DEPENDS tstDecoupledPhotonProductionReaction.cpp)
FRENSIE_ADD_TEST(DecoupledPhotonProductionReaction
  EXTRA_ARGS
  --test_basic_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_h1_ace_file.txt
  --test_basic_ace_table=1001.70c)

FRENSIE_ADD_TEST_EXECUTABLE(DecoupledYieldBasedPhotonProductionReaction DEPENDS tstDecoupledYieldBasedPhotonProductionReaction.cpp)
FRENSIE_ADD_TEST(DecoupledYieldBasedPhotonProductionReaction
  EXTRA_ARGS
  --test_basic_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_h1_ace_file.txt
  --test_basic_ace_table=1001.70c)

FRENSIE_ADD_TEST_EXECUTABLE(DecoupledCrossSectionBasedPhotonProductionReaction DEPENDS tstDecoupledCrossSectionBasedPhotonProductionReaction.cpp)
FRENSIE_ADD_TEST(DecoupledCrossSectionBasedPhotonProductionReaction
  EXTRA_ARGS
  --test_basic_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_h1_ace_file.txt
  --test_basic_ace_table=1001.70c)

##---------------------------------------------------------------------------##
## Reaction factory tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(NeutronNuclearReactionACEFactory DEPENDS tstNeutronNuclearReactionACEFactory.cpp)
FRENSIE_ADD_TEST(NeutronNuclearReactionACEFactory
    EXTRA_ARGS
    --test_h1_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_h1_ace_file.txt
    --test_h1_ace_table=1001.70c
    --test_o16_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_o16_ace_file.txt
    --test_o16_ace_table=8016.70c)

FRENSIE_ADD_TEST_EXECUTABLE(DecoupledPhotonProductionReactionACEFactory DEPENDS tstDecoupledPhotonProductionReactionACEFactory.cpp)
FRENSIE_ADD_TEST(DecoupledPhotonProductionReactionACEFactory
  EXTRA_ARGS
  --test_o16_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_o16_ace_file.txt
  --test_o16_ace_table=8016.70c)

##---------------------------------------------------------------------------##
## Scattering center tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(Nuclide DEPENDS tstNuclide.cpp)
FRENSIE_ADD_TEST(Nuclide
  EXTRA_ARGS
  --test_h1_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_h1_ace_file.txt
  --test_h1_ace_table=1001.70c
  --test_o16_ace_file=${GLOBAL_ACE_TEST_DATA_SOURCE_DIR}/test_o16_ace_file.txt
  --test_o16_ace_table=8016.70c)

##---------------------------------------------------------------------------##
## Scattering center factory tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(NuclideFactory
  DEPENDS tstNuclideFactory.cpp
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
FRENSIE_ADD_TEST(NuclideFactory
  EXTRA_ARGS
  --test_database=${COLLISION_DATABASE_XML_FILE})

##---------------------------------------------------------------------------##
## Material tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(NeutronMaterial
  DEPENDS tstNeutronMaterial.cpp
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
FRENSIE_ADD_TEST(NeutronMaterial
  EXTRA_ARGS
  --test_database=${COLLISION_DATABASE_XML_FILE})

FRENSIE_FINALIZE_PACKAGE_TESTS(monte_carlo_collision_neutron)
