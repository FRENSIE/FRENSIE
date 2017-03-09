//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhaseSpacePoint.hpp
//! \author Alex Robinson
//! \brief  Phase space point class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHASE_SPACE_POINT_HPP
#define MONTE_CARLO_PHASE_SPACE_POINT_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "Utility_SpatialCoordinateConversionPolicy.hpp"
#include "Utility_DirectionalCoordinateConversionPolicy.hpp"

namespace MonteCarlo{

//! The particle source phase space point class
class PhaseSpacePoint
{

public:

  //! Constructor (default initialization)
  PhaseSpacePoint(
   const std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>&
   spatial_coord_conversion_policy,
   const std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>&
   directional_coord_conversion_policy );

  //! Constructor (particle state initialization)
  PhaseSpacePoint(
   const ParticleState& particle,
   const std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>&
   spatial_coord_conversion_policy,
   const std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>&
   directional_coord_conversion_policy );

  //! Destructor
  ~PhaseSpacePoint()
  { /* ... */ }

  //! Return the primary spatial coordinate of the phase space point
  double getPrimarySpatialCoordinate() const;

  //! Set the primary spatial coordinate of the phase space point
  void setPrimarySpatialCoordinate( const double primary_spatial_coord );

  //! Return the primary spatial coordinate weight
  double getPrimarySpatialCoordinateWeight() const;

  //! Set the primary spatial coordinate weight
  void setPrimarySpatialCoordinateWeight( const double weight );

  //! Return the secondary spatial coordinate of the phase space point
  double getSecondarySpatialCoordinate() const;

  //! Set the secondary spatial coordinate of the phase space point
  void setSecondarySpatialCoordinate( const double secondary_spatial_coord );

  //! Return the secondary spatial coordinate weight
  double getSecondarySpatialCoordinateWeight() const;

  //! Set the secondary spatial coordinate weight
  void setSecondarySpatialCoordinateWeight( const double weight );

  //! Return the tertiary spatial coordinate of the phase space point
  double getTertiarySpatialCoordinate() const;

  //! Set the tertiary spatial coordinate of the phase space point
  void setTertiarySpatialCoordinate( const double tertiary_spatial_coord );

  //! Return the tertiary spatial coordinate weight
  double getTertiarySpatialCoordinateWeight() const;

  //! Set the tertiary spatial coordinate weight
  void setTertiarySpatialCoordinateWeight( const double weight );

  //! Convert spatial coordinates to Cartesian coordinates
  void convertSpatialCoordinatesToCartesianCoordinates(
                                               double& x_spatial_coord,
                                               double& y_spatial_coord,
                                               double& z_spatial_coord ) const;

  //! Convert spatial coordinates to Cartesian coordinates
  void convertSpatialCoordinatesToCartesianCoordinates(
                                              double spatial_coords[3] ) const;
                                              
  //! Return the weight of all spatial coordinates
  double getWeightOfSpatialCoordinates() const;

  //! Return the primary directional coordinate of the phase space point
  double getPrimaryDirectionalCoordinate() const;

  //! Set the primary directional coordinate of the phase space point
  void setPrimaryDirectionalCoordinate( const double primary_directional_coord );

  //! Return the primary directional coordinate weight
  double getPrimaryDirectionalCoordinateWeight() const;
  
  //! Set the primary directional coordinate weight
  void setPrimaryDirectionalCoordinateWeight( const double weight );

  //! Return the secondary directional coordinate of the phase space point
  double getSecondaryDirectionalCoordinate() const;

  //! Set the secondary directional coordinate of the phase space point
  void setSecondaryDirectionalCoordinate( const double secondary_directional_coord );

  //! Return the secondary directional coordinate weight
  double getSecondaryDirectionalCoordinateWeight() const;

  //! Set the secondary directional coordinate weight
  void setSecondaryDirectionalCoordinateWeight( const double weight );

  //! Return the tertiary directional coordinate of the phase space point
  double getTertiaryDirectionalCoordinate() const;

  //! Set the tertiary directional coordinate of the phase space point
  void setTertiaryDirectionalCoordinate( const double tertiary_directional_coord );

  //! Return the tertiary directional coordinate weight
  double getTertiaryDirectionalCoordinateWeight() const;

  //! Set the tertiary directional coordinate weight
  void setTertiaryDirectionalCoordinateWeight( const double weight );

  //! Convert directional coordinates to Cartesian coordinates
  void convertDirectionalCoordinatesToCartesianCoordinates(
                                           double& u_directional_coord,
                                           double& v_directional_coord,
                                           double& w_directional_coord ) const;

  //! Convert directional coordinates to Cartesian coordinates
  void convertDirectionalCoordinatesToCartesianCoordinates(
                                          double directional_coords[3] ) const;

  //! Return the weight of all directional coordinates
  double getWeightOfDirectionalCoordinates() const;

  //! Return the energy coordinate of the phase space point
  double getEnergyCoordinate() const;

  //! Set the energy coordinate of the phase space point
  void setEnergyCoordinate( const double energy_coord );

  //! Return the energy coordinate weight
  double getEnergyCoordinateWeight() const;

  //! Set the energy coordinate weight
  void setEnergyCoordinateWeight( const double weight );

  //! Return the time coordinate of the phase space point
  double getTimeCoordinate() const;

  //! Set the time coordinate of the phase space point
  void setTimeCoordinate( const double time_coord );

  //! Return the time coordinate weight
  double getTimeCoordinateWeight() const;

  //! Set the time coordinate weight
  void setTimeCoordinateWeight( const double weight );

  //! Return the weight coordinate of the phase space point
  double getWeightCoordinate() const;

  //! Set the weight coordinate of the phase space point
  void setWeightCoordinate( const double weight_coord );

  //! Return the weight of all coordinates
  double getWeightOfCoordinates() const;

  //! Set a particle state
  void setParticleState( ParticleState& particle ) const;

private:

  // The spatial coordinate conversion policy
  std::shared_ptr<const Utility::SpatialCoordinateConversionPolicy>
  d_spatial_coord_conversion_policy;

  // The directional coordinate conversion policy
  std::shared_ptr<const Utility::DirectionalCoordinateConversionPolicy>
  d_directional_coord_conversion_policy;

  // The primary spatial coordinate
  double d_primary_spatial_coord;

  // The primary spatial coordinate weight
  double d_primary_spatial_coord_weight;

  // The secondary spatial coordinate
  double d_secondary_spatial_coord;

  // The secondary spatial coordinate weight
  double d_secondary_spatial_coord_weight;

  // The tertiary spatial coordinate
  double d_tertiary_spatial_coord;

  // The tertiary spatial coordinate weight
  double d_tertiary_spatial_coord_weight;
  
  // The primary directional coordinate
  double d_primary_directional_coord;

  // The primary directional coordinate weight
  double d_primary_directional_coord_weight;

  // The secondary directional coordinate
  double d_secondary_directional_coord;

  // The secondary directional coordinate weight
  double d_secondary_directional_coord_weight;

  // The tertiary directional coordinate
  double d_tertiary_directional_coord;

  // The tertiary directional coordinate weight
  double d_tertiary_directional_coord_weight;

  // The energy coordinate
  double d_energy_coord;

  // The energy coordinate weight
  double d_energy_coord_weight;

  // The time coordinate
  double d_time_coord;

  // The time coordinate weight
  double d_time_coord_weight;

  // The weight coordinate
  double d_weight_coord;
};

// Convert spatial coordinates to Cartesian coordinates
inline void PhaseSpacePoint::convertSpatialCoordinatesToCartesianCoordinates(
                                               double spatial_coords[3] ) const
{
  this->convertSpatialCoordinatesToCartesianCoordinates( spatial_coords[0],
                                                         spatial_coords[1],
                                                         spatial_coords[2] );
}

// Convert directional coordinates to Cartesian coordinates
inline void PhaseSpacePoint::convertDirectionalCoordinatesToCartesianCoordinates(
                                           double directional_coords[3] ) const
{
  this->convertDirectionalCoordinatesToCartesianCoordinates(
                                                       directional_coords[0],
                                                       directional_coords[1],
                                                       directional_coords[2] );
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHASE_SPACE_POINT_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhaseSpacePoint.hpp
//---------------------------------------------------------------------------//
