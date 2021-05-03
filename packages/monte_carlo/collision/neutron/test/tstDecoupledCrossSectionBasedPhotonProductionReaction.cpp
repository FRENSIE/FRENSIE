//---------------------------------------------------------------------------//
//!
//! \file   tstDecoupledCrossSectionBasedPhotonProductionReaction.cpp
//! \author Eli  Moll
//! \brief  Cross section based decoupled photon production reaction unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_DecoupledCrossSectionBasedPhotonProductionReaction.hpp"
#include "MonteCarlo_PhotonProductionNuclearScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "MonteCarlo_NeutronAbsorptionReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::DecoupledCrossSectionBasedPhotonProductionReaction> nuclear_reaction;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the base photon production ID can be returned
FRENSIE_UNIT_TEST( DecoupledCrossSectionBasedPhotonProductionReaction, getThresholdEnergy )
{
  FRENSIE_CHECK_EQUAL( nuclear_reaction->getThresholdEnergy(),
		       1.00000000000E+01 );
}

//---------------------------------------------------------------------------//
// Check that the base reaction type can be returned
FRENSIE_UNIT_TEST( DecoupledCrossSectionBasedPhotonProductionReaction, getCrossSection )
{
  double cross_section =
    nuclear_reaction->getCrossSection( 1.00000000000e+01 );

  FRENSIE_CHECK_EQUAL( cross_section, 1.00000000000E+00 );

  cross_section = nuclear_reaction->getCrossSection( 1.50000000000e+01 );

  FRENSIE_CHECK_EQUAL( cross_section, 1.50000000000E+00 );

  cross_section = nuclear_reaction->getCrossSection( 2.00000000000e+01 );

  FRENSIE_CHECK_EQUAL( cross_section, 2.00000000000E+00 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_basic_ace_file_name;
unsigned test_basic_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_basic_ace_file",
                                        test_basic_ace_file_name, "",
                                        "Test basic ACE file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_basic_ace_file_start_line",
                                        test_basic_ace_file_start_line, 1,
                                        "Test basic ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the ace file handler
  std::unique_ptr<Data::ACEFileHandler> ace_file_handler(
                  new Data::ACEFileHandler( test_basic_ace_file_name,
                                            "1001.70c",
					    test_basic_ace_file_start_line ) );

  // Create the XSS data extractor
  std::unique_ptr<Data::XSSNeutronDataExtractor> xss_data_extractor(
     new Data::XSSNeutronDataExtractor( ace_file_handler->getTableNXSArray(),
                                        ace_file_handler->getTableJXSArray(),
                                        ace_file_handler->getTableXSSArray()));

  // Create the photon production nuclear scattering distribution ACE factory
  MonteCarlo::PhotonProductionNuclearScatteringDistributionACEFactory
    photon_production_dist_factory( "1001.70c",
                                    ace_file_handler->getTableAtomicWeightRatio(),
                                    *xss_data_extractor );

  MonteCarlo::SimulationProperties properties;

  std::shared_ptr<const MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::PhotonState> >
    photon_production_distribution;

  // Create the photon production nuclear scattering distribution
  photon_production_dist_factory.createScatteringDistribution(
                                             102001u,
                                             properties,
					     photon_production_distribution );

  std::shared_ptr<const std::vector<double> > energy_grid(
          new std::vector<double>( xss_data_extractor->extractEnergyGrid() ) );

  std::shared_ptr<const std::vector<double> > total_cross_section(
          new std::vector<double>( xss_data_extractor->extractTotalCrossSection() ) );

  // Create the total reaction
  std::shared_ptr<MonteCarlo::NeutronNuclearReaction> total_reaction(
                        new MonteCarlo::NeutronAbsorptionReaction(
                           energy_grid,
                           total_cross_section,
                           0u,
                           MonteCarlo::N__TOTAL_REACTION,
                           0.0,
                           ace_file_handler->getTableTemperature().value() ) );


  // Construct the photon production energy grid and yield data
  std::vector<double> xs_energy_grid = { 1.00000000000E+01,
                                         2.00000000000E+01 };
  std::vector<double> xs_energy_values = { 1.00000000000E+00,
                                           2.00000000000E+00 };

  Utility::ArrayView<const double> energy_grid_av( xs_energy_grid );
  Utility::ArrayView<const double> xs_energy_values_av( xs_energy_values );

  std::shared_ptr<const std::vector<double> > energy_grid_rcp(
                                   new std::vector<double>( energy_grid_av ) );

  std::shared_ptr<const std::vector<double> > xs_energy_values_rcp(
                              new std::vector<double>( xs_energy_values_av ) );

  std::vector<std::shared_ptr<const Utility::UnivariateDistribution> > tmp_vec;

  // Create the nuclear reaction
  nuclear_reaction.reset( new MonteCarlo::DecoupledCrossSectionBasedPhotonProductionReaction(
			                         MonteCarlo::N__GAMMA_REACTION,
                               102001u,
			                         ace_file_handler->getTableTemperature().value(),
                               0u,
                               energy_grid_rcp,
                               xs_energy_values_rcp,
                               photon_production_distribution,
                               total_reaction,
                               tmp_vec) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDecoupledCrossSectionBasedPhotonProductionReaction.cpp
//---------------------------------------------------------------------------//
