//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ObserverPhaseSpaceDimensionTraits.hpp
//! \author Alex Robinson
//! \brief  Observer phase space dimension traits class specializations
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_OBSERVER_PHASE_SPACE_DIMENSION_TRAITS_HPP
#define MONTE_CARLO_OBSERVER_PHASE_SPACE_DIMENSION_TRAITS_HPP

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_ObserverPhaseSpaceDimensionTraitsDecl.hpp"
#include "MonteCarlo_ObserverPhaseSpaceDimension.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

/*! \brief The specialization of the ObserverPhaseSpaceDimensionTraits for 
 * OBSERVER_COSINE_DIMENSION
 * \ingroup observer_phase_space_dim_traits
 */
template<>
struct ObserverPhaseSpaceDimensionTraits<OBSERVER_COSINE_DIMENSION>
{
  typedef double dimensionType;

  typedef dimensionType dimensionBinType;

  typedef std::true_type isOrdered;

  typedef std::true_type isContinuous;

  static inline std::string name()
  { return "Cosine"; }

  static inline std::string basicName()
  { return "Cosine"; }

  static inline dimensionType lowerBound()
  { return -1.0; }

  static inline dimensionType upperBound()
  { return 1.0; }

  static inline dimensionType getDimensionValue( const ObserverParticleStateWrapper& particle_wrapper )
  { return particle_wrapper.getAngleCosine(); }

  static inline dimensionType getDimensionValue( const boost::any& any_value )
  { return boost::any_cast<dimensionType>( any_value ); }

  static inline void getDimensionRange( const ObserverParticleStateWrapper& particle_wrapper,
                                        dimensionType& range_start,
                                        dimensionType& range_end )
  {
    range_start = particle_wrapper.getAngleCosine();
    range_end = range_start;
  }
};

/*! \brief The specialization of the ObserverPhaseSpaceDimensionTraits for OBSERVER_SOURCE_ENERGY_DIMENSION
 * \ingroup observer_phase_space_dim_traits
 */
template<>
struct ObserverPhaseSpaceDimensionTraits<OBSERVER_SOURCE_ENERGY_DIMENSION>
{
  typedef ParticleState::energyType dimensionType;

  typedef dimensionType dimensionBinType;

  typedef std::true_type isOrdered;

  typedef std::true_type isContinuous;

  static inline std::string name()
  { return "Source Energy"; }

  static inline std::string basicName()
  { return "Source_Energy"; }

  static inline dimensionType lowerBound()
  { return 0.0; }

  static inline dimensionType upperBound()
  { return std::numeric_limits<dimensionType>::infinity(); }

  static inline dimensionType getDimensionValue( const ObserverParticleStateWrapper& particle_wrapper )
  { return particle_wrapper.getParticleState().getSourceEnergy(); }

  static inline dimensionType getDimensionValue( const boost::any& any_value )
  { return boost::any_cast<dimensionType>( any_value ); }

  static inline void getDimensionRange( const ObserverParticleStateWrapper& particle_wrapper,
                                        dimensionType& range_start,
                                        dimensionType& range_end )
  {
    range_start = particle_wrapper.getParticleState().getSourceEnergy();
    range_end = range_start;
  }
};

/*! \brief The specialization of the ObserverPhaseSpaceDimensionTraits for 
 * OBSERVER_ENERGY_DIMENSION
 * \ingroup observer_phase_space_dim_traits
 */
template<>
struct ObserverPhaseSpaceDimensionTraits<OBSERVER_ENERGY_DIMENSION>
{
  typedef ParticleState::energyType dimensionType;

  typedef dimensionType dimensionBinType;

  typedef std::true_type isOrdered;

  typedef std::true_type isContinuous;

  static inline std::string name()
  { return "Energy"; }

  static inline std::string basicName()
  { return "Energy"; }

  static inline dimensionType lowerBound()
  { return 0.0; }

  static inline dimensionType upperBound()
  { return std::numeric_limits<dimensionType>::infinity(); }

  static inline dimensionType getDimensionValue( const ObserverParticleStateWrapper& particle_wrapper )
  { return particle_wrapper.getParticleState().getEnergy(); }

  static inline dimensionType getDimensionValue( const boost::any& any_value )
  { return boost::any_cast<dimensionType>( any_value ); }

  static inline void getDimensionRange( const ObserverParticleStateWrapper& particle_wrapper,
                                        dimensionType& range_start,
                                        dimensionType& range_end )
  {
    range_start = particle_wrapper.getParticleState().getEnergy();
    range_end = range_start;
  }
};

/*! The specialization of the PhaseSpaceDimensionTraits for SOURCE_TIME_DIMENSION
 * \ingroup observer_phase_space_dim_traits
 */
template<>
struct ObserverPhaseSpaceDimensionTraits<OBSERVER_SOURCE_TIME_DIMENSION>
{
  typedef ParticleState::timeType dimensionType;

  typedef dimensionType dimensionBinType;

  typedef std::true_type isOrdered;

  typedef std::true_type isContinuous;

  static inline std::string name()
  { return "Source Time"; }

  static inline std::string basicName()
  { return "Source_Time"; }

  static inline dimensionType lowerBound()
  { return 0.0; }

  static inline dimensionType upperBound()
  { return std::numeric_limits<dimensionType>::infinity(); }

  static inline dimensionType getDimensionValue( const ObserverParticleStateWrapper& particle_wrapper )
  { return particle_wrapper.getParticleState().getSourceTime(); }

  static inline dimensionType getDimensionValue( const boost::any& any_value )
  { return boost::any_cast<dimensionType>( any_value ); }

  static inline void getDimensionRange( const ObserverParticleStateWrapper& particle_wrapper,
                                        dimensionType& range_start,
                                        dimensionType& range_end )
  {
    range_start = particle_wrapper.getParticleState().getSourceTime();
    range_end = range_start;
  }
};

/*! \brief The specialization of the ObserverPhaseSpaceDimensionTraits for 
 * OBSERVER_TIME_DIMENSION
 * \ingroup observer_phase_space_dim_traits
 */
template<>
struct ObserverPhaseSpaceDimensionTraits<OBSERVER_TIME_DIMENSION>
{
  typedef ParticleState::timeType dimensionType;

  typedef dimensionType dimensionBinType;

  typedef std::true_type isOrdered;

  typedef std::true_type isContinuous;

  static inline std::string name()
  { return "Time"; }

  static inline std::string basicName()
  { return "Time"; }

  static inline dimensionType lowerBound()
  { return 0.0; }

  static inline dimensionType upperBound()
  { return std::numeric_limits<dimensionType>::infinity(); }

  static inline dimensionType getDimensionValue( const ObserverParticleStateWrapper& particle_wrapper )
  { return particle_wrapper.getParticleState().getTime(); }

  static inline dimensionType getDimensionValue( const boost::any& any_value )
  { return boost::any_cast<dimensionType>( any_value ); }

  static inline void getDimensionRange( const ObserverParticleStateWrapper& particle_wrapper,
                                        dimensionType& range_start,
                                        dimensionType& range_end )
  {
    range_start = particle_wrapper.getStartTime();
    range_end = particle_wrapper.getEndTime();
  }
};

/*! \brief The specialization of the ObserverPhaseSpaceDimensionTraits for
 * OBSERVER_COLLISION_NUMBER_DIMENSION
 * \ingroup observer_phase_space_dim_traits
 */
template<>
struct ObserverPhaseSpaceDimensionTraits<OBSERVER_COLLISION_NUMBER_DIMENSION>
{
  typedef ParticleState::collisionNumberType dimensionType;

  typedef dimensionType dimensionBinType;

  typedef std::true_type isOrdered;

  typedef std::false_type isContinuous;

  static inline std::string name()
  { return "Collision Number"; }

  static inline std::string basicName()
  { return "Collision_Number"; }

  static inline dimensionType lowerBound()
  { return 0u; }

  static inline dimensionType upperBound()
  { return std::numeric_limits<dimensionType>::max(); }

  static inline dimensionType getDimensionValue( const ObserverParticleStateWrapper& particle_wrapper )
  { return particle_wrapper.getParticleState().getCollisionNumber(); }

  static inline dimensionType getDimensionValue( const boost::any& any_value )
  { return boost::any_cast<dimensionType>( any_value ); }

  static inline void getDimensionRange( const ObserverParticleStateWrapper& particle_wrapper,
                                        dimensionType& range_start,
                                        dimensionType& range_end )
  {
    range_start = particle_wrapper.getParticleState().getCollisionNumber();
    range_end = range_start;
  }
};

/*! \brief The specialization of the ObserverPhaseSpaceDimensionTraits for
 * OBSERVER_SOURCE_ID_DIMENSION
 * \ingroup observer_phase_space_dim_traits
 */
template<>
struct ObserverPhaseSpaceDimensionTraits<OBSERVER_SOURCE_ID_DIMENSION>
{
  typedef ParticleState::sourceIdType dimensionType;

  typedef std::vector<dimensionType> dimensionBinType;

  typedef std::false_type isOrdered;

  typedef std::false_type isContinuous;

  static inline std::string name()
  { return "Source Id"; }

  static inline std::string basicName()
  { return "Source_Id"; }

  static inline dimensionType lowerBound()
  { return 0; }

  static inline dimensionType upperBound()
  { return std::numeric_limits<dimensionType>::max(); }

  static inline dimensionType getDimensionValue( const ObserverParticleStateWrapper& particle_wrapper )
  { return particle_wrapper.getParticleState().getSourceId(); }

  static inline dimensionType getDimensionValue( const boost::any& any_value )
  { return boost::any_cast<dimensionType>( any_value ); }

  static inline void getDimensionRange( const ObserverParticleStateWrapper& particle_wrapper,
                                        dimensionType& range_start,
                                        dimensionType& range_end )
  {
    range_start = particle_wrapper.getParticleState().getSourceId();
    range_end = range_start;
  }
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_OBSERVER_PHASE_SPACE_DIMENSION_TRAITS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ObserverPhaseSpaceDimensionTraits.hpp
//---------------------------------------------------------------------------//
