//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCProperties.cpp
//! \author Alex Robinson
//! \brief  DagMC property keywords class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Geometry_DagMCProperties.hpp"

namespace Geometry{

// Initialize the static member data
std::string DagMCProperties::termination_cell_property = "termination.cell";
std::string DagMCProperties::material_property = "material";
std::string DagMCProperties::density_property = "density";
std::string DagMCProperties::estimator_property = "estimator";
std::string DagMCProperties::cell_track_length_flux_property = "cell.tl.flux";
std::string DagMCProperties::cell_collision_flux_property = "cell.c.flux";
std::string DagMCProperties::cell_pulse_height_property = "cell.pulse.height";
std::string DagMCProperties::surface_flux_property = "surface.flux";
std::string DagMCProperties::surface_current_property = "surface.current";

// Set the termination cell property name
void DagMCProperties::setTerminationCellPropertyName( const std::string& name )
{
  DagMCProperties::termination_cell_property = name;
}

// Get the termination cell property name
const std::string& DagMCProperties::getTerminationCellPropertyName()
{
  return DagMCProperties::termination_cell_property;
}

// Set the material property name
void DagMCProperties::setMaterialPropertyName( const std::string& name )
{
  DagMCProperties::material_property = name;
}

// Get the material property name
const std::string& DagMCProperties::getMaterialPropertyName()
{
  return DagMCProperties::material_property;
}

// Set the density property name
void DagMCProperties::setDensityPropertyName( const std::string& name )
{
  DagMCProperties::density_property = name;
}

// Get the density property name
const std::string& DagMCProperties::getDensityPropertyName()
{
  return DagMCProperties::density_property;
}

// Set the estimator property name
void DagMCProperties::setEstimatorPropertyName( const std::string& name )
{
  DagMCProperties::estimator_property = name;
}

// Get the estimator property name
const std::string& DagMCProperties::getEstimatorPropertyName()
{
  return DagMCProperties::estimator_property;
}

// Set the cell track length flux property name
void DagMCProperties::setCellTrackLengthFluxPropertyName( 
						      const std::string& name )
{
  DagMCProperties::cell_track_length_flux_property = name;
}
  
// Get the cell track length flux property name
const std::string& DagMCProperties::getCellTrackLengthFluxPropertyName()
{
  return DagMCProperties::cell_track_length_flux_property;
}

// Set the cell collision flux property name
void DagMCProperties::setCellCollisionFluxPropertyName(
						      const std::string& name )
{
  DagMCProperties::cell_collision_flux_property = name;
}
  
// Get the cell collision flux property name
const std::string& DagMCProperties::getCellCollisionFluxPropertyName()
{
  return DagMCProperties::cell_collision_flux_property;
}

// Set the cell pulse height property name
void DagMCProperties::setCellPulseHeightPropertyName( const std::string& name )
{
  DagMCProperties::cell_pulse_height_property = name;
}

// Get the cell pulse height property name
const std::string& DagMCProperties::getCellPulseHeightPropertyName()
{
  return DagMCProperties::cell_pulse_height_property;
}

// Set the surface flux property name
void DagMCProperties::setSurfaceFluxPropertyName( const std::string& name )
{
  DagMCProperties::surface_flux_property = name;
}

// Get the surface flux property name
const std::string& DagMCProperties::getSurfaceFluxPropertyName()
{
  return DagMCProperties::surface_flux_property;
}

// Set the surface current property name
void DagMCProperties::setSurfaceCurrentPropertyName( const std::string& name )
{
  DagMCProperties::surface_current_property = name;
}

// Get the surface current property name
const std::string& DagMCProperties::getSurfaceCurrentPropertyName()
{
  return DagMCProperties::surface_current_property;
}

// Get all of the properties
void DagMCProperties::getProperties( std::vector<std::string>& properties )
{
  properties.clear();
  properties.resize( 9 );

  properties[0] = DagMCProperties::termination_cell_property;
  properties[1] = DagMCProperties::material_property;
  properties[2] = DagMCProperties::density_property;
  properties[3] = DagMCProperties::estimator_property;
  properties[4] = DagMCProperties::cell_track_length_flux_property;
  properties[5] = DagMCProperties::cell_collision_flux_property;
  properties[6] = DagMCProperties::cell_pulse_height_property;
  properties[7] = DagMCProperties::surface_flux_property;
  properties[8] = DagMCProperties::surface_current_property;
}

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_DagMCProperties.cpp
//---------------------------------------------------------------------------//
