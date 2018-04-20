//---------------------------------------------------------------------------//
//!
//! \file   tstNuclide.cpp
//! \author Alex Robinson
//! \brief  Nuclide class unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_Nuclide.hpp"
#include "MonteCarlo_NeutronNuclearReactionACEFactory.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::Nuclide> h1_nuclide;
std::shared_ptr<const MonteCarlo::Nuclide> o16_nuclide;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the nuclide name can be returned
FRENSIE_UNIT_TEST( Nuclide_hydrogen, getName )
{
  FRENSIE_CHECK_EQUAL( h1_nuclide->getName(), "1001.70c" );
}

//---------------------------------------------------------------------------//
// Check that the nuclide id can be returned
FRENSIE_UNIT_TEST( Nuclide_hydrogen, getId )
{
  FRENSIE_CHECK_EQUAL( h1_nuclide->getId(), 100170u );
}

//---------------------------------------------------------------------------//
// Check that the nuclide atomic number can be returned
FRENSIE_UNIT_TEST( Nuclide_hydrogen, getAtomicNumber )
{
  FRENSIE_CHECK_EQUAL( h1_nuclide->getAtomicMassNumber(), 1u );
}

//---------------------------------------------------------------------------//
// Check that the nuclide atomic mass number can be returned
FRENSIE_UNIT_TEST( Nuclide_hydrogen, getAtomicMassNumber )
{
  FRENSIE_CHECK_EQUAL( h1_nuclide->getAtomicMassNumber(), 1u );
}

//---------------------------------------------------------------------------//
// Check that the nuclide isomer number can be returned
FRENSIE_UNIT_TEST( Nuclide_hydrogen, getIsomerNumber )
{
  FRENSIE_CHECK_EQUAL( h1_nuclide->getIsomerNumber(), 0u );
}

//---------------------------------------------------------------------------//
// Check that the atomic weight ratio can be returned
FRENSIE_UNIT_TEST( Nuclide_hydrogen, getAtomicWeightRatio )
{
  FRENSIE_CHECK_EQUAL( h1_nuclide->getAtomicWeightRatio(), 0.999167 );
}

//---------------------------------------------------------------------------//
// Check that the temperature can be returned
FRENSIE_UNIT_TEST( Nuclide_hydrogen, getTemperature )
{
  FRENSIE_CHECK_EQUAL( h1_nuclide->getTemperature(), 2.53010e-8 );
}

//---------------------------------------------------------------------------//
// Check that the total cross section can be returned
FRENSIE_UNIT_TEST( Nuclide_hydrogen, getTotalCrossSection )
{
  double cross_section = h1_nuclide->getTotalCrossSection( 1.0e-11 );

  FRENSIE_CHECK_EQUAL( cross_section, 1.17724711e3 );

  cross_section = h1_nuclide->getTotalCrossSection( 1.015625e-11 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.168262615e3, 1e-15 );

  cross_section = h1_nuclide->getTotalCrossSection( 1.03125e-11 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.15927812e3, 1e-15 );

  cross_section = h1_nuclide->getTotalCrossSection( 1.046875e-11 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.15069229e3, 1e-9 );

  cross_section = h1_nuclide->getTotalCrossSection( 1.0625e-11 );

  FRENSIE_CHECK_EQUAL( cross_section, 1.14210646e3 );

  cross_section = h1_nuclide->getTotalCrossSection( 1.90e1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 5.08805961e-1, 1e-9 );

  cross_section = h1_nuclide->getTotalCrossSection( 1.925e1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 5.02148202e-1, 1e-9 );

  cross_section = h1_nuclide->getTotalCrossSection( 1.95e1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.95490443e-1, 1e-9 );

  cross_section = h1_nuclide->getTotalCrossSection( 1.975e1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.891319335e-1, 1e-9 );

  cross_section = h1_nuclide->getTotalCrossSection( 2.0e1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.82773424e-1, 1e-9 );
}

//---------------------------------------------------------------------------//
// Check that the absorption cross section can be returned
FRENSIE_UNIT_TEST( Nuclide_hydrogen, getAbsorptionCrossSection )
{
  double cross_section = h1_nuclide->getAbsorptionCrossSection(1.0e-11 );

  FRENSIE_CHECK_EQUAL( cross_section, 1.670111e1 );

  cross_section = h1_nuclide->getAbsorptionCrossSection( 1.015625e-11 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.6573615e1, 1e-15 );

  cross_section = h1_nuclide->getAbsorptionCrossSection( 1.03125e-11 );

  FRENSIE_CHECK_EQUAL( cross_section, 1.644612e1 );

  cross_section = h1_nuclide->getAbsorptionCrossSection( 1.046875e-11 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.632429e1, 1e-15 );

  cross_section = h1_nuclide->getAbsorptionCrossSection( 1.0625e-11 );

  FRENSIE_CHECK_EQUAL( cross_section, 1.620246e1 );

  cross_section = h1_nuclide->getAbsorptionCrossSection( 1.90e1 );

  FRENSIE_CHECK_EQUAL( cross_section, 2.766095e-5 );

  cross_section = h1_nuclide->getAbsorptionCrossSection( 1.925e1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.755177e-5, 1e-15 );

  cross_section = h1_nuclide->getAbsorptionCrossSection( 1.95e1 );

  FRENSIE_CHECK_EQUAL( cross_section, 2.744259e-5 );

  cross_section = h1_nuclide->getAbsorptionCrossSection( 1.975e1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 2.7333065e-5, 1e-15 );

  cross_section = h1_nuclide->getAbsorptionCrossSection( 2.0e1 );

  FRENSIE_CHECK_EQUAL( cross_section, 2.722354e-5 );
}

//---------------------------------------------------------------------------//
// Check that the survival probability can be returned
FRENSIE_UNIT_TEST( Nuclide_hydrogen, getSurvivalProbability )
{
  double survival_prob = h1_nuclide->getSurvivalProbability( 1.0e-11 );

  FRENSIE_CHECK_FLOATING_EQUALITY( survival_prob, 0.98581342025975, 1e-13 );

  survival_prob = h1_nuclide->getSurvivalProbability( 1.03125e-11 );

  FRENSIE_CHECK_FLOATING_EQUALITY( survival_prob, 0.98581348192787, 1e-13 );

  survival_prob = h1_nuclide->getSurvivalProbability( 1.0625e-11 );

  FRENSIE_CHECK_FLOATING_EQUALITY( survival_prob, 0.98581352915209, 1e-13 );

  survival_prob = h1_nuclide->getSurvivalProbability( 1.90e1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( survival_prob, 0.99994563556224, 1e-13 );

  survival_prob = h1_nuclide->getSurvivalProbability( 1.95e1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( survival_prob, 0.99994461529907, 1e-13  );

  survival_prob = h1_nuclide->getSurvivalProbability( 2.0e1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( survival_prob, 0.99994361011057, 1e-13 );
}

//---------------------------------------------------------------------------//
// Check that a reaction cross section can be returned
FRENSIE_UNIT_TEST( Nuclide_hydrogen, getReactionCrossSection )
{
  double cross_section =
    h1_nuclide->getReactionCrossSection( 1.0e-11, MonteCarlo::N__TOTAL_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 1.17724711e3 );

  cross_section =
    h1_nuclide->getReactionCrossSection( 2.0e1, MonteCarlo::N__TOTAL_REACTION );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 4.82773424e-1, 1e-9 );

  cross_section =
    h1_nuclide->getReactionCrossSection( 1.0e-11, MonteCarlo::N__N_ELASTIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 1.160546e3 );

  cross_section =
    h1_nuclide->getReactionCrossSection( 2.0e1, MonteCarlo::N__N_ELASTIC_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 4.827462e-1 );

  cross_section =
    h1_nuclide->getReactionCrossSection( 1.0e-11, MonteCarlo::N__GAMMA_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 1.670111e1 );

  cross_section =
    h1_nuclide->getReactionCrossSection( 2.0e1, MonteCarlo::N__GAMMA_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 2.722354e-5 );

  cross_section =
    h1_nuclide->getReactionCrossSection( 1.0e-11, MonteCarlo::N__TOTAL_D_PRODUCTION );

  FRENSIE_CHECK_EQUAL( cross_section, 1.670111e1 );

  cross_section =
    h1_nuclide->getReactionCrossSection( 2.0e1, MonteCarlo::N__TOTAL_D_PRODUCTION );

  FRENSIE_CHECK_EQUAL( cross_section, 2.722354e-5 );

  cross_section =
    h1_nuclide->getReactionCrossSection( 1.0e-11, MonteCarlo::N__DPA );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );

  cross_section =
    h1_nuclide->getReactionCrossSection( 2.0e1, MonteCarlo::N__DPA );

  FRENSIE_CHECK_EQUAL( cross_section, 3.067696e-4 );

  cross_section =
    h1_nuclide->getReactionCrossSection( 1.0e-11, MonteCarlo::N__FISSION_REACTION );

  FRENSIE_CHECK_EQUAL( cross_section, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the a neutron can collide with a nuclide
FRENSIE_UNIT_TEST( Nuclide_hydrogen, collideAnalogue )
{
  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setDirection( 0.0, 0.0, 1.0 );
  neutron.setEnergy( 1.0 );
  neutron.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  h1_nuclide->collideAnalogue( neutron, bank );

  FRENSIE_CHECK_EQUAL( neutron.getWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );

  std::cout << neutron << std::endl;
}

//---------------------------------------------------------------------------//
// Check that a neutron can collide with a nuclide
FRENSIE_UNIT_TEST( Nuclide_hydrogen, collideSurvivalBias)
{
  MonteCarlo::NeutronState neutron( 0ull );
  neutron.setDirection( 0.0, 0.0, 1.0 );
  neutron.setEnergy( 1.03125e-11 );
  neutron.setWeight( 1.0 );

  MonteCarlo::ParticleBank bank;

  h1_nuclide->collideSurvivalBias( neutron, bank );

  FRENSIE_CHECK_FLOATING_EQUALITY( neutron.getWeight(), 0.98581348192787, 1e-14 );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );

  std::cout << neutron << std::endl;
}

//---------------------------------------------------------------------------//
// Check that a neutron can collide with a nuclide
// FRENSIE_UNIT_TEST( Nuclide_oxygen, collideSurvivalBias)
// {
  // double energy;
  // for( unsigned i = 0; i < 1e6; ++i )
  // {
  //   energy = exp(log(1.01e-11) + ((log(7.0)-log(1.01e-11))/1e6)*i);
  //   std::cout << energy << " " << o16_nuclide->getTotalCrossSection( energy )
  //   	      << " " << o16_nuclide->getAbsorptionCrossSection( energy )
  //   	      << " " << o16_nuclide->getReactionCrossSection( energy, MonteCarlo::N__ALPHA_REACTION )
  //   	      << " " << o16_nuclide->getReactionCrossSection( energy, MonteCarlo::N__N_ELASTIC_REACTION )
  //   	      << " " << o16_nuclide->getReactionCrossSection( energy, MonteCarlo::N__N_EXCITED_STATE_1_REACTION )
  //   	      << " " << o16_nuclide->getReactionCrossSection( energy, MonteCarlo::N__N_EXCITED_STATE_2_REACTION )
  //   	      << std::endl;
  // }

  // double sampling_prob =
  //   o16_nuclide->getReactionCrossSection( 7.0, MonteCarlo::N__N_EXCITED_STATE_2_REACTION )/
  //   o16_nuclide->getTotalCrossSection( 7.0 );

  // std::cout << sampling_prob << std::endl;

  // Teuchos::RCP<MonteCarlo::NeutronState> neutron( new MonteCarlo::NeutronState( 0ull ) );
  // neutron->setEnergy( 7.0 );
  // neutron->setDirection( 0.0, 0.0, 1.0 );

  // MonteCarlo::ParticleBank bank;

  // unsigned number_of_samples = 0u;
  // double ave_energy = 0.0;
  // for( unsigned i = 0; i < 1e6; ++i )
  // {
  //   o16_nuclide->collideAnalogue( *neutron, bank );

  //   if( neutron->getEnergy() > 0.24 && neutron->getEnergy() < 0.658 )
  //   {
  //     ++number_of_samples;
  //     ave_energy += neutron->getEnergy();
  //   }

  //   neutron->setEnergy( 7.0 );
  // }

  // std::cout << number_of_samples/1e6 << std::endl;
  // std::cout << ave_energy/number_of_samples << std::endl;
  // std::cout << o16_nuclide->getTotalCrossSection( 0.24 ) << std::endl;
  // std::cout << o16_nuclide->getTotalCrossSection( 0.450 ) << std::endl;
  // std::cout << o16_nuclide->getTotalCrossSection( 0.658 ) << std::endl;
// }

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_h1_ace_file_name, test_h1_ace_table_name;
std::string test_o16_ace_file_name, test_o16_ace_table_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_h1_ace_file",
                                         test_h1_ace_file_name, "",
                                         "Test h1 ACE file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_h1_ace_table",
                                        test_h1_ace_table_name, "",
                                        "Test ACE table name in h1 ACE file" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_o16_ace_file",
                                        test_o16_ace_file_name, "",
                                        "Test o16 ACE file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_o16_ace_table",
                                        test_o16_ace_table_name, "",
                                        "Test ACE table name in o16 ACE file" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Initialize H-1
  std::unique_ptr<Data::ACEFileHandler> ace_file_handler;
  ace_file_handler.reset( new Data::ACEFileHandler( test_h1_ace_file_name,
                                                    test_h1_ace_table_name,
                                                    1u ) );

  std::unique_ptr<Data::XSSNeutronDataExtractor> xss_data_extractor(
   new Data::XSSNeutronDataExtractor( ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray()));

  std::shared_ptr<const std::vector<double> > energy_grid(
          new std::vector<double>( xss_data_extractor->extractEnergyGrid() ) );

  std::shared_ptr<const Utility::HashBasedGridSearcher<double> > energy_grid_searcher(
       new Utility::StandardHashBasedGridSearcher<std::vector<double>, false>(
                                                  energy_grid,
                                                  energy_grid->size()/100+1) );

  MonteCarlo::SimulationProperties properties;

  std::unique_ptr<MonteCarlo::NeutronNuclearReactionACEFactory> reaction_factory(
                          new MonteCarlo::NeutronNuclearReactionACEFactory(
			       test_h1_ace_table_name,
                               ace_file_handler->getTableAtomicWeightRatio(),
			       ace_file_handler->getTableTemperature().value(),
                               energy_grid,
                               energy_grid_searcher,
                               properties,
                               *xss_data_extractor ) );

  MonteCarlo::Nuclide::ConstReactionMap standard_scattering_reactions;
  reaction_factory->createScatteringReactions( standard_scattering_reactions );
  reaction_factory->createFissionReactions( standard_scattering_reactions );

  MonteCarlo::Nuclide::ConstReactionMap standard_absorption_reactions;
  reaction_factory->createAbsorptionReactions( standard_absorption_reactions );

  h1_nuclide.reset( new MonteCarlo::Nuclide(
			       test_h1_ace_table_name,
                               1u,
                               1u,
                               0u,
                               ace_file_handler->getTableAtomicWeightRatio(),
			       ace_file_handler->getTableTemperature().value(),
                               energy_grid,
                               energy_grid_searcher,
                               standard_scattering_reactions,
                               standard_absorption_reactions ) );

  // Initialize O-16
  ace_file_handler.reset(new Data::ACEFileHandler( test_o16_ace_file_name,
						   test_o16_ace_table_name,
						   1u ) );

  xss_data_extractor.reset(
   new Data::XSSNeutronDataExtractor( ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray()));

  energy_grid.reset(
          new std::vector<double>( xss_data_extractor->extractEnergyGrid() ) );

  energy_grid_searcher.reset(
       new Utility::StandardHashBasedGridSearcher<std::vector<double>, false>(
                                                  energy_grid,
                                                  energy_grid->size()/100+1) );

  reaction_factory.reset(
                          new MonteCarlo::NeutronNuclearReactionACEFactory(
			       test_h1_ace_table_name,
                               ace_file_handler->getTableAtomicWeightRatio(),
			       ace_file_handler->getTableTemperature().value(),
                               energy_grid,
                               energy_grid_searcher,
                               properties,
                               *xss_data_extractor ) );

  standard_scattering_reactions.clear();
  reaction_factory->createScatteringReactions( standard_scattering_reactions );
  reaction_factory->createFissionReactions( standard_scattering_reactions );

  standard_absorption_reactions.clear();
  reaction_factory->createAbsorptionReactions( standard_absorption_reactions );

  o16_nuclide.reset( new MonteCarlo::Nuclide(
			       test_o16_ace_table_name,
                               1u,
                               1u,
                               0u,
                               ace_file_handler->getTableAtomicWeightRatio(),
			       ace_file_handler->getTableTemperature().value(),
                               energy_grid,
                               energy_grid_searcher,
                               standard_scattering_reactions,
                               standard_absorption_reactions ) );
  
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstNuclide.cpp
//---------------------------------------------------------------------------//
