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
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using boost::units::quantity;
using namespace Utility::Units;
namespace si = boost::units::si;
namespace cgs = boost::units::cgs;

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

std::unique_ptr<Utility::PropertyTree> test_dists_ptree;

std::shared_ptr<Utility::OneDDistribution> distribution(
			 new Utility::WattDistribution( 1.0, 1.0, 1.0, 0.1 ) );

std::shared_ptr<Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount> >
unit_aware_distribution( new Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 1e6*eV, 1e3*keV, 1e-6/eV, 0.1*MeV ) );

//---------------------------------------------------------------------------//
// Testing Tables
//---------------------------------------------------------------------------//
// This table describes the data in the property tree
FRENSIE_DATA_TABLE( TestPropertyTreeTable )
{
  std::vector<std::string> no_unused_children;

  // The data table will always use the basic distribution since they are
  // serialized the same in the table
  Utility::WattDistribution dummy_dist;

  COLUMNS() << "dist_name" << "valid_dist_rep" << "expected_unused_children" << "expected_dist";
  NEW_ROW( "inline_6_args_valid" ) << "Distribution A" << true << no_unused_children << Utility::WattDistribution( 3.0, 2.0, 1.0, 0.0, 0.5 );
  NEW_ROW( "inline_5_args_valid" ) << "Distribution B" << true << no_unused_children << Utility::WattDistribution( 3.0, 2.0, 1.0, 0.1 );
  NEW_ROW( "inline_4_args_valid" ) << "Distribution C" << true << no_unused_children << Utility::WattDistribution( 3.0, 2.0, 1.0 );
  NEW_ROW( "inline_3_args_valid" ) << "Distribution D" << true << no_unused_children << Utility::WattDistribution( 3.0, 2.0 );
  NEW_ROW( "inline_2_args_valid" ) << "Distribution E" << true << no_unused_children << Utility::WattDistribution( 3.0 );
  NEW_ROW( "inline_1_arg_valid" ) << "Distribution F" << true << no_unused_children << Utility::WattDistribution();
  NEW_ROW( "inline_bad_type" ) << "Distribution G" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_energy" ) << "Distribution H" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_zero_energy" ) << "Distribution I" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_neg_energy" ) << "Distribution J" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_a_param" ) << "Distribution K" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_zero_a_param" ) << "Distribution L" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_neg_a_param" ) << "Distribution M" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_b_param" ) << "Distribution N" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_zero_b_param" ) << "Distribution O" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_neg_b_param" ) << "Distribution P" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_restric_energy" ) << "Distribution Q" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_equal_restrict_energy" ) << "Distribution R" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_greater_restrict_energy" ) << "Distribution S" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_inf_mult" ) << "Distribution T" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inline_zero_mult" ) << "Distribution U" << false << no_unused_children << dummy_dist;

  NEW_ROW( "6_args_valid" ) << "Distribution V" << true << no_unused_children << Utility::WattDistribution( 3.0, 2.0, 1.0, 0.0, 0.5 );
  NEW_ROW( "5_args_valid" ) << "Distribution W" << true << no_unused_children << Utility::WattDistribution( 3.0, 2.0, 1.0, 0.1 );
  NEW_ROW( "4_args_valid" ) << "Distribution X" << true << no_unused_children << Utility::WattDistribution( 3.0, 2.0, 1.0 );
  NEW_ROW( "3_args_valid" ) << "Distribution Y" << true << no_unused_children << Utility::WattDistribution( 3.0, 2.0 );
  NEW_ROW( "2_args_valid" ) << "Distribution Z" << true << no_unused_children << Utility::WattDistribution( 3.0 );
  NEW_ROW( "1_arg_valid" ) << "Distribution AA" << true << std::vector<std::string>( {"dummy"} ) << Utility::WattDistribution();
  NEW_ROW( "repeated_keys" ) << "Distribution AB" << true << std::vector<std::string>( {"mult", "restrict", "b", "a", "energy"} ) << Utility::WattDistribution( 1.0, 1.0, 1.0, 0.1, 2.0 );
  NEW_ROW( "bad_type" ) << "Distribution AC" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_energy" ) << "Distribution AD" << false << no_unused_children << dummy_dist;
  NEW_ROW( "zero_energy" ) << "Distribution AE" << false << no_unused_children << dummy_dist;
  NEW_ROW( "neg_energy" ) << "Distribution AF" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_a_param" ) << "Distribution AG" << false << no_unused_children << dummy_dist;
  NEW_ROW( "zero_a_param" ) << "Distribution AH" << false << no_unused_children << dummy_dist;
  NEW_ROW( "neg_a_param" ) << "Distribution AI" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_b_param" ) << "Distribution AJ" << false << no_unused_children << dummy_dist;
  NEW_ROW( "zero_b_param" ) << "Distribution AK" << false << no_unused_children << dummy_dist;
  NEW_ROW( "neg_b_param" ) << "Distribution AL" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_restric_energy" ) << "Distribution AM" << false << no_unused_children << dummy_dist;
  NEW_ROW( "equal_restrict_energy" ) << "Distribution AN" << false << no_unused_children << dummy_dist;
  NEW_ROW( "greater_restrict_energy" ) << "Distribution AO" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_mult" ) << "Distribution AP" << false << no_unused_children << dummy_dist;
  NEW_ROW( "zero_mult" ) << "Distribution AQ" << false << no_unused_children << dummy_dist;
}

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

  Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount>::IndepQuantity incident_energy, a_parameter, restriction_energy, sample;

  Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount>::InverseIndepQuantity b_parameter;

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
// Check that the distribution type name can be returned
FRENSIE_UNIT_TEST( WattDistribution, getDistributionTypeName )
{
  FRENSIE_CHECK_EQUAL( Utility::WattDistribution::typeName( true, false, " " ),
                       "Watt Distribution" );
  FRENSIE_CHECK_EQUAL( Utility::WattDistribution::typeName( false ),
                       "Watt" );
  FRENSIE_CHECK_EQUAL( Utility::typeName<Utility::WattDistribution>(),
                       "WattDistribution" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type name can be returned
FRENSIE_UNIT_TEST( UnitAwareWattDistribution,
                   getDistributionTypeName )
{
  FRENSIE_CHECK_EQUAL( (Utility::UnitAwareWattDistribution<ElectronVolt,si::amount>::typeName( true, false, " " )),
                       "Watt Distribution" );
  FRENSIE_CHECK_EQUAL( (Utility::UnitAwareWattDistribution<ElectronVolt,si::amount>::typeName( false )),
                       "Watt" );
  FRENSIE_CHECK_EQUAL( (Utility::typeName<Utility::UnitAwareWattDistribution<ElectronVolt,si::amount> >()),
                       (std::string("UnitAwareWattDistribution<")+Utility::typeName<ElectronVolt,si::amount>()+">" ));
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
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is compatible with the interp type
FRENSIE_UNIT_TEST( UnitAwareWattDistribution, isCompatibleWithInterpType )
{
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be converted to a string
FRENSIE_UNIT_TEST( WattDistribution, toString )
{
  std::string dist_string =
    Utility::toString( Utility::WattDistribution() );

  FRENSIE_CHECK_EQUAL( dist_string, "{Watt Distribution, 1.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::WattDistribution( 3.0 ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Watt Distribution, 3.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::WattDistribution( 5.0, 4.0 ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::WattDistribution( 5.0, 4.0, 3.0 ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 3.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0 ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0, 0.5 ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 3.000000000000000000e+00, 2.000000000000000000e+00, 5.000000000000000000e-01}" );

  std::shared_ptr<Utility::OneDDistribution> shared_dist( new Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0, 0.5 ) );
  dist_string = Utility::toString( *shared_dist );

  FRENSIE_CHECK_EQUAL( dist_string, "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 3.000000000000000000e+00, 2.000000000000000000e+00, 5.000000000000000000e-01}" );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be converted to a string
FRENSIE_UNIT_TEST( UnitAwareWattDistribution, toString )
{
  std::string dist_string =
    Utility::toString( Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>() );

  FRENSIE_CHECK_EQUAL( dist_string, "{Watt Distribution, 1.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 3.0*MeV ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Watt Distribution, 3.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 3.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV, 0.5 ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 3.000000000000000000e+00, 2.000000000000000000e+00, 5.000000000000000000e-01}" );

  std::shared_ptr<Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount>> shared_dist( new Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV, 0.5 ) );
  dist_string = Utility::toString( *shared_dist );

  FRENSIE_CHECK_EQUAL( dist_string, "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 3.000000000000000000e+00, 2.000000000000000000e+00, 5.000000000000000000e-01}" );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be placed in a stream
FRENSIE_UNIT_TEST( WattDistribution, toStream )
{
  std::ostringstream oss;
  
  Utility::toStream( oss, Utility::WattDistribution() );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Watt Distribution, 1.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::WattDistribution( 3.0 ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Watt Distribution, 3.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::WattDistribution( 5.0, 4.0 ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::WattDistribution( 5.0, 4.0, 3.0 ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 3.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0 ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0, 0.5 ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 3.000000000000000000e+00, 2.000000000000000000e+00, 5.000000000000000000e-01}" );

  oss.str( "" );
  oss.clear();

  std::shared_ptr<Utility::WattDistribution> shared_dist( new Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0, 0.5 ) );
  Utility::toStream( oss, *shared_dist );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 3.000000000000000000e+00, 2.000000000000000000e+00, 5.000000000000000000e-01}" );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST( UnitAwareWattDistribution, toStream )
{
  std::ostringstream oss;
  Utility::toStream( oss, Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>() );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Watt Distribution, 1.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 3.0*MeV ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Watt Distribution, 3.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );
  
  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 3.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV, 0.5 ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 3.000000000000000000e+00, 2.000000000000000000e+00, 5.000000000000000000e-01}" );

  oss.str( "" );
  oss.clear();

  std::shared_ptr<Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount>> shared_dist( new Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV, 0.5 ) );
  Utility::toStream( oss, *shared_dist );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 3.000000000000000000e+00, 2.000000000000000000e+00, 5.000000000000000000e-01}" );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be placed in a stream
FRENSIE_UNIT_TEST( WattDistribution, ostream_operator )
{
  std::ostringstream oss;
  
  oss << Utility::WattDistribution();

  FRENSIE_CHECK_EQUAL( oss.str(), "{Watt Distribution, 1.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::WattDistribution( 3.0 );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Watt Distribution, 3.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::WattDistribution( 5.0, 4.0 );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::WattDistribution( 5.0, 4.0, 3.0 );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 3.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0 );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0, 0.5 );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 3.000000000000000000e+00, 2.000000000000000000e+00, 5.000000000000000000e-01}" );

  oss.str( "" );
  oss.clear();

  std::shared_ptr<Utility::WattDistribution> shared_dist( new Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0, 0.5 ) );
  oss << *shared_dist;

  FRENSIE_CHECK_EQUAL( oss.str(), "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 3.000000000000000000e+00, 2.000000000000000000e+00, 5.000000000000000000e-01}" );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST( UnitAwareWattDistribution, ostream_operator )
{
  std::ostringstream oss;
  oss << Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>();

  FRENSIE_CHECK_EQUAL( oss.str(), "{Watt Distribution, 1.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 3.0*MeV );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Watt Distribution, 3.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );
  
  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 3.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV, 0.5 );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 3.000000000000000000e+00, 2.000000000000000000e+00, 5.000000000000000000e-01}" );

  oss.str( "" );
  oss.clear();

  std::shared_ptr<Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount>> shared_dist( new Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV, 0.5 ) );
  oss << *shared_dist;

  FRENSIE_CHECK_EQUAL( oss.str(), "{Watt Distribution, 5.000000000000000000e+00, 4.000000000000000000e+00, 3.000000000000000000e+00, 2.000000000000000000e+00, 5.000000000000000000e-01}" );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a string
FRENSIE_UNIT_TEST( WattDistribution, fromString )
{
  Utility::WattDistribution test_dist =
    Utility::fromString<Utility::WattDistribution>( "{Watt Distribution}" );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::WattDistribution() );

  test_dist = Utility::fromString<Utility::WattDistribution>( "{Watt Distribution, 5.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::WattDistribution( 5.0 ) );

  test_dist = Utility::fromString<Utility::WattDistribution>( "{Watt Distribution, 5.0, 4.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::WattDistribution( 5.0, 4.0 ) );

  test_dist = Utility::fromString<Utility::WattDistribution>( "{Watt Distribution, 5.0, 4.0, 3.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::WattDistribution( 5.0, 4.0, 3.0 ) );

  test_dist = Utility::fromString<Utility::WattDistribution>( "{Watt Distribution, 5.0, 4.0, 3.0, 2.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0 ) );

  test_dist = Utility::fromString<Utility::WattDistribution>( "{Watt Distribution, 5.0, 4.0, 3.0, 2.0, 0.5}" );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0, 0.5 ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialized from a string
FRENSIE_UNIT_TEST( UnitAwareWattDistribution, fromString )
{
  Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> test_dist =
    Utility::fromString<Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>>( "{Watt Distribution}" );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>()) );

  test_dist = Utility::fromString<Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>>( "{Watt Distribution, 5.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV )) );

  test_dist = Utility::fromString<Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>>( "{Watt Distribution, 5.0, 4.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV )) );

  test_dist = Utility::fromString<Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>>( "{Watt Distribution, 5.0, 4.0, 3.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV )) );

  test_dist = Utility::fromString<Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>>( "{Watt Distribution, 5.0, 4.0, 3.0, 2.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV )) );

  test_dist = Utility::fromString<Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>>( "{Watt Distribution, 5.0, 4.0, 3.0, 2.0, 0.5}" );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV, 0.5 )) );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a stream
FRENSIE_UNIT_TEST( WattDistribution, fromStream )
{
  std::istringstream iss( "{Watt Distribution}" );
  
  Utility::WattDistribution test_dist;

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::WattDistribution() );

  iss.str( "{Watt Distribution, 5.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::WattDistribution( 5.0 ) );

  iss.str( "{Watt Distribution, 5.0, 4.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::WattDistribution( 5.0, 4.0 ) );

  iss.str( "{Watt Distribution, 5.0, 4.0, 3.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::WattDistribution( 5.0, 4.0, 3.0 ) );

  iss.str( "{Watt Distribution, 5.0, 4.0, 3.0, 2.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0 ) );

  iss.str( "{Watt Distribution, 5.0, 4.0, 3.0, 2.0, 0.5}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0, 0.5 ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialized from a stream
FRENSIE_UNIT_TEST( UnitAwareWattDistribution, fromStream )
{
  std::istringstream iss( "{Watt Distribution}" );
  Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> test_dist;

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>()) );

  iss.str( "{Watt Distribution, 5.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV )) );

  iss.str( "{Watt Distribution, 5.0, 4.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV )) );

  iss.str( "{Watt Distribution, 5.0, 4.0, 3.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV )) );

  iss.str( "{Watt Distribution, 5.0, 4.0, 3.0, 2.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV )) );

  iss.str( "{Watt Distribution, 5.0, 4.0, 3.0, 2.0, 0.5}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV, 0.5 )) );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a stream
FRENSIE_UNIT_TEST( WattDistribution, istream_operator )
{
  std::istringstream iss( "{Watt Distribution}" );
  
  Utility::WattDistribution test_dist;

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, Utility::WattDistribution() );

  iss.str( "{Watt Distribution, 5.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, Utility::WattDistribution( 5.0 ) );

  iss.str( "{Watt Distribution, 5.0, 4.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, Utility::WattDistribution( 5.0, 4.0 ) );

  iss.str( "{Watt Distribution, 5.0, 4.0, 3.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, Utility::WattDistribution( 5.0, 4.0, 3.0 ) );

  iss.str( "{Watt Distribution, 5.0, 4.0, 3.0, 2.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0 ) );

  iss.str( "{Watt Distribution, 5.0, 4.0, 3.0, 2.0, 0.5}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0, 0.5 ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialized from a stream
FRENSIE_UNIT_TEST( UnitAwareWattDistribution, istream_operator )
{
  std::istringstream iss( "{Watt Distribution}" );
  Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> test_dist;

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>()) );

  iss.str( "{Watt Distribution, 5.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV )) );

  iss.str( "{Watt Distribution, 5.0, 4.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV )) );

  iss.str( "{Watt Distribution, 5.0, 4.0, 3.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV )) );

  iss.str( "{Watt Distribution, 5.0, 4.0, 3.0, 2.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV )) );

  iss.str( "{Watt Distribution, 5.0, 4.0, 3.0, 2.0, 0.5}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV, 0.5 )) );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be written to a property tree
FRENSIE_UNIT_TEST( WattDistribution, toPropertyTree )
{
  // Use the property tree interface directly
  Utility::PropertyTree ptree;

  ptree.put( "test distribution", Utility::WattDistribution() );

  Utility::WattDistribution copy_dist =
    ptree.get<Utility::WattDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, Utility::WattDistribution() );

  ptree.put( "test distribution", Utility::WattDistribution( 5.0 ) );

  copy_dist = ptree.get<Utility::WattDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, Utility::WattDistribution( 5.0 ) );

  ptree.put( "test distribution", Utility::WattDistribution( 5.0, 4.0 ) );

  copy_dist = ptree.get<Utility::WattDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, Utility::WattDistribution( 5.0, 4.0 ) );

  ptree.put( "test distribution", Utility::WattDistribution( 5.0, 4.0, 3.0 ) );

  copy_dist = ptree.get<Utility::WattDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, Utility::WattDistribution( 5.0, 4.0, 3.0 ) );

  ptree.put( "test distribution", Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0 ) );

  copy_dist = ptree.get<Utility::WattDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0 ) );

  ptree.put( "test distribution", Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0, 0.5 ) );

  copy_dist = ptree.get<Utility::WattDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0, 0.5 ) );

  // Use the PropertyTreeCompatibleObject interface
  ptree = Utility::WattDistribution().toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::WattDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::WattDistribution() );

  ptree = Utility::WattDistribution().toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Watt Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "a parameter" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "b parameter" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::WattDistribution( 5.0 ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::WattDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::WattDistribution( 5.0 ) );

  ptree = Utility::WattDistribution( 5.0 ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Watt Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 5.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "a parameter" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "b parameter" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::WattDistribution( 5.0, 4.0 ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::WattDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::WattDistribution( 5.0, 4.0 ) );

  ptree = Utility::WattDistribution( 5.0, 4.0 ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Watt Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 5.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "a parameter" ), 4.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "b parameter" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::WattDistribution( 5.0, 4.0, 3.0 ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::WattDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::WattDistribution( 5.0, 4.0, 3.0 ) );

  ptree = Utility::WattDistribution( 5.0, 4.0, 3.0 ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Watt Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 5.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "a parameter" ), 4.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "b parameter" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0 ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::WattDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0 ) );

  ptree = Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0 ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Watt Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 5.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "a parameter" ), 4.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "b parameter" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0, 0.5 ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::WattDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0, 0.5 ) );

  ptree = Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0, 0.5 ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Watt Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 5.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "a parameter" ), 4.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "b parameter" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 0.5 );

  // Use the property tree helper methods
  ptree = Utility::toPropertyTree( Utility::WattDistribution(), true );

  copy_dist = ptree.get_value<Utility::WattDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::WattDistribution() );

  ptree = Utility::toPropertyTree( Utility::WattDistribution(), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Watt Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "a parameter" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "b parameter" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::toPropertyTree( Utility::WattDistribution( 5.0 ), true );

  copy_dist = ptree.get_value<Utility::WattDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::WattDistribution( 5.0 ) );

  ptree = Utility::toPropertyTree( Utility::WattDistribution( 5.0 ), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Watt Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 5.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "a parameter" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "b parameter" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::toPropertyTree( Utility::WattDistribution( 5.0, 4.0 ), true );

  copy_dist = ptree.get_value<Utility::WattDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::WattDistribution( 5.0, 4.0 ) );

  ptree = Utility::toPropertyTree( Utility::WattDistribution( 5.0, 4.0 ), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Watt Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 5.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "a parameter" ), 4.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "b parameter" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::toPropertyTree( Utility::WattDistribution( 5.0, 4.0, 3.0 ), true );

  copy_dist = ptree.get_value<Utility::WattDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::WattDistribution( 5.0, 4.0, 3.0 ) );

  ptree = Utility::toPropertyTree( Utility::WattDistribution( 5.0, 4.0, 3.0 ), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Watt Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 5.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "a parameter" ), 4.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "b parameter" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::toPropertyTree( Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0 ), true );

  copy_dist = ptree.get_value<Utility::WattDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0 ) );

  ptree = Utility::toPropertyTree( Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0 ), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Watt Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 5.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "a parameter" ), 4.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "b parameter" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::toPropertyTree( Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0, 0.5 ), true );

  copy_dist = ptree.get_value<Utility::WattDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0, 0.5 ) );

  ptree = Utility::toPropertyTree( Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0, 0.5 ), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Watt Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 5.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "a parameter" ), 4.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "b parameter" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 0.5 );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be written to a property tree
FRENSIE_UNIT_TEST( UnitAwareWattDistribution, toPropertyTree )
{
  // Use the property tree interface directly
  Utility::PropertyTree ptree;

  ptree.put( "test distribution", Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>() );

  Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> copy_dist =
    ptree.get<Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>()) );

  ptree.put( "test distribution", Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV ) );

  copy_dist = ptree.get<Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV )) );

  ptree.put( "test distribution", Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV ) );

  copy_dist = ptree.get<Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV )) );

  ptree.put( "test distribution", Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV ) );

  copy_dist = ptree.get<Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV )) );

  ptree.put( "test distribution", Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV ) );

  copy_dist = ptree.get<Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV )) );

  ptree.put( "test distribution", Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV, 0.5 ) );

  copy_dist = ptree.get<Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV, 0.5 )) );

  // Use the PropertyTreeCompatibleObject interface
  ptree = Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>().toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>()) );

  ptree = Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>().toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Watt Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "a parameter" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "b parameter" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV )) );

  ptree = Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Watt Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 5.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "a parameter" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "b parameter" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV )) );

  ptree = Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Watt Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 5.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "a parameter" ), 4.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "b parameter" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV )) );

  ptree = Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Watt Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 5.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "a parameter" ), 4.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "b parameter" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV )) );

  ptree = Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Watt Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 5.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "a parameter" ), 4.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "b parameter" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV, 0.5 ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV, 0.5 )) );

  ptree = Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV, 0.5 ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Watt Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 5.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "a parameter" ), 4.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "b parameter" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 0.5 );

  // Use the property tree helper methods
  ptree = Utility::toPropertyTree( Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>(), true );

  copy_dist = ptree.get_value<Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>()) );

  ptree = Utility::toPropertyTree( Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>(), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Watt Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "a parameter" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "b parameter" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::toPropertyTree( Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV ), true );

  copy_dist = ptree.get_value<Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV )) );

  ptree = Utility::toPropertyTree( Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV ), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Watt Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 5.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "a parameter" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "b parameter" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::toPropertyTree( Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV ), true );

  copy_dist = ptree.get_value<Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV )) );

  ptree = Utility::toPropertyTree( Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV ), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Watt Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 5.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "a parameter" ), 4.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "b parameter" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::toPropertyTree( Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV ), true );

  copy_dist = ptree.get_value<Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV )) );

  ptree = Utility::toPropertyTree( Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV ), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Watt Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 5.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "a parameter" ), 4.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "b parameter" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::toPropertyTree( Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV ), true );

  copy_dist = ptree.get_value<Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV )) );

  ptree = Utility::toPropertyTree( Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV ), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Watt Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 5.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "a parameter" ), 4.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "b parameter" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::toPropertyTree( Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV, 0.5 ), true );

  copy_dist = ptree.get_value<Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV, 0.5 )) );

  ptree = Utility::toPropertyTree( Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV, 0.5 ), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 6 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Watt Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 5.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "a parameter" ), 4.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "b parameter" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 0.5 );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be read from a property tree
FRENSIE_DATA_UNIT_TEST( WattDistribution,
                        fromPropertyTree,
                        TestPropertyTreeTable )
{                                                                     
  FETCH_FROM_TABLE( std::string, dist_name );                           
  FETCH_FROM_TABLE( bool, valid_dist_rep );                             
  FETCH_FROM_TABLE( std::vector<std::string>, expected_unused_children ); 
  FETCH_FROM_TABLE( Utility::WattDistribution, expected_dist );     
                                                   
  Utility::WattDistribution dist;                         
  std::vector<std::string> unused_children;        
                                                        
  /* Use the PropertyTreeCompatibleObject interface */  
  if( valid_dist_rep )                                  
  {                                                                   
    FRENSIE_CHECK_NO_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( dist_name ), unused_children ) ); 
    FRENSIE_CHECK_EQUAL( dist, expected_dist );                         
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );   
                                                                        
    unused_children.clear();                                            
  }                                                                     
  else                                                                  
  {                                                                   
    FRENSIE_CHECK_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( dist_name ) ), 
                         Utility::PropertyTreeConversionException );    
  }                                                                     
                                                                        
  /* Use the property tree helper methods */                            
  if( valid_dist_rep )                                                  
  {                                                                   
    FRENSIE_CHECK_NO_THROW(                                             
            dist = Utility::fromPropertyTree<Utility::WattDistribution>(
                                    test_dists_ptree->get_child( dist_name ), 
                                    unused_children ) );                
    FRENSIE_CHECK_EQUAL( dist, expected_dist );                         
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );   
  }                                                                     
  else                                                                  
  {                                                                   
    FRENSIE_CHECK_THROW(
                 Utility::fromPropertyTree<Utility::WattDistribution>(
                                  test_dists_ptree->get_child( dist_name ) ), 
                 Utility::PropertyTreeConversionException );    
  }                                                                     
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be read from a property tree
FRENSIE_DATA_UNIT_TEST( UnitAwareWattDistribution,
                        fromPropertyTree,
                        TestPropertyTreeTable )  
{
  typedef Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> DistributionType;
  
  FETCH_FROM_TABLE( std::string, dist_name );                           
  FETCH_FROM_TABLE( bool, valid_dist_rep );                             
  FETCH_FROM_TABLE( std::vector<std::string>, expected_unused_children ); 
  FETCH_FROM_TABLE( DistributionType, expected_dist );     
                                                   
  DistributionType dist;                         
  std::vector<std::string> unused_children;        
                                                        
  /* Use the PropertyTreeCompatibleObject interface */  
  if( valid_dist_rep )                                  
  {                                                                   
    FRENSIE_CHECK_NO_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( dist_name ), unused_children ) ); 
    FRENSIE_CHECK_EQUAL( dist, expected_dist );                         
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );   
                                                                        
    unused_children.clear();                                            
  }                                                                     
  else                                                                  
  {                                                                   
    FRENSIE_CHECK_THROW( dist.fromPropertyTree( test_dists_ptree->get_child( dist_name ) ), 
                         Utility::PropertyTreeConversionException );    
  }                                                                     
                                                                        
  /* Use the property tree helper methods */                            
  if( valid_dist_rep )                                                  
  {                                                                   
    FRENSIE_CHECK_NO_THROW( dist = Utility::fromPropertyTree<DistributionType>(
                                    test_dists_ptree->get_child( dist_name ), 
                                    unused_children ) );                
    FRENSIE_CHECK_EQUAL( dist, expected_dist );                         
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );   
  }                                                                     
  else                                                                  
  {                                                                   
    FRENSIE_CHECK_THROW( Utility::fromPropertyTree<DistributionType>(
                                  test_dists_ptree->get_child( dist_name ) ), 
                         Utility::PropertyTreeConversionException );    
  }                                                                     
}

//---------------------------------------------------------------------------//
// Check that a distribution can be archived
FRENSIE_UNIT_TEST( WattDistribution, archive )
{
  std::string archive_name( "test_watt_dist.h5a" );

  // Create and archive some watt distributions
  {
    Utility::WattDistribution dist_a;
    Utility::WattDistribution dist_b( 5.0 );
    Utility::WattDistribution dist_c( 5.0, 4.0 );
    Utility::WattDistribution dist_d( 5.0, 4.0, 3.0 );
    Utility::WattDistribution dist_e( 5.0, 4.0, 3.0, 2.0 );
    Utility::WattDistribution dist_f( 5.0, 4.0, 3.0, 2.0, 0.5 );

    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_a )
                             );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_b )
                             );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_c )
                             );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_d )
                             );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_e )
                             );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_f )
                             );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( distribution )
                             );
  }

  // Load the archived distributions
  Utility::HDF5IArchive archive( archive_name );

  Utility::WattDistribution dist_a;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_a ) );
  FRENSIE_CHECK_EQUAL( dist_a, Utility::WattDistribution() );

  Utility::WattDistribution dist_b;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_b ) );
  FRENSIE_CHECK_EQUAL( dist_b, Utility::WattDistribution( 5.0 ) );

  Utility::WattDistribution dist_c;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_c ) );
  FRENSIE_CHECK_EQUAL( dist_c, Utility::WattDistribution( 5.0, 4.0 ) );

  Utility::WattDistribution dist_d;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_d ) );
  FRENSIE_CHECK_EQUAL( dist_d, Utility::WattDistribution( 5.0, 4.0, 3.0 ) );

  Utility::WattDistribution dist_e;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_e ) );
  FRENSIE_CHECK_EQUAL( dist_e, Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0 ) );

  Utility::WattDistribution dist_f;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_f ) );
  FRENSIE_CHECK_EQUAL( dist_f, Utility::WattDistribution( 5.0, 4.0, 3.0, 2.0, 0.5 ) );

  std::shared_ptr<Utility::OneDDistribution> shared_dist;

  FRENSIE_REQUIRE_NO_THROW(
    archive >> boost::serialization::make_nvp( "distribution", shared_dist ) );
  FRENSIE_CHECK_EQUAL( *dynamic_cast<Utility::WattDistribution*>( shared_dist.get() ),
                       *dynamic_cast<Utility::WattDistribution*>( distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be archived
FRENSIE_UNIT_TEST( UnitAwareWattDistribution, archive )
{
  std::string archive_name( "test_watt_dist.h5a" );

  // Create and archive some watt distributions
  {
    Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> dist_a;
    Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> dist_b( 5.0*MeV );
    Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> dist_c( 5.0*MeV, 4.0*MeV );
    Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> dist_d( 5.0*MeV, 4.0*MeV, 3.0/MeV );
    Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> dist_e( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV );
    Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> dist_f( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV, 0.5 );

    Utility::HDF5OArchive archive( archive_name, Utility::HDF5OArchiveFlags::OVERWRITE_EXISTING_ARCHIVE );

    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_a )
                             );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_b )
                             );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_c )
                             );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_d )
                             );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_e )
                             );
    FRENSIE_REQUIRE_NO_THROW(
                             archive << BOOST_SERIALIZATION_NVP( dist_f )
                             );
    FRENSIE_REQUIRE_NO_THROW(
                  archive << BOOST_SERIALIZATION_NVP( unit_aware_distribution )
                             );
  }

  // Load the archived distributions
  Utility::HDF5IArchive archive( archive_name );

  Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> dist_a;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_a ) );
  FRENSIE_CHECK_EQUAL( dist_a, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>()) );

  Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> dist_b;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_b ) );
  FRENSIE_CHECK_EQUAL( dist_b, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV )) );

  Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> dist_c;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_c ) );
  FRENSIE_CHECK_EQUAL( dist_c, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV )) );

  Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> dist_d;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_d ) );
  FRENSIE_CHECK_EQUAL( dist_d, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV )) );

  Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> dist_e;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_e ) );
  FRENSIE_CHECK_EQUAL( dist_e, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV )) );

  Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount> dist_f;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_f ) );
  FRENSIE_CHECK_EQUAL( dist_f, (Utility::UnitAwareWattDistribution<MegaElectronVolt,si::amount>( 5.0*MeV, 4.0*MeV, 3.0/MeV, 2.0*MeV, 0.5 )) );

  std::shared_ptr<Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount> > shared_dist;

  FRENSIE_REQUIRE_NO_THROW(
    archive >> boost::serialization::make_nvp( "unit_aware_distribution", shared_dist ) );
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

std::string test_dists_json_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS() 
{
  ADD_OPTION( "test_dists_json_file",
              boost::program_options::value<std::string>(&test_dists_json_file_name)->default_value(""),
              "Test distributions xml file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Load the property tree from the json file
  test_dists_ptree.reset( new Utility::PropertyTree );

  std::ifstream test_dists_json_file( test_dists_json_file_name );

  test_dists_json_file >> *test_dists_ptree;

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstWattDistribution.cpp
//---------------------------------------------------------------------------//
