//---------------------------------------------------------------------------//
//!
//! \file   DataGen_StandardElectronPhotonRelaxationDataGenerator.hpp
//! \author Alex Robinson
//! \brief  The standard electron-photon-relaxation data generator class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_STANDARD_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP
#define DATA_GEN_STANDARD_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "DataGen_ElectronPhotonRelaxationDataGenerator.hpp"
#include "Data_XSSEPRDataExtractor.hpp"

namespace DataGen{

//! The standard electron-photon-relaxation data generator class
class StandardElectronPhotonRelaxationDataGenerator : public ElectronPhotonRelaxationDataGenerator
{

public:

  //! Constructor
  StandardElectronPhotonRelaxationDataGenerator( 
	   const unsigned atomic_number,
	   const Teuchos::RCP<const Data::XSSEPRDataExtractor>& ace_epr_data );

  //! Destructor
  ~StandardElectronPhotonRelaxationDataGenerator()
  { /* ... */ }

  //! Populate the electron-photon-relaxation data container
  void populateEPRDataContainer(
			   Data::ElectronPhotonRelaxationVolatileDataContainer&
			   data_container ) const;

protected:

  // Set the atomic data
  void setRelaxationData( Data::ElectronPhotonRelaxationVolatileDataContainer&
			  data_container ) const;

  // Set the Compton profile data
  void setComptonProfileData( 
			   Data::ElectronPhotonRelaxationVolatileDataContainer&
			   data_container ) const;

  // Set the occupation number data
  void setOccupationNumberData(
			   Data::ElectronPhotonRelaxationVolatileDataContainer&
			   data_container ) const;

  // Set the Waller-Hartree scattering function data
  void setWallerHartreeScatteringFunctionData(
			   Data::ElectronPhotonRelaxationVolatileDataContainer&
			   data_container ) const;

  // Set the Waller-Hartree atomic form factor data
  void setWallerHartreeAtomicFormFactorData(
			   Data::ElectronPhotonRelaxationVolatileDataContainer&
			   data_container ) const;

  // Set the photon data
  void setPhotonData( Data::ElectronPhotonRelaxationVolatileDataContainer&
		      data_container ) const;

  // Set the electron data
  void setElectronData( Data::ElectronPhotonRelaxationVolatileDataContainer&
			data_container ) const;

private:

  // Test if a value is greater than or equal to one
  static bool greaterThanOrEqualToOne( const double value );

  // The if a value is not equal to zero
  static bool notEqualZero( const double value );

  // Set the transition data
  void setTransitionData( const unsigned subshell,
			  const unsigned transitions,
			  const unsigned subshell_data_start_index;
			  Data::ElectronPhotonRelaxationVolatileDataContainer&
			  data_container ) const;

  // Extract the half Compton profile from the ACE table
  void extractHalfComptonProfile( 
			   const unsigned subshell,
			   std::vector<double>& half_momentum_grid,
			   std::vector<double>& half_profile ) const;

  // Extract the average photon heating numbers
  void extractAveragePhotonHeatingNumbers(
	Teuchos::RCP<const Utility::OneDDistribution>& heating_numbers ) const;

  // Extract the Waller-Hartree incoherent cross section
  void extractWallerHartreeIncoherentCrossSection(
	  Teuchos::RCP<const Utility::OneDDistribution>& incoherent_cs ) const;

  // Extract the Waller-Hartree coherent cross section
  void extractWallerHartreeCoherentCrossSection(
	    Teuchos::RCP<const Utility::OneDDistribution>& coherent_cs ) const;

  // Extract the pair production cross section
  void extractPairProductionCrossSection(
     Teuchos::RCP<const Utility::OneDDistribution>& pair_production_cs ) const;

  // Extract the subshell photoelectric effect cross section
  void extractSubshellPhotoelectricEffectCrossSection(
       const unsigned subshell,
       Teuchos::RCP<const Utility::OneDDistribution>& photoelectric_cs ) const;

  // The ace epr data
  Teuchos::RCP<const Data::XSSEPRDataExtractor> d_ace_epr_data;
};

// Test if a value is greater than or equal to one
inline bool 
StandardElectronPhotonRelaxationDataGenerator::greaterThanOrEqualToOne( 
							   const double value )
{
  return value >= 1.0;
}

} // end DataGen namespace

#endif // end DATA_GEN_STANDARD_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_StandardElectronPhotonRelaxationDataGenerator.hpp
//---------------------------------------------------------------------------//
