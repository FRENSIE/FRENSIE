//---------------------------------------------------------------------------//
//!
//! \file   tstStandardENDLDataGenerator.cpp
//! \author Luke Kersting
//! \brief  Standard endl data generator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "DataGen_StandardENDLDataGenerator.hpp"
#include "Data_ENDLVolatileDataContainer.hpp"
#include "Data_ENDLFileHandler.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<DataGen::StandardENDLDataGenerator>
  data_generator_h, data_generator_c;

std::string test_h_eadl_file_name, test_h_epdl_file_name, test_h_eedl_file_name,
            test_c_eadl_file_name, test_c_epdl_file_name, test_c_eedl_file_name;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a data container can be populated
FRENSIE_UNIT_TEST( StandardENDLDataGenerator,
                   populateENDLDataContainer_h )
{
  data_generator_h.reset( new DataGen::StandardENDLDataGenerator(
                                                     test_h_eadl_file_name,
                                                     test_h_epdl_file_name,
                                                     test_h_eedl_file_name ) );

  data_generator_h->populateENDLDataContainer();

  const Data::ENDLDataContainer& data_container =
    data_generator_h->getDataContainer();

  FRENSIE_CHECK_EQUAL( data_container.getAtomicNumber(), 1 );

  // CHECK ATOMIC RELAXATION DATA
  FRENSIE_CHECK_EQUAL( data_container.getSubshells().size(), 1 );
  FRENSIE_CHECK( data_container.getSubshells().count( 1 ) );
  FRENSIE_CHECK_EQUAL( data_container.getSubshellOccupancy(1), 1 );
  FRENSIE_CHECK_EQUAL( data_container.getSubshellBindingEnergy(1), 1.361e-5 );
  FRENSIE_CHECK_EQUAL( data_container.getSubshellKineticEnergy(1), 1.361e-5 );
  FRENSIE_CHECK_EQUAL( data_container.getSubshellAverageRadius(1), 7.9356e-9 );
  FRENSIE_CHECK_EQUAL( data_container.getLocalDepositionPerInitialVacancy(1),
                       1.361e-5 );

  // CHECK COHERENT PHOTON DATA
  {
  std::vector<double> energy_grid =
    data_container.getCoherentCrossSectionEnergyGrid();

  FRENSIE_CHECK_EQUAL( energy_grid.front(), 1.0e-6 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 362 );

  std::vector<double> cross_section = data_container.getCoherentCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 9.887553000E-06 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 4.626160000E-16 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), energy_grid.size() );

  std::vector<double> form_factor_argument =
    data_container.getCoherentFormFactorArgument();

  FRENSIE_CHECK_EQUAL( form_factor_argument.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( form_factor_argument.back(), 1.0e17 );
  FRENSIE_CHECK_EQUAL( form_factor_argument.size(), 90 );

  std::vector<double> form_factor = data_container.getCoherentFormFactor();

  FRENSIE_CHECK_EQUAL( form_factor.front(), 1.0 );
  FRENSIE_CHECK_EQUAL( form_factor.back(), 8.182900000E-39 );
  FRENSIE_CHECK_EQUAL( form_factor.size(), form_factor_argument.size() );

  std::vector<double> factor_energy =
    data_container.getCoherentImaginaryAnomalousFactorIncidentEnergy();

  FRENSIE_CHECK_EQUAL( factor_energy.front(), 1.0e-6 );
  FRENSIE_CHECK_EQUAL( factor_energy.back(), 10.0 );
  FRENSIE_CHECK_EQUAL( factor_energy.size(), 194 );

  std::vector<double> factor =
    data_container.getCoherentImaginaryAnomalousFactor();

  FRENSIE_CHECK_EQUAL( factor.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( factor.back(), 6.265660000E-12 );
  FRENSIE_CHECK_EQUAL( factor.size(), factor_energy.size() );

  factor_energy = data_container.getCoherentRealAnomalousFactorIncidentEnergy();

  FRENSIE_CHECK_EQUAL( factor_energy.front(), 1.0e-6 );
  FRENSIE_CHECK_EQUAL( factor_energy.back(), 10.0 );
  FRENSIE_CHECK_EQUAL( factor_energy.size(), 308 );

  factor =
    data_container.getCoherentRealAnomalousFactor();

  FRENSIE_CHECK_EQUAL( factor.front(), -9.961483000E-01 );
  FRENSIE_CHECK_EQUAL( factor.back(), -2.665509000E-05 );
  FRENSIE_CHECK_EQUAL( factor.size(), factor_energy.size() );

  std::vector<double> photon_energy_grid =
    data_container.getCoherentAveragePhotonIncidentEnergy();

  FRENSIE_CHECK_EQUAL( photon_energy_grid.front(), 1.0e-6 );
  FRENSIE_CHECK_EQUAL( photon_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( photon_energy_grid.size(), 2 );

  std::vector<double> photon_energy =
    data_container.getCoherentAveragePhotonEnergy();

  FRENSIE_CHECK_EQUAL( photon_energy.front(), 1.0e-6 );
  FRENSIE_CHECK_EQUAL( photon_energy.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( photon_energy.size(), photon_energy_grid.size() );
  }

  // SET INCOHERENT PHOTON DATA

  {
  std::vector<double> energy_grid =
    data_container.getIncoherentCrossSectionEnergyGrid();

  FRENSIE_CHECK_EQUAL( energy_grid.front(), 1.0e-6 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 111 );

  std::vector<double> cross_section =
    data_container.getIncoherentCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 9.562300000E-08 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 1.704200000E-05 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), energy_grid.size() );

  std::vector<double> scattering_function_argument =
    data_container.getIncoherentScatteringFunctionArgument();

  FRENSIE_CHECK_EQUAL( scattering_function_argument.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( scattering_function_argument.back(), 1.0e17 );
  FRENSIE_CHECK_EQUAL( scattering_function_argument.size(), 94 );

  std::vector<double> scattering_function =
    data_container.getIncoherentScatteringFunction();

  FRENSIE_CHECK_EQUAL( scattering_function.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( scattering_function.back(), 1.0 );
  FRENSIE_CHECK_EQUAL( scattering_function.size(),
                       scattering_function_argument.size() );

  std::vector<double> photon_energy_grid =
    data_container.getIncoherentAveragePhotonIncidentEnergy();

  FRENSIE_CHECK_EQUAL( photon_energy_grid.front(), 1.0e-6 );
  FRENSIE_CHECK_EQUAL( photon_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( photon_energy_grid.size(), 111 );

  std::vector<double> photon_energy =
    data_container.getIncoherentAveragePhotonEnergy();

  FRENSIE_CHECK_EQUAL( photon_energy.front(), 9.999973000E-07 );
  FRENSIE_CHECK_EQUAL( photon_energy.back(), 9.955317000E+03 );
  FRENSIE_CHECK_EQUAL( photon_energy.size(), photon_energy_grid.size() );

  std::vector<double> electron_energy_grid =
    data_container.getIncoherentAverageElectronIncidentEnergy();

  FRENSIE_CHECK_EQUAL( electron_energy_grid.front(), 1.0e-6 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.size(), 111 );

  std::vector<double> electron_energy =
    data_container.getIncoherentAverageElectronEnergy();

  FRENSIE_CHECK_EQUAL( electron_energy.front(), 2.740270000E-12 );
  FRENSIE_CHECK_EQUAL( electron_energy.back(), 9.004468000E+04 );
  FRENSIE_CHECK_EQUAL( electron_energy.size(), electron_energy_grid.size() );
  }

  // SET PHOTOELECTRIC PHOTON DATA
  {
  std::vector<double> energy_grid =
    data_container.getPhotoelectricCrossSectionEnergyGrid();

  FRENSIE_CHECK_EQUAL( energy_grid.front(), 1.361000000E-05 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 73 );

  std::vector<double> cross_section =
    data_container.getPhotoelectricCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 6.305834000E+06 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 7.736000000E-15 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), energy_grid.size() );

  std::vector<double> residual_energy_grid =
    data_container.getPhotoelectricAverageResidualIncidentEnergy();

  FRENSIE_CHECK_EQUAL( residual_energy_grid.front(), 1.361000000E-05 );
  FRENSIE_CHECK_EQUAL( residual_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( residual_energy_grid.size(), 2 );

  std::vector<double> residual_energy =
    data_container.getPhotoelectricAverageResidualEnergy();

  FRENSIE_CHECK_EQUAL( residual_energy.front(), 1.361000000E-05 );
  FRENSIE_CHECK_EQUAL( residual_energy.back(), 1.361000000E-05 );
  FRENSIE_CHECK_EQUAL( residual_energy.size(), residual_energy_grid.size() );

  std::vector<double> photon_energy_grid =
    data_container.getPhotoelectricAveragePhotonsIncidentEnergy();

  FRENSIE_CHECK_EQUAL( photon_energy_grid.size(), 0 );

  std::vector<double> photon_energy =
    data_container.getPhotoelectricAveragePhotonsEnergy();

  FRENSIE_CHECK_EQUAL( photon_energy.size(), photon_energy_grid.size() );

  std::vector<double> electron_energy_grid =
    data_container.getPhotoelectricAverageElectronsIncidentEnergy();

  FRENSIE_CHECK_EQUAL( electron_energy_grid.front(), 1.361000000E-05 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.size(), 2 );

  std::vector<double> electron_energy =
    data_container.getPhotoelectricAverageElectronsEnergy();

  FRENSIE_CHECK_EQUAL( electron_energy.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( electron_energy.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( electron_energy.size(), electron_energy_grid.size() );
  }

  // SET PHOTOELECTRIC PHOTON DATA BY SUBSHELL
  {
  std::vector<double> energy_grid =
    data_container.getPhotoelectricCrossSectionEnergyGrid(1);

  FRENSIE_CHECK_EQUAL( energy_grid.front(), 1.361000000E-05 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 73 );

  std::vector<double> cross_section =
    data_container.getPhotoelectricCrossSection(1);

  FRENSIE_CHECK_EQUAL( cross_section.front(), 6.305834000E+06 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 7.736000000E-15 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), energy_grid.size() );

  std::vector<double> residual_energy_grid =
    data_container.getPhotoelectricAverageResidualIncidentEnergy(1);

  FRENSIE_CHECK_EQUAL( residual_energy_grid.front(), 1.361000000E-05 );
  FRENSIE_CHECK_EQUAL( residual_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( residual_energy_grid.size(), 2 );

  std::vector<double> residual_energy =
    data_container.getPhotoelectricAverageResidualEnergy(1);

  FRENSIE_CHECK_EQUAL( residual_energy.front(), 1.361000000E-05 );
  FRENSIE_CHECK_EQUAL( residual_energy.back(), 1.361000000E-05 );
  FRENSIE_CHECK_EQUAL( residual_energy.size(), residual_energy_grid.size() );

  std::vector<double> electron_energy_grid =
    data_container.getPhotoelectricAverageElectronsIncidentEnergy(1);

  FRENSIE_CHECK_EQUAL( electron_energy_grid.front(), 1.361000000E-05 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.size(), 2 );

  std::vector<double> electron_energy =
    data_container.getPhotoelectricAverageElectronsEnergy(1);

  FRENSIE_CHECK_EQUAL( electron_energy.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( electron_energy.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( electron_energy.size(), electron_energy_grid.size() );
  }

  // SET PAIR PRODUCTION PHOTON DATA
  {
  std::vector<double> energy_grid =
    data_container.getPairProductionCrossSectionEnergyGrid();

  FRENSIE_CHECK_EQUAL( energy_grid.front(), 1.022000000E+00 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 83 );

  std::vector<double> cross_section =
    data_container.getPairProductionCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 9.601000000E-03 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), energy_grid.size() );

  std::vector<double> positron_energy_grid =
    data_container.getPairProductionAveragePositronIncidentEnergy();

  FRENSIE_CHECK_EQUAL( positron_energy_grid.front(),  1.022000000E+00 );
  FRENSIE_CHECK_EQUAL( positron_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( positron_energy_grid.size(), 2 );

  std::vector<double> positron_energy =
    data_container.getPairProductionAveragePositronEnergy();

  FRENSIE_CHECK_EQUAL( positron_energy.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( positron_energy.back(), 4.999949000E+04 );
  FRENSIE_CHECK_EQUAL( positron_energy.size(), positron_energy_grid.size() );

  std::vector<double> electron_energy_grid =
    data_container.getPairProductionAverageElectronIncidentEnergy();

  FRENSIE_CHECK_EQUAL( electron_energy_grid.front(),  1.022000000E+00 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.size(), 2 );

  std::vector<double> electron_energy =
    data_container.getPairProductionAverageElectronEnergy();

  FRENSIE_CHECK_EQUAL( electron_energy.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( electron_energy.back(), 4.999949000E+04 );
  FRENSIE_CHECK_EQUAL( electron_energy.size(), electron_energy_grid.size() );
  }

  // SET TRIPLET PRODUCTION PHOTON DATA
  {
  std::vector<double> energy_grid =
    data_container.getTripletProductionCrossSectionEnergyGrid();

  FRENSIE_CHECK_EQUAL( energy_grid.front(), 2.044000000E+00 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 77 );

  std::vector<double> cross_section =
    data_container.getTripletProductionCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 1.110000000E-02 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), energy_grid.size() );

  std::vector<double> positron_energy_grid =
    data_container.getTripletProductionAveragePositronIncidentEnergy();

  FRENSIE_CHECK_EQUAL( positron_energy_grid.front(), 2.044000000E+00 );
  FRENSIE_CHECK_EQUAL( positron_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( positron_energy_grid.size(), 2 );

  std::vector<double> positron_energy =
    data_container.getTripletProductionAveragePositronEnergy();

  FRENSIE_CHECK_EQUAL( positron_energy.front(), 5.110000000E-01 );
  FRENSIE_CHECK_EQUAL( positron_energy.back(), 4.999949000E+04 );
  FRENSIE_CHECK_EQUAL( positron_energy.size(), positron_energy_grid.size() );

  std::vector<double> electron_energy_grid =
    data_container.getTripletProductionAverageElectronIncidentEnergy();

  FRENSIE_CHECK_EQUAL( electron_energy_grid.front(), 2.044000000E+00 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.size(), 2 );

  std::vector<double> electron_energy =
    data_container.getTripletProductionAverageElectronEnergy();

  FRENSIE_CHECK_EQUAL( electron_energy.front(), 5.110000000E-01 );
  FRENSIE_CHECK_EQUAL( electron_energy.back(), 4.999949000E+04 );
  FRENSIE_CHECK_EQUAL( electron_energy.size(), electron_energy_grid.size() );
  }

  // CHECK ELASTIC DATA
  {
  std::vector<double> energy_grid = data_container.getElasticEnergyGrid();
  FRENSIE_CHECK_EQUAL( energy_grid.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 101 );

  std::vector<double> cross_section =
    data_container.getElasticTransportCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 2.74896e+8 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 4.33534E-10 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), energy_grid.size() );

  cross_section =
    data_container.getCutoffElasticCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 2.74896e+8 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 1.31176e-5 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), energy_grid.size() );

  std::vector<double> residual_energy_grid =
    data_container.getCutoffElasticResidualIncidentEnergy();

  FRENSIE_CHECK_EQUAL( residual_energy_grid.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( residual_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( residual_energy_grid.size(), 2 );

  std::vector<double> residual_energy =
    data_container.getCutoffElasticResidualEnergy();

  FRENSIE_CHECK_EQUAL( residual_energy.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( residual_energy.back(), 0.0 );
  FRENSIE_CHECK_EQUAL( residual_energy.size(),
                       residual_energy_grid.size() );

  std::vector<double> scattered_incident_energy =
    data_container.getCutoffElasticScatteredElectronIncidentEnergy();

  FRENSIE_CHECK_EQUAL( scattered_incident_energy.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( scattered_incident_energy.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( scattered_incident_energy.size(), 2 );

  std::vector<double> scattered_energy =
    data_container.getCutoffElasticScatteredElectronEnergy();

  FRENSIE_CHECK_EQUAL( scattered_energy.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( scattered_energy.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( scattered_energy.size(),
                       scattered_incident_energy.size() );

  std::vector<double> angular_grid =
    data_container.getCutoffElasticAngularEnergyGrid();

  FRENSIE_CHECK_EQUAL( angular_grid.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( angular_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( angular_grid.size(), 16 );

  std::vector<double> elastic_angles =
    data_container.getCutoffElasticAnglesAtEnergy(1.0e-5);

  FRENSIE_CHECK_EQUAL( elastic_angles.front(), 1.0e-6 );
  FRENSIE_CHECK_EQUAL( elastic_angles.back(), 2.0 );
  FRENSIE_CHECK_EQUAL( elastic_angles.size(), 2 );

  elastic_angles =
    data_container.getCutoffElasticAnglesAtEnergy(1.0e+5);

  FRENSIE_CHECK_EQUAL( elastic_angles.front(), 1.0e-6 );
  FRENSIE_CHECK_EQUAL( elastic_angles.back(), 2.0 );
  FRENSIE_CHECK_EQUAL( elastic_angles.size(), 96 );

  std::vector<double> elastic_pdf =
    data_container.getCutoffElasticPDFAtEnergy(1.0e-5);

  FRENSIE_CHECK_EQUAL( elastic_pdf.front(), 0.5 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.back(), 0.5 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.size(), 2 );

  elastic_pdf =
    data_container.getCutoffElasticPDFAtEnergy(1.0e+5);

  FRENSIE_CHECK_EQUAL( elastic_pdf.front(), 9.86945e5 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.back(), 6.25670e-13 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.size(), 96 );

  cross_section =
    data_container.getTotalElasticCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 2.74896e8 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 1.29871e4 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), energy_grid.size() );
  }

  // CHECK ELECTROIONIZATION DATA
  {
  std::vector<double> energy_grid =
    data_container.getElectroionizationCrossSectionEnergyGrid( 1u );
  FRENSIE_CHECK_EQUAL( energy_grid.front(), 1.361e-5 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 35 );

  std::vector<double> cross_section =
    data_container.getElectroionizationCrossSection( 1u );

  FRENSIE_CHECK_EQUAL( cross_section.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 8.28924e+4 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), energy_grid.size() );

  std::vector<double> scattered_incident_energy =
    data_container.getElectroionizationAverageScatteredElectronIncidentEnergy( 1u );

  FRENSIE_CHECK_EQUAL( scattered_incident_energy.front(), 1.361e-5 );
  FRENSIE_CHECK_EQUAL( scattered_incident_energy.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( scattered_incident_energy.size(), 6 );

  std::vector<double> scattered_energy =
    data_container.getElectroionizationAverageScatteredElectronEnergy( 1u );

  FRENSIE_CHECK_EQUAL( scattered_energy.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( scattered_energy.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( scattered_energy.size(),
                       scattered_incident_energy.size() );

  std::vector<double> recoil_incident_energy =
    data_container.getElectroionizationAverageRecoilElectronIncidentEnergy( 1u );

  FRENSIE_CHECK_EQUAL( recoil_incident_energy.front(), 1.361e-5 );
  FRENSIE_CHECK_EQUAL( recoil_incident_energy.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( recoil_incident_energy.size(), 25 );

  std::vector<double> recoil_energy =
    data_container.getElectroionizationAverageRecoilElectronEnergy( 1u );

  FRENSIE_CHECK_EQUAL( recoil_energy.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( recoil_energy.back(), 7.28699e-5 );
  FRENSIE_CHECK_EQUAL( recoil_energy.size(),
                       recoil_incident_energy.size() );

  std::vector<double> recoil_energy_grid =
    data_container.getElectroionizationRecoilEnergyGrid( 1u );

  FRENSIE_CHECK_EQUAL( recoil_energy_grid.front(), 1.36100e-5 );
  FRENSIE_CHECK_EQUAL( recoil_energy_grid.back(), 1.00000e+5 );
  FRENSIE_CHECK_EQUAL( recoil_energy_grid.size(), 8 );

  std::vector<double> electroionization_recoil_energy =
    data_container.getElectroionizationRecoilEnergyAtEnergy( 1u, 1.36100e-5 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.front(), 2.79866e-9 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.back(), 2.79866e-8 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.size(), 2 );

  electroionization_recoil_energy =
    data_container.getElectroionizationRecoilEnergyAtEnergy( 1u, 1.00000e+5 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.front(), 1.00000e-7 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.back(), 5.00000e+4 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.size(), 147 );

  std::vector<double> electroionization_recoil_pdf =
    data_container.getElectroionizationRecoilPDFAtEnergy( 1u, 1.36100e-5 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.front(), 3.97015e+7 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.back(), 3.97015e+7 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.size(), 2 );

  electroionization_recoil_pdf =
    data_container.getElectroionizationRecoilPDFAtEnergy( 1u, 1.00000e+5 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.front(), 1.61897e+5 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.back(), 2.77550e-15 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.size(), 147 );
  }

  // CHECK BREMSSTRAHLUNG DATA
  {
  std::vector<double> energy_grid =
    data_container.getBremsstrahlungCrossSectionEnergyGrid();

  FRENSIE_CHECK_EQUAL( energy_grid.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 96 );

  std::vector<double> cross_section =
    data_container.getBremsstrahlungCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(),  2.97832e+1 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 9.90621e-1 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), energy_grid.size() );

  std::vector<double> photon_energy_grid =
    data_container.getBremsstrahlungAveragePhotonIncidentEnergy();

  FRENSIE_CHECK_EQUAL( photon_energy_grid.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( photon_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( photon_energy_grid.size(), 82 );

  std::vector<double> photon_energy =
    data_container.getBremsstrahlungAveragePhotonEnergy();

  FRENSIE_CHECK_EQUAL( photon_energy.front(), 2.14426e-6 );
  FRENSIE_CHECK_EQUAL( photon_energy.back(), 2.66815e3 );
  FRENSIE_CHECK_EQUAL( photon_energy.size(),
                       photon_energy_grid.size() );

  std::vector<double> bremsstrahlung_photon_energy_grid =
    data_container.getBremsstrahlungPhotonEnergyGrid();

  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy_grid.front(), 1.00000e-5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy_grid.back(), 1.00000e+5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy_grid.size(), 10 );

  std::vector<double> bremsstrahlung_photon_energy =
    data_container.getBremsstrahlungPhotonEnergyAtEnergy( 1.00000e-5 );

  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.back(), 1.00000e-5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.size(), 17 );

  bremsstrahlung_photon_energy =
    data_container.getBremsstrahlungPhotonEnergyAtEnergy( 1.00000e+5 );

  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.back(), 1.00000e+5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.size(), 111 );

  std::vector<double> bremsstrahlung_photon_pdf =
    data_container.getBremsstrahlungPhotonPDFAtEnergy( 1.00000e-5 );

  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.front(), 2.13940e+6 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.back(), 2.12245e+4 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.size(), 17 );

  bremsstrahlung_photon_pdf =
    data_container.getBremsstrahlungPhotonPDFAtEnergy( 1.00000e+5 );

  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.front(),  3.65591e+5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.back(),  5.16344e-10 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.size(), 111 );

  std::vector<double> electron_incident_energy =
    data_container.getBremsstrahlungAverageElectronIncidentEnergy();

  FRENSIE_CHECK_EQUAL( electron_incident_energy.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( electron_incident_energy.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( electron_incident_energy.size(), 85 );

  std::vector<double> electron_energy =
    data_container.getBremsstrahlungAverageElectronEnergy();

  FRENSIE_CHECK_EQUAL( electron_energy.front(), 7.85574e-6 );
  FRENSIE_CHECK_EQUAL( electron_energy.back(), 9.73318e4 );
  FRENSIE_CHECK_EQUAL( electron_energy.size(),
                       electron_incident_energy.size() );
  }

  // CHECK ATOMIC EXCITATION DATA
  {
  std::vector<double> energy_grid =
    data_container.getAtomicExcitationEnergyGrid();
  FRENSIE_CHECK_EQUAL( energy_grid.front(), 1.361e-5 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 170 );

  std::vector<double> cross_section =
    data_container.getAtomicExcitationCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 8.14416e+4 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), energy_grid.size() );

  std::vector<double> atomic_excitation_energy_loss =
    data_container.getAtomicExcitationEnergyLoss();

  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_loss.front(), 1.36100e-5 );
  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_loss.back(), 2.10777e-5 );
  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_loss.size(),
                       energy_grid.size() );
  }
}

//---------------------------------------------------------------------------//
// Check that a data container can be populated
FRENSIE_UNIT_TEST( StandardENDLDataGenerator, populateENDLDataContainer_c )
{
  data_generator_c.reset( new DataGen::StandardENDLDataGenerator(
                                                     test_c_eadl_file_name,
                                                     test_c_epdl_file_name,
                                                     test_c_eedl_file_name ) );

  data_generator_c->populateENDLDataContainer();

  const Data::ENDLDataContainer& data_container =
    data_generator_c->getDataContainer();

  FRENSIE_CHECK_EQUAL( data_container.getAtomicNumber(), 6 );

  // CHECK ATOMIC RELAXATION DATA
  FRENSIE_CHECK_EQUAL( data_container.getSubshells().size(), 4 );
  FRENSIE_CHECK( data_container.getSubshells().count( 1 ) );
  FRENSIE_CHECK( data_container.getSubshells().count( 2 ) );
  FRENSIE_CHECK( data_container.getSubshells().count( 3 ) );
  FRENSIE_CHECK( data_container.getSubshells().count( 4 ) );

  FRENSIE_CHECK_EQUAL( data_container.getSubshellOccupancy(1), 2 );
  FRENSIE_CHECK_EQUAL( data_container.getSubshellOccupancy(2), 2 );
  FRENSIE_CHECK_EQUAL( data_container.getSubshellOccupancy(3), .67 );
  FRENSIE_CHECK_EQUAL( data_container.getSubshellOccupancy(4), 1.33 );

  FRENSIE_CHECK_EQUAL( data_container.getSubshellBindingEnergy(1), 2.9101E-04 );
  FRENSIE_CHECK_EQUAL( data_container.getSubshellBindingEnergy(2), 1.7560E-05 );
  FRENSIE_CHECK_EQUAL( data_container.getSubshellBindingEnergy(3), 8.9900E-06 );
  FRENSIE_CHECK_EQUAL( data_container.getSubshellBindingEnergy(4), 8.9800E-06 );

  FRENSIE_CHECK_EQUAL( data_container.getSubshellKineticEnergy(1), 4.4702E-04 );
  FRENSIE_CHECK_EQUAL( data_container.getSubshellKineticEnergy(2), 4.8360E-05 );
  FRENSIE_CHECK_EQUAL( data_container.getSubshellKineticEnergy(3), 3.6960E-05 );
  FRENSIE_CHECK_EQUAL( data_container.getSubshellKineticEnergy(4), 3.6900E-05 );

  FRENSIE_CHECK_EQUAL( data_container.getSubshellAverageRadius(1), 1.4068E-09 );
  FRENSIE_CHECK_EQUAL( data_container.getSubshellAverageRadius(2), 8.0784E-09 );
  FRENSIE_CHECK_EQUAL( data_container.getSubshellAverageRadius(3), 9.1365E-09 );
  FRENSIE_CHECK_EQUAL( data_container.getSubshellAverageRadius(4), 9.1442E-09 );

  FRENSIE_CHECK_EQUAL( data_container.getSubshellRadiativeLevel(1),
                       1.033500000E-10 );
  FRENSIE_CHECK_EQUAL( data_container.getSubshellNonRadiativeLevel(1),
                       6.133600000E-08 );
  FRENSIE_CHECK_EQUAL( data_container.getLocalDepositionPerInitialVacancy(1),
                       2.853950000E-05 );
  FRENSIE_CHECK_EQUAL( data_container.getLocalDepositionPerInitialVacancy(2),
                       1.756000000E-05 );
  FRENSIE_CHECK_EQUAL( data_container.getLocalDepositionPerInitialVacancy(3),
                       8.990000000E-06 );
  FRENSIE_CHECK_EQUAL( data_container.getLocalDepositionPerInitialVacancy(4),
                       8.980000000E-06 );


  FRENSIE_CHECK_EQUAL( data_container.getAveragePhotonsPerInitialVacancy(1),
                       1.682080000E-03 );
  FRENSIE_CHECK_EQUAL( data_container.getAveragePhotonEnergyPerInitialVacancy(1),
                       4.743930000E-07 );
  FRENSIE_CHECK_EQUAL( data_container.getAverageElectronsPerInitialVacancy(1),
                       9.983180000E-01 );
  FRENSIE_CHECK_EQUAL( data_container.getAverageElectronEnergyPerInitialVacancy(1),
                       2.619960000E-04 );

  FRENSIE_CHECK_EQUAL(
    data_container.getRadiativeTransitionProbability(1).size(),
    2 );
  FRENSIE_CHECK_EQUAL(
    data_container.getRadiativeTransitionProbability(1).find(3)->second,
    5.614880000E-04 );
  FRENSIE_CHECK_EQUAL(
    data_container.getRadiativeTransitionProbability(1).find(4)->second,
    1.120600000E-03 );

  FRENSIE_CHECK_EQUAL(
    data_container.getRadiativeTransitionEnergy(1).size(),
    2 );
  FRENSIE_CHECK_EQUAL(
    data_container.getRadiativeTransitionEnergy(1).find(3)->second,
    2.820200000E-04 );
  FRENSIE_CHECK_EQUAL(
    data_container.getRadiativeTransitionEnergy(1).find(4)->second,
    2.820300000E-04 );



  FRENSIE_CHECK_EQUAL(
    data_container.getNonRadiativeTransitionProbability(1).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    data_container.getNonRadiativeTransitionProbability(1).find(2)->second.size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    data_container.getNonRadiativeTransitionProbability(1).find(3)->second.size(),
    2 );
  FRENSIE_CHECK_EQUAL(
    data_container.getNonRadiativeTransitionProbability(1).find(4)->second.size(),
    1 );
  FRENSIE_CHECK_EQUAL(
    data_container.getNonRadiativeTransitionProbability(1).find(2)->second.find(2)->second,
    4.136090000E-01 );
  FRENSIE_CHECK_EQUAL(
    data_container.getNonRadiativeTransitionProbability(1).find(2)->second.find(3)->second,
    1.361900000E-01 );
  FRENSIE_CHECK_EQUAL(
    data_container.getNonRadiativeTransitionProbability(1).find(2)->second.find(4)->second,
    2.710990000E-01 );
  FRENSIE_CHECK_EQUAL(
    data_container.getNonRadiativeTransitionProbability(1).find(3)->second.find(3)->second,
    4.207480000E-03 );
  FRENSIE_CHECK_EQUAL(
    data_container.getNonRadiativeTransitionProbability(1).find(3)->second.find(4)->second,
    1.100120000E-01 );
  FRENSIE_CHECK_EQUAL(
    data_container.getNonRadiativeTransitionProbability(1).find(4)->second.find(4)->second,
    6.320080000E-02 );

  FRENSIE_CHECK_EQUAL(
    data_container.getNonRadiativeTransitionEnergy(1).size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    data_container.getNonRadiativeTransitionEnergy(1).find(2)->second.size(),
    3 );
  FRENSIE_CHECK_EQUAL(
    data_container.getNonRadiativeTransitionEnergy(1).find(3)->second.size(),
    2 );
  FRENSIE_CHECK_EQUAL(
    data_container.getNonRadiativeTransitionEnergy(1).find(4)->second.size(),
    1 );
  FRENSIE_CHECK_EQUAL(
    data_container.getNonRadiativeTransitionEnergy(1).find(2)->second.find(2)->second,
    2.558900000E-04 );
  FRENSIE_CHECK_EQUAL(
    data_container.getNonRadiativeTransitionEnergy(1).find(2)->second.find(3)->second,
    2.644600000E-04 );
  FRENSIE_CHECK_EQUAL(
    data_container.getNonRadiativeTransitionEnergy(1).find(2)->second.find(4)->second,
    2.644700000E-04 );
  FRENSIE_CHECK_EQUAL(
    data_container.getNonRadiativeTransitionEnergy(1).find(3)->second.find(3)->second,
    2.730300000E-04 );
  FRENSIE_CHECK_EQUAL(
    data_container.getNonRadiativeTransitionEnergy(1).find(3)->second.find(4)->second,
    2.730400000E-04 );
  FRENSIE_CHECK_EQUAL(
    data_container.getNonRadiativeTransitionEnergy(1).find(4)->second.find(4)->second,
    2.730500000E-04 );

  // CHECK COHERENT PHOTON DATA
  {
  std::vector<double> energy_grid =
    data_container.getCoherentCrossSectionEnergyGrid();

  FRENSIE_CHECK_EQUAL( energy_grid.front(), 1.0e-6 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 634 );

  std::vector<double> cross_section = data_container.getCoherentCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 5.063257000E-05 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 7.687960000E-14 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), energy_grid.size() );

  std::vector<double> form_factor_argument =
    data_container.getCoherentFormFactorArgument();

  FRENSIE_CHECK_EQUAL( form_factor_argument.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( form_factor_argument.back(), 1.0e17 );
  FRENSIE_CHECK_EQUAL( form_factor_argument.size(), 138 );

  std::vector<double> form_factor = data_container.getCoherentFormFactor();

  FRENSIE_CHECK_EQUAL( form_factor.front(), 6.0 );
  FRENSIE_CHECK_EQUAL( form_factor.back(), 1.681000000E-29 );
  FRENSIE_CHECK_EQUAL( form_factor.size(), form_factor_argument.size() );

  std::vector<double> factor_energy =
    data_container.getCoherentImaginaryAnomalousFactorIncidentEnergy();

  FRENSIE_CHECK_EQUAL( factor_energy.front(), 1.0e-6 );
  FRENSIE_CHECK_EQUAL( factor_energy.back(), 10.0 );
  FRENSIE_CHECK_EQUAL( factor_energy.size(), 273 );

  std::vector<double> factor =
    data_container.getCoherentImaginaryAnomalousFactor();

  FRENSIE_CHECK_EQUAL( factor.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( factor.back(), 8.131066000E-08 );
  FRENSIE_CHECK_EQUAL( factor.size(), factor_energy.size() );

  factor_energy = data_container.getCoherentRealAnomalousFactorIncidentEnergy();

  FRENSIE_CHECK_EQUAL( factor_energy.front(), 1.0e-6 );
  FRENSIE_CHECK_EQUAL( factor_energy.back(), 10.0 );
  FRENSIE_CHECK_EQUAL( factor_energy.size(), 340 );

  factor =
    data_container.getCoherentRealAnomalousFactor();

  FRENSIE_CHECK_EQUAL( factor.front(), -5.991287000E+00 );
  FRENSIE_CHECK_EQUAL( factor.back(), -2.077819000E-03 );
  FRENSIE_CHECK_EQUAL( factor.size(), factor_energy.size() );

  std::vector<double> photon_energy_grid =
    data_container.getCoherentAveragePhotonIncidentEnergy();

  FRENSIE_CHECK_EQUAL( photon_energy_grid.front(), 1.0e-6 );
  FRENSIE_CHECK_EQUAL( photon_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( photon_energy_grid.size(), 2 );

  std::vector<double> photon_energy =
    data_container.getCoherentAveragePhotonEnergy();

  FRENSIE_CHECK_EQUAL( photon_energy.front(), 1.0e-6 );
  FRENSIE_CHECK_EQUAL( photon_energy.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( photon_energy.size(), photon_energy_grid.size() );
  }

  // SET INCOHERENT PHOTON DATA
  {
  std::vector<double> energy_grid =
    data_container.getIncoherentCrossSectionEnergyGrid();

  FRENSIE_CHECK_EQUAL( energy_grid.front(), 1.0e-6 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 111 );

  std::vector<double> cross_section =
    data_container.getIncoherentCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 2.821900000E-07 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 1.023000000E-04 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), energy_grid.size() );

  std::vector<double> scattering_function_argument =
    data_container.getIncoherentScatteringFunctionArgument();

  FRENSIE_CHECK_EQUAL( scattering_function_argument.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( scattering_function_argument.back(), 1.0e17 );
  FRENSIE_CHECK_EQUAL( scattering_function_argument.size(), 142 );

  std::vector<double> scattering_function =
    data_container.getIncoherentScatteringFunction();

  FRENSIE_CHECK_EQUAL( scattering_function.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( scattering_function.back(), 6.0 );
  FRENSIE_CHECK_EQUAL( scattering_function.size(),
                       scattering_function_argument.size() );

  std::vector<double> photon_energy_grid =
    data_container.getIncoherentAveragePhotonIncidentEnergy();

  FRENSIE_CHECK_EQUAL( photon_energy_grid.front(), 1.0e-6 );
  FRENSIE_CHECK_EQUAL( photon_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( photon_energy_grid.size(), 111 );

  std::vector<double> photon_energy =
    data_container.getIncoherentAveragePhotonEnergy();

  FRENSIE_CHECK_EQUAL( photon_energy.front(), 9.999973000E-07 );
  FRENSIE_CHECK_EQUAL( photon_energy.back(), 9.955317000E+03 );
  FRENSIE_CHECK_EQUAL( photon_energy.size(), photon_energy_grid.size() );

  std::vector<double> electron_energy_grid =
    data_container.getIncoherentAverageElectronIncidentEnergy();

  FRENSIE_CHECK_EQUAL( electron_energy_grid.front(), 1.0e-6 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.size(), 111 );

  std::vector<double> electron_energy =
    data_container.getIncoherentAverageElectronEnergy();

  FRENSIE_CHECK_EQUAL( electron_energy.front(), 2.740270000E-12 );
  FRENSIE_CHECK_EQUAL( electron_energy.back(), 9.004468000E+04 );
  FRENSIE_CHECK_EQUAL( electron_energy.size(), electron_energy_grid.size() );
  }

  // SET PHOTOELECTRIC PHOTON DATA
  {
  std::vector<double> energy_grid =
    data_container.getPhotoelectricCrossSectionEnergyGrid();

  FRENSIE_CHECK_EQUAL( energy_grid.front(), 8.980000000E-06 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 355 );

  std::vector<double> cross_section =
    data_container.getPhotoelectricCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 8.801018000E+06 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 9.055050000E-11 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), energy_grid.size() );

  std::vector<double> residual_energy_grid =
    data_container.getPhotoelectricAverageResidualIncidentEnergy();

  FRENSIE_CHECK_EQUAL( residual_energy_grid.front(), 8.980000000E-06 );
  FRENSIE_CHECK_EQUAL( residual_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( residual_energy_grid.size(), 25 );

  std::vector<double> residual_energy =
    data_container.getPhotoelectricAverageResidualEnergy();

  FRENSIE_CHECK_EQUAL( residual_energy.front(), 8.980000000E-06 );
  FRENSIE_CHECK_EQUAL( residual_energy.back(), 2.798494000E-05 );
  FRENSIE_CHECK_EQUAL( residual_energy.size(), residual_energy_grid.size() );

  std::vector<double> photon_energy_grid =
    data_container.getPhotoelectricAveragePhotonsIncidentEnergy();

  FRENSIE_CHECK_EQUAL( photon_energy_grid.front(), 8.980000000E-06 );
  FRENSIE_CHECK_EQUAL( photon_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( photon_energy_grid.size(), 9 );

  std::vector<double> photon_energy =
    data_container.getPhotoelectricAveragePhotonsEnergy();

  FRENSIE_CHECK_EQUAL( photon_energy.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( photon_energy.back(), 4.504140000E-07 );
  FRENSIE_CHECK_EQUAL( photon_energy.size(), photon_energy_grid.size() );

  std::vector<double> electron_energy_grid =
    data_container.getPhotoelectricAverageElectronsIncidentEnergy();

  FRENSIE_CHECK_EQUAL( electron_energy_grid.front(), 8.980000000E-06 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.size(), 16 );

  std::vector<double> electron_energy =
    data_container.getPhotoelectricAverageElectronsEnergy();

  FRENSIE_CHECK_EQUAL( electron_energy.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( electron_energy.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( electron_energy.size(), electron_energy_grid.size() );
  }

  // SET PHOTOELECTRIC PHOTON DATA BY SUBSHELL
  //subshell 1
  {
  std::vector<double> energy_grid =
    data_container.getPhotoelectricCrossSectionEnergyGrid(1);

  FRENSIE_CHECK_EQUAL( energy_grid.front(), 2.910100000E-04 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 78 );

  std::vector<double> cross_section =
    data_container.getPhotoelectricCrossSection(1);

  FRENSIE_CHECK_EQUAL( cross_section.front(), 9.589120000E+05 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 8.597400000E-11 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), energy_grid.size() );

  std::vector<double> residual_energy_grid =
    data_container.getPhotoelectricAverageResidualIncidentEnergy(1);

  FRENSIE_CHECK_EQUAL( residual_energy_grid.front(), 2.910100000E-04 );
  FRENSIE_CHECK_EQUAL( residual_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( residual_energy_grid.size(), 2 );

  std::vector<double> residual_energy =
    data_container.getPhotoelectricAverageResidualEnergy(1);

  FRENSIE_CHECK_EQUAL( residual_energy.front(), 2.854000000E-05 );
  FRENSIE_CHECK_EQUAL( residual_energy.back(), 2.854000000E-05 );
  FRENSIE_CHECK_EQUAL( residual_energy.size(), residual_energy_grid.size() );

  std::vector<double> photon_energy_grid =
    data_container.getPhotoelectricAveragePhotonsIncidentEnergy(1);

  FRENSIE_CHECK_EQUAL( photon_energy_grid.front(), 2.910100000E-04 );
  FRENSIE_CHECK_EQUAL( photon_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( photon_energy_grid.size(), 2 );

  std::vector<double> photon_energy =
    data_container.getPhotoelectricAveragePhotonsEnergy(1);

  FRENSIE_CHECK_EQUAL( photon_energy.front(), 4.743900000E-07 );
  FRENSIE_CHECK_EQUAL( photon_energy.back(), 4.743900000E-07 );
  FRENSIE_CHECK_EQUAL( photon_energy.size(), photon_energy_grid.size() );

  std::vector<double> electron_energy_grid =
    data_container.getPhotoelectricAverageElectronsIncidentEnergy(1);

  FRENSIE_CHECK_EQUAL( electron_energy_grid.front(), 2.910100000E-04 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.size(), 2 );

  std::vector<double> electron_energy =
    data_container.getPhotoelectricAverageElectronsEnergy(1);

  FRENSIE_CHECK_EQUAL( electron_energy.front(), 2.619956000E-04 );
  FRENSIE_CHECK_EQUAL( electron_energy.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( electron_energy.size(), electron_energy_grid.size() );
  }
  // subshell 2
  {
  std::vector<double> energy_grid =
    data_container.getPhotoelectricCrossSectionEnergyGrid(2);

  FRENSIE_CHECK_EQUAL( energy_grid.front(), 1.756000000E-05 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 109 );

  std::vector<double> cross_section =
    data_container.getPhotoelectricCrossSection(2);

  FRENSIE_CHECK_EQUAL( cross_section.front(), 8.760920000E+05 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 4.575200000E-12 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), energy_grid.size() );

  std::vector<double> residual_energy_grid =
    data_container.getPhotoelectricAverageResidualIncidentEnergy(2);

  FRENSIE_CHECK_EQUAL( residual_energy_grid.front(), 1.756000000E-05 );
  FRENSIE_CHECK_EQUAL( residual_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( residual_energy_grid.size(), 2 );

  std::vector<double> residual_energy =
    data_container.getPhotoelectricAverageResidualEnergy(2);

  FRENSIE_CHECK_EQUAL( residual_energy.front(), 1.756000000E-05 );
  FRENSIE_CHECK_EQUAL( residual_energy.back(), 1.756000000E-05 );
  FRENSIE_CHECK_EQUAL( residual_energy.size(), residual_energy_grid.size() );

  std::vector<double> electron_energy_grid =
    data_container.getPhotoelectricAverageElectronsIncidentEnergy(2);

  FRENSIE_CHECK_EQUAL( electron_energy_grid.front(), 1.756000000E-05 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.size(), 2 );

  std::vector<double> electron_energy =
    data_container.getPhotoelectricAverageElectronsEnergy(2);

  FRENSIE_CHECK_EQUAL( electron_energy.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( electron_energy.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( electron_energy.size(), electron_energy_grid.size() );
  }
  //subshell 3
  {
  std::vector<double> energy_grid =
    data_container.getPhotoelectricCrossSectionEnergyGrid(3);

  FRENSIE_CHECK_EQUAL( energy_grid.front(), 8.990000000E-06 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 115 );

  std::vector<double> cross_section =
    data_container.getPhotoelectricCrossSection(3);

  FRENSIE_CHECK_EQUAL( cross_section.front(), 4.393500000E+06 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 3.875700000E-16 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), energy_grid.size() );

  std::vector<double> residual_energy_grid =
    data_container.getPhotoelectricAverageResidualIncidentEnergy(3);

  FRENSIE_CHECK_EQUAL( residual_energy_grid.front(), 8.990000000E-06 );
  FRENSIE_CHECK_EQUAL( residual_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( residual_energy_grid.size(), 2 );

  std::vector<double> residual_energy =
    data_container.getPhotoelectricAverageResidualEnergy(3);

  FRENSIE_CHECK_EQUAL( residual_energy.front(), 8.990000000E-06 );
  FRENSIE_CHECK_EQUAL( residual_energy.back(), 8.990000000E-06 );
  FRENSIE_CHECK_EQUAL( residual_energy.size(), residual_energy_grid.size() );


  std::vector<double> electron_energy_grid =
    data_container.getPhotoelectricAverageElectronsIncidentEnergy(3);

  FRENSIE_CHECK_EQUAL( electron_energy_grid.front(), 8.990000000E-06 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.size(), 2 );

  std::vector<double> electron_energy =
    data_container.getPhotoelectricAverageElectronsEnergy(3);

  FRENSIE_CHECK_EQUAL( electron_energy.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( electron_energy.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( electron_energy.size(), electron_energy_grid.size() );
  }
  //subshell 4
  {
  std::vector<double> energy_grid =
    data_container.getPhotoelectricCrossSectionEnergyGrid(4);

  FRENSIE_CHECK_EQUAL( energy_grid.front(), 8.980000000E-06 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 113 );

  std::vector<double> cross_section =
    data_container.getPhotoelectricCrossSection(4);

  FRENSIE_CHECK_EQUAL( cross_section.front(), 8.801018000E+06 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 8.933100000E-16 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), energy_grid.size() );

  std::vector<double> residual_energy_grid =
    data_container.getPhotoelectricAverageResidualIncidentEnergy(4);

  FRENSIE_CHECK_EQUAL( residual_energy_grid.front(), 8.980000000E-06 );
  FRENSIE_CHECK_EQUAL( residual_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( residual_energy_grid.size(), 2 );

  std::vector<double> residual_energy =
    data_container.getPhotoelectricAverageResidualEnergy(4);

  FRENSIE_CHECK_EQUAL( residual_energy.front(), 8.980000000E-06 );
  FRENSIE_CHECK_EQUAL( residual_energy.back(), 8.980000000E-06 );
  FRENSIE_CHECK_EQUAL( residual_energy.size(), residual_energy_grid.size() );

  std::vector<double> electron_energy_grid =
    data_container.getPhotoelectricAverageElectronsIncidentEnergy(4);

  FRENSIE_CHECK_EQUAL( electron_energy_grid.front(), 8.980000000E-06 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.size(), 2 );

  std::vector<double> electron_energy =
    data_container.getPhotoelectricAverageElectronsEnergy(4);

  FRENSIE_CHECK_EQUAL( electron_energy.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( electron_energy.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( electron_energy.size(), electron_energy_grid.size() );
  }

  // SET PAIR PRODUCTION PHOTON DATA
  {
  std::vector<double> energy_grid =
    data_container.getPairProductionCrossSectionEnergyGrid();

  FRENSIE_CHECK_EQUAL( energy_grid.front(), 1.022000000E+00 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 94 );

  std::vector<double> cross_section =
    data_container.getPairProductionCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 3.002000000E-01 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), energy_grid.size() );

  std::vector<double> positron_energy_grid =
    data_container.getPairProductionAveragePositronIncidentEnergy();

  FRENSIE_CHECK_EQUAL( positron_energy_grid.front(),  1.022000000E+00 );
  FRENSIE_CHECK_EQUAL( positron_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( positron_energy_grid.size(), 2 );

  std::vector<double> positron_energy =
    data_container.getPairProductionAveragePositronEnergy();

  FRENSIE_CHECK_EQUAL( positron_energy.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( positron_energy.back(), 4.999949000E+04 );
  FRENSIE_CHECK_EQUAL( positron_energy.size(), positron_energy_grid.size() );

  std::vector<double> electron_energy_grid =
    data_container.getPairProductionAverageElectronIncidentEnergy();

  FRENSIE_CHECK_EQUAL( electron_energy_grid.front(),  1.022000000E+00 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.size(), 2 );

  std::vector<double> electron_energy =
    data_container.getPairProductionAverageElectronEnergy();

  FRENSIE_CHECK_EQUAL( electron_energy.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( electron_energy.back(), 4.999949000E+04 );
  FRENSIE_CHECK_EQUAL( electron_energy.size(), electron_energy_grid.size() );
  }

  // SET TRIPLET PRODUCTION PHOTON DATA
  {
  std::vector<double> energy_grid =
    data_container.getTripletProductionCrossSectionEnergyGrid();

  FRENSIE_CHECK_EQUAL( energy_grid.front(), 2.044000000E+00 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 83 );

  std::vector<double> cross_section =
    data_container.getTripletProductionCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 5.873000000E-02 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), energy_grid.size() );

  std::vector<double> positron_energy_grid =
    data_container.getTripletProductionAveragePositronIncidentEnergy();

  FRENSIE_CHECK_EQUAL( positron_energy_grid.front(), 2.044000000E+00 );
  FRENSIE_CHECK_EQUAL( positron_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( positron_energy_grid.size(), 2 );

  std::vector<double> positron_energy =
    data_container.getTripletProductionAveragePositronEnergy();

  FRENSIE_CHECK_EQUAL( positron_energy.front(), 5.110000000E-01 );
  FRENSIE_CHECK_EQUAL( positron_energy.back(), 4.999949000E+04 );
  FRENSIE_CHECK_EQUAL( positron_energy.size(), positron_energy_grid.size() );

  std::vector<double> electron_energy_grid =
    data_container.getTripletProductionAverageElectronIncidentEnergy();

  FRENSIE_CHECK_EQUAL( electron_energy_grid.front(), 2.044000000E+00 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( electron_energy_grid.size(), 2 );

  std::vector<double> electron_energy =
    data_container.getTripletProductionAverageElectronEnergy();

  FRENSIE_CHECK_EQUAL( electron_energy.front(), 5.110000000E-01 );
  FRENSIE_CHECK_EQUAL( electron_energy.back(), 4.999949000E+04 );
  FRENSIE_CHECK_EQUAL( electron_energy.size(), electron_energy_grid.size() );
  }
  // CHECK ELASTIC DATA
  std::vector<double> energy_grid = data_container.getElasticEnergyGrid();
  FRENSIE_CHECK_EQUAL( energy_grid.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 101 );

  std::vector<double> cross_section =
    data_container.getElasticTransportCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 3.06351e+9 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 1.51014e-8 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), energy_grid.size() );

  cross_section =
    data_container.getCutoffElasticCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 3.06351e+9 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 4.72309e-4 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), energy_grid.size() );

  std::vector<double> residual_incident_energy =
    data_container.getCutoffElasticResidualIncidentEnergy();

  FRENSIE_CHECK_EQUAL( residual_incident_energy.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( residual_incident_energy.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( residual_incident_energy.size(), 2 );

  std::vector<double> residual_energy =
    data_container.getCutoffElasticResidualEnergy();

  FRENSIE_CHECK_EQUAL( residual_energy.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( residual_energy.back(), 0.0 );
  FRENSIE_CHECK_EQUAL( residual_energy.size(),
                       residual_incident_energy.size() );

  std::vector<double> scattered_incident_energy =
    data_container.getCutoffElasticScatteredElectronIncidentEnergy();

  FRENSIE_CHECK_EQUAL( scattered_incident_energy.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( scattered_incident_energy.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( scattered_incident_energy.size(), 2 );

  std::vector<double> scattered_energy =
    data_container.getCutoffElasticScatteredElectronEnergy();

  FRENSIE_CHECK_EQUAL( scattered_energy.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( scattered_energy.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( scattered_energy.size(),
                       scattered_incident_energy.size() );

  std::vector<double> angular_grid =
    data_container.getCutoffElasticAngularEnergyGrid();

  FRENSIE_CHECK_EQUAL( angular_grid.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( angular_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( angular_grid.size(), 16 );

  std::vector<double> elastic_angles =
    data_container.getCutoffElasticAnglesAtEnergy(1.0e-5);

  FRENSIE_CHECK_EQUAL( elastic_angles.front(), 1.0e-6 );
  FRENSIE_CHECK_EQUAL( elastic_angles.back(), 2.0 );
  FRENSIE_CHECK_EQUAL( elastic_angles.size(), 2 );

  elastic_angles =
    data_container.getCutoffElasticAnglesAtEnergy(1.0e+5);

  FRENSIE_CHECK_EQUAL( elastic_angles.front(), 1.0e-6 );
  FRENSIE_CHECK_EQUAL( elastic_angles.back(), 2.0 );
  FRENSIE_CHECK_EQUAL( elastic_angles.size(), 96 );

  std::vector<double> elastic_pdf =
    data_container.getCutoffElasticPDFAtEnergy(1.0e-5);

  FRENSIE_CHECK_EQUAL( elastic_pdf.front(), 0.5 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.back(), 0.5 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.size(), 2 );

  elastic_pdf =
    data_container.getCutoffElasticPDFAtEnergy(1.0e+5);

  FRENSIE_CHECK_EQUAL( elastic_pdf.front(), 9.868670E+05 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.back(), 1.693970E-11 );
  FRENSIE_CHECK_EQUAL( elastic_pdf.size(), 96 );

  cross_section =
    data_container.getTotalElasticCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 3.06351e+9 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 1.40722e5 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), energy_grid.size() );

  // CHECK ELECTROIONIZATION DATA
  // Subshell 1
  energy_grid = data_container.getElectroionizationCrossSectionEnergyGrid( 1u );

  FRENSIE_CHECK_EQUAL( energy_grid.front(), 2.9101e-4 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 25 );

  cross_section =
    data_container.getElectroionizationCrossSection( 1u );

  FRENSIE_CHECK_EQUAL( cross_section.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 1.338050e4 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), energy_grid.size() );

  scattered_incident_energy =
    data_container.getElectroionizationAverageScatteredElectronIncidentEnergy( 1u );

  FRENSIE_CHECK_EQUAL( scattered_incident_energy.front(), 2.9101e-4 );
  FRENSIE_CHECK_EQUAL( scattered_incident_energy.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( scattered_incident_energy.size(), 6 );

  scattered_energy =
    data_container.getElectroionizationAverageScatteredElectronEnergy( 1u );

  FRENSIE_CHECK_EQUAL( scattered_energy.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( scattered_energy.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( scattered_energy.size(),
                       scattered_incident_energy.size() );

  std::vector<double> recoil_incident_energy =
    data_container.getElectroionizationAverageRecoilElectronIncidentEnergy( 1u );

  FRENSIE_CHECK_EQUAL( recoil_incident_energy.front(), 2.9101e-4 );
  FRENSIE_CHECK_EQUAL( recoil_incident_energy.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( recoil_incident_energy.size(), 22 );

  std::vector<double> recoil_energy =
    data_container.getElectroionizationAverageRecoilElectronEnergy( 1u );

  FRENSIE_CHECK_EQUAL( recoil_energy.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( recoil_energy.back(), 8.76406e-4 );
  FRENSIE_CHECK_EQUAL( recoil_energy.size(), recoil_incident_energy.size() );

  std::vector<double> recoil_energy_grid =
    data_container.getElectroionizationRecoilEnergyGrid( 1u );

  FRENSIE_CHECK_EQUAL( recoil_energy_grid.front(), 2.910100E-04 );
  FRENSIE_CHECK_EQUAL( recoil_energy_grid.back(), 1.00000e+5 );
  FRENSIE_CHECK_EQUAL( recoil_energy_grid.size(), 7 );

  std::vector<double> electroionization_recoil_energy =
    data_container.getElectroionizationRecoilEnergyAtEnergy( 1u, 2.910100E-04 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.front(), 1.00000e-8 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.back(), 1.00000e-7 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.size(), 2 );

  electroionization_recoil_energy =
    data_container.getElectroionizationRecoilEnergyAtEnergy( 1u, 1.00000e+5 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.front(), 1.00000e-7 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.back(), 5.00000e+4 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.size(), 128 );

  std::vector<double> electroionization_recoil_pdf =
    data_container.getElectroionizationRecoilPDFAtEnergy( 1u, 2.910100E-04 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.front(), 1.111110E+07 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.back(), 1.111110E+07 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.size(), 2 );

  electroionization_recoil_pdf =
    data_container.getElectroionizationRecoilPDFAtEnergy( 1u, 1.00000e+5 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.front(), 7.358100E+03 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.back(), 3.45597E-14 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.size(), 128 );


  // Subshell 4
  energy_grid = data_container.getElectroionizationCrossSectionEnergyGrid( 4u );

  FRENSIE_CHECK_EQUAL( energy_grid.front(), 8.980e-6 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 35 );

  cross_section =
    data_container.getElectroionizationCrossSection( 4u );

  FRENSIE_CHECK_EQUAL( cross_section.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 2.017010E+05 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), energy_grid.size() );


  scattered_incident_energy =
    data_container.getElectroionizationAverageScatteredElectronIncidentEnergy( 4u );

  FRENSIE_CHECK_EQUAL( scattered_incident_energy.front(), 8.980e-6 );
  FRENSIE_CHECK_EQUAL( scattered_incident_energy.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( scattered_incident_energy.size(), 6 );

  scattered_energy =
    data_container.getElectroionizationAverageScatteredElectronEnergy( 4u );

  FRENSIE_CHECK_EQUAL( scattered_energy.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( scattered_energy.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( scattered_energy.size(),
                       scattered_incident_energy.size() );

  recoil_incident_energy =
    data_container.getElectroionizationAverageRecoilElectronIncidentEnergy( 4u );

  FRENSIE_CHECK_EQUAL( recoil_incident_energy.front(), 8.980e-6 );
  FRENSIE_CHECK_EQUAL( recoil_incident_energy.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( recoil_incident_energy.size(), 25 );

  recoil_energy =
    data_container.getElectroionizationAverageRecoilElectronEnergy( 4u );

  FRENSIE_CHECK_EQUAL( recoil_energy.front(), 0.0 );
  FRENSIE_CHECK_EQUAL( recoil_energy.back(), 4.687980e-5 );
  FRENSIE_CHECK_EQUAL( recoil_energy.size(), recoil_incident_energy.size() );

  recoil_energy_grid =
    data_container.getElectroionizationRecoilEnergyGrid( 4u );

  FRENSIE_CHECK_EQUAL( recoil_energy_grid.front(), 8.980000E-06 );
  FRENSIE_CHECK_EQUAL( recoil_energy_grid.back(), 1.00000e+5 );
  FRENSIE_CHECK_EQUAL( recoil_energy_grid.size(), 8 );

  electroionization_recoil_energy =
    data_container.getElectroionizationRecoilEnergyAtEnergy( 4u, 8.980000E-06 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.front(), 2.550000E-09 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.back(), 2.550000E-08 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.size(), 2 );

  electroionization_recoil_energy =
    data_container.getElectroionizationRecoilEnergyAtEnergy( 4u, 1.00000e+5 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.front(), 1.00000e-7 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.back(), 5.00000e+4 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_energy.size(), 143 );

  electroionization_recoil_pdf =
    data_container.getElectroionizationRecoilPDFAtEnergy( 4u, 8.980000E-06 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.front(), 4.357300E+07 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.back(), 4.357300E+07 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.size(), 2 );

  electroionization_recoil_pdf =
    data_container.getElectroionizationRecoilPDFAtEnergy( 4u, 1.00000e+5 );

  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.front(), 1.120930E+05 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.back(), 1.515230E-15 );
  FRENSIE_CHECK_EQUAL( electroionization_recoil_pdf.size(), 143 );

  // CHECK BREMSSTRAHLUNG DATA
  energy_grid = data_container.getBremsstrahlungCrossSectionEnergyGrid();
  FRENSIE_CHECK_EQUAL( energy_grid.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 84 );

  cross_section =
    data_container.getBremsstrahlungCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 6.03128e2 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 1.69715e1 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), energy_grid.size() );

  std::vector<double> photon_energy_grid =
    data_container.getBremsstrahlungAveragePhotonIncidentEnergy();

  FRENSIE_CHECK_EQUAL( photon_energy_grid.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( photon_energy_grid.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( photon_energy_grid.size(), 75 );

  std::vector<double> photon_energy =
    data_container.getBremsstrahlungAveragePhotonEnergy();

  FRENSIE_CHECK_EQUAL( photon_energy.front(), 2.15038e-6 );
  FRENSIE_CHECK_EQUAL( photon_energy.back(), 2.71203e3 );
  FRENSIE_CHECK_EQUAL( photon_energy.size(), photon_energy_grid.size() );

  std::vector<double> bremsstrahlung_photon_energy_grid =
    data_container.getBremsstrahlungPhotonEnergyGrid();

  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy_grid.front(), 1.00000e-5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy_grid.back(), 1.00000e+5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy_grid.size(), 9 );

  std::vector<double> bremsstrahlung_photon_energy =
    data_container.getBremsstrahlungPhotonEnergyAtEnergy( 1.00000e-5 );

  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.back(), 1.00000e-5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.size(), 17 );

  bremsstrahlung_photon_energy =
    data_container.getBremsstrahlungPhotonEnergyAtEnergy( 1.00000e+5 );

  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.front(), 1.00000e-7 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.back(), 1.00000e+5 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_energy.size(), 105 );

  std::vector<double> bremsstrahlung_photon_pdf =
    data_container.getBremsstrahlungPhotonPDFAtEnergy( 1.00000e-5 );

  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.front(), 2.134970E+06 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.back(), 2.136140E+04 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.size(), 17 );

  bremsstrahlung_photon_pdf =
    data_container.getBremsstrahlungPhotonPDFAtEnergy( 1.00000e+5 );

  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.front(), 3.649330E+05 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.back(),  5.638520E-09 );
  FRENSIE_CHECK_EQUAL( bremsstrahlung_photon_pdf.size(), 105 );

  std::vector<double> electron_incident_energy =
    data_container.getBremsstrahlungAverageElectronIncidentEnergy();

  FRENSIE_CHECK_EQUAL( electron_incident_energy.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( electron_incident_energy.back(), 1.0e5 );
  FRENSIE_CHECK_EQUAL( electron_incident_energy.size(), 76 );

  std::vector<double> electron_energy =
    data_container.getBremsstrahlungAverageElectronEnergy();

  FRENSIE_CHECK_EQUAL( electron_energy.front(), 7.84962e-6 );
  FRENSIE_CHECK_EQUAL( electron_energy.back(), 9.7288e4 );
  FRENSIE_CHECK_EQUAL( electron_energy.size(),
                       electron_incident_energy.size() );

  // CHECK ATOMIC EXCITATION DATA
  energy_grid = data_container.getAtomicExcitationEnergyGrid();

  FRENSIE_CHECK_EQUAL( energy_grid.front(), 1.0e-5 );
  FRENSIE_CHECK_EQUAL( energy_grid.back(), 1.0e+5 );
  FRENSIE_CHECK_EQUAL( energy_grid.size(), 181 );

  cross_section =
    data_container.getAtomicExcitationCrossSection();

  FRENSIE_CHECK_EQUAL( cross_section.front(), 3.168630E+06 );
  FRENSIE_CHECK_EQUAL( cross_section.back(), 1.19892e5 );
  FRENSIE_CHECK_EQUAL( cross_section.size(), energy_grid.size() );

  std::vector<double> atomic_excitation_energy_loss =
    data_container.getAtomicExcitationEnergyLoss();

  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_loss.front(), 9.232690E-06 );
  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_loss.back(), 1.981540E-05 );
  FRENSIE_CHECK_EQUAL( atomic_excitation_energy_loss.size(),
                       energy_grid.size() );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_h_eadl_file",
                                        test_h_eadl_file_name, "",
                                        "Test EADL file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_h_epdl_file",
                                        test_h_epdl_file_name, "",
                                        "Test EPDL file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_h_eedl_file",
                                        test_h_eedl_file_name, "",
                                        "Test EEDL file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_c_eadl_file",
                                        test_c_eadl_file_name, "",
                                        "Test EADL file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_c_epdl_file",
                                        test_c_epdl_file_name, "",
                                        "Test EPDL file name" );
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_c_eedl_file",
                                        test_c_eedl_file_name, "",
                                        "Test EEDL file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstStandardENDLDataGenerator.cpp
//---------------------------------------------------------------------------//
