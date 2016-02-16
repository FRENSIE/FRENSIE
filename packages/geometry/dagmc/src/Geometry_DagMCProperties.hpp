//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCProperties.hpp
//! \author Alex Robinson
//! \brief  DagMC property keywords class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_DAGMC_PROPERTIES_HPP
#define GEOMETRY_DAGMC_PROPERTIES_HPP

// Std Lib Includes
#include <string>
#include <vector>

namespace Geometry{

//! The DagMC property class
class DagMCProperties
{

public:

  //! Set the termination cell property name
  static void setTerminationCellPropertyName( const std::string& name );

  //! Get the termination cell property name
  static const std::string& getTerminationCellPropertyName();

  //! Set the material property name
  static void setMaterialPropertyName( const std::string& name );

  //! Get the material property name
  static const std::string& getMaterialPropertyName();

  //! Set the density property name
  static void setDensityPropertyName( const std::string& name );

  //! Get the density property name
  static const std::string& getDensityPropertyName();

  //! Set the estimator property name
  static void setEstimatorPropertyName( const std::string& name );

  //! Get the estimator property name
  static const std::string& getEstimatorPropertyName();

  //! Set the surface current name
  static void setSurfaceCurrentName( const std::string& name );

  //! Get the surface current name
  static const std::string& getSurfaceCurrentName();

  //! Set the surface flux name
  static void setSurfaceFluxName( const std::string& name );

  //! Get the surface flux name
  static const std::string& getSurfaceFluxName();

  //! Set the cell pulse height name
  static void setCellPulseHeightName( const std::string& name );

  //! Get the cell pulse height name
  static const std::string& getCellPulseHeightName();

  //! Set the cell track-length flux name
  static void setCellTrackLengthFluxName( const std::string& name );

  //! Get the cell pulse height name
  static const std::string& getCellTrackLengthFluxName();

  //! Set the cell collision flux name
  static void setCellCollisionFluxName( const std::string& name );

  //! Get the cell collision flux name
  static const std::string& getCellCollisionFluxName();

  //! Extract estimator property values
  static void extractEstimatorPropertyValues( const std::string& prop_value,
					      unsigned& estimator_id,
					      std::string& estimator_type,
					      std::string& particle_type );

  //! Check if the cell estimator type is valid
  static bool isCellEstimatorTypeValid( const std::string& estimator_type );

  //! Check if the cell observer type is valid
  static bool isCellObserverTypeValid( const std::string& observer_type );

  //! Check if the surface estimator type is valid
  static bool isSurfaceEstimatorTypeValid( const std::string& estimator_type );

  //! Check if the surface observer type is valid
  static bool isSurfaceObserverTypeValid( const std::string& observer_type );

  //! Check if the estimator type is valid
  static bool isEtimatorTypeValid( const std::string& estimator_type );

  //! Check if the observer type is valid
  static bool isObserverTypeValid( const std::string& observer_type );

  //! Check if the particle type is valid
  static bool isParticleTypeValid( const std::string& particle_type );

  //! Get all of the properties
  static void getProperties( std::vector<std::string>& properties );

private:

  //! The termination cell property name
  static std::string termination_cell_property;

  //! The material property name
  static std::string material_property;

  //! The density property name
  static std::string density_property;

  //! The estimator property name
  static std::string estimator_property;

  //! The surface current name
  static std::string surface_current_name;

  //! The surface flux name
  static std::string surface_flux_name;

  //! The cell pulse height name
  static std::string cell_pulse_height_name;

  //! The cell track-length flux name
  static std::string cell_track_length_flux_name;

  //! The cell collision flux name
  static std::string cell_collision_flux_name;
};

} // end Geometry namespace

#endif // end GEOMETRY_DAGMC_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Geometry_DagMCProperties.hpp
//---------------------------------------------------------------------------//
