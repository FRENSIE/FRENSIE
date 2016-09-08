//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointPairProductionEnergyDistributionNormConstantEvaluator.cpp
//! \author Alex Robinson
//! \brief  Adjoint pair production energy distribution norm const evaluator
//!         unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "DataGen_AdjointPairProductionEnergyDistributionNormConstantEvaluator.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<DataGen::AdjointPairProductionEnergyDistributionNormConstantEvaluator> pp_edist_norm_pb_evaluator;

std::shared_ptr<DataGen::AdjointPairProductionEnergyDistributionNormConstantEvaluator> tp_edist_norm_pb_evaluator;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the energy distribution norm constant can be evaluated
TEUCHOS_UNIT_TEST(AdjointPairProductionEnergyDistributionNormConstantEvaluator,
                  evaluateEnergyDistributionNormConstant_pp )
{
  double norm_constant =
    pp_edist_norm_pb_evaluator->evaluateEnergyDistributionNormConstant(
               2*Utility::PhysicalConstants::electron_rest_mass_energy, 1e-3 );

  TEST_EQUALITY_CONST( norm_constant, 0.0 );

  norm_constant =
    pp_edist_norm_pb_evaluator->evaluateEnergyDistributionNormConstant(
                                                                   2.0, 1e-3 );

  TEST_FLOATING_EQUALITY( norm_constant, 0.717462372397138948, 1e-15 );

  norm_constant =
    pp_edist_norm_pb_evaluator->evaluateEnergyDistributionNormConstant(
                                                                  20.0, 1e-3 );

  TEST_FLOATING_EQUALITY( norm_constant, 225.830572420365428, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the energy distribution norm constant can be evaluated
TEUCHOS_UNIT_TEST(AdjointPairProductionEnergyDistributionNormConstantEvaluator,
                  evaluateEnergyDistributionNormConstant_tp )
{
  double norm_constant =
    tp_edist_norm_pb_evaluator->evaluateEnergyDistributionNormConstant(
               4*Utility::PhysicalConstants::electron_rest_mass_energy, 1e-3 );

  TEST_EQUALITY_CONST( norm_constant, 0.0 );

  norm_constant =
    tp_edist_norm_pb_evaluator->evaluateEnergyDistributionNormConstant(
                                                                   3.0, 1e-3 );

  TEST_FLOATING_EQUALITY( norm_constant, 0.000976815700301481319, 1e-15 );

  norm_constant =
    tp_edist_norm_pb_evaluator->evaluateEnergyDistributionNormConstant(
                                                                  20.0, 1e-3 );

  TEST_FLOATING_EQUALITY( norm_constant, 1.7787765108349336, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that an evaluation wrapper can be returned
TEUCHOS_UNIT_TEST(AdjointPairProductionEnergyDistributionNormConstantEvaluator,
                  getEnergyDistributionNormConstantEvaluationWrapper_pp )
{
  std::function<double(double)> evaluation_wrapper =
    pp_edist_norm_pb_evaluator->getEnergyDistributionNormConstantEvaluationWrapper( 1e-3 );

  double norm_constant = evaluation_wrapper( 
                     2*Utility::PhysicalConstants::electron_rest_mass_energy );

  TEST_EQUALITY_CONST( norm_constant, 0.0 );

  norm_constant = evaluation_wrapper( 2.0 );

  TEST_FLOATING_EQUALITY( norm_constant, 0.717462372397138948, 1e-15 );

  norm_constant = evaluation_wrapper( 20.0 );

  TEST_FLOATING_EQUALITY( norm_constant, 225.830572420365428, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that an evaluation wrapper can be returned
TEUCHOS_UNIT_TEST(AdjointPairProductionEnergyDistributionNormConstantEvaluator,
                  getEnergyDistributionNormConstantEvaluationWrapper_tp )
{
  std::function<double(double)> evaluation_wrapper =
    tp_edist_norm_pb_evaluator->getEnergyDistributionNormConstantEvaluationWrapper( 1e-3 );

  double norm_constant = evaluation_wrapper(
                     4*Utility::PhysicalConstants::electron_rest_mass_energy );

  TEST_EQUALITY_CONST( norm_constant, 0.0 );

  norm_constant = evaluation_wrapper( 3.0 );

  TEST_FLOATING_EQUALITY( norm_constant, 0.000976815700301481319, 1e-15 );

  norm_constant = evaluation_wrapper( 20.0 );

  TEST_FLOATING_EQUALITY( norm_constant, 1.7787765108349336, 1e-15 );
}

//---------------------------------------------------------------------------//
// Custom main function
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

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  {
    // Create the native data file container
    Data::ElectronPhotonRelaxationDataContainer 
      data_container( test_native_file_name );

    pp_edist_norm_pb_evaluator =
      DataGen::AdjointPairProductionEnergyDistributionNormConstantEvaluator::createEvaluator<Utility::LinLin,false>(
          data_container.getPhotonEnergyGrid(),
          data_container.getPairProductionCrossSection(),
          data_container.getPairProductionCrossSectionThresholdEnergyIndex() );

    tp_edist_norm_pb_evaluator =
      DataGen::AdjointPairProductionEnergyDistributionNormConstantEvaluator::createEvaluator<Utility::LinLin,false>(
       data_container.getPhotonEnergyGrid(),
       data_container.getTripletProductionCrossSection(),
       data_container.getTripletProductionCrossSectionThresholdEnergyIndex() );
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
// end tstAdjointPairProductionEnergyDistributionNormConstantEvaluator.cpp
//---------------------------------------------------------------------------//
