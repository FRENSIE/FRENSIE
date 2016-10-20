//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronCollisionHandler.hpp
//! \author Alex Robinson
//! \brief  Neutron collision handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NEUTRON_COLLISION_HANDLER_HPP
#define MONTE_CARLO_NEUTRON_COLLISION_HANDLER_HPP

// FRENSIE Includes
#include "MonteCarlo_NeutronMaterial.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_StandardParticleCollisionHandler.hpp"

namespace MonteCarlo{

//! The neutron collision handler traits
struct NeutronCollisionHandlerTraits
{
  //! The material used by this collision handler
  typedef NeutronMaterial MaterialType;
  
  //! The particle type used by this collision handler
  typedef NeutronState ParticleType;
};

//! The neutron collision handler class
class NeutronCollisionHandler : public StandardParticleCollisionHandler<NeutronCollisionHandlerTraits>
{

private:

  // Typedef for the base type
  typedef StandardParticleCollisionHandler<NeutronCollisionHandlerTraits> BaseType;

public:

  //! The material used by this collision handler
  typedef NeutronCollisionHandlerTraits::MaterialType MaterialType;
  
  //! The particle type used by this collision handler
  typedef NeutronCollisionHandlerTraits::ParticleType ParticleType;
  
  NeutronCollisionHandler( const bool analogue_collisions = true );

  //! Destructor
  virtual ~NeutronCollisionHandler()
  { /* ... */ }

  //! Get the macroscopic cross section for a specific reaction
  double getMacroscopicReactionCrossSection(
                                    const NeutronState& neutron,
                                    const NuclearReactionType reaction ) const;
}; 
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NEUTRON_COLLISION_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronCollisionHandler.hpp
//---------------------------------------------------------------------------//
