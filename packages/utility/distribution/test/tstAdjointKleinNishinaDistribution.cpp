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
// Check that the min inverse energy gain ratio can be calculated
TEUCHOS_UNIT_TEST( AdjointKleinNishinaDistribution,
		   calculateMinInverseEnergyGainRatio )
{
  double min_inverse_energy_gain_ratio = 
    Utility::AdjointKleinNishinaDistribution::calculateMinInverseEnergyGainRatio(
									0.1,
									0.5 );

  TEST_FLOATING_EQUALITY( min_inverse_energy_gain_ratio, 0.8, 1e-15 );

  min_inverse_energy_gain_ratio = 
    Utility::AdjointKleinNishinaDistribution::calculateMinInverseEnergyGainRatio(
									0.25,
									0.5 );

  TEST_FLOATING_EQUALITY( min_inverse_energy_gain_ratio, 0.5, 1e-15 );

  min_inverse_energy_gain_ratio = 
    Utility::AdjointKleinNishinaDistribution::calculateMinInverseEnergyGainRatio(
									0.4,
									0.5 );

  TEST_FLOATING_EQUALITY( min_inverse_energy_gain_ratio, 0.8, 1e-15 );

  min_inverse_energy_gain_ratio = 
    Utility::AdjointKleinNishinaDistribution::calculateMinInverseEnergyGainRatio(
									0.4,
									12.0 );

  TEST_FLOATING_EQUALITY( min_inverse_energy_gain_ratio, 0.2, 1e-15 );

  min_inverse_energy_gain_ratio = 
    Utility::AdjointKleinNishinaDistribution::calculateMinInverseEnergyGainRatio(
									0.48,
									12.0 );

  TEST_FLOATING_EQUALITY( min_inverse_energy_gain_ratio, 0.04, 1e-15 );

  min_inverse_energy_gain_ratio = 
    Utility::AdjointKleinNishinaDistribution::calculateMinInverseEnergyGainRatio(
									2.4,
									12.0 );

  TEST_FLOATING_EQUALITY( min_inverse_energy_gain_ratio, 0.2, 1e-15 );
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

  integrated_cs = distribution->evaluateIntegratedCrossSection();

  UTILITY_TEST_FLOATING_EQUALITY( integrated_cs, 0.0, 1e-12 );
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

  value = distribution_base->evaluate( 1.01 );

  TEST_EQUALITY_CONST( value, 0.0 );

  distribution->setEnergy( 
		  Utility::PhysicalConstants::electron_rest_mass_energy*0.25 );

  value = distribution_base->evaluate( 0.49 );

  TEST_EQUALITY_CONST( value, 0.0 );

  value = distribution_base->evaluate( 0.5 );

  UTILITY_TEST_FLOATING_EQUALITY( value, 2.4946720254416257e-24, 1e-12 );

  value = distribution_base->evaluate( 1.0 );

  UTILITY_TEST_FLOATING_EQUALITY( value, 1.9957376203533005e-24, 1e-12 );

  value = distribution_base->evaluate( 1.01 );

  TEST_EQUALITY_CONST( value, 0.0 );

  distribution->setEnergy(
		   Utility::PhysicalConstants::electron_rest_mass_energy*0.4 );

  value = distribution_base->evaluate( 0.79 );

  TEST_EQUALITY_CONST( value, 0.0 );

  value = distribution_base->evaluate( 0.8 );

  UTILITY_TEST_FLOATING_EQUALITY( value, 8.107684082685284e-25, 1e-12 );

  value = distribution_base->evaluate( 1.0 );

  UTILITY_TEST_FLOATING_EQUALITY( value, 1.247336012720813e-24, 1e-12 );

  value = distribution_base->evaluate( 1.01 );

  TEST_EQUALITY_CONST( value, 0.0 );

  // Set a new max energy
  distribution.reset(
	   new Utility::AdjointKleinNishinaDistribution( 
		Utility::PhysicalConstants::electron_rest_mass_energy*0.4,
		Utility::PhysicalConstants::electron_rest_mass_energy*12.0 ) );

  distribution_base = distribution;

  value = distribution_base->evaluate( 0.19 );

  TEST_EQUALITY_CONST( value, 0.0 );

  value = distribution_base->evaluate( 0.2 );

  UTILITY_TEST_FLOATING_EQUALITY( value, 3.2430736330741126e-24, 1e-12 );

  value = distribution_base->evaluate( 1.0 );

  UTILITY_TEST_FLOATING_EQUALITY( value, 1.247336012720813e-24, 1e-12 );

  value = distribution_base->evaluate( 1.01 );

  TEST_EQUALITY_CONST( value, 0.0 );

  distribution->setEnergy( 
		  Utility::PhysicalConstants::electron_rest_mass_energy*0.48 );

  value = distribution_base->evaluate( 0.039 );

  TEST_EQUALITY_CONST( value, 0.0 );

  value = distribution_base->evaluate( 0.04 );

  UTILITY_TEST_FLOATING_EQUALITY( value, 1.3013872399387147e-23, 1e-12 );

  value = distribution_base->evaluate( 1.0 );

  UTILITY_TEST_FLOATING_EQUALITY( value, 1.0394466772673439e-24, 1e-12 );

  value = distribution_base->evaluate( 1.01 );
  
  TEST_EQUALITY_CONST( value, 0.0 );

  distribution->setEnergy(
		   Utility::PhysicalConstants::electron_rest_mass_energy*2.4 );

  value = distribution_base->evaluate( 0.19 );

  TEST_EQUALITY_CONST( value, 0.0 );

  value = distribution_base->evaluate( 0.2 );

  UTILITY_TEST_FLOATING_EQUALITY( value, 4.827652345530553e-25, 1e-12 );

  value = distribution_base->evaluate( 1.0 );

  UTILITY_TEST_FLOATING_EQUALITY( value, 2.078893354534688e-25, 1e-12 );

  value = distribution_base->evaluate( 1.01 );

  TEST_EQUALITY_CONST( value, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( AdjointKleinNishinaDistribution, evaluatePDF )
{
  Teuchos::RCP<Utility::AdjointKleinNishinaDistribution> 
    distribution( new Utility::AdjointKleinNishinaDistribution( 
		 Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		 Utility::PhysicalConstants::electron_rest_mass_energy/2.0 ) );

  Teuchos::RCP<Utility::OneDDistribution> distribution_base = distribution;

  double value = distribution_base->evaluatePDF( 0.79 );

  TEST_EQUALITY_CONST( value, 0.0 );

  value = distribution_base->evaluatePDF( 0.8 );

  UTILITY_TEST_FLOATING_EQUALITY( value, 7.59793315219362, 1e-11 );

  value = distribution_base->evaluatePDF( 1.0 );

  UTILITY_TEST_FLOATING_EQUALITY( value, 7.412617709457161, 1e-11 );

  value = distribution_base->evaluatePDF( 1.01 );

  TEST_EQUALITY_CONST( value, 0.0 );

  distribution->setEnergy( 
  		  Utility::PhysicalConstants::electron_rest_mass_energy*0.25 );

  value = distribution_base->evaluatePDF( 0.49 );

  TEST_EQUALITY_CONST( value, 0.0 );

  value = distribution_base->evaluatePDF( 0.5 );

  UTILITY_TEST_FLOATING_EQUALITY( value, 3.4022222219081852, 1e-12 );

  value = distribution_base->evaluatePDF( 1.0 );

  UTILITY_TEST_FLOATING_EQUALITY( value, 2.7217777775265484, 1e-12 );

  value = distribution_base->evaluatePDF( 1.01 );

  TEST_EQUALITY_CONST( value, 0.0 );

  distribution->setEnergy(
  		   Utility::PhysicalConstants::electron_rest_mass_energy*0.4 );

  value = distribution_base->evaluatePDF( 0.79 );

  TEST_EQUALITY_CONST( value, 0.0 );

  value = distribution_base->evaluatePDF( 0.8 );

  UTILITY_TEST_FLOATING_EQUALITY( value, 4.0649107717928095, 1e-12 );

  value = distribution_base->evaluatePDF( 1.0 );

  UTILITY_TEST_FLOATING_EQUALITY( value, 6.253708879681246, 1e-12 );

  value = distribution_base->evaluatePDF( 1.01 );

  TEST_EQUALITY_CONST( value, 0.0 );

  // Set a new max energy
  distribution.reset(
  	   new Utility::AdjointKleinNishinaDistribution( 
  		Utility::PhysicalConstants::electron_rest_mass_energy*0.4,
  		Utility::PhysicalConstants::electron_rest_mass_energy*12.0 ) );

  distribution_base = distribution;

  value = distribution_base->evaluatePDF( 0.19 );

  TEST_EQUALITY_CONST( value, 0.0 );

  value = distribution_base->evaluatePDF( 0.2 );

  UTILITY_TEST_FLOATING_EQUALITY( value, 3.3416777187335565, 1e-12 );

  value = distribution_base->evaluatePDF( 1.0 );

  UTILITY_TEST_FLOATING_EQUALITY( value, 1.2852606610513684, 1e-12 );

  value = distribution_base->evaluatePDF( 1.01 );

  TEST_EQUALITY_CONST( value, 0.0 );

  distribution->setEnergy( 
  		  Utility::PhysicalConstants::electron_rest_mass_energy*0.48 );

  value = distribution_base->evaluatePDF( 0.039 );

  TEST_EQUALITY_CONST( value, 0.0 );

  value = distribution_base->evaluatePDF( 0.04 );

  UTILITY_TEST_FLOATING_EQUALITY( value, 8.134952296398385, 1e-12 );

  value = distribution_base->evaluatePDF( 1.0 );

  UTILITY_TEST_FLOATING_EQUALITY( value, 0.6497565731947591, 1e-12 );

  value = distribution_base->evaluatePDF( 1.01 );
  
  TEST_EQUALITY_CONST( value, 0.0 );

  distribution->setEnergy(
  		   Utility::PhysicalConstants::electron_rest_mass_energy*2.4 );

  value = distribution_base->evaluatePDF( 0.19 );

  TEST_EQUALITY_CONST( value, 0.0 );

  value = distribution_base->evaluatePDF( 0.2 );

  UTILITY_TEST_FLOATING_EQUALITY( value, 2.507256666810253, 1e-12 );

  value = distribution_base->evaluatePDF( 1.0 );

  UTILITY_TEST_FLOATING_EQUALITY( value, 1.0796799043680516, 1e-12 );

  value = distribution_base->evaluatePDF( 1.01 );

  TEST_EQUALITY_CONST( value, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the energy pdf can be evaluated
TEUCHOS_UNIT_TEST( AdjointKleinNishinaDistribution, evaluateEnergyPDF )
{
  Teuchos::RCP<Utility::AdjointKleinNishinaDistribution> 
    distribution( new Utility::AdjointKleinNishinaDistribution( 
		 Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		 Utility::PhysicalConstants::electron_rest_mass_energy/2.0 ) );

  double value = distribution->evaluateEnergyPDF( 
	      Utility::PhysicalConstants::electron_rest_mass_energy*0.1/0.79 );

  TEST_EQUALITY_CONST( value, 0.0 );

  value = distribution->evaluateEnergyPDF(
	       Utility::PhysicalConstants::electron_rest_mass_energy*0.1/0.8 );

  // dc/dE = 6.7308800297602e-25
  UTILITY_TEST_FLOATING_EQUALITY( value, 95.16022678339682, 1e-11 );

  value = distribution->evaluateEnergyPDF( 
		   Utility::PhysicalConstants::electron_rest_mass_energy*0.1 );

  // dc/dE = 9.763903507375277e-23
  UTILITY_TEST_FLOATING_EQUALITY( value, 145.06132131615388, 1e-11 );

  value = distribution->evaluateEnergyPDF( 
	      Utility::PhysicalConstants::electron_rest_mass_energy*0.1/1.01 );

  TEST_EQUALITY_CONST( value, 0.0 );

  distribution->setEnergy( 
  		  Utility::PhysicalConstants::electron_rest_mass_energy*0.25 );

  value = distribution->evaluateEnergyPDF( 
	     Utility::PhysicalConstants::electron_rest_mass_energy*0.25/0.49 );

  TEST_EQUALITY_CONST( value, 0.0 );

  value = distribution->evaluateEnergyPDF( 
	      Utility::PhysicalConstants::electron_rest_mass_energy*0.25/0.5 );

  // dc/dE = 4.881951753687639e-24
  UTILITY_TEST_FLOATING_EQUALITY( value, 6.6579833233746974, 1e-12 );

  value = distribution->evaluateEnergyPDF( 
	      Utility::PhysicalConstants::electron_rest_mass_energy*0.25/1.0 );

  // dc/dE = 1.5622245611800446e-23
  UTILITY_TEST_FLOATING_EQUALITY( value, 21.305546634799033, 1e-12 );

  value = distribution->evaluateEnergyPDF( 
	     Utility::PhysicalConstants::electron_rest_mass_energy*0.25/1.01 );

  TEST_EQUALITY_CONST( value, 0.0 );

  distribution->setEnergy(
  		   Utility::PhysicalConstants::electron_rest_mass_energy*0.4 );

  value = distribution->evaluateEnergyPDF( 
	      Utility::PhysicalConstants::electron_rest_mass_energy*0.4/0.79 );

  TEST_EQUALITY_CONST( value, 0.0 );

  value = distribution->evaluateEnergyPDF( 
	       Utility::PhysicalConstants::electron_rest_mass_energy*0.4/0.8 );

  // dc/dE = 2.5386149119175728e-24
  UTILITY_TEST_FLOATING_EQUALITY( value, 12.727732106539897, 1e-12 );

  value = distribution->evaluateEnergyPDF( 
		   Utility::PhysicalConstants::electron_rest_mass_energy*0.4 );

  // dc/dE = 6.1024396921095496e-24
  UTILITY_TEST_FLOATING_EQUALITY( value, 30.595509871490137, 1e-12 );

  value = distribution->evaluateEnergyPDF( 
	      Utility::PhysicalConstants::electron_rest_mass_energy*0.4/1.01 );

  TEST_EQUALITY_CONST( value, 0.0 );

  // Set a new max energy
  distribution.reset(
  	   new Utility::AdjointKleinNishinaDistribution( 
  		Utility::PhysicalConstants::electron_rest_mass_energy*0.4,
  		Utility::PhysicalConstants::electron_rest_mass_energy*12.0 ) );

  value = distribution->evaluateEnergyPDF( 
	      Utility::PhysicalConstants::electron_rest_mass_energy*0.4/0.19 );

  TEST_EQUALITY_CONST( value, 0.0 );

  value = distribution->evaluateEnergyPDF( 
	       Utility::PhysicalConstants::electron_rest_mass_energy*0.4/0.2 );

  // dc/dE = 6.34653727979393e-25
  UTILITY_TEST_FLOATING_EQUALITY( value, 0.6539500676984658, 1e-12 );

  value = distribution->evaluateEnergyPDF( 
		   Utility::PhysicalConstants::electron_rest_mass_energy*0.4 );

  // dc/dE = 6.1024396921095496e-24
  UTILITY_TEST_FLOATING_EQUALITY( value, 6.287981420177557, 1e-12 );

  value = distribution->evaluateEnergyPDF( 
	      Utility::PhysicalConstants::electron_rest_mass_energy*0.4/1.01 );

  TEST_EQUALITY_CONST( value, 0.0 );

  distribution->setEnergy( 
  		  Utility::PhysicalConstants::electron_rest_mass_energy*0.48 );

  value = distribution->evaluateEnergyPDF( 
	    Utility::PhysicalConstants::electron_rest_mass_energy*0.48/0.039 );

  TEST_EQUALITY_CONST( value, 0.0 );

  value = distribution->evaluateEnergyPDF( 
	     Utility::PhysicalConstants::electron_rest_mass_energy*0.48/0.04 );

  // dc/dE = 8.489171660579061e-26
  UTILITY_TEST_FLOATING_EQUALITY( value, 0.05306568588915923, 1e-12 );

  value = distribution->evaluateEnergyPDF( 
	          Utility::PhysicalConstants::electron_rest_mass_energy*0.48 );

  // dc/dE = 4.237805341742741e-24
  UTILITY_TEST_FLOATING_EQUALITY( value, 2.64904582114413, 1e-12 );

  value = distribution->evaluateEnergyPDF( 
	     Utility::PhysicalConstants::electron_rest_mass_energy*0.48/1.01 );
  
  TEST_EQUALITY_CONST( value, 0.0 );

  distribution->setEnergy(
  		   Utility::PhysicalConstants::electron_rest_mass_energy*2.4 );

  value = distribution->evaluateEnergyPDF( 
	      Utility::PhysicalConstants::electron_rest_mass_energy*2.4/0.19 );

  TEST_EQUALITY_CONST( value, 0.0 );

  value = distribution->evaluateEnergyPDF( 
	       Utility::PhysicalConstants::electron_rest_mass_energy*2.4/0.2 );

  // dc/dE = 1.5745801180875262e-26
  UTILITY_TEST_FLOATING_EQUALITY( value, 0.08177632140716959, 1e-12 );

  value = distribution->evaluateEnergyPDF( 
		   Utility::PhysicalConstants::electron_rest_mass_energy*2.4 );

  // dc/dE = 1.6951221366970969e-25
  UTILITY_TEST_FLOATING_EQUALITY( value, 0.8803670964886674, 1e-12 );

  value = distribution->evaluateEnergyPDF( 
	      Utility::PhysicalConstants::electron_rest_mass_energy*2.4/1.01 );

  TEST_EQUALITY_CONST( value, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that a random number can be sampled from the distribution
TEUCHOS_UNIT_TEST( AdjointKleinNishinaDistribution, sample )
{
  Teuchos::RCP<Utility::OneDDistribution>
    distribution( new Utility::AdjointKleinNishinaDistribution( 
		 Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		 Utility::PhysicalConstants::electron_rest_mass_energy/2.0 ) );

  // Set up the fake stream
  std::vector<double> fake_stream( 12 );
  fake_stream[0] = 0.15; // branch 1
  fake_stream[1] = 0.4721647344828152; // select x = 0.9
  fake_stream[2] = 0.55; // reject
  fake_stream[3] = 0.15; // branch 1
  fake_stream[4] = 0.22986680137273696; // select x = 0.95
  fake_stream[5] = 0.245; // accept
  fake_stream[6] = 0.77; // branch 2
  fake_stream[7] = 0.5; // select x = 0.9055385138137417
  fake_stream[8] = 0.78; // branch 3
  fake_stream[9] = 0.1; // select x = 0.8071682233277445
  fake_stream[10] = 0.99; // branch 3
  fake_stream[11] = 0.5; // select x = 0.9000009536743164
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();

  TEST_FLOATING_EQUALITY( sample, 0.95, 1e-15 );
  TEST_EQUALITY_CONST( distribution->getSamplingEfficiency(), 0.5 );

  sample = distribution->sample();

  TEST_FLOATING_EQUALITY( sample, 0.9055385138137417, 1e-15 );
  TEST_EQUALITY_CONST( distribution->getSamplingEfficiency(), 2/3.0 );
  
  sample = distribution->sample();

  TEST_FLOATING_EQUALITY( sample, 0.8071682233277445, 1e-15 );
  TEST_EQUALITY_CONST( distribution->getSamplingEfficiency(), 3/4.0 );

  sample = distribution->sample();

  TEST_FLOATING_EQUALITY( sample, 0.9000009536743164, 1e-15 );
  TEST_EQUALITY_CONST( distribution->getSamplingEfficiency(), 4/5.0 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a random number can be sampled from the distribution
TEUCHOS_UNIT_TEST( AdjointKleinNishinaDistribution, sample_const )
{
  Teuchos::RCP<const Utility::OneDDistribution>
    distribution( new Utility::AdjointKleinNishinaDistribution( 
		 Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		 Utility::PhysicalConstants::electron_rest_mass_energy/2.0 ) );

  // Set up the fake stream
  std::vector<double> fake_stream( 12 );
  fake_stream[0] = 0.15; // branch 1
  fake_stream[1] = 0.4721647344828152; // select x = 0.9
  fake_stream[2] = 0.55; // reject
  fake_stream[3] = 0.15; // branch 1
  fake_stream[4] = 0.22986680137273696; // select x = 0.95
  fake_stream[5] = 0.245; // accept
  fake_stream[6] = 0.77; // branch 2
  fake_stream[7] = 0.5; // select x = 0.9055385138137417
  fake_stream[8] = 0.78; // branch 3
  fake_stream[9] = 0.1; // select x = 0.8071682233277445
  fake_stream[10] = 0.99; // branch 3
  fake_stream[11] = 0.5; // select x = 0.9000009536743164
  
  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();

  TEST_FLOATING_EQUALITY( sample, 0.95, 1e-15 );
  TEST_EQUALITY_CONST( distribution->getSamplingEfficiency(), 1.0 );

  sample = distribution->sample();

  TEST_FLOATING_EQUALITY( sample, 0.9055385138137417, 1e-15 );
  TEST_EQUALITY_CONST( distribution->getSamplingEfficiency(), 1.0 );
  
  sample = distribution->sample();

  TEST_FLOATING_EQUALITY( sample, 0.8071682233277445, 1e-15 );
  TEST_EQUALITY_CONST( distribution->getSamplingEfficiency(), 1.0 );

  sample = distribution->sample();

  TEST_FLOATING_EQUALITY( sample, 0.9000009536743164, 1e-15 );
  TEST_EQUALITY_CONST( distribution->getSamplingEfficiency(), 1.0 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the sampling efficiency can be returned
TEUCHOS_UNIT_TEST( AdjointKleinNishinaDistribution, getSamplingEfficiency )
{
  Teuchos::RCP<Utility::OneDDistribution>
    distribution( new Utility::AdjointKleinNishinaDistribution( 
		 Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		 Utility::PhysicalConstants::electron_rest_mass_energy/2.0 ) );

  for( unsigned i = 0; i < 10; ++i )
    distribution->sample();

  TEST_ASSERT( distribution->getSamplingEfficiency() < 1.0 );
  TEST_ASSERT( distribution->getSamplingEfficiency() > 0.0 );

  distribution.reset();

  Teuchos::RCP<const Utility::OneDDistribution>
    const_distribution( new Utility::AdjointKleinNishinaDistribution( 
		 Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		 Utility::PhysicalConstants::electron_rest_mass_energy/2.0 ) );

  for( unsigned i = 0; i < 10; ++i )
    const_distribution->sample();

  TEST_EQUALITY_CONST( const_distribution->getSamplingEfficiency(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( AdjointKleinNishinaDistribution, getUpperBoundOfIndepVar )
{
  Teuchos::RCP<Utility::AdjointKleinNishinaDistribution>
    distribution( new Utility::AdjointKleinNishinaDistribution( 
		 Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		 Utility::PhysicalConstants::electron_rest_mass_energy/2.0 ) );

  Teuchos::RCP<Utility::OneDDistribution>
    base_distribution = distribution;

  TEST_EQUALITY_CONST( base_distribution->getUpperBoundOfIndepVar(), 1.0 );

  distribution->setEnergy( 
		  Utility::PhysicalConstants::electron_rest_mass_energy*0.25 );
  
  TEST_EQUALITY_CONST( base_distribution->getUpperBoundOfIndepVar(), 1.0 );

  distribution->setEnergy(
		   Utility::PhysicalConstants::electron_rest_mass_energy*0.4 );

  TEST_EQUALITY_CONST( base_distribution->getUpperBoundOfIndepVar(), 1.0 );

  // Set a new max energy
  distribution.reset(
	   new Utility::AdjointKleinNishinaDistribution( 
		Utility::PhysicalConstants::electron_rest_mass_energy*0.4,
		Utility::PhysicalConstants::electron_rest_mass_energy*12.0 ) );

  base_distribution = distribution;

  TEST_EQUALITY_CONST( base_distribution->getUpperBoundOfIndepVar(), 1.0 );

  distribution->setEnergy( 
		  Utility::PhysicalConstants::electron_rest_mass_energy*0.48 );

  TEST_EQUALITY_CONST( base_distribution->getUpperBoundOfIndepVar(), 1.0 );

  distribution->setEnergy(
		   Utility::PhysicalConstants::electron_rest_mass_energy*2.4 );

  TEST_EQUALITY_CONST( base_distribution->getUpperBoundOfIndepVar(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( AdjointKleinNishinaDistribution, getLowerBoundOfIndepVar )
{
  Teuchos::RCP<Utility::AdjointKleinNishinaDistribution>
    distribution( new Utility::AdjointKleinNishinaDistribution( 
		 Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		 Utility::PhysicalConstants::electron_rest_mass_energy/2.0 ) );

  Teuchos::RCP<Utility::OneDDistribution>
    base_distribution = distribution;

  TEST_FLOATING_EQUALITY( base_distribution->getLowerBoundOfIndepVar(), 
			  0.8,
			  1e-15 );

  distribution->setEnergy( 
		  Utility::PhysicalConstants::electron_rest_mass_energy*0.25 );
  
  TEST_FLOATING_EQUALITY( base_distribution->getLowerBoundOfIndepVar(), 
			  0.5,
			  1e-15 );

  distribution->setEnergy(
		   Utility::PhysicalConstants::electron_rest_mass_energy*0.4 );

  TEST_FLOATING_EQUALITY( base_distribution->getLowerBoundOfIndepVar(), 
			  0.8,
			  1e-15 );

  // Set a new max energy
  distribution.reset(
	   new Utility::AdjointKleinNishinaDistribution( 
		Utility::PhysicalConstants::electron_rest_mass_energy*0.4,
		Utility::PhysicalConstants::electron_rest_mass_energy*12.0 ) );

  base_distribution = distribution;

  TEST_FLOATING_EQUALITY( base_distribution->getLowerBoundOfIndepVar(), 
			  0.2,
			  1e-15 );

  distribution->setEnergy( 
		  Utility::PhysicalConstants::electron_rest_mass_energy*0.48 );

  TEST_FLOATING_EQUALITY( base_distribution->getLowerBoundOfIndepVar(), 
			  0.04,
			  1e-15 );

  distribution->setEnergy(
		   Utility::PhysicalConstants::electron_rest_mass_energy*2.4 );

  TEST_FLOATING_EQUALITY( base_distribution->getLowerBoundOfIndepVar(), 
			  0.2,
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
