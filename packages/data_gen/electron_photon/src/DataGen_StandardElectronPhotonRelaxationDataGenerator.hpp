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
	   const Teuchos::RCP<const Data::XSSEPRDataExtractor>& ace_epr_data,
	   const double min_photon_energy,
	   const double occupation_number_evaluation_tolerance,
	   const double subshell_incoherent_evaluation_tolerance,
	   const double grid_tolerance = 0.001 );

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
  void extractCrossSection(
	  Teuchos::ArrayView<const double> raw_energy_grid,
	  Teuchos::ArrayView<const double> raw_cross_section,
	  Teuchos::RCP<const Utility::OneDDistribution>& cross_section ) const;

  // Extract the subshell photoelectric cross sections
  void extractSubshellPhotoelectricCrossSections( Teuchos::Array<std::pair<unsigned,Teuchos::RCP<const Utility::OneDDistribution> >& cross_sections ) const;

  // Create the subshell impulse approx incoherent cross section evaluators
  void createSubshellImpulseApproxIncoherentCrossSectionEvaluators(
     const Data::ElectronPhotonRelaxationVolatileDataContainer& data_container,
     Teuchos::Array<std::pair<unsigned,Teuchos::RCP<const SubshellIncoherentCrossSectionEvaluator> > >& evaluators ) const;

  // Initialize the photon union energy grid
  void initializePhotonUnionEnergyGrid( 
     const Data::ElectronPhotonRelaxationVolatileDataContainer& data_container,
     std::list<double>& union_energy_grid ) const;

  // Create the cross section on the union energy grid
  void createCrossSectionOnUnionEnergyGrid(
   const std::list<double>& union_energy_grid,
   const Teuchos::RCP<const Utility::OneDDistribution>& original_cross_section,
   std::vector<double>& cross_section ) const;

  // Create the cross section on the union energy grid
  void createCrossSectionOnUnionEnergyGrid(
	     const std::list<double>& union_energy_grid,
	     const Teuchos::RCP<const SubshellIncoherentCrossSectionEvaluator>&
	     original_cross_section,
	     std::vector<double>& cross_section ) const;

  // Calculate the total photoelectric cross section
  void calculateTotalPhotoelectricCrossSection( 
	                   Data::ElectronPhotonRelaxationVolatileDataContainer&
			   data_container ) const;

  // Calculate the total impulse approx. incoherent cross section
  void calculateImpulseApproxTotalIncoherentCrossSection(
		           Data::ElectronPhotonRelaxationVolatileDataContainer&
			   data_container ) const;

  // Calculate the Waller-Hartree total cross section
  void calculateWallerHartreeTotalCrossSection(
		          Data::ElectronPhotonRelaxationVolatileDataContainer&
			  data_container ) const;

  // Calculate the impulse approx total cross section
  void calculateImpulseApproxTotalCrossSection(
		          Data::ElectronPhotonRelaxationVolatileDataContainer&
			  data_container ) const;

  // The ACE data
  Teuchos::RCP<const Data::XSSEPRDataExtractor> d_ace_epr_data;

  // The min photon energy
  double d_min_photon_energy;

  // The occupation number evaluation tolerance
  double d_occupation_number_evaluation_tolerance;

  // The subshell incoherent evaluation tolerance
  double d_subshell_incoherent_evaluation_tolerance;
  
  // The grid tolerance
  double d_grid_tolerance;
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
