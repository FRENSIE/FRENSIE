FRENSIE_INITIALIZE_PACKAGE_TESTS(utility_dist)

FRENSIE_ADD_TEST_EXECUTABLE(DeltaDistribution DEPENDS tstDeltaDistribution.cpp)
FRENSIE_ADD_TEST(DeltaDistribution
  EXTRA_ARGS --test_dists_json_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_delta_distributions.json)

FRENSIE_ADD_TEST_EXECUTABLE(DiscreteDistribution DEPENDS tstDiscreteDistribution.cpp)
FRENSIE_ADD_TEST(DiscreteDistribution
  EXTRA_ARGS --test_dists_json_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_discrete_distributions.json)

FRENSIE_ADD_TEST_EXECUTABLE(EquiprobableBinDistribution DEPENDS tstEquiprobableBinDistribution.cpp)
FRENSIE_ADD_TEST(EquiprobableBinDistribution
  EXTRA_ARGS --test_dists_json_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_equiprobable_bin_distributions.json)

FRENSIE_ADD_TEST_EXECUTABLE(EvaporationDistribution DEPENDS tstEvaporationDistribution.cpp)
FRENSIE_ADD_TEST(EvaporationDistribution
  EXTRA_ARGS --test_dists_json_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_evaporation_distributions.json)

FRENSIE_ADD_TEST_EXECUTABLE(ExponentialDistribution DEPENDS tstExponentialDistribution.cpp)
FRENSIE_ADD_TEST(ExponentialDistribution
  EXTRA_ARGS --test_dists_json_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_exponential_distributions.json)

FRENSIE_ADD_TEST_EXECUTABLE(HistogramDistribution DEPENDS tstHistogramDistribution.cpp)
FRENSIE_ADD_TEST(HistogramDistribution
  EXTRA_ARGS --test_dists_json_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_histogram_distributions.json)

FRENSIE_ADD_TEST_EXECUTABLE(MaxwellFissionDistribution DEPENDS tstMaxwellFissionDistribution.cpp)
FRENSIE_ADD_TEST(MaxwellFissionDistribution
  EXTRA_ARGS --test_dists_json_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_maxwell_fission_distributions.json)

FRENSIE_ADD_TEST_EXECUTABLE(NormalDistribution DEPENDS tstNormalDistribution.cpp)
FRENSIE_ADD_TEST(NormalDistribution
  EXTRA_ARGS --test_dists_json_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_normal_distributions.json)

FRENSIE_ADD_TEST_EXECUTABLE(PolynomialDistribution DEPENDS tstPolynomialDistribution.cpp)
FRENSIE_ADD_TEST(PolynomialDistribution
  EXTRA_ARGS --test_dists_json_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_polynomial_distributions.json)

FRENSIE_ADD_TEST_EXECUTABLE(PowerDistribution DEPENDS tstPowerDistribution.cpp)
FRENSIE_ADD_TEST(PowerDistribution
  EXTRA_ARGS --test_dists_json_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_power_distributions.json)

FRENSIE_ADD_TEST_EXECUTABLE(TabularDistribution DEPENDS tstTabularDistribution.cpp)
FRENSIE_ADD_TEST(TabularDistribution
  EXTRA_ARGS --test_dists_json_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_tabular_distributions.json)

FRENSIE_ADD_TEST_EXECUTABLE(UniformDistribution DEPENDS tstUniformDistribution.cpp)
FRENSIE_ADD_TEST(UniformDistribution
  EXTRA_ARGS --test_dists_json_file=${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_uniform_distributions.json)

FRENSIE_FINALIZE_PACKAGE_TESTS(utility_dist)

# ADD_EXECUTABLE(tstUniformDistribution
#   tstUniformDistribution.cpp
#   ${FRENSIE_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstUniformDistribution utility_dist)
# ADD_TEST(UniformDistribution_test tstUniformDistribution --test_dists_json_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_uniform_distributions.json")
# SET_PROPERTY(TEST UniformDistribution_test PROPERTY LABELS utility_dist)

# ADD_EXECUTABLE(tstTabularDistribution
#   tstTabularDistribution.cpp
#   ${FRENSIE_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstTabularDistribution utility_dist)
# ADD_TEST(TabularDistribution_test tstTabularDistribution --test_dists_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_tabular_distributions.xml")
# SET_PROPERTY(TEST TabularDistribution_test PROPERTY LABELS utility_dist)

# ADD_EXECUTABLE(tstPowerDistribution
#   tstPowerDistribution.cpp
#   ${FRENSIE_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstPowerDistribution utility_dist)
# ADD_TEST(PowerDistribution_test tstPowerDistribution --test_dists_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_power_distributions.xml")
# SET_PROPERTY(TEST PowerDistribution_test PROPERTY LABELS utility_dist)


# ADD_EXECUTABLE(tstWattDistribution
#   tstWattDistribution.cpp
#   ${FRENSIE_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstWattDistribution utility_dist)
# ADD_TEST(WattDistribution_test tstWattDistribution
# --test_dists_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_watt_distributions.xml")
# SET_PROPERTY(TEST WattDistribution_test PROPERTY LABELS utility_dist)

# ADD_EXECUTABLE(tstOneDDistribution
#   tstOneDDistribution.cpp
#   ${FRENSIE_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstOneDDistribution utility_dist)
# ADD_TEST(OneDDistribution_test tstOneDDistribution)
# SET_PROPERTY(TEST OneDDistribution_test PROPERTY LABELS utility_dist)

# ADD_EXECUTABLE(tstHistogramPartiallyTabularTwoDDistribution
#   tstHistogramPartiallyTabularTwoDDistribution.cpp
#   ${FRENSIE_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstHistogramPartiallyTabularTwoDDistribution utility_dist)
# ADD_TEST(HistogramPartiallyTabularTwoDDistribution_test tstHistogramPartiallyTabularTwoDDistribution)
# SET_PROPERTY(TEST HistogramPartiallyTabularTwoDDistribution_test PROPERTY LABELS utility_dist)

# ADD_EXECUTABLE(tstHistogramFullyTabularTwoDDistribution
#   tstHistogramFullyTabularTwoDDistribution.cpp
#   ${FRENSIE_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstHistogramFullyTabularTwoDDistribution utility_dist)
# ADD_TEST(HistogramFullyTabularTwoDDistribution_test tstHistogramFullyTabularTwoDDistribution)
# SET_PROPERTY(TEST HistogramFullyTabularTwoDDistribution_test PROPERTY LABELS utility_dist)

# ADD_EXECUTABLE(tstLinLinLinInterpolatedPartiallyTabularTwoDDistribution
#   tstLinLinLinInterpolatedPartiallyTabularTwoDDistribution.cpp
#   ${FRENSIE_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstLinLinLinInterpolatedPartiallyTabularTwoDDistribution utility_dist)
# ADD_TEST(LinLinLinInterpolatedPartiallyTabularTwoDDistribution_test tstLinLinLinInterpolatedPartiallyTabularTwoDDistribution)
# SET_PROPERTY(TEST LinLinLinInterpolatedPartiallyTabularTwoDDistribution_test PROPERTY LABELS utility_dist)

# ADD_EXECUTABLE(tstLinLinLinInterpolatedFullyTabularTwoDDistribution
#   tstLinLinLinInterpolatedFullyTabularTwoDDistribution.cpp
#   ${FRENSIE_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstLinLinLinInterpolatedFullyTabularTwoDDistribution utility_dist)
# ADD_TEST(LinLinLinInterpolatedFullyTabularTwoDDistribution_test tstLinLinLinInterpolatedFullyTabularTwoDDistribution)
# SET_PROPERTY(TEST LinLinLinInterpolatedFullyTabularTwoDDistribution_test PROPERTY LABELS utility_dist)

# ADD_EXECUTABLE(tstTwoDDistributionFactory
#   tstTwoDDistributionFactory.cpp
#   ${FRENSIE_STD_UNIT_TEST_MAIN})
# TARGET_LINK_LIBRARIES(tstTwoDDistributionFactory utility_dist)
# ADD_TEST(TwoDDistributionFactory_test tstTwoDDistributionFactory)
# SET_PROPERTY(TEST TwoDDistributionFactory_test PROPERTY LABELS utility_dist)
