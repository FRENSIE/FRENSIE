//---------------------------------------------------------------------------//
//!
//! \file   tstDecoupledYieldBasedPhotonProductionReaction.cpp
//! \author Eli  Moll
//! \brief  Yield Based Decoupled photon production reaction unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_DecoupledYieldBasedPhotonProductionReaction.hpp"
#include "MonteCarlo_PhotonProductionNuclearScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "MonteCarlo_NeutronAbsorptionReaction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables.
//---------------------------------------------------------------------------//

std::shared_ptr<const MonteCarlo::DecoupledYieldBasedPhotonProductionReaction> nuclear_reaction;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the base photon production ID can be returned
FRENSIE_UNIT_TEST( DecoupledYieldBasedPhotonProductionReaction, getThresholdEnergy )
{
  FRENSIE_CHECK_EQUAL( nuclear_reaction->getThresholdEnergy(),
		       1.00000000000E-11 );
}

//---------------------------------------------------------------------------//
// Check that the base reaction type can be returned
FRENSIE_UNIT_TEST( DecoupledYieldBasedPhotonProductionReaction, getCrossSection )
{
  double cross_section =
    nuclear_reaction->getCrossSection( 1.00000000000e-11 );

  FRENSIE_CHECK_EQUAL( cross_section, 2.0*1.17724711000E+03 );

  cross_section = nuclear_reaction->getCrossSection( 1.03125000000E-11 );

  FRENSIE_CHECK_EQUAL( cross_section, 2.0*1.15927812000E+03 );

  cross_section = nuclear_reaction->getCrossSection( 1.95e1 );

  FRENSIE_CHECK_EQUAL( cross_section, 2.0*4.95490443000E-01 );

  cross_section = nuclear_reaction->getCrossSection( 2.0e1 );

  FRENSIE_CHECK_EQUAL( cross_section, 2.0*4.82773424000E-01 );
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
  std::shared_ptr< MonteCarlo::NeutronNuclearReaction>
    total_reaction( new MonteCarlo::NeutronAbsorptionReaction(
                           energy_grid,
                           total_cross_section,
                           0u,
                           MonteCarlo::N__TOTAL_REACTION,
                           0.0,
                           ace_file_handler->getTableTemperature().value() ) );

 // Create the base reaction with fictitious cross section data (total)
  std::shared_ptr< MonteCarlo::NeutronNuclearReaction> base_reaction;
  base_reaction.reset( new MonteCarlo::NeutronAbsorptionReaction(
                           energy_grid,
                           total_cross_section,
                           0u,
                           MonteCarlo::N__GAMMA_REACTION,
                           0.0,
                           ace_file_handler->getTableTemperature().value() ) );
  
  // Construct the yield energy grid and yield data
  std::vector<double> yield_energy_grid = { 1.00000000000E-11,
                                            2.00000000000E+01 };
  std::vector<double> yield_energy_values = { 2.00000000000E+00,
                                              2.00000000000E+00 };

  Utility::ArrayView<const double> yield_energy_grid_av( yield_energy_grid );
  Utility::ArrayView<const double> yield_energy_values_av( yield_energy_values );

  std::vector<std::shared_ptr<const Utility::UnivariateDistribution> > d_total_mt_yield_array;

  std::shared_ptr<Utility::UnivariateDistribution> d_mtp_yield(
        new Utility::TabularDistribution<Utility::LinLin>(
                              yield_energy_grid,
                              yield_energy_values ) );

  d_total_mt_yield_array.push_back( d_mtp_yield );

  // Create the nuclear reaction
  nuclear_reaction.reset( new MonteCarlo::DecoupledYieldBasedPhotonProductionReaction(
			       MonteCarlo::N__GAMMA_REACTION,
                               102001u,
                               ace_file_handler->getTableTemperature().value(),
                               d_total_mt_yield_array,
                               d_mtp_yield,
                               base_reaction,
                               photon_production_distribution,
                               total_reaction ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDecoupledYieldBasedPhotonProductionReaction.cpp
//---------------------------------------------------------------------------//
