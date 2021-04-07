//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhaseSpacePoint.cpp
//! \author Alex Robinson
//! \brief  Particle source phase space point class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PhaseSpacePoint.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
PhaseSpacePoint::PhaseSpacePoint(
   const std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>&
   spatial_coord_conversion_policy,
   const std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>&
   directional_coord_conversion_policy )
  : d_spatial_coord_conversion_policy( spatial_coord_conversion_policy ),
    d_directional_coord_conversion_policy( directional_coord_conversion_policy ),
    d_primary_spatial_coord( 0.0 ),
    d_primary_spatial_coord_weight( 1.0 ),
    d_secondary_spatial_coord( 0.0 ),
    d_secondary_spatial_coord_weight( 1.0 ),
    d_tertiary_spatial_coord( 0.0 ),
    d_tertiary_spatial_coord_weight( 1.0 ),
    d_primary_directional_coord( 1.0 ),
    d_primary_directional_coord_weight( 1.0 ),
    d_secondary_directional_coord( 0.0 ),
    d_secondary_directional_coord_weight( 1.0 ),
    d_tertiary_directional_coord( 0.0 ),
    d_tertiary_directional_coord_weight( 1.0 ),
    d_energy_coord( 1.0 ),
    d_energy_coord_weight( 1.0 ),
    d_time_coord( 0.0 ),
    d_time_coord_weight( 1.0 ),
    d_weight_coord( 1.0 )
{ /* ... */ }

// Constructor (particle state initialization)
PhaseSpacePoint::PhaseSpacePoint(
   const ParticleState& particle,
   const std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>&
   spatial_coord_conversion_policy,
   const std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>&
   directional_coord_conversion_policy )
  : d_spatial_coord_conversion_policy( spatial_coord_conversion_policy ),
    d_directional_coord_conversion_policy( directional_coord_conversion_policy ),
    d_primary_spatial_coord( 0.0 ),
    d_primary_spatial_coord_weight( 1.0 ),
    d_secondary_spatial_coord( 0.0 ),
    d_secondary_spatial_coord_weight( 1.0 ),
    d_tertiary_spatial_coord( 0.0 ),
    d_tertiary_spatial_coord_weight( 1.0 ),
    d_primary_directional_coord( 1.0 ),
    d_primary_directional_coord_weight( 1.0 ),
    d_secondary_directional_coord( 0.0 ),
    d_secondary_directional_coord_weight( 1.0 ),
    d_tertiary_directional_coord( 0.0 ),
    d_tertiary_directional_coord_weight( 1.0 ),
    d_energy_coord( particle.getEnergy() ),
    d_energy_coord_weight( 1.0 ),
    d_time_coord( particle.getTime() ),
    d_time_coord_weight( 1.0 ),
    d_weight_coord( particle.getWeight() )
{
  // Convert the particle's Cartesian spatial coordinates to the spatial
  // coordinates of the phase space
  d_spatial_coord_conversion_policy->convertFromCartesianSpatialCoordinates(
                                                    particle.getXPosition(),
                                                    particle.getYPosition(),
                                                    particle.getZPosition(),
                                                    d_primary_spatial_coord,
                                                    d_secondary_spatial_coord,
                                                    d_tertiary_spatial_coord );

  // Convert the particle's Cartesian directional coordinates to the
  // directional coordinates of the phase space
  d_directional_coord_conversion_policy->convertFromCartesianDirectionalCoordinates(
                                                particle.getXDirection(),
                                                particle.getYDirection(),
                                                particle.getZDirection(),
                                                d_primary_directional_coord,
                                                d_secondary_directional_coord,
                                                d_tertiary_directional_coord );
}

// Return the primary spatial coordinate of the phase space point
double PhaseSpacePoint::getPrimarySpatialCoordinate() const
{
  return d_primary_spatial_coord;
}

// Set the primary spatial coordinate of the phase space point
void PhaseSpacePoint::setPrimarySpatialCoordinate(
                                           const double primary_spatial_coord )
{
  // Make sure that the coordinate is valid
  testPrecondition( d_spatial_coord_conversion_policy->isPrimarySpatialCoordinateValid( primary_spatial_coord ) );
  
  d_primary_spatial_coord = primary_spatial_coord;
}

// Return the primary spatial coordinate weight
double PhaseSpacePoint::getPrimarySpatialCoordinateWeight() const
{
  return d_primary_spatial_coord_weight;
}

// Set the primary spatial coordinate weight
void PhaseSpacePoint::setPrimarySpatialCoordinateWeight(
                                                          const double weight )
{
  // Make sure that the weight is valid
  testPrecondition( weight > 0.0 );
  
  d_primary_spatial_coord_weight = weight;
}

// Return the secondary spatial coordinate of the phase space point
double PhaseSpacePoint::getSecondarySpatialCoordinate() const
{
  return d_secondary_spatial_coord;
}

// Set the secondary spatial coordinate of the phase space point
void PhaseSpacePoint::setSecondarySpatialCoordinate(
                                         const double secondary_spatial_coord )
{
  // Make sure that the coordinate is valid
  testPrecondition( d_spatial_coord_conversion_policy->isSecondarySpatialCoordinateValid( secondary_spatial_coord ) );
  
  d_secondary_spatial_coord = secondary_spatial_coord;
}

// Return the secondary spatial coordinate weight
double PhaseSpacePoint::getSecondarySpatialCoordinateWeight() const
{
  return d_secondary_spatial_coord_weight;
}

// Set the secondary spatial coordinate weight
void PhaseSpacePoint::setSecondarySpatialCoordinateWeight(
                                                          const double weight )
{
  // Make sure that the weight is valid
  testPrecondition( weight > 0.0 );
  
  d_secondary_spatial_coord_weight = weight;
}

// Return the tertiary spatial coordinate of the phase space point
double PhaseSpacePoint::getTertiarySpatialCoordinate() const
{
  return d_tertiary_spatial_coord;
}

// Set the tertiary spatial coordinate of the phase space point
void PhaseSpacePoint::setTertiarySpatialCoordinate(
                                          const double tertiary_spatial_coord )
{
  // Make sure that the coordinate is valid
  testPrecondition( d_spatial_coord_conversion_policy->isTertiarySpatialCoordinateValid( tertiary_spatial_coord ) );
  
  d_tertiary_spatial_coord = tertiary_spatial_coord;
}

// Return the tertiary spatial coordinate weight
double PhaseSpacePoint::getTertiarySpatialCoordinateWeight() const
{
  return d_tertiary_spatial_coord_weight;
}

// Set the tertiary spatial coordinate weight
void PhaseSpacePoint::setTertiarySpatialCoordinateWeight( const double weight )
{
  // Make sure that the weight is valid
  testPrecondition( weight > 0.0 );
  
  d_tertiary_spatial_coord_weight = weight;
}

// Convert spatial coordinates to cartesian coordinates
void PhaseSpacePoint::convertSpatialCoordinatesToCartesianCoordinates(
                                                double& x_spatial_coord,
                                                double& y_spatial_coord,
                                                double& z_spatial_coord ) const
{
  d_spatial_coord_conversion_policy->convertToCartesianSpatialCoordinates(
                                                     d_primary_spatial_coord,
                                                     d_secondary_spatial_coord,
                                                     d_tertiary_spatial_coord,
                                                     x_spatial_coord,
                                                     y_spatial_coord,
                                                     z_spatial_coord );
}

// Return the weight of all spatial coordinates
double PhaseSpacePoint::getWeightOfSpatialCoordinates() const
{
  return d_primary_spatial_coord_weight*
    d_secondary_spatial_coord_weight*
    d_tertiary_spatial_coord_weight;
}

// Return the primary Directional coordinate of the phase space point
double PhaseSpacePoint::getPrimaryDirectionalCoordinate() const
{
  return d_primary_directional_coord;
}

// Set the primary Directional coordinate of the phase space point
void PhaseSpacePoint::setPrimaryDirectionalCoordinate(
                                       const double primary_directional_coord )
{
  // Make sure that the coordinate is valid
  testPrecondition( d_directional_coord_conversion_policy->isPrimaryDirectionalCoordinateValid( primary_directional_coord ) );

  d_primary_directional_coord = primary_directional_coord;
}

// Return the primary Directional coordinate weight
double PhaseSpacePoint::getPrimaryDirectionalCoordinateWeight() const
{
  return d_primary_directional_coord_weight;
}
  
// Set the primary Directional coordinate weight
void PhaseSpacePoint::setPrimaryDirectionalCoordinateWeight(
                                                          const double weight )
{
  // Make sure that the weight is valid
  testPrecondition( weight > 0.0 );

  d_primary_directional_coord_weight = weight;
}

// Return the secondary Directional coordinate of the phase space point
double PhaseSpacePoint::getSecondaryDirectionalCoordinate() const
{
  return d_secondary_directional_coord;
}

// Set the secondary Directional coordinate of the phase space point
void PhaseSpacePoint::setSecondaryDirectionalCoordinate(
                                     const double secondary_directional_coord )
{
  // Make sure that the coordinate is valid
  testPrecondition( d_directional_coord_conversion_policy->isSecondaryDirectionalCoordinateValid( secondary_directional_coord ) );

  d_secondary_directional_coord = secondary_directional_coord;
}

// Return the secondary Directional coordinate weight
double PhaseSpacePoint::getSecondaryDirectionalCoordinateWeight() const
{
  return d_secondary_directional_coord_weight;
}

// Set the secondary Directional coordinate weight
void PhaseSpacePoint::setSecondaryDirectionalCoordinateWeight(
                                                          const double weight )
{
  // Make sure that the weight is valid
  testPrecondition( weight > 0.0 );

  d_secondary_directional_coord_weight = weight;
}

// Return the tertiary Directional coordinate of the phase space point
double PhaseSpacePoint::getTertiaryDirectionalCoordinate() const
{
  return d_tertiary_directional_coord;
}

// Set the tertiary Directional coordinate of the phase space point
void PhaseSpacePoint::setTertiaryDirectionalCoordinate(
                                      const double tertiary_directional_coord )
{
  // Make sure that the coordinate is valid
  testPrecondition( d_directional_coord_conversion_policy->isTertiaryDirectionalCoordinateValid( tertiary_directional_coord ) );

  d_tertiary_directional_coord = tertiary_directional_coord;
}

// Return the tertiary Directional coordinate weight
double PhaseSpacePoint::getTertiaryDirectionalCoordinateWeight() const
{
  return d_tertiary_directional_coord_weight;
}

// Set the tertiary Directional coordinate weight
void PhaseSpacePoint::setTertiaryDirectionalCoordinateWeight(
                                                          const double weight )
{
  // Make sure that the weight is valid
  testPrecondition( weight > 0.0 );

  d_tertiary_directional_coord_weight = weight;
}

// Convert directional coordinates to Cartesian coordinates
/*! \details After converting to the Cartesian coordinate system the 
 * directional coordinates will be normalized.
 */
void PhaseSpacePoint::convertDirectionalCoordinatesToCartesianCoordinates(
                                            double& x_directional_coord,
                                            double& y_directional_coord,
                                            double& z_directional_coord ) const
{
  // Normalize the directional coordinates
  double normalized_directional_coords[3] = {d_primary_directional_coord,
                                             d_secondary_directional_coord,
                                             d_tertiary_directional_coord};

  d_directional_coord_conversion_policy->normalizeLocalDirectionalCoordinates(
                                               normalized_directional_coords );
  
  d_directional_coord_conversion_policy->convertToCartesianDirectionalCoordinates(
                                              normalized_directional_coords[0],
                                              normalized_directional_coords[1],
                                              normalized_directional_coords[2],
                                              x_directional_coord,
                                              y_directional_coord,
                                              z_directional_coord );
}

// Return the weight of all directional coordinates
double PhaseSpacePoint::getWeightOfDirectionalCoordinates() const
{
  return d_primary_directional_coord_weight*
    d_secondary_directional_coord_weight*
    d_tertiary_directional_coord_weight;
}

// Return the energy coordinate of the phase space point
double PhaseSpacePoint::getEnergyCoordinate() const
{
  return d_energy_coord;
}

// Set the energy coordinate of the phase space point
void PhaseSpacePoint::setEnergyCoordinate( const double energy_coord )
{
  // Make sure the energy coordinate value is valid
  testPrecondition( energy_coord > 0.0 );

  d_energy_coord = energy_coord;
}

// Return the energy coordinate weight
double PhaseSpacePoint::getEnergyCoordinateWeight() const
{
  return d_energy_coord_weight;
}

// Set the energy coordinate weight
void PhaseSpacePoint::setEnergyCoordinateWeight( const double weight )
{
  // Make sure that the weight is valid
  testPrecondition( weight > 0.0 );

  d_energy_coord_weight = weight;
}

// Return the time coordinate of the phase space point
double PhaseSpacePoint::getTimeCoordinate() const
{
  return d_time_coord;
}

// Set the time coordinate of the phase space point
void PhaseSpacePoint::setTimeCoordinate( const double time_coord )
{
  // Make sure that the time coordinate value is valid
  testPrecondition( time_coord >= 0.0 );
  
  d_time_coord = time_coord;
}

// Return the time coordinate weight
double PhaseSpacePoint::getTimeCoordinateWeight() const
{
  return d_time_coord_weight;
}

// Set the time coordinate weight
void PhaseSpacePoint::setTimeCoordinateWeight( const double weight )
{
  // Make sure that the weight is valid
  testPrecondition( weight > 0.0 );
  
  d_time_coord_weight = weight;
}

// Return the weight coordinate of the phase space point
double PhaseSpacePoint::getWeightCoordinate() const
{
  return d_weight_coord;
}

// Set the weight coordinate of the phase space point
void PhaseSpacePoint::setWeightCoordinate( const double weight_coord )
{
  // Make sure that the weight coordinate value is valid
  testPrecondition( weight_coord > 0.0 );

  d_weight_coord = weight_coord;
}

// Return the weight of all coordinates
double PhaseSpacePoint::getWeightOfCoordinates() const
{
  return this->getWeightOfSpatialCoordinates()*
    this->getWeightOfDirectionalCoordinates()*
    this->getEnergyCoordinateWeight()*
    this->getTimeCoordinateWeight()*
    this->getWeightCoordinate();
}

// Set a particle state
/*! \details The particle source states will also be set by this method.
 */
void PhaseSpacePoint::setParticleState( ParticleState& particle ) const
{
  double cartesian_spatial_coords[3];

  this->convertSpatialCoordinatesToCartesianCoordinates(
                                                 cartesian_spatial_coords[0],
                                                 cartesian_spatial_coords[1],
                                                 cartesian_spatial_coords[2] );

  double cartesian_directional_coords[3];
  
  this->convertDirectionalCoordinatesToCartesianCoordinates(
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
// end MonteCarlo_PhaseSpacePoint.cpp
//---------------------------------------------------------------------------//
