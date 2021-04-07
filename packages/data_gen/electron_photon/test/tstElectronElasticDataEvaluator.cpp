//---------------------------------------------------------------------------//
//!
//! \file   tstElectronElasticDataEvaluator.cpp
//! \author Luke Kersting
//! \brief  The electron elastic data evaluator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "DataGen_ElectronElasticDataEvaluator.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Data_ENDLDataContainer.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<Data::ENDLDataContainer> h_endl_data_container;
std::shared_ptr<Data::ElectronPhotonRelaxationDataContainer> h_native_data_container;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a data evaluator can be constructed
FRENSIE_UNIT_TEST( ElectronElasticDataEvaluator,
                   basic_constructor_endl )
{
  DataGen::ElectronElasticDataEvaluator
    evaluator( h_endl_data_container );

  FRENSIE_CHECK_EQUAL( evaluator.getMinEnergy(), 1e-5 );
  FRENSIE_CHECK_EQUAL( evaluator.getMaxEnergy(), 1e5 );
  FRENSIE_CHECK_EQUAL( evaluator.getCutoffAngleCosine(), 0.9 );
  FRENSIE_CHECK_EQUAL( evaluator.getNumberOfMomentPreservingAngles(), 2 );
  FRENSIE_CHECK_EQUAL( evaluator.getTabularEvaluationTolerance(), 1e-7 );
  FRENSIE_CHECK_EQUAL( evaluator.getElectronTwoDInterpPolicy(),
                       MonteCarlo::LOGLOGLOG_INTERPOLATION );
  FRENSIE_CHECK_EQUAL( evaluator.getElectronTwoDGridPolicy(),
                       MonteCarlo::UNIT_BASE_CORRELATED_GRID );
  FRENSIE_CHECK_EQUAL( evaluator.getCoupledElasticSamplingMethod(),
                       MonteCarlo::MODIFIED_TWO_D_UNION );
  FRENSIE_CHECK_EQUAL( evaluator.isGenerateNewDistributionAtMinAndMaxEnergyOn(),
                       false );
}

//---------------------------------------------------------------------------//
// Check that a data evaluator can be constructed
FRENSIE_UNIT_TEST( ElectronElasticDataEvaluator, constructor_endl )
{
  DataGen::ElectronElasticDataEvaluator
    evaluator( h_endl_data_container, 1e-3, 20.0, 1.0, 0u, 1e-6, MonteCarlo::CORRELATED_GRID, MonteCarlo::LINLINLOG_INTERPOLATION, MonteCarlo::TWO_D_UNION, true );

  FRENSIE_CHECK_EQUAL( evaluator.getMinEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( evaluator.getMaxEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( evaluator.getCutoffAngleCosine(), 1.0 );
  FRENSIE_CHECK_EQUAL( evaluator.getNumberOfMomentPreservingAngles(), 0u );
  FRENSIE_CHECK_EQUAL( evaluator.getTabularEvaluationTolerance(), 1e-6 );
  FRENSIE_CHECK_EQUAL( evaluator.getElectronTwoDInterpPolicy(),
                       MonteCarlo::LINLINLOG_INTERPOLATION );
  FRENSIE_CHECK_EQUAL( evaluator.getElectronTwoDGridPolicy(),
                       MonteCarlo::CORRELATED_GRID );
  FRENSIE_CHECK_EQUAL( evaluator.getCoupledElasticSamplingMethod(),
                       MonteCarlo::TWO_D_UNION );
  FRENSIE_CHECK_EQUAL( evaluator.isGenerateNewDistributionAtMinAndMaxEnergyOn(),
                       true );
}

//---------------------------------------------------------------------------//
// Check that a data evaluator can be constructed
FRENSIE_UNIT_TEST( ElectronElasticDataEvaluator, constructor_native )
{
  DataGen::ElectronElasticDataEvaluator
    evaluator( h_native_data_container, 1e-3, 20.0, 1.0, 0u, 1e-6, MonteCarlo::CORRELATED_GRID, MonteCarlo::LINLINLOG_INTERPOLATION, MonteCarlo::TWO_D_UNION, true );

  FRENSIE_CHECK_EQUAL( evaluator.getMinEnergy(), 1e-3 );
  FRENSIE_CHECK_EQUAL( evaluator.getMaxEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( evaluator.getCutoffAngleCosine(), 1.0 );
  FRENSIE_CHECK_EQUAL( evaluator.getNumberOfMomentPreservingAngles(), 0u );
  FRENSIE_CHECK_EQUAL( evaluator.getTabularEvaluationTolerance(), 1e-6 );
  FRENSIE_CHECK_EQUAL( evaluator.getElectronTwoDInterpPolicy(),
                       MonteCarlo::LINLINLOG_INTERPOLATION );
  FRENSIE_CHECK_EQUAL( evaluator.getElectronTwoDGridPolicy(),
                       MonteCarlo::CORRELATED_GRID );
  FRENSIE_CHECK_EQUAL( evaluator.getCoupledElasticSamplingMethod(),
                       MonteCarlo::TWO_D_UNION );
  FRENSIE_CHECK_EQUAL( evaluator.isGenerateNewDistributionAtMinAndMaxEnergyOn(),
                       true );
}

//---------------------------------------------------------------------------//
// Check that the cutoff angle cosine can be set
FRENSIE_UNIT_TEST( ElectronElasticDataEvaluator,
                   setCutoffAngleCosine )
{
  DataGen::ElectronElasticDataEvaluator evaluator( h_endl_data_container );

  evaluator.setCutoffAngleCosine( 0.89 );
  FRENSIE_CHECK_EQUAL( evaluator.getCutoffAngleCosine(), 0.89 );
}

//---------------------------------------------------------------------------//
// Check that the number of moment preserving angles can be set
FRENSIE_UNIT_TEST( ElectronElasticDataEvaluator,
                   setNumberOfMomentPreservingAngles )
{
  DataGen::ElectronElasticDataEvaluator evaluator( h_endl_data_container );

  evaluator.setNumberOfMomentPreservingAngles( 5 );
  FRENSIE_CHECK_EQUAL( evaluator.getNumberOfMomentPreservingAngles(), 5 );
}

//---------------------------------------------------------------------------//
// Check that the cutoff angle cosine can be set
FRENSIE_UNIT_TEST( ElectronElasticDataEvaluator,
                   setTabularEvaluationTolerance )
{
  DataGen::ElectronElasticDataEvaluator evaluator( h_endl_data_container );

  FRENSIE_CHECK_EQUAL( evaluator.getTabularEvaluationTolerance(), 1e-7 );
  evaluator.setTabularEvaluationTolerance( 1e-6 );
  FRENSIE_CHECK_EQUAL( evaluator.getTabularEvaluationTolerance(), 1e-6 );
}

//---------------------------------------------------------------------------//
// Check that the electron TwoDInterpPolicy can be set
FRENSIE_UNIT_TEST( ElectronElasticDataEvaluator,
                   setElectronTwoDInterpPolicy )
{
  DataGen::ElectronElasticDataEvaluator evaluator( h_endl_data_container );

  FRENSIE_CHECK_EQUAL( evaluator.getElectronTwoDInterpPolicy(),
                       MonteCarlo::LOGLOGLOG_INTERPOLATION );

  evaluator.setElectronTwoDInterpPolicy( MonteCarlo::LINLINLIN_INTERPOLATION );
  FRENSIE_CHECK_EQUAL( evaluator.getElectronTwoDInterpPolicy(),
                       MonteCarlo::LINLINLIN_INTERPOLATION );

  evaluator.setElectronTwoDInterpPolicy( MonteCarlo::LINLINLOG_INTERPOLATION );
  FRENSIE_CHECK_EQUAL( evaluator.getElectronTwoDInterpPolicy(),
                       MonteCarlo::LINLINLOG_INTERPOLATION );
}

//---------------------------------------------------------------------------//
// Check that the electron TwoDGridPolicy can be set
FRENSIE_UNIT_TEST( ElectronElasticDataEvaluator,
                   setElectronTwoDGridPolicy )
{
  DataGen::ElectronElasticDataEvaluator evaluator( h_endl_data_container );

  FRENSIE_CHECK_EQUAL( evaluator.getElectronTwoDGridPolicy(),
                       MonteCarlo::UNIT_BASE_CORRELATED_GRID );

  evaluator.setElectronTwoDGridPolicy( MonteCarlo::CORRELATED_GRID );
  FRENSIE_CHECK_EQUAL( evaluator.getElectronTwoDGridPolicy(),
                       MonteCarlo::CORRELATED_GRID );

  evaluator.setElectronTwoDGridPolicy( MonteCarlo::DIRECT_GRID );
  FRENSIE_CHECK_EQUAL( evaluator.getElectronTwoDGridPolicy(),
                       MonteCarlo::DIRECT_GRID );

  evaluator.setElectronTwoDGridPolicy( MonteCarlo::UNIT_BASE_GRID );
  FRENSIE_CHECK_EQUAL( evaluator.getElectronTwoDGridPolicy(),
                       MonteCarlo::UNIT_BASE_GRID );

  evaluator.setElectronTwoDGridPolicy( MonteCarlo::UNIT_BASE_CORRELATED_GRID );
  FRENSIE_CHECK_EQUAL( evaluator.getElectronTwoDGridPolicy(),
                       MonteCarlo::UNIT_BASE_CORRELATED_GRID );
}

//---------------------------------------------------------------------------//
// Check that the electron CoupledElasticSamplingMethod can be set
FRENSIE_UNIT_TEST( ElectronElasticDataEvaluator,
                   setCoupledElasticSamplingMethod )
{
  DataGen::ElectronElasticDataEvaluator evaluator( h_endl_data_container );

  FRENSIE_CHECK_EQUAL( evaluator.getCoupledElasticSamplingMethod(),
                       MonteCarlo::MODIFIED_TWO_D_UNION );

  evaluator.setCoupledElasticSamplingMethod( MonteCarlo::TWO_D_UNION );
  FRENSIE_CHECK_EQUAL( evaluator.getCoupledElasticSamplingMethod(),
                       MonteCarlo::TWO_D_UNION );

  evaluator.setCoupledElasticSamplingMethod( MonteCarlo::ONE_D_UNION );
  FRENSIE_CHECK_EQUAL( evaluator.getCoupledElasticSamplingMethod(),
                       MonteCarlo::ONE_D_UNION );
}

//---------------------------------------------------------------------------//
// Check that GenerateNewDistributionAtMaxEnergy can be set
FRENSIE_UNIT_TEST( ElectronElasticDataEvaluator,
                   setGenerateNewDistributionAtMinAndMaxEnergyOffOn )
{
  DataGen::ElectronElasticDataEvaluator evaluator( h_endl_data_container );

  FRENSIE_CHECK_EQUAL( evaluator.isGenerateNewDistributionAtMinAndMaxEnergyOn(),
                       false );

  evaluator.setGenerateNewDistributionAtMinAndMaxEnergyOn();
  FRENSIE_CHECK_EQUAL( evaluator.isGenerateNewDistributionAtMinAndMaxEnergyOn(),
                       true );

  evaluator.setGenerateNewDistributionAtMinAndMaxEnergyOff();
  FRENSIE_CHECK_EQUAL( evaluator.isGenerateNewDistributionAtMinAndMaxEnergyOn(),
                       false );
}

//---------------------------------------------------------------------------//
// Check that the cutoff cross section evaluator can be created
FRENSIE_UNIT_TEST( ElectronElasticDataEvaluator,
                   createCutoffCrossSectionEvaluator_endl )
{
  DataGen::ElectronElasticDataEvaluator evaluator( h_endl_data_container );

  std::shared_ptr<const Utility::UnivariateDistribution> cutoff_evaluator;

  evaluator.createCutoffCrossSectionEvaluator( cutoff_evaluator );

  FRENSIE_CHECK_EQUAL( cutoff_evaluator->evaluate(1e-5), 2.74896e+8 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cutoff_evaluator->evaluate(1e5), 1.31176e-5, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the cutoff cross section evaluator can be created
FRENSIE_UNIT_TEST( ElectronElasticDataEvaluator,
                   createCutoffCrossSectionEvaluator_native )
{
  DataGen::ElectronElasticDataEvaluator evaluator( h_native_data_container );;

  std::shared_ptr<MonteCarlo::ElectroatomicReaction> cutoff_evaluator;

  evaluator.createCutoffCrossSectionEvaluator( cutoff_evaluator );

  FRENSIE_CHECK_EQUAL( cutoff_evaluator->getCrossSection(1e-5), 2.74896e+8 );
  FRENSIE_CHECK_FLOATING_EQUALITY( cutoff_evaluator->getCrossSection(1e5), 1.31176e-5, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the total cross section evaluator can be created
FRENSIE_UNIT_TEST( ElectronElasticDataEvaluator,
                   createTotalCrossSectionEvaluator_endl )
{
  DataGen::ElectronElasticDataEvaluator evaluator( h_endl_data_container );

  std::shared_ptr<const Utility::UnivariateDistribution> total_evaluator;

  evaluator.createTotalCrossSectionEvaluator( total_evaluator );

  FRENSIE_CHECK_EQUAL( total_evaluator->evaluate(1e-5), 2.74896e+8 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_evaluator->evaluate(1e5), 1.29871e+04, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the total cross section evaluator can be created
FRENSIE_UNIT_TEST( ElectronElasticDataEvaluator,
                   createTotalCrossSectionEvaluator_native )
{
  DataGen::ElectronElasticDataEvaluator evaluator( h_native_data_container );

  std::shared_ptr<MonteCarlo::ElectroatomicReaction> total_evaluator;

  evaluator.createTotalCrossSectionEvaluator( total_evaluator );

  FRENSIE_CHECK_EQUAL( total_evaluator->getCrossSection(1e-5), 2.74896e+8 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_evaluator->getCrossSection(1e5), 1.29871e+04, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the total cross section evaluator can be created
FRENSIE_UNIT_TEST( ElectronElasticDataEvaluator,
                   evaluateScreenedRutherfordCrossSection_endl )
{
  DataGen::ElectronElasticDataEvaluator evaluator( h_endl_data_container );

  std::vector<double> cross_section;
  unsigned threshold;

  evaluator.evaluateScreenedRutherfordCrossSection(
      h_endl_data_container->getTotalElasticCrossSection(),
      h_endl_data_container->getCutoffElasticCrossSection(),
      cross_section,
      threshold );

  FRENSIE_CHECK_EQUAL( threshold, 45 );
  FRENSIE_CHECK_EQUAL( cross_section.front(), 1.779999999999927240e+01 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 1.298709998688240012e+04);
  FRENSIE_CHECK_EQUAL( cross_section.size(), 101-threshold );
}

//---------------------------------------------------------------------------//
// Check that the total cross section evaluator can be created
FRENSIE_UNIT_TEST( ElectronElasticDataEvaluator,
                   evaluateScreenedRutherfordCrossSection_native )
{
  DataGen::ElectronElasticDataEvaluator evaluator( h_native_data_container );

  std::vector<double> cross_section;
  unsigned threshold;

  evaluator.evaluateScreenedRutherfordCrossSection(
      h_native_data_container->getTotalElasticCrossSection(),
      h_native_data_container->getCutoffElasticCrossSection(),
      cross_section,
      threshold );

  std::vector<double> rutherford_cross_section = h_native_data_container->getScreenedRutherfordElasticCrossSection();

  FRENSIE_CHECK_EQUAL( threshold, h_native_data_container->getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex() );
  FRENSIE_CHECK_EQUAL( cross_section.front(), rutherford_cross_section.front() );
  FRENSIE_CHECK_EQUAL( cross_section.back(), rutherford_cross_section.back() );
  FRENSIE_CHECK_EQUAL( cross_section.size(), rutherford_cross_section.size() );
}

//---------------------------------------------------------------------------//
// Check that the elastic secondary distribution can be evaluated
FRENSIE_UNIT_TEST( ElectronElasticDataEvaluator,
                   evaluateElasticSecondaryDistribution_endl )
{
  DataGen::ElectronElasticDataEvaluator evaluator( h_endl_data_container );

  evaluator.setCutoffAngleCosine( 0.9 );
  evaluator.setNumberOfMomentPreservingAngles( 1 );
  evaluator.setTabularEvaluationTolerance( 1e-7 );
  evaluator.setElectronTwoDInterpPolicy( MonteCarlo::LOGLOGLOG_INTERPOLATION );
  evaluator.setElectronTwoDGridPolicy( MonteCarlo::UNIT_BASE_CORRELATED_GRID );

  std::vector<double> angular_grid, mp_cross_section_reduction;
  std::map<double,std::vector<double> > cutoff_elastic_angles, cutoff_elastic_pdf, moment_preserving_angles, moment_preserving_weights;

  // Create the coupled elastic distribution (combined Cutoff and Screened Rutherford)
  evaluator.evaluateElasticSecondaryDistribution(
      angular_grid,
      cutoff_elastic_angles,
      cutoff_elastic_pdf,
      mp_cross_section_reduction,
      moment_preserving_angles,
      moment_preserving_weights );

  FRENSIE_CHECK_EQUAL( angular_grid.size(), 16 );
  FRENSIE_CHECK_EQUAL( angular_grid.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( angular_grid.back(), 1.0e+5 );

  std::vector<double> elastic_angles = cutoff_elastic_angles[1.0e-5];

  FRENSIE_CHECK_EQUAL( elastic_angles.front(), -1.0 );
  FRENSIE_CHECK_EQUAL( elastic_angles.back(), 0.999999 );
  FRENSIE_CHECK_EQUAL( elastic_angles.size(), 2 );

  elastic_angles = cutoff_elastic_angles[1.0e+5];

  FRENSIE_CHECK_EQUAL( elastic_angles.front(), -1.0 );
  FRENSIE_CHECK_EQUAL( elastic_angles.back(), 0.999999 );
  FRENSIE_CHECK_EQUAL( elastic_angles.size(), 96 );

  std::vector<double> elastic_pdf = cutoff_elastic_pdf[1.0e-5];

  FRENSIE_CHECK_EQUAL( elastic_pdf.front(), 0.5 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.back(), 0.5 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.size(), 2 );

  elastic_pdf = cutoff_elastic_pdf[1.0e+5];

  FRENSIE_CHECK_EQUAL( elastic_pdf.front(), 6.25670e-13 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.back(), 9.86945e+5 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.size(), 96 );

  FRENSIE_REQUIRE( moment_preserving_angles.size() > 0 )

  std::vector<double> discrete_angles = moment_preserving_angles[1.0e-5];

  FRENSIE_CHECK_EQUAL( discrete_angles.front(), 9.333333333266671250e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.back(), 9.333333333266671250e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.size(), 1 );

  discrete_angles = moment_preserving_angles[1.0e5];

  FRENSIE_CHECK_EQUAL( discrete_angles.front(), 9.968477432556352991e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.back(), 9.968477432556352991e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.size(), 1 );

  std::vector<double> discrete_weights = moment_preserving_weights[1.0e-5];

  FRENSIE_CHECK_EQUAL( discrete_weights.front(), 1.0 );
  FRENSIE_CHECK_EQUAL( discrete_weights.back(), 1.0 );
  FRENSIE_CHECK_EQUAL( discrete_weights.size(), 1 );

  discrete_weights = moment_preserving_weights[1.0e5];

  FRENSIE_CHECK_EQUAL( discrete_weights.front(), 1.0 );
  FRENSIE_CHECK_EQUAL( discrete_weights.back(), 1.0 );
  FRENSIE_CHECK_EQUAL( discrete_weights.size(), 1 );

  FRENSIE_CHECK_EQUAL( mp_cross_section_reduction.front(), 7.50007499925003707e-01 );
  FRENSIE_CHECK_EQUAL( mp_cross_section_reduction.back(), 9.95726637137201650e-12 );
  FRENSIE_CHECK_EQUAL( mp_cross_section_reduction.size(), 16 );
}

//---------------------------------------------------------------------------//
// Check that the elastic secondary distribution can be evaluated
FRENSIE_UNIT_TEST( ElectronElasticDataEvaluator,
                   evaluateElasticSecondaryDistribution_higher_min_energy )
{
  DataGen::ElectronElasticDataEvaluator evaluator( h_endl_data_container, true );

  evaluator.setMinEnergy( 1.5e-3 );
  evaluator.setCutoffAngleCosine( 1.0 );
  evaluator.setNumberOfMomentPreservingAngles( 1 );
  evaluator.setTabularEvaluationTolerance( 1e-7 );
  evaluator.setElectronTwoDInterpPolicy( MonteCarlo::LOGLOGLOG_INTERPOLATION );
  evaluator.setElectronTwoDGridPolicy( MonteCarlo::UNIT_BASE_CORRELATED_GRID );

  std::vector<double> angular_grid, moment_preserving_cross_section_reduction;
  std::map<double,std::vector<double> > cutoff_elastic_angles, cutoff_elastic_pdf, moment_preserving_angles, moment_preserving_weights;

  // Create the coupled elastic distribution (combined Cutoff and Screened Rutherford)
  evaluator.evaluateElasticSecondaryDistribution(
      angular_grid,
      cutoff_elastic_angles,
      cutoff_elastic_pdf,
      moment_preserving_cross_section_reduction,
      moment_preserving_angles,
      moment_preserving_weights );

  FRENSIE_CHECK_EQUAL( angular_grid.size(), 15 );
  FRENSIE_CHECK_EQUAL( angular_grid.front(), 1.0e-3 );
  FRENSIE_CHECK_EQUAL( angular_grid.back(), 1.0e+5 );

  std::vector<double> elastic_angles = cutoff_elastic_angles[1.0e-3];

  FRENSIE_CHECK_EQUAL( elastic_angles.front(), -1.0 );
  FRENSIE_CHECK_EQUAL( elastic_angles.back(), 0.999999 );
  FRENSIE_CHECK_EQUAL( elastic_angles.size(), 30 );

  elastic_angles = cutoff_elastic_angles[1.0e+5];

  FRENSIE_CHECK_EQUAL( elastic_angles.front(), -1.0 );
  FRENSIE_CHECK_EQUAL( elastic_angles.back(), 0.999999 );
  FRENSIE_CHECK_EQUAL( elastic_angles.size(), 96 );

  std::vector<double> elastic_pdf = cutoff_elastic_pdf[1.0e-3];

  FRENSIE_CHECK_EQUAL( elastic_pdf.front(), 2.93923e-03 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.back(), 6.21102e+01 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.size(), 30 );

  elastic_pdf = cutoff_elastic_pdf[1.0e+5];

  FRENSIE_CHECK_EQUAL( elastic_pdf.front(), 6.25670e-13 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.back(), 9.86945e+5 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.size(), 96 );

  FRENSIE_REQUIRE( moment_preserving_angles.size() == 0 )
}

//---------------------------------------------------------------------------//
// Check that the elastic secondary distribution can be evaluated
FRENSIE_UNIT_TEST( ElectronElasticDataEvaluator,
                   evaluateElasticSecondaryDistribution_lower_max_energy )
{
  DataGen::ElectronElasticDataEvaluator evaluator( h_endl_data_container );

  evaluator.setMaxEnergy( 20.0 );
  evaluator.setCutoffAngleCosine( 1.0 );
  evaluator.setNumberOfMomentPreservingAngles( 1 );
  evaluator.setTabularEvaluationTolerance( 1e-7 );
  evaluator.setElectronTwoDInterpPolicy( MonteCarlo::LOGLOGLOG_INTERPOLATION );
  evaluator.setElectronTwoDGridPolicy( MonteCarlo::UNIT_BASE_CORRELATED_GRID );

  std::vector<double> angular_grid, moment_preserving_cross_section_reduction;
  std::map<double,std::vector<double> > cutoff_elastic_angles, cutoff_elastic_pdf, moment_preserving_angles, moment_preserving_weights;

  // Create the coupled elastic distribution (combined Cutoff and Screened Rutherford)
  evaluator.evaluateElasticSecondaryDistribution(
      angular_grid,
      cutoff_elastic_angles,
      cutoff_elastic_pdf,
      moment_preserving_cross_section_reduction,
      moment_preserving_angles,
      moment_preserving_weights );

  FRENSIE_CHECK_EQUAL( angular_grid.size(), 12 );
  FRENSIE_CHECK_EQUAL( angular_grid.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( angular_grid.back(), 2.125e1 );

  std::vector<double> elastic_angles = cutoff_elastic_angles[1.0e-5];

  FRENSIE_CHECK_EQUAL( elastic_angles.front(), -1.0 );
  FRENSIE_CHECK_EQUAL( elastic_angles.back(), 0.999999 );
  FRENSIE_CHECK_EQUAL( elastic_angles.size(), 2 );

  elastic_angles = cutoff_elastic_angles[2.125e1];

  FRENSIE_REQUIRE( elastic_angles.size() > 0 );
  FRENSIE_CHECK_EQUAL( elastic_angles.front(), -1.0 );
  FRENSIE_CHECK_EQUAL( elastic_angles.back(), 0.999999 );
  FRENSIE_CHECK_EQUAL( elastic_angles.size(), 95 );

  std::vector<double> elastic_pdf = cutoff_elastic_pdf[1.0e-5];

  FRENSIE_CHECK_EQUAL( elastic_pdf.front(), 0.5 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.back(), 0.5 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.size(), 2 );

  elastic_pdf = cutoff_elastic_pdf[2.125e1];

  FRENSIE_CHECK_EQUAL( elastic_pdf.front(), 1.39545e-10 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.back(), 9.66202e+05 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.size(), 95 );

  FRENSIE_REQUIRE( moment_preserving_angles.size() == 0 )
}

//---------------------------------------------------------------------------//
// Check that the elastic secondary distribution can be evaluated
FRENSIE_UNIT_TEST( ElectronElasticDataEvaluator,
                   evaluateElasticSecondaryDistribution_native )
{
  DataGen::ElectronElasticDataEvaluator evaluator( h_native_data_container );

  evaluator.setMinEnergy( 1e-4 );
  evaluator.setMaxEnergy( 20.0 );
  evaluator.setCutoffAngleCosine( 0.9 );
  evaluator.setNumberOfMomentPreservingAngles( 1 );
  evaluator.setTabularEvaluationTolerance( 1e-7 );
  evaluator.setElectronTwoDInterpPolicy( MonteCarlo::LOGLOGLOG_INTERPOLATION );
  evaluator.setElectronTwoDGridPolicy( MonteCarlo::UNIT_BASE_CORRELATED_GRID );
  evaluator.setGenerateNewDistributionAtMinAndMaxEnergyOn();

  std::vector<double> angular_grid, mp_cross_section_reduction;
  std::map<double,std::vector<double> > cutoff_elastic_angles, cutoff_elastic_pdf, moment_preserving_angles, moment_preserving_weights;

  // Create the coupled elastic distribution (combined Cutoff and Screened Rutherford)
  evaluator.evaluateElasticSecondaryDistribution(
      angular_grid,
      cutoff_elastic_angles,
      cutoff_elastic_pdf,
      mp_cross_section_reduction,
      moment_preserving_angles,
      moment_preserving_weights,
      1e-1 );

  FRENSIE_CHECK_EQUAL( angular_grid.size(), 12 );
  FRENSIE_CHECK_EQUAL( angular_grid.front(), 1e-4 );
  FRENSIE_CHECK_EQUAL( angular_grid.back(), 20.0 );

  std::vector<double> elastic_angles = cutoff_elastic_angles[1e-4];

  FRENSIE_CHECK_EQUAL( elastic_angles.front(), -1.0 );
  FRENSIE_CHECK_EQUAL( elastic_angles.back(), 0.999999 );
  FRENSIE_CHECK_EQUAL( elastic_angles.size(), 41 );

  elastic_angles = cutoff_elastic_angles[20.0];

  FRENSIE_CHECK_EQUAL( elastic_angles.front(), -1.0 );
  FRENSIE_CHECK_EQUAL( elastic_angles.back(), 0.999999 );
  FRENSIE_CHECK_EQUAL( elastic_angles.size(), 95 );

  std::vector<double> elastic_pdf = cutoff_elastic_pdf[1e-4];

  FRENSIE_CHECK_EQUAL( elastic_pdf.front(), 5.844104724870039999e-03 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.back(), 9.920145715224548688e-01 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.size(), 41 );

  elastic_pdf = cutoff_elastic_pdf[20.0];

  FRENSIE_CHECK_EQUAL( elastic_pdf.front(), 1.488941264770909258e-10 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.back(), 9.608615060065749567e+05 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.size(), 95 );

  FRENSIE_REQUIRE( moment_preserving_angles.size() > 0 )

  std::vector<double> discrete_angles = moment_preserving_angles[1e-3];

  FRENSIE_CHECK_EQUAL( discrete_angles.front(), 9.563120131506376298e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.back(), 9.563120131506376298e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.size(), 1 );

  discrete_angles = moment_preserving_angles[20.0];

  FRENSIE_CHECK_EQUAL( discrete_angles.front(), 9.931382017989757172e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.back(), 9.931382017989757172e-01 );
  FRENSIE_CHECK_EQUAL( discrete_angles.size(), 1 );

  std::vector<double> discrete_weights = moment_preserving_weights[1e-3];

  FRENSIE_CHECK_EQUAL( discrete_weights.front(), 1.0 );
  FRENSIE_CHECK_EQUAL( discrete_weights.back(), 1.0 );
  FRENSIE_CHECK_EQUAL( discrete_weights.size(), 1 );

  discrete_weights = moment_preserving_weights[20.0];

  FRENSIE_CHECK_EQUAL( discrete_weights.front(), 1.0 );
  FRENSIE_CHECK_EQUAL( discrete_weights.back(), 1.0 );
  FRENSIE_CHECK_EQUAL( discrete_weights.size(), 1 );

  FRENSIE_CHECK_EQUAL( mp_cross_section_reduction.front(), 7.168695557344448854e-01 );
  FRENSIE_CHECK_EQUAL( mp_cross_section_reduction.back(), 4.935491711992172245e-05 );
  FRENSIE_CHECK_EQUAL( mp_cross_section_reduction.size(), 12 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_h_endl_file_name, test_h_native_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_endl_file",
                                        test_h_endl_file_name, "",
                                        "Test ENDL file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_file",
                                        test_h_native_file_name, "",
                                        "Test Native file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Create the endl data container for hydrogen
  h_endl_data_container.reset(
                        new Data::ENDLDataContainer( test_h_endl_file_name ) );

  h_native_data_container.reset(
                        new Data::ElectronPhotonRelaxationDataContainer( test_h_native_file_name ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElectronElasticDataEvaluator.cpp
//---------------------------------------------------------------------------//
