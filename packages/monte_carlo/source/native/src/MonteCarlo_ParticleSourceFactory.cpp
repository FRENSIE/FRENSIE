//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSourceFactory.cpp
//! \author Alex Robinson
//! \brief  Particle source factory class declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ParticleSourceFactory.hpp"
#include "MonteCarlo_CachedStateParticleSource.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Initialize static member data
const std::shared_ptr<Utility::OneDDistribution> 
ParticleSourceFactory::s_default_time_dist( 
				       new Utility::DeltaDistribution( 0.0 ) );

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
      source_rep.isParameter( "Rejection Cells" ) ||
      source_rep.isParameter( "Id" )  ||
      source_rep.isParameter( "Particle Type" ) )
  {
    TEST_FOR_EXCEPTION( !source_rep.isParameter( "Spatial Distribution" ),
			InvalidParticleSourceRepresentation,
			"Error: A distributed source needs to have a spatial "
			"distribution specified!" );

    TEST_FOR_EXCEPTION( !source_rep.isParameter( "Energy Distribution" ),
			InvalidParticleSourceRepresentation,
			"Error: A distributed source needs to have an energy "
			"distribution specified!" );
    
    TEST_FOR_EXCEPTION( !source_rep.isParameter( "Id" ),
			InvalidParticleSourceRepresentation,
			"Error: A distributed source needs to have an id "
			" specified!" );

    TEST_FOR_EXCEPTION( !source_rep.isParameter( "Particle Type" ),
			InvalidParticleSourceRepresentation,
			"Error: A distributed source needs to have the "
			"emitted particle type specified!" );

    // Test if the weight parameter has been set if multiple source are present
    if( num_sources > 1u )
    {
      TEST_FOR_EXCEPTION( !source_rep.isParameter( "Weight" ),
                          InvalidParticleSourceRepresentation,
                          "Error: When multiple sources are present, each "
                          "must have a weight specified!" );
    }  

    valid_source = true;
  }

  // Make sure a valid state source has been specified
  else
  {
    TEST_FOR_EXCEPTION( !source_rep.isParameter( "Particle State File" ),
			InvalidParticleSourceRepresentation,
			"Error: A state source needs to have a particle "
			"state hdf5 file specified!" );
    
    TEST_FOR_EXCEPTION( !source_rep.isParameter( "Internal State Bank Name" ),
                        InvalidParticleSourceRepresentation,
                        "Error: A state source needs to specify the name of "
                        "the state bank name in the particle state file!" );
    
    TEST_FOR_EXCEPTION( !source_rep.isParameter( "File Type" ),
                        InvalidParticleSourceRepresentation,
                        "Error: A state source needs to specify the file type "
                        "of the state bank file!" );

    if( num_sources > 1u )
    {
      THROW_EXCEPTION( InvalidParticleSourceRepresentation,
                       "Error: State sources cannot be part of a compound "
                       "source!" );
    }
   
    valid_source = true;
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
		      << particle_type_name << ")!" );
}

// Get the particle type enum
ParticleType ParticleSourceFactory::getParticleType( 
                                      const Teuchos::ParameterList& source_rep,
                                      const ParticleModeType& particle_mode )
{
  // Extract the particle type
  std::string particle_type_name = 
    source_rep.get<std::string>( "Particle Type" );

  ParticleSourceFactory::validateParticleTypeName( particle_type_name );

  ParticleType particle_type = convertParticleTypeNameToParticleTypeEnum( 
                                                          particle_type_name );

  TEST_FOR_EXCEPTION( 
                 !isParticleModeTypeCompatible( particle_mode, particle_type ),
                 InvalidParticleSourceRepresentation,
                 "Error: particle type ("
                 << particle_type << ") is not compatible with particle mode ("
                 << particle_mode << ")" );

  return particle_type;
}

// Create a state source
void ParticleSourceFactory::createCachedStateSource( 
				      const Teuchos::ParameterList& source_rep,
                                      const ParticleModeType& particle_mode,
                                      std::shared_ptr<ParticleSource>& source,
                                      std::ostream& os_warn )
{
  TEST_FOR_EXCEPTION( !source_rep.isParameter( "Particle State File" ),
			InvalidParticleSourceRepresentation,
			"Error: A state source needs to have a particle "
			"state hdf5 file specified!" );
    
  TEST_FOR_EXCEPTION( !source_rep.isParameter( "Internal State Bank Name" ),
                        InvalidParticleSourceRepresentation,
                        "Error: A state source needs to specify the name of "
                        "the state bank name in the particle state file!" );
    
    TEST_FOR_EXCEPTION( !source_rep.isParameter( "File Type" ),
                        InvalidParticleSourceRepresentation,
                        "Error: A state source needs to specify the file type "
                        "of the state bank file!" );
    
  std::string particle_state_file_name = 
    source_rep.get<std::string>( "Particle State File" );

  std::string internal_bank_name = 
    source_rep.get<std::string>( "Internal State Bank Name" );

  std::string file_type = 
    source_rep.get<std::string>( "File Type" );

  Utility::ArchivableObject::ArchiveType archive_type;

  if( file_type == "XML" )
    archive_type = Utility::ArchivableObject::XML_ARCHIVE;
  else if( file_type == "BINARY" )
    archive_type = Utility::ArchivableObject::BINARY_ARCHIVE;
  else if( file_type == "ASCII" )
    archive_type = Utility::ArchivableObject::ASCII_ARCHIVE;
  
  source.reset( new CachedStateParticleSource( particle_state_file_name,
                                               internal_bank_name,
                                               archive_type ) );
  
  // Print out unused parameters
  source_rep.unused( os_warn );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSourceFactory.cpp
//---------------------------------------------------------------------------//
