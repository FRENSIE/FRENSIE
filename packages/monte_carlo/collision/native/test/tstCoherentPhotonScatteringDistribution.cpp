//---------------------------------------------------------------------------//
//!
//! \file   tstCoherentPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  Coherent photon scattering distribution unit tests
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
#include "MonteCarlo_CoherentPhotonScatteringDistribution.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSPhotoatomicDataExtractor.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_DirectionHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Variable
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::PhotonScatteringDistribution>
  coherent_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a photon can be scattered coherently
TEUCHOS_UNIT_TEST( CoherentPhotonScatteringDistribution, scatterPhoton )
{
  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 4.95936772145E-03 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  
  MonteCarlo::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 1.00475965594E-03; // sample form factor function squared (y = 1E6 cm)
  fake_stream[1] = 9.98800000000E-01; // reject the cosine scattering angle form function rejection loop
  fake_stream[2] = 6.50327467413E-01; // sample form factor function squared (y = 3E7 cm)
  fake_stream[3] = 5.07800000000E-01; // accept the cosine scattering angle form function rejection loop


  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  coherent_distribution->scatterPhoton( photon,
					bank,
					shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_FLOATING_EQUALITY( photon.getEnergy(), 4.95936772145E-03, 1e-15  );
// \todo Check why z direction test fails if rel err is above 1e-11
  TEST_FLOATING_EQUALITY( photon.getZDirection(), -1.25000000000E-01, 1e-11 );
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::UNKNOWN_SUBSHELL );
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
  
  // Create the form factor argument squared
  Teuchos::Array<double> form_factor_argument_squared( 55 ); // (1/cm^2)
  form_factor_argument_squared[0] = (0.0*1e8)*(0.0*1e8);
  form_factor_argument_squared[1] = (0.01*1e8)*(0.01*1e8);
  form_factor_argument_squared[2] = (0.02*1e8)*(0.02*1e8);
  form_factor_argument_squared[3] = (0.03*1e8)*(0.03*1e8);
  form_factor_argument_squared[4] = (0.04*1e8)*(0.04*1e8);
  form_factor_argument_squared[5] = (0.05*1e8)*(0.05*1e8);
  form_factor_argument_squared[6] = (0.06*1e8)*(0.06*1e8);
  form_factor_argument_squared[7] = (0.08*1e8)*(0.08*1e8);
  form_factor_argument_squared[8] = (0.10*1e8)*(0.10*1e8);
  form_factor_argument_squared[9] = (0.12*1e8)*(0.12*1e8);
  form_factor_argument_squared[10] = (0.15*1e8)*(0.15*1e8);
  form_factor_argument_squared[11] = (0.18*1e8)*(0.18*1e8);
  form_factor_argument_squared[12] = (0.20*1e8)*(0.20*1e8);
  form_factor_argument_squared[13] = (0.25*1e8)*(0.25*1e8);
  form_factor_argument_squared[14] = (0.30*1e8)*(0.30*1e8);
  form_factor_argument_squared[15] = (0.35*1e8)*(0.35*1e8);
  form_factor_argument_squared[16] = (0.40*1e8)*(0.40*1e8);
  form_factor_argument_squared[17] = (0.45*1e8)*(0.45*1e8);
  form_factor_argument_squared[18] = (0.50*1e8)*(0.50*1e8);
  form_factor_argument_squared[19] = (0.55*1e8)*(0.55*1e8);
  form_factor_argument_squared[20] = (0.60*1e8)*(0.60*1e8);
  form_factor_argument_squared[21] = (0.70*1e8)*(0.70*1e8);
  form_factor_argument_squared[22] = (0.80*1e8)*(0.80*1e8);
  form_factor_argument_squared[23] = (0.90*1e8)*(0.90*1e8);
  form_factor_argument_squared[24] = (1.0*1e8)*(1.0*1e8);
  form_factor_argument_squared[25] = (1.1*1e8)*(1.1*1e8);
  form_factor_argument_squared[26] = (1.2*1e8)*(1.2*1e8);
  form_factor_argument_squared[27] = (1.3*1e8)*(1.3*1e8);
  form_factor_argument_squared[28] = (1.4*1e8)*(1.4*1e8);
  form_factor_argument_squared[29] = (1.5*1e8)*(1.5*1e8);
  form_factor_argument_squared[30] = (1.6*1e8)*(1.6*1e8);
  form_factor_argument_squared[31] = (1.7*1e8)*(1.7*1e8);
  form_factor_argument_squared[32] = (1.8*1e8)*(1.8*1e8);
  form_factor_argument_squared[33] = (1.9*1e8)*(1.9*1e8);
  form_factor_argument_squared[34] = (2.0*1e8)*(2.0*1e8);
  form_factor_argument_squared[35] = (2.2*1e8)*(2.2*1e8);
  form_factor_argument_squared[36] = (2.4*1e8)*(2.4*1e8);
  form_factor_argument_squared[37] = (2.6*1e8)*(2.6*1e8);
  form_factor_argument_squared[38] = (2.8*1e8)*(2.8*1e8);
  form_factor_argument_squared[39] = (3.0*1e8)*(3.0*1e8);
  form_factor_argument_squared[40] = (3.2*1e8)*(3.2*1e8);
  form_factor_argument_squared[41] = (3.4*1e8)*(3.4*1e8);
  form_factor_argument_squared[42] = (3.6*1e8)*(3.6*1e8);
  form_factor_argument_squared[43] = (3.8*1e8)*(3.8*1e8);
  form_factor_argument_squared[44] = (4.0*1e8)*(4.0*1e8);
  form_factor_argument_squared[45] = (4.2*1e8)*(4.2*1e8);
  form_factor_argument_squared[46] = (4.4*1e8)*(4.4*1e8);
  form_factor_argument_squared[47] = (4.6*1e8)*(4.6*1e8);
  form_factor_argument_squared[48] = (4.8*1e8)*(4.8*1e8);
  form_factor_argument_squared[49] = (5.0*1e8)*(5.0*1e8);
  form_factor_argument_squared[50] = (5.2*1e8)*(5.2*1e8);
  form_factor_argument_squared[51] = (5.4*1e8)*(5.4*1e8);
  form_factor_argument_squared[52] = (5.6*1e8)*(5.6*1e8);
  form_factor_argument_squared[53] = (5.8*1e8)*(5.8*1e8);
  form_factor_argument_squared[54] = (6.0*1e8)*(6.0*1e8);
  
  // Extract the coherent scattering data block (jcoh)
  Teuchos::ArrayView<const double> jcoh_block(
				      xss_data_extractor->extractJCOHBlock() );

  // Extract the form factor function values and square them
  Teuchos::Array<double> form_factor_function_squared_values(jcoh_block(55,55));

  for( int i = 0; i < 55; i++)
   {
   form_factor_function_squared_values[i] *= 
   form_factor_function_squared_values[i];
   };

  Teuchos::RCP<Utility::OneDDistribution> form_factor_function_squared(
			    new Utility::TabularDistribution<Utility::LinLin>( 
						form_factor_argument_squared,
						form_factor_function_squared_values ) );

  // Create the scattering distribution
  coherent_distribution.reset( 
		new MonteCarlo::CoherentPhotonScatteringDistribution( 
						     form_factor_function_squared ) );


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
// end tstCoherentPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
