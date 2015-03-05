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

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Data_ElectronPhotonRelaxationVolatileDataContainer.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"


//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Data::ElectronPhotonRelaxationVolatileDataContainer epr_data_container;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the atomic number can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, setAtomicNumber )
{
  epr_data_container.setAtomicNumber( 1u );
  
  TEST_EQUALITY_CONST( epr_data_container.getAtomicNumber(), 1u );
}

//---------------------------------------------------------------------------//
// Check that the subshells can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, setSubshells )
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
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, 
		   setSubshellOccupancy )
{
  epr_data_container.setSubshellOccupancy( 1, 1.0 );

  TEST_EQUALITY_CONST( epr_data_container.getSubshellOccupancy( 1 ), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that the subshell binding energies can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer, 
		   setSubshellBindingEnergy )
{
  epr_data_container.setSubshellBindingEnergy( 1, 1.361e-5 );

  TEST_EQUALITY_CONST( epr_data_container.getSubshellBindingEnergy( 1 ),
		       1.361e-5 );
}

//---------------------------------------------------------------------------//
// Check that the number of subshell relaxation transitions can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setSubshellRelaxationTransitions )
{
  TEST_ASSERT( !epr_data_container.hasRelaxationData() );

  epr_data_container.setSubshellRelaxationTransitions( 1, 1 );
  
  TEST_EQUALITY_CONST( epr_data_container.getSubshellRelaxationTransitions(1),
		       1 );
  TEST_ASSERT( epr_data_container.hasRelaxationData() );
  TEST_ASSERT( epr_data_container.hasSubshellRelaxationData( 1 ) );
}

//---------------------------------------------------------------------------//
// Check that the relaxation vacancies for a subshell can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setSubshellRelaxationVacancies )
{
  std::vector<std::pair<unsigned,unsigned> > vacancies( 1 );
  vacancies[0].first = 1u;
  vacancies[1].second = 0u;

  epr_data_container.setSubshellRelaxationVacancies( 1, vacancies );

  UTILITY_TEST_COMPARE_ARRAYS( 
			epr_data_container.getSubshellRelaxationVacancies( 1 ),
			vacancies );
  
}

//---------------------------------------------------------------------------//
// Check that the relaxation particle energies for a subshell can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setSubshellRelaxationEnergies )
{
  std::vector<double> energies( 1 );
  energies[0] = 1e-6;
  
  epr_data_container.setSubshellRelaxationParticleEnergies( 1, energies );

  TEST_COMPARE_ARRAYS( 
		 epr_data_container.getSubshellRelaxationParticleEnergies( 1 ),
		 energies );
}

//---------------------------------------------------------------------------//
// Check that the relaxation probabilities for a subshell can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setSubshellRelaxationProbabilities )
{
  std::vector<double> probabilities( 1 );
  probabilities[0] = 1.0;

  epr_data_container.setSubshellRelaxationProbabilities( 1, probabilities );

  TEST_COMPARE_ARRAYS( 
		    epr_data_container.getSubshellRelaxationProbabilities( 1 ),
		    probabilities );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile momentum grid can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setComptonProfileMomentumGrid )
{
  std::vector<double> compton_profile_momentum_grid( 3 );
  compton_profile_momentum_grid[0] = -1.0;
  compton_profile_momentum_grid[1] = 0.0;
  compton_profile_momentum_grid[2] = 1.0;

  epr_data_container.setComptonProfileMomentumGrid( 
					    1, compton_profile_momentum_grid );
  
  TEST_COMPARE_ARRAYS( epr_data_container.getComptonProfileMomentumGrid( 1 ),
		       compton_profile_momentum_grid );
}

//---------------------------------------------------------------------------//
// Check that the Compton profile for a subshell can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setComptonProfile )
{
  std::vector<double> compton_profile( 3 );
  compton_profile[0] = 1e-12;
  compton_profile[1] = 10.0;
  compton_profile[2] = 1e-12;

  epr_data_container.setComptonProfile( 1, compton_profile );

  TEST_COMPARE_ARRAYS( epr_data_container.getComptonProfile( 1 ), 
		       compton_profile );
} 

//---------------------------------------------------------------------------//
// Check that the occupancy number momentum grid can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setOccupancyNumberMomentumGrid )
{
  std::vector<double> momentum_grid( 3 );
  momentum_grid[0] = -1.0;
  momentum_grid[1] = 0.0;
  momentum_grid[2] = 1.0;

  epr_data_container.setOccupancyNumberMomentumGrid( 1, momentum_grid );

  TEST_COMPARE_ARRAYS( epr_data_container.getOccupancyNumberMomentumGrid( 1 ),
		       momentum_grid );
}

//---------------------------------------------------------------------------//
// Check that the occupancy number for a subshell can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setOccupancyNumber )
{
  std::vector<double> occupancy_number( 3 );
  occupancy_number[0] = 0.0;
  occupancy_number[1] = 0.5;
  occupancy_number[2] = 1.0;

  epr_data_container.setOccupancyNumber( 1, occupancy_number );

  TEST_COMPARE_ARRAYS( epr_data_container.getOccupancyNumber( 1 ),
		       occupancy_number );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree scattering function momentum grid can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setWallerHartreeScatteringFunctionMomentumGrid )
{
  std::vector<double> momentum_grid( 4 );
  momentum_grid[0] = 1e-30;
  momentum_grid[1] = 1.0;
  momentum_grid[2] = 10.0;
  momentum_grid[3] = 1e8;

  epr_data_container.setWallerHartreeScatteringFunctionMomentumGrid(
							       momentum_grid );
  
  TEST_COMPARE_ARRAYS( epr_data_container.getWallerHartreeScatteringFunctionMomentumGrid(),
		       momentum_grid );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree scattering function can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setWallerHartreeScatteringFunction )
{
  std::vector<double> scattering_function( 4 );
  scattering_function[0] = 1e-30;
  scattering_function[1] = 1e-3;
  scattering_function[2] = 0.1;
  scattering_function[3] = 1.0;

  epr_data_container.setWallerHartreeScatteringFunction( scattering_function );

  TEST_COMPARE_ARRAYS( epr_data_container.getWallerHartreeScatteringFunction(),
		       scattering_function );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree atomic form factor momentum grid can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setWallerHartreeAtomicFormFactorMomentumGrid )
{
  std::vector<double> momentum_grid( 4 );
  momentum_grid[0] = 1e-30;
  momentum_grid[1] = 1.0;
  momentum_grid[2] = 10.0;
  momentum_grid[3] = 1e8;

  epr_data_container.setWallerHartreeAtomicFormFactorMomentumGrid(
							       momentum_grid );

  TEST_COMPARE_ARRAYS( epr_data_container.getWallerHartreeAtomicFormFactorMomentumGrid(),
		       momentum_grid );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree atomic form factor can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setWallerHartreeAtomicFormFactor )
{
  std::vector<double> form_factor( 4 );
  form_factor[0] = 1.0;
  form_factor[1] = 1.0;
  form_factor[2] = 0.3;
  form_factor[3] = 1e-30;

  epr_data_container.setWallerHartreeAtomicFormFactor( form_factor );

  TEST_COMPARE_ARRAYS( epr_data_container.getWallerHartreeAtomicFormFactor(),
		       form_factor );
}

//---------------------------------------------------------------------------//
// Check that the photon energy grid can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setPhotonEnergyGrid )
{
  std::vector<double> photon_energy_grid( 3 );
  photon_energy_grid[0] = 1e-3;
  photon_energy_grid[1] = 1.0;
  photon_energy_grid[2] = 20.0;

  epr_data_container.setPhotonEnergyGrid( photon_energy_grid );

  TEST_COMPARE_ARRAYS( epr_data_container.getPhotonEnergyGrid(),
		       photon_energy_grid );
}

//---------------------------------------------------------------------------//
// Check that the average heating numbers can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setAveragePhotonHeatingNumbers )
{
  std::vector<double> heating_numbers( 3 );
  heating_numbers[0] = 1e-6;
  heating_numbers[1] = 1e-3;
  heating_numbers[2] = 1.0;

  epr_data_container.setAveragePhotonHeatingNumbers( heating_numbers );

  TEST_COMPARE_ARRAYS( epr_data_container.getAveragePhotonHeatingNumbers(),
		       heating_numbers );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree incoherent cross section can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setWallerHartreeIncoherentCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setWallerHartreeIncoherentCrossSection( cross_section );

  TEST_COMPARE_ARRAYS( epr_data_container.getWallerHartreeIncoherentCrossSection(),
		       cross_section );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree incoherent cs threshold index can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setWallerHartreeIncoherentCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setWallerHartreeIncoherentCrossSectionThresholdEnergyIndex( 0 );

  TEST_EQUALITY_CONST( epr_data_container.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(),
		       0 );
}

//---------------------------------------------------------------------------//
// Check that the impulse approx. incoherent cross section can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setImpulseApproxIncoherentCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setImpulseApproxIncoherentCrossSection( cross_section );
  
  TEST_COMPARE_ARRAYS( epr_data_container.getImpulseApproxIncoherentCrossSection(),
		       cross_section );
}

//---------------------------------------------------------------------------//
// Check that the impulse approx. incoherent cs threshold index can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setImpulseApproxIncoherentCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setImpulseApproxIncoherentCrossSectionThresholdEnergyIndex( 0 );

  TEST_EQUALITY_CONST( epr_data_container.getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
		       0u );
}

//---------------------------------------------------------------------------//
// Check that the impulse approx. subshell incoherent cross section can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setImpulseApproxSubshellIncoherentCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setImpulseApproxSubshellIncoherentCrossSection( 1, cross_section );

  TEST_COMPARE_ARRAYS( epr_data_container.getImpulseApproxSubshellIncoherentCrossSection( 1 ),
		       cross_section );
}

//---------------------------------------------------------------------------//
// Check that the impulse approx. subshell incoh. cs threshold index can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex( 1, 0 );

  TEST_EQUALITY_CONST( epr_data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex( 1 ), 
		       0 );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree coherent cross section can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setWallerHartreeCoherentCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setWallerHartreeCoherentCrossSection( cross_section );

  TEST_COMPARE_ARRAYS( epr_data_container.getWallerHartreeCoherentCrossSection(),
		       cross_section );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree coherent cs threshold energy index can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setWallerHartreeCoherentCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setWallerHartreeCoherentCrossSectionThresholdEnergyIndex( 0 );
  
  TEST_EQUALITY_CONST( epr_data_container.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex(),
		       0 );
}

//---------------------------------------------------------------------------//
// Check that the pair production cross section can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setPairProductionCrossSection )
{
  std::vector<double> cross_section( 2 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1.0;
  
  epr_data_container.setPairProductionCrossSection( cross_section );

  TEST_COMPARE_ARRAYS( epr_data_container.getPairProductionCrossSection(),
		       cross_section );
}

//---------------------------------------------------------------------------//
// Check that the pair production cross section threshold index can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setPairProductionCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setPairProductionCrossSectionThresholdEnergyIndex( 1 );

  TEST_EQUALITY_CONST( epr_data_container.getPairProductionCrossSectionThresholdEnergyIndex(),
		       1 );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric effect cross section can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setPhotoelectricCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setPhotoelectricCrossSection( cross_section );

  TEST_COMPARE_ARRAYS( epr_data_container.getPhotoelectricCrossSection(),
		       cross_section );
}

//---------------------------------------------------------------------------//
// Check that the photoelectric effect cs threshold energy index can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setPhotoelectricCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setPhotoelectricCrossSectionThresholdEnergyIndex( 0u );

  TEST_EQUALITY_CONST( epr_data_container.getPhotoelectricCrossSectionThresholdEnergyIndex(),
		       0u );
}

//---------------------------------------------------------------------------//
// Check that the subshell photoelectric effect cross section can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setSubshellPhotoelectricCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setSubshellPhotoelectricCrossSection( 1, cross_section );

  TEST_COMPARE_ARRAYS( epr_data_container.getSubshellPhotoelectricCrossSection( 1 ),
		       cross_section );
}

//---------------------------------------------------------------------------//
// Check that the subshell photoelectric effect cs threshold index can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setSubshellPhotoelectricCrossSectionThresholdEnergyIndex )
{
  epr_data_container.setSubshellPhotoelectricCrossSectionThresholdEnergyIndex( 1, 0u );

  TEST_EQUALITY_CONST( epr_data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex( 1 ),
		       0u );
}

//---------------------------------------------------------------------------//
// Check that the Waller-Hartree total cross section can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setWallerHartreeTotalCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setWallerHartreeTotalCrossSection( cross_section );
  
  TEST_COMPARE_ARRAYS( epr_data_container.getWallerHartreeTotalCrossSection(),
		       cross_section );
}

//---------------------------------------------------------------------------//
// Check that the impulse approx. total cross section can be set
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   setImpulseApproxTotalCrossSection )
{
  std::vector<double> cross_section( 3 );
  cross_section[0] = 1e-6;
  cross_section[1] = 1e-1;
  cross_section[2] = 1.0;

  epr_data_container.setImpulseApproxTotalCrossSection( cross_section );

  TEST_COMPARE_ARRAYS( epr_data_container.getImpulseApproxTotalCrossSection(),
		       cross_section );
}

//---------------------------------------------------------------------------//
// Check that the data can be exported and imported
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   export_importData_ascii )
{
  const std::string test_ascii_file_name( "test_epr_data_container.txt" );

  epr_data_container.exportData( test_ascii_file_name,
				 Utility::ArchivableObject::ASCII_ARCHIVE );

  const Data::ElectronPhotonRelaxationDataContainer 
    epr_data_container_copy( test_ascii_file_name, 
			     Utility::ArchivableObject::ASCII_ARCHIVE );

  TEST_EQUALITY_CONST( epr_data_container_copy.getAtomicNumber(), 1 );
  TEST_ASSERT( epr_data_container_copy.getSubshells().count( 1 ) );
  TEST_ASSERT( !epr_data_container_copy.getSubshells().count( 0 ) );
  TEST_ASSERT( !epr_data_container_copy.getSubshells().count( 2 ) );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellOccupancy( 1 ), 1.0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellBindingEnergy( 1 ),
		       1.361e-5 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationTransitions(1),
		       1 );
  TEST_ASSERT( epr_data_container_copy.hasRelaxationData() );
  TEST_ASSERT( epr_data_container_copy.hasSubshellRelaxationData( 1 ) );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationVacancies( 1 ).size(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationParticleEnergies( 1 ).size(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationProbabilities( 1 ).size(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getComptonProfileMomentumGrid( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getComptonProfile( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getOccupancyNumberMomentumGrid( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getOccupancyNumber( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeScatteringFunctionMomentumGrid().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeScatteringFunction().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeAtomicFormFactorMomentumGrid().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeAtomicFormFactor().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPhotonEnergyGrid().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getAveragePhotonHeatingNumbers().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeIncoherentCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxIncoherentCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
		       0u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxSubshellIncoherentCrossSection( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex( 1 ), 
		       0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeCoherentCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPairProductionCrossSection().size(),
		       2 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPairProductionCrossSectionThresholdEnergyIndex(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPhotoelectricCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPhotoelectricCrossSectionThresholdEnergyIndex(),
		       0u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellPhotoelectricCrossSection( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex( 1 ),
		       0u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeTotalCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxTotalCrossSection().size(),
		       3u );
}

//---------------------------------------------------------------------------//
// Check that the data can be exported and imported
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   export_importData_binary )
{
  const std::string test_binary_file_name( "test_epr_data_container.bin" );

  epr_data_container.exportData( test_binary_file_name,
				 Utility::ArchivableObject::BINARY_ARCHIVE );

  const Data::ElectronPhotonRelaxationDataContainer 
    epr_data_container_copy( test_binary_file_name, 
			     Utility::ArchivableObject::BINARY_ARCHIVE );

  TEST_EQUALITY_CONST( epr_data_container_copy.getAtomicNumber(), 1 );
  TEST_ASSERT( epr_data_container_copy.getSubshells().count( 1 ) );
  TEST_ASSERT( !epr_data_container_copy.getSubshells().count( 0 ) );
  TEST_ASSERT( !epr_data_container_copy.getSubshells().count( 2 ) );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellOccupancy( 1 ), 1.0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellBindingEnergy( 1 ),
		       1.361e-5 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationTransitions(1),
		       1 );
  TEST_ASSERT( epr_data_container_copy.hasRelaxationData() );
  TEST_ASSERT( epr_data_container_copy.hasSubshellRelaxationData( 1 ) );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationVacancies( 1 ).size(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationParticleEnergies( 1 ).size(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationProbabilities( 1 ).size(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getComptonProfileMomentumGrid( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getComptonProfile( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getOccupancyNumberMomentumGrid( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getOccupancyNumber( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeScatteringFunctionMomentumGrid().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeScatteringFunction().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeAtomicFormFactorMomentumGrid().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeAtomicFormFactor().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPhotonEnergyGrid().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getAveragePhotonHeatingNumbers().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeIncoherentCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxIncoherentCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
		       0u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxSubshellIncoherentCrossSection( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex( 1 ), 
		       0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeCoherentCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPairProductionCrossSection().size(),
		       2 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPairProductionCrossSectionThresholdEnergyIndex(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPhotoelectricCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPhotoelectricCrossSectionThresholdEnergyIndex(),
		       0u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellPhotoelectricCrossSection( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex( 1 ),
		       0u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeTotalCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxTotalCrossSection().size(),
		       3u );
}

//---------------------------------------------------------------------------//
// Check that the data can be exported and imported
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   export_importData_xml )
{
  const std::string test_xml_file_name( "test_epr_data_container.xml" );

  epr_data_container.exportData( test_xml_file_name,
				 Utility::ArchivableObject::XML_ARCHIVE );

  const Data::ElectronPhotonRelaxationDataContainer 
    epr_data_container_copy( test_xml_file_name, 
			     Utility::ArchivableObject::XML_ARCHIVE );

  TEST_EQUALITY_CONST( epr_data_container_copy.getAtomicNumber(), 1 );
  TEST_ASSERT( epr_data_container_copy.getSubshells().count( 1 ) );
  TEST_ASSERT( !epr_data_container_copy.getSubshells().count( 0 ) );
  TEST_ASSERT( !epr_data_container_copy.getSubshells().count( 2 ) );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellOccupancy( 1 ), 1.0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellBindingEnergy( 1 ),
		       1.361e-5 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationTransitions(1),
		       1 );
  TEST_ASSERT( epr_data_container_copy.hasRelaxationData() );
  TEST_ASSERT( epr_data_container_copy.hasSubshellRelaxationData( 1 ) );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationVacancies( 1 ).size(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationParticleEnergies( 1 ).size(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationProbabilities( 1 ).size(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getComptonProfileMomentumGrid( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getComptonProfile( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getOccupancyNumberMomentumGrid( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getOccupancyNumber( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeScatteringFunctionMomentumGrid().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeScatteringFunction().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeAtomicFormFactorMomentumGrid().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeAtomicFormFactor().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPhotonEnergyGrid().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getAveragePhotonHeatingNumbers().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeIncoherentCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxIncoherentCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
		       0u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxSubshellIncoherentCrossSection( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex( 1 ), 
		       0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeCoherentCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPairProductionCrossSection().size(),
		       2 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPairProductionCrossSectionThresholdEnergyIndex(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPhotoelectricCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPhotoelectricCrossSectionThresholdEnergyIndex(),
		       0u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellPhotoelectricCrossSection( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex( 1 ),
		       0u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeTotalCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxTotalCrossSection().size(),
		       3u );
}

//---------------------------------------------------------------------------//
// Check that the data can be packed into a string and unpacked from a string
TEUCHOS_UNIT_TEST( ElectronPhotonRelaxationDataContainer,
		   pack_unpackDataFromString )
{
  std::string packed_data = epr_data_container.packDataInString();

  Data::ElectronPhotonRelaxationVolatileDataContainer epr_data_container_copy;
  
  epr_data_container_copy.unpackDataFromString( packed_data );
  
  TEST_EQUALITY_CONST( epr_data_container_copy.getAtomicNumber(), 1 );
  TEST_ASSERT( epr_data_container_copy.getSubshells().count( 1 ) );
  TEST_ASSERT( !epr_data_container_copy.getSubshells().count( 0 ) );
  TEST_ASSERT( !epr_data_container_copy.getSubshells().count( 2 ) );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellOccupancy( 1 ), 1.0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellBindingEnergy( 1 ),
		       1.361e-5 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationTransitions(1),
		       1 );
  TEST_ASSERT( epr_data_container_copy.hasRelaxationData() );
  TEST_ASSERT( epr_data_container_copy.hasSubshellRelaxationData( 1 ) );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationVacancies( 1 ).size(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationParticleEnergies( 1 ).size(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellRelaxationProbabilities( 1 ).size(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getComptonProfileMomentumGrid( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getComptonProfile( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getOccupancyNumberMomentumGrid( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getOccupancyNumber( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeScatteringFunctionMomentumGrid().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeScatteringFunction().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeAtomicFormFactorMomentumGrid().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeAtomicFormFactor().size(),
		       4 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPhotonEnergyGrid().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getAveragePhotonHeatingNumbers().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeIncoherentCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxIncoherentCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
		       0u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxSubshellIncoherentCrossSection( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex( 1 ), 
		       0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeCoherentCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex(),
		       0 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPairProductionCrossSection().size(),
		       2 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPairProductionCrossSectionThresholdEnergyIndex(),
		       1 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPhotoelectricCrossSection().size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getPhotoelectricCrossSectionThresholdEnergyIndex(),
		       0u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellPhotoelectricCrossSection( 1 ).size(),
		       3 );
  TEST_EQUALITY_CONST( epr_data_container_copy.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex( 1 ),
		       0u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getWallerHartreeTotalCrossSection().size(),
		       3u );
  TEST_EQUALITY_CONST( epr_data_container_copy.getImpulseApproxTotalCrossSection().size(),
		       3u );
}

//---------------------------------------------------------------------------//
// end tstElectronPhotonRelaxationDataContainer.cpp
//---------------------------------------------------------------------------//
