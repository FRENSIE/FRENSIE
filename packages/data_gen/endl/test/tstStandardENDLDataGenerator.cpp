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
#include "Data_ENDLVolatileDataContainer.hpp"
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


  Data::ENDLVolatileDataContainer data_container;

  data_generator_h->populateENDLDataContainer( data_container );

  TEST_EQUALITY_CONST( data_container.getAtomicNumber(), 1 );

//---------------------------------------------------------------------------//
// CHECK ATOMIC RELAXATION DATA
//---------------------------------------------------------------------------//

  TEST_EQUALITY_CONST( data_container.getSubshells().size(), 1 );
  TEST_ASSERT( data_container.getSubshells().count( 1 ) );
  TEST_EQUALITY_CONST( data_container.getSubshellOccupancy(1), 1 );
  TEST_EQUALITY_CONST( data_container.getSubshellBindingEnergy(1), 1.361e-5 );
  TEST_EQUALITY_CONST( data_container.getSubshellKineticEnergy(1), 1.361e-5 );
  TEST_EQUALITY_CONST( data_container.getSubshellAverageRadius(1), 7.9356e-9 );
  TEST_EQUALITY_CONST( data_container.getLocalDepositionPerInitialVacancy(1),
                       1.361e-5 );

//---------------------------------------------------------------------------//
// CHECK COHERENT PHOTON DATA
//---------------------------------------------------------------------------//
  {
  std::vector<double> energy_grid =
    data_container.getCoherentCrossSectionEnergyGrid();

  TEST_EQUALITY_CONST( energy_grid.front(), 1.0e-6 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 362 );

  std::vector<double> cross_section = data_container.getCoherentCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 9.887553000E-06 );
  TEST_EQUALITY_CONST( cross_section.back(), 4.626160000E-16 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

  std::vector<double> form_factor_argument =
    data_container.getCoherentFormFactorArgument();

  TEST_EQUALITY_CONST( form_factor_argument.front(), 0.0 );
  TEST_EQUALITY_CONST( form_factor_argument.back(), 1.0e17 );
  TEST_EQUALITY_CONST( form_factor_argument.size(), 90 );

  std::vector<double> form_factor = data_container.getCoherentFormFactor();

  TEST_EQUALITY_CONST( form_factor.front(), 1.0 );
  TEST_EQUALITY_CONST( form_factor.back(), 8.182900000E-39 );
  TEST_EQUALITY_CONST( form_factor.size(), form_factor_argument.size() );

  std::vector<double> factor_energy =
    data_container.getCoherentImaginaryAnomalousFactorIncidentEnergy();

  TEST_EQUALITY_CONST( factor_energy.front(), 1.0e-6 );
  TEST_EQUALITY_CONST( factor_energy.back(), 10.0 );
  TEST_EQUALITY_CONST( factor_energy.size(), 194 );

  std::vector<double> factor =
    data_container.getCoherentImaginaryAnomalousFactor();

  TEST_EQUALITY_CONST( factor.front(), 0.0 );
  TEST_EQUALITY_CONST( factor.back(), 6.265660000E-12 );
  TEST_EQUALITY_CONST( factor.size(), factor_energy.size() );

  factor_energy = data_container.getCoherentRealAnomalousFactorIncidentEnergy();

  TEST_EQUALITY_CONST( factor_energy.front(), 1.0e-6 );
  TEST_EQUALITY_CONST( factor_energy.back(), 10.0 );
  TEST_EQUALITY_CONST( factor_energy.size(), 308 );

  factor =
    data_container.getCoherentRealAnomalousFactor();

  TEST_EQUALITY_CONST( factor.front(), -9.961483000E-01 );
  TEST_EQUALITY_CONST( factor.back(), -2.665509000E-05 );
  TEST_EQUALITY_CONST( factor.size(), factor_energy.size() );

  std::vector<double> photon_energy_grid =
    data_container.getCoherentAveragePhotonIncidentEnergy();

  TEST_EQUALITY_CONST( photon_energy_grid.front(), 1.0e-6 );
  TEST_EQUALITY_CONST( photon_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( photon_energy_grid.size(), 2 );

  std::vector<double> photon_energy =
    data_container.getCoherentAveragePhotonEnergy();

  TEST_EQUALITY_CONST( photon_energy.front(), 1.0e-6 );
  TEST_EQUALITY_CONST( photon_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( photon_energy.size(), photon_energy_grid.size() );
  }
//---------------------------------------------------------------------------//
// SET INCOHERENT PHOTON DATA
//---------------------------------------------------------------------------//

  {
  std::vector<double> energy_grid =
    data_container.getIncoherentCrossSectionEnergyGrid();

  TEST_EQUALITY_CONST( energy_grid.front(), 1.0e-6 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 111 );

  std::vector<double> cross_section =
    data_container.getIncoherentCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 9.562300000E-08 );
  TEST_EQUALITY_CONST( cross_section.back(), 1.704200000E-05 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

  std::vector<double> scattering_function_argument =
    data_container.getIncoherentScatteringFunctionArgument();

  TEST_EQUALITY_CONST( scattering_function_argument.front(), 0.0 );
  TEST_EQUALITY_CONST( scattering_function_argument.back(), 1.0e17 );
  TEST_EQUALITY_CONST( scattering_function_argument.size(), 94 );

  std::vector<double> scattering_function =
    data_container.getIncoherentScatteringFunction();

  TEST_EQUALITY_CONST( scattering_function.front(), 0.0 );
  TEST_EQUALITY_CONST( scattering_function.back(), 1.0 );
  TEST_EQUALITY_CONST( scattering_function.size(),
                       scattering_function_argument.size() );

  std::vector<double> photon_energy_grid =
    data_container.getIncoherentAveragePhotonIncidentEnergy();

  TEST_EQUALITY_CONST( photon_energy_grid.front(), 1.0e-6 );
  TEST_EQUALITY_CONST( photon_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( photon_energy_grid.size(), 111 );

  std::vector<double> photon_energy =
    data_container.getIncoherentAveragePhotonEnergy();

  TEST_EQUALITY_CONST( photon_energy.front(), 9.999973000E-07 );
  TEST_EQUALITY_CONST( photon_energy.back(), 9.955317000E+03 );
  TEST_EQUALITY_CONST( photon_energy.size(), photon_energy_grid.size() );

  std::vector<double> electron_energy_grid =
    data_container.getIncoherentAverageElectronIncidentEnergy();

  TEST_EQUALITY_CONST( electron_energy_grid.front(), 1.0e-6 );
  TEST_EQUALITY_CONST( electron_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( electron_energy_grid.size(), 111 );

  std::vector<double> electron_energy =
    data_container.getIncoherentAverageElectronEnergy();

  TEST_EQUALITY_CONST( electron_energy.front(), 2.740270000E-12 );
  TEST_EQUALITY_CONST( electron_energy.back(), 9.004468000E+04 );
  TEST_EQUALITY_CONST( electron_energy.size(), electron_energy_grid.size() );
  }
//---------------------------------------------------------------------------//
// SET PHOTOELECTRIC PHOTON DATA
//---------------------------------------------------------------------------//
  {
  std::vector<double> energy_grid =
    data_container.getPhotoelectricCrossSectionEnergyGrid();

  TEST_EQUALITY_CONST( energy_grid.front(), 1.361000000E-05 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 73 );

  std::vector<double> cross_section =
    data_container.getPhotoelectricCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 6.305834000E+06 );
  TEST_EQUALITY_CONST( cross_section.back(), 7.736000000E-15 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

  std::vector<double> residual_energy_grid =
    data_container.getPhotoelectricAverageResidualIncidentEnergy();

  TEST_EQUALITY_CONST( residual_energy_grid.front(), 1.361000000E-05 );
  TEST_EQUALITY_CONST( residual_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( residual_energy_grid.size(), 2 );

  std::vector<double> residual_energy =
    data_container.getPhotoelectricAverageResidualEnergy();

  TEST_EQUALITY_CONST( residual_energy.front(), 1.361000000E-05 );
  TEST_EQUALITY_CONST( residual_energy.back(), 1.361000000E-05 );
  TEST_EQUALITY_CONST( residual_energy.size(), residual_energy_grid.size() );

  std::vector<double> photon_energy_grid =
    data_container.getPhotoelectricAveragePhotonsIncidentEnergy();

  TEST_EQUALITY_CONST( photon_energy_grid.size(), 0 );

  std::vector<double> photon_energy =
    data_container.getPhotoelectricAveragePhotonsEnergy();

  TEST_EQUALITY_CONST( photon_energy.size(), photon_energy_grid.size() );

  std::vector<double> electron_energy_grid =
    data_container.getPhotoelectricAverageElectronsIncidentEnergy();

  TEST_EQUALITY_CONST( electron_energy_grid.front(), 1.361000000E-05 );
  TEST_EQUALITY_CONST( electron_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( electron_energy_grid.size(), 2 );

  std::vector<double> electron_energy =
    data_container.getPhotoelectricAverageElectronsEnergy();

  TEST_EQUALITY_CONST( electron_energy.front(), 0.0 );
  TEST_EQUALITY_CONST( electron_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( electron_energy.size(), electron_energy_grid.size() );
  }
//---------------------------------------------------------------------------//
// SET PHOTOELECTRIC PHOTON DATA BY SUBSHELL
//---------------------------------------------------------------------------//
  {
  std::vector<double> energy_grid =
    data_container.getPhotoelectricCrossSectionEnergyGrid(1);

  TEST_EQUALITY_CONST( energy_grid.front(), 1.361000000E-05 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 73 );

  std::vector<double> cross_section =
    data_container.getPhotoelectricCrossSection(1);

  TEST_EQUALITY_CONST( cross_section.front(), 6.305834000E+06 );
  TEST_EQUALITY_CONST( cross_section.back(), 7.736000000E-15 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

  std::vector<double> residual_energy_grid =
    data_container.getPhotoelectricAverageResidualIncidentEnergy(1);

  TEST_EQUALITY_CONST( residual_energy_grid.front(), 1.361000000E-05 );
  TEST_EQUALITY_CONST( residual_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( residual_energy_grid.size(), 2 );

  std::vector<double> residual_energy =
    data_container.getPhotoelectricAverageResidualEnergy(1);

  TEST_EQUALITY_CONST( residual_energy.front(), 1.361000000E-05 );
  TEST_EQUALITY_CONST( residual_energy.back(), 1.361000000E-05 );
  TEST_EQUALITY_CONST( residual_energy.size(), residual_energy_grid.size() );

  std::vector<double> electron_energy_grid =
    data_container.getPhotoelectricAverageElectronsIncidentEnergy(1);

  TEST_EQUALITY_CONST( electron_energy_grid.front(), 1.361000000E-05 );
  TEST_EQUALITY_CONST( electron_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( electron_energy_grid.size(), 2 );

  std::vector<double> electron_energy =
    data_container.getPhotoelectricAverageElectronsEnergy(1);

  TEST_EQUALITY_CONST( electron_energy.front(), 0.0 );
  TEST_EQUALITY_CONST( electron_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( electron_energy.size(), electron_energy_grid.size() );
  }
//---------------------------------------------------------------------------//
// SET PAIR PRODUCTION PHOTON DATA
//---------------------------------------------------------------------------//
  {
  std::vector<double> energy_grid =
    data_container.getPairProductionCrossSectionEnergyGrid();

  TEST_EQUALITY_CONST( energy_grid.front(), 1.022000000E+00 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 83 );

  std::vector<double> cross_section =
    data_container.getPairProductionCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 0.0 );
  TEST_EQUALITY_CONST( cross_section.back(), 9.601000000E-03 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

  std::vector<double> positron_energy_grid =
    data_container.getPairProductionAveragePositronIncidentEnergy();

  TEST_EQUALITY_CONST( positron_energy_grid.front(),  1.022000000E+00 );
  TEST_EQUALITY_CONST( positron_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( positron_energy_grid.size(), 2 );

  std::vector<double> positron_energy =
    data_container.getPairProductionAveragePositronEnergy();

  TEST_EQUALITY_CONST( positron_energy.front(), 0.0 );
  TEST_EQUALITY_CONST( positron_energy.back(), 4.999949000E+04 );
  TEST_EQUALITY_CONST( positron_energy.size(), positron_energy_grid.size() );

  std::vector<double> electron_energy_grid =
    data_container.getPairProductionAverageElectronIncidentEnergy();

  TEST_EQUALITY_CONST( electron_energy_grid.front(),  1.022000000E+00 );
  TEST_EQUALITY_CONST( electron_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( electron_energy_grid.size(), 2 );

  std::vector<double> electron_energy =
    data_container.getPairProductionAverageElectronEnergy();

  TEST_EQUALITY_CONST( electron_energy.front(), 0.0 );
  TEST_EQUALITY_CONST( electron_energy.back(), 4.999949000E+04 );
  TEST_EQUALITY_CONST( electron_energy.size(), electron_energy_grid.size() );
  }
//---------------------------------------------------------------------------//
// SET TRIPLET PRODUCTION PHOTON DATA
//---------------------------------------------------------------------------//
  {
  std::vector<double> energy_grid =
    data_container.getTripletProductionCrossSectionEnergyGrid();

  TEST_EQUALITY_CONST( energy_grid.front(), 2.044000000E+00 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 77 );

  std::vector<double> cross_section =
    data_container.getTripletProductionCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 0.0 );
  TEST_EQUALITY_CONST( cross_section.back(), 1.110000000E-02 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

  std::vector<double> positron_energy_grid =
    data_container.getTripletProductionAveragePositronIncidentEnergy();

  TEST_EQUALITY_CONST( positron_energy_grid.front(), 2.044000000E+00 );
  TEST_EQUALITY_CONST( positron_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( positron_energy_grid.size(), 2 );

  std::vector<double> positron_energy =
    data_container.getTripletProductionAveragePositronEnergy();

  TEST_EQUALITY_CONST( positron_energy.front(), 5.110000000E-01 );
  TEST_EQUALITY_CONST( positron_energy.back(), 4.999949000E+04 );
  TEST_EQUALITY_CONST( positron_energy.size(), positron_energy_grid.size() );

  std::vector<double> electron_energy_grid =
    data_container.getTripletProductionAverageElectronIncidentEnergy();

  TEST_EQUALITY_CONST( electron_energy_grid.front(), 2.044000000E+00 );
  TEST_EQUALITY_CONST( electron_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( electron_energy_grid.size(), 2 );

  std::vector<double> electron_energy =
    data_container.getTripletProductionAverageElectronEnergy();

  TEST_EQUALITY_CONST( electron_energy.front(), 5.110000000E-01 );
  TEST_EQUALITY_CONST( electron_energy.back(), 4.999949000E+04 );
  TEST_EQUALITY_CONST( electron_energy.size(), electron_energy_grid.size() );
  }

//---------------------------------------------------------------------------//
// CHECK ELASTIC DATA
//---------------------------------------------------------------------------//
  {
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

  std::vector<double> residual_energy_grid =
    data_container.getCutoffElasticResidualIncidentEnergy();

  TEST_EQUALITY_CONST( residual_energy_grid.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( residual_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( residual_energy_grid.size(), 2 );

  std::vector<double> residual_energy =
    data_container.getCutoffElasticResidualEnergy();

  TEST_EQUALITY_CONST( residual_energy.front(), 0.0 );
  TEST_EQUALITY_CONST( residual_energy.back(), 0.0 );
  TEST_EQUALITY_CONST( residual_energy.size(),
                       residual_energy_grid.size() );

  std::vector<double> scattered_incident_energy =
    data_container.getCutoffElasticScatteredElectronIncidentEnergy();

  TEST_EQUALITY_CONST( scattered_incident_energy.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( scattered_incident_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( scattered_incident_energy.size(), 2 );

  std::vector<double> scattered_energy =
    data_container.getCutoffElasticScatteredElectronEnergy();

  TEST_EQUALITY_CONST( scattered_energy.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( scattered_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( scattered_energy.size(),
                       scattered_incident_energy.size() );

  std::vector<double> angular_grid =
    data_container.getCutoffElasticAngularEnergyGrid();

  TEST_EQUALITY_CONST( angular_grid.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( angular_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( angular_grid.size(), 16 );

  std::vector<double> elastic_angles =
    data_container.getCutoffElasticAnglesAtEnergy(1.0e-5);

  TEST_EQUALITY_CONST( elastic_angles.front(), 1.0e-6 );
  TEST_EQUALITY_CONST( elastic_angles.back(), 2.0 );
  TEST_EQUALITY_CONST( elastic_angles.size(), 2 );

  elastic_angles =
    data_container.getCutoffElasticAnglesAtEnergy(1.0e+5);

  TEST_EQUALITY_CONST( elastic_angles.front(), 1.0e-6 );
  TEST_EQUALITY_CONST( elastic_angles.back(), 2.0 );
  TEST_EQUALITY_CONST( elastic_angles.size(), 96 );

  std::vector<double> elastic_pdf =
    data_container.getCutoffElasticPDFAtEnergy(1.0e-5);

  TEST_EQUALITY_CONST( elastic_pdf.front(), 0.5 );
  TEST_EQUALITY_CONST( elastic_pdf.back(), 0.5 );
  TEST_EQUALITY_CONST( elastic_pdf.size(), 2 );

  elastic_pdf =
    data_container.getCutoffElasticPDFAtEnergy(1.0e+5);

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
  }
//---------------------------------------------------------------------------//
// CHECK ELECTROIONIZATION DATA
//---------------------------------------------------------------------------//
  {
  std::vector<double> energy_grid =
    data_container.getElectroionizationCrossSectionEnergyGrid( 1u );
  TEST_EQUALITY_CONST( energy_grid.front(), 1.361e-5 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 35 );

  std::vector<double> cross_section =
    data_container.getElectroionizationCrossSection( 1u );

  TEST_EQUALITY_CONST( cross_section.front(), 0.0 );
  TEST_EQUALITY_CONST( cross_section.back(), 8.28924e+4 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

  std::vector<double> scattered_incident_energy =
    data_container.getElectroionizationAverageScatteredElectronIncidentEnergy( 1u );

  TEST_EQUALITY_CONST( scattered_incident_energy.front(), 1.361e-5 );
  TEST_EQUALITY_CONST( scattered_incident_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( scattered_incident_energy.size(), 6 );

  std::vector<double> scattered_energy =
    data_container.getElectroionizationAverageScatteredElectronEnergy( 1u );

  TEST_EQUALITY_CONST( scattered_energy.front(), 0.0 );
  TEST_EQUALITY_CONST( scattered_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( scattered_energy.size(),
                       scattered_incident_energy.size() );

  std::vector<double> recoil_incident_energy =
    data_container.getElectroionizationAverageRecoilElectronIncidentEnergy( 1u );

  TEST_EQUALITY_CONST( recoil_incident_energy.front(), 1.361e-5 );
  TEST_EQUALITY_CONST( recoil_incident_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( recoil_incident_energy.size(), 25 );

  std::vector<double> recoil_energy =
    data_container.getElectroionizationAverageRecoilElectronEnergy( 1u );

  TEST_EQUALITY_CONST( recoil_energy.front(), 0.0 );
  TEST_EQUALITY_CONST( recoil_energy.back(), 7.28699e-5 );
  TEST_EQUALITY_CONST( recoil_energy.size(),
                       recoil_incident_energy.size() );

  std::vector<double> recoil_energy_grid =
    data_container.getElectroionizationRecoilEnergyGrid( 1u );

  TEST_EQUALITY_CONST( recoil_energy_grid.front(), 1.36100e-5 );
  TEST_EQUALITY_CONST( recoil_energy_grid.back(), 1.00000e+5 );
  TEST_EQUALITY_CONST( recoil_energy_grid.size(), 8 );

  std::vector<double> electroionization_recoil_energy =
    data_container.getElectroionizationRecoilEnergyAtEnergy( 1u, 1.36100e-5 );

  TEST_EQUALITY_CONST( electroionization_recoil_energy.front(), 2.79866e-9 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.back(), 2.79866e-8 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.size(), 2 );

  electroionization_recoil_energy =
    data_container.getElectroionizationRecoilEnergyAtEnergy( 1u, 1.00000e+5 );

  TEST_EQUALITY_CONST( electroionization_recoil_energy.front(), 1.00000e-7 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.back(), 5.00000e+4 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.size(), 147 );

  std::vector<double> electroionization_recoil_pdf =
    data_container.getElectroionizationRecoilPDFAtEnergy( 1u, 1.36100e-5 );

  TEST_EQUALITY_CONST( electroionization_recoil_pdf.front(), 3.97015e+7 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.back(), 3.97015e+7 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.size(), 2 );

  electroionization_recoil_pdf =
    data_container.getElectroionizationRecoilPDFAtEnergy( 1u, 1.00000e+5 );

  TEST_EQUALITY_CONST( electroionization_recoil_pdf.front(), 1.61897e+5 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.back(), 2.77550e-15 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.size(), 147 );
  }
//---------------------------------------------------------------------------//
// CHECK BREMSSTRAHLUNG DATA
//---------------------------------------------------------------------------//
  {
  std::vector<double> energy_grid =
    data_container.getBremsstrahlungCrossSectionEnergyGrid();

  TEST_EQUALITY_CONST( energy_grid.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 96 );

  std::vector<double> cross_section =
    data_container.getBremsstrahlungCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(),  2.97832e+1 );
  TEST_EQUALITY_CONST( cross_section.back(), 9.90621e-1 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

  std::vector<double> photon_energy_grid =
    data_container.getBremsstrahlungAveragePhotonIncidentEnergy();

  TEST_EQUALITY_CONST( photon_energy_grid.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( photon_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( photon_energy_grid.size(), 82 );

  std::vector<double> photon_energy =
    data_container.getBremsstrahlungAveragePhotonEnergy();

  TEST_EQUALITY_CONST( photon_energy.front(), 2.14426e-6 );
  TEST_EQUALITY_CONST( photon_energy.back(), 2.66815e3 );
  TEST_EQUALITY_CONST( photon_energy.size(),
                       photon_energy_grid.size() );

  std::vector<double> bremsstrahlung_photon_energy_grid =
    data_container.getBremsstrahlungPhotonEnergyGrid();

  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy_grid.front(), 1.00000e-5 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy_grid.back(), 1.00000e+5 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy_grid.size(), 10 );

  std::vector<double> bremsstrahlung_photon_energy =
    data_container.getBremsstrahlungPhotonEnergyAtEnergy( 1.00000e-5 );

  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.back(), 1.00000e-5 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.size(), 17 );

  bremsstrahlung_photon_energy =
    data_container.getBremsstrahlungPhotonEnergyAtEnergy( 1.00000e+5 );

  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.back(), 1.00000e+5 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.size(), 111 );

  std::vector<double> bremsstrahlung_photon_pdf =
    data_container.getBremsstrahlungPhotonPDFAtEnergy( 1.00000e-5 );

  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.front(), 2.13940e+6 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.back(), 2.12245e+4 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.size(), 17 );

  bremsstrahlung_photon_pdf =
    data_container.getBremsstrahlungPhotonPDFAtEnergy( 1.00000e+5 );

  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.front(),  3.65591e+5 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.back(),  5.16344e-10 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.size(), 111 );

  std::vector<double> electron_incident_energy =
    data_container.getBremsstrahlungAverageElectronIncidentEnergy();

  TEST_EQUALITY_CONST( electron_incident_energy.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( electron_incident_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( electron_incident_energy.size(), 85 );

  std::vector<double> electron_energy =
    data_container.getBremsstrahlungAverageElectronEnergy();

  TEST_EQUALITY_CONST( electron_energy.front(), 7.85574e-6 );
  TEST_EQUALITY_CONST( electron_energy.back(), 9.73318e4 );
  TEST_EQUALITY_CONST( electron_energy.size(),
                       electron_incident_energy.size() );
  }
//---------------------------------------------------------------------------//
// CHECK ATOMIC EXCITATION DATA
//---------------------------------------------------------------------------//
  {
  std::vector<double> energy_grid =
    data_container.getAtomicExcitationEnergyGrid();
  TEST_EQUALITY_CONST( energy_grid.front(), 1.361e-5 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 170 );

  std::vector<double> cross_section =
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

  Data::ENDLVolatileDataContainer data_container;

  data_generator_c->populateENDLDataContainer( data_container );

  TEST_EQUALITY_CONST( data_container.getAtomicNumber(), 6 );

//---------------------------------------------------------------------------//
// CHECK ATOMIC RELAXATION DATA
//---------------------------------------------------------------------------//

  TEST_EQUALITY_CONST( data_container.getSubshells().size(), 4 );
  TEST_ASSERT( data_container.getSubshells().count( 1 ) );
  TEST_ASSERT( data_container.getSubshells().count( 2 ) );
  TEST_ASSERT( data_container.getSubshells().count( 3 ) );
  TEST_ASSERT( data_container.getSubshells().count( 4 ) );

  TEST_EQUALITY_CONST( data_container.getSubshellOccupancy(1), 2 );
  TEST_EQUALITY_CONST( data_container.getSubshellOccupancy(2), 2 );
  TEST_EQUALITY_CONST( data_container.getSubshellOccupancy(3), .67 );
  TEST_EQUALITY_CONST( data_container.getSubshellOccupancy(4), 1.33 );

  TEST_EQUALITY_CONST( data_container.getSubshellBindingEnergy(1), 2.9101E-04 );
  TEST_EQUALITY_CONST( data_container.getSubshellBindingEnergy(2), 1.7560E-05 );
  TEST_EQUALITY_CONST( data_container.getSubshellBindingEnergy(3), 8.9900E-06 );
  TEST_EQUALITY_CONST( data_container.getSubshellBindingEnergy(4), 8.9800E-06 );

  TEST_EQUALITY_CONST( data_container.getSubshellKineticEnergy(1), 4.4702E-04 );
  TEST_EQUALITY_CONST( data_container.getSubshellKineticEnergy(2), 4.8360E-05 );
  TEST_EQUALITY_CONST( data_container.getSubshellKineticEnergy(3), 3.6960E-05 );
  TEST_EQUALITY_CONST( data_container.getSubshellKineticEnergy(4), 3.6900E-05 );

  TEST_EQUALITY_CONST( data_container.getSubshellAverageRadius(1), 1.4068E-09 );
  TEST_EQUALITY_CONST( data_container.getSubshellAverageRadius(2), 8.0784E-09 );
  TEST_EQUALITY_CONST( data_container.getSubshellAverageRadius(3), 9.1365E-09 );
  TEST_EQUALITY_CONST( data_container.getSubshellAverageRadius(4), 9.1442E-09 );

  TEST_EQUALITY_CONST( data_container.getSubshellRadiativeLevel(1),
                       1.033500000E-10 );
  TEST_EQUALITY_CONST( data_container.getSubshellNonRadiativeLevel(1),
                       6.133600000E-08 );
  TEST_EQUALITY_CONST( data_container.getLocalDepositionPerInitialVacancy(1),
                       2.853950000E-05 );
  TEST_EQUALITY_CONST( data_container.getLocalDepositionPerInitialVacancy(2),
                       1.756000000E-05 );
  TEST_EQUALITY_CONST( data_container.getLocalDepositionPerInitialVacancy(3),
                       8.990000000E-06 );
  TEST_EQUALITY_CONST( data_container.getLocalDepositionPerInitialVacancy(4),
                       8.980000000E-06 );


  TEST_EQUALITY_CONST( data_container.getAveragePhotonsPerInitialVacancy(1),
                       1.682080000E-03 );
  TEST_EQUALITY_CONST( data_container.getAveragePhotonEnergyPerInitialVacancy(1),
                       4.743930000E-07 );
  TEST_EQUALITY_CONST( data_container.getAverageElectronsPerInitialVacancy(1),
                       9.983180000E-01 );
  TEST_EQUALITY_CONST( data_container.getAverageElectronEnergyPerInitialVacancy(1),
                       2.619960000E-04 );

  TEST_EQUALITY_CONST(
    data_container.getRadiativeTransitionProbability(1).size(),
    2 );
  TEST_EQUALITY_CONST(
    data_container.getRadiativeTransitionProbability(1).find(3)->second,
    5.614880000E-04 );
  TEST_EQUALITY_CONST(
    data_container.getRadiativeTransitionProbability(1).find(4)->second,
    1.120600000E-03 );

  TEST_EQUALITY_CONST(
    data_container.getRadiativeTransitionEnergy(1).size(),
    2 );
  TEST_EQUALITY_CONST(
    data_container.getRadiativeTransitionEnergy(1).find(3)->second,
    2.820200000E-04 );
  TEST_EQUALITY_CONST(
    data_container.getRadiativeTransitionEnergy(1).find(4)->second,
    2.820300000E-04 );



  TEST_EQUALITY_CONST(
    data_container.getNonRadiativeTransitionProbability(1).size(),
    3 );
  TEST_EQUALITY_CONST(
    data_container.getNonRadiativeTransitionProbability(1).find(2)->second.size(),
    3 );
  TEST_EQUALITY_CONST(
    data_container.getNonRadiativeTransitionProbability(1).find(3)->second.size(),
    2 );
  TEST_EQUALITY_CONST(
    data_container.getNonRadiativeTransitionProbability(1).find(4)->second.size(),
    1 );
  TEST_EQUALITY_CONST(
    data_container.getNonRadiativeTransitionProbability(1).find(2)->second.find(2)->second,
    4.136090000E-01 );
  TEST_EQUALITY_CONST(
    data_container.getNonRadiativeTransitionProbability(1).find(2)->second.find(3)->second,
    1.361900000E-01 );
  TEST_EQUALITY_CONST(
    data_container.getNonRadiativeTransitionProbability(1).find(2)->second.find(4)->second,
    2.710990000E-01 );
  TEST_EQUALITY_CONST(
    data_container.getNonRadiativeTransitionProbability(1).find(3)->second.find(3)->second,
    4.207480000E-03 );
  TEST_EQUALITY_CONST(
    data_container.getNonRadiativeTransitionProbability(1).find(3)->second.find(4)->second,
    1.100120000E-01 );
  TEST_EQUALITY_CONST(
    data_container.getNonRadiativeTransitionProbability(1).find(4)->second.find(4)->second,
    6.320080000E-02 );

  TEST_EQUALITY_CONST(
    data_container.getNonRadiativeTransitionEnergy(1).size(),
    3 );
  TEST_EQUALITY_CONST(
    data_container.getNonRadiativeTransitionEnergy(1).find(2)->second.size(),
    3 );
  TEST_EQUALITY_CONST(
    data_container.getNonRadiativeTransitionEnergy(1).find(3)->second.size(),
    2 );
  TEST_EQUALITY_CONST(
    data_container.getNonRadiativeTransitionEnergy(1).find(4)->second.size(),
    1 );
  TEST_EQUALITY_CONST(
    data_container.getNonRadiativeTransitionEnergy(1).find(2)->second.find(2)->second,
    2.558900000E-04 );
  TEST_EQUALITY_CONST(
    data_container.getNonRadiativeTransitionEnergy(1).find(2)->second.find(3)->second,
    2.644600000E-04 );
  TEST_EQUALITY_CONST(
    data_container.getNonRadiativeTransitionEnergy(1).find(2)->second.find(4)->second,
    2.644700000E-04 );
  TEST_EQUALITY_CONST(
    data_container.getNonRadiativeTransitionEnergy(1).find(3)->second.find(3)->second,
    2.730300000E-04 );
  TEST_EQUALITY_CONST(
    data_container.getNonRadiativeTransitionEnergy(1).find(3)->second.find(4)->second,
    2.730400000E-04 );
  TEST_EQUALITY_CONST(
    data_container.getNonRadiativeTransitionEnergy(1).find(4)->second.find(4)->second,
    2.730500000E-04 );

//---------------------------------------------------------------------------//
// CHECK COHERENT PHOTON DATA
//---------------------------------------------------------------------------//
  {
  std::vector<double> energy_grid =
    data_container.getCoherentCrossSectionEnergyGrid();

  TEST_EQUALITY_CONST( energy_grid.front(), 1.0e-6 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 634 );

  std::vector<double> cross_section = data_container.getCoherentCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 5.063257000E-05 );
  TEST_EQUALITY_CONST( cross_section.back(), 7.687960000E-14 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

  std::vector<double> form_factor_argument =
    data_container.getCoherentFormFactorArgument();

  TEST_EQUALITY_CONST( form_factor_argument.front(), 0.0 );
  TEST_EQUALITY_CONST( form_factor_argument.back(), 1.0e17 );
  TEST_EQUALITY_CONST( form_factor_argument.size(), 138 );

  std::vector<double> form_factor = data_container.getCoherentFormFactor();

  TEST_EQUALITY_CONST( form_factor.front(), 6.0 );
  TEST_EQUALITY_CONST( form_factor.back(), 1.681000000E-29 );
  TEST_EQUALITY_CONST( form_factor.size(), form_factor_argument.size() );

  std::vector<double> factor_energy =
    data_container.getCoherentImaginaryAnomalousFactorIncidentEnergy();

  TEST_EQUALITY_CONST( factor_energy.front(), 1.0e-6 );
  TEST_EQUALITY_CONST( factor_energy.back(), 10.0 );
  TEST_EQUALITY_CONST( factor_energy.size(), 273 );

  std::vector<double> factor =
    data_container.getCoherentImaginaryAnomalousFactor();

  TEST_EQUALITY_CONST( factor.front(), 0.0 );
  TEST_EQUALITY_CONST( factor.back(), 8.131066000E-08 );
  TEST_EQUALITY_CONST( factor.size(), factor_energy.size() );

  factor_energy = data_container.getCoherentRealAnomalousFactorIncidentEnergy();

  TEST_EQUALITY_CONST( factor_energy.front(), 1.0e-6 );
  TEST_EQUALITY_CONST( factor_energy.back(), 10.0 );
  TEST_EQUALITY_CONST( factor_energy.size(), 340 );

  factor =
    data_container.getCoherentRealAnomalousFactor();

  TEST_EQUALITY_CONST( factor.front(), -5.991287000E+00 );
  TEST_EQUALITY_CONST( factor.back(), -2.077819000E-03 );
  TEST_EQUALITY_CONST( factor.size(), factor_energy.size() );

  std::vector<double> photon_energy_grid =
    data_container.getCoherentAveragePhotonIncidentEnergy();

  TEST_EQUALITY_CONST( photon_energy_grid.front(), 1.0e-6 );
  TEST_EQUALITY_CONST( photon_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( photon_energy_grid.size(), 2 );

  std::vector<double> photon_energy =
    data_container.getCoherentAveragePhotonEnergy();

  TEST_EQUALITY_CONST( photon_energy.front(), 1.0e-6 );
  TEST_EQUALITY_CONST( photon_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( photon_energy.size(), photon_energy_grid.size() );
  }
//---------------------------------------------------------------------------//
// SET INCOHERENT PHOTON DATA
//---------------------------------------------------------------------------//

  {
  std::vector<double> energy_grid =
    data_container.getIncoherentCrossSectionEnergyGrid();

  TEST_EQUALITY_CONST( energy_grid.front(), 1.0e-6 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 111 );

  std::vector<double> cross_section =
    data_container.getIncoherentCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 2.821900000E-07 );
  TEST_EQUALITY_CONST( cross_section.back(), 1.023000000E-04 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

  std::vector<double> scattering_function_argument =
    data_container.getIncoherentScatteringFunctionArgument();

  TEST_EQUALITY_CONST( scattering_function_argument.front(), 0.0 );
  TEST_EQUALITY_CONST( scattering_function_argument.back(), 1.0e17 );
  TEST_EQUALITY_CONST( scattering_function_argument.size(), 142 );

  std::vector<double> scattering_function =
    data_container.getIncoherentScatteringFunction();

  TEST_EQUALITY_CONST( scattering_function.front(), 0.0 );
  TEST_EQUALITY_CONST( scattering_function.back(), 6.0 );
  TEST_EQUALITY_CONST( scattering_function.size(),
                       scattering_function_argument.size() );

  std::vector<double> photon_energy_grid =
    data_container.getIncoherentAveragePhotonIncidentEnergy();

  TEST_EQUALITY_CONST( photon_energy_grid.front(), 1.0e-6 );
  TEST_EQUALITY_CONST( photon_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( photon_energy_grid.size(), 111 );

  std::vector<double> photon_energy =
    data_container.getIncoherentAveragePhotonEnergy();

  TEST_EQUALITY_CONST( photon_energy.front(), 9.999973000E-07 );
  TEST_EQUALITY_CONST( photon_energy.back(), 9.955317000E+03 );
  TEST_EQUALITY_CONST( photon_energy.size(), photon_energy_grid.size() );

  std::vector<double> electron_energy_grid =
    data_container.getIncoherentAverageElectronIncidentEnergy();

  TEST_EQUALITY_CONST( electron_energy_grid.front(), 1.0e-6 );
  TEST_EQUALITY_CONST( electron_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( electron_energy_grid.size(), 111 );

  std::vector<double> electron_energy =
    data_container.getIncoherentAverageElectronEnergy();

  TEST_EQUALITY_CONST( electron_energy.front(), 2.740270000E-12 );
  TEST_EQUALITY_CONST( electron_energy.back(), 9.004468000E+04 );
  TEST_EQUALITY_CONST( electron_energy.size(), electron_energy_grid.size() );
  }
//---------------------------------------------------------------------------//
// SET PHOTOELECTRIC PHOTON DATA
//---------------------------------------------------------------------------//
  {
  std::vector<double> energy_grid =
    data_container.getPhotoelectricCrossSectionEnergyGrid();

  TEST_EQUALITY_CONST( energy_grid.front(), 8.980000000E-06 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 355 );

  std::vector<double> cross_section =
    data_container.getPhotoelectricCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 8.801018000E+06 );
  TEST_EQUALITY_CONST( cross_section.back(), 9.055050000E-11 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

  std::vector<double> residual_energy_grid =
    data_container.getPhotoelectricAverageResidualIncidentEnergy();

  TEST_EQUALITY_CONST( residual_energy_grid.front(), 8.980000000E-06 );
  TEST_EQUALITY_CONST( residual_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( residual_energy_grid.size(), 25 );

  std::vector<double> residual_energy =
    data_container.getPhotoelectricAverageResidualEnergy();

  TEST_EQUALITY_CONST( residual_energy.front(), 8.980000000E-06 );
  TEST_EQUALITY_CONST( residual_energy.back(), 2.798494000E-05 );
  TEST_EQUALITY_CONST( residual_energy.size(), residual_energy_grid.size() );

  std::vector<double> photon_energy_grid =
    data_container.getPhotoelectricAveragePhotonsIncidentEnergy();

  TEST_EQUALITY_CONST( photon_energy_grid.front(), 8.980000000E-06 );
  TEST_EQUALITY_CONST( photon_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( photon_energy_grid.size(), 9 );

  std::vector<double> photon_energy =
    data_container.getPhotoelectricAveragePhotonsEnergy();

  TEST_EQUALITY_CONST( photon_energy.front(), 0.0 );
  TEST_EQUALITY_CONST( photon_energy.back(), 4.504140000E-07 );
  TEST_EQUALITY_CONST( photon_energy.size(), photon_energy_grid.size() );

  std::vector<double> electron_energy_grid =
    data_container.getPhotoelectricAverageElectronsIncidentEnergy();

  TEST_EQUALITY_CONST( electron_energy_grid.front(), 8.980000000E-06 );
  TEST_EQUALITY_CONST( electron_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( electron_energy_grid.size(), 16 );

  std::vector<double> electron_energy =
    data_container.getPhotoelectricAverageElectronsEnergy();

  TEST_EQUALITY_CONST( electron_energy.front(), 0.0 );
  TEST_EQUALITY_CONST( electron_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( electron_energy.size(), electron_energy_grid.size() );
  }
//---------------------------------------------------------------------------//
// SET PHOTOELECTRIC PHOTON DATA BY SUBSHELL
//---------------------------------------------------------------------------//
  //subshell 1
  {
  std::vector<double> energy_grid =
    data_container.getPhotoelectricCrossSectionEnergyGrid(1);

  TEST_EQUALITY_CONST( energy_grid.front(), 2.910100000E-04 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 78 );

  std::vector<double> cross_section =
    data_container.getPhotoelectricCrossSection(1);

  TEST_EQUALITY_CONST( cross_section.front(), 9.589120000E+05 );
  TEST_EQUALITY_CONST( cross_section.back(), 8.597400000E-11 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

  std::vector<double> residual_energy_grid =
    data_container.getPhotoelectricAverageResidualIncidentEnergy(1);

  TEST_EQUALITY_CONST( residual_energy_grid.front(), 2.910100000E-04 );
  TEST_EQUALITY_CONST( residual_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( residual_energy_grid.size(), 2 );

  std::vector<double> residual_energy =
    data_container.getPhotoelectricAverageResidualEnergy(1);

  TEST_EQUALITY_CONST( residual_energy.front(), 2.854000000E-05 );
  TEST_EQUALITY_CONST( residual_energy.back(), 2.854000000E-05 );
  TEST_EQUALITY_CONST( residual_energy.size(), residual_energy_grid.size() );

  std::vector<double> photon_energy_grid =
    data_container.getPhotoelectricAveragePhotonsIncidentEnergy(1);

  TEST_EQUALITY_CONST( photon_energy_grid.front(), 2.910100000E-04 );
  TEST_EQUALITY_CONST( photon_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( photon_energy_grid.size(), 2 );

  std::vector<double> photon_energy =
    data_container.getPhotoelectricAveragePhotonsEnergy(1);

  TEST_EQUALITY_CONST( photon_energy.front(), 4.743900000E-07 );
  TEST_EQUALITY_CONST( photon_energy.back(), 4.743900000E-07 );
  TEST_EQUALITY_CONST( photon_energy.size(), photon_energy_grid.size() );

  std::vector<double> electron_energy_grid =
    data_container.getPhotoelectricAverageElectronsIncidentEnergy(1);

  TEST_EQUALITY_CONST( electron_energy_grid.front(), 2.910100000E-04 );
  TEST_EQUALITY_CONST( electron_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( electron_energy_grid.size(), 2 );

  std::vector<double> electron_energy =
    data_container.getPhotoelectricAverageElectronsEnergy(1);

  TEST_EQUALITY_CONST( electron_energy.front(), 2.619956000E-04 );
  TEST_EQUALITY_CONST( electron_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( electron_energy.size(), electron_energy_grid.size() );
  }
  // subshell 2
  {
  std::vector<double> energy_grid =
    data_container.getPhotoelectricCrossSectionEnergyGrid(2);

  TEST_EQUALITY_CONST( energy_grid.front(), 1.756000000E-05 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 109 );

  std::vector<double> cross_section =
    data_container.getPhotoelectricCrossSection(2);

  TEST_EQUALITY_CONST( cross_section.front(), 8.760920000E+05 );
  TEST_EQUALITY_CONST( cross_section.back(), 4.575200000E-12 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

  std::vector<double> residual_energy_grid =
    data_container.getPhotoelectricAverageResidualIncidentEnergy(2);

  TEST_EQUALITY_CONST( residual_energy_grid.front(), 1.756000000E-05 );
  TEST_EQUALITY_CONST( residual_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( residual_energy_grid.size(), 2 );

  std::vector<double> residual_energy =
    data_container.getPhotoelectricAverageResidualEnergy(2);

  TEST_EQUALITY_CONST( residual_energy.front(), 1.756000000E-05 );
  TEST_EQUALITY_CONST( residual_energy.back(), 1.756000000E-05 );
  TEST_EQUALITY_CONST( residual_energy.size(), residual_energy_grid.size() );

  std::vector<double> electron_energy_grid =
    data_container.getPhotoelectricAverageElectronsIncidentEnergy(2);

  TEST_EQUALITY_CONST( electron_energy_grid.front(), 1.756000000E-05 );
  TEST_EQUALITY_CONST( electron_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( electron_energy_grid.size(), 2 );

  std::vector<double> electron_energy =
    data_container.getPhotoelectricAverageElectronsEnergy(2);

  TEST_EQUALITY_CONST( electron_energy.front(), 0.0 );
  TEST_EQUALITY_CONST( electron_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( electron_energy.size(), electron_energy_grid.size() );
  }
  //subshell 3
  {
  std::vector<double> energy_grid =
    data_container.getPhotoelectricCrossSectionEnergyGrid(3);

  TEST_EQUALITY_CONST( energy_grid.front(), 8.990000000E-06 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 115 );

  std::vector<double> cross_section =
    data_container.getPhotoelectricCrossSection(3);

  TEST_EQUALITY_CONST( cross_section.front(), 4.393500000E+06 );
  TEST_EQUALITY_CONST( cross_section.back(), 3.875700000E-16 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

  std::vector<double> residual_energy_grid =
    data_container.getPhotoelectricAverageResidualIncidentEnergy(3);

  TEST_EQUALITY_CONST( residual_energy_grid.front(), 8.990000000E-06 );
  TEST_EQUALITY_CONST( residual_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( residual_energy_grid.size(), 2 );

  std::vector<double> residual_energy =
    data_container.getPhotoelectricAverageResidualEnergy(3);

  TEST_EQUALITY_CONST( residual_energy.front(), 8.990000000E-06 );
  TEST_EQUALITY_CONST( residual_energy.back(), 8.990000000E-06 );
  TEST_EQUALITY_CONST( residual_energy.size(), residual_energy_grid.size() );


  std::vector<double> electron_energy_grid =
    data_container.getPhotoelectricAverageElectronsIncidentEnergy(3);

  TEST_EQUALITY_CONST( electron_energy_grid.front(), 8.990000000E-06 );
  TEST_EQUALITY_CONST( electron_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( electron_energy_grid.size(), 2 );

  std::vector<double> electron_energy =
    data_container.getPhotoelectricAverageElectronsEnergy(3);

  TEST_EQUALITY_CONST( electron_energy.front(), 0.0 );
  TEST_EQUALITY_CONST( electron_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( electron_energy.size(), electron_energy_grid.size() );
  }
  //subshell 4
  {
  std::vector<double> energy_grid =
    data_container.getPhotoelectricCrossSectionEnergyGrid(4);

  TEST_EQUALITY_CONST( energy_grid.front(), 8.980000000E-06 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 113 );

  std::vector<double> cross_section =
    data_container.getPhotoelectricCrossSection(4);

  TEST_EQUALITY_CONST( cross_section.front(), 8.801018000E+06 );
  TEST_EQUALITY_CONST( cross_section.back(), 8.933100000E-16 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

  std::vector<double> residual_energy_grid =
    data_container.getPhotoelectricAverageResidualIncidentEnergy(4);

  TEST_EQUALITY_CONST( residual_energy_grid.front(), 8.980000000E-06 );
  TEST_EQUALITY_CONST( residual_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( residual_energy_grid.size(), 2 );

  std::vector<double> residual_energy =
    data_container.getPhotoelectricAverageResidualEnergy(4);

  TEST_EQUALITY_CONST( residual_energy.front(), 8.980000000E-06 );
  TEST_EQUALITY_CONST( residual_energy.back(), 8.980000000E-06 );
  TEST_EQUALITY_CONST( residual_energy.size(), residual_energy_grid.size() );

  std::vector<double> electron_energy_grid =
    data_container.getPhotoelectricAverageElectronsIncidentEnergy(4);

  TEST_EQUALITY_CONST( electron_energy_grid.front(), 8.980000000E-06 );
  TEST_EQUALITY_CONST( electron_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( electron_energy_grid.size(), 2 );

  std::vector<double> electron_energy =
    data_container.getPhotoelectricAverageElectronsEnergy(4);

  TEST_EQUALITY_CONST( electron_energy.front(), 0.0 );
  TEST_EQUALITY_CONST( electron_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( electron_energy.size(), electron_energy_grid.size() );
  }
//---------------------------------------------------------------------------//
// SET PAIR PRODUCTION PHOTON DATA
//---------------------------------------------------------------------------//
  {
  std::vector<double> energy_grid =
    data_container.getPairProductionCrossSectionEnergyGrid();

  TEST_EQUALITY_CONST( energy_grid.front(), 1.022000000E+00 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 94 );

  std::vector<double> cross_section =
    data_container.getPairProductionCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 0.0 );
  TEST_EQUALITY_CONST( cross_section.back(), 3.002000000E-01 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

  std::vector<double> positron_energy_grid =
    data_container.getPairProductionAveragePositronIncidentEnergy();

  TEST_EQUALITY_CONST( positron_energy_grid.front(),  1.022000000E+00 );
  TEST_EQUALITY_CONST( positron_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( positron_energy_grid.size(), 2 );

  std::vector<double> positron_energy =
    data_container.getPairProductionAveragePositronEnergy();

  TEST_EQUALITY_CONST( positron_energy.front(), 0.0 );
  TEST_EQUALITY_CONST( positron_energy.back(), 4.999949000E+04 );
  TEST_EQUALITY_CONST( positron_energy.size(), positron_energy_grid.size() );

  std::vector<double> electron_energy_grid =
    data_container.getPairProductionAverageElectronIncidentEnergy();

  TEST_EQUALITY_CONST( electron_energy_grid.front(),  1.022000000E+00 );
  TEST_EQUALITY_CONST( electron_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( electron_energy_grid.size(), 2 );

  std::vector<double> electron_energy =
    data_container.getPairProductionAverageElectronEnergy();

  TEST_EQUALITY_CONST( electron_energy.front(), 0.0 );
  TEST_EQUALITY_CONST( electron_energy.back(), 4.999949000E+04 );
  TEST_EQUALITY_CONST( electron_energy.size(), electron_energy_grid.size() );
  }
//---------------------------------------------------------------------------//
// SET TRIPLET PRODUCTION PHOTON DATA
//---------------------------------------------------------------------------//
  {
  std::vector<double> energy_grid =
    data_container.getTripletProductionCrossSectionEnergyGrid();

  TEST_EQUALITY_CONST( energy_grid.front(), 2.044000000E+00 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 83 );

  std::vector<double> cross_section =
    data_container.getTripletProductionCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 0.0 );
  TEST_EQUALITY_CONST( cross_section.back(), 5.873000000E-02 );
  TEST_EQUALITY_CONST( cross_section.size(), energy_grid.size() );

  std::vector<double> positron_energy_grid =
    data_container.getTripletProductionAveragePositronIncidentEnergy();

  TEST_EQUALITY_CONST( positron_energy_grid.front(), 2.044000000E+00 );
  TEST_EQUALITY_CONST( positron_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( positron_energy_grid.size(), 2 );

  std::vector<double> positron_energy =
    data_container.getTripletProductionAveragePositronEnergy();

  TEST_EQUALITY_CONST( positron_energy.front(), 5.110000000E-01 );
  TEST_EQUALITY_CONST( positron_energy.back(), 4.999949000E+04 );
  TEST_EQUALITY_CONST( positron_energy.size(), positron_energy_grid.size() );

  std::vector<double> electron_energy_grid =
    data_container.getTripletProductionAverageElectronIncidentEnergy();

  TEST_EQUALITY_CONST( electron_energy_grid.front(), 2.044000000E+00 );
  TEST_EQUALITY_CONST( electron_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( electron_energy_grid.size(), 2 );

  std::vector<double> electron_energy =
    data_container.getTripletProductionAverageElectronEnergy();

  TEST_EQUALITY_CONST( electron_energy.front(), 5.110000000E-01 );
  TEST_EQUALITY_CONST( electron_energy.back(), 4.999949000E+04 );
  TEST_EQUALITY_CONST( electron_energy.size(), electron_energy_grid.size() );
  }
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

  std::vector<double> residual_incident_energy =
    data_container.getCutoffElasticResidualIncidentEnergy();

  TEST_EQUALITY_CONST( residual_incident_energy.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( residual_incident_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( residual_incident_energy.size(), 2 );

  std::vector<double> residual_energy =
    data_container.getCutoffElasticResidualEnergy();

  TEST_EQUALITY_CONST( residual_energy.front(), 0.0 );
  TEST_EQUALITY_CONST( residual_energy.back(), 0.0 );
  TEST_EQUALITY_CONST( residual_energy.size(),
                       residual_incident_energy.size() );

  std::vector<double> scattered_incident_energy =
    data_container.getCutoffElasticScatteredElectronIncidentEnergy();

  TEST_EQUALITY_CONST( scattered_incident_energy.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( scattered_incident_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( scattered_incident_energy.size(), 2 );

  std::vector<double> scattered_energy =
    data_container.getCutoffElasticScatteredElectronEnergy();

  TEST_EQUALITY_CONST( scattered_energy.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( scattered_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( scattered_energy.size(),
                       scattered_incident_energy.size() );

  std::vector<double> angular_grid =
    data_container.getCutoffElasticAngularEnergyGrid();

  TEST_EQUALITY_CONST( angular_grid.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( angular_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( angular_grid.size(), 16 );

  std::vector<double> elastic_angles =
    data_container.getCutoffElasticAnglesAtEnergy(1.0e-5);

  TEST_EQUALITY_CONST( elastic_angles.front(), 1.0e-6 );
  TEST_EQUALITY_CONST( elastic_angles.back(), 2.0 );
  TEST_EQUALITY_CONST( elastic_angles.size(), 2 );

  elastic_angles =
    data_container.getCutoffElasticAnglesAtEnergy(1.0e+5);

  TEST_EQUALITY_CONST( elastic_angles.front(), 1.0e-6 );
  TEST_EQUALITY_CONST( elastic_angles.back(), 2.0 );
  TEST_EQUALITY_CONST( elastic_angles.size(), 96 );

  std::vector<double> elastic_pdf =
    data_container.getCutoffElasticPDFAtEnergy(1.0e-5);

  TEST_EQUALITY_CONST( elastic_pdf.front(), 0.5 );
  TEST_EQUALITY_CONST( elastic_pdf.back(), 0.5 );
  TEST_EQUALITY_CONST( elastic_pdf.size(), 2 );

  elastic_pdf =
    data_container.getCutoffElasticPDFAtEnergy(1.0e+5);

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

  scattered_incident_energy =
    data_container.getElectroionizationAverageScatteredElectronIncidentEnergy( 1u );

  TEST_EQUALITY_CONST( scattered_incident_energy.front(), 2.9101e-4 );
  TEST_EQUALITY_CONST( scattered_incident_energy.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( scattered_incident_energy.size(), 6 );

  scattered_energy =
    data_container.getElectroionizationAverageScatteredElectronEnergy( 1u );

  TEST_EQUALITY_CONST( scattered_energy.front(), 0.0 );
  TEST_EQUALITY_CONST( scattered_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( scattered_energy.size(),
                       scattered_incident_energy.size() );

  std::vector<double> recoil_incident_energy =
    data_container.getElectroionizationAverageRecoilElectronIncidentEnergy( 1u );

  TEST_EQUALITY_CONST( recoil_incident_energy.front(), 2.9101e-4 );
  TEST_EQUALITY_CONST( recoil_incident_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( recoil_incident_energy.size(), 22 );

  std::vector<double> recoil_energy =
    data_container.getElectroionizationAverageRecoilElectronEnergy( 1u );

  TEST_EQUALITY_CONST( recoil_energy.front(), 0.0 );
  TEST_EQUALITY_CONST( recoil_energy.back(), 8.76406e-4 );
  TEST_EQUALITY_CONST( recoil_energy.size(), recoil_incident_energy.size() );

  std::vector<double> recoil_energy_grid =
    data_container.getElectroionizationRecoilEnergyGrid( 1u );

  TEST_EQUALITY_CONST( recoil_energy_grid.front(), 2.910100E-04 );
  TEST_EQUALITY_CONST( recoil_energy_grid.back(), 1.00000e+5 );
  TEST_EQUALITY_CONST( recoil_energy_grid.size(), 7 );

  std::vector<double> electroionization_recoil_energy =
    data_container.getElectroionizationRecoilEnergyAtEnergy( 1u, 2.910100E-04 );

  TEST_EQUALITY_CONST( electroionization_recoil_energy.front(), 1.00000e-8 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.back(), 1.00000e-7 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.size(), 2 );

  electroionization_recoil_energy =
    data_container.getElectroionizationRecoilEnergyAtEnergy( 1u, 1.00000e+5 );

  TEST_EQUALITY_CONST( electroionization_recoil_energy.front(), 1.00000e-7 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.back(), 5.00000e+4 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.size(), 128 );

  std::vector<double> electroionization_recoil_pdf =
    data_container.getElectroionizationRecoilPDFAtEnergy( 1u, 2.910100E-04 );

  TEST_EQUALITY_CONST( electroionization_recoil_pdf.front(), 1.111110E+07 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.back(), 1.111110E+07 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.size(), 2 );

  electroionization_recoil_pdf =
    data_container.getElectroionizationRecoilPDFAtEnergy( 1u, 1.00000e+5 );

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


  scattered_incident_energy =
    data_container.getElectroionizationAverageScatteredElectronIncidentEnergy( 4u );

  TEST_EQUALITY_CONST( scattered_incident_energy.front(), 8.980e-6 );
  TEST_EQUALITY_CONST( scattered_incident_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( scattered_incident_energy.size(), 6 );

  scattered_energy =
    data_container.getElectroionizationAverageScatteredElectronEnergy( 4u );

  TEST_EQUALITY_CONST( scattered_energy.front(), 0.0 );
  TEST_EQUALITY_CONST( scattered_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( scattered_energy.size(),
                       scattered_incident_energy.size() );

  recoil_incident_energy =
    data_container.getElectroionizationAverageRecoilElectronIncidentEnergy( 4u );

  TEST_EQUALITY_CONST( recoil_incident_energy.front(), 8.980e-6 );
  TEST_EQUALITY_CONST( recoil_incident_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( recoil_incident_energy.size(), 25 );

  recoil_energy =
    data_container.getElectroionizationAverageRecoilElectronEnergy( 4u );

  TEST_EQUALITY_CONST( recoil_energy.front(), 0.0 );
  TEST_EQUALITY_CONST( recoil_energy.back(), 4.687980e-5 );
  TEST_EQUALITY_CONST( recoil_energy.size(), recoil_incident_energy.size() );

  recoil_energy_grid =
    data_container.getElectroionizationRecoilEnergyGrid( 4u );

  TEST_EQUALITY_CONST( recoil_energy_grid.front(), 8.980000E-06 );
  TEST_EQUALITY_CONST( recoil_energy_grid.back(), 1.00000e+5 );
  TEST_EQUALITY_CONST( recoil_energy_grid.size(), 8 );

  electroionization_recoil_energy =
    data_container.getElectroionizationRecoilEnergyAtEnergy( 4u, 8.980000E-06 );

  TEST_EQUALITY_CONST( electroionization_recoil_energy.front(), 2.550000E-09 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.back(), 2.550000E-08 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.size(), 2 );

  electroionization_recoil_energy =
    data_container.getElectroionizationRecoilEnergyAtEnergy( 4u, 1.00000e+5 );

  TEST_EQUALITY_CONST( electroionization_recoil_energy.front(), 1.00000e-7 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.back(), 5.00000e+4 );
  TEST_EQUALITY_CONST( electroionization_recoil_energy.size(), 143 );

  electroionization_recoil_pdf =
    data_container.getElectroionizationRecoilPDFAtEnergy( 4u, 8.980000E-06 );

  TEST_EQUALITY_CONST( electroionization_recoil_pdf.front(), 4.357300E+07 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.back(), 4.357300E+07 );
  TEST_EQUALITY_CONST( electroionization_recoil_pdf.size(), 2 );

  electroionization_recoil_pdf =
    data_container.getElectroionizationRecoilPDFAtEnergy( 4u, 1.00000e+5 );

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

  std::vector<double> photon_energy_grid =
    data_container.getBremsstrahlungAveragePhotonIncidentEnergy();

  TEST_EQUALITY_CONST( photon_energy_grid.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( photon_energy_grid.back(), 1.0e5 );
  TEST_EQUALITY_CONST( photon_energy_grid.size(), 75 );

  std::vector<double> photon_energy =
    data_container.getBremsstrahlungAveragePhotonEnergy();

  TEST_EQUALITY_CONST( photon_energy.front(), 2.15038e-6 );
  TEST_EQUALITY_CONST( photon_energy.back(), 2.71203e3 );
  TEST_EQUALITY_CONST( photon_energy.size(), photon_energy_grid.size() );

  std::vector<double> bremsstrahlung_photon_energy_grid =
    data_container.getBremsstrahlungPhotonEnergyGrid();

  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy_grid.front(), 1.00000e-5 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy_grid.back(), 1.00000e+5 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy_grid.size(), 9 );

  std::vector<double> bremsstrahlung_photon_energy =
    data_container.getBremsstrahlungPhotonEnergyAtEnergy( 1.00000e-5 );

  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.back(), 1.00000e-5 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.size(), 17 );

  bremsstrahlung_photon_energy =
    data_container.getBremsstrahlungPhotonEnergyAtEnergy( 1.00000e+5 );

  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.back(), 1.00000e+5 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_energy.size(), 105 );

  std::vector<double> bremsstrahlung_photon_pdf =
    data_container.getBremsstrahlungPhotonPDFAtEnergy( 1.00000e-5 );

  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.front(), 2.134970E+06 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.back(), 2.136140E+04 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.size(), 17 );

  bremsstrahlung_photon_pdf =
    data_container.getBremsstrahlungPhotonPDFAtEnergy( 1.00000e+5 );

  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.front(), 3.649330E+05 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.back(),  5.638520E-09 );
  TEST_EQUALITY_CONST( bremsstrahlung_photon_pdf.size(), 105 );

  std::vector<double> electron_incident_energy =
    data_container.getBremsstrahlungAverageElectronIncidentEnergy();

  TEST_EQUALITY_CONST( electron_incident_energy.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( electron_incident_energy.back(), 1.0e5 );
  TEST_EQUALITY_CONST( electron_incident_energy.size(), 76 );

  std::vector<double> electron_energy =
    data_container.getBremsstrahlungAverageElectronEnergy();

  TEST_EQUALITY_CONST( electron_energy.front(), 7.84962e-6 );
  TEST_EQUALITY_CONST( electron_energy.back(), 9.7288e4 );
  TEST_EQUALITY_CONST( electron_energy.size(),
                       electron_incident_energy.size() );

//---------------------------------------------------------------------------//
// CHECK ATOMIC EXCITATION DATA
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
