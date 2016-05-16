//---------------------------------------------------------------------------//
//!
//! \file   tstStandardElectronPhotonRelaxationDataGenerator.cpp
//! \author Alex Robinson
//! \brief  Standard electron-photon-relaxation data generator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "DataGen_StandardElectronPhotonRelaxationDataGenerator.hpp"
#include "Data_ElectronPhotonRelaxationVolatileDataContainer.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_ENDLDataContainer.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<const DataGen::StandardElectronPhotonRelaxationDataGenerator>
  data_generator_h, data_generator_c;

Teuchos::RCP<Data::XSSEPRDataExtractor> 
  h_xss_data_extractor, c_xss_data_extractor;

Teuchos::RCP<Data::ENDLDataContainer> 
  h_endl_data_container, c_endl_data_container;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a data container can be populated
TEUCHOS_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
		   populateEPRDataContainer_h )
{
    data_generator_h.reset( 
        new DataGen::StandardElectronPhotonRelaxationDataGenerator(
                h_xss_data_extractor->extractAtomicNumber(),
                h_xss_data_extractor,
                h_endl_data_container,
                0.001,
                20.0,
                1.0e-5,
                1.0e+5,
                0.999999,  
                1e-4,
                1e-3,
                0.001,
                1e-42,
                1e-15) );

  Data::ElectronPhotonRelaxationVolatileDataContainer data_container;

  data_generator_h->populateEPRDataContainer( data_container );

  // Check the table settings data
  TEST_EQUALITY_CONST( data_container.getAtomicNumber(), 1 );
  TEST_EQUALITY_CONST( data_container.getMinPhotonEnergy(), 0.001 );
  TEST_EQUALITY_CONST( data_container.getMaxPhotonEnergy(), 20.0 );
  TEST_EQUALITY_CONST( data_container.getMinElectronEnergy(), 1.0e-5 );
  TEST_EQUALITY_CONST( data_container.getMaxElectronEnergy(), 1.0e+5 );
  TEST_EQUALITY_CONST( data_container.getCutoffAngleCosine(), 0.999999 );
  TEST_EQUALITY_CONST( 
    data_container.getOccupationNumberEvaluationTolerance(), 1e-4 );
  TEST_EQUALITY_CONST( 
    data_container.getSubshellIncoherentEvaluationTolerance(), 1e-3 );
  TEST_EQUALITY_CONST( data_container.getGridConvergenceTolerance(), 0.001 );
  TEST_EQUALITY_CONST( 
    data_container.getGridAbsoluteDifferenceTolerance(), 1e-42 );
  TEST_EQUALITY_CONST( data_container.getGridDistanceTolerance(), 1e-15 );

  // Check the relaxation data
  TEST_EQUALITY_CONST( data_container.getSubshells().size(), 1 );
  TEST_ASSERT( data_container.getSubshells().count( 1 ) );
  TEST_EQUALITY_CONST( data_container.getSubshellOccupancy( 1 ), 1 );
  TEST_EQUALITY_CONST( data_container.getSubshellBindingEnergy( 1 ),
		       1.361000000000E-05 );
  TEST_ASSERT( !data_container.hasRelaxationData() );
  TEST_ASSERT( !data_container.hasSubshellRelaxationData( 1 ) );

  // Check the photon data
  TEST_EQUALITY_CONST( data_container.getComptonProfileMomentumGrid(1).size(),
		       63 );
  TEST_EQUALITY_CONST( data_container.getComptonProfileMomentumGrid(1).front(),
		       -1.0 );
  TEST_EQUALITY_CONST( data_container.getComptonProfileMomentumGrid(1).back(),
		       1.0 );
  TEST_EQUALITY_CONST( data_container.getComptonProfile(1).size(), 63 );
  TEST_FLOATING_EQUALITY( data_container.getComptonProfile(1).front(),
			  2.22639295466368597e-09,
			  1e-15 );
  TEST_FLOATING_EQUALITY( data_container.getComptonProfile(1).back(),
			  2.22639295466368597e-09,
			  1e-15 );
  TEST_EQUALITY_CONST(data_container.getOccupationNumberMomentumGrid(1).size(),
		      409 );
  TEST_EQUALITY_CONST(
		     data_container.getOccupationNumberMomentumGrid(1).front(),
		     -1.00000000000000000e+00 );
  TEST_EQUALITY_CONST(data_container.getOccupationNumberMomentumGrid(1).back(),
		      1.00000000000000000e+00 );
  TEST_EQUALITY_CONST( data_container.getOccupationNumber(1).size(), 409 );
  TEST_EQUALITY_CONST( data_container.getOccupationNumber(1).front(), 
		       0.00000000000000000e+00 );
  TEST_EQUALITY_CONST( data_container.getOccupationNumber(1).back(),
		       1.00000000000000000e+00 );
  TEST_EQUALITY_CONST( 
	data_container.getWallerHartreeScatteringFunctionMomentumGrid().size(),
	365 );
  TEST_EQUALITY_CONST(
       data_container.getWallerHartreeScatteringFunctionMomentumGrid().front(),
       0.0 );
  TEST_FLOATING_EQUALITY(
	data_container.getWallerHartreeScatteringFunctionMomentumGrid().back(),
	1.0e+17,
	1e-15 );
  TEST_EQUALITY_CONST(
		    data_container.getWallerHartreeScatteringFunction().size(),
		    365 );
  TEST_EQUALITY_CONST( 
		   data_container.getWallerHartreeScatteringFunction().front(),
		   0.0 );
  TEST_EQUALITY_CONST(
		    data_container.getWallerHartreeScatteringFunction().back(),
		    1.0 );
  TEST_EQUALITY_CONST( 
	  data_container.getWallerHartreeAtomicFormFactorMomentumGrid().size(),
	  1583 );
  TEST_EQUALITY_CONST(
	 data_container.getWallerHartreeAtomicFormFactorMomentumGrid().front(),
	 0.0 );
  TEST_FLOATING_EQUALITY(
	  data_container.getWallerHartreeAtomicFormFactorMomentumGrid().back(),
	  1.0e+17,
	  1e-15 );
  TEST_EQUALITY_CONST(data_container.getWallerHartreeAtomicFormFactor().size(),
		      1583 );
  TEST_FLOATING_EQUALITY(
		     data_container.getWallerHartreeAtomicFormFactor().front(),
		     1.0e+00,
		     1e-15 );
  TEST_FLOATING_EQUALITY(
		      data_container.getWallerHartreeAtomicFormFactor().back(),
		      8.18290000000000004e-39,
		      1e-15 );
  TEST_EQUALITY_CONST( data_container.getPhotonEnergyGrid().size(), 727 );
  TEST_FLOATING_EQUALITY( data_container.getPhotonEnergyGrid().front(),
			  1.0e-03,
			  1e-15 );
  TEST_FLOATING_EQUALITY( data_container.getPhotonEnergyGrid().back(), 
			  2.0e+01,
			  1e-15 );
  TEST_EQUALITY_CONST( data_container.getAveragePhotonHeatingNumbers().size(), 
		       727 );
  TEST_FLOATING_EQUALITY( 
		       data_container.getAveragePhotonHeatingNumbers().front(),
		       9.44850385307779940e-04,
		       1e-15 );
  TEST_FLOATING_EQUALITY( 
			data_container.getAveragePhotonHeatingNumbers().back(),
			1.52602263568998424e+01,
			1e-15 );
  TEST_EQUALITY_CONST( 
		data_container.getWallerHartreeIncoherentCrossSection().size(),
		727 );
  TEST_FLOATING_EQUALITY(
	       data_container.getWallerHartreeIncoherentCrossSection().front(),
	       8.43429999999524560e-02,
	       1e-15 );
  TEST_FLOATING_EQUALITY(
	       data_container.getWallerHartreeIncoherentCrossSection().back(),
	       3.02353826681303964e-02,
	       1e-15 );
  TEST_EQUALITY_CONST(
   data_container.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(),
   0 );
  TEST_EQUALITY_CONST(
		data_container.getImpulseApproxIncoherentCrossSection().size(),
		727 );
  TEST_FLOATING_EQUALITY(
	       data_container.getImpulseApproxIncoherentCrossSection().front(),
	       2.31173954978115201e-02,
	       1e-15 );
  TEST_FLOATING_EQUALITY(
	        data_container.getImpulseApproxIncoherentCrossSection().back(),
		3.02498575770965353e-02,
		1e-15 );
  TEST_EQUALITY_CONST(
   data_container.getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
   0 );
  TEST_EQUALITY_CONST(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(1).size(),
       727 );
  TEST_FLOATING_EQUALITY(
      data_container.getImpulseApproxSubshellIncoherentCrossSection(1).front(),
      2.31173954978115201e-02,
      1e-15 );
  TEST_FLOATING_EQUALITY(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(1).back(),
       3.02498575770965353e-02,
       1e-15 );
  TEST_EQUALITY_CONST( data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(1),
		       0 );
  TEST_EQUALITY_CONST( 
		  data_container.getWallerHartreeCoherentCrossSection().size(),
		  727 );
  TEST_FLOATING_EQUALITY(
		 data_container.getWallerHartreeCoherentCrossSection().front(),
		 5.81790484064093394e-01,
		 1e-15 );
  TEST_FLOATING_EQUALITY(
		 data_container.getWallerHartreeCoherentCrossSection().back(),
		 1.15654029975768264e-08,
		 1e-15 );
  TEST_EQUALITY_CONST(
     data_container.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex(),
     0 );
  TEST_EQUALITY_CONST( data_container.getPairProductionCrossSection().size(),
		       296 );
  TEST_EQUALITY_CONST( data_container.getPairProductionCrossSection().front(),
		       1.00971567358274950e-10 );
  TEST_EQUALITY_CONST( data_container.getPairProductionCrossSection().back(),
		       5.65100000000240063e-03 );
  TEST_EQUALITY_CONST( 
	    data_container.getPairProductionCrossSectionThresholdEnergyIndex(),
	    431 );
  TEST_EQUALITY_CONST( data_container.getPhotoelectricCrossSection().size(),
		       727 );
  TEST_EQUALITY_CONST( data_container.getPhotoelectricCrossSection().front(),
		       1.14084154957847943e+01 );
  TEST_EQUALITY_CONST( data_container.getPhotoelectricCrossSection().back(),
		       4.05895811339709049e-11 );
  TEST_EQUALITY_CONST( 
	     data_container.getPhotoelectricCrossSectionThresholdEnergyIndex(),
	     0 );
  TEST_EQUALITY_CONST( 
		 data_container.getSubshellPhotoelectricCrossSection(1).size(),
		 727 );
  TEST_EQUALITY_CONST( 
		data_container.getSubshellPhotoelectricCrossSection(1).front(),
		1.14084154957847943e+01 );
  TEST_EQUALITY_CONST( 
		 data_container.getSubshellPhotoelectricCrossSection(1).back(),
		 4.05895811339709049e-11 );
  TEST_EQUALITY_CONST( 
    data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex(1),
    0 );
  TEST_EQUALITY_CONST( 
		     data_container.getWallerHartreeTotalCrossSection().size(),
		     727 );
  TEST_EQUALITY_CONST(
		    data_container.getWallerHartreeTotalCrossSection().front(),
		    1.20745489798488403e+01 );
  TEST_EQUALITY_CONST(
		     data_container.getWallerHartreeTotalCrossSection().back(),
		     3.58863942741253703e-02 );
  TEST_EQUALITY_CONST( 
		     data_container.getImpulseApproxTotalCrossSection().size(),
		     727 );
  TEST_EQUALITY_CONST(
		    data_container.getImpulseApproxTotalCrossSection().front(),
		    1.20133233753466993e+01 );
  TEST_EQUALITY_CONST(
		     data_container.getImpulseApproxTotalCrossSection().back(),
		     3.59008691830915092e-02 );


  std::vector<double> energy_grid = data_container.getElectronEnergyGrid();
  TEST_EQUALITY_CONST( energy_grid.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 728 );

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

//  TEST_EQUALITY_CONST( cross_section.front(), 2.5745520470700284932 );
//! \todo double check what the front cross section should be 
  TEST_EQUALITY_CONST( cross_section.front(), 2.57455204707366647 );
  TEST_EQUALITY_CONST( cross_section.back(), 1.29871e+4-1.31176e-5 );
  TEST_EQUALITY_CONST( cross_section.size(), 728-threshold );

  std::vector<double> angular_grid = 
    data_container.getElasticAngularEnergyGrid();

  TEST_EQUALITY_CONST( angular_grid.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( angular_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( angular_grid.size(), 16 );

  std::vector<double> elastic_angles = 
    data_container.getCutoffElasticAngles(1.0e-5);

  TEST_EQUALITY_CONST( elastic_angles.front(), -1.0 );
  TEST_EQUALITY_CONST( elastic_angles.back(), 0.999999 );
  TEST_EQUALITY_CONST( elastic_angles.size(), 2 );

  elastic_angles = 
    data_container.getCutoffElasticAngles(1.0e+5);

  TEST_EQUALITY_CONST( elastic_angles.front(), -1.0 );
  TEST_EQUALITY_CONST( elastic_angles.back(), 0.999999 );
  TEST_EQUALITY_CONST( elastic_angles.size(), 96 );

  std::vector<double> elastic_pdf = 
    data_container.getCutoffElasticPDF(1.0e-5);

  TEST_EQUALITY_CONST( elastic_pdf.front(), 0.5 );
  TEST_EQUALITY_CONST( elastic_pdf.back(), 0.5 );
  TEST_EQUALITY_CONST( elastic_pdf.size(), 2 );

  elastic_pdf = 
    data_container.getCutoffElasticPDF(1.0e+5);

  TEST_EQUALITY_CONST( elastic_pdf.front(), 6.25670e-13 );
  TEST_EQUALITY_CONST( elastic_pdf.back(), 9.86945e+5 );
  TEST_EQUALITY_CONST( elastic_pdf.size(), 96 );

  // Check the electroionization data
  threshold = 
    data_container.getElectroionizationCrossSectionThresholdEnergyIndex( 1u ); 

  TEST_EQUALITY_CONST( threshold, 7 );

  cross_section = 
    data_container.getElectroionizationCrossSection( 1u );

//  TEST_EQUALITY_CONST( cross_section.front(), 1.26041968911917554e+06 );
//! \todo double check what the front cross section should be 
  TEST_EQUALITY_CONST( cross_section.front(), 1.26041968911917577e+06 );
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
}

//---------------------------------------------------------------------------//
// Check that a data container can be populated
TEUCHOS_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
		   populateEPRDataContainer_c )
{
    data_generator_c.reset( 
		   new DataGen::StandardElectronPhotonRelaxationDataGenerator(
				     c_xss_data_extractor->extractAtomicNumber(),
				     c_xss_data_extractor,
                     c_endl_data_container,
				     0.001,
				     20.0,
                     1.0e-5,
                     1.0e+5,
                     0.999999,  
				     1e-3,
				     1e-3,
				     0.001,
				     1e-32,
				     1e-16) );

  Data::ElectronPhotonRelaxationVolatileDataContainer data_container;

  data_generator_c->populateEPRDataContainer( data_container );

  // Check the table settings data
  TEST_EQUALITY_CONST( data_container.getAtomicNumber(), 6 );
  TEST_EQUALITY_CONST( data_container.getMinPhotonEnergy(), 0.001 );
  TEST_EQUALITY_CONST( data_container.getMaxPhotonEnergy(), 20.0 );
  TEST_EQUALITY_CONST( data_container.getMinElectronEnergy(), 1.0e-5 );
  TEST_EQUALITY_CONST( data_container.getMaxElectronEnergy(), 1.0e+5 );
  TEST_EQUALITY_CONST( data_container.getCutoffAngleCosine(), 0.999999 );
  TEST_EQUALITY_CONST( 
    data_container.getOccupationNumberEvaluationTolerance(), 1e-3 );
  TEST_EQUALITY_CONST( 
    data_container.getSubshellIncoherentEvaluationTolerance(), 1e-3 );
  TEST_EQUALITY_CONST( data_container.getGridConvergenceTolerance(), 0.001 );
  TEST_EQUALITY_CONST( 
    data_container.getGridAbsoluteDifferenceTolerance(), 1e-32 );
  TEST_EQUALITY_CONST( data_container.getGridDistanceTolerance(), 1e-16 );

  // Check the relaxation data
  TEST_EQUALITY_CONST( data_container.getSubshells().size(), 4 );
  TEST_ASSERT( data_container.getSubshells().count( 1 ) );
  TEST_ASSERT( data_container.getSubshells().count( 2 ) );
  TEST_ASSERT( data_container.getSubshells().count( 3 ) );
  TEST_ASSERT( data_container.getSubshells().count( 4 ) );
  TEST_EQUALITY_CONST( data_container.getSubshellOccupancy( 1 ), 2 );
  TEST_EQUALITY_CONST( data_container.getSubshellOccupancy( 2 ), 2 );
  TEST_EQUALITY_CONST( data_container.getSubshellOccupancy( 3 ), 0.67 );
  TEST_EQUALITY_CONST( data_container.getSubshellOccupancy( 4 ), 1.33 );
  TEST_EQUALITY_CONST( data_container.getSubshellBindingEnergy( 1 ),
		       2.9101e-4 );
  TEST_EQUALITY_CONST( data_container.getSubshellBindingEnergy( 2 ),
		       1.7560e-5 );
  TEST_EQUALITY_CONST( data_container.getSubshellBindingEnergy( 3 ),
		       8.9900e-6 );
  TEST_EQUALITY_CONST( data_container.getSubshellBindingEnergy( 4 ),
		       8.9800e-6 );
  TEST_ASSERT( data_container.hasRelaxationData() );
  TEST_ASSERT( data_container.hasSubshellRelaxationData( 1 ) );
  TEST_ASSERT( !data_container.hasSubshellRelaxationData( 2 ) );
  TEST_ASSERT( !data_container.hasSubshellRelaxationData( 3 ) );
  TEST_ASSERT( !data_container.hasSubshellRelaxationData( 4 ) );
  TEST_EQUALITY_CONST( data_container.getSubshellRelaxationTransitions( 1 ),
		       8 );
  TEST_EQUALITY_CONST(
		     data_container.getSubshellRelaxationVacancies(1).size(),
		     8 );
  TEST_EQUALITY_CONST(
		data_container.getSubshellRelaxationVacancies(1).front().first,
		3 );
  TEST_EQUALITY_CONST(
	       data_container.getSubshellRelaxationVacancies(1).front().second,
	       0 );
  TEST_EQUALITY_CONST(
		 data_container.getSubshellRelaxationVacancies(1).back().first,
		 4 );
  TEST_EQUALITY_CONST(
	        data_container.getSubshellRelaxationVacancies(1).back().second,
		4 );   
  TEST_EQUALITY_CONST( 
		data_container.getSubshellRelaxationParticleEnergies(1).size(),
		8 );
  TEST_FLOATING_EQUALITY(
	       data_container.getSubshellRelaxationParticleEnergies(1).front(),
	       2.8202e-4,
	       1e-15 );
  TEST_FLOATING_EQUALITY(
		data_container.getSubshellRelaxationParticleEnergies(1).back(),
		2.7305e-4,
		1e-15 );
  TEST_EQUALITY_CONST(
		   data_container.getSubshellRelaxationProbabilities(1).size(),
		   8 );
  TEST_FLOATING_EQUALITY(
		  data_container.getSubshellRelaxationProbabilities(1).front(),
		  5.614877933725e-04,
		  1e-15 );
  TEST_FLOATING_EQUALITY(
		   data_container.getSubshellRelaxationProbabilities(1).back(),
		   6.32007767421e-02,
		   1e-15 );

  // Check the photon data
  TEST_EQUALITY_CONST( data_container.getComptonProfileMomentumGrid(1).size(),
		       63 );
  TEST_EQUALITY_CONST( data_container.getComptonProfileMomentumGrid(1).front(),
		       -1.0 );
  TEST_EQUALITY_CONST( data_container.getComptonProfileMomentumGrid(1).back(),
		       1.0 );
  TEST_EQUALITY_CONST( data_container.getComptonProfileMomentumGrid(2).size(),
		       63 );
  TEST_EQUALITY_CONST( data_container.getComptonProfileMomentumGrid(2).front(),
		       -1.0 );
  TEST_EQUALITY_CONST( data_container.getComptonProfileMomentumGrid(2).back(),
		       1.0 );
  TEST_EQUALITY_CONST( data_container.getComptonProfileMomentumGrid(3).size(),
		       63 );
  TEST_EQUALITY_CONST( data_container.getComptonProfileMomentumGrid(3).front(),
		       -1.0 );
  TEST_EQUALITY_CONST( data_container.getComptonProfileMomentumGrid(3).back(),
		       1.0 );
  TEST_EQUALITY_CONST( data_container.getComptonProfileMomentumGrid(4).size(),
		       63 );
  TEST_EQUALITY_CONST( data_container.getComptonProfileMomentumGrid(4).front(),
		       -1.0 );
  TEST_EQUALITY_CONST( data_container.getComptonProfileMomentumGrid(4).back(),
		       1.0 );
  TEST_EQUALITY_CONST( data_container.getComptonProfile(1).size(), 63 );
  TEST_FLOATING_EQUALITY( data_container.getComptonProfile(1).front(), 
			  4.76097080587270975e-08,
			  1e-15 );
  TEST_FLOATING_EQUALITY( data_container.getComptonProfile(1).back(),
			  4.76097080587270975e-08,
			  1e-15 );
  TEST_EQUALITY_CONST( data_container.getComptonProfile(2).size(), 63 );
  TEST_FLOATING_EQUALITY( data_container.getComptonProfile(2).front(), 
			  2.22296325751965260e-09,
			  1e-15 );
  TEST_FLOATING_EQUALITY( data_container.getComptonProfile(2).back(), 
			  2.22296325751965260e-09,
			  1e-15 );
  TEST_EQUALITY_CONST( data_container.getComptonProfile(3).size(), 63 );
  TEST_FLOATING_EQUALITY( data_container.getComptonProfile(3).front(), 
			  2.46239765051693239e-13,
			  1e-15 );
  TEST_FLOATING_EQUALITY( data_container.getComptonProfile(3).back(), 
			  2.46239765051693239e-13,
			  1e-15 );
  TEST_EQUALITY_CONST( data_container.getComptonProfile(4).size(), 63 );
  TEST_FLOATING_EQUALITY( data_container.getComptonProfile(4).front(),
			  2.46239765051693239e-13,
			  1e-15 );
  TEST_FLOATING_EQUALITY( data_container.getComptonProfile(4).back(), 
			  2.46239765051693239e-13,
			  1e-15 );
  TEST_EQUALITY_CONST(data_container.getOccupationNumberMomentumGrid(1).size(),
		      440 );
  TEST_EQUALITY_CONST(
		     data_container.getOccupationNumberMomentumGrid(1).front(),
		     -1.0 );
  TEST_EQUALITY_CONST(data_container.getOccupationNumberMomentumGrid(1).back(),
		      1.0 );
  TEST_EQUALITY_CONST(data_container.getOccupationNumberMomentumGrid(2).size(),
		      399 );
  TEST_EQUALITY_CONST(
		     data_container.getOccupationNumberMomentumGrid(2).front(),
		     -1.0 );
  TEST_EQUALITY_CONST(data_container.getOccupationNumberMomentumGrid(2).back(),
		      1.0 );
  TEST_EQUALITY_CONST(data_container.getOccupationNumberMomentumGrid(3).size(),
		      573 );
  TEST_EQUALITY_CONST(
		     data_container.getOccupationNumberMomentumGrid(3).front(),
		     -1.0 );
  TEST_EQUALITY_CONST(data_container.getOccupationNumberMomentumGrid(3).back(),
		      1.0 );
  TEST_EQUALITY_CONST(data_container.getOccupationNumberMomentumGrid(4).size(),
		      573 );
  TEST_EQUALITY_CONST(
		     data_container.getOccupationNumberMomentumGrid(4).front(),
		     -1.0 );
  TEST_EQUALITY_CONST(data_container.getOccupationNumber(4).back(),
		      1.0 );
  TEST_EQUALITY_CONST( data_container.getOccupationNumber(1).size(), 440 );
  TEST_EQUALITY_CONST( data_container.getOccupationNumber(1).front(),
		       0.0 );
  TEST_EQUALITY_CONST( data_container.getOccupationNumber(1).back(),
		       1.0 );
  TEST_EQUALITY_CONST( data_container.getOccupationNumber(2).size(), 399 );
  TEST_EQUALITY_CONST( data_container.getOccupationNumber(2).front(),
		       0.0 );
  TEST_EQUALITY_CONST( data_container.getOccupationNumber(2).back(),
		       1.0 );
  TEST_EQUALITY_CONST( data_container.getOccupationNumber(3).size(), 573 );
  TEST_EQUALITY_CONST( data_container.getOccupationNumber(3).front(),
		       0.0 );
  TEST_EQUALITY_CONST( data_container.getOccupationNumber(3).back(),
		       1.0 );
  TEST_EQUALITY_CONST( data_container.getOccupationNumber(4).size(), 573 );
  TEST_EQUALITY_CONST( data_container.getOccupationNumber(4).front(),
		       0.0 );
  TEST_EQUALITY_CONST( data_container.getOccupationNumber(4).back(),
		       1.0 );
  TEST_EQUALITY_CONST( 
	data_container.getWallerHartreeScatteringFunctionMomentumGrid().size(),
	379 );
  TEST_EQUALITY_CONST(
       data_container.getWallerHartreeScatteringFunctionMomentumGrid().front(),
       0.0 );
  TEST_EQUALITY_CONST(
	data_container.getWallerHartreeScatteringFunctionMomentumGrid().back(),
	1e17 );  
  TEST_EQUALITY_CONST( 
		    data_container.getWallerHartreeScatteringFunction().size(),
		    379 );
  TEST_EQUALITY_CONST(
		   data_container.getWallerHartreeScatteringFunction().front(),
		   0.0 );
  TEST_EQUALITY_CONST(
		    data_container.getWallerHartreeScatteringFunction().back(),
		    6.0 );  
  TEST_EQUALITY_CONST( 
	  data_container.getWallerHartreeAtomicFormFactorMomentumGrid().size(),
	  1259 );
  TEST_EQUALITY_CONST(
	 data_container.getWallerHartreeAtomicFormFactorMomentumGrid().front(),
	 0.0 );
  TEST_EQUALITY_CONST(
	  data_container.getWallerHartreeAtomicFormFactorMomentumGrid().back(),
	  1e17 );
  TEST_EQUALITY_CONST(data_container.getWallerHartreeAtomicFormFactor().size(),
		      1259 );
  TEST_EQUALITY_CONST(
		     data_container.getWallerHartreeAtomicFormFactor().front(),
		     6.0 );
  TEST_FLOATING_EQUALITY(
		      data_container.getWallerHartreeAtomicFormFactor().back(),
		      1.68099999999999989e-29,
		      1e-15 );
  TEST_EQUALITY_CONST( data_container.getPhotonEnergyGrid().size(), 775 );
  TEST_EQUALITY_CONST( data_container.getPhotonEnergyGrid().front(), 
		       0.001 );
  TEST_EQUALITY_CONST( data_container.getPhotonEnergyGrid().back(),
		       20.0 );
  TEST_EQUALITY_CONST( data_container.getAveragePhotonHeatingNumbers().size(),
		       775 );
  TEST_FLOATING_EQUALITY( 
		       data_container.getAveragePhotonHeatingNumbers().front(),
		       9.99436862257738331e-04,
		       1e-15 );
  TEST_FLOATING_EQUALITY( 
			data_container.getAveragePhotonHeatingNumbers().back(),
			1.64023854081998266e+01,
			1e-15 );
  TEST_EQUALITY_CONST( 
		data_container.getWallerHartreeIncoherentCrossSection().size(),
		775 );
  TEST_FLOATING_EQUALITY( 
	       data_container.getWallerHartreeIncoherentCrossSection().front(),
	       2.52250000000042829e-01,
	       1e-15 );
  TEST_FLOATING_EQUALITY( 
		data_container.getWallerHartreeIncoherentCrossSection().back(),
		1.81486137923699387e-01,
		1e-15 );
  TEST_EQUALITY_CONST(
   data_container.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(),
   0 );
  TEST_EQUALITY_CONST(
		data_container.getImpulseApproxIncoherentCrossSection().size(),
		775 );
  TEST_FLOATING_EQUALITY(
	       data_container.getImpulseApproxIncoherentCrossSection().front(),
	       2.68987545509888737e-01,
	       1e-15 );
  TEST_FLOATING_EQUALITY(
	        data_container.getImpulseApproxIncoherentCrossSection().back(),
		1.81499083920329374e-01,
		1e-15 );
  TEST_EQUALITY_CONST( 
   data_container.getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
   0 );
  TEST_EQUALITY_CONST(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(1).size(),
       775 );
  TEST_FLOATING_EQUALITY(
      data_container.getImpulseApproxSubshellIncoherentCrossSection(1).front(),
      6.79748251620507996e-05,
      1e-15 );
  TEST_FLOATING_EQUALITY(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(1).back(),
       6.04996536119432188e-02,
       1e-15 );
  TEST_EQUALITY_CONST( data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(1),
		       0 );
  TEST_EQUALITY_CONST(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(2).size(),
       775 );
  TEST_FLOATING_EQUALITY(
      data_container.getImpulseApproxSubshellIncoherentCrossSection(2).front(),
      3.49837183987976100e-02,
      1e-15 );
  TEST_FLOATING_EQUALITY(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(2).back(),
       6.04997151541930706e-02,
       1e-15 );
  TEST_EQUALITY_CONST( data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(2),
		       0 );
  TEST_EQUALITY_CONST(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(3).size(),
       775 );
  TEST_FLOATING_EQUALITY(
      data_container.getImpulseApproxSubshellIncoherentCrossSection(3).front(),
      7.82914016886618047e-02,
      1e-15 );
  TEST_FLOATING_EQUALITY(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(3).back(),
       2.02674045766546781e-02,
       1e-15 );
  TEST_EQUALITY_CONST( data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(3),
		       0 );
  TEST_EQUALITY_CONST(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(4).size(),
       775 );
  TEST_FLOATING_EQUALITY(
      data_container.getImpulseApproxSubshellIncoherentCrossSection(4).front(),
      1.55644450597267281e-01,
      1e-15 );
  TEST_FLOATING_EQUALITY(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(4).back(),
       4.02323105775383924e-02,
       1e-15 );
  TEST_EQUALITY_CONST( data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(4),
		       0 );
  TEST_EQUALITY_CONST( 
		  data_container.getWallerHartreeCoherentCrossSection().size(),
		  775 );
  TEST_FLOATING_EQUALITY( 
		 data_container.getWallerHartreeCoherentCrossSection().front(),
		 2.45600299049398139e+01,
		 1e-15 );
  TEST_FLOATING_EQUALITY( 
		  data_container.getWallerHartreeCoherentCrossSection().back(),
		  1.92198769740615498e-06,
		  1e-15 );
  TEST_EQUALITY_CONST( 
     data_container.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex(),
     0 );
  TEST_EQUALITY_CONST( data_container.getPairProductionCrossSection().size(),
		       280 );
  TEST_FLOATING_EQUALITY( 
			data_container.getPairProductionCrossSection().front(),
			3.71284984483754554e-09,
			1e-15 );
  TEST_FLOATING_EQUALITY(data_container.getPairProductionCrossSection().back(),
			 1.31849999999978429e-01,
			 1e-15 );
  TEST_EQUALITY_CONST( 
	    data_container.getPairProductionCrossSectionThresholdEnergyIndex(),
	    495 );
  TEST_EQUALITY_CONST( data_container.getPhotoelectricCrossSection().size(),
		       775 ); 
  TEST_FLOATING_EQUALITY(data_container.getPhotoelectricCrossSection().front(),
			 4.40346567781178965e+04,
			 1e-15 ); 
  TEST_FLOATING_EQUALITY( data_container.getPhotoelectricCrossSection().back(),
			  4.78641586632171115e-07,
			  1e-15 ); 
  TEST_EQUALITY_CONST( 
	     data_container.getPhotoelectricCrossSectionThresholdEnergyIndex(),
	     0 ); 
  TEST_EQUALITY_CONST(
		 data_container.getSubshellPhotoelectricCrossSection(1).size(),
		 775 );
  TEST_FLOATING_EQUALITY(
		data_container.getSubshellPhotoelectricCrossSection(1).front(),
		4.20106634766030475e+04,
		1e-15 );
  TEST_FLOATING_EQUALITY(
		 data_container.getSubshellPhotoelectricCrossSection(1).back(),
		 4.54467548753621960e-07,
		 1e-15 );
  TEST_EQUALITY_CONST(
    data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex(1),
    0 );
  TEST_EQUALITY_CONST(
		 data_container.getSubshellPhotoelectricCrossSection(2).size(),
		 775 );
  TEST_FLOATING_EQUALITY(
		data_container.getSubshellPhotoelectricCrossSection(2).front(),
		1.92946542999592748e+03,
		1e-15 );
  TEST_FLOATING_EQUALITY(
		 data_container.getSubshellPhotoelectricCrossSection(2).back(),
		 2.41672669261238441e-08,
		 1e-15 );
  TEST_EQUALITY_CONST(
    data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex(2),
    0 );
  TEST_EQUALITY_CONST(
		 data_container.getSubshellPhotoelectricCrossSection(3).size(),
		 775 );
  TEST_FLOATING_EQUALITY(
		data_container.getSubshellPhotoelectricCrossSection(3).front(),
		3.16445995519961478e+01,
		1e-15 );
  TEST_FLOATING_EQUALITY(
		 data_container.getSubshellPhotoelectricCrossSection(3).back(),
		 2.04871323525023182e-12,
		 1e-15 );
  TEST_EQUALITY_CONST(
    data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex(3),
    0 );
  TEST_EQUALITY_CONST(
		 data_container.getSubshellPhotoelectricCrossSection(4).size(),
		 775 );
  TEST_FLOATING_EQUALITY(
		data_container.getSubshellPhotoelectricCrossSection(4).front(),
		6.28832719669201197e+01,
		1e-15 );
  TEST_FLOATING_EQUALITY(
		 data_container.getSubshellPhotoelectricCrossSection(4).back(),
		 4.72223919011517413e-12,
		 1e-15 );
  TEST_EQUALITY_CONST(
    data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex(4),
    0 );
  TEST_EQUALITY_CONST(
		     data_container.getWallerHartreeTotalCrossSection().size(),
		     775 );
  TEST_FLOATING_EQUALITY(
		    data_container.getWallerHartreeTotalCrossSection().front(),
		    4.40594690580228344e+04,
		    1e-15 );
  TEST_FLOATING_EQUALITY(
		     data_container.getWallerHartreeTotalCrossSection().back(),
		     3.13338538552961843e-01,
		     1e-15 );
  TEST_EQUALITY_CONST(
		     data_container.getImpulseApproxTotalCrossSection().size(),
		     775 );
  TEST_FLOATING_EQUALITY(
		    data_container.getImpulseApproxTotalCrossSection().front(),
		    4.40594857955683474e+04,
		    1e-15 );
  TEST_FLOATING_EQUALITY(
		     data_container.getImpulseApproxTotalCrossSection().back(),
		     3.13351484549591885e-01,
		     1e-15 );

  // Check the electron energy grid data
  std::vector<double> energy_grid = data_container.getElectronEnergyGrid();
  TEST_EQUALITY_CONST( energy_grid.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( energy_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( energy_grid.size(), 723 );

  // Check the elastic data
  unsigned threshold = 
    data_container.getCutoffElasticCrossSectionThresholdEnergyIndex(); 

  TEST_EQUALITY_CONST( threshold, 0 );

  std::vector<double> cross_section = 
    data_container.getCutoffElasticCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 3.06351e+9 );
  TEST_FLOATING_EQUALITY( cross_section.back(), 4.72309e-4, 1e-15 );
  TEST_EQUALITY_CONST( cross_section.size(), 723-threshold );

  threshold = 
    data_container.getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(); 

  TEST_EQUALITY_CONST( threshold, 276 );

  cross_section = 
    data_container.getScreenedRutherfordElasticCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 1.93634596180636436e+01 );
  TEST_EQUALITY_CONST( cross_section.back(), 1.407220E+05-4.723090E-04 );
  TEST_EQUALITY_CONST( cross_section.size(), 723-threshold );

  std::vector<double> angular_grid = 
    data_container.getElasticAngularEnergyGrid();

  TEST_EQUALITY_CONST( angular_grid.front(), 1.0e-5 );
  TEST_EQUALITY_CONST( angular_grid.back(), 1.0e+5 );
  TEST_EQUALITY_CONST( angular_grid.size(), 16 );

  std::vector<double> elastic_angles = 
    data_container.getCutoffElasticAngles(1.0e-5);

  TEST_EQUALITY_CONST( elastic_angles.front(), -1.0 );
  TEST_EQUALITY_CONST( elastic_angles.back(), 0.999999 );
  TEST_EQUALITY_CONST( elastic_angles.size(), 2 );

  elastic_angles = 
    data_container.getCutoffElasticAngles(1.0e+5);

  TEST_EQUALITY_CONST( elastic_angles.front(), -1.0 );
  TEST_EQUALITY_CONST( elastic_angles.back(), 0.999999 );
  TEST_EQUALITY_CONST( elastic_angles.size(), 96 );

  std::vector<double> elastic_pdf = 
    data_container.getCutoffElasticPDF(1.0e-5);

  TEST_EQUALITY_CONST( elastic_pdf.front(), 0.5 );
  TEST_EQUALITY_CONST( elastic_pdf.back(), 0.5 );
  TEST_EQUALITY_CONST( elastic_pdf.size(), 2 );

  elastic_pdf = 
    data_container.getCutoffElasticPDF(1.0e+5);

  TEST_EQUALITY_CONST( elastic_pdf.front(), 1.693970E-11 );
  TEST_EQUALITY_CONST( elastic_pdf.back(), 9.868670E+05 );
  TEST_EQUALITY_CONST( elastic_pdf.size(), 96 );

  // Check the electroionization data
  threshold = 
    data_container.getElectroionizationCrossSectionThresholdEnergyIndex( 1u ); 

  TEST_EQUALITY_CONST( threshold, 85 );

  cross_section = 
    data_container.getElectroionizationCrossSection( 1u );

  TEST_EQUALITY_CONST( cross_section.front(), 1.10703713515228592e+04 );
  TEST_EQUALITY_CONST( cross_section.back(), 1.338050E+04 );
  TEST_EQUALITY_CONST( cross_section.size(), 723-threshold );

  std::vector<double> electroionization_energy_grid =  
    data_container.getElectroionizationEnergyGrid( 1u );

  TEST_EQUALITY_CONST( electroionization_energy_grid.front(), 2.910100E-04 );
  TEST_EQUALITY_CONST( electroionization_energy_grid.back(), 1.00000e+5 );
  TEST_EQUALITY_CONST( electroionization_energy_grid.size(), 7 );

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


  threshold = 
    data_container.getElectroionizationCrossSectionThresholdEnergyIndex( 4u ); 

  TEST_EQUALITY_CONST( threshold, 0 );

  cross_section = 
    data_container.getElectroionizationCrossSection( 4u );

  TEST_EQUALITY_CONST( cross_section.front(), 2.102930E+07 );
  TEST_EQUALITY_CONST( cross_section.back(), 2.017010E+05 );
  TEST_EQUALITY_CONST( cross_section.size(), 723-threshold );

  electroionization_energy_grid =  
    data_container.getElectroionizationEnergyGrid( 4u );

  TEST_EQUALITY_CONST( electroionization_energy_grid.front(), 8.980000E-06 );
  TEST_EQUALITY_CONST( electroionization_energy_grid.back(), 1.00000e+5 );
  TEST_EQUALITY_CONST( electroionization_energy_grid.size(), 8 );

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

  // Check the bremsstrahlung data
  threshold = 
    data_container.getBremsstrahlungCrossSectionThresholdEnergyIndex(); 

  TEST_EQUALITY_CONST( threshold, 0 );

  cross_section = 
    data_container.getBremsstrahlungCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 6.031280E+02 );
  TEST_EQUALITY_CONST( cross_section.back(), 1.697150E+01 );
  TEST_EQUALITY_CONST( cross_section.size(), 723-threshold );

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

  // Check the atomic excitation data
  threshold = 
    data_container.getAtomicExcitationCrossSectionThresholdEnergyIndex(); 

  TEST_EQUALITY_CONST( threshold, 0 );

  cross_section = 
    data_container.getAtomicExcitationCrossSection();

  TEST_EQUALITY_CONST( cross_section.front(), 3.168630E+06 );
  TEST_EQUALITY_CONST( cross_section.back(), 1.198920E+05 );
  TEST_EQUALITY_CONST( cross_section.size(), 723-threshold );

  std::vector<double> atomic_excitation_energy_grid =  
    data_container.getAtomicExcitationEnergyGrid();

  TEST_EQUALITY_CONST( atomic_excitation_energy_grid.front(), 1.00000e-5 );
  TEST_EQUALITY_CONST( atomic_excitation_energy_grid.back(), 1.00000e+5 );
  TEST_EQUALITY_CONST( atomic_excitation_energy_grid.size(), 181 );

  std::vector<double> atomic_excitation_energy_loss =  
    data_container.getAtomicExcitationEnergyLoss();

  TEST_EQUALITY_CONST( atomic_excitation_energy_loss.front(), 9.232690E-06 );
  TEST_EQUALITY_CONST( atomic_excitation_energy_loss.back(), 1.981540E-05 );
  TEST_EQUALITY_CONST( atomic_excitation_energy_loss.size(), 181 );

  data_container.exportData( "test_c_epr.xml",
			     Utility::ArchivableObject::XML_ARCHIVE );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_h_ace_file_name, test_h_ace_table_name;
  std::string test_c_ace_file_name, test_c_ace_table_name;
  std::string test_h_endl_file_name, test_c_endl_file_name;
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_h_ace_file",
		 &test_h_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_h_ace_table",
		 &test_h_ace_table_name,
		 "Test ACE table name" );
  clp.setOption( "test_h_endl_file",
		 &test_h_endl_file_name,
		 "Test ENDL file name" );

  clp.setOption( "test_c_ace_file",
		 &test_c_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_c_ace_table",
		 &test_c_ace_table_name,
		 "Test ACE table name" );
  clp.setOption( "test_c_endl_file",
		 &test_c_endl_file_name,
		 "Test ENDL file name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  
  {
    // Create the file handler and data extractor for hydrogen
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
    // Create the file handler and data extractor for carbon
    Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
			       new Data::ACEFileHandler( test_c_ace_file_name,
							 test_c_ace_table_name,
							 1u ) );

    c_xss_data_extractor.reset(
				new Data::XSSEPRDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );
  }

  {
    // Create the endl data container for hydrogen
    h_endl_data_container.reset(
        new Data::ENDLDataContainer( 
            test_h_endl_file_name,
            Utility::ArchivableObject::XML_ARCHIVE ) );
  }

  {
    c_endl_data_container.reset(
        new Data::ENDLDataContainer( 
            test_c_endl_file_name,
            Utility::ArchivableObject::XML_ARCHIVE ) );
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
// end tstStandardElectronPhotonRelaxationDataGenerator.cpp
//---------------------------------------------------------------------------//
