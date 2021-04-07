//---------------------------------------------------------------------------//
//!
//! \file   tstElectronPhotonRelaxationDataContainer.cpp
//! \author Alex Robinson
//! \brief  Electron-photon-relaxation data container class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// FRENSIE Includes
#include "Data_ElectronPhotonRelaxationVolatileDataContainer.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Data::ElectronPhotonRelaxationVolatileDataContainer epr_data_container;

const std::string notes( "This is a test data table. Do not use it for "
                         "anything other than tests!" );

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the notes can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer, setNotes )
{
  epr_data_container.setNotes( notes );

  FRENSIE_CHECK_EQUAL( epr_data_container.getNotes(), notes );
}

//---------------------------------------------------------------------------//
// Check that the atomic number can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer, setAtomicNumber )
{
  epr_data_container.setAtomicNumber( 1u );

  FRENSIE_CHECK_EQUAL( epr_data_container.getAtomicNumber(), 1u );
}

//---------------------------------------------------------------------------//
// Check that the atomic weight can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer, setAtomicWeight )
{
  epr_data_container.setAtomicWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getAtomicWeight(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the min photon energy can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer, setMinPhotonEnergy )
{
  epr_data_container.setMinPhotonEnergy( 0.001 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getMinPhotonEnergy(),
                       0.001 );
}

//---------------------------------------------------------------------------//
// Check that the max photon energy can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer, setMaxPhotonEnergy )
{
  epr_data_container.setMaxPhotonEnergy( 20.0 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getMaxPhotonEnergy(),
                       20.0 );
}

//---------------------------------------------------------------------------//
// Check that the min electron energy can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer, setMinElectronEnergy )
{
  epr_data_container.setMinElectronEnergy( 1.0e-5 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getMinElectronEnergy(),
                       1.0e-5 );
}

//---------------------------------------------------------------------------//
// Check that the max electron energy can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer, setMaxElectronEnergy )
{
  epr_data_container.setMaxElectronEnergy( 1.0e+5 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getMaxElectronEnergy(),
                       1.0e+5 );
}

//---------------------------------------------------------------------------//
// Check that the occupation number evaluation tolerance can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setOccupationNumberEvaluationTolerance )
{
  epr_data_container.setOccupationNumberEvaluationTolerance( 1e-4 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getOccupationNumberEvaluationTolerance(),
                       1e-4 );
}

//---------------------------------------------------------------------------//
// Check that the subshell incoherent evaluation tolerance can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setSubshellIncoherentEvaluationTolerance )
{
  epr_data_container.setSubshellIncoherentEvaluationTolerance( 1e-3 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getSubshellIncoherentEvaluationTolerance(),
                       1e-3 );
}

//---------------------------------------------------------------------------//
// Check that the photon threshold energy nudge factor can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setPhotonThresholdEnergyNudgeFactor )
{
  epr_data_container.setPhotonThresholdEnergyNudgeFactor( 1.01 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getPhotonThresholdEnergyNudgeFactor(),
                       1.01 );
}

//---------------------------------------------------------------------------//
// Check that the Cutoff Angle can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer, setCutoffAngleCosine )
{
  epr_data_container.setCutoffAngleCosine( 0.9 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getCutoffAngleCosine(),
                       0.9 );
}

//---------------------------------------------------------------------------//
// Check that the number of discrete moment preserving angles can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setNumberOfMomentPreservingAngles )
{
  epr_data_container.setNumberOfMomentPreservingAngles( 1 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getNumberOfMomentPreservingAngles(),
                       1 );
}

//---------------------------------------------------------------------------//
// Check that the electron tabular tol can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setElectronTabularEvaluationTolerance )
{
  epr_data_container.setElectronTabularEvaluationTolerance( 1e-3 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getElectronTabularEvaluationTolerance(),
                       1e-3 );
}

//---------------------------------------------------------------------------//
// Check that the photon grid convergence tolerance can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setPhotonGridConvergenceTolerance )
{
  epr_data_container.setPhotonGridConvergenceTolerance( 0.001 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getPhotonGridConvergenceTolerance(),
                       0.001 );
}

//---------------------------------------------------------------------------//
// Check that the photon grid absolute difference tolerance can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setPhotonGridAbsoluteDifferenceTolerance )
{
  epr_data_container.setPhotonGridAbsoluteDifferenceTolerance( 1e-42 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getPhotonGridAbsoluteDifferenceTolerance(),
                       1e-42 );
}

//---------------------------------------------------------------------------//
// Check that the photon grid distance tolerance can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setPhotonGridDistanceTolerance )
{
  epr_data_container.setPhotonGridDistanceTolerance( 1e-15 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getPhotonGridDistanceTolerance(),
                       1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the electron grid convergence tolerance can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setElectronGridConvergenceTolerance )
{
  epr_data_container.setElectronGridConvergenceTolerance( 0.001 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getElectronGridConvergenceTolerance(),
                       0.001 );
}

//---------------------------------------------------------------------------//
// Check that the electron grid absolute difference tolerance can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setElectronGridAbsoluteDifferenceTolerance )
{
  epr_data_container.setElectronGridAbsoluteDifferenceTolerance( 1e-42 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getElectronGridAbsoluteDifferenceTolerance(),
                       1e-42 );
}

//---------------------------------------------------------------------------//
// Check that the electron grid distance tolerance can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setElectronGridDistanceTolerance )
{
  epr_data_container.setElectronGridDistanceTolerance( 1e-15 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getElectronGridDistanceTolerance(),
                       1e-15 );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung_evaluation_tolerance can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setBremsstrahlungEvaluationTolerance )
{
  epr_data_container.setBremsstrahlungEvaluationTolerance( 1e-3 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getBremsstrahlungEvaluationTolerance(),
                       1e-3 );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung_convergence_tolerance can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setBremsstrahlungGridConvergenceTolerance )
{
  epr_data_container.setBremsstrahlungGridConvergenceTolerance( 1e-3 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getBremsstrahlungGridConvergenceTolerance(),
                       1e-3 );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung_absolute_diff_tol can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setBremsstrahlungAbsoluteDifferenceTolerance )
{
  epr_data_container.setBremsstrahlungAbsoluteDifferenceTolerance( 1e-3 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getBremsstrahlungAbsoluteDifferenceTolerance(),
                       1e-3 );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung_distance_tol can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setBremsstrahlungDistanceTolerance )
{
  epr_data_container.setBremsstrahlungDistanceTolerance( 1e-3 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getBremsstrahlungDistanceTolerance(),
                       1e-3 );
}

//---------------------------------------------------------------------------//
// Check that the electroionization_evaluation_tolerance can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setElectroionizationEvaluationTolerance )
{
  epr_data_container.setElectroionizationEvaluationTolerance( 1e-3 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getElectroionizationEvaluationTolerance(),
                       1e-3 );
}

//---------------------------------------------------------------------------//
// Check that the electroionization_convergence_tolerance can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setElectroionizationGridConvergenceTolerance )
{
  epr_data_container.setElectroionizationGridConvergenceTolerance( 1e-3 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getElectroionizationGridConvergenceTolerance(),
                       1e-3 );
}

//---------------------------------------------------------------------------//
// Check that the electroionization_absolute_diff_tol can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setElectroionizationAbsoluteDifferenceTolerance )
{
  epr_data_container.setElectroionizationAbsoluteDifferenceTolerance( 1e-3 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getElectroionizationAbsoluteDifferenceTolerance(),
                       1e-3 );
}

//---------------------------------------------------------------------------//
// Check that the electroionization_distance_tol can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setElectroionizationDistanceTolerance )
{
  epr_data_container.setElectroionizationDistanceTolerance( 1e-3 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getElectroionizationDistanceTolerance(),
                       1e-3 );
}

// Relaxation Tests

//---------------------------------------------------------------------------//
// Check that the subshells can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer, setSubshells )
{
  std::set<unsigned> subshells;
  subshells.insert( 1 );

  epr_data_container.setSubshells( subshells );

  FRENSIE_CHECK( epr_data_container.getSubshells().count( 1 ) );
  FRENSIE_CHECK( !epr_data_container.getSubshells().count( 0 ) );
  FRENSIE_CHECK( !epr_data_container.getSubshells().count( 2 ) );
}

//---------------------------------------------------------------------------//
// Check that the subshell occupancies can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setSubshellOccupancy )
{
  epr_data_container.setSubshellOccupancy( 1, 1.0 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getSubshellOccupancy( 1 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the subshell binding energies can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setSubshellBindingEnergy )
{
  epr_data_container.setSubshellBindingEnergy( 1, 1.361e-5 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getSubshellBindingEnergy( 1 ),
                       1.361e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of subshell relaxation transitions can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setSubshellRelaxationTransitions )
{
  FRENSIE_CHECK( !epr_data_container.hasRelaxationData() );

  epr_data_container.setSubshellRelaxationTransitions( 1, 1 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getSubshellRelaxationTransitions(1),
                       1 );
  FRENSIE_CHECK( epr_data_container.hasRelaxationData() );
  FRENSIE_CHECK( epr_data_container.hasSubshellRelaxationData( 1 ) );
}

//---------------------------------------------------------------------------//
// Check that the relaxation vacancies for a subshell can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setSubshellRelaxationVacancies )
{
  std::vector<std::pair<unsigned,unsigned> > vacancies( 1 );
  vacancies[0].first = 1u;
  vacancies[1].second = 0u;

  epr_data_container.setSubshellRelaxationVacancies( 1, vacancies );

  FRENSIE_CHECK_EQUAL(
                        epr_data_container.getSubshellRelaxationVacancies( 1 ),
                        vacancies );

}

//---------------------------------------------------------------------------//
// Check that the relaxation particle energies for a subshell can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setSubshellRelaxationEnergies )
{
  std::vector<double> energies( 1 );
  energies[0] = 1e-6;

  epr_data_container.setSubshellRelaxationParticleEnergies( 1, energies );

  FRENSIE_CHECK_EQUAL(
                 epr_data_container.getSubshellRelaxationParticleEnergies( 1 ),
                 energies );
}

//---------------------------------------------------------------------------//
// Check that the relaxation probabilities for a subshell can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setSubshellRelaxationProbabilities )
{
  std::vector<double> probabilities( 1 );
  probabilities[0] = 1.0;

  epr_data_container.setSubshellRelaxationProbabilities( 1, probabilities );

  FRENSIE_CHECK_EQUAL(
                    epr_data_container.getSubshellRelaxationProbabilities( 1 ),
                    probabilities );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile momentum grid can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setComptonProfileMomentumGrid )
{
  std::vector<double> compton_profile_momentum_grid( 3 );
  compton_profile_momentum_grid[0] = -1.0;
  compton_profile_momentum_grid[1] = 0.0;
  compton_profile_momentum_grid[2] = 1.0;

  epr_data_container.setComptonProfileMomentumGrid(
                                            1, compton_profile_momentum_grid );

  FRENSIE_CHECK_EQUAL( epr_data_container.getComptonProfileMomentumGrid( 1 ),
                       compton_profile_momentum_grid );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile for a subshell can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setComptonProfile )
{
  std::vector<double> compton_profile( 3 );
  compton_profile[0] = 1e-12;
  compton_profile[1] = 10.0;
  compton_profile[2] = 1e-12;

  epr_data_container.setComptonProfile( 1, compton_profile );

  FRENSIE_CHECK_EQUAL( epr_data_container.getComptonProfile( 1 ),
                       compton_profile );
}

//---------------------------------------------------------------------------//
// Check that the occupation number momentum grid can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setOccupationNumberMomentumGrid )
{
  std::vector<double> momentum_grid( 3 );
  momentum_grid[0] = -1.0;
  momentum_grid[1] = 0.0;
  momentum_grid[2] = 1.0;

  epr_data_container.setOccupationNumberMomentumGrid( 1, momentum_grid );

  FRENSIE_CHECK_EQUAL( epr_data_container.getOccupationNumberMomentumGrid( 1 ),
                       momentum_grid );
}

//---------------------------------------------------------------------------//
// Check that the occupation number for a subshell can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setOccupationNumber )
{
  std::vector<double> occupation_number( 3 );
  occupation_number[0] = 0.0;
  occupation_number[1] = 0.5;
  occupation_number[2] = 1.0;

  epr_data_container.setOccupationNumber( 1, occupation_number );

  FRENSIE_CHECK_EQUAL( epr_data_container.getOccupationNumber( 1 ),
                       occupation_number );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree scattering function momentum grid can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setWallerHartreeScatteringFunctionMomentumGrid )
{
  std::vector<double> momentum_grid( 4 );
  momentum_grid[0] = 1e-30;
  momentum_grid[1] = 1.0;
  momentum_grid[2] = 10.0;
  momentum_grid[3] = 1e8;

  epr_data_container.setWallerHartreeScatteringFunctionMomentumGrid(
                                                               momentum_grid );

  FRENSIE_CHECK_EQUAL( epr_data_container.getWallerHartreeScatteringFunctionMomentumGrid(),
                       momentum_grid );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree scattering function can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setWallerHartreeScatteringFunction )
{
  std::vector<double> scattering_function( 4 );
  scattering_function[0] = 1e-30;
  scattering_function[1] = 1e-3;
  scattering_function[2] = 0.1;
  scattering_function[3] = 1.0;

  epr_data_container.setWallerHartreeScatteringFunction( scattering_function );

  FRENSIE_CHECK_EQUAL( epr_data_container.getWallerHartreeScatteringFunction(),
                       scattering_function );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree atomic form factor momentum grid can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setWallerHartreeAtomicFormFactorMomentumGrid )
{
  std::vector<double> momentum_grid( 4 );
  momentum_grid[0] = 0.0;
  momentum_grid[1] = 1.0;
  momentum_grid[2] = 10.0;
  momentum_grid[3] = 1e8;

  epr_data_container.setWallerHartreeAtomicFormFactorMomentumGrid(
                                                               momentum_grid );

  FRENSIE_CHECK_EQUAL( epr_data_container.getWallerHartreeAtomicFormFactorMomentumGrid(),
                       momentum_grid );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree atomic form factor can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setWallerHartreeAtomicFormFactor )
{
  std::vector<double> form_factor( 4 );
  form_factor[0] = 1.0;
  form_factor[1] = 1.0;
  form_factor[2] = 0.3;
  form_factor[3] = 0.0;

  epr_data_container.setWallerHartreeAtomicFormFactor( form_factor );

  FRENSIE_CHECK_EQUAL( epr_data_container.getWallerHartreeAtomicFormFactor(),
                       form_factor );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree atomic form factor momentum grid can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid )
{
  std::vector<double> squared_momentum_grid( 4 );
  squared_momentum_grid[0] = 0.0;
  squared_momentum_grid[1] = 1.0;
  squared_momentum_grid[2] = 100.0;
  squared_momentum_grid[3] = 1e16;

  epr_data_container.setWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid(
                                                       squared_momentum_grid );

  FRENSIE_CHECK_EQUAL( epr_data_container.getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid(),
                       squared_momentum_grid );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree atomic form factor can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setWallerHartreeSquaredAtomicFormFactor )
{
  std::vector<double> squared_form_factor( 4 );
  squared_form_factor[0] = 1.0;
  squared_form_factor[1] = 1.0;
  squared_form_factor[2] = 0.09;
  squared_form_factor[3] = 0.0;

  epr_data_container.setWallerHartreeSquaredAtomicFormFactor( squared_form_factor );

  FRENSIE_CHECK_EQUAL( epr_data_container.getWallerHartreeSquaredAtomicFormFactor(),
                       squared_form_factor );
}

//---------------------------------------------------------------------------//
// Check that the photon energy grid can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setPhotonEnergyGrid )
{
  std::vector<double> photon_energy_grid( 3 );
  photon_energy_grid[0] = 1e-3;
  photon_energy_grid[1] = 1.0;
  photon_energy_grid[2] = 20.0;

  epr_data_container.setPhotonEnergyGrid( photon_energy_grid );

  FRENSIE_CHECK_EQUAL( epr_data_container.getPhotonEnergyGrid(),
                       photon_energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the has average heating numbers flag can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setHasAveragePhotonHeatingNumbers )
{
  epr_data_container.setHasAveragePhotonHeatingNumbers( false );

  FRENSIE_CHECK_EQUAL( epr_data_container.hasAveragePhotonHeatingNumbers(),
                       false );

  epr_data_container.setHasAveragePhotonHeatingNumbers( true );

  FRENSIE_CHECK_EQUAL( epr_data_container.hasAveragePhotonHeatingNumbers(),
                       true );
}

//---------------------------------------------------------------------------//
// Check that the average heating numbers can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setAveragePhotonHeatingNumbers )
{
  std::vector<double> heating_numbers( 3 );
  heating_numbers[0] = 1e-6;
  heating_numbers[1] = 1e-3;
  heating_numbers[2] = 1.0;

  epr_data_container.setAveragePhotonHeatingNumbers( heating_numbers );

  FRENSIE_CHECK_EQUAL( epr_data_container.getAveragePhotonHeatingNumbers(),
                       heating_numbers );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree incoherent cross section can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setWallerHartreeIncoherentCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setWallerHartreeIncoherentCrossSection( cross_section );

  FRENSIE_CHECK_EQUAL( epr_data_container.getWallerHartreeIncoherentCrossSection(),
                       cross_section );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree incoherent cs threshold index can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setWallerHartreeIncoherentCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setWallerHartreeIncoherentCrossSectionThresholdEnergyIndex( 0 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(),
                       0 );
}

//---------------------------------------------------------------------------//
// Check that the impulse approx. incoherent cross section can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setImpulseApproxIncoherentCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setImpulseApproxIncoherentCrossSection( cross_section );

  FRENSIE_CHECK_EQUAL( epr_data_container.getImpulseApproxIncoherentCrossSection(),
                       cross_section );
}

//---------------------------------------------------------------------------//
// Check that the impulse approx. incoherent cs threshold index can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setImpulseApproxIncoherentCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setImpulseApproxIncoherentCrossSectionThresholdEnergyIndex( 0 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the impulse approx. subshell incoherent cross section can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setImpulseApproxSubshellIncoherentCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setImpulseApproxSubshellIncoherentCrossSection( 1, cross_section );

  FRENSIE_CHECK_EQUAL( epr_data_container.getImpulseApproxSubshellIncoherentCrossSection( 1 ),
                       cross_section );
}

//---------------------------------------------------------------------------//
// Check that the impulse approx. subshell incoh. cs threshold index can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex( 1, 0 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex( 1 ),
                       0 );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree coherent cross section can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setWallerHartreeCoherentCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setWallerHartreeCoherentCrossSection( cross_section );

  FRENSIE_CHECK_EQUAL( epr_data_container.getWallerHartreeCoherentCrossSection(),
                       cross_section );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree coherent cs threshold energy index can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setWallerHartreeCoherentCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setWallerHartreeCoherentCrossSectionThresholdEnergyIndex( 0 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex(),
                       0 );
}

//---------------------------------------------------------------------------//
// Check that the pair production cross section can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setPairProductionCrossSection )
{
  std::vector<double> cross_section( 2 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1.0;

  epr_data_container.setPairProductionCrossSection( cross_section );

  FRENSIE_CHECK_EQUAL( epr_data_container.getPairProductionCrossSection(),
                       cross_section );
}

//---------------------------------------------------------------------------//
// Check that the pair production cross section threshold index can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setPairProductionCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setPairProductionCrossSectionThresholdEnergyIndex( 1 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getPairProductionCrossSectionThresholdEnergyIndex(),
                       1 );
}

//---------------------------------------------------------------------------//
// Check that the triplet production cross section can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setTripletProductionCrossSection )
{
  std::vector<double> cross_section( 2 );
  cross_section[0] = 1e-12;
  cross_section[1] = 2.0;

  epr_data_container.setTripletProductionCrossSection( cross_section );

  FRENSIE_CHECK_EQUAL( epr_data_container.getTripletProductionCrossSection(),
                       cross_section );
}

//---------------------------------------------------------------------------//
// Check that the triplet production cross section threshold index can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setTripletProductionCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setTripletProductionCrossSectionThresholdEnergyIndex( 1 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getTripletProductionCrossSectionThresholdEnergyIndex(),
                       1 );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric effect cross section can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setPhotoelectricCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setPhotoelectricCrossSection( cross_section );

  FRENSIE_CHECK_EQUAL( epr_data_container.getPhotoelectricCrossSection(),
                       cross_section );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric effect cs threshold energy index can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setPhotoelectricCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setPhotoelectricCrossSectionThresholdEnergyIndex( 0u );

  FRENSIE_CHECK_EQUAL( epr_data_container.getPhotoelectricCrossSectionThresholdEnergyIndex(),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the subshell photoelectric effect cross section can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setSubshellPhotoelectricCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setSubshellPhotoelectricCrossSection( 1, cross_section );

  FRENSIE_CHECK_EQUAL( epr_data_container.getSubshellPhotoelectricCrossSection( 1 ),
                       cross_section );
}

//---------------------------------------------------------------------------//
// Check that the subshell photoelectric effect cs threshold index can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setSubshellPhotoelectricCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setSubshellPhotoelectricCrossSectionThresholdEnergyIndex( 1, 0u );

  FRENSIE_CHECK_EQUAL( epr_data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex( 1 ),
                       0u );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree total cross section can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setWallerHartreeTotalCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setWallerHartreeTotalCrossSection( cross_section );

  FRENSIE_CHECK_EQUAL( epr_data_container.getWallerHartreeTotalCrossSection(),
                       cross_section );
}

//---------------------------------------------------------------------------//
// Check that the impulse approx. total cross section can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setImpulseApproxTotalCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setImpulseApproxTotalCrossSection( cross_section );

  FRENSIE_CHECK_EQUAL( epr_data_container.getImpulseApproxTotalCrossSection(),
                       cross_section );
}

//---------------------------------------------------------------------------//
// ELECTRON TESTS
//---------------------------------------------------------------------------//
// Check that the electron TwoDInterpPolicy can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setElectronTwoDInterpPolicy )
{
  std::string interp = "Lin-Lin-Lin";
  epr_data_container.setElectronTwoDInterpPolicy( interp );

  FRENSIE_CHECK_EQUAL( interp,
                       epr_data_container.getElectronTwoDInterpPolicy() );
}

//---------------------------------------------------------------------------//
// Check that the electron TwoDGridPolicy can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setElectronTwoDGridPolicy )
{
  std::string grid = "Unit-base Correlated";
  epr_data_container.setElectronTwoDGridPolicy( grid );

  FRENSIE_CHECK_EQUAL( grid,
                       epr_data_container.getElectronTwoDGridPolicy() );
}

//---------------------------------------------------------------------------//
// Check that the angular energy grid can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setElasticAngularEnergyGrid )
{
  std::vector<double> angular_energy_grid(1), grid(1);
  angular_energy_grid[0] = 1.0;

  epr_data_container.setElasticAngularEnergyGrid(
                                    angular_energy_grid );

  grid = epr_data_container.getElasticAngularEnergyGrid();
  FRENSIE_CHECK_EQUAL( grid[0], angular_energy_grid[0] );
}

//---------------------------------------------------------------------------//
// Check that the cutoff elastic InterpPolicy can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setCutoffElasticInterpPolicy )
{
  std::string interp = "Lin-Lin";
  epr_data_container.setCutoffElasticInterpPolicy( interp );

  FRENSIE_CHECK_EQUAL( interp,
                       epr_data_container.getCutoffElasticInterpPolicy() );
}

//---------------------------------------------------------------------------//
// Check that the elastic angles can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setCutoffElasticAnglesAtEnergy )
{
  std::vector<double> angles( 3 );
  angles[0] = -1.0;
  angles[1] = 0.0;
  angles[2] = 0.90;

  epr_data_container.setCutoffElasticAnglesAtEnergy( 1.0, angles );

  FRENSIE_CHECK_EQUAL( epr_data_container.getCutoffElasticAngles(1.0),
                       angles );
}

//---------------------------------------------------------------------------//
// Check that the elastic pdf can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setCutoffElasticPDFAtEnergy )
{
  std::vector<double> pdf( 3 );
  pdf[0] = 0.1;
  pdf[1] = 0.2;
  pdf[2] = 0.7;

  epr_data_container.setCutoffElasticPDFAtEnergy( 1.0, pdf );

  FRENSIE_CHECK_EQUAL( epr_data_container.getCutoffElasticPDF(1.0),
                       pdf );
}

//---------------------------------------------------------------------------//
// Check that the elastic angles can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setCutoffElasticAngles )
{
  std::vector<double> angles( 3 );
  angles[0] = -1.0;
  angles[1] = 0.0;
  angles[2] = 0.90;

  double energy = 1.0;
  std::map<double, std::vector<double> > angles_map, map;

  angles_map[energy] = angles;

  epr_data_container.setCutoffElasticAngles( angles_map );

  map = epr_data_container.getCutoffElasticAngles();

  FRENSIE_CHECK_EQUAL( map.find(1.0)->second,
                       angles );
}

//---------------------------------------------------------------------------//
// Check that the elastic pdf can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setCutoffElasticPDF )
{
  std::vector<double> pdf( 3 );
  pdf[0] = 0.1;
  pdf[1] = 0.2;
  pdf[2] = 0.7;

  double energy = 1.0;
  std::map<double, std::vector<double> > pdf_map, map;

  pdf_map[energy] = pdf;

  epr_data_container.setCutoffElasticPDF( pdf_map );

  map = epr_data_container.getCutoffElasticPDF();

  FRENSIE_CHECK_EQUAL( map.find(1.0)->second,
                       pdf );
}

////---------------------------------------------------------------------------//
//// Check that the screened Rutherford elastic normalization constant can be set
//FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
//                   setScreenedRutherfordNormalizationConstant )
//{
//  FRENSIE_CHECK( !epr_data_container.hasScreenedRutherfordData() );

//  std::vector<double> norm( 3 );
//  norm[0] = 100;
//  norm[1] = 200;
//  norm[2] = 700;

//  epr_data_container.setScreenedRutherfordNormalizationConstant( norm );

//  FRENSIE_CHECK_EQUAL( epr_data_container.getScreenedRutherfordNormalizationConstant(),
//                       norm );

//  FRENSIE_CHECK( epr_data_container.hasScreenedRutherfordData() );
//}

////---------------------------------------------------------------------------//
//// Check that Moliere's screening constant can be set
//FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
//                   setMoliereScreeningConstant )
//{
//  std::vector<double> eta( 3 );
//  eta[0] = 100;
//  eta[1] = 0.0;
//  eta[2] = 0.90;

//  epr_data_container.setMoliereScreeningConstant( eta );

//  FRENSIE_CHECK_EQUAL( epr_data_container.getMoliereScreeningConstant(),
//                       eta );
//}

//---------------------------------------------------------------------------//
// Check that the moment preserving elastic discrete angles can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setMomentPreservingElasticDiscreteAngles )
{
  FRENSIE_CHECK( !epr_data_container.hasMomentPreservingData() );

  std::vector<double> discrete_angles( 3 );
  discrete_angles[0] = 0.90;
  discrete_angles[1] = 0.95;
  discrete_angles[2] = 0.99;

  epr_data_container.setMomentPreservingElasticDiscreteAngles( 1.0,
                                                            discrete_angles );

  FRENSIE_CHECK_EQUAL( epr_data_container.getMomentPreservingElasticDiscreteAngles(1.0),
                       discrete_angles );

  FRENSIE_CHECK( epr_data_container.hasMomentPreservingData() );

  epr_data_container.clearMomentPreservingData();

  FRENSIE_CHECK( !epr_data_container.hasMomentPreservingData() );

  epr_data_container.setMomentPreservingElasticDiscreteAngles( 1.0,
                                                            discrete_angles );
}

//---------------------------------------------------------------------------//
// Check that the moment preserving elastic weights can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setMomentPreservingElasticWeights )
{
  std::vector<double> weights( 3 );
  weights[0] = 0.1;
  weights[1] = 0.2;
  weights[2] = 0.7;

  epr_data_container.setMomentPreservingElasticWeights( 1.0, weights );

  FRENSIE_CHECK_EQUAL( epr_data_container.getMomentPreservingElasticWeights(1.0),
                       weights );
}

//---------------------------------------------------------------------------//
// Check that the moment preserving elastic discrete angles can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setMomentPreservingCrossSectionReduction )
{
  FRENSIE_CHECK( epr_data_container.hasMomentPreservingData() );

  std::vector<double> reductions( 1 );
  reductions[0] = 0.90;

  epr_data_container.setMomentPreservingCrossSectionReduction( reductions );

  FRENSIE_CHECK_EQUAL( epr_data_container.getMomentPreservingCrossSectionReduction(),
                       reductions );
}

//---------------------------------------------------------------------------//
// Check that the electroionization energy grid can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setElectroionizationEnergyGrid )
{
  std::vector<double> energy_grid(2), grid(2);
  energy_grid[0] = 1.0;
  energy_grid[1] = 2.0;

  unsigned subshell = 1;

  epr_data_container.setElectroionizationEnergyGrid(
                                subshell,
                                energy_grid );

  FRENSIE_CHECK_EQUAL( epr_data_container.getElectroionizationEnergyGrid( subshell ),
                       energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the electroionization Recoil InterpPolicy can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setElectroionizationInterpPolicy )
{
  std::string interp = "Lin-Lin";
  epr_data_container.setElectroionizationInterpPolicy( interp );

  FRENSIE_CHECK_EQUAL( interp,
                       epr_data_container.getElectroionizationInterpPolicy() );
}

//---------------------------------------------------------------------------//
// Check that the electroionization recoil energy can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setElectroionizationRecoilEnergyAtIncomingEnergy )
{
  std::vector<double> recoil_energy( 3 );
  recoil_energy[0] = 0.01;
  recoil_energy[1] = 0.001;
  recoil_energy[2] = 0.0001;

  unsigned subshell = 1;
  double energy = 1.0;

  epr_data_container.setElectroionizationRecoilEnergyAtIncomingEnergy(
                                subshell,
                                energy,
                                recoil_energy );

  FRENSIE_CHECK_EQUAL( epr_data_container.getElectroionizationRecoilEnergy(subshell, energy),
                       recoil_energy );
}

//---------------------------------------------------------------------------//
// Check that the electroionization recoil pdf can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setElectroionizationRecoilPDFAtIncomingEnergy )
{
  std::vector<double> recoil_pdf( 3 );
  recoil_pdf[0] = 1.0;
  recoil_pdf[1] = 2.0;
  recoil_pdf[2] = 5.0;

  unsigned subshell = 1;
  double energy = 1.0;

  epr_data_container.setElectroionizationRecoilPDFAtIncomingEnergy(
                                subshell,
                                energy,
                                recoil_pdf );

  FRENSIE_CHECK_EQUAL( epr_data_container.getElectroionizationRecoilPDF( subshell, energy ),
                       recoil_pdf );
}

//---------------------------------------------------------------------------//
// Check that the electroionization recoil energy can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setElectroionizationRecoilEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.01;
  energy[1] = 0.001;
  energy[2] = 0.0001;

  unsigned subshell = 1;
  double energy_bin = 1.0;

  std::map<double,std::vector<double> > recoil_energy;

  recoil_energy[energy_bin] = energy;

  epr_data_container.setElectroionizationRecoilEnergy(
                                subshell,
                                recoil_energy );

  FRENSIE_CHECK_EQUAL(
    epr_data_container.getElectroionizationRecoilEnergy(subshell, energy_bin),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the electroionization recoil pdf can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setElectroionizationRecoilPDF )
{
  std::vector<double> pdf( 3 );
  pdf[0] = 1.0;
  pdf[1] = 2.0;
  pdf[2] = 5.0;

  unsigned subshell = 1;
  double energy_bin = 1.0;

  std::map<double,std::vector<double> > recoil_pdf;

  recoil_pdf[energy_bin] = pdf;

  epr_data_container.setElectroionizationRecoilPDF(
                                subshell,
                                recoil_pdf );

  FRENSIE_CHECK_EQUAL(
    epr_data_container.getElectroionizationRecoilPDF( subshell, energy_bin ),
    pdf );
}

//---------------------------------------------------------------------------//
// Check that the electroionization outgoing energy can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setElectroionizationOutgoingEnergyAtIncomingEnergy )
{
  std::vector<double> outgoing_energy( 3 );
  outgoing_energy[0] = 0.9;
  outgoing_energy[1] = 0.5;
  outgoing_energy[2] = 0.1;

  unsigned subshell = 1;
  double energy = 1.0;

  epr_data_container.setElectroionizationOutgoingEnergyAtIncomingEnergy(
                                subshell,
                                energy,
                                outgoing_energy );

  FRENSIE_CHECK_EQUAL( epr_data_container.getElectroionizationOutgoingEnergy(subshell, energy),
                       outgoing_energy );
}

//---------------------------------------------------------------------------//
// Check that the electroionization outgoing energy pdf can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setElectroionizationOutgoingPDFAtIncomingEnergy )
{
  std::vector<double> outgoing_pdf( 3 );
  outgoing_pdf[0] = 1.0;
  outgoing_pdf[1] = 2.0;
  outgoing_pdf[2] = 5.0;

  unsigned subshell = 1;
  double energy = 1.0;

  epr_data_container.setElectroionizationOutgoingPDFAtIncomingEnergy(
                                subshell,
                                energy,
                                outgoing_pdf );

  FRENSIE_CHECK_EQUAL( epr_data_container.getElectroionizationOutgoingPDF( subshell, energy ),
                       outgoing_pdf );
}

//---------------------------------------------------------------------------//
// Check that the electroionization outgoing energy energy can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setElectroionizationOutgoingEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.9;
  energy[1] = 0.5;
  energy[2] = 0.1;

  unsigned subshell = 1;
  double energy_bin = 1.0;

  std::map<double,std::vector<double> > outgoing_energy;

  outgoing_energy[energy_bin] = energy;

  epr_data_container.setElectroionizationOutgoingEnergy(
                                subshell,
                                outgoing_energy );

  FRENSIE_CHECK_EQUAL(
    epr_data_container.getElectroionizationOutgoingEnergy(subshell, energy_bin),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the electroionization outgoing energy pdf can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setElectroionizationOutgoingPDF )
{
  std::vector<double> pdf( 3 );
  pdf[0] = 1.0;
  pdf[1] = 2.0;
  pdf[2] = 5.0;

  unsigned subshell = 1;
  double energy_bin = 1.0;

  std::map<double,std::vector<double> > outgoing_pdf;

  outgoing_pdf[energy_bin] = pdf;

  epr_data_container.setElectroionizationOutgoingPDF(
                                subshell,
                                outgoing_pdf );

  FRENSIE_CHECK_EQUAL(
    epr_data_container.getElectroionizationOutgoingPDF( subshell, energy_bin ),
    pdf );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung energy grid can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setBremsstrahlungEnergyGrid )
{
  std::vector<double> energy_grid(2), grid(2);
  energy_grid[0] = 1.0;
  energy_grid[1] = 2.0;

  epr_data_container.setBremsstrahlungEnergyGrid( energy_grid );

  FRENSIE_CHECK_EQUAL( epr_data_container.getBremsstrahlungEnergyGrid(),
                       energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung photon InterpPolicy can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setBremsstrahlungPhotonInterpPolicy )
{
  std::string interp = "Lin-Lin";
  epr_data_container.setBremsstrahlungPhotonInterpPolicy( interp );

  FRENSIE_CHECK_EQUAL( interp,
                       epr_data_container.getBremsstrahlungPhotonInterpPolicy() );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung photon energy can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setBremsstrahlungPhotonEnergyAtIncomingEnergy )
{
  std::vector<double> photon_energy( 3 );
  photon_energy[0] = 0.01;
  photon_energy[1] = 0.001;
  photon_energy[2] = 0.0001;

  epr_data_container.setBremsstrahlungPhotonEnergyAtIncomingEnergy( 1.0,
                                                                   photon_energy );

  FRENSIE_CHECK_EQUAL( epr_data_container.getBremsstrahlungPhotonEnergy(1.0),
                       photon_energy );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung photon pdf can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setBremsstrahlungPhotonPDFAtIncomingEnergy )
{
  std::vector<double> photon_pdf( 3 );
  photon_pdf[0] = 1.0;
  photon_pdf[1] = 2.0;
  photon_pdf[2] = 5.0;

  epr_data_container.setBremsstrahlungPhotonPDFAtIncomingEnergy( 1.0,
                                                                photon_pdf );

  FRENSIE_CHECK_EQUAL( epr_data_container.getBremsstrahlungPhotonPDF(1.0),
                       photon_pdf );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung photon energy can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setBremsstrahlungPhotonEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.01;
  energy[1] = 0.001;
  energy[2] = 0.0001;

  double energy_bin = 1.0;

  std::map<double,std::vector<double> > photon_energy;

  photon_energy[energy_bin] = energy;

  epr_data_container.setBremsstrahlungPhotonEnergy( photon_energy );

  FRENSIE_CHECK_EQUAL( epr_data_container.getBremsstrahlungPhotonEnergy(energy_bin),
                       energy );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung photon pdf can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setBremsstrahlungPhotonPDF )
{
  std::vector<double> pdf( 3 );
  pdf[0] = 1.0;
  pdf[1] = 2.0;
  pdf[2] = 5.0;

  double energy_bin = 1.0;

  std::map<double,std::vector<double> > photon_pdf;

  photon_pdf[energy_bin] = pdf;

  epr_data_container.setBremsstrahlungPhotonPDF( photon_pdf );

  FRENSIE_CHECK_EQUAL( epr_data_container.getBremsstrahlungPhotonPDF(energy_bin),
                       pdf );
}

//---------------------------------------------------------------------------//
// Check that the atomic excitation energy grid can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setAtomicExcitationEnergyGrid )
{
  std::vector<double> energy_grid(3);
  energy_grid[0] = 1.0;
  energy_grid[1] = 5.0;
  energy_grid[2] = 10.0;

  epr_data_container.setAtomicExcitationEnergyGrid(
                                    energy_grid );

  FRENSIE_CHECK_EQUAL( epr_data_container.getAtomicExcitationEnergyGrid(),
                       energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the atomic excitation energy loss InterpPolicy can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setAtomicExcitationEnergyLossInterpPolicy )
{
  std::string interp = "Lin-Lin";
  epr_data_container.setAtomicExcitationEnergyLossInterpPolicy( interp );

  FRENSIE_CHECK_EQUAL( interp,
                       epr_data_container.getAtomicExcitationEnergyLossInterpPolicy() );
}

//---------------------------------------------------------------------------//
// Check that the atomic excitation energy loss can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setAtomicExcitationEnergyLoss )
{
  std::vector<double> energy_loss(3);
  energy_loss[0] = 1.0;
  energy_loss[1] = 5.0;
  energy_loss[2] = 10.0;

  epr_data_container.setAtomicExcitationEnergyLoss(
                                    energy_loss );

  FRENSIE_CHECK_EQUAL( epr_data_container.getAtomicExcitationEnergyLoss(),
                       energy_loss );
}

//---------------------------------------------------------------------------//
// Check that the electron energy grid can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setElectronEnergyGrid )
{
  std::vector<double> electron_energy_grid( 3 );
  electron_energy_grid[0] = 1e-3;
  electron_energy_grid[1] = 1.0;
  electron_energy_grid[2] = 20.0;

  epr_data_container.setElectronEnergyGrid( electron_energy_grid );

  FRENSIE_CHECK_EQUAL( epr_data_container.getElectronEnergyGrid(),
                       electron_energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the electron cross section InterpPolicy can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setElectronCrossSectionInterpPolicy )
{
  std::string interp = "Lin-Lin";
  epr_data_container.setElectronCrossSectionInterpPolicy( interp );

  FRENSIE_CHECK_EQUAL( interp,
                       epr_data_container.getElectronCrossSectionInterpPolicy() );
}

//---------------------------------------------------------------------------//
// Check that the total electron electron cross section can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setTotalElectronCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setTotalElectronCrossSection(
                        cross_section );

  FRENSIE_CHECK_EQUAL(
            epr_data_container.getTotalElectronCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the cutoff elastic electron cross section can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setCutoffElasticCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 0.5e-6;
  cross_section[1] = 0.5e-1;
  cross_section[2] = 0.5;

  epr_data_container.setCutoffElasticCrossSection(
                        cross_section );

  FRENSIE_CHECK_EQUAL(
            epr_data_container.getCutoffElasticCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the elastic cs threshold index can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setCutoffElasticCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setCutoffElasticCrossSectionThresholdEnergyIndex( 0 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getCutoffElasticCrossSectionThresholdEnergyIndex(),
                       0 );
}

//---------------------------------------------------------------------------//
// Check that the screened rutherford elastic electron cross section can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setScreenedRutherfordElasticCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 0.6e-6;
  cross_section[1] = 0.6e-1;
  cross_section[2] = 0.6;

  epr_data_container.setScreenedRutherfordElasticCrossSection(
                        cross_section );

  FRENSIE_CHECK_EQUAL(
            epr_data_container.getScreenedRutherfordElasticCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the elastic cs threshold index can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setScreenedRutherfordElasticCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setScreenedRutherfordElasticCrossSectionThresholdEnergyIndex( 0 );

  FRENSIE_CHECK_EQUAL(
    epr_data_container.getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(),
    0 );
}

//---------------------------------------------------------------------------//
// Check that the total elastic electron cross section can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setTotalElasticCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setTotalElasticCrossSection(
                        cross_section );

  FRENSIE_CHECK_EQUAL(
            epr_data_container.getTotalElasticCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the elastic cs threshold index can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setTotalElasticCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setTotalElasticCrossSectionThresholdEnergyIndex( 0 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getTotalElasticCrossSectionThresholdEnergyIndex(),
                       0 );
}

//---------------------------------------------------------------------------//
// Check that the electroionization electron cross section can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setElectroionizationCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  unsigned subshell = 1;

  epr_data_container.setElectroionizationCrossSection(
                        subshell,
                        cross_section );

  FRENSIE_CHECK_EQUAL(
            epr_data_container.getElectroionizationCrossSection( subshell ),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the electroionization cs threshold index can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setElectroionizationCrossSectionThresholdEnergyIndex )
{
  unsigned subshell = 1;

  epr_data_container.setElectroionizationCrossSectionThresholdEnergyIndex( subshell, 0 );

  FRENSIE_CHECK_EQUAL(
    epr_data_container.getElectroionizationCrossSectionThresholdEnergyIndex( subshell ),
    0 );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung electron cross section can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setBremsstrahlungCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setBremsstrahlungCrossSection(
                        cross_section );

  FRENSIE_CHECK_EQUAL(
            epr_data_container.getBremsstrahlungCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung cs threshold index can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setBremsstrahlungCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setBremsstrahlungCrossSectionThresholdEnergyIndex( 0 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getBremsstrahlungCrossSectionThresholdEnergyIndex(),
                       0 );
}

//---------------------------------------------------------------------------//
// Check that the atomic excitation electron cross section can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setAtomicExcitationCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setAtomicExcitationCrossSection(
                        cross_section );

  FRENSIE_CHECK_EQUAL(
            epr_data_container.getAtomicExcitationCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the atomic excitation cs threshold index can be set
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   setAtomicExcitationCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setAtomicExcitationCrossSectionThresholdEnergyIndex( 0 );

  FRENSIE_CHECK_EQUAL( epr_data_container.getAtomicExcitationCrossSectionThresholdEnergyIndex(),
                       0 );
}

//---------------------------------------------------------------------------//
// Check that the data can be exported and imported
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   export_importData_ascii )
{
  const std::string test_ascii_file_name( "test_epr_data_container.txt" );

  epr_data_container.saveToFile( test_ascii_file_name, true );

  const Data::ElectronPhotonRelaxationDataContainer
    epr_data_container_copy( test_ascii_file_name );

  // Table Tests
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getNotes(), notes );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getAtomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getAtomicWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getMinPhotonEnergy(), 0.001 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getMaxPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getMinElectronEnergy(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getMaxElectronEnergy(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getOccupationNumberEvaluationTolerance(),
                       1e-4 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getSubshellIncoherentEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( epr_data_container.getPhotonThresholdEnergyNudgeFactor(),
                       1.01 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getCutoffAngleCosine(),
                       0.9 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getNumberOfMomentPreservingAngles(),
                       1 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getPhotonGridConvergenceTolerance(),
                       0.001 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getPhotonGridAbsoluteDifferenceTolerance(),
                       1e-42 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getPhotonGridDistanceTolerance(),
                       1e-15 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getElectronGridConvergenceTolerance(),
                       0.001 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getElectronGridAbsoluteDifferenceTolerance(),
                       1e-42 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getElectronGridDistanceTolerance(),
                       1e-15 );

  // Relaxation Tests
  FRENSIE_CHECK( epr_data_container_copy.getSubshells().count( 1 ) );
  FRENSIE_CHECK( !epr_data_container_copy.getSubshells().count( 0 ) );
  FRENSIE_CHECK( !epr_data_container_copy.getSubshells().count( 2 ) );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getSubshellOccupancy( 1 ), 1.0 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getSubshellBindingEnergy( 1 ),
                       1.361e-5 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getSubshellRelaxationTransitions(1),
                       1 );
  FRENSIE_CHECK( epr_data_container_copy.hasRelaxationData() );
  FRENSIE_CHECK( epr_data_container_copy.hasSubshellRelaxationData( 1 ) );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getSubshellRelaxationVacancies( 1 ).size(),
                       1 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getSubshellRelaxationParticleEnergies( 1 ).size(),
                       1 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getSubshellRelaxationProbabilities( 1 ).size(),
                       1 );

  // Photon Tests
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getComptonProfileMomentumGrid( 1 ).size(),
                       3 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getComptonProfile( 1 ).size(),
                       3 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getOccupationNumberMomentumGrid( 1 ).size(),
                       3 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getOccupationNumber( 1 ).size(),
                       3 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getWallerHartreeScatteringFunctionMomentumGrid().size(),
                       4 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getWallerHartreeScatteringFunction().size(),
                       4 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getWallerHartreeAtomicFormFactorMomentumGrid().size(),
                       4 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getWallerHartreeAtomicFormFactor().size(),
                       4 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid().size(),
                       4 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getWallerHartreeSquaredAtomicFormFactor().size(),
                       4 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getPhotonEnergyGrid().size(),
                       3 );
  FRENSIE_CHECK( epr_data_container.hasAveragePhotonHeatingNumbers() );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getAveragePhotonHeatingNumbers().size(),
                       3 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getWallerHartreeIncoherentCrossSection().size(),
                       3 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(),
                       0 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getImpulseApproxIncoherentCrossSection().size(),
                       3 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
                       0u );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getImpulseApproxSubshellIncoherentCrossSection( 1 ).size(),
                       3 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex( 1 ),
                       0 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getWallerHartreeCoherentCrossSection().size(),
                       3 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex(),
                       0 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getPairProductionCrossSection().size(),
                       2 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getPairProductionCrossSectionThresholdEnergyIndex(),
                       1 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getTripletProductionCrossSection().size(),
                       2 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getTripletProductionCrossSectionThresholdEnergyIndex(),
                       1 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getPhotoelectricCrossSection().size(),
                       3 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getPhotoelectricCrossSectionThresholdEnergyIndex(),
                       0u );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getSubshellPhotoelectricCrossSection( 1 ).size(),
                       3 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex( 1 ),
                       0u );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getWallerHartreeTotalCrossSection().size(),
                       3u );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getImpulseApproxTotalCrossSection().size(),
                       3u );

  // Electron Tests
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getCutoffAngleCosine(), 0.9 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getElasticAngularEnergyGrid().size(),
    1 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getElasticAngularEnergyGrid().front(),
    1.0 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getCutoffElasticAngles(1.0).size(), 3 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getCutoffElasticPDF(1.0).size(), 3 );
//  FRENSIE_CHECK( epr_data_container_copy.hasScreenedRutherfordData() );
//  FRENSIE_CHECK_EQUAL(
//    epr_data_container_copy.getScreenedRutherfordNormalizationConstant().size(), 3 );
//  FRENSIE_CHECK_EQUAL(
//    epr_data_container_copy.getMoliereScreeningConstant().size(), 3 );
  FRENSIE_CHECK( epr_data_container_copy.hasMomentPreservingData() );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getMomentPreservingCrossSectionReduction().size(), 1 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getMomentPreservingElasticDiscreteAngles(1.0).size(), 3 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getMomentPreservingElasticWeights(1.0).size(), 3 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getElectroionizationEnergyGrid(1u).size(),
    2 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getElectroionizationEnergyGrid(1u).front(),
    1.0 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getElectroionizationEnergyGrid(1u).back(),
    2.0 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getElectroionizationRecoilEnergy(1u, 1.0).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getElectroionizationRecoilPDF(1u, 1.0).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getElectroionizationOutgoingEnergy(1u, 1.0).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getElectroionizationOutgoingPDF(1u, 1.0).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getBremsstrahlungEnergyGrid().size(),
    2 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getBremsstrahlungEnergyGrid().front(),
    1.0 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getBremsstrahlungEnergyGrid().back(),
    2.0 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getBremsstrahlungPhotonEnergy(1.0).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getBremsstrahlungPhotonPDF(1.0).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getAtomicExcitationEnergyGrid().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getAtomicExcitationEnergyLoss().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getElectronEnergyGrid().size(), 3 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getTotalElectronCrossSection().size(),
                       3u );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getCutoffElasticCrossSection().size(),
                       3u );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getCutoffElasticCrossSectionThresholdEnergyIndex(),
                       0 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getScreenedRutherfordElasticCrossSection().size(),
                       3u );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(),
                       0 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getTotalElasticCrossSection().size(),
                       3u );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getTotalElasticCrossSectionThresholdEnergyIndex(),
                       0 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getElectroionizationCrossSection(1u).size(),
                       3u );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getElectroionizationCrossSectionThresholdEnergyIndex(1u),
                       0 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getBremsstrahlungCrossSection().size(),
                       3u );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getBremsstrahlungCrossSectionThresholdEnergyIndex(),
                       0 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getAtomicExcitationCrossSection().size(),
                       3u );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getAtomicExcitationCrossSectionThresholdEnergyIndex(),
                       0 );
}

//---------------------------------------------------------------------------//
// Check that the data can be exported and imported
FRENSIE_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
                   export_importData_xml )
{
  const std::string test_xml_file_name( "test_epr_data_container.xml" );

  epr_data_container.saveToFile( test_xml_file_name, true );

  const Data::ElectronPhotonRelaxationDataContainer
    epr_data_container_copy( test_xml_file_name );

  // Table Tests
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getNotes(), notes );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getAtomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getAtomicWeight(), 1.0 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getMinPhotonEnergy(), 0.001 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getMaxPhotonEnergy(), 20.0 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getMinElectronEnergy(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getMaxElectronEnergy(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getOccupationNumberEvaluationTolerance(),
                       1e-4 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getSubshellIncoherentEvaluationTolerance(),
                       1e-3 );
  FRENSIE_CHECK_EQUAL( epr_data_container.getPhotonThresholdEnergyNudgeFactor(),
                       1.01 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getCutoffAngleCosine(),
                       0.9 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getNumberOfMomentPreservingAngles(),
                       1 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getPhotonGridConvergenceTolerance(),
                       0.001 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getPhotonGridAbsoluteDifferenceTolerance(),
                       1e-42 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getPhotonGridDistanceTolerance(),
                       1e-15 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getElectronGridConvergenceTolerance(),
                       0.001 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getElectronGridAbsoluteDifferenceTolerance(),
                       1e-42 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getElectronGridDistanceTolerance(),
                       1e-15 );

  // Relaxation Tests
  FRENSIE_CHECK( epr_data_container_copy.getSubshells().count( 1 ) );
  FRENSIE_CHECK( !epr_data_container_copy.getSubshells().count( 0 ) );
  FRENSIE_CHECK( !epr_data_container_copy.getSubshells().count( 2 ) );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getSubshellOccupancy( 1 ), 1.0 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getSubshellBindingEnergy( 1 ),
                       1.361e-5 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getSubshellRelaxationTransitions(1),
                       1 );
  FRENSIE_CHECK( epr_data_container_copy.hasRelaxationData() );
  FRENSIE_CHECK( epr_data_container_copy.hasSubshellRelaxationData( 1 ) );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getSubshellRelaxationVacancies( 1 ).size(),
                       1 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getSubshellRelaxationParticleEnergies( 1 ).size(),
                       1 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getSubshellRelaxationProbabilities( 1 ).size(),
                       1 );

  // Photon Tests
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getComptonProfileMomentumGrid( 1 ).size(),
                       3 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getComptonProfile( 1 ).size(),
                       3 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getOccupationNumberMomentumGrid( 1 ).size(),
                       3 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getOccupationNumber( 1 ).size(),
                       3 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getWallerHartreeScatteringFunctionMomentumGrid().size(),
                       4 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getWallerHartreeScatteringFunction().size(),
                       4 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getWallerHartreeAtomicFormFactorMomentumGrid().size(),
                       4 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getWallerHartreeAtomicFormFactor().size(),
                       4 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getWallerHartreeSquaredAtomicFormFactorSquaredMomentumGrid().size(),
                       4 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getWallerHartreeSquaredAtomicFormFactor().size(),
                       4 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getPhotonEnergyGrid().size(),
                       3 );
  FRENSIE_CHECK( epr_data_container.hasAveragePhotonHeatingNumbers() );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getAveragePhotonHeatingNumbers().size(),
                       3 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getWallerHartreeIncoherentCrossSection().size(),
                       3 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(),
                       0 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getImpulseApproxIncoherentCrossSection().size(),
                       3 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
                       0u );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getImpulseApproxSubshellIncoherentCrossSection( 1 ).size(),
                       3 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex( 1 ),
                       0 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getWallerHartreeCoherentCrossSection().size(),
                       3 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex(),
                       0 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getPairProductionCrossSection().size(),
                       2 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getPairProductionCrossSectionThresholdEnergyIndex(),
                       1 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getTripletProductionCrossSection().size(),
                       2 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getTripletProductionCrossSectionThresholdEnergyIndex(),
                       1 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getPhotoelectricCrossSection().size(),
                       3 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getPhotoelectricCrossSectionThresholdEnergyIndex(),
                       0u );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getSubshellPhotoelectricCrossSection( 1 ).size(),
                       3 );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex( 1 ),
                       0u );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getWallerHartreeTotalCrossSection().size(),
                       3u );
  FRENSIE_CHECK_EQUAL( epr_data_container_copy.getImpulseApproxTotalCrossSection().size(),
                       3u );

  // Electron Tests
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getCutoffAngleCosine(), 0.9 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getElasticAngularEnergyGrid().size(),
    1 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getElasticAngularEnergyGrid().front(),
    1.0 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getCutoffElasticAngles(1.0).size(), 3 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getCutoffElasticPDF(1.0).size(), 3 );
//  FRENSIE_CHECK( epr_data_container_copy.hasScreenedRutherfordData() );
//  FRENSIE_CHECK_EQUAL(
//    epr_data_container_copy.getScreenedRutherfordNormalizationConstant().size(), 3 );
//  FRENSIE_CHECK_EQUAL(
//    epr_data_container_copy.getMoliereScreeningConstant().size(), 3 );
  FRENSIE_CHECK( epr_data_container_copy.hasMomentPreservingData() );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getMomentPreservingCrossSectionReduction().size(), 1 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getMomentPreservingElasticDiscreteAngles(1.0).size(), 3 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getMomentPreservingElasticWeights(1.0).size(), 3 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getElectroionizationEnergyGrid(1u).size(),
    2 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getElectroionizationEnergyGrid(1u).front(),
    1.0 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getElectroionizationEnergyGrid(1u).back(),
    2.0 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getElectroionizationRecoilEnergy(1u, 1.0).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getElectroionizationRecoilPDF(1u, 1.0).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getElectroionizationOutgoingEnergy(1u, 1.0).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getElectroionizationOutgoingPDF(1u, 1.0).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getBremsstrahlungEnergyGrid().size(),
    2 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getBremsstrahlungEnergyGrid().front(),
    1.0 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getBremsstrahlungEnergyGrid().back(),
    2.0 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getBremsstrahlungPhotonEnergy(1.0).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getBremsstrahlungPhotonPDF(1.0).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getAtomicExcitationEnergyGrid().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getAtomicExcitationEnergyLoss().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getElectronEnergyGrid().size(), 3 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getTotalElectronCrossSection().size(),
                       3u );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getCutoffElasticCrossSection().size(),
                       3u );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getCutoffElasticCrossSectionThresholdEnergyIndex(),
                       0 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getScreenedRutherfordElasticCrossSection().size(),
                       3u );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(),
                       0 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getTotalElasticCrossSection().size(),
                       3u );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getTotalElasticCrossSectionThresholdEnergyIndex(),
                       0 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getElectroionizationCrossSection(1u).size(),
                       3u );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getElectroionizationCrossSectionThresholdEnergyIndex(1u),
                       0 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getBremsstrahlungCrossSection().size(),
                       3u );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getBremsstrahlungCrossSectionThresholdEnergyIndex(),
                       0 );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getAtomicExcitationCrossSection().size(),
                       3u );
  FRENSIE_CHECK_EQUAL(
    epr_data_container_copy.getAtomicExcitationCrossSectionThresholdEnergyIndex(),
                       0 );
}

//---------------------------------------------------------------------------//
// end tstElectronPhotonRelaxationDataContainer.cpp
//---------------------------------------------------------------------------//
