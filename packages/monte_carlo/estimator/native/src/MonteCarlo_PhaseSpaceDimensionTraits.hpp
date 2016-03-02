//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhaseSpaceDimensionTraits.hpp
//! \author Alex Robinson
//! \brief  Phase space dimension traits class specializations
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHASE_SPACE_DIMENSION_TRAITS_HPP
#define MONTE_CARLO_PHASE_SPACE_DIMENSION_TRAITS_HPP

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimensionTraitsDecl.hpp"
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "MonteCarlo_ParticleState.hpp"

namespace MonteCarlo{

/*! The specialization of the PhaseSpaceDimensionTraits for ENERGY_DIMENSION
 * \ingroup phase_space_dim_traits
 */
template<>
struct PhaseSpaceDimensionTraits<ENERGY_DIMENSION>
{
  typedef ParticleState::energyType dimensionType;
  
  static inline std::string name()
  { return "Energy"; }

  static inline dimensionType lowerBound()
  { return 0.0; }

  static inline dimensionType upperBound()
  { return std::numeric_limits<dimensionType>::infinity(); }

  static inline dimensionType getDimensionValue( const EstimatorParticleStateWrapper& particle_wrapper )
  { return particle_wrapper.getParticleState().getEnergy(); }

  static inline dimensionType getDimensionValue( const Teuchos::any& any_value )
  { return Teuchos::any_cast<dimensionType>( any_value ); }
};

/*! The specialization of the PhaseSpaceDimensionTraits for COSINE_DIMENSION
 * \ingroup phase_space_dim_traits
 */
template<>
struct PhaseSpaceDimensionTraits<COSINE_DIMENSION>
{
  typedef double dimensionType;
    
  static inline std::string name()
  { return "Cosine"; }

  static inline dimensionType lowerBound()
  { return -1.0; }

  static inline dimensionType upperBound()
  { return 1.0; }

  static inline dimensionType getDimensionValue( const EstimatorParticleStateWrapper& particle_wrapper )
  { return particle_wrapper.getAngleCosine(); }

  static inline dimensionType getDimensionValue( const Teuchos::any& any_value )
  { return Teuchos::any_cast<dimensionType>( any_value ); }
};

/*! The specialization of the PhaseSpaceDimensionTraits for TIME_DIMENSION
 * \ingroup phase_space_dim_traits
 */
template<>
struct PhaseSpaceDimensionTraits<TIME_DIMENSION>
{
  typedef ParticleState::timeType dimensionType;
    
  static inline std::string name()
  { return "Time"; }

  static inline dimensionType lowerBound()
  { return 0.0; }

  static inline dimensionType upperBound()
  { return std::numeric_limits<dimensionType>::infinity(); }

  static inline dimensionType getDimensionValue( const EstimatorParticleStateWrapper& particle_wrapper )
  { return particle_wrapper.getParticleState().getTime(); }

  static inline dimensionType getDimensionValue( const Teuchos::any& any_value )
  { return Teuchos::any_cast<dimensionType>( any_value ); }
};

/*! The specialization of the PhaseSpaceDimensionTraits for
 * COLLISION_NUMBER_DIMENSION
 * \ingroup phase_space_dim_traits
 */
template<>
struct PhaseSpaceDimensionTraits<COLLISION_NUMBER_DIMENSION>
{
  typedef ParticleState::collisionNumberType dimensionType;
    
  static inline std::string name()
  { return "Collision Number"; }

  static inline dimensionType lowerBound()
  { return 0u; }

  static inline dimensionType upperBound()
  { return std::numeric_limits<dimensionType>::max(); }

  static inline dimensionType getDimensionValue( const EstimatorParticleStateWrapper& particle_wrapper )
  { return particle_wrapper.getParticleState().getCollisionNumber(); }

  static inline dimensionType getDimensionValue( const Teuchos::any& any_value )
  { return Teuchos::any_cast<dimensionType>( any_value ); }
};

} // end MonteCarlo namespace

#endif // end PHASE_SPACE_DIMENSION_TRAITS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceDimensionTraits.hpp
//---------------------------------------------------------------------------//
