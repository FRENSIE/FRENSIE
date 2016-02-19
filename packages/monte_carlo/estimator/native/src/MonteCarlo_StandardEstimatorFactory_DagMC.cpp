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
#include "FRENSIE_dagmc_config.hpp"

#ifdef HAVE_FRENSIE_DAGMC
#include "Geometry_DagMCProperties.hpp"
#include "Geometry_ModuleInterface.hpp"
#include "Geometry_ModuleInterface_DagMC.hpp"
#endif

namespace MonteCarlo{

// Constructor
/*! \details The DagMC geometry must be initialized before constructing this
 * factory. If DagMC is not enabled this constructor will do nothing.
 */ 
StandardEstimatorFactory<moab::DagMC>::StandardEstimatorFactory(
          const std::shared_ptr<EventHandler>& event_handler,
          const boost::unordered_map<unsigned,Teuchos::RCP<ResponseFunction> >&
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
void StandardEstimatorFactory<moab::DagMC>::createAndRegisterCachedEstimators()
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
    Teuchos::Array<Teuchos::RCP<ResponseFunction> > response_functions;

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
void StandardEstimatorFactory<moab::DagMC>::loadEstimatorIdMapsWithCellEstimatorProps()
{
  #ifdef HAVE_FRENSIE_DAGMC
  typedef boost::unordered_map<std::string,
                      std::vector<Geometry::ModuleTraits::InternalCellHandle> >
    EstimatorPropCellIdMap;

  EstimatorPropCellIdMap estimator_prop_cell_id_map;

  Geometry::getCellIdsWithPropertyValue(
			 Geometry::DagMCProperties::getEstimatorPropertyName(),
			 estimator_prop_cell_id_map );

  EstimatorPropCellIdMap::const_iterator cell_it = 
    estimator_prop_cell_id_map.begin();

  // Loop through the cell estimators
  while( cell_it != estimator_prop_cell_id_map.end() )
  {
    unsigned id;
    std::string estimator_type;
    std::string particle_type;
    
    try{
      Geometry::DagMCProperties::extractEstimatorPropertyValues(
                                                               cell_it->first,
                                                               id,
                                                               estimator_type,
                                                               particle_type );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::exception,
                                InvalidEstimatorRepresentation,
                                "Error: an invalid estimator specification "
                                "was found in the .sat file ("
                                << cell_it->first << ")!" );

    // Make sure the id is valid
    TEST_FOR_EXCEPTION( id == 
                        ModuleTraits::invalid_internal_event_observer_handle,
                        InvalidEstimatorRepresentation,
                        "Error: estimator id " << id << " found in the "
                        ".sat file is reserved!" );
    
    // The observer id must be unique
    TEST_FOR_EXCEPTION( d_geom_estimator_id_type_map.find( id ) !=
			d_geom_estimator_id_type_map.end(),
			InvalidEstimatorRepresentation,
			"Error: estimator id " << id << " is used multiple "
			"times in the .sat file!" );

    // Store the estimator type requested
    TEST_FOR_EXCEPTION( 
        !Geometry::DagMCProperties::isCellEstimatorTypeValid( estimator_type ),
	InvalidEstimatorRepresentation,
	"Error: cell estimator " << id << " has estimator type " 
	<< estimator_type << " specified in the .sat file, which is "
	"invalid!" );

    d_geom_estimator_id_type_map[id] = 
      this->convertDagMCEstimatorTypeNameToStandard( estimator_type );

    // Store the particle type requested
    TEST_FOR_EXCEPTION(
	     !Geometry::DagMCProperties::isParticleTypeValid( particle_type ),
	     InvalidEstimatorRepresentation,
	     "Error: estimator " << id << " has particle type " 
	     << particle_type << " specified in the .sat file, which is "
	     "not valid (choose n, p or e)!" );
    
    TEST_FOR_EXCEPTION( estimator_type == "cell.pulse.height" &&
			particle_type == "n",
			InvalidEstimatorRepresentation,
			"Error: pulse height estimator " << id << " has "
			"been assigned a particle type of neutron (only "
			"photons or electrons can be assigned)" );
			

    d_geom_estimator_id_ptype_map[id] = 
      convertShortParticleTypeNameToVerboseParticleTypeName( particle_type );

    // Store the cells assigned to the estimator
    TEST_FOR_EXCEPTION( cell_it->second.size() == 0,
			InvalidEstimatorRepresentation,
			"Error: estimator " << id << " has no cells "
			"specified!" );

    d_geom_estimator_id_cells_map[id].assign( cell_it->second.begin(),
                                              cell_it->second.end() );

    ++cell_it;
  }
#endif // end HAVE_FRENSIE_DAGMC
}

// Load estimator id mpas with surface estimator properties
void StandardEstimatorFactory<moab::DagMC>::loadEstimatorIdMapsWithSurfaceEstimatorProps()
{
#ifdef HAVE_FRENSIE_DAGMC
  // Load the estimator info from the DagMC geometry
  typedef boost::unordered_map<std::string,
                   std::vector<Geometry::ModuleTraits::InternalSurfaceHandle> >
    EstimatorPropSurfaceIdMap;

  EstimatorPropSurfaceIdMap estimator_prop_surface_id_map;
  
  Geometry::getSurfaceIdsWithPropertyValue(
			 Geometry::DagMCProperties::getEstimatorPropertyName(),
			 estimator_prop_surface_id_map );

  EstimatorPropSurfaceIdMap::const_iterator surface_it = 
    estimator_prop_surface_id_map.begin();

  // Loop through the surface estimators
  while( surface_it != estimator_prop_surface_id_map.end() )
  {
    unsigned id;
    std::string estimator_type;
    std::string particle_type;
    
    Geometry::DagMCProperties::extractEstimatorPropertyValues(
							     surface_it->first,
							     id,
							     estimator_type,
							     particle_type );
    // The estimator id must be unique
    TEST_FOR_EXCEPTION( d_geom_estimator_id_type_map.find( id ) !=
			d_geom_estimator_id_type_map.end(),
			InvalidEstimatorRepresentation,
			"Error: estimator id " << id << " is used multiple "
			"times in the .sat file!" );
    
    // Store the estimator type requested
    TEST_FOR_EXCEPTION( 
       !Geometry::DagMCProperties::isSurfaceEstimatorTypeValid(estimator_type),
       InvalidEstimatorRepresentation,
       "Error: surface estimator " << id << " has estimator type " 
       << estimator_type << " specified in the .sat file, which is "
       "invalid!" );

    d_geom_estimator_id_type_map[id] = 
      this->convertDagMCEstimatorTypeNameToStandard( estimator_type );

    // Store the particle type requested
    TEST_FOR_EXCEPTION(
	     !Geometry::DagMCProperties::isParticleTypeValid( particle_type ),
	     InvalidEstimatorRepresentation,
	     "Error: estimator " << id << " has particle type " 
	     << particle_type << " specified in the .sat file, which is "
	     "not valid (choose n, p or e)!" );

    d_geom_estimator_id_ptype_map[id] = 
      convertShortParticleTypeNameToVerboseParticleTypeName( particle_type );
    
    // Store the cells assigned to the estimator
    TEST_FOR_EXCEPTION( surface_it->second.size() == 0,
			InvalidEstimatorRepresentation,
			"Error: estimator " << id << " has no cells "
			"specified!" );

    d_geom_estimator_id_surfaces_map[id].assign( surface_it->second.begin(),
                                                 surface_it->second.end() );

    ++surface_it;
  }
#endif // end HAVE_FRENSIE_DAGMC
}

// Load the cell volume map
void StandardEstimatorFactory<moab::DagMC>::loadCellVolumeMap()
{
#ifdef HAVE_FRENSIE_DAGMC
  EstimatorIdCellsMap::const_iterator it = 
    d_geom_estimator_id_cells_map.begin();

  while( it != d_geom_estimator_id_cells_map.end() )
  {
    for( unsigned i = 0u; i < it->second.size(); ++i )
    {
      if( d_cell_volume_map.find( it->second[i] ) == d_cell_volume_map.end() )
      {
	d_cell_volume_map[it->second[i]] = 
	  Geometry::ModuleInterface<moab::DagMC>::getCellVolume(it->second[i]);
      }
    }

    ++it;
  }
#endif // end HAVE_FRENSIE_DAGMC
}

// Load the surface area map
void StandardEstimatorFactory<moab::DagMC>::loadSurfaceAreaMap()
{
#ifdef HAVE_FRENSIE_DAGMC
  EstimatorIdSurfacesMap::const_iterator it = 
    d_geom_estimator_id_surfaces_map.begin();

  while( it != d_geom_estimator_id_surfaces_map.end() )
  {
    for( unsigned i = 0u; i < it->second.size(); ++i )
    {
      if( d_surface_area_map.find( it->second[i] ) == d_surface_area_map.end() )
      {
	d_surface_area_map[it->second[i]] = 
	  Geometry::ModuleInterface<moab::DagMC>::getCellSurfaceArea(
								 it->second[i],
								 0 );
      }
    }
    
    ++it;
  }
#endif // end HAVE_FRENSIE_DAGMC
}

// Convert a DagMC estimator type name to the standard estimator type name
std::string StandardEstimatorFactory<moab::DagMC>::convertDagMCEstimatorTypeNameToStandard(
                          const std::string& dagmc_estimator_type_name ) const
{
#ifdef HAVE_FRENSIE_DAGMC
  // Make sure the estimator type is valid
  testPrecondition( Geometry::DagMCProperties::isEstimatorTypeValid( dagmc_estimator_type_name ) );
  
  if( dagmc_estimator_type_name == 
      Geometry::DagMCProperties::getSurfaceCurrentName() )
  {
    return EstimatorFactory::getSurfaceCurrentEstimatorName();
  }
  else if( dagmc_estimator_type_name ==
           Geometry::DagMCProperties::getSurfaceFluxName() )
  {
    return EstimatorFactory::getSurfaceFluxEstimatorName();
  }
  else if( dagmc_estimator_type_name ==
           Geometry::DagMCProperties::getCellPulseHeightName() )
  {
    return EstimatorFactory::getCellPulseHeightEstimatorName();
  }
  else if( dagmc_estimator_type_name ==
           Geometry::DagMCProperties::getCellTrackLengthFluxName() )
  {
    return EstimatorFactory::getCellTrackLengthFluxEstimatorName();
  }
  else if( dagmc_estimator_type_name ==
           Geometry::DagMCProperties::getCellCollisionFluxName() )
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
#endif // end HAVE_FRENSIE_DAGMC
}

// Verify that the estimator type is consistent with cached data
/*! \details This method will check that, if there data was found for the 
 * estimator in the .sat file, the estimator type requested in the xml file
 * is the same as the estimator type requested in the .sat file. An 
 * exception will be thrown if there is an ambiguity. 
 */
void StandardEstimatorFactory<moab::DagMC>::verifyEstimatorTypeConsistency( 
                                     const unsigned estimator_id,
                                     const std::string& estimator_type ) const
{
  // Check if there is any cached data for the estimator
  if( d_geom_estimator_id_type_map.find( estimator_id ) !=
      d_geom_estimator_id_type_map.end() )
  {
    TEST_FOR_EXCEPTION( d_geom_estimator_id_type_map.find(estimator_id)->second
                        != estimator_type,
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
void StandardEstimatorFactory<moab::DagMC>::getEstimatorParticleType( 
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
                  " specified in the xml file and the .sat file have "
                  "inconsitent particle types ("
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
void StandardEstimatorFactory<moab::DagMC>::verifyExistenceOfCells(
        const boost::unordered_set<Geometry::ModuleTraits::InternalCellHandle>&
        cells,
        const unsigned estimator_id ) const
{
#ifdef HAVE_FRENSIE_DAGMC
  boost::unordered_set<Geometry::ModuleTraits::InternalCellHandle>::const_iterator cell = cells.begin();

  while( cell != cells.end() )
  {
    TEST_FOR_EXCEPTION( 
          !Geometry::ModuleInterface<moab::DagMC>::doesCellExist( *cell ),
          InvalidEstimatorRepresentation,
          "Error: estimator " << estimator_id << " specified "
          "cell " << *cell << " in the xml "
          "file, which does not exists!" );
    
    ++cell;
  }
#endif // end HAVE_FRENSIE_DAGMC
}

// Get the cached cells (add to set)
void StandardEstimatorFactory<moab::DagMC>::getCachedCells( 
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
void StandardEstimatorFactory<moab::DagMC>::getCellVolumes( 
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
      cell_volumes[i] = 
        Geometry::ModuleInterface<moab::DagMC>::getCellVolume( cells[i] );

      d_cell_volume_map[cells[i]] = cell_volumes[i];
    }
  }
}

// Verify the existence of surfaces
void StandardEstimatorFactory<moab::DagMC>::verifyExistenceOfSurfaces(
     const boost::unordered_set<Geometry::ModuleTraits::InternalSurfaceHandle>&
     surfaces,
     const unsigned estimator_id ) const
{
  boost::unordered_set<Geometry::ModuleTraits::InternalSurfaceHandle>::const_iterator surface = surfaces.begin();

  while( surface != surfaces.end() )
  {
    TEST_FOR_EXCEPTION( 
          !Geometry::ModuleInterface<moab::DagMC>::doesSurfaceExist(*surface),
          InvalidEstimatorRepresentation,
          "Error: estimator " << estimator_id << " specified "
          "surface " << *surface << " in the xml "
          "file, which does not exists!" );
    
    ++surface;
  }
}

// Get the cached surfaces (add to set)
void StandardEstimatorFactory<moab::DagMC>::getCachedSurfaces(
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
void StandardEstimatorFactory<moab::DagMC>::getSurfaceAreas( 
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
      surface_areas[i] = 
        Geometry::ModuleInterface<moab::DagMC>::getCellSurfaceArea(
                                                              surfaces[i], 0 );
      d_surface_area_map[surfaces[i]] = surface_areas[i];
    }
  }
}

// Update the estimator cache info
/*! \details This function should be called after an estimator has been
 * successfully created by the factory. All of the cached info for this
 * estimator will be deleted.
 */
void StandardEstimatorFactory<moab::DagMC>::updateEstimatorCacheInfo( 
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

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardEstimatorFactory_DagMC.cpp
//---------------------------------------------------------------------------//
