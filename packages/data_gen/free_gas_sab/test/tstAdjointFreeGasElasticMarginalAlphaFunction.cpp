//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointFreeGasElasticMarginalAlphaFunction.cpp
//! \author Eli Moll
//! \brief  Free gas elastic marginal alpha function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "DataGen_AdjointFreeGasElasticMarginalAlphaFunction.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_KinematicHelpers.hpp"


//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<DataGen::AdjointFreeGasElasticMarginalAlphaFunction> alpha_function;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the alpha bounds can be returned
TEUCHOS_UNIT_TEST( AdjointFreeGasElasticMarginalAlphaFunction, getAlphaMin_Max )
{
  alpha_function->setIndependentVariables( -0.9, 2.53010e-8 );

  TEST_FLOATING_EQUALITY( alpha_function->getAlphaMin(),
			  0.14330962650083087,
			  1e-9 );

  TEST_FLOATING_EQUALITY( alpha_function->getAlphaMax(),
			  5.66152580141062,
			  1e-9 );
  
  alpha_function->setIndependentVariables( 0.0, 1e-6 );

  TEST_FLOATING_EQUALITY( alpha_function->getAlphaMin(),
			  0.0,
			  1e-12 );

  TEST_FLOATING_EQUALITY( alpha_function->getAlphaMax(),
			  158.22832211652,
			  1e-12 );

  alpha_function->setIndependentVariables( 1, 2.53010e-8 );

  TEST_FLOATING_EQUALITY( alpha_function->getAlphaMin(),
			  1.0008336944674914,
			  1e-12 );

  TEST_FLOATING_EQUALITY( alpha_function->getAlphaMax(),
			  1.0008336944674914,
			  1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( AdjointFreeGasElasticMarginalAlphaFunction, evaulatePDF )
{
  alpha_function->setIndependentVariables( -0.9, 2.53010e-8 );

  double pdf_value = (*alpha_function)( alpha_function->getAlphaMin() );

  TEST_ASSERT( pdf_value > 0.0 );
  
  pdf_value = (*alpha_function)( (alpha_function->getAlphaMin()+
				  alpha_function->getAlphaMax())/2 );
  
  TEST_ASSERT( pdf_value > 0.0 );

  pdf_value = (*alpha_function)( alpha_function->getAlphaMax() );
  
  TEST_ASSERT( pdf_value > 0.0 );
  
  alpha_function->setIndependentVariables( 0.0, 1e-6 );

  pdf_value = (*alpha_function)( alpha_function->getAlphaMin() );
  
  // alpha = 0.0 is the only value that will result in a pdf value of inf
  TEST_EQUALITY_CONST( pdf_value, 
		       std::numeric_limits<double>::infinity() );
  
  pdf_value = (*alpha_function)( (alpha_function->getAlphaMin()+
				  alpha_function->getAlphaMax())/2 );
  
  TEST_ASSERT( pdf_value > 0.0 );

  pdf_value = (*alpha_function)( alpha_function->getAlphaMax() );
  
  TEST_ASSERT( pdf_value > 0.0 );

  alpha_function->setIndependentVariables( 1e-6/2.53010e-8, 1e-6 );

  pdf_value = (*alpha_function)( alpha_function->getAlphaMin() );
  
  TEST_ASSERT( pdf_value > 0.0 );
  
  pdf_value = (*alpha_function)( (alpha_function->getAlphaMin()+
				  alpha_function->getAlphaMax())/2 );
  
  TEST_ASSERT( pdf_value > 0.0 );

  pdf_value = (*alpha_function)( alpha_function->getAlphaMax() );
  
  TEST_ASSERT( pdf_value > 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated
TEUCHOS_UNIT_TEST( AdjointFreeGasElasticMarginalAlphaFunction, evaluateCDF )
{
  alpha_function->setIndependentVariables( -9.9e-7/2.53010e-8, 1e-6 );

  double cdf_value = alpha_function->evaluateCDF( 
                alpha_function->getAlphaMin() );
  
  TEST_EQUALITY_CONST( cdf_value, 0.0 );

  cdf_value = alpha_function->evaluateCDF( (alpha_function->getAlphaMin()+
              alpha_function->getAlphaMax())/2 );
  
  TEST_ASSERT( cdf_value > 0.0 );
  TEST_ASSERT( cdf_value < 1.0 );

  cdf_value = alpha_function->evaluateCDF( alpha_function->getAlphaMax()-1e-6);

  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-6 );

  cdf_value = alpha_function->evaluateCDF( alpha_function->getAlphaMax() );
  
  TEST_EQUALITY_CONST( cdf_value, 1.0 );

  alpha_function->setIndependentVariables( 0.0, 1e-6 );

  cdf_value = alpha_function->evaluateCDF( alpha_function->getAlphaMin() );
  
  TEST_EQUALITY_CONST( cdf_value, 0.0 );

  cdf_value = alpha_function->evaluateCDF( (alpha_function->getAlphaMin()+
              alpha_function->getAlphaMax())/2 );
  
  TEST_ASSERT( cdf_value > 0.0 );
  TEST_ASSERT( cdf_value < 1.0 );

  cdf_value = alpha_function->evaluateCDF( alpha_function->getAlphaMax()-1e-6);

  TEST_FLOATING_EQUALITY( cdf_value, 1.0, 1e-6 );

  cdf_value = alpha_function->evaluateCDF( alpha_function->getAlphaMax()-1e-6 );
  
  TEST_EQUALITY_CONST( cdf_value, 1.0 );

  alpha_function->setIndependentVariables( 1e-6/2.53010e-8, 1e-6 );

  cdf_value = alpha_function->evaluateCDF( alpha_function->getAlphaMin() );
  
  TEST_EQUALITY_CONST( cdf_value, 1.0 );
 
  cdf_value = alpha_function->evaluateCDF( (alpha_function->getAlphaMin()+
					    alpha_function->getAlphaMax())/2 );
  
  TEST_EQUALITY_CONST( cdf_value, 1.0 );

  cdf_value = alpha_function->evaluateCDF( alpha_function->getAlphaMax() );
  
  TEST_EQUALITY_CONST( cdf_value, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated
TEUCHOS_UNIT_TEST( AdjointFreeGasElasticMarginalAlphaFunction, assessNormalization )
{
  std::vector<double> beta_vector;
  double beta_max = Utility::calculateAdjointBetaMax( 2.53010e-8, 2.53010e-8 );
  double beta_min = -5*beta_max;
  double num_points = 1001;
  double beta_spacing = (beta_max - beta_min)/(num_points - 1);

  for (int i = 0; i < num_points; ++i)
  {
    beta_vector.push_back(beta_min + i* beta_spacing);
  }

  for (int i = 0; i < num_points; ++i)
  {
    alpha_function->setIndependentVariables( beta_vector[i], 2.53010e-8 );
    //std::cout << beta_vector[i] + 1 << " " << alpha_function->getNormalizationConstant() << std::endl;
  }
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated
TEUCHOS_UNIT_TEST( AdjointFreeGasElasticMarginalAlphaFunction, assessPDF )
{
  double beta = -0.5; 
  alpha_function->setIndependentVariables( beta, 2.53010e-8 );

  double alpha_min = Utility::calculateAdjointAlphaMin( 2.53010e-8, beta, 0.999167, 2.53010e-8 );
  double alpha_max = Utility::calculateAdjointAlphaMax( 2.53010e-8, beta, 0.999167, 2.53010e-8 );
  double alpha_space = (alpha_max - alpha_min)/(1000);

  for (int i = 0; i < 1001; ++i)
  {
    const double alpha_value = alpha_min + i*alpha_space;
    //std::cout << alpha_function->operator()(alpha_value) << std::endl;
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

  // Initialize the zero temperature cross section
  Teuchos::RCP<Utility::OneDDistribution> cross_section(
			  new Utility::UniformDistribution( 0.0, 20.0, 1.0 ) );

  // Initialize the scattering probability distribution
  Teuchos::RCP<Utility::TabularOneDDistribution> isotropic_distribution(
			  new Utility::UniformDistribution( -1.0, 1.0, 0.5 ) );

  // Initialize the scattering distribution
  MonteCarlo::NuclearScatteringAngularDistribution::AngularDistribution
    distribution( 2 );

  distribution[0].first = 0.0;
  distribution[0].second = isotropic_distribution;
  
  distribution[1].first = 20.0;
  distribution[1].second = isotropic_distribution;

  Teuchos::RCP<MonteCarlo::NuclearScatteringAngularDistribution> 
    scattering_distribution( 
			 new MonteCarlo::NuclearScatteringAngularDistribution(
							      distribution ) );

  // Initialize the gkq_set factor
  alpha_function.reset( new DataGen::AdjointFreeGasElasticMarginalAlphaFunction(
						    cross_section, 
						    scattering_distribution,
						    0.999167,
						    2.53010e-8,
						    0.0,
						    1.0e-06 ) );

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
// end tstFreeGasElasticMarginalAlphaFunction.cpp
//---------------------------------------------------------------------------//
