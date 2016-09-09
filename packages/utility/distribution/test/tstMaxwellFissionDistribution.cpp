//---------------------------------------------------------------------------//
//!
//! \file   tstMaxwellFissionDistribution.cpp
//! \author Aaron Tumulak
//! \brief  Maxwell Fission distribution unit tests.
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
#include "Utility_MaxwellFissionDistribution.hpp"
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
				 new Utility::MaxwellFissionDistribution( 1.0, 1.0, 0.1 ) );

Teuchos::RCP<Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount> >
  unit_aware_distribution( new Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 1e6*eV, 1e3*keV, 0.1*MeV ) );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( MaxwellFissionDistribution, evaluate )
{
  double test_value_1 = 0.0 ;
  double test_value_2 = sqrt( 0.9 )*exp( -0.9 );

  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), test_value_1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.9 ), test_value_2 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareMaxwellFissionDistribution, evaluate )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV ),
		       0.0*si::mole );
  
  double scale_factor = sqrt( 0.9 )*exp( -0.9 );

  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.9*MeV ),
                       scale_factor*si::mole );
  
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.0*MeV ),
		       0.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( MaxwellFissionDistribution, evaluatePDF )
{
  double test_value_1 = 0.0;
  double test_value_2 = sqrt( 0.9 )*exp( -0.9 )/
    (sqrt(Utility::PhysicalConstants::pi)*0.5*erf(sqrt(0.9)) -
     sqrt(0.9)*exp(-0.9));
  
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.0 ), test_value_1 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.9 ), test_value_2 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 1.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareMaxwellFissionDistribution, evaluatePDF )
{
  double scale_factor = sqrt( 0.9 )*exp( -0.9 )/
    (sqrt(Utility::PhysicalConstants::pi)*0.5*erf(sqrt(0.9)) -
     sqrt(0.9)*exp(-0.9));

  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 0.0*MeV ),
		       0.0/MeV );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 0.9*MeV ),
                       scale_factor/MeV );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 1.0*MeV ),
		       0.0/MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled using OpenMC method
TEUCHOS_UNIT_TEST( MaxwellFissionDistribution, sample )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.9526660807223237;
  fake_stream[1] = 0.2628340201570147;
  fake_stream[2] = 0.4684607693058543;
  fake_stream[3] = 0.2948581100330813;
  fake_stream[4] = 0.4810986077957187;
  fake_stream[5] = 0.8453449553051804;
  fake_stream[6] = 0.4656289304981871;
  fake_stream[7] = 0.7470315175721101;
  fake_stream[8] = 0.5418708973800604;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 0.78269807500829, 1e-14 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 0.89106359701991, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled using OpenMC method
TEUCHOS_UNIT_TEST( UnitAwareMaxwellFissionDistribution, sample )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.9526660807223237;
  fake_stream[1] = 0.2628340201570147;
  fake_stream[2] = 0.4684607693058543;
  fake_stream[3] = 0.2948581100330813;
  fake_stream[4] = 0.4810986077957187;
  fake_stream[5] = 0.8453449553051804;
  fake_stream[6] = 0.4656289304981871;
  fake_stream[7] = 0.7470315175721101;
  fake_stream[8] = 0.5418708973800604;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<MegaElectronVolt> sample = unit_aware_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.78269807500829*MeV, 1e-14 );

  sample = unit_aware_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.89106359701991*MeV, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled using OpenMC method and the
// trials can be recorded
TEUCHOS_UNIT_TEST( MaxwellFissionDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.9526660807223237;
  fake_stream[1] = 0.2628340201570147;
  fake_stream[2] = 0.4684607693058543;
  fake_stream[3] = 0.2948581100330813;
  fake_stream[4] = 0.4810986077957187;
  fake_stream[5] = 0.8453449553051804;
  fake_stream[6] = 0.4656289304981871;
  fake_stream[7] = 0.7470315175721101;
  fake_stream[8] = 0.5418708973800604;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0;

  double sample = distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 0.78269807500829, 1e-14 );
  TEST_EQUALITY_CONST( trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  TEST_FLOATING_EQUALITY( sample, 0.89106359701991, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled using OpenMC method
// and the trials can be recorded
TEUCHOS_UNIT_TEST( UnitAwareMaxwellFissionDistribution, sampleAndRecordTrials )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.9526660807223237;
  fake_stream[1] = 0.2628340201570147;
  fake_stream[2] = 0.4684607693058543;
  fake_stream[3] = 0.2948581100330813;
  fake_stream[4] = 0.4810986077957187;
  fake_stream[5] = 0.8453449553051804;
  fake_stream[6] = 0.4656289304981871;
  fake_stream[7] = 0.7470315175721101;
  fake_stream[8] = 0.5418708973800604;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  unsigned trials = 0;

  quantity<MegaElectronVolt> sample =
    unit_aware_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.78269807500829*MeV, 1e-14 );
  TEST_EQUALITY_CONST( trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.89106359701991*MeV, 1e-14 );
  TEST_EQUALITY_CONST( trials, 3.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled using OpenMC method, passing in
// parameters
TEUCHOS_UNIT_TEST( MaxwellFissionDistribution,
		   sample_pass_parameters )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.1324998063336137;
  fake_stream[1] = 0.9247996934252033;
  fake_stream[2] = 0.1918514900811418;
  fake_stream[3] = 0.3062640867105594;
  fake_stream[4] = 0.8754839687423933;
  fake_stream[5] = 0.2274300298185482;
  fake_stream[6] = 0.9336967385663441;
  fake_stream[7] = 0.2459018944829507;
  fake_stream[8] = 0.4770873202414019;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incident_energy, nuclear_temperature, restriction_energy, sample;

  incident_energy = 0.5;
  nuclear_temperature = 0.1;
  restriction_energy = 0.01;

  sample = Utility::MaxwellFissionDistribution::sample( incident_energy, nuclear_temperature, restriction_energy );
  TEST_FLOATING_EQUALITY( sample, 0.20924646054839, 1e-13 );

  incident_energy = 0.75;
  nuclear_temperature = 0.5;
  restriction_energy = 0.25;

  sample = Utility::MaxwellFissionDistribution::sample( incident_energy, nuclear_temperature, restriction_energy );
  TEST_FLOATING_EQUALITY( sample, 0.41023025568120, 1e-13 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled using OpenMC method,
// passing in parameters
TEUCHOS_UNIT_TEST( UnitAwareMaxwellFissionDistribution,
		   sample_pass_parameters )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.1324998063336137;
  fake_stream[1] = 0.9247996934252033;
  fake_stream[2] = 0.1918514900811418;
  fake_stream[3] = 0.3062640867105594;
  fake_stream[4] = 0.8754839687423933;
  fake_stream[5] = 0.2274300298185482;
  fake_stream[6] = 0.9336967385663441;
  fake_stream[7] = 0.2459018944829507;
  fake_stream[8] = 0.4770873202414019;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<MegaElectronVolt> incident_energy, nuclear_temperature,
    restriction_energy, sample;

  incident_energy = 0.5*MeV;
  nuclear_temperature = 0.1*MeV;
  restriction_energy = 0.01*MeV;

  sample = Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt>::sample( incident_energy, nuclear_temperature, restriction_energy );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.20924646054839*MeV, 1e-13 );

  incident_energy = 0.75*MeV;
  nuclear_temperature = 0.5*MeV;
  restriction_energy = 0.25*MeV;

  sample = Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt>::sample( incident_energy, nuclear_temperature, restriction_energy );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.41023025568120*MeV, 1e-13 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled using OpenMC method, passing in
// parameters
TEUCHOS_UNIT_TEST( MaxwellFissionDistribution,
		   sampleAndRecordTrials_pass_parameters )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.1324998063336137;
  fake_stream[1] = 0.9247996934252033;
  fake_stream[2] = 0.1918514900811418;
  fake_stream[3] = 0.3062640867105594;
  fake_stream[4] = 0.8754839687423933;
  fake_stream[5] = 0.2274300298185482;
  fake_stream[6] = 0.9336967385663441;
  fake_stream[7] = 0.2459018944829507;
  fake_stream[8] = 0.4770873202414019;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incident_energy, nuclear_temperature, restriction_energy, sample;
  unsigned trials = 0;

  incident_energy = 0.5;
  nuclear_temperature = 0.1;
  restriction_energy = 0.01;

  sample = Utility::MaxwellFissionDistribution::sampleAndRecordTrials(incident_energy, nuclear_temperature, restriction_energy, trials);
  TEST_FLOATING_EQUALITY( sample, 0.20924646054839, 1e-13 );

  incident_energy = 0.75;
  nuclear_temperature = 0.5;
  restriction_energy = 0.25;

  sample = Utility::MaxwellFissionDistribution::sampleAndRecordTrials(incident_energy, nuclear_temperature, restriction_energy, trials);
  TEST_FLOATING_EQUALITY( sample, 0.41023025568120, 1e-13 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled using OpenMC method,
// passing in parameters
TEUCHOS_UNIT_TEST( UnitAwareMaxwellFissionDistribution,
		   sampleAndRecordTrials_pass_parameters )
{
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.1324998063336137;
  fake_stream[1] = 0.9247996934252033;
  fake_stream[2] = 0.1918514900811418;
  fake_stream[3] = 0.3062640867105594;
  fake_stream[4] = 0.8754839687423933;
  fake_stream[5] = 0.2274300298185482;
  fake_stream[6] = 0.9336967385663441;
  fake_stream[7] = 0.2459018944829507;
  fake_stream[8] = 0.4770873202414019;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<MegaElectronVolt> incident_energy, nuclear_temperature,
    restriction_energy, sample;
  unsigned trials = 0;

  incident_energy = 0.5*MeV;
  nuclear_temperature = 0.1*MeV;
  restriction_energy = 0.01*MeV;

  sample = Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,void>::sampleAndRecordTrials(incident_energy, nuclear_temperature, restriction_energy, trials);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.20924646054839*MeV, 1e-13 );

  incident_energy = 0.75*MeV;
  nuclear_temperature = 0.5*MeV;
  restriction_energy = 0.25*MeV;

  sample = Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>::sampleAndRecordTrials(incident_energy, nuclear_temperature, restriction_energy, trials);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.41023025568120*MeV, 1e-13 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( MaxwellFissionDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(), 0.9 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareMaxwellFissionDistribution,
		   getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfIndepVar(),
		       0.9*MeV );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( MaxwellFissionDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent
// variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareMaxwellFissionDistribution,
		   getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfIndepVar(),
		       0.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( MaxwellFissionDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( distribution->getDistributionType(),
		       Utility::MAXWELLFISSION_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
TEUCHOS_UNIT_TEST( UnitAwareMaxwellFissionDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getDistributionType(),
		       Utility::MAXWELLFISSION_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST( MaxwellFissionDistribution, isTabular )
{
  TEST_ASSERT( !distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular
TEUCHOS_UNIT_TEST( UnitAwareMaxwellFissionDistribution, isTabular )
{
  TEST_ASSERT( !unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
TEUCHOS_UNIT_TEST( MaxwellFissionDistribution, isContinuous )
{
  TEST_ASSERT( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is continuous
TEUCHOS_UNIT_TEST( UnitAwareMaxwellFissionDistribution, isContinuous )
{
  TEST_ASSERT( unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
TEUCHOS_UNIT_TEST( MaxwellFissionDistribution, isCompatibleWithInterpType )
{
  TEST_ASSERT( distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is compatible with the interp type
TEUCHOS_UNIT_TEST( UnitAwareMaxwellFissionDistribution,
                   isCompatibleWithInterpType )
{
  TEST_ASSERT( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  TEST_ASSERT( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to an xml file
TEUCHOS_UNIT_TEST( MaxwellFissionDistribution, toParameterList )
{
  Teuchos::RCP<Utility::MaxwellFissionDistribution> true_distribution =
    Teuchos::rcp_dynamic_cast<Utility::MaxwellFissionDistribution>( distribution );

  Teuchos::ParameterList parameter_list;

  parameter_list.set<Utility::MaxwellFissionDistribution>( "test distribution",
						     *true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
					"maxwellfission_dist_test_list.xml" );

  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list =
    Teuchos::getParametersFromXmlFile( "maxwellfission_dist_test_list.xml" );

  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<Utility::MaxwellFissionDistribution>
    copy_distribution( new Utility::MaxwellFissionDistribution );

  *copy_distribution = read_parameter_list->get<Utility::MaxwellFissionDistribution>(
							  "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be written to an xml file
TEUCHOS_UNIT_TEST( UnitAwareMaxwellFissionDistribution, toParameterList )
{
  typedef Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>
    UnitAwareMaxwellFissionDistribution;

  Teuchos::RCP<UnitAwareMaxwellFissionDistribution> true_distribution =
    Teuchos::rcp_dynamic_cast<UnitAwareMaxwellFissionDistribution>( unit_aware_distribution );

  Teuchos::ParameterList parameter_list;

  parameter_list.set<UnitAwareMaxwellFissionDistribution>( "test distribution",
							   *true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
					"unit_aware_maxwellfission_dist_test_list.xml" );

  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list =
    Teuchos::getParametersFromXmlFile( "unit_aware_maxwellfission_dist_test_list.xml" );

  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<UnitAwareMaxwellFissionDistribution>
    copy_distribution( new UnitAwareMaxwellFissionDistribution );

  *copy_distribution = read_parameter_list->get<UnitAwareMaxwellFissionDistribution>(
							  "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be read from an xml file
TEUCHOS_UNIT_TEST( MaxwellFissionDistribution, fromParameterList )
{
  double test_value_1;
  double test_value_2;

  Utility::MaxwellFissionDistribution read_distribution =
    test_dists_list->get<Utility::MaxwellFissionDistribution>( "Maxwell Fission Distribution A" );

  test_value_1 = 0.0 ;
  test_value_2 = sqrt(0.9)*exp(-0.9)/
    (sqrt( Utility::PhysicalConstants::pi)*0.5*erf(sqrt(0.9)) -
     sqrt(0.9)*exp(-0.9));

  TEST_EQUALITY_CONST( read_distribution.evaluatePDF( 0.0 ), test_value_1 );
  TEST_EQUALITY_CONST( read_distribution.evaluatePDF( 0.9 ), test_value_2 );
  TEST_EQUALITY_CONST( read_distribution.evaluatePDF( 1.0 ), test_value_1 );

  read_distribution =
    test_dists_list->get<Utility::MaxwellFissionDistribution>( "Maxwell Fission Distribution B" );

  test_value_1 = 0.0 ;
  test_value_2 = pow( 2.0, 1.5 ) * ( sqrt( Utility::PhysicalConstants::pi) * 0.5 * erf(sqrt(1.0)) - sqrt(1.0) * exp(-1.0) );
  test_value_2 = pow( test_value_2, -1.0 );
  test_value_2 = test_value_2 * exp( -0.5 );

  TEST_EQUALITY_CONST( read_distribution.evaluatePDF( 0.0 ), test_value_1 );
  TEST_EQUALITY_CONST( read_distribution.evaluatePDF( 1.0 ), test_value_2 );

  read_distribution =
    test_dists_list->get<Utility::MaxwellFissionDistribution>( "Maxwell Fission Distribution C" );

  test_value_1 = 0.0 ;
  test_value_2 = ( sqrt( Utility::PhysicalConstants::pi) * 0.5 * erf(sqrt(1.0)) - sqrt(1.0) * exp(-1.0) );
  test_value_2 = pow( test_value_2, -1.0 );
  test_value_2 = test_value_2 * exp( -1.0 );

  TEST_EQUALITY_CONST( read_distribution.evaluatePDF( 0.0 ), test_value_1 );
  TEST_EQUALITY_CONST( read_distribution.evaluatePDF( 1.0 ), test_value_2 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be read from an xml file
TEUCHOS_UNIT_TEST( UnitAwareMaxwellFissionDistribution, fromParameterList )
{
  typedef Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>
    UnitAwareMaxwellFissionDistribution;

  UnitAwareMaxwellFissionDistribution read_distribution =
    test_dists_list->get<UnitAwareMaxwellFissionDistribution>( "Unit-Aware Maxwell Fission Distribution A" );

  double scale_factor = sqrt(0.9)*exp(-0.9)/
    ( sqrt( Utility::PhysicalConstants::pi) * 0.5 * erf(sqrt(0.9)) -
      sqrt(0.9) * exp(-0.9) );

  UTILITY_TEST_FLOATING_EQUALITY( read_distribution.evaluate( 0.0*MeV ),
				  0.0*si::mole,
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( read_distribution.evaluatePDF( 0.0*MeV ),
				  0.0/MeV,
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( read_distribution.evaluate( 0.9*MeV ),
				  10.0*sqrt(0.9)*exp(-0.9)*si::mole,
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( read_distribution.evaluatePDF( 0.9*MeV ),
				  scale_factor/MeV,
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( read_distribution.evaluate( 1.0*MeV ),
				  0.0*si::mole,
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( read_distribution.evaluatePDF( 1.0*MeV ),
				  0.0/MeV,
				  1e-15 );

  read_distribution =
    test_dists_list->get<UnitAwareMaxwellFissionDistribution>( "Unit-Aware Maxwell Fission Distribution B" );

  scale_factor = exp( -0.5 )/
    ( pow( 2.0, 1.5 )*(sqrt(Utility::PhysicalConstants::pi)*0.5*erf(sqrt(1.0))-
		       sqrt(1.0)*exp(-1.0)) );

  UTILITY_TEST_FLOATING_EQUALITY( read_distribution.evaluatePDF( 0.0*MeV ),
				  0.0/MeV,
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( read_distribution.evaluatePDF( 1.0*MeV ),
				  scale_factor/MeV,
				  1e-15 );

  read_distribution =
    test_dists_list->get<UnitAwareMaxwellFissionDistribution>( "Unit-Aware Maxwell Fission Distribution C" );

  scale_factor = exp(-1.0 )/
    (sqrt(Utility::PhysicalConstants::pi)*0.5* erf(sqrt(1.0)) -
     sqrt(1.0)*exp(-1.0));

  UTILITY_TEST_FLOATING_EQUALITY( read_distribution.evaluatePDF( 0.0*MeV ),
				  0.0/MeV,
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( read_distribution.evaluatePDF( 1.0*MeV ),
				  scale_factor/MeV,
				  1e-15 );
}

//---------------------------------------------------------------------------//
// Check that distributions can be scaled
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( UnitAwareMaxwellFissionDistribution,
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
  Utility::UnitAwareMaxwellFissionDistribution<IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwareMaxwellFissionDistribution<IndepUnitA,DepUnitA>::fromUnitlessDistribution( *Teuchos::rcp_dynamic_cast<Utility::MaxwellFissionDistribution>( distribution ) );

  // Copy from distribution type A to distribution type B
  Utility::UnitAwareMaxwellFissionDistribution<IndepUnitB,DepUnitB>
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

  Utility::setQuantity( indep_quantity_a, 0.899999999999999 );
  Utility::setQuantity( inv_indep_quantity_a,
			sqrt(0.9)*exp(-0.9)/
                        (sqrt(Utility::PhysicalConstants::pi)*0.5*
                         erf(sqrt(0.9)) - sqrt(0.9)*exp(-0.9) ) );
  Utility::setQuantity( dep_quantity_a, sqrt(0.9)*exp(-0.9) );

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

  // std::cout << indep_quantity_a << " " << indep_quantity_b << " " << std::endl;
  // std::cout << inv_indep_quantity_a << " " << inv_indep_quantity_b << " " << std::endl;
  // std::cout << dep_quantity_a << " " << dep_quantity_b << " " << std::endl;
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

TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareMaxwellFissionDistribution,
				      explicit_conversion,
				      si_energy,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareMaxwellFissionDistribution,
				      explicit_conversion,
				      cgs_energy,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareMaxwellFissionDistribution,
				      explicit_conversion,
				      si_energy,
				      si_length,
				      cgs_energy,
				      cgs_length );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareMaxwellFissionDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_length,
				      si_energy,
				      si_length );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareMaxwellFissionDistribution,
				      explicit_conversion,
				      si_energy,
				      si_mass,
				      cgs_energy,
				      cgs_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareMaxwellFissionDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_mass,
				      si_energy,
				      si_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareMaxwellFissionDistribution,
				      explicit_conversion,
				      si_energy,
				      si_dimensionless,
				      cgs_energy,
				      cgs_dimensionless );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareMaxwellFissionDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_dimensionless,
				      si_energy,
				      si_dimensionless );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareMaxwellFissionDistribution,
				      explicit_conversion,
				      si_energy,
				      void,
				      cgs_energy,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareMaxwellFissionDistribution,
				      explicit_conversion,
				      cgs_energy,
				      void,
				      si_energy,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareMaxwellFissionDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareMaxwellFissionDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareMaxwellFissionDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      KiloElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareMaxwellFissionDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      MegaElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareMaxwellFissionDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareMaxwellFissionDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareMaxwellFissionDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      ElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareMaxwellFissionDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      MegaElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareMaxwellFissionDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareMaxwellFissionDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareMaxwellFissionDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      ElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareMaxwellFissionDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      KiloElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareMaxwellFissionDistribution,
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
  TEUCHOS_ADD_TYPE_CONVERTER( Utility::MaxwellFissionDistribution );
  typedef Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>
    UnitAwareMaxwellFissionDistribution;
  TEUCHOS_ADD_TYPE_CONVERTER( UnitAwareMaxwellFissionDistribution );

  test_dists_list = Teuchos::getParametersFromXmlFile( test_dists_xml_file );

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

UTILITY_CUSTOM_TEUCHOS_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstMaxwellFissionDistribution.cpp
//---------------------------------------------------------------------------//

