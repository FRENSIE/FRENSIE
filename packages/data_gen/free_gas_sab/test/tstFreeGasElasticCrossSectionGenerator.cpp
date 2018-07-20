//---------------------------------------------------------------------------//
//!
//! \file   tstFreeGasElasticCrossSectionGenerator.cpp
//! \author Eli Moll
//! \brief  Free gas elastic scattering generator tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>
#include <math.h>

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "DataGen_FreeGasElasticCrossSectionGenerator.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_KinematicHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<DataGen::FreeGasElasticCrossSectionGenerator> free_gas_generator;
std::vector<double> E = {1e-11,2e-11,5e-11,1e-10,2e-10,5e-10,1e-9,2e-9,5e-9,1e-8,2e-8,5e-8,1e-7,2e-7,5e-7,1e-6};//,2e-6,5e-6};
//std::vector<double> E = {2.5301e-9,2.5301e-8,2.5301e-7};

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the integrated value can be returned
TEUCHOS_UNIT_TEST( FreeGasElasticSAlphaBetaFunction,
		   getTotalCrossSection )
{
  std::cout << " " << std::endl;

  //free_gas_generator->calculateEnergyCrossSectionValue();
  
  
  boost::unordered_map< double, double > total_cross_section;
  free_gas_generator->getTotalCrossSection( total_cross_section );
  std::cout << " " << std::endl;
  for (int i = 0; i < total_cross_section.size(); ++i)
  {
    std::cout << E[i] << " " << total_cross_section[E[i]] << std::endl; 
  }
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  double kT = 2.53010e-8;
  double A = 0.99167;
  double beta_num = 1001;
  double alpha_num = 10001;
  double beta_max_multiplier = -5;
  double zero_tolerance = 1e-6;

  free_gas_generator.reset( new DataGen::FreeGasElasticCrossSectionGenerator(
                                  kT,
                                  E, 
                                  A,
                                  beta_num,
                                  alpha_num,
                                  beta_max_multiplier,
                                  zero_tolerance ) );

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
// end tstFreeGasElasticCrossSectionGenerator.cpp
//---------------------------------------------------------------------------//
