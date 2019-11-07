//---------------------------------------------------------------------------//
//!
//! \file   tstWHIncoherentPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  Waller-Hartree incoherent photon scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_DetailedWHIncoherentPhotonScatteringDistribution.hpp"
#include "Data_SubshellType.hpp"
#include "MonteCarlo_StandardScatteringFunction.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_InverseAngstromUnit.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::PhotonScatteringDistribution>
  distribution;

std::shared_ptr<Utility::UnivariateDistribution> incoherent_cs;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
bool notEqualZero( const double value )
{
  return value != 0.0;
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( WHIncoherentPhotonScatteringDistribution, evaluate )
{
  double dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 1.0 );

  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 7.575780417613796, 1e-12 );

  dist_value = distribution->evaluate( 1.0, 1.0 );

  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  dist_value = distribution->evaluate( 1.0, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 5.369480917669441, 1e-15 );

  dist_value = distribution->evaluate( 1.0, -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 4.3353499509629834, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( WHIncoherentPhotonScatteringDistribution, evaluatePDF )
{
  double pdf_value = distribution->evaluatePDF(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 1.0 );

  FRENSIE_CHECK_SMALL( pdf_value, 1e-15 );

  pdf_value = distribution->evaluatePDF(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.329438478611696395, 1e-15 );

  pdf_value = distribution->evaluatePDF( 1.0, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0, 1e-15 );

  pdf_value = distribution->evaluatePDF( 1.0, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.312736983381781464, 1e-15 );

  pdf_value = distribution->evaluatePDF( 1.0, -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.25250564930902053, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the integrated cross section can be evaluated
FRENSIE_UNIT_TEST( WHIncoherentPhotonScatteringDistribution,
		   evaluateIntegratedCrossSection )
{
  double cross_section =
    distribution->evaluateIntegratedCrossSection(0.001, 1e-4);

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
			  incoherent_cs->evaluate( 0.001 ),
			  2e-3 );

  cross_section =
    distribution->evaluateIntegratedCrossSection( 0.1, 1e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
			  incoherent_cs->evaluate( 0.1 ),
			  1e-3 );

  cross_section =
    distribution->evaluateIntegratedCrossSection(20.0, 1e-3);

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section,
			  incoherent_cs->evaluate( 20.0 ),
			  1e-3 );
}

//---------------------------------------------------------------------------//
// Check that an outgoing energy and direction can be sampled
FRENSIE_UNIT_TEST( WHIncoherentPhotonScatteringDistribution, sample )
{
  double outgoing_energy, scattering_angle_cosine;

  // Left branch of Kahn's method
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.27;
  fake_stream[1] = 0.25;
  fake_stream[2] = 0.90; // reject
  fake_stream[3] = 0.10;
  fake_stream[4] = 0.50;
  fake_stream[5] = 0.999;
  fake_stream[6] = 0.989; // accept based on scattering function

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->sample( Utility::PhysicalConstants::electron_rest_mass_energy,
			outgoing_energy,
			scattering_angle_cosine );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY(
		       outgoing_energy,
		       Utility::PhysicalConstants::electron_rest_mass_energy/2,
		       1e-15 );
  FRENSIE_CHECK_SMALL( scattering_angle_cosine, 1e-15 );

  // Koblinger's method
  fake_stream.resize( 6 );
  fake_stream[0] = 0.818; // third term
  fake_stream[1] = 0.6;
  fake_stream[2] = 0.99997; // reject based on scattering function
  fake_stream[3] = 0.120; // first term
  fake_stream[4] = 0.2;
  fake_stream[5] = 0.9; // accept based on scattering function

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->sample( 3.1,
			outgoing_energy,
			scattering_angle_cosine );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.9046816718380433, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.6, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that an outgoing energy and direction can be sampled
FRENSIE_UNIT_TEST( WHIncoherentPhotonScatteringDistribution,
		   sampleAndRecordTrials )
{
  double outgoing_energy, scattering_angle_cosine;
  MonteCarlo::IncoherentPhotonScatteringDistribution::Counter trials = 0;

  // Left branch of Kahn's method
  std::vector<double> fake_stream( 7 );
  fake_stream[0] = 0.27;
  fake_stream[1] = 0.25;
  fake_stream[2] = 0.90; // reject
  fake_stream[3] = 0.10;
  fake_stream[4] = 0.50;
  fake_stream[5] = 0.999;
  fake_stream[6] = 0.989; // accept based on scattering function

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->sampleAndRecordTrials(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 outgoing_energy,
			 scattering_angle_cosine,
			 trials );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY(
		       outgoing_energy,
		       Utility::PhysicalConstants::electron_rest_mass_energy/2,
		       1e-15 );
  FRENSIE_CHECK_SMALL( scattering_angle_cosine, 1e-15 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 0.5 );

  // Koblinger's method
  fake_stream.resize( 6 );
  fake_stream[0] = 0.818; // third term
  fake_stream[1] = 0.6;
  fake_stream[2] = 0.99997; // reject based on scattering function
  fake_stream[3] = 0.120; // first term
  fake_stream[4] = 0.2;
  fake_stream[5] = 0.9; // accept based on scattering function

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;

  distribution->sampleAndRecordTrials( 3.1,
				       outgoing_energy,
				       scattering_angle_cosine,
				       trials );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.9046816718380433, 1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.6, 1e-15 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 0.5 );
}

//---------------------------------------------------------------------------//
// Check that a photon can be scattered incoherently without Doppler broadening
FRENSIE_UNIT_TEST( WHIncoherentPhotonScatteringDistribution, scatterPhoton )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 0.001; // sample from first term of koblinger's method
  fake_stream[1] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[2] = 0.5; // accept x in scattering function rejection loop
  fake_stream[3] = 0.2; // select M3 subshell
  fake_stream[4] = 0.5; // azimuthal_angle = pi

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->scatterPhoton( photon,
			       bank,
			       shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(),
			  19.50173181484825,
			  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(),
			  0.9996898054103247,
			  1e-15 );
  FRENSIE_CHECK_SMALL( bank.top().getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getXDirection(),
                                   0.024905681252821114,
                                   1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-15 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXDirection(), -1.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::M3_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_ace_file_name;
unsigned test_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file",
                                        test_ace_file_name, "",
                                        "Test ACE file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file_start_line",
                                        test_ace_file_start_line, 1,
                                        "Test ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create a file handler and data extractor
  std::shared_ptr<Data::ACEFileHandler> ace_file_handler(
                        new Data::ACEFileHandler( test_ace_file_name,
                                                  "82000.12p",
						  test_ace_file_start_line ) );
  
  std::shared_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
                            new Data::XSSEPRDataExtractor(
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

  // Create the scattering function
  Utility::ArrayView<const double> jince_block =
    xss_data_extractor->extractJINCEBlock();

  unsigned scatt_func_size = jince_block.size()/2;

  std::vector<double> recoil_momentum( jince_block( 0, scatt_func_size ) );
  std::vector<double> scat_func_values( jince_block( scatt_func_size,
							scatt_func_size ) );

  std::shared_ptr<Utility::UnitAwareUnivariateDistribution<Utility::Units::InverseAngstrom,void> > raw_scattering_function(
    new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::InverseAngstrom,void>(
							  recoil_momentum,
			                                  scat_func_values ) );

  std::shared_ptr<MonteCarlo::ScatteringFunction> scattering_function(
      new MonteCarlo::StandardScatteringFunction<Utility::Units::InverseAngstrom>( raw_scattering_function ) );

  // Create the subshell order array
  Utility::ArrayView<const double> subshell_endf_designators =
    xss_data_extractor->extractSubshellENDFDesignators();

  std::vector<Data::SubshellType> subshell_order(
					    subshell_endf_designators.size() );

  for( unsigned i = 0; i < subshell_order.size(); ++i )
  {
    subshell_order[i] = Data::convertENDFDesignatorToSubshellEnum(
				      (unsigned)subshell_endf_designators[i] );
  }

  // Create the scattering distributions
  distribution.reset( new MonteCarlo::DetailedWHIncoherentPhotonScatteringDistribution(
			  scattering_function,
			  xss_data_extractor->extractSubshellOccupancies(),
			  subshell_order ) );

  // Extract the incoherent cross section
  {
    // Extract the incoherent cross section
    Utility::ArrayView<const double> raw_energy_grid =
      xss_data_extractor->extractPhotonEnergyGrid();

    Utility::ArrayView<const double> raw_incoherent_cross_section =
      xss_data_extractor->extractIncoherentCrossSection();

    Utility::ArrayView<const double>::iterator start =
      std::find_if( raw_incoherent_cross_section.begin(),
		    raw_incoherent_cross_section.end(),
		    notEqualZero );

    std::vector<double> incoherent_cross_section;
    incoherent_cross_section.assign( start,
				     raw_incoherent_cross_section.end() );

    unsigned start_index = std::distance( raw_incoherent_cross_section.begin(),
					  start );

    start = raw_energy_grid.begin();

    std::advance( start, start_index );

    std::vector<double> energy_grid;
    energy_grid.assign( start, raw_energy_grid.end() );

    // Extract the original energy and cross section values
    for( unsigned i = 0; i < energy_grid.size(); ++i )
    {
      energy_grid[i] = exp( energy_grid[i] );
      incoherent_cross_section[i] = exp( incoherent_cross_section[i] );
    }

    incoherent_cs.reset( new Utility::TabularDistribution<Utility::LogLog>(
						  energy_grid,
						  incoherent_cross_section ) );
  }

  // Clear setup data
  ace_file_handler.reset();
  xss_data_extractor.reset();

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstWHIncoherentPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
