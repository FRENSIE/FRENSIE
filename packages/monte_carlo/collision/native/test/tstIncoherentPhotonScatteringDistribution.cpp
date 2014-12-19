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
#include "MonteCarlo_ComptonProfileSubshellConverterFactory.hpp"
#include "MonteCarlo_SubshellType.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
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
  
  MonteCarlo::SubshellType shell_of_interaction;

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
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::UNKNOWN_SUBSHELL );
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
  
  MonteCarlo::SubshellType shell_of_interaction;

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
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::K_SUBSHELL );
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

  for( unsigned i = 0; i < scatt_func_size; ++i )
    recoil_momentum[i] *= 1e8; // convert from inverse Anstrom to inverse cm
  
  Teuchos::RCP<Utility::OneDDistribution> scattering_function(
	  new Utility::TabularDistribution<Utility::LinLin>( 
			   recoil_momentum,
			   jince_block( scatt_func_size, scatt_func_size ) ) );

  // Create the subshell order array
  Teuchos::ArrayView<const double> subshell_endf_des = 
    xss_data_extractor->extractSubshellENDFDesignators();

  Teuchos::Array<MonteCarlo::SubshellType> subshell_order( 
						    subshell_endf_des.size() );

  for( unsigned i = 0; i < subshell_order.size(); ++i )
  {
    subshell_order[i] = MonteCarlo::convertENDFDesignatorToSubshellEnum( 
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
			  xss_data_extractor->extractSubshellBindingEnergies(),
			  xss_data_extractor->extractSubshellOccupancies(),
			  subshell_order,
			  converter,
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
