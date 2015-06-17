//---------------------------------------------------------------------------//
//!
//! \file   tstWHIncoherentAdjointPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  Waller-Hartree incoherent adjoint photon scatt. dist. unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
  
// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_WHIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_UnitConversionPolicy.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::AdjointPhotonScatteringDistribution> 
  distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( WHIncoherentAdjointPhotonScatteringDistribution,
		   evaluate )
{

}

//---------------------------------------------------------------------------//
// Check that the distribution pdf can be evaluated
TEUCHOS_UNIT_TEST( WHIncoherentAdjointPhotonScatteringDistribution,
		   evaluatePDF )
{

}

//---------------------------------------------------------------------------//
// Check that the integrated cross section can be evaluated
TEUCHOS_UNIT_TEST( WHIncoherentAdjointPhotonScatteringDistribution,
		   evaluateIntegratedCrossSection )
{

}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from
TEUCHOS_UNIT_TEST( WHIncoherentAdjointPhotonScatteringDistribution,
		   sample )
{

}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from and trials can be recorded
TEUCHOS_UNIT_TEST( WHIncoherentAdjointPhotonScatteringDistribution,
		   sampleAndRecordTrials )
{

}

//---------------------------------------------------------------------------//
// Check that an adjoint photon can be scattered
TEUCHOS_UNIT_TEST( WHIncoherentAdjointPhotonScatteringDistribution,
		   scatterAdjointPhoton )
{

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

  {
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

    Teuchos::RCP<Utility::OneDDistribution> scattering_function(
	  new Utility::TabularDistribution<Utility::LinLin>( 
							  recoil_momentum,
			                                  scat_func_values ) );
  
  
    // Create the scattering distribution
    Teuchos::ArrayRCP<double> critical_line_energies( 3 );
    
    critical_line_energies[0] = 0.08;
    critical_line_energies[1] = 
      Utility::PhysicalConstants::electron_rest_mass_energy;
    critical_line_energies[2] = 1.0;
    
    // Create the scattering distribution
    distribution.reset( new MonteCarlo::WHIncoherentAdjointPhotonScatteringDistribution<Utility::InverseAngstromConversionPolicy>( 
						       20.0,
						       critical_line_energies,
						       scattering_function ) );
  }

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
// end tstWHIncoherentAdjointPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
