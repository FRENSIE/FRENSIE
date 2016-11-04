//---------------------------------------------------------------------------//
//!
//! \file   tstDeltaDistribution.cpp
//! \author Alex Robinson
//! \brief  Delta distribution unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>

// Boost Includes
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
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

Teuchos::RCP<Utility::TabularOneDDistribution>
  tab_distribution( new Utility::DeltaDistribution( 0.0 ) );

Teuchos::RCP<Utility::OneDDistribution>
  distribution( tab_distribution );

Teuchos::RCP<Utility::UnitAwareTabularOneDDistribution<si::time,si::length> >
  unit_aware_tab_distribution( new Utility::UnitAwareDeltaDistribution<si::time,si::length>( 3.0*si::seconds ) );

Teuchos::RCP<Utility::UnitAwareOneDDistribution<si::time,si::length> >
  unit_aware_distribution( unit_aware_tab_distribution );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( DeltaDistribution, evaluate )
{
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, evaluate )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*si::seconds ),
		       0.0*si::meters );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 3.0*si::seconds ),
		       1.0*si::meters );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 6.0*si::seconds ),
		       0.0*si::meters );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( DeltaDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, evaluatePDF )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 0.0*si::seconds ),
		       0.0/si::seconds );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 3.0*si::seconds ),
		       1.0/si::seconds );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 6.0*si::seconds ),
		       0.0/si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the CDF can be evaluated
TEUCHOS_UNIT_TEST( DeltaDistribution, evaluateCDF )
{
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( -1.0 ), 0.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 0.0 ), 1.0 );
  TEST_EQUALITY_CONST( tab_distribution->evaluateCDF( 1.0 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware CDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, evaluateCDF )
{
  TEST_EQUALITY_CONST(
		   unit_aware_tab_distribution->evaluateCDF( 0.0*si::seconds ),
		   0.0 );
  TEST_EQUALITY_CONST(
		   unit_aware_tab_distribution->evaluateCDF( 3.0*si::seconds ),
		   1.0 );
  TEST_EQUALITY_CONST(
		   unit_aware_tab_distribution->evaluateCDF( 6.0*si::seconds ),
		   1.0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DeltaDistribution, sample )
{
  TEST_EQUALITY_CONST( distribution->sample(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, sample )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->sample(), 3.0*si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DeltaDistribution, sampleAndRecordTrials )
{
  unsigned trials = 0;
  double sample = distribution->sampleAndRecordTrials( trials );

  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( trials, 1 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, sampleAndRecordTrials )
{
  unsigned trials = 0;

  quantity<si::time> sample =
    unit_aware_distribution->sampleAndRecordTrials( trials );

  TEST_EQUALITY_CONST( sample, 3.0*si::seconds );
  TEST_EQUALITY_CONST( trials, 1 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DeltaDistribution, sampleAndRecordBinIndex )
{
  unsigned bin_index = 0;
  double sample = tab_distribution->sampleAndRecordBinIndex( bin_index );

  TEST_EQUALITY_CONST( sample, 0.0 );
  TEST_EQUALITY_CONST( bin_index, 0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, sampleAndRecordBinIndex )
{
  unsigned bin_index = 0;

  quantity<si::time> sample =
    unit_aware_tab_distribution->sampleAndRecordBinIndex( bin_index );

  TEST_EQUALITY_CONST( sample, 3.0*si::seconds );
  TEST_EQUALITY_CONST( bin_index, 0 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DeltaDistribution, sampleWithRandomNumber )
{
  double sample = tab_distribution->sampleWithRandomNumber( 0.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleWithRandomNumber( 0.5 );

  TEST_EQUALITY_CONST( sample, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, sampleWithRandomNumber )
{
  quantity<si::time> sample =
    unit_aware_tab_distribution->sampleWithRandomNumber( 0.0 );

  TEST_EQUALITY_CONST( sample, 3.0*si::seconds );

  sample = unit_aware_tab_distribution->sampleWithRandomNumber( 0.5 );

  TEST_EQUALITY_CONST( sample, 3.0*si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DeltaDistribution, sampleInSubrange )
{
  double sample = tab_distribution->sampleInSubrange( 1.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleInSubrange( 0.1 );

  TEST_EQUALITY_CONST( sample, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, sampleInSubrange )
{
  quantity<si::time> sample =
    unit_aware_tab_distribution->sampleInSubrange( 4.0*si::seconds );

  TEST_EQUALITY_CONST( sample, 3.0*si::seconds );

  sample = unit_aware_tab_distribution->sampleInSubrange( 3.1*si::seconds );

  TEST_EQUALITY_CONST( sample, 3.0*si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled
TEUCHOS_UNIT_TEST( DeltaDistribution, sampleWithRandomNumberInSubrange )
{
  double sample =
    tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 1.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );

  sample = tab_distribution->sampleWithRandomNumberInSubrange( 0.5, 2.0 );

  TEST_EQUALITY_CONST( sample, 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution,
		   sampleWithRandomNumberInSubrange )
{
  quantity<si::time> sample =
    unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 0.0, 4.0*si::seconds );

  TEST_EQUALITY_CONST( sample, 3.0*si::seconds );

  sample = unit_aware_tab_distribution->sampleWithRandomNumberInSubrange( 0.5, 3.1*si::seconds );

  TEST_EQUALITY_CONST( sample, 3.0*si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can
// be returned
TEUCHOS_UNIT_TEST( DeltaDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfIndepVar(),
		       3.0*si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can
// be returned
TEUCHOS_UNIT_TEST( DeltaDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent
// variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfIndepVar(),
		       3.0*si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( DeltaDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( distribution->getDistributionType(),
		       Utility::DELTA_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getDistributionType(),
		       Utility::DELTA_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST( DeltaDistribution, isTabular )
{
  TEST_ASSERT( distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, isTabular )
{
  TEST_ASSERT( unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
TEUCHOS_UNIT_TEST( DeltaDistribution, isContinuous )
{
  TEST_ASSERT( !distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, isContinuous )
{
  TEST_ASSERT( !unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
TEUCHOS_UNIT_TEST( DeltaDistribution, isCompatibleWithInterpType )
{
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, isCompatibleWithInterpType )
{
  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to an xml file
TEUCHOS_UNIT_TEST( DeltaDistribution, toParameterList )
{
  Teuchos::RCP<Utility::DeltaDistribution> true_distribution =
    Teuchos::rcp_dynamic_cast<Utility::DeltaDistribution>( distribution );

  Teuchos::ParameterList parameter_list;

  parameter_list.set<Utility::DeltaDistribution>( "test distribution",
						  *true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
					"delta_dist_test_list.xml" );

  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list =
    Teuchos::getParametersFromXmlFile( "delta_dist_test_list.xml" );

  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<Utility::DeltaDistribution>
    copy_distribution( new Utility::DeltaDistribution );

  *copy_distribution = read_parameter_list->get<Utility::DeltaDistribution>(
							  "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be written to an xml file
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, toParameterList )
{
  typedef Utility::UnitAwareDeltaDistribution<si::time,si::length> UnitAwareDeltaDistribution;

  Teuchos::RCP<UnitAwareDeltaDistribution> true_distribution =
    Teuchos::rcp_dynamic_cast<UnitAwareDeltaDistribution>( unit_aware_distribution );

  Teuchos::ParameterList parameter_list;

  parameter_list.set<UnitAwareDeltaDistribution>( "test distribution",
						  *true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
					"unit_aware_delta_dist_test_list.xml");

  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list =
    Teuchos::getParametersFromXmlFile( "unit_aware_delta_dist_test_list.xml" );

  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<UnitAwareDeltaDistribution>
    copy_distribution( new UnitAwareDeltaDistribution );

  *copy_distribution = read_parameter_list->get<UnitAwareDeltaDistribution>(
							  "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );

  std::cout << boost::units::name_string( si::energy() ) << std::endl;
}

//---------------------------------------------------------------------------//
// Check that the distribution can be read from an xml file
TEUCHOS_UNIT_TEST( DeltaDistribution, fromParameterList )
{
  Utility::DeltaDistribution xml_distribution =
    test_dists_list->get<Utility::DeltaDistribution>( "Delta Distribution A" );

  TEST_EQUALITY_CONST( xml_distribution.getLowerBoundOfIndepVar(), 0 );

  xml_distribution =
    test_dists_list->get<Utility::DeltaDistribution>( "Delta Distribution B" );

  TEST_EQUALITY_CONST( xml_distribution.getLowerBoundOfIndepVar(),
		       Utility::PhysicalConstants::pi );

  xml_distribution =
    test_dists_list->get<Utility::DeltaDistribution>( "Delta Distribution C" );

  TEST_EQUALITY_CONST( xml_distribution.getLowerBoundOfIndepVar(),
		       -Utility::PhysicalConstants::pi/2 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be read from an xml file
TEUCHOS_UNIT_TEST( UnitAwareDeltaDistribution, fromParameterList )
{
  typedef Utility::UnitAwareDeltaDistribution<si::time,si::length> UnitAwareDeltaDistribution;

  UnitAwareDeltaDistribution xml_distribution =
    test_dists_list->get<UnitAwareDeltaDistribution>( "Unit-Aware Delta Distribution A" );

  TEST_EQUALITY_CONST( xml_distribution.getLowerBoundOfIndepVar(),
		       3.0*si::seconds );

  xml_distribution =
    test_dists_list->get<UnitAwareDeltaDistribution>( "Unit-Aware Delta Distribution B" );

  TEST_EQUALITY_CONST( xml_distribution.getLowerBoundOfIndepVar(),
		       2*Utility::PhysicalConstants::pi*si::seconds );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be scaled
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( UnitAwareDeltaDistribution,
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

  // Copy from unitless distribution to distribution type A
  Utility::UnitAwareDeltaDistribution<IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwareDeltaDistribution<IndepUnitA,DepUnitA>::fromUnitlessDistribution( *Teuchos::rcp_dynamic_cast<Utility::DeltaDistribution>( distribution ) );

  // Copy from distribution type A to distribution type B
  Utility::UnitAwareDeltaDistribution<IndepUnitB,DepUnitB>
    unit_aware_dist_b_copy( unit_aware_dist_a_copy );

  IndepQuantityA indep_quantity_a =
    Utility::QuantityTraits<IndepQuantityA>::initializeQuantity( 0.0 );
  InverseIndepQuantityA inv_indep_quantity_a =
    Utility::QuantityTraits<InverseIndepQuantityA>::initializeQuantity( 1.0 );
  DepQuantityA dep_quantity_a =
    Utility::QuantityTraits<DepQuantityA>::initializeQuantity( 1.0 );

  IndepQuantityB indep_quantity_b( indep_quantity_a );
  InverseIndepQuantityB inv_indep_quantity_b =
    Utility::QuantityTraits<InverseIndepQuantityB>::initializeQuantity( 1.0 );
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
  Utility::setQuantity( inv_indep_quantity_a, 0.0 );
  Utility::setQuantity( dep_quantity_a, 0.0 );

  indep_quantity_b = IndepQuantityB( indep_quantity_a );
  Utility::setQuantity( inv_indep_quantity_b, 0.0 );
  dep_quantity_b = DepQuantityB( dep_quantity_a );

  UTILITY_TEST_FLOATING_EQUALITY(
			   unit_aware_dist_a_copy.evaluate( indep_quantity_a ),
			   dep_quantity_a,
			   1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY(
			unit_aware_dist_a_copy.evaluatePDF( indep_quantity_a ),
			inv_indep_quantity_a,
			1e-6 );
  UTILITY_TEST_FLOATING_EQUALITY(
			   unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
			   dep_quantity_b,
			   1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY(
			unit_aware_dist_b_copy.evaluatePDF( indep_quantity_b ),
			inv_indep_quantity_b,
			1e-6 );
}

typedef si::energy si_energy;
typedef cgs::energy cgs_energy;
typedef si::amount si_amount;
typedef si::length si_length;
typedef cgs::length cgs_length;
typedef si::mass si_mass;
typedef cgs::mass cgs_mass;
typedef si::dimensionless si_dimensionless;
typedef cgs::dimensionless cgs_dimensionless;

TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      si_energy,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      cgs_energy,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      si_energy,
				      si_length,
				      cgs_energy,
				      cgs_length );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_length,
				      si_energy,
				      si_length );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      si_energy,
				      si_mass,
				      cgs_energy,
				      cgs_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_mass,
				      si_energy,
				      si_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      si_energy,
				      si_dimensionless,
				      cgs_energy,
				      cgs_dimensionless );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_dimensionless,
				      si_energy,
				      si_dimensionless );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      si_energy,
				      void,
				      cgs_energy,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      cgs_energy,
				      void,
				      si_energy,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      KiloElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      MegaElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      ElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      MegaElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      ElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      KiloElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareDeltaDistribution,
				      explicit_conversion,
				      void,
				      MegaElectronVolt,
				      void,
				      KiloElectronVolt );

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_BEGIN();

std::string test_dists_xml_file;

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  clp().setOption( "test_dists_xml_file",
                   &test_dists_xml_file,
                   "Test distributions xml file name" );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_DATA_INITIALIZATION()
{
  TEUCHOS_ADD_TYPE_CONVERTER( Utility::DeltaDistribution );
  typedef Utility::UnitAwareDeltaDistribution<si::time,si::length> UnitAwareDeltaDistribution;
  TEUCHOS_ADD_TYPE_CONVERTER( UnitAwareDeltaDistribution );

  test_dists_list = Teuchos::getParametersFromXmlFile( test_dists_xml_file );
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstDeltaDistribution.cpp
//---------------------------------------------------------------------------//
