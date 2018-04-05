//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CollisionHandler_def.hpp
//! \author Alex Robinson
//! \brief  Collision handler template function definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COLLISION_HANDLER_DEF_HPP
#define MONTE_CARLO_COLLISION_HANDLER_DEF_HPP

namespace MonteCarlo{

namespace Details{

//! The collision handler upcast helper
template<typename ParticleStateType>
struct CollisionHandlerUpcastHelper;

//! Specialization of the collision handler upcast helper for neutrons
template<>
struct CollisionHandlerUpcastHelper<NeutronState>
{
  //! The desired base type for the upcast
  typedef NeutronCollisionHandler UpcastType;
  
  //! Upcast the collision handler to a NeutronCollisionHandler
  static inline UpcastType* upcast( CollisionHandler* handler )
  { return dynamic_cast<UpcastType*>( handler ); }

  //! Upcast the collision handler to a NeutronCollisionHandler
  static inline const UpcastType* upcast( const CollisionHandler* handler )
  { return dynamic_cast<const UpcastType*>( handler ); }
};

//! Specialization of the collision handler upcast helper for photons
template<>
struct CollisionHandlerUpcastHelper<PhotonState>
{
  //! The desired base type for the upcast
  typedef PhotonCollisionHandler UpcastType;
  
  //! Upcast the collision handler to a PhotonCollisionHandler
  static inline UpcastType* upcast( CollisionHandler* handler )
  { return dynamic_cast<UpcastType*>( handler ); }

  //! Upcast the collision handler to a PhotonCollisionHandler
  static inline const UpcastType* upcast( const CollisionHandler* handler )
  { return dynamic_cast<const UpcastType*>( handler ); }
};

//! Specialization of the collision handler upcast helper for adjoint photons
template<>
struct CollisionHandlerUpcastHelper<AdjointPhotonState>
{
  //! The desired base type for the upcast
  typedef AdjointPhotonCollisionHandler UpcastType;
  
  //! Upcast the collision handler to a AdjointPhotonCollisionHandler
  static inline UpcastType* upcast( CollisionHandler* handler )
  { return dynamic_cast<UpcastType*>( handler ); }

  //! Upcast the collision handler to a AdjointPhotonCollisionHandler
  static inline const UpcastType* upcast( const CollisionHandler* handler )
  { return dynamic_cast<const UpcastType*>( handler ); }
};

//! Specialization of the collision handler upcast helper for electrons
template<>
struct CollisionHandlerUpcastHelper<ElectronState>
{
  //! The desired base type for the upcast
  typedef ElectronCollisionHandler UpcastType;
  
  //! Upcast the collision handler to a ElectronCollisionHandler
  static inline UpcastType* upcast( CollisionHandler* handler )
  { return dynamic_cast<UpcastType*>( handler ); }

  //! Upcast the collision handler to a ElectronCollisionHandler
  static inline const UpcastType* upcast( const CollisionHandler* handler )
  { return dynamic_cast<const UpcastType*>( handler ); }
};

//! Specialization of the collision handler upcast helper for adjoint electrons
template<>
struct CollisionHandlerUpcastHelper<AdjointElectronState>
{
  //! The desired base type for the upcast
  typedef AdjointElectronCollisionHandler UpcastType;
  
  //! Upcast the collision handler to a AdjointElectronCollisionHandler
  static inline UpcastType* upcast( CollisionHandler* handler )
  { return dynamic_cast<UpcastType*>( handler ); }

  //! Upcast the collision handler to a AdjointElectronCollisionHandler
  static inline const UpcastType* upcast( const CollisionHandler* handler )
  { return dynamic_cast<const UpcastType*>( handler ); }
};

//! Specialization of the collision handler upcast helper for positrons
template<>
struct CollisionHandlerUpcastHelper<PositronState>
{
  //! The desired base type for the upcast
  typedef PositronCollisionHandler UpcastType;
  
  //! Upcast the collision handler to a PositronCollisionHandler
  static inline UpcastType* upcast( CollisionHandler* handler )
  { return dynamic_cast<UpcastType*>( handler ); }

  //! Upcast the collision handler to a PositronCollisionHandler
  static inline const UpcastType* upcast( const CollisionHandler* handler )
  { return dynamic_cast<const UpcastType*>( handler ); }
};
  
} // end Details namespace

// Check if a cell is void (as experienced by the given particle type)
/*! \details This method overload can be used to avoid the extra switch 
 * statement overhead.
 */
template<typename ParticleStateType>
inline bool CollisionHandler::isCellVoid(
                  const Geometry::ModuleTraits::InternalCellHandle cell ) const
{
  Details::CollisionHandlerUpcastHelper<ParticleStateType>::UpcastType::isCellVoid( cell );
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COLLISION_HANDLER_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CollisionHandler_def.hpp
//---------------------------------------------------------------------------//
