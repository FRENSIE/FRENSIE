//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointKleinNishinaDistribution.cpp
//! \author Alex Robinson
//! \brief  Klein-Nishina distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_AdjointKleinNishinaDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the min energy loss ratio can be calculated
TEUCHOS_UNIT_TEST( AdjointKleinNishinaDistribution,
		   calculateMinEnergyLossRatio )
{
  double min_energy_loss_ratio = 
    Utility::AdjointKleinNishinaDistribution::calculateMinEnergyLossRatio(
									0.1,
									0.5 );

  TEST_FLOATING_EQUALITY( min_energy_loss_ratio, 0.8, 1e-15 );

  min_energy_loss_ratio = 
    Utility::AdjointKleinNishinaDistribution::calculateMinEnergyLossRatio(
									0.25,
									0.5 );

  TEST_FLOATING_EQUALITY( min_energy_loss_ratio, 0.5, 1e-15 );

  min_energy_loss_ratio = 
    Utility::AdjointKleinNishinaDistribution::calculateMinEnergyLossRatio(
									0.4,
									0.5 );

  TEST_FLOATING_EQUALITY( min_energy_loss_ratio, 0.8, 1e-15 );

  min_energy_loss_ratio = 
    Utility::AdjointKleinNishinaDistribution::calculateMinEnergyLossRatio(
									0.4,
									12.0 );

  TEST_FLOATING_EQUALITY( min_energy_loss_ratio, 0.2, 1e-15 );

  min_energy_loss_ratio = 
    Utility::AdjointKleinNishinaDistribution::calculateMinEnergyLossRatio(
									0.48,
									12.0 );

  TEST_FLOATING_EQUALITY( min_energy_loss_ratio, 0.04, 1e-15 );

  min_energy_loss_ratio = 
    Utility::AdjointKleinNishinaDistribution::calculateMinEnergyLossRatio(
									2.4,
									12.0 );

  TEST_FLOATING_EQUALITY( min_energy_loss_ratio, 0.2, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the integrated cross section can be evaluated
TEUCHOS_UNIT_TEST( AdjointKleinNishinaDistribution,
		   evaluateIntegratedCrossSection )
{
  Teuchos::RCP<Utility::AdjointKleinNishinaDistribution> 
    distribution( new Utility::AdjointKleinNishinaDistribution( 
		 Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		 Utility::PhysicalConstants::electron_rest_mass_energy/2.0 ) );

  double integrated_cs = distribution->evaluateIntegratedCrossSection();

  UTILITY_TEST_FLOATING_EQUALITY( integrated_cs, 6.7308800297602e-25, 1e-11 );

  distribution->setEnergy( 
		   Utility::PhysicalConstants::electron_rest_mass_energy/4.0 );

  integrated_cs = distribution->evaluateIntegratedCrossSection();

  UTILITY_TEST_FLOATING_EQUALITY( integrated_cs, 7.3324781943328e-25, 1e-12 );

  distribution->setEnergy( 
		   Utility::PhysicalConstants::electron_rest_mass_energy/2.5 );

  integrated_cs = distribution->evaluateIntegratedCrossSection();

  UTILITY_TEST_FLOATING_EQUALITY( integrated_cs, 1.9945540106184e-25, 1e-12 );

  distribution->setEnergy( 
		   Utility::PhysicalConstants::electron_rest_mass_energy/2.0 );

  integrated_cs = distribution->evaluateIntegratedCrossSection();

  UTILITY_TEST_FLOATING_EQUALITY( integrated_cs, 0.0, 1e-12 );

  // Use a max energy of 12*me
  distribution.reset( new Utility::AdjointKleinNishinaDistribution(
		 Utility::PhysicalConstants::electron_rest_mass_energy/2.5,
		 Utility::PhysicalConstants::electron_rest_mass_energy*12.0 ));
  
  integrated_cs = distribution->evaluateIntegratedCrossSection();

  UTILITY_TEST_FLOATING_EQUALITY( integrated_cs, 9.7049264053602e-25, 1e-12 );

  distribution->setEnergy(
		  Utility::PhysicalConstants::electron_rest_mass_energy*0.48 );

  integrated_cs = distribution->evaluateIntegratedCrossSection();

  UTILITY_TEST_FLOATING_EQUALITY( integrated_cs, 1.5997478442681e-24, 1e-12 );

  distribution->setEnergy(
		   Utility::PhysicalConstants::electron_rest_mass_energy*2.4 );

  integrated_cs = distribution->evaluateIntegratedCrossSection();

  UTILITY_TEST_FLOATING_EQUALITY( integrated_cs, 1.9254719348986e-25, 1e-12 );

  distribution->setEnergy(
		  Utility::PhysicalConstants::electron_rest_mass_energy*12.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( AdjointKleinNishinaDistribution, evaluate )
{
  Teuchos::RCP<Utility::AdjointKleinNishinaDistribution> 
    distribution( new Utility::AdjointKleinNishinaDistribution( 
		 Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		 Utility::PhysicalConstants::electron_rest_mass_energy/2.0 ) );

  Teuchos::RCP<Utility::OneDDistribution> distribution_base = distribution;

  double value = distribution_base->evaluate( 0.79 );

  TEST_EQUALITY_CONST( value, 0.0 );

  value = distribution_base->evaluate( 0.8 );

  UTILITY_TEST_FLOATING_EQUALITY( value, 5.1140776521553e-24, 1e-12 );

  value = distribution_base->evaluate( 1.0 );

  UTILITY_TEST_FLOATING_EQUALITY( value, 4.9893440508832e-24, 1e-12 );
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
  
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  
  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstAdjointKleinNishinaDistribution.cpp
//---------------------------------------------------------------------------//
