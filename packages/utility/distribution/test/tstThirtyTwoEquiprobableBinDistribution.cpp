//---------------------------------------------------------------------------//
//!
//! \file   tstThirtyTwoEquiprobableBinDistribution.cpp
//! \author Alex Robinson
//! \brief  Thirty-two equiprobable bin distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRNECS Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_ThirtyTwoEquiprobableBinDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"

Teuchos::RCP<Utility::OneDDistribution> distribution;

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//
// Initialize the distribution
void initializeDistribution( 
			 Teuchos::RCP<Utility::OneDDistribution>& distribution )
{
  Teuchos::Array<double> bin_boundaries( 33 );
  
  bin_boundaries[0] = -16.0;
  bin_boundaries[1] = -15.0;
  bin_boundaries[2] = -14.0;
  bin_boundaries[3] = -13.0;
  bin_boundaries[4] = -12.0;
  bin_boundaries[5] = -11.0;
  bin_boundaries[6] = -10.0;
  bin_boundaries[7] = -9.0;
  bin_boundaries[8] = -8.0;
  bin_boundaries[9] = -7.0;
  bin_boundaries[10] = -6.0;
  bin_boundaries[11] = -5.0;
  bin_boundaries[12] = -4.0;
  bin_boundaries[13] = -3.0;
  bin_boundaries[14] = -2.0;
  bin_boundaries[15] = -0.5;
  bin_boundaries[16] = 0.0;
  bin_boundaries[17] = 0.5;
  bin_boundaries[18] = 2.0;
  bin_boundaries[19] = 3.0;
  bin_boundaries[20] = 4.0;
  bin_boundaries[21] = 5.0;
  bin_boundaries[22] = 6.0;
  bin_boundaries[23] = 7.0;
  bin_boundaries[24] = 8.0;
  bin_boundaries[25] = 9.0;
  bin_boundaries[26] = 10.0;
  bin_boundaries[27] = 11.0;
  bin_boundaries[28] = 12.0;
  bin_boundaries[29] = 13.0;
  bin_boundaries[30] = 14.0;
  bin_boundaries[31] = 15.0;
  bin_boundaries[32] = 16.0;

  distribution.reset( 
	  new Utility::ThirtyTwoEquiprobableBinDistribution( bin_boundaries ) );
  
  Utility::RandomNumberGenerator::initialize();
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( ThirtyTwoEquiprobableBinDistribution, evaluate )
{
  initializeDistribution( distribution );

  TEST_EQUALITY_CONST( distribution->evaluate( -17.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -16.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( -15.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( -14.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( -13.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( -12.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( -11.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( -10.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( -9.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( -8.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( -7.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( -6.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( -5.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( -4.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( -3.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( -2.0 ), 1.0/48 );
  TEST_EQUALITY_CONST( distribution->evaluate( -0.5 ), 1.0/16 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 1.0/16 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.5 ), 1.0/48 );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 3.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 4.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 5.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 6.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 7.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 8.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 9.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 10.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 11.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 12.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 13.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 14.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 15.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluate( 16.0 ), 1.0/32 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( ThirtyTwoEquiprobableBinDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -17.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -16.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -15.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -14.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -13.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -12.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -11.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -10.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -9.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -8.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -7.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -6.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -5.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -4.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -3.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -2.0 ), 1.0/48 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -0.5 ), 1.0/16 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.0 ), 1.0/16 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.5 ), 1.0/48 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 2.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 3.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 4.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 5.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 6.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 7.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 8.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 9.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 10.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 11.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 12.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 13.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 14.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 15.0 ), 1.0/32 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 16.0 ), 1.0/32 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( ThirtyTwoEquiprobableBinDistribution, sample )
{
  std::vector<double> fake_stream( 65 );
  // First bin
  fake_stream[0] = 0.0;      fake_stream[1] = 1.0/64;
  // Second bin
  fake_stream[2] = 2.0/64;   fake_stream[3] = 3.0/64;   
  // Third bin
  fake_stream[4] = 4.0/64;   fake_stream[5] = 5.0/64;
  // Fourth bin
  fake_stream[6] = 6.0/64;   fake_stream[7] = 7.0/64; 
  // Fifth bin
  fake_stream[8] = 8.0/64;   fake_stream[9] = 9.0/64;  
  // Sixth bin
  fake_stream[10] = 10.0/64; fake_stream[11] = 11.0/64; 
  // Seventh bin
  fake_stream[12] = 12.0/64; fake_stream[13] = 13.0/64; 
  // Eighth bin
  fake_stream[14] = 14.0/64; fake_stream[15] = 15.0/64;
  // Nineth bin
  fake_stream[16] = 16.0/64; fake_stream[17] = 17.0/64;
  // Tenth bin
  fake_stream[18] = 18.0/64; fake_stream[19] = 19.0/64; 
  // Eleventh bin
  fake_stream[20] = 20.0/64; fake_stream[21] = 21.0/64; 
  // Twelfth bin
  fake_stream[22] = 22.0/64; fake_stream[23] = 23.0/64; 
  // Thirteenth bin
  fake_stream[24] = 24.0/64; fake_stream[25] = 25.0/64; 
  // Fourteenth bin
  fake_stream[26] = 26.0/64; fake_stream[27] = 27.0/64; 
  // Fifteenth bin
  fake_stream[28] = 28.0/64; fake_stream[29] = 29.0/64; 
  // Sixteenth bin
  fake_stream[30] = 30.0/64; fake_stream[31] = 31.0/64; 
  // Seventeenth bin
  fake_stream[32] = 32.0/64; fake_stream[33] = 33.0/64;
  // Eighteenth bin
  fake_stream[34] = 34.0/64; fake_stream[35] = 35.0/64; 
  // Nineteenth bin
  fake_stream[36] = 36.0/64; fake_stream[37] = 37.0/64; 
  // Twentieth bin
  fake_stream[38] = 38.0/64; fake_stream[39] = 39.0/64; 
  // Twenty-first bin
  fake_stream[40] = 40.0/64; fake_stream[41] = 41.0/64; 
  // Twenty-second bin
  fake_stream[42] = 42.0/64; fake_stream[43] = 43.0/64; 
  // Twenty-third bin
  fake_stream[44] = 44.0/64; fake_stream[45] = 45.0/64;
  // Twenty-fourth bin
  fake_stream[46] = 46.0/64; fake_stream[47] = 47.0/64; 
  // Twenty-fifth bin
  fake_stream[48] = 48.0/64; fake_stream[49] = 49.0/64; 
  // Twenty-sixth bin
  fake_stream[50] = 50.0/64; fake_stream[51] = 51.0/64; 
  // Twenty-seventh bin
  fake_stream[52] = 52.0/64; fake_stream[53] = 53.0/64; 
  // Twenty-eighth bin
  fake_stream[54] = 54.0/64; fake_stream[55] = 55.0/64; 
  // Twenty-nineth bin
  fake_stream[56] = 56.0/64; fake_stream[57] = 57.0/64; 
  // Thirtieth bin
  fake_stream[58] = 58.0/64; fake_stream[59] = 59.0/64;
  // Thirty-first bin
  fake_stream[60] = 60.0/64; fake_stream[61] = 61.0/64; 
  // Thirty-second bin
  fake_stream[62] = 62.0/64; fake_stream[63] = 63.0/64; 
  fake_stream[64] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // First bin
  double sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -16.0 );
  
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -15.5 );

  // Second bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -15.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -14.5 );

  // Third bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -14.0 );
  
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -13.5 );

  // Fourth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -13.0 );
  
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -12.5 );

  // Fifth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -12.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -11.5 );

  // Sixth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -11.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -10.5 );

  // Seventh bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -10.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -9.5 );

  // Eighth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -9.0 );
  
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -8.5 );

  // Nineth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -8.0 );
  
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -7.5 );

  // Tenth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -7.0 );
  
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -6.5 );

  // Eleventh bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -6.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -5.5 );

  // Twelfth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -5.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -4.5 );

  // Thirteenth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -4.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -3.5 );

  // Fourteenth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -3.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -2.5 );

  // Fifteenth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -2.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -1.25 );

  // Sixteenth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -0.5 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, -0.25 );

  // Seventeenth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.25 );
  
  // Eighteenth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.5 );
  
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 1.25 );

  // Nineteenth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 2.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 2.5 );

  // Twentieth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 3.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 3.5 );

  // Twenty-first bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 4.0 );
  
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 4.5 );

  // Twenty-second bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 5.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 5.5 );

  // Twenty-third bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 6.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 6.5 );

  // Twenty-fourth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 7.0 );
  
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 7.5 );

  // Twenty-fifth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 8.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 8.5 );

  // Twenty-sixth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 9.0 );
  
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 9.5 );

  // Twenty-seventh bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 10.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 10.5 );
  
  // Twenty-eighth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 11.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 11.5 );

  // Twenty-nineth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 12.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 12.5 );

  // Thirtieth bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 13.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 13.5 );

  // Thirty-first bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 14.0 );
  
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 14.5 );

  // Thirty-second bin
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 15.0 );
  
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 15.5 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 16.0, 1e-14 );
}

//---------------------------------------------------------------------------//
// Check that the sampling efficiency can be returned
TEUCHOS_UNIT_TEST( ThirtyTwoEquiprobableBinDistribution, 
		   getSamplingEfficiency )
{
  TEST_EQUALITY_CONST( distribution->getSamplingEfficiency(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be 
// returned
TEUCHOS_UNIT_TEST( ThirtyTwoEquiprobableBinDistribution, 
		   getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(), 16.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( ThirtyTwoEquiprobableBinDistribution,
		   getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), -16.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( ThirtyTwoEquiprobableBinDistribution,
		   getDistributionType )
{
  TEST_EQUALITY_CONST( distribution->getDistributionType(),
		       Utility::THIRTY_TWO_EQUIPROBABLE_BIN_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// end tstThirtyTwoEquiprobableBinDistribution.cpp
//---------------------------------------------------------------------------//
