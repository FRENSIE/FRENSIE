//---------------------------------------------------------------------------//
//!
//! \file   DataGen_StandardElectronPhotonRelaxationDataGenerator.hpp
//! \author Alex Robinson, Luke Kersting
//! \brief  The standard electron-photon-relaxation data generator class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_STANDARD_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP
#define DATA_GEN_STANDARD_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP

// Std Lib Includes
#include <utility>
#include <iostream>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "DataGen_ElectronPhotonRelaxationDataGenerator.hpp"
#include "DataGen_ElasticElectronMomentsEvaluator.hpp"
#include "MonteCarlo_SubshellIncoherentPhotonScatteringDistribution.hpp"
#include "Data_ENDLDataContainer.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"

namespace DataGen{

//! The standard electron-photon-relaxation data generator class
class StandardElectronPhotonRelaxationDataGenerator : public ElectronPhotonRelaxationDataGenerator
{

public:

  //! Constructor 
  StandardElectronPhotonRelaxationDataGenerator(
     const std::shared_ptr<const Data::XSSEPRDataExtractor>& ace_epr_data,
     const std::shared_ptr<const Data::ENDLDataContainer>& endl_data_container,
     const double min_photon_energy,
     const double max_photon_energy,
     const double min_electron_energy,
     const double max_electron_energy,
     std::ostream* os_log = &std::cout,
     std::ostream* os_warn = &std::cerr );

  //! Basic Constructor
  StandardElectronPhotonRelaxationDataGenerator(
     const std::shared_ptr<const Data::XSSEPRDataExtractor>& ace_epr_data,
     const std::shared_ptr<const Data::ENDLDataContainer>& endl_data_container,
     std::ostream* os_log = &std::cout );

  //! Destructor
  ~StandardElectronPhotonRelaxationDataGenerator()
  { /* ... */ }

  //! Set the occupation number evaluation tolerance
  void setOccupationNumberEvaluationTolerance(
                                           const double evaluation_tolerance );

  //! Get the occupation number evaluation tolerance
  double getOccupationNumberEvaluationTolerance() const;

  //! Set the subshell incoherent evaluation tolerance
  void setSubshellIncoherentEvaluationTolerance(
                                           const double evaluation_tolerance );

  //! Get the subshell incoherent evaluation tolerance
  double getSubshellIncoherentEvaluationTolerance() const;

  //! Set the photon threshold energy nudge factor
  void setPhotonThresholdEnergyNudgeFactor( const double nudge_factor );

  //! Get the photon threshold energy nudge factor
  double getPhotonThresholdEnergyNudgeFactor() const;
  
  //! Set the cutoff angle cosine
  void setCutoffAngleCosine( const double cutoff_angle_cosine );

  //! Get the cutoff angle cosine
  double getCutoffAngleCosine() const;

  //! Set the number of moment preserving angles
  void setNumberOfMomentPreservingAngles( const unsigned number_of_angles );

  //! Get the number of moment preserving angles
  double getNumberOfMomentPreservingAngles() const;

  //! Set the FullyTabularTwoDDistribution evaluation tolerance
  void setTabularEvaluationTolerance( const double evaluation_tolerance );

  //! Get the FullyTabularTwoDDistribution evaluation tolerance
  double getTabularEvaluationTolerance() const;

  //! Set electron FullyTabularTwoDDistribution LinLinLog interpolation mode to off (on by default)
  void setElectronLinLinLogInterpolationModeOff();

  //! Set electron FullyTabularTwoDDistribution LinLinLog interpolation mode to on (on by default)
  void setElectronLinLinLogInterpolationModeOn();

  //! Return if electron FullyTabularTwoDDistribution LinLinLog interpolation mode is on
  bool isElectronLinLinLogInterpolationModeOn() const;

  //! Set electron FullyTabularTwoDDistribution correlated sampling mode to off (on by default)
  void setElectronCorrelatedSamplingModeOff();

  //! Set electron FullyTabularTwoDDistribution correlated sampling mode to on (on by default)
  void setElectronCorrelatedSamplingModeOn();

  //! Return if electron FullyTabularTwoDDistribution correlated sampling mode is on
  bool isElectronCorrelatedSamplingModeOn() const;

  //! Set electron FullyTabularTwoDDistribution unit based interpolation mode to off (on by default)
  void setElectronUnitBasedInterpolationModeOff();

  //! Set electron FullyTabularTwoDDistribution unit based interpolation mode to on (on by default)
  void setElectronUnitBasedInterpolationModeOn();

  //! Return if electron FullyTabularTwoDDistribution unit based interpolation mode is on
  bool isElectronUnitBasedInterpolationModeOn() const;

  //! Populate the electron-photon-relaxation data container
  void populateEPRDataContainer(
   Data::ElectronPhotonRelaxationVolatileDataContainer& data_container ) const;

  //! Repopulate the electron elastic data
  static void repopulateElectronElasticData(
    Data::ElectronPhotonRelaxationVolatileDataContainer& data_container,
    const double max_electron_energy = 20.0,
    const double cutoff_angle_cosine = 0.9,
    const double tabular_evaluation_tol = 1e-7,
    const unsigned number_of_moment_preserving_angles = 1,
    const bool linlinlog_interpolation_mode_on = true,
    std::ostream& os_log = std::cout );

  //! Repopulate the electron moment preserving data
  static void repopulateMomentPreservingData(
    Data::ElectronPhotonRelaxationVolatileDataContainer& data_container,
    const double cutoff_angle_cosine = 0.9,
    const double tabular_evaluation_tol = 1e-7,
    const unsigned number_of_moment_preserving_angles = 1,
    const bool linlinlog_interpolation_mode_on = true,
    std::ostream& os_log = std::cout );

protected:

  //! Set the atomic data
  void setRelaxationData(
   Data::ElectronPhotonRelaxationVolatileDataContainer& data_container ) const;

  //! Set the Compton profile data
  void setComptonProfileData(
   Data::ElectronPhotonRelaxationVolatileDataContainer& data_container ) const;

  //! Set the occupation number data
  void setOccupationNumberData(
   Data::ElectronPhotonRelaxationVolatileDataContainer& data_container ) const;

  //! Set the Waller-Hartree scattering function data
  void setWallerHartreeScatteringFunctionData(
   Data::ElectronPhotonRelaxationVolatileDataContainer& data_container ) const;

  //! Set the Waller-Hartree atomic form factor data
  void setWallerHartreeAtomicFormFactorData(
   Data::ElectronPhotonRelaxationVolatileDataContainer& data_container ) const;

  //! Set the photon data
  void setPhotonData(
   Data::ElectronPhotonRelaxationVolatileDataContainer& data_container ) const;

  //! Set the electron data
  void setElectronData(
   Data::ElectronPhotonRelaxationVolatileDataContainer& data_container ) const;

private:

  // The if a value is not equal to zero
  static bool notEqualZero( const double value );

  // Set the transition data
  void setTransitionData( const unsigned subshell,
                          const unsigned transitions,
                          const unsigned subshell_data_start_index,
                          Data::ElectronPhotonRelaxationVolatileDataContainer&
                          data_container ) const;

  // Set the Waller-Hartree atomic form factor data
  void setWallerHartreeAtomicFormFactorData(
                       const std::function<double(double)>& evaluation_wrapper,
                       std::list<double>& recoil_momentum_grid,
                       const double initial_grid_value,
                       const double initial_form_factor_value,
                       Data::ElectronPhotonRelaxationVolatileDataContainer&
                       data_container ) const;

  // Extract the half Compton profile from the ACE table
  void extractHalfComptonProfile(
                           const unsigned subshell,
                           std::vector<double>& half_momentum_grid,
                           std::vector<double>& half_profile ) const;

  // Set the electron cross section union energy grid
  void setElectronCrossSectionsData(
    Data::ElectronPhotonRelaxationVolatileDataContainer& data_container ) const;

  // Set the moment preserving data
  static void setMomentPreservingData(
    const std::vector<double>& elastic_energy_grid,
    const double tabular_evaluation_tol,
    const bool linlinlog_interpolation_mode_on,
    Data::ElectronPhotonRelaxationVolatileDataContainer& data_container );

  // Extract the average photon heating numbers
  template<typename InterpPolicy>
  void extractPhotonCrossSection(
          Teuchos::ArrayView<const double> raw_energy_grid,
          Teuchos::ArrayView<const double> raw_cross_section,
          std::shared_ptr<const Utility::OneDDistribution>& cross_section,
          const bool processed_raw_data = true ) const;

  // Extract electron cross sections
  template<typename InterpPolicy>
  void extractElectronCrossSection(
        const std::vector<double>& raw_energy_grid,
        const std::vector<double>& raw_cross_section,
        std::shared_ptr<const Utility::OneDDistribution>& cross_section ) const;

  // Extract the subshell photoelectric cross sections
  void extractSubshellPhotoelectricCrossSections( std::vector<std::pair<unsigned,std::shared_ptr<const Utility::OneDDistribution> > >& cross_sections ) const;

  // Create the subshell impulse approx incoherent cross section evaluators
  void createSubshellImpulseApproxIncoherentCrossSectionEvaluators(
     const Data::ElectronPhotonRelaxationVolatileDataContainer& data_container,
     Teuchos::Array<std::pair<unsigned,std::shared_ptr<const MonteCarlo::SubshellIncoherentPhotonScatteringDistribution> > >& evaluators ) const;

  // Initialize the photon union energy grid
  void initializePhotonUnionEnergyGrid(
     const Data::ElectronPhotonRelaxationVolatileDataContainer& data_container,
     std::list<double>& union_energy_grid ) const;

  // Initialize the electron union energy grid
  void initializeElectronUnionEnergyGrid(
     const Data::ElectronPhotonRelaxationVolatileDataContainer& data_container,
     std::list<double>& union_energy_grid ) const;

  // Add binding energies to union energy grid
  void addBindingEnergiesToUnionEnergyGrid(
     const Data::ElectronPhotonRelaxationVolatileDataContainer& data_container,
     const double min_energy,
     const double max_energy,
     const bool add_nudged_values,
     std::list<double>& union_energy_grid ) const;

  // Create the cross section on the union energy grid
  void createCrossSectionOnUnionEnergyGrid(
   const std::list<double>& union_energy_grid,
   const std::shared_ptr<const Utility::OneDDistribution>& original_cross_section,
   std::vector<double>& cross_section,
   unsigned& threshold_index,
   const double true_threshold_energy,
   const bool zero_at_threshold ) const;

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

  // Merge the electron union energy grid
  void mergeElectronUnionEnergyGrid(
    const std::vector<double>& energy_grid,
    std::list<double>& union_energy_grid ) const;

  // Calculate the total photoelectric cross section
  void calculateTotalPhotoelectricCrossSection(
   Data::ElectronPhotonRelaxationVolatileDataContainer& data_container ) const;

  // Calculate the total impulse approx. incoherent cross section
  void calculateImpulseApproxTotalIncoherentCrossSection(
   Data::ElectronPhotonRelaxationVolatileDataContainer& data_container ) const;

  // Calculate the photon total cross section
  void calculatePhotonTotalCrossSection(
           Data::ElectronPhotonRelaxationVolatileDataContainer& data_container,
           const bool use_waller_hartree_incoherent_cs ) const;

  // Add cross section to photon total cross section
  void addCrossSectionToPhotonTotalCrossSection(
                              const std::vector<double>& energy_grid,
                              const std::vector<double>& cross_section,
                              std::vector<double>& total_cross_section ) const;

  // Calculate the elastic anglular distribution for the angle cosine
  void calculateElasticAngleCosine(
    const std::vector<double>& raw_elastic_angle,
    const std::vector<double>& raw_elastic_pdf,
    std::vector<double>& elastic_angle,
    std::vector<double>& elastic_pdf ) const;

  // Generate elastic moment preserving discrete angle cosines and weights
  static void evaluateDisceteAnglesAndWeights(
    const std::shared_ptr<DataGen::ElasticElectronMomentsEvaluator>& moments_evaluator,
    const double& energy,
    const int& number_of_moment_preserving_angles,
    std::vector<double>& discrete_angles,
    std::vector<double>& weights,
    double& cross_section_reduction );

  // Generate elastic moment preserving cross section
  static void evaluateMomentPreservingCrossSection(
    const Teuchos::ArrayRCP<double>& electron_energy_grid,
    const Teuchos::ArrayRCP<const double>& cutoff_cross_section,
    const Teuchos::ArrayRCP<const double>& screened_rutherford_cross_section,
    const unsigned cutoff_threshold_energy_index,
    const unsigned screened_rutherford_threshold_energy_index,
    const std::shared_ptr<const MonteCarlo::AnalogElasticElectronScatteringDistribution>
        analog_distribution,
    const std::shared_ptr<const Utility::OneDDistribution>& reduction_distribution,
    const double cutoff_angle_cosine,
    std::vector<double>& moment_preserving_cross_section );

  // The ACE data
  std::shared_ptr<const Data::XSSEPRDataExtractor> d_ace_epr_data;

  // The ENDL data
  std::shared_ptr<const Data::ENDLDataContainer> d_endl_data_container;
 
  // The log stream
  std::ostream* d_os_log;

  // The FullyTabularTwoDDistribution evaluation tolerance
  double d_tabular_evaluation_tol;

  // The occupation number evaluation tolerance
  double d_occupation_number_evaluation_tolerance;

  // The subshell incoherent evaluation tolerance
  double d_subshell_incoherent_evaluation_tolerance;

  // The photon threshold energy nudge factor
  double d_photon_threshold_energy_nudge_factor;

  // The cutoff angle cosine above which screened rutherford is used
  double d_cutoff_angle_cosine;

  // The number of moment preserving angles
  unsigned d_number_of_moment_preserving_angles;

  /* The electron FullyTabularTwoDDistribution lin-lin-log interpolation mode
   * (true = on - default, false = off) */
  bool d_linlinlog_interpolation_mode_on;

  // The electron FullyTabularTwoDDistribution correlated sampling mode
  bool d_correlated_sampling_mode_on;

  // The electron FullyTabularTwoDDistribution unit based interpolation mode
  bool d_unit_based_interpolation_mode_on;

};

// The if a value is not equal to zero
inline bool StandardElectronPhotonRelaxationDataGenerator::notEqualZero(
                                                           const double value )
{
  return value != 0.0;
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "DataGen_StandardElectronPhotonRelaxationDataGenerator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_GEN_STANDARD_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_StandardElectronPhotonRelaxationDataGenerator.hpp
//---------------------------------------------------------------------------//
