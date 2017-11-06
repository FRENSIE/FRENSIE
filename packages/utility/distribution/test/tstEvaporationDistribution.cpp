//---------------------------------------------------------------------------//
//!
//! \file   tstEvaporationDistribution.cpp
//! \author Aaron Tumulak
//! \brief  Evaporation distribution unit tests. Unit-aware unit tests
//!         added by Alex Robinson.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/cgs.hpp>
#include <boost/units/io.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_EvaporationDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"
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

Teuchos::RCP<Utility::OneDDistribution> distribution(
				 new Utility::EvaporationDistribution( 1.0, 1.0, 0.1 ) );

Teuchos::RCP<Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount> >
  unit_aware_distribution( new Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 1e3*keV, 1e3*keV, 100.0*keV ) );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( EvaporationDistribution, evaluate )
{
  double test_value_1 = 0.0 ;
  double test_value_2 = 0.9*exp( -0.9 );

  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), test_value_1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.9 ), test_value_2 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), test_value_1 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareEvaporationDistribution, evaluate )
{
  double scale_factor = 0.9*exp(-0.9);

  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV ),
		       0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.9*MeV ),
                       scale_factor*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.0*MeV ),
		       0.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( EvaporationDistribution, evaluatePDF )
{
  double test_value_1 = 0.0 ;
  double test_value_2 = 0.9*exp(-0.9)/(1.0 - exp(-0.9)*(1.0+0.9));

  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.0 ), test_value_1 );
  TEST_FLOATING_EQUALITY( distribution->evaluatePDF( 0.9 ),
                          test_value_2,
                          1e-15 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 1.0 ), test_value_1 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareEvaporationDistribution, evaluatePDF )
{
  double scale_factor = 0.9*exp(-0.9)/(1.0 - exp(-0.9)*(1.0+0.9));

  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 0.0*MeV ),
		       0.0/MeV );
  UTILITY_TEST_FLOATING_EQUALITY( unit_aware_distribution->evaluatePDF( 0.9*MeV ),
                                  scale_factor/MeV,
                                  1e-15 );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 1.0*MeV ),
                       0.0/MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled using OpenMC method
TEUCHOS_UNIT_TEST( EvaporationDistribution, sample )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.8388165507412660;
  fake_stream[1] = 0.0267354287196134;
  fake_stream[2] = 0.9615425535640773;
  fake_stream[3] = 0.9996969006924931;
  fake_stream[4] = 0.1891183747157897;
  fake_stream[5] = 0.8650163759473460;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 0.70470821836401, 1e-14 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 0.83920374256297, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that unit-aware distribution can be sampled using the OpenMC method
TEUCHOS_UNIT_TEST( UnitAwareEvaporationDistribution, sample )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.8388165507412660;
  fake_stream[1] = 0.0267354287196134;
  fake_stream[2] = 0.9615425535640773;
  fake_stream[3] = 0.9996969006924931;
  fake_stream[4] = 0.1891183747157897;
  fake_stream[5] = 0.8650163759473460;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<MegaElectronVolt> sample = unit_aware_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.70470821836401*MeV, 1e-14 );

  sample = unit_aware_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.83920374256297*MeV, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled using OpenMC method, and the
// trials can be recorded
TEUCHOS_UNIT_TEST( EvaporationDistribution, sample_pass_parameters )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.7109904185738904;
  fake_stream[1] = 0.1535897705184878;
  fake_stream[2] = 0.6915260327666102;
  fake_stream[3] = 0.6291257012282162;
  fake_stream[4] = 0.3183560295023423;
  fake_stream[5] = 0.7492388871308626;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incident_energy, nuclear_temperature, restriction_energy, sample;

  incident_energy = 0.5;
  nuclear_temperature = 0.1;
  restriction_energy = 0.01;

  sample = Utility::EvaporationDistribution::sample( incident_energy, nuclear_temperature, restriction_energy );
  TEST_FLOATING_EQUALITY( sample, 0.13885427138954, 1e-13 );

  incident_energy = 0.75;
  nuclear_temperature = 0.5;
  restriction_energy = 0.25;

  sample = Utility::EvaporationDistribution::sample( incident_energy, nuclear_temperature, restriction_energy );
  TEST_FLOATING_EQUALITY( sample, 0.43320278283758, 1e-13 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled using OpenMC method,
// and the trials can be recorded
TEUCHOS_UNIT_TEST( UnitAwareEvaporationDistribution, sample_pass_parameters )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.7109904185738904;
  fake_stream[1] = 0.1535897705184878;
  fake_stream[2] = 0.6915260327666102;
  fake_stream[3] = 0.6291257012282162;
  fake_stream[4] = 0.3183560295023423;
  fake_stream[5] = 0.7492388871308626;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<MegaElectronVolt> incident_energy, nuclear_temperature,
    restriction_energy, sample;

  incident_energy = 0.5*MeV;
  nuclear_temperature = 0.1*MeV;
  restriction_energy = 0.01*MeV;

  sample = Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>::sample( incident_energy, nuclear_temperature, restriction_energy );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.13885427138954*MeV, 1e-13 );

  incident_energy = 0.75*MeV;
  nuclear_temperature = 0.5*MeV;
  restriction_energy = 0.25*MeV;

  sample = Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>::sample( incident_energy, nuclear_temperature, restriction_energy );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.43320278283758*MeV, 1e-13 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled using OpenMC method, and the
// trials can be recorded
TEUCHOS_UNIT_TEST( EvaporationDistribution, sampleAndRecordTrials_pass_parameters )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.7109904185738904;
  fake_stream[1] = 0.1535897705184878;
  fake_stream[2] = 0.6915260327666102;
  fake_stream[3] = 0.6291257012282162;
  fake_stream[4] = 0.3183560295023423;
  fake_stream[5] = 0.7492388871308626;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incident_energy, nuclear_temperature, restriction_energy, sample;
  Utility::DistributionTraits::Counter trials = 0;

  incident_energy = 0.5;
  nuclear_temperature = 0.1;
  restriction_energy = 0.01;

  sample = Utility::EvaporationDistribution::sampleAndRecordTrials(incident_energy, nuclear_temperature, restriction_energy, trials);
  TEST_FLOATING_EQUALITY( sample, 0.13885427138954, 1e-13 );
  TEST_EQUALITY_CONST( trials, 1.0 );

  incident_energy = 0.75;
  nuclear_temperature = 0.5;
  restriction_energy = 0.25;

  sample = Utility::EvaporationDistribution::sampleAndRecordTrials(incident_energy, nuclear_temperature, restriction_energy, trials);
  TEST_FLOATING_EQUALITY( sample, 0.43320278283758, 1e-13 );
  TEST_EQUALITY_CONST( trials, 3.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled using OpenMC method,
// and the trials can be recorded
TEUCHOS_UNIT_TEST( UnitAwareEvaporationDistribution,
		   sampleAndRecordTrials_pass_parameters )
{
  std::vector<double> fake_stream( 6 );
  fake_stream[0] = 0.7109904185738904;
  fake_stream[1] = 0.1535897705184878;
  fake_stream[2] = 0.6915260327666102;
  fake_stream[3] = 0.6291257012282162;
  fake_stream[4] = 0.3183560295023423;
  fake_stream[5] = 0.7492388871308626;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<MegaElectronVolt> incident_energy, nuclear_temperature,
    restriction_energy, sample;
  Utility::DistributionTraits::Counter trials = 0;

  incident_energy = 0.5*MeV;
  nuclear_temperature = 0.1*MeV;
  restriction_energy = 0.01*MeV;

  sample = Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>::sampleAndRecordTrials(incident_energy, nuclear_temperature, restriction_energy, trials);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.13885427138954*MeV, 1e-13 );
  TEST_EQUALITY_CONST( trials, 1.0 );

  incident_energy = 0.75*MeV;
  nuclear_temperature = 0.5*MeV;
  restriction_energy = 0.25*MeV;

  sample = Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>::sampleAndRecordTrials(incident_energy, nuclear_temperature, restriction_energy, trials);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.43320278283758*MeV, 1e-13 );
  TEST_EQUALITY_CONST( trials, 3.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( EvaporationDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(), 0.9 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareEvaporationDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfIndepVar(),
		       0.9*MeV );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( EvaporationDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent
// variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareEvaporationDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfIndepVar(),
		       0.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( EvaporationDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( distribution->getDistributionType(),
		       Utility::EVAPORATION_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
TEUCHOS_UNIT_TEST( UnitAwareEvaporationDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getDistributionType(),
		       Utility::EVAPORATION_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST( EvaporationDistribution, isTabular )
{
  TEST_ASSERT( !distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular
TEUCHOS_UNIT_TEST( UnitAwareEvaporationDistribution, isTabular )
{
  TEST_ASSERT( !unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
TEUCHOS_UNIT_TEST( EvaporationDistribution, isContinuous )
{
  TEST_ASSERT( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is continuous
TEUCHOS_UNIT_TEST( UnitAwareEvaporationDistribution, isContinuous )
{
  TEST_ASSERT( unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
TEUCHOS_UNIT_TEST( EvaporationDistribution, isCompatibleWithInterpType )
{
  TEST_ASSERT( distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
TEUCHOS_UNIT_TEST( UnitAwareEvaporationDistribution,
                   isCompatibleWithInterpType )
{
  TEST_ASSERT( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to an xml file
TEUCHOS_UNIT_TEST( EvaporationDistribution, toParameterList )
{
  Teuchos::RCP<Utility::EvaporationDistribution> true_distribution =
  Teuchos::rcp_dynamic_cast<Utility::EvaporationDistribution>( distribution );

  Teuchos::ParameterList parameter_list;

  parameter_list.set<Utility::EvaporationDistribution>( "test distribution",
                                                  *true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
                                       "evaporation_dist_test_list.xml" );

  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list =
  Teuchos::getParametersFromXmlFile( "evaporation_dist_test_list.xml" );

  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<Utility::EvaporationDistribution>
  copy_distribution( new Utility::EvaporationDistribution );

  *copy_distribution = read_parameter_list->get<Utility::EvaporationDistribution>(
                                                                             "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be written to an xml file
TEUCHOS_UNIT_TEST( UnitAwareEvaporationDistribution, toParameterList )
{
  typedef Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount> UnitAwareEvaporationDistribution;

  Teuchos::RCP<UnitAwareEvaporationDistribution> true_distribution =
    Teuchos::rcp_dynamic_cast<UnitAwareEvaporationDistribution>( unit_aware_distribution );

  Teuchos::ParameterList parameter_list;

  parameter_list.set<UnitAwareEvaporationDistribution>( "test distribution",
							*true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
					"unit_aware_evaporation_dist_test_list.xml" );

  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list =
    Teuchos::getParametersFromXmlFile( "unit_aware_evaporation_dist_test_list.xml" );

  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<UnitAwareEvaporationDistribution>
    copy_distribution( new UnitAwareEvaporationDistribution );

  *copy_distribution = read_parameter_list->get<UnitAwareEvaporationDistribution>(
							  "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be read from an xml file
TEUCHOS_UNIT_TEST( EvaporationDistribution, fromParameterList )
{
  double test_value_1;
  double test_value_2;
  Utility::EvaporationDistribution read_distribution =
    test_dists_list->get<Utility::EvaporationDistribution>( "Evaporation Distribution A" );

  test_value_1 = 0.0 ;
  test_value_2 = 0.9*exp(-0.9)/(1.0 - exp(-0.9)*(1.0+0.9));

  TEST_EQUALITY_CONST( read_distribution.evaluatePDF( 0.0 ), test_value_1 );
  TEST_FLOATING_EQUALITY( read_distribution.evaluatePDF( 0.9 ),
                          test_value_2,
                          1e-15 );
  TEST_EQUALITY_CONST( read_distribution.evaluatePDF( 1.0 ), test_value_1 );

  read_distribution =
    test_dists_list->get<Utility::EvaporationDistribution>( "Evaporation Distribution B" );

  test_value_1 = 0.0 ;
  test_value_2 = pow( 2.0, 2.0) * ( 1.0 - exp(-1.0) * (1.0 + 1.0) );
  test_value_2 = pow( test_value_2, -1.0 ) * exp( -0.5 );

  TEST_EQUALITY_CONST( read_distribution.evaluatePDF( 0.0 ), test_value_1 );
  TEST_EQUALITY_CONST( read_distribution.evaluatePDF( 1.0 ), test_value_2 );

  read_distribution =
    test_dists_list->get<Utility::EvaporationDistribution>( "Evaporation Distribution C" );

  test_value_1 = 0.0 ;
  test_value_2 = 1.0 - exp(-1.0) * (1.0 + 1.0) ;
  test_value_2 = pow( test_value_2, -1.0 ) * exp( -1.0 );

  TEST_EQUALITY_CONST( read_distribution.evaluatePDF( 0.0 ), test_value_1 );
  TEST_EQUALITY_CONST( read_distribution.evaluatePDF( 1.0 ), test_value_2 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be read from an xml file
TEUCHOS_UNIT_TEST( UnitAwareEvaporationDistribution, fromParameterList )
{
  typedef Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount> UnitAwareEvaporationDistribution;

  UnitAwareEvaporationDistribution read_distribution =
    test_dists_list->get<UnitAwareEvaporationDistribution>( "Unit-Aware Evaporation Distribution A" );

  double scale_factor = 0.9*exp(-0.9)/(1.0 - exp(-0.9)*(1.0+0.9));

  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0*MeV ),
		       0.0*si::mole );
  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.9*MeV ),
		       10.0*0.9*exp(-0.9)*si::mole );
  TEST_EQUALITY_CONST( read_distribution.evaluatePDF( 0.9*MeV ),
		       scale_factor/MeV );
  TEST_EQUALITY_CONST( read_distribution.evaluate( 1.0*MeV ),
                       0.0*si::mole );
  TEST_EQUALITY_CONST( read_distribution.evaluatePDF( 1.0*MeV ),
                       0.0/MeV );

  read_distribution =
    test_dists_list->get<UnitAwareEvaporationDistribution>( "Unit-Aware Evaporation Distribution B" );

  scale_factor = exp(-0.5)/(4.0*(1.0-exp(-1.0)*(1.0+1.0)));

  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0*MeV ),
		       0.0*si::mole );
  TEST_EQUALITY_CONST( read_distribution.evaluate( 1.0*MeV ),
		       exp(-0.5)*si::mole );
  TEST_EQUALITY_CONST( read_distribution.evaluatePDF( 1.0*MeV ),
		       scale_factor/MeV );

  read_distribution =
    test_dists_list->get<UnitAwareEvaporationDistribution>( "Unit-Aware Evaporation Distribution C" );

  scale_factor = exp(-1.0)/(1.0 - exp(-1.0)*(1.0+1.0));

  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0*MeV ),
		       0.0*si::mole );
  TEST_EQUALITY_CONST( read_distribution.evaluate( 1.0*MeV ),
		       exp(-1.0)*si::mole );
  TEST_EQUALITY_CONST( read_distribution.evaluatePDF( 1.0*MeV ),
		       scale_factor/MeV );
}

//---------------------------------------------------------------------------//
// Check that distributions can be scaled
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( UnitAwareEvaporationDistribution,
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

  // Copy from unitless distribution to distribution type A (static method)
  Utility::UnitAwareEvaporationDistribution<IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwareEvaporationDistribution<IndepUnitA,DepUnitA>::fromUnitlessDistribution( *Teuchos::rcp_dynamic_cast<Utility::EvaporationDistribution>( distribution ) );

  // Copy from distribution type A to distribution type B (explicit cast)
  Utility::UnitAwareEvaporationDistribution<IndepUnitB,DepUnitB>
    unit_aware_dist_b_copy( unit_aware_dist_a_copy );

  IndepQuantityA indep_quantity_a =
    Utility::QuantityTraits<IndepQuantityA>::initializeQuantity( 0.0 );
  InverseIndepQuantityA inv_indep_quantity_a =
    Utility::QuantityTraits<InverseIndepQuantityA>::initializeQuantity( 0.0 );
  DepQuantityA dep_quantity_a =
    Utility::QuantityTraits<DepQuantityA>::initializeQuantity( 0.0 );

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

  Utility::setQuantity( indep_quantity_a, 0.89999999999999 );
  Utility::setQuantity( inv_indep_quantity_a,
			0.9*exp(-0.9)/(1.0 - exp(-0.9)*(1.0+0.9)) );
  Utility::setQuantity( dep_quantity_a, 0.9*exp(-0.9) );

  indep_quantity_b = IndepQuantityB( indep_quantity_a );
  inv_indep_quantity_b = InverseIndepQuantityB( inv_indep_quantity_a );
  dep_quantity_b = DepQuantityB( dep_quantity_a );

  UTILITY_TEST_FLOATING_EQUALITY(
			   unit_aware_dist_a_copy.evaluate( indep_quantity_a ),
			   dep_quantity_a,
			   1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY(
			unit_aware_dist_a_copy.evaluatePDF( indep_quantity_a ),
			inv_indep_quantity_a,
			1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY(
			   unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
			   dep_quantity_b,
			   1e-14 );
  UTILITY_TEST_FLOATING_EQUALITY(
			unit_aware_dist_b_copy.evaluatePDF( indep_quantity_b ),
			inv_indep_quantity_b,
			1e-14 );
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

TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEvaporationDistribution,
				      explicit_conversion,
				      si_energy,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEvaporationDistribution,
				      explicit_conversion,
				      cgs_energy,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEvaporationDistribution,
				      explicit_conversion,
				      si_energy,
				      si_length,
				      cgs_energy,
				      cgs_length );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEvaporationDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_length,
				      si_energy,
				      si_length );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEvaporationDistribution,
				      explicit_conversion,
				      si_energy,
				      si_mass,
				      cgs_energy,
				      cgs_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEvaporationDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_mass,
				      si_energy,
				      si_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEvaporationDistribution,
				      explicit_conversion,
				      si_energy,
				      si_dimensionless,
				      cgs_energy,
				      cgs_dimensionless );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEvaporationDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_dimensionless,
				      si_energy,
				      si_dimensionless );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEvaporationDistribution,
				      explicit_conversion,
				      si_energy,
				      void,
				      cgs_energy,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEvaporationDistribution,
				      explicit_conversion,
				      cgs_energy,
				      void,
				      si_energy,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEvaporationDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEvaporationDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEvaporationDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      KiloElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEvaporationDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      MegaElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEvaporationDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEvaporationDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEvaporationDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      ElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEvaporationDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      MegaElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEvaporationDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEvaporationDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEvaporationDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      ElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEvaporationDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      KiloElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareEvaporationDistribution,
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
  TEUCHOS_ADD_TYPE_CONVERTER( Utility::EvaporationDistribution );
  typedef Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount> UnitAwareEvaporationDistribution;
  TEUCHOS_ADD_TYPE_CONVERTER( UnitAwareEvaporationDistribution );

  test_dists_list = Teuchos::getParametersFromXmlFile( test_dists_xml_file );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstEvaporationDistribution.cpp
//---------------------------------------------------------------------------//

