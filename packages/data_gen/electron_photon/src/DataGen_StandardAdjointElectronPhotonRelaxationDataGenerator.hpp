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
#include "DataGen_AdjointElectronGridGenerator.hpp"
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

  typedef DataGen::AdjointElectronGridGenerator<BremsstrahlungReaction, Utility::LinLinLin>
    BremsstrahlungGridGenerator;

  typedef DataGen::AdjointElectronGridGenerator<ElectroionizationReaction, Utility::LinLinLin>
    ElectroionizationGridGenerator;

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

  ///////////////////////
  // Photon Table Data //
  ///////////////////////

  //! Set the adjoint pair production energy dist. norm const. evaluation tol.
  void setAdjointPairProductionEnergyDistNormConstEvaluationTolerance(
                                                 const double evaluation_tol );

  //! Get the adjoint pair production energy dist. norm const. evaluation tol
  double getAdjointPairProductionEnergyDistNormConstEvaluationTolerance() const;

  //! Set the adjoint pair production energy dist. norm const. nudge value
  void setAdjointPairProductionEnergyDistNormConstNudgeValue(
                                                    const double nudge_value );

  //! Get the adjoint pair production energy dist. norm const. nudge value
  double getAdjointPairProductionEnergyDistNormConstNudgeValue() const;

  //! Set the adjoint triplet production energy dist. norm const. evaluation tol.
  void setAdjointTripletProductionEnergyDistNormConstEvaluationTolerance(
                                                 const double evaluation_tol );

  //! Get the adjoint triplet production energy dist. norm const. evaluation tol
  double getAdjointTripletProductionEnergyDistNormConstEvaluationTolerance() const;

  //! Set the adjoint triplet production energy dist. norm const. nudge value
  void setAdjointTripletProductionEnergyDistNormConstNudgeValue(
                                                    const double nudge_value );

  //! Get the adjoint triplet production energy dist. norm const. nudge value
  double getAdjointTripletProductionEnergyDistNormConstNudgeValue() const;

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
  void setAdjointIncoherentCrossSectionEvaluationTolerance(
                                                 const double evaluation_tol );

  //! Return the adjoint incoherent cross section evaluation tolerance
  double getAdjointIncoherentCrossSectionEvaluationTolerance() const;

  //! Set the adjoint incoherent grid convergence tolerance
  void setAdjointIncoherentGridConvergenceTolerance(
                                                const double convergence_tol );

  //! Return the adjoint incoherent grid convergence tolerance
  double getAdjointIncoherentGridConvergenceTolerance() const;

  //! Set the adjoint incoherent grid absolute difference tolerance
  void setAdjointIncoherentGridAbsoluteDifferenceTolerance(
                                              const double absolute_diff_tol );

  //! Get the adjoint incoherent grid absolute difference tolerance
  double getAdjointIncoherentGridAbsoluteDifferenceTolerance() const;

  //! Set the adjoint incoherent grid distance tolerance
  void setAdjointIncoherentGridDistanceTolerance( const double distance_tol );

  //! Get the adjoint incoherent grid distance tolerance
  double getAdjointIncoherentGridDistanceTolerance() const;

  /////////////////////////
  // Electron Table Data //
  /////////////////////////

  //! Get the cutoff angle cosine above which screened rutherford is used
  double getCutoffAngleCosine() const;

  //! Get the number of moment preserving angles
  unsigned getNumberOfMomentPreservingAngles() const;

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

  //! Set the adjoint bremsstrahlung max energy nudge value
  void setAdjointBremsstrahlungMaxEnergyNudgeValue( const double max_energy_nudge_value );
  
  //! Return the adjoint bremsstrahlung max energy nudge value
  double getAdjointBremsstrahlungMaxEnergyNudgeValue() const;

  //! Set the adjoint bremsstrahlung energy to outgoing energy nudge value
  void setAdjointBremsstrahlungEnergyToOutgoingEnergyNudgeValue(
                          const double energy_to_outgoing_energy_nudge_value );

  //! Return the adjoint bremsstrahlung energy to outgoing energy nudge value
  double getAdjointBremsstrahlungEnergyToOutgoingEnergyNudgeValue() const;

  //! Set the adjoint bremsstrahlung cross section evaluation tolerance
  void setAdjointBremsstrahlungEvaluationTolerance( const double evaluation_tol );

  //! Return the adjoint bremsstrahlung cross section evaluation tolerance
  double getAdjointBremsstrahlungEvaluationTolerance() const;

  //! Set the adjoint bremsstrahlung grid convergence tolerance
  void setAdjointBremsstrahlungGridConvergenceTolerance(
                                                const double convergence_tol );

  //! Return the adjoint bremsstrahlung grid convergence tolerance
  double getAdjointBremsstrahlungGridConvergenceTolerance() const;

  //! Set the adjoint bremsstrahlung absolute difference tolerance
  void setAdjointBremsstrahlungAbsoluteDifferenceTolerance(
                                              const double absolute_diff_tol );

  //! Get the adjoint bremsstrahlung absolute difference tolerance
  double getAdjointBremsstrahlungAbsoluteDifferenceTolerance() const;

  //! Set the adjoint bremsstrahlung distance tolerance
  void setAdjointBremsstrahlungDistanceTolerance( const double distance_tol );

  //! Get the adjoint bremsstrahlung distance tolerance
  double getAdjointBremsstrahlungDistanceTolerance() const;

  //! Set the adjoint electroionization cross section evaluation tolerance
  void setAdjointElectroionizationEvaluationTolerance( const double evaluation_tol );

  //! Return the adjoint electroionization cross section evaluation tolerance
  double getAdjointElectroionizationEvaluationTolerance() const;

  //! Set the adjoint electroionization grid convergence tolerance
  void setAdjointElectroionizationGridConvergenceTolerance(
                                                const double convergence_tol );

  //! Return the adjoint electroionization grid convergence tolerance
  double getAdjointElectroionizationGridConvergenceTolerance() const;

  //! Set the adjoint electroionization absolute difference tolerance
  void setAdjointElectroionizationAbsoluteDifferenceTolerance(
                                              const double absolute_diff_tol );

  //! Get the adjoint electroionization absolute difference tolerance
  double getAdjointElectroionizationAbsoluteDifferenceTolerance() const;

  //! Set the adjoint electroionization distance tolerance
  void setAdjointElectroionizationDistanceTolerance( const double distance_tol );

  //! Get the adjoint electroionization distance tolerance
  double getAdjointElectroionizationDistanceTolerance() const;



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

  // Set the adjoint pair production energy distribution
  void setAdjointPairProductionEnergyDistribution(
         Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const;

  // Set the adjoint triplet production energy distribution
  void setAdjointTripletProductionEnergyDistribution(
         Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const;   

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

  // Calculate the impulse approx total incoherent adjoint cross section
  void calculateAdjointImpulseApproxTotalIncoherentCrossSection(
                    Data::AdjointElectronPhotonRelaxationVolatileDataContainer&
                    data_container ) const;

  // Calculate the adjoint photon total cross section
  void calculateAdjointPhotonTotalCrossSection(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container,
    const bool use_waller_hartree_adjoint_incoherent_cs ) const;

  // Evaluate the total cross section at an energy and max energy
  double evaluateAdjointPhotonTotalCrossSection(
          const std::vector<std::shared_ptr<const Utility::OneDDistribution> >&
          cross_sections,
          const double max_energy ) const;

  //////////////////////
  // Electron Methods //
  //////////////////////

  // Initialize the electron union energy grid
  void initializeAdjointElectronUnionEnergyGrid(
     const Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container,
     std::list<double>& union_energy_grid ) const;

  // Create the inelastic cross section distribution
  void createForwardInelasticElectronCrossSectionDistribution(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container,
    std::shared_ptr<const Utility::OneDDistribution>&
        forward_inelastic_electron_cross_section_distribution ) const;

  // Create the adjoint atomic excitation cross section distribution
  void createAdjointAtomicExcitationCrossSectionDistribution(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container,
    const Teuchos::ArrayRCP<const double>& forward_electron_energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& forward_grid_searcher,
    std::shared_ptr<const Utility::OneDDistribution>&
        adjoint_excitation_cross_section_distribution ) const;

  // Create the adjoint bremsstrahlung grid generator
  void createAdjointBremsstrahlungGridGenerator(
    const Teuchos::ArrayRCP<const double>& forward_electron_energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& forward_grid_searcher,
    std::shared_ptr<BremsstrahlungGridGenerator>&
        adjoint_bremsstrahlung_grid_generator ) const;

  // Create the adjoint electroionization subshell grid generator
  void createAdjointElectroionizationSubshellGridGenerator(
    const Teuchos::ArrayRCP<const double>& forward_electron_energy_grid,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& forward_grid_searcher,
    std::shared_ptr<ElectroionizationGridGenerator>&
        adjoint_electroionization_grid_generator,
    const unsigned shell ) const;

  // The forward data
  std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>
  d_forward_epr_data;

  // The log stream
  std::ostream* d_os_log;

  // The adjoint pair production energy dist norm constant evaluation tolerance
  double d_adjoint_pair_production_energy_dist_norm_const_evaluation_tol;

  // The adjoint pair production energy dist norm constant nudge value
  double d_adjoint_pair_production_energy_dist_norm_const_nudge_value;

  // The adjoint triplet production energy dist norm constant evaluation tol
  double d_adjoint_triplet_production_energy_dist_norm_const_evaluation_tol;

  // The adjoint triplet production energy dist norm constant nudge value
  double d_adjoint_triplet_production_energy_dist_norm_const_nudge_value;

  // The adjoint incoherent max energy nudge value
  double d_adjoint_incoherent_max_energy_nudge_value;

  // The adjoint incoherent energy to max energy nudge value
  double d_adjoint_incoherent_energy_to_max_energy_nudge_value;

  // The adjoint incoherent cross section evaluation tolerance
  double d_adjoint_incoherent_evaluation_tol;

  // The adjoint incoherent grid convergence tolerance
  double d_adjoint_incoherent_grid_convergence_tol;

  // The adjoint incoherent grid absolute diff tolerance
  double d_adjoint_incoherent_grid_absolute_diff_tol;

  // The adjoint incoherent grid distance tolerance
  double d_adjoint_incoherent_grid_distance_tol;

  // The adjoint electron grid convergence tolerance
  double d_adjoint_electron_grid_convergence_tol;

  // The adjoint electron absolute diff tolerance
  double d_adjoint_electron_absolute_diff_tol;

  // The adjoint electron distance tolerance
  double d_adjoint_electron_distance_tol;

  // The adjoint bremsstrahlung max energy nudge value
  double d_adjoint_bremsstrahlung_max_energy_nudge_value;

  // The adjoint bremsstrahlung energy to outgoing energy nudge value
  double d_adjoint_bremsstrahlung_energy_to_outgoing_energy_nudge_value;

  // The evaluation tolerance for the adjoint bremsstrahlung cross sections
  double d_adjoint_bremsstrahlung_evaluation_tol;

  // The adjoint bremsstrahlung grid convergence tolerance for the scattering distribution
  double d_adjoint_bremsstrahlung_grid_convergence_tol;

  // The adjoint bremsstrahlung absolute diff tolerance for the scattering distribution
  double d_adjoint_bremsstrahlung_absolute_diff_tol;

  // The adjoint bremsstrahlung distance tolerance for the scattering distribution
  double d_adjoint_bremsstrahlung_distance_tol;

  // The evaluation tolerance for the adjoint electroionization cross sections
  double d_adjoint_electroionization_evaluation_tol;

  // The adjoint electroionization grid convergence tolerance for the scattering distribution
  double d_adjoint_electroionization_grid_convergence_tol;

  // The adjoint electroionization absolute diff tolerance for the scattering distribution
  double d_adjoint_electroionization_absolute_diff_tol;

  // The adjoint electroionization distance tolerance for the scattering distribution
  double d_adjoint_electroionization_distance_tol;
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
