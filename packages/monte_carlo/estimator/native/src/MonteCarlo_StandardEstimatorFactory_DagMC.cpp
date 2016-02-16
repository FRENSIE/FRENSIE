//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardEstimatorFactory_DagMC.cpp
//! \author Alex Robinson
//! \brief  The standard estimator factory class specialization for DagMC
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_StandardEstimatorFactory_DagMC.hpp"
#include "MonteCarlo_CellPulseHeightEstimator.hpp"
#include "MonteCarlo_CellTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_CellCollisionFluxEstimator.hpp"
#include "MonteCarlo_SurfaceFluxEstimator.hpp"
#include "MonteCarlo_SurfaceCurrentEstimator.hpp"
#include "MonteCarlo_TetMeshTrackLengthFluxEstimator.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

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
  : EstimatoryFactory( event_handler, response_function_id_map, os_warn ),
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

// Create and register all estimators
void createAndRegisterEstimator( 
                            const std::shared_ptr<EventHandler>& event_handler,
                            const Teuchos::ParameterList& estimator_rep ) const
{
  // Make sure the parameter list describes an estimator
  testPrecondition( this->isEstimatorRep( estimator_rep ) );
  
  // Get the estimator id - required
  TEST_FOR_EXCEPTION( !estimator_rep.isParameter( "Id" ),
                      InvalidEstimatorRepresentation,
                      "Error: the estimator id was not specified in estimator "
                      << estimator_rep.name() << "!" );
  
  unsigned id = estimator_rep.get<unsigned>( "Id" );
  
  // Get the estimator type - required
  std::string estimator_type; 

  if( d_estimator_id_type_map.find( id ) != d_estimator_id_type_map.end() )
  {
    // Make sure the DagMC type and the parameter list type match
    if( estimator_rep.isParameter( "Type" ) )
    {
      TEST_FOR_EXCEPTION( d_estimator_id_type_map.find( id )->second != 
                          estimator_rep.get<std::string>( "Type" ),
                          InvalidEstimatorRepresentation,
                          "Error: estimator " << id << " specified in the "
                          "xml file and the .sat file have inconsistent "
                          "types (" 
                          << estimator_rep.get<std::string>( "Type" ) << " != "
                          << estimator_id_type_map[id] << ")!" );
    }

    estimator_type = d_estimator_id_type_map.find( id )->second;
  }
  else if( estimator_rep.isParameter( "Type" ) )
    estimator_type = estimator_rep.get<std::string>( "Type" );
  else
  {
    THROW_EXCEPTION( InvalidEstimatorRepresentation,
                     "Error: estimator " << id << " does not have a "
                     "type specified!" );
  }

  // Get the estimator particle type - required
  std::string estimator_particle_type;
  
  if( d_estimator_id_ptype_map.find( id ) != d_estimator_id_ptype_map.end() )
  {
    // Make sure the DagMC particle type and the param. list particle type ==
    if( estimator_rep.isParameter( "Particle Type" ) )
    {
      TEST_FOR_EXCEPTION( d_estimator_id_ptype_map[id] !=
                          estimator_rep.get<std::string>( "Particle Type" ),
                          InvalidEstimatorRepresentation,
                          "Error: estimator " << id << " specified in the "
                          "xml file and the .sat file have inconsitent "
                          "particle types ("
                          << estimator_rep.get<std::string>("Particle Type")
                          << " != " << d_estimator_id_ptype_map[id] <<
                          ")!" );
    }
    
    estimator_particle_type = d_estimator_id_ptype_map.find( id )->second;
  }
  else if( estimator_rep.isParameter( "Particle Type" ) )
    estimator_particle_type = estimator_rep.get<std::string>("Particle Type");
  else
  {
    THROW_EXCEPTION( InvalidEstimatorRepresentation,
                     "Error: estimator " << id << " does not have a "
                     "particle type specified!" );
  }

  // Make sure the particle type name is valid
  TEST_FOR_EXCEPTION( !isValidParticleTypeName( estimator_particle_type ),
                      InvalidEstimatorRepresentation,
                      "Error: estimator " << id << " specified particle "
                      "type " << particle_type << " which is not valid!" );

  Teuchos::Array<ParticleType> particle_types( 1 );
  particle_types[0] = 
    convertParticleTypeNameToParticleTypeEnum( estimator_particle_type );

  // Get the estimator multiplier - optional
  double multiplier = 1.0;

  if( estimator_rep.isParameter( "Multiplier" ) )
    multiplier = estimator_rep.get<double>( "Multiplier" );

  TEST_FOR_EXCEPTION( multiplier <= 0.0,
                      InvalidEstimatorRepresentation,
                      "Error: estimator " << id << " has a negative "
                      "multiplier specified!" );
  
  // Check if energy multiplication was requested - optional
  bool energy_mult = false;

  if( estimator_rep.isParameter( "Energy Multiplication" ) )
    energy_mult = estimator_rep.get<bool>( "Energy Multiplication" ); 

  // Get the estimator bins - optional
  const Teuchos::ParameterList* estimator_bins = NULL;

  if( estimator_rep.isParameter( "Bins" ) )
    estimator_bins = &estimator_rep.get<Teuchos::ParameterList>( "Bins" );

  // Get the response functions assigned to the estimator - optional
  Teuchos::Array<Teuchos::RCP<ResponseFunction> > response_functions;

  if( estimator_rep.isParameter( "Response Functions" ) )
  {
    const Utility::ArrayString& array_string = 
      estimator_rep.get<Utility::ArrayString>( "Response Functions" );

    Teuchos::Array<unsigned> requested_response_functions;

    try{
      requested_response_functions = 
        array_string.getConcreteArray<unsigned>();
    }
    EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
                                InvalidEstimatorRepresentation,
                                "Error: the response functions requested for"
                                " estimator " << id << " are not valid!" );

    response_functions.resize( requested_response_functions.size() );

    for( unsigned i = 0; i < requested_response_functions.size(); ++i )
    {
      TEST_FOR_EXCEPTION( this->getResponseFunctionIdMap().find( requested_response_functions[i] ) ==
                          this->getResponseFunctionIdMap().end(),
                          InvalidEstimatorRepresentation,
                          "Error: estimator " << id << " has requested "
                          "response function " << 
                          requested_response_functions[i] << 
                          " which does not exist!" );

      response_functions[i] = this->getResponseFunctionIdMap().find( 
                                     requested_response_functions[i] )->second;
    }
  }

  // Create the cell pulse height estimator
  if( this->isCellPulseHeightEstimator( estimator_type ) )
  {
    // Get the cells assigned to the estimator
    Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> assigned_cells;

    // Filter out multiple occurances of the same cell
    {
      boost::unordered_set<Geometry::ModuleTraits::InternalCellHandle>
        unique_cells;

      if( d_estimator_id_cells_map.find( id ) != d_estimator_id_cells_map.end() )
      {
        unique_cells.insert( 
                           d_estimator_id_cells_map.find( id )->second.begin(),
                           d_estimator_id_cells_map.find( id )->second.end() );
      }
      
      if( estimator_rep.isParameter( "Cells" ) )
      {
        const Utility::ArrayString& array_string = 
          estimator_rep.get<Utility::ArrayString>( "Cells" );

        Teuchos::Array<unsigned> xml_cells;

        try{
          xml_cells = array_string.getConcreteArray<unsigned>();
        }
        EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
                                    InvalidEstimatorRepresentation,
                                    "Error: the cells requested for "
                                    "estimator " << id << 
                                    " are not valid!" );

        for( unsigned i = 0u; i < xml_cells.size(); ++i )
        {
          TEST_FOR_EXCEPTION( 
            !Geometry::ModuleInterface<moab::DagMC>::doesCellExist( xml_cells[i] ),
            InvalidEstimatorRepresentation,
            "Error: estimator " << id << " specified "
            "cell " << xml_cells[i] << " in the xml "
            "file, which does not exists!" );

          unique_cells.insert( xml_cells[i] );
        }
      }

      assigned_cells.assign( unique_cells.begin(), unique_cells.end() );
    }
    
    if( 
    std::shared_ptr<CellPulseHeightEstimator
  }
}

// Create and register cached estimators
void StandardEstimatorFactory<moab::DagMC>::createAndRegisterCachedEstimators()
{

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
    
    Geometry::DagMCProperties::extractEstimatorPropertyValues( cell_it->first,
							       id,
							       estimator_type,
							       particle_type );
    
    // The observer id must be unique
    TEST_FOR_EXCEPTION( d_estimator_id_type_map.find( id ) !=
			d_estimator_id_type_map.end(),
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

    d_estimator_id_type_map[id] = 
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
			

    d_estimator_id_ptype_map[id] = 
      convertShortParticleTypeNameToVerboseParticleTypeName( particle_type );

    // Store the cells assigned to the estimator
    TEST_FOR_EXCEPTION( cell_it->second.size() == 0,
			InvalidEstimatorRepresentation,
			"Error: estimator " << id << " has no cells "
			"specified!" );

    d_estimator_id_cells_map[id].assign( cell_it->second.begin(),
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
    TEST_FOR_EXCEPTION( estimator_id_type_map.find( id ) !=
			estimator_id_type_map.end(),
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

    d_estimator_id_type_map[id] = 
      this->convertDagMCEstimatorTypeNameToStandard( estimator_type );

    // Store the particle type requested
    TEST_FOR_EXCEPTION(
	     !Geometry::DagMCProperties::isParticleTypeValid( particle_type ),
	     InvalidEstimatorRepresentation,
	     "Error: estimator " << id << " has particle type " 
	     << particle_type << " specified in the .sat file, which is "
	     "not valid (choose n, p or e)!" );

    d_estimator_id_ptype_map[id] = 
      convertShortParticleTypeNameToVerboseParticleTypeName( particle_type );
    
    // Store the cells assigned to the estimator
    TEST_FOR_EXCEPTION( surface_it->second.size() == 0,
			InvalidEstimatorRepresentation,
			"Error: estimator " << id << " has no cells "
			"specified!" );

    d_estimator_id_surfaces_map[id].assign( surface_it->second.begin(),
                                            surface_it->second.end() );

    ++surface_it;
  }
#endif // end HAVE_FRENSIE_DAGMC
}

// Load the cell volume map
void StandardEstimatorFactory<moab::DagMC>::loadCellVolumeMap()
{
#ifdef HAVE_FRENSIE_DAGMC
  boost::unordered_map<unsigned,
   Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> >::const_iterator
    it = d_estimator_id_cells_map.begin();

  while( it != d_estimator_id_cells_map.end() )
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
  boost::unordered_map<unsigned,
    Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle> >::const_iterator
    it = d_estimator_id_surfaces_map.begin();

  while( it != d_estimator_id_surfaces_map.end() )
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
void StandardEstimatorFactory<moab::DagMC>::verifyEstimatorTypeConsistency( 
                                     const unsigned estimator_id,
                                     const std::string& estimator_type ) const
{

}

// Get the estimator particle types - required
void StandardEstimatorFactory<moab::DagMC>::getEstimatorParticleType( 
                           Teuchos::Array<ParticleType>& particle_types,
                           const unsigned estimator_id,
                           const Teuchos::ParameterList& estimator_rep ) const
{

}

// Get the cells assigned to the estimator - required if cell estimator
void StandardEstimatorFactory<moab::DagMC>::getEstimatorCells( 
    Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& assigned_cells,
    const unsigned estimator_id,
    const Teuchos::ParameterList& estimator_rep ) const
{

}

// Get the cell volumes
void StandardEstimatorFactory<moab::DagMC>::getCellVolumes( 
     Teuchos::Array<double>& cell_volumes,
     const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cells )
{

}

// Get the surfaces assigned to the estimator - required if surface est.
void StandardEstimatorFactory<moab::DagMC>::getEstimatorSurfaces( 
                 Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>&
                 assigned_surfaces,
                 const unsigned estimator_id,
                 const Teuchos::ParameterList& estimator_rep ) const
{

}

// Get the surface areas
void StandardEstimatorFactory<moab::DagMC>::getSurfaceAreas( 
           Teuchos::Array<double>& surface_areas,
           const Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>&
           surfaces )
{

}

// Update the estimator cache info
void StandardEstimatorFactory<moab::DagMC>::updateEstimatorCacheInfo( 
                                                            const unsigned id )
{

}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardEstimatorFactory_DagMC.cpp
//---------------------------------------------------------------------------//
