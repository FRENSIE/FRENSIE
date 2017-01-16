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
ParticleSourcePhaseSpacePoint::ParticleSourcePhaseSpacePoint(
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

// Return the primary spatial coordinate of the phase space point
double ParticleSourcePhaseSpacePoint::getPrimarySpatialCoordinate() const
{
  return d_primary_spatial_coord;
}

// Set the primary spatial coordinate of the phase space point
void ParticleSourcePhaseSpacePoint::setPrimarySpatialCoordinate(
                                           const double primary_spatial_coord )
{
  // Make sure that the coordinate is valid
  testPrecondition( d_spatial_coord_conversion_policy->isPrimarySpatialCoordinateValid( primary_spatial_coord ) );
  
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
  // Make sure that the coordinate is valid
  testPrecondition( d_spatial_coord_conversion_policy->isSecondarySpatialCoordinateValid( secondary_spatial_coord ) );
  
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
  // Make sure that the coordinate is valid
  testPrecondition( d_spatial_coord_conversion_policy->isTertiarySpatialCoordinateValid( tertiary_spatial_coord ) );
  
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
double ParticleSourcePhaseSpacePoint::getWeightOfSpatialCoordinates() const
{
  return d_primary_spatial_coord_weight*
    d_secondary_spatial_coord_weight*
    d_tertiary_spatial_coord_weight;
}

// Return the primary Directional coordinate of the phase space point
double ParticleSourcePhaseSpacePoint::getPrimaryDirectionalCoordinate() const
{
  return d_primary_directional_coord;
}

// Set the primary Directional coordinate of the phase space point
void ParticleSourcePhaseSpacePoint::setPrimaryDirectionalCoordinate(
                                       const double primary_directional_coord )
{
  // Make sure that the coordinate is valid
  testPrecondition( d_directional_coord_conversion_policy->isPrimaryDirectionalCoordinateValid( primary_directional_coord ) );

  d_primary_directional_coord = primary_directional_coord;
}

// Return the primary Directional coordinate weight
double ParticleSourcePhaseSpacePoint::getPrimaryDirectionalCoordinateWeight() const
{
  return d_primary_directional_coord_weight;
}
  
// Set the primary Directional coordinate weight
void ParticleSourcePhaseSpacePoint::setPrimaryDirectionalCoordinateWeight(
                                                          const double weight )
{
  // Make sure that the weight is valid
  testPrecondition( weight > 0.0 );

  d_primary_directional_coord_weight = weight;
}

// Return the secondary Directional coordinate of the phase space point
double ParticleSourcePhaseSpacePoint::getSecondaryDirectionalCoordinate() const
{
  return d_secondary_directional_coord;
}

// Set the secondary Directional coordinate of the phase space point
void ParticleSourcePhaseSpacePoint::setSecondaryDirectionalCoordinate(
                                     const double secondary_directional_coord )
{
  // Make sure that the coordinate is valid
  testPrecondition( d_directional_coord_conversion_policy->isSecondaryDirectionalCoordinateValid( secondary_directional_coord ) );

  d_secondary_directional_coord = secondary_directional_coord;
}

// Return the secondary Directional coordinate weight
double ParticleSourcePhaseSpacePoint::getSecondaryDirectionalCoordinateWeight() const
{
  return d_secondary_directional_coord_weight;
}

// Set the secondary Directional coordinate weight
void ParticleSourcePhaseSpacePoint::setSecondaryDirectionalCoordinateWeight(
                                                          const double weight )
{
  // Make sure that the weight is valid
  testPrecondition( weight > 0.0 );

  d_secondary_directional_coord_weight = weight;
}

// Return the tertiary Directional coordinate of the phase space point
double ParticleSourcePhaseSpacePoint::getTertiaryDirectionalCoordinate() const
{
  return d_tertiary_directional_coord;
}

// Set the tertiary Directional coordinate of the phase space point
void ParticleSourcePhaseSpacePoint::setTertiaryDirectionalCoordinate(
                                      const double tertiary_directional_coord )
{
  // Make sure that the coordinate is valid
  testPrecondition( d_directional_coord_conversion_policy->isTertiaryDirectionalCoordinateValid( tertiary_directional_coord ) );

  d_tertiary_directional_coord = tertiary_directional_coord;
}

// Return the tertiary Directional coordinate weight
double ParticleSourcePhaseSpacePoint::getTertiaryDirectionalCoordinateWeight() const
{
  return d_tertiary_directional_coord_weight;
}

// Set the tertiary Directional coordinate weight
void ParticleSourcePhaseSpacePoint::setTertiaryDirectionalCoordinateWeight(
                                                          const double weight )
{
  // Make sure that the weight is valid
  testPrecondition( weight > 0.0 );

  d_tertiary_directional_coord_weight = weight;
}

// Convert directional coordinates to cartesian coordinates
void ParticleSourcePhaseSpacePoint::convertDirectionalCoordinatesToCartesianCoordinates(
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
double ParticleSourcePhaseSpacePoint::getWeightOfDirectionalCoordinates() const
{
  return d_primary_directional_coord_weight*
    d_secondary_directional_coord_weight*
    d_tertiary_directional_coord_weight;
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
double ParticleSourcePhaseSpacePoint::getWeightCoordinate() const
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
double ParticleSourcePhaseSpacePoint::getWeightOfCoordinates() const
{
  return this->getWeightOfSpatialCoordinates()*
    this->getWeightOfDirectionalCoordinates()*
    this->getEnergyCoordinateWeight()*
    this->getTimeCoordinateWeight()*
    this->getWeightCoordinate();
}

// Set a particle state
void ParticleSourcePhaseSpacePoint::setParticleState(
                                                ParticleState& particle ) const
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
// end MonteCarlo_ParticleSourcePhaseSpacePoint.cpp
//---------------------------------------------------------------------------//
