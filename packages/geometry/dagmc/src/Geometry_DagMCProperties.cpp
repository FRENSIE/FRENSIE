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
#include "Utility_ContractException.hpp"

namespace Geometry{

// Initialize the static member data
std::string DagMCProperties::termination_cell_property = "termination.cell";
std::string DagMCProperties::material_property = "material";
std::string DagMCProperties::density_property = "density";
std::string DagMCProperties::estimator_property = "estimator";
std::string DagMCProperties::surface_current_name = "surface.current";
std::string DagMCProperties::surface_flux_name = "surface.flux";
std::string DagMCProperties::cell_pulse_height_name = "cell.pulse.height";
std::string DagMCProperties::cell_track_length_flux_name = "cell.tl.flux";
std::string DagMCProperties::cell_collision_flux_name = "cell.c.flux";

// Set the termination cell property name
void DagMCProperties::setTerminationCellPropertyName( const std::string& name )
{
  // Make sure the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );
  
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
  // Make sure the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );
  
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
  // Make sure the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );
  
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
  // Make sure the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );
  
  DagMCProperties::estimator_property = name;
}

// Get the estimator property name
const std::string& DagMCProperties::getEstimatorPropertyName()
{
  return DagMCProperties::estimator_property;
}

// Set the surface current name
void DagMCProperties::setSurfaceCurrentName( const std::string& name )
{
  // Make sure the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );
  
  DagMCProperties::surface_current_name = name;
}

// Get the surface current name
const std::string& DagMCProperties::getSurfaceCurrentName()
{
  return DagMCProperties::surface_current_name;
}

// Set the surface flux name
void DagMCProperties::setSurfaceFluxName( const std::string& name )
{
  // Make sure the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );

  DagMCProperties::surface_flux_name = name;
}

// Get the surface flux name
const std::string& DagMCProperties::getSurfaceFluxName()
{
  return DagMCProperties::surface_flux_name;
}

// Set the cell pulse height name
void DagMCProperties::setCellPulseHeightName( const std::string& name )
{
  // Make sure the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );

  DagMCProperties::cell_pulse_height_name = name;
}

// Get the cell pulse height name
const std::string& DagMCProperties::getCellPulseHeightName()
{
  return DagMCProperties::cell_pulse_height_name;
}

// Set the cell track-length flux name
void DagMCProperties::setCellTrackLengthFluxName( const std::string& name )
{
  // Make sure the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );
  
  DagMCProperties::cell_track_length_flux_name = name;
}

// Get the cell pulse height name
const std::string& DagMCProperties::getCellTrackLengthFluxName()
{
  return DagMCProperties::cell_track_length_flux_name;
}

// Set the cell collision flux name
void DagMCProperties::setCellCollisionFluxName( const std::string& name )
{
  // Make sure the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );
  
  DagMCProperties::cell_collision_flux_name = name;
}

// Get the cell collision flux name
const std::string& DagMCProperties::getCellCollisionFluxName()
{
  return DagMCProperties::cell_collision_flux_name;
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

  TEST_FOR_EXCEPTION( first_pos > prop_value.size(),
                      std::runtime_error,
                      "Error: the observer property " << prop_value <<
                      " found in the .sat file is invalid (the form needs to "
                      "be id.type.ptype)!" );
  TEST_FOR_EXCEPTION( last_pos > prop_value.size(),
                      std::runtime_error,
                      "Error: the observer property " << prop_value <<
                      " found in the .sat file is invalid (the form needs to "
                      "be id.type.ptype)!" );
  TEST_FOR_EXCEPTION( first_pos == last_pos,
                      std::runtime_error,
                      "Error: the observer property " << prop_value <<
                      " found in the .sat file is invalid (the form needs to "
                      "be id.type.ptype)!" );

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
  return estimator_type.compare(DagMCProperties::cell_pulse_height_name)== 0 ||
    estimator_type.compare(DagMCProperties::cell_track_length_flux_name)== 0 ||
    estimator_type.compare( DagMCProperties::cell_collision_flux_name ) == 0;
}

// Check if the cell observer type is valid
bool DagMCProperties::isCellObserverTypeValid( const std::string& observer_type )
{
  return DagMCProperties::isCellEstimatorTypeValid( observer_type );
}

// Check if the surface estimator type is valid
bool DagMCProperties::isSurfaceEstimatorTypeValid( 
					    const std::string& estimator_type )
{
  return estimator_type.compare( DagMCProperties::surface_flux_name ) == 0 ||
    estimator_type.compare( DagMCProperties::surface_current_name ) == 0;
}

// Check if the surface observer type is valid
bool DagMCProperties::isSurfaceObserverTypeValid( const std::string& observer_type )
{
  return DagMCProperties::isSurfaceEstimatorTypeValid( observer_type );
}

// Check if the estimator type is valid
bool DagMCProperties::isEstimatorTypeValid( const std::string& estimator_type )
{
  return DagMCProperties::isCellEstimatorTypeValid( estimator_type ) ||
    DagMCProperties::isSurfaceEstimatorTypeValid( estimator_type );
}

// Check if the observer type is valid
bool DagMCProperties::isObserverTypeValid( const std::string& observer_type )
{
  return DagMCProperties::isEstimatorTypeValid( observer_type );
}

// Check if the particle type is valid
bool DagMCProperties::isParticleTypeValid( const std::string& particle_type )
{
  return particle_type.compare( "n" ) == 0 ||
    particle_type.compare( "p" ) == 0 ||
    particle_type.compare( "e" ) == 0;
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
