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
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_HardElasticElectroatomicReaction.hpp"
#include "MonteCarlo_HardElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_HardElasticElectronScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_ElectroatomicReactionACEFactory.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor;
Teuchos::RCP<DataGen::ElasticElectronMomentsEvaluator>
  distribution;
Teuchos::RCP<const MonteCarlo::HardElasticElectronScatteringDistribution>
    elastic_scattering_distribution;

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
// Check that the hydrogen expanded differential cross section can be evaluated
TEUCHOS_UNIT_TEST( ElasticElectronMomentsEvaluator,
                   evaluateLegendreExpandedPDF )
{
  double n = 4;
  
  double diff_cross_section = 
    distribution->evaluateLegendreExpandedPDF( 9.999990000000E-01,
                                               1.000000000000E-05,
                                               n );

  UTILITY_TEST_FLOATING_EQUALITY( 
                    diff_cross_section,
                    4.999999999445E-01*0.9999900000224990,
                    1e-12 );

  diff_cross_section = 
    distribution->evaluateLegendreExpandedPDF( -1.000000000000,
                                               1.000000000000E-03,
                                               n );

  UTILITY_TEST_FLOATING_EQUALITY(  
                    diff_cross_section,
                    5.181320360405E-01*1.0,
                    1e-12 );

  diff_cross_section = 
    distribution->evaluateLegendreExpandedPDF( 9.999980000000E-01,
                                               1.000000000000E+05,
                                               n );

  UTILITY_TEST_FLOATING_EQUALITY( 
                    diff_cross_section,
                    2.572485667358630E+05*0.9999800000900000,
                    1e-12 );		


n = 2;
  
  diff_cross_section = 
    distribution->evaluateLegendreExpandedPDF( -1.0,
                                               1.000000000000E-05,
                                               n );

  UTILITY_TEST_FLOATING_EQUALITY( 
                    diff_cross_section,
                    5.000000000000E-01*1.0000000000000000,
                    1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the hydrogen expanded differential cross section can be evaluated
TEUCHOS_UNIT_TEST( ElasticElectronMomentsEvaluator,
                   evaluateLegendreExpandedPDFAtEnergyBin )
{
  double n = 4;
  
  double diff_cross_section = 
    distribution->evaluateLegendreExpandedPDFAtEnergyBin( 9.999990000000E-01,
                                                          0,
                                                          n );

  UTILITY_TEST_FLOATING_EQUALITY( 
                    diff_cross_section,
                    4.999999999445E-01*0.9999900000224990,
                    1e-12 );

  diff_cross_section = 
    distribution->evaluateLegendreExpandedPDFAtEnergyBin( -1.000000000000,
                                                          1,
                                                          n );

  UTILITY_TEST_FLOATING_EQUALITY(  
                    diff_cross_section,
                    5.181320360405E-01*1.0,
                    1e-12 );

  diff_cross_section = 
    distribution->evaluateLegendreExpandedPDFAtEnergyBin( 9.999980000000E-01,
                                                          13,
                                                          n );

  UTILITY_TEST_FLOATING_EQUALITY( 
                    diff_cross_section,
                    2.572485667358630E+05*0.9999800000900000,
                    1e-12 );		


n = 2;
  
  diff_cross_section = 
    distribution->evaluateLegendreExpandedPDFAtEnergyBin( -1.0,
                                                          0,
                                                          n );

  UTILITY_TEST_FLOATING_EQUALITY( 
                    diff_cross_section,
                    5.000000000000E-01*1.0000000000000000,
                    1e-12 );
}
*//*
//---------------------------------------------------------------------------//
// Check that the moments can be evaluated
TEUCHOS_UNIT_TEST( ElasticElectronMomentsEvaluator,
                   evaluateElasticMoment )
{
  double precision = 1e-13;
  double n = 0;
  double energy = 1.0e-5;
  double tol = 1e-12;

  Teuchos::RCP<DataGen::ElasticElectronMomentsEvaluator> full_distribution; 

  full_distribution.reset( new DataGen::ElasticElectronMomentsEvaluator(
                                    *xss_data_extractor,
                                    elastic_scattering_distribution,
                                    -1.0 ) );

  Teuchos::Array<Utility::long_float> total_moments(n+1);
/*
  full_distribution->evaluateElasticMoment( total_moments, energy, n, precision );
  
  UTILITY_TEST_FLOATING_EQUALITY( total_moments[0].convert_to<double>(),
                                  9.999995E-01+5.0000000014344E-07,
                                  tol );	

  energy = 0.001;
  full_distribution->evaluateElasticMoment( total_moments, energy, n, precision );
  
  UTILITY_TEST_FLOATING_EQUALITY( total_moments[0].convert_to<double>(),
                                  9.99909223828E-01+9.07762058421518E-05,
                                  tol );
*//*
  energy = 5.5e1;
  full_distribution->evaluateElasticMoment( total_moments, energy, n, precision );
  
  UTILITY_TEST_FLOATING_EQUALITY( total_moments[0].convert_to<double>(),
                                  5.7093654836950E-01+3.62337948943E+00,
                                  5e-10 );			 


 
  energy = 0.001;
  distribution->evaluateElasticMoment( total_moments, energy, n, precision );
  
  UTILITY_TEST_FLOATING_EQUALITY( total_moments[0].convert_to<double>(),
                                  7.559416647842E-01+9.07762058421518E-05,
                                  tol );

  energy = 5.5e1;
  distribution->evaluateElasticMoment( total_moments, energy, n, precision );
  
  UTILITY_TEST_FLOATING_EQUALITY( total_moments[0].convert_to<double>(),
                                  5.70927204446350E-01+3.62337948943E+00,
                                  5e-11 );		

  unsigned energy_bin = 0;

  full_distribution->evaluateElasticMoment( total_moments, energy_bin, n, precision );
  
  UTILITY_TEST_FLOATING_EQUALITY( total_moments[0].convert_to<double>(),
                                  9.999995E-01+5.0000000014344E-07,
                                  tol );	

  energy_bin = 1;
  full_distribution->evaluateElasticMoment( total_moments, energy_bin, n, precision );
  
  UTILITY_TEST_FLOATING_EQUALITY( total_moments[0].convert_to<double>(),
                                  9.99909223828E-01+9.07762058421518E-05,
                                  tol );

  energy_bin = 12;
  full_distribution->evaluateElasticMoment( total_moments, energy_bin, n, precision );
  
  UTILITY_TEST_FLOATING_EQUALITY( total_moments[0].convert_to<double>(),
                                  5.7093654836950E-01+3.62337948943E+00,
                                  tol );			 


 
  energy_bin = 1;
  distribution->evaluateElasticMoment( total_moments, energy_bin, n, precision );
  
  UTILITY_TEST_FLOATING_EQUALITY( total_moments[0].convert_to<double>(),
                                  7.559416647842E-01+9.07762058421518E-05,
                                  tol );

  energy_bin = 12;
  distribution->evaluateElasticMoment( total_moments, energy_bin, n, precision );
  
  UTILITY_TEST_FLOATING_EQUALITY( total_moments[0].convert_to<double>(),
                                  5.70927204446350E-01+3.62337948943E+00,
                                  tol );

  distribution->evaluateElasticMoment( total_moments, energy_bin, 6, precision ); 

  precision = 1e-13;
  n = 8;
  energy = 1e-5;
  total_moments.resize(n+1);
  distribution->evaluateElasticMoment( total_moments, energy, n, precision );

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
                                  5e-11 ); 
}
/*
//---------------------------------------------------------------------------//
// Check that the screened rutherford moments can be evaluated
TEUCHOS_UNIT_TEST( ElasticElectronMomentsEvaluator,
                   evaluateNormalizedScreenedRutherfordMoment )
{
  unsigned n = 6;
  double energy = 1.0e5;
  double tol = 1e-13;
  Teuchos::Array<Utility::long_float> rutherford_moments(n+1), moments(n+1);

  moments[0] = elastic_scattering_distribution->
                    evaluateScreenedRutherfordCrossSectionRatio( energy );
  moments[1] = 1.081706689774130E+07L; 
  moments[2] = 1.081706689772690E+07L; 
  moments[3] = 1.081706689770540E+07L;  
  moments[4] = 1.081706689768060E+07L;  
  moments[5] = 1.081706689766460E+07L;  
  moments[6] = 1.081706689761800E+07L; 

  distribution->
    evaluateNormalizedScreenedRutherfordMoment( rutherford_moments,
                                                   energy, 
                                                   n);
  
  UTILITY_TEST_FLOATING_EQUALITY( rutherford_moments[0].convert_to<double>(), 
                                  moments[0].convert_to<double>(),
                                  tol );	
  UTILITY_TEST_FLOATING_EQUALITY( rutherford_moments[1].convert_to<double>(), 
                                  moments[1].convert_to<double>(),
                                  tol );		
  UTILITY_TEST_FLOATING_EQUALITY( rutherford_moments[2].convert_to<double>(), 
                                  moments[2].convert_to<double>(), 
                                  tol );
  UTILITY_TEST_FLOATING_EQUALITY( rutherford_moments[3].convert_to<double>(), 
                                  moments[3].convert_to<double>(),  
                                  tol );
  UTILITY_TEST_FLOATING_EQUALITY( rutherford_moments[4].convert_to<double>(), 
                                  moments[4].convert_to<double>(),
                                  tol ); 
  UTILITY_TEST_FLOATING_EQUALITY( rutherford_moments[5].convert_to<double>(), 
                                  moments[5].convert_to<double>(),  
                                  tol ); 
  UTILITY_TEST_FLOATING_EQUALITY( rutherford_moments[6].convert_to<double>(), 
                                  moments[6].convert_to<double>(),
                                  tol ); 

  tol = 1e-12;
  energy = 1.0e-5;
  n = 8;
  rutherford_moments.clear();
  moments.resize(n+1);

  moments[0] = elastic_scattering_distribution->
                    evaluateScreenedRutherfordCrossSectionRatio( energy );
  moments[1] = 4.99831051546706E-07L; 
  moments[2] = -7.72416605970237E-07L;  
  moments[3] = -7.99720468531762E-03L;  
  moments[4] = -4.69068896975228E+01L;  
  moments[5] = -2.65347726376627E+05L; 
  moments[6] = -1.46768998685250E+09L;  
  moments[7] = -7.99507814226753E+12L;
  moments[8] = -4.30737032107294E+16L;

  distribution->
    evaluateNormalizedScreenedRutherfordMoment( rutherford_moments,
                                                 energy, 
                                                 n);
  
  UTILITY_TEST_FLOATING_EQUALITY( rutherford_moments[0].convert_to<double>(), 
                                  moments[0].convert_to<double>(),
                                  tol );	
  UTILITY_TEST_FLOATING_EQUALITY( rutherford_moments[1].convert_to<double>(), 
                                  moments[1].convert_to<double>(),
                                  tol );		
  UTILITY_TEST_FLOATING_EQUALITY( rutherford_moments[2].convert_to<double>(), 
                                  moments[2].convert_to<double>(), 
                                  tol );
  UTILITY_TEST_FLOATING_EQUALITY( rutherford_moments[3].convert_to<double>(), 
                                  moments[3].convert_to<double>(),  
                                  tol );
  UTILITY_TEST_FLOATING_EQUALITY( rutherford_moments[4].convert_to<double>(), 
                                  moments[4].convert_to<double>(),
                                  tol ); 
  UTILITY_TEST_FLOATING_EQUALITY( rutherford_moments[5].convert_to<double>(), 
                                  moments[5].convert_to<double>(),  
                                  tol ); 
  UTILITY_TEST_FLOATING_EQUALITY( rutherford_moments[6].convert_to<double>(), 
                                  moments[6].convert_to<double>(),
                                  tol ); 
  UTILITY_TEST_FLOATING_EQUALITY( rutherford_moments[7].convert_to<double>(), 
                                  moments[7].convert_to<double>(),  
                                  tol ); 
  UTILITY_TEST_FLOATING_EQUALITY( rutherford_moments[8].convert_to<double>(), 
                                  moments[8].convert_to<double>(),
                                  tol ); 
}
*/
//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_ace_file_name, test_ace_table_name;
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_ace_file",
		         &test_ace_file_name,
		         "Test ACE file name" );
  clp.setOption( "test_ace_table",
		         &test_ace_table_name,
		         "Test ACE table name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Create a file handler and data extractor
  Teuchos::RCP<Data::ACEFileHandler> ace_file_handler( 
				 new Data::ACEFileHandler( test_ace_file_name,
							               test_ace_table_name,
							               1u ) );

  xss_data_extractor.reset( new Data::XSSEPRDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
		              ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );
  
  // Extract the energy grid and cross section
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( xss_data_extractor->extractElectronEnergyGrid() );
  
  Teuchos::ArrayView<const double> raw_elastic_cross_section = 
    xss_data_extractor->extractElasticCrossSection();
  
  Teuchos::ArrayView<const double>::iterator start = 
    std::find_if( raw_elastic_cross_section.begin(),
                  raw_elastic_cross_section.end(),
                  notEqualZero );

  Teuchos::ArrayRCP<double> elastic_cross_section;
  elastic_cross_section.assign( start, raw_elastic_cross_section.end() );

  unsigned elastic_threshold_index = 
    energy_grid.size() - elastic_cross_section.size();

  // Extract the elastic scattering information data block (ELASI)
  Teuchos::ArrayView<const double> elasi_block(
				      xss_data_extractor->extractELASIBlock() );
  
  // Extract the number of tabulated distributions
  int size = elasi_block.size()/3;

  // Extract the energy grid for elastic scattering angular distributions
  Teuchos::Array<double> elastic_energy_grid(elasi_block(0,size));

  // Extract the table lengths for elastic scattering angular distributions
  Teuchos::Array<double> table_length(elasi_block(size,size));

  // Extract the offsets for elastic scattering angular distributions
  Teuchos::Array<double> offset(elasi_block(2*size,size));

  // Extract the elastic scattering angular distributions block (elas)
  Teuchos::ArrayView<const double> elas_block = 
    xss_data_extractor->extractELASBlock();

  // Create the elastic scattering distributions
  Teuchos::Array<Utility::Pair<double,Teuchos::RCP<const Utility::TabularOneDDistribution> > >
    elastic_scattering_function( size );
  /*
  for( unsigned n = 0; n < size; ++n )
  {
    elastic_scattering_function[n].first = elastic_energy_grid[n];

    elastic_scattering_function[n].second.reset( 
	  new Utility::HistogramDistribution(
		 elas_block( offset[n], table_length[n] ),
		 elas_block( offset[n] + 1 + table_length[n], table_length[n]-1 ),
         true ) );
  }  

  // Get the atomic number 
  const int atomic_number = xss_data_extractor->extractAtomicNumber();

  elastic_scattering_distribution.reset( 
	      new MonteCarlo::HardElasticElectronScatteringDistribution( 
                                                atomic_number, 
                                                elastic_scattering_function ) );

/*
  Teuchos::RCP<MonteCarlo::ElectroatomicReaction> elastic_reaction;
 
  // Create the reaction
  elastic_reaction.reset(
	new MonteCarlo::HardElasticElectroatomicReaction<Utility::LinLin>(
                        energy_grid,
                        elastic_cross_section,
                        elastic_threshold_index,
                        elastic_scattering_distribution ) );
*//*

  distribution.reset( new DataGen::ElasticElectronMomentsEvaluator(
                                    *xss_data_extractor,
                                    elastic_scattering_distribution ) );
*/
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
