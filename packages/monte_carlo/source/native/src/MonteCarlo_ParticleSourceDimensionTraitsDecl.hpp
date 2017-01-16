//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSourceDimensionTraits.hpp
//! \author Alex Robinson
//! \brief  Particle source dimension traits class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SOURCE_DIMENSION_TRAITS_DECL_HPP
#define MONTE_CARLO_PARTICLE_SOURCE_DIMENSION_TRAITS_DECL_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleSourcePhaseSpacePoint.hpp"
#include "MonteCarlo_ParticleSourceDimensionType.hpp"

/*! \defgroup particle_source_dimension_traits Particle Source Dimension Traits
 * \ingroup policy
 *
 * This traits class defines basic properties for each dimension of the 
 * particle source phase space. Among the properties are very
 * basic methods for accessing a dimension value (or weight) of 
 * MonteCarlo::ParticleSourcePhaseSpacePoint class objects.
 */

namespace MonteCarlo{

/*! Class that defines the custom compile-time error message
 * \ingroup particle_source_dimension_traits
 */
template<typename T, ParticleSourceDimensionType dimension>
struct UndefinedParticleSourceDimensionTraits
{
  //! This function should not compile if there is any attempt to instantiate
  static inline double notDefined() { return T::desired_dimension_is_missing_specialization(); }
};

/*! This class defines the basic properties of a particle source dimension.
 *
 * The functions in the templated base unspecialized struct are designed not
 * to compile and therefore specializations must be written for each
 * MonteCarlo::ParticleSourceDimensionType enum. When compilation fails
 * due to the attempted use of a dimension without a specialization a
 * custom compile-time error message will be displayed, which will indicate
 * that a specialization is needed.
 * \ingroup particle_source_dimension_traits
 */
template<ParticleSourceDimensionType dimension>
struct ParticleSourceDimensionTraits
{
  //! The type associated with this dimension
  typedef double DimensionType;
  
  //! Get the coordinate value
  static inline double getCoordinate( const ParticleSourcePhaseSpacePoint& point )
  {
    UndefinedParticleSourceDimensionTraits<double,dimension>::notDefined();
    return 0;
  }

  //! Set the coordinate value
  static inline void setCoordinate( ParticleSourcePhaseSpacePoint& point,
                                    const double coord_value )
  {
    UndefinedParticleSourceDimensionTraits<double,dimension>::notDefined();
  }

  //! Get the coordinate weight
  static inline double getCoordinateWeight( const ParticleSourcePhaseSpacePoint& point )
  {
    UndefinedParticleSourceDimensionTraits<double,dimension>::notDefined();
    return 0;
  }

  //! Set the coordinate weight
  static inline void setCoordinateWeight( ParticleSourcePhaseSpacePoint& point,
                                          const double coord_weight )
  {
    UndefinedParticleSourceDimensionTraits<double,dimension>::notDefined();
  }
};

/*! This function gives access to the getCoordinate MonteCarlo::ParticleSourceDimensionTraits method
 * \ingroup particle_source_dimension_traits
 */
template<ParticleSourceDimensionType dimension>
inline double getCoordinate( const ParticleSourcePhaseSpacePoint& point )
{
  return ParticleSourceDimensionTraits<dimension>::getCoordinate( point );
}

/*! This function gives access to the setCoordinate MonteCarlo::ParticleSourceDimensionTraits method
 * \ingroup particle_source_dimension_traits
 */
template<ParticleSourceDimensionType dimension>
inline void setCoordinate( ParticleSourcePhaseSpacePoint& point,
                           const double coord_value )
{
  ParticleSourceDimensionTraits<dimension>::setCoordinate( point, coord_value );
}

/*! This function gives access to the getCoordinateWeight MonteCarlo::ParticleSourceDimensionTraits method
 * \ingroup particle_source_dimension_traits
 */
template<ParticleSourceDimensionType dimension>
inline double getCoordinateWeight( const ParticleSourcePhaseSpacePoint& point )
{
  return ParticleSourceDimensionTraits<dimension>::getCoordinateWeight( point );
}

/*! This function gives access to the setCoordinateWeight MonteCarlo::ParticleSourceDimensionTraits method
 * \ingroup particle_source_dimension_traits
 */
template<ParticleSourceDimensionType dimension>
inline void setCoordinateWeight( ParticleSourcePhaseSpacePoint& point,
                                 const double coord_weight )
{
  ParticleSourceDimensionTraits<dimension>::setCoordinateWeight( point, coord_weight );
}  
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_SOURCE_DIMENSION_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSourceDimensionTraits.hpp
//---------------------------------------------------------------------------//
