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

namespace MonteCarlo{

/*! Specialization of MonteCarlo::PhaseSpaceDimensionTraits for MonteCarlo::PRIMARY_SPATIAL_PS_DIMENSION
 * \ingroup phase_space_dimension_traits
 */
template<>
struct PhaseSpaceDimensionTraits<PRIMARY_SPATIAL_PS_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionType;

  //! Get the dimension class type
  static inline PhaseSpaceDimensionClass getClass()
  { return SPATIAL_PS_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline double getCoordinate( const PhaseSpacePoint& point )
  { return point.getPrimarySpatialCoordinate(); }

  //! Set the coordinate value
  static inline double setCoordinate( PhaseSpacePoint& point,
                                      const double coord_value )
  { point.setPrimarySpatialCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline double getCoordinateWeight( const PhaseSpacePoint& point )
  { point.getPrimarySpatialCoordinateWeight(); }

  //! Set the coordinate weight
  static inline double setCoordinateWeight( PhaseSpacePoint& point,
                                            const double coord_weight )
  { point.setPrimarySpatialCoordinateWeight( coord_weight ); }
};

/*! Specialization of MonteCarlo::PhaseSpaceDimensionTraits for MonteCarlo::SECONDARY_SPATIAL_PS_DIMENSION
 * \ingroup phase_space_dimension_traits
 */
template<>
struct PhaseSpaceDimensionTraits<SECONDARY_SPATIAL_PS_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionType;

  //! Get the dimension class type
  static inline PhaseSpaceDimensionClass getClass()
  { return SPATIAL_PS_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline double getCoordinate( const PhaseSpacePoint& point )
  { return point.getSecondarySpatialCoordinate(); }

  //! Set the coordinate value
  static inline double setCoordinate( PhaseSpacePoint& point,
                                      const double coord_value )
  { point.setSecondarySpatialCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline double getCoordinateWeight( const PhaseSpacePoint& point )
  { point.getSecondarySpatialCoordinateWeight(); }

  //! Set the coordinate weight
  static inline double setCoordinateWeight( PhaseSpacePoint& point,
                                            const double coord_weight )
  { point.setSecondarySpatialCoordinateWeight( coord_weight ); }
};

/*! Specialization of MonteCarlo::PhaseSpaceDimensionTraits for MonteCarlo::TERTIARY_SPATIAL_PS_DIMENSION
 * \ingroup phase_space_dimension_traits
 */
template<>
struct PhaseSpaceDimensionTraits<TERTIARY_SPATIAL_PS_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionType;

  //! Get the dimension class type
  static inline PhaseSpaceDimensionClass getClass()
  { return SPATIAL_PS_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline double getCoordinate( const PhaseSpacePoint& point )
  { return point.getTertiarySpatialCoordinate(); }

  //! Set the coordinate value
  static inline double setCoordinate( PhaseSpacePoint& point,
                                      const double coord_value )
  { point.setTertiarySpatialCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline double getCoordinateWeight( const PhaseSpacePoint& point )
  { point.getTertiarySpatialCoordinateWeight(); }

  //! Set the coordinate weight
  static inline double setCoordinateWeight( PhaseSpacePoint& point,
                                            const double coord_weight )
  { point.setTertiarySpatialCoordinateWeight( coord_weight ); }
};

/*! Specialization of MonteCarlo::PhaseSpaceDimensionTraits for MonteCarlo::PRIMARY_DIRECTIONAL_PS_DIMENSION
 * \ingroup phase_space_dimension_traits
 */
template<>
struct PhaseSpaceDimensionTraits<PRIMARY_DIRECTIONAL_PS_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionType;

  //! Get the dimension class type
  static inline PhaseSpaceDimensionClass getClass()
  { return DIRECTIONAL_PS_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline double getCoordinate( const PhaseSpacePoint& point )
  { return point.getPrimaryDirectionalCoordinate(); }

  //! Set the coordinate value
  static inline double setCoordinate( PhaseSpacePoint& point,
                                      const double coord_value )
  { point.setPrimaryDirectionalCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline double getCoordinateWeight( const PhaseSpacePoint& point )
  { point.getPrimaryDirectionalCoordinateWeight(); }

  //! Set the coordinate weight
  static inline double setCoordinateWeight( PhaseSpacePoint& point,
                                            const double coord_weight )
  { point.setPrimaryDirectionalCoordinateWeight( coord_weight ); }
};

/*! Specialization of MonteCarlo::PhaseSpaceDimensionTraits for MonteCarlo::SECONDARY_DIRECTIONAL_PS_DIMENSION
 * \ingroup phase_space_dimension_traits
 */
template<>
struct PhaseSpaceDimensionTraits<SECONDARY_DIRECTIONAL_PS_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionType;

  //! Get the dimension class type
  static inline PhaseSpaceDimensionClass getClass()
  { return DIRECTIONAL_PS_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline double getCoordinate( const PhaseSpacePoint& point )
  { return point.getSecondaryDirectionalCoordinate(); }

  //! Set the coordinate value
  static inline double setCoordinate( PhaseSpacePoint& point,
                                      const double coord_value )
  { point.setSecondaryDirectionalCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline double getCoordinateWeight( const PhaseSpacePoint& point )
  { point.getSecondaryDirectionalCoordinateWeight(); }

  //! Set the coordinate weight
  static inline double setCoordinateWeight( PhaseSpacePoint& point,
                                            const double coord_weight )
  { point.setSecondaryDirectionalCoordinateWeight( coord_weight ); }
};

/*! Specialization of MonteCarlo::PhaseSpaceDimensionTraits for MonteCarlo::TERTIARY_DIRECTIONAL_PS_DIMENSION
 * \ingroup phase_space_dimension_traits
 */
template<>
struct PhaseSpaceDimensionTraits<TERTIARY_DIRECTIONAL_PS_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionType;

  //! Get the dimension class type
  static inline PhaseSpaceDimensionClass getClass()
  { return DIRECTIONAL_PS_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline double getCoordinate( const PhaseSpacePoint& point )
  { return point.getTertiaryDirectionalCoordinate(); }

  //! Set the coordinate value
  static inline double setCoordinate( PhaseSpacePoint& point,
                                      const double coord_value )
  { point.setTertiaryDirectionalCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline double getCoordinateWeight( const PhaseSpacePoint& point )
  { point.getTertiaryDirectionalCoordinateWeight(); }

  //! Set the coordinate weight
  static inline double setCoordinateWeight( PhaseSpacePoint& point,
                                            const double coord_weight )
  { point.setTertiaryDirectionalCoordinateWeight( coord_weight ); }
};

/*! Specialization of MonteCarlo::PhaseSpaceDimensionTraits for MonteCarlo::ENERGY_PS_DIMENSION
 * \ingroup phase_space_dimension_traits
 */
template<>
struct PhaseSpaceDimensionTraits<ENERGY_PS_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionType;

  //! Get the dimension class type
  static inline PhaseSpaceDimensionClass getClass()
  { return ENERGY_PS_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline double getCoordinate( const PhaseSpacePoint& point )
  { return point.getEnergyCoordinate(); }

  //! Set the coordinate value
  static inline double setCoordinate( PhaseSpacePoint& point,
                                      const double coord_value )
  { point.setEnergyCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline double getCoordinateWeight( const PhaseSpacePoint& point )
  { point.getEnergyCoordinateWeight(); }

  //! Set the coordinate weight
  static inline double setCoordinateWeight( PhaseSpacePoint& point,
                                            const double coord_weight )
  { point.setEnergyCoordinateWeight( coord_weight ); }
};

/*! Specialization of MonteCarlo::PhaseSpaceDimensionTraits for MonteCarlo::TIME_PS_DIMENSION
 * \ingroup phase_space_dimension_traits
 */
template<>
struct PhaseSpaceDimensionTraits<TIME_PS_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionType;

  //! Get the dimension class type
  static inline PhaseSpaceDimensionClass getClass()
  { return TIME_PS_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline double getCoordinate( const PhaseSpacePoint& point )
  { return point.getTimeCoordinate(); }

  //! Set the coordinate value
  static inline double setCoordinate( PhaseSpacePoint& point,
                                      const double coord_value )
  { point.setTimeCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline double getCoordinateWeight( const PhaseSpacePoint& point )
  { point.getTimeCoordinateWeight(); }

  //! Set the coordinate weight
  static inline double setCoordinateWeight( PhaseSpacePoint& point,
                                            const double coord_weight )
  { point.setTimeCoordinateWeight( coord_weight ); }
};

/*! Specialization of MonteCarlo::PhaseSpaceDimensionTraits for MonteCarlo::WEIGHT_PS_DIMENSION
 *
 * Note that the weight dimension does not have an additional weight associated
 * with it (the set/get coordinate weight methods call the same 
 * MonteCarlo::PhaseSpacePoint method as the set/get coordinate
 * methods).
 * \ingroup phase_space_dimension_traits
 */
template<>
struct PhaseSpaceDimensionTraits<WEIGHT_PS_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionType;

  //! Get the dimension class type
  static inline PhaseSpaceDimensionClass getClass()
  { return WEIGHT_PS_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline double getCoordinate( const PhaseSpacePoint& point )
  { return point.getWeightCoordinate(); }

  //! Set the coordinate value
  static inline double setCoordinate( PhaseSpacePoint& point,
                                      const double coord_value )
  { point.setWeightCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline double getCoordinateWeight( const PhaseSpacePoint& point )
  { point.getWeightCoordinate(); }

  //! Set the coordinate weight
  static inline double setCoordinateWeight( PhaseSpacePoint& point,
                                            const double coord_weight )
  { point.setWeightCoordinate( coord_weight ); }
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHASE_SPACE_DIMENSION_TRAITS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpaceDimensionTraits.hpp
//---------------------------------------------------------------------------//
