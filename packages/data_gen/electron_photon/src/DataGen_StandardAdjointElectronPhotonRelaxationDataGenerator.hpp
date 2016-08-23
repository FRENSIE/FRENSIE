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
#include "DataGen_AdjointBremsstrahlungCrossSectionEvaluator.hpp"
#include "DataGen_AdjointElectroionizationSubshellCrossSectionEvaluator.hpp"
#include "DataGen_AdjointIncoherentGridGenerator.hpp"
#include "DataGen_ElasticElectronMomentsEvaluator.hpp"
#include "DataGen_AdjointIncoherentGridGenerator.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_SubshellIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "Utility_OneDDistribution.hpp"

namespace DataGen{

//! The standard adjoint electron-photon-relaxation data generator class
class StandardAdjointElectronPhotonRelaxationDataGenerator : public AdjointElectronPhotonRelaxationDataGenerator
{

public:

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

  //! Set the adjoint pair production energy dist. norm const. evaluation tol.
  void setAdjointPairProductionEnergyDistNormConstEvaluationTolerance(
                                                 const double evaluation_tol );

  //! Get the adjoint pair production energy dist. norm const. evaluation tol
  double getAdjointPairProductionEnergyDistNormConstEvaluationTolerance() const;

  //! Set the adjoint triplet production energy dist. norm const. evaluation tol.
  void setAdjointTripletProductionEnergyDistNormConstEvaluationTolerance(
                                                 const double evaluation_tol );

  //! Get the adjoint triplet production energy dist. norm const. evaluation tol
  double getAdjointTripletProductionEnergyDistNormConstEvaluationTolerance() const;

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
  void setAdjointIncoherentEvaluationTolerance( const double evaluation_tol );

  //! Return the adjoint incoherent cross section evaluation tolerance
  double getAdjointIncoherentCrossSectionEvaluationTolerance() const;

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

  //! Set the cutoff angle cosine above which screened rutherford is used
  void setCutoffAngleCosine( const double cutoff_angle_cosine );

  //! Get the cutoff angle cosine above which screened rutherford is used
  double getCutoffAngleCosine() const;

  //! Set the number of moment preserving angles
  void setNumberOfMomentumPreservingAngles(
                           const unsigned number_of_moment_preserving_angles );

  //! Get the number of moment preserving angles
  unsigned getNumberOfMomentumPreservingAngles() const;
  
  //! Set the evaluation tolerance for the adjoint bremsstrahlung cross section
  void setAdjointBremsstrahlungCrossSectionEvaluationTolerance(
                                           const double evaluation_tolerance );
  
  //! Get the evaluation tolerance for the adjoint bremsstrahlung cross section
  double getAdjointBremsstrahlungCrossSectionEvaluationTolerance() const;

  //! Populate the adjoint electron-photon-relaxation data container
  void populateEPRDataContainer(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const;

  //! Repopulate the adjoint electron moment preserving data
  static void repopulateAdjointMomentPreservingData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container,
    const double cutoff_angle_cosine = 0.9,
    const unsigned number_of_moment_preserving_angles = 1,
    std::ostream& os_log = std::cout );
  
protected:

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

  // Create the cross section on the union energy grid
  void createCrossSectionOnUnionEnergyGrid(
          const std::list<double>& union_energy_grid,
          const std::shared_ptr<const Utility::OneDDistribution>& cs_evaluator,
          std::vector<double>& cross_section ) const;

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

  // Set the electron cross section union energy grid
  void setAdjointElectronCrossSectionsData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container,
    bool recalculate_union_energy_grid = false ) const;

  // Set the adjoint moment preserving data
  static void setAdjointMomentPreservingData(
    std::vector<double>& elastic_energy_grid,
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container );

  // Initialize the electron union energy grid
  void initializeAdjointElectronUnionEnergyGrid(
     const Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container,
     std::list<double>& union_energy_grid ) const;

  // Create the cross section on the union energy grid
  void createCrossSectionOnUnionEnergyGrid(
   const std::list<double>& union_energy_grid,
   const std::shared_ptr<const Utility::OneDDistribution>& original_cross_section,
   std::vector<double>& cross_section,
   unsigned& threshold_index ) const;
  
  // Create the cross section on the union energy grid
  void createCrossSectionOnUnionEnergyGrid(
   const std::list<double>& union_energy_grid,
   const std::shared_ptr<DataGen::AdjointBremsstrahlungCrossSectionEvaluator>
        adjoint_bremsstrahlung_cs_evaluator,
   std::vector<double>& cross_section,
   unsigned& threshold_index ) const;

  // Create the cross section on the union energy grid
  void createCrossSectionOnUnionEnergyGrid(
   const std::list<double>& union_energy_grid,
   const std::list<double>& old_union_energy_grid,
   const std::vector<double>& old_cross_section,
   const std::shared_ptr<DataGen::AdjointBremsstrahlungCrossSectionEvaluator>
        adjoint_bremsstrahlung_cs_evaluator,
   std::vector<double>& cross_section,
   unsigned& threshold_index ) const;

  // Merge the electron union energy grid
  void mergeAdjointElectronUnionEnergyGrid(
    const std::vector<double>& energy_grid,
    std::list<double>& union_energy_grid ) const;

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

  // Generate adjoint elastic moment preserving cross section
  static void evaluateAdjointMomentPreservingCrossSection(
    const Teuchos::ArrayRCP<double>& electron_energy_grid,
    const Teuchos::RCP<MonteCarlo::AnalogElasticElectroatomicReaction<Utility::LinLin> >&
        analog_reaction,
    const std::shared_ptr<const MonteCarlo::AnalogElasticElectronScatteringDistribution>&
        analog_distribution,
    const std::shared_ptr<const Utility::OneDDistribution>& reduction_distribution,
    const double cutoff_angle_cosine,
    const unsigned threshold_energy_index,
    std::vector<double>& moment_preserving_cross_section );

  // Create the adjoint bremsstrahlung cross section evaluator
  void createAdjointBremsstrahlungCrossSectionEvaluator(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container,
    std::shared_ptr<DataGen::AdjointBremsstrahlungCrossSectionEvaluator>&
        adjoint_bremsstrahlung_cs_evaluator ) const;

  // Generate adjoint bremsstrahlung photon energy distribution
  void evaluateAdjointBremsstrahlungPhotonDistribution(
    const double incoming_adjoint_energy,
    const unsigned bin_index,
    const unsigned threshold_energy_index,
    const Teuchos::ArrayRCP<const double>& adjoint_cross_section,
    const Teuchos::ArrayRCP<const double>& adjoint_electron_energy_grid,
    const std::shared_ptr<DataGen::AdjointBremsstrahlungCrossSectionEvaluator>
        adjoint_bremsstrahlung_cs_evaluator,
    const std::vector<double>& adjoint_bremsstrahlung_photon_energy,
    std::vector<double>& adjoint_bremsstrahlung_pdf ) const;

  // Create the adjoint electroionization subshell cross section evaluator
  void createAdjointElectroionizationSubshellCrossSectionEvaluator(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container,
    std::shared_ptr<DataGen::AdjointElectroionizationSubshellCrossSectionEvaluator>&
        adjoint_electroionization_cs_evaluator ) const;

  // The threshold energy nudge factor
  static const double s_threshold_energy_nudge_factor;

  // The forward data
  std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>
  d_forward_epr_data;

  // The log stream
  std::ostream* d_os_log;

  // The adjoint pair production energy dist norm constant evaluation tolerance
  double d_adjoint_pair_production_energy_dist_norm_const_evaluation_tol;

  // The adjoint triplet production energy dist norm constant evaluation tol
  double d_adjoint_triplet_production_energy_dist_norm_const_evaluation_tol;

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

  // The cutoff angle cosine above which screened rutherford is used
  double d_cutoff_angle_cosine;

  // The number of moment preserving angles
  unsigned d_number_of_moment_preserving_angles;

  // The evaluation tolerance for the adjoint bremsstrahlung cross sections
  double d_adjoint_bremsstrahlung_evaluation_tolerance;

  // The adjoint bremsstrahlung cross section evaluator
  std::shared_ptr<DataGen::AdjointBremsstrahlungCrossSectionEvaluator>
    d_adjoint_bremsstrahlung_cs_evaluator;
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

#endif // end DATA_GEN_STANDARD_ADJOINT_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_StandardAdjointElectronPhotonRelaxationDataGenerator.hpp
//---------------------------------------------------------------------------//
