//---------------------------------------------------------------------------//
//!
//! \file   tstElasticElectronMomentsEvaluator.cpp
//! \author Luke Kersting
//! \brief  Elastic electron cross section moments evaluator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "DataGen_ElasticElectronMomentsEvaluator.hpp"
#include "Data_EvaluatedElectronDataContainer.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_HardElasticElectroatomicReaction.hpp"
#include "MonteCarlo_HardElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_HardElasticElectronScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_ElectroatomicReactionACEFactory.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Data::EvaluatedElectronDataContainer> native_eedl_data;
Teuchos::RCP<DataGen::ElasticElectronMomentsEvaluator>
  evaluator;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
bool notEqualZero( double value )
{
  return value != 0.0;
}
/*
//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the legendre expanded screened rutherford pdf can be evaluated
TEUCHOS_UNIT_TEST( ElasticElectronMomentsEvaluator,
                   evaluateLegendreExpandedRutherford )
{
  double n = 4;
  
  double expanded_pdf = 
    evaluator->evaluateLegendreExpandedRutherford( 1.0e-6,
                                                   1.000000000000E-05,
                                                   n );

  UTILITY_TEST_FLOATING_EQUALITY( 
                    expanded_pdf,
                    5.00E-01*9.999900000224990E-01,
                    1e-12 );

  expanded_pdf = 
    evaluator->evaluateLegendreExpandedRutherford( 0.0,
                                                   1.000000000000E-03,
                                                   n );

  UTILITY_TEST_FLOATING_EQUALITY(  
                    expanded_pdf,
                    9.078446769559230E+01*1.0,
                    1e-12 );

  expanded_pdf = 
    evaluator->evaluateLegendreExpandedRutherford( 1.0e-6,
                                                   1.000000000000E+05,
                                                   n );

  UTILITY_TEST_FLOATING_EQUALITY( 
                    expanded_pdf,
                    9.863740E+05*9.999900000224990E-01,
                    1e-12 );		


n = 2;
  
  expanded_pdf = 
    evaluator->evaluateLegendreExpandedRutherford( 0.0,
                                                   1.000000000000E-05,
                                                   n );

  UTILITY_TEST_FLOATING_EQUALITY( 
                    expanded_pdf,
                    5.000000003979020E-01*1.0,
                    1e-12 );
}
*/
//---------------------------------------------------------------------------//
// Check that the legendre expanded differential cross section can be evaluated
TEUCHOS_UNIT_TEST( ElasticElectronMomentsEvaluator,
                   evaluateLegendreExpandedPDF )
{
  double n = 4;
  
  double expanded_pdf = 
    evaluator->evaluateLegendreExpandedPDF( 1.0e-6,
                                            1.000000000000E-05,
                                            n );

  UTILITY_TEST_FLOATING_EQUALITY( 
                    expanded_pdf,
                    5.00E-01*0.9999900000224990,
                    1e-12 );

  expanded_pdf = 
    evaluator->evaluateLegendreExpandedPDF( 2.0,
                                            1.000000000000E-03,
                                            n );

  UTILITY_TEST_FLOATING_EQUALITY(  
                    expanded_pdf,
                    5.968430E-01*1.0,
                    1e-12 );

  expanded_pdf = 
    evaluator->evaluateLegendreExpandedPDF( 2.1e-6,
                                            1.000000000000E+05,
                                            n );

  UTILITY_TEST_FLOATING_EQUALITY( 
                    expanded_pdf,
                    2.237270E+05*9.999790000992250E-01,
                    1e-12 );		


n = 2;
  
  expanded_pdf = 
    evaluator->evaluateLegendreExpandedPDF( 2.0,
                                            1.000000000000E-05,
                                               n );

  UTILITY_TEST_FLOATING_EQUALITY( 
                    expanded_pdf,
                    5.000E-01*1.0,
                    1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the hydrogen expanded differential cross section can be evaluated
TEUCHOS_UNIT_TEST( ElasticElectronMomentsEvaluator,
                   evaluateLegendreExpandedPDFAtEnergyBin )
{
  double n = 4;
  
  double expanded_pdf = 
    evaluator->evaluateLegendreExpandedPDFAtEnergyBin( 1.0e-6,
                                                       0,
                                                       n );

  UTILITY_TEST_FLOATING_EQUALITY( 
                    expanded_pdf,
                    5.00E-01*0.9999900000224990,
                    1e-12 );

  expanded_pdf = 
    evaluator->evaluateLegendreExpandedPDFAtEnergyBin( 2.0,
                                                       1,
                                                       n );

  UTILITY_TEST_FLOATING_EQUALITY(  
                    expanded_pdf,
                    5.968430E-01*1.0,
                    1e-12 );

  expanded_pdf = 
    evaluator->evaluateLegendreExpandedPDFAtEnergyBin( 2.1e-6,
                                                       13,
                                                       n );

  UTILITY_TEST_FLOATING_EQUALITY( 
                    expanded_pdf,
                    2.237270E+05*9.999790000992250E-01,
                    1e-12 );		


n = 2;
  
  expanded_pdf = 
    evaluator->evaluateLegendreExpandedPDFAtEnergyBin( 2.0,
                                                       0,
                                                       n );

  UTILITY_TEST_FLOATING_EQUALITY( 
                    expanded_pdf,
                    5.000E-01*1.0,
                    1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the moments can be evaluated
TEUCHOS_UNIT_TEST( ElasticElectronMomentsEvaluator,
                   evaluateElasticMoment )
{
  double precision = 1e-13;
  double n = 0;
  double energy = 1.0e-5;
  double tol = 1e-12;

  Teuchos::RCP<DataGen::ElasticElectronMomentsEvaluator> full_evaluator; 

  full_evaluator.reset( new DataGen::ElasticElectronMomentsEvaluator(
                                    *native_eedl_data,
                                    2.0 ) );

  Teuchos::Array<Utility::long_float> total_moments(n+1);

  full_evaluator->evaluateElasticMoment( total_moments, energy, n, precision );
  
  UTILITY_TEST_FLOATING_EQUALITY( total_moments[0].convert_to<double>(),
                                  2.48924E+09 + 0.0,
                                  tol );	

  energy = 0.001;
  full_evaluator->evaluateElasticMoment( total_moments, energy, n, precision );
  
  UTILITY_TEST_FLOATING_EQUALITY( total_moments[0].convert_to<double>(),
                                  2.90281E+08 + 0.0,
                                  tol );

  energy = 5.5e1;
  full_evaluator->evaluateElasticMoment( total_moments, energy, n, precision );
  
  UTILITY_TEST_FLOATING_EQUALITY( total_moments[0].convert_to<double>(),
                                  2.51777E+05 + 1.8907655682E+06,
                                  5e-10 );			 

  unsigned energy_bin = 0;

  full_evaluator->evaluateElasticMoment( total_moments, energy_bin, n, precision );
  
  UTILITY_TEST_FLOATING_EQUALITY( total_moments[0].convert_to<double>(),
                                  9.999995000E-01*2.48924E+09 + 0.0,
                                  tol );	

  energy_bin = 1;
  full_evaluator->evaluateElasticMoment( total_moments, energy_bin, n, precision );
  
  UTILITY_TEST_FLOATING_EQUALITY( total_moments[0].convert_to<double>(),
                                  9.9999985651050E-01*2.90281E+08 + 0.0,
                                  tol );

  energy_bin = 12;
  full_evaluator->evaluateElasticMoment( total_moments, energy_bin, n, precision );
  
  UTILITY_TEST_FLOATING_EQUALITY( total_moments[0].convert_to<double>(),
                                  5.7093654836950E-01+3.62337948943E+00,
                                  tol );			 


 
  energy_bin = 1;
  evaluator->evaluateElasticMoment( total_moments, energy_bin, n, precision );
  
  UTILITY_TEST_FLOATING_EQUALITY( total_moments[0].convert_to<double>(),
                                  7.559416647842E-01+9.07762058421518E-05,
                                  tol );

  energy_bin = 12;
  evaluator->evaluateElasticMoment( total_moments, energy_bin, n, precision );
  
  UTILITY_TEST_FLOATING_EQUALITY( total_moments[0].convert_to<double>(),
                                  5.70927204446350E-01+3.62337948943E+00,
                                  tol );

  evaluator->evaluateElasticMoment( total_moments, energy_bin, 6, precision ); 
/*
  precision = 1e-13;
  n = 8;
  energy = 1e-5;
  total_moments.resize(n+1);
  evaluator->evaluateElasticMoment( total_moments, energy, n, precision );

  UTILITY_TEST_FLOATING_EQUALITY( total_moments[0].convert_to<double>(), 
                                  5.000000000000020E-02,
                                  tol );	
  UTILITY_TEST_FLOATING_EQUALITY( total_moments[1].convert_to<double>(), 
                                  4.750000000000010E-02,
                                  tol );		
  UTILITY_TEST_FLOATING_EQUALITY( total_moments[2].convert_to<double>(), 
                                  4.275000000000010E-02, 
                                  tol );
  UTILITY_TEST_FLOATING_EQUALITY( total_moments[3].convert_to<double>(), 
                                  3.621875000000010E-02,  
                                  tol );
  UTILITY_TEST_FLOATING_EQUALITY( total_moments[4].convert_to<double>(), 
                                  2.853562500000020E-02,
                                  tol ); 
  UTILITY_TEST_FLOATING_EQUALITY( total_moments[5].convert_to<double>(), 
                                  2.041371875000010E-02,  
                                  tol ); 
  UTILITY_TEST_FLOATING_EQUALITY( total_moments[6].convert_to<double>(), 
                                  1.256475937499990E-02,
                                  tol ); 
  UTILITY_TEST_FLOATING_EQUALITY( total_moments[7].convert_to<double>(), 
                                  5.617386367188300E-03,
                                  tol ); 
  UTILITY_TEST_FLOATING_EQUALITY( total_moments[8].convert_to<double>(), 
                                  4.957330078227900E-05,
                                  5e-11 ); */
}

//---------------------------------------------------------------------------//
// Check that the screened rutherford moments can be evaluated
TEUCHOS_UNIT_TEST( ElasticElectronMomentsEvaluator,
                   evaluateScreenedRutherfordMoment )
{
  unsigned n = 6;
  double energy = 1.0e5;
  double tol = 1e-13;
  Teuchos::Array<Utility::long_float> moments(n+1);
  Utility::long_float rutherford_moment;

  moments[0] = 1.0L*2.11160991169490E+06L;
  moments[1] = 9.999999999993360E-01L*2.11160991169490E+06L;
  moments[2] = 9.999999999980090E-01L*2.11160991169490E+06L;
  moments[3] = 9.999999999960180E-01L*2.11160991169490E+06L;
  moments[4] = 9.999999999933630E-01L*2.11160991169490E+06L;
  moments[5] = 9.999999999900440E-01L*2.11160991169490E+06L;
  moments[6] = 9.999999999860620E-01L*2.11160991169490E+06L;

  evaluator->
    evaluateScreenedRutherfordMoment( rutherford_moment,
                                      energy, 
                                      0 );
  
  UTILITY_TEST_FLOATING_EQUALITY( rutherford_moment.convert_to<double>(), 
                                  moments[0].convert_to<double>(),
                                  tol );	

  evaluator->
    evaluateScreenedRutherfordMoment( rutherford_moment,
                                      energy, 
                                      1 );

  UTILITY_TEST_FLOATING_EQUALITY( rutherford_moment.convert_to<double>(), 
                                  moments[1].convert_to<double>(),
                                  tol );	

  evaluator->
    evaluateScreenedRutherfordMoment( rutherford_moment,
                                      energy, 
                                      2 );
	
  UTILITY_TEST_FLOATING_EQUALITY( rutherford_moment.convert_to<double>(), 
                                  moments[2].convert_to<double>(), 
                                  tol );

  evaluator->
    evaluateScreenedRutherfordMoment( rutherford_moment,
                                      energy, 
                                      3 );

  UTILITY_TEST_FLOATING_EQUALITY( rutherford_moment.convert_to<double>(), 
                                  moments[3].convert_to<double>(),  
                                  tol );

  evaluator->
    evaluateScreenedRutherfordMoment( rutherford_moment,
                                      energy, 
                                      4 );

  UTILITY_TEST_FLOATING_EQUALITY( rutherford_moment.convert_to<double>(), 
                                  moments[4].convert_to<double>(),
                                  tol ); 

  evaluator->
    evaluateScreenedRutherfordMoment( rutherford_moment,
                                      energy, 
                                      5 );

  UTILITY_TEST_FLOATING_EQUALITY( rutherford_moment.convert_to<double>(), 
                                  moments[5].convert_to<double>(),  
                                  tol ); 

  evaluator->
    evaluateScreenedRutherfordMoment( rutherford_moment,
                                      energy, 
                                      n );

  UTILITY_TEST_FLOATING_EQUALITY( rutherford_moment.convert_to<double>(), 
                                  moments[6].convert_to<double>(),
                                  tol ); 

  tol = 1e-12;
  n = 0;
  moments.resize(n+1);
  moments[0] = 0.0; 

  energy = 1.0e-5;
  evaluator->
    evaluateScreenedRutherfordMoment( rutherford_moment,
                                      energy, 
                                      0 );
  
  UTILITY_TEST_FLOATING_EQUALITY( rutherford_moment.convert_to<double>(), 
                                  moments[0].convert_to<double>(),
                                  tol );	

  energy = 6.30957E+00;
  evaluator->
    evaluateScreenedRutherfordMoment( rutherford_moment,
                                      energy, 
                                      0 );
  
  UTILITY_TEST_FLOATING_EQUALITY( rutherford_moment.convert_to<double>(), 
                                  moments[0].convert_to<double>(),
                                  tol );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_native_file_name;
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_native_file",
		 &test_native_file_name,
		 "Test Native file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Create the native data file container
  native_eedl_data.reset( new Data::EvaluatedElectronDataContainer( 
						     test_native_file_name ) );


  // Create the momentum evaluator
  evaluator.reset( new DataGen::ElasticElectronMomentsEvaluator(
                                    *native_eedl_data,
                                    0.1 ) );

  // Run the unit tests
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);  
}

//---------------------------------------------------------------------------//
// end tstElasticElectronMomentsEvaluator.cpp
//---------------------------------------------------------------------------//
