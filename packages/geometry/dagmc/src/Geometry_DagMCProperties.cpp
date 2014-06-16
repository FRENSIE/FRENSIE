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
const std::string DagMCProperties::termination_cell_property = 
  "termination.cell";

const std::string DagMCProperties::material_property = "material";

const std::string DagMCProperties::density_property = "density";

const std::string DagMCProperties::estimator_property = "estimator";

const std::string DagMCProperties::cell_track_length_flux_property = 
  "cell.tl.flux";

const std::string DagMCProperties::cell_collision_flux_property = 
  "cell.c.flux";

const std::string DagMCProperties::cell_pulse_height_property = 
  "cell.pulse.height";

const std::string DagMCProperties::surface_flux_property = 
  "surface.flux";

const std::string DagMCProperties::surface_current_property = 
  "surface.current";

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
