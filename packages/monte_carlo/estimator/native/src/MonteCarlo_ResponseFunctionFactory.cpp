//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ResponseFunctionFactory.cpp
//! \author Alex Robinson
//! \brief  Response function factory class definition.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ResponseFunctionFactory.hpp"
#include "MonteCarlo_EnergySpaceResponseFunction.hpp"
#include "MonteCarlo_PhaseSpaceResponseFunction.hpp"
#include "Utility_SpatialDistributionFactory.hpp"
#include "Utility_DirectionalDistributionFactory.hpp"
#include "Utility_OneDDistributionEntryConverterDB.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create the response functions specified
void ResponseFunctionFactory::createResponseFunctions( 
	     const Teuchos::ParameterList& response_reps,
	     boost::unordered_map<unsigned,std::shared_ptr<ResponseFunction> >&
             response_id_map )
{
  // Construct all response functions defined
  Teuchos::ParameterList::ConstIterator it = response_reps.begin();

  while( it != response_reps.end() )
  {
    const Teuchos::ParameterList& response_rep = 
      Teuchos::any_cast<Teuchos::ParameterList>( it->second.getAny() );

    // Validate the response function representation
    ResponseFunctionFactory::validateResponseFunctionRep( response_rep );

    if( response_rep.isParameter( "Spatial Distribution" ) )
    {
      ResponseFunctionFactory::createPhaseSpaceResponseFunction( 
							     response_rep,
							     response_id_map );
    }
    else
    {
      ResponseFunctionFactory::createEnergySpaceResponseFunction(
							     response_rep,
							     response_id_map );
    }

    ++it;
  }
}

// Valdate a response function representation
void ResponseFunctionFactory::validateResponseFunctionRep(
				   const Teuchos::ParameterList& response_rep )
{
  // Make sure the id is present
  TEST_FOR_EXCEPTION( !response_rep.isParameter( "Id" ),
		      InvalidResponseFunctionRepresentation,
		      "Error: the response function id must be specified!" );

  bool valid_response_rep = false;

  if( response_rep.isParameter( "Spatial Distribution" ) ||
      response_rep.isParameter( "Directional Distribution" ) ||
      response_rep.isParameter( "Time Distribution" ) )
  {
    TEST_FOR_EXCEPTION( !response_rep.isParameter( "Spatial Distribution" ),
			InvalidResponseFunctionRepresentation,
			"Error: the spatial distribution must be specified in "
			"a phase space response function!" );

    TEST_FOR_EXCEPTION( !response_rep.isParameter( "Directional Distribution"),
			InvalidResponseFunctionRepresentation,
			"Error: the directional distribution must be "
			"specified in a phase space response function!" );

    TEST_FOR_EXCEPTION( !response_rep.isParameter( "Time Distribution" ),
			InvalidResponseFunctionRepresentation,
			"Error: the time distribution must be specified in "
			"a phase space response function!" );

    TEST_FOR_EXCEPTION( !response_rep.isParameter( "Energy Distribution" ),
			InvalidResponseFunctionRepresentation,
			"Error: the energy distribution must be specified in "
			"a phase space response function!" );

    valid_response_rep = true;
  }
  else
  {
    TEST_FOR_EXCEPTION( !response_rep.isParameter( "Energy Distribution" ),
			InvalidResponseFunctionRepresentation,
			"Error: the energy distribution must be specified in "
			"an energy space response function!" );
    
    valid_response_rep = true;
  }

  TEST_FOR_EXCEPTION( !valid_response_rep,
		      InvalidResponseFunctionRepresentation,
		      "Error: the response function type could not be "
		      "determined!\n" << response_rep << "\n" );
}

// Create an energy space response function
void ResponseFunctionFactory::createEnergySpaceResponseFunction(
	     const Teuchos::ParameterList& response_rep,
	     boost::unordered_map<unsigned,std::shared_ptr<ResponseFunction> >&
             response_id_map )
{
  // Extract the entity id
  unsigned id = response_rep.get<unsigned int>( "Id" );

  TEST_FOR_EXCEPTION( response_id_map.find( id ) != response_id_map.end(),
		      InvalidResponseFunctionRepresentation,
		      "Error: response function id " << id << " is used "
		      "multiple times!" );

  TEST_FOR_EXCEPTION( id >= std::numeric_limits<unsigned>::max(),
		      InvalidResponseFunctionRepresentation,
		      "Error: response function id " << id << " is greater "
		      "than the max value of "
		      << std::numeric_limits<unsigned>::max() - 1u << "!" );

  // Extract the energy distribution
  Teuchos::RCP<const Teuchos::ParameterEntry> entry = 
    response_rep.getEntryRCP( "Energy Distribution" );

  std::shared_ptr<Utility::OneDDistribution> energy_distribution = 
    Utility::OneDDistributionEntryConverterDB::convertEntryToSharedPtr( entry);

  // Create the response function
  std::shared_ptr<ResponseFunction>& new_response_function = 
    response_id_map[id];

  new_response_function.reset( new EnergySpaceResponseFunction(
			   id,
			   ResponseFunctionFactory::createName( response_rep ),
			   energy_distribution ) );

  response_rep.unused( std::cout );
}

// Create a phase space response function
void ResponseFunctionFactory::createPhaseSpaceResponseFunction(
	     const Teuchos::ParameterList& response_rep,
	     boost::unordered_map<unsigned,std::shared_ptr<ResponseFunction> >&
             response_id_map )
{
  // Extract the entity id
  unsigned id = response_rep.get<unsigned int>( "Id" );

  TEST_FOR_EXCEPTION( response_id_map.find( id ) != response_id_map.end(),
		      InvalidResponseFunctionRepresentation,
		      "Error: response function id " << id << " is used "
		      "multiple times!" );

  TEST_FOR_EXCEPTION( id >= std::numeric_limits<unsigned>::max(),
		      InvalidResponseFunctionRepresentation,
		      "Error: response function id " << id << " is greater "
		      "than the max value of "
		      << std::numeric_limits<unsigned>::max() - 1u << "!" );

  // Extract the spatial distribution
  Teuchos::RCP<const Teuchos::ParameterEntry> entry = 
    response_rep.getEntryRCP( "Spatial Distribution" );

  const Teuchos::ParameterList& spatial_dist_rep = 
    Teuchos::any_cast<Teuchos::ParameterList>( entry->getAny() );

  std::shared_ptr<Utility::SpatialDistribution> spatial_distribution;
  try{
    spatial_distribution = 
      Utility::SpatialDistributionFactory::createDistribution( 
							    spatial_dist_rep );
					      
  }
  catch( Utility::InvalidSpatialDistributionRepresentation& error )
  {
    std::string message = "Error: An invalid spatial distribution was ";
    message += "specified in response function ";
    message += response_rep.name();
    message += "!\n";
    message += error.what();

    throw InvalidResponseFunctionRepresentation( message );
  }

  // Extract the directional distribution
  entry = response_rep.getEntryRCP( "Directional Distribution" );

  const Teuchos::ParameterList& directional_dist_rep = 
    Teuchos::any_cast<Teuchos::ParameterList>( entry->getAny() );

  std::shared_ptr<Utility::DirectionalDistribution> directional_distribution;
  try{
    directional_distribution = 
      Utility::DirectionalDistributionFactory::createDistribution(
							directional_dist_rep );
  }
  catch( Utility::InvalidDirectionalDistributionRepresentation& error )
  {
    std::string message = "Error: An invalid directional distribution was ";
    message += "specified in response function ";
    message += response_rep.name();
    message += "!\n";
    message += error.what();
    
    throw InvalidResponseFunctionRepresentation( message );
  }

  // Extract the energy distribution
  entry = response_rep.getEntryRCP( "Energy Distribution" );

  std::shared_ptr<Utility::OneDDistribution> energy_distribution = 
    Utility::OneDDistributionEntryConverterDB::convertEntryToSharedPtr( entry);

  // Extract the time distribution
  entry = response_rep.getEntryRCP( "Time Distribution" );

  std::shared_ptr<Utility::OneDDistribution> time_distribution = 
    Utility::OneDDistributionEntryConverterDB::convertEntryToSharedPtr( entry);

  // Create the new response function
  std::shared_ptr<ResponseFunction>& new_response_function = 
    response_id_map[id];

  new_response_function.reset( new PhaseSpaceResponseFunction( 
			   id,
			   ResponseFunctionFactory::createName( response_rep ),
			   spatial_distribution,
			   directional_distribution,
			   energy_distribution,
			   time_distribution ) );

  response_rep.unused( std::cout );
}

// Create the response function name
std::string ResponseFunctionFactory::createName( 
				   const Teuchos::ParameterList& response_rep )
{
  std::string name = response_rep.name();

  unsigned start_loc = name.find_first_of( ">" );
  
  return name.substr( start_loc+1, name.size()-start_loc-1 );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ResponseFunctionFactory.cpp
//---------------------------------------------------------------------------//
