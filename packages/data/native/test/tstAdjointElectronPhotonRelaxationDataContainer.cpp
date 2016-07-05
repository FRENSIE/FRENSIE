//---------------------------------------------------------------------------//
//!
//! \file   tstAdjointElectronPhotonRelaxationDataContainer.cpp
//! \author Alex Robinson
//! \brief  Electron-photon-relaxation data container class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Data_AdjointElectronPhotonRelaxationVolatileDataContainer.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"


//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Data::AdjointElectronPhotonRelaxationVolatileDataContainer epr_data_container;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the atomic number can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer, setAtomicNumber )
{
  epr_data_container.setAtomicNumber( 1u );

  TEST_EQUALITY_CONST( epr_data_container.getAtomicNumber(), 1u );
}

//---------------------------------------------------------------------------//
// Check that the min photon energy can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer, setMinPhotonEnergy )
{
  epr_data_container.setMinPhotonEnergy( 0.001 );

  TEST_EQUALITY_CONST( epr_data_container.getMinPhotonEnergy(),
                       0.001 );
}

//---------------------------------------------------------------------------//
// Check that the max photon energy can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer, setMaxPhotonEnergy )
{
  epr_data_container.setMaxPhotonEnergy( 20.0 );

  TEST_EQUALITY_CONST( epr_data_container.getMaxPhotonEnergy(),
                       20.0 );
}

//---------------------------------------------------------------------------//
// Check that the min electron energy can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer, setMinElectronEnergy )
{
  epr_data_container.setMinElectronEnergy( 1.0e-5 );

  TEST_EQUALITY_CONST( epr_data_container.getMinElectronEnergy(),
                       1.0e-5 );
}

//---------------------------------------------------------------------------//
// Check that the max electron energy can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer, setMaxElectronEnergy )
{
  epr_data_container.setMaxElectronEnergy( 1.0e+5 );

  TEST_EQUALITY_CONST( epr_data_container.getMaxElectronEnergy(),
                       1.0e+5 );
}

//---------------------------------------------------------------------------//
// Check that the Cutoff Angle can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer, setCutoffAngleCosine )
{
  epr_data_container.setCutoffAngleCosine( 0.9 );

  TEST_EQUALITY_CONST( epr_data_container.getCutoffAngleCosine(),
                       0.9 );
}

//---------------------------------------------------------------------------//
// Check that the number of discrete moment preserving angles can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setNumberOfAdjointMomentPreservingAngles )
{
  epr_data_container.setNumberOfAdjointMomentPreservingAngles( 1 );

  TEST_EQUALITY_CONST( epr_data_container.getNumberOfAdjointMomentPreservingAngles(),
                       1 );
}

//---------------------------------------------------------------------------//
// Check that the grid convergence tolerance can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setGridConvergenceTolerance )
{
  epr_data_container.setGridConvergenceTolerance( 0.001 );

  TEST_EQUALITY_CONST( epr_data_container.getGridConvergenceTolerance(),
                       0.001 );
}

//---------------------------------------------------------------------------//
// Check that the grid absolute difference tolerance can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setGridAbsoluteDifferenceTolerance )
{
  epr_data_container.setGridAbsoluteDifferenceTolerance( 1e-42 );

  TEST_EQUALITY_CONST( epr_data_container.getGridAbsoluteDifferenceTolerance(),
                       1e-42 );
}

//---------------------------------------------------------------------------//
// Check that the grid distance tolerance can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setGridDistanceTolerance )
{
  epr_data_container.setGridDistanceTolerance( 1e-15 );

  TEST_EQUALITY_CONST( epr_data_container.getGridDistanceTolerance(),
                       1e-15 );
}

//---------------------------------------------------------------------------//
// Relaxation Tests
//---------------------------------------------------------------------------//
// Check that the subshells can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer, setSubshells )
{
  std::set<unsigned> subshells;
  subshells.insert( 1 );

  epr_data_container.setSubshells( subshells );

  TEST_ASSERT( epr_data_container.getSubshells().count( 1 ) );
  TEST_ASSERT( !epr_data_container.getSubshells().count( 0 ) );
  TEST_ASSERT( !epr_data_container.getSubshells().count( 2 ) );
}

//---------------------------------------------------------------------------//
// Check that the subshell occupancies can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
		   setSubshellOccupancy )
{
  epr_data_container.setSubshellOccupancy( 1, 1.0 );

  TEST_EQUALITY_CONST( epr_data_container.getSubshellOccupancy( 1 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the subshell binding energies can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
		   setSubshellBindingEnergy )
{
  epr_data_container.setSubshellBindingEnergy( 1, 1.361e-5 );

  TEST_EQUALITY_CONST( epr_data_container.getSubshellBindingEnergy( 1 ),
		       1.361e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of subshell relaxation transitions can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
		   hasAdjointRelaxationData )
{
  TEST_ASSERT( !epr_data_container.hasAdjointRelaxationData() );
}

//---------------------------------------------------------------------------//
// Photon Tests
//---------------------------------------------------------------------------//
// Check that the number of subshell relaxation transitions can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
		   hasAdjointPhotonData )
{
  TEST_ASSERT( !epr_data_container.hasAdjointPhotonData() );
}

//---------------------------------------------------------------------------//
// Electron Tests
//---------------------------------------------------------------------------//
// Check that the angular energy grid can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setAdjointElasticAngularEnergyGrid )
{
  std::vector<double> angular_energy_grid(1), grid(1);
  angular_energy_grid[0] = 1.0;

  epr_data_container.setAdjointElasticAngularEnergyGrid(
                                    angular_energy_grid );

  grid = epr_data_container.getAdjointElasticAngularEnergyGrid();
  TEST_EQUALITY_CONST( grid[0], angular_energy_grid[0] );
}

//---------------------------------------------------------------------------//
// Check that the elastic angles can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setAdjointCutoffElasticAnglesAtEnergy )
{
  std::vector<double> angles( 3 );
  angles[0] = -1.0;
  angles[1] = 0.0;
  angles[2] = 0.90;

  epr_data_container.setAdjointCutoffElasticAnglesAtEnergy( 1.0, angles );

  TEST_COMPARE_ARRAYS( epr_data_container.getAdjointCutoffElasticAngles(1.0),
                       angles );
}

//---------------------------------------------------------------------------//
// Check that the elastic pdf can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setAdjointCutoffElasticPDFAtEnergy )
{
  std::vector<double> pdf( 3 );
  pdf[0] = 0.1;
  pdf[1] = 0.2;
  pdf[2] = 0.7;

  epr_data_container.setAdjointCutoffElasticPDFAtEnergy( 1.0, pdf );

  TEST_COMPARE_ARRAYS( epr_data_container.getAdjointCutoffElasticPDF(1.0),
                       pdf );
}

//---------------------------------------------------------------------------//
// Check that the elastic angles can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setAdjointCutoffElasticAngles )
{
  std::vector<double> angles( 3 );
  angles[0] = -1.0;
  angles[1] = 0.0;
  angles[2] = 0.90;

  double energy = 1.0;
  std::map<double, std::vector<double> > angles_map, map;

  angles_map[energy] = angles;

  epr_data_container.setAdjointCutoffElasticAngles( angles_map );

  map = epr_data_container.getAdjointCutoffElasticAngles();

  TEST_COMPARE_ARRAYS( map.find(1.0)->second,
                       angles );
}

//---------------------------------------------------------------------------//
// Check that the elastic pdf can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setAdjointCutoffElasticPDF )
{
  std::vector<double> pdf( 3 );
  pdf[0] = 0.1;
  pdf[1] = 0.2;
  pdf[2] = 0.7;

  double energy = 1.0;
  std::map<double, std::vector<double> > pdf_map, map;

  pdf_map[energy] = pdf;

  epr_data_container.setAdjointCutoffElasticPDF( pdf_map );

  map = epr_data_container.getAdjointCutoffElasticPDF();

  TEST_COMPARE_ARRAYS( map.find(1.0)->second,
                       pdf );
}

//---------------------------------------------------------------------------//
// Check that the moment preserving elastic discrete angles can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setAdjointMomentPreservingElasticDiscreteAngles )
{
  TEST_ASSERT( !epr_data_container.hasAdjointMomentPreservingData() );

  std::vector<double> discrete_angles( 3 );
  discrete_angles[0] = 0.90;
  discrete_angles[1] = 0.95;
  discrete_angles[2] = 0.99;

  epr_data_container.setAdjointMomentPreservingElasticDiscreteAngles( 1.0,
                                                            discrete_angles );

  TEST_COMPARE_ARRAYS( epr_data_container.getAdjointMomentPreservingElasticDiscreteAngles(1.0),
                       discrete_angles );

  TEST_ASSERT( epr_data_container.hasAdjointMomentPreservingData() );
}

//---------------------------------------------------------------------------//
// Check that the moment preserving elastic weights can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setAdjointMomentPreservingElasticWeights )
{
  std::vector<double> weights( 3 );
  weights[0] = 0.1;
  weights[1] = 0.2;
  weights[2] = 0.7;

  epr_data_container.setAdjointMomentPreservingElasticWeights( 1.0, weights );

  TEST_COMPARE_ARRAYS( epr_data_container.getAdjointMomentPreservingElasticWeights(1.0),
                       weights );
}

//---------------------------------------------------------------------------//
// Check that the electroionization energy grid can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setAdjointElectroionizationEnergyGrid )
{
  std::vector<double> energy_grid(2), grid(2);
  energy_grid[0] = 1.0;
  energy_grid[1] = 2.0;

  unsigned subshell = 1;

  epr_data_container.setAdjointElectroionizationEnergyGrid(
                                subshell,
                                energy_grid );

  TEST_COMPARE_ARRAYS( epr_data_container.getAdjointElectroionizationEnergyGrid( subshell ),
                       energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the electroionization recoil energy can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setAdjointElectroionizationRecoilEnergyAtIncomingEnergy )
{
  std::vector<double> recoil_energy( 3 );
  recoil_energy[0] = 0.01;
  recoil_energy[1] = 0.001;
  recoil_energy[2] = 0.0001;

  unsigned subshell = 1;
  double energy = 1.0;

  epr_data_container.setAdjointElectroionizationRecoilEnergyAtIncomingEnergy(
                                subshell,
                                energy,
                                recoil_energy );

  TEST_COMPARE_ARRAYS( epr_data_container.getAdjointElectroionizationRecoilEnergy(subshell, energy),
                       recoil_energy );
}

//---------------------------------------------------------------------------//
// Check that the electroionization recoil pdf can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setAdjointElectroionizationRecoilPDFAtIncomingEnergy )
{
  std::vector<double> recoil_pdf( 3 );
  recoil_pdf[0] = 1.0;
  recoil_pdf[1] = 2.0;
  recoil_pdf[2] = 5.0;

  unsigned subshell = 1;
  double energy = 1.0;

  epr_data_container.setAdjointElectroionizationRecoilPDFAtIncomingEnergy(
                                subshell,
                                energy,
                                recoil_pdf );

  TEST_COMPARE_ARRAYS( epr_data_container.getAdjointElectroionizationRecoilPDF( subshell, energy ),
                       recoil_pdf );
}

//---------------------------------------------------------------------------//
// Check that the electroionization recoil energy can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setAdjointElectroionizationRecoilEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.01;
  energy[1] = 0.001;
  energy[2] = 0.0001;

  unsigned subshell = 1;
  double energy_bin = 1.0;

  std::map<double,std::vector<double> > recoil_energy;

  recoil_energy[energy_bin] = energy;

  epr_data_container.setAdjointElectroionizationRecoilEnergy(
                                subshell,
                                recoil_energy );

  TEST_COMPARE_ARRAYS(
    epr_data_container.getAdjointElectroionizationRecoilEnergy(subshell, energy_bin),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the electroionization recoil pdf can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setAdjointElectroionizationRecoilPDF )
{
  std::vector<double> pdf( 3 );
  pdf[0] = 1.0;
  pdf[1] = 2.0;
  pdf[2] = 5.0;

  unsigned subshell = 1;
  double energy_bin = 1.0;

  std::map<double,std::vector<double> > recoil_pdf;

  recoil_pdf[energy_bin] = pdf;

  epr_data_container.setAdjointElectroionizationRecoilPDF(
                                subshell,
                                recoil_pdf );

  TEST_COMPARE_ARRAYS(
    epr_data_container.getAdjointElectroionizationRecoilPDF( subshell, energy_bin ),
    pdf );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung energy grid can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setAdjointBremsstrahlungEnergyGrid )
{
  std::vector<double> energy_grid(2), grid(2);
  energy_grid[0] = 1.0;
  energy_grid[1] = 2.0;

  epr_data_container.setAdjointBremsstrahlungEnergyGrid( energy_grid );

  TEST_COMPARE_ARRAYS( epr_data_container.getAdjointBremsstrahlungEnergyGrid(),
                       energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung photon energy can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setAdjointBremsstrahlungPhotonEnergyAtIncomingEnergy )
{
  std::vector<double> photon_energy( 3 );
  photon_energy[0] = 0.01;
  photon_energy[1] = 0.001;
  photon_energy[2] = 0.0001;

  epr_data_container.setAdjointBremsstrahlungPhotonEnergyAtIncomingEnergy( 1.0,
                                                                   photon_energy );

  TEST_COMPARE_ARRAYS( epr_data_container.getAdjointBremsstrahlungPhotonEnergy(1.0),
                       photon_energy );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung photon pdf can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setAdjointBremsstrahlungPhotonPDFAtIncomingEnergy )
{
  std::vector<double> photon_pdf( 3 );
  photon_pdf[0] = 1.0;
  photon_pdf[1] = 2.0;
  photon_pdf[2] = 5.0;

  epr_data_container.setAdjointBremsstrahlungPhotonPDFAtIncomingEnergy( 1.0,
                                                                photon_pdf );

  TEST_COMPARE_ARRAYS( epr_data_container.getAdjointBremsstrahlungPhotonPDF(1.0),
                       photon_pdf );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung photon energy can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setAdjointBremsstrahlungPhotonEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.01;
  energy[1] = 0.001;
  energy[2] = 0.0001;

  double energy_bin = 1.0;

  std::map<double,std::vector<double> > photon_energy;

  photon_energy[energy_bin] = energy;

  epr_data_container.setAdjointBremsstrahlungPhotonEnergy( photon_energy );

  TEST_COMPARE_ARRAYS( epr_data_container.getAdjointBremsstrahlungPhotonEnergy(energy_bin),
                       energy );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung photon pdf can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setAdjointBremsstrahlungPhotonPDF )
{
  std::vector<double> pdf( 3 );
  pdf[0] = 1.0;
  pdf[1] = 2.0;
  pdf[2] = 5.0;

  double energy_bin = 1.0;

  std::map<double,std::vector<double> > photon_pdf;

  photon_pdf[energy_bin] = pdf;

  epr_data_container.setAdjointBremsstrahlungPhotonPDF( photon_pdf );

  TEST_COMPARE_ARRAYS( epr_data_container.getAdjointBremsstrahlungPhotonPDF(energy_bin),
                       pdf );
}

//---------------------------------------------------------------------------//
// Check that the atomic excitation energy grid can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setAdjointAtomicExcitationEnergyGrid )
{
  std::vector<double> energy_grid(3);
  energy_grid[0] = 1.0;
  energy_grid[1] = 5.0;
  energy_grid[2] = 10.0;

  epr_data_container.setAdjointAtomicExcitationEnergyGrid(
                                    energy_grid );

  TEST_COMPARE_ARRAYS( epr_data_container.getAdjointAtomicExcitationEnergyGrid(),
                       energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the atomic excitation energy gain can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setAdjointAtomicExcitationEnergyGain )
{
  std::vector<double> energy_gain(3);
  energy_gain[0] = 1.0;
  energy_gain[1] = 5.0;
  energy_gain[2] = 10.0;

  epr_data_container.setAdjointAtomicExcitationEnergyGain(
                                    energy_gain );

  TEST_COMPARE_ARRAYS( epr_data_container.getAdjointAtomicExcitationEnergyGain(),
                       energy_gain );
}

//---------------------------------------------------------------------------//
// Check that the electron energy grid can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setAdjointElectronEnergyGrid )
{
  std::vector<double> electron_energy_grid( 3 );
  electron_energy_grid[0] = 1e-3;
  electron_energy_grid[1] = 1.0;
  electron_energy_grid[2] = 20.0;

  epr_data_container.setAdjointElectronEnergyGrid( electron_energy_grid );

  TEST_COMPARE_ARRAYS( epr_data_container.getAdjointElectronEnergyGrid(),
                       electron_energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the cutoff elastic electron cross section can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setAdjointCutoffElasticCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 0.5e-6;
  cross_section[1] = 0.5e-1;
  cross_section[2] = 0.5;

  epr_data_container.setAdjointCutoffElasticCrossSection(
                        cross_section );

  TEST_COMPARE_ARRAYS(
            epr_data_container.getAdjointCutoffElasticCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the elastic cs threshold index can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
		           setAdjointCutoffElasticCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setAdjointCutoffElasticCrossSectionThresholdEnergyIndex( 0 );

  TEST_EQUALITY_CONST( epr_data_container.getAdjointCutoffElasticCrossSectionThresholdEnergyIndex(),
                       0 );
}

//---------------------------------------------------------------------------//
// Check that the screened rutherford elastic electron cross section can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setAdjointScreenedRutherfordElasticCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 0.6e-6;
  cross_section[1] = 0.6e-1;
  cross_section[2] = 0.6;

  epr_data_container.setAdjointScreenedRutherfordElasticCrossSection(
                        cross_section );

  TEST_COMPARE_ARRAYS(
            epr_data_container.getAdjointScreenedRutherfordElasticCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the elastic cs threshold index can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
		           setAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex( 0 );

  TEST_EQUALITY_CONST(
    epr_data_container.getAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(),
    0 );
}

//---------------------------------------------------------------------------//
// Check that the total elastic electron cross section can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setAdjointTotalElasticCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setAdjointTotalElasticCrossSection(
                        cross_section );

  TEST_COMPARE_ARRAYS(
            epr_data_container.getAdjointTotalElasticCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the elastic cs threshold index can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
		           setAdjointTotalElasticCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setAdjointTotalElasticCrossSectionThresholdEnergyIndex( 0 );

  TEST_EQUALITY_CONST( epr_data_container.getAdjointTotalElasticCrossSectionThresholdEnergyIndex(),
                       0 );
}

//---------------------------------------------------------------------------//
// Check that the Moment Preserving (MP) elastic electron cross section can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setAdjointMomentPreservingCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setAdjointMomentPreservingCrossSection(
                        cross_section );

  TEST_COMPARE_ARRAYS(
            epr_data_container.getAdjointMomentPreservingCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the Moment Preserving elastic cs threshold index can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
		        setAdjointMomentPreservingCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setAdjointMomentPreservingCrossSectionThresholdEnergyIndex( 0 );

  TEST_EQUALITY_CONST( epr_data_container.getAdjointMomentPreservingCrossSectionThresholdEnergyIndex(),
                       0 );
}

//---------------------------------------------------------------------------//
// Check that the electroionization electron cross section can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setAdjointElectroionizationCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  unsigned subshell = 1;

  epr_data_container.setAdjointElectroionizationCrossSection(
                        subshell,
                        cross_section );

  TEST_COMPARE_ARRAYS(
            epr_data_container.getAdjointElectroionizationCrossSection( subshell ),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the electroionization cs threshold index can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
		        setAdjointElectroionizationCrossSectionThresholdEnergyIndex )
{
  unsigned subshell = 1;

  epr_data_container.setAdjointElectroionizationCrossSectionThresholdEnergyIndex( subshell, 0 );

  TEST_EQUALITY_CONST(
    epr_data_container.getAdjointElectroionizationCrossSectionThresholdEnergyIndex( subshell ),
    0 );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung electron cross section can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setAdjointBremsstrahlungCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setAdjointBremsstrahlungCrossSection(
                        cross_section );

  TEST_COMPARE_ARRAYS(
            epr_data_container.getAdjointBremsstrahlungCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung cs threshold index can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
		        setAdjointBremsstrahlungCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setAdjointBremsstrahlungCrossSectionThresholdEnergyIndex( 0 );

  TEST_EQUALITY_CONST( epr_data_container.getAdjointBremsstrahlungCrossSectionThresholdEnergyIndex(),
                       0 );
}

//---------------------------------------------------------------------------//
// Check that the atomic excitation electron cross section can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   setAdjointAtomicExcitationCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setAdjointAtomicExcitationCrossSection(
                        cross_section );

  TEST_COMPARE_ARRAYS(
            epr_data_container.getAdjointAtomicExcitationCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the atomic excitation cs threshold index can be set
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
		        setAdjointAtomicExcitationCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setAdjointAtomicExcitationCrossSectionThresholdEnergyIndex( 0 );

  TEST_EQUALITY_CONST( epr_data_container.getAdjointAtomicExcitationCrossSectionThresholdEnergyIndex(),
                       0 );
}

//---------------------------------------------------------------------------//
// Check that the data can be exported and imported
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   export_importData_ascii )
{
  const std::string test_ascii_file_name( "test_epr_data_container.txt" );

  epr_data_container.exportData( test_ascii_file_name,
				 Utility::ArchivableObject::ASCII_ARCHIVE );

  const Data::AdjointElectronPhotonRelaxationDataContainer
    epr_data_container_copy( test_ascii_file_name,
			     Utility::ArchivableObject::ASCII_ARCHIVE );

  // Table Tests
  TEST_EQUALITY_CONST( epr_data_container_copy.getAtomicNumber(), 1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getMinPhotonEnergy(), 0.001 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getMaxPhotonEnergy(), 20.0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getMinElectronEnergy(), 1.0e-5 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getMaxElectronEnergy(), 1.0e5 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getCutoffAngleCosine(),
                       0.9 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getNumberOfAdjointMomentPreservingAngles(),
                       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getGridConvergenceTolerance(),
                       0.001 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getGridAbsoluteDifferenceTolerance(),
                       1e-42 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getGridDistanceTolerance(),
                       1e-15 );

  // Relaxation Tests
  TEST_ASSERT( epr_data_container_copy.getSubshells().count( 1 ) );
  TEST_ASSERT( !epr_data_container_copy.getSubshells().count( 0 ) );
  TEST_ASSERT( !epr_data_container_copy.getSubshells().count( 2 ) );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellOccupancy( 1 ), 1.0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellBindingEnergy( 1 ),
		       1.361e-5 );
  
  // Photon Tests
  TEST_ASSERT( !epr_data_container_copy.hasAdjointPhotonData() );

  // Electron Tests
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getCutoffAngleCosine(), 0.9 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElasticAngularEnergyGrid().size(),
    1 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElasticAngularEnergyGrid().front(),
    1.0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointCutoffElasticAngles(1.0).size(), 3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointCutoffElasticPDF(1.0).size(), 3 );
  TEST_ASSERT( epr_data_container_copy.hasAdjointMomentPreservingData() );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointMomentPreservingElasticDiscreteAngles(1.0).size(), 3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointMomentPreservingElasticWeights(1.0).size(), 3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElectroionizationEnergyGrid(1u).size(),
    2 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElectroionizationEnergyGrid(1u).front(),
    1.0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElectroionizationEnergyGrid(1u).back(),
    2.0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElectroionizationRecoilEnergy(1u, 1.0).size(),
    3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElectroionizationRecoilPDF(1u, 1.0).size(),
    3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointBremsstrahlungEnergyGrid().size(),
    2 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointBremsstrahlungEnergyGrid().front(),
    1.0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointBremsstrahlungEnergyGrid().back(),
    2.0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointBremsstrahlungPhotonEnergy(1.0).size(),
    3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointBremsstrahlungPhotonPDF(1.0).size(),
    3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointAtomicExcitationEnergyGrid().size(),
    3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointAtomicExcitationEnergyGain().size(),
    3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElectronEnergyGrid().size(), 3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointCutoffElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointCutoffElasticCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointScreenedRutherfordElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointTotalElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointTotalElasticCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointMomentPreservingCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointMomentPreservingCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElectroionizationCrossSection(1u).size(),
		       3u );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElectroionizationCrossSectionThresholdEnergyIndex(1u),
		       0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointBremsstrahlungCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointBremsstrahlungCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointAtomicExcitationCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointAtomicExcitationCrossSectionThresholdEnergyIndex(),
		       0 );
}

//---------------------------------------------------------------------------//
// Check that the data can be exported and imported
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
                   export_importData_xml )
{
  const std::string test_xml_file_name( "test_epr_data_container.xml" );

  epr_data_container.exportData( test_xml_file_name,
				 Utility::ArchivableObject::XML_ARCHIVE );

  const Data::AdjointElectronPhotonRelaxationDataContainer
    epr_data_container_copy( test_xml_file_name,
			     Utility::ArchivableObject::XML_ARCHIVE );

  // Table Tests
  TEST_EQUALITY_CONST( epr_data_container_copy.getAtomicNumber(), 1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getMinPhotonEnergy(), 0.001 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getMaxPhotonEnergy(), 20.0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getMinElectronEnergy(), 1.0e-5 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getMaxElectronEnergy(), 1.0e5 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getCutoffAngleCosine(),
                       0.9 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getNumberOfAdjointMomentPreservingAngles(),
                       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getGridConvergenceTolerance(),
                       0.001 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getGridAbsoluteDifferenceTolerance(),
                       1e-42 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getGridDistanceTolerance(),
                       1e-15 );

  // Relaxation Tests
  TEST_ASSERT( epr_data_container_copy.getSubshells().count( 1 ) );
  TEST_ASSERT( !epr_data_container_copy.getSubshells().count( 0 ) );
  TEST_ASSERT( !epr_data_container_copy.getSubshells().count( 2 ) );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellOccupancy( 1 ), 1.0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellBindingEnergy( 1 ),
		       1.361e-5 );

    TEST_ASSERT( !epr_data_container_copy.hasAdjointPhotonData() );

  // Electron Tests
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getCutoffAngleCosine(), 0.9 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElasticAngularEnergyGrid().size(),
    1 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElasticAngularEnergyGrid().front(),
    1.0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointCutoffElasticAngles(1.0).size(), 3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointCutoffElasticPDF(1.0).size(), 3 );
  TEST_ASSERT( epr_data_container_copy.hasAdjointMomentPreservingData() );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointMomentPreservingElasticDiscreteAngles(1.0).size(), 3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointMomentPreservingElasticWeights(1.0).size(), 3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElectroionizationEnergyGrid(1u).size(),
    2 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElectroionizationEnergyGrid(1u).front(),
    1.0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElectroionizationEnergyGrid(1u).back(),
    2.0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElectroionizationRecoilEnergy(1u, 1.0).size(),
    3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElectroionizationRecoilPDF(1u, 1.0).size(),
    3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointBremsstrahlungEnergyGrid().size(),
    2 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointBremsstrahlungEnergyGrid().front(),
    1.0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointBremsstrahlungEnergyGrid().back(),
    2.0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointBremsstrahlungPhotonEnergy(1.0).size(),
    3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointBremsstrahlungPhotonPDF(1.0).size(),
    3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointAtomicExcitationEnergyGrid().size(),
    3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointAtomicExcitationEnergyGain().size(),
    3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElectronEnergyGrid().size(), 3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointCutoffElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointCutoffElasticCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointScreenedRutherfordElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointTotalElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointTotalElasticCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointMomentPreservingCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointMomentPreservingCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElectroionizationCrossSection(1u).size(),
		       3u );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElectroionizationCrossSectionThresholdEnergyIndex(1u),
		       0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointBremsstrahlungCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointBremsstrahlungCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointAtomicExcitationCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointAtomicExcitationCrossSectionThresholdEnergyIndex(),
		       0 );
}

//---------------------------------------------------------------------------//
// Check that the data can be packed into a string and unpacked from a string
TEUCHOS_UNIT_TEST( AdjointElectronPhotonRelaxationDataContainer,
		   pack_unpackDataFromString )
{
  std::string packed_data = epr_data_container.packDataInString();

  Data::AdjointElectronPhotonRelaxationVolatileDataContainer epr_data_container_copy;

  epr_data_container_copy.unpackDataFromString( packed_data );

  // Table Tests
  TEST_EQUALITY_CONST( epr_data_container_copy.getAtomicNumber(), 1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getMinPhotonEnergy(), 0.001 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getMaxPhotonEnergy(), 20.0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getMinElectronEnergy(), 1.0e-5 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getMaxElectronEnergy(), 1.0e5 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getCutoffAngleCosine(),
                       0.9 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getNumberOfAdjointMomentPreservingAngles(),
                       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getGridConvergenceTolerance(),
                       0.001 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getGridAbsoluteDifferenceTolerance(),
                       1e-42 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getGridDistanceTolerance(),
                       1e-15 );

  // Relaxation Tests
  TEST_ASSERT( epr_data_container_copy.getSubshells().count( 1 ) );
  TEST_ASSERT( !epr_data_container_copy.getSubshells().count( 0 ) );
  TEST_ASSERT( !epr_data_container_copy.getSubshells().count( 2 ) );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellOccupancy( 1 ), 1.0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellBindingEnergy( 1 ),
		       1.361e-5 );

    TEST_ASSERT( !epr_data_container_copy.hasAdjointPhotonData() );

  // Electron Tests
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getCutoffAngleCosine(), 0.9 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElasticAngularEnergyGrid().size(),
    1 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElasticAngularEnergyGrid().front(),
    1.0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointCutoffElasticAngles(1.0).size(), 3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointCutoffElasticPDF(1.0).size(), 3 );
  TEST_ASSERT( epr_data_container_copy.hasAdjointMomentPreservingData() );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointMomentPreservingElasticDiscreteAngles(1.0).size(), 3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointMomentPreservingElasticWeights(1.0).size(), 3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElectroionizationEnergyGrid(1u).size(),
    2 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElectroionizationEnergyGrid(1u).front(),
    1.0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElectroionizationEnergyGrid(1u).back(),
    2.0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElectroionizationRecoilEnergy(1u, 1.0).size(),
    3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElectroionizationRecoilPDF(1u, 1.0).size(),
    3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointBremsstrahlungEnergyGrid().size(),
    2 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointBremsstrahlungEnergyGrid().front(),
    1.0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointBremsstrahlungEnergyGrid().back(),
    2.0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointBremsstrahlungPhotonEnergy(1.0).size(),
    3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointBremsstrahlungPhotonPDF(1.0).size(),
    3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointAtomicExcitationEnergyGrid().size(),
    3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointAtomicExcitationEnergyGain().size(),
    3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElectronEnergyGrid().size(), 3 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointCutoffElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointCutoffElasticCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointScreenedRutherfordElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointTotalElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointTotalElasticCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointMomentPreservingCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointMomentPreservingCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElectroionizationCrossSection(1u).size(),
		       3u );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointElectroionizationCrossSectionThresholdEnergyIndex(1u),
		       0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointBremsstrahlungCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointBremsstrahlungCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointAtomicExcitationCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST(
    epr_data_container_copy.getAdjointAtomicExcitationCrossSectionThresholdEnergyIndex(),
		       0 );
}

//---------------------------------------------------------------------------//
// end tstAdjointElectronPhotonRelaxationDataContainer.cpp
//---------------------------------------------------------------------------//
