ADD_SUBDIRECTORY(test_files)

ADD_EXECUTABLE(tstTwoDDistributionHelpers
  tstTwoDDistributionHelpers.cpp)
TARGET_LINK_LIBRARIES(tstTwoDDistributionHelpers monte_carlo_collision_native)
ADD_TEST(TwoDDistributionHelpers_test tstTwoDDistributionHelpers)

ADD_EXECUTABLE(tstAceLaw1NuclearScatteringEnergyDistribution
  tstAceLaw1NuclearScatteringEnergyDistribution.cpp)
TARGET_LINK_LIBRARIES(tstAceLaw1NuclearScatteringEnergyDistribution monte_carlo_collision_native)
ADD_TEST(AceLaw1NuclearScatteringEnergyDistribution_test
tstAceLaw1NuclearScatteringEnergyDistribution)

ADD_EXECUTABLE(tstAceLaw2NuclearScatteringEnergyDistribution
  tstAceLaw2NuclearScatteringEnergyDistribution.cpp)
TARGET_LINK_LIBRARIES(tstAceLaw2NuclearScatteringEnergyDistribution monte_carlo_collision_native)
ADD_TEST(AceLaw2NuclearScatteringEnergyDistribution_test
tstAceLaw9NuclearScatteringEnergyDistribution)

ADD_EXECUTABLE(tstAceLaw4NuclearScatteringEnergyDistribution
  tstAceLaw4NuclearScatteringEnergyDistribution.cpp)
TARGET_LINK_LIBRARIES(tstAceLaw4NuclearScatteringEnergyDistribution monte_carlo_collision_native)
ADD_TEST(AceLaw4NuclearScatteringEnergyDistribution_test
tstAceLaw4NuclearScatteringEnergyDistribution)

ADD_EXECUTABLE(tstAceLaw5NuclearScatteringEnergyDistribution
  tstAceLaw5NuclearScatteringEnergyDistribution.cpp)
TARGET_LINK_LIBRARIES(tstAceLaw5NuclearScatteringEnergyDistribution monte_carlo_collision_native)
ADD_TEST(AceLaw5NuclearScatteringEnergyDistribution_test
tstAceLaw5NuclearScatteringEnergyDistribution)

ADD_EXECUTABLE(tstAceLaw7NuclearScatteringEnergyDistribution
  tstAceLaw7NuclearScatteringEnergyDistribution.cpp)
TARGET_LINK_LIBRARIES(tstAceLaw7NuclearScatteringEnergyDistribution monte_carlo_collision_native)
ADD_TEST(AceLaw7NuclearScatteringEnergyDistribution_test
tstAceLaw7NuclearScatteringEnergyDistribution)

ADD_EXECUTABLE(tstAceLaw9NuclearScatteringEnergyDistribution
  tstAceLaw9NuclearScatteringEnergyDistribution.cpp)
TARGET_LINK_LIBRARIES(tstAceLaw9NuclearScatteringEnergyDistribution monte_carlo_collision_native)
ADD_TEST(AceLaw9NuclearScatteringEnergyDistribution_test
tstAceLaw9NuclearScatteringEnergyDistribution)

ADD_EXECUTABLE(tstAceLaw11NuclearScatteringEnergyDistribution
  tstAceLaw11NuclearScatteringEnergyDistribution.cpp)
TARGET_LINK_LIBRARIES(tstAceLaw11NuclearScatteringEnergyDistribution monte_carlo_collision_native)
ADD_TEST(AceLaw11NuclearScatteringEnergyDistribution_test
tstAceLaw9NuclearScatteringEnergyDistribution)

ADD_EXECUTABLE(tstAceLaw44NuclearScatteringDistribution
  tstAceLaw44NuclearScatteringDistribution.cpp)
TARGET_LINK_LIBRARIES(tstAceLaw44NuclearScatteringDistribution monte_carlo_collision_native)
ADD_TEST(AceLaw44NuclearScatteringDistribution_test
tstAceLaw44NuclearScatteringDistribution)

ADD_EXECUTABLE(tstLabSystemConversionPolicy
  tstLabSystemConversionPolicy.cpp)
TARGET_LINK_LIBRARIES(tstLabSystemConversionPolicy monte_carlo_collision_native)
ADD_TEST(LabSystemConversionPolicy_test
tstLabSystemConversionPolicy)

ADD_EXECUTABLE(tstCrossSectionsXMLProperties
  tstCrossSectionsXMLProperties.cpp)
TARGET_LINK_LIBRARIES(tstCrossSectionsXMLProperties monte_carlo_collision_native)
ADD_TEST(CrossSectionsXMLProperties_test tstCrossSectionsXMLProperties --test_cross_sections_xml_directory="${CMAKE_CURRENT_SOURCE_DIR}/test_files")

ADD_EXECUTABLE(tstMaterialHelpers
  tstMaterialHelpers.cpp
  ${TEUCHOS_STD_UNIT_TEST_MAIN})
TARGET_LINK_LIBRARIES(tstMaterialHelpers monte_carlo_collision_native)
ADD_TEST(MaterialHelpers_test tstMaterialHelpers)

##----------------------------------------------------------------------------##
##      neutron class tests                                                   ##
##----------------------------------------------------------------------------##

ADD_EXECUTABLE(tstNuclearScatteringDistribution
  tstNuclearScatteringDistribution.cpp)
TARGET_LINK_LIBRARIES(tstNuclearScatteringDistribution monte_carlo_collision_native)
ADD_TEST(NuclearScatteringDistribution_test tstNuclearScatteringDistribution)

ADD_EXECUTABLE(tstElasticNeutronNuclearScatteringDistribution
  tstElasticNeutronNuclearScatteringDistribution.cpp)
TARGET_LINK_LIBRARIES(tstElasticNeutronNuclearScatteringDistribution monte_carlo_collision_native)
ADD_TEST(ElasticNeutronNuclearScatteringDistribution_test tstElasticNeutronNuclearScatteringDistribution)

ADD_EXECUTABLE(tstInelasticLevelNeutronScatteringDistribution
  tstInelasticLevelNeutronScatteringDistribution.cpp)
TARGET_LINK_LIBRARIES(tstInelasticLevelNeutronScatteringDistribution monte_carlo_collision_native)
ADD_TEST(InelasticLevelNeutronScatteringDistribution_test tstInelasticLevelNeutronScatteringDistribution)

ADD_EXECUTABLE(tstNuclearScatteringDistributionFactoryHelpers
  tstNuclearScatteringDistributionFactoryHelpers.cpp)
TARGET_LINK_LIBRARIES(tstNuclearScatteringDistributionFactoryHelpers monte_carlo_collision_native)
ADD_TEST(NuclearScatteringDistributionFactoryHelpers_test
tstNuclearScatteringDistributionFactoryHelpers
--test_u238_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_u238_ace_file.txt"
--test_u238_ace_table="92238.70c")

ADD_EXECUTABLE(tstNeutronNuclearScatteringDistributionACEFactory
  tstNeutronNuclearScatteringDistributionACEFactory.cpp)
TARGET_LINK_LIBRARIES(tstNeutronNuclearScatteringDistributionACEFactory monte_carlo_collision_native)
ADD_TEST(NeutronNuclearScatteringDistributionACEFactory_test
tstNeutronNuclearScatteringDistributionACEFactory
--test_basic_h1_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h1_ace_file.txt"
--test_basic_h1_ace_table="1001.70c"
--test_basic_o16_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_o16_ace_file.txt"
--test_basic_o16_ace_table="8016.70c")

ADD_EXECUTABLE(tstFissionNeutronMultiplicityDistributionACEFactory
  tstFissionNeutronMultiplicityDistributionACEFactory.cpp)
TARGET_LINK_LIBRARIES(tstFissionNeutronMultiplicityDistributionACEFactory monte_carlo_collision_native)
ADD_TEST(FissionNeutronMultiplicityDistributionACEFactory_test tstFissionNeutronMultiplicityDistributionACEFactory --test_u238_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_u238_ace_file.txt" --test_u238_ace_table="92238.70c")

ADD_EXECUTABLE(tstFissionNeutronMultiplicityDistribution
  tstFissionNeutronMultiplicityDistribution.cpp)
TARGET_LINK_LIBRARIES(tstFissionNeutronMultiplicityDistribution monte_carlo_collision_native)
ADD_TEST(FissionNeutronMultiplicityDistribution_test tstFissionNeutronMultiplicityDistribution --test_u238_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_u238_ace_file.txt" --test_u238_ace_table="92238.70c")

ADD_EXECUTABLE(tstDelayedNeutronEmissionDistributionACEFactory
  tstDelayedNeutronEmissionDistributionACEFactory.cpp)
TARGET_LINK_LIBRARIES(tstDelayedNeutronEmissionDistributionACEFactory monte_carlo_collision_native)
ADD_TEST(DelayedNeutronEmissionDistributionACEFactory_test tstDelayedNeutronEmissionDistributionACEFactory --test_u238_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_u238_ace_file.txt" --test_u238_ace_table="92238.70c")

ADD_EXECUTABLE(tstDelayedNeutronEmissionDistribution
  tstDelayedNeutronEmissionDistribution.cpp)
TARGET_LINK_LIBRARIES(tstDelayedNeutronEmissionDistribution monte_carlo_collision_native)
ADD_TEST(DelayedNeutronEmissionDistribution_test tstDelayedNeutronEmissionDistribution --test_u238_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_u238_ace_file.txt" --test_u238_ace_table="92238.70c")

ADD_EXECUTABLE(tstNuclearReaction
  tstNuclearReaction.cpp)
TARGET_LINK_LIBRARIES(tstNuclearReaction monte_carlo_collision_native)
ADD_TEST(NuclearReaction_test tstNuclearReaction --test_basic_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h1_ace_file.txt" --test_basic_ace_table="1001.70c")

ADD_EXECUTABLE(tstDecoupledPhotonProductionReaction
  tstDecoupledPhotonProductionReaction.cpp)
TARGET_LINK_LIBRARIES(tstDecoupledPhotonProductionReaction monte_carlo_collision_native)
ADD_TEST(DecoupledPhotonProductionReaction_test tstDecoupledPhotonProductionReaction --test_basic_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h1_ace_file.txt" --test_basic_ace_table="1001.70c")

ADD_EXECUTABLE(tstDecoupledYieldBasedPhotonProductionReaction
  tstDecoupledYieldBasedPhotonProductionReaction.cpp)
TARGET_LINK_LIBRARIES(tstDecoupledYieldBasedPhotonProductionReaction monte_carlo_collision_native)
ADD_TEST(DecoupledYieldBasedPhotonProductionReaction_test tstDecoupledYieldBasedPhotonProductionReaction --test_basic_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h1_ace_file.txt" --test_basic_ace_table="1001.70c")

ADD_EXECUTABLE(tstDecoupledCrossSectionBasedPhotonProductionReaction
  tstDecoupledCrossSectionBasedPhotonProductionReaction.cpp)
TARGET_LINK_LIBRARIES(tstDecoupledCrossSectionBasedPhotonProductionReaction monte_carlo_collision_native)
ADD_TEST(DecoupledCrossSectionBasedPhotonProductionReaction_test tstDecoupledCrossSectionBasedPhotonProductionReaction --test_basic_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h1_ace_file.txt" --test_basic_ace_table="1001.70c")

ADD_EXECUTABLE(tstNeutronScatteringReaction
  tstNeutronScatteringReaction.cpp)
TARGET_LINK_LIBRARIES(tstNeutronScatteringReaction monte_carlo_collision_native)
ADD_TEST(NeutronScatteringReaction_test tstNeutronScatteringReaction --test_basic_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h1_ace_file.txt" --test_basic_ace_table="1001.70c")

ADD_EXECUTABLE(tstEnergyDependentNeutronMultiplicityReaction
   tstEnergyDependentNeutronMultiplicityReaction.cpp)
TARGET_LINK_LIBRARIES(tstEnergyDependentNeutronMultiplicityReaction monte_carlo_collision_native)
ADD_TEST(EnergyDependentNeutronMultiplicityReaction_test tstEnergyDependentNeutronMultiplicityReaction --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_o16_ace_file.txt" --test_ace_table="8016.70c")

ADD_EXECUTABLE(tstNeutronAbsorptionReaction
  tstNeutronAbsorptionReaction.cpp)
TARGET_LINK_LIBRARIES(tstNeutronAbsorptionReaction monte_carlo_collision_native)
ADD_TEST(NeutronAbsorptionReaction_test tstNeutronAbsorptionReaction --test_basic_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h1_ace_file.txt" --test_basic_ace_table="1001.70c")

ADD_EXECUTABLE(tstNuclearReactionACEFactory
  tstNuclearReactionACEFactory.cpp)
TARGET_LINK_LIBRARIES(tstNuclearReactionACEFactory monte_carlo_collision_native)
ADD_TEST(NuclearReactionACEFactory_test tstNuclearReactionACEFactory --test_h1_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h1_ace_file.txt" --test_h1_ace_table="1001.70c" --test_o16_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_o16_ace_file.txt" --test_o16_ace_table="8016.70c")

ADD_EXECUTABLE(tstDecoupledPhotonProductionReactionACEFactory
  tstDecoupledPhotonProductionReactionACEFactory.cpp)
TARGET_LINK_LIBRARIES(tstDecoupledPhotonProductionReactionACEFactory monte_carlo_collision_native)
ADD_TEST(DecoupledPhotonProductionReactionACEFactory_test tstDecoupledPhotonProductionReactionACEFactory --test_o16_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_o16_ace_file.txt" --test_o16_ace_table="8016.70c")

ADD_EXECUTABLE(tstNuclide
  tstNuclide.cpp)
TARGET_LINK_LIBRARIES(tstNuclide monte_carlo_collision_native)
ADD_TEST(Nuclide_test tstNuclide --test_h1_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h1_ace_file.txt" --test_h1_ace_table="1001.70c" --test_o16_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_o16_ace_file.txt" --test_o16_ace_table="8016.70c")

ADD_EXECUTABLE(tstNuclideFactory
  tstNuclideFactory.cpp)
TARGET_LINK_LIBRARIES(tstNuclideFactory monte_carlo_collision_native)
ADD_TEST(NuclideFactory_test tstNuclideFactory --test_cross_sections_xml_directory="${CMAKE_CURRENT_SOURCE_DIR}/test_files")

ADD_EXECUTABLE(tstNeutronMaterial
  tstNeutronMaterial.cpp)
TARGET_LINK_LIBRARIES(tstNeutronMaterial monte_carlo_collision_native)
ADD_TEST(NeutronMaterial_test tstNeutronMaterial --test_cross_sections_xml_directory="${CMAKE_CURRENT_SOURCE_DIR}/test_files")

##----------------------------------------------------------------------------##
##      photon class tests                                                    ##
##----------------------------------------------------------------------------##

ADD_EXECUTABLE(tstPhotonuclearNeutronScatteringDistributionACEFactory
	tstPhotonuclearNeutronScatteringDistributionACEFactory.cpp)
TARGET_LINK_LIBRARIES(tstPhotonuclearNeutronScatteringDistributionACEFactory
 monte_carlo_collision_native)
ADD_TEST(PhotonuclearNeutronScatteringDistributionACEFactory_test tstPhotonuclearNeutronScatteringDistributionACEFactory --test_basic_h2_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h2_photonuclear_ace_file.txt" --test_basic_h2_ace_table=1002.24u )

ADD_EXECUTABLE(tstPhotonuclearScatteringDistributionACEFactory
	tstPhotonuclearScatteringDistributionACEFactory.cpp)
TARGET_LINK_LIBRARIES(tstPhotonuclearScatteringDistributionACEFactory
 monte_carlo_collision_native)
ADD_TEST(PhotonuclearScatteringDistributionACEFactory_test tstPhotonuclearScatteringDistributionACEFactory --test_basic_c12_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_c12_photonuclear_ace_file.txt" --test_basic_c12_ace_table=6012.24u )

ADD_EXECUTABLE(tstPhotonuclearReaction
               tstPhotonuclearReaction.cpp)
TARGET_LINK_LIBRARIES(tstPhotonuclearReaction
  monte_carlo_collision_native)
ADD_TEST(PhotonuclearReaction_test tstPhotonuclearReaction --h2_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_h2_photonuclear_ace_file.txt" --h2_ace_table=1002.24u --c12_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_c12_photonuclear_ace_file.txt" --c12_ace_table=6012.24u)

ADD_EXECUTABLE(tstStandardComptonProfile
  tstStandardComptonProfile.cpp)
TARGET_LINK_LIBRARIES(tstStandardComptonProfile monte_carlo_collision_native)
ADD_TEST(StandardComptonProfile_test tstStandardComptonProfile)

ADD_EXECUTABLE(tstStandardScatteringFunction
  tstStandardScatteringFunction.cpp)
TARGET_LINK_LIBRARIES(tstStandardScatteringFunction monte_carlo_collision_native)
ADD_TEST(StandardScatteringFunction_test tstStandardScatteringFunction)

ADD_EXECUTABLE(tstStandardFormFactorSquared
  tstStandardFormFactorSquared.cpp)
TARGET_LINK_LIBRARIES(tstStandardFormFactorSquared monte_carlo_collision_native)
ADD_TEST(StandardFormFactorSquared_test tstStandardFormFactorSquared)

ADD_EXECUTABLE(tstCoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution
  tstCoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution.cpp)
TARGET_LINK_LIBRARIES(tstCoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution monte_carlo_collision_native)
ADD_TEST(CoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution_test tstCoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

# ADD_EXECUTABLE(tstDecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution
#   tstDecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution.cpp)
# TARGET_LINK_LIBRARIES(tstDecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution monte_carlo_collision_native)
# ADD_TEST(DecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution_test tstDecoupledStandardCompleteDopplerBroadenedPhotonEnergyDistribution --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstStandardSubshellDopplerBroadenedPhotonEnergyDistribution
  tstStandardSubshellDopplerBroadenedPhotonEnergyDistribution.cpp)
TARGET_LINK_LIBRARIES(tstStandardSubshellDopplerBroadenedPhotonEnergyDistribution monte_carlo_collision_native)
ADD_TEST(StandardSubshellDopplerBroadenedPhotonEnergyDistribution_test tstStandardSubshellDopplerBroadenedPhotonEnergyDistribution --test_native_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_epr_82_native.xml")

ADD_EXECUTABLE(tstKleinNishinaPhotonScatteringDistribution
  tstKleinNishinaPhotonScatteringDistribution.cpp)
TARGET_LINK_LIBRARIES(tstKleinNishinaPhotonScatteringDistribution monte_carlo_collision_native)
ADD_TEST(KleinNishinaPhotonScatteringDistribution_test tstKleinNishinaPhotonScatteringDistribution)

ADD_EXECUTABLE(tstDetailedWHIncoherentPhotonScatteringDistribution
  tstDetailedWHIncoherentPhotonScatteringDistribution.cpp)
TARGET_LINK_LIBRARIES(tstDetailedWHIncoherentPhotonScatteringDistribution monte_carlo_collision_native)
ADD_TEST(DetailedWHIncoherentPhotonScatteringDistribution_test tstDetailedWHIncoherentPhotonScatteringDistribution --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstDopplerBroadenedHybridIncoherentPhotonScatteringDistribution
  tstDopplerBroadenedHybridIncoherentPhotonScatteringDistribution.cpp)
TARGET_LINK_LIBRARIES(tstDopplerBroadenedHybridIncoherentPhotonScatteringDistribution monte_carlo_collision_native)
ADD_TEST(DopplerBroadenedHybridIncoherentPhotonScatteringDistribution_test tstDopplerBroadenedHybridIncoherentPhotonScatteringDistribution --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstSubshellIncoherentPhotonScatteringDistribution
  tstSubshellIncoherentPhotonScatteringDistribution.cpp)
TARGET_LINK_LIBRARIES(tstSubshellIncoherentPhotonScatteringDistribution monte_carlo_collision_native)
ADD_TEST(SubshellIncoherentPhotonScatteringDistribution_test tstSubshellIncoherentPhotonScatteringDistribution --test_native_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_epr_82_native.xml")

ADD_EXECUTABLE(tstDopplerBroadenedSubshellIncoherentPhotonScatteringDistribution
  tstDopplerBroadenedSubshellIncoherentPhotonScatteringDistribution.cpp)
TARGET_LINK_LIBRARIES(tstDopplerBroadenedSubshellIncoherentPhotonScatteringDistribution monte_carlo_collision_native)
ADD_TEST(DopplerBroadenedSubshellIncoherentPhotonScatteringDistribution_test tstDopplerBroadenedSubshellIncoherentPhotonScatteringDistribution --test_native_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_epr_82_native.xml")

ADD_EXECUTABLE(tstThompsonScatteringDistribution
  tstThompsonScatteringDistribution.cpp)
TARGET_LINK_LIBRARIES(tstThompsonScatteringDistribution monte_carlo_collision_native)
ADD_TEST(ThompsonScatteringDistribution_test tstThompsonScatteringDistribution)

ADD_EXECUTABLE(tstBasicCoherentScatteringDistribution
  tstBasicCoherentScatteringDistribution.cpp)
TARGET_LINK_LIBRARIES(tstBasicCoherentScatteringDistribution monte_carlo_collision_native)
ADD_TEST(BasicCoherentScatteringDistribution_test tstBasicCoherentScatteringDistribution --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstEfficientCoherentScatteringDistribution
  tstEfficientCoherentScatteringDistribution.cpp)
TARGET_LINK_LIBRARIES(tstEfficientCoherentScatteringDistribution monte_carlo_collision_native)
ADD_TEST(EfficientCoherentScatteringDistribution_test tstEfficientCoherentScatteringDistribution --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstIncoherentPhotonScatteringDistributionACEFactory
  tstIncoherentPhotonScatteringDistributionACEFactory.cpp)
TARGET_LINK_LIBRARIES(tstIncoherentPhotonScatteringDistributionACEFactory monte_carlo_collision_native)
ADD_TEST(IncoherentPhotonScatteringDistributionACEFactory_test tstIncoherentPhotonScatteringDistributionACEFactory --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstIncoherentPhotonScatteringDistributionNativeFactory
  tstIncoherentPhotonScatteringDistributionNativeFactory.cpp)
TARGET_LINK_LIBRARIES(tstIncoherentPhotonScatteringDistributionNativeFactory monte_carlo_collision_native)
ADD_TEST(IncoherentPhotonScatteringDistributionNativeFactory_test tstIncoherentPhotonScatteringDistributionNativeFactory --test_native_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_epr_82_native.xml")

ADD_EXECUTABLE(tstCoherentScatteringDistributionACEFactory
  tstCoherentScatteringDistributionACEFactory.cpp)
TARGET_LINK_LIBRARIES(tstCoherentScatteringDistributionACEFactory monte_carlo_collision_native)
ADD_TEST(CoherentScatteringDistributionACEFactory_test tstCoherentScatteringDistributionACEFactory --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstCoherentScatteringDistributionNativeFactory
  tstCoherentScatteringDistributionNativeFactory.cpp)
TARGET_LINK_LIBRARIES(tstCoherentScatteringDistributionNativeFactory monte_carlo_collision_native)
ADD_TEST(CoherentScatteringDistributionNativeFactory_test tstCoherentScatteringDistributionNativeFactory --test_native_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_epr_82_native.xml")

ADD_EXECUTABLE(tstStandardPhotoatomicReaction
  tstStandardPhotoatomicReaction.cpp)
TARGET_LINK_LIBRARIES(tstStandardPhotoatomicReaction monte_carlo_collision_native)
ADD_TEST(StandardPhotoatomicReaction_test tstStandardPhotoatomicReaction --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_photoatomic_ace_file.txt" --test_ace_table=82000.04p)

ADD_EXECUTABLE(tstPairProductionPhotoatomicReaction
  tstPairProductionPhotoatomicReaction.cpp)
TARGET_LINK_LIBRARIES(tstPairProductionPhotoatomicReaction monte_carlo_collision_native)
ADD_TEST(PairProductionPhotoatomicReaction_test tstPairProductionPhotoatomicReaction --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_photoatomic_ace_file.txt" --test_ace_table=82000.04p)

ADD_EXECUTABLE(tstIncoherentPhotoatomicReaction
  tstIncoherentPhotoatomicReaction.cpp)
TARGET_LINK_LIBRARIES(tstIncoherentPhotoatomicReaction monte_carlo_collision_native)
ADD_TEST(IncoherentPhotoatomicReaction_test tstIncoherentPhotoatomicReaction --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstSubshellIncoherentPhotoatomicReaction
  tstSubshellIncoherentPhotoatomicReaction.cpp)
TARGET_LINK_LIBRARIES(tstSubshellIncoherentPhotoatomicReaction monte_carlo_collision_native)
ADD_TEST(SubshellIncoherentPhotoatomicReaction_test tstSubshellIncoherentPhotoatomicReaction --test_native_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_epr_82_native.xml")

ADD_EXECUTABLE(tstCoherentPhotoatomicReaction
  tstCoherentPhotoatomicReaction.cpp)
TARGET_LINK_LIBRARIES(tstCoherentPhotoatomicReaction monte_carlo_collision_native)
ADD_TEST(CoherentPhotoatomicReaction_test tstCoherentPhotoatomicReaction --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstPhotoelectricPhotoatomicReaction
  tstPhotoelectricPhotoatomicReaction.cpp)
TARGET_LINK_LIBRARIES(tstPhotoelectricPhotoatomicReaction monte_carlo_collision_native)
ADD_TEST(PhotoelectricPhotoatomicReaction_test tstPhotoelectricPhotoatomicReaction --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstSubshellPhotoelectricPhotoatomicReaction
  tstSubshellPhotoelectricPhotoatomicReaction.cpp)
TARGET_LINK_LIBRARIES(tstSubshellPhotoelectricPhotoatomicReaction monte_carlo_collision_native)
ADD_TEST(SubshellPhotoelectricPhotoatomicReaction_test tstSubshellPhotoelectricPhotoatomicReaction --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstAbsorptionPhotoatomicReaction
  tstAbsorptionPhotoatomicReaction.cpp)
TARGET_LINK_LIBRARIES(tstAbsorptionPhotoatomicReaction monte_carlo_collision_native)
ADD_TEST(AbsorptionPhotoatomicReaction_test tstAbsorptionPhotoatomicReaction --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstPhotoatomCore tstPhotoatomCore.cpp)
TARGET_LINK_LIBRARIES(tstPhotoatomCore monte_carlo_collision_native)
ADD_TEST(PhotoatomCore_test tstPhotoatomCore --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstPhotoatom tstPhotoatom.cpp)
TARGET_LINK_LIBRARIES(tstPhotoatom monte_carlo_collision_native)
ADD_TEST(Photoatom_test tstPhotoatom --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstPhotoatomicReactionACEFactory
  tstPhotoatomicReactionACEFactory.cpp)
TARGET_LINK_LIBRARIES(tstPhotoatomicReactionACEFactory monte_carlo_collision_native)
ADD_TEST(PhotoatomicReactionACEFactory_test tstPhotoatomicReactionACEFactory --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstPhotoatomicReactionNativeFactory
  tstPhotoatomicReactionNativeFactory.cpp)
TARGET_LINK_LIBRARIES(tstPhotoatomicReactionNativeFactory monte_carlo_collision_native)
ADD_TEST(PhotoatomicReactionNativeFactory_test tstPhotoatomicReactionNativeFactory --test_native_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_epr_82_native.xml")

ADD_EXECUTABLE(tstPhotoatomACEFactory
  tstPhotoatomACEFactory.cpp)
TARGET_LINK_LIBRARIES(tstPhotoatomACEFactory monte_carlo_collision_native)
ADD_TEST(PhotoatomACEFactory_test tstPhotoatomACEFactory --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstPhotoatomFactory
  tstPhotoatomFactory.cpp)
TARGET_LINK_LIBRARIES(tstPhotoatomFactory monte_carlo_collision_native)
ADD_TEST(PhotoatomFactory_test tstPhotoatomFactory --test_cross_sections_xml_directory="${CMAKE_CURRENT_SOURCE_DIR}/test_files/")

ADD_EXECUTABLE(tstPhotonMaterial tstPhotonMaterial.cpp)
TARGET_LINK_LIBRARIES(tstPhotonMaterial monte_carlo_collision_native)
ADD_TEST(PhotonMaterial_test tstPhotonMaterial --test_cross_sections_xml_directory="${CMAKE_CURRENT_SOURCE_DIR}/test_files/")

ADD_EXECUTABLE(tstIncoherentAdjointPhotonScatteringDistribution
  tstIncoherentAdjointPhotonScatteringDistribution.cpp)
TARGET_LINK_LIBRARIES(tstIncoherentAdjointPhotonScatteringDistribution monte_carlo_collision_native)
ADD_TEST(IncoherentAdjointPhotonScatteringDistribution_test tstIncoherentAdjointPhotonScatteringDistribution)

ADD_EXECUTABLE(tstKleinNishinaAdjointPhotonScatteringDistribution
  tstKleinNishinaAdjointPhotonScatteringDistribution.cpp)
TARGET_LINK_LIBRARIES(tstKleinNishinaAdjointPhotonScatteringDistribution monte_carlo_collision_native)
ADD_TEST(KleinNishinaAdjointPhotonScatteringDistribution_test tstKleinNishinaAdjointPhotonScatteringDistribution)

# ADD_EXECUTABLE(tstWHIncoherentAdjointPhotonScatteringDistribution
#   tstWHIncoherentAdjointPhotonScatteringDistribution.cpp)
# TARGET_LINK_LIBRARIES(tstWHIncoherentAdjointPhotonScatteringDistribution monte_carlo_collision_native)
# ADD_TEST(WHIncoherentAdjointPhotonScatteringDistribution_test tstWHIncoherentAdjointPhotonScatteringDistribution --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

##----------------------------------------------------------------------------##
##      electron class tests                                                  
##----------------------------------------------------------------------------##


##      electron distribution tests                                           
ADD_EXECUTABLE(tstHardElasticElectronScatteringDistribution
  tstHardElasticElectronScatteringDistribution.cpp)
TARGET_LINK_LIBRARIES(tstHardElasticElectronScatteringDistribution monte_carlo_collision_native)
ADD_TEST(HardElasticElectronScatteringDistribution_test tstHardElasticElectronScatteringDistribution --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstAtomicExcitationElectronScatteringDistribution
  tstAtomicExcitationElectronScatteringDistribution.cpp)
TARGET_LINK_LIBRARIES(tstAtomicExcitationElectronScatteringDistribution monte_carlo_collision_native)
ADD_TEST(AtomicExcitationElectronScatteringDistribution_test tstAtomicExcitationElectronScatteringDistribution --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstBremsstrahlungElectronScatteringDistribution
  tstBremsstrahlungElectronScatteringDistribution.cpp)
TARGET_LINK_LIBRARIES(tstBremsstrahlungElectronScatteringDistribution monte_carlo_collision_native)
ADD_TEST(BremsstrahlungElectronScatteringDistribution_test tstBremsstrahlungElectronScatteringDistribution --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstElectroionizationSubshellElectronScatteringDistribution
  tstElectroionizationSubshellElectronScatteringDistribution.cpp)
TARGET_LINK_LIBRARIES(tstElectroionizationSubshellElectronScatteringDistribution monte_carlo_collision_native)
ADD_TEST(ElectroionizationSubshellElectronScatteringDistribution_test tstElectroionizationSubshellElectronScatteringDistribution --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

##      electron distribution ace factory tests 

##      electron distribution native factory tests 

##      electroatomic reaction tests  
ADD_EXECUTABLE(tstAbsorptionElectroatomicReaction
  tstAbsorptionElectroatomicReaction.cpp)
TARGET_LINK_LIBRARIES(tstAbsorptionElectroatomicReaction monte_carlo_collision_native)
ADD_TEST(AbsorptionElectroatomicReaction_test tstAbsorptionElectroatomicReaction --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstAtomicExcitationElectroatomicReaction
  tstAtomicExcitationElectroatomicReaction.cpp)
TARGET_LINK_LIBRARIES(tstAtomicExcitationElectroatomicReaction monte_carlo_collision_native)
ADD_TEST(AtomicExcitationElectroatomicReaction_test tstAtomicExcitationElectroatomicReaction --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstBremsstrahlungElectroatomicReaction
  tstBremsstrahlungElectroatomicReaction.cpp)
TARGET_LINK_LIBRARIES(tstBremsstrahlungElectroatomicReaction monte_carlo_collision_native)
ADD_TEST(BremsstrahlungElectroatomicReaction_test tstBremsstrahlungElectroatomicReaction --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstElectroionizationSubshellElectroatomicReaction
  tstElectroionizationSubshellElectroatomicReaction.cpp)
TARGET_LINK_LIBRARIES(tstElectroionizationSubshellElectroatomicReaction monte_carlo_collision_native)
ADD_TEST(ElectroionizationSubshellElectroatomicReaction_test tstElectroionizationSubshellElectroatomicReaction --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstHardElasticElectroatomicReaction
  tstHardElasticElectroatomicReaction.cpp)
TARGET_LINK_LIBRARIES(tstHardElasticElectroatomicReaction monte_carlo_collision_native)
ADD_TEST(HardElasticElectroatomicReaction_test tstHardElasticElectroatomicReaction --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstElectroatomicReactionACEFactory
  tstElectroatomicReactionACEFactory.cpp)
TARGET_LINK_LIBRARIES(tstElectroatomicReactionACEFactory monte_carlo_collision_native)
ADD_TEST(ElectroatomicReactionACEFactory_test tstElectroatomicReactionACEFactory --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

##      electroatom tests  
ADD_EXECUTABLE(tstElectroatomCore
  tstElectroatomCore.cpp)
TARGET_LINK_LIBRARIES(tstElectroatomCore monte_carlo_collision_native)
ADD_TEST(ElectroatomCore_test tstElectroatomCore --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstElectroatom
  tstElectroatom.cpp)
TARGET_LINK_LIBRARIES(tstElectroatom monte_carlo_collision_native)
ADD_TEST(Electroatom_test tstElectroatom --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstElectroatomACEFactory
  tstElectroatomACEFactory.cpp)
TARGET_LINK_LIBRARIES(tstElectroatomACEFactory monte_carlo_collision_native)
ADD_TEST(ElectroatomACEFactory_test tstElectroatomACEFactory --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstElectroatomFactory
  tstElectroatomFactory.cpp)
TARGET_LINK_LIBRARIES(tstElectroatomFactory monte_carlo_collision_native)
ADD_TEST(ElectroatomFactory_test tstElectroatomFactory --test_cross_sections_xml_directory="${CMAKE_CURRENT_SOURCE_DIR}/test_files/")

##      electron materials tests 
ADD_EXECUTABLE(tstElectronMaterial tstElectronMaterial.cpp)
TARGET_LINK_LIBRARIES(tstElectronMaterial monte_carlo_collision_native)
ADD_TEST(ElectronMaterial_test tstElectronMaterial --test_cross_sections_xml_directory="${CMAKE_CURRENT_SOURCE_DIR}/test_files/")

##----------------------------------------------------------------------------##
##      atomic relaxation class tests                                         ##
##----------------------------------------------------------------------------##

ADD_EXECUTABLE(tstDetailedSubshellRelaxationModel
  tstDetailedSubshellRelaxationModel.cpp)
TARGET_LINK_LIBRARIES(tstDetailedSubshellRelaxationModel monte_carlo_collision_native)
ADD_TEST(DetailedSubshellRelaxationModel_test tstDetailedSubshellRelaxationModel --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstDetailedAtomicRelaxationModel
  tstDetailedAtomicRelaxationModel.cpp)
TARGET_LINK_LIBRARIES(tstDetailedAtomicRelaxationModel monte_carlo_collision_native)
ADD_TEST(DetailedAtomicRelaxationModel_test tstDetailedAtomicRelaxationModel --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p)

ADD_EXECUTABLE(tstAtomicRelaxationModelFactory
  tstAtomicRelaxationModelFactory.cpp)
TARGET_LINK_LIBRARIES(tstAtomicRelaxationModelFactory monte_carlo_collision_native)
ADD_TEST(AtomicRelaxationModelFactory_test tstAtomicRelaxationModelFactory --test_ace_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_pb_epr_ace_file.txt" --test_ace_table=82000.12p --test_native_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_epr_82_native.xml")

##----------------------------------------------------------------------------##
##      collision handler class tests                                         ##
##----------------------------------------------------------------------------##

ADD_EXECUTABLE(tstCollisionHandler
  tstCollisionHandler.cpp)
TARGET_LINK_LIBRARIES(tstCollisionHandler monte_carlo_collision_native)
ADD_TEST(CollisionHandler_test tstCollisionHandler --test_cross_sections_xml_directory="${CMAKE_CURRENT_SOURCE_DIR}/test_files")

IF(FRENSIE_ENABLE_DAGMC)
  ADD_EXECUTABLE(tstCollisionHandlerFactoryNeutronMode_DagMC
    tstCollisionHandlerFactoryNeutronMode_DagMC.cpp)
  TARGET_LINK_LIBRARIES(tstCollisionHandlerFactoryNeutronMode_DagMC monte_carlo_collision_native)
  ADD_TEST(CollisionHandlerFactoryNeutronMode_DagMC_test tstCollisionHandlerFactoryNeutronMode_DagMC --test_cross_sections_xml_directory="${CMAKE_CURRENT_SOURCE_DIR}/test_files" --test_mat_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_material.xml" --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom.xml")
ENDIF()

IF(FRENSIE_ENABLE_DAGMC)
  ADD_EXECUTABLE(tstCollisionHandlerFactoryPhotonMode_DagMC
    tstCollisionHandlerFactoryPhotonMode_DagMC.cpp)
  TARGET_LINK_LIBRARIES(tstCollisionHandlerFactoryPhotonMode_DagMC monte_carlo_collision_native)
  ADD_TEST(CollisionHandlerFactoryPhotonMode_DagMC_test tstCollisionHandlerFactoryPhotonMode_DagMC --test_cross_sections_xml_directory="${CMAKE_CURRENT_SOURCE_DIR}/test_files" --test_mat_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_material.xml" --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom.xml")
ENDIF()

IF(FRENSIE_ENABLE_DAGMC)
  ADD_EXECUTABLE(tstCollisionHandlerFactoryNeutronPhotonMode_DagMC
    tstCollisionHandlerFactoryNeutronPhotonMode_DagMC.cpp)
  TARGET_LINK_LIBRARIES(tstCollisionHandlerFactoryNeutronPhotonMode_DagMC monte_carlo_collision_native)
  ADD_TEST(CollisionHandlerFactoryNeutronPhotonMode_DagMC_test tstCollisionHandlerFactoryNeutronPhotonMode_DagMC --test_cross_sections_xml_directory="${CMAKE_CURRENT_SOURCE_DIR}/test_files" --test_mat_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_material.xml" --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom.xml")
ENDIF()

IF(FRENSIE_ENABLE_DAGMC)
  ADD_EXECUTABLE(tstCollisionHandlerFactoryElectronMode_DagMC
    tstCollisionHandlerFactoryElectronMode_DagMC.cpp)
  TARGET_LINK_LIBRARIES(tstCollisionHandlerFactoryElectronMode_DagMC monte_carlo_collision_native)
  ADD_TEST(CollisionHandlerFactoryElectronMode_DagMC_test tstCollisionHandlerFactoryElectronMode_DagMC --test_cross_sections_xml_directory="${CMAKE_CURRENT_SOURCE_DIR}/test_files" --test_mat_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_material.xml" --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom.xml")
ENDIF()

IF(FRENSIE_ENABLE_ROOT)
  ADD_EXECUTABLE(tstCollisionHandlerFactoryNeutronMode_Root
    tstCollisionHandlerFactoryNeutronMode_Root.cpp)
  TARGET_LINK_LIBRARIES(tstCollisionHandlerFactoryNeutronMode_Root monte_carlo_collision_native geometry_root)
  ADD_TEST(CollisionHandlerFactoryNeutronMode_Root_test tstCollisionHandlerFactoryNeutronMode_Root --test_cross_sections_xml_directory="${CMAKE_CURRENT_SOURCE_DIR}/test_files" --test_mat_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_material_root.xml" --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_root.xml")
ENDIF()

IF(FRENSIE_ENABLE_ROOT)
  ADD_EXECUTABLE(tstCollisionHandlerFactoryPhotonMode_Root
    tstCollisionHandlerFactoryPhotonMode_Root.cpp)
  TARGET_LINK_LIBRARIES(tstCollisionHandlerFactoryPhotonMode_Root monte_carlo_collision_native geometry_root)
  ADD_TEST(CollisionHandlerFactoryPhotonMode_Root_test tstCollisionHandlerFactoryPhotonMode_Root --test_cross_sections_xml_directory="${CMAKE_CURRENT_SOURCE_DIR}/test_files" --test_mat_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_material_root.xml" --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_root.xml")
ENDIF()

IF(FRENSIE_ENABLE_ROOT)
  ADD_EXECUTABLE(tstCollisionHandlerFactoryNeutronPhotonMode_Root
    tstCollisionHandlerFactoryNeutronPhotonMode_Root.cpp)
  TARGET_LINK_LIBRARIES(tstCollisionHandlerFactoryNeutronPhotonMode_Root monte_carlo_collision_native geometry_root)
  ADD_TEST(CollisionHandlerFactoryNeutronPhotonMode_Root_test tstCollisionHandlerFactoryNeutronPhotonMode_Root --test_cross_sections_xml_directory="${CMAKE_CURRENT_SOURCE_DIR}/test_files" --test_mat_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_material_root.xml" --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_root.xml")
ENDIF()

IF(FRENSIE_ENABLE_ROOT)
  ADD_EXECUTABLE(tstCollisionHandlerFactoryElectronMode_Root
    tstCollisionHandlerFactoryElectronMode_Root.cpp)
  TARGET_LINK_LIBRARIES(tstCollisionHandlerFactoryElectronMode_Root monte_carlo_collision_native geometry_root)
  ADD_TEST(CollisionHandlerFactoryElectronMode_Root_test tstCollisionHandlerFactoryElectronMode_Root --test_cross_sections_xml_directory="${CMAKE_CURRENT_SOURCE_DIR}/test_files" --test_mat_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_material_root.xml" --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom_root.xml")
ENDIF()

IF(FRENSIE_ENABLE_DAGMC)
  ADD_EXECUTABLE(tstCollisionModuleInterface_Native_DagMC
    tstModuleInterface_DagMC.cpp)
  TARGET_LINK_LIBRARIES(tstCollisionModuleInterface_Native_DagMC monte_carlo_collision_native)
  ADD_TEST(CollisionModuleInterface_Native_DagMC_test tstCollisionModuleInterface_Native_DagMC --test_cross_sections_xml_directory="${CMAKE_CURRENT_SOURCE_DIR}/test_files" --test_mat_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_material.xml" --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom.xml")
ENDIF()

IF(FRENSIE_ENABLE_DAGMC)
  ADD_EXECUTABLE(tstCollisionModuleInterface_NativeElectronMode_DagMC
    tstModuleInterface_ElectronMode_DagMC.cpp)
  TARGET_LINK_LIBRARIES(tstCollisionModuleInterface_NativeElectronMode_DagMC monte_carlo_collision_native)
  ADD_TEST(CollisionModuleInterface_NativeElectronMode_DagMC_test tstCollisionModuleInterface_NativeElectronMode_DagMC --test_cross_sections_xml_directory="${CMAKE_CURRENT_SOURCE_DIR}/test_files" --test_mat_xml_file="${CMAKE_CURRENT_SOURCE_DIR}/test_files/test_material.xml" --test_geom_xml_file="${CMAKE_CURRENT_BINARY_DIR}/test_files/test_geom.xml")
ENDIF()
