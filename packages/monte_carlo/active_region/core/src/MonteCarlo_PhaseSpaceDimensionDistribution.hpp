//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhaseSpaceDimensionDistribution.hpp
//! \author Alex Robinson
//! \brief  Phase space dimension distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP
#define MONTE_CARLO_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>
#include <string>

// Boost Includes
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/weak_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "MonteCarlo_PhaseSpaceDimensionClass.hpp"
#include "MonteCarlo_PhaseSpacePoint.hpp"
#include "Utility_UnivariateDistributionType.hpp"
#include "Utility_DistributionTraits.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_Map.hpp"
#include "Utility_Set.hpp"

namespace MonteCarlo{

/*! The phase space dimension distribution class
 *
 * All PhaseSpaceDimensionDistribution objects must be managed
 * through std::shared_ptr. Failure to do this will result in undefined
 * behavior.
 */
class PhaseSpaceDimensionDistribution : public std::enable_shared_from_this<PhaseSpaceDimensionDistribution>
{

public:

  //! The trial counter type
  typedef Utility::DistributionTraits::Counter Counter;

  //! The dimension trial counter map
  typedef std::map<PhaseSpaceDimension,Counter> DimensionCounterMap;

  //! The dependent dimension set
  typedef std::set<PhaseSpaceDimension> DependentDimensionSet;

  //! Constructor
  PhaseSpaceDimensionDistribution();

  //! Destructor
  virtual ~PhaseSpaceDimensionDistribution()
  { /* ... */ }

  //! Return the phase space dimension
  virtual PhaseSpaceDimension getDimension() const = 0;

  //! Return the phase space dimension class
  virtual PhaseSpaceDimensionClass getDimensionClass() const = 0;

  //! Get the distribution type name
  virtual std::string getDistributionTypeName() const = 0;

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
       const Utility::UnivariateDistributionType distribution_type ) const = 0;

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
                                      DimensionCounterMap& trials ) const;

  //! Sample a dimension value without a cascade to the dependent dists.
  virtual void sampleAndRecordTrialsWithoutCascade(
                                           PhaseSpacePoint& phase_space_sample,
                                           Counter& trials ) const = 0;

  //! Sample a dimension value and cascade to the dependent distributions
  void sampleWithCascadeUsingDimensionValue(
                                        PhaseSpacePoint& phase_space_sample,
                                        const PhaseSpaceDimension dimension,
                                        const double dimension_value ) const;

  //! Set the dimension value, weight appropriately and record the trials
  void sampleAndRecordTrialsWithCascadeUsingDimensionValue(
                                          PhaseSpacePoint& phase_space_sample,
                                          DimensionCounterMap& trials,
                                          const PhaseSpaceDimension dimension,
                                          const double dimension_value ) const;

  //! Set the dimension value (weight appropriately)
  virtual void setDimensionValueAndApplyWeight(
                                      PhaseSpacePoint& phase_space_sample,
                                      const double dimension_value ) const = 0;

  //! Check if the distribution has a parent
  bool hasParentDistribution() const;

  //! Get the parent distribution
  const PhaseSpaceDimensionDistribution& getParentDistribution() const;

  //! Add a dependent distribution
  void addDependentDistribution(
                        const std::shared_ptr<PhaseSpaceDimensionDistribution>&
                        dependent_dimension );

  //! Remove dependent distributions
  void removeDependentDistributions();

  //! Get the dependent dimensions
  void getDependentDimensions( DependentDimensionSet& dependent_dimensions ) const;

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
                                           DimensionCounterMap& trials ) const;

  // Sample from all of the dependent dimensions using the dimension value
  void sampleFromDependentDistributionsUsingDimensionValue(
                                          PhaseSpacePoint& phase_space_sample,
                                          const PhaseSpaceDimension dimension,
                                          const double dimension_value ) const;

  // Sample from all of the dependent dims. and record trials using dim. value
  void sampleFromDependentDistributionsAndRecordTrialsUsingDimensionValue(
                                          PhaseSpacePoint& phase_space_sample,
                                          DimensionCounterMap& trials,
                                          const PhaseSpaceDimension dimension,
                                          const double dimension_value ) const;

  // Save the state to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The parent distribution
  std::weak_ptr<const PhaseSpaceDimensionDistribution> d_parent_distribution;

  // The dependent dimensions
  typedef std::map<PhaseSpaceDimension,std::shared_ptr<PhaseSpaceDimensionDistribution> > DimensionDependentDistributionMap;
  DimensionDependentDistributionMap d_dependent_dimension_distributions;
};

// Save the state to an archive
template<typename Archive>
void PhaseSpaceDimensionDistribution::save( Archive& ar,
                                            const unsigned version ) const
{
  ar & BOOST_SERIALIZATION_NVP( d_parent_distribution );
  ar & BOOST_SERIALIZATION_NVP( d_dependent_dimension_distributions );
}

// Load the data from an archive
template<typename Archive>
void PhaseSpaceDimensionDistribution::load( Archive& ar,
                                            const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_parent_distribution );
  ar & BOOST_SERIALIZATION_NVP( d_dependent_dimension_distributions );
}

} // end MonteCarlo namespace


BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( PhaseSpaceDimensionDistribution, MonteCarlo );
BOOST_SERIALIZATION_CLASS_VERSION( PhaseSpaceDimensionDistribution, MonteCarlo, 0 );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, PhaseSpaceDimensionDistribution );

#endif // end MONTE_CARLO_PHASE_SPACE_DIMENSION_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceDimensionDistribution.hpp
//---------------------------------------------------------------------------//
