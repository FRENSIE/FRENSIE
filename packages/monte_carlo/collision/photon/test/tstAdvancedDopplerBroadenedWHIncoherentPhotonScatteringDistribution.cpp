//---------------------------------------------------------------------------//
//!
//! \file tstAdvancedDopplerBroadenedWHIncoherentPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  Advanced Doppler broadened Waller-Hartree incoherent photon scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_AdvancedDopplerBroadenedWHIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_ComptonProfileHelpers.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverterFactory.hpp"
#include "Data_SubshellType.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::PhotonScatteringDistribution> distribution;

Teuchos::RCP<Utility::UnivariateDistribution> incoherent_cs;

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
TEUCHOS_UNIT_TEST( AdvancedDopplerBroadenedWHIncoherentPhotonScatteringDistribution,
		   evaluate )
{
  double dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 1.0 );

  TEST_FLOATING_EQUALITY( dist_value, 0.0, 1e-15 );

  dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 -1.0 );

  TEST_FLOATING_EQUALITY( dist_value, 7.575780417613796, 1e-12 );

  dist_value = distribution->evaluate( 1.0, 1.0 );

  TEST_FLOATING_EQUALITY( dist_value, 0.0, 1e-15 );

  dist_value = distribution->evaluate( 1.0, 0.0 );

  TEST_FLOATING_EQUALITY( dist_value, 5.369480917669441, 1e-15 );

  dist_value = distribution->evaluate( 1.0, -1.0 );

  TEST_FLOATING_EQUALITY( dist_value, 4.3353499509629834, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( AdvancedDopplerBroadenedWHIncoherentPhotonScatteringDistribution,
		   evaluatePDF )
{
  double pdf_value = distribution->evaluatePDF(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 1.0 );

  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-15 );

  pdf_value = distribution->evaluatePDF(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 -1.0 );

  TEST_FLOATING_EQUALITY( pdf_value, 0.329438478611696395, 1e-15 );

  pdf_value = distribution->evaluatePDF( 1.0, 1.0 );

  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-15 );

  pdf_value = distribution->evaluatePDF( 1.0, 0.0 );

  TEST_FLOATING_EQUALITY( pdf_value, 0.312736983381781464, 1e-15 );

  pdf_value = distribution->evaluatePDF( 1.0, -1.0 );

  TEST_FLOATING_EQUALITY( pdf_value, 0.25250564930902053, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the integrated cross section can be evaluated
TEUCHOS_UNIT_TEST( DopplerBroadenedWHIncoherentPhotonScatteringDistribution,
		   evaluateIntegratedCrossSection )
{
  double cross_section =
    distribution->evaluateIntegratedCrossSection(0.001, 1e-4);

  TEST_FLOATING_EQUALITY( cross_section,
			  incoherent_cs->evaluate( 0.001 ),
			  2e-3 );

  cross_section =
    distribution->evaluateIntegratedCrossSection( 0.1, 1e-3 );

  TEST_FLOATING_EQUALITY( cross_section,
			  incoherent_cs->evaluate( 0.1 ),
			  1e-3 );

  cross_section =
    distribution->evaluateIntegratedCrossSection(20.0, 1e-3);

  TEST_FLOATING_EQUALITY( cross_section,
			  incoherent_cs->evaluate( 20.0 ),
			  1e-3 );
}

//---------------------------------------------------------------------------//
// Check that an outgoing energy and direction can be sampled
TEUCHOS_UNIT_TEST( AdvancedDopplerBroadenedWHIncoherentPhotonScatteringDistribution,
		   sample )
{
  double outgoing_energy, scattering_angle_cosine;
  Data::SubshellType shell_of_interaction;

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
			scattering_angle_cosine,
			shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY(
		       outgoing_energy,
		       Utility::PhysicalConstants::electron_rest_mass_energy/2,
		       1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.0, 1e-15 );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::UNKNOWN_SUBSHELL );

  // Koblinger's method
  fake_stream.resize( 5 );
  fake_stream[0] = 0.818; // third term
  fake_stream[1] = 0.6;
  fake_stream[2] = 0.99997; // reject based on scattering function
  fake_stream[3] = 0.120; // first term
  fake_stream[4] = 0.2;
  fake_stream[5] = 1.0; // accept based on scattering function

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->sample( 3.1,
			outgoing_energy,
			scattering_angle_cosine,
			shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( outgoing_energy, 0.9046816718380433, 1e-12 );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.6, 1e-15 );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::UNKNOWN_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that an outgoing energy and direction can be sampled
TEUCHOS_UNIT_TEST( AdvancedDopplerBroadenedWHIncoherentPhotonScatteringDistribution,
		   sampleAndRecordTrials )
{
  double outgoing_energy, scattering_angle_cosine;
  Data::SubshellType shell_of_interaction;
  unsigned trials = 0;

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
			 shell_of_interaction,
			 trials );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY(
		       outgoing_energy,
		       Utility::PhysicalConstants::electron_rest_mass_energy/2,
		       1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.0, 1e-15 );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::UNKNOWN_SUBSHELL );
  TEST_EQUALITY_CONST( 1.0/trials, 0.5 );

  // Koblinger's method
  fake_stream.resize( 5 );
  fake_stream[0] = 0.818; // third term
  fake_stream[1] = 0.6;
  fake_stream[2] = 0.99997; // reject based on scattering function
  fake_stream[3] = 0.120; // first term
  fake_stream[4] = 0.2;
  fake_stream[5] = 1.0; // accept based on scattering function

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;

  distribution->sampleAndRecordTrials( 3.1,
				       outgoing_energy,
				       scattering_angle_cosine,
				       shell_of_interaction,
				       trials );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( outgoing_energy, 0.9046816718380433, 1e-12 );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.6, 1e-15 );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::UNKNOWN_SUBSHELL );
  TEST_EQUALITY_CONST( 1.0/trials, 0.5 );
}

//---------------------------------------------------------------------------//
// Check that a photon can be scattered incoherently with doppler broadening
TEUCHOS_UNIT_TEST( AdvancedDopplerBroadenedWHIncoherentPhotonScatteringDistribution,
		   scatterPhoton )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.001; // sample from first term of koblinger's method
  fake_stream[1] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[2] = 0.5; // accept x in scattering function rejection loop
  fake_stream[3] = 0.005; // select first shell for collision
  fake_stream[4] = 0.5; // select pz = 0.0
  fake_stream[5] = 0.0; // azimuthal_angle = pi

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->scatterPhoton( photon,
			       bank,
			       shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  TEST_FLOATING_EQUALITY( bank.top().getEnergy(),
  			  19.50173181484825,
  			  1e-15 );
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(),
  			  0.9996898054103247,
  			  1e-15 );
  TEST_FLOATING_EQUALITY( bank.top().getYDirection(),
  			  0.024905681252821114,
  			  1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getXDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getYDirection(), -1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getXDirection(), 0.0, 1e-15 );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_ace_file_name, test_ace_table_name;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_ace_file",
		 &test_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_ace_table",
		 &test_ace_table_name,
		 "Test ACE table name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return =
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Create a file handler and data extractor
  Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
				 new Data::ACEFileHandler( test_ace_file_name,
							   test_ace_table_name,
							   1u ) );
  Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
                            new Data::XSSEPRDataExtractor(
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

  // Create the scattering function
  Teuchos::ArrayView<const double> jince_block =
    xss_data_extractor->extractJINCEBlock();

  unsigned scatt_func_size = jince_block.size()/2;

  Teuchos::Array<double> recoil_momentum( jince_block( 0, scatt_func_size ) );
  Teuchos::Array<double> scat_func_values( jince_block( scatt_func_size,
							scatt_func_size ) );

  for( unsigned i = 0; i < scatt_func_size; ++i )
    recoil_momentum[i] *= 1e8; // convert from inverse Anstrom to inverse cm

  std::shared_ptr<Utility::UnivariateDistribution> scattering_function(
	  new Utility::TabularDistribution<Utility::LinLin>(
							  recoil_momentum,
			                                  scat_func_values ) );

  // Create the subshell order array
  Teuchos::ArrayView<const double> subshell_endf_des =
    xss_data_extractor->extractSubshellENDFDesignators();

  Teuchos::Array<Data::SubshellType> subshell_order(
						    subshell_endf_des.size() );

  for( unsigned i = 0; i < subshell_order.size(); ++i )
  {
    subshell_order[i] = Data::convertENDFDesignatorToSubshellEnum(
					      (unsigned)subshell_endf_des[i] );
  }

  // Create the Compton profile subshell converter
  Teuchos::RCP<MonteCarlo::ComptonProfileSubshellConverter> converter;

  MonteCarlo::ComptonProfileSubshellConverterFactory::createConverter(
				   converter,
			           xss_data_extractor->extractAtomicNumber() );

  // Create the compton profile distributions
  Teuchos::ArrayView<const double> lswd_block =
    xss_data_extractor->extractLSWDBlock();

  Teuchos::ArrayView<const double> swd_block =
    xss_data_extractor->extractSWDBlock();

  Teuchos::Array<Teuchos::RCP<const Utility::TabularUnivariateDistribution> >
    half_compton_profiles( lswd_block.size() ),
    full_compton_profiles( lswd_block.size() );

  for( unsigned shell = 0; shell < lswd_block.size(); ++shell )
  {
    unsigned shell_index = lswd_block[shell]; // ignore interp parameter

    unsigned num_mom_vals = swd_block[shell_index];

    Teuchos::Array<double> half_momentum_grid(
				  swd_block( shell_index + 1, num_mom_vals ) );

    Teuchos::Array<double> half_profile(
		   swd_block( shell_index + 1 + num_mom_vals, num_mom_vals ) );

    Teuchos::Array<double> full_momentum_grid, full_profile;

    MonteCarlo::createFullProfileFromHalfProfile( half_momentum_grid.begin(),
						  half_momentum_grid.end(),
						  half_profile.begin(),
						  half_profile.end(),
						  full_momentum_grid,
						  full_profile );

    MonteCarlo::convertMomentumGridToMeCUnits( full_momentum_grid.begin(),
					       full_momentum_grid.end() );

    MonteCarlo::convertProfileToInverseMeCUnits( full_profile.begin(),
						 full_profile.end() );

    full_compton_profiles[shell].reset(
	 new Utility::TabularDistribution<Utility::LogLin>( full_momentum_grid,
							    full_profile ) );

  }

  // Create the scattering distributions
  distribution.reset(
   new MonteCarlo::AdvancedDopplerBroadenedWHIncoherentPhotonScatteringDistribution(
			  scattering_function,
			  xss_data_extractor->extractSubshellBindingEnergies(),
			  xss_data_extractor->extractSubshellOccupancies(),
			  subshell_order,
			  converter,
			  full_compton_profiles ) );

  // Extract the incoherent cross section
  {
    // Extract the incoherent cross section
    Teuchos::ArrayView<const double> raw_energy_grid =
      xss_data_extractor->extractPhotonEnergyGrid();

    Teuchos::ArrayView<const double> raw_incoherent_cross_section =
      xss_data_extractor->extractIncoherentCrossSection();

    Teuchos::ArrayView<const double>::iterator start =
      std::find_if( raw_incoherent_cross_section.begin(),
		    raw_incoherent_cross_section.end(),
		    notEqualZero );

    Teuchos::Array<double> incoherent_cross_section;
    incoherent_cross_section.assign( start,
				     raw_incoherent_cross_section.end() );

    unsigned start_index = std::distance( raw_incoherent_cross_section.begin(),
					  start );

    start = raw_energy_grid.begin();

    std::advance( start, start_index );

    Teuchos::Array<double> energy_grid;
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

  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstAdvancedDopplerBroadenedWHIncoherentPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
