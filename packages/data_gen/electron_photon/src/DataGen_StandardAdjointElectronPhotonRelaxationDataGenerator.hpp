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

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "DataGen_AdjointElectronPhotonRelaxationDataGenerator.hpp"
#include "DataGen_AdjointElectronCrossSectionEvaluator.hpp"
#include "DataGen_AdjointIncoherentGridGenerator.hpp"
#include "DataGen_ElasticElectronMomentsEvaluator.hpp"
#include "DataGen_AdjointIncoherentGridGenerator.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_SubshellIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "Utility_OneDDistribution.hpp"
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectroatomicReaction.hpp"

namespace DataGen{

//! The standard adjoint electron-photon-relaxation data generator class
class StandardAdjointElectronPhotonRelaxationDataGenerator : public AdjointElectronPhotonRelaxationDataGenerator
{

public:

  typedef MonteCarlo::ElectroionizationSubshellElectroatomicReaction<Utility::LinLin>
    ElectroionizationReaction;

  typedef MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin> 
    BremsstrahlungReaction;

  //! Advanced Constructor
  StandardAdjointElectronPhotonRelaxationDataGenerator(
      const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>&
      forward_epr_data,
      const double min_photon_energy,
      const double max_photon_energy,
      const double min_electron_energy,
      const double max_electron_energy,
      std::ostream* os_log = &std::cout,
      std::ostream* os_warn = &std::cerr );
  
  //! Basic Constructor
  StandardAdjointElectronPhotonRelaxationDataGenerator(
      const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>&
      forward_epr_data,
      std::ostream* os_log = &std::cout );
  
  //! Destructor
  virtual ~StandardAdjointElectronPhotonRelaxationDataGenerator()
  { /* ... */ }

  //! Set the adjoint incoherent max energy nudge value
  void setAdjointIncoherentMaxEnergyNudgeValue( const double max_energy_nudge_value );
  
  //! Return the adjoint incoherent max energy nudge value
  double getAdjointIncoherentMaxEnergyNudgeValue() const;

  //! Set the adjoint incoherent energy to max energy nudge value
  void setAdjointIncoherentEnergyToMaxEnergyNudgeValue(
                               const double energy_to_max_energy_nudge_value );

  //! Return the adjoint incoherent energy to max energy nudge value
  double getAdjointIncoherentEnergyToMaxEnergyNudgeValue() const;

  //! Set the adjoint incoherent cross section evaluation tolerance
  void setAdjointIncoherentEvaluationTolerance( const double integration_tol );

  //! Return the adjoint incoherent cross section integration tolerance
  double getAdjointIncoherentCrossSectionIntegrationTolerance() const;

  //! Set the adjoint incoherent grid convergence tolerance
  void setAdjointIncoherentGridConvergenceTolerance(
                                                const double convergence_tol );

  //! Return the adjoint incoherent grid convergence tolerance
  double getAdjointIncoherentGridConvergenceTolerance() const;

  //! Set the adjoint incoherent absolute difference tolerance
  void setAdjointIncoherentAbsoluteDifferenceTolerance(
                                              const double absolute_diff_tol );

  //! Get the adjoint incoherent absolute difference tolerance
  double getAdjointIncoherentAbsoluteDifferenceTolerance() const;

  //! Set the adjoint incoherent distance tolerance
  void setAdjointIncoherentDistanceTolerance( const double distance_tol );

  //! Get the adjoint incoherent distance tolerance
  double getAdjointIncoherentDistanceTolerance() const;
/*
  //! Set the cutoff angle cosine above which screened rutherford is used
  void setCutoffAngleCosine( const double cutoff_angle_cosine );
*/
  //! Get the cutoff angle cosine above which screened rutherford is used
  double getCutoffAngleCosine() const;
/*
  //! Set the number of moment preserving angles
  void setNumberOfMomentPreservingAngles(
                           const unsigned number_of_moment_preserving_angles );
*/
  //! Get the number of moment preserving angles
  unsigned getNumberOfMomentPreservingAngles() const;
  
  //! Set the evaluation tolerance for the adjoint bremsstrahlung cross section
  void setAdjointBremsstrahlungCrossSectionEvaluationTolerance(
                                           const double evaluation_tolerance );
  
  //! Get the evaluation tolerance for the adjoint bremsstrahlung cross section
  double getAdjointBremsstrahlungCrossSectionEvaluationTolerance() const;

  //! Set the evaluation tolerance for the adjoint electroionization cross section
  void setAdjointElectroionizationCrossSectionEvaluationTolerance(
                                           const double evaluation_tolerance );
  
  //! Get the evaluation tolerance for the adjoint electroionization cross section
  double getAdjointElectroionizationCrossSectionEvaluationTolerance() const;

  //! Set the adjoint electron grid convergence tolerance
  void setAdjointElectronGridConvergenceTolerance(
                        const double adjoint_electron_grid_convergence_tol );

  //! Get the adjoint electron grid convergence tolerance
  double getAdjointElectronGridConvergenceTolerance() const;

  //! Set the adjoint electron absolute diff tolerance
  void setAdjointElectronAbsoluteDifferenceTolerance(
                        const double adjoint_electron_absolute_diff_tol );

  //! Get the adjoint electron absolute diff tolerance
  double getAdjointElectronAbsoluteDifferenceTolerance() const;

  //! Set the adjoint electron distance tolerance
  void setAdjointElectronDistanceTolerance(
                        const double adjoint_electron_distance_tol );

  //! Get the adjoint electron distance tolerance
  double getAdjointElectronDistanceTolerance() const;

  //! Populate the adjoint electron-photon-relaxation data container
  void populateEPRDataContainer(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const;

protected:

  //! Set the table data
  void setTableData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const;

  //! Set the adjoint atomic data
  void setAdjointRelaxationData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const;

  //! Set the Compton profile data
  void setComptonProfileData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const;

  //! Set the occupation number data
  void setOccupationNumberData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const;

  //! Set the Waller-Hartree scattering function data
  void setWallerHartreeScatteringFunctionData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const;

  //! Set the Waller-Hartree atomic form factor data
  void setWallerHartreeAtomicFormFactorData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const;

  //! Set the adjoint photon data
  void setAdjointPhotonData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const;

  //! Set the adjoint electron data
  void setAdjointElectronData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const;

private:

  // Test if a value is greater than or equal to one
  static bool greaterThanOrEqualToOne( const double value );

  // Test if a value is greater than one
  static bool greaterThanOne( const double value );

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
          const std::shared_ptr<const Utility::OneDDistribution>& cs_evaluator,
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

  // Create the Waller-Hartree incoherent adjoint cs evaluator
  void createWallerHartreeIncoherentAdjointCrossSectionEvaluator(
         std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>& cs_evaluator ) const;

  // Create the subshell impulse approx incoherent adjoint cs evaluators
  void createSubshellImpulseApproxIncoherentAdjointCrossSectionEvaluators(
          Teuchos::Array<std::pair<unsigned,std::shared_ptr<const MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution> > >&
          cs_evaluators ) const;

  // Create a subshell impulse approx incoherent adjoint cs evaluators
  void createSubshellImpulseApproxIncoherentAdjointCrossSectionEvaluator(
          const unsigned subshell,
          std::shared_ptr<const MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution>& cs_evaluator ) const;

  // Initialize the adjoint photon union energy grid
  void initializeAdjointPhotonUnionEnergyGrid(
                                  std::list<double>& union_energy_grid ) const;

  // Update the adjoint photon union energy grid
  void updateAdjointPhotonUnionEnergyGrid(
         std::list<double>& union_energy_grid,
         const std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>& cs_evaluator ) const;

  // Update the adjoint photon union energy grid
  void updateAdjointPhotonUnionEnergyGrid(
         std::list<double>& union_energy_grid,
         const Teuchos::Array<std::pair<unsigned,std::shared_ptr<const MonteCarlo::SubshellIncoherentAdjointPhotonScatteringDistribution> > >&
         cs_evaluators ) const;

  // Update the adjoint photon union energy grid
  void updateAdjointPhotonUnionEnergyGrid(
        std::list<double>& union_energy_grid,
        const std::shared_ptr<const Utility::OneDDistribution>&
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
          std::vector<std::vector<double> >& cross_section ) const;

  //////////////////////
  // Electron Methods //
  //////////////////////

  // Initialize the electron union energy grid
  void initializeAdjointElectronUnionEnergyGrid(
     const Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container,
     std::list<double>& union_energy_grid ) const;

  // Set the electron cross section union energy grid
  void setAdjointElectronCrossSectionsData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container,
    bool recalculate_union_energy_grid = false ) const;
  
  // Create the adjoint atomic excitation cross section distribution
  void createAdjointAtomicExcitationCrossSectionDistribution(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container,
    const Teuchos::ArrayRCP<const double>& forward_electron_energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& forward_grid_searcher,
    std::shared_ptr<const Utility::OneDDistribution>&
        adjoint_excitation_cross_section_distribution ) const;

  // Create the adjoint bremsstrahlung cross section evaluator
  void createAdjointBremsstrahlungCrossSectionEvaluator(
    const Teuchos::ArrayRCP<const double>& forward_electron_energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& forward_grid_searcher,
    std::shared_ptr<DataGen::AdjointElectronCrossSectionEvaluator<BremsstrahlungReaction> >&
        adjoint_bremsstrahlung_cs_evaluator ) const;

  // Generate adjoint bremsstrahlung photon energy distribution
  void evaluateAdjointBremsstrahlungPhotonDistribution(
    const double incoming_adjoint_energy,
    const unsigned bin_index,
    const unsigned threshold_energy_index,
    const Teuchos::ArrayRCP<const double>& adjoint_cross_section,
    const Teuchos::ArrayRCP<const double>& adjoint_electron_energy_grid,
    const std::shared_ptr<DataGen::AdjointElectronCrossSectionEvaluator<BremsstrahlungReaction> >
        adjoint_bremsstrahlung_cs_evaluator,
    const std::vector<double>& adjoint_bremsstrahlung_photon_energy,
    std::vector<double>& adjoint_bremsstrahlung_pdf ) const;


  // Create the adjoint electroionization subshell cross section evaluator
  void createAdjointElectroionizationSubshellCrossSectionEvaluator(
    const Teuchos::ArrayRCP<const double>& forward_electron_energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& forward_grid_searcher,
    std::map<unsigned,std::shared_ptr<DataGen::AdjointElectronCrossSectionEvaluator<ElectroionizationReaction> > >&
        adjoint_electroionization_cs_evaluators ) const;

  // The threshold energy nudge factor
  static const double s_threshold_energy_nudge_factor;

  // The minimum tabulated energy loss
  static const double s_min_tabulated_energy_loss;

  // The forward data
  std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>
  d_forward_epr_data;

  // The log stream
  std::ostream* d_os_log;

  // The adjoint incoherent max energy nudge value
  double d_adjoint_incoherent_max_energy_nudge_value;

  // The adjoint incoherent energy to max energy nudge value
  double d_adjoint_incoherent_energy_to_max_energy_nudge_value;

  // The adjoint incoherent cross section evaluation tolerance
  double d_adjoint_incoherent_evaluation_tol;

  // The adjoint incoherent grid convergence tolerance
  double d_adjoint_incoherent_grid_convergence_tol;

  // The adjoint incoherent absolute diff tolerance
  double d_adjoint_incoherent_absolute_diff_tol;

  // The adjoint incoherent distance tolerance
  double d_adjoint_incoherent_distance_tol;

  // The adjoint electron grid convergence tolerance
  double d_adjoint_electron_grid_convergence_tol;

  // The adjoint electron absolute diff tolerance
  double d_adjoint_electron_absolute_diff_tol;

  // The adjoint electron distance tolerance
  double d_adjoint_electron_distance_tol;

  // The evaluation tolerance for the adjoint bremsstrahlung cross sections
  double d_adjoint_bremsstrahlung_evaluation_tolerance;

  // The evaluation tolerance for the adjoint electroionization cross sections
  double d_adjoint_electroionization_evaluation_tolerance;
};

// Test if a value is greater than or equal to one
inline bool
StandardAdjointElectronPhotonRelaxationDataGenerator::greaterThanOrEqualToOne(
							   const double value )
{
  return value >= 1.0;
}

// Test if a value is greater than one
inline bool
StandardAdjointElectronPhotonRelaxationDataGenerator::greaterThanOne(
							   const double value )
{
  return value > 1.0;
}

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
