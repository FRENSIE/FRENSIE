//---------------------------------------------------------------------------//
//!
//! \file   DataGen_StandardAdjointElectronPhotonRelaxationDataGenerator.hpp
//! \author Luke Kersting
//! \brief  The standard electron-photon-relaxation data generator class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_STANDARD_ADJOINT_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP
#define DATA_GEN_STANDARD_ADJOINT_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP

// Std Lib Includes
#include <utility>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "DataGen_AdjointElectronPhotonRelaxationDataGenerator.hpp"
#include "DataGen_AdjointBremsstrahlungCrossSectionEvaluator.hpp"
#include "DataGen_AdjointElectroionizationSubshellCrossSectionEvaluator.hpp"
#include "DataGen_ElasticElectronMomentsEvaluator.hpp"
#include "Data_ENDLDataContainer.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_OneDDistribution.hpp"

namespace DataGen{

//! The standard adjoint electron-photon-relaxation data generator class
class StandardAdjointElectronPhotonRelaxationDataGenerator : public AdjointElectronPhotonRelaxationDataGenerator
{

public:

  //! Constructor
  StandardAdjointElectronPhotonRelaxationDataGenerator(
        const unsigned atomic_number,
        const std::shared_ptr<const Data::XSSEPRDataExtractor>& ace_epr_data,
        const std::shared_ptr<const Data::ENDLDataContainer>& forward_endl_data,
        const double min_photon_energy,
        const double max_photon_energy,
        const double min_electron_energy,
        const double max_electron_energy,
        const double cutoff_angle_cosine = 1.0,
        const unsigned number_of_moment_preserving_angles = 0,
        const double adjoint_bremsstrahlung_evaluation_tolerance = 0.001,
        const double grid_convergence_tol = 0.001,
        const double grid_absolute_diff_tol = 1e-13,
        const double grid_distance_tol = 1e-13 );

  //! Destructor
  ~StandardAdjointElectronPhotonRelaxationDataGenerator()
  { /* ... */ }

  //! Populate the adjoint electron-photon-relaxation data container
  void populateEPRDataContainer(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const;

  //! Repopulate the adjoint electron moment preserving data
  static void repopulateAdjointMomentPreservingData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container,
    const double cutoff_angle_cosine = 0.9,
    const unsigned number_of_moment_preserving_angles = 1 );

protected:

  // Set the adjoint atomic data
  void setAdjointRelaxationData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const;

  // Set the adjoint photon data
  void setAdjointPhotonData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const;

  // Set the adjoint electron data
  void setAdjointElectronData(
    Data::AdjointElectronPhotonRelaxationVolatileDataContainer& data_container ) const;

private:

  // Test if a value is greater than or equal to one
  static bool greaterThanOrEqualToOne( const double value );

  // Test if a value is greater than one
  static bool greaterThanOne( const double value );

  // The if a value is not equal to zero
  static bool notEqualZero( const double value );

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
  void createAdjointCrossSectionOnUnionEnergyGrid(
   const std::list<double>& union_energy_grid,
   const std::shared_ptr<const Utility::OneDDistribution>& original_cross_section,
   std::vector<double>& cross_section,
   unsigned& threshold_index ) const;

  // Create the cross section on the union energy grid
  void createAdjointCrossSectionOnUnionEnergyGrid(
   const std::list<double>& union_energy_grid,
   const std::shared_ptr<DataGen::AdjointBremsstrahlungCrossSectionEvaluator>
        adjoint_bremsstrahlung_cs_evaluator,
   std::vector<double>& cross_section,
   unsigned& threshold_index ) const;

  // Create the cross section on the union energy grid
  void createAdjointCrossSectionOnUnionEnergyGrid(
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

  // The ACE forward data
  std::shared_ptr<const Data::XSSEPRDataExtractor> d_ace_epr_data;

  // The EDNL forward epr data
  std::shared_ptr<const Data::ENDLDataContainer> d_forward_endl_data;

  // The min photon energy
  double d_min_photon_energy;

  // The max photon energy
  double d_max_photon_energy;

  // The min electron energy
  double d_min_electron_energy;

  // The max electron energy
  double d_max_electron_energy;

  // The cutoff angle cosine above which screened rutherford is used
  double d_cutoff_angle_cosine;

  // The grid convergence tolerance
  double d_grid_convergence_tol;

  // The grid absolute difference tolerance
  double d_grid_absolute_diff_tol;

  // The grid distance tolerance
  double d_grid_distance_tol;

  // The number of moment preserving angles
  int d_number_of_moment_preserving_angles;

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

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "DataGen_StandardAdjointElectronPhotonRelaxationDataGenerator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_GEN_STANDARD_ADJOINT_ELECTRON_PHOTON_RELAXATION_DATA_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_StandardAdjointElectronPhotonRelaxationDataGenerator.hpp
//---------------------------------------------------------------------------//
