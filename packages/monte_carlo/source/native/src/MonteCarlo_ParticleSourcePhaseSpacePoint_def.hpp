//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSourcePhaseSpacePoint_def.hpp
//! \author Alex Robinson
//! \brief  Particle source phase space point class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SOURCE_PHASE_SPACE_POINT_DEF_HPP
#define MONTE_CARLO_PARTICLE_SOURCE_PHASE_SPACE_POINT_DEF_HPP

// FRENSIE Includes
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Return the dimension value
template<ParticleSourceDimensionType dimension>
double ParticleSourcePhaseSpacePoint::getCoordinate() const
{
  THROW_EXCEPTION( std::logic_error,
                   "Error: The " << dimension << " coordinate does not "
                   "exist!" );
}

// Set the dimension value
template<ParticleSourceDimensionType dimension>
void ParticleSourcePhaseSpacePoint::setCoordinate( const double coord_value )
{
  THROW_EXCEPTION( std::logic_error,
                   "Error: The " << dimension << " coordinate does not "
                   "exist!" );
}

// Get the dimension weight
template<ParticleSourceDimensionType dimension>
double ParticleSourcePhaseSpacePoint::getCoordinateWeight() const
{
  THROW_EXCEPTION( std::logic_error,
                   "Error: The " << dimension << " does not have a weight!" );
}

// Set the dimension weight
template<ParticleSourceDimensionType dimension>
void ParticleSourcePhaseSpacePoint::setCoordinateWeight( const double coord_weight )
{
  THROW_EXCEPTION( std::logic_error,
                   "Error: The " << dimension << " does not have a weight!" );
}

//! Return the x dimension value
template<>
inline double ParticleSourcePhaseSpacePoint::getCoordinate<X_PS_DIMENSION> const
{
  return this->getPrimarySpatialCoordinate();
}

//! Set the x dimension value
template<>
inline void ParticleSourcePhaseSpacePoint::setCoordinate<X_PS_DIMENSION>(
                                                     const double coord_value )
{
  this->setPrimarySpatialCoordinate( coord_value );
}

//! Return the x dimension weight
template<>
inline double ParticleSourcePhaseSpacePoint::getCoordinateWeight<X_PS_DIMENSION> const
{
  return this->getPrimarySpatialCoordinateWeight();
}

//! Set the x dimension weight
template<>
inline void ParticleSourcePhaseSpacePoint::setCoordinateWeight<X_PS_DIMENSION>(
                                                    const double coord_weight )
{
  this->setPrimarySpatialCoordinateWeight( coord_weight );
}

//! Return the y dimension value
template<>
inline double ParticleSourcePhaseSpacePoint::getCoordinate<Y_PS_DIMENSION> const
{
  return this->getSecondarySpatialCoordinate();
}

//! Set the y dimension value
template<>
inline void ParticleSourcePhaseSpacePoint::setCoordinate<Y_PS_DIMENSION>(
                                                     const double coord_value )
{
  this->setSecondarySpatialCoordinate( coord_value );
}

//! Return the y dimension weight
template<>
inline double ParticleSourcePhaseSpacePoint::getCoordinateWeight<Y_PS_DIMENSION> const
{
  return this->getSecondarySpatialCoordinateWeight();
}

//! Set the y dimension weight
template<>
inline void ParticleSourcePhaseSpacePoint::setCoordinateWeight<Y_PS_DIMENSION>(
                                                    const double coord_weight )
{
  this->setSecondarySpatialCoordinateWeight( coord_weight );
}

//! Return the z dimension value
template<>
inline double ParticleSourcePhaseSpacePoint::getCoordinate<Z_PS_DIMENSION> const
{
  return this->getTertiarySpatialCoordinate();
}

//! Set the z dimension value
template<>
inline void ParticleSourcePhaseSpacePoint::setCoordinate<Z_PS_DIMENSION>(
                                                     const double coord_value )
{
  this->setTertiarySpatialCoordinate( coord_value );
}

//! Return the z dimension weight
template<>
inline double ParticleSourcePhaseSpacePoint::getCoordinateWeight<Z_PS_DIMENSION> const
{
  return this->getTertiarySpatialCoordinateWeight();
}

//! Set the z dimension weight
template<>
inline void ParticleSourcePhaseSpacePoint::setCoordinateWeight<Z_PS_DIMENSION>(
                                                    const double coord_weight )
{
  this->setTertiarySpatialCoordinateWeight( coord_weight );
}

//! Return the r dimension value
template<>
inline double ParticleSourcePhaseSpacePoint::getCoordinate<R_PS_DIMENSION> const
{
  return this->getPrimarySpatialCoordinate();
}

//! Set the r dimension value
template<>
inline void ParticleSourcePhaseSpacePoint::setCoordinate<R_PS_DIMENSION>(
                                                     const double coord_value )
{
  this->setPrimarySpatialCoordinate( coord_value );
}

//! Return the r dimension weight
template<>
inline double ParticleSourcePhaseSpacePoint::getCoordinateWeight<R_PS_DIMENSION> const
{
  return this->getPrimarySpatialCoordinateWeight();
}

//! Set the r dimension weight
template<>
inline void ParticleSourcePhaseSpacePoint::setCoordinateWeight<R_PS_DIMENSION>(
                                                    const double coord_weight )
{
  this->setPrimarySpatialCoordinateWeight( coord_weight );
}

//! Return the axis dimension value
template<>
inline double ParticleSourcePhaseSpacePoint::getCoordinate<AXIS_PS_DIMENSION> const
{
  return this->getTertiarySpatialCoordinate();
}

//! Set the axis dimension value
template<>
inline void ParticleSourcePhaseSpacePoint::setCoordinate<AXIS_PS_DIMENSION>(
                                                     const double coord_value )
{
  this->setTertiarySpatialCoordinate( coord_value );
}

//! Return the axis dimension weight
template<>
inline double ParticleSourcePhaseSpacePoint::getCoordinateWeight<AXIS_PS_DIMENSION> const
{
  return this->getTertiarySpatialCoordinateWeight();
}

//! Set the axis dimension weight
template<>
inline void ParticleSourcePhaseSpacePoint::setCoordinateWeight<AXIS_PS_DIMENSION>(
                                                    const double coord_weight )
{
  this->setTertiarySpatialCoordinateWeight( coord_weight );
}

//! Return the spatial polar angle dimension value
template<>
inline double ParticleSourcePhaseSpacePoint::getCoordinate<SPATIAL_POLAR_ANGLE_PS_DIMENSION> const
{
  return this->getTertiarySpatialCoordinate();
}

//! Set the spatial polar angle dimension value
template<>
inline void ParticleSourcePhaseSpacePoint::setCoordinate<SPATIAL_POLAR_ANGLE_PS_DIMENSION>(
                                                     const double coord_value )
{
  this->setTertiarySpatialCoordinate( coord_value );
}

//! Return the spatial polar angle dimension weight
template<>
inline double ParticleSourcePhaseSpacePoint::getCoordinateWeight<SPATIAL_POLAR_ANGLE_PS_DIMENSION> const
{
  return this->getTertiarySpatialCoordinateWeight();
}

//! Set the spatial polar angle dimension weight
template<>
inline void ParticleSourcePhaseSpacePoint::setCoordinateWeight<SPATIAL_POLAR_ANGLE_PS_DIMENSION>(
                                                    const double coord_weight )
{
  this->setTertiarySpatialCoordinateWeight( coord_weight );
}

//! Return the spatial azimuthal angle dimension value
inline double ParticleSourcePhaseSpacePoint::getCoordinate<SPATIAL_AZIMUTHAL_ANGLE_DIMENSION> const
{
  return this->getSecondarySpatialCoordinate();
}

//! Set the spatial azimuthal angle value
template<>
inline void ParticleSourcePhaseSpacePoint::setCoordinate<SPATIAL_AZIMUTHAL_ANGLE_PS_DIMENSION>(
                                                     const double coord_value )
{
  this->setSecondarySpatialCoordinate( coord_value );
}

//! Return the spatial azimuthal angle weight
template<>
inline double ParticleSourcePhaseSpacePoint::getCoordinateWeight<SPATIAL_AZIMUTHAL_ANGLE_PS_DIMENSION> const
{
  return this->getSecondarySpatialCoordinateWeight();
}

//! Set the spatial azimuthal angle weight
template<>
inline void ParticleSourcePhaseSpacePoint::setCoordinateWeight<SPATIAL_AZIMUTHAL_ANGLE_PS_DIMENSION>(
                                                    const double coord_weight )
{
  this->setSecondarySpatialCoordinateWeight( coord_weight );
}

//! Return the directional polar angle dimension value
inline double ParticleSourcePhaseSpacePoint::getCoordinate<DIRECTIONAL_POLAR_ANGLE_PS_DIMENSION> const
{
  return this->getPolarAngleDirectionalCoordinate();
}

//! Set the directional polar angle value
template<>
inline void ParticleSourcePhaseSpacePoint::setCoordinate<DIRECTIONAL_POLAR_ANGLE_PS_DIMENSION>(
                                                     const double coord_value )
{
  this->setPolarAngleDirectionalCoordinate( coord_value );
}

//! Return the directional polar angle weight
template<>
inline double ParticleSourcePhaseSpacePoint::getCoordinateWeight<DIRECTIONAL_POLAR_ANGLE_PS_DIMENSION> const
{
  return this->getPolarAngleDirectionalCoordinateWeight();
}

//! Set the directional polar angle weight
template<>
inline void ParticleSourcePhaseSpacePoint::setCoordinateWeight<DIRECTIONAL_POLAR_ANGLE_PS_DIMENSION>(
                                                    const double coord_weight )
{
  this->setPolarAngleDirectionalCoordinateWeight( coord_weight );
}

//! Return the directional azimuthal angle dimension value
inline double ParticleSourcePhaseSpacePoint::getCoordinate<DIRECTIONAL_AZIMUTHAL_ANGLE_PS_DIMENSION> const
{
  return this->getAzimuthalAngleDirectionalCoordinate();
}

//! Set the directional azimuthal angle value
template<>
inline void ParticleSourcePhaseSpacePoint::setCoordinate<DIRECTIONAL_AZIMUTHAL_ANGLE_PS_DIMENSION>(
                                                     const double coord_value )
{
  this->setAzimuthalAngleDirectionalCoordinate( coord_value );
}

//! Return the directional azimuthal angle weight
template<>
inline double ParticleSourcePhaseSpacePoint::getCoordinateWeight<DIRECTIONAL_AZIMUTHAL_ANGLE_PS_DIMENSION> const
{
  return this->getAzimuthalAngleDirectionalCoordinateWeight();
}

//! Set the directional azimuthal angle weight
template<>
inline void ParticleSourcePhaseSpacePoint::setCoordinateWeight<DIRECTIONAL_AZIMUTHAL_ANGLE_PS_DIMENSION>(
                                                    const double coord_weight )
{
  this->setAzimuthalAngleDirectionalCoordinateWeight( coord_weight );
}

//! Return the energy dimension value
inline double ParticleSourcePhaseSpacePoint::getCoordinate<ENERGY_PS_DIMENSION>
{
  return this->getEnergyCoordinate();
}

//! Set the energy dimension value
template<>
inline void ParticleSourcePhaseSpacePoint::setCoordinate<ENERGY_PS_DIMENSION>(
                                                     const double coord_value )
{
  this->setEnergyCoordinate( coord_value );
}

//! Return the energy dimension weight
template<>
inline double ParticleSourcePhaseSpacePoint::getCoordinateWeight<ENERGY_PS_DIMENSION> const
{
  return this->getEnergyCoordinateWeight();
}

//! Set the energy dimension weight
template<>
inline void ParticleSourcePhaseSpacePoint::setCoordinateWeight<ENERGY_PS_DIMENSION>(
                                                    const double coord_weight )
{
  this->setEnergyCoordinateWeight( coord_weight );
}

//! Return the time dimension value
inline double ParticleSourcePhaseSpacePoint::getCoordinate<TIME_PS_DIMENSION>
{
  return this->getTimeCoordinate();
}

//! Set the time dimension value
template<>
inline void ParticleSourcePhaseSpacePoint::setCoordinate<TIME_PS_DIMENSION>(
                                                     const double coord_value )
{
  this->setTimeCoordinate( coord_value );
}

//! Return the time dimension weight
template<>
inline double ParticleSourcePhaseSpacePoint::getCoordinateWeight<TIME_PS_DIMENSION> const
{
  return this->getTimeCoordinateWeight();
}

//! Set the time dimension weight
template<>
inline void ParticleSourcePhaseSpacePoint::setCoordinateWeight<TIME_PS_DIMENSION>(
                                                    const double coord_weight )
{
  this->setTimeCoordinateWeight( coord_weight );
}

//! Return the weight dimension value
inline double ParticleSourcePhaseSpacePoint::getCoordinate<WEIGHT_PS_DIMENSION>
{
  return this->getWeightCoordinate();
}

// Set the time dimension value
template<>
inline void ParticleSourcePhaseSpacePoint::setCoordinate<WEIGHT_PS_DIMENSION>(
                                                     const double coord_value )
{
  this->setWeightCoordinate( coord_value );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_SOURCE_PHASE_SPACE_POINT_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSourcePhaseSpacePoint_def.hpp
//---------------------------------------------------------------------------//
