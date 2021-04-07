//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_FullPhaseSpaceParticleResponseFunction.hpp
//! \author Alex Robinson
//! \brief  Full phase-space particle response function class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_FULL_PHASE_SPACE_PARTICLE_RESPONSE_FUNCTION_HPP
#define MONTE_CARLO_FULL_PHASE_SPACE_PARTICLE_RESPONSE_FUNCTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ParticleResponseFunction.hpp"
#include "MonteCarlo_ParticleDistribution.hpp"

namespace MonteCarlo{

//! The detailed response function class
class FullPhaseSpaceParticleResponseFunction : public ParticleResponseFunction
{

public:

  //! Constructor
  FullPhaseSpaceParticleResponseFunction(
            const std::shared_ptr<const ParticleDistribution>& particle_dist );

  //! Destructor
  ~FullPhaseSpaceParticleResponseFunction()
  { /* ... */ }

  //! Evaluate the response function at the desired phase space point
  double evaluate( const ParticleState& particle ) const final override;

  //! Check if the response function is spatially uniform
  bool isSpatiallyUniform() const final override;

  //! Get a description of the response function
  std::string description() const final override;

private:

  //! Default constructor
  FullPhaseSpaceParticleResponseFunction()
  { /* ... */ }

  // Serialize the response function data
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The particle distribution
  std::shared_ptr<const ParticleDistribution> d_particle_dist;
};

// Serialize the response function data
template<typename Archive>
void FullPhaseSpaceParticleResponseFunction::serialize( Archive& ar, const unsigned version )
{
  // Serialize the base class data
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( ParticleResponseFunction );

  // Serialize the local data
  ar & BOOST_SERIALIZATION_NVP( d_particle_dist );
}
  
} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( FullPhaseSpaceParticleResponseFunction, MonteCarlo, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( FullPhaseSpaceParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, FullPhaseSpaceParticleResponseFunction );

#endif // end MONTE_CARLO_FULL_PHASE_SPACE_PARTICLE_RESPONSE_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_FullPhaseSpaceParticleResponseFunction.hpp
//---------------------------------------------------------------------------//
