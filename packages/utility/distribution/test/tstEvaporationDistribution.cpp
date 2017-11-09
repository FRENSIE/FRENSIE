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
#include "Utility_EvaporationDistribution.hpp"
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
                       new Utility::EvaporationDistribution( 1.0, 1.0, 0.1 ) );

std::shared_ptr<Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount> >
  unit_aware_distribution( new Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 1e3*keV, 1e3*keV, 100.0*keV ) );

//---------------------------------------------------------------------------//
// Testing Tables
//---------------------------------------------------------------------------//
// This table describes the data in the property tree
FRENSIE_DATA_TABLE( TestPropertyTreeTable )
{
  std::vector<std::string> no_unused_children;

  // The data table will always use the basic distribution since they are
  // serialized the same in the table
  Utility::EvaporationDistribution dummy_dist;

  COLUMNS() << "dist_name" << "valid_dist_rep" << "expected_unused_children" << "expected_dist";
  NEW_ROW( "inline_5_args_valid" ) << "Distribution A" << true  << no_unused_children << Utility::EvaporationDistribution( 3.0, 2.0, 1.0, 0.1 );
  NEW_ROW( "inline_4_args_valid" ) << "Distribution B" << true  << no_unused_children << Utility::EvaporationDistribution( 3.0, 2.0, 1.0 );
  NEW_ROW( "inline_3_args_valid" ) << "Distribution C" << true  << no_unused_children << Utility::EvaporationDistribution( 3.0, 2.0 );
  NEW_ROW( "inline_2_args_valid" ) << "Distribution D" << true  << no_unused_children << Utility::EvaporationDistribution( 3.0 );
  NEW_ROW( "inline_1_arg_valid" )  << "Distribution E" << true  << no_unused_children << Utility::EvaporationDistribution();
  NEW_ROW( "inline_bad_type" )     << "Distribution M" << false << no_unused_children << dummy_dist;

  NEW_ROW( "1_arg_valid" )         << "Distribution F" << true  << no_unused_children << Utility::EvaporationDistribution();
  NEW_ROW( "2_args_valid" )        << "Distribution G" << true  << no_unused_children << Utility::EvaporationDistribution( 3.0 );
  NEW_ROW( "3_args_valid" )        << "Distribution H" << true  << no_unused_children << Utility::EvaporationDistribution( 3.0, 2.0 );
  NEW_ROW( "4_args_valid" )        << "Distribution I" << true  << no_unused_children << Utility::EvaporationDistribution( 3.0, 2.0, 1.0 );
  NEW_ROW( "5_args_valid" )        << "Distribution J" << true  << no_unused_children << Utility::EvaporationDistribution( 3.0, 2.0, 1.0, 0.1 );
  NEW_ROW( "5_abrv_args_valid" )   << "Distribution K" << true  << no_unused_children << Utility::EvaporationDistribution( 3.0, 2.0, 1.0, 0.1 );
  NEW_ROW( "6_args_valid" )        << "Distribution L" << true  << std::vector<std::string>({"dummy"}) << Utility::EvaporationDistribution( 1.0, 1.0, 0.1, 10.0 );
  NEW_ROW( "bad_type" )            << "Distribution N" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_energy" )          << "Distribution O" << false << no_unused_children << dummy_dist;
  NEW_ROW( "zero_energy" )         << "Distribution P" << false << no_unused_children << dummy_dist;
  NEW_ROW( "neg_energy" )          << "Distribution Q" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_restrict" )        << "Distribution R" << false << no_unused_children << dummy_dist;
  NEW_ROW( "high_restrict" )       << "Distribution S" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_temp" )            << "Distribution T" << false << no_unused_children << dummy_dist;
  NEW_ROW( "zero_temp" )           << "Distribution U" << false << no_unused_children << dummy_dist;
  NEW_ROW( "neg_temp" )            << "Distribution V" << false << no_unused_children << dummy_dist;
  NEW_ROW( "inf_mult" )            << "Distribution W" << false << no_unused_children << dummy_dist;
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( EvaporationDistribution, evaluate )
{
  double test_value_1 = 0.0 ;
  double test_value_2 = 0.9*exp( -0.9 );

  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0 ), test_value_1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.9 ), test_value_2 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.0 ), test_value_1 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
FRENSIE_UNIT_TEST( UnitAwareEvaporationDistribution, evaluate )
{
  double scale_factor = 0.9*exp(-0.9);

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV ),
		       0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.9*MeV ),
                       scale_factor*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.0*MeV ),
		       0.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
FRENSIE_UNIT_TEST( EvaporationDistribution, evaluatePDF )
{
  double test_value_1 = 0.0 ;
  double test_value_2 = 0.9*exp(-0.9)/(1.0 - exp(-0.9)*(1.0+0.9));

  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.0 ), test_value_1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( distribution->evaluatePDF( 0.9 ),
                          test_value_2,
                          1e-15 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 1.0 ), test_value_1 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwareEvaporationDistribution, evaluatePDF )
{
  double scale_factor = 0.9*exp(-0.9)/(1.0 - exp(-0.9)*(1.0+0.9));

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 0.0*MeV ),
		       0.0/MeV );
  FRENSIE_CHECK_FLOATING_EQUALITY( unit_aware_distribution->evaluatePDF( 0.9*MeV ),
                                  scale_factor/MeV,
                                  1e-15 );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 1.0*MeV ),
                       0.0/MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled using OpenMC method
FRENSIE_UNIT_TEST( EvaporationDistribution, sample )
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
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.70470821836401, 1e-14 );

  sample = distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.83920374256297, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that unit-aware distribution can be sampled using the OpenMC method
FRENSIE_UNIT_TEST( UnitAwareEvaporationDistribution, sample )
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
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.70470821836401*MeV, 1e-14 );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.83920374256297*MeV, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled using OpenMC method, and the
// trials can be recorded
FRENSIE_UNIT_TEST( EvaporationDistribution, sample_pass_parameters )
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
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.13885427138954, 1e-13 );

  incident_energy = 0.75;
  nuclear_temperature = 0.5;
  restriction_energy = 0.25;

  sample = Utility::EvaporationDistribution::sample( incident_energy, nuclear_temperature, restriction_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.43320278283758, 1e-13 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled using OpenMC method,
// and the trials can be recorded
FRENSIE_UNIT_TEST( UnitAwareEvaporationDistribution, sample_pass_parameters )
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
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.13885427138954*MeV, 1e-13 );

  incident_energy = 0.75*MeV;
  nuclear_temperature = 0.5*MeV;
  restriction_energy = 0.25*MeV;

  sample = Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>::sample( incident_energy, nuclear_temperature, restriction_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.43320278283758*MeV, 1e-13 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled using OpenMC method, and the
// trials can be recorded
FRENSIE_UNIT_TEST( EvaporationDistribution, sampleAndRecordTrials_pass_parameters )
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
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.13885427138954, 1e-13 );
  FRENSIE_CHECK_EQUAL( trials, 1.0 );

  incident_energy = 0.75;
  nuclear_temperature = 0.5;
  restriction_energy = 0.25;

  sample = Utility::EvaporationDistribution::sampleAndRecordTrials(incident_energy, nuclear_temperature, restriction_energy, trials);
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.43320278283758, 1e-13 );
  FRENSIE_CHECK_EQUAL( trials, 3.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled using OpenMC method,
// and the trials can be recorded
FRENSIE_UNIT_TEST( UnitAwareEvaporationDistribution,
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
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.13885427138954*MeV, 1e-13 );
  FRENSIE_CHECK_EQUAL( trials, 1.0 );

  incident_energy = 0.75*MeV;
  nuclear_temperature = 0.5*MeV;
  restriction_energy = 0.25*MeV;

  sample = Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>::sampleAndRecordTrials(incident_energy, nuclear_temperature, restriction_energy, trials);
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.43320278283758*MeV, 1e-13 );
  FRENSIE_CHECK_EQUAL( trials, 3.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST( EvaporationDistribution, getUpperBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfIndepVar(), 0.9 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST( UnitAwareEvaporationDistribution, getUpperBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfIndepVar(),
		       0.9*MeV );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST( EvaporationDistribution, getLowerBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST( UnitAwareEvaporationDistribution, getLowerBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfIndepVar(),
		       0.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
FRENSIE_UNIT_TEST( EvaporationDistribution, getDistributionType )
{
  FRENSIE_CHECK_EQUAL( distribution->getDistributionType(),
		       Utility::EVAPORATION_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
FRENSIE_UNIT_TEST( UnitAwareEvaporationDistribution, getDistributionType )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getDistributionType(),
		       Utility::EVAPORATION_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the distribution type name can be returned
FRENSIE_UNIT_TEST( EvaporationDistribution, getDistributionTypeName )
{
  FRENSIE_CHECK_EQUAL( Utility::EvaporationDistribution::typeName( true, false, " " ),
                       "Evaporation Distribution" );
  FRENSIE_CHECK_EQUAL( Utility::EvaporationDistribution::typeName( false ),
                       "Evaporation" );
  FRENSIE_CHECK_EQUAL( Utility::typeName<Utility::EvaporationDistribution>(),
                       "EvaporationDistribution" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type name can be returned
FRENSIE_UNIT_TEST( UnitAwareEvaporationDistribution,
                   getDistributionTypeName )
{
  FRENSIE_CHECK_EQUAL( (Utility::UnitAwareEvaporationDistribution<ElectronVolt,si::amount>::typeName( true, false, " " )),
                       "Evaporation Distribution" );
  FRENSIE_CHECK_EQUAL( (Utility::UnitAwareEvaporationDistribution<ElectronVolt,si::amount>::typeName( false )),
                       "Evaporation" );
  FRENSIE_CHECK_EQUAL( (Utility::typeName<Utility::UnitAwareEvaporationDistribution<ElectronVolt,si::amount> >()),
                       std::string("UnitAwareEvaporationDistribution<")+Utility::typeName<ElectronVolt>()+","+Utility::typeName<si::amount>()+">" );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
FRENSIE_UNIT_TEST( EvaporationDistribution, isTabular )
{
  FRENSIE_CHECK( !distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular
FRENSIE_UNIT_TEST( UnitAwareEvaporationDistribution, isTabular )
{
  FRENSIE_CHECK( !unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
FRENSIE_UNIT_TEST( EvaporationDistribution, isContinuous )
{
  FRENSIE_CHECK( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is continuous
FRENSIE_UNIT_TEST( UnitAwareEvaporationDistribution, isContinuous )
{
  FRENSIE_CHECK( unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
FRENSIE_UNIT_TEST( EvaporationDistribution, isCompatibleWithInterpType )
{
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
FRENSIE_UNIT_TEST( UnitAwareEvaporationDistribution,
                   isCompatibleWithInterpType )
{
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be converted to a string
FRENSIE_UNIT_TEST( EvaporationDistribution, toString )
{
  //std::string dist_string = Utility::toString( *distribution );
  std::string dist_string =
    Utility::toString( Utility::EvaporationDistribution() );

  FRENSIE_CHECK_EQUAL( dist_string, "{Evaporation Distribution, 1.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::EvaporationDistribution( 2.0 ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Evaporation Distribution, 2.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::EvaporationDistribution( 3.0, 2.0 ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Evaporation Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::EvaporationDistribution( 3.0, 2.0, 1.0 ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Evaporation Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::EvaporationDistribution( 3.0, 2.0, 1.0, 10.0 ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Evaporation Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+01}" );

  FRENSIE_CHECK_NO_THROW( dist_string = Utility::toString( *distribution ) );
  FRENSIE_CHECK_LESS( dist_string.find( "Evaporation Distribution" ),
                      dist_string.size() );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be converted to a string
FRENSIE_UNIT_TEST( UnitAwareEvaporationDistribution, toString )
{
  //std::string dist_string = Utility::toString( *distribution );
  std::string dist_string =
    Utility::toString( Utility::UnitAwareEvaporationDistribution<ElectronVolt,si::amount>() );

  FRENSIE_CHECK_EQUAL( dist_string, "{Evaporation Distribution, 1.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::UnitAwareEvaporationDistribution<ElectronVolt,si::amount>( 2.0*eV ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Evaporation Distribution, 2.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::UnitAwareEvaporationDistribution<ElectronVolt,si::amount>( 3.0*eV, 2.0*eV ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Evaporation Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::UnitAwareEvaporationDistribution<ElectronVolt,si::amount>( 3.0*eV, 2.0*eV, 1.0*eV ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Evaporation Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::UnitAwareEvaporationDistribution<ElectronVolt,si::amount>( 3.0*eV, 2.0*eV, 1.0*eV, 10.0 ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Evaporation Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+01}" );

  FRENSIE_CHECK_NO_THROW( dist_string = Utility::toString( *unit_aware_distribution ) );
  FRENSIE_CHECK_LESS( dist_string.find( "Evaporation Distribution" ),
                      dist_string.size() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
FRENSIE_UNIT_TEST( EvaporationDistribution, toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, Utility::EvaporationDistribution() );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Evaporation Distribution, 1.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::EvaporationDistribution( 2.0 ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Evaporation Distribution, 2.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::EvaporationDistribution( 3.0, 2.0 ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Evaporation Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::EvaporationDistribution( 3.0, 2.0, 1.0 ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Evaporation Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::EvaporationDistribution( 3.0, 2.0, 1.0, 10.0 ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Evaporation Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+01}" );

  oss.str( "" );
  oss.clear();

  FRENSIE_CHECK_NO_THROW( Utility::toStream( oss, *distribution ) );
  FRENSIE_CHECK_LESS( oss.str().find( "Evaporation Distribution" ),
                      oss.str().size() );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST( UnitAwareEvaporationDistribution, toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, Utility::UnitAwareEvaporationDistribution<ElectronVolt,si::amount>() );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Evaporation Distribution, 1.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::UnitAwareEvaporationDistribution<ElectronVolt,si::amount>( 2.0*eV ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Evaporation Distribution, 2.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::UnitAwareEvaporationDistribution<ElectronVolt,si::amount>( 3.0*eV, 2.0*eV ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Evaporation Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::UnitAwareEvaporationDistribution<ElectronVolt,si::amount>( 3.0*eV, 2.0*eV, 1.0*eV ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Evaporation Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::UnitAwareEvaporationDistribution<ElectronVolt,si::amount>( 3.0*eV, 2.0*eV, 1.0*eV, 10.0 ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Evaporation Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+01}" );

  oss.str( "" );
  oss.clear();

  FRENSIE_CHECK_NO_THROW( Utility::toStream( oss, *unit_aware_distribution ) );
  FRENSIE_CHECK_LESS( oss.str().find( "Evaporation Distribution" ),
                      oss.str().size() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
FRENSIE_UNIT_TEST( EvaporationDistribution, ostream_operator )
{
  std::ostringstream oss;

  oss << Utility::EvaporationDistribution();

  FRENSIE_CHECK_EQUAL( oss.str(), "{Evaporation Distribution, 1.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::EvaporationDistribution( 2.0 );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Evaporation Distribution, 2.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::EvaporationDistribution( 3.0, 2.0 );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Evaporation Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::EvaporationDistribution( 3.0, 2.0, 1.0 );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Evaporation Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::EvaporationDistribution( 3.0, 2.0, 1.0, 10.0 );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Evaporation Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+01}" );

  oss.str( "" );
  oss.clear();

  FRENSIE_CHECK_NO_THROW( oss << *distribution );
  FRENSIE_CHECK_LESS( oss.str().find( "Evaporation Distribution" ),
                      oss.str().size() );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST( UnitAwareEvaporationDistribution, ostream_operator )
{
  std::ostringstream oss;

  oss << Utility::UnitAwareEvaporationDistribution<ElectronVolt,si::amount>();

  FRENSIE_CHECK_EQUAL( oss.str(), "{Evaporation Distribution, 1.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareEvaporationDistribution<ElectronVolt,si::amount>( 2.0*eV );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Evaporation Distribution, 2.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareEvaporationDistribution<ElectronVolt,si::amount>( 3.0*eV, 2.0*eV );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Evaporation Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareEvaporationDistribution<ElectronVolt,si::amount>( 3.0*eV, 2.0*eV, 1.0*eV );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Evaporation Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareEvaporationDistribution<ElectronVolt,si::amount>( 3.0*eV, 2.0*eV, 1.0*eV, 10.0 );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Evaporation Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+01}" );

  oss.str( "" );
  oss.clear();

  FRENSIE_CHECK_NO_THROW( oss << *unit_aware_distribution );
  FRENSIE_CHECK_LESS( oss.str().find( "Evaporation Distribution" ),
                      oss.str().size() );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a string
FRENSIE_UNIT_TEST( EvaporationDistribution, fromString )
{
  Utility::EvaporationDistribution test_dist =
    Utility::fromString<Utility::EvaporationDistribution>( "{Evaporation Distribution}" );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::EvaporationDistribution() );

  test_dist =
    Utility::fromString<Utility::EvaporationDistribution>( "{Evaporation Distribution, 3.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::EvaporationDistribution( 3.0 ) );

  test_dist =
    Utility::fromString<Utility::EvaporationDistribution>( "{evaporation distribution, 3.0, 2.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::EvaporationDistribution( 3.0, 2.0 ) );

  test_dist =
    Utility::fromString<Utility::EvaporationDistribution>( "{Evaporation, 3.0, 2.0, 1.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::EvaporationDistribution( 3.0, 2.0, 1.0 ) );

  test_dist =
    Utility::fromString<Utility::EvaporationDistribution>( "{evaporation, 3.0, 2.0, 1.0, 10.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::EvaporationDistribution( 3.0, 2.0, 1.0, 10.0 ) );

  test_dist =
    Utility::fromString<Utility::EvaporationDistribution>( Utility::toString(*distribution) );

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::EvaporationDistribution*>( distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialized from a string
FRENSIE_UNIT_TEST( UnitAwareEvaporationDistribution, fromString )
{
  Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount> test_dist=
    Utility::fromString<Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount> >( "{Evaporation Distribution}" );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>()) );

  test_dist =
    Utility::fromString<Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount> >( "{Evaporation Distribution, 3.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV )) );

  test_dist =
    Utility::fromString<Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount> >( "{evaporation distribution, 3.0, 2.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV )) );

  test_dist =
    Utility::fromString<Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount> >( "{Evaporation, 3.0, 2.0, 1.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV )) );

  test_dist =
    Utility::fromString<Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount> >( "{evaporation, 3.0, 2.0, 1.0, 10.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV, 10.0 )) );

  test_dist =
    Utility::fromString<Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount> >( Utility::toString(*distribution) );

  FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>*>( unit_aware_distribution.get() )) );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a stream
FRENSIE_UNIT_TEST( EvaporationDistribution, fromStream )
{
  std::istringstream iss( "{Evaporation Distribution}" );
  
  Utility::EvaporationDistribution test_dist;

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::EvaporationDistribution() );

  iss.str( "{Evaporation Distribution, 3.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::EvaporationDistribution( 3.0 ) );

  iss.str( "{evaporation distribution, 3.0, 2.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::EvaporationDistribution( 3.0, 2.0 ) );

  iss.str( "{Evaporation, 3.0, 2.0, 1.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::EvaporationDistribution( 3.0, 2.0, 1.0 ) );

  iss.str( "{evaporation, 3.0, 2.0, 1.0, 10.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::EvaporationDistribution( 3.0, 2.0, 1.0, 10.0 ) );

  iss.str( Utility::toString(*distribution) );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::EvaporationDistribution*>( distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialized from a stream
FRENSIE_UNIT_TEST( UnitAwareEvaporationDistribution, fromStream )
{
  std::istringstream iss( "{Evaporation Distribution}" );
  
  Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount> test_dist;

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>()) );

  iss.str( "{Evaporation Distribution, 3.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV )) );

  iss.str( "{evaporation distribution, 3.0, 2.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV )) );

  iss.str( "{Evaporation, 3.0, 2.0, 1.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV )) );

  iss.str( "{evaporation, 3.0, 2.0, 1.0, 10.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV, 10.0 )) );

  iss.str( Utility::toString(*unit_aware_distribution) );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>*>( unit_aware_distribution.get() )) );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a stream
FRENSIE_UNIT_TEST( EvaporationDistribution, istream_operator )
{
  std::istringstream iss( "{Evaporation Distribution}" );
  
  Utility::EvaporationDistribution test_dist;

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, Utility::EvaporationDistribution() );

  iss.str( "{Evaporation Distribution, 3.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, Utility::EvaporationDistribution( 3.0 ) );

  iss.str( "{evaporation distribution, 3.0, 2.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, Utility::EvaporationDistribution( 3.0, 2.0 ) );

  iss.str( "{Evaporation, 3.0, 2.0, 1.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, Utility::EvaporationDistribution( 3.0, 2.0, 1.0 ) );

  iss.str( "{evaporation, 3.0, 2.0, 1.0, 10.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, Utility::EvaporationDistribution( 3.0, 2.0, 1.0, 10.0 ) );

  iss.str( Utility::toString(*distribution) );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::EvaporationDistribution*>( distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialized from a stream
FRENSIE_UNIT_TEST( UnitAwareEvaporationDistribution, istream_operator )
{
  std::istringstream iss( "{Evaporation Distribution}" );
  
  Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount> test_dist;

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>()) );

  iss.str( "{Evaporation Distribution, 3.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV )) );

  iss.str( "{evaporation distribution, 3.0, 2.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV )) );

  iss.str( "{Evaporation, 3.0, 2.0, 1.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV )) );

  iss.str( "{evaporation, 3.0, 2.0, 1.0, 10.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV, 10.0 )) );

  iss.str( Utility::toString(*unit_aware_distribution) );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>*>( unit_aware_distribution.get() )) );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to a property tree
FRENSIE_UNIT_TEST( EvaporationDistribution, toPropertyTree )
{
  // Use the property tree interface directly
  Utility::PropertyTree ptree;

  ptree.put( "test distribution", Utility::EvaporationDistribution() );

  Utility::EvaporationDistribution copy_dist =
    ptree.get<Utility::EvaporationDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, Utility::EvaporationDistribution() );

  ptree.put( "test distribution", Utility::EvaporationDistribution( 3.0 ) );

  copy_dist = ptree.get<Utility::EvaporationDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, Utility::EvaporationDistribution( 3.0 ) );

  ptree.put( "test distribution", Utility::EvaporationDistribution( 3.0, 2.0 ) );

  copy_dist = ptree.get<Utility::EvaporationDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, Utility::EvaporationDistribution( 3.0, 2.0 ) );

  ptree.put( "test distribution", Utility::EvaporationDistribution( 3.0, 2.0, 1.0 ) );

  copy_dist = ptree.get<Utility::EvaporationDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, Utility::EvaporationDistribution( 3.0, 2.0, 1.0 ) );

  ptree.put( "test distribution", Utility::EvaporationDistribution( 3.0, 2.0, 1.0, 10.0 ) );

  copy_dist = ptree.get<Utility::EvaporationDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, Utility::EvaporationDistribution( 3.0, 2.0, 1.0, 10.0 ) );

  ptree.put( "test distribution", *distribution );

  copy_dist = ptree.get<Utility::EvaporationDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::EvaporationDistribution*>( distribution.get() ) );

  // Use the PropertyTreeCompatibleObject interface
  ptree = Utility::EvaporationDistribution().toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::EvaporationDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::EvaporationDistribution() );

  ptree = Utility::EvaporationDistribution().toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Evaporation Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::EvaporationDistribution( 3.0 ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::EvaporationDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::EvaporationDistribution( 3.0 ) );

  ptree = Utility::EvaporationDistribution( 3.0 ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Evaporation Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::EvaporationDistribution( 3.0, 2.0 ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::EvaporationDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::EvaporationDistribution( 3.0, 2.0 ) );

  ptree = Utility::EvaporationDistribution( 3.0, 2.0 ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Evaporation Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::EvaporationDistribution( 3.0, 2.0, 1.0 ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::EvaporationDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::EvaporationDistribution( 3.0, 2.0, 1.0 ) );

  ptree = Utility::EvaporationDistribution( 3.0, 2.0, 1.0 ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Evaporation Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::EvaporationDistribution( 3.0, 2.0, 1.0, 10.0 ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::EvaporationDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::EvaporationDistribution( 3.0, 2.0, 1.0, 10.0 ) );

  ptree = Utility::EvaporationDistribution( 3.0, 2.0, 1.0, 10.0 ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Evaporation Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 10.0 );

  ptree = distribution->toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::EvaporationDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::EvaporationDistribution*>( distribution.get() ) );

  ptree = distribution->toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Evaporation Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.1 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  // Use the property tree helper methods
  ptree = Utility::toPropertyTree( Utility::EvaporationDistribution(), true );

  copy_dist = ptree.get_value<Utility::EvaporationDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::EvaporationDistribution() );

  ptree = Utility::toPropertyTree( Utility::EvaporationDistribution(), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Evaporation Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::toPropertyTree( *distribution, true );

  copy_dist = ptree.get_value<Utility::EvaporationDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::EvaporationDistribution*>( distribution.get() ) );

  ptree = Utility::toPropertyTree( *distribution, false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Evaporation Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.1 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::toPropertyTree( *distribution );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Evaporation Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.1 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be written to a property tree
FRENSIE_UNIT_TEST( UnitAwareEvaporationDistribution, toPropertyTree )
{
  // Use the property tree interface directly
  Utility::PropertyTree ptree;
  
  ptree.put( "test distribution", Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>() );

  Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount> copy_dist =
    ptree.get<Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>()) );

  ptree.put( "test distribution", (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV )) );

  copy_dist = ptree.get<Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV )) );

  ptree.put( "test distribution", (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV )) );

  copy_dist = ptree.get<Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV )) );

  ptree.put( "test distribution", (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV )) );

  copy_dist = ptree.get<Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV )) );

  ptree.put( "test distribution", (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV, 10.0 )) );

  copy_dist = ptree.get<Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV, 10.0 )) );

  ptree.put( "test distribution", *distribution );

  copy_dist = ptree.get<Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (*dynamic_cast<Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>*>( unit_aware_distribution.get() )) );

  // Use the PropertyTreeCompatibleObject interface
  ptree = Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>().toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>()) );

  ptree = Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>().toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Evaporation Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV )) );

  ptree = Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Evaporation Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV )) );

  ptree = Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Evaporation Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV )) );

  ptree = Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Evaporation Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV, 10.0 ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV, 10.0 )) );

  ptree = Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV, 10.0 ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Evaporation Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 10.0 );

  ptree = unit_aware_distribution->toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (*dynamic_cast<Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>*>( unit_aware_distribution.get() )) );

  ptree = unit_aware_distribution->toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Evaporation Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.1 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  // Use the property tree helper methods
  ptree = Utility::toPropertyTree( Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>(), true );

  copy_dist = ptree.get_value<Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>()) );

  ptree = Utility::toPropertyTree( Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>(), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Evaporation Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::toPropertyTree( *unit_aware_distribution, true );

  copy_dist = ptree.get_value<Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (*dynamic_cast<Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>*>( unit_aware_distribution.get() )) );

  ptree = Utility::toPropertyTree( *unit_aware_distribution, false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Evaporation Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.1 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::toPropertyTree( *unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Evaporation Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.1 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be read from a property tree
FRENSIE_DATA_UNIT_TEST( EvaporationDistribution,
                        fromPropertyTree,
                        TestPropertyTreeTable )
{                                                                     
  FETCH_FROM_TABLE( std::string, dist_name );                           
  FETCH_FROM_TABLE( bool, valid_dist_rep );                             
  FETCH_FROM_TABLE( std::vector<std::string>, expected_unused_children ); 
  FETCH_FROM_TABLE( Utility::EvaporationDistribution, expected_dist );     
                                                   
  Utility::EvaporationDistribution dist;                         
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
            dist = Utility::fromPropertyTree<Utility::EvaporationDistribution>(
                                    test_dists_ptree->get_child( dist_name ), 
                                    unused_children ) );                
    FRENSIE_CHECK_EQUAL( dist, expected_dist );                         
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );   
  }                                                                     
  else                                                                  
  {                                                                   
    FRENSIE_CHECK_THROW(
                 Utility::fromPropertyTree<Utility::EvaporationDistribution>(
                                  test_dists_ptree->get_child( dist_name ) ), 
                 Utility::PropertyTreeConversionException );    
  }                                                                     
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be read from a property tree
FRENSIE_DATA_UNIT_TEST( UnitAwareEvaporationDistribution,
                        fromPropertyTree,
                        TestPropertyTreeTable )  
{
  typedef Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount> DistributionType;
  
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
FRENSIE_UNIT_TEST( EvaporationDistribution, archive )
{
  std::string archive_name( "test_evaporation_dist.h5a" );

  // Create and archive some evaporation distributions
  {
    Utility::EvaporationDistribution dist_a;
    Utility::EvaporationDistribution dist_b( 3.0 );
    Utility::EvaporationDistribution dist_c( 3.0, 2.0 );
    Utility::EvaporationDistribution dist_d( 3.0, 2.0, 1.0 );
    Utility::EvaporationDistribution dist_e( 3.0, 2.0, 1.0, 10.0 );

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
                             archive << BOOST_SERIALIZATION_NVP( distribution )
                             );
  }

  // Load the archived distributions
  Utility::HDF5IArchive archive( archive_name );

  Utility::EvaporationDistribution dist_a;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_a )
                           );
  FRENSIE_CHECK_EQUAL( dist_a, Utility::EvaporationDistribution() );

  Utility::EvaporationDistribution dist_b;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_b )
                           );
  FRENSIE_CHECK_EQUAL( dist_b, Utility::EvaporationDistribution( 3.0 ) );

  Utility::EvaporationDistribution dist_c;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_c )
                           );
  FRENSIE_CHECK_EQUAL( dist_c, Utility::EvaporationDistribution( 3.0, 2.0 ) );

  Utility::EvaporationDistribution dist_d;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_d )
                           );
  FRENSIE_CHECK_EQUAL( dist_d, Utility::EvaporationDistribution( 3.0, 2.0, 1.0 ) );

  Utility::EvaporationDistribution dist_e;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_e )
                           );
  FRENSIE_CHECK_EQUAL( dist_e, Utility::EvaporationDistribution( 3.0, 2.0, 1.0, 10.0 ) );

  std::shared_ptr<Utility::OneDDistribution> shared_dist;

  FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "distribution", shared_dist ) );
  FRENSIE_CHECK_EQUAL( shared_dist->getLowerBoundOfIndepVar(), 0.0 );
  FRENSIE_CHECK_EQUAL( shared_dist->getUpperBoundOfIndepVar(), 0.9 );
  FRENSIE_CHECK_EQUAL( shared_dist->evaluate( 0.0 ), 0.0 );
  FRENSIE_CHECK_EQUAL( shared_dist->evaluate( 0.9 ), 0.9*exp( -0.9 ) );
  FRENSIE_CHECK_EQUAL( shared_dist->evaluate( 1.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be archived
FRENSIE_UNIT_TEST( UnitAwareEvaporationDistribution, archive )
{
  std::string archive_name( "test_unit_aware_evaporation_dist.h5a" );

  // Create and archive some evaporation distributions
  {
    Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount> dist_a;
    Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount> dist_b( 3.0*MeV );
    Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount> dist_c( 3.0*MeV, 2.0*MeV );
    Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount> dist_d( 3.0*MeV, 2.0*MeV, 1.0*MeV );
    Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount> dist_e( 3.0*MeV, 2.0*MeV, 1.0*MeV, 10.0 );

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
                  archive << BOOST_SERIALIZATION_NVP( unit_aware_distribution )
                             );
  }

  // Load the archived distributions
  Utility::HDF5IArchive archive( archive_name );

  Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount> dist_a;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_a )
                           );
  FRENSIE_CHECK_EQUAL( dist_a, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>()) );

  Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount> dist_b;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_b )
                           );
  FRENSIE_CHECK_EQUAL( dist_b, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV )) );

  Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount> dist_c;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_c )
                           );
  FRENSIE_CHECK_EQUAL( dist_c, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV )) );

  Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount> dist_d;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_d )
                           );
  FRENSIE_CHECK_EQUAL( dist_d, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV )) );

  Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount> dist_e;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_e )
                           );
  FRENSIE_CHECK_EQUAL( dist_e, (Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV, 10.0 )) );

  std::shared_ptr<Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount> > shared_dist;

  FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "distribution", shared_dist ) );
  FRENSIE_CHECK_EQUAL( shared_dist->getLowerBoundOfIndepVar(), 0.0*MeV );
  FRENSIE_CHECK_EQUAL( shared_dist->getUpperBoundOfIndepVar(), 0.9*MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV ),
		       0.0*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.9*MeV ),
                       0.9*exp(-0.9)*si::mole );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.0*MeV ),
		       0.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that distributions can be scaled
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareEvaporationDistribution,
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
  Utility::UnitAwareEvaporationDistribution<IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwareEvaporationDistribution<IndepUnitA,DepUnitA>::fromUnitlessDistribution( *dynamic_cast<Utility::EvaporationDistribution*>( distribution.get() ) );

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
			0.9*exp(-0.9)/(1.0 - exp(-0.9)*(1.0+0.9)) );
  Utility::setQuantity( dep_quantity_a, 0.9*exp(-0.9) );

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
// end tstEvaporationDistribution.cpp
//---------------------------------------------------------------------------//

