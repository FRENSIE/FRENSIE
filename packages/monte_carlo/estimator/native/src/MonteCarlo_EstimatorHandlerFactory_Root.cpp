//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EstimatorHandlerFactory_Root.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Estimator handler factory class declaration.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <set>

// FRENSIE Includes
#include "MonteCarlo_EstimatorHandlerFactoryDecl.hpp"
#include "MonteCarlo_EstimatorHandlerFactory_Root.hpp"
#include "MonteCarlo_ResponseFunctionFactory.hpp"
#include "MonteCarlo_CellPulseHeightEstimator.hpp"
#include "MonteCarlo_CellTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_CellCollisionFluxEstimator.hpp"
#include "MonteCarlo_SurfaceFluxEstimator.hpp"
#include "MonteCarlo_SurfaceCurrentEstimator.hpp"
#include "MonteCarlo_TetMeshTrackLengthFluxEstimator.hpp"

#ifdef HAVE_FRENSIE_ROOT
#include "Geometry_ModuleInterface.hpp"
#include "Geometry_ModuleInterface_Root.hpp"
#endif

#include "Utility_ArrayString.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Initialize static member data
const std::string EstimatorHandlerFactory<Geometry::Root>::surface_current_name = 
  "Surface Current";

const std::string EstimatorHandlerFactory<Geometry::Root>::surface_flux_name = 
  "Surface Flux";

const std::string EstimatorHandlerFactory<Geometry::Root>::cell_pulse_height_name = 
  "Cell Pulse Height";

const std::string EstimatorHandlerFactory<Geometry::Root>::cell_track_length_flux_name = 
  "Cell Track-Length Flux";

const std::string EstimatorHandlerFactory<Geometry::Root>::cell_collision_flux_name = 
  "Cell Collision Flux";

const std::string EstimatorHandlerFactory<Geometry::Root>::tet_mesh_track_length_flux_name = 
  "Tet Mesh Track-Length Flux";

// Initialize the estimator handler using Root
void EstimatorHandlerFactory<Geometry::Root>::initializeHandler(
				 const Teuchos::ParameterList& response_reps,
				 const Teuchos::ParameterList& estimator_reps )
{
  // Create the response functions
  boost::unordered_map<unsigned,Teuchos::RCP<ResponseFunction> > 
    response_id_map;
  
  ResponseFunctionFactory::createResponseFunctions( response_reps,
						    response_id_map );

  // Validate the estimators
  Teuchos::ParameterList::ConstIterator it = estimator_reps.begin();

  while( it != estimator_reps.end() )
  {
    const Teuchos::ParameterList& estimator_rep = 
      Teuchos::any_cast<Teuchos::ParameterList>( it->second.getAny() );

    EstimatorHandlerFactory<Geometry::Root>::validateEstimatorRep( estimator_rep,
						   response_id_map );

    ++it;
  }

  // Create the estimator data maps
  boost::unordered_map<unsigned,std::string> estimator_id_type_map;
  boost::unordered_map<unsigned,std::string> estimator_id_ptype_map;
  boost::unordered_map<unsigned,
                 Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> >
    estimator_id_cells_map;
  boost::unordered_map<unsigned,
    Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle> >
    estimator_id_surfaces_map;
  
  EstimatorHandlerFactory<Geometry::Root>::createEstimatorDataMaps(
						   estimator_id_type_map,
						   estimator_id_ptype_map,
						   estimator_id_cells_map,
						   estimator_id_surfaces_map );

  // Append the data in the xml file to the estimator data maps
  EstimatorHandlerFactory<Geometry::Root>::appendDataToEstimatorDataMaps(
						   estimator_reps,
						   estimator_id_type_map,
						   estimator_id_ptype_map,
						   estimator_id_cells_map,
						   estimator_id_surfaces_map );

  // Create the cell volume map
  boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,double>
    cell_volume_map;

  EstimatorHandlerFactory<Geometry::Root>::createCellVolumeMap( estimator_id_cells_map,
						cell_volume_map );
  
  // Create the surface area map
  boost::unordered_map<Geometry::ModuleTraits::InternalSurfaceHandle,double>
    surface_area_map;
    
  EstimatorHandlerFactory<Geometry::Root>::createSurfaceAreaMap( estimator_id_surfaces_map,
						 surface_area_map );

  // Create the estimators
  it = estimator_reps.begin();

  while( it != estimator_reps.end() )
  {
    const Teuchos::ParameterList& estimator_rep = 
      Teuchos::any_cast<Teuchos::ParameterList>( it->second.getAny() );
								
    // Get the estimator id
    unsigned id = estimator_rep.get<unsigned int> ( "Id" );

    // Get the estimator multiplier
    double multiplier = 1.0;

    if( estimator_rep.isParameter( "Multiplier" ) )
      multiplier = estimator_rep.get<double>( "Multiplier" );

    TEST_FOR_EXCEPTION( multiplier <= 0.0,
			InvalidEstimatorRepresentation,
			"Error: estimator " << id << " has a negative "
			"multiplier specified!" );

    // Check if energy multiplication was requested
    bool energy_mult = false;
    
    if( estimator_rep.isParameter( "Energy Multiplication" ) )
      energy_mult = estimator_rep.get<bool>("Energy Multiplication");

    const Teuchos::ParameterList* estimator_bins = NULL;

    if( estimator_rep.isParameter( "Bins" ) )
      estimator_bins = &estimator_rep.get<Teuchos::ParameterList>( "Bins" );

    // Get the particle types assigned to the estimator
    Teuchos::Array<ParticleType> particle_types( 1 );
    particle_types[0] = 
      convertParticleTypeNameToParticleTypeEnum( estimator_id_ptype_map[id] );

    // Get the response functions assigned to the estimator
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
	TEST_FOR_EXCEPTION( 
		     response_id_map.find( requested_response_functions[i] ) ==
		     response_id_map.end(),
		     InvalidEstimatorRepresentation,
		     "Error: estimator " << id << " has requested response "
		     "function " << requested_response_functions[i] << 
		     " which does not exist!" );
	
	response_functions[i] = 
	  response_id_map[requested_response_functions[i]];
      }
    }    

    // Create cell estimator
    if( estimator_id_cells_map.find( id ) != estimator_id_cells_map.end() )
    {
      Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cells = 
	estimator_id_cells_map[id];
    
      Teuchos::Array<double> cell_volumes;
    
      if( EstimatorHandlerFactory<Geometry::Root>::isCellPulseHeightEstimator( estimator_id_type_map[id] ) )
      {
	EstimatorHandlerFactory<Geometry::Root>::createPulseHeightEstimator(
							id,
							multiplier,
							particle_types,
							cells,
							response_functions,
							energy_mult,
							estimator_bins );
      }
      else if( EstimatorHandlerFactory<Geometry::Root>::isCellTrackLengthFluxEstimator( estimator_id_type_map[id] ) )
      {
	EstimatorHandlerFactory<Geometry::Root>::fillCellVolumesArray( cells,
						       cell_volume_map,
						       cell_volumes );
	
	EstimatorHandlerFactory<Geometry::Root>::createCellTrackLengthFluxEstimator(
							id,
							multiplier,
							particle_types,
							cells,
							cell_volumes,
							response_functions,
							energy_mult,
							estimator_bins );
      }
      else if( EstimatorHandlerFactory<Geometry::Root>::isCellCollisionFluxEstimator( estimator_id_type_map[id] ) )
      {
	EstimatorHandlerFactory<Geometry::Root>::fillCellVolumesArray( cells,
						       cell_volume_map,
						       cell_volumes );
	
	EstimatorHandlerFactory<Geometry::Root>::createCellCollisionFluxEstimator(
							id,
							multiplier,
							particle_types,
							cells,
							cell_volumes,
							response_functions,
							energy_mult,
							estimator_bins );
      }
     
      estimator_id_cells_map.erase( id );
    }

    // Create surface estimator
    else if( estimator_id_surfaces_map.find( id ) != 
	     estimator_id_surfaces_map.end() )
    {
      Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>& 
	surfaces = estimator_id_surfaces_map[id];
    
      Teuchos::Array<double> surface_areas;
      
      if( EstimatorHandlerFactory<Geometry::Root>::isSurfaceFluxEstimator( estimator_id_type_map[id] ) )
      {
	EstimatorHandlerFactory<Geometry::Root>::fillSurfaceAreasArray( surfaces,
							surface_area_map,
							surface_areas );
	
	EstimatorHandlerFactory<Geometry::Root>::createSurfaceFluxEstimator(
							id,
							multiplier,
							particle_types,
							surfaces,
							surface_areas,
							response_functions,
							energy_mult,
							estimator_bins );
      }
      else
      {	
	EstimatorHandlerFactory<Geometry::Root>::createSurfaceCurrentEstimator(
							id,
							multiplier,
							particle_types,
							surfaces,
							response_functions,
							energy_mult,
							estimator_bins );
      }

      estimator_id_surfaces_map.erase( id );
    }

    // Create a tet mesh track length flux estimator
    /* Warning: Mesh tallies are not currently supported by ROOT and thus have
     * been turned off for the ROOT specialization.
     */  
    else if( estimator_id_type_map[id] == 
	     EstimatorHandlerFactory<Geometry::Root>::tet_mesh_track_length_flux_name )
    { /* ... */ }

    // Remove the ids from the maps
    estimator_id_type_map.erase( id );
    estimator_id_ptype_map.erase( id );

    estimator_rep.unused( std::cout );
    
    ++it;
  }

  /* There can be no remaining tallies to create, as the Root input cannot 
   * be used to specify tallies on surfaces/volumes.
   */  
}

// Validate an estimator representation
void EstimatorHandlerFactory<Geometry::Root>::validateEstimatorRep(
	  const Teuchos::ParameterList& estimator_rep,
	  const boost::unordered_map<unsigned,Teuchos::RCP<ResponseFunction> >&
	  response_id_map )
{
  // Make sure the estimator id has been specified
  TEST_FOR_EXCEPTION( !estimator_rep.isParameter( "Id" ),
		      InvalidEstimatorRepresentation,
		      "Error: the estimator id was not specified in estimator "
		      << estimator_rep.name() << "!" );

  // Make sure the estimator type has been specified
  TEST_FOR_EXCEPTION( !estimator_rep.isParameter( "Type" ),
		      InvalidEstimatorRepresentation,
		      "Error: the estimator type was not specified in "
		      "estimator " << estimator_rep.name() << "!" );
}

// Test if two estimator types are equivalent
bool EstimatorHandlerFactory<Geometry::Root>::areEstimatorTypesEquivalent( 
						 const std::string& geometry_module_type,
						 const std::string& xml_type )
{
  if( geometry_module_type == xml_type )
    return true;
}

// Create the estimator data maps using Root information
/*   Note that ROOT does not have estimator data, therefore this is an empty
 *   function call.
 */
void EstimatorHandlerFactory<Geometry::Root>::createEstimatorDataMaps(
	boost::unordered_map<unsigned,std::string>& estimator_id_type_map,
	boost::unordered_map<unsigned,std::string>& estimator_id_ptype_map,
	boost::unordered_map<unsigned,
	          Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> >&
	estimator_id_cells_map,
	boost::unordered_map<unsigned,
	       Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle> >&
	estimator_id_surfaces_map )
{ /* ... */ }

// Append data to estimator data maps
/*   Note that ROOT does not have estimator data, therefore this is an empty
 *   function call.
 */
void EstimatorHandlerFactory<Geometry::Root>::appendDataToEstimatorDataMaps(
	const Teuchos::ParameterList& estimator_reps,
	boost::unordered_map<unsigned,std::string>& estimator_id_type_map,
	boost::unordered_map<unsigned,std::string>& estimator_id_ptype_map,
	boost::unordered_map<unsigned,
	          Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> >&
	estimator_id_cells_map,
	boost::unordered_map<unsigned,
	       Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle> >&
	estimator_id_surfaces_map )
{ 
  #ifdef HAVE_FRENSIE_ROOT
  Teuchos::ParameterList::ConstIterator it = estimator_reps.begin();

  while( it != estimator_reps.end() )
  {
    const Teuchos::ParameterList& estimator_rep = 
      Teuchos::any_cast<Teuchos::ParameterList>( it->second.getAny() );

    unsigned id = estimator_rep.get<unsigned>( "Id" );
    std::string estimator_type = estimator_rep.get<std::string>( "Type" );

    if( estimator_id_type_map.find( id ) != estimator_id_type_map.end() )
    {   
      // Append cells to the estimator cells map
      if( Geometry::DagMCProperties::isCellEstimatorTypeValid(estimator_type) )
      {
        if( estimator_rep.isParameter( "Cells" ) )
        {
          const Utility::ArrayString& array_string = 
            estimator_rep.get<Utility::ArrayString>( "Cells" );
          
          Teuchos::Array<unsigned> extra_cells;

          try{
            extra_cells = array_string.getConcreteArray<unsigned>();
          }
          EXCEPTION_CATCH_RETHROW_AS(Teuchos::InvalidArrayStringRepresentation,
			             InvalidEstimatorRepresentation,
			             "Error: the cells requested for "
			             "estimator " << id << 
			             " are not valid!" );
            
          EstimatorHandlerFactory<Geometry::Root>::appendCellsToAssignedCells( 
					            id,
			                estimator_id_cells_map[id],
					            extra_cells );
        }
      }
      else
      {
	      if( estimator_rep.isParameter( "Surfaces" ) )
	      {
	        const Utility::ArrayString& array_string = 
	          estimator_rep.get<Utility::ArrayString>( "Surfaces" );
	        
	        Teuchos::Array<unsigned> extra_surfaces;

	        try{
	          extra_surfaces = array_string.getConcreteArray<unsigned>();
	        }
	        EXCEPTION_CATCH_RETHROW_AS(Teuchos::InvalidArrayStringRepresentation,
				           InvalidEstimatorRepresentation,
				           "Error: the surfaces requested for "
				           "estimator " << id << " are not valid!" );

	        EstimatorHandlerFactory<Geometry::Root>::appendSurfacesToAssignedSurfaces(
						       id,
						       estimator_id_surfaces_map[id],
						       extra_surfaces );
	      }
      }
    }
    else
    {
      // Assign the estimator type
      std::string estimator_type = estimator_rep.get<std::string>( "Type" );

      TEST_FOR_EXCEPTION( 
       !Geometry::DagMCProperties::isCellEstimatorTypeValid(estimator_type) &&
       !Geometry::DagMCProperties::isSurfaceEstimatorTypeValid(estimator_type) &&
       !EstimatorHandlerFactory<Geometry::Root>::isEstimatorTypeValid(estimator_type),
       InvalidEstimatorRepresentation,
       "Error: estimator " << id << " has estimator type " 
       << estimator_type << " specified in the xml file, which is "
       "invalid!" );

      estimator_id_type_map[id] = estimator_type;
      
      // Assign the estimator particle type
      TEST_FOR_EXCEPTION( !estimator_rep.isParameter( "Particle Type" ),
			  InvalidEstimatorRepresentation,
			  "Error: estimator " << id << " does not have a "
			  "particle type specified!" );

      const std::string& particle_type = 
	                           estimator_rep.get<std::string>( "Particle Type" );
      
      TEST_FOR_EXCEPTION( !isValidParticleTypeName( particle_type ),
			  InvalidEstimatorRepresentation,
			  "Error: estimator " << id << " specified particle "
			  "type " << particle_type << " which is not valid ("
			  "choose Neutron or Photon)" );

      estimator_id_ptype_map[id] = particle_type;
			 
      if( Geometry::DagMCProperties::isCellEstimatorTypeValid(estimator_type)||
          EstimatorHandlerFactory<Geometry::Root>::isCellEstimatorTypeValid(estimator_type) )
      {
	      TEST_FOR_EXCEPTION( !estimator_rep.isParameter( "Cells" ),
			          InvalidEstimatorRepresentation,
			          "Error: estimator " << id << " does not have "
			          "cells specified!" );

	      const Utility::ArrayString& array_string = 
	        estimator_rep.get<Utility::ArrayString>( "Cells" );
	
	      Teuchos::Array<unsigned> cells;

	      try{
	        cells = array_string.getConcreteArray<unsigned>();
	      }
	      EXCEPTION_CATCH_RETHROW_AS(Teuchos::InvalidArrayStringRepresentation,
				         InvalidEstimatorRepresentation,
				         "Error: the cells requested for "
				         "estimator " << id << 
				         " are not valid!" );
	
	      EstimatorHandlerFactory<Geometry::Root>::appendCellsToAssignedCells( 
						          id,
						          estimator_id_cells_map[id],
						          cells );
      }
      else if( Geometry::DagMCProperties::isSurfaceEstimatorTypeValid(estimator_type) ||
               EstimatorHandlerFactory<Geometry::Root>::isSurfaceEstimatorTypeValid( estimator_type ) )
      {
	      TEST_FOR_EXCEPTION( !estimator_rep.isParameter( "Surfaces" ),
			          InvalidEstimatorRepresentation,
			          "Error: estimator " << id << " does not have "
			          "surfaces specified!" );

	      const Utility::ArrayString& array_string = 
	          estimator_rep.get<Utility::ArrayString>( "Surfaces" );
	        
	      Teuchos::Array<unsigned> surfaces;

	      try{
	        surfaces = array_string.getConcreteArray<unsigned>();
	      }
	      EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
				          InvalidEstimatorRepresentation,
				          "Error: the surfaces requested for "
				          "estimator " << id << " are not valid!" );

	      EstimatorHandlerFactory<Geometry::Root>::appendSurfacesToAssignedSurfaces(
						       id,
						       estimator_id_surfaces_map[id],
						       surfaces );
      }
    }

    ++it;
  }

  // Make sure the maps have the correct sizes
  testPostcondition( estimator_id_type_map.size() ==
		     estimator_id_ptype_map.size() );
  testPostcondition( estimator_id_type_map.size() >=
		     estimator_id_cells_map.size() + 
		     estimator_id_surfaces_map.size() );
  #endif // end HAVE_FRENSIE_ROOT
}

// Append cells to assigned cells
// If Root is not enabled, this function will be empty
void EstimatorHandlerFactory<Geometry::Root>::appendCellsToAssignedCells(
	      const unsigned estimator_id,
	      Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>&
	      assigned_cells,
	      const Teuchos::Array<unsigned>& extra_cells )
{
  #ifdef HAVE_FRENSIE_ROOT
  std::set<Geometry::ModuleTraits::InternalCellHandle> 
    cells( assigned_cells.begin(), assigned_cells.end() );

  // Verify that the extra cells exist
  for( unsigned i = 0u; i < extra_cells.size(); ++i )
  {
    TEST_FOR_EXCEPTION( 
      !Geometry::ModuleInterface<Geometry::Root>::doesCellExist( extra_cells[i] ),
      InvalidEstimatorRepresentation,
      "Error: estimator " << estimator_id << " specified "
      "cell " << extra_cells[i] << " in the xml "
      "file, which does not exists!" );
    
    cells.insert( extra_cells[i] );
  }
  
  assigned_cells.clear();
  assigned_cells.assign( cells.begin(), cells.end() );
  #endif // end HAVE_FRENSIE_ROOT
}

// Append surfaces to assigned surfaces
// If Root is not enabled, this function will be empty
void EstimatorHandlerFactory<Geometry::Root>::appendSurfacesToAssignedSurfaces(
	   const unsigned estimator_id,
	   Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>&
	   assigned_surfaces,
	   const Teuchos::Array<unsigned>& extra_surfaces )
{
  #ifdef HAVE_FRENSIE_ROOT
  std::set<Geometry::ModuleTraits::InternalSurfaceHandle>
    surfaces( assigned_surfaces.begin(), assigned_surfaces.end() );

  // Verify that the extra surfaces exist
  for( unsigned i = 0u; i < extra_surfaces.size(); ++i )
  {
    TEST_FOR_EXCEPTION(
       !Geometry::ModuleInterface<Geometry::Root>::doesSurfaceExist( 
							   extra_surfaces[i] ),
       InvalidEstimatorRepresentation,
       "Error: estimator " << estimator_id << " specified "
       "surface " << extra_surfaces[i] << " in the "
       "xml file, which does not exists!" );
    
    surfaces.insert( extra_surfaces[i] );
  }
  
  assigned_surfaces.clear();
  assigned_surfaces.assign( surfaces.begin(), surfaces.end() );
  #endif // end HAVE_FRENSIE_ROOT
}

// Create the cell volume map
// If Root is not enabled, this function will be empty
void EstimatorHandlerFactory<Geometry::Root>::createCellVolumeMap(
       const boost::unordered_map<unsigned,
                  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> >&
       estimator_id_cells_map,
       boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,double>&
       cell_volume_map )
{
  #ifdef HAVE_FRENSIE_ROOT
  boost::unordered_map<unsigned,
   Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> >::const_iterator
    it = estimator_id_cells_map.begin();

  while( it != estimator_id_cells_map.end() )
  {
    for( unsigned i = 0u; i < it->second.size(); ++i )
    {
      if( cell_volume_map.find( it->second[i] ) == cell_volume_map.end() )
      {
	cell_volume_map[it->second[i]] = 
	  Geometry::ModuleInterface<Geometry::Root>::getCellVolume(it->second[i]);
      }
    }

    ++it;
  }
  #endif // end HAVE_FRENSIE_ROOT
}

// Create the surface area map
// If Root is not enabled, this function will be empty
void EstimatorHandlerFactory<Geometry::Root>::createSurfaceAreaMap(
    const boost::unordered_map<unsigned,
               Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle> >&
    estimator_id_surfaces_map,
    boost::unordered_map<Geometry::ModuleTraits::InternalSurfaceHandle,double>&
    surface_area_map )
{
  #ifdef HAVE_FRENSIE_ROOT
  boost::unordered_map<unsigned,
    Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle> >::const_iterator
    it = estimator_id_surfaces_map.begin();

  while( it != estimator_id_surfaces_map.end() )
  {
    for( unsigned i = 0u; i < it->second.size(); ++i )
    {
      if( surface_area_map.find( it->second[i] ) == surface_area_map.end() )
      {
	surface_area_map[it->second[i]] = 
	  Geometry::ModuleInterface<Geometry::Root>::getCellSurfaceArea(
								 it->second[i],
								 0 );
      }
    }
    
    ++it;
  }
  #endif // end HAVE_FRENSIE_ROOT
}

// Create a cell pulse height estimator
void EstimatorHandlerFactory<Geometry::Root>::createPulseHeightEstimator(
      const unsigned id,
      const double multiplier,
      const Teuchos::Array<ParticleType> particle_types,
      const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cells,
      const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_funcs,
      const bool energy_multiplication,
      const Teuchos::ParameterList* bins )
{
  // Create the estimator
  Teuchos::RCP<Estimator> estimator;
  
  if( energy_multiplication )
  {
    estimator.reset( new CellPulseHeightEstimator<WeightAndEnergyMultiplier>(
								    id,
						                    multiplier,
								    cells ) );
  }
  else
  {
    estimator.reset( new CellPulseHeightEstimator<WeightMultiplier>(id,
								    multiplier,
								    cells ) );
  }

  // Set the particle type
  estimator->setParticleTypes( particle_types );

  // Set the response functions
  if( response_funcs.size() > 0 )
    estimator->setResponseFunctions( response_funcs ); 

  // Assign estimator bins
  if( bins )
    EstimatorHandlerFactory<Geometry::Root>::assignBinsToEstimator( *bins, estimator );
  // Add this estimator to the handler
  if( energy_multiplication )
  {
    Teuchos::RCP<CellPulseHeightEstimator<WeightAndEnergyMultiplier> > 
      derived_estimator = Teuchos::rcp_dynamic_cast<CellPulseHeightEstimator<WeightAndEnergyMultiplier> >( estimator );

    EstimatorHandler::addEstimator( derived_estimator, cells );
  }
  else
  {
    Teuchos::RCP<CellPulseHeightEstimator<WeightMultiplier> >
      derived_estimator = Teuchos::rcp_dynamic_cast<CellPulseHeightEstimator<WeightMultiplier> >( estimator );

    EstimatorHandler::addEstimator( derived_estimator, cells );
  }
}

// Create a cell track length flux estimator
void EstimatorHandlerFactory<Geometry::Root>::createCellTrackLengthFluxEstimator(
      const unsigned id,
      const double multiplier,
      const Teuchos::Array<ParticleType> particle_types,
      const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cells,
      const Teuchos::Array<double>& cell_volumes,
      const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_funcs,
      const bool energy_multiplication,
      const Teuchos::ParameterList* bins )
{
  // Create the estimator
  Teuchos::RCP<Estimator> estimator;
  
  if( energy_multiplication )
  {
    estimator.reset( 
	          new CellTrackLengthFluxEstimator<WeightAndEnergyMultiplier>(
							      id,
							      multiplier,
							      cells,
							      cell_volumes ) );
  }
  else
  {
    estimator.reset( new CellTrackLengthFluxEstimator<WeightMultiplier>(
							      id,
							      multiplier,
							      cells,
							      cell_volumes ) );
  }

  // Set the particle type
  estimator->setParticleTypes( particle_types );

  // Set the response functions
  if( response_funcs.size() > 0 )
    estimator->setResponseFunctions( response_funcs );

  // Assign estimator bins
  if( bins )
    EstimatorHandlerFactory<Geometry::Root>::assignBinsToEstimator( *bins, estimator );

  // Add this estimator to the handler
  if( energy_multiplication )
  {
    Teuchos::RCP<CellTrackLengthFluxEstimator<WeightAndEnergyMultiplier> > 
      derived_estimator = Teuchos::rcp_dynamic_cast<CellTrackLengthFluxEstimator<WeightAndEnergyMultiplier> >( estimator );

    EstimatorHandler::addEstimator( derived_estimator, cells );
  }
  else
  {
    Teuchos::RCP<CellTrackLengthFluxEstimator<WeightMultiplier> >
      derived_estimator = Teuchos::rcp_dynamic_cast<CellTrackLengthFluxEstimator<WeightMultiplier> >( estimator );

    EstimatorHandler::addEstimator( derived_estimator, cells );
  }
}

// Create a cell collision flux estimator
void EstimatorHandlerFactory<Geometry::Root>::createCellCollisionFluxEstimator(
      const unsigned id,
      const double multiplier,
      const Teuchos::Array<ParticleType> particle_types,
      const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cells,
      const Teuchos::Array<double>& cell_volumes,
      const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_funcs,
      const bool energy_multiplication,
      const Teuchos::ParameterList* bins )
{
  // Create the estimator
  Teuchos::RCP<Estimator> estimator;
  
  if( energy_multiplication )
  {
    estimator.reset( new CellCollisionFluxEstimator<WeightAndEnergyMultiplier>(
							      id,
							      multiplier,
							      cells,
							      cell_volumes ) );
  }
  else
  {
    estimator.reset( new CellCollisionFluxEstimator<WeightMultiplier>(
							      id,
							      multiplier,
							      cells,
							      cell_volumes ) );
  }

  // Set the particle type
  estimator->setParticleTypes( particle_types );

  // Set the response functions
  if( response_funcs.size() > 0 )
    estimator->setResponseFunctions( response_funcs );

  // Assign estimator bins
  if( bins )
    EstimatorHandlerFactory<Geometry::Root>::assignBinsToEstimator( *bins, estimator );

  // Add this estimator to the handler
  if( energy_multiplication )
  {
    Teuchos::RCP<CellCollisionFluxEstimator<WeightAndEnergyMultiplier> > 
      derived_estimator = Teuchos::rcp_dynamic_cast<CellCollisionFluxEstimator<WeightAndEnergyMultiplier> >( estimator );

    EstimatorHandler::addEstimator( derived_estimator, cells );
  }
  else
  {
    Teuchos::RCP<CellCollisionFluxEstimator<WeightMultiplier> >
      derived_estimator = Teuchos::rcp_dynamic_cast<CellCollisionFluxEstimator<WeightMultiplier> >( estimator );

    EstimatorHandler::addEstimator( derived_estimator, cells );
  }
}

// Create a surface flux estimator
void EstimatorHandlerFactory<Geometry::Root>::createSurfaceFluxEstimator(
      const unsigned id,
      const double multiplier,
      const Teuchos::Array<ParticleType> particle_types,
      const Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>&
      surfaces,
      const Teuchos::Array<double>& surface_areas,
      const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_funcs,
      const bool energy_multiplication,
      const Teuchos::ParameterList* bins )
{
  // Create the estimator
  Teuchos::RCP<Estimator> estimator;
  
  if( energy_multiplication )
  {
    estimator.reset( new SurfaceFluxEstimator<WeightAndEnergyMultiplier>(
							      id,
							      multiplier,
							      surfaces,
							      surface_areas ) );
  }
  else
  {
    estimator.reset( new SurfaceFluxEstimator<WeightMultiplier>(
							      id,
							      multiplier,
							      surfaces,
							      surface_areas ) );
  }

  // Set the particle type
  estimator->setParticleTypes( particle_types );

  // Set the response functions
  if( response_funcs.size() > 0 )
    estimator->setResponseFunctions( response_funcs );

  // Assign estimator bins
  if( bins )
    EstimatorHandlerFactory<Geometry::Root>::assignBinsToEstimator( *bins, estimator );

  // Add this estimator to the handler
  if( energy_multiplication )
  {
    Teuchos::RCP<SurfaceFluxEstimator<WeightAndEnergyMultiplier> > 
      derived_estimator = Teuchos::rcp_dynamic_cast<SurfaceFluxEstimator<WeightAndEnergyMultiplier> >( estimator );

    EstimatorHandler::addEstimator( derived_estimator, surfaces );
  }
  else
  {
    Teuchos::RCP<SurfaceFluxEstimator<WeightMultiplier> >
      derived_estimator = Teuchos::rcp_dynamic_cast<SurfaceFluxEstimator<WeightMultiplier> >( estimator );

    EstimatorHandler::addEstimator( derived_estimator, surfaces );
  }
}

// Create a surface current estimator
void EstimatorHandlerFactory<Geometry::Root>::createSurfaceCurrentEstimator(
      const unsigned id,
      const double multiplier,
      const Teuchos::Array<ParticleType> particle_types,
      const Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>&
      surfaces,
      const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_funcs,
      const bool energy_multiplication,
      const Teuchos::ParameterList* bins )
{
  // Create the estimator
  Teuchos::RCP<Estimator> estimator;
  
  if( energy_multiplication )
  {
    estimator.reset( new SurfaceCurrentEstimator<WeightAndEnergyMultiplier>(
							          id,
							          multiplier,
							          surfaces ) );
  }
  else
  {
    estimator.reset( new SurfaceCurrentEstimator<WeightMultiplier>(
							          id,
							          multiplier,
							          surfaces ) );
  }

  // Set the particle type
  estimator->setParticleTypes( particle_types );

  // Set the response functions
  if( response_funcs.size() > 0 )
    estimator->setResponseFunctions( response_funcs );

  // Assign estimator bins
  if( bins )
    EstimatorHandlerFactory<Geometry::Root>::assignBinsToEstimator( *bins, estimator );

  // Add this estimator to the handler
  if( energy_multiplication )
  {
    Teuchos::RCP<SurfaceCurrentEstimator<WeightAndEnergyMultiplier> > 
      derived_estimator = Teuchos::rcp_dynamic_cast<SurfaceCurrentEstimator<WeightAndEnergyMultiplier> >( estimator );

    EstimatorHandler::addEstimator( derived_estimator, surfaces );
  }
  else
  {
    Teuchos::RCP<SurfaceCurrentEstimator<WeightMultiplier> >
      derived_estimator = Teuchos::rcp_dynamic_cast<SurfaceCurrentEstimator<WeightMultiplier> >( estimator );

    EstimatorHandler::addEstimator( derived_estimator, surfaces );
  }
}

// Create a tet mesh track length flux estimator
void EstimatorHandlerFactory<Geometry::Root>::createTetMeshTrackLengthFluxEstimator(
	 const unsigned id,
	 const double multiplier,
	 const Teuchos::Array<ParticleType> particle_types,
	 const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_funcs,
	 const std::string& mesh_file_name,
	 const std::string& output_mesh_file_name,
	 const bool energy_multiplication,
	 const Teuchos::ParameterList* bins )
{
  // Create the estimator
  Teuchos::RCP<Estimator> estimator;
  
  if( energy_multiplication )
  {
    estimator.reset( new TetMeshTrackLengthFluxEstimator<WeightAndEnergyMultiplier>(
						     id,
						     multiplier,
						     mesh_file_name,
						     output_mesh_file_name ) );
  }
  else
  {
    estimator.reset( new TetMeshTrackLengthFluxEstimator<WeightMultiplier>(
						     id,
						     multiplier,
						     mesh_file_name,
						     output_mesh_file_name ) );
  }

  // Set the particle type
  estimator->setParticleTypes( particle_types );

  // Set the response functions
  if( response_funcs.size() > 0 )
    estimator->setResponseFunctions( response_funcs );

  // Assign estimator bins
  if( bins )
    EstimatorHandlerFactory<Geometry::Root>::assignBinsToEstimator( *bins, estimator );

  // Add this estimator to the handler
  if( energy_multiplication )
  {
    Teuchos::RCP<TetMeshTrackLengthFluxEstimator<WeightAndEnergyMultiplier> > 
      derived_estimator = Teuchos::rcp_dynamic_cast<TetMeshTrackLengthFluxEstimator<WeightAndEnergyMultiplier> >( estimator );

    EstimatorHandler::addGlobalEstimator( derived_estimator );
  }
  else
  {
    Teuchos::RCP<TetMeshTrackLengthFluxEstimator<WeightMultiplier> >
      derived_estimator = Teuchos::rcp_dynamic_cast<TetMeshTrackLengthFluxEstimator<WeightMultiplier> >( estimator );

    EstimatorHandler::addGlobalEstimator( derived_estimator );
  }
}

// Assign bins to an estimator
void EstimatorHandlerFactory<Geometry::Root>::assignBinsToEstimator( 
					   const Teuchos::ParameterList& bins,
					   Teuchos::RCP<Estimator>& estimator )
{
  Teuchos::ParameterList::ConstIterator it = bins.begin();

  while( it != bins.end() )
  {
    if( bins.name( it ) == "Energy Bins" )
    {
      const Utility::ArrayString& array_string = 
	Teuchos::any_cast<Utility::ArrayString>( it->second.getAny() );
      
      Teuchos::Array<double> energy_bins;
      
      try{
	energy_bins = array_string.getConcreteArray<double>();
      }
      EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
				  InvalidEstimatorRepresentation,
				  "Error: the energy bins requested for "
				  "estimator " << estimator->getId() << 
				  " are not valid!" );
      
      TEST_FOR_EXCEPTION(!Utility::Sort::isSortedAscending(energy_bins.begin(),
							   energy_bins.end() ),
			  InvalidEstimatorRepresentation,
			  "Error: the energy bins requested for estimator "
			  << estimator->getId() << " are not sorted from "
			  "lowest to highest!" );
    
      estimator->setBinBoundaries<ENERGY_DIMENSION>( energy_bins );
    }

    else if( bins.name( it ) == "Time Bins" )
    {
      const Utility::ArrayString& array_string = 
	Teuchos::any_cast<Utility::ArrayString>( it->second.getAny() );
      
      Teuchos::Array<double> time_bins;

      try{
	time_bins = array_string.getConcreteArray<double>();
      }
      EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
				  InvalidEstimatorRepresentation,
				  "Error: the time bins requested for "
				  "estimator " << estimator->getId() << 
				  " are not valid!" );
      
      TEST_FOR_EXCEPTION( !Utility::Sort::isSortedAscending( time_bins.begin(),
							     time_bins.end() ),
			  InvalidEstimatorRepresentation,
			  "Error: the time bins requested for estimator "
			  << estimator->getId() << " are not sorted from "
			  "lowest to highest!" );

      estimator->setBinBoundaries<TIME_DIMENSION>( time_bins );
    }

    else if( bins.name( it ) == "Collision Number Bins" )
    {
      const Utility::ArrayString& array_string = 
	Teuchos::any_cast<Utility::ArrayString>( it->second.getAny() );
      
      Teuchos::Array<unsigned> col_num_bins;
      
      try{
	col_num_bins = array_string.getConcreteArray<unsigned>();
      }
      EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
				  InvalidEstimatorRepresentation,
				  "Error: the collision number bins requested "
				  "for estimator " << estimator->getId() << 
				  " are not valid!" );
      
      TEST_FOR_EXCEPTION( !Utility::Sort::isSortedAscending(
							  col_num_bins.begin(),
							  col_num_bins.end() ),
			  InvalidEstimatorRepresentation,
			  "Error: the collision number bins requested for "
			  "estimator " << estimator->getId() << " are not "
			  "sorted from lowest to highest!" );

      estimator->setBinBoundaries<COLLISION_NUMBER_DIMENSION>( col_num_bins );
    }

    else if( bins.name( it ) == "Cosine Bins" )
    {
      const Utility::ArrayString& array_string = 
	Teuchos::any_cast<Utility::ArrayString>( it->second.getAny() );
      
      Teuchos::Array<double> cosine_bins;

      try{
	cosine_bins = array_string.getConcreteArray<double>();
      }

      EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
				  InvalidEstimatorRepresentation,
				  "Error: the cosine bins requested "
				  "for estimator " << estimator->getId() << 
				  " are not valid!" );
      
      TEST_FOR_EXCEPTION(!Utility::Sort::isSortedAscending(cosine_bins.begin(),
							   cosine_bins.end() ),
			  InvalidEstimatorRepresentation,
			  "Error: the cosine bins requested for estimator "
			  << estimator->getId() << " are not sorted from "
			  "lowest to highest!" );

      estimator->setBinBoundaries<COSINE_DIMENSION>( cosine_bins );
    }
    
    ++it;
  }

  bins.unused( std::cout );
      
}

// Fill cell volumes array
void EstimatorHandlerFactory<Geometry::Root>::fillCellVolumesArray( 
       const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cells,
       const boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
	                          double>& cell_volume_map,
       Teuchos::Array<double>& cell_volumes )
{
  cell_volumes.clear();
  cell_volumes.resize( cells.size() );
  
  for( unsigned i = 0; i < cells.size(); ++i )
    cell_volumes[i] = cell_volume_map.find( cells[i] )->second;
}

// Fill the surface areas array
void EstimatorHandlerFactory<Geometry::Root>::fillSurfaceAreasArray(
      const Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>&
      surfaces,
      const boost::unordered_map<Geometry::ModuleTraits::InternalSurfaceHandle,
                                 double>& surface_area_map,
      Teuchos::Array<double>& surface_areas )
{
  surface_areas.clear();
  surface_areas.resize( surfaces.size() );

  for( unsigned i = 0; i < surfaces.size(); ++i )
    surface_areas[i] = surface_area_map.find( surfaces[i] )->second;
}

// Check if the estimator type is valid
bool EstimatorHandlerFactory<Geometry::Root>::isEstimatorTypeValid(
					   const std::string& estimator_type )
{
  return EstimatorHandlerFactory<Geometry::Root>::isCellEstimatorTypeValid( estimator_type ) ||
    EstimatorHandlerFactory<Geometry::Root>::isSurfaceEstimatorTypeValid( estimator_type ) ||
    EstimatorHandlerFactory<Geometry::Root>::isMeshEstimatorTypeValid( estimator_type );
  
}

// Check if a cell estimator type is valid
bool EstimatorHandlerFactory<Geometry::Root>::isCellEstimatorTypeValid( 
					    const std::string& estimator_type )
{
  if( estimator_type == EstimatorHandlerFactory<Geometry::Root>::cell_track_length_flux_name )
    return true;
  else if( estimator_type == EstimatorHandlerFactory<Geometry::Root>::cell_collision_flux_name )
    return true;
  else if( estimator_type == EstimatorHandlerFactory<Geometry::Root>::cell_pulse_height_name )
    return true;
  else
    return false;
}

// Check if a surface estimator type is valid
bool EstimatorHandlerFactory<Geometry::Root>::isSurfaceEstimatorTypeValid( 
					    const std::string& estimator_type )
{
  if( estimator_type == EstimatorHandlerFactory<Geometry::Root>::surface_current_name )
    return true;
  else if( estimator_type == EstimatorHandlerFactory<Geometry::Root>::surface_flux_name )
    return true;
  else
    return false;
}

// Check if a mesh estimator type is valid
bool EstimatorHandlerFactory<Geometry::Root>::isMeshEstimatorTypeValid( 
                                            const std::string& estimator_type )
{
  if( estimator_type == EstimatorHandlerFactory<Geometry::Root>::tet_mesh_track_length_flux_name )
    return true;
  else
    return false;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_EstimatorHandlerFactory_Root.cpp
//---------------------------------------------------------------------------//
