//---------------------------------------------------------------------------//
//!
//! \file   tstStandardEvaluatedElectronDataGenerator.cpp
//! \author Luke Kersting
//! \brief  The eedl data generator class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <string>
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "DataGen_StandardEvaluatedElectronDataGenerator.hpp"
#include "DataGen_EvaluatedElectronDataGenerator.hpp"
#include "Data_ENDLFileHandler.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"


//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<const DataGen::StandardEvaluatedElectronDataGenerator>
  data_generator_h, data_generator_pb;

Teuchos::RCP<Data::XSSEPRDataExtractor> 
  h_xss_data_extractor, pb_xss_data_extractor;

std::string test_h_eedl_file_name, test_pb_eedl_file_name;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a data container can be populated
TEUCHOS_UNIT_TEST( StandardEvaluatedElectronDataGenerator,
                   populateEvaluatedDataContainer_h )
{
  unsigned atomic_number;
  double min_electron_energy = 1.0e-5;
  double max_electron_energy = 1.0e+5;
  double cutoff_angle = 1.0e-6;
  double grid_convergence_tol = 0.001;
  double grid_absolute_diff_tol = 1e-13;
  double grid_distance_tol = 1e-13;

  atomic_number = 1u;    

Teuchos::RCP<Data::ENDLFileHandler> eedl_file_handler( 
    new Data::ENDLFileHandler( test_h_eedl_file_name ) );

  data_generator_h.reset( 
		new DataGen::StandardEvaluatedElectronDataGenerator(
            atomic_number,
            eedl_file_handler,
            h_xss_data_extractor,
            min_electron_energy,
            max_electron_energy,
            cutoff_angle,
            grid_convergence_tol,
            grid_absolute_diff_tol,
            grid_distance_tol ) );

  Data::EvaluatedElectronVolatileDataContainer data_container;

  data_generator_h->populateEvaluatedDataContainer( data_container );

  TEST_EQUALITY_CONST( data_container.getAtomicNumber(), 1 );

  std::set<unsigned> atomic_subshells = data_container.getSubshells();
  TEST_EQUALITY_CONST( *atomic_subshells.begin(), 1 );
  TEST_EQUALITY_CONST( atomic_subshells.size(), 1 );

  TEST_EQUALITY_CONST( data_container.getSubshellOccupancy( 1 ), 1 );
  TEST_ASSERT( !data_container.hasRelaxationData() );
  TEST_ASSERT( !data_container.hasSubshellRelaxationData( 1 ) );

  double binding_energy = 
    data_container.getSubshellBindingEnergy( *atomic_subshells.begin() );
  TEST_EQUALITY_CONST( binding_energy, 1.36100e-5 );

  std::vector<double> energy_grid = data_container.getElectronEnergyGrid();
  TEST_EQUALITY_CONST( energy_grid.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 728 );

  TEST_EQUALITY_CONST( data_container.getCutoffAngle(), 1.0e-6 );

  // Check the elastic data
  unsigned threshold = 
    data_container.getCutoffElasticCrossSectionThresholdEnergyIndex(); 

  TEST_EQUALITY_CONST( threshold, 0 );

  std::vector<double> cross_section = 
    data_container.getCutoffElasticCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 2.74896e+8 );
  TEST_FLOATING_EQUALITY( cross_section.back(), 1.31176e-5, 1e-15 );
  TEST_EQUALITY_CONST( cross_section.size(), 728-threshold );

  threshold = 
    data_container.getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(); 

  TEST_EQUALITY_CONST( threshold, 263 );

  cross_section = 
    data_container.getScreenedRutherfordElasticCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 2.5745520470700284932 );
  TEST_EQUALITY_CONST( cross_section.back(), 1.29871e+4-1.31176e-5 );
  TEST_EQUALITY_CONST( cross_section.size(), 728-threshold );

  std::vector<double> angular_grid = 
    data_container.getElasticAngularEnergyGrid();

  TEST_EQUALITY_CONST( angular_grid.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( angular_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( angular_grid.size(), 16 );

  std::vector<double> elastic_angles = 
    data_container.getAnalogElasticAngles(1.0e-5);

  TEST_EQUALITY_CONST( elastic_angles.front(), 1.0e-6 );
  TEST_EQUALITY_CONST( elastic_angles.back(), 2.0 );
  TEST_EQUALITY_CONST( elastic_angles.size(), 2 );

  elastic_angles = 
    data_container.getAnalogElasticAngles(1.0e+5);

  TEST_EQUALITY_CONST( elastic_angles.front(), 1.0e-6 );
  TEST_EQUALITY_CONST( elastic_angles.back(), 2.0 );
  TEST_EQUALITY_CONST( elastic_angles.size(), 96 );

  std::vector<double> elastic_pdf = 
    data_container.getAnalogElasticPDF(1.0e-5);

  TEST_EQUALITY_CONST( elastic_pdf.front(), 0.5 );
  TEST_EQUALITY_CONST( elastic_pdf.back(), 0.5 );
  TEST_EQUALITY_CONST( elastic_pdf.size(), 2 );

  elastic_pdf = 
    data_container.getAnalogElasticPDF(1.0e+5);

  TEST_EQUALITY_CONST( elastic_pdf.front(), 9.86945e+5 );
  TEST_EQUALITY_CONST( elastic_pdf.back(), 6.25670e-13 );
  TEST_EQUALITY_CONST( elastic_pdf.size(), 96 );

  std::vector<double> moliere_screening_constant = 
    data_container.getMoliereScreeningConstant();

  TEST_EQUALITY_CONST( moliere_screening_constant.front(), 
                       -1.0e-6 );
  TEST_EQUALITY_CONST( moliere_screening_constant[1], 
                       -1.0039841898413188328e-06 );
  TEST_EQUALITY_CONST( moliere_screening_constant.back(), 
                       9.968622523875358279e-16 );
  TEST_EQUALITY_CONST( moliere_screening_constant.size(), 8 );

  std::vector<double> screened_rutherford_normalization_constant = 
    data_container.getScreenedRutherfordNormalizationConstant();

  TEST_EQUALITY_CONST( screened_rutherford_normalization_constant.front(), 
                       0.0 );
  TEST_EQUALITY_CONST( screened_rutherford_normalization_constant[1], 
                       2.75592435140403470e-13 );
  TEST_EQUALITY_CONST( screened_rutherford_normalization_constant.back(),  
                       9.86945001967696289e-07 );
  TEST_EQUALITY_CONST( screened_rutherford_normalization_constant.size(), 8 );

  // Check the electroionization data
  threshold = 
    data_container.getElectroionizationCrossSectionThresholdEnergyIndex( 1u ); 

  TEST_EQUALITY_CONST( threshold, 7 );

  cross_section = 
    data_container.getElectroionizationCrossSection( 1u );

  TEST_EQUALITY_CONST( cross_section.front(), 1.26041968911917554e+06 );
  TEST_EQUALITY_CONST( cross_section.back(), 8.28924e+4 );
  TEST_EQUALITY_CONST( cross_section.size(), 728-threshold );

  std::vector<double> electroionization_energy_grid =  
    data_container.getElectroionizationEnergyGrid( 1u );

  TEST_EQUALITY_CONST( electroionization_energy_grid.front(), 1.36100e-5 );
  TEST_EQUALITY_CONST( electroionization_energy_grid.back(), 1.00000e+5 );
  TEST_EQUALITY_CONST( electroionization_energy_grid.size(), 8 );

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

  // Check the bremsstrahlung data
  threshold = 
    data_container.getBremsstrahlungCrossSectionThresholdEnergyIndex(); 

  TEST_EQUALITY_CONST( threshold, 0 );

  cross_section = 
    data_container.getBremsstrahlungCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(),  2.97832e+1 );
  TEST_EQUALITY_CONST( cross_section.back(), 9.90621e-1 );
  TEST_EQUALITY_CONST( cross_section.size(), 728-threshold );

  std::vector<double> bremsstrahlung_energy_grid =  
    data_container.getBremsstrahlungEnergyGrid();

  TEST_EQUALITY_CONST( bremsstrahlung_energy_grid.front(), 1.00000e-5 );
  TEST_EQUALITY_CONST( bremsstrahlung_energy_grid.back(), 1.00000e+5 );
  TEST_EQUALITY_CONST( bremsstrahlung_energy_grid.size(), 10 );

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

  // Check the atomic excitation data
  threshold = 
    data_container.getAtomicExcitationCrossSectionThresholdEnergyIndex(); 

  TEST_EQUALITY_CONST( threshold, 7 );

  cross_section = 
    data_container.getAtomicExcitationCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 6.23029e+5 );
  TEST_EQUALITY_CONST( cross_section.back(), 8.14416e+4 );
  TEST_EQUALITY_CONST( cross_section.size(), 728-threshold );

  std::vector<double> atomic_excitation_energy_grid =  
    data_container.getAtomicExcitationEnergyGrid();

  TEST_EQUALITY_CONST( atomic_excitation_energy_grid.front(), 1.36100e-5 );
  TEST_EQUALITY_CONST( atomic_excitation_energy_grid.back(), 1.00000e+5 );
  TEST_EQUALITY_CONST( atomic_excitation_energy_grid.size(), 170 );

  std::vector<double> atomic_excitation_energy_loss =  
    data_container.getAtomicExcitationEnergyLoss();

  TEST_EQUALITY_CONST( atomic_excitation_energy_loss.front(), 1.36100e-5 );
  TEST_EQUALITY_CONST( atomic_excitation_energy_loss.back(), 2.10777e-5 );
  TEST_EQUALITY_CONST( atomic_excitation_energy_loss.size(), 170 );

  data_container.exportData( "test_h_epr.xml",
			     Utility::ArchivableObject::XML_ARCHIVE );
/*
  data_container.exportData( "/home/ljkerst/software/frensie/data/test_h_epr.xml",
			     Utility::ArchivableObject::XML_ARCHIVE );*/
}

//---------------------------------------------------------------------------//
// Check that a data container can be populated
TEUCHOS_UNIT_TEST( StandardEvaluatedElectronDataGenerator,
                   populateEvaluatedDataContainer_pb )
{
  unsigned atomic_number;
  double min_electron_energy = 1.0e-5;
  double max_electron_energy = 1.0e+5;
  double cutoff_angle = 1.0e-6;
  double grid_convergence_tol = 0.001;
  double grid_absolute_diff_tol = 1e-13;
  double grid_distance_tol = 1e-13;

  atomic_number = 82u; 

Teuchos::RCP<Data::ENDLFileHandler> eedl_file_handler( 
    new Data::ENDLFileHandler( test_pb_eedl_file_name ) );

  data_generator_pb.reset( 
		new DataGen::StandardEvaluatedElectronDataGenerator(
            atomic_number,
            eedl_file_handler,
            pb_xss_data_extractor,
            min_electron_energy,
            max_electron_energy,
            cutoff_angle,
            grid_convergence_tol,
            grid_absolute_diff_tol,
            grid_distance_tol ) );

  Data::EvaluatedElectronVolatileDataContainer data_container;

  data_generator_pb->populateEvaluatedDataContainer( data_container );

  TEST_EQUALITY_CONST( data_container.getAtomicNumber(), 82 );

  std::set<unsigned> atomic_subshells = data_container.getSubshells();
  TEST_EQUALITY_CONST( *atomic_subshells.begin(), 1 );
  TEST_EQUALITY_CONST( *--atomic_subshells.end(), 44 );
  TEST_EQUALITY_CONST( atomic_subshells.size(), 24 );

  TEST_EQUALITY_CONST( data_container.getSubshellOccupancy( 1 ), 2 );
  TEST_ASSERT( data_container.hasRelaxationData() );
  TEST_ASSERT( data_container.hasSubshellRelaxationData( 1 ) );
  TEST_ASSERT( !data_container.hasSubshellRelaxationData( 44 ) );

  double binding_energy = 
    data_container.getSubshellBindingEnergy( *atomic_subshells.begin() );
  TEST_EQUALITY_CONST( binding_energy, 8.82900e-2 );

  binding_energy = 
    data_container.getSubshellBindingEnergy( *--atomic_subshells.end() );
  TEST_EQUALITY_CONST( binding_energy, 5.29000e-6 );

  std::vector<double> energy_grid = data_container.getElectronEnergyGrid();
  TEST_EQUALITY_CONST( energy_grid.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 759 );

  TEST_EQUALITY_CONST( data_container.getCutoffAngle(), 1.0e-6 );

  // Check the elastic data
  unsigned threshold = 
    data_container.getCutoffElasticCrossSectionThresholdEnergyIndex(); 

  TEST_EQUALITY_CONST( threshold, 0 );

  std::vector<double> cross_section = 
    data_container.getCutoffElasticCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 2.48924e+9 );
  TEST_FLOATING_EQUALITY( cross_section.back(), 8.83051e-2, 1e-15 );
  TEST_EQUALITY_CONST( cross_section.size(), 759-threshold );

  threshold = 
    data_container.getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(); 

  TEST_EQUALITY_CONST( threshold, 399 );

  cross_section = 
    data_container.getScreenedRutherfordElasticCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 3.40785608241669834e+04 );
  TEST_EQUALITY_CONST( cross_section.back(), 2.11161e+6-8.83051e-2 );
  TEST_EQUALITY_CONST( cross_section.size(), 759-threshold );

  std::vector<double> angular_grid = 
    data_container.getElasticAngularEnergyGrid();

  TEST_EQUALITY_CONST( angular_grid.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( angular_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( angular_grid.size(), 14 );

  std::vector<double> elastic_angles = 
    data_container.getAnalogElasticAngles(1.0e-5);

  TEST_EQUALITY_CONST( elastic_angles.front(), 1.0e-6 );
  TEST_EQUALITY_CONST( elastic_angles.back(), 2.0 );
  TEST_EQUALITY_CONST( elastic_angles.size(), 2 );

  elastic_angles = 
    data_container.getAnalogElasticAngles(1.0e+5);

  TEST_EQUALITY_CONST( elastic_angles.front(), 1.0e-6 );
  TEST_EQUALITY_CONST( elastic_angles.back(), 2.0 );
  TEST_EQUALITY_CONST( elastic_angles.size(), 90 );

  std::vector<double> elastic_pdf = 
    data_container.getAnalogElasticPDF(1.0e-5);

  TEST_EQUALITY_CONST( elastic_pdf.front(), 0.5 );
  TEST_EQUALITY_CONST( elastic_pdf.back(), 0.5 );
  TEST_EQUALITY_CONST( elastic_pdf.size(), 2 );

  elastic_pdf = 
    data_container.getAnalogElasticPDF(1.0e+5);

  TEST_EQUALITY_CONST( elastic_pdf.front(), 9.86374e+5 );
  TEST_EQUALITY_CONST( elastic_pdf.back(), 1.76576e-8 );
  TEST_EQUALITY_CONST( elastic_pdf.size(), 90 );

  std::vector<double> moliere_screening_constant = 
    data_container.getMoliereScreeningConstant();

  TEST_FLOATING_EQUALITY( moliere_screening_constant.front(), 
                          -1.0e-06,
                          1e-12 );
  TEST_FLOATING_EQUALITY( moliere_screening_constant[1], 
                          -1.06552060095948850e-05,
                          1e-12 );
  TEST_FLOATING_EQUALITY( moliere_screening_constant.back(), 
                          4.124902891289890E-14,
                          1e-12 );
  TEST_EQUALITY_CONST( moliere_screening_constant.size(), 5 );

  std::vector<double> screened_rutherford_normalization_constant = 
    data_container.getScreenedRutherfordNormalizationConstant();

  TEST_FLOATING_EQUALITY( screened_rutherford_normalization_constant.front(), 
                          0.0,
                          1e-12 );
  TEST_FLOATING_EQUALITY( screened_rutherford_normalization_constant[1], 
                          1.94353181297334527e-05,
                          1e-12 );
  TEST_FLOATING_EQUALITY( screened_rutherford_normalization_constant.back(),  
                          9.863740813739410E-07,
                          1e-12 );
  TEST_EQUALITY_CONST( screened_rutherford_normalization_constant.size(), 5 );

  // Check the electroionization data
  threshold = 
    data_container.getElectroionizationCrossSectionThresholdEnergyIndex( 1u ); 

  TEST_EQUALITY_CONST( threshold, 309 );

  cross_section = 
    data_container.getElectroionizationCrossSection( 1u );

  TEST_EQUALITY_CONST( cross_section.front(), 1.25067357130657558e-01 );
  TEST_EQUALITY_CONST( cross_section.back(), 3.64919e+1 );
  TEST_EQUALITY_CONST( cross_section.size(), 759-threshold );

  std::vector<double> electroionization_energy_grid =  
    data_container.getElectroionizationEnergyGrid( 1u );

  TEST_EQUALITY_CONST( electroionization_energy_grid.front(), 8.82900e-2 );
  TEST_EQUALITY_CONST( electroionization_energy_grid.back(), 1.00000e+5 );
  TEST_EQUALITY_CONST( electroionization_energy_grid.size(), 5 );

  std::vector<double> electroionization_recoil_energy =  
    data_container.getElectroionizationRecoilEnergy( 1u, 8.82900e-2 );

  TEST_EQUALITY_CONST( electroionization_recoil_energy.front(), 1.00000e-8 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.back(), 1.00000e-7 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.size(), 2 );

  electroionization_recoil_energy =  
    data_container.getElectroionizationRecoilEnergy( 1u, 1.00000e+5 );

  TEST_EQUALITY_CONST( electroionization_recoil_energy.front(), 1.00000e-7 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.back(), 5.00000e+4 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.size(), 90 );

  std::vector<double> electroionization_recoil_pdf =  
    data_container.getElectroionizationRecoilPDF( 1u, 8.82900e-2 );

  TEST_EQUALITY_CONST( electroionization_recoil_pdf.front(), 1.11111e+7 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.back(), 1.11111e+7 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.size(), 2 );

  electroionization_recoil_pdf =  
    data_container.getElectroionizationRecoilPDF( 1u, 1.00000e+5 );

  TEST_EQUALITY_CONST( electroionization_recoil_pdf.front(), 2.52642e+1 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.back(), 1.26188e-11 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.size(), 90 );

  threshold = 
    data_container.getElectroionizationCrossSectionThresholdEnergyIndex( 44u ); 

  TEST_EQUALITY_CONST( threshold, 0 );

  cross_section = 
    data_container.getElectroionizationCrossSection( 44u );

  TEST_EQUALITY_CONST( cross_section.front(), 1.06530e+8 );
  TEST_EQUALITY_CONST( cross_section.back(), 1.82234e+5 );
  TEST_EQUALITY_CONST( cross_section.size(), 759-threshold );

  electroionization_energy_grid =  
    data_container.getElectroionizationEnergyGrid( 44u );

  TEST_EQUALITY_CONST( electroionization_energy_grid.front(), 5.29000e-6 );
  TEST_EQUALITY_CONST( electroionization_energy_grid.back(), 1.00000e+5 );
  TEST_EQUALITY_CONST( electroionization_energy_grid.size(), 8 );

  electroionization_recoil_energy =  
    data_container.getElectroionizationRecoilEnergy( 44u, 5.29000e-6 );

  TEST_EQUALITY_CONST( electroionization_recoil_energy.front(), 2.54893e-9 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.back(), 2.54893e-8 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.size(), 2 );

  electroionization_recoil_energy =  
    data_container.getElectroionizationRecoilEnergy( 44u, 1.00000e+5 );

  TEST_EQUALITY_CONST( electroionization_recoil_energy.front(), 1.00000e-7 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.back(), 5.00000e+4 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.size(), 141 );

  electroionization_recoil_pdf =  
    data_container.getElectroionizationRecoilPDF( 44u, 5.29000e-6 );

  TEST_EQUALITY_CONST( electroionization_recoil_pdf.front(), 4.35913e+7 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.back(), 4.35913e+7 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.size(), 2 );

  electroionization_recoil_pdf =  
    data_container.getElectroionizationRecoilPDF( 44u, 1.00000e+5 );

  TEST_EQUALITY_CONST( electroionization_recoil_pdf.front(), 1.64629e+5 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.back(), 1.68999e-15 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.size(), 141 );

  // Check the bremsstrahlung data
  threshold = 
    data_container.getBremsstrahlungCrossSectionThresholdEnergyIndex(); 

  TEST_EQUALITY_CONST( threshold, 0 );

  cross_section = 
    data_container.getBremsstrahlungCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 4.86980e+3 );
  TEST_EQUALITY_CONST( cross_section.back(), 1.95417e+3 );
  TEST_EQUALITY_CONST( cross_section.size(), 759-threshold );

  std::vector<double> bremsstrahlung_energy_grid =  
    data_container.getBremsstrahlungEnergyGrid();

  TEST_EQUALITY_CONST( bremsstrahlung_energy_grid.front(), 1.00000e-5 );
  TEST_EQUALITY_CONST( bremsstrahlung_energy_grid.back(), 1.00000e+5 );
  TEST_EQUALITY_CONST( bremsstrahlung_energy_grid.size(), 9 );

  std::vector<double> bremsstrahlung_photon_energy =  
    data_container.getBremsstrahlungPhotonEnergy( 1.00000e-5 );

  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.back(), 1.00000e-5 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.size(), 17 );

  bremsstrahlung_photon_energy =  
    data_container.getBremsstrahlungPhotonEnergy( 1.00000e+5 );

  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.back(), 1.00000e+5 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.size(), 101 );

  std::vector<double> bremsstrahlung_photon_pdf =  
    data_container.getBremsstrahlungPhotonPDF( 1.00000e-5 );

  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.front(), 2.12760e+6 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.back(), 2.16305e+4 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.size(), 17 );

  bremsstrahlung_photon_pdf =  
    data_container.getBremsstrahlungPhotonPDF( 1.00000e+5 );

  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.front(), 3.64644e+5 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.back(),  4.47808e-8 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.size(), 101 );

  // Check the atomic excitation data
  threshold = 
    data_container.getAtomicExcitationCrossSectionThresholdEnergyIndex(); 

  TEST_EQUALITY_CONST( threshold, 0 );

  cross_section = 
    data_container.getAtomicExcitationCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 8.75755e+6 );
  TEST_EQUALITY_CONST( cross_section.back(), 1.57861e+6 );
  TEST_EQUALITY_CONST( cross_section.size(), 759-threshold );

  std::vector<double> atomic_excitation_energy_grid =  
    data_container.getAtomicExcitationEnergyGrid();

  TEST_EQUALITY_CONST( atomic_excitation_energy_grid.front(), 1.00000e-5 );
  TEST_EQUALITY_CONST( atomic_excitation_energy_grid.back(), 1.00000e+5 );
  TEST_EQUALITY_CONST( atomic_excitation_energy_grid.size(), 286 );

  std::vector<double> atomic_excitation_energy_loss =  
    data_container.getAtomicExcitationEnergyLoss();

  TEST_EQUALITY_CONST( atomic_excitation_energy_loss.front(), 6.29685e-6 );
  TEST_EQUALITY_CONST( atomic_excitation_energy_loss.back(), 1.09533e-5 );
  TEST_EQUALITY_CONST( atomic_excitation_energy_loss.size(), 286 );
		    
  data_container.exportData( "test_pb_epr.xml",
			     Utility::ArchivableObject::XML_ARCHIVE );
/*
  data_container.exportData( "/home/ljkerst/software/frensie/data/test_pb_epr.xml",
			     Utility::ArchivableObject::XML_ARCHIVE );
*/
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_h_ace_file_name, test_pb_ace_file_name;
  std::string test_h_ace_table_name, test_pb_ace_table_name;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_h_eedl_file",
		 &test_h_eedl_file_name,
		 "Test EEDL file name" );
  clp.setOption( "test_h_ace_file",
		 &test_h_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_h_ace_table",
		 &test_h_ace_table_name,
		 "Test ACE table name" );

  clp.setOption( "test_pb_eedl_file",
		 &test_pb_eedl_file_name,
		 "Test EEDL file name" );
  clp.setOption( "test_pb_ace_file",
		 &test_pb_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_pb_ace_table",
		 &test_pb_ace_table_name,
		 "Test ACE table name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  {
    // Create the ace file handler and data extractor for hydrogen
    Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
			       new Data::ACEFileHandler( test_h_ace_file_name,
							 test_h_ace_table_name,
							 1u ) );

    h_xss_data_extractor.reset(
				new Data::XSSEPRDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );
  }

  {
    // Create the ace file handler and data extractor for lead
    Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
			       new Data::ACEFileHandler( test_pb_ace_file_name,
							 test_pb_ace_table_name,
							 1u ) );

    pb_xss_data_extractor.reset(
				new Data::XSSEPRDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );
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
// end tstStandardEvaluatedElectronDataGenerator.cpp
//---------------------------------------------------------------------------//
