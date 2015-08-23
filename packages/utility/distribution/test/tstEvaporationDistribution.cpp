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
#include "Utility_EvaporationDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_ElectronVoltUnit.hpp"

using boost::units::quantity;
using namespace Utility::Units;
namespace si = boost::units::si;

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
  double test_value_2 = pow( 1.0 - exp(-0.9) * (1.0 + 0.9), -1.0 ) * exp( -1.0 ); 
  
  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), test_value_1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), test_value_2 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareEvaporationDistribution, evaluate )
{
  double scale_factor = exp(-1.0)/(1.0 - exp(-0.9)*(1.0+0.9));

  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 0.0*MeV ), 
		       0.0*si::mole );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluate( 1.0*MeV ), 
		       scale_factor*si::mole );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( EvaporationDistribution, evaluatePDF )
{
  double test_value_1 = 0.0 ;
  double test_value_2 = pow( 1.0 - exp(-0.9) * (1.0 + 0.9), -1.0 ) * exp( -1.0 );

  TEST_EQUALITY_CONST( distribution->evaluate( 0.0 ), test_value_1 );
  TEST_EQUALITY_CONST( distribution->evaluate( 1.0 ), test_value_2 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware PDF can be evaluated
TEUCHOS_UNIT_TEST( UnitAwareEvaporationDistribution, evaluatePDF )
{
  double scale_factor = exp(-1.0)/(1.0 - exp(-0.9)*(1.0+0.9));

  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 0.0*MeV ), 
		       0.0/MeV );
  TEST_EQUALITY_CONST( unit_aware_distribution->evaluatePDF( 1.0*MeV ), 
		       scale_factor/MeV );
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
  unsigned trials = 0;
 
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
  unsigned trials = 0;
 
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
  test_value_2 = pow( 1.0 - exp(-0.9) * (1.0 + 0.9), -1.0 ) * exp( -1.0 );

  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0 ), test_value_1 );
  TEST_EQUALITY_CONST( read_distribution.evaluate( 1.0 ), test_value_2 );

  read_distribution = 
    test_dists_list->get<Utility::EvaporationDistribution>( "Evaporation Distribution B" );

  test_value_1 = 0.0 ;
  test_value_2 = pow( 2.0, 2.0) * ( 1.0 - exp(-1.0) * (1.0 + 1.0) );
  test_value_2 = pow( test_value_2, -1.0 ) * exp( -0.5 );

  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0 ), test_value_1 );
  TEST_EQUALITY_CONST( read_distribution.evaluate( 1.0 ), test_value_2 );

  read_distribution = 
    test_dists_list->get<Utility::EvaporationDistribution>( "Evaporation Distribution C" );

  test_value_1 = 0.0 ;
  test_value_2 = 1.0 - exp(-1.0) * (1.0 + 1.0) ;
  test_value_2 = pow( test_value_2, -1.0 ) * exp( -1.0 );

  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0 ), test_value_1 );
  TEST_EQUALITY_CONST( read_distribution.evaluate( 1.0 ), test_value_2 );
}

//---------------------------------------------------------------------------//
// Check that the unit-aware distribution can be read from an xml file
TEUCHOS_UNIT_TEST( UnitAwareEvaporationDistribution, fromParameterList )
{
  typedef Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount> UnitAwareEvaporationDistribution;
  
  UnitAwareEvaporationDistribution read_distribution = 
    test_dists_list->get<UnitAwareEvaporationDistribution>( "Unit-Aware Evaporation Distribution A" );

  double scale_factor = exp(-1.0)/(1.0 - exp(-0.9)*(1.0+0.9));
  
  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0*MeV ), 
		       0.0*si::mole );
  TEST_EQUALITY_CONST( read_distribution.evaluate( 1.0*MeV ), 
		       scale_factor*si::mole );

  read_distribution = 
    test_dists_list->get<UnitAwareEvaporationDistribution>( "Unit-Aware Evaporation Distribution B" );

  scale_factor = exp(-0.5)/(4.0*(1.0-exp(-1.0)*(1.0+1.0)));

  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0*MeV ), 
		       0.0*si::mole );
  TEST_EQUALITY_CONST( read_distribution.evaluate( 1.0*MeV ), 
		       scale_factor*si::mole );

  read_distribution = 
    test_dists_list->get<UnitAwareEvaporationDistribution>( "Unit-Aware Evaporation Distribution C" );

  scale_factor = exp(-1.0)/(1.0 - exp(-1.0)*(1.0+1.0));

  TEST_EQUALITY_CONST( read_distribution.evaluate( 0.0*MeV ), 
		       0.0*si::mole );
  TEST_EQUALITY_CONST( read_distribution.evaluate( 1.0*MeV ), 
		       scale_factor*si::mole );
}

//---------------------------------------------------------------------------//
// Check that a unit-aware distribution can be constructed from a unitless
// distribution
TEUCHOS_UNIT_TEST_TEMPLATE_2_DECL( UnitAwareEvaporationDistribution,
				   unitless_copy_constructor,
				   IndepUnit,
				   DepUnit )
{
  typedef typename Utility::UnitTraits<IndepUnit>::template GetQuantityType<double>::type
    IndepQuantity;
  typedef typename Utility::UnitTraits<DepUnit>::template GetQuantityType<double>::type
    DepQuantity;

  Utility::UnitAwareEvaporationDistribution<IndepUnit,DepUnit>
    unit_aware_dist_copy( *Teuchos::rcp_dynamic_cast<Utility::EvaporationDistribution>( distribution ) );
			 
  IndepQuantity indep_quantity = 
    Utility::QuantityTraits<IndepQuantity>::initializeQuantity( 0.0 );
  DepQuantity dep_quantity = 
    Utility::QuantityTraits<DepQuantity>::initializeQuantity( 0.0 );

  TEST_EQUALITY_CONST( unit_aware_dist_copy.evaluate( indep_quantity ),
		       dep_quantity );
  
  Utility::setQuantity( indep_quantity, 1.0 );
  Utility::setQuantity( dep_quantity, exp(-1.0)/(1.0 - exp(-0.9)*(1.0+0.9)) );
  
  TEST_EQUALITY_CONST( unit_aware_dist_copy.evaluate( indep_quantity ),
		       dep_quantity );
}

typedef si::energy si_energy;
typedef si::amount si_amount;
typedef si::length si_length;
typedef si::mass si_mass;
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareEvaporationDistribution,
				      unitless_copy_constructor,
				      si_energy,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareEvaporationDistribution,
				      unitless_copy_constructor,
				      si_energy,
				      si_length );
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareEvaporationDistribution,
				      unitless_copy_constructor,
				      si_energy,
				      si_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareEvaporationDistribution,
				      unitless_copy_constructor,
				      si_energy,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareEvaporationDistribution,
				      unitless_copy_constructor,
				      ElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareEvaporationDistribution,
				      unitless_copy_constructor,
				      ElectronVolt,
				      si_length );
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareEvaporationDistribution,
				      unitless_copy_constructor,
				      ElectronVolt,
				      si_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareEvaporationDistribution,
				      unitless_copy_constructor,
				      ElectronVolt,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareEvaporationDistribution,
				      unitless_copy_constructor,
				      KiloElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareEvaporationDistribution,
				      unitless_copy_constructor,
				      KiloElectronVolt,
				      si_length );
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareEvaporationDistribution,
				      unitless_copy_constructor,
				      KiloElectronVolt,
				      si_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareEvaporationDistribution,
				      unitless_copy_constructor,
				      KiloElectronVolt,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareEvaporationDistribution,
				      unitless_copy_constructor,
				      MegaElectronVolt,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareEvaporationDistribution,
				      unitless_copy_constructor,
				      MegaElectronVolt,
				      si_length );
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareEvaporationDistribution,
				      unitless_copy_constructor,
				      MegaElectronVolt,
				      si_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareEvaporationDistribution,
				      unitless_copy_constructor,
				      MegaElectronVolt,
				      void );
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareEvaporationDistribution,
				      unitless_copy_constructor,
				      void,
				      si_amount );
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareEvaporationDistribution,
				      unitless_copy_constructor,
				      void,
				      si_length );
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareEvaporationDistribution,
				      unitless_copy_constructor,
				      void,
				      si_mass );
TEUCHOS_UNIT_TEST_TEMPLATE_2_INSTANT( UnitAwareEvaporationDistribution,
				      unitless_copy_constructor,
				      void,
				      void );				      

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

  TEUCHOS_ADD_TYPE_CONVERTER( Utility::EvaporationDistribution );
  typedef Utility::UnitAwareEvaporationDistribution<MegaElectronVolt,si::amount> UnitAwareEvaporationDistribution;
  TEUCHOS_ADD_TYPE_CONVERTER( UnitAwareEvaporationDistribution );

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
// end tstEvaporationDistribution.cpp
//---------------------------------------------------------------------------//

