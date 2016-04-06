//---------------------------------------------------------------------------//
//!
//! \file   tstEvaluatedElectronDataContainer.cpp
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
#include "Data_EvaluatedElectronVolatileDataContainer.hpp"
#include "Data_EvaluatedElectronDataContainer.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"


//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Data::EvaluatedElectronVolatileDataContainer evaluated_electron_data_container;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the atomic number can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, setAtomicNumber )
{
  evaluated_electron_data_container.setAtomicNumber( 1u );
  
  TEST_EQUALITY_CONST(
    evaluated_electron_data_container.getAtomicNumber(), 1u );
}

//---------------------------------------------------------------------------//
// Check that the subshells can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, setSubshells )
{
  std::set<unsigned> subshells;
  subshells.insert( 1 );

  evaluated_electron_data_container.setSubshells( subshells );
  
  TEST_ASSERT( evaluated_electron_data_container.getSubshells().count( 1 ) );
  TEST_ASSERT( !evaluated_electron_data_container.getSubshells().count( 0 ) );
  TEST_ASSERT( !evaluated_electron_data_container.getSubshells().count( 2 ) );
}

/*
//---------------------------------------------------------------------------//
// TEST RELAXATION DATA 
//---------------------------------------------------------------------------//
// Check that the subshell occupancies can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, 
		   setSubshellOccupancy )
{
  evaluated_electron_data_container.setSubshellOccupancy( 1, 1.0 );

  TEST_EQUALITY_CONST(
    evaluated_electron_data_container.getSubshellOccupancy( 1 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the subshell binding energies can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, 
		   setSubshellBindingEnergy )
{
  evaluated_electron_data_container.setSubshellBindingEnergy( 1, 1.361e-5 );

  TEST_EQUALITY_CONST( 
               evaluated_electron_data_container.getSubshellBindingEnergy( 1 ),
		       1.361e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of subshell relaxation transitions can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setSubshellRelaxationTransitions )
{
  TEST_ASSERT( !evaluated_electron_data_container.hasRelaxationData() );

  evaluated_electron_data_container.setSubshellRelaxationTransitions( 1, 1 );
  
  TEST_EQUALITY_CONST( 
        evaluated_electron_data_container.getSubshellRelaxationTransitions(1),
		1 );
  TEST_ASSERT( evaluated_electron_data_container.hasRelaxationData() );
  TEST_ASSERT( 
    evaluated_electron_data_container.hasSubshellRelaxationData( 1 ) );
}

//---------------------------------------------------------------------------//
// Check that the relaxation vacancies for a subshell can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setSubshellRelaxationVacancies )
{
  std::vector<std::pair<unsigned,unsigned> > vacancies( 1 );
  vacancies[0].first = 1u;
  vacancies[1].second = 0u;

  evaluated_electron_data_container.setSubshellRelaxationVacancies( 
    1, 
    vacancies );

  UTILITY_TEST_COMPARE_ARRAYS( 
		evaluated_electron_data_container.getSubshellRelaxationVacancies( 1 ),
		vacancies );
  
}

//---------------------------------------------------------------------------//
// Check that the relaxation particle energies for a subshell can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setSubshellRelaxationEnergies )
{
  std::vector<double> energies( 1 );
  energies[0] = 1e-6;
  
  evaluated_electron_data_container.setSubshellRelaxationParticleEnergies( 
    1, energies );

  TEST_COMPARE_ARRAYS( 
	evaluated_electron_data_container.getSubshellRelaxationParticleEnergies( 1 ),
	energies );
}

//---------------------------------------------------------------------------//
// Check that the relaxation probabilities for a subshell can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setSubshellRelaxationProbabilities )
{
  std::vector<double> probabilities( 1 );
  probabilities[0] = 1.0;

  evaluated_electron_data_container.setSubshellRelaxationProbabilities( 
    1, probabilities );

  TEST_COMPARE_ARRAYS( 
	evaluated_electron_data_container.getSubshellRelaxationProbabilities( 1 ),
	probabilities );
}
*/

//---------------------------------------------------------------------------//
// TEST ELASTIC DATA 
//---------------------------------------------------------------------------//

// Check that the elastic energy grid can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer,
                   setElasticEnergyGrid )
{
  std::vector<double> electron_energy_grid( 3 );
  electron_energy_grid[0] = 1e-3;
  electron_energy_grid[1] = 1.0;
  electron_energy_grid[2] = 20.0;

  evaluated_electron_data_container.setElasticEnergyGrid( electron_energy_grid );

  TEST_COMPARE_ARRAYS( evaluated_electron_data_container.getElasticEnergyGrid(),
                       electron_energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the elastic transport cross section can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer,
                   setElasticTransportCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 0.5e-6;
  cross_section[1] = 0.5e-1;
  cross_section[2] = 0.5;

  evaluated_electron_data_container.setElasticTransportCrossSection( 
                        cross_section );

  TEST_COMPARE_ARRAYS( 
            evaluated_electron_data_container.getElasticTransportCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the cutoff elastic electron cross section can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer,
                   setCutoffElasticCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 0.5e-6;
  cross_section[1] = 0.5e-1;
  cross_section[2] = 0.5;

  evaluated_electron_data_container.setCutoffElasticCrossSection( 
                        cross_section );

  TEST_COMPARE_ARRAYS( 
            evaluated_electron_data_container.getCutoffElasticCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the residual atom incoming energy grid can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
                   setCutoffElasticResidualIncomingEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  evaluated_electron_data_container.setCutoffElasticResidualIncomingEnergy(
    energy );

  TEST_COMPARE_ARRAYS( 
    evaluated_electron_data_container.getCutoffElasticResidualIncomingEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the cutoff elastic average energy to the residual atom can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
                   setCutoffElasticResidualEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.0;
  energy[1] = 0.1;
  energy[2] = 1.0;

  evaluated_electron_data_container.setCutoffElasticResidualEnergy(
    energy );

  TEST_COMPARE_ARRAYS( 
    evaluated_electron_data_container.getCutoffElasticResidualEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the scattered electron incoming energy grid can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
                   setCutoffElasticScatteredElectronIncomingEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  evaluated_electron_data_container.setCutoffElasticScatteredElectronIncomingEnergy(
    energy );

  TEST_COMPARE_ARRAYS( 
    evaluated_electron_data_container.getCutoffElasticScatteredElectronIncomingEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the average energy to the scattered electron can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
                   setCutoffElasticScatteredElectronEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.0;
  energy[1] = 0.1;
  energy[2] = 1.0;

  evaluated_electron_data_container.setCutoffElasticScatteredElectronEnergy(
    energy );

  TEST_COMPARE_ARRAYS( 
    evaluated_electron_data_container.getCutoffElasticScatteredElectronEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the cutoff elastic angular energy grid can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
                   setCutoffElasticAngularEnergyGrid )
{
  std::vector<double> angular_energy_grid(1), grid(1);
  angular_energy_grid[0] = 1.0;

  evaluated_electron_data_container.setCutoffElasticAngularEnergyGrid( 
                                    angular_energy_grid );
  
  grid = evaluated_electron_data_container.getCutoffElasticAngularEnergyGrid();
  TEST_EQUALITY_CONST( grid[0], angular_energy_grid[0] );
}

//---------------------------------------------------------------------------//
// Check that the elastic angles can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
                   setCutoffElasticAnglesAtEnergy )
{
  std::vector<double> angles( 3 );
  angles[0] = -1.0;
  angles[1] = 0.0;
  angles[2] = 0.90;

  evaluated_electron_data_container.setCutoffElasticAnglesAtEnergy( 1.0, angles );

  TEST_COMPARE_ARRAYS( evaluated_electron_data_container.getCutoffElasticAngles(1.0),
                       angles );
}

//---------------------------------------------------------------------------//
// Check that the elastic pdf can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
                   setCutoffElasticPDFAtEnergy )
{
  std::vector<double> pdf( 3 );
  pdf[0] = 0.1;
  pdf[1] = 0.2;
  pdf[2] = 0.7;

  evaluated_electron_data_container.setCutoffElasticPDFAtEnergy( 1.0, pdf );

  TEST_COMPARE_ARRAYS( evaluated_electron_data_container.getCutoffElasticPDF(1.0),
                       pdf );
}

//---------------------------------------------------------------------------//
// Check that the elastic angles can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
                   setCutoffElasticAngles )
{
  std::vector<double> angles( 3 );
  angles[0] = -1.0;
  angles[1] = 0.0;
  angles[2] = 0.90;

  double energy = 1.0;
  std::map<double, std::vector<double> > angles_map;

  angles_map[energy] = angles;

  evaluated_electron_data_container.setCutoffElasticAngles( angles_map );

  TEST_COMPARE_ARRAYS( evaluated_electron_data_container.getCutoffElasticAngles(1.0),
                       angles );
}

//---------------------------------------------------------------------------//
// Check that the elastic pdf can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
                   setCutoffElasticPDF )
{
  std::vector<double> pdf( 3 );
  pdf[0] = 0.1;
  pdf[1] = 0.2;
  pdf[2] = 0.7;
  
  double energy = 1.0;
  std::map<double, std::vector<double> > pdf_map;

  pdf_map[energy] = pdf;

  evaluated_electron_data_container.setCutoffElasticPDF( pdf_map );

  TEST_COMPARE_ARRAYS( evaluated_electron_data_container.getCutoffElasticPDF(1.0),
                       pdf );
}

//---------------------------------------------------------------------------//
// Check that the total elastic electron cross section can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer,
                   setTotalElasticCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  evaluated_electron_data_container.setTotalElasticCrossSection( 
                        cross_section );

  TEST_COMPARE_ARRAYS( 
            evaluated_electron_data_container.getTotalElasticCrossSection(),
            cross_section );
}

/*
//---------------------------------------------------------------------------//
// Check that the screened rutherford elastic electron cross section can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer,
                   setScreenedRutherfordElasticCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 0.6e-6;
  cross_section[1] = 0.6e-1;
  cross_section[2] = 0.6;

  evaluated_electron_data_container.setScreenedRutherfordElasticCrossSection( 
                        cross_section );

  TEST_COMPARE_ARRAYS( 
            evaluated_electron_data_container.getScreenedRutherfordElasticCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the screened Rutherford elastic normalization constant can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
                   setScreenedRutherfordNormalizationConstant )
{
  std::vector<double> norm( 3 );
  norm[0] = 100;
  norm[1] = 200;
  norm[2] = 700;

  evaluated_electron_data_container.setScreenedRutherfordNormalizationConstant( norm );

  TEST_COMPARE_ARRAYS( evaluated_electron_data_container.getScreenedRutherfordNormalizationConstant(),
                       norm );
}

//---------------------------------------------------------------------------//
// Check that Moliere's screening constant can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
                   setMoliereScreeningConstant )
{
  std::vector<double> eta( 3 );
  eta[0] = 100;
  eta[1] = 0.0;
  eta[2] = 0.90;

  evaluated_electron_data_container.setMoliereScreeningConstant( eta );

  TEST_COMPARE_ARRAYS( evaluated_electron_data_container.getMoliereScreeningConstant(),
                       eta );
}
*/


//---------------------------------------------------------------------------//
// TEST ELECTROIONIZATION DATA 
//---------------------------------------------------------------------------//

// Check that the electroionization cross section energy grid can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer,
                   setElectroionizationCrossSectionEnergyGrid )
{
  std::vector<double> electron_energy_grid( 3 );
  electron_energy_grid[0] = 1e-3;
  electron_energy_grid[1] = 1.0;
  electron_energy_grid[2] = 20.0;

  unsigned subshell = 1;

  evaluated_electron_data_container.setElectroionizationCrossSectionEnergyGrid(
    subshell,
    electron_energy_grid );

  TEST_COMPARE_ARRAYS(
    evaluated_electron_data_container.getElectroionizationCrossSectionEnergyGrid( subshell ),
    electron_energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the electroionization electron cross section can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer,
                   setElectroionizationCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  unsigned subshell = 1;

  evaluated_electron_data_container.setElectroionizationCrossSection(
    subshell,
    cross_section );

  TEST_COMPARE_ARRAYS( 
    evaluated_electron_data_container.getElectroionizationCrossSection( subshell ),
    cross_section );
}

//---------------------------------------------------------------------------//
// Check that the incoming energy grid for the electroionization scattered electron can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
                   setElectroionizationAverageScatteredElectronIncomingEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  unsigned subshell = 1;

  evaluated_electron_data_container.setElectroionizationAverageScatteredElectronIncomingEnergy(
    subshell,
    energy );

  TEST_COMPARE_ARRAYS( 
    evaluated_electron_data_container.getElectroionizationAverageScatteredElectronIncomingEnergy( subshell ),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the electroionization average scattered electron energy can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
                   setElectroionizationAverageScatteredElectronEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.0;
  energy[1] = 0.1;
  energy[2] = 1.0;

  unsigned subshell = 1;

  evaluated_electron_data_container.setElectroionizationAverageScatteredElectronEnergy(
    subshell,
    energy );

  TEST_COMPARE_ARRAYS( 
    evaluated_electron_data_container.getElectroionizationAverageScatteredElectronEnergy( subshell ),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the incoming energy grid for the electroionization recoil can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
                   setElectroionizationAverageRecoilElectronIncomingEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  unsigned subshell = 1;

  evaluated_electron_data_container.setElectroionizationAverageRecoilElectronIncomingEnergy(
    subshell,
    energy );

  TEST_COMPARE_ARRAYS( 
    evaluated_electron_data_container.getElectroionizationAverageRecoilElectronIncomingEnergy( subshell ),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the electroionization average recoil energy can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
                   setElectroionizationAverageRecoilElectronEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.0;
  energy[1] = 0.1;
  energy[2] = 1.0;

  unsigned subshell = 1;

  evaluated_electron_data_container.setElectroionizationAverageRecoilElectronEnergy(
    subshell,
    energy );

  TEST_COMPARE_ARRAYS( 
    evaluated_electron_data_container.getElectroionizationAverageRecoilElectronEnergy( subshell ),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the electroionization recoil energy grid can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
                   setElectroionizationRecoilEnergyGrid )
{
  std::vector<double> energy_grid(1), grid(1);
  energy_grid[0] = 1.0;

  unsigned subshell = 1;

  evaluated_electron_data_container.setElectroionizationRecoilEnergyGrid( 
                                subshell,
                                energy_grid );
  
  TEST_COMPARE_ARRAYS( 
    evaluated_electron_data_container.getElectroionizationRecoilEnergyGrid( subshell ), 
    energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the electroionization recoil energy can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
                   setElectroionizationRecoilEnergyAtIncomingEnergy )
{
  std::vector<double> recoil_energy( 3 );
  recoil_energy[0] = 0.01;
  recoil_energy[1] = 0.001;
  recoil_energy[2] = 0.0001;

  unsigned subshell = 1;
  double energy = 1.0;

  evaluated_electron_data_container.setElectroionizationRecoilEnergyAtIncomingEnergy( 
                                subshell,
                                energy, 
                                recoil_energy );

  TEST_COMPARE_ARRAYS( evaluated_electron_data_container.getElectroionizationRecoilEnergy(subshell, energy),
                       recoil_energy );
}

//---------------------------------------------------------------------------//
// Check that the electroionization recoil pdf can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
                   setElectroionizationRecoilPDFAtIncomingEnergy )
{
  std::vector<double> recoil_pdf( 3 );
  recoil_pdf[0] = 1.0;
  recoil_pdf[1] = 2.0;
  recoil_pdf[2] = 5.0;

  unsigned subshell = 1;
  double energy = 1.0;

  evaluated_electron_data_container.setElectroionizationRecoilPDFAtIncomingEnergy(
                                subshell,
                                energy, 
                                recoil_pdf );

  TEST_COMPARE_ARRAYS( evaluated_electron_data_container.getElectroionizationRecoilPDF( subshell, energy ),
                       recoil_pdf );
}

//---------------------------------------------------------------------------//
// Check that the electroionization recoil energy can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
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

  evaluated_electron_data_container.setElectroionizationRecoilEnergy( 
                                subshell,
                                recoil_energy );

  TEST_COMPARE_ARRAYS( 
    evaluated_electron_data_container.getElectroionizationRecoilEnergy(subshell, energy_bin),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the electroionization recoil pdf can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
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

  evaluated_electron_data_container.setElectroionizationRecoilPDF(
                                subshell,
                                recoil_pdf );

  TEST_COMPARE_ARRAYS( 
    evaluated_electron_data_container.getElectroionizationRecoilPDF( subshell, energy_bin ),
    pdf );
}

//---------------------------------------------------------------------------//
// TEST BREMSSTRAHLUNG DATA 
//---------------------------------------------------------------------------//
// Check that the bremsstrahlung cross section energy grid can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer,
                   setBremsstrahlungCrossSectionEnergyGrid )
{
  std::vector<double> electron_energy_grid( 3 );
  electron_energy_grid[0] = 1e-3;
  electron_energy_grid[1] = 1.0;
  electron_energy_grid[2] = 20.0;

  evaluated_electron_data_container.setBremsstrahlungCrossSectionEnergyGrid(
    electron_energy_grid );

  TEST_COMPARE_ARRAYS(
    evaluated_electron_data_container.getBremsstrahlungCrossSectionEnergyGrid(),
    electron_energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung electron cross section can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer,
                   setBremsstrahlungCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  evaluated_electron_data_container.setBremsstrahlungCrossSection( 
                        cross_section );

  TEST_COMPARE_ARRAYS( 
            evaluated_electron_data_container.getBremsstrahlungCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung energy grid for the secondary photon can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
                   setBremsstrahlungAveragePhotonIncomingEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  evaluated_electron_data_container.setBremsstrahlungAveragePhotonIncomingEnergy(
    energy );

  TEST_COMPARE_ARRAYS( 
    evaluated_electron_data_container.getBremsstrahlungAveragePhotonIncomingEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung average energy of the secondary photon can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
                   setBremsstrahlungAveragePhotonEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.001;
  energy[1] = 0.1;
  energy[2] = 1.0;

  evaluated_electron_data_container.setBremsstrahlungAveragePhotonEnergy(
    energy );

  TEST_COMPARE_ARRAYS( 
    evaluated_electron_data_container.getBremsstrahlungAveragePhotonEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung energy grid can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
                   setBremsstrahlungPhotonEnergyGrid )
{
  std::vector<double> energy_grid(2), grid(2);
  energy_grid[0] = 1.0;
  energy_grid[1] = 2.0;

  evaluated_electron_data_container.setBremsstrahlungPhotonEnergyGrid( 
    energy_grid );
  
  grid = evaluated_electron_data_container.getBremsstrahlungPhotonEnergyGrid();
  TEST_EQUALITY_CONST( grid[0], energy_grid[0] );
  TEST_EQUALITY_CONST( grid[1], energy_grid[1] );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung photon energy can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
                   setBremsstrahlungPhotonEnergyAtIncomingEnergy )
{
  std::vector<double> photon_energy( 3 );
  photon_energy[0] = 0.01;
  photon_energy[1] = 0.001;
  photon_energy[2] = 0.0001;

  evaluated_electron_data_container.setBremsstrahlungPhotonEnergyAtIncomingEnergy( 1.0, 
                                                                   photon_energy );

  TEST_COMPARE_ARRAYS( evaluated_electron_data_container.getBremsstrahlungPhotonEnergy(1.0),
                       photon_energy );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung photon pdf can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
                   setBremsstrahlungPhotonPDFAtIncomingEnergy )
{
  std::vector<double> photon_pdf( 3 );
  photon_pdf[0] = 1.0;
  photon_pdf[1] = 2.0;
  photon_pdf[2] = 5.0;

  evaluated_electron_data_container.setBremsstrahlungPhotonPDFAtIncomingEnergy( 1.0, 
                                                                photon_pdf );

  TEST_COMPARE_ARRAYS( evaluated_electron_data_container.getBremsstrahlungPhotonPDF(1.0),
                       photon_pdf );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung photon energy can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
                   setBremsstrahlungPhotonEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.01;
  energy[1] = 0.001;
  energy[2] = 0.0001;

  double energy_bin = 1.0;

  std::map<double,std::vector<double> > photon_energy;

  photon_energy[energy_bin] = energy;

  evaluated_electron_data_container.setBremsstrahlungPhotonEnergy( photon_energy );

  TEST_COMPARE_ARRAYS( evaluated_electron_data_container.getBremsstrahlungPhotonEnergy(energy_bin),
                       energy );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung photon pdf can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
                   setBremsstrahlungPhotonPDF )
{
  std::vector<double> pdf( 3 );
  pdf[0] = 1.0;
  pdf[1] = 2.0;
  pdf[2] = 5.0;

  double energy_bin = 1.0;

  std::map<double,std::vector<double> > photon_pdf;

  photon_pdf[energy_bin] = pdf;

  evaluated_electron_data_container.setBremsstrahlungPhotonPDF( photon_pdf );

  TEST_COMPARE_ARRAYS( evaluated_electron_data_container.getBremsstrahlungPhotonPDF(energy_bin),
                       pdf );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung energy grid for the secondary electron can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
                   setBremsstrahlungAverageElectronIncomingEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 1.0;
  energy[1] = 2.0;
  energy[2] = 3.0;

  evaluated_electron_data_container.setBremsstrahlungAverageElectronIncomingEnergy(
    energy );

  TEST_COMPARE_ARRAYS( 
    evaluated_electron_data_container.getBremsstrahlungAverageElectronIncomingEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// Check that the bremsstrahlung average energy of the secondary electron can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
                   setBremsstrahlungAverageElectronEnergy )
{
  std::vector<double> energy( 3 );
  energy[0] = 0.001;
  energy[1] = 0.1;
  energy[2] = 1.0;

  evaluated_electron_data_container.setBremsstrahlungAverageElectronEnergy(
    energy );

  TEST_COMPARE_ARRAYS( 
    evaluated_electron_data_container.getBremsstrahlungAverageElectronEnergy(),
    energy );
}

//---------------------------------------------------------------------------//
// TEST ATOMIC EXCITAION DATA 
//---------------------------------------------------------------------------//
// Check that the atomic excitation cross section energy grid can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer,
                   setAtomicExcitationEnergyGrid )
{
  std::vector<double> electron_energy_grid( 3 );
  electron_energy_grid[0] = 1e-3;
  electron_energy_grid[1] = 1.0;
  electron_energy_grid[2] = 20.0;

  evaluated_electron_data_container.setAtomicExcitationEnergyGrid(
    electron_energy_grid );

  TEST_COMPARE_ARRAYS(
    evaluated_electron_data_container.getAtomicExcitationEnergyGrid(),
    electron_energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the atomic excitation electron cross section can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer,
                   setAtomicExcitationCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  evaluated_electron_data_container.setAtomicExcitationCrossSection( 
                        cross_section );

  TEST_COMPARE_ARRAYS( 
            evaluated_electron_data_container.getAtomicExcitationCrossSection(),
            cross_section );
}

//---------------------------------------------------------------------------//
// Check that the atomic excitation energy loss can be set
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer, 
                   setAtomicExcitationEnergyLoss )
{
  std::vector<double> energy_loss(3);
  energy_loss[0] = 1.0;
  energy_loss[1] = 5.0;
  energy_loss[2] = 10.0;

  evaluated_electron_data_container.setAtomicExcitationEnergyLoss( 
                                    energy_loss );
  
  TEST_COMPARE_ARRAYS( evaluated_electron_data_container.getAtomicExcitationEnergyLoss(), 
                       energy_loss );
}



//---------------------------------------------------------------------------//
// Check that the data can be exported and imported
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer,
                   export_importData_ascii )
{
  const std::string test_ascii_file_name( 
                    "test_evaluated_electron_data_container.txt" );

  evaluated_electron_data_container.exportData( test_ascii_file_name,
				 Utility::ArchivableObject::ASCII_ARCHIVE );

  const Data::EvaluatedElectronDataContainer 
    evaluated_electron_data_container_copy( test_ascii_file_name, 
			     Utility::ArchivableObject::ASCII_ARCHIVE );

  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getAtomicNumber(), 1 );
  TEST_ASSERT( 
    evaluated_electron_data_container_copy.getSubshells().count( 1 ) );
  TEST_ASSERT( 
    !evaluated_electron_data_container_copy.getSubshells().count( 0 ) );
  TEST_ASSERT( 
    !evaluated_electron_data_container_copy.getSubshells().count( 2 ) );

/*
//---------------------------------------------------------------------------//
// TEST RELAXATION DATA
//---------------------------------------------------------------------------//
  TEST_ASSERT( 
    evaluated_electron_data_container_copy.getSubshells().count( 1 ) );
  TEST_ASSERT( 
    !evaluated_electron_data_container_copy.getSubshells().count( 0 ) );
  TEST_ASSERT( 
    !evaluated_electron_data_container_copy.getSubshells().count( 2 ) );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getSubshellOccupancy( 1 ), 1.0 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getSubshellBindingEnergy( 1 ),
    1.361e-5 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getSubshellRelaxationTransitions(1),
    1 );
  TEST_ASSERT( evaluated_electron_data_container_copy.hasRelaxationData() );
  TEST_ASSERT( 
    evaluated_electron_data_container_copy.hasSubshellRelaxationData( 1 ) );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getSubshellRelaxationVacancies( 1 ).size(),
    1 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getSubshellRelaxationParticleEnergies( 1 ).size(),
    1 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getSubshellRelaxationProbabilities( 1 ).size(),
    1 );
*/

//---------------------------------------------------------------------------//
// TEST ELASTIC DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElasticEnergyGrid().size(), 3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticCrossSection().size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticResidualIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticResidualEnergy().size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticScatteredElectronIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticScatteredElectronEnergy().size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticAngularEnergyGrid().size(), 
    1 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticAngularEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticAngles(1.0).size(), 3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticPDF(1.0).size(), 3 );
/*
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getScreenedRutherfordElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getScreenedRutherfordNormalizationConstant().size(), 3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getMoliereScreeningConstant().size(), 3 );
*/
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getTotalElasticCrossSection().size(),
		       3u );

//---------------------------------------------------------------------------//
// TEST ELECTROIONIZATION DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationCrossSectionEnergyGrid(1u).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationCrossSection(1u).size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationAverageScatteredElectronIncomingEnergy(1u).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationAverageScatteredElectronEnergy(1u).size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationAverageRecoilElectronIncomingEnergy(1u).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationAverageRecoilElectronEnergy(1u).size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationRecoilEnergyGrid(1u).size(), 
    1 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationRecoilEnergyGrid(1u).front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationRecoilEnergy(1u, 1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationRecoilPDF(1u, 1.0).size(), 
    3 );

//---------------------------------------------------------------------------//
// TEST BREMSSTRAHLUNG DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungCrossSectionEnergyGrid().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungCrossSection().size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungAverageElectronIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungAverageElectronEnergy().size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungPhotonEnergyGrid().size(), 
    2 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungPhotonEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungPhotonEnergy(1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungPhotonPDF(1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungAveragePhotonIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungAveragePhotonEnergy().size(),
    3u );

//---------------------------------------------------------------------------//
// TEST ATOMIC EXCITATION DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getAtomicExcitationEnergyGrid().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getAtomicExcitationCrossSection().size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getAtomicExcitationEnergyLoss().size(), 
    3 );
}

//---------------------------------------------------------------------------//
// Check that the data can be exported and imported
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer,
                   export_importData_binary )
{
  const std::string test_binary_file_name( 
                    "test_evaluated_electron_data_container.bin" );

  evaluated_electron_data_container.exportData( test_binary_file_name,
				 Utility::ArchivableObject::BINARY_ARCHIVE );

  const Data::EvaluatedElectronDataContainer 
    evaluated_electron_data_container_copy( test_binary_file_name, 
			     Utility::ArchivableObject::BINARY_ARCHIVE );

  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getAtomicNumber(), 1 );
  TEST_ASSERT( 
    evaluated_electron_data_container_copy.getSubshells().count( 1 ) );
  TEST_ASSERT( 
    !evaluated_electron_data_container_copy.getSubshells().count( 0 ) );
  TEST_ASSERT( 
    !evaluated_electron_data_container_copy.getSubshells().count( 2 ) );

/*
//---------------------------------------------------------------------------//
// TEST RELAXATION DATA
//---------------------------------------------------------------------------//
  TEST_ASSERT( 
    evaluated_electron_data_container_copy.getSubshells().count( 1 ) );
  TEST_ASSERT( 
    !evaluated_electron_data_container_copy.getSubshells().count( 0 ) );
  TEST_ASSERT( 
    !evaluated_electron_data_container_copy.getSubshells().count( 2 ) );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getSubshellOccupancy( 1 ), 1.0 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getSubshellBindingEnergy( 1 ),
    1.361e-5 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getSubshellRelaxationTransitions(1),
    1 );
  TEST_ASSERT( evaluated_electron_data_container_copy.hasRelaxationData() );
  TEST_ASSERT( 
    evaluated_electron_data_container_copy.hasSubshellRelaxationData( 1 ) );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getSubshellRelaxationVacancies( 1 ).size(),
    1 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getSubshellRelaxationParticleEnergies( 1 ).size(),
    1 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getSubshellRelaxationProbabilities( 1 ).size(),
    1 );
*/

//---------------------------------------------------------------------------//
// TEST ELASTIC DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElasticEnergyGrid().size(), 3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticCrossSection().size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticResidualIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticResidualEnergy().size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticScatteredElectronIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticScatteredElectronEnergy().size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticAngularEnergyGrid().size(), 
    1 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticAngularEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticAngles(1.0).size(), 3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticPDF(1.0).size(), 3 );
/*
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getScreenedRutherfordElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getScreenedRutherfordNormalizationConstant().size(), 3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getMoliereScreeningConstant().size(), 3 );
*/
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getTotalElasticCrossSection().size(),
		       3u );

//---------------------------------------------------------------------------//
// TEST ELECTROIONIZATION DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationCrossSectionEnergyGrid(1u).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationCrossSection(1u).size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationAverageScatteredElectronIncomingEnergy(1u).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationAverageScatteredElectronEnergy(1u).size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationAverageRecoilElectronIncomingEnergy(1u).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationAverageRecoilElectronEnergy(1u).size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationRecoilEnergyGrid(1u).size(), 
    1 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationRecoilEnergyGrid(1u).front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationRecoilEnergy(1u, 1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationRecoilPDF(1u, 1.0).size(), 
    3 );

//---------------------------------------------------------------------------//
// TEST BREMSSTRAHLUNG DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungCrossSectionEnergyGrid().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungCrossSection().size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungAverageElectronIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungAverageElectronEnergy().size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungPhotonEnergyGrid().size(), 
    2 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungPhotonEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungPhotonEnergy(1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungPhotonPDF(1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungAveragePhotonIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungAveragePhotonEnergy().size(),
    3u );

//---------------------------------------------------------------------------//
// TEST ATOMIC EXCITATION DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getAtomicExcitationEnergyGrid().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getAtomicExcitationCrossSection().size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getAtomicExcitationEnergyLoss().size(), 
    3 );
}

//---------------------------------------------------------------------------//
// Check that the data can be exported and imported
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer,
                   export_importData_xml )
{
  const std::string test_xml_file_name( 
                    "test_evaluated_electron_data_container.xml" );

  evaluated_electron_data_container.exportData( test_xml_file_name,
				 Utility::ArchivableObject::XML_ARCHIVE );

  const Data::EvaluatedElectronDataContainer 
    evaluated_electron_data_container_copy( test_xml_file_name, 
			     Utility::ArchivableObject::XML_ARCHIVE );


  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getAtomicNumber(), 1 );
  TEST_ASSERT( 
    evaluated_electron_data_container_copy.getSubshells().count( 1 ) );
  TEST_ASSERT( 
    !evaluated_electron_data_container_copy.getSubshells().count( 0 ) );
  TEST_ASSERT( 
    !evaluated_electron_data_container_copy.getSubshells().count( 2 ) );

/*
//---------------------------------------------------------------------------//
// TEST RELAXATION DATA
//---------------------------------------------------------------------------//
  TEST_ASSERT( 
    evaluated_electron_data_container_copy.getSubshells().count( 1 ) );
  TEST_ASSERT( 
    !evaluated_electron_data_container_copy.getSubshells().count( 0 ) );
  TEST_ASSERT( 
    !evaluated_electron_data_container_copy.getSubshells().count( 2 ) );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getSubshellOccupancy( 1 ), 1.0 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getSubshellBindingEnergy( 1 ),
    1.361e-5 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getSubshellRelaxationTransitions(1),
    1 );
  TEST_ASSERT( evaluated_electron_data_container_copy.hasRelaxationData() );
  TEST_ASSERT( 
    evaluated_electron_data_container_copy.hasSubshellRelaxationData( 1 ) );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getSubshellRelaxationVacancies( 1 ).size(),
    1 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getSubshellRelaxationParticleEnergies( 1 ).size(),
    1 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getSubshellRelaxationProbabilities( 1 ).size(),
    1 );
*/

//---------------------------------------------------------------------------//
// TEST ELASTIC DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElasticEnergyGrid().size(), 3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticCrossSection().size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticResidualIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticResidualEnergy().size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticScatteredElectronIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticScatteredElectronEnergy().size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticAngularEnergyGrid().size(), 
    1 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticAngularEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticAngles(1.0).size(), 3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticPDF(1.0).size(), 3 );
/*
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getScreenedRutherfordElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getScreenedRutherfordNormalizationConstant().size(), 3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getMoliereScreeningConstant().size(), 3 );
*/
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getTotalElasticCrossSection().size(),
		       3u );

//---------------------------------------------------------------------------//
// TEST ELECTROIONIZATION DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationCrossSectionEnergyGrid(1u).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationCrossSection(1u).size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationAverageScatteredElectronIncomingEnergy(1u).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationAverageScatteredElectronEnergy(1u).size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationAverageRecoilElectronIncomingEnergy(1u).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationAverageRecoilElectronEnergy(1u).size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationRecoilEnergyGrid(1u).size(), 
    1 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationRecoilEnergyGrid(1u).front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationRecoilEnergy(1u, 1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationRecoilPDF(1u, 1.0).size(), 
    3 );

//---------------------------------------------------------------------------//
// TEST BREMSSTRAHLUNG DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungCrossSectionEnergyGrid().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungCrossSection().size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungAverageElectronIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungAverageElectronEnergy().size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungPhotonEnergyGrid().size(), 
    2 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungPhotonEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungPhotonEnergy(1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungPhotonPDF(1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungAveragePhotonIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungAveragePhotonEnergy().size(),
    3u );

//---------------------------------------------------------------------------//
// TEST ATOMIC EXCITATION DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getAtomicExcitationEnergyGrid().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getAtomicExcitationCrossSection().size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getAtomicExcitationEnergyLoss().size(), 
    3 );
}

//---------------------------------------------------------------------------//
// Check that the data can be packed into a string and unpacked from a string
TEUCHOS_UNIT_TEST( EvaluatedElectronDataContainer,
                   pack_unpackDataFromString )
{
  std::string packed_data = evaluated_electron_data_container.packDataInString();

  Data::EvaluatedElectronVolatileDataContainer evaluated_electron_data_container_copy;
  
  evaluated_electron_data_container_copy.unpackDataFromString( packed_data );
  

  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getAtomicNumber(), 1 );
  TEST_ASSERT( 
    evaluated_electron_data_container_copy.getSubshells().count( 1 ) );
  TEST_ASSERT( 
    !evaluated_electron_data_container_copy.getSubshells().count( 0 ) );
  TEST_ASSERT( 
    !evaluated_electron_data_container_copy.getSubshells().count( 2 ) );

/*
//---------------------------------------------------------------------------//
// TEST RELAXATION DATA
//---------------------------------------------------------------------------//
  TEST_ASSERT( 
    evaluated_electron_data_container_copy.getSubshells().count( 1 ) );
  TEST_ASSERT( 
    !evaluated_electron_data_container_copy.getSubshells().count( 0 ) );
  TEST_ASSERT( 
    !evaluated_electron_data_container_copy.getSubshells().count( 2 ) );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getSubshellOccupancy( 1 ), 1.0 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getSubshellBindingEnergy( 1 ),
    1.361e-5 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getSubshellRelaxationTransitions(1),
    1 );
  TEST_ASSERT( evaluated_electron_data_container_copy.hasRelaxationData() );
  TEST_ASSERT( 
    evaluated_electron_data_container_copy.hasSubshellRelaxationData( 1 ) );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getSubshellRelaxationVacancies( 1 ).size(),
    1 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getSubshellRelaxationParticleEnergies( 1 ).size(),
    1 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getSubshellRelaxationProbabilities( 1 ).size(),
    1 );
*/

//---------------------------------------------------------------------------//
// TEST ELASTIC DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElasticEnergyGrid().size(), 3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticCrossSection().size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticResidualIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticResidualEnergy().size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticScatteredElectronIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticScatteredElectronEnergy().size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticAngularEnergyGrid().size(), 
    1 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticAngularEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticAngles(1.0).size(), 3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getCutoffElasticPDF(1.0).size(), 3 );
/*
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getScreenedRutherfordElasticCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getScreenedRutherfordNormalizationConstant().size(), 3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getMoliereScreeningConstant().size(), 3 );
*/
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getTotalElasticCrossSection().size(),
		       3u );

//---------------------------------------------------------------------------//
// TEST ELECTROIONIZATION DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationCrossSectionEnergyGrid(1u).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationCrossSection(1u).size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationAverageScatteredElectronIncomingEnergy(1u).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationAverageScatteredElectronEnergy(1u).size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationAverageRecoilElectronIncomingEnergy(1u).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationAverageRecoilElectronEnergy(1u).size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationRecoilEnergyGrid(1u).size(), 
    1 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationRecoilEnergyGrid(1u).front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationRecoilEnergy(1u, 1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getElectroionizationRecoilPDF(1u, 1.0).size(), 
    3 );

//---------------------------------------------------------------------------//
// TEST BREMSSTRAHLUNG DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungCrossSectionEnergyGrid().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungCrossSection().size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungAverageElectronIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungAverageElectronEnergy().size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungPhotonEnergyGrid().size(), 
    2 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungPhotonEnergyGrid().front(), 
    1.0 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungPhotonEnergy(1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungPhotonPDF(1.0).size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungAveragePhotonIncomingEnergy().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getBremsstrahlungAveragePhotonEnergy().size(),
    3u );

//---------------------------------------------------------------------------//
// TEST ATOMIC EXCITATION DATA 
//---------------------------------------------------------------------------//
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getAtomicExcitationEnergyGrid().size(), 
    3 );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getAtomicExcitationCrossSection().size(),
    3u );
  TEST_EQUALITY_CONST( 
    evaluated_electron_data_container_copy.getAtomicExcitationEnergyLoss().size(), 
    3 );
}

//---------------------------------------------------------------------------//
// end tstEvaluatedElectronDataContainer.cpp
//---------------------------------------------------------------------------//

