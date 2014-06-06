//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleSourceFactory.cpp
//! \author Alex Robinson
//! \brief  Particle source factory class declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_ParticleSourceFactory.hpp"
#include "Facemc_DistributedSource.hpp"
#include "Facemc_StateSource.hpp"
#include "Facemc_CompoundSource.hpp"
#include "Utility_SpatialDistributionFactory.hpp"
#include "Utility_DirectionalDistributionFactory.hpp"
#include "Utility_OneDDistributionEntryConverterDB.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Geometry_ModuleInterface.hpp"

namespace Facemc{

// Initialize the static member data
DistributedSource::getLocationFunction 
ParticleSourceFactory::get_location_function_pointer = 
  Geometry::ModuleInterface<moab::DagMC>::getPointLocation;

// Create the source represented by the parameter list
Teuchos::RCP<ParticleSource>
ParticleSourceFactory::createSource( const Teuchos::ParameterList& source_rep )
{
  // Validate all sources defined
  Teuchos::ParameterList::ConstIterator param_iter = 
    source_rep.begin();

  while( param_iter != source_rep.end() )
  {
    ParticleSourceFactory::validateSourceRep( *param_iter );

    ++param_iter;
  }

  if( source_rep.numParams() == 1 )
  {
    if( source_rep.isParameter( "Spatial Distribution" ) )
      return ParticleSourceFactory::createDistributedSource( 
							 *source_rep.begin() );
    else
      return ParticleSourceFactory::createStateSource( *source_rep.begin() );
  }
  else
    return ParticleSourceFactory::createCompoundSource( source_rep );
}

// Validate a source representation
void ParticleSourceFactory::validateSourceRep( 
				     const Teuchos::ParameterList& source_rep )
{
  bool valid_source = false;

  // Make sure a valid distributed source has been specified
  if( source_rep.isParameter( "Spatial Distribution" ) ||
      source_rep.isParameter( "Spatial Importance Function" ) ||
      source_rep.isParameter( "Directional Distribution" ) ||
      source_rep.isParameter( "Directional Importance Function" ) ||
      source_rep.isParameter( "Energy Distribution" ) ||
      source_rep.isParameter( "Energy Importance Function" ) ||
      source_rep.isParameter( "Time Distribution" ) || 
      source_rep.isParameter( "Time Importance Function" ) ||
      source_rep.isParameter( "Rejection Cell" ) ||
      source_rep.isParameter( "Id" )  ||
      source_rep.isParameter( "Particle Type" ) )
  {
    TEST_FOR_EXCEPTION( !source_rep.isParameter( "Spatial Distribution" ),
			InvalidParticleSourceRepresentation,
			"Error: A distributed source needs to have a spatial "
			"distribution specified!" );
    
    TEST_FOR_EXCEPTION( !source_rep.isParameter( "Directional Distribution" ),
			InvalidParticleSourceRepresentation,
			"Error: A distributed source needs to have a "
			"directional distribution specified!" );

    TEST_FOR_EXCEPTION( !source_rep.isParameter( "Energy Distribution" ),
			InvalidParticleSourceRepresentation,
			"Error: A distributed source needs to have an energy "
			"distribution specified!" );

    TEST_FOR_EXCEPTION( !source_rep.isParameter( "Time Distribution" ),
			InvalidParticleSourceRepresentation,
			"Error: A distributed source needs to have a time "
			"distribution specified!" );
    
    TEST_FOR_EXCEPTION( !source_rep.isParameter( "Id" ),
			InvalidParticleSourceRepresentation,
			"Error: A distributed source needs to have an id "
			" specified!" );

    TEST_FOR_EXCEPTION( !source_rep.isParameter( "Particle Type" ),
			InvalidParticleSourceRepresentation,
			"Error: A distributed source needs to have the "
			"emitted particle type specified!" );
    
    valid_source = true;
  }

  // Make sure a valid state source has been specified
  else
  {
    TEST_FOR_EXCEPTION( !source_rep.isParameter( "Particle State File" ),
			InvalidParticleSourceRepresentation,
			"Error: A state source needs to have a the particle "
			"state hdf5 file specified!" );
   
    valid_source = true;
  }

  TEST_FOR_EXCEPTION( !valid_source,
		      InvalidParticleSourceRepresentation,
		      "Error: The type of source " << source_rep <<
		      " could not be determined!" );  
}

// Create a distributed source
void Teuchos::RCP<ParticleSource>
ParticleSourceFactory::createDistributedSource(
				     const Teuchos::ParameterList& source_rep )
{
  unsigned id = source_rep.get<int>( "Id" );
  
  Teuchos::RCP<const Teuchos::ParameterEntry> entry = 
    source_rep.getEntryRCP( "Spatial Distribution" );

  Teuchos::RCP<Utility::SpatialDistribution> spatial_distribution;
  try{
    spatial_distribution = 
      Utility::SpatialDistributionFactory::createDistribution( 
					       entry.getValue( &source_rep ) );
  }
  catch( Utility::InvalidSpatialDistributionRepresentation& error )
  {
    std::string message = "Error: An invalid spatial distribution was ";
    message += "specified in the distributed source!";
    message += error.what();
    
    throw InvalidParticleSourceRepresentation( message );
  }
  
  entry = source_rep.getEntryRCP( "Directional Distribution" );
  
  Teuchos::RCP<Utility::DirectionalDistribution> directional_distribution;
  try{
    directional_distribution = 
      Utility::DirectionalDistributionFactory::createDistribution(
					       entry.getValue( &source_rep ) );
  }
  catch( Utility::InvalidDirectionalDistributionRepresentation& error )
  {
    std::string message = "Error: An invalid directional distribution was ";
    message += "specified in the distributed source!";
    message += error.what();
    
    throw InvalidParticleSourceRepresentation( message );
  }

  entry = source_rep.getEntryRCP( "Energy Distribution" );

  Teuchos::RCP<Utility::OneDDistribution> energy_distribution = 
    Utility::OneDDistributionEntryConvterDB::convertEntry( entry );

  entry = source_rep.getEntryRCP( "Time Distribution" );

  Teuchos::RCP<Utility::OneDDistribution> time_distribution = 
    Utility::OneDDistributionEntryConveterDB::convertEntry( entry );

  std::string particle_type_name = 
    source_rep.get<std::string>( "Particle Type" );

  ParticleSourceFactory::validateParticleTypeName( particle_type_name );

  ParticleType particle_type = 
    convertParticleTypeNameToParticleTypeEnum( particle_type_name );
  
  Teuchos::RCP<DistributedSource> source( new DistributedSource( 
			  id,
			  spatial_distribution,
			  directional_distribution,
			  energy_distribution,
			  time_distribution,
			  particle_type,
			  ParticleSourceFactory::get_location_function_ptr ) );

  if( source_rep.isParam( "Rejection Cell" ) )
  {
    source->setRejectionCell( source_rep.get<int>( "Rejection Cell" ) );
  }

  if( source_rep.isParam( "Spatial Importance Function" ) )
  {
    entry = source_rep.getEntryRCP( "Spatial Importance Function" );

    Teuchos::RCP<Utility::SpatialDistribution> spatial_importance_func;
    try{
      spatial_importance_func = 
	Utility::SpatialDistributionFactory::createDistribution( 
					       entry.getValue( &source_rep ) );
    }
    catch( Utility::InvalidSpatialDistributionRepresentation& error )
    {
      std::string message = "Error: An invalid spatial importance function "
	message += "was specified in the distributed source!";
      message += error.what();
    
      throw InvalidParticleSourceRepresentation( message );
    }

    source->setSpatialImportanceDistribution( spatial_importance_func );
  }

  if( source_rep.isParameter( "Directional Importance Function" ) )
  {
    entry = source_rep.getEntryRCP( "Directional Importance Function" );

    Teuchos::RCP<Utility::DirectionalDistribution> directional_importance_func;
    try{
      spatial_importance_func = 
	Utility::DirectionalDistributionFactory::createDistribution( 
					       entry.getValue( &source_rep ) );
    }
    catch( Utility::InvalidDirectionalDistributionRepresentation& error )
    {
      std::string message = "Error: An invalid direcional importance function "
	message += "was specified in the distributed source!";
      message += error.what();
    
      throw InvalidParticleSourceRepresentation( message );
    }

    source->setDirectionalImportanceDistribution( spatial_importance_func );
  }

  if( source_rep.isParameter( "Energy Importance Function" ) )
  {
    entry = source_rep.getEntryRCP( "Energy Importance Function" );
    
    Teuchos::RCP<Utility::OneDDistribution> energy_importance_func = 
      Utility::OneDDistributionEntryConvterDB::convertEntry( entry );
    
    source->setEnergyImportanceDistribution( energy_importance_func );
  }

  if( source_rep.isParameter( "Time Importance Function" ) )
  {
    entry = source_rep.getEntryRCP( "Time Importance Function" );

    Teuchos::RCP<Utility::OneDDistribution> time_importance_func = 
      Utility::OneDDistributionEntryConverterDB::convertEntry( entry );

    source->setTimeImportanceDistribution( time_importance_func )
  }
  
  return source;
}

// Create a state source
void Teuchos::RCP<ParticleSource>
ParticleSourceFactory::createStateSource( const Teuchos::ParameterList& source_rep )
{

}

// Create a compound source
void Teuchos::RCP<ParticleSource>
ParticleSourceFactory::createCompoundSource(const Teuchos::ParameterList& source_rep )
{
  Teuchos::ParameterList::ConstIterator sub_source = source_rep.begin();

  while( sub_source != source_rep.end() )
  {
    if( sub_source->isParam( "Spatial Distribution" ) )
  }
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_ParticleSourceFactory.cpp
//---------------------------------------------------------------------------//
