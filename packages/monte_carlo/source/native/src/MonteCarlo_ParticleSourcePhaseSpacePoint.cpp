//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSourcePhaseSpacePoint.cpp
//! \author Alex Robinson
//! \brief  Particle source phase space point class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleSourcePhaseSpacePoint.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
ParticleSourcePhaseSpacePoint::ParticleSourcePhaseSpacePoint()
  : d_primary_spatial_coord( 0.0 ),
    d_primary_spatial_coord_weight( 1.0 ),
    d_secondary_spatial_coord( 0.0 ),
    d_secondary_spatial_coord_weight( 1.0 ),
    d_tertiary_spatial_coord( 0.0 ),
    d_tertiary_spatial_coord_weight( 1.0 ),
    d_polar_angle_directional_coord( 1.0 ),
    d_polar_angle_directional_coord_weight( 1.0 ),
    d_azimuthal_angle_directional_coord( 0.0 ),
    d_azimuthal_angle_directional_coord_weight( 1.0 ),
    d_energy_coord( 1.0 ),
    d_energy_coord_weight( 1.0 ),
    d_time_coord( 0.0 ),
    d_time_coord_weight( 1.0 ),
    d_weight_coord( 1.0 )
{ /* ... */ }

// Return the primary spatial coordinate of the phase space point
double ParticleSourcePhaseSpacePoint::getPrimarySpatialCoordinate() const
{
  return d_primary_spatial_coord;
}

// Set the primary spatial coordinate of the phase space point
void ParticleSourcePhaseSpacePoint::setPrimarySpatialCoordinate(
                                           const double primary_spatial_coord )
{
  d_primary_spatial_coord = primary_spatial_coord;
}

// Return the primary spatial coordinate weight
double ParticleSourcePhaseSpacePoint::getPrimarySpatialCoordinateWeight() const
{
  return d_primary_spatial_coord_weight;
}

// Set the primary spatial coordinate weight
void ParticleSourcePhaseSpacePoint::setPrimarySpatialCoordinateWeight(
                                                          const double weight )
{
  // Make sure that the weight is valid
  testPrecondition( weight > 0.0 );
  
  d_primary_spatial_coord_weight = weight;
}

// Return the secondary spatial coordinate of the phase space point
double ParticleSourcePhaseSpacePoint::getSecondarySpatialCoordinate() const
{
  return d_secondary_spatial_coord;
}

// Set the secondary spatial coordinate of the phase space point
void ParticleSourcePhaseSpacePoint::setSecondarySpatialCoordinate(
                                         const double secondary_spatial_coord )
{
  d_secondary_spatial_coord = secondary_spatial_coord;
}

// Return the secondary spatial coordinate weight
double ParticleSourcePhaseSpacePoint::getSecondarySpatialCoordinateWeight() const
{
  return d_secondary_spatial_coord_weight;
}

// Set the secondary spatial coordinate weight
void ParticleSourcePhaseSpacePoint::setSecondarySpatialCoordinateWeight(
                                                          const double weight )
{
  // Make sure that the weight is valid
  testPrecondition( weight > 0.0 );
  
  d_secondary_spatial_coord_weight = weight;
}

// Return the tertiary spatial coordinate of the phase space point
double ParticleSourcePhaseSpacePoint::getTertiarySpatialCoordinate() const
{
  return d_tertiary_spatial_coord;
}

// Set the tertiary spatial coordinate of the phase space point
void ParticleSourcePhaseSpacePoint::setTertiarySpatialCoordinate(
                                          const double tertiary_spatial_coord )
{
  d_tertiary_spatial_coord = tertiary_spatial_coord;
}

// Return the tertiary spatial coordinate weight
double ParticleSourcePhaseSpacePoint::getTertiarySpatialCoordinateWeight() const
{
  return d_tertiary_spatial_coord_weight;
}

// Set the tertiary spatial coordinate weight
void ParticleSourcePhaseSpacePoint::setTertiarySpatialCoordinateWeight( const double weight )
{
  // Make sure that the weight is valid
  testPrecondition( weight > 0.0 );
  
  d_tertiary_spatial_coord_weight = weight;
}

// Convert spatial coordinates to cartesian coordinates
void ParticleSourcePhaseSpacePoint::convertSpatialCoordinatesToCartesianCoordinates(
                                       const SpatialCoordinateConversionPolicy&
                                       spatial_coord_conversion_policy,
                                       double& x_spatial_coord,
                                       double& y_spatial_coord,
                                       double& z_spatial_coord ) const
{
  spatial_coord_conversion_policy.convert( d_primary_spatial_coord,
                                           d_secondary_spatial_coord,
                                           d_tertiary_spatial_coord,
                                           x_spatial_coord,
                                           y_spatial_coord,
                                           z_spatial_coord );
}

// Return the weight of all spatial coordinates
double ParticleSourcePhaseSpacePoint::getWeightOfSpatialCoordinates() const
{
  return d_primary_spatial_coord_weight*
    d_secondary_spatial_coord_weight*
    d_tertiary_spatial_coord_weight;
}

// Return the polar angle directional coordinate of the phase space point
/*! \details This will return the cosine of the polar angle.
 */
double ParticleSourcePhaseSpacePoint::getPolarAngleDirectionalCoordinate() const
{
  return d_polar_angle_directional_coord;
}

// Set the polar angle directional coordinate of the phase space point
/*! \details the input coordinate value must be the cosine of the polar angle.
 */
void ParticleSourcePhaseSpacePoint::setPolarAngleDirectionalCoordinate(
                                   const double polar_angle_directional_coord )
{
  // Make sure the polar angle cosine is valid
  testPrecondition( polar_angle_directional_coord >= -1.0 );
  testPrecondition( polar_angle_directional_coord <= 1.0 );
  
  d_polar_angle_directional_coord = polar_angle_directional_coord;
}

// Return the polar angle directional coordinate weight
double ParticleSourcePhaseSpacePoint::getPolarAngleDirectionalCoordinateWeight() const
{
  return d_polar_angle_directional_coord_weight;
}

// Set the polar angle directional coordinate weight
void ParticleSourcePhaseSpacePoint::setPolarAngleDirectionalCoordinateWeight( const double weight )
{
  // Make sure that the weight is valid
  testPrecondition( weight > 0.0 );

  d_polar_angle_directional_coord_weight = weight;
}

// Return the azimuthal angle directional coord. of the phase space point
double ParticleSourcePhaseSpacePoint::getAzimuthalAngleDirectionalCoordinate() const
{
  return d_azimuthal_angle_directional_coord;
}

// Set the the azimuthal angle directional coord. of the phase space point
void ParticleSourcePhaseSpacePoint::setAzimuthalAngleDirectionalCoordinate(
                               const double azimuthal_angle_directional_coord )
{
  d_azimuthal_angle_directional_coord = azimuthal_angle_directional_coord;
}

// Return the azimuthal angle directional coordinate weight
double ParticleSourcePhaseSpacePoint::getAzimuthalAngleDirectionalCoordinateWeight() const
{
  return d_azimuthal_angle_directional_coord_weight;
}

// Set the azimuthal angle directional coordinate weight
void ParticleSourcePhaseSpacePoint::setAzimuthalAngleDirectionalCoordinateWeight( const double weight )
{
  // Make sure that the weight is valid
  testPrecondition( weight > 0.0 );

  d_azimuthal_angle_directional_coord_weight = weight;
}

// Convert directional coordinates to cartesian coordinates
void ParticleSourcePhaseSpacePoint::convertDirectionalCoordinatesToCartesianCoordinates(
                                   const DirectionalCoordinateConversionPolicy&
                                   directional_coord_conversion_policy,
                                   double& x_directional_coord,
                                   double& y_directional_coord,
                                   double& z_directional_coord ) const
{
  directional_coord_conversion_policy.convert(
                                          d_polar_angle_directional_coord,
                                          d_azimtuthal_angle_directional_coord,
                                          x_directional_coord,
                                          y_directional_coord,
                                          z_directional_coord );
}

// Return the weight of all directional coordinates
double ParticleSourcePhaseSpacePoint::getWeightOfDirectionalCoordinates() const
{
  return d_polar_angle_directional_coord_weight*
    d_azimuthal_angle_directional_coord_weight;
}

// Return the energy coordinate of the phase space point
double ParticleSourcePhaseSpacePoint::getEnergyCoordinate() const
{
  return d_energy_coord;
}

// Set the energy coordinate of the phase space point
void ParticleSourcePhaseSpacePoint::setEnergyCoordinate( const double energy_coord )
{
  // Make sure the energy coordinate value is valid
  testPrecondition( energy_coord > 0.0 );

  d_energy_coord = energy_coord;
}

// Return the energy coordinate weight
double ParticleSourcePhaseSpacePoint::getEnergyCoordinateWeight() const
{
  return d_energy_coord_weight;
}

// Set the energy coordinate weight
void ParticleSourcePhaseSpacePoint::setEnergyCoordinateWeight( const double weight )
{
  // Make sure that the weight is valid
  testPrecondition( weight > 0.0 );

  d_energy_coord_weight = weight;
}

// Return the time coordinate of the phase space point
double ParticleSourcePhaseSpacePoint::getTimeCoordinate() const
{
  return d_time_coord;
}

// Set the time coordinate of the phase space point
void ParticleSourcePhaseSpacePoint::setTimeCoordinate( const double time_coord )
{
  // Make sure that the time coordinate value is valid
  testPrecondition( time_coord >= 0.0 );
  
  d_time_coord = time_coord;
}

// Return the time coordinate weight
double ParticleSourcePhaseSpacePoint::getTimeCoordinateWeight() const
{
  return d_time_coord_weight;
}

// Set the time coordinate weight
void ParticleSourcePhaseSpacePoint::setTimeCoordinateWeight( const double weight )
{
  // Make sure that the weight is valid
  testPrecondition( weight > 0.0 );
  
  d_time_coord_weight = weight;
}

// Return the weight coordinate of the phase space point
void ParticleSourcePhaseSpacePoint::getWeightCoordinate() const
{
  return d_weight_coord;
}

// Set the weight coordinate of the phase space point
void ParticleSourcePhaseSpacePoint::setWeightCoordinate( const double weight_coord )
{
  // Make sure that the weight coordinate value is valid
  testPrecondition( weight_coord > 0.0 );

  d_weight_coord = weight_coord;
}

// Return the weight of all coordinates
void ParticleSourcePhaseSpacePoint::getWeightOfCoordinates() const
{
  return this->getWeightOfSpatialCoordinates()*
    this->getWeightOfDirectionalCoordinates()*
    this->getEnergyCoordinateWeight()*
    this->getTimeCoordinateWeight()*
    this->getWeightCoordinate();
}

// Set a particle state
void ParticleSourcePhaseSpacePoint::setParticleState(
                          const Utility::SpatialCoordinateConversionPolicy&
                          spatial_coord_conversion_policy,
                          const Utility::DirectionalCoordinateConversionPolicy&
                          directional_coord_conversion_policy,
                          ParticleState& particle ) const
{
  double cartesian_spatial_coords[3];

  this->convertSpatialCoordinatesToCartesianCoordinates(
                                               spatial_coord_conversion_policy,
                                               cartesian_spatial_coords[0],
                                               cartesian_spatial_coords[1],
                                               cartesian_spatial_coords[2] );

  double cartesian_directional_coords[3];
  
  this->convertDireectionalCoordinatesToCartesianCoordinates(
                                           directional_coord_conversion_policy,
                                           cartesian_directional_coords[0],
                                           cartesian_directional_coords[1],
                                           cartesian_directional_coords[2] );

  particle.setPosition( cartesian_spatial_coords );
  particle.setDirection( cartesian_directional_coords );
  particle.setSourceEnergy( d_energy_coord );
  particle.setEnergy( d_energy_coord );
  particle.setSourceTime( d_time_coord );
  particle.setTime( d_time_coord );
  particle.setSourceWeight( this->getWeightOfCoordinates() );
  particle.setWeight( particle.getSourceWeight() );
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSourcePhaseSpacePoint.cpp
//---------------------------------------------------------------------------//
