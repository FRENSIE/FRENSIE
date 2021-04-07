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

// FRENSIE Includes
#include "Data_ENDLVolatileDataContainer.hpp"
#include "Data_ENDLDataContainer.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Data::ENDLVolatileDataContainer endl_data_container;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the atomic number can be set
FRENSIE_UNIT_TEST( ENDLDataContainer, setAtomicNumber )
{
  endl_data_container.setAtomicNumber( 1u );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getAtomicNumber(), 1u );
}

//---------------------------------------------------------------------------//
// Check that the atomic weight can be set
FRENSIE_UNIT_TEST( ENDLDataContainer, setAtomicWeight )
{
  endl_data_container.setAtomicWeight( 1.0 );

  FRENSIE_CHECK_EQUAL( endl_data_container.getAtomicWeight(), 1.0 );
}

//---------------------------------------------------------------------------//
// TEST RELAXATION DATA
//---------------------------------------------------------------------------//
// Check that the subshells can be set
FRENSIE_UNIT_TEST( ENDLDataContainer, setSubshells )
{
  std::set<unsigned> subshells;
  subshells.insert( 1 );
  subshells.insert( 3 );
  subshells.insert( 5 );

  endl_data_container.setSubshells( subshells );

  FRENSIE_CHECK( endl_data_container.getSubshells().count( 1 ) );
  FRENSIE_CHECK( endl_data_container.getSubshells().count( 3 ) );
  FRENSIE_CHECK( endl_data_container.getSubshells().count( 5 ) );
  FRENSIE_CHECK( !endl_data_container.getSubshells().count( 0 ) );
  FRENSIE_CHECK( !endl_data_container.getSubshells().count( 2 ) );
  FRENSIE_CHECK( !endl_data_container.getSubshells().count( 4 ) );
  FRENSIE_CHECK( !endl_data_container.getSubshells().count( 6 ) );
}

//---------------------------------------------------------------------------//
// Check that the number of electrons in subshells can be set
FRENSIE_UNIT_TEST( ENDLDataContainer, setSubshellOccupancy )
{
  std::map<unsigned,double> number_of_electrons_map;

  double number_of_electrons = 2.0;
  unsigned shell = 1;
  number_of_electrons_map[shell] = number_of_electrons;

  number_of_electrons = 4;
  shell = 3;
  number_of_electrons_map[shell] = number_of_electrons;

  endl_data_container.setSubshellOccupancy( number_of_electrons_map );

  FRENSIE_CHECK_EQUAL( endl_data_container.getSubshellOccupancy( 1 ),
                       2 );
  FRENSIE_CHECK_EQUAL( endl_data_container.getSubshellOccupancy( 3 ),
                       number_of_electrons );
}

//---------------------------------------------------------------------------//
// Check that the binding energy in subshells can be set
FRENSIE_UNIT_TEST( ENDLDataContainer, setSubshellBindingEnergy )
{
  std::map<unsigned,double> energy_map;

  double energy = 0.1;
  unsigned shell = 1;
  energy_map[shell] = energy;

  energy = 0.2;
  shell = 3;
  energy_map[shell] = energy;

  endl_data_container.setSubshellBindingEnergy( energy_map );

  FRENSIE_CHECK_EQUAL( endl_data_container.getSubshellBindingEnergy( 1 ),
                       0.1 );
  FRENSIE_CHECK_EQUAL( endl_data_container.getSubshellBindingEnergy( 3 ),
                       energy );
}

//---------------------------------------------------------------------------//
// Check that the kinetic energy in subshells can be set
FRENSIE_UNIT_TEST( ENDLDataContainer, setSubshellKineticEnergy )
{
  std::map<unsigned,double> energy_map;

  double energy = 0.1;
  unsigned shell = 1;
  energy_map[shell] = energy;

  energy = 0.2;
  shell = 3;
  energy_map[shell] = energy;

  endl_data_container.setSubshellKineticEnergy( energy_map );

  FRENSIE_CHECK_EQUAL( endl_data_container.getSubshellKineticEnergy( 1 ),
                       0.1 );
  FRENSIE_CHECK_EQUAL( endl_data_container.getSubshellKineticEnergy( 3 ),
                       energy );
}

//---------------------------------------------------------------------------//
// Check that the average radius in subshells can be set
FRENSIE_UNIT_TEST( ENDLDataContainer, setSubshellAverageRadius )
{
  std::map<unsigned,double> radius_map;

  double radius = 0.1;
  unsigned shell = 1;
  radius_map[shell] = radius;

  radius = 0.2;
  shell = 3;
  radius_map[shell] = radius;

  endl_data_container.setSubshellAverageRadius( radius_map );

  FRENSIE_CHECK_EQUAL( endl_data_container.getSubshellAverageRadius( 1 ),
                       0.1 );
  FRENSIE_CHECK_EQUAL( endl_data_container.getSubshellAverageRadius( 3 ),
                       radius );
}

//---------------------------------------------------------------------------//
// Check that the radiative level width in subshells can be set
FRENSIE_UNIT_TEST( ENDLDataContainer, setSubshellRadiativeLevel )
{
  std::map<unsigned,double> levels_map;

  double levels = 0.1;
  unsigned shell = 1;
  levels_map[shell] = levels;

  levels = 0.2;
  shell = 3;
  levels_map[shell] = levels;

  endl_data_container.setSubshellRadiativeLevel( levels_map );

  FRENSIE_CHECK_EQUAL( endl_data_container.getSubshellRadiativeLevel( 1 ),
                       0.1 );
  FRENSIE_CHECK_EQUAL( endl_data_container.getSubshellRadiativeLevel( 3 ),
                       levels );
}

//---------------------------------------------------------------------------//
// Check that the non radiative level width in subshells can be set
FRENSIE_UNIT_TEST( ENDLDataContainer, setSubshellNonRadiativeLevel )
{
  std::map<unsigned,double> levels_map;

  double levels = 0.1;
  unsigned shell = 1;
  levels_map[shell] = levels;

  levels = 0.2;
  shell = 3;
  levels_map[shell] = levels;

  endl_data_container.setSubshellNonRadiativeLevel( levels_map );

  FRENSIE_CHECK_EQUAL( endl_data_container.getSubshellNonRadiativeLevel( 1 ),
                       0.1 );
  FRENSIE_CHECK_EQUAL( endl_data_container.getSubshellNonRadiativeLevel( 3 ),
                       levels );
}

//---------------------------------------------------------------------------//
// Check that the average energy to the residual atom can be set
FRENSIE_UNIT_TEST( ENDLDataContainer, setLocalDepositionPerInitialVacancy )
{
  std::map<unsigned,double> deposition_map;

  double deposition = 0.1;
  unsigned shell = 1;
  deposition_map[shell] = deposition;

  deposition = 0.2;
  shell = 3;
  deposition_map[shell] = deposition;

  endl_data_container.setLocalDepositionPerInitialVacancy( deposition_map );

  FRENSIE_CHECK_EQUAL( endl_data_container.getLocalDepositionPerInitialVacancy( 1 ),
                       0.1 );
  FRENSIE_CHECK_EQUAL( endl_data_container.getLocalDepositionPerInitialVacancy( 3 ),
                       deposition );
}

//---------------------------------------------------------------------------//
// Check that the average number of photons can be set
FRENSIE_UNIT_TEST( ENDLDataContainer, setAveragePhotonsPerInitialVacancy )
{
  std::map<unsigned,double> number_of_particles_map;

  double number_of_particles = 2.0;
  unsigned shell = 1;
  number_of_particles_map[shell] = number_of_particles;

  number_of_particles = 4;
  shell = 3;
  number_of_particles_map[shell] = number_of_particles;

  endl_data_container.setAveragePhotonsPerInitialVacancy(
    number_of_particles_map );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getAveragePhotonsPerInitialVacancy( 1 ),
    2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container.getAveragePhotonsPerInitialVacancy( 3 ),
    number_of_particles );
}

//---------------------------------------------------------------------------//
// Check that the average energy of photons can be set
FRENSIE_UNIT_TEST( ENDLDataContainer, setAveragePhotonEnergyPerInitialVacancy )
{
  std::map<unsigned,double> energy_map;

  double energy = 0.1;
  unsigned shell = 1;
  energy_map[shell] = energy;

  energy = 0.2;
  shell = 3;
  energy_map[shell] = energy;

  endl_data_container.setAveragePhotonEnergyPerInitialVacancy( energy_map );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getAveragePhotonEnergyPerInitialVacancy( 1 ),
    0.1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container.getAveragePhotonEnergyPerInitialVacancy( 3 ),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the average number of electrons can be set
FRENSIE_UNIT_TEST( ENDLDataContainer, setAverageElectronsPerInitialVacancy )
{
  std::map<unsigned,double> number_of_particles_map;

  double number_of_particles = 2.0;
  unsigned shell = 1;
  number_of_particles_map[shell] = number_of_particles;

  number_of_particles = 4;
  shell = 3;
  number_of_particles_map[shell] = number_of_particles;

  endl_data_container.setAverageElectronsPerInitialVacancy(
    number_of_particles_map );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getAverageElectronsPerInitialVacancy( 1 ),
    2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container.getAverageElectronsPerInitialVacancy( 3 ),
    number_of_particles );
}


//---------------------------------------------------------------------------//
// Check that the average energy of particles can be set
FRENSIE_UNIT_TEST( ENDLDataContainer, setAverageElectronEnergyPerInitialVacancy )
{
  std::map<unsigned,double> energy_map;

  double energy = 0.1;
  unsigned shell = 1;
  energy_map[shell] = energy;

  energy = 0.2;
  shell = 3;
  energy_map[shell] = energy;

  endl_data_container.setAverageElectronEnergyPerInitialVacancy( energy_map );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getAverageElectronEnergyPerInitialVacancy( 1 ),
    0.1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container.getAverageElectronEnergyPerInitialVacancy( 3 ),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the radiative transition probability can be set
FRENSIE_UNIT_TEST( ENDLDataContainer, setRadiativeTransitionProbability )
{
  std::map<unsigned,double> probability_map;

  double probability = 0.3;

  unsigned shell = 1;
  unsigned secondary_shell = 3;
  probability_map[secondary_shell] = probability;

  endl_data_container.setRadiativeTransitionProbability( shell, probability_map );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getRadiativeTransitionProbability(
        shell ).find( secondary_shell )->second,
    probability );
}

//---------------------------------------------------------------------------//
// Check that the radiative transition energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer, setRadiativeTransitionEnergy )
{
  std::map<unsigned,double> energy_map;

  double energy = 0.3;

  unsigned shell = 1;
  unsigned secondary_shell = 3;
  energy_map[secondary_shell] = energy;

  endl_data_container.setRadiativeTransitionEnergy( shell, energy_map );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getRadiativeTransitionEnergy(
        shell ).find( secondary_shell )->second,
    energy );
}

//---------------------------------------------------------------------------//
// Check that the non radiative transition probability can be set
FRENSIE_UNIT_TEST( ENDLDataContainer, setNonRadiativeTransitionProbability )
{
  std::map<unsigned,double> probability_map;
  std::map<unsigned,std::map<unsigned,double> > probability_map_map;

  double probability = 0.3;

  unsigned shell = 1;
  unsigned secondary_shell = 3;
  unsigned tertiary_shell = 5;

  probability_map[tertiary_shell] = probability;
  probability_map_map[secondary_shell] = probability_map;

  endl_data_container.setNonRadiativeTransitionProbability( shell, probability_map_map );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getNonRadiativeTransitionProbability(
        shell ).find( secondary_shell )->second.find( tertiary_shell )->second,
    probability );
}

//---------------------------------------------------------------------------//
// Check that the non radiative transition energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer, setNonRadiativeTransitionEnergy )
{
  std::map<unsigned,double> energy_map;
  std::map<unsigned,std::map<unsigned,double> > energy_map_map;

  double energy = 0.3;

  unsigned shell = 1;
  unsigned secondary_shell = 3;
  unsigned tertiary_shell = 5;

  energy_map[tertiary_shell] = energy;
  energy_map_map[secondary_shell] = energy_map;

  endl_data_container.setNonRadiativeTransitionEnergy( shell, energy_map_map );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getNonRadiativeTransitionEnergy(
        shell ).find( secondary_shell )->second.find( tertiary_shell )->second,
    energy );
}

//---------------------------------------------------------------------------//
// TEST COHERENT PHOTON DATA
//---------------------------------------------------------------------------//
// Check that the coherent cross section energy grid can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setCoherentCrossSectionEnergyGrid )
{
  std::vector<double> energy_grid( 3 );
  energy_grid[0] = 1e-3;
  energy_grid[1] = 1.0;
  energy_grid[2] = 20.0;

  endl_data_container.setCoherentCrossSectionEnergyGrid( energy_grid );

  FRENSIE_CHECK_EQUAL( endl_data_container.getCoherentCrossSectionEnergyGrid(),
                       energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the coherent photon cross section can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setCoherentCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 0.5e-6;
  cross_section[1] = 0.5e-1;
  cross_section[2] = 0.5;

  endl_data_container.setCoherentCrossSection(
                        cross_section );

  FRENSIE_CHECK_EQUAL(
            endl_data_container.getCoherentCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the coherent photon cross section interpolation type can be set
FRENSIE_UNIT_TEST( ENDLDataContainer, setCoherentCrossSectionInterpType )
{
  endl_data_container.setCoherentCrossSectionInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCoherentCrossSectionInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setCoherentCrossSectionInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCoherentCrossSectionInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setCoherentCrossSectionInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCoherentCrossSectionInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setCoherentCrossSectionInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCoherentCrossSectionInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the argument for the coherent form factor can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setCoherentFormFactorArgument)
{
  std::vector<double> argument( 3 );
  argument[0] = 0.0;
  argument[1] = 10.0;
  argument[2] = 1.0e12;

  endl_data_container.setCoherentFormFactorArgument( argument );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getCoherentFormFactorArgument(),
    argument );
}

//---------------------------------------------------------------------------//
// Check that the coherent form factor can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setCoherentFormFactor )
{
  std::vector<double> factor( 3 );
  factor[0] = 1.0;
  factor[1] = 0.5;
  factor[2] = 0.1;

  endl_data_container.setCoherentFormFactor( factor );

  FRENSIE_CHECK_EQUAL( endl_data_container.getCoherentFormFactor(), factor );
}

//---------------------------------------------------------------------------//
// Check that the coherent form factor interpolation type can be set
FRENSIE_UNIT_TEST( ENDLDataContainer, setCoherentFormFactorInterpType )
{
  endl_data_container.setCoherentFormFactorInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCoherentFormFactorInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setCoherentFormFactorInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCoherentFormFactorInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setCoherentFormFactorInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCoherentFormFactorInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setCoherentFormFactorInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCoherentFormFactorInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the energy grid for the coherent imaginary factor can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setCoherentImaginaryAnomalousFactorIncidentEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  endl_data_container.setCoherentImaginaryAnomalousFactorIncidentEnergy(
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getCoherentImaginaryAnomalousFactorIncidentEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the coherent imaginary factor can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setCoherentImaginaryAnomalousFactor )
{
  std::vector<double> factor( 3 );
  factor[0] = 0.0;
  factor[1] = 1.0;
  factor[2] = 0.1;

  endl_data_container.setCoherentImaginaryAnomalousFactor( factor );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getCoherentImaginaryAnomalousFactor(),
    factor );
}

//---------------------------------------------------------------------------//
// Check that the coherent imaginary factor interpolation type can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setCoherentImaginaryAnomalousFactorInterpType )
{
  endl_data_container.setCoherentImaginaryAnomalousFactorInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCoherentImaginaryAnomalousFactorInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setCoherentImaginaryAnomalousFactorInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCoherentImaginaryAnomalousFactorInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setCoherentImaginaryAnomalousFactorInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCoherentImaginaryAnomalousFactorInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setCoherentImaginaryAnomalousFactorInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCoherentImaginaryAnomalousFactorInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the energy grid for the coherent real factor can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setCoherentRealAnomalousFactorIncidentEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  endl_data_container.setCoherentRealAnomalousFactorIncidentEnergy( energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getCoherentRealAnomalousFactorIncidentEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the coherent real factor can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setCoherentRealAnomalousFactor )
{
  std::vector<double> factor( 3 );
  factor[0] = 0.1;
  factor[1] = 1.0;
  factor[2] = -1.0;

  endl_data_container.setCoherentRealAnomalousFactor( factor );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getCoherentRealAnomalousFactor(),
    factor );
}

//---------------------------------------------------------------------------//
// Check that the coherent real factor interpolation type can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setCoherentRealAnomalousFactorInterpType )
{
  endl_data_container.setCoherentRealAnomalousFactorInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCoherentRealAnomalousFactorInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setCoherentRealAnomalousFactorInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCoherentRealAnomalousFactorInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setCoherentRealAnomalousFactorInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCoherentRealAnomalousFactorInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setCoherentRealAnomalousFactorInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCoherentRealAnomalousFactorInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the coherent average photon incident energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setCoherentAveragePhotonIncidentEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  endl_data_container.setCoherentAveragePhotonIncidentEnergy( energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getCoherentAveragePhotonIncidentEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the coherent average photon energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setCoherentAveragePhotonEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  endl_data_container.setCoherentAveragePhotonEnergy( energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getCoherentAveragePhotonEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the coherent average photon energy interpolation type can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setCoherentAveragePhotonEnergyInterpType )
{
  endl_data_container.setCoherentAveragePhotonEnergyInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCoherentAveragePhotonEnergyInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setCoherentAveragePhotonEnergyInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCoherentAveragePhotonEnergyInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setCoherentAveragePhotonEnergyInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCoherentAveragePhotonEnergyInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setCoherentAveragePhotonEnergyInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCoherentAveragePhotonEnergyInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// TEST INCOHERENT PHOTON DATA
//---------------------------------------------------------------------------//
// Check that the incoherent cross section energy grid can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setIncoherentCrossSectionEnergyGrid )
{
  std::vector<double> energy_grid( 3 );
  energy_grid[0] = 1e-3;
  energy_grid[1] = 1.0;
  energy_grid[2] = 20.0;

  endl_data_container.setIncoherentCrossSectionEnergyGrid( energy_grid );

  FRENSIE_CHECK_EQUAL( endl_data_container.getIncoherentCrossSectionEnergyGrid(),
                       energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the incoherent cross section can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setIncoherentCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 0.5e-6;
  cross_section[1] = 0.5e-1;
  cross_section[2] = 0.5;

  endl_data_container.setIncoherentCrossSection( cross_section );

  FRENSIE_CHECK_EQUAL(
            endl_data_container.getIncoherentCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the incoherent cross section interpolation type can be set
FRENSIE_UNIT_TEST( ENDLDataContainer, setIncoherentCrossSectionInterpType )
{
  endl_data_container.setIncoherentCrossSectionInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getIncoherentCrossSectionInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setIncoherentCrossSectionInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getIncoherentCrossSectionInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setIncoherentCrossSectionInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getIncoherentCrossSectionInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setIncoherentCrossSectionInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getIncoherentCrossSectionInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the argument for the incoherent scattering function can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setIncoherentScatteringFunctionArgument)
{
  std::vector<double> argument( 3 );
  argument[0] = 0.0;
  argument[1] = 10.0;
  argument[2] = 1.0e12;

  endl_data_container.setIncoherentScatteringFunctionArgument( argument );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getIncoherentScatteringFunctionArgument(),
    argument );
}

//---------------------------------------------------------------------------//
// Check the incoherent scattering function can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setIncoherentScatteringFunction )
{
  std::vector<double> factor( 3 );
  factor[0] = 0.0;
  factor[1] = 0.1;
  factor[2] = 1.0;

  endl_data_container.setIncoherentScatteringFunction( factor );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getIncoherentScatteringFunction(),
    factor );
}

//---------------------------------------------------------------------------//
// Check the incoherent scattering function interpolation type can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setIncoherentScatteringFunctionInterpType )
{
  endl_data_container.setIncoherentScatteringFunctionInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getIncoherentScatteringFunctionInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setIncoherentScatteringFunctionInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getIncoherentScatteringFunctionInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setIncoherentScatteringFunctionInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getIncoherentScatteringFunctionInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setIncoherentScatteringFunctionInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getIncoherentScatteringFunctionInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the incoherent average photon incident energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setIncoherentAveragePhotonIncidentEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  endl_data_container.setIncoherentAveragePhotonIncidentEnergy( energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getIncoherentAveragePhotonIncidentEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the incoherent average photon energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setIncoherentAveragePhotonEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.9;
  energy[1] = 1.8;
  energy[2] = 2.7;

  endl_data_container.setIncoherentAveragePhotonEnergy( energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getIncoherentAveragePhotonEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the incoherent average photon energy interpolation type can be
// set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setIncoherentAveragePhotonEnergyInterpType )
{
  endl_data_container.setIncoherentAveragePhotonEnergyInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getIncoherentAveragePhotonEnergyInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setIncoherentAveragePhotonEnergyInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getIncoherentAveragePhotonEnergyInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setIncoherentAveragePhotonEnergyInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getIncoherentAveragePhotonEnergyInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setIncoherentAveragePhotonEnergyInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getIncoherentAveragePhotonEnergyInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the incoherent average electron incident energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setIncoherentAverageElectronIncidentEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  endl_data_container.setIncoherentAverageElectronIncidentEnergy( energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getIncoherentAverageElectronIncidentEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the incoherent average electron energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setIncoherentAverageElectronEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.1;
  energy[1] = 0.2;
  energy[2] = 0.3;

  endl_data_container.setIncoherentAverageElectronEnergy( energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getIncoherentAverageElectronEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the incoherent average electron energy interpolation type can be
// set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setIncoherentAverageElectronEnergyInterpType )
{
  endl_data_container.setIncoherentAverageElectronEnergyInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getIncoherentAverageElectronEnergyInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setIncoherentAverageElectronEnergyInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getIncoherentAverageElectronEnergyInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setIncoherentAverageElectronEnergyInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getIncoherentAverageElectronEnergyInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setIncoherentAverageElectronEnergyInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getIncoherentAverageElectronEnergyInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// TEST PHOTOELECTRIC PHOTON DATA
//---------------------------------------------------------------------------//

// Check that the photoelectric cross section energy grid can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPhotoelectricCrossSectionEnergyGrid )
{
  std::vector<double> energy_grid( 3 );
  energy_grid[0] = 1e-3;
  energy_grid[1] = 1.0;
  energy_grid[2] = 20.0;

  endl_data_container.setPhotoelectricCrossSectionEnergyGrid( energy_grid );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getPhotoelectricCrossSectionEnergyGrid(),
    energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric cross section can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPhotoelectricCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 0.5e-6;
  cross_section[1] = 0.5e-1;
  cross_section[2] = 0.5;

  endl_data_container.setPhotoelectricCrossSection( cross_section );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getPhotoelectricCrossSection(),
    cross_section );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric cross section interpolation type can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPhotoelectricCrossSectionInterpType )
{
  endl_data_container.setPhotoelectricCrossSectionInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricCrossSectionInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setPhotoelectricCrossSectionInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricCrossSectionInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setPhotoelectricCrossSectionInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricCrossSectionInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setPhotoelectricCrossSectionInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricCrossSectionInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric average photon incident energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPhotoelectricAverageResidualIncidentEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  endl_data_container.setPhotoelectricAverageResidualIncidentEnergy(
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getPhotoelectricAverageResidualIncidentEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric average photon energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPhotoelectricAverageResidualEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.9;
  energy[1] = 1.8;
  energy[2] = 2.7;

  endl_data_container.setPhotoelectricAverageResidualEnergy( energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getPhotoelectricAverageResidualEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric average photon energy interpolation type can be
// set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPhotoelectricAverageResidualEnergyInterpType )
{
  endl_data_container.setPhotoelectricAverageResidualEnergyInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricAverageResidualEnergyInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setPhotoelectricAverageResidualEnergyInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricAverageResidualEnergyInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setPhotoelectricAverageResidualEnergyInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricAverageResidualEnergyInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setPhotoelectricAverageResidualEnergyInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricAverageResidualEnergyInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric average photons incident energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPhotoelectricAveragePhotonsIncidentEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  endl_data_container.setPhotoelectricAveragePhotonsIncidentEnergy(
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getPhotoelectricAveragePhotonsIncidentEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric average photons energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPhotoelectricAveragePhotonsEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.9;
  energy[1] = 1.8;
  energy[2] = 2.7;

  endl_data_container.setPhotoelectricAveragePhotonsEnergy(
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getPhotoelectricAveragePhotonsEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric average photons energy interpolation type can
// be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPhotoelectricAveragePhotonsEnergyInterpType )
{
  endl_data_container.setPhotoelectricAveragePhotonsEnergyInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricAveragePhotonsEnergyInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setPhotoelectricAveragePhotonsEnergyInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricAveragePhotonsEnergyInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setPhotoelectricAveragePhotonsEnergyInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricAveragePhotonsEnergyInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setPhotoelectricAveragePhotonsEnergyInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricAveragePhotonsEnergyInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric average electrons incident energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPhotoelectricAverageElectronsIncidentEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  endl_data_container.setPhotoelectricAverageElectronsIncidentEnergy(
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getPhotoelectricAverageElectronsIncidentEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric average electrons energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPhotoelectricAverageElectronsEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.1;
  energy[1] = 0.2;
  energy[2] = 0.3;

  endl_data_container.setPhotoelectricAverageElectronsEnergy(
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getPhotoelectricAverageElectronsEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric average electrons energy interpolation type can
// be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPhotoelectricAverageElectronsEnergyInterpType )
{
  endl_data_container.setPhotoelectricAverageElectronsEnergyInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricAverageElectronsEnergyInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setPhotoelectricAverageElectronsEnergyInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricAverageElectronsEnergyInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setPhotoelectricAverageElectronsEnergyInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricAverageElectronsEnergyInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setPhotoelectricAverageElectronsEnergyInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricAverageElectronsEnergyInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// TEST PHOTOELECTRIC PHOTON DATA BY SUBSHELL
//---------------------------------------------------------------------------//
// Check that the photoelectric cross section energy grid can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPhotoelectricCrossSectionEnergyGrid_Subshell )
{
  unsigned shell = 1;

  std::vector<double> energy_grid( 3 );
  energy_grid[0] = 1e-3;
  energy_grid[1] = 1.0;
  energy_grid[2] = 20.0;

  endl_data_container.setPhotoelectricCrossSectionEnergyGrid(
    shell,
    energy_grid );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getPhotoelectricCrossSectionEnergyGrid( shell ),
    energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric cross section can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPhotoelectricCrossSection_Subshell )
{
  unsigned shell = 1;

  std::vector<double> cross_section( 3 );
  cross_section[0] = 0.5e-6;
  cross_section[1] = 0.5e-1;
  cross_section[2] = 0.5;

  endl_data_container.setPhotoelectricCrossSection( shell, cross_section );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getPhotoelectricCrossSection( shell ),
    cross_section );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric cross section interpolation type can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPhotoelectricCrossSectionInterpType_Subshell )
{
  unsigned shell = 1;

  endl_data_container.setPhotoelectricCrossSectionInterpType<Utility::LinLin>( shell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricCrossSectionInterpType( shell ),
                       Utility::LinLin::name() );

  endl_data_container.setPhotoelectricCrossSectionInterpType<Utility::LinLog>( shell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricCrossSectionInterpType( shell ),
                       Utility::LinLog::name() );

  endl_data_container.setPhotoelectricCrossSectionInterpType<Utility::LogLin>( shell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricCrossSectionInterpType( shell ),
                       Utility::LogLin::name() );

  endl_data_container.setPhotoelectricCrossSectionInterpType<Utility::LogLog>( shell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricCrossSectionInterpType( shell ),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric average photon incident energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPhotoelectricAverageResidualIncidentEnergy_Subshell )
{
  unsigned shell = 1;

  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  endl_data_container.setPhotoelectricAverageResidualIncidentEnergy(
    shell,
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getPhotoelectricAverageResidualIncidentEnergy( shell ),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric average photon energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPhotoelectricAverageResidualEnergy_Subshell )
{
  unsigned shell = 1;

  std::vector<double> energy( 3 );
  energy[0] = 0.9;
  energy[1] = 1.8;
  energy[2] = 2.7;

  endl_data_container.setPhotoelectricAverageResidualEnergy( shell, energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getPhotoelectricAverageResidualEnergy( shell ),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric average photon energy interpolation type can be
// set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPhotoelectricAverageResidualEnergyInterpType_Subshell )
{
  unsigned shell = 1;
    
  endl_data_container.setPhotoelectricAverageResidualEnergyInterpType<Utility::LinLin>( shell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricAverageResidualEnergyInterpType( shell ),
                       Utility::LinLin::name() );

  endl_data_container.setPhotoelectricAverageResidualEnergyInterpType<Utility::LinLog>( shell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricAverageResidualEnergyInterpType( shell ),
                       Utility::LinLog::name() );

  endl_data_container.setPhotoelectricAverageResidualEnergyInterpType<Utility::LogLin>( shell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricAverageResidualEnergyInterpType( shell ),
                       Utility::LogLin::name() );

  endl_data_container.setPhotoelectricAverageResidualEnergyInterpType<Utility::LogLog>( shell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricAverageResidualEnergyInterpType( shell ),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric average photons incident energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPhotoelectricAveragePhotonsIncidentEnergy_Subshell )
{
  unsigned shell = 1;

  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  endl_data_container.setPhotoelectricAveragePhotonsIncidentEnergy(
    shell,
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getPhotoelectricAveragePhotonsIncidentEnergy( shell ),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric average photons energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPhotoelectricAveragePhotonsEnergy_Subshell )
{
  unsigned shell = 1;

  std::vector<double> energy( 3 );
  energy[0] = 0.9;
  energy[1] = 1.8;
  energy[2] = 2.7;

  endl_data_container.setPhotoelectricAveragePhotonsEnergy(
    shell,
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getPhotoelectricAveragePhotonsEnergy( shell ),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric average photons energy interpolation type can
// be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPhotoelectricAveragePhotonsEnergyInterpType_Subshell )
{
  unsigned shell = 1;

  endl_data_container.setPhotoelectricAveragePhotonsEnergyInterpType<Utility::LinLin>( shell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricAveragePhotonsEnergyInterpType( shell ),
                       Utility::LinLin::name() );

  endl_data_container.setPhotoelectricAveragePhotonsEnergyInterpType<Utility::LinLog>( shell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricAveragePhotonsEnergyInterpType( shell ),
                       Utility::LinLog::name() );

  endl_data_container.setPhotoelectricAveragePhotonsEnergyInterpType<Utility::LogLin>( shell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricAveragePhotonsEnergyInterpType( shell ),
                       Utility::LogLin::name() );

  endl_data_container.setPhotoelectricAveragePhotonsEnergyInterpType<Utility::LogLog>( shell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricAveragePhotonsEnergyInterpType( shell ),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric average electrons incident energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPhotoelectricAverageElectronsIncidentEnergy_Subshell )
{
  unsigned shell = 1;

  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  endl_data_container.setPhotoelectricAverageElectronsIncidentEnergy(
    shell,
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getPhotoelectricAverageElectronsIncidentEnergy( shell ),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric average electrons energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPhotoelectricAverageElectronsEnergy_Subshell )
{
  unsigned shell = 1;

  std::vector<double> energy( 3 );
  energy[0] = 0.1;
  energy[1] = 0.2;
  energy[2] = 0.3;

  endl_data_container.setPhotoelectricAverageElectronsEnergy(
    shell,
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getPhotoelectricAverageElectronsEnergy( shell ),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric average electrons energy interpolation type can
// be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPhotoelectricAverageElectronsEnergyInterpType_Subshell )
{
  unsigned shell = 1;

  endl_data_container.setPhotoelectricAverageElectronsEnergyInterpType<Utility::LinLin>( shell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricAverageElectronsEnergyInterpType( shell ),
                       Utility::LinLin::name() );

  endl_data_container.setPhotoelectricAverageElectronsEnergyInterpType<Utility::LinLog>( shell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricAverageElectronsEnergyInterpType( shell ),
                       Utility::LinLog::name() );

  endl_data_container.setPhotoelectricAverageElectronsEnergyInterpType<Utility::LogLin>( shell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricAverageElectronsEnergyInterpType( shell ),
                       Utility::LogLin::name() );

  endl_data_container.setPhotoelectricAverageElectronsEnergyInterpType<Utility::LogLog>( shell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getPhotoelectricAverageElectronsEnergyInterpType( shell ),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// TEST PAIR PRODUCTION PHOTON DATA
//---------------------------------------------------------------------------//
// Check that the pair production cross section energy grid can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPairProductionCrossSectionEnergyGrid )
{
  std::vector<double> energy_grid( 3 );
  energy_grid[0] = 1e-3;
  energy_grid[1] = 1.0;
  energy_grid[2] = 20.0;

  endl_data_container.setPairProductionCrossSectionEnergyGrid( energy_grid );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getPairProductionCrossSectionEnergyGrid(),
    energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the pair production cross section can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPairProductionCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 0.5e-6;
  cross_section[1] = 0.5e-1;
  cross_section[2] = 0.5;

  endl_data_container.setPairProductionCrossSection( cross_section );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getPairProductionCrossSection(),
    cross_section );
}

//---------------------------------------------------------------------------//
// Check that the pair production cross section interpolatio type can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPairProductionCrossSectionInterpType )
{
  endl_data_container.setPairProductionCrossSectionInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getPairProductionCrossSectionInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setPairProductionCrossSectionInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getPairProductionCrossSectionInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setPairProductionCrossSectionInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getPairProductionCrossSectionInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setPairProductionCrossSectionInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getPairProductionCrossSectionInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the pair production average positron incident energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPairProductionAveragePositronIncidentEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  endl_data_container.setPairProductionAveragePositronIncidentEnergy(
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getPairProductionAveragePositronIncidentEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the pair production average positron energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPairProductionAveragePositronEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.9;
  energy[1] = 1.8;
  energy[2] = 2.7;

  endl_data_container.setPairProductionAveragePositronEnergy(
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getPairProductionAveragePositronEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the pair production average positron energy interpolation type
// can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPairProductionAveragePositronEnergyInterpType )
{
  endl_data_container.setPairProductionAveragePositronEnergyInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getPairProductionAveragePositronEnergyInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setPairProductionAveragePositronEnergyInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getPairProductionAveragePositronEnergyInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setPairProductionAveragePositronEnergyInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getPairProductionAveragePositronEnergyInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setPairProductionAveragePositronEnergyInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getPairProductionAveragePositronEnergyInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the pair production average electron incident energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPairProductionAverageElectronIncidentEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  endl_data_container.setPairProductionAverageElectronIncidentEnergy(
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getPairProductionAverageElectronIncidentEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the pair production average electron energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPairProductionAverageElectronEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.1;
  energy[1] = 0.2;
  energy[2] = 0.3;

  endl_data_container.setPairProductionAverageElectronEnergy(
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getPairProductionAverageElectronEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the pair production average electron energy interpolation type
// can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setPairProductionAverageElectronEnergyInterpType )
{
  endl_data_container.setPairProductionAverageElectronEnergyInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getPairProductionAverageElectronEnergyInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setPairProductionAverageElectronEnergyInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getPairProductionAverageElectronEnergyInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setPairProductionAverageElectronEnergyInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getPairProductionAverageElectronEnergyInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setPairProductionAverageElectronEnergyInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getPairProductionAverageElectronEnergyInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// TEST TRIPLET PRODUCTION PHOTON DATA
//---------------------------------------------------------------------------//
// Check that the triplet production cross section energy grid can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setTripletProductionCrossSectionEnergyGrid )
{
  std::vector<double> energy_grid( 3 );
  energy_grid[0] = 1e-3;
  energy_grid[1] = 1.0;
  energy_grid[2] = 20.0;

  endl_data_container.setTripletProductionCrossSectionEnergyGrid( energy_grid );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getTripletProductionCrossSectionEnergyGrid(),
    energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the triplet production cross section can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setTripletProductionCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 0.5e-6;
  cross_section[1] = 0.5e-1;
  cross_section[2] = 0.5;

  endl_data_container.setTripletProductionCrossSection( cross_section );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getTripletProductionCrossSection(),
    cross_section );
}

//---------------------------------------------------------------------------//
// Check that the triplet production cross section interpolation type can be
// set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setTripletProductionCrossSectionInterpType )
{
  endl_data_container.setTripletProductionCrossSectionInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getTripletProductionCrossSectionInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setTripletProductionCrossSectionInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getTripletProductionCrossSectionInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setTripletProductionCrossSectionInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getTripletProductionCrossSectionInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setTripletProductionCrossSectionInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getTripletProductionCrossSectionInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the triplet production average positron incident energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setTripletProductionAveragePositronIncidentEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  endl_data_container.setTripletProductionAveragePositronIncidentEnergy(
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getTripletProductionAveragePositronIncidentEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the triplet production average positron energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setTripletProductionAveragePositronEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.9;
  energy[1] = 1.8;
  energy[2] = 2.7;

  endl_data_container.setTripletProductionAveragePositronEnergy(
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getTripletProductionAveragePositronEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the triplet production average positron energy interpolation type
// can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setTripletProductionAveragePositronEnergyInterpType )
{
  endl_data_container.setTripletProductionAveragePositronEnergyInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getTripletProductionAveragePositronEnergyInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setTripletProductionAveragePositronEnergyInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getTripletProductionAveragePositronEnergyInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setTripletProductionAveragePositronEnergyInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getTripletProductionAveragePositronEnergyInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setTripletProductionAveragePositronEnergyInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getTripletProductionAveragePositronEnergyInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the triplet production average electron incident energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setTripletProductionAverageElectronIncidentEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  endl_data_container.setTripletProductionAverageElectronIncidentEnergy(
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getTripletProductionAverageElectronIncidentEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the triplet production average electron energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setTripletProductionAverageElectronEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.1;
  energy[1] = 0.2;
  energy[2] = 0.3;

  endl_data_container.setTripletProductionAverageElectronEnergy(
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getTripletProductionAverageElectronEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the triplet production average electron energy interpolation type
// can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setTripletProductionAverageElectronEnergyInterpType )
{
  endl_data_container.setTripletProductionAverageElectronEnergyInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getTripletProductionAverageElectronEnergyInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setTripletProductionAverageElectronEnergyInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getTripletProductionAverageElectronEnergyInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setTripletProductionAverageElectronEnergyInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getTripletProductionAverageElectronEnergyInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setTripletProductionAverageElectronEnergyInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getTripletProductionAverageElectronEnergyInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// TEST ELASTIC ELECTRON DATA
//---------------------------------------------------------------------------//
// Check that the elastic energy grid can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setElasticEnergyGrid )
{
  std::vector<double> electron_energy_grid( 3 );
  electron_energy_grid[0] = 1e-3;
  electron_energy_grid[1] = 1.0;
  electron_energy_grid[2] = 20.0;

  endl_data_container.setElasticEnergyGrid( electron_energy_grid );

  FRENSIE_CHECK_EQUAL( endl_data_container.getElasticEnergyGrid(),
                       electron_energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the elastic transport cross section can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setElasticTransportCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 0.5e-6;
  cross_section[1] = 0.5e-1;
  cross_section[2] = 0.5;

  endl_data_container.setElasticTransportCrossSection(
                        cross_section );

  FRENSIE_CHECK_EQUAL(
            endl_data_container.getElasticTransportCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the elastic transport cross section interpolation type can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setElasticTransportCrossSectionInterpType )
{
  endl_data_container.setElasticTransportCrossSectionInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getElasticTransportCrossSectionInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setElasticTransportCrossSectionInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getElasticTransportCrossSectionInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setElasticTransportCrossSectionInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getElasticTransportCrossSectionInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setElasticTransportCrossSectionInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getElasticTransportCrossSectionInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the cutoff elastic electron cross section can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setCutoffElasticCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 0.5e-6;
  cross_section[1] = 0.5e-1;
  cross_section[2] = 0.5;

  endl_data_container.setCutoffElasticCrossSection(
                        cross_section );

  FRENSIE_CHECK_EQUAL(
            endl_data_container.getCutoffElasticCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the cutoff elastic electron cross section interpolation type can
// be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setCutoffElasticCrossSectionInterpType )
{
  endl_data_container.setCutoffElasticCrossSectionInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCutoffElasticCrossSectionInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setCutoffElasticCrossSectionInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCutoffElasticCrossSectionInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setCutoffElasticCrossSectionInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCutoffElasticCrossSectionInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setCutoffElasticCrossSectionInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCutoffElasticCrossSectionInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the residual atom incident energy grid can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setCutoffElasticResidualIncidentEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  endl_data_container.setCutoffElasticResidualIncidentEnergy(
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getCutoffElasticResidualIncidentEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the cutoff elastic average energy to the residual atom can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setCutoffElasticResidualEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.0;
  energy[1] = 0.1;
  energy[2] = 1.0;

  endl_data_container.setCutoffElasticResidualEnergy(
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getCutoffElasticResidualEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the cutoff elastic average energy to the residual atom can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setCutoffElasticResidualEnergyInterpType )
{
  endl_data_container.setCutoffElasticResidualEnergyInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCutoffElasticResidualEnergyInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setCutoffElasticResidualEnergyInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCutoffElasticResidualEnergyInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setCutoffElasticResidualEnergyInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCutoffElasticResidualEnergyInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setCutoffElasticResidualEnergyInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCutoffElasticResidualEnergyInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the scattered electron incident energy grid can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setCutoffElasticScatteredElectronIncidentEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  endl_data_container.setCutoffElasticScatteredElectronIncidentEnergy(
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getCutoffElasticScatteredElectronIncidentEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the average energy to the scattered electron can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setCutoffElasticScatteredElectronEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.0;
  energy[1] = 0.1;
  energy[2] = 1.0;

  endl_data_container.setCutoffElasticScatteredElectronEnergy(
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getCutoffElasticScatteredElectronEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the average energy to the scattered electron can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setCutoffElasticScatteredElectronEnergyInterpType )
{
  endl_data_container.setCutoffElasticScatteredElectronEnergyInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCutoffElasticScatteredElectronEnergyInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setCutoffElasticScatteredElectronEnergyInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCutoffElasticScatteredElectronEnergyInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setCutoffElasticScatteredElectronEnergyInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCutoffElasticScatteredElectronEnergyInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setCutoffElasticScatteredElectronEnergyInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCutoffElasticScatteredElectronEnergyInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the cutoff elastic angular energy grid can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setCutoffElasticAngularEnergyGrid )
{
  std::vector<double> angular_energy_grid(1), grid(1);
  angular_energy_grid[0] = 1.0;

  endl_data_container.setCutoffElasticAngularEnergyGrid(
                                    angular_energy_grid );

  grid = endl_data_container.getCutoffElasticAngularEnergyGrid();
  FRENSIE_CHECK_EQUAL( grid[0], angular_energy_grid[0] );
}

//---------------------------------------------------------------------------//
// Check that the elastic angles can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setCutoffElasticAnglesAtEnergy )
{
  std::vector<double> angles( 3 );
  angles[0] = -1.0;
  angles[1] = 0.0;
  angles[2] = 0.90;

  endl_data_container.setCutoffElasticAnglesAtEnergy( 1.0, angles );

  FRENSIE_CHECK_EQUAL( endl_data_container.getCutoffElasticAnglesAtEnergy(1.0),
                       angles );
}

//---------------------------------------------------------------------------//
// Check that the elastic pdf can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setCutoffElasticPDFAtEnergy )
{
  std::vector<double> pdf( 3 );
  pdf[0] = 0.1;
  pdf[1] = 0.2;
  pdf[2] = 0.7;

  endl_data_container.setCutoffElasticPDFAtEnergy( 1.0, pdf );

  FRENSIE_CHECK_EQUAL( endl_data_container.getCutoffElasticPDFAtEnergy(1.0),
                       pdf );
}

//---------------------------------------------------------------------------//
// Check that the elastic angles can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setCutoffElasticAngles )
{
  std::vector<double> angles( 3 );
  angles[0] = -1.0;
  angles[1] = 0.0;
  angles[2] = 0.90;

  double energy = 1.0;
  std::map<double, std::vector<double> > angles_map, test_angles_map;

  angles_map[energy] = angles;

  endl_data_container.setCutoffElasticAngles( angles_map );

  test_angles_map = endl_data_container.getCutoffElasticAngles();

  FRENSIE_CHECK_EQUAL( test_angles_map.find( 1.0 )->second,
                       angles );
}

//---------------------------------------------------------------------------//
// Check that the elastic pdf can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setCutoffElasticPDF )
{
  std::vector<double> pdf( 3 );
  pdf[0] = 0.1;
  pdf[1] = 0.2;
  pdf[2] = 0.7;

  double energy = 1.0;
  std::map<double, std::vector<double> > pdf_map, test_pdf_map;

  pdf_map[energy] = pdf;

  endl_data_container.setCutoffElasticPDF( pdf_map );

  test_pdf_map = endl_data_container.getCutoffElasticPDF();

  FRENSIE_CHECK_EQUAL( test_pdf_map.find( 1.0 )->second,
                       pdf );
}

//---------------------------------------------------------------------------//
// Check that the elastic pdf interpolation type can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setCutoffElasticPDFInterpType )
{
  endl_data_container.setCutoffElasticPDFInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCutoffElasticPDFInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setCutoffElasticPDFInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCutoffElasticPDFInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setCutoffElasticPDFInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCutoffElasticPDFInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setCutoffElasticPDFInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getCutoffElasticPDFInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the total elastic electron cross section can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setTotalElasticCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  endl_data_container.setTotalElasticCrossSection(
                        cross_section );

  FRENSIE_CHECK_EQUAL(
            endl_data_container.getTotalElasticCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the total elastic electron cross section interpolation type can
// be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setTotalElasticCrossSectionInterpType )
{
  endl_data_container.setTotalElasticCrossSectionInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getTotalElasticCrossSectionInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setTotalElasticCrossSectionInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getTotalElasticCrossSectionInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setTotalElasticCrossSectionInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getTotalElasticCrossSectionInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setTotalElasticCrossSectionInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getTotalElasticCrossSectionInterpType(),
                       Utility::LogLog::name() );
}

/*
//---------------------------------------------------------------------------//
// Check that the screened rutherford elastic electron cross section can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setScreenedRutherfordElasticCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 0.6e-6;
  cross_section[1] = 0.6e-1;
  cross_section[2] = 0.6;

  endl_data_container.setScreenedRutherfordElasticCrossSection(
                        cross_section );

  FRENSIE_CHECK_EQUAL(
            endl_data_container.getScreenedRutherfordElasticCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the screened Rutherford elastic normalization constant can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setScreenedRutherfordNormalizationConstant )
{
  std::vector<double> norm( 3 );
  norm[0] = 100;
  norm[1] = 200;
  norm[2] = 700;

  endl_data_container.setScreenedRutherfordNormalizationConstant( norm );

  FRENSIE_CHECK_EQUAL( endl_data_container.getScreenedRutherfordNormalizationConstant(),
                       norm );
}

//---------------------------------------------------------------------------//
// Check that Moliere's screening constant can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setMoliereScreeningConstant )
{
  std::vector<double> eta( 3 );
  eta[0] = 100;
  eta[1] = 0.0;
  eta[2] = 0.90;

  endl_data_container.setMoliereScreeningConstant( eta );

  FRENSIE_CHECK_EQUAL( endl_data_container.getMoliereScreeningConstant(),
                       eta );
}
*/


//---------------------------------------------------------------------------//
// TEST ELECTROIONIZATION ELECTRON DATA
//---------------------------------------------------------------------------//
// Check that the electroionization cross section energy grid can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
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

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getElectroionizationCrossSectionEnergyGrid( subshell ),
    electron_energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the electroionization electron cross section can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
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

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getElectroionizationCrossSection( subshell ),
    cross_section );
}

//---------------------------------------------------------------------------//
// Check that the electroionization electron cross section interpolation type
// can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setElectroionizationCrossSectionInterpType )
{
  unsigned subshell = 1;

  endl_data_container.setElectroionizationCrossSectionInterpType<Utility::LinLin>( subshell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getElectroionizationCrossSectionInterpType( subshell ),
                       Utility::LinLin::name() );

  endl_data_container.setElectroionizationCrossSectionInterpType<Utility::LinLog>( subshell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getElectroionizationCrossSectionInterpType( subshell ),
                       Utility::LinLog::name() );

  endl_data_container.setElectroionizationCrossSectionInterpType<Utility::LogLin>( subshell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getElectroionizationCrossSectionInterpType( subshell ),
                       Utility::LogLin::name() );

  endl_data_container.setElectroionizationCrossSectionInterpType<Utility::LogLog>( subshell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getElectroionizationCrossSectionInterpType( subshell ),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the incident energy grid for the electroionization scattered electron can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setElectroionizationAverageScatteredElectronIncidentEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  unsigned subshell = 1;

  endl_data_container.setElectroionizationAverageScatteredElectronIncidentEnergy(
    subshell,
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getElectroionizationAverageScatteredElectronIncidentEnergy( subshell ),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the electroionization average scattered electron energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
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

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getElectroionizationAverageScatteredElectronEnergy( subshell ),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the electroionization average scattered electron energy
// interpolation type can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setElectroionizationAverageScatteredElectronEnergyInterpType )
{
  unsigned subshell = 1;
  
  endl_data_container.setElectroionizationAverageScatteredElectronEnergyInterpType<Utility::LinLin>( subshell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getElectroionizationAverageScatteredElectronEnergyInterpType( subshell ),
                       Utility::LinLin::name() );

  endl_data_container.setElectroionizationAverageScatteredElectronEnergyInterpType<Utility::LinLog>( subshell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getElectroionizationAverageScatteredElectronEnergyInterpType( subshell ),
                       Utility::LinLog::name() );

  endl_data_container.setElectroionizationAverageScatteredElectronEnergyInterpType<Utility::LogLin>( subshell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getElectroionizationAverageScatteredElectronEnergyInterpType( subshell ),
                       Utility::LogLin::name() );

  endl_data_container.setElectroionizationAverageScatteredElectronEnergyInterpType<Utility::LogLog>( subshell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getElectroionizationAverageScatteredElectronEnergyInterpType( subshell ),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the incident energy grid for the electroionization recoil can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setElectroionizationAverageRecoilElectronIncidentEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  unsigned subshell = 1;

  endl_data_container.setElectroionizationAverageRecoilElectronIncidentEnergy(
    subshell,
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getElectroionizationAverageRecoilElectronIncidentEnergy( subshell ),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the electroionization average recoil energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
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

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getElectroionizationAverageRecoilElectronEnergy( subshell ),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the electroionization average recoil energy interpolation type
// can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setElectroionizationAverageRecoilElectronEnergyInterpType )
{
  unsigned subshell = 1;
  
  endl_data_container.setElectroionizationAverageRecoilElectronEnergyInterpType<Utility::LinLin>( subshell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getElectroionizationAverageRecoilElectronEnergyInterpType( subshell ),
                       Utility::LinLin::name() );

  endl_data_container.setElectroionizationAverageRecoilElectronEnergyInterpType<Utility::LinLog>( subshell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getElectroionizationAverageRecoilElectronEnergyInterpType( subshell ),
                       Utility::LinLog::name() );

  endl_data_container.setElectroionizationAverageRecoilElectronEnergyInterpType<Utility::LogLin>( subshell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getElectroionizationAverageRecoilElectronEnergyInterpType( subshell ),
                       Utility::LogLin::name() );

  endl_data_container.setElectroionizationAverageRecoilElectronEnergyInterpType<Utility::LogLog>( subshell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getElectroionizationAverageRecoilElectronEnergyInterpType( subshell ),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the electroionization recoil energy grid can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setElectroionizationRecoilEnergyGrid )
{
  std::vector<double> energy_grid(1), grid(1);
  energy_grid[0] = 1.0;

  unsigned subshell = 1;

  endl_data_container.setElectroionizationRecoilEnergyGrid(
                                subshell,
                                energy_grid );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getElectroionizationRecoilEnergyGrid( subshell ),
    energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the electroionization recoil energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setElectroionizationRecoilEnergyAtIncidentEnergy )
{
  std::vector<double> recoil_energy( 3 );
  recoil_energy[0] = 0.01;
  recoil_energy[1] = 0.001;
  recoil_energy[2] = 0.0001;

  unsigned subshell = 1;
  double energy = 1.0;

  endl_data_container.setElectroionizationRecoilEnergyAtIncidentEnergy(
                                subshell,
                                energy,
                                recoil_energy );

  FRENSIE_CHECK_EQUAL( endl_data_container.getElectroionizationRecoilEnergyAtEnergy(subshell, energy),
                       recoil_energy );
}

//---------------------------------------------------------------------------//
// Check that the electroionization recoil pdf can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setElectroionizationRecoilPDFAtIncidentEnergy )
{
  std::vector<double> recoil_pdf( 3 );
  recoil_pdf[0] = 1.0;
  recoil_pdf[1] = 2.0;
  recoil_pdf[2] = 5.0;

  unsigned subshell = 1;
  double energy = 1.0;

  endl_data_container.setElectroionizationRecoilPDFAtIncidentEnergy(
                                subshell,
                                energy,
                                recoil_pdf );

  FRENSIE_CHECK_EQUAL( endl_data_container.getElectroionizationRecoilPDFAtEnergy( subshell, energy ),
                       recoil_pdf );
}

//---------------------------------------------------------------------------//
// Check that the electroionization recoil energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
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

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getElectroionizationRecoilEnergyAtEnergy(subshell, energy_bin),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the electroionization recoil pdf can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
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

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getElectroionizationRecoilPDFAtEnergy( subshell, energy_bin ),
    pdf );
}

//---------------------------------------------------------------------------//
// Check that the electroionization recoil pdf interpolation type can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setElectroionizationRecoilPDFInterpType )
{
  unsigned subshell = 1;

  endl_data_container.setElectroionizationRecoilPDFInterpType<Utility::LinLin>( subshell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getElectroionizationRecoilPDFInterpType( subshell ),
                       Utility::LinLin::name() );

  endl_data_container.setElectroionizationRecoilPDFInterpType<Utility::LinLog>( subshell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getElectroionizationRecoilPDFInterpType( subshell ),
                       Utility::LinLog::name() );

  endl_data_container.setElectroionizationRecoilPDFInterpType<Utility::LogLin>( subshell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getElectroionizationRecoilPDFInterpType( subshell ),
                       Utility::LogLin::name() );

  endl_data_container.setElectroionizationRecoilPDFInterpType<Utility::LogLog>( subshell );

  FRENSIE_CHECK_EQUAL( endl_data_container.getElectroionizationRecoilPDFInterpType( subshell ),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// TEST BREMSSTRAHLUNG ELECTRON DATA
//---------------------------------------------------------------------------//
// Check that the bremsstrahlung cross section energy grid can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setBremsstrahlungCrossSectionEnergyGrid )
{
  std::vector<double> electron_energy_grid( 3 );
  electron_energy_grid[0] = 1e-3;
  electron_energy_grid[1] = 1.0;
  electron_energy_grid[2] = 20.0;

  endl_data_container.setBremsstrahlungCrossSectionEnergyGrid(
    electron_energy_grid );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getBremsstrahlungCrossSectionEnergyGrid(),
    electron_energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung electron cross section can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setBremsstrahlungCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  endl_data_container.setBremsstrahlungCrossSection(
                        cross_section );

  FRENSIE_CHECK_EQUAL(
            endl_data_container.getBremsstrahlungCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung electron cross section interpolation type can
// be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setBremsstrahlungCrossSectionInterpType )
{
  endl_data_container.setBremsstrahlungCrossSectionInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getBremsstrahlungCrossSectionInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setBremsstrahlungCrossSectionInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getBremsstrahlungCrossSectionInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setBremsstrahlungCrossSectionInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getBremsstrahlungCrossSectionInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setBremsstrahlungCrossSectionInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getBremsstrahlungCrossSectionInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung energy grid for the secondary photon can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setBremsstrahlungAveragePhotonIncidentEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  endl_data_container.setBremsstrahlungAveragePhotonIncidentEnergy(
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getBremsstrahlungAveragePhotonIncidentEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung average energy of the secondary photon can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setBremsstrahlungAveragePhotonEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.001;
  energy[1] = 0.1;
  energy[2] = 1.0;

  endl_data_container.setBremsstrahlungAveragePhotonEnergy(
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getBremsstrahlungAveragePhotonEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung average energy of the secondary photon
// interpolation type can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setBremsstrahlungAveragePhotonEnergyInterpType )
{
  endl_data_container.setBremsstrahlungAveragePhotonEnergyInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getBremsstrahlungAveragePhotonEnergyInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setBremsstrahlungAveragePhotonEnergyInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getBremsstrahlungAveragePhotonEnergyInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setBremsstrahlungAveragePhotonEnergyInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getBremsstrahlungAveragePhotonEnergyInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setBremsstrahlungAveragePhotonEnergyInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getBremsstrahlungAveragePhotonEnergyInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung energy grid can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setBremsstrahlungPhotonEnergyGrid )
{
  std::vector<double> energy_grid(2), grid(2);
  energy_grid[0] = 1.0;
  energy_grid[1] = 2.0;

  endl_data_container.setBremsstrahlungPhotonEnergyGrid(
    energy_grid );

  grid = endl_data_container.getBremsstrahlungPhotonEnergyGrid();
  FRENSIE_CHECK_EQUAL( grid[0], energy_grid[0] );
  FRENSIE_CHECK_EQUAL( grid[1], energy_grid[1] );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung photon energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setBremsstrahlungPhotonEnergyAtIncidentEnergy )
{
  std::vector<double> photon_energy( 3 );
  photon_energy[0] = 0.01;
  photon_energy[1] = 0.001;
  photon_energy[2] = 0.0001;

  endl_data_container.setBremsstrahlungPhotonEnergyAtIncidentEnergy( 1.0,
                                                                   photon_energy );

  FRENSIE_CHECK_EQUAL( endl_data_container.getBremsstrahlungPhotonEnergyAtEnergy(1.0),
                       photon_energy );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung photon pdf can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setBremsstrahlungPhotonPDFAtIncidentEnergy )
{
  std::vector<double> photon_pdf( 3 );
  photon_pdf[0] = 1.0;
  photon_pdf[1] = 2.0;
  photon_pdf[2] = 5.0;

  endl_data_container.setBremsstrahlungPhotonPDFAtIncidentEnergy( 1.0,
                                                                photon_pdf );

  FRENSIE_CHECK_EQUAL( endl_data_container.getBremsstrahlungPhotonPDFAtEnergy(1.0),
                       photon_pdf );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung photon energy can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
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

  FRENSIE_CHECK_EQUAL( endl_data_container.getBremsstrahlungPhotonEnergyAtEnergy(energy_bin),
                       energy );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung photon pdf can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
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

  FRENSIE_CHECK_EQUAL( endl_data_container.getBremsstrahlungPhotonPDFAtEnergy(energy_bin),
                       pdf );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung photon pdf interpolation type can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setBremsstrahlungPhotonPDFInterpType )
{
  endl_data_container.setBremsstrahlungPhotonPDFInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getBremsstrahlungPhotonPDFInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setBremsstrahlungPhotonPDFInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getBremsstrahlungPhotonPDFInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setBremsstrahlungPhotonPDFInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getBremsstrahlungPhotonPDFInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setBremsstrahlungPhotonPDFInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getBremsstrahlungPhotonPDFInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung energy grid for the secondary electron can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setBremsstrahlungAverageElectronIncidentEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  endl_data_container.setBremsstrahlungAverageElectronIncidentEnergy(
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getBremsstrahlungAverageElectronIncidentEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung average energy of the secondary electron can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setBremsstrahlungAverageElectronEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.001;
  energy[1] = 0.1;
  energy[2] = 1.0;

  endl_data_container.setBremsstrahlungAverageElectronEnergy(
    energy );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getBremsstrahlungAverageElectronEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung average energy of the secondary electron
// interpolatio type can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setBremsstrahlungAverageElectronEnergyInterpType )
{
  endl_data_container.setBremsstrahlungAverageElectronEnergyInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getBremsstrahlungAverageElectronEnergyInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setBremsstrahlungAverageElectronEnergyInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getBremsstrahlungAverageElectronEnergyInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setBremsstrahlungAverageElectronEnergyInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getBremsstrahlungAverageElectronEnergyInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setBremsstrahlungAverageElectronEnergyInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getBremsstrahlungAverageElectronEnergyInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// TEST ATOMIC EXCITATION ELECTRON DATA
//---------------------------------------------------------------------------//
// Check that the atomic excitation cross section energy grid can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setAtomicExcitationEnergyGrid )
{
  std::vector<double> electron_energy_grid( 3 );
  electron_energy_grid[0] = 1e-3;
  electron_energy_grid[1] = 1.0;
  electron_energy_grid[2] = 20.0;

  endl_data_container.setAtomicExcitationEnergyGrid(
    electron_energy_grid );

  FRENSIE_CHECK_EQUAL(
    endl_data_container.getAtomicExcitationEnergyGrid(),
    electron_energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the atomic excitation electron cross section can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setAtomicExcitationCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  endl_data_container.setAtomicExcitationCrossSection(
                        cross_section );

  FRENSIE_CHECK_EQUAL(
            endl_data_container.getAtomicExcitationCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the atomic excitation electron cross section interpolation type
// can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setAtomicExcitationCrossSectionInterpType )
{
  endl_data_container.setAtomicExcitationCrossSectionInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getAtomicExcitationCrossSectionInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setAtomicExcitationCrossSectionInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getAtomicExcitationCrossSectionInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setAtomicExcitationCrossSectionInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getAtomicExcitationCrossSectionInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setAtomicExcitationCrossSectionInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getAtomicExcitationCrossSectionInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the atomic excitation energy loss can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setAtomicExcitationEnergyLoss )
{
  std::vector<double> energy_loss(3);
  energy_loss[0] = 1.0;
  energy_loss[1] = 5.0;
  energy_loss[2] = 10.0;

  endl_data_container.setAtomicExcitationEnergyLoss(
                                    energy_loss );

  FRENSIE_CHECK_EQUAL( endl_data_container.getAtomicExcitationEnergyLoss(),
                       energy_loss );
}

//---------------------------------------------------------------------------//
// Check that the atomic excitation energy loss interpolation type can be set
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   setAtomicExcitationEnergyLossInterpType )
{
  endl_data_container.setAtomicExcitationEnergyLossInterpType<Utility::LinLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getAtomicExcitationEnergyLossInterpType(),
                       Utility::LinLin::name() );

  endl_data_container.setAtomicExcitationEnergyLossInterpType<Utility::LinLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getAtomicExcitationEnergyLossInterpType(),
                       Utility::LinLog::name() );

  endl_data_container.setAtomicExcitationEnergyLossInterpType<Utility::LogLin>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getAtomicExcitationEnergyLossInterpType(),
                       Utility::LogLin::name() );

  endl_data_container.setAtomicExcitationEnergyLossInterpType<Utility::LogLog>();

  FRENSIE_CHECK_EQUAL( endl_data_container.getAtomicExcitationEnergyLossInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the data can be exported and imported
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   export_importData_ascii )
{
  const std::string test_ascii_file_name( "test_endl_data_container.txt" );

  endl_data_container.saveToFile( test_ascii_file_name, true );

  const Data::ENDLDataContainer
    endl_data_container_copy( test_ascii_file_name );

  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getAtomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getAtomicWeight(), 1.0 );

//---------------------------------------------------------------------------//
// TEST RELAXATION DATA
//---------------------------------------------------------------------------//
  FRENSIE_CHECK( endl_data_container_copy.getSubshells().count( 1 ) );
  FRENSIE_CHECK( endl_data_container_copy.getSubshells().count( 3 ) );
  FRENSIE_CHECK( endl_data_container_copy.getSubshells().count( 5 ) );
  FRENSIE_CHECK( !endl_data_container_copy.getSubshells().count( 0 ) );
  FRENSIE_CHECK( !endl_data_container_copy.getSubshells().count( 2 ) );
  FRENSIE_CHECK( !endl_data_container_copy.getSubshells().count( 4 ) );
  FRENSIE_CHECK( !endl_data_container_copy.getSubshells().count( 6 ) );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellOccupancy( 1 ),
    2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellOccupancy( 3 ),
    4 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellBindingEnergy( 1 ),
    0.1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellBindingEnergy( 3 ),
    0.2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellKineticEnergy( 1 ),
    0.1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellKineticEnergy( 3 ),
    0.2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellAverageRadius( 1 ),
    0.1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellAverageRadius( 3 ),
    0.2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellRadiativeLevel( 1 ),
    0.1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellRadiativeLevel( 3 ),
    0.2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellNonRadiativeLevel( 1 ),
    0.1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellNonRadiativeLevel( 3 ),
    0.2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getLocalDepositionPerInitialVacancy( 1 ),
    0.1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getLocalDepositionPerInitialVacancy( 3 ),
    0.2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAveragePhotonsPerInitialVacancy( 1 ),
    2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAveragePhotonsPerInitialVacancy( 3 ),
    4 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAveragePhotonEnergyPerInitialVacancy( 1 ),
    0.1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAveragePhotonEnergyPerInitialVacancy( 3 ),
    0.2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAverageElectronsPerInitialVacancy( 1 ),
    2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAverageElectronsPerInitialVacancy( 3 ),
    4 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAverageElectronEnergyPerInitialVacancy( 1 ),
    0.1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAverageElectronEnergyPerInitialVacancy( 3 ),
    0.2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getRadiativeTransitionProbability( 1 ).size(),
    1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getRadiativeTransitionEnergy( 1 ).size(),
    1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getNonRadiativeTransitionProbability( 1 ).size(),
    1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getNonRadiativeTransitionEnergy( 1 ).size(),
    1 );

//---------------------------------------------------------------------------//
// TEST COHERENT PHOTON DATA
//---------------------------------------------------------------------------//

  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentCrossSectionEnergyGrid().size(), 3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentCrossSection().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container.getCoherentCrossSectionInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentFormFactorArgument().size(), 3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentFormFactor().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getCoherentFormFactorInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentImaginaryAnomalousFactorIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentImaginaryAnomalousFactor().size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getCoherentImaginaryAnomalousFactorInterpType(),
                       Utility::LogLog::name() );
                      
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentRealAnomalousFactorIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentRealAnomalousFactor().size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getCoherentRealAnomalousFactorInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentAveragePhotonIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentAveragePhotonEnergy().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getCoherentAveragePhotonEnergyInterpType(),
                       Utility::LogLog::name() );

//---------------------------------------------------------------------------//
// TEST INCOHERENT PHOTON DATA
//---------------------------------------------------------------------------//

  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getIncoherentCrossSectionEnergyGrid().size(), 3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getIncoherentCrossSection().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getIncoherentCrossSectionInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getIncoherentScatteringFunctionArgument().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getIncoherentScatteringFunction().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getIncoherentScatteringFunctionInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getIncoherentAveragePhotonIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getIncoherentAveragePhotonEnergy().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getIncoherentAveragePhotonEnergyInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getIncoherentAverageElectronIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getIncoherentAverageElectronEnergy().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getIncoherentAverageElectronEnergyInterpType(),
                       Utility::LogLog::name() );

//---------------------------------------------------------------------------//
// TEST PHOTOELECTRIC PHOTON DATA
//---------------------------------------------------------------------------//

  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricCrossSectionEnergyGrid().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricCrossSection().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPhotoelectricCrossSectionInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAverageResidualIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAverageResidualEnergy().size(),
    3 );

  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPhotoelectricAverageResidualEnergyInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAveragePhotonsIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAveragePhotonsEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPhotoelectricAveragePhotonsEnergyInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAverageElectronsIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAverageElectronsEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPhotoelectricAverageElectronsEnergyInterpType(),
                       Utility::LogLog::name() );

//---------------------------------------------------------------------------//
// TEST PHOTOELECTRIC PHOTON DATA BY SUBSHELL
//---------------------------------------------------------------------------//

  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricCrossSectionEnergyGrid(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricCrossSection(1u).size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPhotoelectricCrossSectionInterpType(1u),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAverageResidualIncidentEnergy(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAverageResidualEnergy(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPhotoelectricAverageResidualEnergyInterpType(1u),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAveragePhotonsIncidentEnergy(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAveragePhotonsEnergy(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPhotoelectricAveragePhotonsEnergyInterpType(1u),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAverageElectronsIncidentEnergy(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAverageElectronsEnergy(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPhotoelectricAverageElectronsEnergyInterpType(1u),
                       Utility::LogLog::name() );

//---------------------------------------------------------------------------//
// TEST PAIR PRODUCTION PHOTON DATA
//---------------------------------------------------------------------------//

  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPairProductionCrossSectionEnergyGrid().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPairProductionCrossSection().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPairProductionCrossSectionInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPairProductionAveragePositronIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPairProductionAveragePositronEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPairProductionAveragePositronEnergyInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPairProductionAverageElectronIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPairProductionAverageElectronEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPairProductionAverageElectronEnergyInterpType(),
                       Utility::LogLog::name() );

//---------------------------------------------------------------------------//
// TEST TRIPLET PRODUCTION PHOTON DATA
//---------------------------------------------------------------------------//

  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getTripletProductionCrossSectionEnergyGrid().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getTripletProductionCrossSection().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getTripletProductionCrossSectionInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getTripletProductionAveragePositronIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getTripletProductionAveragePositronEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getTripletProductionAveragePositronEnergyInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getTripletProductionAverageElectronIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getTripletProductionAverageElectronEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getTripletProductionAverageElectronEnergyInterpType(),
                       Utility::LogLog::name() );

//---------------------------------------------------------------------------//
// TEST ELASTIC ELECTRON DATA
//---------------------------------------------------------------------------//
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElasticEnergyGrid().size(), 3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCutoffElasticCrossSection().size(),
    3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getCutoffElasticCrossSectionInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCutoffElasticResidualIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCutoffElasticResidualEnergy().size(),
    3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getCutoffElasticResidualEnergyInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCutoffElasticScatteredElectronIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCutoffElasticScatteredElectronEnergy().size(),
    3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getCutoffElasticScatteredElectronEnergyInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCutoffElasticAngularEnergyGrid().size(),
    1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCutoffElasticAngularEnergyGrid().front(),
    1.0 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCutoffElasticAnglesAtEnergy(1.0).size(), 3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCutoffElasticPDFAtEnergy(1.0).size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getCutoffElasticPDFInterpType(),
                       Utility::LogLog::name() );
/*
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getScreenedRutherfordElasticCrossSection().size(),
		       3u );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getScreenedRutherfordNormalizationConstant().size(), 3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getMoliereScreeningConstant().size(), 3 );
*/
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getTotalElasticCrossSection().size(),
		       3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getTotalElasticCrossSectionInterpType(),
                       Utility::LogLog::name() );

//---------------------------------------------------------------------------//
// TEST ELECTROIONIZATION ELECTRON DATA
//---------------------------------------------------------------------------//
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationCrossSectionEnergyGrid(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationCrossSection(1u).size(),
    3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getElectroionizationCrossSectionInterpType(1u),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationAverageScatteredElectronIncidentEnergy(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationAverageScatteredElectronEnergy(1u).size(),
    3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getElectroionizationAverageScatteredElectronEnergyInterpType(1u),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationAverageRecoilElectronIncidentEnergy(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationAverageRecoilElectronEnergy(1u).size(),
    3u );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationRecoilEnergyGrid(1u).size(),
    1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationRecoilEnergyGrid(1u).front(),
    1.0 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationRecoilEnergyAtEnergy(1u, 1.0).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationRecoilPDFAtEnergy(1u, 1.0).size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getElectroionizationRecoilPDFInterpType(1u),
                       Utility::LogLog::name() );

//---------------------------------------------------------------------------//
// TEST BREMSSTRAHLUNG ELECTRON DATA
//---------------------------------------------------------------------------//
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungCrossSectionEnergyGrid().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungCrossSection().size(),
    3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getBremsstrahlungCrossSectionInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungAverageElectronIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungAverageElectronEnergy().size(),
    3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getBremsstrahlungAverageElectronEnergyInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungPhotonEnergyGrid().size(),
    2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungPhotonEnergyGrid().front(),
    1.0 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungPhotonEnergyAtEnergy(1.0).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungPhotonPDFAtEnergy(1.0).size(),
    3 );
    FRENSIE_CHECK_EQUAL( endl_data_container_copy.getBremsstrahlungPhotonPDFInterpType(),
                         Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungAveragePhotonIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungAveragePhotonEnergy().size(),
    3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getBremsstrahlungAveragePhotonEnergyInterpType(),
                       Utility::LogLog::name() );

//---------------------------------------------------------------------------//
// TEST ATOMIC EXCITATION ELECTRON DATA
//---------------------------------------------------------------------------//
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAtomicExcitationEnergyGrid().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAtomicExcitationCrossSection().size(),
    3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getAtomicExcitationCrossSectionInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAtomicExcitationEnergyLoss().size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getAtomicExcitationEnergyLossInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the data can be exported and imported
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   export_importData_binary )
{
  const std::string test_binary_file_name( "test_endl_data_container.bin" );

  endl_data_container.saveToFile( test_binary_file_name, true );

  const Data::ENDLDataContainer
    endl_data_container_copy( test_binary_file_name );

//---------------------------------------------------------------------------//
// TEST RELAXATION DATA
//---------------------------------------------------------------------------//
  FRENSIE_CHECK( endl_data_container_copy.getSubshells().count( 1 ) );
  FRENSIE_CHECK( endl_data_container_copy.getSubshells().count( 3 ) );
  FRENSIE_CHECK( endl_data_container_copy.getSubshells().count( 5 ) );
  FRENSIE_CHECK( !endl_data_container_copy.getSubshells().count( 0 ) );
  FRENSIE_CHECK( !endl_data_container_copy.getSubshells().count( 2 ) );
  FRENSIE_CHECK( !endl_data_container_copy.getSubshells().count( 4 ) );
  FRENSIE_CHECK( !endl_data_container_copy.getSubshells().count( 6 ) );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellOccupancy( 1 ),
    2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellOccupancy( 3 ),
    4 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellBindingEnergy( 1 ),
    0.1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellBindingEnergy( 3 ),
    0.2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellKineticEnergy( 1 ),
    0.1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellKineticEnergy( 3 ),
    0.2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellAverageRadius( 1 ),
    0.1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellAverageRadius( 3 ),
    0.2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellRadiativeLevel( 1 ),
    0.1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellRadiativeLevel( 3 ),
    0.2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellNonRadiativeLevel( 1 ),
    0.1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellNonRadiativeLevel( 3 ),
    0.2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getLocalDepositionPerInitialVacancy( 1 ),
    0.1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getLocalDepositionPerInitialVacancy( 3 ),
    0.2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAveragePhotonsPerInitialVacancy( 1 ),
    2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAveragePhotonsPerInitialVacancy( 3 ),
    4 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAveragePhotonEnergyPerInitialVacancy( 1 ),
    0.1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAveragePhotonEnergyPerInitialVacancy( 3 ),
    0.2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAverageElectronsPerInitialVacancy( 1 ),
    2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAverageElectronsPerInitialVacancy( 3 ),
    4 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAverageElectronEnergyPerInitialVacancy( 1 ),
    0.1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAverageElectronEnergyPerInitialVacancy( 3 ),
    0.2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getRadiativeTransitionProbability( 1 ).size(),
    1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getRadiativeTransitionEnergy( 1 ).size(),
    1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getNonRadiativeTransitionProbability( 1 ).size(),
    1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getNonRadiativeTransitionEnergy( 1 ).size(),
    1 );

//---------------------------------------------------------------------------//
// TEST COHERENT PHOTON DATA
//---------------------------------------------------------------------------//

  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentCrossSectionEnergyGrid().size(), 3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentCrossSection().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container.getCoherentCrossSectionInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentFormFactorArgument().size(), 3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentFormFactor().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getCoherentFormFactorInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentImaginaryAnomalousFactorIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentImaginaryAnomalousFactor().size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getCoherentImaginaryAnomalousFactorInterpType(),
                       Utility::LogLog::name() );
                      
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentRealAnomalousFactorIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentRealAnomalousFactor().size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getCoherentRealAnomalousFactorInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentAveragePhotonIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentAveragePhotonEnergy().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getCoherentAveragePhotonEnergyInterpType(),
                       Utility::LogLog::name() );

//---------------------------------------------------------------------------//
// TEST INCOHERENT PHOTON DATA
//---------------------------------------------------------------------------//

  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getIncoherentCrossSectionEnergyGrid().size(), 3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getIncoherentCrossSection().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getIncoherentCrossSectionInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getIncoherentScatteringFunctionArgument().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getIncoherentScatteringFunction().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getIncoherentScatteringFunctionInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getIncoherentAveragePhotonIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getIncoherentAveragePhotonEnergy().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getIncoherentAveragePhotonEnergyInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getIncoherentAverageElectronIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getIncoherentAverageElectronEnergy().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getIncoherentAverageElectronEnergyInterpType(),
                       Utility::LogLog::name() );

//---------------------------------------------------------------------------//
// TEST PHOTOELECTRIC PHOTON DATA
//---------------------------------------------------------------------------//

  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricCrossSectionEnergyGrid().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricCrossSection().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPhotoelectricCrossSectionInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAverageResidualIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAverageResidualEnergy().size(),
    3 );

  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPhotoelectricAverageResidualEnergyInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAveragePhotonsIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAveragePhotonsEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPhotoelectricAveragePhotonsEnergyInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAverageElectronsIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAverageElectronsEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPhotoelectricAverageElectronsEnergyInterpType(),
                       Utility::LogLog::name() );

//---------------------------------------------------------------------------//
// TEST PHOTOELECTRIC PHOTON DATA BY SUBSHELL
//---------------------------------------------------------------------------//

  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricCrossSectionEnergyGrid(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricCrossSection(1u).size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPhotoelectricCrossSectionInterpType(1u),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAverageResidualIncidentEnergy(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAverageResidualEnergy(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPhotoelectricAverageResidualEnergyInterpType(1u),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAveragePhotonsIncidentEnergy(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAveragePhotonsEnergy(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPhotoelectricAveragePhotonsEnergyInterpType(1u),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAverageElectronsIncidentEnergy(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAverageElectronsEnergy(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPhotoelectricAverageElectronsEnergyInterpType(1u),
                       Utility::LogLog::name() );

//---------------------------------------------------------------------------//
// TEST PAIR PRODUCTION PHOTON DATA
//---------------------------------------------------------------------------//

  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPairProductionCrossSectionEnergyGrid().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPairProductionCrossSection().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPairProductionCrossSectionInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPairProductionAveragePositronIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPairProductionAveragePositronEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPairProductionAveragePositronEnergyInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPairProductionAverageElectronIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPairProductionAverageElectronEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPairProductionAverageElectronEnergyInterpType(),
                       Utility::LogLog::name() );

//---------------------------------------------------------------------------//
// TEST TRIPLET PRODUCTION PHOTON DATA
//---------------------------------------------------------------------------//

  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getTripletProductionCrossSectionEnergyGrid().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getTripletProductionCrossSection().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getTripletProductionCrossSectionInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getTripletProductionAveragePositronIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getTripletProductionAveragePositronEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getTripletProductionAveragePositronEnergyInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getTripletProductionAverageElectronIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getTripletProductionAverageElectronEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getTripletProductionAverageElectronEnergyInterpType(),
                       Utility::LogLog::name() );

//---------------------------------------------------------------------------//
// TEST ELASTIC ELECTRON DATA
//---------------------------------------------------------------------------//
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElasticEnergyGrid().size(), 3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCutoffElasticCrossSection().size(),
    3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getCutoffElasticCrossSectionInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCutoffElasticResidualIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCutoffElasticResidualEnergy().size(),
    3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getCutoffElasticResidualEnergyInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCutoffElasticScatteredElectronIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCutoffElasticScatteredElectronEnergy().size(),
    3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getCutoffElasticScatteredElectronEnergyInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCutoffElasticAngularEnergyGrid().size(),
    1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCutoffElasticAngularEnergyGrid().front(),
    1.0 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCutoffElasticAnglesAtEnergy(1.0).size(), 3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCutoffElasticPDFAtEnergy(1.0).size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getCutoffElasticPDFInterpType(),
                       Utility::LogLog::name() );
/*
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getScreenedRutherfordElasticCrossSection().size(),
		       3u );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getScreenedRutherfordNormalizationConstant().size(), 3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getMoliereScreeningConstant().size(), 3 );
*/
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getTotalElasticCrossSection().size(),
		       3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getTotalElasticCrossSectionInterpType(),
                       Utility::LogLog::name() );

//---------------------------------------------------------------------------//
// TEST ELECTROIONIZATION ELECTRON DATA
//---------------------------------------------------------------------------//
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationCrossSectionEnergyGrid(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationCrossSection(1u).size(),
    3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getElectroionizationCrossSectionInterpType(1u),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationAverageScatteredElectronIncidentEnergy(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationAverageScatteredElectronEnergy(1u).size(),
    3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getElectroionizationAverageScatteredElectronEnergyInterpType(1u),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationAverageRecoilElectronIncidentEnergy(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationAverageRecoilElectronEnergy(1u).size(),
    3u );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationRecoilEnergyGrid(1u).size(),
    1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationRecoilEnergyGrid(1u).front(),
    1.0 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationRecoilEnergyAtEnergy(1u, 1.0).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationRecoilPDFAtEnergy(1u, 1.0).size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getElectroionizationRecoilPDFInterpType(1u),
                       Utility::LogLog::name() );

//---------------------------------------------------------------------------//
// TEST BREMSSTRAHLUNG ELECTRON DATA
//---------------------------------------------------------------------------//
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungCrossSectionEnergyGrid().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungCrossSection().size(),
    3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getBremsstrahlungCrossSectionInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungAverageElectronIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungAverageElectronEnergy().size(),
    3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getBremsstrahlungAverageElectronEnergyInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungPhotonEnergyGrid().size(),
    2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungPhotonEnergyGrid().front(),
    1.0 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungPhotonEnergyAtEnergy(1.0).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungPhotonPDFAtEnergy(1.0).size(),
    3 );
    FRENSIE_CHECK_EQUAL( endl_data_container_copy.getBremsstrahlungPhotonPDFInterpType(),
                         Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungAveragePhotonIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungAveragePhotonEnergy().size(),
    3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getBremsstrahlungAveragePhotonEnergyInterpType(),
                       Utility::LogLog::name() );

//---------------------------------------------------------------------------//
// TEST ATOMIC EXCITATION ELECTRON DATA
//---------------------------------------------------------------------------//
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAtomicExcitationEnergyGrid().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAtomicExcitationCrossSection().size(),
    3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getAtomicExcitationCrossSectionInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAtomicExcitationEnergyLoss().size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getAtomicExcitationEnergyLossInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// Check that the data can be exported and imported
FRENSIE_UNIT_TEST( ENDLDataContainer,
                   export_importData_xml )
{
  const std::string test_xml_file_name( "test_endl_data_container.xml" );

  endl_data_container.saveToFile( test_xml_file_name, true );

  const Data::ENDLDataContainer
    endl_data_container_copy( test_xml_file_name );

  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAtomicNumber(), 1 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getAtomicWeight(), 1.0 );

//---------------------------------------------------------------------------//
// TEST RELAXATION DATA
//---------------------------------------------------------------------------//

  FRENSIE_CHECK( endl_data_container_copy.getSubshells().count( 1 ) );
  FRENSIE_CHECK( endl_data_container_copy.getSubshells().count( 3 ) );
  FRENSIE_CHECK( endl_data_container_copy.getSubshells().count( 5 ) );
  FRENSIE_CHECK( !endl_data_container_copy.getSubshells().count( 0 ) );
  FRENSIE_CHECK( !endl_data_container_copy.getSubshells().count( 2 ) );
  FRENSIE_CHECK( !endl_data_container_copy.getSubshells().count( 4 ) );
  FRENSIE_CHECK( !endl_data_container_copy.getSubshells().count( 6 ) );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellOccupancy( 1 ),
    2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellOccupancy( 3 ),
    4 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellBindingEnergy( 1 ),
    0.1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellBindingEnergy( 3 ),
    0.2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellKineticEnergy( 1 ),
    0.1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellKineticEnergy( 3 ),
    0.2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellAverageRadius( 1 ),
    0.1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellAverageRadius( 3 ),
    0.2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellRadiativeLevel( 1 ),
    0.1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellRadiativeLevel( 3 ),
    0.2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellNonRadiativeLevel( 1 ),
    0.1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getSubshellNonRadiativeLevel( 3 ),
    0.2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getLocalDepositionPerInitialVacancy( 1 ),
    0.1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getLocalDepositionPerInitialVacancy( 3 ),
    0.2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAveragePhotonsPerInitialVacancy( 1 ),
    2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAveragePhotonsPerInitialVacancy( 3 ),
    4 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAveragePhotonEnergyPerInitialVacancy( 1 ),
    0.1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAveragePhotonEnergyPerInitialVacancy( 3 ),
    0.2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAverageElectronsPerInitialVacancy( 1 ),
    2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAverageElectronsPerInitialVacancy( 3 ),
    4 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAverageElectronEnergyPerInitialVacancy( 1 ),
    0.1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAverageElectronEnergyPerInitialVacancy( 3 ),
    0.2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getRadiativeTransitionProbability( 1 ).size(),
    1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getRadiativeTransitionEnergy( 1 ).size(),
    1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getNonRadiativeTransitionProbability( 1 ).size(),
    1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getNonRadiativeTransitionEnergy( 1 ).size(),
    1 );

//---------------------------------------------------------------------------//
// TEST COHERENT PHOTON DATA
//---------------------------------------------------------------------------//

  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentCrossSectionEnergyGrid().size(), 3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentCrossSection().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container.getCoherentCrossSectionInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentFormFactorArgument().size(), 3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentFormFactor().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getCoherentFormFactorInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentImaginaryAnomalousFactorIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentImaginaryAnomalousFactor().size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getCoherentImaginaryAnomalousFactorInterpType(),
                       Utility::LogLog::name() );
                      
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentRealAnomalousFactorIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentRealAnomalousFactor().size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getCoherentRealAnomalousFactorInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentAveragePhotonIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCoherentAveragePhotonEnergy().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getCoherentAveragePhotonEnergyInterpType(),
                       Utility::LogLog::name() );

//---------------------------------------------------------------------------//
// TEST INCOHERENT PHOTON DATA
//---------------------------------------------------------------------------//

  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getIncoherentCrossSectionEnergyGrid().size(), 3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getIncoherentCrossSection().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getIncoherentCrossSectionInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getIncoherentScatteringFunctionArgument().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getIncoherentScatteringFunction().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getIncoherentScatteringFunctionInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getIncoherentAveragePhotonIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getIncoherentAveragePhotonEnergy().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getIncoherentAveragePhotonEnergyInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getIncoherentAverageElectronIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getIncoherentAverageElectronEnergy().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getIncoherentAverageElectronEnergyInterpType(),
                       Utility::LogLog::name() );

//---------------------------------------------------------------------------//
// TEST PHOTOELECTRIC PHOTON DATA
//---------------------------------------------------------------------------//

  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricCrossSectionEnergyGrid().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricCrossSection().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPhotoelectricCrossSectionInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAverageResidualIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAverageResidualEnergy().size(),
    3 );

  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPhotoelectricAverageResidualEnergyInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAveragePhotonsIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAveragePhotonsEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPhotoelectricAveragePhotonsEnergyInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAverageElectronsIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAverageElectronsEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPhotoelectricAverageElectronsEnergyInterpType(),
                       Utility::LogLog::name() );

//---------------------------------------------------------------------------//
// TEST PHOTOELECTRIC PHOTON DATA BY SUBSHELL
//---------------------------------------------------------------------------//

  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricCrossSectionEnergyGrid(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricCrossSection(1u).size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPhotoelectricCrossSectionInterpType(1u),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAverageResidualIncidentEnergy(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAverageResidualEnergy(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPhotoelectricAverageResidualEnergyInterpType(1u),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAveragePhotonsIncidentEnergy(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAveragePhotonsEnergy(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPhotoelectricAveragePhotonsEnergyInterpType(1u),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAverageElectronsIncidentEnergy(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPhotoelectricAverageElectronsEnergy(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPhotoelectricAverageElectronsEnergyInterpType(1u),
                       Utility::LogLog::name() );

//---------------------------------------------------------------------------//
// TEST PAIR PRODUCTION PHOTON DATA
//---------------------------------------------------------------------------//

  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPairProductionCrossSectionEnergyGrid().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPairProductionCrossSection().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPairProductionCrossSectionInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPairProductionAveragePositronIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPairProductionAveragePositronEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPairProductionAveragePositronEnergyInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPairProductionAverageElectronIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getPairProductionAverageElectronEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getPairProductionAverageElectronEnergyInterpType(),
                       Utility::LogLog::name() );

//---------------------------------------------------------------------------//
// TEST TRIPLET PRODUCTION PHOTON DATA
//---------------------------------------------------------------------------//

  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getTripletProductionCrossSectionEnergyGrid().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getTripletProductionCrossSection().size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getTripletProductionCrossSectionInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getTripletProductionAveragePositronIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getTripletProductionAveragePositronEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getTripletProductionAveragePositronEnergyInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getTripletProductionAverageElectronIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getTripletProductionAverageElectronEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getTripletProductionAverageElectronEnergyInterpType(),
                       Utility::LogLog::name() );

//---------------------------------------------------------------------------//
// TEST ELASTIC ELECTRON DATA
//---------------------------------------------------------------------------//
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElasticEnergyGrid().size(), 3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCutoffElasticCrossSection().size(),
    3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getCutoffElasticCrossSectionInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCutoffElasticResidualIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCutoffElasticResidualEnergy().size(),
    3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getCutoffElasticResidualEnergyInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCutoffElasticScatteredElectronIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCutoffElasticScatteredElectronEnergy().size(),
    3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getCutoffElasticScatteredElectronEnergyInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCutoffElasticAngularEnergyGrid().size(),
    1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCutoffElasticAngularEnergyGrid().front(),
    1.0 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCutoffElasticAnglesAtEnergy(1.0).size(), 3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getCutoffElasticPDFAtEnergy(1.0).size(), 3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getCutoffElasticPDFInterpType(),
                       Utility::LogLog::name() );
/*
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getScreenedRutherfordElasticCrossSection().size(),
		       3u );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getScreenedRutherfordNormalizationConstant().size(), 3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getMoliereScreeningConstant().size(), 3 );
*/
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getTotalElasticCrossSection().size(),
		       3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getTotalElasticCrossSectionInterpType(),
                       Utility::LogLog::name() );

//---------------------------------------------------------------------------//
// TEST ELECTROIONIZATION ELECTRON DATA
//---------------------------------------------------------------------------//
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationCrossSectionEnergyGrid(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationCrossSection(1u).size(),
    3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getElectroionizationCrossSectionInterpType(1u),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationAverageScatteredElectronIncidentEnergy(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationAverageScatteredElectronEnergy(1u).size(),
    3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getElectroionizationAverageScatteredElectronEnergyInterpType(1u),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationAverageRecoilElectronIncidentEnergy(1u).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationAverageRecoilElectronEnergy(1u).size(),
    3u );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationRecoilEnergyGrid(1u).size(),
    1 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationRecoilEnergyGrid(1u).front(),
    1.0 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationRecoilEnergyAtEnergy(1u, 1.0).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getElectroionizationRecoilPDFAtEnergy(1u, 1.0).size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getElectroionizationRecoilPDFInterpType(1u),
                       Utility::LogLog::name() );

//---------------------------------------------------------------------------//
// TEST BREMSSTRAHLUNG ELECTRON DATA
//---------------------------------------------------------------------------//
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungCrossSectionEnergyGrid().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungCrossSection().size(),
    3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getBremsstrahlungCrossSectionInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungAverageElectronIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungAverageElectronEnergy().size(),
    3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getBremsstrahlungAverageElectronEnergyInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungPhotonEnergyGrid().size(),
    2 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungPhotonEnergyGrid().front(),
    1.0 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungPhotonEnergyAtEnergy(1.0).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungPhotonPDFAtEnergy(1.0).size(),
    3 );
    FRENSIE_CHECK_EQUAL( endl_data_container_copy.getBremsstrahlungPhotonPDFInterpType(),
                         Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungAveragePhotonIncidentEnergy().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getBremsstrahlungAveragePhotonEnergy().size(),
    3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getBremsstrahlungAveragePhotonEnergyInterpType(),
                       Utility::LogLog::name() );

//---------------------------------------------------------------------------//
// TEST ATOMIC EXCITATION ELECTRON DATA
//---------------------------------------------------------------------------//
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAtomicExcitationEnergyGrid().size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAtomicExcitationCrossSection().size(),
    3u );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getAtomicExcitationCrossSectionInterpType(),
                       Utility::LogLog::name() );
  FRENSIE_CHECK_EQUAL(
    endl_data_container_copy.getAtomicExcitationEnergyLoss().size(),
    3 );
  FRENSIE_CHECK_EQUAL( endl_data_container_copy.getAtomicExcitationEnergyLossInterpType(),
                       Utility::LogLog::name() );
}

//---------------------------------------------------------------------------//
// end tstENDLDataContainer.cpp
//---------------------------------------------------------------------------//

