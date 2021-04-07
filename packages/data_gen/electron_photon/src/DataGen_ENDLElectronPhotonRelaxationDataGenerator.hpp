//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ENDLElectronPhotonRelaxationDataGenerator.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  The ENDL electron-photon-relaxation data generator class
//!         declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ENDL_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP
#define DATA_GEN_ENDL_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP

// Std Lib Includes
#include <utility>
#include <iostream>

// FRENSIE Includes
#include "DataGen_ElectronPhotonRelaxationDataGenerator.hpp"
#include "DataGen_ElectronElasticDataEvaluator.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_SubshellIncoherentPhotonScatteringDistribution.hpp"
#include "MonteCarlo_ElectroionizationSamplingType.hpp"
#include "Data_ENDLDataContainer.hpp"
#include "Utility_ArrayView.hpp"
#include "Utility_UnivariateDistribution.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"

namespace DataGen{

//! The ENDL electron-photon-relaxation data generator class
class ENDLElectronPhotonRelaxationDataGenerator : public ElectronPhotonRelaxationDataGenerator
{

public:

  //! Constructor
  ENDLElectronPhotonRelaxationDataGenerator(
     const std::shared_ptr<const Data::ENDLDataContainer>& endl_data_container,
     const double min_photon_energy,
     const double max_photon_energy,
     const double min_electron_energy,
     const double max_electron_energy );

  //! Basic Constructor
  ENDLElectronPhotonRelaxationDataGenerator(
                          const std::shared_ptr<const Data::ENDLDataContainer>&
                          endl_data_container );

  //! Constructor (existing data container)
  ENDLElectronPhotonRelaxationDataGenerator(
                          const std::shared_ptr<const Data::ENDLDataContainer>&
                          endl_data_container,
                          const boost::filesystem::path& file_name_with_path );

  //! Destructor
  ~ENDLElectronPhotonRelaxationDataGenerator()
  { /* ... */ }

  //! Populate the electron-photon-relaxation data container
  void populateEPRDataContainer() final override;

protected:

  //! Constructor (check for valid min/max particle energies)
  ENDLElectronPhotonRelaxationDataGenerator(
     const std::shared_ptr<const Data::ENDLDataContainer>& endl_data_container,
     const double min_photon_energy,
     const double max_photon_energy,
     const double min_electron_energy,
     const double max_electron_energy,
     const bool check_photon_energies );

  //! Set the atomic data
  virtual void setRelaxationData();

  //! Set the Compton profile data
  virtual void setComptonProfileData();

  //! Set the Waller-Hartree scattering function data
  virtual void setWallerHartreeScatteringFunctionData();

  //! Set the Waller-Hartree atomic form factor data
  virtual void setWallerHartreeAtomicFormFactorData();

  //! Extract the photon heating numbers
  virtual void extractPhotonHeatingNumbers(
                        std::shared_ptr<const Utility::UnivariateDistribution>&
                        heating_numbers ) const;

  //! Extract the Waller-Hartree incoherent cross section
  virtual void extractWallerHartreeIncoherentCrossSection(
                        std::shared_ptr<const Utility::UnivariateDistribution>&
                        waller_hartree_incoherent_cs ) const;

  //! Extract the Waller-Hartree coherent cross section
  virtual void extractWallerHartreeCoherentCrossSection(
                        std::shared_ptr<const Utility::UnivariateDistribution>&
                        waller_hartree_coherent_cs ) const;

  //! Extract the pair production cross section
  virtual void extractPairProductionCrossSection(
                        std::shared_ptr<const Utility::UnivariateDistribution>&
                        pair_production_cs ) const;

  //! Extract the triplet production cross section
  virtual void extractTripletProductionCrossSection(
                        std::shared_ptr<const Utility::UnivariateDistribution>&
                        triplet_production_cs ) const;

  //! Extract the subshell photoelectric effect cross sections
  virtual void extractSubshellPhotoelectricEffectCrossSections(
                  std::vector<std::pair<unsigned,std::shared_ptr<const Utility::UnivariateDistribution> > >&
                  subshell_photoelectric_effect_css ) const;

  //! Create the heating numbers on the union energy grid
  virtual bool createHeatingNumbersOnUnionEnergyGrid(
                  const std::list<double>& union_energy_grid,
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  original_cross_section,
                  std::vector<double>& cross_section ) const;

  //! Extract the average photon heating numbers
  template<typename InterpPolicy>
  void extractPhotonCrossSection(
          Utility::ArrayView<const double> raw_energy_grid,
          Utility::ArrayView<const double> raw_cross_section,
          std::shared_ptr<const Utility::UnivariateDistribution>& cross_section,
          const bool processed_raw_data = true ) const;

  // Create the subshell impulse approx incoherent cross section evaluators
  void createSubshellImpulseApproxIncoherentCrossSectionEvaluators(
     std::vector<std::pair<unsigned,std::shared_ptr<const MonteCarlo::SubshellIncoherentPhotonScatteringDistribution> > >& evaluators ) const;

  // Initialize the photon union energy grid
  void initializePhotonUnionEnergyGrid( std::list<double>& union_energy_grid ) const;

  // Create the cross section on the union energy grid
  void createCrossSectionOnUnionEnergyGrid(
                  const std::list<double>& union_energy_grid,
                  const std::shared_ptr<const Utility::UnivariateDistribution>&
                  original_cross_section,
                  std::vector<double>& cross_section,
                  unsigned& threshold_index,
                  const double true_threshold_energy,
                  const bool zero_at_threshold ) const;

  //! Return the endl data container
  const Data::ENDLDataContainer& getENDLDataContainer() const;

private:

  // Find the table min photon energy
  double findTableMinPhotonEnergy() const;

  // Fine the table max photon energy
  double findTableMaxPhotonEnergy() const;

  // Set the photon data
  void setPhotonData();

  // Set the electron data
  void setElectronData();

  // Set the occupation number data
  void setOccupationNumberData();

  // Extract the half Compton profile from the ACE table
  void extractHalfComptonProfile(
                           const unsigned subshell,
                           std::vector<double>& half_momentum_grid,
                           std::vector<double>& half_profile ) const;

  // Set the electron cross section union energy grid
  void setElectronCrossSectionsData( const ElectronElasticDataEvaluator& elastic_evaluator );

  // Extract electron cross sections
  template<typename InterpPolicy>
  void extractElectronCrossSection(
        const std::vector<double>& raw_energy_grid,
        const std::vector<double>& raw_cross_section,
        std::shared_ptr<const Utility::UnivariateDistribution>& cross_section ) const;

  // Set the bremsstrahlung secondary grid data
  void setRefinedBremsstrahlungDistributionData();

  // Set the electroionization subshell secondary grid data
  void setRefinedElectroionizationSubshellDistributionData(
      const MonteCarlo::ElectroionizationSamplingType sampling_type );


  // Initialize the electroionization subshell secondary grid
  std::vector<double> initializeElectroionizationSecondaryGrid(
    const MonteCarlo::ElectroionizationSamplingType sampling_type,
    const double incoming_energy,
    const double min_secondary_energy,
    const double max_secondary_energy,
    const unsigned shell ) const;

  // Add binding energies to union energy grid
  void addBindingEnergiesToUnionEnergyGrid(
                                  const double min_energy,
                                  const double max_energy,
                                  const bool add_nudged_values,
                                  std::list<double>& union_energy_grid ) const;

  // Initialize the electron union energy grid
  void initializeElectronUnionEnergyGrid(
                                  std::list<double>& union_energy_grid ) const;

  // Merge the electron union energy grid
  void mergeElectronUnionEnergyGrid(
    const std::vector<double>& energy_grid,
    std::list<double>& union_energy_grid ) const;

  // Calculate the electron total cross section
  void calculateElectronTotalCrossSection();

  // Create the cross section on the union energy grid
  void createCrossSectionOnUnionEnergyGrid(
             const std::list<double>& union_energy_grid,
             const std::shared_ptr<const MonteCarlo::SubshellIncoherentPhotonScatteringDistribution>&
             original_cross_section,
             std::vector<double>& cross_section,
             unsigned& threshold_index ) const;

  // Populate a cross section using the raw cross section
  void populateCrossSection( const std::vector<double>& raw_cross_section,
                             std::vector<double>& cross_section,
                             unsigned& threshold_index,
                             const bool zero_at_threshold ) const;

  // Calculate the total photoelectric cross section
  void calculateTotalPhotoelectricCrossSection();

  // Calculate the total impulse approx. incoherent cross section
  void calculateImpulseApproxTotalIncoherentCrossSection();

  // Calculate the photon total cross section
  void calculatePhotonTotalCrossSection(
                                 const bool use_waller_hartree_incoherent_cs );

  // Add cross section to electron/photon total cross section
  void addCrossSectionToTotalCrossSection(
                              const std::vector<double>& energy_grid,
                              const std::vector<double>& cross_section,
                              std::vector<double>& total_cross_section ) const;

  // The if a value is not equal to zero
  static bool notEqualZero( const double value );

  // The ENDL data
  std::shared_ptr<const Data::ENDLDataContainer> d_endl_data_container;
};

// The if a value is not equal to zero
inline bool ENDLElectronPhotonRelaxationDataGenerator::notEqualZero(
                                                           const double value )
{
  return value != 0.0;
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "DataGen_ENDLElectronPhotonRelaxationDataGenerator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_GEN_ENDL_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_ENDLElectronPhotonRelaxationDataGenerator.hpp
//---------------------------------------------------------------------------//
