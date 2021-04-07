//---------------------------------------------------------------------------//
//!
//! \file   tstWHIncoherentAdjointPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  Waller-Hartree incoherent adjoint photon scatt. dist. unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>
  
// FRENSIE Includes
#include "MonteCarlo_WHIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_StandardScatteringFunction.hpp"
#include "MonteCarlo_AdjointPhotonProbeState.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_InverseAngstromUnit.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointPhotonScatteringDistribution> 
  distribution, distribution_three_branch;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( WHIncoherentAdjointPhotonScatteringDistribution,
		   evaluate )
{
  double dist_value = distribution->evaluate( 0.1, -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 45.339225535578684, 1e-15 );

  dist_value = distribution->evaluate( 0.1, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 20.27125904362207, 1e-15 );

  dist_value = distribution->evaluate( 0.1, 1.0 );

  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  dist_value = distribution->evaluate( 1.0, 0.5145510353765 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 395.10878651418614, 1e-15 );

  dist_value = distribution->evaluate( 1.0, 0.9 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 37.868307610914194, 1e-15 );

  dist_value = distribution->evaluate( 1.0, 1.0 );

  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );

  dist_value = distribution->evaluate( 10.0, 0.9744500544935 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 50.10881515266787, 1e-15 );

  dist_value = distribution->evaluate( 10.0, 0.99 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 41.4790358560026, 1e-15 );

  dist_value = distribution->evaluate( 10.0, 1.0 );

  FRENSIE_CHECK_SMALL( dist_value, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the distribution pdf can be evaluated
FRENSIE_UNIT_TEST( WHIncoherentAdjointPhotonScatteringDistribution,
		   evaluatePDF )
{
  double pdf = distribution->evaluatePDF( 0.1, -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 0.879881897438394067, 1e-15 );

  pdf = distribution->evaluatePDF( 0.1, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 0.393396968300017302, 1e-15 );

  pdf = distribution->evaluatePDF( 0.1, 1.0 );

  FRENSIE_CHECK_SMALL( pdf, 1e-15 );

  pdf = distribution->evaluatePDF( 1.0, 0.5145510353765 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 12.2143006910790692, 1e-15 );

  pdf = distribution->evaluatePDF( 1.0, 0.9 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 1.17065201182352618, 1e-15 );

  pdf = distribution->evaluatePDF( 1.0, 1.0 );

  FRENSIE_CHECK_SMALL( pdf, 1e-15 );

  pdf = distribution->evaluatePDF( 10.0, 0.9744500544935 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 45.4868639688830285, 1e-15 );

  pdf = distribution->evaluatePDF( 10.0, 0.99 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf, 37.6530807163170067, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the integrated cross section can be evaluated
FRENSIE_UNIT_TEST( WHIncoherentAdjointPhotonScatteringDistribution,
		   evaluateIntegratedCrossSection )
{
  double cross_section =
    distribution->evaluateIntegratedCrossSection( 0.1, 1e-4 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 51.5291662208688734, 1e-15 );

  cross_section = distribution->evaluateIntegratedCrossSection( 1.0, 1e-4 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 32.3480137739510241, 1e-15 );

  cross_section = distribution->evaluateIntegratedCrossSection( 10.0, 1e-4 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 1.10160733569996983, 1e-15 );

  cross_section = distribution->evaluateIntegratedCrossSection( 20.0, 1e-4 );

  FRENSIE_CHECK_SMALL( cross_section, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from
FRENSIE_UNIT_TEST( WHIncoherentAdjointPhotonScatteringDistribution,
		   sample )
{
  double outgoing_energy, scattering_angle_cosine;

  // Set the fake stream
  std::vector<double> fake_stream( 17 );
  fake_stream[0] = 0.15; // branch 1
  fake_stream[1] = 0.4721647344828152; // select x = 0.9
  fake_stream[2] = 0.49; // accept
  fake_stream[3] = 0.91; // reject based on scattering function
  fake_stream[4] = 0.15; // branch 1
  fake_stream[5] = 0.4721647344828152; // select x = 0.9
  fake_stream[6] = 0.49; // accept
  fake_stream[7] = 0.909; // accept based on scattering function
  fake_stream[8] = 0.77; // branch 2
  fake_stream[9] = 0.5; // select x = 0.8124038404635961
  fake_stream[10] = 0.90; // accept based on scattering function
  fake_stream[11] = 0.78; // branch 3
  fake_stream[12] = 0.1; // select x = 0.8071682233277445
  fake_stream[13] = 0.99561; // reject based on scattering function
  fake_stream[14] = 0.99; // branch 3
  fake_stream[15] = 0.5; // select x = 0.9000009536743164
  fake_stream[16] = 0.909; // accept based on scattering function

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution_three_branch->sample(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.05677765668111111, 1e-15 );
  FRENSIE_CHECK_SMALL( scattering_angle_cosine, 1e-15 );

  distribution_three_branch->sample(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.05643038946823926, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.0553851381374173, 1e-15 );

  distribution_three_branch->sample(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.056777596517404945, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.5367431640625e-06, 1e-10 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from and trials can be recorded
FRENSIE_UNIT_TEST( WHIncoherentAdjointPhotonScatteringDistribution,
		   sampleAndRecordTrials_two_branch )
{
  double outgoing_energy, scattering_angle_cosine;
  MonteCarlo::AdjointPhotonScatteringDistribution::Counter trials = 0;

  // Set the fake stream
  std::vector<double> fake_stream( 12 );
  fake_stream[0] = 0.1; // branch 1
  fake_stream[1] = 0.5; // select x = 0.9
  fake_stream[2] = 0.44; // accept
  fake_stream[3] = 0.91; // reject based on scattering function
  fake_stream[4] = 0.11; // branch 1
  fake_stream[5] = 0.5; // select x = 0.9
  fake_stream[6] = 0.44; // accept
  fake_stream[7] = 0.909; // accept based on scattering function
  fake_stream[8] = 0.12; // branch 2
  fake_stream[9] = 0.0620192023179805; // select x = 0.8124038404635961
  fake_stream[10] = 0.78; // accept
  fake_stream[11] = 0.9921; // accept based on scattering function

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->sampleAndRecordTrials(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine,
		    trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.05677765668111111, 1e-15 );
  FRENSIE_CHECK_SMALL( scattering_angle_cosine, 1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 2 );

  distribution->sampleAndRecordTrials(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine,
		    trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.06289961773671575, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, -0.8759615953640392, 1e-15 );
  FRENSIE_CHECK_EQUAL( trials, 3 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from and trials can be recorded
FRENSIE_UNIT_TEST( WHIncoherentAdjointPhotonScatteringDistribution,
		   sampleAndRecordTrials_three_branch_inv )
{
  double outgoing_energy, scattering_angle_cosine;
  MonteCarlo::AdjointPhotonScatteringDistribution::Counter trials = 0;

  // Set the fake stream
  std::vector<double> fake_stream( 17 );
  fake_stream[0] = 0.15; // branch 1
  fake_stream[1] = 0.4721647344828152; // select x = 0.9
  fake_stream[2] = 0.49; // accept
  fake_stream[3] = 0.91; // reject based on scattering function
  fake_stream[4] = 0.15; // branch 1
  fake_stream[5] = 0.4721647344828152; // select x = 0.9
  fake_stream[6] = 0.49; // accept
  fake_stream[7] = 0.909; // accept based on scattering function
  fake_stream[8] = 0.77; // branch 2
  fake_stream[9] = 0.5; // select x = 0.8124038404635961
  fake_stream[10] = 0.90; // accept based on scattering function
  fake_stream[11] = 0.78; // branch 3
  fake_stream[12] = 0.1; // select x = 0.8071682233277445
  fake_stream[13] = 0.99561; // reject based on scattering function
  fake_stream[14] = 0.99; // branch 3
  fake_stream[15] = 0.5; // select x = 0.9000009536743164
  fake_stream[16] = 0.909; // accept based on scattering function

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution_three_branch->sampleAndRecordTrials(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine,
		    trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.05677765668111111, 1e-15 );
  FRENSIE_CHECK_SMALL( scattering_angle_cosine, 1e-15 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 0.5 );

  distribution_three_branch->sampleAndRecordTrials(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine,
		    trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.05643038946823926, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.0553851381374173, 1e-15 );
  FRENSIE_CHECK_EQUAL( 2.0/trials, 2.0/3.0 );

  distribution_three_branch->sampleAndRecordTrials(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine,
		    trials );

  FRENSIE_CHECK_FLOATING_EQUALITY( outgoing_energy, 0.056777596517404945, 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 9.5367431640625e-06, 1e-10 );
  FRENSIE_CHECK_EQUAL( 3.0/trials, 0.6 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that an adjoint photon can be scattered
FRENSIE_UNIT_TEST( WHIncoherentAdjointPhotonScatteringDistribution,
		   scatterAdjointPhoton )
{
  MonteCarlo::AdjointPhotonState adjoint_photon( 0 );
  adjoint_photon.setEnergy(
		  Utility::PhysicalConstants::electron_rest_mass_energy/10.0 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  // Set the fake stream
  std::vector<double> fake_stream( 9 );
  fake_stream[0] = 0.11; // branch 1
  fake_stream[1] = 0.5; // select x = 0.9
  fake_stream[2] = 0.44; // accept
  fake_stream[3] = 0.91; // reject based on scattering function
  fake_stream[4] = 0.11; // branch 1
  fake_stream[5] = 0.5; // select x = 0.9
  fake_stream[6] = 0.44; // accept
  fake_stream[7] = 0.909; // accept based on scattering function
  fake_stream[8] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->scatterAdjointPhoton( adjoint_photon,
				      bank,
				      shell_of_interaction );

  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_photon.getEnergy(),
                                   0.05677765668111111,
                                   1e-15 );
  FRENSIE_CHECK_SMALL( adjoint_photon.getZDirection(), 1e-15 );
  FRENSIE_CHECK_EQUAL( bank.size(), 0 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Generate a probe with energy 0.08
  adjoint_photon.setEnergy( 0.07 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );

  distribution->scatterAdjointPhoton( adjoint_photon,
				      bank,
				      shell_of_interaction );

  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 0.08 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getWeight(),
                                   31.7162862019685967,
                                   1e-14 );

  bank.pop();

  // Generate a probe with energy mec^2
  adjoint_photon.setEnergy( 0.19 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );

  distribution->scatterAdjointPhoton( adjoint_photon,
				      bank,
				      shell_of_interaction );

  FRENSIE_CHECK_EQUAL( bank.size(), 1 );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(),
		       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getWeight(),
                                   1.43055314362791086,
                                   1e-15 );

  bank.pop();

  // Generate two probes
  adjoint_photon.setEnergy( 0.3 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );

  distribution->scatterAdjointPhoton( adjoint_photon,
				      bank,
				      shell_of_interaction );

  FRENSIE_CHECK_EQUAL( bank.size(), 2 );
  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(),
		       Utility::PhysicalConstants::electron_rest_mass_energy );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getWeight(),
                                   0.401104057813784276,
                                   1e-15 );

  bank.pop();

  FRENSIE_CHECK_EQUAL( bank.top().getEnergy(), 1.0 );
  FRENSIE_CHECK_FLOATING_EQUALITY( bank.top().getWeight(),
                                   0.203384875392762621,
                                   1e-15 );

  bank.pop();

  // Make sure that probes do not generate more probe particles
  MonteCarlo::AdjointPhotonProbeState adjoint_photon_probe( 0 );
  adjoint_photon_probe.setEnergy( 0.3 );
  adjoint_photon_probe.setDirection( 0.0, 0.0, 1.0 );

  distribution->scatterAdjointPhoton( adjoint_photon_probe,
                                      bank,
                                      shell_of_interaction );

  FRENSIE_CHECK_EQUAL( bank.size(), 0 );
}

//---------------------------------------------------------------------------//
// Custom Setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_ace_file_name;
unsigned test_ace_file_start_line;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file",
                                        test_ace_file_name, "",
                                        "Test ACE file name" );

  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_ace_file_start_line",
                                        test_ace_file_start_line, 1,
                                        "Test ACE file start line" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  {
    // Create a file handler and data extractor
    std::shared_ptr<Data::ACEFileHandler> ace_file_handler( 
                        new Data::ACEFileHandler( test_ace_file_name,
                                                  "82000.12p",
						  test_ace_file_start_line ) );
    
    std::shared_ptr<Data::XSSEPRDataExtractor> xss_data_extractor(
                            new Data::XSSEPRDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

    // Create the scattering function
    Utility::ArrayView<const double> jince_block =
      xss_data_extractor->extractJINCEBlock();

    unsigned scatt_func_size = jince_block.size()/2;

    std::vector<double> recoil_momentum( jince_block( 0, scatt_func_size ) );
    std::vector<double> scat_func_values( jince_block( scatt_func_size,
                                                       scatt_func_size ) );

    std::shared_ptr<Utility::UnitAwareUnivariateDistribution<Utility::Units::InverseAngstrom,void> > raw_scattering_function(
    new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::InverseAngstrom,void>( 
							  recoil_momentum,
			                                  scat_func_values ) );

    std::shared_ptr<MonteCarlo::ScatteringFunction> scattering_function(
      new MonteCarlo::StandardScatteringFunction<Utility::Units::InverseAngstrom>( raw_scattering_function ) );
    
    // Create the scattering distribution
    std::shared_ptr<std::vector<double> >
      critical_line_energies( new std::vector<double>(3) );

    (*critical_line_energies)[0] = 0.08;
    (*critical_line_energies)[1] =
      Utility::PhysicalConstants::electron_rest_mass_energy;
    (*critical_line_energies)[2] = 1.0;

    // Create the scattering distribution (two branch sampling)
    std::shared_ptr<MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>
      incoherent_base_dist( 
         new MonteCarlo::WHIncoherentAdjointPhotonScatteringDistribution( 
                20.0,
                scattering_function,
                MonteCarlo::THREE_BRANCH_INVERSE_MIXED_ADJOINT_KN_SAMPLING ) );

    incoherent_base_dist->setCriticalLineEnergies( critical_line_energies );

    
    distribution_three_branch = incoherent_base_dist;

    // Create the scattering distribution (three branch sampling)
    incoherent_base_dist.reset( 
              new MonteCarlo::WHIncoherentAdjointPhotonScatteringDistribution( 
						       20.0,
						       scattering_function ) );

    incoherent_base_dist->setCriticalLineEnergies( critical_line_energies );

    
    distribution = incoherent_base_dist;
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstWHIncoherentAdjointPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
