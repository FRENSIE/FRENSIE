//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointIncoherentCrossSection.cpp
//! \author Alex Robinson
//! \brief  Adjoint incoherent cross section evaluator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "DataGen_AdjointIncoherentCrossSectionEvaluator.cpp"
#include "Utility_UniformDistribution.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<DataGen::AdjointIncoherentCrossSectionEvaluator> 
  adjoint_free_cs;

Teuchos::RCP<DataGen::AdjointIncoherentCrossSectionEvaluator>
  adjoint_cs;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
TEUCHOS_UNIT_TEST( AdjointIncoherentCrossSectionEvaluator, 
		   getEnergyOfMaxCrossSection )
{
  double energy = 
    DataGen::AdjointIncoherentCrossSectionEvaluator::getEnergyOfMaxCrossSection( 
								       0.001 );

  TEST_FLOATING_EQUALITY( energy, 0.0009961013562397372, 1e-15 );

  energy = DataGen::AdjointIncoherentCrossSectionEvaluator::getEnergyOfMaxCrossSection( 
								        0.01 );

  TEST_FLOATING_EQUALITY( energy, 0.0096233513926591, 1e-15 );

  energy = DataGen::AdjointIncoherentCrossSectionEvaluator::getEnergyOfMaxCrossSection( 
									 0.1 );

  TEST_FLOATING_EQUALITY( energy, 0.0718705616632476, 1e-15 );

  energy = DataGen::AdjointIncoherentCrossSectionEvaluator::getEnergyOfMaxCrossSection( 
									 1.0 );

  TEST_FLOATING_EQUALITY( energy, 0.20350423413905203, 1e-15 );

  energy = DataGen::AdjointIncoherentCrossSectionEvaluator::getEnergyOfMaxCrossSection( 
									10.0 );

  TEST_FLOATING_EQUALITY( energy, 0.24913409257587504, 1e-15 );

  energy = DataGen::AdjointIncoherentCrossSectionEvaluator::getEnergyOfMaxCrossSection( 
								       100.0 );

  TEST_FLOATING_EQUALITY( energy, 0.25484831899871596, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the energy can be tested for the presence of a max cross section
// value
TEUCHOS_UNIT_TEST( AdjointIncoherentCrossSectionEvaluator,
		   doesEnergyCorrespondToAMaxCrossSectionValue )
{
  TEST_ASSERT( DataGen::AdjointIncoherentCrossSectionEvaluator::doesEnergyCorrespondToAMaxCrossSectionValue( 0.001 ) );

  TEST_ASSERT( DataGen::AdjointIncoherentCrossSectionEvaluator::doesEnergyCorrespondToAMaxCrossSectionValue( 0.255 ) );

  TEST_ASSERT( !DataGen::AdjointIncoherentCrossSectionEvaluator::doesEnergyCorrespondToAMaxCrossSectionValue( 0.255499455065 ) );

  TEST_ASSERT( !DataGen::AdjointIncoherentCrossSectionEvaluator::doesEnergyCorrespondToAMaxCrossSectionValue( 10.0 ) );
}

//---------------------------------------------------------------------------//
// Check that the max energy resulting in a max cross section value at an 
// energy can be returned
TEUCHOS_UNIT_TEST( AdjointIncoherentCrossSectionEvaluator,
		   getMaxEnergyResultingInMaxCrossSectionValueAtEnergy )
{
  double max_energy = DataGen::AdjointIncoherentCrossSectionEvaluator::getMaxEnergyResultingInMaxCrossSectionValueAtEnergy(
								       0.001 );

  TEST_FLOATING_EQUALITY( max_energy, 0.0010039292814978508, 1e-15 );

  max_energy = DataGen::AdjointIncoherentCrossSectionEvaluator::getMaxEnergyResultingInMaxCrossSectionValueAtEnergy(
									0.01 );

  TEST_FLOATING_EQUALITY( max_energy, 0.010407332879714635, 1e-15 );

  max_energy = DataGen::AdjointIncoherentCrossSectionEvaluator::getMaxEnergyResultingInMaxCrossSectionValueAtEnergy(
									 0.1 );

  TEST_FLOATING_EQUALITY( max_energy, 0.16430890703649043, 1e-15 );

  max_energy = DataGen::AdjointIncoherentCrossSectionEvaluator::getMaxEnergyResultingInMaxCrossSectionValueAtEnergy( 
							 0.25227662801581613 );

  TEST_FLOATING_EQUALITY( max_energy, 20.0, 1e-14 );

  max_energy = DataGen::AdjointIncoherentCrossSectionEvaluator::getMaxEnergyResultingInMaxCrossSectionValueAtEnergy(
								       0.255 );

  TEST_FLOATING_EQUALITY( max_energy, 130.44689223759954, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the free electron cross section can be evaluated
TEUCHOS_UNIT_TEST( AdjointIncoherentCrossSectionEvaluator, 
		   evaluateCrossSection_free )
{
  double cross_section = adjoint_free_cs->evaluateCrossSection( 0.001, 0.001 );
  
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = adjoint_free_cs->evaluateCrossSection( 0.001, 0.001002 );
  
  Teuchos::RCP<Utility::AdjointKleinNishinaDistribution> 
    distribution( new Utility::AdjointKleinNishinaDistribution( 0.001,
								0.001002 ) );
  
  TEST_FLOATING_EQUALITY( cross_section,
			  distribution->evaluateIntegratedCrossSection(),
			  1e-15 );

  cross_section = adjoint_free_cs->evaluateCrossSection( 
						       0.001, 
						       0.0010039292814978508 );
  
  distribution.reset( new Utility::AdjointKleinNishinaDistribution( 
						     0.001,
						     0.0010039292814978508 ) );

  TEST_FLOATING_EQUALITY( cross_section, 
			  distribution->evaluateIntegratedCrossSection(),
			  1e-15 );

  // Note: The cross section won't change once the peak has been reached for
  //       this energy
  cross_section = adjoint_free_cs->evaluateCrossSection( 0.001, 0.002 );
  
  TEST_FLOATING_EQUALITY( cross_section,
			  distribution->evaluateIntegratedCrossSection(),
			  1e-15 );

  cross_section = adjoint_free_cs->evaluateCrossSection( 0.001, 20.0 );
  
  TEST_FLOATING_EQUALITY( cross_section,
			  distribution->evaluateIntegratedCrossSection(),
			  1e-15 );

  // Set a new energy
  cross_section = adjoint_free_cs->evaluateCrossSection( 0.01, 0.01 );
  
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = adjoint_free_cs->evaluateCrossSection( 0.01, 0.0103 );

  distribution.reset( new Utility::AdjointKleinNishinaDistribution( 0.01,
						                    0.0103 ) );

  TEST_FLOATING_EQUALITY( cross_section,
			  distribution->evaluateIntegratedCrossSection(),
			  1e-15 );

  cross_section = adjoint_free_cs->evaluateCrossSection( 
							0.01, 
							0.010407332879714635 );

  distribution.reset( new Utility::AdjointKleinNishinaDistribution( 
						      0.01,
						      0.010407332879714635 ) );

  TEST_FLOATING_EQUALITY( cross_section,
			  distribution->evaluateIntegratedCrossSection(),
			  1e-15 );

  cross_section = adjoint_free_cs->evaluateCrossSection( 0.01, 20.0 );

  TEST_FLOATING_EQUALITY( cross_section,
			  distribution->evaluateIntegratedCrossSection(),
			  1e-15 );

  // Set a new energy
  cross_section = adjoint_free_cs->evaluateCrossSection( 0.25227662801581613,
							 0.25227662801581613 );
  
  TEST_EQUALITY_CONST( cross_section, 0.0 );
  
  cross_section = adjoint_free_cs->evaluateCrossSection( 0.25227662801581613,
							 10.0 );
  
  distribution.reset( new Utility::AdjointKleinNishinaDistribution( 
							   0.25227662801581613,
							   10.0 ) );

  TEST_FLOATING_EQUALITY( cross_section, 
			  distribution->evaluateIntegratedCrossSection(),
			  1e-15 );
  
  cross_section = adjoint_free_cs->evaluateCrossSection( 0.25227662801581613,
							 20.0 );
  
  distribution.reset( new Utility::AdjointKleinNishinaDistribution( 
							   0.25227662801581613,
							   20.0 ) );

  TEST_FLOATING_EQUALITY( cross_section, 
			  distribution->evaluateIntegratedCrossSection(),
			  1e-15 );

  cross_section = adjoint_free_cs->evaluateCrossSection( 0.25227662801581613,
							 100.0 );
  
  distribution.reset( new Utility::AdjointKleinNishinaDistribution( 
							   0.25227662801581613,
							   100.0 ) );

  TEST_FLOATING_EQUALITY( cross_section, 
			  distribution->evaluateIntegratedCrossSection(),
			  1e-15 );

  // Set a new energy
  cross_section = adjoint_free_cs->evaluateCrossSection( 10.0, 10.0 );
  
  TEST_EQUALITY_CONST( cross_section, 0.0 );

  cross_section = adjoint_free_cs->evaluateCrossSection( 10.0, 20.0 );
  
  distribution.reset( new Utility::AdjointKleinNishinaDistribution( 10.0,
								    20.0 ) );

  TEST_FLOATING_EQUALITY( cross_section, 
			  distribution->evaluateIntegratedCrossSection(),
			  1e-15 );

  cross_section = adjoint_free_cs->evaluateCrossSection( 10.0, 100.0 );
  
  distribution.reset( new Utility::AdjointKleinNishinaDistribution( 10.0,
								    100.0 ) );

  TEST_FLOATING_EQUALITY( cross_section, 
			  distribution->evaluateIntegratedCrossSection(),
			  1e-15 );

  cross_section = adjoint_free_cs->evaluateCrossSection( 10.0, 1000.0 );
  
  distribution.reset( new Utility::AdjointKleinNishinaDistribution( 10.0,
								    1000.0 ) );

  TEST_FLOATING_EQUALITY( cross_section, 
			  distribution->evaluateIntegratedCrossSection(),
			  1e-15 );
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

  // Initialize the free electron adjoint cross section
  adjoint_free_cs.reset(
		       new DataGen::AdjointIncoherentCrossSectionEvaluator() );

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
// end tstAdjointIncoherentCrossSectionEvaluator.cpp
//---------------------------------------------------------------------------//
