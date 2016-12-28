//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSourcePhaseSpacePoint.hpp
//! \author Alex Robinson
//! \brief  Particle source phase space point class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SOURCE_PHASE_SPACE_POINT_HPP
#define MONTE_CARLO_PARTICLE_SOURCE_PHASE_SPACE_POINT_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ParticleSourceDimensionType.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "Utility_SpatialCoordinateConversionPolicy.hpp"
#include "Utility_DirectionalCoordinateConversionPolicy.hpp"

namespace MonteCarlo{

//! The particle source phase space point class
class ParticleSourcePhaseSpacePoint
{

public:

  //! Constructor
  ParticleSourcePhaseSpacePoint(
            const std::shared_ptr<const SpatialCoordinateConversionPolicy>&
            spatial_coord_conversion_policy,
            const std::shared_ptr<const DirectionalCoordinateConversionPolicy>&
            directional_coord_conversion_policy );

  //! Destructor
  ~ParticleSourcePhaseSpacePoint()
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

  //! Get the tertiary spatial coordinate weight
  double getTertiarySpatialCoordinateWeight() const;

  //! Convert spatial coordinates to cartesian coordinates
  void convertSpatialCoordinatesToCartesianCoordinates(
                                               double& x_spatial_coord,
                                               double& y_spatial_coord,
                                               double& z_spatial_coord ) const;

  //! Return the weight of all spatial coordinates
  double getWeightOfSpatialCoordinates() const;

  //! Return the primary Directional coordinate of the phase space point
  double getPrimaryDirectionalCoordinate() const;

  //! Set the primary Directional coordinate of the phase space point
  void setPrimaryDirectionalCoordinate( const double primary_directional_coord );

  //! Return the primary Directional coordinate weight
  double getPrimaryDirectionalCoordinateWeight() const;
  
  //! Set the primary Directional coordinate weight
  void setPrimaryDirectionalCoordinateWeight( const double weight );

  //! Return the secondary Directional coordinate of the phase space point
  double getSecondaryDirectionalCoordinate() const;

  //! Set the secondary Directional coordinate of the phase space point
  void setSecondaryDirectionalCoordinate( const double secondary_directional_coord );

  //! Return the secondary Directional coordinate weight
  double getSecondaryDirectionalCoordinateWeight() const;

  //! Set the secondary Directional coordinate weight
  void setSecondaryDirectionalCoordinateWeight( const double weight );

  //! Return the tertiary Directional coordinate of the phase space point
  double getTertiaryDirectionalCoordinate() const;

  //! Set the tertiary Directional coordinate of the phase space point
  void setTertiaryDirectionalCoordinate( const double tertiary_directional_coord );

  //! Return the tertiary Directional coordinate weight
  double getTertiaryDirectionalCoordinateWeight() const;

  //! Set the tertiary Directional coordinate weight
  void setTertiaryDirectionalCoordinateWeight( const double weight );

  //! Convert directional coordinates to cartesian coordinates
  void convertDirectionalCoordinatesToCartesianCoordinates(
                                       double& x_directional_coord,
                                       double& y_directional_coord,
                                       double& z_directional_coord ) const = 0;

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
  void getWeightCoordinate() const;

  //! Set the weight coordinate of the phase space point
  void setWeightCoordinate( const double weight_coord );

  //! Return the weight of all coordinates
  void getWeightOfCoordinates() const;

  //! Set a particle state
  void setParticleState( ParticleState& particle ) const;

  //! Return the dimension value
  template<ParticleSourceDimensionType dimension>
  double getCoordinate() const;

  //! Set the dimension value
  template<ParticleSourceDimensionType dimension>
  void setCoordinate( const double coord_value );

  //! Get the dimension weight
  template<ParticleSourceDimensionType dimension>
  double getCoordinateWeight() const;

  //! Set the dimension weight
  template<ParticleSourceDimensionType dimension>
  void setCoordinateWeight( const double coord_weight );

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
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_ParticleSourcePhaseSpacePoint_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_PARTICLE_SOURCE_PHASE_SPACE_POINT_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSourcePhaseSpacePoint.hpp
//---------------------------------------------------------------------------//
