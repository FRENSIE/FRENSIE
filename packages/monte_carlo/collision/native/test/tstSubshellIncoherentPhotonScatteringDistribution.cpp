//---------------------------------------------------------------------------//
//!
//! \file   tstSubshellIncoherentPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brier  Subshell incoherent photon scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>
  
// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_SubshellIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_SubshellType.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_DirectionHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::PhotonScatteringDistribution>
  distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( SubshellIncoherentPhotonScatteringDistribution,
		   evaluate )
{
  double dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 1.0 );
  
  TEST_FLOATING_EQUALITY( dist_value, 0.0, 1e-15 );

  dist_value = distribution->evaluate( 
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 -1.0 );
  
  TEST_FLOATING_EQUALITY( dist_value, 0.18204031443868224, 1e-6 );

  dist_value = distribution->evaluate( 1.0, 1.0 );
  
  TEST_FLOATING_EQUALITY( dist_value, 0.0, 1e-15 );
  
  dist_value = distribution->evaluate( 1.0, 0.0 );

  TEST_FLOATING_EQUALITY( dist_value, 0.1309675807668618, 1e-15 );

  dist_value = distribution->evaluate( 1.0, -1.0 );

  TEST_FLOATING_EQUALITY( dist_value, 0.10574024270641422, 1e-15 );	
}

//---------------------------------------------------------------------------//
// Check that the distribution pdf can be evaluated
TEUCHOS_UNIT_TEST( SubshellIncoherentPhotonScatteringDistribution,
		   evaluatePDF )
{
  double pdf_value = distribution->evaluatePDF( 
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 1.0 );
  
  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-15 );

  pdf_value = distribution->evaluatePDF( 
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 -1.0 );
  
  TEST_FLOATING_EQUALITY( pdf_value, 0.468206881760033666, 1e-15 );

  pdf_value = distribution->evaluatePDF( 1.0, 1.0 );

  TEST_FLOATING_EQUALITY( pdf_value, 0.0, 1e-15 );

  pdf_value = distribution->evaluatePDF( 1.0, 0.0 );
  
  TEST_FLOATING_EQUALITY( pdf_value, 0.361055269849248517, 1e-15 );

  pdf_value = distribution->evaluatePDF( 1.0, -1.0 );
  
  TEST_FLOATING_EQUALITY( pdf_value, 0.291507803998082682, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the integrated cross section can be evaluated
TEUCHOS_UNIT_TEST( SubshellIncoherentPhotonScatteringDistribution,
		   evaluateIntegratedCrossSection )
{
  double cross_section = distribution->evaluateIntegratedCrossSection( 
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 1e-3 );
  std::cout.precision( 18 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.38880309491689713, 1e-15 );

  cross_section = distribution->evaluateIntegratedCrossSection( 1.0, 1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.362735546891601146, 1e-15 );

  cross_section = distribution->evaluateIntegratedCrossSection( 20.0, 1e-3 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.0603100615156834663, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the subshell can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentPhotonScatteringDistribution,
		   getSubshell )
{
  Teuchos::RCP<MonteCarlo::SubshellIncoherentPhotonScatteringDistribution>
    derived_dist = Teuchos::rcp_dynamic_cast<MonteCarlo::SubshellIncoherentPhotonScatteringDistribution>( distribution );

  TEST_EQUALITY_CONST( derived_dist->getSubshell(), MonteCarlo::K_SUBSHELL);
}

//---------------------------------------------------------------------------//
// Check that the binding energy can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentPhotonScatteringDistribution,
		   getSubshellBindingEnergy )
{
  Teuchos::RCP<MonteCarlo::SubshellIncoherentPhotonScatteringDistribution>
    derived_dist = Teuchos::rcp_dynamic_cast<MonteCarlo::SubshellIncoherentPhotonScatteringDistribution>( distribution );

  TEST_EQUALITY_CONST( derived_dist->getSubshellBindingEnergy(), 
		       8.82899999999999935e-02 );
}

//---------------------------------------------------------------------------//
// Check that a photon can be scattered incoherently without Doppler broadening
TEUCHOS_UNIT_TEST( SubshellIncoherentPhotonScatteringDistribution,
		   scatterPhoton )
{
  MonteCarlo::ParticleBank bank;
  
  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );
  
  MonteCarlo::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.001; // sample from first term of koblinger's method
  fake_stream[1] = 0.5; // x = 40.13902672495315, mu = 0.0
  fake_stream[2] = 1.0-1e-15; // accept x in occupation number rejection loop
  fake_stream[3] = 0.5; // azimuthal_angle = pi

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->scatterPhoton( photon,
			       bank,
			       shell_of_interaction);

  Utility::RandomNumberGenerator::unsetFakeStream();

  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  TEST_FLOATING_EQUALITY( bank.top().getEnergy(), 
			  19.50173181484825,
			  1e-15 );
  TEST_FLOATING_EQUALITY( bank.top().getZDirection(), 
			  0.9996898054103247, 
			  1e-15 );
  TEST_FLOATING_EQUALITY( bank.top().getYDirection(), 
			  -0.024905681252821114, 
			  1e-12 );
  UTILITY_TEST_FLOATING_EQUALITY( bank.top().getXDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getZDirection(), 0.0, 1e-15 );
  TEST_FLOATING_EQUALITY( photon.getYDirection(), 1.0, 1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( photon.getXDirection(), 0.0, 1e-15 );
  TEST_EQUALITY_CONST( shell_of_interaction, MonteCarlo::K_SUBSHELL );
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

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) 
  {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  {
    // Create the native data file container
    Data::ElectronPhotonRelaxationDataContainer 
      data_container( test_native_file_name );
    
    // Extract the occupation number for the first subshell
    const std::vector<double>& occupation_number_grid_s1 = 
      data_container.getOccupationNumberMomentumGrid( 1 );
    
    const std::vector<double>& occupation_number_s1 = 
      data_container.getOccupationNumber( 1 );
    
    // Create the occupation number distributions
    Teuchos::RCP<const Utility::OneDDistribution> occupation_number_s1_dist(
			    new Utility::TabularDistribution<Utility::LinLin>(
						    occupation_number_grid_s1,
						    occupation_number_s1 ) );

    // Create the subshell incoherent distributions
    distribution.reset(
		new MonteCarlo::SubshellIncoherentPhotonScatteringDistribution(
			  MonteCarlo::convertENDFDesignatorToSubshellEnum( 1 ),
			  data_container.getSubshellOccupancy( 1 ),
			  data_container.getSubshellBindingEnergy( 1 ),
			  occupation_number_s1_dist,
			  3.0 ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  
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
// end tstSubshellIncoherentPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
