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
  : d_file_name( filename ),
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
    d_cell_collision_flux_name( "cell.c.flux" ),
    d_photon_name( "p" ),
    d_neutron_name( "n" ),
    d_electron_name( "e" ),
    d_adjoint_photon_name( "p*" ),
    d_adjoint_neutron_name( "n*" ),
    d_adjoint_electron_name( "e*" )
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

  d_facet_tolerance = facet_tol;
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
const std::string& DagMCModelProperties::getTerminationCellPropertyName() const
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

// Set the material property name
void DagMCModelProperties::setMaterialPropertyName( const std::string& name )
{
  // Make sure that the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );

  d_material_property = name;
}

// Get the material property name
const std::string& DagMCModelProperties::getMaterialPropertyName() const
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
const std::string& DagMCModelProperties::getDensityPropertyName() const
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
const std::string& DagMCModelProperties::getEstimatorPropertyName() const
{
  return d_estimator_property;
}

// Get all of the properties
void DagMCModelProperties::getPropertyNames( std::vector<std::string>& properties ) const
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
const std::string& DagMCModelProperties::getSurfaceCurrentName() const
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
const std::string& DagMCModelProperties::getSurfaceFluxName() const
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
const std::string& DagMCModelProperties::getCellPulseHeightName() const
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
const std::string& DagMCModelProperties::getCellTrackLengthFluxName() const
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
const std::string& DagMCModelProperties::getCellCollisionFluxName() const
{
  return d_cell_collision_flux_name;
}

// Check if the cell estimator name is valid
bool DagMCModelProperties::isCellEstimatorNameValid(
                                      const std::string& estimator_name ) const
{
  return estimator_name == d_cell_pulse_height_name ||
    estimator_name == d_cell_track_length_flux_name ||
    estimator_name == d_cell_collision_flux_name;
}

// Check if the surface estimator name is valid
bool DagMCModelProperties::isSurfaceEstimatorNameValid(
                                      const std::string& estimator_name ) const
{
  return estimator_name == d_surface_flux_name ||
    estimator_name == d_surface_current_name;
}

// Check if the estimator name is valid
bool DagMCModelProperties::isEstimatorNameValid(
                                      const std::string& estimator_name ) const
{
  return this->isCellEstimatorNameValid( estimator_name ) ||
    this->isSurfaceEstimatorNameValid( estimator_name );
}

// Get the estimator type
DagMCEstimatorType DagMCModelProperties::getEstimatorType(
                                      const std::string& estimator_name ) const
{
  // Make sure that the estimator name is valid
  testPrecondition( this->isEstimatorNameValid( estimator_name ) );

  if( estimator_name == d_surface_current_name )
    return DAGMC_SURFACE_CURRENT_ESTIMATOR;
  else if( estimator_name == d_surface_flux_name )
    return DAGMC_SURFACE_FLUX_ESTIMATOR;
  else if( estimator_name == d_cell_pulse_height_name )
    return DAGMC_CELL_PULSE_HEIGHT_ESTIMATOR;
  else if( estimator_name == d_cell_track_length_flux_name )
    return DAGMC_CELL_TRACK_LENGTH_FLUX_ESTIMATOR;
  else if( estimator_name == d_cell_collision_flux_name )
    return DAGMC_CELL_COLLISION_FLUX_ESTIMATOR;
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Estimator name " << estimator_name << " is not "
                     "supported!" );
  }
}

// Set the photon name
void DagMCModelProperties::setPhotonName( const std::string& name )
{
  // Make sure that the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );
  testPrecondition( name.find( "." ) >= name.size() );

  d_photon_name = name;
}

// Get the photon name
const std::string& DagMCModelProperties::getPhotonName() const
{
  return d_photon_name;
}

// Set the neutron name
void DagMCModelProperties::setNeutronName( const std::string& name )
{
  // Make sure that the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );
  testPrecondition( name.find( "." ) >= name.size() );

  d_neutron_name = name;
}

// Get the neutron name
const std::string& DagMCModelProperties::getNeutronName() const
{
  return d_neutron_name;
}

// Set the electron name
void DagMCModelProperties::setElectronName( const std::string& name )
{
  // Make sure that the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );
  testPrecondition( name.find( "." ) >= name.size() );

  d_electron_name = name;
}

// Get the electron name
const std::string& DagMCModelProperties::getElectronName() const
{
  return d_electron_name;
}

// Set the adjoint photon name
void DagMCModelProperties::setAdjointPhotonName( const std::string& name )
{
  // Make sure that the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );
  testPrecondition( name.find( "." ) >= name.size() );

  d_adjoint_photon_name = name;
}

// Get the adjoint photon name
const std::string& DagMCModelProperties::getAdjointPhotonName() const
{
  return d_adjoint_photon_name;
}

// Set the adjoint neutron name
void DagMCModelProperties::setAdjointNeutronName( const std::string& name )
{
  // Make sure that the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );
  testPrecondition( name.find( "." ) >= name.size() );

  d_adjoint_neutron_name = name;
}

// Get the adjoint neutron name
const std::string& DagMCModelProperties::getAdjointNeutronName() const
{
  return d_adjoint_neutron_name;
}

// Set the adjoint electron name
void DagMCModelProperties::setAdjointElectronName( const std::string& name )
{
  // Make sure that the name is valid
  testPrecondition( name.find( "_" ) >= name.size() );
  testPrecondition( name.find( "." ) >= name.size() );

  d_adjoint_electron_name = name;
}
  
// Get the adjoint electron name
const std::string& DagMCModelProperties::getAdjointElectronName() const
{
  return d_adjoint_electron_name;
}

// Check if the particle name is valid
bool DagMCModelProperties::isParticleNameValid(
                                       const std::string& particle_name ) const
{
  return particle_name == d_photon_name ||
    particle_name == d_neutron_name ||
    particle_name == d_electron_name ||
    particle_name == d_adjoint_photon_name ||
    particle_name == d_adjoint_neutron_name ||
    particle_name == d_adjoint_electron_name;
}

// Get the partile type
DagMCParticleType DagMCModelProperties::getParticleType(
                                       const std::string& particle_name ) const
{
  // Make sure the particle name is valid
  testPrecondition( this->isParticleNameValid( particle_name ) );

  if( particle_name == d_photon_name )
    return DAGMC_PHOTON;
  else if( particle_name == d_neutron_name )
    return DAGMC_NEUTRON;
  else if( particle_name == d_electron_name )
    return DAGMC_ELECTRON;
  else if( particle_name == d_adjoint_photon_name )
    return DAGMC_ADJOINT_PHOTON;
  else if( particle_name == d_adjoint_neutron_name )
    return DAGMC_ADJOINT_NEUTRON;
  else if( particle_name == d_adjoint_electron_name )
    return DAGMC_ADJOINT_ELECTRON;
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Particle name " << particle_name << " is not "
                     "supported!" );
  }
}

} // end Geometry namespace

//---------------------------------------------------------------------------//
// end Geometry_DagMCModelProperties.cpp
//---------------------------------------------------------------------------//
