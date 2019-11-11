//---------------------------------------------------------------------------//
//!
//! \file   tstEfficientCoherentScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  Efficient coherent scattering distribution unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_EfficientCoherentScatteringDistribution.hpp"
#include "MonteCarlo_StandardFormFactorSquared.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_InverseSquareAngstromUnit.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variable
//---------------------------------------------------------------------------//

std::shared_ptr<MonteCarlo::PhotonScatteringDistribution>
  distribution;

std::shared_ptr<MonteCarlo::AdjointPhotonScatteringDistribution>
  adjoint_distribution;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the distribution can be evaluated
FRENSIE_UNIT_TEST( EfficientCoherentScatteringDistribution, evaluate )
{
  double dist_value = distribution->evaluate( 0.1, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 3.354834939813898e3, 1e-15 );

  dist_value = distribution->evaluate( 0.1, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 4.17273487105470142, 1e-15 );

  dist_value = distribution->evaluate( 0.1, -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 3.59244179705391486, 1e-15 );

  dist_value = distribution->evaluate( 1.0, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 3354.83493981389802, 1e-15 );

  dist_value = distribution->evaluate( 1.0, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.00346135656968035591, 1e-15 );

  dist_value = distribution->evaluate( 1.0, -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( dist_value, 0.00114806389085036088, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the distribution pdf can be evaluated
FRENSIE_UNIT_TEST( EfficientCoherentScatteringDistribution, evaluatePDF )
{
  double pdf_value = distribution->evaluatePDF( 0.1, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 49.4688663359142353, 1e-15 );

  pdf_value = distribution->evaluatePDF( 0.1, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0615292457884274099, 1e-15 );

  pdf_value = distribution->evaluatePDF( 0.1, -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.0529725087124166966, 1e-15 );

  pdf_value = distribution->evaluatePDF( 1.0, 1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 3673.12567843006855, 1e-15 );

  pdf_value = distribution->evaluatePDF( 1.0, 0.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.00378975357249642037, 1e-15 );

  pdf_value = distribution->evaluatePDF( 1.0, -1.0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( pdf_value, 0.00125698671726446362, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the integrated cross section can be evaluated
FRENSIE_UNIT_TEST( EfficientCoherentScatteringDistribution,
		   evaluateIntegratedCrossSection )
{
  double cross_section =
    distribution->evaluateIntegratedCrossSection( 0.1, 1e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 6.78170976677162821e1, 1e-15 );

  cross_section =
    distribution->evaluateIntegratedCrossSection( 1.0, 1e-3 );

  FRENSIE_CHECK_FLOATING_EQUALITY( cross_section, 9.13346080019725521e-1, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from
FRENSIE_UNIT_TEST( EfficientCoherentScatteringDistribution, sample )
{
  double outgoing_energy, scattering_angle_cosine;

  // Set up the random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.942; // reject
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.941;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->sample( 0.1,
			outgoing_energy,
			scattering_angle_cosine );

  FRENSIE_CHECK_EQUAL( outgoing_energy, 0.1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.940007827406442842, 1e-15 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that the distribution can be sampled from
FRENSIE_UNIT_TEST( EfficientCoherentScatteringDistribution,
		   sampleAndRecordTrials )
{
  double outgoing_energy, scattering_angle_cosine;
  MonteCarlo::PhotonScatteringDistribution::Counter trials = 0;

  // Set up the random number stream
  std::vector<double> fake_stream( 4 );
  fake_stream[0] = 0.5;
  fake_stream[1] = 0.942; // reject
  fake_stream[2] = 0.5;
  fake_stream[3] = 0.941;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->sampleAndRecordTrials( 0.1,
				       outgoing_energy,
				       scattering_angle_cosine,
				       trials );

  FRENSIE_CHECK_EQUAL( outgoing_energy, 0.1 );
  FRENSIE_CHECK_FLOATING_EQUALITY( scattering_angle_cosine, 0.940007827406442842, 1e-15 );
  FRENSIE_CHECK_EQUAL( 1.0/trials, 0.5 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

//---------------------------------------------------------------------------//
// Check that a photon can be scattered coherently
FRENSIE_UNIT_TEST( EfficientCoherentScatteringDistribution,
		   scatterPhoton )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::PhotonState photon( 0 );
  photon.setEnergy( 4.95936772145E-03 );
  photon.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 1.00475965594E-03; // sample form factor function squared (y = 1E6 cm)
  fake_stream[1] = 9.98800000000E-01; // reject the cosine scattering angle form function rejection loop
  fake_stream[2] = 6.50327467413E-01; // sample form factor function squared (y = 3E7 cm)
  fake_stream[3] = 5.07800000000E-01; // accept the cosine scattering angle form function rejection loop
  fake_stream[4] = 0.0;


  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  distribution->scatterPhoton( photon,
                               bank,
                               shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getEnergy(), 4.95936772145E-03, 1e-15  );
  FRENSIE_CHECK_FLOATING_EQUALITY( photon.getZDirection(), -0.125019990362325473, 1e-14 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );
}

//---------------------------------------------------------------------------//
// Check that an adjoint photon can be scattered coherently
FRENSIE_UNIT_TEST( EfficientCoherentScatteringDistribution,
		   scatterAdjointPhoton )
{
  MonteCarlo::ParticleBank bank;

  MonteCarlo::AdjointPhotonState adjoint_photon( 0 );
  adjoint_photon.setEnergy( 4.95936772145E-03 );
  adjoint_photon.setDirection( 0.0, 0.0, 1.0 );

  Data::SubshellType shell_of_interaction;

  // Set up the random number stream
  std::vector<double> fake_stream( 5 );
  fake_stream[0] = 1.00475965594E-03; // sample form factor function squared (y = 1E6 cm)
  fake_stream[1] = 9.98800000000E-01; // reject the cosine scattering angle form function rejection loop
  fake_stream[2] = 6.50327467413E-01; // sample form factor function squared (y = 3E7 cm)
  fake_stream[3] = 5.07800000000E-01; // accept the cosine scattering angle form function rejection loop
  fake_stream[4] = 0.0;


  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  adjoint_distribution->scatterAdjointPhoton( adjoint_photon,
					      bank,
					      shell_of_interaction );

  Utility::RandomNumberGenerator::unsetFakeStream();

  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_photon.getEnergy(),
			  4.95936772145E-03,
			  1e-15  );
  FRENSIE_CHECK_FLOATING_EQUALITY( adjoint_photon.getZDirection(),
			  -0.125019990362325473,
			  1e-14 );
  FRENSIE_CHECK_EQUAL( shell_of_interaction, Data::UNKNOWN_SUBSHELL );
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

    // Extract the form factor
    Utility::ArrayView<const double> jcohe_block =
      xss_data_extractor->extractJCOHEBlock();

    unsigned form_factor_size = jcohe_block.size()/3;

    std::vector<double> recoil_momentum_squared(
					  jcohe_block( 0, form_factor_size ) );

    std::vector<double> form_factor_squared(
			 jcohe_block( 2*form_factor_size, form_factor_size ) );

    for( unsigned i = 0; i < form_factor_size; ++i )
    {
      recoil_momentum_squared[i] *= recoil_momentum_squared[i]; 

      form_factor_squared[i] *= form_factor_squared[i];
    }

    std::shared_ptr<Utility::UnitAwareTabularUnivariateDistribution<Utility::Units::InverseSquareAngstrom,void> >
    raw_form_factor_squared(
         new Utility::UnitAwareTabularDistribution<Utility::LinLin,Utility::Units::InverseSquareAngstrom,void>(
                                                       recoil_momentum_squared,
						       form_factor_squared ) );

    std::shared_ptr<const MonteCarlo::FormFactorSquared> form_factor_obj(
       new MonteCarlo::StandardFormFactorSquared<Utility::Units::InverseSquareAngstrom>(
                                                   raw_form_factor_squared ) );

    // Create the scattering distribution
    distribution.reset(
		new MonteCarlo::EfficientCoherentScatteringDistribution(
                                                           form_factor_obj ) );

    adjoint_distribution.reset(
		new MonteCarlo::EfficientCoherentScatteringDistribution(
                                                           form_factor_obj ) );
  }

  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstEfficientCoherentScatteringDistribution.cpp
//---------------------------------------------------------------------------//
