//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSourceFactory_def.hpp
//! \author Alex Robinson
//! \brief  Particle source factory base class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SOURCE_FACTORY_DEF_HPP
#define MONTE_CARLO_PARTICLE_SOURCE_FACTORY_DEF_HPP

// Std Lib Includes
#include <set>

// FRENSIE Includes
#include "MonteCarlo_StandardParticleSource.hpp"
#include "MonteCarlo_CachedStateParticleSource.hpp"
#include "MonteCarlo_CompoundStandardParticleSource.hpp"
#include "Utility_SpatialDistributionFactory.hpp"
#include "Utility_DirectionalDistributionFactory.hpp"
#include "Utility_OneDDistributionEntryConverterDB.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create the source represented by the parameter list
template<typename GeometryModuleInterface>
std::shared_ptr<ParticleSource>
ParticleSourceFactory::createSourceImpl( 
				     const Teuchos::ParameterList& source_rep,
		    		     const ParticleModeType& particle_mode,
                                     std::ostream& os_warn )
{
  // Get the number of parameters in the list
  unsigned num_params = source_rep.numParams();
  
  // Validate all sources defined
  Teuchos::ParameterList::ConstIterator param_iter = 
    source_rep.begin();
  
  while( param_iter != source_rep.end() )
  {
    Teuchos::ParameterList sub_source;
    
    try{
      sub_source = 
        Teuchos::any_cast<Teuchos::ParameterList>( 
                                                 param_iter->second.getAny() );
    }
    EXCEPTION_CATCH_RETHROW_AS( std::exception,
                                InvalidParticleSourceRepresentation,
                                "Error: The source xml file is not valid! "
                                "The source definition must be a "
                                "ParameterList." );
    
    ParticleSourceFactory::validateSourceRep( sub_source, num_params );
    
    ++param_iter;
  }
  
  std::shared_ptr<ParticleSource> source;
  
  if( num_params == 1 )
  {
    const Teuchos::ParameterList& sub_source = 
      Teuchos::any_cast<Teuchos::ParameterList>( 
					 source_rep.begin()->second.getAny() );
    
    if( sub_source.isParameter( "Spatial Distribution" ) )
    {
      ParticleSourceFactory::createStandardSource<GeometryModuleInterface>( 
							         sub_source,
                                                                 particle_mode,
                                                                 source,
                                                                 os_warn );
    }
    else
    {
      ParticleSourceFactory::createCachedStateSource( sub_source, 
                                                      particle_mode, 
                                                      source,
                                                      os_warn );
    }
  }
  else
  {
    ParticleSourceFactory::createCompoundStandardSource<GeometryModuleInterface>(
                                                                 source_rep, 
								 particle_mode,
                                                                 source,
                                                                 os_warn );
  }
  
  // Make sure the source has been created
  testPostcondition( source.get() );

  // Print out unused parameters
  source_rep.unused( os_warn );
  
  return source;
}

// Create a standard source
template<typename GeometryModuleInterface, typename SourceType>
double ParticleSourceFactory::createStandardSource(
				      const Teuchos::ParameterList& source_rep,
			  	      const ParticleModeType& particle_mode,
				      std::shared_ptr<SourceType>& source,
                                      std::ostream& os_warn,
				      const unsigned num_sources )
{
  // Extract the source id
  unsigned id = source_rep.get<int>( "Id" );
  
  Teuchos::RCP<const Teuchos::ParameterEntry> entry = 
    source_rep.getEntryRCP( "Spatial Distribution" );
  
  // Extract the spatial distribution
  const Teuchos::ParameterList& spatial_dist_rep = 
      Teuchos::any_cast<Teuchos::ParameterList>( entry->getAny() );
  
  std::shared_ptr<Utility::SpatialDistribution> spatial_distribution;
  try{
    spatial_distribution = 
      Utility::SpatialDistributionFactory::createDistribution( 
							    spatial_dist_rep );
					      
  }
  EXCEPTION_CATCH_RETHROW_AS(Utility::InvalidSpatialDistributionRepresentation,
			     InvalidParticleSourceRepresentation,
			     "Error: An invalid spatial distribution was "
			     "specified in the standard source!" );
  
  // Extract the directional distribution
  std::shared_ptr<Utility::DirectionalDistribution> directional_distribution;
  
  if( source_rep.isParameter( "Directional Distribution" ) )
  {
    entry = source_rep.getEntryRCP( "Directional Distribution" );
  
    const Teuchos::ParameterList& directional_dist_rep = 
      Teuchos::any_cast<Teuchos::ParameterList>( entry->getAny() );
  
    try{
      directional_distribution = 
	Utility::DirectionalDistributionFactory::createDistribution(
							directional_dist_rep );
    }
    EXCEPTION_CATCH_RETHROW_AS(
			 Utility::InvalidDirectionalDistributionRepresentation,
			 InvalidParticleSourceRepresentation,
			 "Error: An invalid directional distribution was "
			 "specified in the standard source!" );
  }
  else // create an isotropic distribution
  {
    directional_distribution = 
      Utility::DirectionalDistributionFactory::createIsotropicDistribution();
  }

  // Extract the energy distribution
  entry = source_rep.getEntryRCP( "Energy Distribution" );

  std::shared_ptr<Utility::OneDDistribution> energy_distribution = 
    Utility::OneDDistributionEntryConverterDB::convertEntryToSharedPtr( entry );

  // Extract the time distribution
  std::shared_ptr<Utility::OneDDistribution> time_distribution;
  
  if( source_rep.isParameter( "Time Distribution" ) )
  {
    entry = source_rep.getEntryRCP( "Time Distribution" );

    time_distribution = 
      Utility::OneDDistributionEntryConverterDB::convertEntryToSharedPtr( entry );
  }
  else // use the default time distribution
    time_distribution = s_default_time_dist;
 
  ParticleType particle_type = getParticleType( source_rep, particle_mode );
  
  // Create the new source
  std::shared_ptr<StandardParticleSource> source_tmp( 
                                           new StandardParticleSource( 
                                                      id,
                                                      spatial_distribution,
	                                              directional_distribution,
                                                      energy_distribution,
                                                      time_distribution,
                                                      particle_type ) );

  // Add optional importance functions
  if( source_rep.isParameter( "Rejection Cells" ) )
  {
    const Utility::ArrayString& array_string =
      source_rep.get<Utility::ArrayString>( "Rejection Cells" );

    Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> rejection_cells;

    try{
      rejection_cells = array_string.getConcreteArray<Geometry::ModuleTraits::InternalCellHandle>();
    }
    EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
                                InvalidParticleSourceRepresentation,
                                "Error: The rejection cells requested for "
                                "standard source " << id <<
                                "in the xml file are not valid!" );

    // Make sure the rejection cells exist
    for( unsigned i = 0; i < rejection_cells.size(); ++i )
    {
      TEST_FOR_EXCEPTION( 
                 !GeometryModuleInterface::doesCellExist( rejection_cells[i] ),
                 InvalidParticleSourceRepresentation,
                 "Error: Rejection cell " << rejection_cells[i] <<
                 " requested for standard source " << id <<
                 " does not exist!" );
    }

    // Add the rejection cells
    for( unsigned i = 0; i < rejection_cells.size(); ++i )
    {
      source_tmp->setRejectionCell(rejection_cells[i], 
                                   GeometryModuleInterface::getPointLocation );
    }
  }

  if( source_rep.isParameter( "Spatial Importance Function" ) )
  {
    entry = source_rep.getEntryRCP( "Spatial Importance Function" );

    const Teuchos::ParameterList& spatial_dist_rep = 
      Teuchos::any_cast<Teuchos::ParameterList>( entry->getAny() );
  
    std::shared_ptr<Utility::SpatialDistribution> spatial_importance_func;
    try{
      spatial_importance_func = 
	Utility::SpatialDistributionFactory::createDistribution( 
							    spatial_dist_rep );
    }
    EXCEPTION_CATCH_RETHROW_AS(
			     Utility::InvalidSpatialDistributionRepresentation,
			     InvalidParticleSourceRepresentation,
			     "Error: An invalid spatial importance function "
			     "was specified in the standard source!" );

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
  
    std::shared_ptr<Utility::DirectionalDistribution> directional_importance_func;
    try{
      directional_importance_func = 
	Utility::DirectionalDistributionFactory::createDistribution(
							directional_dist_rep );
    }
    EXCEPTION_CATCH_RETHROW_AS( 
		         Utility::InvalidDirectionalDistributionRepresentation,
			 InvalidParticleSourceRepresentation,
			 "Error: An invalid direcional importance "
			 "function was specified in the standard source!" );

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
    
    std::shared_ptr<Utility::OneDDistribution> energy_importance_func = 
      Utility::OneDDistributionEntryConverterDB::convertEntryToSharedPtr( entry );
   
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

    std::shared_ptr<Utility::OneDDistribution> time_importance_func = 
      Utility::OneDDistributionEntryConverterDB::convertEntryToSharedPtr( entry );
    
    // Make sure the importance function is compatible with the time dist
    TEST_FOR_EXCEPTION(
		 !time_importance_func->hasSameBounds( *time_distribution ),
		 InvalidParticleSourceRepresentation,
		 "Error: The bounds of the time importance function must be "
		 "the same as the bounds of the time distribution!" );

    source_tmp->setTimeImportanceDistribution( time_importance_func );
  }
  
  // Set the return source
  source = source_tmp;

  double weight;
  // Return the weight of the source
  if( num_sources == 1u )
    weight = 1.0;
  else
    weight = source_rep.get<double>( "Weight" );

  // Print out unused parameters
  source_rep.unused( os_warn );

  return weight;
}

// Create a compound source
template<typename GeometryModuleInterface>
void ParticleSourceFactory::createCompoundStandardSource(
				      const Teuchos::ParameterList& source_rep,
			  	      const ParticleModeType& particle_mode,
				      std::shared_ptr<ParticleSource>& source,
                                      std::ostream& os_warn )
{
  unsigned num_sources = source_rep.numParams();
  unsigned source_index = 0u;

  std::set<unsigned> source_ids;

  Teuchos::Array<std::shared_ptr<StandardParticleSource> > 
    sources( num_sources );
  Teuchos::Array<double> source_weights( num_sources );
  
  Teuchos::ParameterList::ConstIterator param_iter = source_rep.begin();

  while( param_iter != source_rep.end() )
  {
    const Teuchos::ParameterList& sub_source = 
      Teuchos::any_cast<Teuchos::ParameterList>( param_iter->second.getAny() );
    
    source_weights[source_index] = 
      ParticleSourceFactory::createStandardSource<GeometryModuleInterface>( 
							 sub_source,
							 particle_mode,
							 sources[source_index],
                                                         os_warn,
							 num_sources );

    TEST_FOR_EXCEPTION( source_ids.find( sources[source_index]->getId() ) !=
                        source_ids.end(),
                        InvalidParticleSourceRepresentation,
                        "Error: The compound source is invalid because source "
                        "id " << sources[source_index]->getId() <<
                        " appears multiple times! Every source id must be "
                        "unique." );

    source_ids.insert( sources[source_index]->getId() );
    
    ++source_index;
    ++param_iter;
  }
  
  source.reset( new CompoundStandardParticleSource( sources, source_weights ));
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_SOURCE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSourceFactory_def.hpp
//---------------------------------------------------------------------------//
