//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ACEAndENDLElectronPhotonRelaxationDataGenerator.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  The ACE and ENDL electron-photon-relaxation data generator class
//!         declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ACE_AND_ENDL_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP
#define DATA_GEN_ACE_AND_ENDL_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP

// Std Lib Includes
#include <utility>
#include <iostream>

// FRENSIE Includes
#include "DataGen_ENDLElectronPhotonRelaxationDataGenerator.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_UnivariateDistribution.hpp"

namespace DataGen{

//! The ACE and ENDL electron-photon-relaxation data generator class
class ACEAndENDLElectronPhotonRelaxationDataGenerator : public ENDLElectronPhotonRelaxationDataGenerator
{

public:

  //! Constructor
  ACEAndENDLElectronPhotonRelaxationDataGenerator(
     const std::shared_ptr<const Data::XSSEPRDataExtractor>& ace_epr_data,
     const std::shared_ptr<const Data::ENDLDataContainer>& endl_data_container,
     const double min_photon_energy,
     const double max_photon_energy,
     const double min_electron_energy,
     const double max_electron_energy );

  //! Basic Constructor
  ACEAndENDLElectronPhotonRelaxationDataGenerator(
   const std::shared_ptr<const Data::XSSEPRDataExtractor>& ace_epr_data,
   const std::shared_ptr<const Data::ENDLDataContainer>& endl_data_container );

  //! Constructor (existing data container)
  ACEAndENDLElectronPhotonRelaxationDataGenerator(
     const std::shared_ptr<const Data::XSSEPRDataExtractor>& ace_epr_data,
     const std::shared_ptr<const Data::ENDLDataContainer>& endl_data_container,
     const boost::filesystem::path& file_name_with_path );
   
  //! Destructor
  ~ACEAndENDLElectronPhotonRelaxationDataGenerator()
  { /* ... */ }

protected:

  //! Set the atomic data
  void setRelaxationData() final override;

  //! Set the Compton profile data
  void setComptonProfileData() final override;

  //! Set the Waller-Hartree scattering function data
  void setWallerHartreeScatteringFunctionData() final override;

  //! Set the Waller-Hartree atomic form factor data
  void setWallerHartreeAtomicFormFactorData() final override;

  //! Extract the photon heating numbers
  void extractPhotonHeatingNumbers(
                        std::shared_ptr<const Utility::UnivariateDistribution>&
                        heating_numbers ) const final override;

  //! Extract the Waller-Hartree incoherent cross section
  void extractWallerHartreeIncoherentCrossSection(
                        std::shared_ptr<const Utility::UnivariateDistribution>&
                        waller_hartree_incoherent_cs ) const final override;

  //! Extract the Waller-Hartree coherent cross section
  void extractWallerHartreeCoherentCrossSection(
                        std::shared_ptr<const Utility::UnivariateDistribution>&
                        waller_hartree_coherent_cs ) const final override;

  //! Extract the subshell photoelectric effect cross sections
  void extractSubshellPhotoelectricEffectCrossSections(
                  std::vector<std::pair<unsigned,std::shared_ptr<const Utility::UnivariateDistribution> > >&
                  subshell_photoelectric_effect_css ) const final override;

  //! Create the heating numbers on the union energy grid
  bool createHeatingNumbersOnUnionEnergyGrid(
                  const std::list<double>& union_energy_grid,
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  original_cross_section,
                  std::vector<double>& cross_section ) const final override;

private:

  // Set the transition data
  void setTransitionData( const unsigned subshell,
                          const unsigned transitions,
                          const unsigned subshell_data_start_index );

  // Set the Waller-Hartree atomic form factor data
  void setWallerHartreeAtomicFormFactorData(
                       const std::function<double(double)>& evaluation_wrapper,
                       std::list<double>& recoil_momentum_grid,
                       const double initial_grid_value,
                       const double initial_form_factor_value );

  // Extract the half Compton profile from the ACE table
  void extractHalfComptonProfile(
                           const unsigned subshell,
                           std::vector<double>& half_momentum_grid,
                           std::vector<double>& half_profile ) const;

  // Extract the subshell photoelectric cross sections
  void extractSubshellPhotoelectricCrossSections( std::vector<std::pair<unsigned,std::shared_ptr<const Utility::UnivariateDistribution> > >& cross_sections ) const;

  // The ACE data
  std::shared_ptr<const Data::XSSEPRDataExtractor> d_ace_epr_data;
};

} // end DataGen namespace

#endif // end DATA_GEN_ACE_AND_ENDL_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_ACEAndENDLElectronPhotonRelaxationDataGenerator.hpp
//---------------------------------------------------------------------------//
