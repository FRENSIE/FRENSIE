//---------------------------------------------------------------------------//
//!
//! \file   tstENDLDataContainer.cpp
//! \author Luke Kersting
//! \brief  The eedl container class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Data_ENDLVolatileDataContainer.hpp"
#include "Data_ENDLDataContainer.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"


//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Data::ENDLVolatileDataContainer endl_data_container;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the atomic number can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, setAtomicNumber )
{
  endl_data_container.setAtomicNumber( 1u );
  
  TEST_EQUALITY_CONST(
    endl_data_container.getAtomicNumber(), 1u );
}

//---------------------------------------------------------------------------//
// TEST RELAXATION DATA 
//---------------------------------------------------------------------------//
// Check that the subshells can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, setSubshells )
{
  std::set<unsigned> subshells;
  subshells.insert( 1 );
  subshells.insert( 3 );
  subshells.insert( 5 );

  endl_data_container.setSubshells( subshells );
  
  TEST_ASSERT( endl_data_container.getSubshells().count( 1 ) );
  TEST_ASSERT( endl_data_container.getSubshells().count( 3 ) );
  TEST_ASSERT( endl_data_container.getSubshells().count( 5 ) );
  TEST_ASSERT( !endl_data_container.getSubshells().count( 0 ) );
  TEST_ASSERT( !endl_data_container.getSubshells().count( 2 ) );
  TEST_ASSERT( !endl_data_container.getSubshells().count( 4 ) );
  TEST_ASSERT( !endl_data_container.getSubshells().count( 6 ) );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons in subshells can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, setSubshellNumberOfElectrons )
{
  std::map<unsigned,unsigned> number_of_electrons_map;

  unsigned number_of_electrons = 2;
  unsigned shell = 1;
  number_of_electrons_map[shell] = number_of_electrons;

  number_of_electrons = 4;
  shell = 3;
  number_of_electrons_map[shell] = number_of_electrons;

  endl_data_container.setSubshellNumberOfElectrons( number_of_electrons_map );

  TEST_EQUALITY_CONST( endl_data_container.getSubshellNumberOfElectrons( 1 ),
                       2 );
  TEST_EQUALITY_CONST( endl_data_container.getSubshellNumberOfElectrons( 3 ),
                       number_of_electrons );
}

//---------------------------------------------------------------------------//
// Check that the binding energy in subshells can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, setSubshellBindingEnergy )
{
  std::map<unsigned,double> energy_map;

  double energy = 0.1;
  unsigned shell = 1;
  energy_map[shell] = energy;

  energy = 0.2;
  shell = 3;
  energy_map[shell] = energy;

  endl_data_container.setSubshellBindingEnergy( energy_map );

  TEST_EQUALITY_CONST( endl_data_container.getSubshellBindingEnergy( 1 ),
                       0.1 );
  TEST_EQUALITY_CONST( endl_data_container.getSubshellBindingEnergy( 3 ),
                       energy );
}

//---------------------------------------------------------------------------//
// Check that the kinetic energy in subshells can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, setSubshellKineticEnergy )
{
  std::map<unsigned,double> energy_map;

  double energy = 0.1;
  unsigned shell = 1;
  energy_map[shell] = energy;

  energy = 0.2;
  shell = 3;
  energy_map[shell] = energy;

  endl_data_container.setSubshellKineticEnergy( energy_map );

  TEST_EQUALITY_CONST( endl_data_container.getSubshellKineticEnergy( 1 ),
                       0.1 );
  TEST_EQUALITY_CONST( endl_data_container.getSubshellKineticEnergy( 3 ),
                       energy );
}

//---------------------------------------------------------------------------//
// Check that the average radius in subshells can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, setSubshellAverageRadius )
{
  std::map<unsigned,double> radius_map;

  double radius = 0.1;
  unsigned shell = 1;
  radius_map[shell] = radius;

  radius = 0.2;
  shell = 3;
  radius_map[shell] = radius;

  endl_data_container.setSubshellAverageRadius( radius_map );

  TEST_EQUALITY_CONST( endl_data_container.getSubshellAverageRadius( 1 ),
                       0.1 );
  TEST_EQUALITY_CONST( endl_data_container.getSubshellAverageRadius( 3 ),
                       radius );
}

//---------------------------------------------------------------------------//
// Check that the radiative level width in subshells can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, setSubshellRadiativeLevel )
{
  std::map<unsigned,double> levels_map;

  double levels = 0.1;
  unsigned shell = 1;
  levels_map[shell] = levels;

  levels = 0.2;
  shell = 3;
  levels_map[shell] = levels;

  endl_data_container.setSubshellRadiativeLevel( levels_map );

  TEST_EQUALITY_CONST( endl_data_container.getSubshellRadiativeLevel( 1 ),
                       0.1 );
  TEST_EQUALITY_CONST( endl_data_container.getSubshellRadiativeLevel( 3 ),
                       levels );
}

//---------------------------------------------------------------------------//
// Check that the non radiative level width in subshells can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, setSubshellNonRadiativeLevel )
{
  std::map<unsigned,double> levels_map;

  double levels = 0.1;
  unsigned shell = 1;
  levels_map[shell] = levels;

  levels = 0.2;
  shell = 3;
  levels_map[shell] = levels;

  endl_data_container.setSubshellNonRadiativeLevel( levels_map );

  TEST_EQUALITY_CONST( endl_data_container.getSubshellNonRadiativeLevel( 1 ),
                       0.1 );
  TEST_EQUALITY_CONST( endl_data_container.getSubshellNonRadiativeLevel( 3 ),
                       levels );
}

//---------------------------------------------------------------------------//
// Check that the average energy to the residual atom can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, setLocalDepositionPerInitialVacancy )
{
  std::map<unsigned,double> deposition_map;

  double deposition = 0.1;
  unsigned shell = 1;
  deposition_map[shell] = deposition;

  deposition = 0.2;
  shell = 3;
  deposition_map[shell] = deposition;

  endl_data_container.setLocalDepositionPerInitialVacancy( deposition_map );

  TEST_EQUALITY_CONST( endl_data_container.getLocalDepositionPerInitialVacancy( 1 ),
                       0.1 );
  TEST_EQUALITY_CONST( endl_data_container.getLocalDepositionPerInitialVacancy( 3 ),
                       deposition );
}

//---------------------------------------------------------------------------//
// Check that the average number of particles can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, setAverageParticlesPerInitialVacancy )
{
  std::map<unsigned,unsigned> number_of_particles_map;

  unsigned number_of_particles = 2;
  unsigned shell = 1;
  number_of_particles_map[shell] = number_of_particles;

  number_of_particles = 4;
  shell = 3;
  number_of_particles_map[shell] = number_of_particles;

  endl_data_container.setAverageParticlesPerInitialVacancy( 
    number_of_particles_map );

  TEST_EQUALITY_CONST( 
    endl_data_container.getAverageParticlesPerInitialVacancy( 1 ),
    2 );
  TEST_EQUALITY_CONST( 
    endl_data_container.getAverageParticlesPerInitialVacancy( 3 ),
    number_of_particles );
}

//---------------------------------------------------------------------------//
// Check that the average energy of particles can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, setAverageParitcleEnergyPerInitialVacancy )
{
  std::map<unsigned,double> energy_map;

  double energy = 0.1;
  unsigned shell = 1;
  energy_map[shell] = energy;

  energy = 0.2;
  shell = 3;
  energy_map[shell] = energy;

  endl_data_container.setAverageParitcleEnergyPerInitialVacancy( energy_map );

  TEST_EQUALITY_CONST( 
    endl_data_container.getAverageParitcleEnergyPerInitialVacancy( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container.getAverageParitcleEnergyPerInitialVacancy( 3 ),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the radiative transition probability can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, setRadiativeTransitionProbability )
{
  std::map<unsigned,std::vector<double> > probability_map;

  std::vector<double> probability(3);
  probability[0] = 0.1;
  probability[0] = 0.2;
  probability[0] = 0.3;

  unsigned shell = 3;
  unsigned secondary_shell = 1;
  probability_map[secondary_shell] = probability;

  endl_data_container.setRadiativeTransitionProbability( shell, probability_map );

  TEST_COMPARE_ARRAYS( 
    endl_data_container.getRadiativeTransitionProbability( 
        shell,
        secondary_shell),
    probability );
}

//---------------------------------------------------------------------------//
// Check that the radiative transition energy can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, setRadiativeTransitionEnergy )
{
  std::map<unsigned,std::vector<double> > energy_map;

  std::vector<double> energy(3);
  energy[0] = 0.1;
  energy[0] = 0.2;
  energy[0] = 0.3;

  unsigned shell = 3;
  unsigned secondary_shell = 1;
  energy_map[secondary_shell] = energy;

  endl_data_container.setRadiativeTransitionEnergy( shell, energy_map );

  TEST_COMPARE_ARRAYS( 
    endl_data_container.getRadiativeTransitionEnergy( 
        shell,
        secondary_shell),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the non radiative transition probability can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, setNonRadiativeTransitionProbability )
{
  std::map<unsigned,std::vector<double> > probability_map;
  std::map<unsigned,std::map<unsigned,std::vector<double> > > probability_map_map;

  std::vector<double> probability(3);
  probability[0] = 0.1;
  probability[0] = 0.2;
  probability[0] = 0.3;

  unsigned shell = 5;
  unsigned secondary_shell = 3;
  unsigned tertiary_shell = 1;
  probability_map[tertiary_shell] = probability;
  probability_map_map[secondary_shell] = probability_map;

  endl_data_container.setNonRadiativeTransitionProbability( shell, probability_map_map );

  TEST_COMPARE_ARRAYS( 
    endl_data_container.getNonRadiativeTransitionProbability( 
        shell,
        secondary_shell,
        tertiary_shell),
    probability );
}

//---------------------------------------------------------------------------//
// Check that the non radiative transition energy can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, setNonRadiativeTransitionEnergy )
{
  std::map<unsigned,std::vector<double> > energy_map;
  std::map<unsigned,std::map<unsigned,std::vector<double> > > energy_map_map;

  std::vector<double> energy(3);
  energy[0] = 0.1;
  energy[0] = 0.2;
  energy[0] = 0.3;

  unsigned shell = 5;
  unsigned secondary_shell = 3;
  unsigned tertiary_shell = 1;
  energy_map[tertiary_shell] = energy;
  energy_map_map[secondary_shell] = energy_map;

  endl_data_container.setNonRadiativeTransitionEnergy( shell, energy_map_map );

  TEST_COMPARE_ARRAYS( 
    endl_data_container.getNonRadiativeTransitionEnergy( 
        shell,
        secondary_shell,
        tertiary_shell),
    energy );
}


//---------------------------------------------------------------------------//
// TEST ELASTIC DATA 
//---------------------------------------------------------------------------//

// Check that the elastic energy grid can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer,
                   setElasticEnergyGrid )
{
  std::vector<double> electron_energy_grid( 3 );
  electron_energy_grid[0] = 1e-3;
  electron_energy_grid[1] = 1.0;
  electron_energy_grid[2] = 20.0;

  endl_data_container.setElasticEnergyGrid( electron_energy_grid );

  TEST_COMPARE_ARRAYS( endl_data_container.getElasticEnergyGrid(),
                       electron_energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the elastic transport cross section can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer,
                   setElasticTransportCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 0.5e-6;
  cross_section[1] = 0.5e-1;
  cross_section[2] = 0.5;

  endl_data_container.setElasticTransportCrossSection( 
                        cross_section );

  TEST_COMPARE_ARRAYS( 
            endl_data_container.getElasticTransportCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the cutoff elastic electron cross section can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer,
                   setCutoffElasticCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 0.5e-6;
  cross_section[1] = 0.5e-1;
  cross_section[2] = 0.5;

  endl_data_container.setCutoffElasticCrossSection( 
                        cross_section );

  TEST_COMPARE_ARRAYS( 
            endl_data_container.getCutoffElasticCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the residual atom incoming energy grid can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
                   setCutoffElasticResidualIncomingEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  endl_data_container.setCutoffElasticResidualIncomingEnergy(
    energy );

  TEST_COMPARE_ARRAYS( 
    endl_data_container.getCutoffElasticResidualIncomingEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the cutoff elastic average energy to the residual atom can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
                   setCutoffElasticResidualEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.0;
  energy[1] = 0.1;
  energy[2] = 1.0;

  endl_data_container.setCutoffElasticResidualEnergy(
    energy );

  TEST_COMPARE_ARRAYS( 
    endl_data_container.getCutoffElasticResidualEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the scattered electron incoming energy grid can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
                   setCutoffElasticScatteredElectronIncomingEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  endl_data_container.setCutoffElasticScatteredElectronIncomingEnergy(
    energy );

  TEST_COMPARE_ARRAYS( 
    endl_data_container.getCutoffElasticScatteredElectronIncomingEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the average energy to the scattered electron can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
                   setCutoffElasticScatteredElectronEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.0;
  energy[1] = 0.1;
  energy[2] = 1.0;

  endl_data_container.setCutoffElasticScatteredElectronEnergy(
    energy );

  TEST_COMPARE_ARRAYS( 
    endl_data_container.getCutoffElasticScatteredElectronEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the cutoff elastic angular energy grid can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
                   setCutoffElasticAngularEnergyGrid )
{
  std::vector<double> angular_energy_grid(1), grid(1);
  angular_energy_grid[0] = 1.0;

  endl_data_container.setCutoffElasticAngularEnergyGrid( 
                                    angular_energy_grid );
  
  grid = endl_data_container.getCutoffElasticAngularEnergyGrid();
  TEST_EQUALITY_CONST( grid[0], angular_energy_grid[0] );
}

//---------------------------------------------------------------------------//
// Check that the elastic angles can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
                   setCutoffElasticAnglesAtEnergy )
{
  std::vector<double> angles( 3 );
  angles[0] = -1.0;
  angles[1] = 0.0;
  angles[2] = 0.90;

  endl_data_container.setCutoffElasticAnglesAtEnergy( 1.0, angles );

  TEST_COMPARE_ARRAYS( endl_data_container.getCutoffElasticAngles(1.0),
                       angles );
}

//---------------------------------------------------------------------------//
// Check that the elastic pdf can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
                   setCutoffElasticPDFAtEnergy )
{
  std::vector<double> pdf( 3 );
  pdf[0] = 0.1;
  pdf[1] = 0.2;
  pdf[2] = 0.7;

  endl_data_container.setCutoffElasticPDFAtEnergy( 1.0, pdf );

  TEST_COMPARE_ARRAYS( endl_data_container.getCutoffElasticPDF(1.0),
                       pdf );
}

//---------------------------------------------------------------------------//
// Check that the elastic angles can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
                   setCutoffElasticAngles )
{
  std::vector<double> angles( 3 );
  angles[0] = -1.0;
  angles[1] = 0.0;
  angles[2] = 0.90;

  double energy = 1.0;
  std::map<double, std::vector<double> > angles_map;

  angles_map[energy] = angles;

  endl_data_container.setCutoffElasticAngles( angles_map );

  TEST_COMPARE_ARRAYS( endl_data_container.getCutoffElasticAngles(1.0),
                       angles );
}

//---------------------------------------------------------------------------//
// Check that the elastic pdf can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
                   setCutoffElasticPDF )
{
  std::vector<double> pdf( 3 );
  pdf[0] = 0.1;
  pdf[1] = 0.2;
  pdf[2] = 0.7;
  
  double energy = 1.0;
  std::map<double, std::vector<double> > pdf_map;

  pdf_map[energy] = pdf;

  endl_data_container.setCutoffElasticPDF( pdf_map );

  TEST_COMPARE_ARRAYS( endl_data_container.getCutoffElasticPDF(1.0),
                       pdf );
}

//---------------------------------------------------------------------------//
// Check that the total elastic electron cross section can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer,
                   setTotalElasticCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  endl_data_container.setTotalElasticCrossSection( 
                        cross_section );

  TEST_COMPARE_ARRAYS( 
            endl_data_container.getTotalElasticCrossSection(),
            cross_section );
}

/*
//---------------------------------------------------------------------------//
// Check that the screened rutherford elastic electron cross section can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer,
                   setScreenedRutherfordElasticCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 0.6e-6;
  cross_section[1] = 0.6e-1;
  cross_section[2] = 0.6;

  endl_data_container.setScreenedRutherfordElasticCrossSection( 
                        cross_section );

  TEST_COMPARE_ARRAYS( 
            endl_data_container.getScreenedRutherfordElasticCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the screened Rutherford elastic normalization constant can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
                   setScreenedRutherfordNormalizationConstant )
{
  std::vector<double> norm( 3 );
  norm[0] = 100;
  norm[1] = 200;
  norm[2] = 700;

  endl_data_container.setScreenedRutherfordNormalizationConstant( norm );

  TEST_COMPARE_ARRAYS( endl_data_container.getScreenedRutherfordNormalizationConstant(),
                       norm );
}

//---------------------------------------------------------------------------//
// Check that Moliere's screening constant can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
                   setMoliereScreeningConstant )
{
  std::vector<double> eta( 3 );
  eta[0] = 100;
  eta[1] = 0.0;
  eta[2] = 0.90;

  endl_data_container.setMoliereScreeningConstant( eta );

  TEST_COMPARE_ARRAYS( endl_data_container.getMoliereScreeningConstant(),
                       eta );
}
*/


//---------------------------------------------------------------------------//
// TEST ELECTROIONIZATION DATA 
//---------------------------------------------------------------------------//

// Check that the electroionization cross section energy grid can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer,
                   setElectroionizationCrossSectionEnergyGrid )
{
  std::vector<double> electron_energy_grid( 3 );
  electron_energy_grid[0] = 1e-3;
  electron_energy_grid[1] = 1.0;
  electron_energy_grid[2] = 20.0;

  unsigned subshell = 1;

  endl_data_container.setElectroionizationCrossSectionEnergyGrid(
    subshell,
    electron_energy_grid );

  TEST_COMPARE_ARRAYS(
    endl_data_container.getElectroionizationCrossSectionEnergyGrid( subshell ),
    electron_energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the electroionization electron cross section can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer,
                   setElectroionizationCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  unsigned subshell = 1;

  endl_data_container.setElectroionizationCrossSection(
    subshell,
    cross_section );

  TEST_COMPARE_ARRAYS( 
    endl_data_container.getElectroionizationCrossSection( subshell ),
    cross_section );
}

//---------------------------------------------------------------------------//
// Check that the incoming energy grid for the electroionization scattered electron can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
                   setElectroionizationAverageScatteredElectronIncomingEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  unsigned subshell = 1;

  endl_data_container.setElectroionizationAverageScatteredElectronIncomingEnergy(
    subshell,
    energy );

  TEST_COMPARE_ARRAYS( 
    endl_data_container.getElectroionizationAverageScatteredElectronIncomingEnergy( subshell ),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the electroionization average scattered electron energy can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
                   setElectroionizationAverageScatteredElectronEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.0;
  energy[1] = 0.1;
  energy[2] = 1.0;

  unsigned subshell = 1;

  endl_data_container.setElectroionizationAverageScatteredElectronEnergy(
    subshell,
    energy );

  TEST_COMPARE_ARRAYS( 
    endl_data_container.getElectroionizationAverageScatteredElectronEnergy( subshell ),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the incoming energy grid for the electroionization recoil can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
                   setElectroionizationAverageRecoilElectronIncomingEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  unsigned subshell = 1;

  endl_data_container.setElectroionizationAverageRecoilElectronIncomingEnergy(
    subshell,
    energy );

  TEST_COMPARE_ARRAYS( 
    endl_data_container.getElectroionizationAverageRecoilElectronIncomingEnergy( subshell ),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the electroionization average recoil energy can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
                   setElectroionizationAverageRecoilElectronEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.0;
  energy[1] = 0.1;
  energy[2] = 1.0;

  unsigned subshell = 1;

  endl_data_container.setElectroionizationAverageRecoilElectronEnergy(
    subshell,
    energy );

  TEST_COMPARE_ARRAYS( 
    endl_data_container.getElectroionizationAverageRecoilElectronEnergy( subshell ),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the electroionization recoil energy grid can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
                   setElectroionizationRecoilEnergyGrid )
{
  std::vector<double> energy_grid(1), grid(1);
  energy_grid[0] = 1.0;

  unsigned subshell = 1;

  endl_data_container.setElectroionizationRecoilEnergyGrid( 
                                subshell,
                                energy_grid );
  
  TEST_COMPARE_ARRAYS( 
    endl_data_container.getElectroionizationRecoilEnergyGrid( subshell ), 
    energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the electroionization recoil energy can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
                   setElectroionizationRecoilEnergyAtIncomingEnergy )
{
  std::vector<double> recoil_energy( 3 );
  recoil_energy[0] = 0.01;
  recoil_energy[1] = 0.001;
  recoil_energy[2] = 0.0001;

  unsigned subshell = 1;
  double energy = 1.0;

  endl_data_container.setElectroionizationRecoilEnergyAtIncomingEnergy( 
                                subshell,
                                energy, 
                                recoil_energy );

  TEST_COMPARE_ARRAYS( endl_data_container.getElectroionizationRecoilEnergy(subshell, energy),
                       recoil_energy );
}

//---------------------------------------------------------------------------//
// Check that the electroionization recoil pdf can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
                   setElectroionizationRecoilPDFAtIncomingEnergy )
{
  std::vector<double> recoil_pdf( 3 );
  recoil_pdf[0] = 1.0;
  recoil_pdf[1] = 2.0;
  recoil_pdf[2] = 5.0;

  unsigned subshell = 1;
  double energy = 1.0;

  endl_data_container.setElectroionizationRecoilPDFAtIncomingEnergy(
                                subshell,
                                energy, 
                                recoil_pdf );

  TEST_COMPARE_ARRAYS( endl_data_container.getElectroionizationRecoilPDF( subshell, energy ),
                       recoil_pdf );
}

//---------------------------------------------------------------------------//
// Check that the electroionization recoil energy can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
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

  endl_data_container.setElectroionizationRecoilEnergy( 
                                subshell,
                                recoil_energy );

  TEST_COMPARE_ARRAYS( 
    endl_data_container.getElectroionizationRecoilEnergy(subshell, energy_bin),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the electroionization recoil pdf can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
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

  endl_data_container.setElectroionizationRecoilPDF(
                                subshell,
                                recoil_pdf );

  TEST_COMPARE_ARRAYS( 
    endl_data_container.getElectroionizationRecoilPDF( subshell, energy_bin ),
    pdf );
}

//---------------------------------------------------------------------------//
// TEST BREMSSTRAHLUNG DATA 
//---------------------------------------------------------------------------//
// Check that the bremsstrahlung cross section energy grid can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer,
                   setBremsstrahlungCrossSectionEnergyGrid )
{
  std::vector<double> electron_energy_grid( 3 );
  electron_energy_grid[0] = 1e-3;
  electron_energy_grid[1] = 1.0;
  electron_energy_grid[2] = 20.0;

  endl_data_container.setBremsstrahlungCrossSectionEnergyGrid(
    electron_energy_grid );

  TEST_COMPARE_ARRAYS(
    endl_data_container.getBremsstrahlungCrossSectionEnergyGrid(),
    electron_energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung electron cross section can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer,
                   setBremsstrahlungCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  endl_data_container.setBremsstrahlungCrossSection( 
                        cross_section );

  TEST_COMPARE_ARRAYS( 
            endl_data_container.getBremsstrahlungCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung energy grid for the secondary photon can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
                   setBremsstrahlungAveragePhotonIncomingEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  endl_data_container.setBremsstrahlungAveragePhotonIncomingEnergy(
    energy );

  TEST_COMPARE_ARRAYS( 
    endl_data_container.getBremsstrahlungAveragePhotonIncomingEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung average energy of the secondary photon can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
                   setBremsstrahlungAveragePhotonEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.001;
  energy[1] = 0.1;
  energy[2] = 1.0;

  endl_data_container.setBremsstrahlungAveragePhotonEnergy(
    energy );

  TEST_COMPARE_ARRAYS( 
    endl_data_container.getBremsstrahlungAveragePhotonEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung energy grid can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
                   setBremsstrahlungPhotonEnergyGrid )
{
  std::vector<double> energy_grid(2), grid(2);
  energy_grid[0] = 1.0;
  energy_grid[1] = 2.0;

  endl_data_container.setBremsstrahlungPhotonEnergyGrid( 
    energy_grid );
  
  grid = endl_data_container.getBremsstrahlungPhotonEnergyGrid();
  TEST_EQUALITY_CONST( grid[0], energy_grid[0] );
  TEST_EQUALITY_CONST( grid[1], energy_grid[1] );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung photon energy can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
                   setBremsstrahlungPhotonEnergyAtIncomingEnergy )
{
  std::vector<double> photon_energy( 3 );
  photon_energy[0] = 0.01;
  photon_energy[1] = 0.001;
  photon_energy[2] = 0.0001;

  endl_data_container.setBremsstrahlungPhotonEnergyAtIncomingEnergy( 1.0, 
                                                                   photon_energy );

  TEST_COMPARE_ARRAYS( endl_data_container.getBremsstrahlungPhotonEnergy(1.0),
                       photon_energy );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung photon pdf can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
                   setBremsstrahlungPhotonPDFAtIncomingEnergy )
{
  std::vector<double> photon_pdf( 3 );
  photon_pdf[0] = 1.0;
  photon_pdf[1] = 2.0;
  photon_pdf[2] = 5.0;

  endl_data_container.setBremsstrahlungPhotonPDFAtIncomingEnergy( 1.0, 
                                                                photon_pdf );

  TEST_COMPARE_ARRAYS( endl_data_container.getBremsstrahlungPhotonPDF(1.0),
                       photon_pdf );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung photon energy can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
                   setBremsstrahlungPhotonEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.01;
  energy[1] = 0.001;
  energy[2] = 0.0001;

  double energy_bin = 1.0;

  std::map<double,std::vector<double> > photon_energy;

  photon_energy[energy_bin] = energy;

  endl_data_container.setBremsstrahlungPhotonEnergy( photon_energy );

  TEST_COMPARE_ARRAYS( endl_data_container.getBremsstrahlungPhotonEnergy(energy_bin),
                       energy );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung photon pdf can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
                   setBremsstrahlungPhotonPDF )
{
  std::vector<double> pdf( 3 );
  pdf[0] = 1.0;
  pdf[1] = 2.0;
  pdf[2] = 5.0;

  double energy_bin = 1.0;

  std::map<double,std::vector<double> > photon_pdf;

  photon_pdf[energy_bin] = pdf;

  endl_data_container.setBremsstrahlungPhotonPDF( photon_pdf );

  TEST_COMPARE_ARRAYS( endl_data_container.getBremsstrahlungPhotonPDF(energy_bin),
                       pdf );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung energy grid for the secondary electron can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
                   setBremsstrahlungAverageElectronIncomingEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  endl_data_container.setBremsstrahlungAverageElectronIncomingEnergy(
    energy );

  TEST_COMPARE_ARRAYS( 
    endl_data_container.getBremsstrahlungAverageElectronIncomingEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung average energy of the secondary electron can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
                   setBremsstrahlungAverageElectronEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.001;
  energy[1] = 0.1;
  energy[2] = 1.0;

  endl_data_container.setBremsstrahlungAverageElectronEnergy(
    energy );

  TEST_COMPARE_ARRAYS( 
    endl_data_container.getBremsstrahlungAverageElectronEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// TEST ATOMIC EXCITAION DATA 
//---------------------------------------------------------------------------//
// Check that the atomic excitation cross section energy grid can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer,
                   setAtomicExcitationEnergyGrid )
{
  std::vector<double> electron_energy_grid( 3 );
  electron_energy_grid[0] = 1e-3;
  electron_energy_grid[1] = 1.0;
  electron_energy_grid[2] = 20.0;

  endl_data_container.setAtomicExcitationEnergyGrid(
    electron_energy_grid );

  TEST_COMPARE_ARRAYS(
    endl_data_container.getAtomicExcitationEnergyGrid(),
    electron_energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the atomic excitation electron cross section can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer,
                   setAtomicExcitationCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  endl_data_container.setAtomicExcitationCrossSection( 
                        cross_section );

  TEST_COMPARE_ARRAYS( 
            endl_data_container.getAtomicExcitationCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the atomic excitation energy loss can be set
TEUCHOS_UNIT_TEST( ENDLDataContainer, 
                   setAtomicExcitationEnergyLoss )
{
  std::vector<double> energy_loss(3);
  energy_loss[0] = 1.0;
  energy_loss[1] = 5.0;
  energy_loss[2] = 10.0;

  endl_data_container.setAtomicExcitationEnergyLoss( 
                                    energy_loss );
  
  TEST_COMPARE_ARRAYS( endl_data_container.getAtomicExcitationEnergyLoss(), 
                       energy_loss );
}

//---------------------------------------------------------------------------//
// Check that the data can be exported and imported
TEUCHOS_UNIT_TEST( ENDLDataContainer,
                   export_importData_ascii )
{
  const std::string test_ascii_file_name( 
                    "test_endl_data_container.txt" );

  endl_data_container.exportData( test_ascii_file_name,
				 Utility::ArchivableObject::ASCII_ARCHIVE );

  const Data::ENDLDataContainer 
    endl_data_container_copy( test_ascii_file_name, 
			     Utility::ArchivableObject::ASCII_ARCHIVE );

  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAtomicNumber(), 1 );

//---------------------------------------------------------------------------//
// TEST RELAXATION DATA
//---------------------------------------------------------------------------//
  TEST_ASSERT( endl_data_container_copy.getSubshells().count( 1 ) );
  TEST_ASSERT( endl_data_container_copy.getSubshells().count( 3 ) );
  TEST_ASSERT( endl_data_container_copy.getSubshells().count( 5 ) );
  TEST_ASSERT( !endl_data_container_copy.getSubshells().count( 0 ) );
  TEST_ASSERT( !endl_data_container_copy.getSubshells().count( 2 ) );
  TEST_ASSERT( !endl_data_container_copy.getSubshells().count( 4 ) );
  TEST_ASSERT( !endl_data_container_copy.getSubshells().count( 6 ) );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellNumberOfElectrons( 1 ),
    2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellNumberOfElectrons( 3 ),
    4 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellBindingEnergy( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellBindingEnergy( 3 ),
    0.2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellKineticEnergy( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellKineticEnergy( 3 ),
    0.2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellAverageRadius( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellAverageRadius( 3 ),
    0.2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellRadiativeLevel( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellRadiativeLevel( 3 ),
    0.2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellNonRadiativeLevel( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellNonRadiativeLevel( 3 ),
    0.2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getLocalDepositionPerInitialVacancy( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getLocalDepositionPerInitialVacancy( 3 ),
    0.2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAverageParticlesPerInitialVacancy( 1 ),
    2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAverageParticlesPerInitialVacancy( 3 ),
    4 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAverageParitcleEnergyPerInitialVacancy( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAverageParitcleEnergyPerInitialVacancy( 3 ),
    0.2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElasticEnergyGrid().size(), 3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getRadiativeTransitionProbability( 3, 1 ).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getRadiativeTransitionEnergy( 3, 1 ).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getNonRadiativeTransitionProbability( 5, 3, 1 ).size(),
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getNonRadiativeTransitionEnergy( 5, 3, 1 ).size(),
    3 );


//---------------------------------------------------------------------------//
// TEST ELASTIC DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElasticEnergyGrid().size(), 3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticCrossSection().size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticResidualIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticResidualEnergy().size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticScatteredElectronIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticScatteredElectronEnergy().size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticAngularEnergyGrid().size(), 
    1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticAngularEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticAngles(1.0).size(), 3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticPDF(1.0).size(), 3 );
/*
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getScreenedRutherfordElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getScreenedRutherfordNormalizationConstant().size(), 3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getMoliereScreeningConstant().size(), 3 );
*/
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getTotalElasticCrossSection().size(),
		       3u );

//---------------------------------------------------------------------------//
// TEST ELECTROIONIZATION DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationCrossSectionEnergyGrid(1u).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationCrossSection(1u).size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationAverageScatteredElectronIncomingEnergy(1u).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationAverageScatteredElectronEnergy(1u).size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationAverageRecoilElectronIncomingEnergy(1u).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationAverageRecoilElectronEnergy(1u).size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationRecoilEnergyGrid(1u).size(), 
    1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationRecoilEnergyGrid(1u).front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationRecoilEnergy(1u, 1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationRecoilPDF(1u, 1.0).size(), 
    3 );

//---------------------------------------------------------------------------//
// TEST BREMSSTRAHLUNG DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungCrossSectionEnergyGrid().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungCrossSection().size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungAverageElectronIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungAverageElectronEnergy().size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungPhotonEnergyGrid().size(), 
    2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungPhotonEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungPhotonEnergy(1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungPhotonPDF(1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungAveragePhotonIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungAveragePhotonEnergy().size(),
    3u );

//---------------------------------------------------------------------------//
// TEST ATOMIC EXCITATION DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAtomicExcitationEnergyGrid().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAtomicExcitationCrossSection().size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAtomicExcitationEnergyLoss().size(), 
    3 );
}

//---------------------------------------------------------------------------//
// Check that the data can be exported and imported
TEUCHOS_UNIT_TEST( ENDLDataContainer,
                   export_importData_binary )
{
  const std::string test_binary_file_name( 
                    "test_endl_data_container.bin" );

  endl_data_container.exportData( test_binary_file_name,
				 Utility::ArchivableObject::BINARY_ARCHIVE );

  const Data::ENDLDataContainer 
    endl_data_container_copy( test_binary_file_name, 
			     Utility::ArchivableObject::BINARY_ARCHIVE );

//---------------------------------------------------------------------------//
// TEST RELAXATION DATA
//---------------------------------------------------------------------------//
  TEST_ASSERT( endl_data_container_copy.getSubshells().count( 1 ) );
  TEST_ASSERT( endl_data_container_copy.getSubshells().count( 3 ) );
  TEST_ASSERT( endl_data_container_copy.getSubshells().count( 5 ) );
  TEST_ASSERT( !endl_data_container_copy.getSubshells().count( 0 ) );
  TEST_ASSERT( !endl_data_container_copy.getSubshells().count( 2 ) );
  TEST_ASSERT( !endl_data_container_copy.getSubshells().count( 4 ) );
  TEST_ASSERT( !endl_data_container_copy.getSubshells().count( 6 ) );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellNumberOfElectrons( 1 ),
    2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellNumberOfElectrons( 3 ),
    4 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellBindingEnergy( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellBindingEnergy( 3 ),
    0.2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellKineticEnergy( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellKineticEnergy( 3 ),
    0.2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellAverageRadius( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellAverageRadius( 3 ),
    0.2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellRadiativeLevel( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellRadiativeLevel( 3 ),
    0.2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellNonRadiativeLevel( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellNonRadiativeLevel( 3 ),
    0.2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getLocalDepositionPerInitialVacancy( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getLocalDepositionPerInitialVacancy( 3 ),
    0.2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAverageParticlesPerInitialVacancy( 1 ),
    2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAverageParticlesPerInitialVacancy( 3 ),
    4 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAverageParitcleEnergyPerInitialVacancy( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAverageParitcleEnergyPerInitialVacancy( 3 ),
    0.2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElasticEnergyGrid().size(), 3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getRadiativeTransitionProbability( 3, 1 ).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getRadiativeTransitionEnergy( 3, 1 ).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getNonRadiativeTransitionProbability( 5, 3, 1 ).size(),
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getNonRadiativeTransitionEnergy( 5, 3, 1 ).size(),
    3 );

//---------------------------------------------------------------------------//
// TEST ELASTIC DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElasticEnergyGrid().size(), 3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticCrossSection().size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticResidualIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticResidualEnergy().size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticScatteredElectronIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticScatteredElectronEnergy().size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticAngularEnergyGrid().size(), 
    1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticAngularEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticAngles(1.0).size(), 3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticPDF(1.0).size(), 3 );
/*
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getScreenedRutherfordElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getScreenedRutherfordNormalizationConstant().size(), 3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getMoliereScreeningConstant().size(), 3 );
*/
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getTotalElasticCrossSection().size(),
		       3u );

//---------------------------------------------------------------------------//
// TEST ELECTROIONIZATION DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationCrossSectionEnergyGrid(1u).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationCrossSection(1u).size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationAverageScatteredElectronIncomingEnergy(1u).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationAverageScatteredElectronEnergy(1u).size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationAverageRecoilElectronIncomingEnergy(1u).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationAverageRecoilElectronEnergy(1u).size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationRecoilEnergyGrid(1u).size(), 
    1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationRecoilEnergyGrid(1u).front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationRecoilEnergy(1u, 1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationRecoilPDF(1u, 1.0).size(), 
    3 );

//---------------------------------------------------------------------------//
// TEST BREMSSTRAHLUNG DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungCrossSectionEnergyGrid().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungCrossSection().size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungAverageElectronIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungAverageElectronEnergy().size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungPhotonEnergyGrid().size(), 
    2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungPhotonEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungPhotonEnergy(1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungPhotonPDF(1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungAveragePhotonIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungAveragePhotonEnergy().size(),
    3u );

//---------------------------------------------------------------------------//
// TEST ATOMIC EXCITATION DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAtomicExcitationEnergyGrid().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAtomicExcitationCrossSection().size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAtomicExcitationEnergyLoss().size(), 
    3 );
}

//---------------------------------------------------------------------------//
// Check that the data can be exported and imported
TEUCHOS_UNIT_TEST( ENDLDataContainer,
                   export_importData_xml )
{
  const std::string test_xml_file_name( 
                    "test_endl_data_container.xml" );

  endl_data_container.exportData( test_xml_file_name,
				 Utility::ArchivableObject::XML_ARCHIVE );

  const Data::ENDLDataContainer 
    endl_data_container_copy( test_xml_file_name, 
			     Utility::ArchivableObject::XML_ARCHIVE );


  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAtomicNumber(), 1 );

//---------------------------------------------------------------------------//
// TEST RELAXATION DATA
//---------------------------------------------------------------------------//
  TEST_ASSERT( endl_data_container_copy.getSubshells().count( 1 ) );
  TEST_ASSERT( endl_data_container_copy.getSubshells().count( 3 ) );
  TEST_ASSERT( endl_data_container_copy.getSubshells().count( 5 ) );
  TEST_ASSERT( !endl_data_container_copy.getSubshells().count( 0 ) );
  TEST_ASSERT( !endl_data_container_copy.getSubshells().count( 2 ) );
  TEST_ASSERT( !endl_data_container_copy.getSubshells().count( 4 ) );
  TEST_ASSERT( !endl_data_container_copy.getSubshells().count( 6 ) );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellNumberOfElectrons( 1 ),
    2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellNumberOfElectrons( 3 ),
    4 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellBindingEnergy( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellBindingEnergy( 3 ),
    0.2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellKineticEnergy( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellKineticEnergy( 3 ),
    0.2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellAverageRadius( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellAverageRadius( 3 ),
    0.2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellRadiativeLevel( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellRadiativeLevel( 3 ),
    0.2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellNonRadiativeLevel( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellNonRadiativeLevel( 3 ),
    0.2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getLocalDepositionPerInitialVacancy( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getLocalDepositionPerInitialVacancy( 3 ),
    0.2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAverageParticlesPerInitialVacancy( 1 ),
    2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAverageParticlesPerInitialVacancy( 3 ),
    4 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAverageParitcleEnergyPerInitialVacancy( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAverageParitcleEnergyPerInitialVacancy( 3 ),
    0.2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElasticEnergyGrid().size(), 3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getRadiativeTransitionProbability( 3, 1 ).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getRadiativeTransitionEnergy( 3, 1 ).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getNonRadiativeTransitionProbability( 5, 3, 1 ).size(),
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getNonRadiativeTransitionEnergy( 5, 3, 1 ).size(),
    3 );


//---------------------------------------------------------------------------//
// TEST PHOTON DATA
//---------------------------------------------------------------------------//


//---------------------------------------------------------------------------//
// TEST ELASTIC DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElasticEnergyGrid().size(), 3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticCrossSection().size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticResidualIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticResidualEnergy().size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticScatteredElectronIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticScatteredElectronEnergy().size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticAngularEnergyGrid().size(), 
    1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticAngularEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticAngles(1.0).size(), 3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticPDF(1.0).size(), 3 );
/*
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getScreenedRutherfordElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getScreenedRutherfordNormalizationConstant().size(), 3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getMoliereScreeningConstant().size(), 3 );
*/
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getTotalElasticCrossSection().size(),
		       3u );

//---------------------------------------------------------------------------//
// TEST ELECTROIONIZATION DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationCrossSectionEnergyGrid(1u).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationCrossSection(1u).size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationAverageScatteredElectronIncomingEnergy(1u).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationAverageScatteredElectronEnergy(1u).size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationAverageRecoilElectronIncomingEnergy(1u).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationAverageRecoilElectronEnergy(1u).size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationRecoilEnergyGrid(1u).size(), 
    1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationRecoilEnergyGrid(1u).front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationRecoilEnergy(1u, 1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationRecoilPDF(1u, 1.0).size(), 
    3 );

//---------------------------------------------------------------------------//
// TEST BREMSSTRAHLUNG DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungCrossSectionEnergyGrid().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungCrossSection().size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungAverageElectronIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungAverageElectronEnergy().size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungPhotonEnergyGrid().size(), 
    2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungPhotonEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungPhotonEnergy(1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungPhotonPDF(1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungAveragePhotonIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungAveragePhotonEnergy().size(),
    3u );

//---------------------------------------------------------------------------//
// TEST ATOMIC EXCITATION DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAtomicExcitationEnergyGrid().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAtomicExcitationCrossSection().size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAtomicExcitationEnergyLoss().size(), 
    3 );
}

//---------------------------------------------------------------------------//
// Check that the data can be packed into a string and unpacked from a string
TEUCHOS_UNIT_TEST( ENDLDataContainer,
                   pack_unpackDataFromString )
{
  std::string packed_data = endl_data_container.packDataInString();

  Data::ENDLVolatileDataContainer endl_data_container_copy;
  
  endl_data_container_copy.unpackDataFromString( packed_data );
  

  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAtomicNumber(), 1 );

//---------------------------------------------------------------------------//
// TEST RELAXATION DATA
//---------------------------------------------------------------------------//
  TEST_ASSERT( endl_data_container_copy.getSubshells().count( 1 ) );
  TEST_ASSERT( endl_data_container_copy.getSubshells().count( 3 ) );
  TEST_ASSERT( endl_data_container_copy.getSubshells().count( 5 ) );
  TEST_ASSERT( !endl_data_container_copy.getSubshells().count( 0 ) );
  TEST_ASSERT( !endl_data_container_copy.getSubshells().count( 2 ) );
  TEST_ASSERT( !endl_data_container_copy.getSubshells().count( 4 ) );
  TEST_ASSERT( !endl_data_container_copy.getSubshells().count( 6 ) );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellNumberOfElectrons( 1 ),
    2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellNumberOfElectrons( 3 ),
    4 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellBindingEnergy( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellBindingEnergy( 3 ),
    0.2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellKineticEnergy( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellKineticEnergy( 3 ),
    0.2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellAverageRadius( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellAverageRadius( 3 ),
    0.2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellRadiativeLevel( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellRadiativeLevel( 3 ),
    0.2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellNonRadiativeLevel( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getSubshellNonRadiativeLevel( 3 ),
    0.2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getLocalDepositionPerInitialVacancy( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getLocalDepositionPerInitialVacancy( 3 ),
    0.2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAverageParticlesPerInitialVacancy( 1 ),
    2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAverageParticlesPerInitialVacancy( 3 ),
    4 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAverageParitcleEnergyPerInitialVacancy( 1 ),
    0.1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAverageParitcleEnergyPerInitialVacancy( 3 ),
    0.2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElasticEnergyGrid().size(), 3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getRadiativeTransitionProbability( 3, 1 ).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getRadiativeTransitionEnergy( 3, 1 ).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getNonRadiativeTransitionProbability( 5, 3, 1 ).size(),
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getNonRadiativeTransitionEnergy( 5, 3, 1 ).size(),
    3 );


//---------------------------------------------------------------------------//
// TEST PHOTON DATA
//---------------------------------------------------------------------------//


//---------------------------------------------------------------------------//
// TEST ELASTIC DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElasticEnergyGrid().size(), 3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticCrossSection().size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticResidualIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticResidualEnergy().size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticScatteredElectronIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticScatteredElectronEnergy().size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticAngularEnergyGrid().size(), 
    1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticAngularEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticAngles(1.0).size(), 3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getCutoffElasticPDF(1.0).size(), 3 );
/*
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getScreenedRutherfordElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getScreenedRutherfordNormalizationConstant().size(), 3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getMoliereScreeningConstant().size(), 3 );
*/
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getTotalElasticCrossSection().size(),
		       3u );

//---------------------------------------------------------------------------//
// TEST ELECTROIONIZATION DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationCrossSectionEnergyGrid(1u).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationCrossSection(1u).size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationAverageScatteredElectronIncomingEnergy(1u).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationAverageScatteredElectronEnergy(1u).size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationAverageRecoilElectronIncomingEnergy(1u).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationAverageRecoilElectronEnergy(1u).size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationRecoilEnergyGrid(1u).size(), 
    1 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationRecoilEnergyGrid(1u).front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationRecoilEnergy(1u, 1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getElectroionizationRecoilPDF(1u, 1.0).size(), 
    3 );

//---------------------------------------------------------------------------//
// TEST BREMSSTRAHLUNG DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungCrossSectionEnergyGrid().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungCrossSection().size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungAverageElectronIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungAverageElectronEnergy().size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungPhotonEnergyGrid().size(), 
    2 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungPhotonEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungPhotonEnergy(1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungPhotonPDF(1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungAveragePhotonIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getBremsstrahlungAveragePhotonEnergy().size(),
    3u );

//---------------------------------------------------------------------------//
// TEST ATOMIC EXCITATION DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAtomicExcitationEnergyGrid().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAtomicExcitationCrossSection().size(),
    3u );
  TEST_EQUALITY_CONST( 
    endl_data_container_copy.getAtomicExcitationEnergyLoss().size(), 
    3 );
}

//---------------------------------------------------------------------------//
// end tstENDLDataContainer.cpp
//---------------------------------------------------------------------------//

