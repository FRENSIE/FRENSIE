//---------------------------------------------------------------------------//
//!
//! \file   tstPolynomialDistribution.cpp
//! \author Alex Robinson
//! \brief  Polynomial distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_PolynomialDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_ElectronVoltUnit.hpp"

using boost::units::quantity;
using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Teuchos::ParameterList> test_dists_list;

Teuchos::RCP<Utility::OneDDistribution> distribution;

Teuchos::RCP<Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount> >
  unit_aware_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( PolynomialDistribution, evaluate )
{
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.5 ), 2.75 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), 6.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwarePolynomialDistribution, evaluate )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( -1.0*MeV ),
		       0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV ),
		       1.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.5*MeV ),
		       2.75*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.0*MeV ),
		       6.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 2.0*MeV ),
		       0.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( PolynomialDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.0 ), 1.0/3.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.5 ), 2.75/3.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 1.0 ), 2.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 2.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwarePolynomialDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( -1.0*MeV ),
		       0.0/MeV );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 0.0*MeV ),
		       (1.0/3.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 0.5*MeV ),
		       (2.75/3.0)/MeV );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 1.0*MeV ),
		       2.0/MeV );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 2.0*MeV ),
		       0.0/MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( PolynomialDistribution, sample )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  double sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.5 );

  fake_stream[0] = 0.5;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, sqrt(0.5) );

  fake_stream[0] = 0.7;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.7;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = distribution->sample();
  TEST_EQUALITY_CONST( sample, pow( 0.5, 1.0/3.0 ) );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwarePolynomialDistribution, sample )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  quantity<MegaElectronVolt> sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0*MeV );

  sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.5*MeV );

  fake_stream[0] = 0.5;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0*MeV );

  sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, sqrt(0.5)*MeV );

  fake_stream[0] = 0.7;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.7;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );
  sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, 0.0*MeV );

  sample = unit_aware_distribution->sample();
  TEST_EQUALITY_CONST( sample, pow( 0.5, (1.0/3.0) )*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( PolynomialDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0;

  double sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.5 );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  fake_stream[0] = 0.5;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, sqrt(0.5) );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  fake_stream[0] = 0.7;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.7;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, pow( 0.5, 1.0/3.0 ) );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwarePolynomialDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0;

  quantity<MegaElectronVolt> sample =
    unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0*MeV );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.5*MeV );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  fake_stream[0] = 0.5;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0*MeV );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, sqrt(0.5)*MeV );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );

  fake_stream[0] = 0.7;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.7;
  fake_stream[3] = 0.5;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  trials = 0;

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, 0.0*MeV );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  TEST_EQUALITY_CONST( sample, pow( 0.5, 1.0/3.0 )*MeV );
  TEST_EQUALITY_CONST( 2.0/trials, 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( PolynomialDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
TEUCHOS_UNIT_TEST( UnitAwarePolynomialDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfIndepVar(),
		       1.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent
// variable can be returned
TEUCHOS_UNIT_TEST( UnitAwarePolynomialDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfIndepVar(),
		       0.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( PolynomialDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( distribution->getDistributionType(),
		       Utility::POLYNOMIAL_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
TEUCHOS_UNIT_TEST( UnitAwarePolynomialDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getDistributionType(),
		       Utility::POLYNOMIAL_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST( PolynomialDistribution, isTabular )
{
  TEST_ASSERT( !distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular
TEUCHOS_UNIT_TEST( UnitAwarePolynomialDistribution, isTabular )
{
  TEST_ASSERT( !unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
TEUCHOS_UNIT_TEST( PolynomialDistribution, isContinuous )
{
  TEST_ASSERT( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is continuous
TEUCHOS_UNIT_TEST( UnitAwarePolynomialDistribution, isContinuous )
{
  TEST_ASSERT( unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to and read from an xml file
TEUCHOS_UNIT_TEST( PolynomialDistribution, toParameterList )
{
  Teuchos::RCP<Utility::PolynomialDistribution> true_distribution =
    Teuchos::rcp_dynamic_cast<Utility::PolynomialDistribution>( distribution );

  Teuchos::ParameterList parameter_list;

  parameter_list.set<Utility::PolynomialDistribution>( "test_distribution",
						       *true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
					"polynomial_dist_test_list.xml" );

  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list =
    Teuchos::getParametersFromXmlFile( "polynomial_dist_test_list.xml" );

  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<Utility::PolynomialDistribution>
    copy_distribution( new Utility::PolynomialDistribution );

  *copy_distribution =
    read_parameter_list->get<Utility::PolynomialDistribution>(
							 "test_distribution" );
  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be written to and read from an
// xml file
TEUCHOS_UNIT_TEST( UnitAwarePolynomialDistribution, toParameterList )
{
  typedef Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount> UnitAwarePolynomialDistribution;

  Teuchos::RCP<UnitAwarePolynomialDistribution> true_distribution =
    Teuchos::rcp_dynamic_cast<UnitAwarePolynomialDistribution>( unit_aware_distribution );

  Teuchos::ParameterList parameter_list;

  parameter_list.set<UnitAwarePolynomialDistribution>( "test_distribution",
						       *true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
					"unit_aware_polynomial_dist_test_list.xml" );

  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list =
    Teuchos::getParametersFromXmlFile( "unit_aware_polynomial_dist_test_list.xml" );

  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<UnitAwarePolynomialDistribution>
    copy_distribution( new UnitAwarePolynomialDistribution );

  *copy_distribution =
    read_parameter_list->get<UnitAwarePolynomialDistribution>(
							 "test_distribution" );
  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be read from an xml file
TEUCHOS_UNIT_TEST( PolynomialDistribution, fromParameterList )
{
  Utility::PolynomialDistribution read_distribution =
    test_dists_list->get<Utility::PolynomialDistribution>( "Polynomial Distribution A" );

  TEST_EQUALITY_CONST( read_distribution.getLowerBoundOfIndepVar(), 0.0 );
  TEST_EQUALITY_CONST( read_distribution.getUpperBoundOfIndepVar(), 1.0 );

  read_distribution =
    test_dists_list->get<Utility::PolynomialDistribution>( "Polynomial Distribution B" );

  TEST_EQUALITY_CONST( read_distribution.getLowerBoundOfIndepVar(), 0.0 );
  TEST_EQUALITY_CONST( read_distribution.getUpperBoundOfIndepVar(),
		       Utility::PhysicalConstants::pi/2 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be read from an xml file
TEUCHOS_UNIT_TEST( UnitAwarePolynomialDistribution, fromParameterList )
{
  typedef Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount> UnitAwarePolynomialDistribution;

  UnitAwarePolynomialDistribution read_distribution =
    test_dists_list->get<UnitAwarePolynomialDistribution>( "Unit-Aware Polynomial Distribution A" );

  TEST_EQUALITY_CONST( read_distribution.getLowerBoundOfIndepVar(), 0.0*MeV );
  TEST_EQUALITY_CONST( read_distribution.getUpperBoundOfIndepVar(), 1.0*MeV );
  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0*MeV ),
		       1.0*si::mole );
  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.5*MeV ),
		       2.75*si::mole );
  TEST_EQUALITY_CONST( read_distribution.evaluate( 1.0*MeV ),
		       6.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be scaled
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( UnitAwarePolynomialDistribution,
				   explicit_conversion,
				   IndepUnitA,
				   DepUnitA,
				   IndepUnitB,
				   DepUnitB )
{
  typedef typename Utility::UnitTraits<IndepUnitA>::template GetQuantityType<double>::type IndepQuantityA;
  typedef typename Utility::UnitTraits<typename Utility::UnitTraits<IndepUnitA>::InverseUnit>::template GetQuantityType<double>::type InverseIndepQuantityA;

  typedef typename Utility::UnitTraits<IndepUnitB>::template GetQuantityType<double>::type IndepQuantityB;
  typedef typename Utility::UnitTraits<typename Utility::UnitTraits<IndepUnitB>::InverseUnit>::template GetQuantityType<double>::type InverseIndepQuantityB;

  typedef typename Utility::UnitTraits<DepUnitA>::template GetQuantityType<double>::type DepQuantityA;
  typedef typename Utility::UnitTraits<DepUnitB>::template GetQuantityType<double>::type DepQuantityB;

  // Copy from a unitless distribution to distribution type A (static method)
  Utility::UnitAwarePolynomialDistribution<IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwarePolynomialDistribution<IndepUnitA,DepUnitA>::fromUnitlessDistribution( *Teuchos::rcp_dynamic_cast<Utility::PolynomialDistribution>( distribution ) );

  // Copy from distribution type A to distribution type B (explicit cast)
  Utility::UnitAwarePolynomialDistribution<IndepUnitB,DepUnitB>
    unit_aware_dist_b_copy( unit_aware_dist_a_copy );

  IndepQuantityA indep_quantity_a =
    Utility::QuantityTraits<IndepQuantityA>::initializeQuantity( 0.0 );
  InverseIndepQuantityA inv_indep_quantity_a =
    Utility::QuantityTraits<InverseIndepQuantityA>::initializeQuantity( 1/3. );
  DepQuantityA dep_quantity_a =
    Utility::QuantityTraits<DepQuantityA>::initializeQuantity( 1.0 );

  IndepQuantityB indep_quantity_b( indep_quantity_a );
  InverseIndepQuantityB inv_indep_quantity_b( inv_indep_quantity_a );
  DepQuantityB dep_quantity_b( dep_quantity_a );

  UTILITY_TEST_FLOATING_EQUALITY(
			   unit_aware_dist_a_copy.evaluate( indep_quantity_a ),
			   dep_quantity_a,
			   1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY(
			unit_aware_dist_a_copy.evaluatePDF( indep_quantity_a ),
			inv_indep_quantity_a,
			1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY(
			   unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
			   dep_quantity_b,
			   1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY(
			unit_aware_dist_b_copy.evaluatePDF( indep_quantity_b ),
			inv_indep_quantity_b,
			1e-15 );

  Utility::setQuantity( indep_quantity_a, 1.0 );
  Utility::setQuantity( inv_indep_quantity_a, 2.0 );
  Utility::setQuantity( dep_quantity_a, 6.0 );

  indep_quantity_b = IndepQuantityB( indep_quantity_a );
  inv_indep_quantity_b = InverseIndepQuantityB( inv_indep_quantity_a );
  dep_quantity_b = DepQuantityB( dep_quantity_a );

  UTILITY_TEST_FLOATING_EQUALITY(
			   unit_aware_dist_a_copy.evaluate( indep_quantity_a ),
			   dep_quantity_a,
			   1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY(
			unit_aware_dist_a_copy.evaluatePDF( indep_quantity_a ),
			inv_indep_quantity_a,
			1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY(
			   unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
			   dep_quantity_b,
			   1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY(
			unit_aware_dist_b_copy.evaluatePDF( indep_quantity_b ),
			inv_indep_quantity_b,
			1e-15 );
}

typedef si::energy si_energy;
typedef cgs::energy cgs_energy;
typedef si::length si_length;
typedef cgs::length cgs_length;
typedef si::mass si_mass;
typedef cgs::mass cgs_mass;
typedef si::amount si_amount;
typedef si::dimensionless si_dimensionless;
typedef cgs::dimensionless cgs_dimensionless;

TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwarePolynomialDistribution,
				      explicit_conversion,
				      si_energy,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwarePolynomialDistribution,
				      explicit_conversion,
				      cgs_energy,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwarePolynomialDistribution,
				      explicit_conversion,
				      si_length,
				      si_energy,
				      cgs_length,
				      cgs_energy );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwarePolynomialDistribution,
				      explicit_conversion,
				      cgs_length,
				      cgs_energy,
				      si_length,
				      si_energy );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwarePolynomialDistribution,
				      explicit_conversion,
				      si_length,
				      si_mass,
				      cgs_length,
				      cgs_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwarePolynomialDistribution,
				      explicit_conversion,
				      cgs_length,
				      cgs_mass,
				      si_length,
				      si_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwarePolynomialDistribution,
				      explicit_conversion,
				      si_length,
				      void,
				      cgs_length,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwarePolynomialDistribution,
				      explicit_conversion,
				      cgs_length,
				      void,
				      si_length,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwarePolynomialDistribution,
				      explicit_conversion,
				      void,
				      si_mass,
				      void,
				      cgs_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwarePolynomialDistribution,
				      explicit_conversion,
				      void,
				      cgs_mass,
				      void,
				      si_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwarePolynomialDistribution,
				      explicit_conversion,
				      si_length,
				      si_dimensionless,
				      cgs_length,
				      cgs_dimensionless );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwarePolynomialDistribution,
				      explicit_conversion,
				      cgs_length,
				      cgs_dimensionless,
				      si_length,
				      si_dimensionless );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwarePolynomialDistribution,
				      explicit_conversion,
				      si_dimensionless,
				      si_length,
				      cgs_dimensionless,
				      cgs_length );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwarePolynomialDistribution,
				      explicit_conversion,
				      cgs_dimensionless,
				      cgs_length,
				      si_dimensionless,
				      si_length );

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_dists_xml_file;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_dists_xml_file",
		 &test_dists_xml_file,
		 "Test distributions xml file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return =
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  TEUCHOS_ADD_TYPE_CONVERTER( Utility::PolynomialDistribution );
  typedef Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount> UnitAwarePolynomialDistribution;
  TEUCHOS_ADD_TYPE_CONVERTER( UnitAwarePolynomialDistribution );

  test_dists_list = Teuchos::getParametersFromXmlFile( test_dists_xml_file );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();

  // Initialize the polynomial distribution
  Teuchos::Array<double> coeffs( 4 );
  coeffs[0] = 1.0;
  coeffs[1] = 2.0;
  coeffs[2] = 3.0;
  coeffs[3] = 0.0;

  distribution.reset( new Utility::PolynomialDistribution( coeffs, 0.0, 1.0 ));

  // Initialize the unit-aware polynomial distribution
  unit_aware_distribution.reset(
     new Utility::UnitAwarePolynomialDistribution<MegaElectronVolt,si::amount>(
						  coeffs, 0.0*eV, 1e6*eV ) );

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
// end tstPolynomialDistribution.cpp
//---------------------------------------------------------------------------//
