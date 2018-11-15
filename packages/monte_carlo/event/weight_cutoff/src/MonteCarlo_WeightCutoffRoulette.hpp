//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_WeightCutoffRoulette.hpp
//! \author Luke Kersting
//! \brief  Weight cutoff roulette class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_WEIGHT_CUTOFF_ROULETTE_HPP
#define MONTE_CARLO_WEIGHT_CUTOFF_ROULETTE_HPP

// // Boost Includes
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ParticleType.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace MonteCarlo{

/*! The wight cutoff roulette class
 *
 * This class roulettes particles below a cutoff weight.
 */
class WeightCutoffRoulette
{

public:

  //! The particle weight type
  typedef double WeightType;

  //! Get the default weight cutoff roulette
  static std::shared_ptr<const WeightCutoffRoulette> getDefault();

  //! Default Constructor
  WeightCutoffRoulette()
  { /* ... */ }

  //! Destructor
  virtual ~WeightCutoffRoulette()
  { /* ... */ }

  //! Return the roulette cutoff weights for the specified particle type
  virtual void getCutoffWeights( const ParticleType particle_type,
                                 WeightType& threshold_weight,
                                 WeightType& survival_weight ) const = 0;

  //! Return the particle types that will have weight cutoff rouletting
  virtual void getParticleTypes( std::set<ParticleType>& particle_types ) const = 0;

  //! Update the particle state and bank
  virtual void rouletteParticleWeight( ParticleState& particle ) const = 0;

private:

  // Serialize the weight cutoff roulette data to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { /* ... */ }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( WeightCutoffRoulette, MonteCarlo, 0 );
BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( WeightCutoffRoulette, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, WeightCutoffRoulette );

#endif // end MONTE_CARLO_WEIGHT_CUTOFF_ROULETTE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_WeightCutoffRoulette.hpp
//---------------------------------------------------------------------------//
