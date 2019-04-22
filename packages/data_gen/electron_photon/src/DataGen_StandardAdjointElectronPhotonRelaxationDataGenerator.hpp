//---------------------------------------------------------------------------//
//!
//! \file   DataGen_StandardAdjointElectronPhotonRelaxationDataGenerator.hpp
//! \author Luke Kersting, Alex Robinson
//! \brief  The standard electron-photon-relaxation data generator class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_STANDARD_ADJOINT_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP
#define DATA_GEN_STANDARD_ADJOINT_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP

// Std Lib Includes
#include <utility>
#include <iostream>

// FRENSIE Includes
#include "DataGen_AdjointElectronPhotonRelaxationDataGenerator.hpp"
#include "DataGen_AdjointElectronGridGenerator.hpp"
#include "DataGen_AdjointIncoherentGridGenerator.hpp"
#include "DataGen_AdjointIncoherentGridGenerator.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_UnivariateDistribution.hpp"
#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_SubshellIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectroatomicReaction.hpp"
#include "MonteCarlo_TwoDInterpolationType.hpp"
#include "MonteCarlo_TwoDGridType.hpp"

namespace DataGen{

//! The standard adjoint electron-photon-relaxation data generator class
class StandardAdjointElectronPhotonRelaxationDataGenerator : public AdjointElectronPhotonRelaxationDataGenerator
{

public:

  typedef DataGen::AdjointElectronGridGenerator<Utility::LogLogLog>
    ElectronGridGenerator;

  //! Advanced Constructor
  StandardAdjointElectronPhotonRelaxationDataGenerator(
      const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>&
      forward_epr_data,
      const double min_photon_energy,
      const double max_photon_energy,
      const double min_electron_energy,
      const double max_electron_energy );

  //! Basic Constructor
  StandardAdjointElectronPhotonRelaxationDataGenerator(
      const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>&
        forward_epr_data );

  //! Constructor (existing data container)
  StandardAdjointElectronPhotonRelaxationDataGenerator(
    const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>&
      forward_epr_data,
    const boost::filesystem::path& file_name_with_path );

  //! Destructor
  virtual ~StandardAdjointElectronPhotonRelaxationDataGenerator()
  { /* ... */ }

  //! Populate the adjoint electron-photon-relaxation data container
  void populateEPRDataContainer(
    const bool populate_photons = true,
    const bool populate_electrons = true ) final override;

protected:

  //! Set the adjoint atomic data
  void setAdjointRelaxationData();

  //! Set the Compton profile data
  void setComptonProfileData();

  //! Set the occupation number data
  void setOccupationNumberData();

  //! Set the Waller-Hartree scattering function data
  void setWallerHartreeScatteringFunctionData();

  //! Set the Waller-Hartree atomic form factor data
  void setWallerHartreeAtomicFormFactorData();

  //! Set the adjoint photon data
  void setAdjointPhotonData();

  //! Set the adjoint electron data
  void setAdjointElectronData();

private:

  // The if a value is not equal to zero
  static bool notEqualZero( const double value );

// Find the lower and upper bin boundary for a min and max energy
  void findLowerAndUpperBinBoundary(
    const double min_energy,
    const double max_energy,
    const std::vector<double>& energy_distribution,
    std::vector<double>::const_iterator& lower_energy_boundary,
    std::vector<double>::const_iterator& upper_energy_boundary ) const;

  // Create the cross section on the union energy grid
  void createCrossSectionOnUnionEnergyGrid(
          const std::list<double>& union_energy_grid,
          const std::shared_ptr<const Utility::UnivariateDistribution>& cs_evaluator,
          std::vector<double>& cross_section ) const;

  // Create the cross section on the union energy grid
  template<typename Functor>
  void createCrossSectionOnUnionEnergyGrid(
   const std::list<double>& union_energy_grid,
   Functor& adjoint_cross_section_functor,
   std::vector<double>& cross_section,
   unsigned& threshold_index ) const;

  // Update the cross section on the union energy grid
  template<typename Functor>
  void updateCrossSectionOnUnionEnergyGrid(
   const std::list<double>& union_energy_grid,
   const std::list<double>& old_union_energy_grid,
   const std::vector<double>& old_cross_section,
   Functor& adjoint_cross_section_functor,
   std::vector<double>& cross_section,
   unsigned& threshold_index ) const;

  // Initialize table generation data
  void initializeTableGenerationData();

  ////////////////////
  // Photon Methods //
  ////////////////////

  // Set the adjoint pair production energy distribution
  void setAdjointPairProductionEnergyDistribution();

  // Set the adjoint triplet production energy distribution
  void setAdjointTripletProductionEnergyDistribution();

  // Create the Waller-Hartree incoherent adjoint cs evaluator
  void createWallerHartreeIncoherentAdjointCrossSectionEvaluator(
         std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>& cs_evaluator ) const;

  // Create the subshell impulse approx incoherent adjoint cs evaluators
  void createSubshellImpulseApproxIncoherentAdjointCrossSectionEvaluators(
          std::vector<std::pair<unsigned,std::shared_ptr<const MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution> > >&
          cs_evaluators ) const;

  // Create the subshell impulse approx incoherent adjoint cs evaluators
  void createSubshellImpulseApproxIncoherentAdjointCrossSectionEvaluators(
          std::vector<std::pair<unsigned,std::shared_ptr<const MonteCarlo::DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution> > >&
          cs_evaluators ) const;

  // Create a subshell impulse approx incoherent adjoint cs evaluators
  void createSubshellImpulseApproxIncoherentAdjointCrossSectionEvaluator(
          const unsigned subshell,
          std::shared_ptr<const MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution>& cs_evaluator ) const;

  // Create a subshell impulse approx incoherent adjoint cs evaluators
  void createSubshellImpulseApproxIncoherentAdjointCrossSectionEvaluator(
          const unsigned subshell,
          std::shared_ptr<const MonteCarlo::DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution>& cs_evaluator ) const;


  // Initialize the adjoint photon union energy grid
  void initializeAdjointPhotonUnionEnergyGrid(
                                  std::list<double>& union_energy_grid ) const;

  // Calculate the binding energy threshold
  double calculateBindingEnergyThreshold( const double binding_energy,
                                          const bool nudge_value ) const;

  // Add binding energies to union energy grid
  void addBindingEnergyThresholdsToUnionEnergyGrid(
                                  const double min_energy,
                                  const double max_energy,
                                  const bool add_nudged_values,
                                  std::list<double>& union_energy_grid ) const;

  // Update the adjoint photon union energy grid
  void updateAdjointPhotonUnionEnergyGrid(
         std::list<double>& union_energy_grid,
         const std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>& cs_evaluator ) const;

  // Update the adjoint photon union energy grid
  void updateAdjointPhotonUnionEnergyGrid(
         std::list<double>& union_energy_grid,
         const std::vector<std::pair<unsigned,std::shared_ptr<const MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution> > >&
         cs_evaluators ) const;

  // Update the adjoint photon union energy grid
  void updateAdjointPhotonUnionEnergyGrid(
         std::list<double>& union_energy_grid,
         const std::vector<std::pair<unsigned,std::shared_ptr<const MonteCarlo::DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution> > >&
         cs_evaluators ) const;

  // Update the adjoint photon union energy grid
  void updateAdjointPhotonUnionEnergyGrid(
        std::list<double>& union_energy_grid,
        const std::shared_ptr<const Utility::UnivariateDistribution>&
        cs_evaluator ) const;

  // Create the cross section on the union energy grid
  void createCrossSectionOnUnionEnergyGrid(
          const std::list<double>& union_energy_grid,
          const std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>& cs_evaluator,
          std::vector<std::vector<double> >& max_energy_grid,
          std::vector<std::vector<double> >& cross_section ) const;

  // Create the cross section on the union energy grid
  void createCrossSectionOnUnionEnergyGrid(
          const std::list<double>& union_energy_grid,
          const std::shared_ptr<const MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution>& cs_evaluator,
          std::vector<std::vector<double> >& max_energy_grid,
          std::vector<std::vector<double> >& cross_section,
          unsigned& threshold_index ) const;

  // Create the cross section on the union energy grid
  void createCrossSectionOnUnionEnergyGrid(
          const std::list<double>& union_energy_grid,
          const std::shared_ptr<const MonteCarlo::DopplerBroadenedSubshellIncoherentAdjointPhotonScatteringDistribution>& cs_evaluator,
          std::vector<std::vector<double> >& max_energy_grid,
          std::vector<std::vector<double> >& cross_section ) const;

  // Calculate the impulse approx total incoherent adjoint cross section
  void calculateAdjointImpulseApproxTotalIncoherentCrossSection();

  // Calculate the impulse approx total incoherent adjoint cross section
  void calculateAdjointDopplerBroadenedImpulseApproxTotalIncoherentCrossSection();

  // Calculate the adjoint photon total cross section
  void calculateAdjointPhotonTotalCrossSection(
          const bool use_waller_hartree_adjoint_incoherent_cs,
          const bool else_use_doppler_broadened_impulse_approx_incoherent_cs );

  // Evaluate the total cross section at an energy and max energy
  double evaluateAdjointPhotonTotalCrossSection(
          const std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >&
          cross_sections,
          const double max_energy ) const;

  //////////////////////
  // Electron Methods //
  //////////////////////

  // Initialize the electron union energy grid
  void initializeAdjointElectronUnionEnergyGrid(
     std::list<double>& union_energy_grid,
     std::map<unsigned,std::shared_ptr<ElectronGridGenerator> >& ionization_grid_generators,
     std::shared_ptr<ElectronGridGenerator>& brem_grid_generator,
     const double excitation_max_energy ) const;

// Create the inelastic cross section evaluators
void createForwardInelasticElectronCrossSectionEvaluators(
    const std::shared_ptr<const std::vector<double> >& forward_electron_energy_grid,
    const std::shared_ptr<Utility::HashBasedGridSearcher<double> >& forward_grid_searcher,
    std::function<double (const double&)>& forward_brem_electron_xs_evaluator,
    std::function<double (const double&)>& forward_ionization_electron_xs_evaluator,
    std::function<double (const double&)>& forward_excitation_electron_xs_evaluator ) const;

  // Create the adjoint atomic excitation evaluators
  void createAdjointAtomicExcitationEvaluators(
    const std::shared_ptr<const std::vector<double> >& forward_electron_energy_grid,
    const std::shared_ptr<Utility::HashBasedGridSearcher<double> >& forward_grid_searcher,
    std::function<double (const double&)>& adjoint_excitation_xs_evaluator,
    std::function<double (const double&)>& adjoint_excitation_energy_gain_evaluator,
    double& excitation_max_energy );

  // Create the adjoint bremsstrahlung grid generator
  void createAdjointBremsstrahlungGridGenerator(
    const std::shared_ptr<const std::vector<double> >& forward_electron_energy_grid,
    const std::shared_ptr<Utility::HashBasedGridSearcher<double> >& forward_grid_searcher,
    std::shared_ptr<ElectronGridGenerator>&
        adjoint_bremsstrahlung_grid_generator ) const;

  // Create the adjoint electroionization subshell grid generator
  void createAdjointElectroionizationSubshellGridGenerator(
    const std::shared_ptr<const std::vector<double> >& forward_electron_energy_grid,
    const std::shared_ptr<Utility::HashBasedGridSearcher<double> >& forward_grid_searcher,
    std::shared_ptr<ElectronGridGenerator>&
        adjoint_electroionization_grid_generator,
    const unsigned shell ) const;

  // The forward data
  std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>
  d_forward_epr_data;
};

// The if a value is not equal to zero
inline bool StandardAdjointElectronPhotonRelaxationDataGenerator::notEqualZero(
                                                           const double value )
{
  return value != 0.0;
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "DataGen_StandardAdjointElectronPhotonRelaxationDataGenerator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_GEN_STANDARD_ADJOINT_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_StandardAdjointElectronPhotonRelaxationDataGenerator.hpp
//---------------------------------------------------------------------------//
