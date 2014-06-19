//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCProperties.cpp
//! \author Alex Robinson
//! \brief  DagMC property keywords class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>

// FRENSIE Includes
#include "Geometry_DagMCProperties.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Geometry{

// Initialize the static member data
std::string DagMCProperties::termination_cell_property = "termination.cell";
std::string DagMCProperties::material_property = "material";
std::string DagMCProperties::density_property = "density";
std::string DagMCProperties::estimator_property = "estimator";

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

// Extract estimator property values
/*! \details An estimator property is assumed to have the form 
 *  id.type.ptype
 */
void DagMCProperties::extractEstimatorPropertyValues( 
						 const std::string& prop_value,
						 unsigned& estimator_id,
						 std::string& estimator_type,
						 std::string& particle_type )
{
  unsigned first_pos = prop_value.find_first_of( "." );
  unsigned last_pos = prop_value.find_last_of( "." );

  std::string id_string = prop_value.substr( 0, first_pos );

  std::istringstream iss( id_string );

  iss >> estimator_id;

  estimator_type = prop_value.substr( first_pos+1, last_pos-first_pos-1 );

  particle_type = prop_value.substr( last_pos+1, prop_value.size()-last_pos-1);
}
	
// Check if the cell estimator type is valid
bool DagMCProperties::isCellEstimatorTypeValid( 
					    const std::string& estimator_type )
{
  return estimator_type.compare( "cell.pulse.height" ) == 0 ||
    estimator_type.compare( "cell.tl.flux" ) == 0 ||
    estimator_type.compare( "cell.c.flux" ) == 0;
}

// Check if the surface estimator type is valid
bool DagMCProperties::isSurfaceEstimatorTypeValid( 
					    const std::string& estimator_type )
{
  return estimator_type.compare( "surface.flux" ) == 0 ||
    estimator_type.compare( "surface.current" ) == 0;
}

// Check if the particle type is valid
bool DagMCProperties::isParticleTypeValid( const std::string& particle_type )
{
  return particle_type.compare( "n" ) == 0 ||
    particle_type.compare( "p" ) == 0;
}

// Get all of the properties
void DagMCProperties::getProperties( std::vector<std::string>& properties )
{
  properties.clear();
  properties.resize( 4 );

  properties[0] = DagMCProperties::termination_cell_property;
  properties[1] = DagMCProperties::material_property;
  properties[2] = DagMCProperties::density_property;
  properties[3] = DagMCProperties::estimator_property;
}

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_DagMCProperties.cpp
//---------------------------------------------------------------------------//
