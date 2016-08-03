//---------------------------------------------------------------------------//
//!
//! \file   tstSubshellIncoherentAdjointPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The subshell incoherent adjoint photon scattering distribution
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
#include "MonteCarlo_SubshellIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_StandardOccupationNumber.hpp"
#include "Data_SubshellType.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_MeCMomentumUnit.hpp"
#include "Utility_InverseMeCMomentumUnit.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution>
  distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the subshell can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentAdjointPhotonScatteringDistribution,
                   getSubshell )
{
  TEST_EQUALITY_CONST( distribution->getSubshell(), Data::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that the subshell occupancy can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentAdjointPhotonScatteringDistribution,
                   getSubshellOccupancy )
{
  TEST_EQUALITY_CONST( distribution->getSubshellOccupancy(), 2 );
}

//---------------------------------------------------------------------------//
// Check that the subshell binding energy can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentAdjointPhotonScatteringDistribution,
                   getSubshellBindingEnergy )
{
  TEST_FLOATING_EQUALITY(
                    distribution->getSubshellBindingEnergy(), 0.08829, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( SubshellIncoherentAdjointPhotonScatteringDistribution,
                   evaluate )
{
  
}

//---------------------------------------------------------------------------//
// Custom main funciton
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_native_file_name;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_native_file",
		 &test_native_file_name,
		 "Test Native file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) 
  {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  {
    // Create the native data file container
    Data::ElectronPhotonRelaxationDataContainer 
      data_container( test_native_file_name );
    
    // Extract the occupation number for the first subshell    
    const std::vector<double>& occupation_number_grid_s1 = 
      data_container.getOccupationNumberMomentumGrid( 1 );
    
    const std::vector<double>& occupation_number_s1 = 
      data_container.getOccupationNumber( 1 );

    for( unsigned i = 0u; i < occupation_number_grid_s1.size(); ++i )
    {
      std::cout << occupation_number_grid_s1[i] << " "
                << occupation_number_s1[i] << std::endl;
    }
    
    // Create the occupation number distribution
    std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<Utility::Units::MeCMomentum,void> > raw_occupation_number(
              new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::MeCMomentum,void>(
                                                    occupation_number_grid_s1,
                                                    occupation_number_s1 ) );

    std::shared_ptr<MonteCarlo::OccupationNumber> occupation_number( new MonteCarlo::StandardOccupationNumber<Utility::Units::MeCMomentum>( raw_occupation_number ) );
   
    // Create the Subshell incoherent adjoint photon scattering distribution
    distribution.reset(
         new MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution(
                                20.0,
                                Data::convertENDFDesignatorToSubshellEnum( 1 ),
                                data_container.getSubshellOccupancy( 1 ),
                                data_container.getSubshellBindingEnergy( 1 ),
                                occupation_number ) );
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
// end tstSubshellIncoherentAdjointPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
