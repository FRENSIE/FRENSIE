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
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_UnitTestHarnessExtensions.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<const DataGen::StandardElectronPhotonRelaxationDataGenerator>
  data_generator_h, data_generator_c;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that a data container can be populated
TEUCHOS_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
		   populateEPRDataContainer_h )
{
  Data::ElectronPhotonRelaxationVolatileDataContainer data_container;

  data_generator_h->populateEPRDataContainer( data_container );

  TEST_EQUALITY_CONST( data_container.getAtomicNumber(), 1 );
  TEST_EQUALITY_CONST( data_container.getSubshells().size(), 1 );
  TEST_ASSERT( data_container.getSubshells().count( 1 ) );
  TEST_EQUALITY_CONST( data_container.getSubshellOccupancy( 1 ), 1 );
  TEST_EQUALITY_CONST( data_container.getSubshellBindingEnergy( 1 ),
		       1.361000000000E-05 );
  TEST_ASSERT( !data_container.hasRelaxationData() );
  TEST_ASSERT( !data_container.hasSubshellRelaxationData( 1 ) );
  TEST_EQUALITY_CONST( data_container.getComptonProfileMomentumGrid(1).size(),
		       63 );
  TEST_EQUALITY_CONST( data_container.getComptonProfileMomentumGrid(1).front(),
		       -1.0 );
  TEST_EQUALITY_CONST( data_container.getComptonProfileMomentumGrid(1).back(),
		       1.0 );
  TEST_EQUALITY_CONST( data_container.getComptonProfile(1).size(), 63 );
  TEST_EQUALITY_CONST( data_container.getComptonProfile(1).front(),
		       2.22639294755138069e-09 );
  TEST_EQUALITY_CONST( data_container.getComptonProfile(1).back(),
		       2.22639294755138069e-09 );
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
  TEST_EQUALITY_CONST(
	data_container.getWallerHartreeScatteringFunctionMomentumGrid().back(),
	1.00000000000000000e+17 );
  TEST_EQUALITY_CONST(
		    data_container.getWallerHartreeScatteringFunction().size(),
		    365 );
  TEST_EQUALITY_CONST( 
		   data_container.getWallerHartreeScatteringFunction().front(),
		   0.0 );
  TEST_EQUALITY_CONST(
		    data_container.getWallerHartreeScatteringFunction().back(),
		    1.00000000000000000e+00 );
  TEST_EQUALITY_CONST( 
	  data_container.getWallerHartreeAtomicFormFactorMomentumGrid().size(),
	  1583 );
  TEST_EQUALITY_CONST(
	 data_container.getWallerHartreeAtomicFormFactorMomentumGrid().front(),
	 0.0 );
  TEST_EQUALITY_CONST(
	  data_container.getWallerHartreeAtomicFormFactorMomentumGrid().back(),
	  1.00000000000000000e+17 );
  TEST_EQUALITY_CONST(data_container.getWallerHartreeAtomicFormFactor().size(),
		      1583 );
  TEST_EQUALITY_CONST(
		     data_container.getWallerHartreeAtomicFormFactor().front(),
		     1.00000000000000000e+00 );
  TEST_EQUALITY_CONST(data_container.getWallerHartreeAtomicFormFactor().back(),
		      8.18290000000000004e-39 );
  TEST_EQUALITY_CONST( data_container.getPhotonEnergyGrid().size(), 727 );
  TEST_EQUALITY_CONST( data_container.getPhotonEnergyGrid().front(),
		       1.00000000000000002e-03 );
  TEST_EQUALITY_CONST( data_container.getPhotonEnergyGrid().back(), 
		       2.00000000000000000e+01 );
  TEST_EQUALITY_CONST( data_container.getAveragePhotonHeatingNumbers().size(), 
		       727 );
  TEST_EQUALITY_CONST( data_container.getAveragePhotonHeatingNumbers().front(),
		       9.44850385307779940e-04 );
  TEST_EQUALITY_CONST( data_container.getAveragePhotonHeatingNumbers().back(),
		       1.52602263568998424e+01 );
  TEST_EQUALITY_CONST( 
		data_container.getWallerHartreeIncoherentCrossSection().size(),
		727 );
  TEST_EQUALITY_CONST(
	       data_container.getWallerHartreeIncoherentCrossSection().front(),
	       8.43429999999524560e-02 );
  TEST_EQUALITY_CONST(
	       data_container.getWallerHartreeIncoherentCrossSection().back(),
	       3.02353826681303964e-02 );
  TEST_EQUALITY_CONST(
   data_container.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(),
   0 );
  TEST_EQUALITY_CONST(
		data_container.getImpulseApproxIncoherentCrossSection().size(),
		727 );
  TEST_EQUALITY_CONST(
	       data_container.getImpulseApproxIncoherentCrossSection().front(),
	       2.31173952527717226e-02 );
  TEST_EQUALITY_CONST(
	        data_container.getImpulseApproxIncoherentCrossSection().back(),
		3.02498575770965249e-02 );
  TEST_EQUALITY_CONST(
   data_container.getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
   0 );
  TEST_EQUALITY_CONST(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(1).size(),
       727 );
  TEST_EQUALITY_CONST(
      data_container.getImpulseApproxSubshellIncoherentCrossSection(1).front(),
      2.31173952527717226e-02 );
  TEST_EQUALITY_CONST(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(1).back(),
       3.02498575770965249e-02 );
  TEST_EQUALITY_CONST( data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(1),
		       0 );
  TEST_EQUALITY_CONST( 
		  data_container.getWallerHartreeCoherentCrossSection().size(),
		  727 );
  TEST_EQUALITY_CONST(
		 data_container.getWallerHartreeCoherentCrossSection().front(),
		 5.81790484064093394e-01 );
  TEST_EQUALITY_CONST(
		 data_container.getWallerHartreeCoherentCrossSection().back(),
		 1.15654029975768264e-08 );
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
		    1.20133233751016597e+01 );
  TEST_EQUALITY_CONST(
		     data_container.getImpulseApproxTotalCrossSection().back(),
		     3.59008691830915022e-02 );

  data_container.exportData( "test_h_epr.xml",
			     Utility::ArchivableObject::XML_ARCHIVE );
}

//---------------------------------------------------------------------------//
// Check that a data container can be populated
TEUCHOS_UNIT_TEST( StandardElectronPhotonRelaxationDataGenerator,
		   populateEPRDataContainer_c )
{
  Data::ElectronPhotonRelaxationVolatileDataContainer data_container;

  data_generator_c->populateEPRDataContainer( data_container );

  TEST_EQUALITY_CONST( data_container.getAtomicNumber(), 6 );
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
  TEST_EQUALITY_CONST(
	       data_container.getSubshellRelaxationParticleEnergies(1).front(),
	       2.8202e-4 );
  TEST_EQUALITY_CONST(
		data_container.getSubshellRelaxationParticleEnergies(1).back(),
		2.7305e-4 );
  TEST_EQUALITY_CONST(
		   data_container.getSubshellRelaxationProbabilities(1).size(),
		   8 );
  TEST_EQUALITY_CONST(
		  data_container.getSubshellRelaxationProbabilities(1).front(),
		  5.614877933725e-04 );
  TEST_EQUALITY_CONST(
		   data_container.getSubshellRelaxationProbabilities(1).back(),
		   6.32007767421e-02 );
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
  TEST_EQUALITY_CONST( data_container.getComptonProfile(1).front(), 
		       4.76097060872893390e-08 );
  TEST_EQUALITY_CONST( data_container.getComptonProfile(1).back(),
		       4.76097060872893390e-08 );
  TEST_EQUALITY_CONST( data_container.getComptonProfile(2).size(), 63 );
  TEST_EQUALITY_CONST( data_container.getComptonProfile(2).front(), 
		       2.22296316538757494e-09 );
  TEST_EQUALITY_CONST( data_container.getComptonProfile(2).back(), 
		       2.22296316538757494e-09 );
  TEST_EQUALITY_CONST( data_container.getComptonProfile(3).size(), 63 );
  TEST_EQUALITY_CONST( data_container.getComptonProfile(3).front(), 
		       2.46239750889935041e-13 );
  TEST_EQUALITY_CONST( data_container.getComptonProfile(3).back(), 
		       2.46239750889935041e-13 );
  TEST_EQUALITY_CONST( data_container.getComptonProfile(4).size(), 63 );
  TEST_EQUALITY_CONST( data_container.getComptonProfile(4).front(),
		       2.46239750889935041e-13 );
  TEST_EQUALITY_CONST( data_container.getComptonProfile(4).back(), 
		       2.46239750889935041e-13 );
  TEST_EQUALITY_CONST(data_container.getOccupationNumberMomentumGrid(1).size(),
		      442 );
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
  TEST_EQUALITY_CONST( data_container.getOccupationNumber(1).size(), 442 );
  TEST_EQUALITY_CONST( data_container.getOccupationNumber(1).front(),
		       0.0 );
  TEST_EQUALITY_CONST( data_container.getOccupationNumber(1).back(),
		       9.99999999999999556e-01 );
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
  TEST_EQUALITY_CONST(data_container.getWallerHartreeAtomicFormFactor().back(),
		      1.68099999999999989e-29 );
  TEST_EQUALITY_CONST( data_container.getPhotonEnergyGrid().size(), 775 );
  TEST_EQUALITY_CONST( data_container.getPhotonEnergyGrid().front(), 
		       0.001 );
  TEST_EQUALITY_CONST( data_container.getPhotonEnergyGrid().back(),
		       20.0 );
  TEST_EQUALITY_CONST( data_container.getAveragePhotonHeatingNumbers().size(),
		       775 );
  TEST_EQUALITY_CONST( data_container.getAveragePhotonHeatingNumbers().front(),
		       9.99436862257738331e-04 );
  TEST_EQUALITY_CONST( data_container.getAveragePhotonHeatingNumbers().back(),
		       1.64023854081998266e+01 );
  TEST_EQUALITY_CONST( 
		data_container.getWallerHartreeIncoherentCrossSection().size(),
		775 );
  TEST_EQUALITY_CONST( 
	       data_container.getWallerHartreeIncoherentCrossSection().front(),
	       2.52250000000042829e-01 );
  TEST_EQUALITY_CONST( 
		data_container.getWallerHartreeIncoherentCrossSection().back(),
		1.81486137923699387e-01 );
  TEST_EQUALITY_CONST(
   data_container.getWallerHartreeIncoherentCrossSectionThresholdEnergyIndex(),
   0 );
  TEST_EQUALITY_CONST(
		data_container.getImpulseApproxIncoherentCrossSection().size(),
		775 );
  TEST_EQUALITY_CONST(
	       data_container.getImpulseApproxIncoherentCrossSection().front(),
	       2.68987544277024648e-01 );
  TEST_EQUALITY_CONST(
	        data_container.getImpulseApproxIncoherentCrossSection().back(),
		1.81499083920324933e-01 );
  TEST_EQUALITY_CONST( 
   data_container.getImpulseApproxIncoherentCrossSectionThresholdEnergyIndex(),
   0 );
  TEST_EQUALITY_CONST(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(1).size(),
       775 );
  TEST_EQUALITY_CONST(
      data_container.getImpulseApproxSubshellIncoherentCrossSection(1).front(),
      6.79748237018359838e-05 );
  TEST_EQUALITY_CONST(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(1).back(),
       6.04996536119388195e-02 );
  TEST_EQUALITY_CONST( data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(1),
		       0 );
  TEST_EQUALITY_CONST(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(2).size(),
       775 );
  TEST_EQUALITY_CONST(
      data_container.getImpulseApproxSubshellIncoherentCrossSection(2).front(),
      3.49837181487809915e-02 );
  TEST_EQUALITY_CONST(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(2).back(),
       6.04997151541930497e-02 );
  TEST_EQUALITY_CONST( data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(2),
		       0 );
  TEST_EQUALITY_CONST(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(3).size(),
       775 );
  TEST_EQUALITY_CONST(
      data_container.getImpulseApproxSubshellIncoherentCrossSection(3).front(),
      7.82914013606348935e-02 );
  TEST_EQUALITY_CONST(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(3).back(),
       2.02674045766546712e-02 );
  TEST_EQUALITY_CONST( data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(3),
		       0 );
  TEST_EQUALITY_CONST(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(4).size(),
       775 );
  TEST_EQUALITY_CONST(
      data_container.getImpulseApproxSubshellIncoherentCrossSection(4).front(),
      1.55644449943906915e-01 );
  TEST_EQUALITY_CONST(
       data_container.getImpulseApproxSubshellIncoherentCrossSection(4).back(),
       4.02323105775383993e-02 );
  TEST_EQUALITY_CONST( data_container.getImpulseApproxSubshellIncoherentCrossSectionThresholdEnergyIndex(4),
		       0 );
  TEST_EQUALITY_CONST( 
		  data_container.getWallerHartreeCoherentCrossSection().size(),
		  775 );
  TEST_EQUALITY_CONST( 
		 data_container.getWallerHartreeCoherentCrossSection().front(),
		 2.45600299049398139e+01 );
  TEST_EQUALITY_CONST( 
		  data_container.getWallerHartreeCoherentCrossSection().back(),
		  1.92198769740615498e-06 );
  TEST_EQUALITY_CONST( 
     data_container.getWallerHartreeCoherentCrossSectionThresholdEnergyIndex(),
     0 );
  TEST_EQUALITY_CONST( data_container.getPairProductionCrossSection().size(),
		       280 );
  TEST_EQUALITY_CONST( data_container.getPairProductionCrossSection().front(),
		       3.71284984483754554e-09 );
  TEST_EQUALITY_CONST( data_container.getPairProductionCrossSection().back(),
		       1.31849999999978429e-01 );
  TEST_EQUALITY_CONST( 
	    data_container.getPairProductionCrossSectionThresholdEnergyIndex(),
	    495 );
  TEST_EQUALITY_CONST( data_container.getPhotoelectricCrossSection().size(),
		       775 ); 
  TEST_EQUALITY_CONST( data_container.getPhotoelectricCrossSection().front(),
		       4.40346567781178965e+04 ); 
  TEST_EQUALITY_CONST( data_container.getPhotoelectricCrossSection().back(),
		       4.78641586632171115e-07 ); 
  TEST_EQUALITY_CONST( 
	     data_container.getPhotoelectricCrossSectionThresholdEnergyIndex(),
	     0 ); 
  TEST_EQUALITY_CONST(
		 data_container.getSubshellPhotoelectricCrossSection(1).size(),
		 775 );
  TEST_EQUALITY_CONST(
		data_container.getSubshellPhotoelectricCrossSection(1).front(),
		4.20106634766030475e+04 );
  TEST_EQUALITY_CONST(
		 data_container.getSubshellPhotoelectricCrossSection(1).back(),
		 4.54467548753621960e-07 );
  TEST_EQUALITY_CONST(
    data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex(1),
    0 );
  TEST_EQUALITY_CONST(
		 data_container.getSubshellPhotoelectricCrossSection(2).size(),
		 775 );
  TEST_EQUALITY_CONST(
		data_container.getSubshellPhotoelectricCrossSection(2).front(),
		1.92946542999592748e+03 );
  TEST_EQUALITY_CONST(
		 data_container.getSubshellPhotoelectricCrossSection(2).back(),
		 2.41672669261238441e-08 );
  TEST_EQUALITY_CONST(
    data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex(2),
    0 );
  TEST_EQUALITY_CONST(
		 data_container.getSubshellPhotoelectricCrossSection(3).size(),
		 775 );
  TEST_EQUALITY_CONST(
		data_container.getSubshellPhotoelectricCrossSection(3).front(),
		3.16445995519961478e+01 );
  TEST_EQUALITY_CONST(
		 data_container.getSubshellPhotoelectricCrossSection(3).back(),
		 2.04871323525023182e-12 );
  TEST_EQUALITY_CONST(
    data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex(3),
    0 );
  TEST_EQUALITY_CONST(
		 data_container.getSubshellPhotoelectricCrossSection(4).size(),
		 775 );
  TEST_EQUALITY_CONST(
		data_container.getSubshellPhotoelectricCrossSection(4).front(),
		6.28832719669201197e+01 );
  TEST_EQUALITY_CONST(
		 data_container.getSubshellPhotoelectricCrossSection(4).back(),
		 4.72223919011517413e-12 );
  TEST_EQUALITY_CONST(
    data_container.getSubshellPhotoelectricCrossSectionThresholdEnergyIndex(4),
    0 );
  TEST_EQUALITY_CONST(
		     data_container.getWallerHartreeTotalCrossSection().size(),
		     775 );
  TEST_EQUALITY_CONST(
		    data_container.getWallerHartreeTotalCrossSection().front(),
		    4.40594690580228344e+04 );
  TEST_EQUALITY_CONST(
		     data_container.getWallerHartreeTotalCrossSection().back(),
		     3.13338538552961843e-01 );
  TEST_EQUALITY_CONST(
		     data_container.getImpulseApproxTotalCrossSection().size(),
		     775 );
  TEST_EQUALITY_CONST(
		    data_container.getImpulseApproxTotalCrossSection().front(),
		    4.40594857955671105e+04 );
  TEST_EQUALITY_CONST(
		     data_container.getImpulseApproxTotalCrossSection().back(),
		     3.13351484549587445e-01 );
		       
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
  
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_h_ace_file",
		 &test_h_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_h_ace_table",
		 &test_h_ace_table_name,
		 "Test ACE table name" );
  clp.setOption( "test_c_ace_file",
		 &test_c_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_c_ace_table",
		 &test_c_ace_table_name,
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
    // Create the file handler and data extractor for hydrogen
    Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
			       new Data::ACEFileHandler( test_h_ace_file_name,
							 test_h_ace_table_name,
							 1u ) );

    Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
				new Data::XSSEPRDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

    data_generator_h.reset( 
		   new DataGen::StandardElectronPhotonRelaxationDataGenerator(
				     xss_data_extractor->extractAtomicNumber(),
				     xss_data_extractor,
				     0.001,
				     20.0,
				     1e-4,
				     1e-3,
				     0.001,
				     1e-42,
				     1e-15 ) );
  }

  {
    // Create the file handler and data extractor for hydrogen
    Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
			       new Data::ACEFileHandler( test_c_ace_file_name,
							 test_c_ace_table_name,
							 1u ) );

    Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
				new Data::XSSEPRDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

    data_generator_c.reset( 
		   new DataGen::StandardElectronPhotonRelaxationDataGenerator(
				     xss_data_extractor->extractAtomicNumber(),
				     xss_data_extractor,
				     0.001,
				     20.0,
				     1e-3,
				     1e-3,
				     0.001,
				     1e-32,
				     1e-16) );
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
