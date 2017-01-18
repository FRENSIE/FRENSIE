//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSourceDimensionTraits.hpp
//! \author Alex Robinson
//! \brief  Particle source dimension traits class specializations
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SOURCE_DIMENSION_TRAITS_HPP
#define MONTE_CARLO_PARTICLE_SOURCE_DIMENSION_TRAITS_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleSourceDimensionTraitsDecl.hpp"

namespace MonteCarlo{

/*! Specialization of MonteCarlo::ParticleSourceDimensionTraits for MonteCarlo::PRIMARY_SPATIAL_PS_DIMENSION
 */
template<>
struct ParticleSourceDimensionTraits<PRIMARY_SPATIAL_PS_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionType;

  //! Get the dimension class type
  static inline ParticleSourceDimensionClassType getClass()
  { return SPATIAL_PS_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline double getCoordinate( const ParticleSourcePhaseSpacePoint& point )
  { return point.getPrimarySpatialCoordinate(); }

  //! Set the coordinate value
  static inline double setCoordinate( ParticleSourcePhaseSpacePoint& point,
                                      const double coord_value )
  { point.setPrimarySpatialCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline double getCoordinateWeight( const ParticleSourcePhaseSpacePoint& point )
  { point.getPrimarySpatialCoordinateWeight(); }

  //! Set the coordinate weight
  static inline double setCoordinateWeight( ParticleSourcePhaseSpacePoint& point,
                                            const double coord_weight )
  { point.setPrimarySpatialCoordinateWeight( coord_weight ); }
};

/*! Specialization of MonteCarlo::ParticleSourceDimensionTraits for MonteCarlo::SECONDARY_SPATIAL_PS_DIMENSION
 */
template<>
struct ParticleSourceDimensionTraits<SECONDARY_SPATIAL_PS_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionType;

  //! Get the dimension class type
  static inline ParticleSourceDimensionClassType getClass()
  { return SPATIAL_PS_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline double getCoordinate( const ParticleSourcePhaseSpacePoint& point )
  { return point.getSecondarySpatialCoordinate(); }

  //! Set the coordinate value
  static inline double setCoordinate( ParticleSourcePhaseSpacePoint& point,
                                      const double coord_value )
  { point.setSecondarySpatialCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline double getCoordinateWeight( const ParticleSourcePhaseSpacePoint& point )
  { point.getSecondarySpatialCoordinateWeight(); }

  //! Set the coordinate weight
  static inline double setCoordinateWeight( ParticleSourcePhaseSpacePoint& point,
                                            const double coord_weight )
  { point.setSecondarySpatialCoordinateWeight( coord_weight ); }
};

/*! Specialization of MonteCarlo::ParticleSourceDimensionTraits for MonteCarlo::TERTIARY_SPATIAL_PS_DIMENSION
 */
template<>
struct ParticleSourceDimensionTraits<TERTIARY_SPATIAL_PS_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionType;

  //! Get the dimension class type
  static inline ParticleSourceDimensionClassType getClass()
  { return SPATIAL_PS_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline double getCoordinate( const ParticleSourcePhaseSpacePoint& point )
  { return point.getTertiarySpatialCoordinate(); }

  //! Set the coordinate value
  static inline double setCoordinate( ParticleSourcePhaseSpacePoint& point,
                                      const double coord_value )
  { point.setTertiarySpatialCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline double getCoordinateWeight( const ParticleSourcePhaseSpacePoint& point )
  { point.getTertiarySpatialCoordinateWeight(); }

  //! Set the coordinate weight
  static inline double setCoordinateWeight( ParticleSourcePhaseSpacePoint& point,
                                            const double coord_weight )
  { point.setTertiarySpatialCoordinateWeight( coord_weight ); }
};

/*! Specialization of MonteCarlo::ParticleSourceDimensionTraits for MonteCarlo::PRIMARY_DIRECTIONAL_PS_DIMENSION
 */
template<>
struct ParticleSourceDimensionTraits<PRIMARY_DIRECTIONAL_PS_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionType;

  //! Get the dimension class type
  static inline ParticleSourceDimensionClassType getClass()
  { return DIRECTIONAL_PS_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline double getCoordinate( const ParticleSourcePhaseSpacePoint& point )
  { return point.getPrimaryDirectionalCoordinate(); }

  //! Set the coordinate value
  static inline double setCoordinate( ParticleSourcePhaseSpacePoint& point,
                                      const double coord_value )
  { point.setPrimaryDirectionalCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline double getCoordinateWeight( const ParticleSourcePhaseSpacePoint& point )
  { point.getPrimaryDirectionalCoordinateWeight(); }

  //! Set the coordinate weight
  static inline double setCoordinateWeight( ParticleSourcePhaseSpacePoint& point,
                                            const double coord_weight )
  { point.setPrimaryDirectionalCoordinateWeight( coord_weight ); }
};

/*! Specialization of MonteCarlo::ParticleSourceDimensionTraits for MonteCarlo::SECONDARY_DIRECTIONAL_PS_DIMENSION
 */
template<>
struct ParticleSourceDimensionTraits<SECONDARY_DIRECTIONAL_PS_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionType;

  //! Get the dimension class type
  static inline ParticleSourceDimensionClassType getClass()
  { return DIRECTIONAL_PS_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline double getCoordinate( const ParticleSourcePhaseSpacePoint& point )
  { return point.getSecondaryDirectionalCoordinate(); }

  //! Set the coordinate value
  static inline double setCoordinate( ParticleSourcePhaseSpacePoint& point,
                                      const double coord_value )
  { point.setSecondaryDirectionalCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline double getCoordinateWeight( const ParticleSourcePhaseSpacePoint& point )
  { point.getSecondaryDirectionalCoordinateWeight(); }

  //! Set the coordinate weight
  static inline double setCoordinateWeight( ParticleSourcePhaseSpacePoint& point,
                                            const double coord_weight )
  { point.setSecondaryDirectionalCoordinateWeight( coord_weight ); }
};

/*! Specialization of MonteCarlo::ParticleSourceDimensionTraits for MonteCarlo::TERTIARY_DIRECTIONAL_PS_DIMENSION
 */
template<>
struct ParticleSourceDimensionTraits<TERTIARY_DIRECTIONAL_PS_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionType;

  //! Get the dimension class type
  static inline ParticleSourceDimensionClassType getClass()
  { return DIRECTIONAL_PS_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline double getCoordinate( const ParticleSourcePhaseSpacePoint& point )
  { return point.getTertiaryDirectionalCoordinate(); }

  //! Set the coordinate value
  static inline double setCoordinate( ParticleSourcePhaseSpacePoint& point,
                                      const double coord_value )
  { point.setTertiaryDirectionalCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline double getCoordinateWeight( const ParticleSourcePhaseSpacePoint& point )
  { point.getTertiaryDirectionalCoordinateWeight(); }

  //! Set the coordinate weight
  static inline double setCoordinateWeight( ParticleSourcePhaseSpacePoint& point,
                                            const double coord_weight )
  { point.setTertiaryDirectionalCoordinateWeight( coord_weight ); }
};

/*! Specialization of MonteCarlo::ParticleSourceDimensionTraits for MonteCarlo::ENERGY_PS_DIMENSION
 */
template<>
struct ParticleSourceDimensionTraits<ENERGY_PS_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionType;

  //! Get the dimension class type
  static inline ParticleSourceDimensionClassType getClass()
  { return ENERGY_PS_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline double getCoordinate( const ParticleSourcePhaseSpacePoint& point )
  { return point.getEnergyCoordinate(); }

  //! Set the coordinate value
  static inline double setCoordinate( ParticleSourcePhaseSpacePoint& point,
                                      const double coord_value )
  { point.setEnergyCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline double getCoordinateWeight( const ParticleSourcePhaseSpacePoint& point )
  { point.getEnergyCoordinateWeight(); }

  //! Set the coordinate weight
  static inline double setCoordinateWeight( ParticleSourcePhaseSpacePoint& point,
                                            const double coord_weight )
  { point.setEnergyCoordinateWeight( coord_weight ); }
};

/*! Specialization of MonteCarlo::ParticleSourceDimensionTraits for MonteCarlo::TIME_PS_DIMENSION
 */
template<>
struct ParticleSourceDimensionTraits<TIME_PS_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionType;

  //! Get the dimension class type
  static inline ParticleSourceDimensionClassType getClass()
  { return TIME_PS_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline double getCoordinate( const ParticleSourcePhaseSpacePoint& point )
  { return point.getTimeCoordinate(); }

  //! Set the coordinate value
  static inline double setCoordinate( ParticleSourcePhaseSpacePoint& point,
                                      const double coord_value )
  { point.setTimeCoordinate( coord_value ); }

  //! Get the coordinate weight
  static inline double getCoordinateWeight( const ParticleSourcePhaseSpacePoint& point )
  { point.getTimeCoordinateWeight(); }

  //! Set the coordinate weight
  static inline double setCoordinateWeight( ParticleSourcePhaseSpacePoint& point,
                                            const double coord_weight )
  { point.setTimeCoordinateWeight( coord_weight ); }
};

/*! Specialization of MonteCarlo::ParticleSourceDimensionTraits for MonteCarlo::WEIGHT_PS_DIMENSION
 *
 * Note that the weight dimension does not have an additional weight associated
 * with it.
 */
template<>
struct ParticleSourceDimensionTraits<WEIGHT_PS_DIMENSION>
{
  //! The type associated with this dimension
  typedef double DimensionType;

  //! Get the dimension class type
  static inline ParticleSourceDimensionClassType getClass()
  { return WEIGHT_PS_DIMENSION_CLASS; }

  //! Get the coordinate value
  static inline double getCoordinate( const ParticleSourcePhaseSpacePoint& point )
  { return point.getWeightCoordinate(); }

  //! Set the coordinate value
  static inline double setCoordinate( ParticleSourcePhaseSpacePoint& point,
                                      const double coord_value )
  { point.setWeightCoordinate( coord_value ); }
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_SOURCE_PHASE_SPACE_POINT_ACCESS_POLICY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSourcePhaseSpacePointAccessPolicy.hpp
//---------------------------------------------------------------------------//
