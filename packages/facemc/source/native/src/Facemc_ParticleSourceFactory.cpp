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
#include "Utility_ContractException.hpp"
#include "Geometry_ModuleInterface.hpp"

namespace Facemc{

// Initialize the static member data
DistributedSource::getLocationFunction 
ParticleSourceFactory::get_location_function_ptr = 
  Geometry::ModuleInterface<moab::DagMC>::getPointLocation;

// Create the source represented by the parameter list
Teuchos::RCP<ParticleSource>
ParticleSourceFactory::createSource( const Teuchos::ParameterList& source_rep )
{
  // Get the number of parameters in the list
  unsigned num_params = source_rep.numParams();
  
  // Validate all sources defined
  Teuchos::ParameterList::ConstIterator param_iter = 
    source_rep.begin();

  const Teuchos::ParameterList sub_source;

  while( param_iter != source_rep.end() )
  {
    sub_source = source_rep.entry( param_iter ).getValue( &sub_source );
    
    ParticleSourceFactory::validateSourceRep( sub_source, num_params );

    ++param_iter;
  }

  Teuchos::RCP<ParticleSource> source;

  if( num_params == 1 )
  {
    if( source_rep.isParameter( "Spatial Distribution" ) )
      ParticleSourceFactory::createDistributedSource( *source_rep.begin(),
						      source );
    else
      ParticleSourceFactory::createStateSource( *source_rep.begin(), source );
  }
  else
    ParticleSourceFactory::createCompoundSource( source_rep, source );

  // Make sure the source has been created
  testPostcondition( !source.is_null() );

  return source;
}

// Validate a source representation
void ParticleSourceFactory::validateSourceRep( 
				      const Teuchos::ParameterList& source_rep,
				      const unsigned num_sources )
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

  // Test if the weight parameter has been set if multiple source are present
  if( num_sources > 1u )
  {
    TEST_FOR_EXCEPTION( !source_rep.isParameter( "Weight" ),
			InvalidParticleSourceRepresentation,
			"Error: When multiple sources are present, each "
			"must have a weight specified!" );
  }  

  TEST_FOR_EXCEPTION( !valid_source,
		      InvalidParticleSourceRepresentation,
		      "Error: The type of source " << source_rep <<
		      " could not be determined!" );  
}

// Validate the particle type name
void ParticleSourceFactory::validateParticleTypeName( 
					const std::string& particle_type_name )
{
  TEST_FOR_EXCEPTION( !isValidParticleTypeName( particle_type_name ),
		      InvalidParticleSourceRepresentation,
		      "Error: An invalid particle type was specified ("
		      << particle_type_name << "). Only 'Neutron', "
		      "'Photon', 'Adjoint Neutron', and 'Adjoint Photon' are "
		      "valid names!" );
}

// Create a distributed source
double ParticleSourceFactory::createDistributedSource(
				      const Teuchos::ParameterList& source_rep,
				      Teuchos::RCP<ParticleSource>& source,
				      const unsigned num_sources )
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
  
  // Create the new source
  Teuchos::RCP<DistributedSource> source_tmp( new DistributedSource( 
			  id,
			  spatial_distribution,
			  directional_distribution,
			  energy_distribution,
			  time_distribution,
			  particle_type,
			  ParticleSourceFactory::get_location_function_ptr ) );

  // Add optional importance functions
  if( source_rep.isParam( "Rejection Cell" ) )
  {
    source_tmp->setRejectionCell( source_rep.get<int>( "Rejection Cell" ) );
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

    source_tmp->setSpatialImportanceDistribution( spatial_importance_func );
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

    source_tmp->setDirectionalImportanceDistribution( spatial_importance_func);
  }

  if( source_rep.isParameter( "Energy Importance Function" ) )
  {
    entry = source_rep.getEntryRCP( "Energy Importance Function" );
    
    Teuchos::RCP<Utility::OneDDistribution> energy_importance_func = 
      Utility::OneDDistributionEntryConvterDB::convertEntry( entry );
    
    source_tmp->setEnergyImportanceDistribution( energy_importance_func );
  }

  if( source_rep.isParameter( "Time Importance Function" ) )
  {
    entry = source_rep.getEntryRCP( "Time Importance Function" );

    Teuchos::RCP<Utility::OneDDistribution> time_importance_func = 
      Utility::OneDDistributionEntryConverterDB::convertEntry( entry );

    source_tmp->setTimeImportanceDistribution( time_importance_func )
  }
  
  // Set the return source
  source = source_tmp;

  // Return the weight of the source
  if( num_sources == 1u )
    return 1.0;
  else
    return source_rep.get<double>( "Weight" );
}

// Create a state source
double ParticleSourceFactory::createStateSource( 
				      const Teuchos::ParameterList& source_rep,
				      Teuchos::RCP<ParticleSource>& source,
				      const unsigned num_sources )
{
  return 0.0;
}

// Create a compound source
void ParticleSourceFactory::createCompoundSource(
				      const Teuchos::ParameterList& source_rep,
				      Teuchos::RCP<ParticleSource>& source )
{
  unsigned num_sources = source_rep.numParams();
  unsigned source_index = 0u;

  Teuchos::Array<Teuchos::RCP<ParticleSource> > sources( num_sources );
  Teuchos::Array<double> source_weights( num_sources );
  
  Teuchos::ParameterList::ConstIterator sub_source = source_rep.begin();

  while( sub_source != source_rep.end() )
  {
    if( sub_source->isParam( "Spatial Distribution" ) )
    {
      source_weight[source_index] = 
	ParticleSourceFactory::createDistributedSource( *sub_source,
							sources[source_index],
							num_sources );
    }
    else
    {
      source_weight[source_index] = 
	ParticleSourceFactory::createStateSource( *sub_source,
						  sources[source_index],
						  num_sources );
    }

    ++source_index;
    ++sub_source;
  }

  // Normalize the source weights
  double norm_constant = 0.0;
  
  for( unsigned i = 0u; i < source_weights.size(); ++i )
  {
    norm_constant += source_weight[i];
  }
  
  for( unsigned i = 0u; i < source_weight.size(); ++i )
  {
    source_weight[i] /= norm_constant;
  }

  source.reset( new CompoundSource( sources, source_weights ) );
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_ParticleSourceFactory.cpp
//---------------------------------------------------------------------------//
