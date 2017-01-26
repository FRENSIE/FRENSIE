//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhaseSpaceDimensionTraitsDecl.hpp
//! \author Alex Robinson
//! \brief  Particle source dimension traits class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHASE_SPACE_DIMENSION_TRAITS_DECL_HPP
#define MONTE_CARLO_PHASE_SPACE_DIMENSION_TRAITS_DECL_HPP

// FRENSIE Includes
#include "MonteCarlo_PhaseSpacePoint.hpp"
#include "MonteCarlo_PhaseSpaceDimensionClass.hpp"
#include "MonteCarlo_PhaseSpaceDimension.hpp"

/*! \defgroup phase_space_dimension_traits Phase Space Dimension Traits
 * \ingroup policy
 *
 * This traits class defines basic properties for each dimension of the 
 * particle phase space. Among the properties are very basic methods for 
 * accessing a dimension value (or weight) of MonteCarlo::PhaseSpacePoint 
 * class objects.
 */

namespace MonteCarlo{

/*! Class that defines the custom compile-time error message
 * \ingroup phase_space_dimension_traits
 */
template<typename T, PhaseSpaceDimension dimension>
struct UndefinedPhaseSpaceDimensionTraits
{
  //! This function should not compile if there is any attempt to instantiate
  static inline double notDefined() { return T::desired_dimension_is_missing_specialization(); }
};

/*! This class defines the basic properties of a phase space dimension.
 *
 * The functions in the templated base unspecialized struct are designed not
 * to compile and therefore specializations must be written for each
 * MonteCarlo::PhaseSpaceDimension enum. When compilation fails
 * due to the attempted use of a dimension without a specialization a
 * custom compile-time error message will be displayed, which will indicate
 * that a specialization is needed.
 * \ingroup phase_space_dimension_traits
 */
template<PhaseSpaceDimension dimension>
struct PhaseSpaceDimensionTraits
{
  //! The type associated with this dimension
  typedef double DimensionType;

  //! Get the dimension class type
  static inline ParticleSourceDimensionClassType getClass()
  {
    UndefinedPhaseSpaceDimensionTraits<double,dimension>::notDefined();
  }
  
  //! Get the coordinate value
  static inline double getCoordinate( const PhaseSpacePoint& point )
  {
    UndefinedPhaseSpaceDimensionTraits<double,dimension>::notDefined();
    return 0;
  }

  //! Set the coordinate value
  static inline void setCoordinate( PhaseSpacePoint& point,
                                    const double coord_value )
  {
    UndefinedPhaseSpaceDimensionTraits<double,dimension>::notDefined();
  }

  //! Get the coordinate weight
  static inline double getCoordinateWeight( const PhaseSpacePoint& point )
  {
    UndefinedPhaseSpaceDimensionTraits<double,dimension>::notDefined();
    return 0;
  }

  //! Set the coordinate weight
  static inline void setCoordinateWeight( PhaseSpacePoint& point,
                                          const double coord_weight )
  {
    UndefinedPhaseSpaceDimensionTraits<double,dimension>::notDefined();
  }
};

/*! This function gives access to the getCoordinate MonteCarlo::PhaseSpaceDimensionTraits method
 * \ingroup phase_space_dimension_traits
 */
template<PhaseSpaceDimension dimension>
inline double getCoordinate( const PhaseSpacePoint& point )
{
  return PhaseSpaceDimensionTraits<dimension>::getCoordinate( point );
}

/*! This function gives access to the setCoordinate MonteCarlo::PhaseSpaceDimensionTraits method
 * \ingroup phase_space_dimension_traits
 */
template<PhaseSpaceDimension dimension>
inline void setCoordinate( PhaseSpacePoint& point,
                           const double coord_value )
{
  PhaseSpaceDimensionTraits<dimension>::setCoordinate( point, coord_value );
}

/*! This function gives access to the getCoordinateWeight MonteCarlo::PhaseSpaceDimensionTraits method
 * \ingroup phase_space_dimension_traits
 */
template<PhaseSpaceDimension dimension>
inline double getCoordinateWeight( const PhaseSpacePoint& point )
{
  return PhaseSpaceDimensionTraits<dimension>::getCoordinateWeight( point );
}

/*! This function gives access to the setCoordinateWeight MonteCarlo::PhaseSpaceDimensionTraits method
 * \ingroup phase_space_dimension_traits
 */
template<PhaseSpaceDimension dimension>
inline void setCoordinateWeight( PhaseSpacePoint& point,
                                 const double coord_weight )
{
  PhaseSpaceDimensionTraits<dimension>::setCoordinateWeight( point, coord_weight );
}  
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHASE_SPACE_DIMENSION_TRAITS_DECL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceDimensionTraitsDecl.hpp
//---------------------------------------------------------------------------//
