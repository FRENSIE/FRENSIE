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
  ACE_LIB_DEPENDS 92238.70c
  EXTRA_ARGS
  --test_u238_ace_file=92238.70c:filepath
  --test_u238_ace_file_start_line=92238.70c:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(DelayedNeutronEmissionDistribution DEPENDS tstDelayedNeutronEmissionDistribution.cpp)
FRENSIE_ADD_TEST(DelayedNeutronEmissionDistribution
  ACE_LIB_DEPENDS 92238.70c
  EXTRA_ARGS
  --test_u238_ace_file=92238.70c:filepath
  --test_u238_ace_file_start_line=92238.70c:filestartline)

##---------------------------------------------------------------------------##
## Scattering distribution factory tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(NeutronNuclearScatteringDistributionACEFactory DEPENDS tstNeutronNuclearScatteringDistributionACEFactory.cpp)
FRENSIE_ADD_TEST(NeutronNuclearScatteringDistributionACEFactory
  ACE_LIB_DEPENDS 1001.70c 8016.70c
  EXTRA_ARGS
  --test_basic_h1_ace_file=1001.70c:filepath
  --test_basic_h1_ace_file_start_line=1001.70c:filestartline
  --test_basic_o16_ace_file=8016.70c:filepath
  --test_basic_o16_ace_file_start_line=8016.70c:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(FissionNeutronMultiplicityDistributionACEFactory DEPENDS tstFissionNeutronMultiplicityDistributionACEFactory.cpp)
FRENSIE_ADD_TEST(FissionNeutronMultiplicityDistributionACEFactory
  ACE_LIB_DEPENDS 92238.70c
  EXTRA_ARGS
  --test_u238_ace_file=92238.70c:filepath
  --test_u238_ace_file_start_line=92238.70c:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(DelayedNeutronEmissionDistributionACEFactory DEPENDS tstDelayedNeutronEmissionDistributionACEFactory.cpp)
FRENSIE_ADD_TEST(DelayedNeutronEmissionDistributionACEFactory
  ACE_LIB_DEPENDS 92238.70c
  EXTRA_ARGS
  --test_u238_ace_file=92238.70c:filepath
  --test_u238_ace_file_start_line=92238.70c:filestartline)

##---------------------------------------------------------------------------##
## Reaction tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(NeutronNuclearReaction DEPENDS tstNeutronNuclearReaction.cpp)
FRENSIE_ADD_TEST(NeutronNuclearReaction
  ACE_LIB_DEPENDS 1001.70c
  EXTRA_ARGS
  --test_basic_ace_file=1001.70c:filepath
  --test_basic_ace_file_start_line=1001.70c:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(NeutronScatteringReaction DEPENDS tstNeutronScatteringReaction.cpp)
FRENSIE_ADD_TEST(NeutronScatteringReaction
  ACE_LIB_DEPENDS 1001.70c
  EXTRA_ARGS
  --test_basic_ace_file=1001.70c:filepath
  --test_basic_ace_file_start_line=1001.70c:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(EnergyDependentNeutronMultiplicityReaction DEPENDS tstEnergyDependentNeutronMultiplicityReaction.cpp)
FRENSIE_ADD_TEST(EnergyDependentNeutronMultiplicityReaction
  ACE_LIB_DEPENDS 8016.70c
  EXTRA_ARGS
  --test_ace_file=8016.70c:filepath
  --test_ace_file_start_line=8016.70c:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(NeutronAbsorptionReaction DEPENDS tstNeutronAbsorptionReaction.cpp)
FRENSIE_ADD_TEST(NeutronAbsorptionReaction
  ACE_LIB_DEPENDS 1001.70c
  EXTRA_ARGS
  --test_basic_ace_file=1001.70c:filepath
  --test_basic_ace_file_start_line=1001.70c:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(DecoupledPhotonProductionReaction DEPENDS tstDecoupledPhotonProductionReaction.cpp)
FRENSIE_ADD_TEST(DecoupledPhotonProductionReaction
  ACE_LIB_DEPENDS 1001.70c
  EXTRA_ARGS
  --test_basic_ace_file=1001.70c:filepath
  --test_basic_ace_file_start_line=1001.70c:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(DecoupledYieldBasedPhotonProductionReaction DEPENDS tstDecoupledYieldBasedPhotonProductionReaction.cpp)
FRENSIE_ADD_TEST(DecoupledYieldBasedPhotonProductionReaction
  ACE_LIB_DEPENDS 1001.70c
  EXTRA_ARGS
  --test_basic_ace_file=1001.70c:filepath
  --test_basic_ace_file_start_line=1001.70c:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(DecoupledCrossSectionBasedPhotonProductionReaction DEPENDS tstDecoupledCrossSectionBasedPhotonProductionReaction.cpp)
FRENSIE_ADD_TEST(DecoupledCrossSectionBasedPhotonProductionReaction
  ACE_LIB_DEPENDS 1001.70c
  EXTRA_ARGS
  --test_basic_ace_file=1001.70c:filepath
  --test_basic_ace_file_start_line=1001.70c:filestartline)

##---------------------------------------------------------------------------##
## Reaction factory tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(NeutronNuclearReactionACEFactory DEPENDS tstNeutronNuclearReactionACEFactory.cpp)
FRENSIE_ADD_TEST(NeutronNuclearReactionACEFactory
  ACE_LIB_DEPENDS 1001.70c 8016.70c
  EXTRA_ARGS
  --test_h1_ace_file=1001.70c:filepath
  --test_h1_ace_file_start_line=1001.70c:filestartline
  --test_o16_ace_file=8016.70c:filepath
  --test_o16_ace_file_start_line=8016.70c:filestartline)

FRENSIE_ADD_TEST_EXECUTABLE(DecoupledPhotonProductionReactionACEFactory DEPENDS tstDecoupledPhotonProductionReactionACEFactory.cpp)
FRENSIE_ADD_TEST(DecoupledPhotonProductionReactionACEFactory
  ACE_LIB_DEPENDS 8016.70c
  EXTRA_ARGS
  --test_o16_ace_file=8016.70c:filepath
  --test_o16_ace_file_start_line=8016.70c:filestartline)

##---------------------------------------------------------------------------##
## Scattering center tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(Nuclide DEPENDS tstNuclide.cpp)
FRENSIE_ADD_TEST(Nuclide
  ACE_LIB_DEPENDS 1001.70c 8016.70c
  EXTRA_ARGS
  --test_h1_ace_file=1001.70c:filepath
  --test_h1_ace_file_start_line=1001.70c:filestartline
  --test_o16_ace_file=8016.70c:filepath
  --test_o16_ace_file_start_line=8016.70c:filestartline)

##---------------------------------------------------------------------------##
## Scattering center factory tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(NuclideFactory
  DEPENDS tstNuclideFactory.cpp
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
FRENSIE_ADD_TEST(NuclideFactory
  ACE_LIB_DEPENDS 1001.70c
  EXTRA_ARGS
  --test_database=${COLLISION_DATABASE_XML_FILE})

##---------------------------------------------------------------------------##
## Material tests
##---------------------------------------------------------------------------##

FRENSIE_ADD_TEST_EXECUTABLE(NeutronMaterial
  DEPENDS tstNeutronMaterial.cpp
  TARGET_DEPENDS ${COLLISION_DATABASE_XML_FILE_TARGET})
FRENSIE_ADD_TEST(NeutronMaterial
  ACE_LIB_DEPENDS 1001.70c
  EXTRA_ARGS
  --test_database=${COLLISION_DATABASE_XML_FILE})

FRENSIE_FINALIZE_PACKAGE_TESTS(monte_carlo_collision_neutron)
