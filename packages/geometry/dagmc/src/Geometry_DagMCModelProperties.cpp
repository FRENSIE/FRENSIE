//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCModelProperties.cpp
//! \author Alex Robinson
//! \brief  DagMC model properties class declaration
//!
//---------------------------------------------------------------------------//

// Freeablo Includes
#include "Geometry_DagMCModelProperties.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Geometry{

// Constructor
DagMCModelProperties::DagMCModelProperties( const std::string& filename )
  : d_file_name( file_name ),
    d_facet_tolerance( 1e-3 ),
    d_fast_id_lookup( false ),
    d_termination_cell_property( "termination.cell" ),
    d_reflecting_surface_property( "reflecting.surface" ),
    d_material_property( "material" ),
    d_density_property( "density" ),
    d_estimator_property( "estimator" ),
    d_surface_current_name( "surface.current" ),
    d_surface_flux_name( "surface.flux" ),
    d_cell_pulse_height_name( "cell.pulse.height" ),
    d_cell_track_length_flux_name( "cell.tl.flux" ),
    d_cell_collision_flux_name( "cell.c.flux" )
{
  // Make sure that the file name is valid
  testPrecondition( filename.size() > 0 );
}

// Get the model file name
const std::string& DagMCModelProperties::getModelFileName() const
{
  return d_file_name;
}

// Set the face tolerance for the model
void DagMCModelProperties::setFacetTolerance( const double facet_tol )
{
  // Make sure that the facet tolerance is valid
  testPrecondition( facet_tol > 0.0 );
  testPrecondition( facet_tol < 1.0 );

  d_face_tolerance = facet_tol;
}
  
// Get the facet tolerance for the model
double DagMCModelProperties::getFacetTolerance() const
{
  return d_facet_tolerance;
}

// Check if fast id lookup is used with the model
bool DagMCModelProperties::isFastIdLookupUsed() const
{
  return d_fast_id_lookup;
}

// Use fast id lookup with the model
void DagMCModelProperties::useFastIdLookup()
{
  d_fast_id_lookup = true;
}

// Use standard id lookup with the model
void DagMCModelProperties::useStandardIdLookup()
{
  d_fast_id_lookup = false;
}

// Set the termination cell property name
void DagMCModelProperties::setTerminationCellPropertyName(
                                                      const std::string& name )
{
  // Make sure that the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );

  d_termination_cell_property = name;
}

// Get the termination cell property name
const std::string& DagMCModelProperties::getTerminationCellPropertyName()
{
  return d_termination_cell_property;
}

// Set the reflecting surface property name
void DagMCModelProperties::setReflectingSurfacePropertyName(
                                                      const std::string& name )
{
  // Make sure that the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );

  d_reflecting_surface_property = name;
}

// Get the reflecting surface property name
const std::string& DagMCModelProperties::getReflectingSurfacePropertyName() const
{
  return d_reflecting_surface_property;
}

// Set the reflecting surface property name
void DagMCModelProperties::setReflectingSurfacePropertyName( const std::string& name )
{
  // Make sure that the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );

  d_reflecting_surface_property = name;
}

// Get the reflecting surface property name
const std::string& DagMCModelProperties::getReflectingSurfacePropertyName()
{
  return d_reflecting_surface_property;
}

// Set the material property name
void DagMCModelProperties::setMaterialPropertyName( const std::string& name )
{
  // Make sure that the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );

  d_material_property = name;
}

// Get the material property name
const std::string& DagMCModelProperties::getMaterialPropertyName()
{
  return d_material_property;
}

// Set the density property name
void DagMCModelProperties::setDensityPropertyName( const std::string& name )
{
  // Make sure that the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );
  
  d_density_property = name;
}

// Get the density property name
const std::string& DagMCModelProperties::getDensityPropertyName()
{
  return d_density_property;
}

// Set the estimator property name
void DagMCModelProperties::setEstimatorPropertyName( const std::string& name )
{
  // Make sure that the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );

  d_estimator_property = name;
}

// Get the estimator property name
const std::string& DagMCModelProperties::getEstimatorPropertyName()
{
  return d_estimator_property;
}

// Get all of the properties
void DagMCModelProperties::getPropertyNames( std::vector<std::string>& properties )
{
  properties.clear();
  properties.resize( 5 );

  properties[0] = d_termination_cell_property;
  properties[1] = d_reflecting_surface_property;
  properties[2] = d_material_property;
  properties[3] = d_density_property;
  properties[4] = d_estimator_property;
}

// Set the surface current name
void DagMCModelProperties::setSurfaceCurrentName( const std::string& name )
{
  // Make sure that the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );
  
  d_surface_current_name = name;
}

// Get the surface current name
const std::string& DagMCModelProperties::getSurfaceCurrentName()
{
  return d_surface_current_name;
}

// Set the surface flux name
void DagMCModelProperties::setSurfaceFluxName( const std::string& name )
{
  // Make sure that the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );

  d_surface_flux_name = name;
}

// Get the surface flux name
const std::string& DagMCModelProperties::getSurfaceFluxName()
{
  return d_surface_flux_name;
}

// Set the cell pulse height name
void DagMCModelProperties::setCellPulseHeightName( const std::string& name )
{
  // Make sure that the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );
  
  d_cell_pulse_height_name = name;
}

// Get the cell pulse height name
const std::string& DagMCModelProperties::getCellPulseHeightName()
{
  return d_cell_pulse_height_name;
}

// Set the cell track-length flux name
void DagMCModelProperties::setCellTrackLengthFluxName( const std::string& name )
{
  // Make sure that the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );
  
  d_cell_track_length_flux_name = name;
}

// Get the cell pulse height name
const std::string& DagMCModelProperties::getCellTrackLengthFluxName()
{
  return d_cell_track_length_flux_name;
}

// Set the cell collision flux name
void DagMCModelProperties::setCellCollisionFluxName( const std::string& name )
{
  // Make sure that the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );
  
  d_cell_collision_flux_name = name;
}

// Get the cell collision flux name
const std::string& DagMCModelProperties::getCellCollisionFluxName()
{
  return d_cell_collision_flux_name;
}

// Check if the cell estimator type is valid
bool DagMCModelProperties::isCellEstimatorTypeValid(
					    const std::string& estimator_type )
{
  return estimator_type.compare( d_cell_pulse_height_name )== 0 ||
    estimator_type.compare( d_cell_track_length_flux_name )== 0 ||
    estimator_type.compare( d_cell_collision_flux_name ) == 0;
}

// Check if the surface estimator type is valid
bool DagMCModelProperties::isSurfaceEstimatorTypeValid(
					    const std::string& estimator_type )
{
  return estimator_type.compare( d_surface_flux_name ) == 0 ||
    estimator_type.compare( d_surface_current_name ) == 0;
}

// Check if the estimator type is valid
bool DagMCModelProperties::isEstimatorTypeValid(
                                            const std::string& estimator_type )
{
  return this->isCellEstimatorTypeValid( estimator_type ) ||
    this->isSurfaceEstimatorTypeValid( estimator_type );
}

// Check if the particle type is valid
bool DagMCModelProperties::isParticleTypeValid(
                                             const std::string& particle_type )
{
  return particle_type.compare( "n" ) == 0 ||
    particle_type.compare( "p" ) == 0 ||
    particle_type.compare( "e" ) == 0;
}

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_DagMCModelProperties.cpp
//---------------------------------------------------------------------------//
