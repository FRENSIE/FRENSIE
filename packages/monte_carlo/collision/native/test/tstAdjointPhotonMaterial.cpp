//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointPhotonMaterial.cpp
//! \author Alex Robinson
//! \brief  The adjoint photon material unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatomFactory.hpp"
#include "MonteCarlo_AdjointPhotonMaterial.hpp"
#include "MonteCarlo_AdjointPhotonProbeState.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointPhotonMaterial> material;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the material id can be returned
TEUCHOS_UNIT_TEST( AdjointPhotonMaterial, getId )
{
  TEST_EQUALITY_CONST( material->getId(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the number density can be returned
TEUCHOS_UNIT_TEST( AdjointPhotonMaterial, getNumberDensity )
{
  TEST_EQUALITY_CONST( material->getNumberDensity(), 2.14418119321605830e-02 );
}

//---------------------------------------------------------------------------//
// Check if the energy corresponds to a line energy reaction
TEUCHOS_UNIT_TEST( AdjointPhotonMaterial, doesEnergyHaveLineEnergyReaction )
{
  TEST_ASSERT( !material->doesEnergyHaveLineEnergyReaction( 0.51 ) );
  TEST_ASSERT( material->doesEnergyHaveLineEnergyReaction( Utility::PhysicalConstants::electron_rest_mass_energy ) );
  TEST_ASSERT( !material->doesEnergyHaveLineEnergyReaction( 0.52 ) );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total cross section can be returned
TEUCHOS_UNIT_TEST( AdjointPhotonMaterial, getMacroscopicTotalCrossSection )
{
  double cross_section = material->getMacroscopicTotalCrossSection( 1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 2.1567210358522892, 1e-12 );

  cross_section = material->getMacroscopicTotalCrossSection( 1.0 );

  TEST_FLOATING_EQUALITY( cross_section, 0.11818718496285092, 1e-12 );

  cross_section = material->getMacroscopicTotalCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 4.2078239999303496e-07, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total line energy cross section can be returned
TEUCHOS_UNIT_TEST( AdjointPhotonMaterial,
                   getMacroscopicTotalLineEnergyCrossSection )
{
  double cross_section =
    material->getMacroscopicTotalLineEnergyCrossSection( 0.51 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = material->getMacroscopicTotalLineEnergyCrossSection( Utility::PhysicalConstants::electron_rest_mass_energy );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.3293792838826523, 1e-12 );

  cross_section = material->getMacroscopicTotalLineEnergyCrossSection( 0.52 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic total forward cross section can be returned
TEUCHOS_UNIT_TEST( AdjointPhotonMaterial,
                   getMacroscopicTotalForwardCrossSection )
{
  double cross_section =
    material->getMacroscopicTotalForwardCrossSection( 1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 1568.1797769044053, 1e-12 );

  cross_section = material->getMacroscopicTotalForwardCrossSection( 1.0 );

  TEST_FLOATING_EQUALITY( cross_section, 0.06351941670470171, 1e-12 );

  cross_section = material->getMacroscopicTotalForwardCrossSection( 20.0 );

  TEST_FLOATING_EQUALITY( cross_section, 0.02332997862851693, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic absorption cross section can be returned
TEUCHOS_UNIT_TEST( AdjointPhotonMaterial,
                   getMacroscopicAbsorptionCrossSection )
{
  double cross_section =
    material->getMacroscopicAbsorptionCrossSection( 1e-3 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = material->getMacroscopicAbsorptionCrossSection( 1.0 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = material->getMacroscopicAbsorptionCrossSection( 20.0 );

  TEST_EQUALITY_CONST( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint weight factor can be returned
TEUCHOS_UNIT_TEST( AdjointPhotonMaterial, getAdjointWeightFactor )
{
  double weight_factor = material->getAdjointWeightFactor( 1e-3 );
  
  TEST_FLOATING_EQUALITY( weight_factor, 0.00137530216089743699, 1e-12 );

  weight_factor = material->getAdjointWeightFactor( 1.0 );

  TEST_FLOATING_EQUALITY( weight_factor, 1.86064657224887142, 1e-12 );

  weight_factor = material->getAdjointWeightFactor( 20.0 );

  TEST_FLOATING_EQUALITY( weight_factor, 1.8036124537152385e-05, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the adjoing line energy weight factor can be returned
TEUCHOS_UNIT_TEST( AdjointPhotonMaterial, getAdjointLineEnergyWeightFactor )
{
  double weight_factor =
    material->getAdjointLineEnergyWeightFactor( 0.51 );
  
  TEST_EQUALITY_CONST( weight_factor, 0.0 );

  weight_factor = material->getAdjointLineEnergyWeightFactor( Utility::PhysicalConstants::electron_rest_mass_energy );

  TEST_FLOATING_EQUALITY( weight_factor, 3.80493907935216980e+00, 1e-12 );

  weight_factor = material->getAdjointLineEnergyWeightFactor( 0.52 );

  TEST_EQUALITY_CONST( weight_factor, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the survival probability can be returned
TEUCHOS_UNIT_TEST( AdjointPhotonMaterial, getSurvivalProbability )
{
  double survival_prob = material->getSurvivalProbability( 1e-3 );

  TEST_EQUALITY_CONST( survival_prob, 1.0 );

  survival_prob = material->getSurvivalProbability( 1.0 );

  TEST_EQUALITY_CONST( survival_prob, 1.0 );

  survival_prob = material->getSurvivalProbability( 1.0 );

  TEST_EQUALITY_CONST( survival_prob, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the macroscopic cross section for a specific reaction can
// be returned
TEUCHOS_UNIT_TEST( AdjointPhotonMaterial, getMacroscopicReactionCrossSection )
{
  // Check the atomic total cross section
  double cross_section = material->getMacroscopicReactionCrossSection( 1e-3, MonteCarlo::TOTAL_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.1567210358522892, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 1.0, MonteCarlo::TOTAL_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.11818718496285092, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 20.0, MonteCarlo::TOTAL_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 4.2078239999303496e-07, 1e-12 );

  // Check the total incoherent cross section
  cross_section = material->getMacroscopicReactionCrossSection( 1e-3, MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.01331366707462057, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 1.0, MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.11801915819678965, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 20.0, MonteCarlo::TOTAL_INCOHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  // Check the coherent cross section
  cross_section = material->getMacroscopicReactionCrossSection( 1e-3, MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 2.1434073687776687, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 1.0, MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 0.00016802676606128398, 1e-12 );

  cross_section = material->getMacroscopicReactionCrossSection( 20.0, MonteCarlo::COHERENT_ADJOINT_PHOTOATOMIC_REACTION );

  TEST_FLOATING_EQUALITY( cross_section, 4.2078239999303496e-07, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that an adjoint photon can collide with the material
TEUCHOS_UNIT_TEST( AdjointPhotonMaterial, collideAnalogue )
{
  // Sample the incoherent reaction
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.99; // choose the only photoatom
  fake_stream[1] = 0.78; // choose incoherent scattering
  fake_stream[2] = 0.15; // branch 1
  fake_stream[3] = 0.4721647344828152; // select x = 0.9
  fake_stream[4] = 0.49; // accept
  fake_stream[5] = 0.91; // reject based on scattering function
  fake_stream[6] = 0.15; // branch 1
  fake_stream[7] = 0.4721647344828152; // select x = 0.9
  fake_stream[8] = 0.49; // accept
  fake_stream[9] = 0.909; // accept based on scattering function
  fake_stream[10] = 0.0;
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  MonteCarlo::AdjointPhotonState adjoint_photon( 0 );
  adjoint_photon.setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy/10.0 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  material->collideAnalogue( adjoint_photon, bank );

  TEST_ASSERT( !adjoint_photon.isGone() );
  TEST_FLOATING_EQUALITY( adjoint_photon.getEnergy(),
			  0.05677765668111111,
			  1e-15 );
  TEST_EQUALITY_CONST( adjoint_photon.getWeight(), 1.0 );
  TEST_EQUALITY_CONST( bank.size(), 0 );

  // Sample the coherent reaction
  fake_stream.resize( 7 );
  fake_stream[0] = 0.99; // choose the only photoatom
  fake_stream[1] = 0.79; // choose coherent scattering
  fake_stream[2] = 1.00475965594E-03; // sample form factor function squared (y = 1E6 cm)
  fake_stream[3] = 9.98800000000E-01; // reject the cosine scattering angle form function rejection loop
  fake_stream[4] = 6.50327467413E-01; // sample form factor function squared (y = 3E7 cm)
  fake_stream[5] = 5.07800000000E-01; // accept the cosine scattering angle form function rejection loop
  fake_stream[6] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  adjoint_photon.setEnergy( 4.95936772145E-03 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon.setWeight( 1.0 );

  material->collideAnalogue( adjoint_photon, bank );

  TEST_ASSERT( !adjoint_photon.isGone() );
  TEST_FLOATING_EQUALITY( adjoint_photon.getEnergy(),
			  4.95936772145E-03,
			  1e-15 );
  TEST_EQUALITY_CONST( adjoint_photon.getWeight(), 1.0 );
  TEST_EQUALITY_CONST( bank.size(), 0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that an adjoint photon can collide with the material and survival
// bias
TEUCHOS_UNIT_TEST( AdjointPhotonMaterial, collideSurvivalBias )
{
  // Sample the incoherent reaction
  std::vector<double> fake_stream( 11 );
  fake_stream[0] = 0.99; // choose the only photoatom
  fake_stream[1] = 0.78; // choose incoherent scattering
  fake_stream[2] = 0.15; // branch 1
  fake_stream[3] = 0.4721647344828152; // select x = 0.9
  fake_stream[4] = 0.49; // accept
  fake_stream[5] = 0.91; // reject based on scattering function
  fake_stream[6] = 0.15; // branch 1
  fake_stream[7] = 0.4721647344828152; // select x = 0.9
  fake_stream[8] = 0.49; // accept
  fake_stream[9] = 0.909; // accept based on scattering function
  fake_stream[10] = 0.0;
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  MonteCarlo::AdjointPhotonState adjoint_photon( 0 );
  adjoint_photon.setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy/10.0 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  material->collideSurvivalBias( adjoint_photon, bank );

  TEST_ASSERT( !adjoint_photon.isGone() );
  TEST_FLOATING_EQUALITY( adjoint_photon.getEnergy(),
			  0.05677765668111111,
			  1e-15 );
  TEST_EQUALITY_CONST( adjoint_photon.getWeight(), 1.0 );
  TEST_EQUALITY_CONST( bank.size(), 0 );

  // Sample the coherent reaction
  fake_stream.resize( 7 );
  fake_stream[0] = 0.99; // choose the only photoatom
  fake_stream[1] = 0.79; // choose coherent scattering
  fake_stream[2] = 1.00475965594E-03; // sample form factor function squared (y = 1E6 cm)
  fake_stream[3] = 9.98800000000E-01; // reject the cosine scattering angle form function rejection loop
  fake_stream[4] = 6.50327467413E-01; // sample form factor function squared (y = 3E7 cm)
  fake_stream[5] = 5.07800000000E-01; // accept the cosine scattering angle form function rejection loop
  fake_stream[6] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  adjoint_photon.setEnergy( 4.95936772145E-03 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon.setWeight( 1.0 );

  material->collideSurvivalBias( adjoint_photon, bank );

  TEST_ASSERT( !adjoint_photon.isGone() );
  TEST_FLOATING_EQUALITY( adjoint_photon.getEnergy(),
			  4.95936772145E-03,
			  1e-15 );
  TEST_EQUALITY_CONST( adjoint_photon.getWeight(), 1.0 );
  TEST_EQUALITY_CONST( bank.size(), 0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that an adjoint photon at a line energy can collide with the
// material
TEUCHOS_UNIT_TEST( AdjointPhotonMaterial, collideAtLineEnergy )
{
  // Sample the pair production reaction
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.99; // select the only photoatom
  fake_stream[1] = 0.95; // select pair production
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  std::unique_ptr<MonteCarlo::AdjointPhotonProbeState>
    adjoint_photon( new MonteCarlo::AdjointPhotonProbeState( 0 ) );
  adjoint_photon->setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );
  adjoint_photon->setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon->setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  material->collideAtLineEnergy( *adjoint_photon, bank );

  TEST_ASSERT( adjoint_photon->isGone() );
  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 
                          2*Utility::PhysicalConstants::electron_rest_mass_energy,
                          1e-15 );

  bank.pop();

  // Sample the triplet production reaction
  fake_stream[0] = 0.99; // select the only photoatom
  fake_stream[1] = 0.96; // select triplet production
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;
  fake_stream[4] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  
  adjoint_photon.reset( new MonteCarlo::AdjointPhotonProbeState( 0 ) );
  adjoint_photon->setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );
  adjoint_photon->setDirection( 0.0, 0.0, 1.0 );
  adjoint_photon->setWeight( 1.0 );

  material->collideAtLineEnergy( *adjoint_photon, bank );

  TEST_ASSERT( adjoint_photon->isGone() );
  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 
                          4*Utility::PhysicalConstants::electron_rest_mass_energy,
                          1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_cross_sections_xml_directory;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_cross_sections_xml_directory",
                   &test_cross_sections_xml_directory,
                   "Directory where test cross_sections.xml file is located.");
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Assign the name of the cross_sections.xml file with path
  std::string cross_sections_xml_file = test_cross_sections_xml_directory;
  cross_sections_xml_file += "/cross_sections.xml";

  // Read in the xml file storing the cross section table info
  Teuchos::ParameterList cross_section_table_info;
  Teuchos::updateParametersFromXmlFile(
                               cross_sections_xml_file,
                               Teuchos::inoutArg( cross_section_table_info ) );

  std::unordered_set<std::string> atom_aliases;
  atom_aliases.insert( "Si-Native" );

  // Create the atom factory
  MonteCarlo::SimulationProperties properties;
  properties.setMaxAdjointPhotonEnergy( 20.0 );
  properties.setNumberOfAdjointPhotonHashGridBins( 100 );
  properties.setIncoherentAdjointModelType( MonteCarlo::WH_INCOHERENT_ADJOINT_MODEL );
  
  MonteCarlo::AdjointPhotoatomFactory factory(
                                             test_cross_sections_xml_directory,
                                             cross_section_table_info,
                                             atom_aliases,
                                             properties );

  std::unordered_map<std::string,Teuchos::RCP<MonteCarlo::AdjointPhotoatom> >
    atom_map;

  factory.createAdjointPhotoatomMap( atom_map );

  // Assign the atom fractions and names
  Teuchos::Array<double> atom_fractions( 1 );
  Teuchos::Array<std::string> atom_names( 1 );

  atom_fractions[0] = -1.0; // weight fraction
  atom_names[0] = "Si-Native";

  // Create the test material
  material.reset( new MonteCarlo::AdjointPhotonMaterial( 0,
                                                         -1.0,
                                                         atom_map,
                                                         atom_fractions,
                                                         atom_names ) );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAdjointPhotonMaterial.cpp
//---------------------------------------------------------------------------//
