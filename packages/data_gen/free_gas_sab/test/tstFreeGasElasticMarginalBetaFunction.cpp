//---------------------------------------------------------------------------//
//!
//! \file   tstFreeGasElasticMarginalBetaFunction.cpp
//! \author Alex Robinson
//! \brief  Free gas elastic marginal beta function unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <vector>
#include <map>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "DataGen_FreeGasElasticMarginalBetaFunction.hpp"
#include "MonteCarlo_NuclearScatteringAngularDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<DataGen::FreeGasElasticMarginalBetaFunction> beta_function;
double A = 0.999167;

// Initialize the zero temperature cross section
Teuchos::RCP<Utility::OneDDistribution> cross_section(
      new Utility::UniformDistribution( 0.0, 20.0, 1.0 ) );

// Initialize the scattering probability distribution
Teuchos::RCP<Utility::TabularOneDDistribution> isotropic_distribution(
      new Utility::UniformDistribution( -1.0, 1.0, 0.5 ) );

// Initialize the scattering distribution
MonteCarlo::NuclearScatteringAngularDistribution::AngularDistribution
  distribution( 2 );

Teuchos::RCP<MonteCarlo::NuclearScatteringAngularDistribution> scattering_distribution;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the beta min bound can be returned

/*
TEUCHOS_UNIT_TEST( FreeGasElasticMarginalBetaFunction, getBetaMin )
{
  beta_function->setIndependentVariables( 1e-7 );

  TEST_FLOATING_EQUALITY( beta_function->getBetaMin(),
  			 -3.95241294810482,
     		  1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( FreeGasElasticMarginalBetaFunction, evaluatePDF )
{
  
  beta_function->setIndependentVariables( 1e-7 );
  double pdf_value = (*beta_function)( beta_function->getBetaMin() );
  
  TEST_EQUALITY_CONST( pdf_value, 0.0 );
  
  pdf_value = (*beta_function)( 0.0 );
  TEST_ASSERT( pdf_value > 0.0 );

  pdf_value = (*beta_function)( -1*(beta_function->getBetaMin()) );
  TEST_ASSERT( pdf_value > 0.0 );

  beta_function->setIndependentVariables( 1e-5 );

  pdf_value = (*beta_function)( beta_function->getBetaMin() );
  TEST_EQUALITY_CONST( pdf_value, 0.0 );
  
  pdf_value = (*beta_function)( 0.0 );
  TEST_ASSERT( pdf_value > 0.0 );

  pdf_value = (*beta_function)( -1*(beta_function->getBetaMin()) );
  TEST_ASSERT( pdf_value > 0.0 );
}
*/ 

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( FreeGasElasticMarginalBetaFunction, evaluatePDF )
{
  double beta = (1.35e-9-2.53010e-8)/2.53010e-8;

  double pdf_value = (*beta_function)( beta );
  
  std::cout << " " << std::endl;
  std::cout << pdf_value << std::endl;
}

/*

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( FreeGasElasticMarginalBetaFunction, outputPDF )
{
  std::vector<std::string> filenames{ "/home/ecmoll/software/frensie/test_data/forward_pdf/H_293K.p",
                                      "/home/ecmoll/software/frensie/test_data/forward_pdf/H_600K.p",
                                      "/home/ecmoll/software/frensie/test_data/forward_pdf/H_900K.p",
                                      "/home/ecmoll/software/frensie/test_data/forward_pdf/H_1200K.p",
                                      "/home/ecmoll/software/frensie/test_data/forward_pdf/H_2500K.p"};

  std::vector<double> kT_vector{ 2.5301e-8, 5.1704e-8, 7.556e-8, 1.03408e-7, 2.15433e-7};                              
  std::vector<double> energies{1e-8, 1e-7, 1e-6};
  // std::vector<double> energies{2.53010e-8};
  std::vector<double> energy_vector{1E-11,1.09715618670273E-11,1.20375169802007E-11,1.32070362273663E-11,1.4490181504862E-11,1.58979922845047E-11,1.74425805910966E-11,1.91372352075826E-11,2.09965360043844E-11,2.30364793765369E-11,2.52746158678173E-11,2.77302011659106E-11,3.042436176769E-11,3.33802767399029E-11,3.66233771390337E-11,4.01815648060381E-11,4.40854524183411E-11,4.83686268643717E-11,5.30679382065612E-11,5.82238167188865E-11,6.3880620726572E-11,7.00870182405691E-11,7.6896405670187E-11,8.43673672162484E-11,9.25641788971279E-11,1.01557361544042E-10,1.11424287523251E-10,1.22249846405078E-10,1.3412717530679E-10,1.47158460192806E-10,1.61455815026184E-10,1.77142246335108E-10,1.94352711492983E-10,2.13235279816976E-10,2.33952406474482E-10,2.56682330157469E-10,2.8162060654954E-10,3.08981790778801E-10,3.3900128333145E-10,3.71937355307265E-10,4.08073370441215E-10,4.47720223008213E-10,4.91219012585386E-10,5.3894397868406E-10,5.91305720499399E-10,6.4875472947863E-10,7.11785265100131E-10,7.8093960720845E-10,8.5681272148995E-10,9.40057378228296E-10,1.03138976837872E-09,1.13159566527861E-09,1.24153718500641E-09,1.36216020355127E-09,1.49450249460653E-09,1.63970265800021E-09,1.79900991557783E-09,1.97379485881577E-09,2.16556124063175E-09,2.37595891284276E-09,2.60679802057693E-09,2.86006457576039E-09,3.13793754366483E-09,3.44280758951861E-09,3.77729764646745E-09,4.14428548183942E-09,4.5469284558624E-09,4.98869068584412E-09,5.47337284952013E-09,6.00514488398175E-09,6.58858186150682E-09,7.22870335094955E-09,7.93101660333304E-09,8.70156393318891E-09,9.5469747032875E-09,1.04745223600063E-08,1.1492187010037E-08,1.26087240768068E-08,1.38337396272962E-08,1.51777730173227E-08,1.66523875663253E-08,1.82702700417654E-08,2.00453398090524E-08,2.19928685860603E-08,2.41296118325361E-08,2.64739529048023E-08,2.90460612159805E-08,3.18680657624591E-08,3.49642455095314E-08,3.83612382741753E-08,4.20882699020889E-08,4.61774057106911E-08,5.06638263613665E-08,5.55861305344059E-08,6.09866670106889E-08,6.69118990171562E-08,7.34128039707012E-08,8.05453120596494E-08,8.83707874361458E-08,9.69565561593592E-08,1.06376485431631E-07,1.16711619111007E-07,1.28050874967733E-07,1.40491809683546E-07,1.54141458175364E-07,1.69117254464481E-07,1.85548042013884E-07,2.0357518222611E-07,2.23353770638512E-07,2.45053971279426E-07,2.68862480665294E-07,2.9498413403417E-07,3.23643667634736E-07,3.55087652232611E-07,3.89586614468756E-07,4.27437364320966E-07,4.68965548692654E-07,5.14528453098585E-07,5.64518075551696E-07,6.19364499097061E-07,6.79539592008376E-07,7.45561067481437E-07,8.17996937751947E-07,8.97470400958433E-07,9.84665202794123E-07,1.08033151907647E-06,1.1852924098447E-06,1.3004509005129E-06,1.42679775100086E-06,1.56541997968413E-06,1.7175102154985E-06,1.88437695865931E-06,2.06745583827313E-06,2.26832196369604E-06,2.48870347590279E-06,2.73049641545532E-06,2.99578103498642E-06,3.28683969654205E-06,3.60617650776123E-06,3.95653886583226E-06,4.34094109457766E-06,4.76269037802798E-06,5.00E-06};
  Teuchos::Array<double> energy_array( energy_vector );

  for( int e = 0; e < filenames.size(); ++e )
  {
    double kT = kT_vector[e];

    std::map< double, Teuchos::Array<double> > data_map;

    for( int i = 0; i < energies.size(); ++i )
    {
      // Initialize the gkq_set factor
      beta_function.reset( new DataGen::FreeGasElasticMarginalBetaFunction(
                    cross_section, 
                    scattering_distribution,
                    A,
                    kT,
                    energies[i] ) ); 

      beta_function->populatePDF( energy_array );

      Teuchos::Array<double> pdf_array;
      beta_function->getPDF( pdf_array );

      data_map[ i ] = pdf_array;
    }

    std::ofstream output_file;
    output_file.open( filenames[e] );

    for( int i = 0; i < energy_vector.size(); ++i )
    {
      output_file << energy_vector[i] << " ";
      for( int j = 0; j < energies.size(); ++j )
      {
        output_file << data_map[ j ][i] << " ";
      }
      output_file << "\n";
    }

    output_file.close();
  }
}

//---------------------------------------------------------------------------//
// Check that the PDF can be evaluated
TEUCHOS_UNIT_TEST( FreeGasElasticMarginalBetaFunction, outputCDF )
{
  std::vector<std::string> filenames{ "/home/ecmoll/software/frensie/test_data/forward_cdf/H_293K.c",
                                      "/home/ecmoll/software/frensie/test_data/forward_cdf/H_600K.c",
                                      "/home/ecmoll/software/frensie/test_data/forward_cdf/H_900K.c",
                                      "/home/ecmoll/software/frensie/test_data/forward_cdf/H_1200K.c",
                                      "/home/ecmoll/software/frensie/test_data/forward_cdf/H_2500K.c"};

  std::vector<double> kT_vector{ 2.5301e-8, 5.1704e-8, 7.556e-8, 1.03408e-7, 2.15433e-7};                              
  std::vector<double> energies{1e-8, 1e-7, 1e-6};
  // std::vector<double> energies{2.53010e-8};
  std::vector<double> energy_vector{1E-11,1.09715618670273E-11,1.20375169802007E-11,1.32070362273663E-11,1.4490181504862E-11,1.58979922845047E-11,1.74425805910966E-11,1.91372352075826E-11,2.09965360043844E-11,2.30364793765369E-11,2.52746158678173E-11,2.77302011659106E-11,3.042436176769E-11,3.33802767399029E-11,3.66233771390337E-11,4.01815648060381E-11,4.40854524183411E-11,4.83686268643717E-11,5.30679382065612E-11,5.82238167188865E-11,6.3880620726572E-11,7.00870182405691E-11,7.6896405670187E-11,8.43673672162484E-11,9.25641788971279E-11,1.01557361544042E-10,1.11424287523251E-10,1.22249846405078E-10,1.3412717530679E-10,1.47158460192806E-10,1.61455815026184E-10,1.77142246335108E-10,1.94352711492983E-10,2.13235279816976E-10,2.33952406474482E-10,2.56682330157469E-10,2.8162060654954E-10,3.08981790778801E-10,3.3900128333145E-10,3.71937355307265E-10,4.08073370441215E-10,4.47720223008213E-10,4.91219012585386E-10,5.3894397868406E-10,5.91305720499399E-10,6.4875472947863E-10,7.11785265100131E-10,7.8093960720845E-10,8.5681272148995E-10,9.40057378228296E-10,1.03138976837872E-09,1.13159566527861E-09,1.24153718500641E-09,1.36216020355127E-09,1.49450249460653E-09,1.63970265800021E-09,1.79900991557783E-09,1.97379485881577E-09,2.16556124063175E-09,2.37595891284276E-09,2.60679802057693E-09,2.86006457576039E-09,3.13793754366483E-09,3.44280758951861E-09,3.77729764646745E-09,4.14428548183942E-09,4.5469284558624E-09,4.98869068584412E-09,5.47337284952013E-09,6.00514488398175E-09,6.58858186150682E-09,7.22870335094955E-09,7.93101660333304E-09,8.70156393318891E-09,9.5469747032875E-09,1.04745223600063E-08,1.1492187010037E-08,1.26087240768068E-08,1.38337396272962E-08,1.51777730173227E-08,1.66523875663253E-08,1.82702700417654E-08,2.00453398090524E-08,2.19928685860603E-08,2.41296118325361E-08,2.64739529048023E-08,2.90460612159805E-08,3.18680657624591E-08,3.49642455095314E-08,3.83612382741753E-08,4.20882699020889E-08,4.61774057106911E-08,5.06638263613665E-08,5.55861305344059E-08,6.09866670106889E-08,6.69118990171562E-08,7.34128039707012E-08,8.05453120596494E-08,8.83707874361458E-08,9.69565561593592E-08,1.06376485431631E-07,1.16711619111007E-07,1.28050874967733E-07,1.40491809683546E-07,1.54141458175364E-07,1.69117254464481E-07,1.85548042013884E-07,2.0357518222611E-07,2.23353770638512E-07,2.45053971279426E-07,2.68862480665294E-07,2.9498413403417E-07,3.23643667634736E-07,3.55087652232611E-07,3.89586614468756E-07,4.27437364320966E-07,4.68965548692654E-07,5.14528453098585E-07,5.64518075551696E-07,6.19364499097061E-07,6.79539592008376E-07,7.45561067481437E-07,8.17996937751947E-07,8.97470400958433E-07,9.84665202794123E-07,1.08033151907647E-06,1.1852924098447E-06,1.3004509005129E-06,1.42679775100086E-06,1.56541997968413E-06,1.7175102154985E-06,1.88437695865931E-06,2.06745583827313E-06,2.26832196369604E-06,2.48870347590279E-06,2.73049641545532E-06,2.99578103498642E-06,3.28683969654205E-06,3.60617650776123E-06,3.95653886583226E-06,4.34094109457766E-06,4.76269037802798E-06,5.00E-06};
  Teuchos::Array<double> energy_array( energy_vector );

  for( int e = 0; e < filenames.size(); ++e )
  {
    double kT = kT_vector[e];

    std::map< double, Teuchos::Array<double> > data_map;

    for( int i = 0; i < energies.size(); ++i )
    {
      // Initialize the gkq_set factor
      beta_function.reset( new DataGen::FreeGasElasticMarginalBetaFunction(
                    cross_section, 
                    scattering_distribution,
                    A,
                    kT,
                    energies[i] ) ); 

      beta_function->populateCDF( energy_array );

      Teuchos::Array<double> cdf_array;
      beta_function->getCDF( cdf_array );

      data_map[ i ] = cdf_array;
    }

    std::ofstream output_file;
    output_file.open( filenames[e] );

    for( int i = 0; i < energy_vector.size(); ++i )
    {
      output_file << energy_vector[i] << " ";
      for( int j = 0; j < energies.size(); ++j )
      {
        output_file << data_map[ j ][i] << " ";
      }
      output_file << "\n";
    }

    output_file.close();
  }
}

*/

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  distribution[0].first = 0.0;
  distribution[0].second = isotropic_distribution;

  distribution[1].first = 20.0;
  distribution[1].second = isotropic_distribution;

  scattering_distribution.reset( 
        new MonteCarlo::NuclearScatteringAngularDistribution(
                    distribution ) );

  // Initialize the gkq_set factor
  beta_function.reset( new DataGen::FreeGasElasticMarginalBetaFunction(
						    cross_section, 
						    scattering_distribution,
						    0.999167,
						    2.53010e-8,
						    2.53010e-8 ) );

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
// end tstFreeGasElasticMarginalBetaFunction.cpp
//---------------------------------------------------------------------------//
