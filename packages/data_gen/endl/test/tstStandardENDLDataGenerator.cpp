//---------------------------------------------------------------------------//
//!
//! \file   tstStandardENDLDataGenerator.cpp
//! \author Luke Kersting
//! \brief  Standard endl data generator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "DataGen_StandardENDLDataGenerator.hpp"
#include "Data_EvaluatedElectronVolatileDataContainer.hpp"
#include "Data_ENDLFileHandler.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<const DataGen::StandardENDLDataGenerator>
  data_generator_h, data_generator_c;

std::string test_h_eadl_file_name, test_h_epdl_file_name, test_h_eedl_file_name, 
            test_c_eadl_file_name, test_c_epdl_file_name, test_c_eedl_file_name;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a data container can be populated
TEUCHOS_UNIT_TEST( StandardENDLDataGenerator,
		   populateENDLDataContainer_h )
{
    data_generator_h.reset( 
        new DataGen::StandardENDLDataGenerator(
                1u,
                test_h_eadl_file_name,
                test_h_epdl_file_name,
                test_h_eedl_file_name ) );


  Data::EvaluatedElectronVolatileDataContainer data_container;

  data_generator_h->populateENDLDataContainer( data_container );

  TEST_EQUALITY_CONST( data_container.getAtomicNumber(), 1 );
  TEST_EQUALITY_CONST( data_container.getSubshells().size(), 1 );
  TEST_ASSERT( data_container.getSubshells().count( 1 ) );

//---------------------------------------------------------------------------//
// CHECK ELASTIC DATA 
//---------------------------------------------------------------------------//
  std::vector<double> energy_grid = data_container.getElasticEnergyGrid();
  TEST_EQUALITY_CONST( energy_grid.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 101 );

  std::vector<double> cross_section = 
    data_container.getElasticTransportCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 2.74896e+8 );
  TEST_EQUALITY_CONST( cross_section.back(), 4.33534E-10 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

  cross_section = 
    data_container.getCutoffElasticCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 2.74896e+8 );
  TEST_EQUALITY_CONST( cross_section.back(), 1.31176e-5 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

  std::vector<double> residual_incoming_energy = 
    data_container.getCutoffElasticResidualIncomingEnergy();

  TEST_EQUALITY_CONST( residual_incoming_energy.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( residual_incoming_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( residual_incoming_energy.size(), 2 );

  std::vector<double> residual_energy = 
    data_container.getCutoffElasticResidualEnergy();

  TEST_EQUALITY_CONST( residual_energy.front(), 0.0 );
  TEST_EQUALITY_CONST( residual_energy.back(), 0.0 );
  TEST_EQUALITY_CONST( residual_energy.size(), 
                       residual_incoming_energy.size() );

  std::vector<double> scattered_incoming_energy = 
    data_container.getCutoffElasticScatteredElectronIncomingEnergy();

  TEST_EQUALITY_CONST( scattered_incoming_energy.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( scattered_incoming_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( scattered_incoming_energy.size(), 2 );

  std::vector<double> scattered_energy = 
    data_container.getCutoffElasticScatteredElectronEnergy();

  TEST_EQUALITY_CONST( scattered_energy.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( scattered_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( scattered_energy.size(), 
                       scattered_incoming_energy.size() );

  std::vector<double> angular_grid = 
    data_container.getCutoffElasticAngularEnergyGrid();

  TEST_EQUALITY_CONST( angular_grid.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( angular_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( angular_grid.size(), 16 );

  std::vector<double> elastic_angles = 
    data_container.getCutoffElasticAngles(1.0e-5);

  TEST_EQUALITY_CONST( elastic_angles.front(), 1.0e-6 );
  TEST_EQUALITY_CONST( elastic_angles.back(), 2.0 );
  TEST_EQUALITY_CONST( elastic_angles.size(), 2 );

  elastic_angles = 
    data_container.getCutoffElasticAngles(1.0e+5);

  TEST_EQUALITY_CONST( elastic_angles.front(), 1.0e-6 );
  TEST_EQUALITY_CONST( elastic_angles.back(), 2.0 );
  TEST_EQUALITY_CONST( elastic_angles.size(), 96 );

  std::vector<double> elastic_pdf = 
    data_container.getCutoffElasticPDF(1.0e-5);

  TEST_EQUALITY_CONST( elastic_pdf.front(), 0.5 );
  TEST_EQUALITY_CONST( elastic_pdf.back(), 0.5 );
  TEST_EQUALITY_CONST( elastic_pdf.size(), 2 );

  elastic_pdf = 
    data_container.getCutoffElasticPDF(1.0e+5);

  TEST_EQUALITY_CONST( elastic_pdf.front(), 9.86945e5 );
  TEST_EQUALITY_CONST( elastic_pdf.back(), 6.25670e-13 );
  TEST_EQUALITY_CONST( elastic_pdf.size(), 96 );

  cross_section = 
    data_container.getTotalElasticCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 2.74896e8 );
  TEST_EQUALITY_CONST( cross_section.back(), 1.29871e4 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

/*
  cross_section = 
    data_container.getScreenedRutherfordElasticCrossSection();

//  TEST_EQUALITY_CONST( cross_section.front(), 2.5745520470700284932 );
//! \todo double check what the front cross section should be 
  TEST_EQUALITY_CONST( cross_section.front(), 2.57455204707366647 );
  TEST_EQUALITY_CONST( cross_section.back(), 1.29871e+4-1.31176e-5 );
  TEST_EQUALITY_CONST( cross_section.size(), 728-threshold );
*/

//---------------------------------------------------------------------------//
// CHECK ELECTROIONIZATION DATA 
//---------------------------------------------------------------------------//
  energy_grid = data_container.getElectroionizationCrossSectionEnergyGrid( 1u );
  TEST_EQUALITY_CONST( energy_grid.front(), 1.361e-5 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 35 );

  cross_section = 
    data_container.getElectroionizationCrossSection( 1u );

  TEST_EQUALITY_CONST( cross_section.front(), 0.0 );
  TEST_EQUALITY_CONST( cross_section.back(), 8.28924e+4 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

  scattered_incoming_energy =  
    data_container.getElectroionizationAverageScatteredElectronIncomingEnergy( 1u );

  TEST_EQUALITY_CONST( scattered_incoming_energy.front(), 1.361e-5 );
  TEST_EQUALITY_CONST( scattered_incoming_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( scattered_incoming_energy.size(), 6 );

  scattered_energy =  
    data_container.getElectroionizationAverageScatteredElectronEnergy( 1u );

  TEST_EQUALITY_CONST( scattered_energy.front(), 0.0 );
  TEST_EQUALITY_CONST( scattered_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( scattered_energy.size(), 
                       scattered_incoming_energy.size() );

  std::vector<double> recoil_incoming_energy =  
    data_container.getElectroionizationAverageRecoilElectronIncomingEnergy( 1u );

  TEST_EQUALITY_CONST( recoil_incoming_energy.front(), 1.361e-5 );
  TEST_EQUALITY_CONST( recoil_incoming_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( recoil_incoming_energy.size(), 25 );

  std::vector<double> recoil_energy =  
    data_container.getElectroionizationAverageRecoilElectronEnergy( 1u );

  TEST_EQUALITY_CONST( recoil_energy.front(), 0.0 );
  TEST_EQUALITY_CONST( recoil_energy.back(), 7.28699e-5 );
  TEST_EQUALITY_CONST( recoil_energy.size(), 
                       recoil_incoming_energy.size() );

  std::vector<double> recoil_energy_grid =  
    data_container.getElectroionizationRecoilEnergyGrid( 1u );

  TEST_EQUALITY_CONST( recoil_energy_grid.front(), 1.36100e-5 );
  TEST_EQUALITY_CONST( recoil_energy_grid.back(), 1.00000e+5 );
  TEST_EQUALITY_CONST( recoil_energy_grid.size(), 8 );

  std::vector<double> electroionization_recoil_energy =  
    data_container.getElectroionizationRecoilEnergy( 1u, 1.36100e-5 );

  TEST_EQUALITY_CONST( electroionization_recoil_energy.front(), 2.79866e-9 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.back(), 2.79866e-8 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.size(), 2 );

  electroionization_recoil_energy =  
    data_container.getElectroionizationRecoilEnergy( 1u, 1.00000e+5 );

  TEST_EQUALITY_CONST( electroionization_recoil_energy.front(), 1.00000e-7 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.back(), 5.00000e+4 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.size(), 147 );

  std::vector<double> electroionization_recoil_pdf =  
    data_container.getElectroionizationRecoilPDF( 1u, 1.36100e-5 );

  TEST_EQUALITY_CONST( electroionization_recoil_pdf.front(), 3.97015e+7 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.back(), 3.97015e+7 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.size(), 2 );

  electroionization_recoil_pdf =  
    data_container.getElectroionizationRecoilPDF( 1u, 1.00000e+5 );

  TEST_EQUALITY_CONST( electroionization_recoil_pdf.front(), 1.61897e+5 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.back(), 2.77550e-15 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.size(), 147 );

//---------------------------------------------------------------------------//
// CHECK BREMSSTRAHLUNG DATA 
//---------------------------------------------------------------------------//
  energy_grid = data_container.getBremsstrahlungCrossSectionEnergyGrid();
  TEST_EQUALITY_CONST( energy_grid.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 96 );

  cross_section = 
    data_container.getBremsstrahlungCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(),  2.97832e+1 );
  TEST_EQUALITY_CONST( cross_section.back(), 9.90621e-1 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

  std::vector<double> photon_incoming_energy =  
    data_container.getBremsstrahlungAveragePhotonIncomingEnergy();

  TEST_EQUALITY_CONST( photon_incoming_energy.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( photon_incoming_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( photon_incoming_energy.size(), 82 );

  std::vector<double> photon_energy =  
    data_container.getBremsstrahlungAveragePhotonEnergy();

  TEST_EQUALITY_CONST( photon_energy.front(), 2.14426e-6 );
  TEST_EQUALITY_CONST( photon_energy.back(), 2.66815e3 );
  TEST_EQUALITY_CONST( photon_energy.size(), 
                       photon_incoming_energy.size() );

  std::vector<double> bremsstrahlung_photon_energy_grid =  
    data_container.getBremsstrahlungPhotonEnergyGrid();

  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy_grid.front(), 1.00000e-5 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy_grid.back(), 1.00000e+5 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy_grid.size(), 10 );

  std::vector<double> bremsstrahlung_photon_energy =  
    data_container.getBremsstrahlungPhotonEnergy( 1.00000e-5 );

  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.back(), 1.00000e-5 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.size(), 17 );

  bremsstrahlung_photon_energy =  
    data_container.getBremsstrahlungPhotonEnergy( 1.00000e+5 );

  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.back(), 1.00000e+5 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.size(), 111 );

  std::vector<double> bremsstrahlung_photon_pdf =  
    data_container.getBremsstrahlungPhotonPDF( 1.00000e-5 );

  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.front(), 2.13940e+6 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.back(), 2.12245e+4 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.size(), 17 );

  bremsstrahlung_photon_pdf =  
    data_container.getBremsstrahlungPhotonPDF( 1.00000e+5 );

  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.front(),  3.65591e+5 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.back(),  5.16344e-10 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.size(), 111 );

  std::vector<double> electron_incoming_energy =  
    data_container.getBremsstrahlungAverageElectronIncomingEnergy();

  TEST_EQUALITY_CONST( electron_incoming_energy.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( electron_incoming_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( electron_incoming_energy.size(), 85 );

  std::vector<double> electron_energy =  
    data_container.getBremsstrahlungAverageElectronEnergy();

  TEST_EQUALITY_CONST( electron_energy.front(), 7.85574e-6 );
  TEST_EQUALITY_CONST( electron_energy.back(), 9.73318e4 );
  TEST_EQUALITY_CONST( electron_energy.size(), 
                       electron_incoming_energy.size() );

//---------------------------------------------------------------------------//
// CHECK ATOMIC EXCITAION DATA 
//---------------------------------------------------------------------------//
  energy_grid = data_container.getAtomicExcitationEnergyGrid();
  TEST_EQUALITY_CONST( energy_grid.front(), 1.361e-5 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 170 );

  cross_section = 
    data_container.getAtomicExcitationCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 0.0 );
  TEST_EQUALITY_CONST( cross_section.back(), 8.14416e+4 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

  std::vector<double> atomic_excitation_energy_loss =  
    data_container.getAtomicExcitationEnergyLoss();

  TEST_EQUALITY_CONST( atomic_excitation_energy_loss.front(), 1.36100e-5 );
  TEST_EQUALITY_CONST( atomic_excitation_energy_loss.back(), 2.10777e-5 );
  TEST_EQUALITY_CONST( atomic_excitation_energy_loss.size(), 
                       energy_grid.size() );
/*
  data_container.exportData( "test_h_endl.xml",
			     Utility::ArchivableObject::XML_ARCHIVE );*/
}

//---------------------------------------------------------------------------//
// Check that a data container can be populated
TEUCHOS_UNIT_TEST( StandardENDLDataGenerator, populateENDLDataContainer_c )
{
    data_generator_c.reset( 
        new DataGen::StandardENDLDataGenerator(
                6u,
                test_c_eadl_file_name,
                test_c_epdl_file_name,
                test_c_eedl_file_name ) );

  Data::EvaluatedElectronVolatileDataContainer data_container;

  data_generator_c->populateENDLDataContainer( data_container );

  TEST_EQUALITY_CONST( data_container.getAtomicNumber(), 6 );
  TEST_EQUALITY_CONST( data_container.getSubshells().size(), 4 );
  TEST_ASSERT( data_container.getSubshells().count( 1 ) );
  TEST_ASSERT( data_container.getSubshells().count( 2 ) );
  TEST_ASSERT( data_container.getSubshells().count( 3 ) );
  TEST_ASSERT( data_container.getSubshells().count( 4 ) );

//---------------------------------------------------------------------------//
// CHECK ELASTIC DATA 
//---------------------------------------------------------------------------//
  std::vector<double> energy_grid = data_container.getElasticEnergyGrid();
  TEST_EQUALITY_CONST( energy_grid.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 101 );

  std::vector<double> cross_section = 
    data_container.getElasticTransportCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 3.06351e+9 );
  TEST_EQUALITY_CONST( cross_section.back(), 1.51014e-8 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

  cross_section = 
    data_container.getCutoffElasticCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 3.06351e+9 );
  TEST_EQUALITY_CONST( cross_section.back(), 4.72309e-4 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

  std::vector<double> residual_incoming_energy = 
    data_container.getCutoffElasticResidualIncomingEnergy();

  TEST_EQUALITY_CONST( residual_incoming_energy.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( residual_incoming_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( residual_incoming_energy.size(), 2 );

  std::vector<double> residual_energy = 
    data_container.getCutoffElasticResidualEnergy();

  TEST_EQUALITY_CONST( residual_energy.front(), 0.0 );
  TEST_EQUALITY_CONST( residual_energy.back(), 0.0 );
  TEST_EQUALITY_CONST( residual_energy.size(), 
                       residual_incoming_energy.size() );

  std::vector<double> scattered_incoming_energy = 
    data_container.getCutoffElasticScatteredElectronIncomingEnergy();

  TEST_EQUALITY_CONST( scattered_incoming_energy.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( scattered_incoming_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( scattered_incoming_energy.size(), 2 );

  std::vector<double> scattered_energy = 
    data_container.getCutoffElasticScatteredElectronEnergy();

  TEST_EQUALITY_CONST( scattered_energy.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( scattered_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( scattered_energy.size(), 
                       scattered_incoming_energy.size() );

  std::vector<double> angular_grid = 
    data_container.getCutoffElasticAngularEnergyGrid();

  TEST_EQUALITY_CONST( angular_grid.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( angular_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( angular_grid.size(), 16 );

  std::vector<double> elastic_angles = 
    data_container.getCutoffElasticAngles(1.0e-5);

  TEST_EQUALITY_CONST( elastic_angles.front(), 1.0e-6 );
  TEST_EQUALITY_CONST( elastic_angles.back(), 2.0 );
  TEST_EQUALITY_CONST( elastic_angles.size(), 2 );

  elastic_angles = 
    data_container.getCutoffElasticAngles(1.0e+5);

  TEST_EQUALITY_CONST( elastic_angles.front(), 1.0e-6 );
  TEST_EQUALITY_CONST( elastic_angles.back(), 2.0 );
  TEST_EQUALITY_CONST( elastic_angles.size(), 96 );

  std::vector<double> elastic_pdf = 
    data_container.getCutoffElasticPDF(1.0e-5);

  TEST_EQUALITY_CONST( elastic_pdf.front(), 0.5 );
  TEST_EQUALITY_CONST( elastic_pdf.back(), 0.5 );
  TEST_EQUALITY_CONST( elastic_pdf.size(), 2 );

  elastic_pdf = 
    data_container.getCutoffElasticPDF(1.0e+5);

  TEST_EQUALITY_CONST( elastic_pdf.front(), 9.868670E+05 );
  TEST_EQUALITY_CONST( elastic_pdf.back(), 1.693970E-11 );
  TEST_EQUALITY_CONST( elastic_pdf.size(), 96 );

  cross_section = 
    data_container.getTotalElasticCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 3.06351e+9 );
  TEST_EQUALITY_CONST( cross_section.back(), 1.40722e5 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

/*
  cross_section = 
    data_container.getScreenedRutherfordElasticCrossSection();

//  TEST_EQUALITY_CONST( cross_section.front(), 2.5745520470700284932 );
//! \todo double check what the front cross section should be 
  TEST_EQUALITY_CONST( cross_section.front(), 1.93634596180636436e+01 );
  TEST_EQUALITY_CONST( cross_section.back(), 1.407220E+05-4.723090E-04 );
  TEST_EQUALITY_CONST( cross_section.size(), 728-threshold );
*/

//---------------------------------------------------------------------------//
// CHECK ELECTROIONIZATION DATA 
//---------------------------------------------------------------------------//
  // Subshell 1
  energy_grid = data_container.getElectroionizationCrossSectionEnergyGrid( 1u );

  TEST_EQUALITY_CONST( energy_grid.front(), 2.9101e-4 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 25 );

  cross_section = 
    data_container.getElectroionizationCrossSection( 1u );

  TEST_EQUALITY_CONST( cross_section.front(), 0.0 );
  TEST_EQUALITY_CONST( cross_section.back(), 1.338050e4 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

  scattered_incoming_energy =  
    data_container.getElectroionizationAverageScatteredElectronIncomingEnergy( 1u );

  TEST_EQUALITY_CONST( scattered_incoming_energy.front(), 2.9101e-4 );
  TEST_EQUALITY_CONST( scattered_incoming_energy.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( scattered_incoming_energy.size(), 6 );

  scattered_energy =  
    data_container.getElectroionizationAverageScatteredElectronEnergy( 1u );

  TEST_EQUALITY_CONST( scattered_energy.front(), 0.0 );
  TEST_EQUALITY_CONST( scattered_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( scattered_energy.size(), 
                       scattered_incoming_energy.size() );

  std::vector<double> recoil_incoming_energy =  
    data_container.getElectroionizationAverageRecoilElectronIncomingEnergy( 1u );

  TEST_EQUALITY_CONST( recoil_incoming_energy.front(), 2.9101e-4 );
  TEST_EQUALITY_CONST( recoil_incoming_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( recoil_incoming_energy.size(), 22 );

  std::vector<double> recoil_energy =  
    data_container.getElectroionizationAverageRecoilElectronEnergy( 1u );

  TEST_EQUALITY_CONST( recoil_energy.front(), 0.0 );
  TEST_EQUALITY_CONST( recoil_energy.back(), 8.76406e-4 );
  TEST_EQUALITY_CONST( recoil_energy.size(), recoil_incoming_energy.size() );

  std::vector<double> recoil_energy_grid =  
    data_container.getElectroionizationRecoilEnergyGrid( 1u );

  TEST_EQUALITY_CONST( recoil_energy_grid.front(), 2.910100E-04 );
  TEST_EQUALITY_CONST( recoil_energy_grid.back(), 1.00000e+5 );
  TEST_EQUALITY_CONST( recoil_energy_grid.size(), 7 );

  std::vector<double> electroionization_recoil_energy =  
    data_container.getElectroionizationRecoilEnergy( 1u, 2.910100E-04 );

  TEST_EQUALITY_CONST( electroionization_recoil_energy.front(), 1.00000e-8 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.back(), 1.00000e-7 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.size(), 2 );

  electroionization_recoil_energy =  
    data_container.getElectroionizationRecoilEnergy( 1u, 1.00000e+5 );

  TEST_EQUALITY_CONST( electroionization_recoil_energy.front(), 1.00000e-7 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.back(), 5.00000e+4 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.size(), 128 );

  std::vector<double> electroionization_recoil_pdf =  
    data_container.getElectroionizationRecoilPDF( 1u, 2.910100E-04 );

  TEST_EQUALITY_CONST( electroionization_recoil_pdf.front(), 1.111110E+07 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.back(), 1.111110E+07 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.size(), 2 );

  electroionization_recoil_pdf =  
    data_container.getElectroionizationRecoilPDF( 1u, 1.00000e+5 );

  TEST_EQUALITY_CONST( electroionization_recoil_pdf.front(), 7.358100E+03 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.back(), 3.45597E-14 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.size(), 128 );


  // Subshell 4
  energy_grid = data_container.getElectroionizationCrossSectionEnergyGrid( 4u );

  TEST_EQUALITY_CONST( energy_grid.front(), 8.980e-6 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 35 );

  cross_section = 
    data_container.getElectroionizationCrossSection( 4u );

  TEST_EQUALITY_CONST( cross_section.front(), 0.0 );
  TEST_EQUALITY_CONST( cross_section.back(), 2.017010E+05 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );


  scattered_incoming_energy =  
    data_container.getElectroionizationAverageScatteredElectronIncomingEnergy( 4u );

  TEST_EQUALITY_CONST( scattered_incoming_energy.front(), 8.980e-6 );
  TEST_EQUALITY_CONST( scattered_incoming_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( scattered_incoming_energy.size(), 6 );

  scattered_energy =  
    data_container.getElectroionizationAverageScatteredElectronEnergy( 4u );

  TEST_EQUALITY_CONST( scattered_energy.front(), 0.0 );
  TEST_EQUALITY_CONST( scattered_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( scattered_energy.size(), 
                       scattered_incoming_energy.size() );

  recoil_incoming_energy =  
    data_container.getElectroionizationAverageRecoilElectronIncomingEnergy( 4u );

  TEST_EQUALITY_CONST( recoil_incoming_energy.front(), 8.980e-6 );
  TEST_EQUALITY_CONST( recoil_incoming_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( recoil_incoming_energy.size(), 25 );

  recoil_energy =  
    data_container.getElectroionizationAverageRecoilElectronEnergy( 4u );

  TEST_EQUALITY_CONST( recoil_energy.front(), 0.0 );
  TEST_EQUALITY_CONST( recoil_energy.back(), 4.687980e-5 );
  TEST_EQUALITY_CONST( recoil_energy.size(), recoil_incoming_energy.size() );

  recoil_energy_grid =  
    data_container.getElectroionizationRecoilEnergyGrid( 4u );

  TEST_EQUALITY_CONST( recoil_energy_grid.front(), 8.980000E-06 );
  TEST_EQUALITY_CONST( recoil_energy_grid.back(), 1.00000e+5 );
  TEST_EQUALITY_CONST( recoil_energy_grid.size(), 8 );

  electroionization_recoil_energy =  
    data_container.getElectroionizationRecoilEnergy( 4u, 8.980000E-06 );

  TEST_EQUALITY_CONST( electroionization_recoil_energy.front(), 2.550000E-09 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.back(), 2.550000E-08 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.size(), 2 );

  electroionization_recoil_energy =  
    data_container.getElectroionizationRecoilEnergy( 4u, 1.00000e+5 );

  TEST_EQUALITY_CONST( electroionization_recoil_energy.front(), 1.00000e-7 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.back(), 5.00000e+4 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.size(), 143 );

  electroionization_recoil_pdf =  
    data_container.getElectroionizationRecoilPDF( 4u, 8.980000E-06 );

  TEST_EQUALITY_CONST( electroionization_recoil_pdf.front(), 4.357300E+07 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.back(), 4.357300E+07 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.size(), 2 );

  electroionization_recoil_pdf =  
    data_container.getElectroionizationRecoilPDF( 4u, 1.00000e+5 );

  TEST_EQUALITY_CONST( electroionization_recoil_pdf.front(), 1.120930E+05 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.back(), 1.515230E-15 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.size(), 143 );

//---------------------------------------------------------------------------//
// CHECK BREMSSTRAHLUNG DATA 
//---------------------------------------------------------------------------//
  energy_grid = data_container.getBremsstrahlungCrossSectionEnergyGrid();
  TEST_EQUALITY_CONST( energy_grid.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 84 );

  cross_section = 
    data_container.getBremsstrahlungCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 6.03128e2 );
  TEST_EQUALITY_CONST( cross_section.back(), 1.69715e1 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

  std::vector<double> photon_incoming_energy =  
    data_container.getBremsstrahlungAveragePhotonIncomingEnergy();

  TEST_EQUALITY_CONST( photon_incoming_energy.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( photon_incoming_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( photon_incoming_energy.size(), 75 );

  std::vector<double> photon_energy =  
    data_container.getBremsstrahlungAveragePhotonEnergy();

  TEST_EQUALITY_CONST( photon_energy.front(), 2.15038e-6 );
  TEST_EQUALITY_CONST( photon_energy.back(), 2.71203e3 );
  TEST_EQUALITY_CONST( photon_energy.size(), photon_incoming_energy.size() );

  std::vector<double> bremsstrahlung_photon_energy_grid =  
    data_container.getBremsstrahlungPhotonEnergyGrid();

  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy_grid.front(), 1.00000e-5 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy_grid.back(), 1.00000e+5 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy_grid.size(), 9 );

  std::vector<double> bremsstrahlung_photon_energy =  
    data_container.getBremsstrahlungPhotonEnergy( 1.00000e-5 );

  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.back(), 1.00000e-5 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.size(), 17 );

  bremsstrahlung_photon_energy =  
    data_container.getBremsstrahlungPhotonEnergy( 1.00000e+5 );

  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.back(), 1.00000e+5 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.size(), 105 );

  std::vector<double> bremsstrahlung_photon_pdf =  
    data_container.getBremsstrahlungPhotonPDF( 1.00000e-5 );

  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.front(), 2.134970E+06 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.back(), 2.136140E+04 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.size(), 17 );

  bremsstrahlung_photon_pdf =  
    data_container.getBremsstrahlungPhotonPDF( 1.00000e+5 );

  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.front(), 3.649330E+05 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.back(),  5.638520E-09 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.size(), 105 );

  std::vector<double> electron_incoming_energy =  
    data_container.getBremsstrahlungAverageElectronIncomingEnergy();

  TEST_EQUALITY_CONST( electron_incoming_energy.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( electron_incoming_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( electron_incoming_energy.size(), 76 );

  std::vector<double> electron_energy =  
    data_container.getBremsstrahlungAverageElectronEnergy();

  TEST_EQUALITY_CONST( electron_energy.front(), 7.84962e-6 );
  TEST_EQUALITY_CONST( electron_energy.back(), 9.7288e4 );
  TEST_EQUALITY_CONST( electron_energy.size(), 
                       electron_incoming_energy.size() );

//---------------------------------------------------------------------------//
// CHECK ATOMIC EXCITAION DATA 
//---------------------------------------------------------------------------//
  energy_grid = data_container.getAtomicExcitationEnergyGrid();

  TEST_EQUALITY_CONST( energy_grid.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 181 );

  cross_section = 
    data_container.getAtomicExcitationCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 3.168630E+06 );
  TEST_EQUALITY_CONST( cross_section.back(), 1.19892e5 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

  std::vector<double> atomic_excitation_energy_loss =  
    data_container.getAtomicExcitationEnergyLoss();

  TEST_EQUALITY_CONST( atomic_excitation_energy_loss.front(), 9.232690E-06 );
  TEST_EQUALITY_CONST( atomic_excitation_energy_loss.back(), 1.981540E-05 );
  TEST_EQUALITY_CONST( atomic_excitation_energy_loss.size(), 
                       energy_grid.size() );
  
/*
  data_container.exportData( "test_c_epr.xml",
			     Utility::ArchivableObject::XML_ARCHIVE );*/
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_h_eadl_file",
		 &test_h_eadl_file_name,
		 "Test EADL file name" );

  clp.setOption( "test_h_epdl_file",
		 &test_h_epdl_file_name,
		 "Test EPDL file name" );

  clp.setOption( "test_h_eedl_file",
		 &test_h_eedl_file_name,
		 "Test EEDL file name" );

  clp.setOption( "test_c_eadl_file",
		 &test_c_eadl_file_name,
		 "Test EADL file name" );

  clp.setOption( "test_c_epdl_file",
		 &test_c_epdl_file_name,
		 "Test EPDL file name" );

  clp.setOption( "test_c_eedl_file",
		 &test_c_eedl_file_name,
		 "Test EEDL file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  
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
// end tstStandardENDLDataGenerator.cpp
//---------------------------------------------------------------------------//
