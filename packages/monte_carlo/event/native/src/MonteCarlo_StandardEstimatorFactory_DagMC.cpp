//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardEstimatorFactory_DagMC.cpp
//! \author Alex Robinson
//! \brief  The standard estimator factory class specialization for DagMC
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_StandardEstimatorFactory_DagMC.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

#ifdef HAVE_FRENSIE_DAGMC

namespace MonteCarlo{

// Constructor
/*! \details The DagMC geometry must be initialized before constructing this
 * factory. If DagMC is not enabled this constructor will do nothing.
 */ 
StandardEstimatorFactory<Geometry::DagMC>::StandardEstimatorFactory(
       const std::shared_ptr<EventHandler>& event_handler,
       const boost::unordered_map<unsigned,std::shared_ptr<ResponseFunction> >&
       response_function_id_map,
       std::ostream* os_warn )
  : EstimatorFactory( event_handler, response_function_id_map, os_warn )
{
  // Load the estimator id maps
  this->loadEstimatorIdMapsWithCellEstimatorProps();
  this->loadEstimatorIdMapsWithSurfaceEstimatorProps();

  // Load the cell volume map
  this->loadCellVolumeMap();

  // Load the surface area map
  this->loadSurfaceAreaMap();

  // Make sure the maps have the correct size
  testPostcondition( d_geom_estimator_id_type_map.size() ==
		     d_geom_estimator_id_ptype_map.size() );
  testPostcondition( d_geom_estimator_id_type_map.size() ==
		     d_geom_estimator_id_cells_map.size() + 
		     d_geom_estimator_id_surfaces_map.size() );
}

// Create and register cached estimators
void StandardEstimatorFactory<Geometry::DagMC>::createAndRegisterCachedEstimators()
{
  boost::unordered_map<unsigned,std::string>::iterator estimator_id_type =
    d_geom_estimator_id_type_map.begin();

  while( estimator_id_type != d_geom_estimator_id_type_map.end() )
  {
    // Get the estimator id
    unsigned estimator_id = estimator_id_type->first;
    
    // Get the estimator type
    const std::string& estimator_type = estimator_id_type->second;

    // Get the estimator particle type
    const std::string& particle_type_name = 
      d_geom_estimator_id_ptype_map.find( estimator_id )->second;

    Teuchos::Array<ParticleType> particle_types;

    this->convertParticleTypeNameToParticleTypes( particle_types,
                                                  estimator_id,
                                                  particle_type_name );

    // Use a default multiplier
    double multiplier = 1.0;

    // No response functions
    Teuchos::Array<std::shared_ptr<ResponseFunction> > response_functions;

    try{
      // Create and register a cell estimator
      if( this->isCellEstimator( estimator_type ) )
      {
        boost::unordered_set<Geometry::ModuleTraits::InternalCellHandle> 
          unique_cells;

        this->getCachedCells( unique_cells, estimator_id );

        Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> 
          assigned_cells( unique_cells.begin(), unique_cells.end() );

        TEST_FOR_EXCEPTION( assigned_cells.size() == 0,
                            InvalidEstimatorRepresentation,
                            "Error: cell estimator " << estimator_id << 
                            " has no cells assigned to it!" );

        this->createAndRegisterCellEstimator( estimator_type,
                                              estimator_id,
                                              multiplier,
                                              particle_types,
                                              response_functions,
                                              assigned_cells );
      }
              
      // Create and register a surface estimator
      else if( this->isSurfaceEstimator( estimator_type ) )
      {
        boost::unordered_set<Geometry::ModuleTraits::InternalSurfaceHandle>
          unique_surfaces;
        
        this->getCachedSurfaces( unique_surfaces, estimator_id );

        Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>
          assigned_surfaces( unique_surfaces.begin(), unique_surfaces.end() );

        TEST_FOR_EXCEPTION( assigned_surfaces.size() == 0,
                            InvalidEstimatorRepresentation,
                            "Error: surface estimator " << estimator_id << 
                            " has no surfaces assigned to it!" );

        this->createAndRegisterSurfaceEstimator( estimator_type,
                                                 estimator_id,
                                                 multiplier,
                                                 particle_types,
                                                 response_functions,
                                                 assigned_surfaces );
      }
      
      // Invalid estimator type
      else
      {
        THROW_EXCEPTION( InvalidEstimatorRepresentation,
                         "Error: estimator " << estimator_id << "has an "
                         "invalid type (" << estimator_type << ")!" );
      }
    } // end try
    EXCEPTION_CATCH_RETHROW_AS( std::exception,
                                InvalidEstimatorRepresentation,
                                "Error: could not create estimator "
                                << estimator_id << "!" );

    ++estimator_id_type;
  }

  // Clear all cached estimator data
  d_geom_estimator_id_type_map.clear();
  d_geom_estimator_id_ptype_map.clear();
  d_geom_estimator_id_cells_map.clear();
  d_geom_estimator_id_surfaces_map.clear();
}
                       
// Load estimator id maps with cell estimator properties
void StandardEstimatorFactory<Geometry::DagMC>::loadEstimatorIdMapsWithCellEstimatorProps()
{
  typedef std::unordered_map<unsigned,Utility::Trip<std::string,std::string,std::vector<Geometry::ModuleTraits::InternalCellHandle> > > EstimatorIdDataMap;
  EstimatorIdDataMap cell_estimator_id_data_map;

  try{
    Geometry::DagMC::getCellEstimatorData( cell_estimator_id_data_map );
  }
  EXCEPTION_CATCH_RETHROW_AS( Geometry::InvalidDagMCGeometry,
                              InvalidEstimatorRepresentation,
                              "Error: Unable to parse the cell estimator data "
                              "in DagMC!" );

  EstimatorIdDataMap::const_iterator cell_estimator_id_data_it = 
    cell_estimator_id_data_map.begin();

  // Loop through the cell estimators
  while( cell_estimator_id_data_it != cell_estimator_id_data_map.end() )
  {
    unsigned id = cell_estimator_id_data_it->first;
    
    // Make sure the id is valid
    TEST_FOR_EXCEPTION( id == 
                        ModuleTraits::invalid_internal_event_observer_handle,
                        InvalidEstimatorRepresentation,
                        "Error: estimator id " << id << " found in DagMC "
                        "is reserved!" );
    
    // The observer id must be unique
    TEST_FOR_EXCEPTION( d_geom_estimator_id_type_map.find( id ) !=
			d_geom_estimator_id_type_map.end(),
			InvalidEstimatorRepresentation,
			"Error: estimator id " << id << " is used multiple "
			"times in DagMC!" );

    // Store the estimator type
    std::string estimator_type = cell_estimator_id_data_it->second.first;

    d_geom_estimator_id_type_map[id] = 
      this->convertDagMCEstimatorTypeNameToStandard( estimator_type );

    // Store the particle type
    std::string particle_type = cell_estimator_id_data_it->second.second;

    TEST_FOR_EXCEPTION( estimator_type == 
                        EstimatorFactory::getCellPulseHeightEstimatorName() &&
			particle_type == "n",
			InvalidEstimatorRepresentation,
			"Error: pulse height estimator " << id << " has "
			"been assigned a particle type of neutron (only "
			"photons or electrons can be assigned)" );

    d_geom_estimator_id_ptype_map[id] = 
      convertShortParticleTypeNameToVerboseParticleTypeName( particle_type );

    // Store the cells assigned to the estimator
    const std::vector<Geometry::ModuleTraits::InternalCellHandle>& cells = 
      cell_estimator_id_data_it->second.third;
    
    TEST_FOR_EXCEPTION( cells.size() == 0,
			InvalidEstimatorRepresentation,
			"Error: estimator " << id << " has no cells "
			"specified!" );

    d_geom_estimator_id_cells_map[id].assign( cells.begin(), cells.end() );

    ++cell_estimator_id_data_it;
  }
}

// Load estimator id mpas with surface estimator properties
void StandardEstimatorFactory<Geometry::DagMC>::loadEstimatorIdMapsWithSurfaceEstimatorProps()
{
  typedef std::unordered_map<unsigned,Utility::Trip<std::string,std::string,std::vector<Geometry::ModuleTraits::InternalSurfaceHandle> > > EstimatorIdDataMap;
  EstimatorIdDataMap surface_estimator_id_data_map;

  try{
    Geometry::DagMC::getSurfaceEstimatorData( surface_estimator_id_data_map );
  }
  EXCEPTION_CATCH_RETHROW_AS( Geometry::InvalidDagMCGeometry,
                              InvalidEstimatorRepresentation,
                              "Error: Unable to parse the surface estimator "
                              "data in DagMC!" );

  EstimatorIdDataMap::const_iterator surface_estimator_id_data_it = 
    surface_estimator_id_data_map.begin();

  // Loop through the surface estimators
  while( surface_estimator_id_data_it != surface_estimator_id_data_map.end() )
  {
    unsigned id = surface_estimator_id_data_it->first;
      
    // Make sure the id is valid
    TEST_FOR_EXCEPTION( id == 
                        ModuleTraits::invalid_internal_event_observer_handle,
                        InvalidEstimatorRepresentation,
                        "Error: estimator id " << id << " found in DagMC "
                        "is reserved!" );
    
    // The estimator id must be unique
    TEST_FOR_EXCEPTION( d_geom_estimator_id_type_map.find( id ) !=
			d_geom_estimator_id_type_map.end(),
			InvalidEstimatorRepresentation,
			"Error: estimator id " << id << " is used multiple "
			"times in DagMC!" );
    
    // Store the estimator type 
    std::string estimator_type = surface_estimator_id_data_it->second.first;
    
    d_geom_estimator_id_type_map[id] = 
      this->convertDagMCEstimatorTypeNameToStandard( estimator_type );

    // Store the particle type requested
    std::string particle_type = surface_estimator_id_data_it->second.second;

    d_geom_estimator_id_ptype_map[id] = 
      convertShortParticleTypeNameToVerboseParticleTypeName( particle_type );
    
    // Store the surfaces assigned to the estimator
    const std::vector<Geometry::ModuleTraits::InternalSurfaceHandle>& 
      surfaces = surface_estimator_id_data_it->second.third;
    
    TEST_FOR_EXCEPTION( surfaces.size() == 0,
			InvalidEstimatorRepresentation,
			"Error: estimator " << id << " has no surfaces "
			"specified!" );

    d_geom_estimator_id_surfaces_map[id].assign( surfaces.begin(),
                                                 surfaces.end() );

    ++surface_estimator_id_data_it;
  }
}

// Load the cell volume map
void StandardEstimatorFactory<Geometry::DagMC>::loadCellVolumeMap()
{
  EstimatorIdCellsMap::const_iterator it = 
    d_geom_estimator_id_cells_map.begin();

  while( it != d_geom_estimator_id_cells_map.end() )
  {
    for( unsigned i = 0u; i < it->second.size(); ++i )
    {
      if( d_cell_volume_map.find( it->second[i] ) == d_cell_volume_map.end() )
      {
	d_cell_volume_map[it->second[i]] = 
	  Geometry::DagMC::getCellVolume( it->second[i] );
      }
    }

    ++it;
  }
}

// Load the surface area map
void StandardEstimatorFactory<Geometry::DagMC>::loadSurfaceAreaMap()
{
  EstimatorIdSurfacesMap::const_iterator it = 
    d_geom_estimator_id_surfaces_map.begin();

  while( it != d_geom_estimator_id_surfaces_map.end() )
  {
    for( unsigned i = 0u; i < it->second.size(); ++i )
    {
      if( d_surface_area_map.find( it->second[i] ) == d_surface_area_map.end() )
      {
	d_surface_area_map[it->second[i]] = 
	  Geometry::DagMC::getSurfaceArea( it->second[i] );
      }
    }
    
    ++it;
  }
}

// Convert a DagMC estimator type name to the standard estimator type name
std::string StandardEstimatorFactory<Geometry::DagMC>::convertDagMCEstimatorTypeNameToStandard(
                          const std::string& dagmc_estimator_type_name ) const
{
  // Make sure the estimator type is valid
  testPrecondition( Geometry::DagMC::isEstimatorTypeValid( dagmc_estimator_type_name ) );
  
  if( dagmc_estimator_type_name == 
      Geometry::DagMC::getSurfaceCurrentName() )
  {
    return EstimatorFactory::getSurfaceCurrentEstimatorName();
  }
  else if( dagmc_estimator_type_name ==
           Geometry::DagMC::getSurfaceFluxName() )
  {
    return EstimatorFactory::getSurfaceFluxEstimatorName();
  }
  else if( dagmc_estimator_type_name ==
           Geometry::DagMC::getCellPulseHeightName() )
  {
    return EstimatorFactory::getCellPulseHeightEstimatorName();
  }
  else if( dagmc_estimator_type_name ==
           Geometry::DagMC::getCellTrackLengthFluxName() )
  {
    return EstimatorFactory::getCellTrackLengthFluxEstimatorName();
  }
  else if( dagmc_estimator_type_name ==
           Geometry::DagMC::getCellCollisionFluxName() )
  {
    return EstimatorFactory::getCellCollisionFluxEstimatorName();
  }
  else
  {
    THROW_EXCEPTION( InvalidEstimatorRepresentation,
                     "Error: encountered an estimator in the .sat file with "
                     "an invalid type: "
                     << dagmc_estimator_type_name << "!" );
  }
}

// Verify that the estimator type is consistent with cached data
/*! \details This method will check that, if there data was found for the 
 * estimator in the .sat file, the estimator type requested in the xml file
 * is the same as the estimator type requested in the .sat file. An 
 * exception will be thrown if there is an ambiguity. 
 */
void StandardEstimatorFactory<Geometry::DagMC>::verifyEstimatorTypeConsistency( 
                                     const unsigned estimator_id,
                                     const std::string& estimator_type ) const
{
  // Check if there is any cached data for the estimator
  if( d_geom_estimator_id_type_map.find( estimator_id ) !=
      d_geom_estimator_id_type_map.end() )
  {
    TEST_FOR_EXCEPTION( 
                  d_geom_estimator_id_type_map.find(estimator_id)->second !=
                  estimator_type,
                  InvalidEstimatorRepresentation,
                  "Error: estimator " << estimator_id << " has an "
                  "ambiguous type. DagMC requested " 
                  << d_geom_estimator_id_type_map.find(estimator_id)->second <<
                  " while the xml file requested "
                  << estimator_type << "!" );
  }
}

// Get the estimator particle types - required
/*! \details Unlike the estimator type, the particle type only needs to be
 * specified in either the .sat file or the xml file. An exception is thrown
 * if it appears in neither or if it appears in both and they do not match.
 */
void StandardEstimatorFactory<Geometry::DagMC>::getEstimatorParticleType( 
                           Teuchos::Array<ParticleType>& particle_types,
                           const unsigned estimator_id,
                           const Teuchos::ParameterList& estimator_rep ) const
{
  if( d_geom_estimator_id_ptype_map.find( estimator_id ) != 
      d_geom_estimator_id_ptype_map.end() )
  {
    // Make sure the DagMC particle type and the param. list particle type ==
    if( estimator_rep.isParameter( "Particle Type" ) )
    {
      TEST_FOR_EXCEPTION( 
                  d_geom_estimator_id_ptype_map.find( estimator_id )->second !=
                  estimator_rep.get<std::string>( "Particle Type" ),
                  InvalidEstimatorRepresentation,
                  "Error: estimator " << estimator_id << 
                  " specified in the xml file and DagMC have inconsitent "
                  "particle types ("
                  << estimator_rep.get<std::string>("Particle Type") <<
                  " != " 
                  << d_geom_estimator_id_ptype_map.find( estimator_id )->second
                  << ")!" );
    }
    
    const std::string& particle_type_name = 
      d_geom_estimator_id_ptype_map.find( estimator_id )->second;

    this->convertParticleTypeNameToParticleTypes( particle_types,
                                                  estimator_id,
                                                  particle_type_name );
  }
  // Use the default method to extract the particle type
  else
  {
    EstimatorFactory::getEstimatorParticleType( particle_types,
                                                estimator_id,
                                                estimator_rep );
  }
}

// Verify the existence of cells
void StandardEstimatorFactory<Geometry::DagMC>::verifyExistenceOfCells(
        const boost::unordered_set<Geometry::ModuleTraits::InternalCellHandle>&
        cells,
        const unsigned estimator_id ) const
{
  boost::unordered_set<Geometry::ModuleTraits::InternalCellHandle>::const_iterator cell = cells.begin();

  while( cell != cells.end() )
  {
    TEST_FOR_EXCEPTION( !Geometry::DagMC::doesCellExist( *cell ),
                        InvalidEstimatorRepresentation,
                        "Error: estimator " << estimator_id << " specified "
                        "cell " << *cell << " in the xml "
                        "file, which does not exists!" );
    
    ++cell;
  }
}

// Get the cached cells (add to set)
void StandardEstimatorFactory<Geometry::DagMC>::getCachedCells( 
       boost::unordered_set<Geometry::ModuleTraits::InternalCellHandle>& cells,
       const unsigned estimator_id ) const
{
  if( d_geom_estimator_id_cells_map.find( estimator_id ) != 
      d_geom_estimator_id_cells_map.end() )
  {
    cells.insert( 
            d_geom_estimator_id_cells_map.find( estimator_id )->second.begin(),
            d_geom_estimator_id_cells_map.find( estimator_id )->second.end() );
  }
}

// Get the cell volumes
/*! \details Make sure the existence of the cells is confirmed before
 * calling this method.
 */ 
void StandardEstimatorFactory<Geometry::DagMC>::getCellVolumes( 
     Teuchos::Array<double>& cell_volumes,
     const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cells )
{
  // Resize the cell volume array
  cell_volumes.resize( cells.size() );

  // Get the volume of every cell
  for( unsigned i = 0; i < cells.size(); ++i )
  {
    // Check if the cell volume has already been cached
    if( d_cell_volume_map.find( cells[i] ) != d_cell_volume_map.end() )
      cell_volumes[i] = d_cell_volume_map.find( cells[i] )->second;
    
    // Calculate and cache the cell volume if the cell is new
    else
    {
      cell_volumes[i] = Geometry::DagMC::getCellVolume( cells[i] );

      d_cell_volume_map[cells[i]] = cell_volumes[i];
    }
  }
}

// Verify the existence of surfaces
void StandardEstimatorFactory<Geometry::DagMC>::verifyExistenceOfSurfaces(
     const boost::unordered_set<Geometry::ModuleTraits::InternalSurfaceHandle>&
     surfaces,
     const unsigned estimator_id ) const
{
  boost::unordered_set<Geometry::ModuleTraits::InternalSurfaceHandle>::const_iterator surface = surfaces.begin();

  while( surface != surfaces.end() )
  {
    TEST_FOR_EXCEPTION( !Geometry::DagMC::doesSurfaceExist( *surface ),
                        InvalidEstimatorRepresentation,
                        "Error: estimator " << estimator_id << " specified "
                        "surface " << *surface << " in the xml "
                        "file, which does not exists!" );
    
    ++surface;
  }
}

// Get the cached surfaces (add to set)
void StandardEstimatorFactory<Geometry::DagMC>::getCachedSurfaces(
     boost::unordered_set<Geometry::ModuleTraits::InternalSurfaceHandle>&
     surfaces,
     const unsigned estimator_id ) const
{
  if( d_geom_estimator_id_surfaces_map.find( estimator_id ) != 
      d_geom_estimator_id_surfaces_map.end() )
  {
    surfaces.insert( 
         d_geom_estimator_id_surfaces_map.find( estimator_id )->second.begin(),
         d_geom_estimator_id_surfaces_map.find( estimator_id )->second.end() );
  }
}

// Get the surface areas
/*! \details Make sure the existence of the surfaces is confirmed before
 * calling this method.
 */
void StandardEstimatorFactory<Geometry::DagMC>::getSurfaceAreas( 
           Teuchos::Array<double>& surface_areas,
           const Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>&
           surfaces )
{
  // Resize the surface areas array
  surface_areas.resize( surfaces.size() );

  // Get the area of every surface
  for( unsigned i = 0; i < surfaces.size(); ++i )
  {
    // Check if the surface area has already been cached
    if( d_surface_area_map.find( surfaces[i] ) != d_surface_area_map.end() )
      surface_areas[i] = d_surface_area_map.find( surfaces[i] )->second;

    // Calculate and cache the surface area if the surface is new
    else
    {
      surface_areas[i] = Geometry::DagMC::getSurfaceArea( surfaces[i] );
      
      d_surface_area_map[surfaces[i]] = surface_areas[i];
    }
  }
}

// Update the estimator cache info
/*! \details This function should be called after an estimator has been
 * successfully created by the factory. All of the cached info for this
 * estimator will be deleted.
 */
void StandardEstimatorFactory<Geometry::DagMC>::updateEstimatorCacheInfo( 
                                                            const unsigned id )
{
  if( d_geom_estimator_id_type_map.find( id ) !=
      d_geom_estimator_id_type_map.end() )
  {
    d_geom_estimator_id_type_map.erase( 
                                     d_geom_estimator_id_type_map.find( id ) );
  }

  if( d_geom_estimator_id_ptype_map.find( id ) !=
      d_geom_estimator_id_ptype_map.end() )
  {
    d_geom_estimator_id_ptype_map.erase(
                                    d_geom_estimator_id_ptype_map.find( id ) );
  }

  if( d_geom_estimator_id_cells_map.find( id ) !=
      d_geom_estimator_id_cells_map.end() )
  {
    d_geom_estimator_id_cells_map.erase(
                                    d_geom_estimator_id_cells_map.find( id ) );
  }

  if( d_geom_estimator_id_surfaces_map.find( id ) !=
      d_geom_estimator_id_surfaces_map.end() )
  {
    d_geom_estimator_id_surfaces_map.erase(
                                 d_geom_estimator_id_surfaces_map.find( id ) );
  }
}

} // end MonteCarlo namespace

#endif // end HAVE_FRENSIE_DAGMC

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardEstimatorFactory_DagMC.cpp
//---------------------------------------------------------------------------//
