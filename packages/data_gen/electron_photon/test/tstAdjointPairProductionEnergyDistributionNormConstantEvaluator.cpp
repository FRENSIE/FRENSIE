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

// FRENSIE Includes
#include "DataGen_AdjointPairProductionEnergyDistributionNormConstantEvaluator.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<DataGen::AdjointPairProductionEnergyDistributionNormConstantEvaluator> pp_edist_norm_pb_evaluator;

std::shared_ptr<DataGen::AdjointPairProductionEnergyDistributionNormConstantEvaluator> tp_edist_norm_pb_evaluator;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the energy distribution norm constant can be evaluated
FRENSIE_UNIT_TEST(AdjointPairProductionEnergyDistributionNormConstantEvaluator,
                  evaluateEnergyDistributionNormConstant_pp )
{
  double norm_constant =
    pp_edist_norm_pb_evaluator->evaluateEnergyDistributionNormConstant(
               2*Utility::PhysicalConstants::electron_rest_mass_energy, 1e-3 );

  FRENSIE_CHECK_EQUAL( norm_constant, 0.0 );

  norm_constant =
    pp_edist_norm_pb_evaluator->evaluateEnergyDistributionNormConstant(
                                                                   2.0, 1e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( norm_constant, 7.174623720415926886e-01, 1e-15 );

  norm_constant =
    pp_edist_norm_pb_evaluator->evaluateEnergyDistributionNormConstant(
                                                                  20.0, 1e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( norm_constant, 225.830572420365428, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the energy distribution norm constant can be evaluated
FRENSIE_UNIT_TEST(AdjointPairProductionEnergyDistributionNormConstantEvaluator,
                  evaluateEnergyDistributionNormConstant_tp )
{
  double norm_constant =
    tp_edist_norm_pb_evaluator->evaluateEnergyDistributionNormConstant(
               4*Utility::PhysicalConstants::electron_rest_mass_energy, 1e-3 );

  FRENSIE_CHECK_EQUAL( norm_constant, 0.0 );

  norm_constant =
    tp_edist_norm_pb_evaluator->evaluateEnergyDistributionNormConstant(
                                                                   3.0, 1e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( norm_constant, 9.768023347495827929e-04, 1e-15 );

  norm_constant =
    tp_edist_norm_pb_evaluator->evaluateEnergyDistributionNormConstant(
                                                                  20.0, 1e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( norm_constant, 1.778776489388709248, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that an evaluation wrapper can be returned
FRENSIE_UNIT_TEST(AdjointPairProductionEnergyDistributionNormConstantEvaluator,
                  getEnergyDistributionNormConstantEvaluationWrapper_pp )
{
  std::function<double(double)> evaluation_wrapper =
    pp_edist_norm_pb_evaluator->getEnergyDistributionNormConstantEvaluationWrapper( 1e-3 );

  double norm_constant = evaluation_wrapper(
                     2*Utility::PhysicalConstants::electron_rest_mass_energy );

  FRENSIE_CHECK_EQUAL( norm_constant, 0.0 );

  norm_constant = evaluation_wrapper( 2.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( norm_constant, 7.174623720415926886e-01, 1e-15 );

  norm_constant = evaluation_wrapper( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( norm_constant, 225.830572420365428, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that an evaluation wrapper can be returned
FRENSIE_UNIT_TEST(AdjointPairProductionEnergyDistributionNormConstantEvaluator,
                  getEnergyDistributionNormConstantEvaluationWrapper_tp )
{
  std::function<double(double)> evaluation_wrapper =
    tp_edist_norm_pb_evaluator->getEnergyDistributionNormConstantEvaluationWrapper( 1e-3 );

  double norm_constant = evaluation_wrapper(
                     4*Utility::PhysicalConstants::electron_rest_mass_energy );

  FRENSIE_CHECK_EQUAL( norm_constant, 0.0 );

  norm_constant = evaluation_wrapper( 3.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( norm_constant, 9.768023347495827929e-04, 1e-15 );

  norm_constant = evaluation_wrapper( 20.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( norm_constant, 1.778776489388709248, 1e-15 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_file",
                                        test_native_file_name, "",
                                        "Test Native file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
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
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstAdjointPairProductionEnergyDistributionNormConstantEvaluator.cpp
//---------------------------------------------------------------------------//
