//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleDistribution.hpp
//! \author Alex Robinson
//! \brief  Particle distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_DISTRIBUTION_HPP
#define MONTE_CARLO_PARTICLE_DISTRIBUTION_HPP

// Std Lib Includes
#include <iostream>
#include <memory>

// Boost Includes
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_TypeNameTraits.hpp"
#include "Utility_Set.hpp"

namespace MonteCarlo{

//! The particle distribution base class
class ParticleDistribution
{

public:

  //! The dimension set
  typedef std::set<PhaseSpaceDimension> DimensionSet;

  //! The dimension trial counter map
  typedef PhaseSpaceDimensionDistribution::DimensionCounterMap
  DimensionCounterMap;

  //! Constructor
  ParticleDistribution( const std::string& name );

  //! Destructor
  virtual ~ParticleDistribution()
  { /* ... */ }

  //! Return the name of the region of interest
  const std::string& getName() const;

  //! Return the dimension distribution type name
  virtual std::string getDimensionDistributionTypeName(
                               const PhaseSpaceDimension dimension ) const = 0;

  //! Check if the distribution is spatially uniform (somewhere)
  virtual bool isSpatiallyUniform() const = 0;

  //! Check if the distribution is directionally uniform (isotropic)
  virtual bool isDirectionallyUniform() const = 0;

  //! Initialize dimension counter map
  virtual void initializeDimensionCounters( DimensionCounterMap& trials ) const = 0;

  //! Evaluate the distribution at the desired phase space point
  virtual double evaluate( const ParticleState& particle ) const = 0;

  //! Sample a particle state from the distribution
  virtual void sample( ParticleState& particle ) const = 0;

  //! Sample a particle state from the dist. and record the number of trials
  virtual void sampleAndRecordTrials( ParticleState& particle,
                                      DimensionCounterMap& trials ) const = 0;

  //! Sample a particle state with the desired dimension value
  virtual void sampleWithDimensionValue(
                                      ParticleState& particle,
                                      const PhaseSpaceDimension dimension,
                                      const double dimension_value ) const = 0;

  //! Sample a particle state with the desired dim. value and record trials
  virtual void sampleWithDimensionValueAndRecordTrials(
                                      ParticleState& particle,
                                      DimensionCounterMap& trials,
                                      const PhaseSpaceDimension dimension,
                                      const double dimension_value ) const = 0;

protected:

  //! Default constructor
  ParticleDistribution();

private:

  // Save the state to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the data from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The distribution name
  std::string d_name;
};

// Save the state to an archive
template<typename Archive>
void ParticleDistribution::save( Archive& ar, const unsigned version ) const
{
  ar & BOOST_SERIALIZATION_NVP( d_name );
}

// Load the data from an archive
template<typename Archive>
void ParticleDistribution::load( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_name );
}

} // end MonteCarlo namespace

namespace Utility{

//! Specialization of Utility::TypeNameTraits for MonteCarlo::ParticleDistribution
template<>
struct TypeNameTraits<MonteCarlo::ParticleDistribution>
{
  //! Check if the type has a specialization
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return "ParticleDistribution"; }
};

} // end Utility namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( ParticleDistribution, MonteCarlo );
BOOST_SERIALIZATION_CLASS_VERSION( ParticleDistribution, MonteCarlo, 0 );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, ParticleDistribution );

#endif // end MONTE_CARLO_PARTICLE_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleDistribution.hpp
//---------------------------------------------------------------------------//
