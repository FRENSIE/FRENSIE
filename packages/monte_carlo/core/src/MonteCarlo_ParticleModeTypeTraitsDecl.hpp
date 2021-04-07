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
#include "MonteCarlo_ParticleModeType.hpp"
#include "MonteCarlo_ParticleType.hpp"
#include "Utility_UndefinedTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"

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
  typedef Utility::UndefinedTraits<void>::DesiredTypeIsMissingSpecialization ActiveParticles;

  //! Check if the particle type is compatible with the mode
  static inline bool isParticleTypeCompatible( const ParticleType type )
  { (void)Utility::UndefinedTraits<void>::notDefined(); return false; }
};

//! Check if the particle type is compatible with the mode
template<ParticleModeType mode>
inline bool isParticleTypeCompatible( const ParticleType type )
{
  return ParticleModeTypeTraits<mode>::isParticleTypeCompatible( type );
}

/*! Check if the source particle type is compatible with the particle mode type
 * \details This method provides runtime support for particle mode/particle 
 * type compatibility checking.
 */
inline bool isParticleTypeCompatible( const ParticleModeType particle_mode,
                                      const ParticleType particle_type )
{
  switch( particle_mode )
  {
  case NEUTRON_MODE:
    return isParticleTypeCompatible<NEUTRON_MODE>( particle_type );
  case PHOTON_MODE:
    return isParticleTypeCompatible<PHOTON_MODE>( particle_type );
  case ELECTRON_MODE:
    return isParticleTypeCompatible<ELECTRON_MODE>( particle_type );
  case NEUTRON_PHOTON_MODE:
    return isParticleTypeCompatible<NEUTRON_PHOTON_MODE>( particle_type );
  case PHOTON_ELECTRON_MODE:
    return isParticleTypeCompatible<PHOTON_ELECTRON_MODE>( particle_type );
  case NEUTRON_PHOTON_ELECTRON_MODE:
    return isParticleTypeCompatible<NEUTRON_PHOTON_ELECTRON_MODE>( particle_type );
  case ADJOINT_PHOTON_MODE:
    return isParticleTypeCompatible<ADJOINT_PHOTON_MODE>( particle_type );
  case ADJOINT_ELECTRON_MODE:
    return isParticleTypeCompatible<ADJOINT_ELECTRON_MODE>( particle_type );
  default:
    THROW_EXCEPTION( std::logic_error,
		     "Error: ParticleModeType " << (int)particle_mode <<
		     " is not supported!" );
  }
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_MODE_TYPE_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleModeTypeTraitsDecl.hpp
//---------------------------------------------------------------------------//
