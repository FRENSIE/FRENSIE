//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ElectronElasticDataEvaluator.hpp
//! \author Luke Kersting
//! \brief  The electron elastic data evaluator class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ELECTRON_ELASTIC_DATA_EVALUATOR_HPP
#define DATA_GEN_ELECTRON_ELASTIC_DATA_EVALUATOR_HPP

// Std Lib Includes
#include <utility>
#include <iostream>

// FRENSIE Includes
#include "DataGen_ElasticElectronMomentsEvaluator.hpp"
#include "Data_ENDLDataContainer.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "MonteCarlo_VoidElectroatomicReaction.hpp"
#include "Utility_ArrayView.hpp"
#include "Utility_UnivariateDistribution.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"

namespace DataGen{

//! The electron elastic data evaluator class
class ElectronElasticDataEvaluator
{

public:

  //! Constructor from ENDL data container
  ElectronElasticDataEvaluator(
    const std::shared_ptr<const Data::ENDLDataContainer>& data_container,
    const double min_electron_energy = 1e-5,
    const double max_electron_energy = 1e5,
    const double cutoff_angle_cosine = 0.9,
    const unsigned number_of_moment_preserving_angles = 2,
    const double tabular_evaluation_tol = 1e-7,
    const MonteCarlo::TwoDGridType two_d_grid =
      MonteCarlo::UNIT_BASE_CORRELATED_GRID,
    const MonteCarlo::TwoDInterpolationType two_d_interp =
      MonteCarlo::LOGLOGLOG_INTERPOLATION,
    const MonteCarlo::CoupledElasticSamplingMethod sampling_method =
      MonteCarlo::MODIFIED_TWO_D_UNION,
    const bool generate_new_distribution_at_min_and_max_energy = false );

  //! Constructor from Native data file
  ElectronElasticDataEvaluator(
    const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>& data_container,
    const double min_energy,
    const double max_energy,
    const double cutoff_angle_cosine = 0.9,
    const unsigned number_of_moment_preserving_angles = 2,
    const double tabular_evaluation_tol = 1e-7,
    const MonteCarlo::TwoDGridType two_d_grid =
      MonteCarlo::UNIT_BASE_CORRELATED_GRID,
    const MonteCarlo::TwoDInterpolationType two_d_interp =
      MonteCarlo::LOGLOGLOG_INTERPOLATION,
    const MonteCarlo::CoupledElasticSamplingMethod sampling_method =
      MonteCarlo::MODIFIED_TWO_D_UNION,
    const bool generate_new_distribution_at_min_and_max_energy = false );

  //! Basic Constructor from Native data file
  ElectronElasticDataEvaluator(
    const std::shared_ptr<const Data::ElectronPhotonRelaxationDataContainer>& data_container,
    const bool generate_new_distribution_at_min_and_max_energy = false );

  //! Destructor
  ~ElectronElasticDataEvaluator()
  { /* ... */ }

  //! Set the minimum energy
  void setMinEnergy( const double min_energy );

  //! Return the minimum energy
  double getMinEnergy() const;

  //! Set the maximum energy
  void setMaxEnergy( const double max_energy );

  //! Return the maximum energy
  double getMaxEnergy() const;

  //! Set the cutoff angle cosine
  void setCutoffAngleCosine( const double cutoff_angle_cosine );

  //! Return the cutoff angle cosine
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

  //! Set the electron TwoDGridPolicy (LogLogLog by default)
  void setElectronTwoDGridPolicy( MonteCarlo::TwoDGridType sampling );

  //! Return the electron TwoDGridPolicy
  MonteCarlo::TwoDGridType getElectronTwoDGridPolicy() const;

  //! Set the CoupledElasticSamplingMethod (Modified Two D Union by default)
  void setCoupledElasticSamplingMethod( MonteCarlo::CoupledElasticSamplingMethod method );

  //! Return the CoupledElasticSamplingMethod
  MonteCarlo::CoupledElasticSamplingMethod getCoupledElasticSamplingMethod() const;

  //! Set generate new distribution at the min and max energy off (off by default)
  void setGenerateNewDistributionAtMinAndMaxEnergyOff();

  //! Set generate new distribution at the min and max energy on (off by default)
  void setGenerateNewDistributionAtMinAndMaxEnergyOn();

  //! Return if generate new distribution at the min and max energy is on (off by default)
  bool isGenerateNewDistributionAtMinAndMaxEnergyOn() const;

  //! Evaluate the electron elastic secondary distribution
  void evaluateElasticSecondaryDistribution(
    std::vector<double>& angular_energy_grid,
    std::map<double,std::vector<double> >& elastic_angle,
    std::map<double,std::vector<double> >& elastic_pdf,
    std::vector<double>& moment_preserving_cross_section_reduction,
    std::map<double,std::vector<double> >& moment_preserving_angles,
    std::map<double,std::vector<double> >& moment_preserving_weights,
    const double grid_convergence_tol = 1e-3,
    const double absolute_diff_tol = 1e-13,
    const double distance_tol = 1e-13 ) const;

  //! Create the analog cutoff elastic cross section evaluator
  void createCutoffCrossSectionEvaluator(
    std::shared_ptr<const Utility::UnivariateDistribution>& cross_section_evaluator ) const;

  //! Create the analog cutoff elastic cross section evaluator
  void createCutoffCrossSectionEvaluator(
    std::shared_ptr<MonteCarlo::ElectroatomicReaction>& cross_section_evaluator ) const;

  //! Create the analog total elastic cross section evaluator
  void createTotalCrossSectionEvaluator(
    std::shared_ptr<const Utility::UnivariateDistribution>& cross_section_evaluator ) const;

  //! Create the analog total elastic cross section evaluator
  void createTotalCrossSectionEvaluator(
    std::shared_ptr<MonteCarlo::ElectroatomicReaction>& cross_section_evaluator ) const;

  //! Evaluate the analog screened Rutherford elastic cross section
  void evaluateScreenedRutherfordCrossSection(
    const std::vector<double>& total_elastic_cross_section,
    const std::vector<double>& cutoff_elastic_cross_section,
    std::vector<double>& rutherford_cross_section,
    unsigned& rutherford_cross_section_threshold_energy_index,
    const double evaluation_tolerance = 1e-6 ) const;

protected:

  // Evaluate the electron analog elastic secondary distribution
  void evaluateAnalogElasticSecondaryDistribution(
    std::vector<double>& angular_energy_grid,
    std::map<double,std::vector<double> >& elastic_angle,
    std::map<double,std::vector<double> >& elastic_pdf,
    const double grid_convergence_tol,
    const double absolute_diff_tol,
    const double distance_tol ) const;

  // Evaluate the electron analog elastic secondary distribution on the angular energy grid
  void evaluateAnalogElasticSecondaryDistributionInPlace(
    const std::vector<double>& angular_energy_grid,
    std::map<double,std::vector<double> >& elastic_angle,
    std::map<double,std::vector<double> >& elastic_pdf,
    const double grid_convergence_tol,
    const double absolute_diff_tol,
    const double distance_tol ) const;

  // Evaluate the electron moment preserving elastic secondary distribution
  void evaluateMomentPreservingElasticData(
    const std::vector<double>& angular_energy_grid,
    const std::map<double,std::vector<double> >& elastic_angle,
    const std::map<double,std::vector<double> >& elastic_pdf,
    std::vector<double>& cross_section_reduction,
    std::map<double,std::vector<double> >& moment_preserving_angles,
    std::map<double,std::vector<double> >& moment_preserving_weights ) const;

private:

  // Calculate the elastic moment preserving discrete angle cosines and weights
  void calculateDiscreteAnglesAndWeights(
    const std::shared_ptr<DataGen::ElasticElectronMomentsEvaluator>& moments_evaluator,
    const double& energy,
    std::vector<double>& discrete_angles,
    std::vector<double>& weights,
    double& cross_section_reduction ) const;

  // Calculate the elastic angular distribution for the angle cosine
  void calculateElasticAngleCosine(
    const std::vector<double>& raw_elastic_angle,
    const std::vector<double>& raw_elastic_pdf,
    std::vector<double>& elastic_angle,
    std::vector<double>& elastic_pdf ) const;


  // The atomic number
  double d_atomic_number;

  // The min electron energy
  double d_min_energy;

  // The max electron energy
  double d_max_energy;

  // The cutoff angle cosine
  double d_cutoff_angle_cosine;

  // The number of moment preserving angles
  unsigned d_number_of_moment_preserving_angles;

  // The tabular evaluation tolerance
  double d_tabular_evaluation_tol;

  // The TwoDInterpPolicy
  MonteCarlo::TwoDInterpolationType d_two_d_interp;

  // The TwoDGridPolicy
  MonteCarlo::TwoDGridType d_two_d_grid;

  // The coupled elastic sampling method
  MonteCarlo::CoupledElasticSamplingMethod d_sampling_method;

  // The energy grid for the elastic cross section
  std::shared_ptr<const std::vector<double> > d_energy_grid;

  // The total elastic cross section
  std::shared_ptr<const std::vector<double> > d_total_cross_section;

  // The total elastic cross section threshold energy index
  unsigned d_total_threshold_energy_index;

  // The cutoff elastic cross section
  std::shared_ptr<const std::vector<double> > d_cutoff_cross_section;

  // The cutoff elastic cross section threshold energy index
  unsigned d_cutoff_threshold_energy_index;

  // The elastic angular energy grid
  std::vector<double> d_angular_energy_grid;

  // The map of the cutoff elastic scattering angles
  std::map<double,std::vector<double> > d_elastic_angle;

  // The map of the cutoff elastic scattering pdf
  std::map<double,std::vector<double> > d_elastic_pdf;

  // If true a new secondary distribution will be generated at the max energy
  bool d_generate_new_distribution_at_min_and_max_energy;

};

} // end DataGen namespace


#endif // end DATA_GEN_ELECTRON_ELASTIC_DATA_EVALUATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_ElectronElasticDataEvaluator.hpp
//---------------------------------------------------------------------------//
