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

// FRENSIE Includes
#include "MonteCarlo_SubshellIncoherentPhotonScatteringDistribution.hpp"
#include "Data_SubshellType.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::PhotonScatteringDistribution>
  distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( SubshellIncoherentPhotonScatteringDistribution,
		   evaluate )
{
  double dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 1.0 );

  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  dist_value = distribution->evaluate(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 -1.0 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.182031495370433727, 1e-6 );

  dist_value = distribution->evaluate( 1.0, 1.0 );

  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  dist_value = distribution->evaluate( 1.0, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.1309675807668618, 1e-15 );

  dist_value = distribution->evaluate( 1.0, -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.10574024270641422, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the distribution pdf can be evaluated
FRENSIE_UNIT_TEST( SubshellIncoherentPhotonScatteringDistribution,
		   evaluatePDF )
{
  double pdf_value = distribution->evaluatePDF(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 1.0 );

  FRENSIE_CHECK_SMALL( pdf_value, 1e-9 );

  pdf_value = distribution->evaluatePDF(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 -1.0 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.468210959354766421, 1e-9 );

  pdf_value = distribution->evaluatePDF( 1.0, 1.0 );

  FRENSIE_CHECK_SMALL( pdf_value, 1e-9 );

  pdf_value = distribution->evaluatePDF( 1.0, 0.0 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.361065574572935588, 1e-9 );

  pdf_value = distribution->evaluatePDF( 1.0, -1.0 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.291516123797359028, 1e-9 );
}

//---------------------------------------------------------------------------//
// Check that the integrated cross section can be evaluated
FRENSIE_UNIT_TEST( SubshellIncoherentPhotonScatteringDistribution,
		   evaluateIntegratedCrossSection )
{
  double cross_section = distribution->evaluateIntegratedCrossSection(
			 Utility::PhysicalConstants::electron_rest_mass_energy,
			 1e-3 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.388780936741182304, 1e-9 );

  cross_section = distribution->evaluateIntegratedCrossSection( 1.0, 1e-3 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.362725194507310333, 1e-9 );

  cross_section = distribution->evaluateIntegratedCrossSection( 20.0, 1e-3 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 0.0603100048795882984, 1e-9 );
}

//---------------------------------------------------------------------------//
// Check that the subshell can be returned
FRENSIE_UNIT_TEST( SubshellIncoherentPhotonScatteringDistribution,
		   getSubshell )
{
  std::shared_ptr<MonteCarlo::SubshellIncoherentPhotonScatteringDistribution>
    derived_dist = std::dynamic_pointer_cast<MonteCarlo::SubshellIncoherentPhotonScatteringDistribution>( distribution );

  FRENSIE_CHECK_EQUAL( derived_dist->getSubshell(), Data::K_SUBSHELL);
}

//---------------------------------------------------------------------------//
// Check that the binding energy can be returned
FRENSIE_UNIT_TEST( SubshellIncoherentPhotonScatteringDistribution,
		   getSubshellBindingEnergy )
{
  std::shared_ptr<MonteCarlo::SubshellIncoherentPhotonScatteringDistribution>
    derived_dist = std::dynamic_pointer_cast<MonteCarlo::SubshellIncoherentPhotonScatteringDistribution>( distribution );

  FRENSIE_CHECK_EQUAL( derived_dist->getSubshellBindingEnergy(),
		       8.82899999999999935e-02 );
}

//---------------------------------------------------------------------------//
// Check that a photon can be scattered incoherently without Doppler broadening
FRENSIE_UNIT_TEST( SubshellIncoherentPhotonScatteringDistribution,
		   scatterPhoton )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 20.0 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;

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

  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getEnergy(),
			  19.50173181484825,
			  1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getZDirection(),
			  0.9996898054103247,
			  1e-15 );
  FRENSIE_CHECK_SMALL( bank.top().getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getXDirection(),
                                   0.024905681252821114,
                                   1e-12 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 0.4982681851517501, 1e-15 );
  FRENSIE_CHECK_SMALL( photon.getZDirection(), 1e-15 );
  FRENSIE_CHECK_SMALL( photon.getYDirection(), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getXDirection(), -1.0, 1e-15 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_native_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_native_file",
                                        test_native_file_name, "",
                                        "Test Native file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
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
    std::shared_ptr<const Utility::UnivariateDistribution> occupation_number_s1_dist(
			    new Utility::TabularDistribution<Utility::LinLin>(
						    occupation_number_grid_s1,
						    occupation_number_s1 ) );

    // Create the subshell incoherent distributions
    distribution.reset(
		new MonteCarlo::SubshellIncoherentPhotonScatteringDistribution(
			  Data::convertENDFDesignatorToSubshellEnum( 1 ),
			  data_container.getSubshellOccupancy( 1 ),
			  data_container.getSubshellBindingEnergy( 1 ),
			  occupation_number_s1_dist,
			  3.0 ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstSubshellIncoherentPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
