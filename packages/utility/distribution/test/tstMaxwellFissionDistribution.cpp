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

// FRENSIE Includes
#include "Utility_MaxwellFissionDistribution.hpp"
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
				 new Utility::MaxwellFissionDistribution( 1.0, 1.0, 0.1 ) );

std::shared_ptr<Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount> >
  unit_aware_distribution( new Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 1e6*eV, 1e3*keV, 0.1*MeV ) );

//---------------------------------------------------------------------------//
// Testing Tables
//---------------------------------------------------------------------------//
// This table describes the data in the property tree
FRENSIE_DATA_TABLE( TestPropertyTreeTable )
{
  std::vector<std::string> no_unused_children;

  // The data table will always use the basic distribution since they are
  // serialized the same in the table
  Utility::MaxwellFissionDistribution dummy_dist;

  COLUMNS() << "dist_name" << "valid_dist_rep" << "expected_unused_children" << "expected_dist";
  NEW_ROW( "inline_5_args_valid" ) << "Distribution A" << true  << no_unused_children << Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0, 0.1 );
  NEW_ROW( "inline_4_args_valid" ) << "Distribution B" << true  << no_unused_children << Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0 );
  NEW_ROW( "inline_3_args_valid" ) << "Distribution C" << true  << no_unused_children << Utility::MaxwellFissionDistribution( 3.0, 2.0 );
  NEW_ROW( "inline_2_args_valid" ) << "Distribution D" << true  << no_unused_children << Utility::MaxwellFissionDistribution( 3.0 );
  NEW_ROW( "inline_1_arg_valid" )  << "Distribution E" << true  << no_unused_children << Utility::MaxwellFissionDistribution();
  NEW_ROW( "inline_bad_type" )     << "Distribution M" << false << no_unused_children << dummy_dist;

  NEW_ROW( "1_arg_valid" )         << "Distribution F" << true  << no_unused_children << Utility::MaxwellFissionDistribution();
  NEW_ROW( "2_args_valid" )        << "Distribution G" << true  << no_unused_children << Utility::MaxwellFissionDistribution( 3.0 );
  NEW_ROW( "3_args_valid" )        << "Distribution H" << true  << no_unused_children << Utility::MaxwellFissionDistribution( 3.0, 2.0 );
  NEW_ROW( "4_args_valid" )        << "Distribution I" << true  << no_unused_children << Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0 );
  NEW_ROW( "5_args_valid" )        << "Distribution J" << true  << no_unused_children << Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0, 0.1 );
  NEW_ROW( "5_abrv_args_valid" )   << "Distribution K" << true  << no_unused_children << Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0, 0.1 );
  NEW_ROW( "6_args_valid" )        << "Distribution L" << true  << std::vector<std::string>({"dummy"}) << Utility::MaxwellFissionDistribution( 1.0, 1.0, 0.1, 10.0 );
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
FRENSIE_UNIT_TEST( MaxwellFissionDistribution, evaluate )
{
  double test_value_1 = 0.0 ;
  double test_value_2 = sqrt( 0.9 )*exp( -0.9 );

  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.0 ), test_value_1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 0.9 ), test_value_2 );
  FRENSIE_CHECK_EQUAL( distribution->evaluate( 1.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
FRENSIE_UNIT_TEST( UnitAwareMaxwellFissionDistribution, evaluate )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.0*MeV ),
		       0.0*si::mole );
  
  double scale_factor = sqrt( 0.9 )*exp( -0.9 );

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 0.9*MeV ),
                       scale_factor*si::mole );
  
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluate( 1.0*MeV ),
		       0.0*si::mole );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
FRENSIE_UNIT_TEST( MaxwellFissionDistribution, evaluatePDF )
{
  double test_value_1 = 0.0;
  double test_value_2 = sqrt( 0.9 )*exp( -0.9 )/
    (sqrt(Utility::PhysicalConstants::pi)*0.5*erf(sqrt(0.9)) -
     sqrt(0.9)*exp(-0.9));
  
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.0 ), test_value_1 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 0.9 ), test_value_2 );
  FRENSIE_CHECK_EQUAL( distribution->evaluatePDF( 1.0 ), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
FRENSIE_UNIT_TEST( UnitAwareMaxwellFissionDistribution, evaluatePDF )
{
  double scale_factor = sqrt( 0.9 )*exp( -0.9 )/
    (sqrt(Utility::PhysicalConstants::pi)*0.5*erf(sqrt(0.9)) -
     sqrt(0.9)*exp(-0.9));

  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 0.0*MeV ),
		       0.0/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 0.9*MeV ),
                       scale_factor/MeV );
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->evaluatePDF( 1.0*MeV ),
		       0.0/MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled using OpenMC method
FRENSIE_UNIT_TEST( MaxwellFissionDistribution, sample )
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
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.78269807500829, 1e-14 );

  sample = distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.89106359701991, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled using OpenMC method
FRENSIE_UNIT_TEST( UnitAwareMaxwellFissionDistribution, sample )
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
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.78269807500829*MeV, 1e-14 );

  sample = unit_aware_distribution->sample();
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.89106359701991*MeV, 1e-14 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled using OpenMC method and the
// trials can be recorded
FRENSIE_UNIT_TEST( MaxwellFissionDistribution, sampleAndRecordTrials )
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

  Utility::DistributionTraits::Counter trials = 0;

  double sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.78269807500829, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 1.0 );

  sample = distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.89106359701991, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled using OpenMC method
// and the trials can be recorded
FRENSIE_UNIT_TEST( UnitAwareMaxwellFissionDistribution, sampleAndRecordTrials )
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

  Utility::DistributionTraits::Counter trials = 0;

  quantity<MegaElectronVolt> sample =
    unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.78269807500829*MeV, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 1.0 );

  sample = unit_aware_distribution->sampleAndRecordTrials( trials );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.89106359701991*MeV, 1e-14 );
  FRENSIE_CHECK_EQUAL( trials, 3.0 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled using OpenMC method, passing in
// parameters
FRENSIE_UNIT_TEST( MaxwellFissionDistribution,
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
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.20924646054839, 1e-13 );

  incident_energy = 0.75;
  nuclear_temperature = 0.5;
  restriction_energy = 0.25;

  sample = Utility::MaxwellFissionDistribution::sample( incident_energy, nuclear_temperature, restriction_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.41023025568120, 1e-13 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled using OpenMC method,
// passing in parameters
FRENSIE_UNIT_TEST( UnitAwareMaxwellFissionDistribution,
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
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.20924646054839*MeV, 1e-13 );

  incident_energy = 0.75*MeV;
  nuclear_temperature = 0.5*MeV;
  restriction_energy = 0.25*MeV;

  sample = Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt>::sample( incident_energy, nuclear_temperature, restriction_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.41023025568120*MeV, 1e-13 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled using OpenMC method, passing in
// parameters
FRENSIE_UNIT_TEST( MaxwellFissionDistribution,
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
  Utility::DistributionTraits::Counter trials = 0;

  incident_energy = 0.5;
  nuclear_temperature = 0.1;
  restriction_energy = 0.01;

  sample = Utility::MaxwellFissionDistribution::sampleAndRecordTrials(incident_energy, nuclear_temperature, restriction_energy, trials);
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.20924646054839, 1e-13 );

  incident_energy = 0.75;
  nuclear_temperature = 0.5;
  restriction_energy = 0.25;

  sample = Utility::MaxwellFissionDistribution::sampleAndRecordTrials(incident_energy, nuclear_temperature, restriction_energy, trials);
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.41023025568120, 1e-13 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be sampled using OpenMC method,
// passing in parameters
FRENSIE_UNIT_TEST( UnitAwareMaxwellFissionDistribution,
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
  Utility::DistributionTraits::Counter trials = 0;

  incident_energy = 0.5*MeV;
  nuclear_temperature = 0.1*MeV;
  restriction_energy = 0.01*MeV;

  sample = Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,void>::sampleAndRecordTrials(incident_energy, nuclear_temperature, restriction_energy, trials);
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.20924646054839*MeV, 1e-13 );

  incident_energy = 0.75*MeV;
  nuclear_temperature = 0.5*MeV;
  restriction_energy = 0.25*MeV;

  sample = Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>::sampleAndRecordTrials(incident_energy, nuclear_temperature, restriction_energy, trials);
  FRENSIE_CHECK_FLOATING_EQUALITY( sample, 0.41023025568120*MeV, 1e-13 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST( MaxwellFissionDistribution, getUpperBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getUpperBoundOfIndepVar(), 0.9 );
}

//---------------------------------------------------------------------------//
// Check that the upper bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST( UnitAwareMaxwellFissionDistribution,
		   getUpperBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getUpperBoundOfIndepVar(),
		       0.9*MeV );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the distribution independent variable can be
// returned
FRENSIE_UNIT_TEST( MaxwellFissionDistribution, getLowerBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( distribution->getLowerBoundOfIndepVar(), 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the lower bound of the unit-aware distribution independent
// variable can be returned
FRENSIE_UNIT_TEST( UnitAwareMaxwellFissionDistribution,
		   getLowerBoundOfIndepVar )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getLowerBoundOfIndepVar(),
		       0.0*MeV );
}

//---------------------------------------------------------------------------//
// Check that the distribution type can be returned
FRENSIE_UNIT_TEST( MaxwellFissionDistribution, getDistributionType )
{
  FRENSIE_CHECK_EQUAL( distribution->getDistributionType(),
		       Utility::MAXWELLFISSION_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type can be returned
FRENSIE_UNIT_TEST( UnitAwareMaxwellFissionDistribution, getDistributionType )
{
  FRENSIE_CHECK_EQUAL( unit_aware_distribution->getDistributionType(),
		       Utility::MAXWELLFISSION_DISTRIBUTION );
}

//---------------------------------------------------------------------------//
// Check that the distribution type name can be returned
FRENSIE_UNIT_TEST( MaxwellFissionDistribution, getDistributionTypeName )
{
  FRENSIE_CHECK_EQUAL( Utility::MaxwellFissionDistribution::typeName( true, false, " " ),
                       "Maxwell Fission Distribution" );
  FRENSIE_CHECK_EQUAL( Utility::MaxwellFissionDistribution::typeName( false ),
                       "Maxwell" );
  FRENSIE_CHECK_EQUAL( Utility::typeName<Utility::MaxwellFissionDistribution>(),
                       "MaxwellFissionDistribution" );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution type name can be returned
FRENSIE_UNIT_TEST( UnitAwareMaxwellFissionDistribution,
                   getDistributionTypeName )
{
  FRENSIE_CHECK_EQUAL( (Utility::UnitAwareMaxwellFissionDistribution<ElectronVolt,si::amount>::typeName( true, false, " " )),
                       "Maxwell Fission Distribution" );
  FRENSIE_CHECK_EQUAL( (Utility::UnitAwareMaxwellFissionDistribution<ElectronVolt,si::amount>::typeName( false )),
                       "Maxwell" );
  FRENSIE_CHECK_EQUAL( (Utility::typeName<Utility::UnitAwareMaxwellFissionDistribution<ElectronVolt,si::amount> >()),
                       std::string("UnitAwareMaxwellFissionDistribution<")+Utility::typeName<ElectronVolt>()+","+Utility::typeName<si::amount>()+">" );
}

//---------------------------------------------------------------------------//
// Check if the distribution is tabular
FRENSIE_UNIT_TEST( MaxwellFissionDistribution, isTabular )
{
  FRENSIE_CHECK( !distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is tabular
FRENSIE_UNIT_TEST( UnitAwareMaxwellFissionDistribution, isTabular )
{
  FRENSIE_CHECK( !unit_aware_distribution->isTabular() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is continuous
FRENSIE_UNIT_TEST( MaxwellFissionDistribution, isContinuous )
{
  FRENSIE_CHECK( distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is continuous
FRENSIE_UNIT_TEST( UnitAwareMaxwellFissionDistribution, isContinuous )
{
  FRENSIE_CHECK( unit_aware_distribution->isContinuous() );
}

//---------------------------------------------------------------------------//
// Check if the distribution is compatible with the interpolation type
FRENSIE_UNIT_TEST( MaxwellFissionDistribution, isCompatibleWithInterpType )
{
  FRENSIE_CHECK( distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !distribution->isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check if the unit-aware distribution is compatible with the interp type
FRENSIE_UNIT_TEST( UnitAwareMaxwellFissionDistribution,
                   isCompatibleWithInterpType )
{
  FRENSIE_CHECK( unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLin>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LinLog>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLin>() );
  FRENSIE_CHECK( !unit_aware_distribution->isCompatibleWithInterpType<Utility::LogLog>() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be converted to a string
FRENSIE_UNIT_TEST( MaxwellFissionDistribution, toString )
{
  std::string dist_string =
    Utility::toString( Utility::MaxwellFissionDistribution() );

  FRENSIE_CHECK_EQUAL( dist_string, "{Maxwell Fission Distribution, 1.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::MaxwellFissionDistribution( 2.0 ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Maxwell Fission Distribution, 2.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::MaxwellFissionDistribution( 3.0, 2.0 ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Maxwell Fission Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0 ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Maxwell Fission Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0, 10.0 ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Maxwell Fission Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+01}" );

  FRENSIE_CHECK_NO_THROW( dist_string = Utility::toString( *distribution ) );
  FRENSIE_CHECK_LESS( dist_string.find( "Maxwell Fission Distribution" ),
                      dist_string.size() );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be converted to a string
FRENSIE_UNIT_TEST( UnitAwareMaxwellFissionDistribution, toString )
{
  std::string dist_string =
    Utility::toString( Utility::UnitAwareMaxwellFissionDistribution<ElectronVolt,si::amount>() );

  FRENSIE_CHECK_EQUAL( dist_string, "{Maxwell Fission Distribution, 1.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::UnitAwareMaxwellFissionDistribution<ElectronVolt,si::amount>( 2.0*eV ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Maxwell Fission Distribution, 2.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::UnitAwareMaxwellFissionDistribution<ElectronVolt,si::amount>( 3.0*eV, 2.0*eV ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Maxwell Fission Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::UnitAwareMaxwellFissionDistribution<ElectronVolt,si::amount>( 3.0*eV, 2.0*eV, 1.0*eV ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Maxwell Fission Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}" );

  dist_string = Utility::toString( Utility::UnitAwareMaxwellFissionDistribution<ElectronVolt,si::amount>( 3.0*eV, 2.0*eV, 1.0*eV, 10.0 ) );

  FRENSIE_CHECK_EQUAL( dist_string, "{Maxwell Fission Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+01}" );

  FRENSIE_CHECK_NO_THROW( dist_string = Utility::toString( *unit_aware_distribution ) );
  FRENSIE_CHECK_LESS( dist_string.find( "Maxwell Fission Distribution" ),
                      dist_string.size() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
FRENSIE_UNIT_TEST( MaxwellFissionDistribution, toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, Utility::MaxwellFissionDistribution() );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Maxwell Fission Distribution, 1.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::MaxwellFissionDistribution( 2.0 ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Maxwell Fission Distribution, 2.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::MaxwellFissionDistribution( 3.0, 2.0 ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Maxwell Fission Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0 ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Maxwell Fission Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0, 10.0 ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Maxwell Fission Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+01}" );

  oss.str( "" );
  oss.clear();

  FRENSIE_CHECK_NO_THROW( Utility::toStream( oss, *distribution ) );
  FRENSIE_CHECK_LESS( oss.str().find( "Maxwell Fission Distribution" ),
                      oss.str().size() );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST( UnitAwareMaxwellFissionDistribution, toStream )
{
  std::ostringstream oss;

  Utility::toStream( oss, Utility::UnitAwareMaxwellFissionDistribution<ElectronVolt,si::amount>() );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Maxwell Fission Distribution, 1.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::UnitAwareMaxwellFissionDistribution<ElectronVolt,si::amount>( 2.0*eV ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Maxwell Fission Distribution, 2.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::UnitAwareMaxwellFissionDistribution<ElectronVolt,si::amount>( 3.0*eV, 2.0*eV ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Maxwell Fission Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::UnitAwareMaxwellFissionDistribution<ElectronVolt,si::amount>( 3.0*eV, 2.0*eV, 1.0*eV ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Maxwell Fission Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  Utility::toStream( oss, Utility::UnitAwareMaxwellFissionDistribution<ElectronVolt,si::amount>( 3.0*eV, 2.0*eV, 1.0*eV, 10.0 ) );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Maxwell Fission Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+01}" );

  oss.str( "" );
  oss.clear();

  FRENSIE_CHECK_NO_THROW( Utility::toStream( oss, *unit_aware_distribution ) );
  FRENSIE_CHECK_LESS( oss.str().find( "Maxwell Fission Distribution" ),
                      oss.str().size() );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be placed in a stream
FRENSIE_UNIT_TEST( MaxwellFissionDistribution, ostream_operator )
{
  std::ostringstream oss;

  oss << Utility::MaxwellFissionDistribution();

  FRENSIE_CHECK_EQUAL( oss.str(), "{Maxwell Fission Distribution, 1.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::MaxwellFissionDistribution( 2.0 );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Maxwell Fission Distribution, 2.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::MaxwellFissionDistribution( 3.0, 2.0 );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Maxwell Fission Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0 );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Maxwell Fission Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0, 10.0 );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Maxwell Fission Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+01}" );

  oss.str( "" );
  oss.clear();

  FRENSIE_CHECK_NO_THROW( oss << *distribution );
  FRENSIE_CHECK_LESS( oss.str().find( "Maxwell Fission Distribution" ),
                      oss.str().size() );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be placed in a stream
FRENSIE_UNIT_TEST( UnitAwareMaxwellFissionDistribution, ostream_operator )
{
  std::ostringstream oss;

  oss << Utility::UnitAwareMaxwellFissionDistribution<ElectronVolt,si::amount>();

  FRENSIE_CHECK_EQUAL( oss.str(), "{Maxwell Fission Distribution, 1.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareMaxwellFissionDistribution<ElectronVolt,si::amount>( 2.0*eV );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Maxwell Fission Distribution, 2.000000000000000000e+00, 1.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareMaxwellFissionDistribution<ElectronVolt,si::amount>( 3.0*eV, 2.0*eV );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Maxwell Fission Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 0.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareMaxwellFissionDistribution<ElectronVolt,si::amount>( 3.0*eV, 2.0*eV, 1.0*eV );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Maxwell Fission Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+00}" );

  oss.str( "" );
  oss.clear();

  oss << Utility::UnitAwareMaxwellFissionDistribution<ElectronVolt,si::amount>( 3.0*eV, 2.0*eV, 1.0*eV, 10.0 );

  FRENSIE_CHECK_EQUAL( oss.str(), "{Maxwell Fission Distribution, 3.000000000000000000e+00, 2.000000000000000000e+00, 1.000000000000000000e+00, 1.000000000000000000e+01}" );

  oss.str( "" );
  oss.clear();

  FRENSIE_CHECK_NO_THROW( oss << *unit_aware_distribution );
  FRENSIE_CHECK_LESS( oss.str().find( "Maxwell Fission Distribution" ),
                      oss.str().size() );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a string
FRENSIE_UNIT_TEST( MaxwellFissionDistribution, fromString )
{
  Utility::MaxwellFissionDistribution test_dist =
    Utility::fromString<Utility::MaxwellFissionDistribution>( "{Maxwell Fission Distribution}" );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::MaxwellFissionDistribution() );

  test_dist =
    Utility::fromString<Utility::MaxwellFissionDistribution>( "{Maxwell Fission Distribution, 3.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::MaxwellFissionDistribution( 3.0 ) );

  test_dist =
    Utility::fromString<Utility::MaxwellFissionDistribution>( "{maxwell fission distribution, 3.0, 2.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::MaxwellFissionDistribution( 3.0, 2.0 ) );

  test_dist =
    Utility::fromString<Utility::MaxwellFissionDistribution>( "{Maxwell, 3.0, 2.0, 1.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0 ) );

  test_dist =
    Utility::fromString<Utility::MaxwellFissionDistribution>( "{maxwell, 3.0, 2.0, 1.0, 10.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0, 10.0 ) );

  test_dist =
    Utility::fromString<Utility::MaxwellFissionDistribution>( Utility::toString(*distribution) );

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::MaxwellFissionDistribution*>( distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialized from a string
FRENSIE_UNIT_TEST( UnitAwareMaxwellFissionDistribution, fromString )
{
  Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount> test_dist=
    Utility::fromString<Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount> >( "{Maxwell Fission Distribution}" );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>()) );

  test_dist =
    Utility::fromString<Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount> >( "{Maxwell Fission Distribution, 3.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV )) );

  test_dist =
    Utility::fromString<Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount> >( "{maxwell fission distribution, 3.0, 2.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV )) );

  test_dist =
    Utility::fromString<Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount> >( "{Maxwell, 3.0, 2.0, 1.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV )) );

  test_dist =
    Utility::fromString<Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount> >( "{maxwell, 3.0, 2.0, 1.0, 10.0}" );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV, 10.0 )) );

  test_dist =
    Utility::fromString<Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount> >( Utility::toString(*distribution) );

  FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>*>( unit_aware_distribution.get() )) );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a stream
FRENSIE_UNIT_TEST( MaxwellFissionDistribution, fromStream )
{
  std::istringstream iss( "{Maxwell Fission Distribution}" );
  
  Utility::MaxwellFissionDistribution test_dist;

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::MaxwellFissionDistribution() );

  iss.str( "{Maxwell Fission Distribution, 3.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::MaxwellFissionDistribution( 3.0 ) );

  iss.str( "{maxwell fission distribution, 3.0, 2.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::MaxwellFissionDistribution( 3.0, 2.0 ) );

  iss.str( "{Maxwell, 3.0, 2.0, 1.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0 ) );

  iss.str( "{maxwell, 3.0, 2.0, 1.0, 10.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0, 10.0 ) );

  iss.str( Utility::toString(*distribution) );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::MaxwellFissionDistribution*>( distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialized from a stream
FRENSIE_UNIT_TEST( UnitAwareMaxwellFissionDistribution, fromStream )
{
  std::istringstream iss( "{Maxwell Fission Distribution}" );
  
  Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount> test_dist;

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>()) );

  iss.str( "{Maxwell Fission Distribution, 3.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV )) );

  iss.str( "{maxwell fission distribution, 3.0, 2.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV )) );

  iss.str( "{Maxwell, 3.0, 2.0, 1.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV )) );

  iss.str( "{maxwell, 3.0, 2.0, 1.0, 10.0}" );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV, 10.0 )) );

  iss.str( Utility::toString(*unit_aware_distribution) );
  iss.clear();

  Utility::fromStream( iss, test_dist );

  FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>*>( unit_aware_distribution.get() )) );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be initialized from a stream
FRENSIE_UNIT_TEST( MaxwellFissionDistribution, istream_operator )
{
  std::istringstream iss( "{Maxwell Fission Distribution}" );
  
  Utility::MaxwellFissionDistribution test_dist;

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, Utility::MaxwellFissionDistribution() );

  iss.str( "{Maxwell Fission Distribution, 3.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, Utility::MaxwellFissionDistribution( 3.0 ) );

  iss.str( "{maxwell fission distribution, 3.0, 2.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, Utility::MaxwellFissionDistribution( 3.0, 2.0 ) );

  iss.str( "{Maxwell, 3.0, 2.0, 1.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0 ) );

  iss.str( "{maxwell, 3.0, 2.0, 1.0, 10.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0, 10.0 ) );

  iss.str( Utility::toString(*distribution) );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, *dynamic_cast<Utility::MaxwellFissionDistribution*>( distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be initialized from a stream
FRENSIE_UNIT_TEST( UnitAwareMaxwellFissionDistribution, istream_operator )
{
  std::istringstream iss( "{Maxwell Fission Distribution}" );
  
  Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount> test_dist;

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>()) );

  iss.str( "{Maxwell Fission Distribution, 3.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV )) );

  iss.str( "{maxwell fission distribution, 3.0, 2.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV )) );

  iss.str( "{Maxwell, 3.0, 2.0, 1.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV )) );

  iss.str( "{maxwell, 3.0, 2.0, 1.0, 10.0}" );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV, 10.0 )) );

  iss.str( Utility::toString(*unit_aware_distribution) );
  iss.clear();

  iss >> test_dist;

  FRENSIE_CHECK_EQUAL( test_dist, (*dynamic_cast<Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>*>( unit_aware_distribution.get() )) );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be written to a property tree
FRENSIE_UNIT_TEST( MaxwellFissionDistribution, toPropertyTree )
{
  // Use the property tree interface directly
  Utility::PropertyTree ptree;

  ptree.put( "test distribution", Utility::MaxwellFissionDistribution() );

  Utility::MaxwellFissionDistribution copy_dist =
    ptree.get<Utility::MaxwellFissionDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, Utility::MaxwellFissionDistribution() );

  ptree.put( "test distribution", Utility::MaxwellFissionDistribution( 3.0 ) );

  copy_dist = ptree.get<Utility::MaxwellFissionDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, Utility::MaxwellFissionDistribution( 3.0 ) );

  ptree.put( "test distribution", Utility::MaxwellFissionDistribution( 3.0, 2.0 ) );

  copy_dist = ptree.get<Utility::MaxwellFissionDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, Utility::MaxwellFissionDistribution( 3.0, 2.0 ) );

  ptree.put( "test distribution", Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0 ) );

  copy_dist = ptree.get<Utility::MaxwellFissionDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0 ) );

  ptree.put( "test distribution", Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0, 10.0 ) );

  copy_dist = ptree.get<Utility::MaxwellFissionDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0, 10.0 ) );

  ptree.put( "test distribution", *distribution );

  copy_dist = ptree.get<Utility::MaxwellFissionDistribution>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::MaxwellFissionDistribution*>( distribution.get() ) );

  // Use the PropertyTreeCompatibleObject interface
  ptree = Utility::MaxwellFissionDistribution().toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::MaxwellFissionDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::MaxwellFissionDistribution() );

  ptree = Utility::MaxwellFissionDistribution().toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Maxwell Fission Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::MaxwellFissionDistribution( 3.0 ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::MaxwellFissionDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::MaxwellFissionDistribution( 3.0 ) );

  ptree = Utility::MaxwellFissionDistribution( 3.0 ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Maxwell Fission Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::MaxwellFissionDistribution( 3.0, 2.0 ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::MaxwellFissionDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::MaxwellFissionDistribution( 3.0, 2.0 ) );

  ptree = Utility::MaxwellFissionDistribution( 3.0, 2.0 ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Maxwell Fission Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0 ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::MaxwellFissionDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0 ) );

  ptree = Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0 ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Maxwell Fission Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0, 10.0 ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::MaxwellFissionDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0, 10.0 ) );

  ptree = Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0, 10.0 ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Maxwell Fission Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 10.0 );

  ptree = distribution->toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::MaxwellFissionDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::MaxwellFissionDistribution*>( distribution.get() ) );

  ptree = distribution->toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Maxwell Fission Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.1 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  // Use the property tree helper methods
  ptree = Utility::toPropertyTree( Utility::MaxwellFissionDistribution(), true );

  copy_dist = ptree.get_value<Utility::MaxwellFissionDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, Utility::MaxwellFissionDistribution() );

  ptree = Utility::toPropertyTree( Utility::MaxwellFissionDistribution(), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Maxwell Fission Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::toPropertyTree( *distribution, true );

  copy_dist = ptree.get_value<Utility::MaxwellFissionDistribution>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, *dynamic_cast<Utility::MaxwellFissionDistribution*>( distribution.get() ) );

  ptree = Utility::toPropertyTree( *distribution, false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Maxwell Fission Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.1 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::toPropertyTree( *distribution );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Maxwell Fission Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.1 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be written to a property tree
FRENSIE_UNIT_TEST( UnitAwareMaxwellFissionDistribution, toPropertyTree )
{
  // Use the property tree interface directly
  Utility::PropertyTree ptree;
  
  ptree.put( "test distribution", Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>() );

  Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount> copy_dist =
    ptree.get<Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>()) );

  ptree.put( "test distribution", (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV )) );

  copy_dist = ptree.get<Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV )) );

  ptree.put( "test distribution", (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV )) );

  copy_dist = ptree.get<Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV )) );

  ptree.put( "test distribution", (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV )) );

  copy_dist = ptree.get<Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV )) );

  ptree.put( "test distribution", (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV, 10.0 )) );

  copy_dist = ptree.get<Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV, 10.0 )) );

  ptree.put( "test distribution", *distribution );

  copy_dist = ptree.get<Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>>( "test distribution" );

  FRENSIE_CHECK_EQUAL( copy_dist, (*dynamic_cast<Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>*>( unit_aware_distribution.get() )) );

  // Use the PropertyTreeCompatibleObject interface
  ptree = Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>().toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>()) );

  ptree = Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>().toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Maxwell Fission Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV )) );

  ptree = Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Maxwell Fission Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV )) );

  ptree = Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Maxwell Fission Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV )) );

  ptree = Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Maxwell Fission Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV, 10.0 ).toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV, 10.0 )) );

  ptree = Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV, 10.0 ).toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Maxwell Fission Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 3.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 2.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 10.0 );

  ptree = unit_aware_distribution->toPropertyTree( true );

  copy_dist = ptree.get_value<Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (*dynamic_cast<Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>*>( unit_aware_distribution.get() )) );

  ptree = unit_aware_distribution->toPropertyTree( false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Maxwell Fission Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.1 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  // Use the property tree helper methods
  ptree = Utility::toPropertyTree( Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>(), true );

  copy_dist = ptree.get_value<Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>()) );

  ptree = Utility::toPropertyTree( Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>(), false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Maxwell Fission Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::toPropertyTree( *unit_aware_distribution, true );

  copy_dist = ptree.get_value<Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>>();

  FRENSIE_CHECK_EQUAL( ptree.size(), 0 );
  FRENSIE_CHECK_EQUAL( copy_dist, (*dynamic_cast<Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>*>( unit_aware_distribution.get() )) );

  ptree = Utility::toPropertyTree( *unit_aware_distribution, false );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Maxwell Fission Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.1 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );

  ptree = Utility::toPropertyTree( *unit_aware_distribution );

  FRENSIE_CHECK_EQUAL( ptree.size(), 5 );
  FRENSIE_CHECK_EQUAL( ptree.get<std::string>( "type" ), "Maxwell Fission Distribution" );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "incident energy" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "nuclear temperature" ), 1.0 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "restriction energy" ), 0.1 );
  FRENSIE_CHECK_EQUAL( ptree.get<double>( "multiplier" ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that a distribution can be read from a property tree
FRENSIE_DATA_UNIT_TEST( MaxwellFissionDistribution,
                        fromPropertyTree,
                        TestPropertyTreeTable )
{                                                                     
  FETCH_FROM_TABLE( std::string, dist_name );                           
  FETCH_FROM_TABLE( bool, valid_dist_rep );                             
  FETCH_FROM_TABLE( std::vector<std::string>, expected_unused_children ); 
  FETCH_FROM_TABLE( Utility::MaxwellFissionDistribution, expected_dist );     
                                                   
  Utility::MaxwellFissionDistribution dist;                         
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
            dist = Utility::fromPropertyTree<Utility::MaxwellFissionDistribution>(
                                    test_dists_ptree->get_child( dist_name ), 
                                    unused_children ) );                
    FRENSIE_CHECK_EQUAL( dist, expected_dist );                         
    FRENSIE_CHECK_EQUAL( unused_children, expected_unused_children );   
  }                                                                     
  else                                                                  
  {                                                                   
    FRENSIE_CHECK_THROW(
                 Utility::fromPropertyTree<Utility::MaxwellFissionDistribution>(
                                  test_dists_ptree->get_child( dist_name ) ), 
                 Utility::PropertyTreeConversionException );    
  }                                                                     
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be read from a property tree
FRENSIE_DATA_UNIT_TEST( UnitAwareMaxwellFissionDistribution,
                        fromPropertyTree,
                        TestPropertyTreeTable )  
{
  typedef Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount> DistributionType;
  
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
FRENSIE_UNIT_TEST( MaxwellFissionDistribution, archive )
{
  std::string archive_name( "test_maxwell_fission_dist.h5a" );

  // Create and archive some maxwell fission distributions
  {
    Utility::MaxwellFissionDistribution dist_a;
    Utility::MaxwellFissionDistribution dist_b( 3.0 );
    Utility::MaxwellFissionDistribution dist_c( 3.0, 2.0 );
    Utility::MaxwellFissionDistribution dist_d( 3.0, 2.0, 1.0 );
    Utility::MaxwellFissionDistribution dist_e( 3.0, 2.0, 1.0, 10.0 );

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

  Utility::MaxwellFissionDistribution dist_a;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_a )
                           );
  FRENSIE_CHECK_EQUAL( dist_a, Utility::MaxwellFissionDistribution() );

  Utility::MaxwellFissionDistribution dist_b;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_b )
                           );
  FRENSIE_CHECK_EQUAL( dist_b, Utility::MaxwellFissionDistribution( 3.0 ) );

  Utility::MaxwellFissionDistribution dist_c;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_c )
                           );
  FRENSIE_CHECK_EQUAL( dist_c, Utility::MaxwellFissionDistribution( 3.0, 2.0 ) );

  Utility::MaxwellFissionDistribution dist_d;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_d )
                           );
  FRENSIE_CHECK_EQUAL( dist_d, Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0 ) );

  Utility::MaxwellFissionDistribution dist_e;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_e )
                           );
  FRENSIE_CHECK_EQUAL( dist_e, Utility::MaxwellFissionDistribution( 3.0, 2.0, 1.0, 10.0 ) );

  std::shared_ptr<Utility::OneDDistribution> shared_dist;

  FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "distribution", shared_dist ) );
  FRENSIE_CHECK_EQUAL( *dynamic_cast<Utility::MaxwellFissionDistribution*>( shared_dist.get() ),
                       *dynamic_cast<Utility::MaxwellFissionDistribution*>( distribution.get() ) );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be archived
FRENSIE_UNIT_TEST( UnitAwareMaxwellFissionDistribution, archive )
{
  std::string archive_name( "test_unit_aware_maxwell_fission_dist.h5a" );

  // Create and archive some maxwell fission distributions
  {
    Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount> dist_a;
    Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount> dist_b( 3.0*MeV );
    Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount> dist_c( 3.0*MeV, 2.0*MeV );
    Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount> dist_d( 3.0*MeV, 2.0*MeV, 1.0*MeV );
    Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount> dist_e( 3.0*MeV, 2.0*MeV, 1.0*MeV, 10.0 );

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

  Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount> dist_a;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_a )
                           );
  FRENSIE_CHECK_EQUAL( dist_a, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>()) );

  Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount> dist_b;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_b )
                           );
  FRENSIE_CHECK_EQUAL( dist_b, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV )) );

  Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount> dist_c;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_c )
                           );
  FRENSIE_CHECK_EQUAL( dist_c, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV )) );

  Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount> dist_d;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_d )
                           );
  FRENSIE_CHECK_EQUAL( dist_d, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV )) );

  Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount> dist_e;

  FRENSIE_REQUIRE_NO_THROW(
                           archive >> BOOST_SERIALIZATION_NVP( dist_e )
                           );
  FRENSIE_CHECK_EQUAL( dist_e, (Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>( 3.0*MeV, 2.0*MeV, 1.0*MeV, 10.0 )) );

  std::shared_ptr<Utility::UnitAwareOneDDistribution<MegaElectronVolt,si::amount> > shared_dist;

  FRENSIE_REQUIRE_NO_THROW( archive >> boost::serialization::make_nvp( "distribution", shared_dist ) );
  FRENSIE_CHECK_EQUAL( (*dynamic_cast<Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>*>( shared_dist.get() )),
                       (*dynamic_cast<Utility::UnitAwareMaxwellFissionDistribution<MegaElectronVolt,si::amount>*>( unit_aware_distribution.get() )) );
                       
}

//---------------------------------------------------------------------------//
// Check that distributions can be scaled
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( UnitAwareMaxwellFissionDistribution,
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

  // Copy from unitless distribution to distribution type A
  Utility::UnitAwareMaxwellFissionDistribution<IndepUnitA,DepUnitA>
    unit_aware_dist_a_copy = Utility::UnitAwareMaxwellFissionDistribution<IndepUnitA,DepUnitA>::fromUnitlessDistribution( *dynamic_cast<Utility::MaxwellFissionDistribution*>( distribution.get() ) );

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

  Utility::setQuantity( indep_quantity_a, 0.899999999999999 );
  Utility::setQuantity( inv_indep_quantity_a,
			sqrt(0.9)*exp(-0.9)/
                        (sqrt(Utility::PhysicalConstants::pi)*0.5*
                         erf(sqrt(0.9)) - sqrt(0.9)*exp(-0.9) ) );
  Utility::setQuantity( dep_quantity_a, sqrt(0.9)*exp(-0.9) );

  indep_quantity_b = IndepQuantityB( indep_quantity_a );
  inv_indep_quantity_b = InverseIndepQuantityB( inv_indep_quantity_a );
  dep_quantity_b = DepQuantityB( dep_quantity_a );

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
// end tstMaxwellFissionDistribution.cpp
//---------------------------------------------------------------------------//

