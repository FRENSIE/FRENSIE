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
#include "MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_TwoDInterpolationType.hpp"
#include "MonteCarlo_TwoDSamplingType.hpp"
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

  //! Set electron total elastic integrated cross section mode to off (off by default)
  //! \todo Remove this option once the proper setting has been found.
  void setElectronTotalElasticIntegratedCrossSectionModeOff();

  //! Set electron total elastic integrated cross section mode to on (off by default)
  //! \todo Remove this option once the proper setting has been found.
  void setElectronTotalElasticIntegratedCrossSectionModeOn();

  //! Return if electron total elastic integrated cross section mode to on (off by default)
  //! \todo Remove this option once the proper setting has been found.
  bool isElectronTotalElasticIntegratedCrossSectionModeOn() const;

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

  //! Set the electron TwoDInterpPolicy (LogLogLog by default)
  void setElectronTwoDInterpPolicy( MonteCarlo::TwoDInterpolationType interp );

  //! Return the electron TwoDInterpPolicy
  MonteCarlo::TwoDInterpolationType getElectronTwoDInterpPolicy() const;

  //! Set the electron TwoDSamplingPolicy (LogLogLog by default)
  void setElectronTwoDSamplingPolicy( MonteCarlo::TwoDSamplingType sampling );

  //! Return the electron TwoDSamplingPolicy
  MonteCarlo::TwoDSamplingType getElectronTwoDSamplingPolicy() const;

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
    const MonteCarlo::TwoDInterpolationType two_d_interp = MonteCarlo::LOGLOGLOG_INTERPOLATION,
    std::ostream& os_log = std::cout );

  //! Repopulate the electron moment preserving data
  static void repopulateMomentPreservingData(
    Data::ElectronPhotonRelaxationVolatileDataContainer& data_container,
    const double cutoff_angle_cosine = 0.9,
    const double tabular_evaluation_tol = 1e-7,
    const unsigned number_of_moment_preserving_angles = 1,
    const MonteCarlo::TwoDInterpolationType two_d_interp = MonteCarlo::LOGLOGLOG_INTERPOLATION,
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
    const MonteCarlo::TwoDInterpolationType two_d_interp,
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

  // Calculate the electron total cross section
  void calculateElectronTotalCrossSection(
    Data::ElectronPhotonRelaxationVolatileDataContainer& data_container ) const;

  // Add cross section to electron/photon total cross section
  void addCrossSectionToTotalCrossSection(
                              const std::vector<double>& energy_grid,
                              const std::vector<double>& cross_section,
                              std::vector<double>& total_cross_section ) const;

  // Calculate the elastic anglular distribution for the angle cosine
  void calculateElasticAngleCosine(
    const std::vector<double>& raw_elastic_angle,
    const std::vector<double>& raw_elastic_pdf,
    std::vector<double>& elastic_angle,
    std::vector<double>& elastic_pdf ) const;

  // Calculate the elastic moment preserving discrete angle cosines and weights
  static void calculateDiscreteAnglesAndWeights(
    const std::shared_ptr<DataGen::ElasticElectronMomentsEvaluator>& moments_evaluator,
    const double& energy,
    const int& number_of_moment_preserving_angles,
    std::vector<double>& discrete_angles,
    std::vector<double>& weights,
    double& cross_section_reduction );

  // Calculate the electron total elastic cross section
  void calculateElectronTotalElasticCrossSection(
    Data::ElectronPhotonRelaxationVolatileDataContainer& data_container,
    std::shared_ptr<const Utility::OneDDistribution>& total_elastic_cross_section,
    const std::vector<double>& raw_energy_grid ) const;

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

  /* The electron total elastic integrated cross section mode
   * (true = on, false = off - default) */
  bool d_integrated_total_elastic_cross_section_mode_on;

  // The cutoff angle cosine above which screened rutherford is used
  double d_cutoff_angle_cosine;

  // The number of moment preserving angles
  unsigned d_number_of_moment_preserving_angles;

  // The electron TwoDInterpPolicy (LogLogLog - default)
  MonteCarlo::TwoDInterpolationType d_two_d_interp;

  // The electron TwoDSamplingPolicy (LogLogLog - default)
  MonteCarlo::TwoDSamplingType d_two_d_sampling;
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
