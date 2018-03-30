//---------------------------------------------------------------------------//
//!
//! \file   tstSubshellIncoherentAdjointPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The subshell incoherent adjoint photon scattering distribution
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"
#include "MonteCarlo_SubshellIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_StandardOccupationNumber.hpp"
#include "MonteCarlo_AdjointPhotonProbeState.hpp"
#include "Data_SubshellType.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_MeCMomentumUnit.hpp"
#include "Utility_InverseMeCMomentumUnit.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::AdjointPhotonScatteringDistribution>
  base_distribution_s1;

std::shared_ptr<MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution>
  distribution_s1;

std::shared_ptr<MonteCarlo::AdjointPhotonScatteringDistribution>
  base_distribution_s5;

std::shared_ptr<MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution>
  distribution_s5;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that the subshell can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentAdjointPhotonScatteringDistribution,
                   getSubshell )
{
  TEST_EQUALITY_CONST( distribution_s1->getSubshell(), Data::K_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that the subshell occupancy can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentAdjointPhotonScatteringDistribution,
                   getSubshellOccupancy )
{
  TEST_EQUALITY_CONST( distribution_s1->getSubshellOccupancy(), 2 );
}

//---------------------------------------------------------------------------//
// Check that the subshell binding energy can be returned
TEUCHOS_UNIT_TEST( SubshellIncoherentAdjointPhotonScatteringDistribution,
                   getSubshellBindingEnergy )
{
  TEST_FLOATING_EQUALITY(
                 distribution_s1->getSubshellBindingEnergy(), 0.08829, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
TEUCHOS_UNIT_TEST( SubshellIncoherentAdjointPhotonScatteringDistribution,
                   evaluate )
{
  // Incoming energy = 0.1 MeV
  double dist_value = base_distribution_s1->evaluate( 0.1, -1.0 );
  
  TEST_FLOATING_EQUALITY( dist_value, 0.435636374191108011, 1e-15 );

  dist_value = base_distribution_s1->evaluate( 0.1, 0.0 );
  
  TEST_FLOATING_EQUALITY( dist_value, 0.111659296287109813, 1e-15 );

  dist_value = base_distribution_s1->evaluate( 0.1, 1.0 );

  TEST_FLOATING_EQUALITY( dist_value, 0.0, 1e-15 );

  // Incoming energy = 1.0 MeV
  dist_value = base_distribution_s1->evaluate( 1.0, 0.5145510353765 );
  
  TEST_FLOATING_EQUALITY( dist_value, 4.76593248990849983, 1e-15 );

  dist_value = base_distribution_s1->evaluate( 1.0, 0.9 );
  
  TEST_FLOATING_EQUALITY( dist_value, 0.715826479226024492, 1e-15 );

  dist_value = base_distribution_s1->evaluate( 1.0, 1.0 );

  TEST_FLOATING_EQUALITY( dist_value, 0.0, 1e-15 );

  // Incoming energy = 10.0 MeV
  dist_value = base_distribution_s1->evaluate( 10.0, 0.9744500544935 );

  TEST_FLOATING_EQUALITY( dist_value, 0.6110831116178992, 1e-15 );

  dist_value = base_distribution_s1->evaluate( 10.0, 0.99 );
  
  TEST_FLOATING_EQUALITY( dist_value, 0.961827451781265497, 1e-15 );

  dist_value = base_distribution_s1->evaluate( 10.0, 1.0 );

  TEST_FLOATING_EQUALITY( dist_value, 0.0, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the distribution PDF can be evaluated
TEUCHOS_UNIT_TEST( SubshellIncoherentAdjointPhotonScatteringDistribution,
                   evaluatePDF )
{
  // Incoming energy = 0.1 MeV
  double pdf = base_distribution_s1->evaluatePDF( 0.1, -1.0 );
  
  TEST_FLOATING_EQUALITY( pdf, 1.48221359227104532, 1e-6 );

  pdf = base_distribution_s1->evaluatePDF( 0.1, 0.0 );
  
  TEST_FLOATING_EQUALITY( pdf, 0.37991071559963463, 1e-6 );

  pdf = base_distribution_s1->evaluatePDF( 0.1, 1.0 );
  
  TEST_FLOATING_EQUALITY( pdf, 0.0, 1e-6 );

  // Incoming energy = 1.0 MeV
  pdf = base_distribution_s1->evaluatePDF( 1.0, 0.5145510353765 );
  
  TEST_FLOATING_EQUALITY( pdf, 9.01494627618673583, 1e-6 );

  pdf = base_distribution_s1->evaluatePDF( 1.0, 0.9 );
  
  TEST_FLOATING_EQUALITY( pdf, 1.35401356753553248, 1e-6 );

  pdf = base_distribution_s1->evaluatePDF( 1.0, 1.0 );

  TEST_FLOATING_EQUALITY( pdf, 0.0, 1e-6 );

  // Incoming energy = 10.0 MeV
  pdf = base_distribution_s1->evaluatePDF( 10.0, 0.9744500544935 );
  
  TEST_FLOATING_EQUALITY( pdf, 27.5843925213305425, 1e-5 );

  pdf = base_distribution_s1->evaluatePDF( 10.0, 0.99 );
  
  TEST_FLOATING_EQUALITY( pdf, 43.4170499287423368, 1e-5 );

  pdf = base_distribution_s1->evaluatePDF( 10.0, 1.0 );

  TEST_FLOATING_EQUALITY( pdf, 0.0, 1e-5 );
}

//---------------------------------------------------------------------------//
// Check that the integrated cross section can be evaluated
TEUCHOS_UNIT_TEST( SubshellIncoherentAdjointPhotonScatteringDistribution,
                   evaluateIntegratedCrossSection )
{
  double cross_section =
    base_distribution_s1->evaluateIntegratedCrossSection( 0.1, 1e-4 );
  
  TEST_FLOATING_EQUALITY( cross_section, 0.2939140614458845, 1e-12 );
  
  cross_section = base_distribution_s1->evaluateIntegratedCrossSection(1.0, 1e-4);
  
  TEST_FLOATING_EQUALITY( cross_section, 0.528671095223852916, 1e-12 );

  cross_section = base_distribution_s1->evaluateIntegratedCrossSection(10.0, 1e-4);
  
  TEST_FLOATING_EQUALITY( cross_section, 0.0221532279926182352, 1e-12 );

  cross_section = base_distribution_s1->evaluateIntegratedCrossSection(20.0-0.08829, 1e-4);
  
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );

  cross_section = base_distribution_s1->evaluateIntegratedCrossSection(20.0, 1e-4);
  
  TEST_FLOATING_EQUALITY( cross_section, 0.0, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from
TEUCHOS_UNIT_TEST( SubshellIncoherentAdjointPhotonScatteringDistribution,
                   sample )
{
  double outgoing_energy, scattering_angle_cosine;

  // Set the fake stream
  std::vector<double> fake_stream( 26 );
  // Sample 1
  fake_stream[0] = 0.15; // branch 1
  fake_stream[1] = 0.4721647344828152; // select x = 0.9
  fake_stream[2] = 0.55; // reject
  fake_stream[3] = 0.15; // branch 1
  fake_stream[4] = 0.22986680137273696; // select x = 0.95
  fake_stream[5] = 0.245; // accept x
  fake_stream[6] = 0.32; // reject mu
  fake_stream[7] = 0.15; // branch 1
  fake_stream[8] = 0.22986680137273696; // select x = 0.95
  fake_stream[9] = 0.245; // accept x
  fake_stream[10] = 0.31; // accept mu
  // Sample 2
  fake_stream[11] = 0.77; // branch 2
  fake_stream[12] = 0.5; // select x = 0.8124038404635961
  fake_stream[13] = 0.88; // reject mu
  fake_stream[14] = 0.77; // branch 2
  fake_stream[15] = 0.5; // select x = 0.8124038404635961
  fake_stream[16] = 0.87; // accept mu
  // Sample 3
  fake_stream[17] = 0.78; // branch 3
  fake_stream[18] = 0.1; // select x = 0.8071682233277445
  fake_stream[19] = 0.89; // reject mu
  fake_stream[20] = 0.78; // branch 3
  fake_stream[21] = 0.1; // select x = 0.8071682233277445
  fake_stream[22] = 0.88; // accept mu
  // Sample 4
  fake_stream[23] = 0.99; // branch 3
  fake_stream[24] = 0.5; // select x = 0.9000009536743164
  fake_stream[25] = 0.69; // accept mu

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  base_distribution_s5->sample(
                    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
                    outgoing_energy,
                    scattering_angle_cosine );

  TEST_FLOATING_EQUALITY( outgoing_energy, 0.053789358961052636, 1e-15 );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.5, 1e-15 );
  
  base_distribution_s5->sample(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine );

  TEST_FLOATING_EQUALITY( outgoing_energy, 0.06289961773671575, 1e-15 );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -0.8759615953640385, 1e-15);
  
  base_distribution_s5->sample(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine );
  
  TEST_FLOATING_EQUALITY( outgoing_energy, 0.06330760990853734, 1e-15 );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -0.9283177667225548, 1e-15);
  
  base_distribution_s5->sample(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine );
		    
  TEST_FLOATING_EQUALITY( outgoing_energy, 0.056777596517404945, 1e-15 );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 
			  9.536743164284545e-06, 
			  1e-15 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from
TEUCHOS_UNIT_TEST( SubshellIncoherentAdjointPhotonScatteringDistribution,
                   sampleAndRecordTrials )
{
  double outgoing_energy, scattering_angle_cosine;
  unsigned trials = 0u;

  // Set the fake stream
  std::vector<double> fake_stream( 26 );
  // Sample 1
  fake_stream[0] = 0.15; // branch 1
  fake_stream[1] = 0.4721647344828152; // select x = 0.9
  fake_stream[2] = 0.55; // reject
  fake_stream[3] = 0.15; // branch 1
  fake_stream[4] = 0.22986680137273696; // select x = 0.95
  fake_stream[5] = 0.245; // accept x
  fake_stream[6] = 0.32; // reject mu
  fake_stream[7] = 0.15; // branch 1
  fake_stream[8] = 0.22986680137273696; // select x = 0.95
  fake_stream[9] = 0.245; // accept x
  fake_stream[10] = 0.31; // accept mu
  // Sample 2
  fake_stream[11] = 0.77; // branch 2
  fake_stream[12] = 0.5; // select x = 0.8124038404635961
  fake_stream[13] = 0.88; // reject mu
  fake_stream[14] = 0.77; // branch 2
  fake_stream[15] = 0.5; // select x = 0.8124038404635961
  fake_stream[16] = 0.87; // accept mu
  // Sample 3
  fake_stream[17] = 0.78; // branch 3
  fake_stream[18] = 0.1; // select x = 0.8071682233277445
  fake_stream[19] = 0.89; // reject mu
  fake_stream[20] = 0.78; // branch 3
  fake_stream[21] = 0.1; // select x = 0.8071682233277445
  fake_stream[22] = 0.88; // accept mu
  // Sample 4
  fake_stream[23] = 0.99; // branch 3
  fake_stream[24] = 0.5; // select x = 0.9000009536743164
  fake_stream[25] = 0.69; // accept mu

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  base_distribution_s5->sampleAndRecordTrials(
                    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
                    outgoing_energy,
                    scattering_angle_cosine,
                    trials );

  TEST_FLOATING_EQUALITY( outgoing_energy, 0.053789358961052636, 1e-15 );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 0.5, 1e-15 );
  TEST_EQUALITY_CONST( 1.0/trials, 1.0/3.0 );
  
  base_distribution_s5->sampleAndRecordTrials(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine,
                    trials );

  TEST_FLOATING_EQUALITY( outgoing_energy, 0.06289961773671575, 1e-15 );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -0.8759615953640385, 1e-15);
  TEST_EQUALITY_CONST( 2.0/trials, 2.0/5.0 );
  
  base_distribution_s5->sampleAndRecordTrials(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine,
                    trials );
  
  TEST_FLOATING_EQUALITY( outgoing_energy, 0.06330760990853734, 1e-15 );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, -0.9283177667225548, 1e-15);
  TEST_EQUALITY_CONST( 3.0/trials, 3.0/7.0 );
  
  base_distribution_s5->sampleAndRecordTrials(
		    Utility::PhysicalConstants::electron_rest_mass_energy/10.0,
		    outgoing_energy,
		    scattering_angle_cosine,
                    trials );
		    
  TEST_FLOATING_EQUALITY( outgoing_energy, 0.056777596517404945, 1e-15 );
  TEST_FLOATING_EQUALITY( scattering_angle_cosine, 
			  9.536743164284545e-06, 
			  1e-15 );
  TEST_EQUALITY_CONST( 4.0/trials, 0.5 );
  
  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that an adjoint photon can be scattered
TEUCHOS_UNIT_TEST( SubshellIncoherentAdjointPhotonScatteringDistribution,
                   scatterAdjointPhoton )
{
  MonteCarlo::AdjointPhotonState adjoint_photon( 0 );
  adjoint_photon.setEnergy(
                  Utility::PhysicalConstants::electron_rest_mass_energy/10.0 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );

  MonteCarlo::ParticleBank bank;

  Data::SubshellType shell_of_interaction;

  // Set the fake stream
  std::vector<double> fake_stream( 8 );
  fake_stream[0] = 0.15; // branch 1
  fake_stream[1] = 0.4721647344828152; // select x = 0.9
  fake_stream[2] = 0.55; // reject
  fake_stream[3] = 0.15; // branch 1
  fake_stream[4] = 0.22986680137273696; // select x = 0.95
  fake_stream[5] = 0.245; // accept x
  fake_stream[6] = 0.31; // accept mu
  fake_stream[7] = 0.0; // azimuthal angle = 0.0

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  base_distribution_s5->scatterAdjointPhoton( adjoint_photon, 
                                              bank, 
                                              shell_of_interaction );

  TEST_FLOATING_EQUALITY( adjoint_photon.getEnergy(),
			  0.053789358961052636, 
			  1e-15 );
  UTILITY_TEST_FLOATING_EQUALITY( adjoint_photon.getZDirection(), 0.5, 1e-15 );
  TEST_EQUALITY_CONST( bank.size(), 0 );
  TEST_EQUALITY_CONST( shell_of_interaction, Data::M1_SUBSHELL );

  Utility::RandomNumberGenerator::unsetFakeStream();

  // Generate a proble with energy 0.08
  adjoint_photon.setEnergy( 0.07 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );

  base_distribution_s5->scatterAdjointPhoton( adjoint_photon,
                                              bank,
                                              shell_of_interaction );

  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_EQUALITY_CONST( bank.top().getEnergy(), 0.08 );
  TEST_FLOATING_EQUALITY( bank.top().getWeight(), 
			  36.652825479485756,
			  1e-14 );

  bank.pop();

  // Generate a probe with energy mec^2
  adjoint_photon.setEnergy( 0.19 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );

  base_distribution_s5->scatterAdjointPhoton( adjoint_photon,
                                              bank,
                                              shell_of_interaction );

  TEST_EQUALITY_CONST( bank.size(), 1 );
  TEST_EQUALITY_CONST( bank.top().getEnergy(), 
		       Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_FLOATING_EQUALITY( bank.top().getWeight(),
			  1.44485870585632448,
			  1e-15 );

  bank.pop();

  // Generate two probes
  adjoint_photon.setEnergy( 0.3 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );

  base_distribution_s5->scatterAdjointPhoton( adjoint_photon,
                                              bank,
                                              shell_of_interaction );

  TEST_EQUALITY_CONST( bank.size(), 2 );
  TEST_EQUALITY_CONST( bank.top().getEnergy(),
		       Utility::PhysicalConstants::electron_rest_mass_energy );
  TEST_FLOATING_EQUALITY( bank.top().getWeight(),
			  0.471349591314760286,
			  1e-15 );
  
  bank.pop();

  TEST_EQUALITY_CONST( bank.top().getEnergy(), 1.0 );
  TEST_FLOATING_EQUALITY( bank.top().getWeight(),
			  0.237508288495414555,
			  1e-15 );

  bank.pop();

  // Make sure that probes do not generate more probe particles
  MonteCarlo::AdjointPhotonProbeState adjoint_photon_probe( 0 );
  adjoint_photon_probe.setEnergy( 0.3 );
  adjoint_photon_probe.setDirection( 0.0, 0.0, 1.0 );

  base_distribution_s5->scatterAdjointPhoton( adjoint_photon_probe,
                                              bank,
                                              shell_of_interaction );

  TEST_EQUALITY_CONST( bank.size(), 0 );
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

    const std::vector<double>& occupation_number_grid_s5 =
      data_container.getOccupationNumberMomentumGrid( 5 );
    
    const std::vector<double>& occupation_number_s1 = 
      data_container.getOccupationNumber( 1 );

    const std::vector<double>& occupation_number_s5 =
      data_container.getOccupationNumber( 5 );
    
    // Create the occupation number distribution
    std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<Utility::Units::MeCMomentum,void> > raw_occupation_number_s1(
              new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::MeCMomentum,void>(
                                                    occupation_number_grid_s1,
                                                    occupation_number_s1 ) );

    std::shared_ptr<MonteCarlo::OccupationNumber> occupation_number_obj_s1( new MonteCarlo::StandardOccupationNumber<Utility::Units::MeCMomentum>( raw_occupation_number_s1 ) );

    std::shared_ptr<Utility::UnitAwareTabularOneDDistribution<Utility::Units::MeCMomentum,void> > raw_occupation_number_s5(
              new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::MeCMomentum,void>(
                                                    occupation_number_grid_s5,
                                                    occupation_number_s5 ) );

    std::shared_ptr<MonteCarlo::OccupationNumber> occupation_number_obj_s5( new MonteCarlo::StandardOccupationNumber<Utility::Units::MeCMomentum>( raw_occupation_number_s5 ) );
   
    // Create the Subshell incoherent adjoint photon scattering distribution
    distribution_s1.reset(
         new MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution(
                                20.0,
                                Data::convertENDFDesignatorToSubshellEnum( 1 ),
                                data_container.getSubshellOccupancy( 1 ),
                                data_container.getSubshellBindingEnergy( 1 ),
                                occupation_number_obj_s1 ) );

    base_distribution_s1 = distribution_s1;

    distribution_s5.reset(
         new MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution(
                                20.0,
                                Data::convertENDFDesignatorToSubshellEnum( 5 ),
                                data_container.getSubshellOccupancy( 5 ),
                                data_container.getSubshellBindingEnergy( 5 ),
                                occupation_number_obj_s5 ) );

    // Set the critical line energies
    Teuchos::ArrayRCP<double> critical_line_energies( 3 );
    critical_line_energies[0] = 0.08;
    critical_line_energies[1] = 
      Utility::PhysicalConstants::electron_rest_mass_energy;
    critical_line_energies[2] = 1.0;
    
    distribution_s5->setCriticalLineEnergies( critical_line_energies );

    base_distribution_s5 = distribution_s5;
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
// end tstSubshellIncoherentAdjointPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
