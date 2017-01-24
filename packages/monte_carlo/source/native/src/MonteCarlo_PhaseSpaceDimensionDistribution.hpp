//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhaseSpaceDimensionDistribution.hpp
//! \author Alex Robinson
//! \brief  Phase space dimension distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHASE_SPACE_DIMENSION_HPP
#define MONTE_CARLO_PHASE_SPACE_DIMENSION_HPP

// Std Lib Includes
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "MonteCarlo_PhaseSpaceDimensionClass.hpp"
#include "MonteCarlo_PhaseSpacePoint.hpp"
#include "Utility_OneDDistributionType.hpp"

namespace MonteCarlo{

//! The phase space dimension distribution class
class PhaseSpaceDimensionDistribution
{

public:

  //! The trial counter
  typedef unsigned long long TrialCounter;

  //! The dimension trial counter map
  typedef std::map<PhaseSpaceDimension,TrialCounter> DimensionTrialCounterMap;

  //! Constructor
  PhaseSpaceDimensionDistribution();

  //! Destructor
  virtual ~PhaseSpaceDimensionDistribution()
  { /* ... */ }

  //! Return the phase space dimension
  virtual PhaseSpaceDimension getDimension() const = 0;

  //! Return the phase space dimension class
  virtual PhaseSpaceDimensionClass getDimensionClass() const = 0;

  //! Check if the dimension distribution is independent
  virtual bool isIndependent() const = 0;

  //! Check if the dimension is dependent on the dimension of interest
  virtual bool isDependentOnDimension(
                               const PhaseSpaceDimension dimension ) const = 0;

  //! Check if the dimension distribution is continuous
  virtual bool isContinuous() const = 0;

  //! Check if the dimension distribution is tabular
  virtual bool isTabular() const = 0;

  //! Check if the dimension distribution is uniform (somewhere)
  virtual bool isUniform() const;

  //! Check if the underlying distribution has the form of interest
  virtual bool hasForm(
                      const OneDDistributionType distribution_type ) const = 0;

  //! Evaluate the dimension distribution with a cascade to the dependent dists
  double evaluateWithCascade( const PhaseSpacePoint& phase_space_point ) const;

  //! Evaluate the dimension distribution without cascade to dependent dists.
  virtual double evaluateWithoutCascade(
                          const PhaseSpacePoint& phase_space_point ) const = 0;

  //! Sample a dimension value and cascade to the dependent distributions
  void sampleWithCascade( PhaseSpacePoint& phase_space_sample ) const;

  //! Sample a dimension value without a cascade to the dependent dists.
  virtual void sampleWithoutCascade(
                               PhaseSpacePoint& phase_space_sample ) const = 0;

  //! Sample a dimension value and cascade to the dependent distributions 
  void sampleAndRecordTrialsWithCascade(
                                      PhaseSpacePoint& phase_space_sample,
                                      DimensionTrialCounterMap& trials ) const;

  //! Sample a dimension value without a cascade to the dependent dists.
  virtual void sampleAndRecordTrialsWithoutCascade(
                                           PhaseSpacePoint& phase_space_sample,
                                           TrialCounter& trials ) const = 0;

  //! Sample a dimension value and cascade to the dependent distributions
  void sampleWithCascadeUsingDimensionValue(
                                        PhaseSpacePoint& phase_space_sample,
                                        const PhaseSpaceDimension dimension,
                                        const double dimension_value ) const;

  //! Set the dimension value, weight appropriately and record the trials
  void sampleAndRecordTrailsWithCascadeUsingDimensionValue(
                                          PhaseSpacePoint& phase_space_sample,
                                          DimensionTrialCounterMap& trials,
                                          const PhaseSpaceDimension dimension,
                                          const double dimension_value ) const;

  //! Set the dimension value (weight appropriately)
  virtual void setDimensionValueAndApplyWeight(
                                      PhaseSpacePoint& phase_space_sample,
                                      const double dimension_value ) const = 0;

  //! Add a dependent dimension
  void addDependentDimension(
                  const std::shared_ptr<const PhaseSpaceDimensionDistribution>&
                  dependent_dimension );

private:

  // Evaluate the dependent dimension dists. at the desired phase space point
  double evaluateDependentDistributions(
                              const PhaseSpacePoint& phase_space_point ) const;

  // Sample from all of the dependent dimensions
  void sampleFromDependentDistributions(
                                   PhaseSpacePoint& phase_space_sample ) const;

  // Sample from all of the dependent dimensions and record trials
  void sampleFromDependentDistributionsAndRecordTrials(
                              PhaseSpacePoint& phase_space_sample,
                              DimensionTrialCounterMap& trials ) const;

  // Sample from all of the dependent dimensions using the dimension value
  void sampleFromDependentDistributionsUsingDimensionValue(
                                          PhaseSpacePoint& phase_space_sample,
                                          const PhaseSpaceDimension dimension,
                                          const double dimension_value ) const;

  // Sample from all of the dependent dims. and record trials using dim. value
  void sampleFromDependentDistributionsAndRecordTrialsUsingDimensionValue(
                                          PhaseSpacePoint& phase_space_sample,
                                          DimensionTrailCounterMap& trials,
                                          const PhaseSpaceDimension dimension,
                                          const double dimension_value ) const;

  // The dependent dimensions
  typedef std::map<PhaseSpaceDimension,std::shared_ptr<const PhaseSpaceDimensionDistribution> > DimensionDependentDistributionMap
  DimensionDependentDistributionMap d_dependent_dimension_distributions;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHASE_SPACE_DIMENSION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceDimensionDistribution.hpp
//---------------------------------------------------------------------------//
