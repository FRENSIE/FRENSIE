//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleSourceFactory.cpp
//! \author Alex Robinson
//! \brief  Particle source factory class declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_ParticleSourceFactory.hpp"
#include "Facemc_StateSource.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{



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

// Create a state source
double ParticleSourceFactory::createStateSource( 
				      const Teuchos::ParameterList& source_rep,
				      Teuchos::RCP<ParticleSource>& source,
				      const unsigned num_sources )
{
  return 0.0;
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_ParticleSourceFactory.cpp
//---------------------------------------------------------------------------//
