//---------------------------------------------------------------------------//
//!
//! \file   tstWattDistribution.cpp
//! \author Aaron Tumulak
//! \brief  Watt distribution unit tests.
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
#include "Utility_WattDistribution.hpp"
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
				 new Utility::WattDistribution( 1.0, 1.0, 1.0, 0.1 ) );

Teuchos::RCP<Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount> >
unit_aware_distribution( new Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 1e6*eV, 1e3*keV, 1e-6/eV, 0.1*MeV ) );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( WattDistribution, evaluate )
{
  double test_value_1 = 0.0 ;
  double test_value_2 = exp(-0.9)*sinh(sqrt(0.9));

  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), test_value_1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 0.9 ), test_value_2 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), test_value_1 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareWattDistribution, evaluate )
{
  double scale_factor = exp(-0.9)*sinh(sqrt(0.9));

  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV ),
		       0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.9*MeV ),
		       scale_factor*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.0*MeV ),
                       0.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( WattDistribution, evaluatePDF )
{
  double test_value_1 = 0.0 ;
  double test_value_2 = exp(-0.9)*sinh(sqrt(0.9))/
    (0.25*sqrt(Utility::PhysicalConstants::pi)*exp(0.25)*
     (erf(sqrt(0.9)-sqrt(0.25))+erf(sqrt(0.9)+sqrt(0.25))) -
     exp(-0.9)*sinh(sqrt(0.9)));

  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.0 ), test_value_1 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 0.9 ), test_value_2 );
  TEST_EQUALITY_CONST( distribution->evaluatePDF( 1.0 ), test_value_1 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareWattDistribution, evaluatePDF )
{
  double scale_factor = exp(-0.9)*sinh(sqrt(0.9))/
    (0.25*sqrt(Utility::PhysicalConstants::pi)*exp(0.25)*
     (erf(sqrt(0.9)-sqrt(0.25))+erf(sqrt(0.9)+sqrt(0.25))) -
     exp(-0.9)*sinh(sqrt(0.9)));

  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 0.0*MeV ),
		       0.0/MeV );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 0.9*MeV ),
                       scale_factor/MeV );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 1.0*MeV ),
		       0.0/MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled using OpenMC method
TEUCHOS_UNIT_TEST( WattDistribution, sample )
{
  std::vector<double> fake_stream( 15 );
  fake_stream[0] = 0.8110855833521807; // Maxwellian Distribution
  fake_stream[1] = 0.9603231091455754; // Sample Accepted. Sample is:
  fake_stream[2] = 0.3888878000049402; // 0.23654793157394
  fake_stream[3] = 0.1790067705163392; // Watt Distribution Sample Accepted. Sample is: 0.17431015530718
  fake_stream[4] = 0.7971990719536760; // Maxwellian Distribution
  fake_stream[5] = 0.0448247918373053; // Sample Rejected. Sample is:
  fake_stream[6] = 0.0375590391821071; // 3.32084968701263
  fake_stream[7] = 0.9522705508082248; // Maxwellian Distribution
  fake_stream[8] = 0.5691586660769004; // Sample Accepted. Sample is:
  fake_stream[9] = 0.0083308067369354; // 0.61240561891848
  fake_stream[10] = 0.6415677450291360; // Watt Distribution Sample Rejected. Sample is: 1.08397711671084
  fake_stream[11] = 0.8589987123720327; // Maxwellian Distribution
  fake_stream[12] = 0.4981431293148418; // Sample Accepted. Sample is:
  fake_stream[13] = 0.5932835342621010; // 0.39976547875177
  fake_stream[14] = 0.6731968005067009; // Watt Distribution Sample Accepted. Sample is: 0.86877979533891

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 0.17431015530718, 1e-13 );

  sample = distribution->sample();
  TEST_FLOATING_EQUALITY( sample, 0.86877979533891, 1e-13 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled using OpenMC method
TEUCHOS_UNIT_TEST( UnitAwareWattDistribution, sample )
{
  std::vector<double> fake_stream( 15 );
  fake_stream[0] = 0.8110855833521807; // Maxwellian Distribution
  fake_stream[1] = 0.9603231091455754; // Sample Accepted. Sample is:
  fake_stream[2] = 0.3888878000049402; // 0.23654793157394
  fake_stream[3] = 0.1790067705163392; // Watt Distribution Sample Accepted. Sample is: 0.17431015530718
  fake_stream[4] = 0.7971990719536760; // Maxwellian Distribution
  fake_stream[5] = 0.0448247918373053; // Sample Rejected. Sample is:
  fake_stream[6] = 0.0375590391821071; // 3.32084968701263
  fake_stream[7] = 0.9522705508082248; // Maxwellian Distribution
  fake_stream[8] = 0.5691586660769004; // Sample Accepted. Sample is:
  fake_stream[9] = 0.0083308067369354; // 0.61240561891848
  fake_stream[10] = 0.6415677450291360; // Watt Distribution Sample Rejected. Sample is: 1.08397711671084
  fake_stream[11] = 0.8589987123720327; // Maxwellian Distribution
  fake_stream[12] = 0.4981431293148418; // Sample Accepted. Sample is:
  fake_stream[13] = 0.5932835342621010; // 0.39976547875177
  fake_stream[14] = 0.6731968005067009; // Watt Distribution Sample Accepted. Sample is: 0.86877979533891

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  quantity<MegaElectronVolt> sample = unit_aware_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.17431015530718*MeV, 1e-13 );

  sample = unit_aware_distribution->sample();
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.86877979533891*MeV, 1e-13 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled using OpenMC method, passing in
// parameters
TEUCHOS_UNIT_TEST( WattDistribution, sample_pass_parameters )
{
  std::vector<double> fake_stream( 15 );
  fake_stream[0] = 0.6617443503056450; // Maxwellian Distribution
  fake_stream[1] = 0.8510592242616175; // Sample Accepted. Sample is:
  fake_stream[2] = 0.5401745197210969; // 0.09667248521245
  fake_stream[3] = 0.2005969462099806; // Watt Distribution Sample Accepted. Sample is: 0.07927727029875
  fake_stream[4] = 0.5189418543931951; // Maxwellian Distribution
  fake_stream[5] = 0.7484231272861934; // Sample Rejected. Sample is:
  fake_stream[6] = 0.8345865134048199; // 0.13501824430785
  fake_stream[7] = 0.8704061668810904; // Maxwellian Distribution
  fake_stream[8] = 0.5575773053122431; // Sample Accepted. Sample is:
  fake_stream[9] = 0.7452925729418971; // 0.04548390223293
  fake_stream[10] = 0.6556974287666129; // Watt Distribution Sample Rejected. Sample is: 0.05068410532744
  fake_stream[11] = 0.8140855348977614; // Maxwellian Distribution
  fake_stream[12] = 0.5750169688125915; // Sample Accepted. Sample is:
  fake_stream[13] = 0.8372435273691630; // 0.04821527540845
  fake_stream[14] = 0.4721727279140688; // Watt Distribution Sample Accepted. Sample is: 0.04844237604136

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incident_energy, a_parameter, b_parameter, restriction_energy, sample;

  incident_energy = 0.5;
  a_parameter = 0.2;
  b_parameter = 0.3;
  restriction_energy = 0.4;

  sample = Utility::WattDistribution::sample( incident_energy, a_parameter, b_parameter, restriction_energy );
  TEST_FLOATING_EQUALITY( sample, 0.07927727029875, 1e-13 );

  incident_energy = 0.3;
  a_parameter = 0.2;
  b_parameter = 0.1;
  restriction_energy = 0.25;

  sample = Utility::WattDistribution::sample( incident_energy, a_parameter, b_parameter, restriction_energy );
  TEST_FLOATING_EQUALITY( sample, 0.04844237604136, 1e-13 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled using OpenMC method,
// passing in parameters
TEUCHOS_UNIT_TEST( UnitAwareWattDistribution,
		   sample_pass_parameters )
{
  std::vector<double> fake_stream( 15 );
  fake_stream[0] = 0.6617443503056450; // Maxwellian Distribution
  fake_stream[1] = 0.8510592242616175; // Sample Accepted. Sample is:
  fake_stream[2] = 0.5401745197210969; // 0.09667248521245
  fake_stream[3] = 0.2005969462099806; // Watt Distribution Sample Accepted. Sample is: 0.07927727029875
  fake_stream[4] = 0.5189418543931951; // Maxwellian Distribution
  fake_stream[5] = 0.7484231272861934; // Sample Rejected. Sample is:
  fake_stream[6] = 0.8345865134048199; // 0.13501824430785
  fake_stream[7] = 0.8704061668810904; // Maxwellian Distribution
  fake_stream[8] = 0.5575773053122431; // Sample Accepted. Sample is:
  fake_stream[9] = 0.7452925729418971; // 0.04548390223293
  fake_stream[10] = 0.6556974287666129; // Watt Distribution Sample Rejected. Sample is: 0.05068410532744
  fake_stream[11] = 0.8140855348977614; // Maxwellian Distribution
  fake_stream[12] = 0.5750169688125915; // Sample Accepted. Sample is:
  fake_stream[13] = 0.8372435273691630; // 0.04821527540845
  fake_stream[14] = 0.4721727279140688; // Watt Distribution Sample Accepted. Sample is: 0.04844237604136

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::UnitAwareWattDistribution<MegaElectronVolt>::IndepQuantity incident_energy, a_parameter, restriction_energy, sample;

  Utility::UnitAwareWattDistribution<MegaElectronVolt>::InverseIndepQuantity b_parameter;

  incident_energy = 0.5*MeV;
  a_parameter = 0.2*MeV;
  b_parameter = 0.3/MeV;
  restriction_energy = 0.4*MeV;

  sample = Utility::UnitAwareWattDistribution<MegaElectronVolt>::sample( incident_energy, a_parameter, b_parameter, restriction_energy );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.07927727029875*MeV, 1e-13 );

  incident_energy = 0.3*MeV;
  a_parameter = 0.2*MeV;
  b_parameter = 0.1/MeV;
  restriction_energy = 0.25*MeV;

  sample = Utility::UnitAwareWattDistribution<MegaElectronVolt>::sample( incident_energy, a_parameter, b_parameter, restriction_energy );
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.04844237604136*MeV, 1e-13 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled using OpenMC method, passing in
// parameters
TEUCHOS_UNIT_TEST( WattDistribution, sampleAndRecordTrials_pass_parameters )
{
  std::vector<double> fake_stream( 15 );
  fake_stream[0] = 0.6617443503056450; // Maxwellian Distribution
  fake_stream[1] = 0.8510592242616175; // Sample Accepted. Sample is:
  fake_stream[2] = 0.5401745197210969; // 0.09667248521245
  fake_stream[3] = 0.2005969462099806; // Watt Distribution Sample Accepted. Sample is: 0.07927727029875
  fake_stream[4] = 0.5189418543931951; // Maxwellian Distribution
  fake_stream[5] = 0.7484231272861934; // Sample Rejected. Sample is:
  fake_stream[6] = 0.8345865134048199; // 0.13501824430785
  fake_stream[7] = 0.8704061668810904; // Maxwellian Distribution
  fake_stream[8] = 0.5575773053122431; // Sample Accepted. Sample is:
  fake_stream[9] = 0.7452925729418971; // 0.04548390223293
  fake_stream[10] = 0.6556974287666129; // Watt Distribution Sample Rejected. Sample is: 0.05068410532744
  fake_stream[11] = 0.8140855348977614; // Maxwellian Distribution
  fake_stream[12] = 0.5750169688125915; // Sample Accepted. Sample is:
  fake_stream[13] = 0.8372435273691630; // 0.04821527540845
  fake_stream[14] = 0.4721727279140688; // Watt Distribution Sample Accepted. Sample is: 0.04844237604136

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  double incident_energy, a_parameter, b_parameter, restriction_energy, sample;
  unsigned trials = 0;

  incident_energy = 0.5;
  a_parameter = 0.2;
  b_parameter = 0.3;
  restriction_energy = 0.4;

  sample = Utility::WattDistribution::sampleAndRecordTrials(incident_energy, a_parameter, b_parameter, restriction_energy, trials);
  TEST_FLOATING_EQUALITY( sample, 0.07927727029875, 1e-13 );
  TEST_EQUALITY_CONST( trials, 1.0 );

  incident_energy = 0.3;
  a_parameter = 0.2;
  b_parameter = 0.1;
  restriction_energy = 0.25;

  sample = Utility::WattDistribution::sampleAndRecordTrials(incident_energy, a_parameter, b_parameter, restriction_energy, trials);
  TEST_FLOATING_EQUALITY( sample, 0.04844237604136, 1e-13 );
  TEST_EQUALITY_CONST( trials, 4.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled using OpenMC method,
// passing in parameters
TEUCHOS_UNIT_TEST( UnitAwareWattDistribution,
		   sampleAndRecordTrials_pass_parameters )
{
  std::vector<double> fake_stream( 15 );
  fake_stream[0] = 0.6617443503056450; // Maxwellian Distribution
  fake_stream[1] = 0.8510592242616175; // Sample Accepted. Sample is:
  fake_stream[2] = 0.5401745197210969; // 0.09667248521245
  fake_stream[3] = 0.2005969462099806; // Watt Distribution Sample Accepted. Sample is: 0.07927727029875
  fake_stream[4] = 0.5189418543931951; // Maxwellian Distribution
  fake_stream[5] = 0.7484231272861934; // Sample Rejected. Sample is:
  fake_stream[6] = 0.8345865134048199; // 0.13501824430785
  fake_stream[7] = 0.8704061668810904; // Maxwellian Distribution
  fake_stream[8] = 0.5575773053122431; // Sample Accepted. Sample is:
  fake_stream[9] = 0.7452925729418971; // 0.04548390223293
  fake_stream[10] = 0.6556974287666129; // Watt Distribution Sample Rejected. Sample is: 0.05068410532744
  fake_stream[11] = 0.8140855348977614; // Maxwellian Distribution
  fake_stream[12] = 0.5750169688125915; // Sample Accepted. Sample is:
  fake_stream[13] = 0.8372435273691630; // 0.04821527540845
  fake_stream[14] = 0.4721727279140688; // Watt Distribution Sample Accepted. Sample is: 0.04844237604136

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount>::IndepQuantity incident_energy, a_parameter, restriction_energy, sample;

  Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount>::InverseIndepQuantity b_parameter;

  unsigned trials = 0;

  incident_energy = 0.5*MeV;
  a_parameter = 0.2*MeV;
  b_parameter = 0.3/MeV;
  restriction_energy = 0.4*MeV;

  sample = Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>::sampleAndRecordTrials(incident_energy, a_parameter, b_parameter, restriction_energy, trials);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.07927727029875*MeV, 1e-13 );
  TEST_EQUALITY_CONST( trials, 1.0 );

  incident_energy = 0.3*MeV;
  a_parameter = 0.2*MeV;
  b_parameter = 0.1/MeV;
  restriction_energy = 0.25*MeV;

  sample = Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>::sampleAndRecordTrials(incident_energy, a_parameter, b_parameter, restriction_energy, trials);
  UTILITY_TEST_FLOATING_EQUALITY( sample, 0.04844237604136*MeV, 1e-13 );
  TEST_EQUALITY_CONST( trials, 4.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( WattDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getUpperBoundOfIndepVar(), 0.9 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareWattDistribution, getUpperBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getUpperBoundOfIndepVar(),
		       0.9*MeV );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
TEUCHOS_UNIT_TEST( WattDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( distribution->getLowerBoundOfIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent
// variable can be returned
TEUCHOS_UNIT_TEST( UnitAwareWattDistribution, getLowerBoundOfIndepVar )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getLowerBoundOfIndepVar(),
		       0.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
TEUCHOS_UNIT_TEST( WattDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( distribution->getDistributionType(),
		       Utility::WATT_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
TEUCHOS_UNIT_TEST( UnitAwareWattDistribution, getDistributionType )
{
  TEST_EQUALITY_CONST( unit_aware_distribution->getDistributionType(),
		       Utility::WATT_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
TEUCHOS_UNIT_TEST( WattDistribution, isTabular )
{
  TEST_ASSERT( !distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular
TEUCHOS_UNIT_TEST( UnitAwareWattDistribution, isTabular )
{
  TEST_ASSERT( !unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
TEUCHOS_UNIT_TEST( WattDistribution, isContinuous )
{
  TEST_ASSERT( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is continuous
TEUCHOS_UNIT_TEST( UnitAwareWattDistribution, isContinuous )
{
  TEST_ASSERT( unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to an xml file
TEUCHOS_UNIT_TEST( WattDistribution, toParameterList )
{
  Teuchos::RCP<Utility::WattDistribution> true_distribution =
  Teuchos::rcp_dynamic_cast<Utility::WattDistribution>( distribution );

  Teuchos::ParameterList parameter_list;

  parameter_list.set<Utility::WattDistribution>( "test distribution",
                                                  *true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
                                       "watt_dist_test_list.xml" );

  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list =
  Teuchos::getParametersFromXmlFile( "watt_dist_test_list.xml" );

  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<Utility::WattDistribution>
  copy_distribution( new Utility::WattDistribution );

  *copy_distribution = read_parameter_list->get<Utility::WattDistribution>(
                                                                             "test distribution");

  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be written to an xml file
TEUCHOS_UNIT_TEST( UnitAwareWattDistribution, toParameterList )
{
  typedef Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> UnitAwareWattDistribution;

  Teuchos::RCP<UnitAwareWattDistribution> true_distribution =
  Teuchos::rcp_dynamic_cast<UnitAwareWattDistribution>( unit_aware_distribution );

  Teuchos::ParameterList parameter_list;

  parameter_list.set<UnitAwareWattDistribution>( "test distribution",
                                                  *true_distribution );

  Teuchos::writeParameterListToXmlFile( parameter_list,
                                       "unit_aware_watt_dist_test_list.xml" );

  Teuchos::RCP<Teuchos::ParameterList> read_parameter_list =
  Teuchos::getParametersFromXmlFile( "unit_aware_watt_dist_test_list.xml" );

  TEST_EQUALITY( parameter_list, *read_parameter_list );

  Teuchos::RCP<UnitAwareWattDistribution>
  copy_distribution( new UnitAwareWattDistribution );

  *copy_distribution = read_parameter_list->get<UnitAwareWattDistribution>(
							 "test distribution" );

  TEST_EQUALITY( *copy_distribution, *true_distribution );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be read from an xml file
TEUCHOS_UNIT_TEST( WattDistribution, fromParameterList )
{
  double test_value_1;
  double test_value_2;

  Utility::WattDistribution read_distribution =
    test_dists_list->get<Utility::WattDistribution>( "Watt Distribution A" );

  test_value_1 = 0.0 ;
  test_value_2 = exp(-0.9)*sinh(sqrt(0.9))/
    (0.25*sqrt(Utility::PhysicalConstants::pi)*exp(0.25)*
     (erf(sqrt(0.9)-sqrt(0.25))+erf(sqrt(0.9)+sqrt(0.25))) -
     exp(-0.9)*sinh(sqrt(0.9)));

  TEST_EQUALITY_CONST( read_distribution.evaluatePDF( 0.0 ), test_value_1 );
  TEST_FLOATING_EQUALITY( read_distribution.evaluatePDF( 0.9 ),
			  test_value_2,
			  1e-15 );
  TEST_EQUALITY_CONST( read_distribution.evaluatePDF( 1.0 ), test_value_1 );

   read_distribution =
    test_dists_list->get<Utility::WattDistribution>( "Watt Distribution B" );

  test_value_1 = 0.0 ;
  test_value_2 = 0.25 * sqrt( Utility::PhysicalConstants::pi * pow( 2.0, 3.0 ) * 1.0 )
    * exp( 0.25 * 2.0 ) * ( erf( sqrt( 1.5 ) - sqrt( 0.25 * 2.0 ) )
    + erf( sqrt( 1.5 ) + sqrt( 0.25 * 2.0 ) ) )
    - 2.0 * exp( - 1.5 ) * sinh( sqrt( 3.0 ) );
  test_value_2 = pow( test_value_2, -1.0 ) * exp( -0.5 ) * sinh( 1.0 );

  TEST_EQUALITY_CONST( read_distribution.evaluatePDF( 0.0 ), test_value_1 );
  TEST_FLOATING_EQUALITY( read_distribution.evaluatePDF( 1.0 ),
			  test_value_2,
			  1e-15 );

}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be read from an xml file
TEUCHOS_UNIT_TEST( UnitAwareWattDistribution, fromParameterList )
{
  typedef Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> UnitAwareWattDistribution;

  double scale_factor;
  scale_factor = exp(-0.9)*sinh(sqrt(0.9))/
    (0.25*sqrt(Utility::PhysicalConstants::pi)*exp(0.25)*
     (erf(sqrt(0.9)-sqrt(0.25))+erf(sqrt(0.9)+sqrt(0.25))) -
     exp(-0.9)*sinh(sqrt(0.9)));

  UnitAwareWattDistribution read_distribution =
    test_dists_list->get<UnitAwareWattDistribution>( "Unit-Aware Watt Distribution A" );

  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0*MeV ), 0.0*si::mole );
  UTILITY_TEST_FLOATING_EQUALITY( read_distribution.evaluate( 0.9*MeV ),
				  exp(-0.9)*sinh(sqrt(0.9))*si::mole,
				  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( read_distribution.evaluatePDF( 0.9*MeV ),
				  scale_factor/MeV,
				  1e-15 );
  TEST_EQUALITY_CONST( read_distribution.evaluate( 1.0*MeV ), 0.0*si::mole );

  read_distribution =
    test_dists_list->get<UnitAwareWattDistribution>( "Unit-Aware Watt Distribution B" );

   scale_factor = exp( -0.5 )*sinh( 1.0 );
   scale_factor /= 0.25*sqrt( Utility::PhysicalConstants::pi*pow( 2.0, 3.0 ) )*
     exp( 0.25 * 2.0 )*( erf( sqrt( 1.5 ) - sqrt( 0.25 * 2.0 ) ) +
			 erf( sqrt( 1.5 ) + sqrt( 0.25 * 2.0 ) ) ) -
     2.0*exp( -1.5 )*sinh( sqrt( 3.0 ) );

   TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0*MeV ), 0.0*si::mole );
   UTILITY_TEST_FLOATING_EQUALITY( read_distribution.evaluate( 1.0*MeV ),
				   2*exp( -0.5 )*sinh( 1.0 )*si::mole,
				   1e-15 );
   UTILITY_TEST_FLOATING_EQUALITY( read_distribution.evaluatePDF( 1.0*MeV ),
				   scale_factor/MeV,
				   1e-15 );

}

//---------------------------------------------------------------------------//
// Check that distributions can be scaled
TEUCHOS_UNIT_TEST_TEMPLATE_4_DECL( UnitAwareWattDistribution,
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
  Utility::UnitAwareWattDistribution<IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwareWattDistribution<IndepUnitA,DepUnitA>::fromUnitlessDistribution( *Teuchos::rcp_dynamic_cast<Utility::WattDistribution>( distribution ) );

  // Copy from distribution type A to distribution type B (explicit cast)
  Utility::UnitAwareWattDistribution<IndepUnitB,DepUnitB>
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
                        exp(-0.9)*sinh(sqrt(0.9))/
                        (0.25*sqrt(Utility::PhysicalConstants::pi)*exp(0.25)*
                         (erf(sqrt(0.9)-sqrt(0.25))+erf(sqrt(0.9)+sqrt(0.25)))-
                         exp(-0.9)*sinh(sqrt(0.9))) );
  Utility::setQuantity( dep_quantity_a,
			exp(-0.9)*sinh(sqrt(0.9)) );

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

TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareWattDistribution,
				      explicit_conversion,
				      si_energy,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareWattDistribution,
				      explicit_conversion,
				      cgs_energy,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareWattDistribution,
				      explicit_conversion,
				      si_energy,
				      si_length,
				      cgs_energy,
				      cgs_length );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareWattDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_length,
				      si_energy,
				      si_length );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareWattDistribution,
				      explicit_conversion,
				      si_energy,
				      si_mass,
				      cgs_energy,
				      cgs_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareWattDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_mass,
				      si_energy,
				      si_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareWattDistribution,
				      explicit_conversion,
				      si_energy,
				      si_dimensionless,
				      cgs_energy,
				      cgs_dimensionless );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareWattDistribution,
				      explicit_conversion,
				      cgs_energy,
				      cgs_dimensionless,
				      si_energy,
				      si_dimensionless );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareWattDistribution,
				      explicit_conversion,
				      si_energy,
				      void,
				      cgs_energy,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareWattDistribution,
				      explicit_conversion,
				      cgs_energy,
				      void,
				      si_energy,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareWattDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareWattDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareWattDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      KiloElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareWattDistribution,
				      explicit_conversion,
				      ElectronVolt,
				      si_amount,
				      MegaElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareWattDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareWattDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareWattDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      ElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareWattDistribution,
				      explicit_conversion,
				      KiloElectronVolt,
				      si_amount,
				      MegaElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareWattDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareWattDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      cgs_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareWattDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      ElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareWattDistribution,
				      explicit_conversion,
				      MegaElectronVolt,
				      si_amount,
				      KiloElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_4_INSTANT( UnitAwareWattDistribution,
				      explicit_conversion,
				      void,
				      MegaElectronVolt,
				      void,
				      KiloElectronVolt );

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

  TEUCHOS_ADD_TYPE_CONVERTER( Utility::WattDistribution );
  typedef Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> UnitAwareWattDistribution;
  TEUCHOS_ADD_TYPE_CONVERTER( UnitAwareWattDistribution );

  test_dists_list = Teuchos::getParametersFromXmlFile( test_dists_xml_file );

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
// end tstWattDistribution.cpp
//---------------------------------------------------------------------------//
