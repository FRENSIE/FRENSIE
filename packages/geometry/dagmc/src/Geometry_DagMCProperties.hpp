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

  //! Set the cell track length flux property name
  static void setCellTrackLengthFluxPropertyName( const std::string& name );
  
  //! Get the cell track length flux property name
  static const std::string& getCellTrackLengthFluxPropertyName();

  //! Set the cell collision flux property name
  static void setCellCollisionFluxPropertyName( const std::string& name );
  
  //! Get the cell collision flux property name
  static const std::string& getCellCollisionFluxPropertyName();

  //! Set the cell pulse height property name
  static void setCellPulseHeightPropertyName( const std::string& name );

  //! Get the cell pulse height property name
  static const std::string& getCellPulseHeightPropertyName();

  //! Set the surface flux property name
  static void setSurfaceFluxPropertyName( const std::string& name );

  //! Get the surface flux property name
  static const std::string& getSurfaceFluxPropertyName();

  //! Set the surface current property name
  static void setSurfaceCurrentPropertyName( const std::string& name );

  //! Get the surface current property name
  static const std::string& getSurfaceCurrentPropertyName();

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

  //! The cell track length flux property name
  static std::string cell_track_length_flux_property;

  //! The cell collision flux property name
  static std::string cell_collision_flux_property;
  
  //! The cell pulse height property name
  static std::string cell_pulse_height_property;

  //! The surface flux property name
  static std::string surface_flux_property;

  //! The surface current property name
  static std::string surface_current_property;
};

} // end Geometry namespace

#endif // end GEOMETRY_DAGMC_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Geometry_DagMCProperties.hpp
//---------------------------------------------------------------------------//
