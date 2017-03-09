//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleModeTypeTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  Particle mode type traits class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_MODE_TYPE_TRAITS_DECL_HPP
#define MONTE_CARLO_PARTICLE_MODE_TYPE_TRAITS_DECL_HPP

// Boost Includes
#include <boost/mpl/set.hpp>

// FRENSIE Includes
#include "Utility_UndefinedTraits.hpp"

/*! \defgroup particle_mode_type_traits Particle Mode Type Traits
 * \ingroup traits
 *
 */

namespace MonteCarlo{

/*! \brief
 *
 * \ingroup particle_mode_type_traits
 */
template<ParticleModeType mode>
struct ParticleModeTypeTraits
{
  //! The active particles (specialization should use boost::mpl::set)
  typedef UndefinedTraits<void>::DesiredTypeIsMissingSpecialization ActiveParticles;

  //! Check if the particle type is compatible with the mode
  static inline bool isParticleTypeCompatible( const ParticleType type )
  { (void)UndefinedTraits<void>::notDefined(); return false; }
};

//! Check if the particle type is compatible with the mode
template<ParticleModeType mode>
inline bool isParticleTypeCompatible( const ParticleType type )
{
  return ParticleModeTypeTraits<mode>::isParticleTypeCompatible( type );
}
  
} // end Utility namespace

#endif // end MONTE_CARLO_PARTICLE_MODE_TYPE_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleModeTypeTraitsDecl.hpp
//---------------------------------------------------------------------------//
