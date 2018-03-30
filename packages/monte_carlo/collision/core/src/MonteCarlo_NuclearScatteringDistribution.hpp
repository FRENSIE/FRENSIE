//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The nuclear scattering distribution base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NUCLEAR_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_NUCLEAR_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_ScatteringDistribution.hpp"

namespace MonteCarlo{

//! The nuclear scattering distribution
template<typename IncomingParticleType, typename OutgoingParticleType>
class NuclearScatteringDistribution : public ScatteringDistribution
{

public:

  //! The incoming particle state
  typedef IncomingParticleType IncomingParticleState;

  //! The outgoing particle state
  typedef OutgoingParticleType OutgoingParticleState;

  //! Constructor
  NuclearScatteringDistribution( const double atomic_weight_ratio );

  //! Destructor
  virtual ~NuclearScatteringDistribution()
  { /* ... */ }

  //! Sample an outgoing particle state given an incoming particle state
  virtual void scatterParticle( const IncomingParticleState& incoming_particle,
				OutgoingParticleState& outgoing_particle,
				const double temperature ) const = 0;

  //! Sample an outgoing particle state given an incoming particle state
  void scatterParticle( const IncomingParticleState& incoming_particle,
			OutgoingParticleState& outgoing_particle ) const;

protected:

  //! Return the atomic weight ratio
  double getAtomicWeightRatio() const;

private:

  // The atomic weight of the nuclide in units of neutron mass
  double d_atomic_weight_ratio;
};

/*! \brief The nuclear scattering distribution partial specialization for
 * incoming and outgoing particle types that are the same.
 */
template<typename ParticleType>
class NuclearScatteringDistribution<ParticleType,ParticleType> : public ScatteringDistribution
{

public:

  //! The incoming particle state
  typedef ParticleType IncomingParticleState;

  //! The outgoing particle state
  typedef ParticleType OutgoingParticleState;

  //! Constructor
  NuclearScatteringDistribution( const double atomic_weight_ratio );

  //! Destructor
  virtual ~NuclearScatteringDistribution()
  { /* ... */ }

  //! Sample an outgoing particle state given an incoming particle state
  virtual void scatterParticle( const ParticleType& incoming_particle,
				ParticleType& outgoing_particle,
				const double temperature ) const = 0;

  //! Sample an outgoing particle state given an incoming particle state
  virtual void scatterParticle( ParticleType& particle,
				const double temperature ) const;

  //! Sample an outgoing particle state given an incoming particle state
  void scatterParticle( ParticleType& particle ) const;

protected:

  //! Return the atomic weight ratio
  double getAtomicWeightRatio() const;

private:

  // The atomic weight of the nuclide in units of neutron mass
  double d_atomic_weight_ratio;
};

// Sample an outgoing particle state given an incoming particle state
template<typename ParticleType>
inline void NuclearScatteringDistribution<ParticleType,ParticleType>::scatterParticle(
					       ParticleType& particle,
					       const double temperature ) const
{
  this->scatterParticle( particle, particle, temperature );
}

// Sample an outgoing particle state given an incoming particle state
template<typename IncomingParticleType, typename OutgoingParticleType>
inline void NuclearScatteringDistribution<IncomingParticleType,OutgoingParticleType>::scatterParticle(
			       const IncomingParticleType& incoming_particle,
			       OutgoingParticleType& outgoing_particle ) const
{
  this->scatterParticle( incoming_particle, outgoing_particle, 0.0 );
}

// Sample an outgoing particle state given an incoming particle state
template<typename ParticleType>
inline void NuclearScatteringDistribution<ParticleType,ParticleType>::scatterParticle(
 				                ParticleType& particle ) const
{
  this->scatterParticle( particle, 0.0 );
}

// Return the atomic weight ratio
template<typename IncomingParticleType, typename OutgoingParticleType>
inline double
NuclearScatteringDistribution<IncomingParticleType,OutgoingParticleType>::getAtomicWeightRatio() const
{
  return d_atomic_weight_ratio;
}

// Return the atomic weight ratio
template<typename ParticleType>
inline double
NuclearScatteringDistribution<ParticleType,ParticleType>::getAtomicWeightRatio() const
{
  return d_atomic_weight_ratio;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_NuclearScatteringDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_NUCLEAR_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearScatteringDistribution.hpp
//---------------------------------------------------------------------------//
