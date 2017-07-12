//---------------------------------------------------------------------------//
//!
//! \file   tstElasticElectronDistribution.cpp
//! \author Luke Kersting
//! \brief  ElasticElectron distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>

// FRENSIE Includes
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_ElasticElectronDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::shared_ptr<Utility::PropertyTree> test_dists_ptree;

std::shared_ptr<Utility::OneDDistribution> distribution;
std::shared_ptr<Utility::TabularOneDDistribution> tab_distribution;

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name )				\
  typedef Utility::LinLin LinLin;					\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, LinLin )

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize the distribution
template<typename InterpolationPolicy>
void initializeACEDistribution()
{
  std::vector<double> independent_values( 3 );
  independent_values[0] = -1.0;
  independent_values[1] = 0.999999;
  independent_values[2] = 1.0;

  std::vector<double> dependent_values( 3 );
  dependent_values[0] = 0.0;
  dependent_values[1] = 0.9999995;
  dependent_values[2] = 1.0;

  double energy = 1.0e-5;

  tab_distribution.reset(new Utility::ElasticElectronDistribution<InterpolationPolicy>(
							  independent_values,
							  dependent_values,
                              energy,
                              82 ) );
  distribution = tab_distribution;
}

// Initialize the distribution
template<typename InterpolationPolicy>
void initializeENDLDistribution()
{
  std::vector<double> independent_values( 3 );
  independent_values[2] = 2.0;
  independent_values[1] = 1.0E-6;
  independent_values[0] = 0.0;

  std::vector<double> dependent_values( 3 );
  dependent_values[2] = 5.0000000019895100E-01;
  dependent_values[1] = 4.9999999980104900E-01;
  dependent_values[0] = 5.0000000019895100E-01;

  double eta = 2.51317958942017E+03;
  double A = 3158035.826;

  tab_distribution.reset(new Utility::ElasticElectronDistribution<InterpolationPolicy>(
							  independent_values,
							  dependent_values,
                              eta,
                              A ) );

  distribution = tab_distribution;
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
				   evaluate,
				   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  TEST_EQUALITY_CONST( distribution->evaluate( 3.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 2.0 ),
                          5.0000000019895100E-01,
                          1e-10 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 0.000001 ),
                          4.9999999980104900E-01,
                          1e-10 );
  TEST_FLOATING_EQUALITY( distribution->evaluate( 0.0 ),
                          5.0000000019895100E-01,
                          1e-10 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0 ), 0.0 );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, evaluate );

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
				   evaluatePDF,
				   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  TEST_EQUALITY_CONST( distribution->evaluatePDF( 3.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( distribution->evaluatePDF( 2.0 ),
                          5.0000000019895100E-01,
                          1e-10 );
  TEST_FLOATING_EQUALITY( distribution->evaluatePDF( 0.000001 ),
                          4.9999999980104900E-01,
                          1e-10 );
  TEST_FLOATING_EQUALITY( distribution->evaluatePDF( 0.0 ),
                          5.0000000019895100E-01,
                          1e-10 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -1.0 ), 0.0 );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, evaluatePDF );

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
				   evaluateCDF,
				   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 3.0 ), 1.0 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 2.0 ),
			  1.0000000000,
			  1e-10 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 0.000001 ),
			  0.0000005000,
			  1e-10 );
  TEST_FLOATING_EQUALITY( tab_distribution->evaluateCDF( 0.0 ),
			  0.0000000000,
			  1e-10 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -1.0 ), 0.0 );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, evaluateCDF );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
                                   sample,
                                   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = distribution->sample();
  TEST_COMPARE( sample, >=, 0.0 );
  TEST_COMPARE( sample, <=, 2.0 );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, sample );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
                                   sampleAndRecordTrials,
                                   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::DistributionTraits::Counter trials = 0;

  double sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-12 );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_COMPARE( sample, >=, 0.0 );
  TEST_COMPARE( sample, <=, 2.0 );
  TEST_EQUALITY_CONST( 3.0/trials, 1.0 );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, sampleAndRecordTrials );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
                                   sampleAndRecordBinIndex,
                                   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned bin_index;

  double sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( bin_index, 0u );

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-12 );
  TEST_EQUALITY_CONST( bin_index, 1u );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = tab_distribution->sampleAndRecordBinIndex( bin_index );
  TEST_COMPARE( sample, >=, 0.0 );
  TEST_COMPARE( sample, <=, 2.0 );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, sampleAndRecordBinIndex );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
                                   sampleWithRandomNumber,
                                   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  double sample = tab_distribution->sampleWithRandomNumber( 0.0 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleWithRandomNumber( 1.0 - 1e-15 );
  TEST_FLOATING_EQUALITY( sample, 2.0, 1e-12 );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, sampleWithRandomNumber );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from a subrange
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
                                   sampleInSubrange,
                                   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  std::vector<double> fake_stream( 2 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 1.0 - 1e-15;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = tab_distribution->sampleInSubrange( 0.000001 );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleInSubrange( 0.000001 );
  TEST_FLOATING_EQUALITY( sample, 0.000001, 1e-12 );

  Utility::RandomNumberGenerator::unsetFakeStream();
  Utility::RandomNumberGenerator::initialize();

  sample = tab_distribution->sampleInSubrange( 0.000001 );
  TEST_COMPARE( sample, >=, 0.0 );
  TEST_COMPARE( sample, <=, 0.000001 );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, sampleInSubrange );

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from a subrange
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
                                   sampleWithRandomNumberInSubrange,
                                   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  double sample =
    tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 0.000001  );
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample =
        tab_distribution->sampleWithRandomNumberInSubrange( 1.0, 0.000001 );
  TEST_FLOATING_EQUALITY( sample, 0.000001, 1e-12 );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution,
			 sampleWithRandomNumberInSubrange );

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
				   getUpperBoundOfIndepVar,
				   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(), 2.0 );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, getUpperBoundOfIndepVar );

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
				   getLowerBoundOfIndepVar,
				   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), 0.0 );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, getLowerBoundOfIndepVar );

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
				   getDistributionType,
				   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  TEST_EQUALITY_CONST( distribution->getDistributionType(),
		       Utility::ELASTIC_ELECTRON_DISTRIBUTION );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, getDistributionType );

//---------------------------------------------------------------------------//
// Check if the distribution is elastic electron
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
				   isTabular,
				   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  TEST_ASSERT( distribution->isTabular() );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, isTabular );

//---------------------------------------------------------------------------//
// Check that the distribution is continuous
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
				   isContinuous,
				   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  TEST_ASSERT( distribution->isContinuous() );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, isContinuous );

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
                                   isCompatibleWithInterpType,
                                   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  if( boost::is_same<InterpolationPolicy,Utility::LinLin>::value )
  {
    TEST_ASSERT( distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  }
  else
  {
    TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  }

  if( boost::is_same<InterpolationPolicy,Utility::LinLog>::value )
  {
    TEST_ASSERT( distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  }
  else
  {
    TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  }

  if( boost::is_same<InterpolationPolicy,Utility::LogLin>::value )
  {
    TEST_ASSERT( distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  }
  else
  {
    TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  }

  if( boost::is_same<InterpolationPolicy,Utility::LogLog>::value )
  {
    TEST_ASSERT( distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  }
  else
  {
    TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );
  }
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution,
                         isCompatibleWithInterpType );

//---------------------------------------------------------------------------//
// Check that the distribution can be converted to a string
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
                                   toString,
                                   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  std::string dist_name = "{Elastic Electron Distribution ";
  dist_name += InterpolationPolicy::name();
    
  std::string dist_string = Utility::toString( *distribution );
  
  TEST_EQUALITY_CONST( dist_string, dist_name + ", {0.000000000000000000e+00, 1.000000000028755665e-06, 2.000000000000000000e+00}, {5.000000001578178699e-01, 4.999999997599156032e-01, 5.000000002400846189e-01}, 2.513179589420172761e+03, 3.158035825335863046e+06}" );

  initializeENDLDistribution<InterpolationPolicy>();

  dist_string = Utility::toString( *distribution );
  
  TEST_EQUALITY_CONST( dist_string, dist_name + ", {0.000000000000000000e+00, 9.999999999999999547e-07, 2.000000000000000000e+00}, {5.000000001989509668e-01, 4.999999998010489777e-01, 5.000000001989509668e-01}, 2.513179589420170032e+03, 3.158035825999999885e+06}" );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, toString );

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
                                   toStream,
                                   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  std::string dist_name = "{Elastic Electron Distribution ";
  dist_name += InterpolationPolicy::name();
  
  std::ostringstream oss;

  Utility::toStream( oss, *distribution );

  TEST_EQUALITY_CONST( oss.str(), dist_name + ", {0.000000000000000000e+00, 1.000000000028755665e-06, 2.000000000000000000e+00}, {5.000000001578178699e-01, 4.999999997599156032e-01, 5.000000002400846189e-01}, 2.513179589420172761e+03, 3.158035825335863046e+06}" );

  initializeENDLDistribution<InterpolationPolicy>();

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, *distribution );
  
  TEST_EQUALITY_CONST( oss.str(), dist_name + ", {0.000000000000000000e+00, 9.999999999999999547e-07, 2.000000000000000000e+00}, {5.000000001989509668e-01, 4.999999998010489777e-01, 5.000000001989509668e-01}, 2.513179589420170032e+03, 3.158035825999999885e+06}" );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, toStream );

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
                                   ostream_operator,
                                   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();

  std::string dist_name = "{Elastic Electron Distribution ";
  dist_name += InterpolationPolicy::name();
  
  std::ostringstream oss;

  oss << *distribution;

  TEST_EQUALITY_CONST( oss.str(), dist_name + ", {0.000000000000000000e+00, 1.000000000028755665e-06, 2.000000000000000000e+00}, {5.000000001578178699e-01, 4.999999997599156032e-01, 5.000000002400846189e-01}, 2.513179589420172761e+03, 3.158035825335863046e+06}" );

  initializeENDLDistribution<InterpolationPolicy>();

  oss.str( "" );
  oss.clear();

  oss << *distribution;
  
  TEST_EQUALITY_CONST( oss.str(), dist_name + ", {0.000000000000000000e+00, 9.999999999999999547e-07, 2.000000000000000000e+00}, {5.000000001989509668e-01, 4.999999998010489777e-01, 5.000000001989509668e-01}, 2.513179589420170032e+03, 3.158035825999999885e+06}" );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, ostream_operator );

//---------------------------------------------------------------------------//
// Check that the distribution can be initialized from a string
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
                                   fromString,
                                   InterpolationPolicy )
{
  std::string dist_rep = "{Elastic Electron Distribution ";
  dist_rep += InterpolationPolicy::name();
  dist_rep += ", {0.000000000000000000e+00, 1.000000000028755665e-06, 2.000000000000000000e+00}, {5.000000001578178699e-01, 4.999999997599156032e-01, 5.000000002400846189e-01}, 2.513179589420172761e+03, 3.158035825335863046e+06}";
    
  Utility::ElasticElectronDistribution<InterpolationPolicy> test_dist =
    Utility::fromString<Utility::ElasticElectronDistribution<InterpolationPolicy> >( dist_rep );

  TEST_EQUALITY_CONST( test_dist.evaluate( 3.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( test_dist.evaluate( 2.0 ),
                          5.0000000019895100E-01,
                          1e-10 );
  TEST_FLOATING_EQUALITY( test_dist.evaluate( 0.000001 ),
                          4.9999999980104900E-01,
                          1e-10 );
  TEST_FLOATING_EQUALITY( test_dist.evaluate( 0.0 ),
                          5.0000000019895100E-01,
                          1e-10 );
  TEST_EQUALITY_CONST( test_dist.evaluate( -1.0 ), 0.0 );

  // Check for robust type name handling
  dist_rep = "{";
  dist_rep += boost::algorithm::to_lower_copy( InterpolationPolicy::name() );
  dist_rep += " ";
  dist_rep += "elastic electron";
  dist_rep += ", {0.000000000000000000e+00, 1.000000000028755665e-06, 2.000000000000000000e+00}, {5.000000001578178699e-01, 4.999999997599156032e-01, 5.000000002400846189e-01}, 2.513179589420172761e+03, 3.158035825335863046e+06}";
    
  TEST_NOTHROW( Utility::fromString<Utility::ElasticElectronDistribution<InterpolationPolicy> >( dist_rep ) );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, fromString );

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a stream
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
                                   fromStream,
                                   InterpolationPolicy )
{
  std::istringstream iss;

  {
    std::string dist_rep = "{Elastic Electron Distribution ";
    dist_rep += InterpolationPolicy::name();
    dist_rep += ", {0.000000000000000000e+00, 1.000000000028755665e-06, 2.000000000000000000e+00}, {5.000000001578178699e-01, 4.999999997599156032e-01, 5.000000002400846189e-01}, 2.513179589420172761e+03, 3.158035825335863046e+06}";

    iss.str( dist_rep );
  }
    
  Utility::ElasticElectronDistribution<InterpolationPolicy> test_dist;

  Utility::fromStream( iss, test_dist );

  TEST_EQUALITY_CONST( test_dist.evaluate( 3.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( test_dist.evaluate( 2.0 ),
                          5.0000000019895100E-01,
                          1e-10 );
  TEST_FLOATING_EQUALITY( test_dist.evaluate( 0.000001 ),
                          4.9999999980104900E-01,
                          1e-10 );
  TEST_FLOATING_EQUALITY( test_dist.evaluate( 0.0 ),
                          5.0000000019895100E-01,
                          1e-10 );
  TEST_EQUALITY_CONST( test_dist.evaluate( -1.0 ), 0.0 );

  // Check for robust type name handling
  {
    std::string dist_rep = "{";
    dist_rep += boost::algorithm::to_lower_copy( InterpolationPolicy::name() );
    dist_rep += " ";
    dist_rep += "elastic electron";
    dist_rep += ", {0.000000000000000000e+00, 1.000000000028755665e-06, 2.000000000000000000e+00}, {5.000000001578178699e-01, 4.999999997599156032e-01, 5.000000002400846189e-01}, 2.513179589420172761e+03, 3.158035825335863046e+06}";

    iss.str( dist_rep );
    iss.clear();
  }

  TEST_NOTHROW( Utility::fromStream( iss, test_dist ) );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, fromStream );

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a stream
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
                                   istream_operator,
                                   InterpolationPolicy )
{
  std::istringstream iss;

  {
    std::string dist_rep = "{Elastic Electron Distribution ";
    dist_rep += InterpolationPolicy::name();
    dist_rep += ", {0.000000000000000000e+00, 1.000000000028755665e-06, 2.000000000000000000e+00}, {5.000000001578178699e-01, 4.999999997599156032e-01, 5.000000002400846189e-01}, 2.513179589420172761e+03, 3.158035825335863046e+06}";

    iss.str( dist_rep );
  }
    
  Utility::ElasticElectronDistribution<InterpolationPolicy> test_dist;

  iss >> test_dist;

  TEST_EQUALITY_CONST( test_dist.evaluate( 3.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( test_dist.evaluate( 2.0 ),
                          5.0000000019895100E-01,
                          1e-10 );
  TEST_FLOATING_EQUALITY( test_dist.evaluate( 0.000001 ),
                          4.9999999980104900E-01,
                          1e-10 );
  TEST_FLOATING_EQUALITY( test_dist.evaluate( 0.0 ),
                          5.0000000019895100E-01,
                          1e-10 );
  TEST_EQUALITY_CONST( test_dist.evaluate( -1.0 ), 0.0 );

  // Check for robust type name handling
  {
    std::string dist_rep = "{";
    dist_rep += boost::algorithm::to_lower_copy( InterpolationPolicy::name() );
    dist_rep += " ";
    dist_rep += "elastic electron";
    dist_rep += ", {0.000000000000000000e+00, 1.000000000028755665e-06, 2.000000000000000000e+00}, {5.000000001578178699e-01, 4.999999997599156032e-01, 5.000000002400846189e-01}, 2.513179589420172761e+03, 3.158035825335863046e+06}";

    iss.str( dist_rep );
    iss.clear();
  }

  TEST_NOTHROW( iss >> test_dist );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, istream_operator );

//---------------------------------------------------------------------------//
// Check that the distribution can be written to a property tree node
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
                                   toNode,
                                   InterpolationPolicy )
{
  initializeACEDistribution<InterpolationPolicy>();
  
  // Use the property tree interface directly
  Utility::PropertyTree ptree;

  ptree.put( "test distribution", *distribution );

  Utility::ElasticElectronDistribution<InterpolationPolicy> copy_dist =
    ptree.get<Utility::ElasticElectronDistribution<InterpolationPolicy> >( "test distribution" );
  
  TEST_EQUALITY_CONST( copy_dist.evaluate( 3.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( copy_dist.evaluate( 2.0 ),
                          5.0000000019895100E-01,
                          1e-10 );
  TEST_FLOATING_EQUALITY( copy_dist.evaluate( 0.000001 ),
                          4.9999999980104900E-01,
                          1e-10 );
  TEST_FLOATING_EQUALITY( copy_dist.evaluate( 0.0 ),
                          5.0000000019895100E-01,
                          1e-10 );
  TEST_EQUALITY_CONST( copy_dist.evaluate( -1.0 ), 0.0 );

  ptree.put( "test distribution", *tab_distribution );

  copy_dist = ptree.get<Utility::ElasticElectronDistribution<InterpolationPolicy> >( "test distribution" );

  TEST_EQUALITY_CONST( copy_dist.evaluate( 3.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( copy_dist.evaluate( 2.0 ),
                          5.0000000019895100E-01,
                          1e-10 );
  TEST_FLOATING_EQUALITY( copy_dist.evaluate( 0.000001 ),
                          4.9999999980104900E-01,
                          1e-10 );
  TEST_FLOATING_EQUALITY( copy_dist.evaluate( 0.0 ),
                          5.0000000019895100E-01,
                          1e-10 );
  TEST_EQUALITY_CONST( copy_dist.evaluate( -1.0 ), 0.0 );

  // Use the PropertyTreeCompatibleObject interface
  distribution->toNode( "test distribution", ptree, true );

  TEST_EQUALITY_CONST( ptree.get_child( "test distribution" ).size(), 0 );

  copy_dist = ptree.get<Utility::ElasticElectronDistribution<InterpolationPolicy> >( "test distribution" );

  TEST_EQUALITY_CONST( copy_dist.evaluate( 3.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( copy_dist.evaluate( 2.0 ),
                          5.0000000019895100E-01,
                          1e-10 );
  TEST_FLOATING_EQUALITY( copy_dist.evaluate( 0.000001 ),
                          4.9999999980104900E-01,
                          1e-10 );
  TEST_FLOATING_EQUALITY( copy_dist.evaluate( 0.0 ),
                          5.0000000019895100E-01,
                          1e-10 );
  TEST_EQUALITY_CONST( copy_dist.evaluate( -1.0 ), 0.0 );

  distribution->toNode( "test distribution", ptree, false );

  TEST_EQUALITY_CONST( ptree.get_child( "test distribution" ).size(), 5 );
  TEST_EQUALITY_CONST( ptree.get_child( "test distribution" ).get<std::string>( "type" ), "Elastic Electron Distribution " + InterpolationPolicy::name() );
  TEST_COMPARE_FLOATING_CONTAINERS( ptree.get_child( "test distribution" ).get<std::vector<double> >( "independent values" ),
                                    std::vector<double>({0.0, 1e-6, 2.0}),
                                    1e-10 );
  TEST_COMPARE_FLOATING_CONTAINERS( ptree.get_child( "test distribution" ).get<std::vector<double> >( "dependent values" ),
                                    std::vector<double>({5.0000000019895100E-01, 4.9999999980104900E-01, 5.0000000019895100E-01}),
                                    1e-10 );
  TEST_FLOATING_EQUALITY( ptree.get_child( "test distribution" ).get<double>( "moliere screening constant" ),
                          2.513179589420172761e+03,
                          1e-15 );
  TEST_FLOATING_EQUALITY( ptree.get_child( "test distribution" ).get<double>( "screened rutherford norm constant" ),
                          3.158035825335863046e+06,
                          1e-15 );
}

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, toNode );

//---------------------------------------------------------------------------//
// Check that the distribution can be read from a property tree node
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( ElasticElectronDistribution,
                                   fromNode,
                                   InterpolationPolicy )
{
  Utility::ElasticElectronDistribution<InterpolationPolicy> dist;

  std::vector<std::string> unused_children;

  dist.fromNode( test_dists_ptree->get_child( "Elastic Electron Distribution A" ),
                 unused_children );

  TEST_EQUALITY_CONST( unused_children.size(), 0 );
  TEST_EQUALITY_CONST( dist.evaluate( 3.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( dist.evaluate( 2.0 ),
                          5.0000000019895100E-01,
                          1e-10 );
  TEST_FLOATING_EQUALITY( dist.evaluate( 0.000001 ),
                          4.9999999980104900E-01,
                          1e-10 );
  TEST_FLOATING_EQUALITY( dist.evaluate( 0.0 ),
                          5.0000000019895100E-01,
                          1e-10 );
  TEST_EQUALITY_CONST( dist.evaluate( -1.0 ), 0.0 );

  dist.fromNode( test_dists_ptree->get_child( "Elastic Electron Distribution B" ),
                 unused_children );
  
  TEST_EQUALITY_CONST( unused_children.size(), 0 );
  TEST_EQUALITY_CONST( dist.evaluate( 3.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( dist.evaluate( 2.0 ),
                          5.0000000019895100E-01,
                          1e-10 );
  TEST_FLOATING_EQUALITY( dist.evaluate( 0.000001 ),
                          4.9999999980104900E-01,
                          1e-10 );
  TEST_FLOATING_EQUALITY( dist.evaluate( 0.0 ),
                          5.0000000019895100E-01,
                          1e-10 );
  TEST_EQUALITY_CONST( dist.evaluate( -1.0 ), 0.0 );

  dist.fromNode( test_dists_ptree->get_child( "Elastic Electron Distribution C" ),
                 unused_children );
  
  TEST_EQUALITY_CONST( unused_children.size(), 1 );
  TEST_EQUALITY_CONST( unused_children.front(), "dummy" );
  TEST_EQUALITY_CONST( dist.evaluate( 3.0 ), 0.0 );
  TEST_FLOATING_EQUALITY( dist.evaluate( 2.0 ),
                          5.0000000019895100E-01,
                          1e-10 );
  TEST_FLOATING_EQUALITY( dist.evaluate( 0.000001 ),
                          4.9999999980104900E-01,
                          1e-10 );
  TEST_FLOATING_EQUALITY( dist.evaluate( 0.0 ),
                          5.0000000019895100E-01,
                          1e-10 );
  TEST_EQUALITY_CONST( dist.evaluate( -1.0 ), 0.0 );

  TEST_THROW( dist.fromNode( test_dists_ptree->get_child( "Elastic Electron Distribution D" ) ),
              Utility::PTreeNodeConversionException );
  TEST_THROW( dist.fromNode( test_dists_ptree->get_child( "Elastic Electron Distribution E" ) ),
              Utility::PTreeNodeConversionException );
  TEST_THROW( dist.fromNode( test_dists_ptree->get_child( "Elastic Electron Distribution F" ) ),
              Utility::PTreeNodeConversionException );
  TEST_THROW( dist.fromNode( test_dists_ptree->get_child( "Elastic Electron Distribution G" ) ),
              Utility::PTreeNodeConversionException );
  TEST_THROW( dist.fromNode( test_dists_ptree->get_child( "Elastic Electron Distribution H" ) ),
              Utility::PTreeNodeConversionException );
} 

UNIT_TEST_INSTANTIATION( ElasticElectronDistribution, fromNode );

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_dists_json_file_name;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_dists_json_file",
                   &test_dists_json_file_name,
                   "Test distributions json file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  // Load the property tree from the json file
  test_dists_ptree.reset( new Utility::PropertyTree );

  std::ifstream test_dists_json_file( test_dists_json_file_name );

  test_dists_json_file >> *test_dists_ptree;

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstElasticElectronDistribution.cpp
//---------------------------------------------------------------------------//
