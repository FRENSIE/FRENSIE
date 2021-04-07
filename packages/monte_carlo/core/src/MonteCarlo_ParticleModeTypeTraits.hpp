//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleModeTypeTraits.hpp
//! \author Alex Robinson
//! \brief  Particle mode type traits class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_MODE_TYPE_TRAITS_HPP
#define MONTE_CARLO_PARTICLE_MODE_TYPE_TRAITS_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleModeTypeTraitsDecl.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_AdjointPhotonState.hpp"
#include "MonteCarlo_AdjointElectronState.hpp"

namespace MonteCarlo{

/*! Specialization of ParticleModeTypeTraits for NEUTRON_MODE
 * \ingroup particle_mode_type_traits
 */
template<>
struct ParticleModeTypeTraits<NEUTRON_MODE>
{
  //! The active particles
  typedef boost::mpl::set<NeutronState> ActiveParticles;

  //! Check if the particle type is compatible with the mode
  static inline bool isParticleTypeCompatible( const ParticleType type )
  { return (type == NEUTRON ? true : false); }
};

/*! Specialization of ParticleModeTypeTraits for PHOTON_MODE
 * \ingroup particle_mode_type_traits
 */
template<>
struct ParticleModeTypeTraits<PHOTON_MODE>
{
  //! The active particles
  typedef boost::mpl::set<PhotonState> ActiveParticles;

  //! Check if the particle type is compatible with the mode
  static inline bool isParticleTypeCompatible( const ParticleType type )
  { return (type == PHOTON ? true : false); }
};

/*! Specialization of ParticleModeTypeTraits for ELECTRON_MODE
 * \ingroup particle_mode_type_traits
 */
template<>
struct ParticleModeTypeTraits<ELECTRON_MODE>
{
  //! The active particles
  typedef boost::mpl::set<ElectronState> ActiveParticles;

  //! Check if the particle type is compatible with the mode
  static inline bool isParticleTypeCompatible( const ParticleType type )
  { return (type == ELECTRON || type == POSITRON ? true : false); }
};

/*! Specialization of ParticleModeTypeTraits for NEUTRON_PHOTON_MODE
 * \ingroup particle_mode_type_traits
 */
template<>
struct ParticleModeTypeTraits<NEUTRON_PHOTON_MODE>
{
  //! The active particles
  typedef boost::mpl::set<NeutronState,PhotonState> ActiveParticles;

  //! Check if the particle type is compatible with the mode
  static inline bool isParticleTypeCompatible( const ParticleType type )
  { return (type == NEUTRON || type == PHOTON ? true : false); }
};

/*! Specialization of ParticleModeTypeTraits for PHOTON_ELECTRON_MODE
 * \ingroup particle_mode_type_traits
 */
template<>
struct ParticleModeTypeTraits<PHOTON_ELECTRON_MODE>
{
  //! The active particles
  typedef boost::mpl::set<PhotonState,ElectronState> ActiveParticles;

  //! Check if the particle type is compatible with the mode
  static inline bool isParticleTypeCompatible( const ParticleType type )
  { return (type == PHOTON || type == ELECTRON || type == POSITRON ? true : false); }
};

/*! Specialization of ParticleModeTypeTraits for NEUTRON_PHOTON_ELECTRON_MODE
 * \ingroup particle_mode_type_traits
 */
template<>
struct ParticleModeTypeTraits<NEUTRON_PHOTON_ELECTRON_MODE>
{
  //! The active particles
  typedef boost::mpl::set<NeutronState,PhotonState,ElectronState> ActiveParticles;

  //! Check if the particle type is compatible with the mode
  static inline bool isParticleTypeCompatible( const ParticleType type )
  { return (type == NEUTRON || type == PHOTON || type == ELECTRON || type == POSITRON ? true : false); }
};

/*! Specialization of ParticleModeTypeTraits for ADJOINT_PHOTON_MODE
 * \ingroup particle_mode_type_traits
 */
template<>
struct ParticleModeTypeTraits<ADJOINT_PHOTON_MODE>
{
  //! The active particles
  typedef boost::mpl::set<AdjointPhotonState> ActiveParticles;

  //! Check if the particle type is compatible with the mode
  static inline bool isParticleTypeCompatible( const ParticleType type )
  { return (type == ADJOINT_PHOTON ? true : false); }
};

/*! Specialization of ParticleModeTypeTraits for ADJOINT_ELECTRON_MODE
 * \ingroup particle_mode_type_traits
 */
template<>
struct ParticleModeTypeTraits<ADJOINT_ELECTRON_MODE>
{
  //! The active particles
  typedef boost::mpl::set<AdjointElectronState> ActiveParticles;

  //! Check if the particle type is compatible with the mode
  static inline bool isParticleTypeCompatible( const ParticleType type )
  { return (type == ADJOINT_ELECTRON ? true : false); }
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_MODE_TYPE_TRAITS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleModeTypeTraits.hpp
//---------------------------------------------------------------------------//
