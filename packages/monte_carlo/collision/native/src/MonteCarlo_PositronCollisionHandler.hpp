//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronCollisionHandler.hpp
//! \author Luke Kersting
//! \brief  Positron collision handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_POSITRON_COLLISION_HANDLER_HPP
#define MONTE_CARLO_POSITRON_COLLISION_HANDLER_HPP

// FRENSIE Includes
#include "MonteCarlo_PositronMaterial.hpp"
#include "MonteCarlo_PositronState.hpp"
#include "MonteCarlo_StandardParticleCollisionHandler.hpp"

namespace MonteCarlo{

//! The positron collision handler traits
struct PositronCollisionHandlerTraits
{
  //! The material used by this collision handler
  typedef PositronMaterial MaterialType;

  //! The particle type used by this collision handler
  typedef PositronState ParticleType;
};

//! The positron collision handler class
class PositronCollisionHandler : public StandardParticleCollisionHandler<PositronCollisionHandlerTraits>
{

private:

  // Typedef for the base type
  typedef StandardParticleCollisionHandler<PositronCollisionHandlerTraits> BaseType;

public:

  //! The material used by this collision handler
  typedef PositronCollisionHandlerTraits::MaterialType MaterialType;

  //! The particle type used by this collision handler
  typedef PositronCollisionHandlerTraits::ParticleType ParticleType;

  //! Constructor
  PositronCollisionHandler( const bool analogue_collisions = true );

  //! Destructor
  virtual ~PositronCollisionHandler()
  { /* ... */ }

  //! Get the macroscopic cross section for a specific reaction
  double getMacroscopicReactionCrossSection(
                              const PositronState& positron,
                              const PositronatomicReactionType reaction ) const;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_POSITRON_COLLISION_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronCollisionHandler.hpp
//---------------------------------------------------------------------------//
