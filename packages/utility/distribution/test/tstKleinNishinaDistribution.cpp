//---------------------------------------------------------------------------//
//!
//! \file   tstKleinNishinaDistribution.cpp
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
#include "Utility_KleinNishinaDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Utility::KleinNishinaDistribution> distribution(
				new Utility::KleinNishinaDistribution( 1.0 ) );

Teuchos::RCP<Utility::OneDDistribution> base_distribution = distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the Koblinger cutoff energy can be returned
TEUCHOS_UNIT_TEST( KleinNishinaDistribution, getKoblingerCutoffEnergy )
{
  TEST_FLOATING_EQUALITY( 
		 Utility::KleinNishinaDistribution::getKoblingerCutoffEnergy(),
		 3.0,
		 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the integrated Klein-Nishina cross section can be evaluated
TEUCHOS_UNIT_TEST( KleinNishinaDistribution, 
		   evaluateIntegratedKleinNishinaCrossSection )
{
  double cross_section_value = 
    Utility::KleinNishinaDistribution::evaluateIntegratedKleinNishinaCrossSection( 1.0 );
  
  TEST_FLOATING_EQUALITY( cross_section_value,
			  2.8653991941448e-25,
			  1e-15 );			 
}

//---------------------------------------------------------------------------//
// Check that the approximate integrated Klein-Nishina cross section can be
// evaluated
TEUCHOS_UNIT_TEST( KleinNishinaDistribution,
		   evaluateApproximateIntegratedKleinNishinaCrossSection )
{
  double cross_section_value = 
    Utility::KleinNishinaDistribution::evaluateApproximateIntegratedKleinNishinaCrossSection( 1.0 );

  TEST_FLOATING_EQUALITY( cross_section_value,
			  2.8631802923437e-25,
			  1e-15 );	
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( KleinNishinaDistribution, evaluate )
{
  distribution->setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );

  TEST_EQUALITY_CONST( base_distribution->evaluate( 0.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( base_distribution->evaluate( 1.0 ), 
			  4.9893440508834e-25,
			  1e-15 );
  TEST_FLOATING_EQUALITY( base_distribution->evaluate( 3.0 ),
			  9.2395260201544e-26,
			  1e-15 );
  TEST_EQUALITY_CONST( base_distribution->evaluate( 4.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( KleinNishinaDistribution, evaluatePDF )
{
  // Use the exact integrated cross section
  distribution->setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );

  TEST_EQUALITY_CONST( base_distribution->evaluatePDF( 0.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( base_distribution->evaluatePDF( 1.0 ), 
			  1.7412387289976,
			  1e-12 );
  TEST_FLOATING_EQUALITY( base_distribution->evaluatePDF( 3.0 ),
			  0.32245161648103,
			  1e-12 );
  TEST_EQUALITY_CONST( base_distribution->evaluatePDF( 4.0 ), 0.0 );

  // Use the approximate integrated cross section
  base_distribution.reset( new Utility::KleinNishinaDistribution( 
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 false,
			 false ) );

  TEST_EQUALITY_CONST( base_distribution->evaluatePDF( 0.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( base_distribution->evaluatePDF( 1.0 ), 
			  1.7425881507445,
			  1e-12 );
  TEST_FLOATING_EQUALITY( base_distribution->evaluatePDF( 3.0 ),
			  0.32270150939713,
			  1e-12 );
  TEST_EQUALITY_CONST( base_distribution->evaluatePDF( 4.0 ), 0.0 );
  
  // Reset the base distribution
  base_distribution = distribution;
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( KleinNishinaDistribution, sample )
{
  distribution->setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );
  
  // Left branch of Kahn's method
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.27;
  fake_stream[1] = 0.25;
  fake_stream[2] = 0.90; // reject
  fake_stream[3] = 0.10;
  fake_stream[4] = 0.50;
  fake_stream[5] = 0.999;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = base_distribution->sample();

  TEST_EQUALITY_CONST( sample, 2.0 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();

  distribution->setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );

  // Right branch of Kahn's method
  fake_stream[0] = 0.273;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.459; // reject
  fake_stream[3] = 0.80;
  fake_stream[4] = 0.25;
  fake_stream[5] = 0.25;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = base_distribution->sample();

  TEST_EQUALITY_CONST( sample, 2.0 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();

  // Koblinger's Method
  distribution->setEnergy( 3.1 );

  fake_stream.resize( 8 );
  fake_stream[0] = 0.120;
  fake_stream[1] = 0.2;
  fake_stream[2] = 0.698;
  fake_stream[3] = 0.4;
  fake_stream[4] = 0.818;
  fake_stream[5] = 0.6;
  fake_stream[6] = 0.90;
  fake_stream[7] = 0.8;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Sample 1st term
  sample = base_distribution->sample();

  TEST_FLOATING_EQUALITY( sample, 3.426619656947095, 1e-12 );
  
  // Sample the 2nd term
  sample = base_distribution->sample();
  
  TEST_FLOATING_EQUALITY( sample, 2.8012178026643353, 1e-12 );
  
  // Sample the 3rd term
  sample = base_distribution->sample();

  TEST_FLOATING_EQUALITY( sample, 1.5861499973593234, 1e-12 );
  
  // Sample the 4th term
  sample = base_distribution->sample();

  TEST_FLOATING_EQUALITY( sample, 2.2105817334378988, 1e-12 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();

  // Koblinger's Method
  distribution->setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( KleinNishinaDistribution, sampleAndRecordTrials )
{
  distribution->setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );
  
  // Left branch of Kahn's method
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.27;
  fake_stream[1] = 0.25;
  fake_stream[2] = 0.90; // reject
  fake_stream[3] = 0.10;
  fake_stream[4] = 0.50;
  fake_stream[5] = 0.999;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0;

  double sample = base_distribution->sampleAndRecordTrials( trials );

  TEST_EQUALITY_CONST( sample, 2.0 );
  TEST_EQUALITY_CONST( 1.0/trials, 0.5 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  distribution->setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );

  // Right branch of Kahn's method
  fake_stream[0] = 0.273;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.459; // reject
  fake_stream[3] = 0.80;
  fake_stream[4] = 0.25;
  fake_stream[5] = 0.25;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = base_distribution->sampleAndRecordTrials( trials );

  TEST_EQUALITY_CONST( sample, 2.0 );
  TEST_EQUALITY_CONST( 2.0/trials, 0.5 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Koblinger's Method
  distribution->setEnergy( 3.1 );

  fake_stream.resize( 8 );
  fake_stream[0] = 0.120;
  fake_stream[1] = 0.2;
  fake_stream[2] = 0.698;
  fake_stream[3] = 0.4;
  fake_stream[4] = 0.818;
  fake_stream[5] = 0.6;
  fake_stream[6] = 0.90;
  fake_stream[7] = 0.8;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;
  
  // Sample 1st term
  sample = base_distribution->sampleAndRecordTrials( trials );

  TEST_FLOATING_EQUALITY( sample, 3.426619656947095, 1e-12 );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  // Sample the 2nd term
  sample = base_distribution->sampleAndRecordTrials( trials );
  
  TEST_FLOATING_EQUALITY( sample, 2.8012178026643353, 1e-12 );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  // Sample the 3rd term
  sample = base_distribution->sampleAndRecordTrials( trials );

  TEST_FLOATING_EQUALITY( sample, 1.5861499973593234, 1e-12 );
  TEST_EQUALITY_CONST( 3.0/trials, 1.0 );

  // Sample the 4th term
  sample = base_distribution->sampleAndRecordTrials( trials );

  TEST_FLOATING_EQUALITY( sample, 2.2105817334378988, 1e-12 );
  TEST_EQUALITY_CONST( 4.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( KleinNishinaDistribution, sampleOptimal )
{
  distribution->setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );
  
  unsigned trials;

  // Left branch of Kahn's method
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.27;
  fake_stream[1] = 0.25;
  fake_stream[2] = 0.90; // reject
  fake_stream[3] = 0.10;
  fake_stream[4] = 0.50;
  fake_stream[5] = 0.999;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = Utility::KleinNishinaDistribution::sampleOptimal( 
	       Utility::PhysicalConstants::electron_rest_mass_energy, trials );

  TEST_EQUALITY_CONST( sample, 2.0 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();

  // Right branch of Kahn's method
  fake_stream[0] = 0.273;
  fake_stream[1] = 0.5;
  fake_stream[2] = 0.459; // reject
  fake_stream[3] = 0.80;
  fake_stream[4] = 0.25;
  fake_stream[5] = 0.25;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  sample = Utility::KleinNishinaDistribution::sampleOptimal( 
	       Utility::PhysicalConstants::electron_rest_mass_energy, trials );

  TEST_EQUALITY_CONST( sample, 2.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Koblinger's Method
  fake_stream.resize( 8 );
  fake_stream[0] = 0.120;
  fake_stream[1] = 0.2;
  fake_stream[2] = 0.698;
  fake_stream[3] = 0.4;
  fake_stream[4] = 0.818;
  fake_stream[5] = 0.6;
  fake_stream[6] = 0.90;
  fake_stream[7] = 0.8;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  // Sample 1st term
  sample = Utility::KleinNishinaDistribution::sampleOptimal( 3.1, trials );

  TEST_FLOATING_EQUALITY( sample, 3.426619656947095, 1e-12 );

  // Sample the 2nd term
  sample = Utility::KleinNishinaDistribution::sampleOptimal( 3.1, trials );
  
  TEST_FLOATING_EQUALITY( sample, 2.8012178026643353, 1e-12 );

  // Sample the 3rd term
  sample = Utility::KleinNishinaDistribution::sampleOptimal( 3.1, trials );

  TEST_FLOATING_EQUALITY( sample, 1.5861499973593234, 1e-12 );

  // Sample the 4th term
  sample = Utility::KleinNishinaDistribution::sampleOptimal( 3.1, trials );

  TEST_FLOATING_EQUALITY( sample, 2.2105817334378988, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( KleinNishinaDistribution, getUpperBoundOfIndepVar )
{
  distribution->setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );
  
  TEST_EQUALITY_CONST( base_distribution->getUpperBoundOfIndepVar(), 3.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( KleinNishinaDistribution, getLowerBoundOfIndepVar )
{
  distribution->setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );

  
  TEST_EQUALITY_CONST( base_distribution->getLowerBoundOfIndepVar(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST( KleinNishinaDistribution, isTabular )
{
  TEST_ASSERT( !distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
TEUCHOS_UNIT_TEST( KleinNishinaDistribution, isContinuous )
{
  TEST_ASSERT( distribution->isContinuous() );
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
// end tstKleinNishinaDistribution.cpp
//---------------------------------------------------------------------------//
