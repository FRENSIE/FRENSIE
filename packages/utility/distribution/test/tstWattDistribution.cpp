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

// FRENSIE Includes
#include "Utility_WattDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_ElectronVoltUnit.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using boost::units::quantity;
using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

typedef TestArchiveHelper::TestArchives TestArchives;

typedef std::tuple<
  std::tuple<si::energy,si::amount,cgs::energy,si::amount>,
  std::tuple<cgs::energy,si::amount,si::energy,si::amount>,
  std::tuple<si::energy,si::length,cgs::energy,cgs::length>,
  std::tuple<cgs::energy,cgs::length,si::energy,si::length>,
  std::tuple<si::energy,si::mass,cgs::energy,cgs::mass>,
  std::tuple<cgs::energy,cgs::mass,si::energy,si::mass>,
  std::tuple<si::energy,si::dimensionless,cgs::energy,cgs::dimensionless>,
  std::tuple<cgs::energy,cgs::dimensionless,si::energy,si::dimensionless>,
  std::tuple<si::energy,void*,cgs::energy,void*>,
  std::tuple<cgs::energy,void*,si::energy,void*>,
  std::tuple<ElectronVolt,si::amount,si::energy,si::amount>,
  std::tuple<ElectronVolt,si::amount,cgs::energy,si::amount>,
  std::tuple<ElectronVolt,si::amount,KiloElectronVolt,si::amount>,
  std::tuple<ElectronVolt,si::amount,MegaElectronVolt,si::amount>,
  std::tuple<KiloElectronVolt,si::amount,si::energy,si::amount>,
  std::tuple<KiloElectronVolt,si::amount,cgs::energy,si::amount>,
  std::tuple<KiloElectronVolt,si::amount,ElectronVolt,si::amount>,
  std::tuple<KiloElectronVolt,si::amount,MegaElectronVolt,si::amount>,
  std::tuple<MegaElectronVolt,si::amount,si::energy,si::amount>,
  std::tuple<MegaElectronVolt,si::amount,cgs::energy,si::amount>,
  std::tuple<MegaElectronVolt,si::amount,ElectronVolt,si::amount>,
  std::tuple<MegaElectronVolt,si::amount,KiloElectronVolt,si::amount>,
  std::tuple<void*,MegaElectronVolt,void*,KiloElectronVolt>
 > TestUnitTypeQuads;

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<Utility::UnivariateDistribution> distribution(
			 new Utility::WattDistribution( 1.0, 1.0, 1.0, 0.1 ) );

std::shared_ptr<Utility::UnitAwareUnivariateDistribution<MegaElectronVolt,si::amount> >
unit_aware_distribution( new Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 1e6*eV, 1e3*keV, 1e-6/eV, 0.1*MeV ) );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( WattDistribution, evaluate )
{
  double test_value_1 = 0.0 ;
  double test_value_2 = exp(-0.9)*sinh(sqrt(0.9));

  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0 ), test_value_1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.9 ), test_value_2 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.0 ), test_value_1 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
FRENSIE_UNIT_TEST( UnitAwareWattDistribution, evaluate )
{
  double scale_factor = exp(-0.9)*sinh(sqrt(0.9));

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV ),
		       0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.9*MeV ),
		       scale_factor*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.0*MeV ),
                       0.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
FRENSIE_UNIT_TEST( WattDistribution, evaluatePDF )
{
  double test_value_1 = 0.0 ;
  double test_value_2 = exp(-0.9)*sinh(sqrt(0.9))/
    (0.25*sqrt(Utility::PhysicalConstants::pi)*exp(0.25)*
     (erf(sqrt(0.9)-sqrt(0.25))+erf(sqrt(0.9)+sqrt(0.25))) -
     exp(-0.9)*sinh(sqrt(0.9)));

  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.0 ), test_value_1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.9 ), test_value_2 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 1.0 ), test_value_1 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwareWattDistribution, evaluatePDF )
{
  double scale_factor = exp(-0.9)*sinh(sqrt(0.9))/
    (0.25*sqrt(Utility::PhysicalConstants::pi)*exp(0.25)*
     (erf(sqrt(0.9)-sqrt(0.25))+erf(sqrt(0.9)+sqrt(0.25))) -
     exp(-0.9)*sinh(sqrt(0.9)));

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 0.0*MeV ),
		       0.0/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 0.9*MeV ),
                       scale_factor/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 1.0*MeV ),
		       0.0/MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled using OpenMC method
FRENSIE_UNIT_TEST( WattDistribution, sample )
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
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.17431015530718, 1e-13 );

  sample = distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.86877979533891, 1e-13 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled using OpenMC method
FRENSIE_UNIT_TEST( UnitAwareWattDistribution, sample )
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
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.17431015530718*MeV, 1e-13 );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.86877979533891*MeV, 1e-13 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled using OpenMC method, passing in
// parameters
FRENSIE_UNIT_TEST( WattDistribution, sample_pass_parameters )
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
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.07927727029875, 1e-13 );

  incident_energy = 0.3;
  a_parameter = 0.2;
  b_parameter = 0.1;
  restriction_energy = 0.25;

  sample = Utility::WattDistribution::sample( incident_energy, a_parameter, b_parameter, restriction_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.04844237604136, 1e-13 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled using OpenMC method,
// passing in parameters
FRENSIE_UNIT_TEST( UnitAwareWattDistribution,
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
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.07927727029875*MeV, 1e-13 );

  incident_energy = 0.3*MeV;
  a_parameter = 0.2*MeV;
  b_parameter = 0.1/MeV;
  restriction_energy = 0.25*MeV;

  sample = Utility::UnitAwareWattDistribution<MegaElectronVolt>::sample( incident_energy, a_parameter, b_parameter, restriction_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.04844237604136*MeV, 1e-13 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled using OpenMC method, passing in
// parameters
FRENSIE_UNIT_TEST( WattDistribution, sampleAndRecordTrials_pass_parameters )
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
  Utility::DistributionTraits::Counter trials = 0;

  incident_energy = 0.5;
  a_parameter = 0.2;
  b_parameter = 0.3;
  restriction_energy = 0.4;

  sample = Utility::WattDistribution::sampleAndRecordTrials(incident_energy, a_parameter, b_parameter, restriction_energy, trials);
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.07927727029875, 1e-13 );
  FRENSIE_CHECK_EQUAL( trials, 1.0 );

  incident_energy = 0.3;
  a_parameter = 0.2;
  b_parameter = 0.1;
  restriction_energy = 0.25;

  sample = Utility::WattDistribution::sampleAndRecordTrials(incident_energy, a_parameter, b_parameter, restriction_energy, trials);
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.04844237604136, 1e-13 );
  FRENSIE_CHECK_EQUAL( trials, 4.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled using OpenMC method,
// passing in parameters
FRENSIE_UNIT_TEST( UnitAwareWattDistribution,
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

  Utility::UnitAwareUnivariateDistribution<MegaElectronVolt,si::amount>::IndepQuantity incident_energy, a_parameter, restriction_energy, sample;

  Utility::UnitAwareUnivariateDistribution<MegaElectronVolt,si::amount>::InverseIndepQuantity b_parameter;

  Utility::DistributionTraits::Counter trials = 0;

  incident_energy = 0.5*MeV;
  a_parameter = 0.2*MeV;
  b_parameter = 0.3/MeV;
  restriction_energy = 0.4*MeV;

  sample = Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>::sampleAndRecordTrials(incident_energy, a_parameter, b_parameter, restriction_energy, trials);
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.07927727029875*MeV, 1e-13 );
  FRENSIE_CHECK_EQUAL( trials, 1.0 );

  incident_energy = 0.3*MeV;
  a_parameter = 0.2*MeV;
  b_parameter = 0.1/MeV;
  restriction_energy = 0.25*MeV;

  sample = Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>::sampleAndRecordTrials(incident_energy, a_parameter, b_parameter, restriction_energy, trials);
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.04844237604136*MeV, 1e-13 );
  FRENSIE_CHECK_EQUAL( trials, 4.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST( WattDistribution, getUpperBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfIndepVar(), 0.9 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST( UnitAwareWattDistribution, getUpperBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfIndepVar(),
		       0.9*MeV );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST( WattDistribution, getLowerBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST( UnitAwareWattDistribution, getLowerBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfIndepVar(),
		       0.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
FRENSIE_UNIT_TEST( WattDistribution, getDistributionType )
{
  FRENSIE_CHECK_EQUAL( distribution->getDistributionType(),
		       Utility::WATT_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
FRENSIE_UNIT_TEST( UnitAwareWattDistribution, getDistributionType )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getDistributionType(),
		       Utility::WATT_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
FRENSIE_UNIT_TEST( WattDistribution, isTabular )
{
  FRENSIE_CHECK( !distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular
FRENSIE_UNIT_TEST( UnitAwareWattDistribution, isTabular )
{
  FRENSIE_CHECK( !unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
FRENSIE_UNIT_TEST( WattDistribution, isContinuous )
{
  FRENSIE_CHECK( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is continuous
FRENSIE_UNIT_TEST( UnitAwareWattDistribution, isContinuous )
{
  FRENSIE_CHECK( unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
FRENSIE_UNIT_TEST( WattDistribution, isCompatibleWithInterpType )
{
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is compatible with the interp type
FRENSIE_UNIT_TEST( UnitAwareWattDistribution, isCompatibleWithInterpType )
{
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be placed in a stream
FRENSIE_UNIT_TEST( WattDistribution, ostream_operator )
{
  std::ostringstream oss;
  
  oss << Utility::WattDistribution();

  Utility::VariantMap dist_data =
    Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Watt Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["incident energy"].toDouble(), 1.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["a parameter"].toDouble(), 1.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["b parameter"].toDouble(), 1.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["restriction energy"].toDouble(), 0.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 1.0, SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << Utility::WattDistribution( 3.0 );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Watt Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["incident energy"].toDouble(), 3.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["a parameter"].toDouble(), 1.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["b parameter"].toDouble(), 1.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["restriction energy"].toDouble(), 0.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 1.0, SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << Utility::WattDistribution( 5.0, 4.0 );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Watt Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["incident energy"].toDouble(), 5.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["a parameter"].toDouble(), 4.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["b parameter"].toDouble(), 1.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["restriction energy"].toDouble(), 0.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 1.0, SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << Utility::WattDistribution( 5.0, 4.0, 3.0 );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Watt Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["incident energy"].toDouble(), 5.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["a parameter"].toDouble(), 4.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["b parameter"].toDouble(), 3.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["restriction energy"].toDouble(), 0.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 1.0, SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0 );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Watt Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["incident energy"].toDouble(), 5.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["a parameter"].toDouble(), 4.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["b parameter"].toDouble(), 3.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["restriction energy"].toDouble(), 2.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 1.0, SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0, 0.5 );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Watt Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["incident energy"].toDouble(), 5.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["a parameter"].toDouble(), 4.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["b parameter"].toDouble(), 3.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["restriction energy"].toDouble(), 2.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 0.5, SHOW_LHS );

  oss.str( "" );
  oss.clear();

  std::shared_ptr<Utility::WattDistribution> shared_dist( new Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0, 0.5 ) );
  
  oss << *shared_dist;

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Watt Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(), "void", SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["incident energy"].toDouble(), 5.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["a parameter"].toDouble(), 4.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["b parameter"].toDouble(), 3.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["restriction energy"].toDouble(), 2.0, SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 0.5, SHOW_LHS );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST( UnitAwareWattDistribution, ostream_operator )
{
  std::ostringstream oss;
  
  oss << Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>();

  Utility::VariantMap dist_data =
    Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Watt Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<MegaElectronVolt>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["incident energy"].toType<quantity<MegaElectronVolt> >(),
                       1.0*MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["a parameter"].toType<quantity<MegaElectronVolt> >(),
                       1.0*MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["b parameter"].toType<quantity<Utility::UnitTraits<MegaElectronVolt>::InverseUnit> >(),
                       1.0/MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["restriction energy"].toType<quantity<MegaElectronVolt> >(),
                       0.0*MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 1.0, SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 3.0*MeV );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Watt Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<MegaElectronVolt>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["incident energy"].toType<quantity<MegaElectronVolt> >(),
                       3.0*MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["a parameter"].toType<quantity<MegaElectronVolt> >(),
                       1.0*MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["b parameter"].toType<quantity<Utility::UnitTraits<MegaElectronVolt>::InverseUnit> >(),
                       1.0/MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["restriction energy"].toType<quantity<MegaElectronVolt> >(),
                       0.0*MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 1.0, SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Watt Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<MegaElectronVolt>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["incident energy"].toType<quantity<MegaElectronVolt> >(),
                       5.0*MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["a parameter"].toType<quantity<MegaElectronVolt> >(),
                       4.0*MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["b parameter"].toType<quantity<Utility::UnitTraits<MegaElectronVolt>::InverseUnit> >(),
                       1.0/MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["restriction energy"].toType<quantity<MegaElectronVolt> >(),
                       0.0*MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 1.0, SHOW_LHS );
  
  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Watt Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<MegaElectronVolt>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["incident energy"].toType<quantity<MegaElectronVolt> >(),
                       5.0*MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["a parameter"].toType<quantity<MegaElectronVolt> >(),
                       4.0*MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["b parameter"].toType<quantity<Utility::UnitTraits<MegaElectronVolt>::InverseUnit> >(),
                       3.0/MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["restriction energy"].toType<quantity<MegaElectronVolt> >(),
                       0.0*MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 1.0, SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Watt Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<MegaElectronVolt>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["incident energy"].toType<quantity<MegaElectronVolt> >(),
                       5.0*MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["a parameter"].toType<quantity<MegaElectronVolt> >(),
                       4.0*MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["b parameter"].toType<quantity<Utility::UnitTraits<MegaElectronVolt>::InverseUnit> >(),
                       3.0/MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["restriction energy"].toType<quantity<MegaElectronVolt> >(),
                       2.0*MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 1.0, SHOW_LHS );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV, 0.5 );

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Watt Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<MegaElectronVolt>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["incident energy"].toType<quantity<MegaElectronVolt> >(),
                       5.0*MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["a parameter"].toType<quantity<MegaElectronVolt> >(),
                       4.0*MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["b parameter"].toType<quantity<Utility::UnitTraits<MegaElectronVolt>::InverseUnit> >(),
                       3.0/MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["restriction energy"].toType<quantity<MegaElectronVolt> >(),
                       2.0*MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 0.5, SHOW_LHS );

  oss.str( "" );
  oss.clear();

  std::shared_ptr<Utility::UnitAwareUnivariateDistribution<MegaElectronVolt,si::amount>> shared_dist( new Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV, 0.5 ) );
  
  oss << *shared_dist;

  dist_data = Utility::fromString<Utility::VariantMap>( oss.str() );

  FRENSIE_CHECK_EQUAL( dist_data["type"].toString(),
                       "Watt Distribution",
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["independent unit"].toString(),
                       Utility::UnitTraits<MegaElectronVolt>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["dependent unit"].toString(),
                       Utility::UnitTraits<si::amount>::name(),
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["incident energy"].toType<quantity<MegaElectronVolt> >(),
                       5.0*MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["a parameter"].toType<quantity<MegaElectronVolt> >(),
                       4.0*MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["b parameter"].toType<quantity<Utility::UnitTraits<MegaElectronVolt>::InverseUnit> >(),
                       3.0/MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["restriction energy"].toType<quantity<MegaElectronVolt> >(),
                       2.0*MeV,
                       SHOW_LHS );
  FRENSIE_CHECK_EQUAL( dist_data["multiplier"].toDouble(), 0.5, SHOW_LHS );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( WattDistribution, archive, TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_watt_dist" );
  std::ostringstream archive_ostream;

  // Create and archive some watt distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );
    
    Utility::WattDistribution dist_a;
    Utility::WattDistribution dist_b( 5.0 );
    Utility::WattDistribution dist_c( 5.0, 4.0 );
    Utility::WattDistribution dist_d( 5.0, 4.0, 3.0 );
    Utility::WattDistribution dist_e( 5.0, 4.0, 3.0, 2.0 );
    Utility::WattDistribution dist_f( 5.0, 4.0, 3.0, 2.0, 0.5 );

    FRENSIE_REQUIRE_NO_THROW(
                             (*oarchive) << BOOST_SERIALIZATION_NVP( dist_a )
                             );
    FRENSIE_REQUIRE_NO_THROW(
                             (*oarchive) << BOOST_SERIALIZATION_NVP( dist_b )
                             );
    FRENSIE_REQUIRE_NO_THROW(
                             (*oarchive) << BOOST_SERIALIZATION_NVP( dist_c )
                             );
    FRENSIE_REQUIRE_NO_THROW(
                             (*oarchive) << BOOST_SERIALIZATION_NVP( dist_d )
                             );
    FRENSIE_REQUIRE_NO_THROW(
                             (*oarchive) << BOOST_SERIALIZATION_NVP( dist_e )
                             );
    FRENSIE_REQUIRE_NO_THROW(
                             (*oarchive) << BOOST_SERIALIZATION_NVP( dist_f )
                             );
    FRENSIE_REQUIRE_NO_THROW(
                         (*oarchive) << BOOST_SERIALIZATION_NVP( distribution )
                             );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Utility::WattDistribution dist_a;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_a ) );
  FRENSIE_CHECK_EQUAL( dist_a, Utility::WattDistribution() );

  Utility::WattDistribution dist_b;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_b ) );
  FRENSIE_CHECK_EQUAL( dist_b, Utility::WattDistribution( 5.0 ) );

  Utility::WattDistribution dist_c;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_c ) );
  FRENSIE_CHECK_EQUAL( dist_c, Utility::WattDistribution( 5.0, 4.0 ) );

  Utility::WattDistribution dist_d;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_d ) );
  FRENSIE_CHECK_EQUAL( dist_d, Utility::WattDistribution( 5.0, 4.0, 3.0 ) );

  Utility::WattDistribution dist_e;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_e ) );
  FRENSIE_CHECK_EQUAL( dist_e, Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0 ) );

  Utility::WattDistribution dist_f;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_f ) );
  FRENSIE_CHECK_EQUAL( dist_f, Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0, 0.5 ) );

  std::shared_ptr<Utility::UnivariateDistribution> shared_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "distribution", shared_dist ) );
  FRENSIE_CHECK_EQUAL( *dynamic_cast<Utility::WattDistribution*>( shared_dist.get() ),
                       *dynamic_cast<Utility::WattDistribution*>( distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareWattDistribution,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;
  
  std::string archive_base_name( "test_watt_dist" );
  std::ostringstream archive_ostream;

  // Create and archive some watt distributions
  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );
    
    Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> dist_a;
    Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> dist_b( 5.0*MeV );
    Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> dist_c( 5.0*MeV, 4.0*MeV );
    Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> dist_d( 5.0*MeV, 4.0*MeV, 3.0/MeV );
    Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> dist_e( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV );
    Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> dist_f( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV, 0.5 );

    FRENSIE_REQUIRE_NO_THROW(
                             (*oarchive) << BOOST_SERIALIZATION_NVP( dist_a )
                             );
    FRENSIE_REQUIRE_NO_THROW(
                             (*oarchive) << BOOST_SERIALIZATION_NVP( dist_b )
                             );
    FRENSIE_REQUIRE_NO_THROW(
                             (*oarchive) << BOOST_SERIALIZATION_NVP( dist_c )
                             );
    FRENSIE_REQUIRE_NO_THROW(
                             (*oarchive) << BOOST_SERIALIZATION_NVP( dist_d )
                             );
    FRENSIE_REQUIRE_NO_THROW(
                             (*oarchive) << BOOST_SERIALIZATION_NVP( dist_e )
                             );
    FRENSIE_REQUIRE_NO_THROW(
                             (*oarchive) << BOOST_SERIALIZATION_NVP( dist_f )
                             );
    FRENSIE_REQUIRE_NO_THROW(
              (*oarchive) << BOOST_SERIALIZATION_NVP( unit_aware_distribution )
                             );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );
  
  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> dist_a;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_a ) );
  FRENSIE_CHECK_EQUAL( dist_a, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>()) );

  Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> dist_b;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_b ) );
  FRENSIE_CHECK_EQUAL( dist_b, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV )) );

  Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> dist_c;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_c ) );
  FRENSIE_CHECK_EQUAL( dist_c, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV )) );

  Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> dist_d;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_d ) );
  FRENSIE_CHECK_EQUAL( dist_d, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV )) );

  Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> dist_e;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_e ) );
  FRENSIE_CHECK_EQUAL( dist_e, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV )) );

  Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> dist_f;

  FRENSIE_REQUIRE_NO_THROW(
                           (*iarchive) >> BOOST_SERIALIZATION_NVP( dist_f ) );
  FRENSIE_CHECK_EQUAL( dist_f, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV, 0.5 )) );

  std::shared_ptr<Utility::UnitAwareUnivariateDistribution<MegaElectronVolt,si::amount> > shared_dist;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> boost::serialization::make_nvp( "unit_aware_distribution", shared_dist ) );
  FRENSIE_CHECK_EQUAL( (*dynamic_cast<Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>*>( shared_dist.get() )),
                       (*dynamic_cast<Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>*>( unit_aware_distribution.get() )) );
}

//---------------------------------------------------------------------------//
// Check that distributions can be scaled
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareWattDistribution,
				   explicit_conversion,
                                   TestUnitTypeQuads )
{
  FETCH_TEMPLATE_PARAM( 0, RawIndepUnitA );
  FETCH_TEMPLATE_PARAM( 1, RawDepUnitA );
  FETCH_TEMPLATE_PARAM( 2, RawIndepUnitB );
  FETCH_TEMPLATE_PARAM( 3, RawDepUnitB );

  typedef typename std::remove_pointer<RawIndepUnitA>::type IndepUnitA;
  typedef typename std::remove_pointer<RawDepUnitA>::type DepUnitA;
  typedef typename std::remove_pointer<RawIndepUnitB>::type IndepUnitB;
  typedef typename std::remove_pointer<RawDepUnitB>::type DepUnitB;
  
  typedef typename Utility::UnitTraits<IndepUnitA>::template GetQuantityType<double>::type IndepQuantityA;
  typedef typename Utility::UnitTraits<typename Utility::UnitTraits<IndepUnitA>::InverseUnit>::template GetQuantityType<double>::type InverseIndepQuantityA;

  typedef typename Utility::UnitTraits<IndepUnitB>::template GetQuantityType<double>::type IndepQuantityB;
  typedef typename Utility::UnitTraits<typename Utility::UnitTraits<IndepUnitB>::InverseUnit>::template GetQuantityType<double>::type InverseIndepQuantityB;

  typedef typename Utility::UnitTraits<DepUnitA>::template GetQuantityType<double>::type DepQuantityA;
  typedef typename Utility::UnitTraits<DepUnitB>::template GetQuantityType<double>::type DepQuantityB;

  // Copy from unitless distribution to distribution type A (static method)
  Utility::UnitAwareWattDistribution<IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwareWattDistribution<IndepUnitA,DepUnitA>::fromUnitlessDistribution( *dynamic_cast<Utility::WattDistribution*>( distribution.get() ) );

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

  FRENSIE_CHECK_FLOATING_EQUALITY(
			   unit_aware_dist_a_copy.evaluate( indep_quantity_a ),
			   dep_quantity_a,
			   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			unit_aware_dist_a_copy.evaluatePDF( indep_quantity_a ),
			inv_indep_quantity_a,
			1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			   unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
			   dep_quantity_b,
			   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
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

  FRENSIE_CHECK_FLOATING_EQUALITY(
			   unit_aware_dist_a_copy.evaluate( indep_quantity_a ),
			   dep_quantity_a,
			   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			unit_aware_dist_a_copy.evaluatePDF( indep_quantity_a ),
			inv_indep_quantity_a,
			1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			   unit_aware_dist_b_copy.evaluate( indep_quantity_b ),
			   dep_quantity_b,
			   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY(
			unit_aware_dist_b_copy.evaluatePDF( indep_quantity_b ),
			inv_indep_quantity_b,
			1e-14 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstWattDistribution.cpp
//---------------------------------------------------------------------------//
