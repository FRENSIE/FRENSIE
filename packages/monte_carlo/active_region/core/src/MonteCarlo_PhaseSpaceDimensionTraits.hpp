//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhaseSpaceDimensionTraits.hpp
//! \author Alex Robinson
//! \brief  Particle source dimension traits class specializations
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHASE_SPACE_DIMENSION_TRAITS_HPP
#define MONTE_CARLO_PHASE_SPACE_DIMENSION_TRAITS_HPP

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimensionTraitsDecl.hpp"
#include "Utility_LoggingMacros.hpp"

namespace MonteCarlo{

/*! Specialization of MonteCarlo::PhaseSpaceDimensionTraits for MonteCarlo::PRIMARY_SPATIAL_PS_DIMENSION
 * \ingroup phase_space_dimension_traits
 */
template<>
struct PhaseSpaceDimensionTraits<PRIMARY_SPATIAL_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionValueType;

  //! The type associated with this dimension weight
  typedef double DimensionWeightType;

  //! Get the dimension class type
  static inline PhaseSpaceDimensionClass getClass()
  { return SPATIAL_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline DimensionValueType getCoordinate( const ParticleState& point )
  { return point.getXPosition(); }

  //! Get the coordinate value
  static inline DimensionValueType getCoordinate( const PhaseSpacePoint& point )
  { return point.getPrimarySpatialCoordinate(); }

  //! Set the coordinate value
  static inline void setCoordinate( PhaseSpacePoint& point,
                                    const DimensionValueType coord_value )
  { point.setPrimarySpatialCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline DimensionWeightType getCoordinateWeight( const PhaseSpacePoint& point )
  { return point.getPrimarySpatialCoordinateWeight(); }

  //! Set the coordinate weight
  static inline void setCoordinateWeight( PhaseSpacePoint& point,
                                          const DimensionWeightType coord_weight )
  { point.setPrimarySpatialCoordinateWeight( coord_weight ); }
};

/*! Specialization of MonteCarlo::PhaseSpaceDimensionTraits for MonteCarlo::SECONDARY_SPATIAL_DIMENSION
 * \ingroup phase_space_dimension_traits
 */
template<>
struct PhaseSpaceDimensionTraits<SECONDARY_SPATIAL_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionValueType;

  //! The type associated with this dimension weight
  typedef double DimensionWeightType;

  //! Get the dimension class type
  static inline PhaseSpaceDimensionClass getClass()
  { return SPATIAL_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline DimensionValueType getCoordinate( const ParticleState& point )
  { return point.getYPosition(); }

  //! Get the coordinate value
  static inline DimensionValueType getCoordinate( const PhaseSpacePoint& point )
  { return point.getSecondarySpatialCoordinate(); }

  //! Set the coordinate value
  static inline void setCoordinate( PhaseSpacePoint& point,
                                    const DimensionValueType coord_value )
  { point.setSecondarySpatialCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline DimensionWeightType getCoordinateWeight( const PhaseSpacePoint& point )
  { return point.getSecondarySpatialCoordinateWeight(); }

  //! Set the coordinate weight
  static inline void setCoordinateWeight( PhaseSpacePoint& point,
                                          const DimensionWeightType coord_weight )
  { point.setSecondarySpatialCoordinateWeight( coord_weight ); }
};

/*! Specialization of MonteCarlo::PhaseSpaceDimensionTraits for MonteCarlo::TERTIARY_SPATIAL_DIMENSION
 * \ingroup phase_space_dimension_traits
 */
template<>
struct PhaseSpaceDimensionTraits<TERTIARY_SPATIAL_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionValueType;

  //! The type associated with this dimension weight
  typedef double DimensionWeightType;

  //! Get the dimension class type
  static inline PhaseSpaceDimensionClass getClass()
  { return SPATIAL_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline DimensionValueType getCoordinate( const ParticleState& point )
  { return point.getZPosition(); }

  //! Get the coordinate value
  static inline DimensionValueType getCoordinate( const PhaseSpacePoint& point )
  { return point.getTertiarySpatialCoordinate(); }

  //! Set the coordinate value
  static inline void setCoordinate( PhaseSpacePoint& point,
                                    const DimensionValueType coord_value )
  { point.setTertiarySpatialCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline DimensionWeightType getCoordinateWeight( const PhaseSpacePoint& point )
  { return point.getTertiarySpatialCoordinateWeight(); }

  //! Set the coordinate weight
  static inline void setCoordinateWeight( PhaseSpacePoint& point,
                                          const DimensionWeightType coord_weight )
  { point.setTertiarySpatialCoordinateWeight( coord_weight ); }
};

/*! Specialization of MonteCarlo::PhaseSpaceDimensionTraits for MonteCarlo::PRIMARY_DIRECTIONAL_DIMENSION
 * \ingroup phase_space_dimension_traits
 */
template<>
struct PhaseSpaceDimensionTraits<PRIMARY_DIRECTIONAL_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionValueType;

  //! The type associated with this dimension weight
  typedef double DimensionWeightType;

  //! Get the dimension class type
  static inline PhaseSpaceDimensionClass getClass()
  { return DIRECTIONAL_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline DimensionValueType getCoordinate( const ParticleState& point )
  { return point.getXDirection(); }

  //! Get the coordinate value
  static inline DimensionValueType getCoordinate( const PhaseSpacePoint& point )
  { return point.getPrimaryDirectionalCoordinate(); }

  //! Set the coordinate value
  static inline void setCoordinate( PhaseSpacePoint& point,
                                    const DimensionValueType coord_value )
  { point.setPrimaryDirectionalCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline DimensionWeightType getCoordinateWeight( const PhaseSpacePoint& point )
  { return point.getPrimaryDirectionalCoordinateWeight(); }

  //! Set the coordinate weight
  static inline void setCoordinateWeight( PhaseSpacePoint& point,
                                          const DimensionWeightType coord_weight )
  { point.setPrimaryDirectionalCoordinateWeight( coord_weight ); }
};

/*! Specialization of MonteCarlo::PhaseSpaceDimensionTraits for MonteCarlo::SECONDARY_DIRECTIONAL_DIMENSION
 * \ingroup phase_space_dimension_traits
 */
template<>
struct PhaseSpaceDimensionTraits<SECONDARY_DIRECTIONAL_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionValueType;

  //! The type associated with this dimension weight
  typedef double DimensionWeightType;

  //! Get the dimension class type
  static inline PhaseSpaceDimensionClass getClass()
  { return DIRECTIONAL_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline DimensionValueType getCoordinate( const ParticleState& point )
  { return point.getYDirection(); }

  //! Get the coordinate value
  static inline DimensionValueType getCoordinate( const PhaseSpacePoint& point )
  { return point.getSecondaryDirectionalCoordinate(); }

  //! Set the coordinate value
  static inline void setCoordinate( PhaseSpacePoint& point,
                                    const DimensionValueType coord_value )
  { point.setSecondaryDirectionalCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline DimensionWeightType getCoordinateWeight( const PhaseSpacePoint& point )
  { return point.getSecondaryDirectionalCoordinateWeight(); }

  //! Set the coordinate weight
  static inline void setCoordinateWeight( PhaseSpacePoint& point,
                                          const DimensionWeightType coord_weight )
  { point.setSecondaryDirectionalCoordinateWeight( coord_weight ); }
};

/*! Specialization of MonteCarlo::PhaseSpaceDimensionTraits for MonteCarlo::TERTIARY_DIRECTIONAL_DIMENSION
 * \ingroup phase_space_dimension_traits
 */
template<>
struct PhaseSpaceDimensionTraits<TERTIARY_DIRECTIONAL_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionValueType;

  //! The type associated with this dimension weight
  typedef double DimensionWeightType;

  //! Get the dimension class type
  static inline PhaseSpaceDimensionClass getClass()
  { return DIRECTIONAL_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline DimensionValueType getCoordinate( const ParticleState& point )
  { return point.getZDirection(); }

  //! Get the coordinate value
  static inline DimensionValueType getCoordinate( const PhaseSpacePoint& point )
  { return point.getTertiaryDirectionalCoordinate(); }

  //! Set the coordinate value
  static inline void setCoordinate( PhaseSpacePoint& point,
                                    const DimensionValueType coord_value )
  { point.setTertiaryDirectionalCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline DimensionWeightType getCoordinateWeight( const PhaseSpacePoint& point )
  { return point.getTertiaryDirectionalCoordinateWeight(); }

  //! Set the coordinate weight
  static inline void setCoordinateWeight( PhaseSpacePoint& point,
                                          const DimensionWeightType coord_weight )
  { point.setTertiaryDirectionalCoordinateWeight( coord_weight ); }
};

/*! Specialization of MonteCarlo::PhaseSpaceDimensionTraits for MonteCarlo::ENERGY_DIMENSION
 * \ingroup phase_space_dimension_traits
 */
template<>
struct PhaseSpaceDimensionTraits<ENERGY_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionValueType;

  //! The type associated with this dimension weight
  typedef double DimensionWeightType;

  //! Get the dimension class type
  static inline PhaseSpaceDimensionClass getClass()
  { return ENERGY_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline DimensionValueType getCoordinate( const ParticleState& point )
  { return point.getEnergy(); }

  //! Get the coordinate value
  static inline DimensionValueType getCoordinate( const PhaseSpacePoint& point )
  { return point.getEnergyCoordinate(); }

  //! Set the coordinate value
  static inline void setCoordinate( PhaseSpacePoint& point,
                                    const DimensionValueType coord_value )
  { point.setEnergyCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline DimensionWeightType getCoordinateWeight( const PhaseSpacePoint& point )
  { return point.getEnergyCoordinateWeight(); }

  //! Set the coordinate weight
  static inline void setCoordinateWeight( PhaseSpacePoint& point,
                                          const DimensionWeightType coord_weight )
  { point.setEnergyCoordinateWeight( coord_weight ); }
};

/*! Specialization of MonteCarlo::PhaseSpaceDimensionTraits for MonteCarlo::ENERGY_DIMENSION
 * \ingroup phase_space_dimension_traits
 */
template<>
struct PhaseSpaceDimensionTraits<SOURCE_ENERGY_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionValueType;

  //! The type associated with this dimension weight
  typedef double DimensionWeightType;

  //! Get the dimension class type
  static inline PhaseSpaceDimensionClass getClass()
  { return ENERGY_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline DimensionValueType getCoordinate( const ParticleState& point )
  { return point.getSourceEnergy(); }

  //! Get the coordinate value
  static inline DimensionValueType getCoordinate( const PhaseSpacePoint& point )
  { return point.getEnergyCoordinate(); }

  //! Set the coordinate value
  static inline void setCoordinate( PhaseSpacePoint& point,
                                    const DimensionValueType coord_value )
  { point.setEnergyCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline DimensionWeightType getCoordinateWeight( const PhaseSpacePoint& point )
  { return point.getEnergyCoordinateWeight(); }

  //! Set the coordinate weight
  static inline void setCoordinateWeight( PhaseSpacePoint& point,
                                          const DimensionWeightType coord_weight )
  { point.setEnergyCoordinateWeight( coord_weight ); }
};

/*! Specialization of MonteCarlo::PhaseSpaceDimensionTraits for MonteCarlo::TIME_DIMENSION
 * \ingroup phase_space_dimension_traits
 */
template<>
struct PhaseSpaceDimensionTraits<TIME_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionValueType;

  //! The type associated with this dimension weight
  typedef double DimensionWeightType;

  //! Get the dimension class type
  static inline PhaseSpaceDimensionClass getClass()
  { return TIME_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline DimensionValueType getCoordinate( const ParticleState& point )
  { return point.getTime(); }

  //! Get the coordinate value
  static inline DimensionValueType getCoordinate( const PhaseSpacePoint& point )
  { return point.getTimeCoordinate(); }

  //! Set the coordinate value
  static inline void setCoordinate( PhaseSpacePoint& point,
                                    const DimensionValueType coord_value )
  { point.setTimeCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline DimensionWeightType getCoordinateWeight( const PhaseSpacePoint& point )
  { return point.getTimeCoordinateWeight(); }

  //! Set the coordinate weight
  static inline void setCoordinateWeight( PhaseSpacePoint& point,
                                          const DimensionWeightType coord_weight )
  { point.setTimeCoordinateWeight( coord_weight ); }
};

/*! Specialization of MonteCarlo::PhaseSpaceDimensionTraits for MonteCarlo::TIME_DIMENSION
 * \ingroup phase_space_dimension_traits
 */
template<>
struct PhaseSpaceDimensionTraits<SOURCE_TIME_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionValueType;

  //! The type associated with this dimension weight
  typedef double DimensionWeightType;

  //! Get the dimension class type
  static inline PhaseSpaceDimensionClass getClass()
  { return TIME_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline DimensionValueType getCoordinate( const ParticleState& point )
  { return point.getSourceTime(); }

  //! Get the coordinate value
  static inline DimensionValueType getCoordinate( const PhaseSpacePoint& point )
  { return point.getTimeCoordinate(); }

  //! Set the coordinate value
  static inline void setCoordinate( PhaseSpacePoint& point,
                                    const DimensionValueType coord_value )
  { point.setTimeCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline DimensionWeightType getCoordinateWeight( const PhaseSpacePoint& point )
  { return point.getTimeCoordinateWeight(); }

  //! Set the coordinate weight
  static inline void setCoordinateWeight( PhaseSpacePoint& point,
                                          const DimensionWeightType coord_weight )
  { point.setTimeCoordinateWeight( coord_weight ); }
};

/*! Specialization of MonteCarlo::PhaseSpaceDimensionTraits for MonteCarlo::WEIGHT_DIMENSION
 *
 * Note that the weight dimension does not have an additional weight associated
 * with it (the set/get coordinate weight methods call the same 
 * MonteCarlo::PhaseSpacePoint method as the set/get coordinate
 * methods).
 * \ingroup phase_space_dimension_traits
 */
template<>
struct PhaseSpaceDimensionTraits<WEIGHT_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionValueType;

  //! The type associated with this dimension weight
  typedef double DimensionWeightType;

  //! Get the dimension class type
  static inline PhaseSpaceDimensionClass getClass()
  { return WEIGHT_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline DimensionValueType getCoordinate( const ParticleState& point )
  { return point.getWeight(); }

  //! Get the coordinate value
  static inline DimensionValueType getCoordinate( const PhaseSpacePoint& point )
  { return point.getWeightCoordinate(); }

  //! Set the coordinate value
  static inline void setCoordinate( PhaseSpacePoint& point,
                                    const DimensionValueType coord_value )
  { point.setWeightCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline DimensionWeightType getCoordinateWeight( const PhaseSpacePoint& point )
  { return point.getWeightCoordinate(); }

  //! Set the coordinate weight
  static inline void setCoordinateWeight( PhaseSpacePoint&,
                                          const DimensionWeightType coord_weight )
  {
    if( coord_weight != 1.0 )
    {
      FRENSIE_LOG_WARNING( "The weight coordinate cannot have a weight "
                           "applied!" );
    }
  }
};

/*! Specialization of MonteCarlo::PhaseSpaceDimensionTraits for MonteCarlo::WEIGHT_DIMENSION
 *
 * Note that the weight dimension does not have an additional weight associated
 * with it (the set/get coordinate weight methods call the same 
 * MonteCarlo::PhaseSpacePoint method as the set/get coordinate
 * methods).
 * \ingroup phase_space_dimension_traits
 */
template<>
struct PhaseSpaceDimensionTraits<SOURCE_WEIGHT_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionValueType;

  //! The type associated with this dimension weight
  typedef double DimensionWeightType;

  //! Get the dimension class type
  static inline PhaseSpaceDimensionClass getClass()
  { return WEIGHT_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline DimensionValueType getCoordinate( const ParticleState& point )
  { return point.getSourceWeight(); }

  //! Get the coordinate value
  static inline DimensionValueType getCoordinate( const PhaseSpacePoint& point )
  { return point.getWeightCoordinate(); }

  //! Set the coordinate value
  static inline void setCoordinate( PhaseSpacePoint& point,
                                    const DimensionValueType coord_value )
  { point.setWeightCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline DimensionWeightType getCoordinateWeight( const PhaseSpacePoint& point )
  { return point.getWeightCoordinate(); }

  //! Set the coordinate weight
  static inline void setCoordinateWeight( PhaseSpacePoint&,
                                          const DimensionWeightType coord_weight )
  {
    if( coord_weight != 1.0 )
    {
      FRENSIE_LOG_WARNING( "The weight coordinate cannot have a weight "
                           "applied!" );
    }
  }
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHASE_SPACE_DIMENSION_TRAITS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceDimensionTraits.hpp
//---------------------------------------------------------------------------//
