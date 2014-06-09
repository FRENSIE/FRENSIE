//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleSourceFactory_def.hpp
//! \author Alex Robinson
//! \brief  Particle source factory base class definition
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_SOURCE_FACTORY_DEF_HPP
#define FACEMC_PARTICLE_SOURCE_FACTORY_DEF_HPP

// FRENSIE Includes
#include "Facemc_DistributedSource.hpp"
#include "Facemc_StateSource.hpp"
#include "Facemc_CompoundSource.hpp"
#include "Geometry_ModuleInterface.hpp"
#include "Utility_SpatialDistributionFactory.hpp"
#include "Utility_DirectionalDistributionFactory.hpp"
#include "Utility_OneDDistributionEntryConverterDB.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Create the source represented by the parameter list
template<typename GeometryHandler>
Teuchos::RCP<ParticleSource>
ParticleSourceFactory::createSourceImpl( 
				     const Teuchos::ParameterList& source_rep )
{
  // Get the number of parameters in the list
  unsigned num_params = source_rep.numParams();
  
  // Validate all sources defined
  Teuchos::ParameterList::ConstIterator param_iter = 
    source_rep.begin();
  
  while( param_iter != source_rep.end() )
  {
    const Teuchos::ParameterList& sub_source = 
      Teuchos::any_cast<Teuchos::ParameterList>( param_iter->second.getAny() );
    
    ParticleSourceFactory::validateSourceRep( sub_source, num_params );
    
    ++param_iter;
  }
  
  Teuchos::RCP<ParticleSource> source;
  
  if( num_params == 1 )
  {
    const Teuchos::ParameterList& sub_source = 
      Teuchos::any_cast<Teuchos::ParameterList>( 
					 source_rep.begin()->second.getAny() );
    
    if( sub_source.isParameter( "Spatial Distribution" ) )
    {
      ParticleSourceFactory::createDistributedSource<GeometryHandler>( 
							            sub_source,
								    source );
    }
    else
      ParticleSourceFactory::createStateSource( sub_source, source );
  }
  else
    ParticleSourceFactory::createCompoundSource<GeometryHandler>( source_rep, 
								  source );
  
  // Make sure the source has been created
  testPostcondition( !source.is_null() );

  // Print out unused parameters
  source_rep.unused( std::cout );
  
  return source;
}

// Create a distributed source
template<typename GeometryHandler>
double ParticleSourceFactory::createDistributedSource(
				      const Teuchos::ParameterList& source_rep,
				      Teuchos::RCP<ParticleSource>& source,
				      const unsigned num_sources )
{
  // Extract the source id
  unsigned id = source_rep.get<int>( "Id" );
  
  Teuchos::RCP<const Teuchos::ParameterEntry> entry = 
    source_rep.getEntryRCP( "Spatial Distribution" );
  
  // Extract the spatial distribution
  const Teuchos::ParameterList& spatial_dist_rep = 
      Teuchos::any_cast<Teuchos::ParameterList>( entry->getAny() );
  
  Teuchos::RCP<Utility::SpatialDistribution> spatial_distribution;
  try{
    spatial_distribution = 
      Utility::SpatialDistributionFactory::createDistribution( 
							    spatial_dist_rep );
					      
  }
  catch( Utility::InvalidSpatialDistributionRepresentation& error )
  {
    std::string message = "Error: An invalid spatial distribution was ";
    message += "specified in the distributed source!";
    message += error.what();
    
    throw InvalidParticleSourceRepresentation( message );
  }
  
  // Extract the directional distribution
  entry = source_rep.getEntryRCP( "Directional Distribution" );
  
  const Teuchos::ParameterList& directional_dist_rep = 
      Teuchos::any_cast<Teuchos::ParameterList>( entry->getAny() );
  
  Teuchos::RCP<Utility::DirectionalDistribution> directional_distribution;
  try{
    directional_distribution = 
      Utility::DirectionalDistributionFactory::createDistribution(
							directional_dist_rep );
  }
  catch( Utility::InvalidDirectionalDistributionRepresentation& error )
  {
    std::string message = "Error: An invalid directional distribution was ";
    message += "specified in the distributed source!";
    message += error.what();
    
    throw InvalidParticleSourceRepresentation( message );
  }

  // Extract the energy distribution
  entry = source_rep.getEntryRCP( "Energy Distribution" );

  Teuchos::RCP<Utility::OneDDistribution> energy_distribution = 
    Utility::OneDDistributionEntryConverterDB::convertEntry( entry );

  // Extract the time distribution
  entry = source_rep.getEntryRCP( "Time Distribution" );

  Teuchos::RCP<Utility::OneDDistribution> time_distribution = 
    Utility::OneDDistributionEntryConverterDB::convertEntry( entry );

  // Extract the particle type
  std::string particle_type_name = 
    source_rep.get<std::string>( "Particle Type" );

  ParticleSourceFactory::validateParticleTypeName( particle_type_name );

  ParticleType particle_type = 
    convertParticleTypeNameToParticleTypeEnum( particle_type_name );
  
  // Create the new source
  Teuchos::RCP<DistributedSource> source_tmp( new DistributedSource( 
	     id,
	     spatial_distribution,
	     directional_distribution,
	     energy_distribution,
	     time_distribution,
	     particle_type,
	     &Geometry::ModuleInterface<GeometryHandler>::getPointLocation ) );

  // Add optional importance functions
  if( source_rep.isParameter( "Rejection Cell" ) )
  {
    int rejection_cell_id = 
      source_rep.get<typename Geometry::ModuleInterface<GeometryHandler>::ExternalCellId>( "Rejection Cell" );

    TEST_FOR_EXCEPTION( 
		   !Geometry::ModuleInterface<GeometryHandler>::doesCellExist( 
							   rejection_cell_id ),
		   InvalidParticleSourceRepresentation,
		   "Error: Rejection cell " << rejection_cell_id <<
		   " does not exist!" );
    
    Geometry::ModuleTraits::InternalCellHandle rejection_cell_internal = 
      Geometry::ModuleInterface<GeometryHandler>::getInternalCellHandle( 
						           rejection_cell_id );

    source_tmp->setRejectionCell( rejection_cell_internal );
  }

  if( source_rep.isParameter( "Spatial Importance Function" ) )
  {
    entry = source_rep.getEntryRCP( "Spatial Importance Function" );

    const Teuchos::ParameterList& spatial_dist_rep = 
      Teuchos::any_cast<Teuchos::ParameterList>( entry->getAny() );
  
    Teuchos::RCP<Utility::SpatialDistribution> spatial_importance_func;
    try{
      spatial_importance_func = 
	Utility::SpatialDistributionFactory::createDistribution( 
							    spatial_dist_rep );
    }
    catch( Utility::InvalidSpatialDistributionRepresentation& error )
    {
      std::string message = "Error: An invalid spatial importance function ";
	message += "was specified in the distributed source!";
      message += error.what();
    
      throw InvalidParticleSourceRepresentation( message );
    }

    // Make sure the importance function is compatible with the spatial dist
    TEST_FOR_EXCEPTION( 
	      !spatial_importance_func->hasSameBounds( *spatial_distribution ),
	      InvalidParticleSourceRepresentation,
	      "Error: The bounds of the spatial importance function must be "
	      "the same as the bounds of the spatial distribution!" );

    source_tmp->setSpatialImportanceDistribution( spatial_importance_func );
  }

  if( source_rep.isParameter( "Directional Importance Function" ) )
  {
    entry = source_rep.getEntryRCP( "Directional Importance Function" );

    const Teuchos::ParameterList& directional_dist_rep = 
      Teuchos::any_cast<Teuchos::ParameterList>( entry->getAny() );
  
    Teuchos::RCP<Utility::DirectionalDistribution> directional_importance_func;
    try{
      directional_importance_func = 
	Utility::DirectionalDistributionFactory::createDistribution(
							directional_dist_rep );
    }
    catch( Utility::InvalidDirectionalDistributionRepresentation& error )
    {
      std::string message = "Error: An invalid direcional importance ";
	message += "function was specified in the distributed source!";
      message += error.what();
    
      throw InvalidParticleSourceRepresentation( message );
    }

    // Make sure the importance function is compatible with the direct. dist
    TEST_FOR_EXCEPTION( 
      !directional_importance_func->hasSameBounds( *directional_distribution ),
      InvalidParticleSourceRepresentation,
      "Error: The bounds of the directional importance function must be "
      "the same as the bounds of the directional distribution!" );

    source_tmp->setDirectionalImportanceDistribution( 
						 directional_importance_func );
  }

  if( source_rep.isParameter( "Energy Importance Function" ) )
  {
    entry = source_rep.getEntryRCP( "Energy Importance Function" );
    
    Teuchos::RCP<Utility::OneDDistribution> energy_importance_func = 
      Utility::OneDDistributionEntryConverterDB::convertEntry( entry );
   
    // Make sure the importance function is compatible with the energy dist
    TEST_FOR_EXCEPTION(
		!energy_importance_func->hasSameBounds( *energy_distribution ),
		InvalidParticleSourceRepresentation,
		"Error: The bounds of the energy importance function must be "
		"the same as the bounds of the energy distribution!" );
    
    source_tmp->setEnergyImportanceDistribution( energy_importance_func );
  }

  if( source_rep.isParameter( "Time Importance Function" ) )
  {
    entry = source_rep.getEntryRCP( "Time Importance Function" );

    Teuchos::RCP<Utility::OneDDistribution> time_importance_func = 
      Utility::OneDDistributionEntryConverterDB::convertEntry( entry );
    
    // Make sure the importance function is compatible with the time dist
    TEST_FOR_EXCEPTION(
		 !time_importance_func->hasSameBounds( *time_distribution ),
		 InvalidParticleSourceRepresentation,
		 "Error: The bounds of the time importance function must be "
		 "the same as the bounds of the time distribution!" );

    source_tmp->setTimeImportanceDistribution( time_importance_func );
  }
  
  // Set the return source
  source = Teuchos::rcp_dynamic_cast<ParticleSource>( source_tmp );

  double weight;
  // Return the weight of the source
  if( num_sources == 1u )
    weight = 1.0;
  else
    weight = source_rep.get<double>( "Weight" );

  // Print out unused parameters
  source_rep.unused( std::cout );

  return weight;
}

// Create a compound source
template<typename GeometryHandler>
void ParticleSourceFactory::createCompoundSource(
				      const Teuchos::ParameterList& source_rep,
				      Teuchos::RCP<ParticleSource>& source )
{
  unsigned num_sources = source_rep.numParams();
  unsigned source_index = 0u;

  Teuchos::Array<Teuchos::RCP<ParticleSource> > sources( num_sources );
  Teuchos::Array<double> source_weights( num_sources );
  
  Teuchos::ParameterList::ConstIterator param_iter = source_rep.begin();

  while( param_iter != source_rep.end() )
  {
    const Teuchos::ParameterList& sub_source = 
      Teuchos::any_cast<Teuchos::ParameterList>( param_iter->second.getAny() );
    
    if( sub_source.isParameter( "Spatial Distribution" ) )
    {
      source_weights[source_index] = 
	ParticleSourceFactory::createDistributedSource<GeometryHandler>( 
							 sub_source,
							 sources[source_index],
							 num_sources );
    }
    else
    {
      source_weights[source_index] = 
	ParticleSourceFactory::createStateSource( sub_source,
						  sources[source_index],
						  num_sources );
    }

    ++source_index;
    ++param_iter;
  }
  
  source.reset( new CompoundSource( sources, source_weights ) );
}


} // end Facemc namespace

#endif // end FACEMC_PARTICLE_SOURCE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleSourceFactory_def.hpp
//---------------------------------------------------------------------------//
