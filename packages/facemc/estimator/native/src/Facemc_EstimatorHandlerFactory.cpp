//---------------------------------------------------------------------------//
//!
//! \file   Facemc_EstimatorHandlerFactory.cpp
//! \author Alex Robinson
//! \brief  Estimator handler factory class declaration.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <set>

// FRENSIE Includes
#include "Facemc_EstimatorHandlerFactory.hpp"
#include "Facemc_ResponseFunctionFactory.hpp"
#include "Facemc_CellPulseHeightEstimator.hpp"
#include "Facemc_CellTrackLengthFluxEstimator.hpp"
#include "Facemc_CellCollisionFluxEstimator.hpp"
#include "Facemc_SurfaceFluxEstimator.hpp"
#include "Facemc_SurfaceCurrentEstimator.hpp"
#include "Geometry_DagMCHelpers.hpp"
#include "Geometry_DagMCProperties.hpp"
#include "Geometry_ModuleInterface.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Initialize the estimator handler using DagMC
void EstimatorHandlerFactory::initializeHandlerUsingDagMC(
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

    EstimatorHandlerFactory::validateEstimatorRep( estimator_rep,
						   response_id_map );

    ++it;
  }

  // Create the estimator data maps using DagMC information
  boost::unordered_map<unsigned,std::string> estimator_id_type_map;
  boost::unordered_map<unsigned,std::string> estimator_id_ptype_map;
  boost::unordered_map<unsigned,
                 Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> >
    estimator_id_cells_map;
  boost::unordered_map<unsigned,
    Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle> >
    estimator_id_surfaces_map;
  
  EstimatorHandlerFactory::createEstimatorDataMapsUsingDagMC(
						   estimator_id_type_map,
						   estimator_id_ptype_map,
						   estimator_id_cells_map,
						   estimator_id_surfaces_map );

  // Append the data in the xml file tot he estimator data maps
  EstimatorHandlerFactory::appendDataToEstimatorDataMaps(
						   estimator_reps,
						   estimator_id_type_map,
						   estimator_id_ptype_map,
						   estimator_id_cells_map,
						   estimator_id_surfaces_map );

  // Create the cell volume map
  boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,double>
    cell_volume_map;

  EstimatorHandlerFactory::createCellVolumeMap( estimator_id_cells_map,
						cell_volume_map );
  
  // Create the surface area map
  boost::unordered_map<Geometry::ModuleTraits::InternalSurfaceHandle,double>
    surface_area_map;
    
  EstimatorHandlerFactory::createSurfaceAreaMap( estimator_id_surfaces_map,
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
      const Teuchos::Array<unsigned>& requested_response_functions = 
	estimator_rep.get<Teuchos::Array<unsigned> >( "Response Functions" );

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
    
      if( estimator_id_type_map[id] == "cell.pulse.height" )
      {
	EstimatorHandlerFactory::createPulseHeightEstimator(
							id,
							multiplier,
							particle_types,
							cells,
							response_functions,
							energy_mult,
							estimator_bins );
      }
      else if( estimator_id_type_map[id] == "cell.tl.flux" )
      {
	EstimatorHandlerFactory::fillCellVolumesArray( cells,
						       cell_volume_map,
						       cell_volumes );
	
	EstimatorHandlerFactory::createCellTrackLengthFluxEstimator(
							id,
							multiplier,
							particle_types,
							cells,
							cell_volumes,
							response_functions,
							energy_mult,
							estimator_bins );
      }
      else if( estimator_id_type_map[id] == "cell.c.flux" )
      {
	EstimatorHandlerFactory::fillCellVolumesArray( cells,
						       cell_volume_map,
						       cell_volumes );
	
	EstimatorHandlerFactory::createCellCollisionFluxEstimator(
							id,
							multiplier,
							particle_types,
							cells,
							cell_volumes,
							response_functions,
							energy_mult,
							estimator_bins );
      }
    }

    // Create surface estimator
    else
    {
      Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>& 
	surfaces = estimator_id_surfaces_map[id];
    
      Teuchos::Array<double> surface_areas;
      
      if( estimator_id_type_map[id] == "surface.flux" )
      {
	EstimatorHandlerFactory::fillSurfaceAreasArray( surfaces,
							surface_area_map,
							surface_areas );
	
	EstimatorHandlerFactory::createSurfaceFluxEstimator(
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
	EstimatorHandlerFactory::createSurfaceCurrentEstimator(
							id,
							multiplier,
							particle_types,
							surfaces,
							response_functions,
							energy_mult,
							estimator_bins );
      }
    }

    // Remove the ids from the maps
    estimator_id_type_map.erase( id );
    estimator_id_ptype_map.erase( id );
    estimator_id_cells_map.erase( id );

    estimator_rep.unused( std::cout );
    
    ++it;
  }

  // Create any remaining estimators
  while( estimator_id_type_map.size() > 0 )
  {
    unsigned id = estimator_id_type_map.begin()->first;

    // Get the particle types assigned to the estimator
    Teuchos::Array<ParticleType> particle_types( 1 );
    particle_types[0] = 
      convertParticleTypeNameToParticleTypeEnum( estimator_id_ptype_map[id] );

    // Create an empty response function array
    Teuchos::Array<Teuchos::RCP<ResponseFunction> > response_functions;

    // Create cell estimator
    if( estimator_id_cells_map.find( id ) != estimator_id_cells_map.end() )
    {
      Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cells = 
	estimator_id_cells_map[id];
    
      Teuchos::Array<double> cell_volumes;
    
      if( estimator_id_type_map[id] == "cell.pulse.height" )
      {
	EstimatorHandlerFactory::createPulseHeightEstimator(
							  id,
							  1.0,
							  particle_types,
							  cells,
							  response_functions );
      }
      else if( estimator_id_type_map[id] == "cell.tl.flux" )
      {
	EstimatorHandlerFactory::fillCellVolumesArray( cells,
						       cell_volume_map,
						       cell_volumes );
	
	EstimatorHandlerFactory::createCellTrackLengthFluxEstimator(
							id,
							1.0,
							particle_types,
							cells,
							cell_volumes,
							response_functions );
      }
      else if( estimator_id_type_map[id] == "cell.c.flux" )
      {
	EstimatorHandlerFactory::fillCellVolumesArray( cells,
						       cell_volume_map,
						       cell_volumes );
	
	EstimatorHandlerFactory::createCellCollisionFluxEstimator(
							id,
							1.0,
							particle_types,
							cells,
							cell_volumes,
							response_functions );
      }
    }

    // Create surface estimator
    else
    {
      Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>& 
	surfaces = estimator_id_surfaces_map[id];
    
      Teuchos::Array<double> surface_areas;
      
      if( estimator_id_type_map[id] == "surface.flux" )
      {
	EstimatorHandlerFactory::fillSurfaceAreasArray( surfaces,
							surface_area_map,
							surface_areas );
	
	EstimatorHandlerFactory::createSurfaceFluxEstimator(
							id,
							1.0,
							particle_types,
							surfaces,
							surface_areas,
							response_functions );
      }
      else
      {
	EstimatorHandlerFactory::createSurfaceCurrentEstimator(
							id,
							1.0,
							particle_types,
							surfaces,
							response_functions );
      }
    }

    // Remove the ids from the maps
    estimator_id_type_map.erase( id );
    estimator_id_ptype_map.erase( id );
    estimator_id_cells_map.erase( id );
  }    
}

// Validate an estimator representation
void EstimatorHandlerFactory::validateEstimatorRep(
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

// Create the estimator data maps using DagMC information
void EstimatorHandlerFactory::createEstimatorDataMapsUsingDagMC(
	boost::unordered_map<unsigned,std::string>& estimator_id_type_map,
	boost::unordered_map<unsigned,std::string>& estimator_id_ptype_map,
	boost::unordered_map<unsigned,
	          Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> >&
	estimator_id_cells_map,
	boost::unordered_map<unsigned,
	       Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle> >&
	estimator_id_surfaces_map )
{
  typedef boost::unordered_map<std::string,
                      std::vector<Geometry::ModuleTraits::InternalCellHandle> >
    EstimatorPropCellIdMap;

  typedef boost::unordered_map<std::string,
                   std::vector<Geometry::ModuleTraits::InternalSurfaceHandle> >
    EstimatorPropSurfaceIdMap;
  
  EstimatorPropCellIdMap estimator_prop_cell_id_map;

  EstimatorPropSurfaceIdMap estimator_prop_surface_id_map;

  Geometry::getCellIdsWithPropertyValue(
			 Geometry::DagMCProperties::getEstimatorPropertyName(),
			 estimator_prop_cell_id_map );
  
  Geometry::getSurfaceIdsWithPropertyValue(
			 Geometry::DagMCProperties::getEstimatorPropertyName(),
			 estimator_prop_surface_id_map );
  
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
    // The estimator id must be unique
    TEST_FOR_EXCEPTION( estimator_id_type_map.find( id ) !=
			estimator_id_type_map.end(),
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

    estimator_id_type_map[id] = estimator_type;

    // Store the particle type requested
    TEST_FOR_EXCEPTION(
	     !Geometry::DagMCProperties::isParticleTypeValid( particle_type ),
	     InvalidEstimatorRepresentation,
	     "Error: estimator " << id << " has particle type " 
	     << particle_type << " specified in the .sat file, which is "
	     "not valid (choose n or p)!" );
    
    TEST_FOR_EXCEPTION( estimator_type == "cell.pulse.height" &&
			particle_type == "n",
			InvalidEstimatorRepresentation,
			"Error: pulse height estimator " << id << " has "
			"been assigned a particle type of neutron (only "
			"photons can be assigned)" );
			

    if( particle_type == "n" )
      estimator_id_ptype_map[id] = "Neutron";
    else if( particle_type == "p" )
      estimator_id_ptype_map[id] = "Photon";

    // Store the cells assigned to the estimator
    TEST_FOR_EXCEPTION( cell_it->second.size() == 0,
			InvalidEstimatorRepresentation,
			"Error: estimator " << id << " has no cells "
			"specified!" );

    estimator_id_cells_map[id].assign( cell_it->second.begin(),
				       cell_it->second.end() );

    ++cell_it;
  }

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

    estimator_id_type_map[id] = estimator_type;

    // Store the particle type requested
    TEST_FOR_EXCEPTION(
	     !Geometry::DagMCProperties::isParticleTypeValid( particle_type ),
	     InvalidEstimatorRepresentation,
	     "Error: estimator " << id << " has particle type " 
	     << particle_type << " specified in the .sat file, which is "
	     "not valid (choose n or p)!" );

    if( particle_type == "n" )
      estimator_id_ptype_map[id] = "Neutron";
    else if( particle_type == "p" )
      estimator_id_ptype_map[id] = "Photon";

    // Store the cells assigned to the estimator
    TEST_FOR_EXCEPTION( surface_it->second.size() == 0,
			InvalidEstimatorRepresentation,
			"Error: estimator " << id << " has no cells "
			"specified!" );

    estimator_id_surfaces_map[id].assign( surface_it->second.begin(),
					  surface_it->second.end() );

    ++surface_it;
  }

  // Make sure the maps have the correct sizes
  testPostcondition( estimator_id_type_map.size() ==
		     estimator_id_ptype_map.size() );
  testPostcondition( estimator_id_type_map.size() ==
		     estimator_id_cells_map.size() + 
		     estimator_id_surfaces_map.size() );
}

// Append data to estimator data maps
void EstimatorHandlerFactory::appendDataToEstimatorDataMaps(
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
  Teuchos::ParameterList::ConstIterator it = estimator_reps.begin();

  while( it != estimator_reps.end() )
  {
    const Teuchos::ParameterList& estimator_rep = 
      Teuchos::any_cast<Teuchos::ParameterList>( it->second.getAny() );

    unsigned id = estimator_rep.get<unsigned>( "Id" );
    std::string estimator_type = estimator_rep.get<std::string>( "Type" );

    if( estimator_id_type_map.find( id ) != estimator_id_type_map.end() )
    {
      TEST_FOR_EXCEPTION( estimator_id_type_map[id] != estimator_type,
			  InvalidEstimatorRepresentation,
			  "Error: estimator " << id << " specified in the "
			  "xml file and the .sat file have inconsistent "
			  "types (" 
			  << estimator_rep.get<std::string>( "Type" ) << " != "
			  << estimator_id_type_map[id] << ")!" );

      if( estimator_rep.isParameter( "Particle Type" ) )
      {
	TEST_FOR_EXCEPTION( estimator_id_ptype_map[id] !=
			    estimator_rep.get<std::string>( "Particle Type" ),
			    InvalidEstimatorRepresentation,
			    "Error: estimator " << id << " specified in the "
			    "xml file and the .sat file have inconsitent "
			    "particle types ("
			    << estimator_rep.get<std::string>("Particle Type")
			    << " != " << estimator_id_ptype_map[id] <<
			    ")!" );
      }
      
      // Append cells to the estimator cells map
      if( Geometry::DagMCProperties::isCellEstimatorTypeValid(estimator_type) )
      {
	if( estimator_rep.isParameter( "Cells" ) )
	{
	  const Teuchos::Array<unsigned>& extra_cells =
	    estimator_rep.get<Teuchos::Array<unsigned int> >( "Cells" );

	  EstimatorHandlerFactory::appendCellsToAssignedCells( 
						    id,
						    estimator_id_cells_map[id],
						    extra_cells );
	}
      }
      else
      {
	if( estimator_rep.isParameter( "Surfaces" ) )
	{
	  const Teuchos::Array<unsigned>& extra_surfaces = 
	    estimator_rep.get<Teuchos::Array<unsigned int> >( "Surfaces" );

	  EstimatorHandlerFactory::appendSurfacesToAssignedSurfaces(
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
       !Geometry::DagMCProperties::isSurfaceEstimatorTypeValid(estimator_type),
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
			 
      if( Geometry::DagMCProperties::isCellEstimatorTypeValid(estimator_type) )
      {
	TEST_FOR_EXCEPTION( !estimator_rep.isParameter( "Cells" ),
			    InvalidEstimatorRepresentation,
			    "Error: estimator " << id << " does not have "
			    "cells specified!" );
	
	const Teuchos::Array<unsigned>& cells = 
	  estimator_rep.get<Teuchos::Array<unsigned int> >( "Cells" );
	
	EstimatorHandlerFactory::appendCellsToAssignedCells( 
						    id,
						    estimator_id_cells_map[id],
						    cells );
      }
      else
      {
	TEST_FOR_EXCEPTION( !estimator_rep.isParameter( "Surfaces" ),
			    InvalidEstimatorRepresentation,
			    "Error: estimator " << id << " does not have "
			    "surfaces specified!" );

	const Teuchos::Array<unsigned>& surfaces = 
	  estimator_rep.get<Teuchos::Array<unsigned int> >( "Surfaces" );

	EstimatorHandlerFactory::appendSurfacesToAssignedSurfaces(
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
  testPostcondition( estimator_id_type_map.size() ==
		     estimator_id_cells_map.size() + 
		     estimator_id_surfaces_map.size() );
}

// Append cells to assigned cells
void EstimatorHandlerFactory::appendCellsToAssignedCells(
	      const unsigned estimator_id,
	      Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>&
	      assigned_cells,
	      const Teuchos::Array<unsigned>& extra_cells )
{
  std::set<Geometry::ModuleTraits::InternalCellHandle> 
    cells( assigned_cells.begin(), assigned_cells.end() );

  // Verify that the extra cells exist
  for( unsigned i = 0u; i < extra_cells.size(); ++i )
  {
    TEST_FOR_EXCEPTION( 
      !Geometry::ModuleInterface<moab::DagMC>::doesCellExist( extra_cells[i] ),
      InvalidEstimatorRepresentation,
      "Error: estimator " << estimator_id << " specified "
      "cell " << extra_cells[i] << " in the xml "
      "file, which does not exists!" );
    
    cells.insert( extra_cells[i] );
  }
  
  assigned_cells.clear();
  assigned_cells.assign( cells.begin(), cells.end() );
}

// Append surfaces to assigned surfaces
void EstimatorHandlerFactory::appendSurfacesToAssignedSurfaces(
	   const unsigned estimator_id,
	   Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>&
	   assigned_surfaces,
	   const Teuchos::Array<unsigned>& extra_surfaces )
{
  std::set<Geometry::ModuleTraits::InternalSurfaceHandle>
    surfaces( assigned_surfaces.begin(), assigned_surfaces.end() );

  // Verify that the extra surfaces exist
  for( unsigned i = 0u; i < extra_surfaces.size(); ++i )
  {
    TEST_FOR_EXCEPTION(
       !Geometry::ModuleInterface<moab::DagMC>::doesSurfaceExist( 
							   extra_surfaces[i] ),
       InvalidEstimatorRepresentation,
       "Error: estimator " << estimator_id << " specified "
       "surface " << extra_surfaces[i] << " in the "
       "xml file, which does not exists!" );
    
    surfaces.insert( extra_surfaces[i] );
  }
  
  assigned_surfaces.clear();
  assigned_surfaces.assign( surfaces.begin(), surfaces.end() );
}

// Create the cell volume map
void EstimatorHandlerFactory::createCellVolumeMap(
       const boost::unordered_map<unsigned,
                  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> >&
       estimator_id_cells_map,
       boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,double>&
       cell_volume_map )
{
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
	  Geometry::ModuleInterface<moab::DagMC>::getCellVolume(it->second[i]);
      }
    }

    ++it;
  }
}

// Create the surface area map
void EstimatorHandlerFactory::createSurfaceAreaMap(
    const boost::unordered_map<unsigned,
               Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle> >&
    estimator_id_surfaces_map,
    boost::unordered_map<Geometry::ModuleTraits::InternalSurfaceHandle,double>&
    surface_area_map )
{
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
	  Geometry::ModuleInterface<moab::DagMC>::getCellSurfaceArea(
								 it->second[i],
								 0 );
      }
    }
    
    ++it;
  }
}

// Create a cell pulse height estimator
void EstimatorHandlerFactory::createPulseHeightEstimator(
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
    EstimatorHandlerFactory::assignBinsToEstimator( *bins, estimator );
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
void EstimatorHandlerFactory::createCellTrackLengthFluxEstimator(
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
    EstimatorHandlerFactory::assignBinsToEstimator( *bins, estimator );

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
void EstimatorHandlerFactory::createCellCollisionFluxEstimator(
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
    EstimatorHandlerFactory::assignBinsToEstimator( *bins, estimator );

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
void EstimatorHandlerFactory::createSurfaceFluxEstimator(
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
    EstimatorHandlerFactory::assignBinsToEstimator( *bins, estimator );

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
void EstimatorHandlerFactory::createSurfaceCurrentEstimator(
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
    EstimatorHandlerFactory::assignBinsToEstimator( *bins, estimator );

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

// Assign bins to an estimator
void EstimatorHandlerFactory::assignBinsToEstimator( 
					   const Teuchos::ParameterList& bins,
					   Teuchos::RCP<Estimator>& estimator )
{
  Teuchos::ParameterList::ConstIterator it = bins.begin();

  while( it != bins.end() )
  {
    if( bins.name( it ) == "Energy Bins" )
    {
      const Teuchos::Array<double>& energy_bins = 
	Teuchos::any_cast<Teuchos::Array<double> >( it->second.getAny() );
      
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
      const Teuchos::Array<double>& time_bins = 
	Teuchos::any_cast<Teuchos::Array<double> >( it->second.getAny() );
      
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
      const Teuchos::Array<unsigned>& col_num_bins = 
	Teuchos::any_cast<Teuchos::Array<unsigned int> >( it->second.getAny());
      
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
      const Teuchos::Array<double>& cosine_bins = 
	Teuchos::any_cast<Teuchos::Array<double> >( it->second.getAny() );
      
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
void EstimatorHandlerFactory::fillCellVolumesArray( 
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
void EstimatorHandlerFactory::fillSurfaceAreasArray(
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

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_EstimatorHandlerFactory.cpp
//---------------------------------------------------------------------------//
