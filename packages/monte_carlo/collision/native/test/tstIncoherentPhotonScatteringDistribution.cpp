//---------------------------------------------------------------------------//
//!
//! \file   tstIncoherentPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  Incoherent photon scattering distribution unit tests
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
#include "MonteCarlo_IncoherentPhotonScatteringDistribution.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSPhotoatomicDataExtractor.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_DirectionHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::PhotonScatteringDistribution>
  basic_incoherent_distribution;

Teuchos::RCP<MonteCarlo::PhotonScatteringDistribution>
  detailed_incoherent_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a photon can be scattered incoherently without doppler broadening
TEUCHOS_UNIT_TEST( IncoherentPhotonScatteringDistribution,
		   scatterPhoton_no_doppler )
{
  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  
  unsigned shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 3 );
  fake_stream[0] = 0.001; // sample from first term of koblinger's method
  fake_stream[1] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[2] = 0.5; // accept x in scattering function rejection loop
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  basic_incoherent_distribution->scatterPhoton( photon,
						bank,
						shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );
  TEST_EQUALITY_CONST( shell_of_interaction, 
		       std::numeric_limits<unsigned>::max() );
}

//---------------------------------------------------------------------------//
// Check that a photon can be scattered incoherently with doppler broadening
TEUCHOS_UNIT_TEST( IncoherentPhotonScatteringDistribution,
		   scatterPhoton_doppler )
{
  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  
  unsigned shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.001; // sample from first term of koblinger's method
  fake_stream[1] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[2] = 0.5; // accept x in scattering function rejection loop
  fake_stream[3] = 0.005; // select first shell for collision
  fake_stream[4] = 6.427713151861e-01; // select pz = 40.0
  fake_stream[5] = 0.25; // select energy loss
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  detailed_incoherent_distribution->scatterPhoton( photon,
						   bank,
						   shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.3528040136905526, 1e-12 );
  TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );
  TEST_EQUALITY_CONST( shell_of_interaction, 0u );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_ace_file_name, test_ace_table_name;
  int atomic_number;
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();
  
  clp.setOption( "test_ace_file",
		 &test_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_ace_table",
		 &test_ace_table_name,
		 "Test ACE table name" );
  clp.setOption( "atomic_number",
		 &atomic_number,
		 "Atomic number" );

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
  Teuchos::RCP<Data::XSSPhotoatomicDataExtractor> xss_data_extractor(
                            new Data::XSSPhotoatomicDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );
  
  // Create the scattering function
  Teuchos::Array<double> recoil_momentum( 22 ); // (1/cm)
  recoil_momentum[0] = 0.0*1e8;
  recoil_momentum[1] = 0.005*1e8;
  recoil_momentum[2] = 0.01*1e8;
  recoil_momentum[3] = 0.05*1e8;
  recoil_momentum[4] = 0.1*1e8;
  recoil_momentum[5] = 0.15*1e8;
  recoil_momentum[6] = 0.20*1e8;
  recoil_momentum[7] = 0.3*1e8;
  recoil_momentum[8] = 0.4*1e8;
  recoil_momentum[9] = 0.5*1e8;
  recoil_momentum[10] = 0.6*1e8;
  recoil_momentum[11] = 0.7*1e8;
  recoil_momentum[12] = 0.8*1e8;
  recoil_momentum[13] = 0.9*1e8;
  recoil_momentum[14] = 1.0*1e8;
  recoil_momentum[15] = 1.5*1e8;
  recoil_momentum[16] = 2.0*1e8;
  recoil_momentum[17] = 3.0*1e8;
  recoil_momentum[18] = 4.0*1e8;
  recoil_momentum[19] = 5.0*1e8;
  recoil_momentum[20] = 8.0*1e8;
  recoil_momentum[21] = std::numeric_limits<double>::max();
  
  Teuchos::Array<double> scattering_function_values(
				      xss_data_extractor->extractJINCBlock() );
  scattering_function_values.push_back( (double)atomic_number );

  Teuchos::RCP<Utility::OneDDistribution> scattering_function(
			    new Utility::TabularDistribution<Utility::LinLin>( 
						recoil_momentum,
						scattering_function_values ) );

  // Create the shell interaction data
  Teuchos::RCP<Utility::OneDDistribution> shell_interaction_data(
			      new Utility::DiscreteDistribution( 
				   xss_data_extractor->extractLBEPSBlock(),
				   xss_data_extractor->extractLPIPSBlock() ) );

  // Create the compton profile distributions
  Teuchos::ArrayView<const double> lswd_block = 
    xss_data_extractor->extractLSWDBlock();

  Teuchos::ArrayView<const double> swd_block = 
    xss_data_extractor->extractSWDBlock();

  Teuchos::Array<Teuchos::RCP<Utility::OneDDistribution> >
    compton_profiles( lswd_block.size() );
  
  for( unsigned shell = 0; shell < lswd_block.size(); ++shell )
  {
    unsigned shell_index = lswd_block[shell]; // ignore interp parameter

    unsigned num_mom_vals = swd_block[shell_index];

    compton_profiles[shell].reset( 
	  new Utility::TabularDistribution<Utility::LinLin>(
		 swd_block( shell_index + 1, num_mom_vals ),
		 swd_block( shell_index + 1 + num_mom_vals, num_mom_vals ) ) );
  }

  // Create the scattering distributions
  basic_incoherent_distribution.reset( 
		   new MonteCarlo::IncoherentPhotonScatteringDistribution( 
						       scattering_function ) );

  detailed_incoherent_distribution.reset( 
		      new MonteCarlo::IncoherentPhotonScatteringDistribution( 
							scattering_function,
							shell_interaction_data,
							compton_profiles ) );
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
// end tstIncoherentPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
