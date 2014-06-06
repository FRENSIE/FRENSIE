//---------------------------------------------------------------------------//
//!
//! \file   Facemc_ParticleSourceFactory.hpp
//! \author Alex Robinson
//! \brief  Particle source factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_PARTICLE_SOURCE_FACTORY_HPP
#define FACEMC_PARTICLE_SOURCE_FACTORY_HPP

// Std Lib Includes
#include <stdexcept>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "Utility_ParticleSource.hpp"
#include "Facemc_DistributedSource.hpp"

namespace Facemc{

//! The particle source factory class
class ParticleSourceFactory
{

public:

  //! Set the getLocationFunction pointer
  static void setGetLocationFunctionPointer( 
	    DistributedSource::getLocationFunction get_location_function_ptr );

  //! Create the particle source represented by the parameter list
  static Teuchos::RCP<ParticleSource>
  createSource( const Teuchos::ParameterList& distribution_rep );

private:

  // Validate a source respresentation
  static void validateSourceRep( const Teuchos::ParameterList& source_rep );

  // Create a distributed source
  static Teuchos::RCP<ParticleSource>
  createDistributedSource( const Teuchos::ParameterList& source_rep );

  // Create a state source
  static Teuchos::RCP<ParticleSource>
  createStateSource( const Teuchos::ParameterList& source_rep );

  // Create a compound source
  static Teuchos::RCP<ParticleSource>
  createCompoundSource( const Teuchos::ParameterList& compound_source );

  // The getLocationFunction pointer
  static DistributedSource::getLocationFunction get_location_function_ptr;

  // Constructor
  ParticleSourceFactory();
};

//! The invalid particle source representation error
class InvalidParticleSourceRepresentation : public std::logic_error
{
  
public:

  InvalidParticleSourceRepresentation( const std::string& what_arg )
    : std::logic_error( what_arg )
  { /* ... */ }
};

} // end Facemc namespace

#endif // end FACEMC_PARTICLE_SOURCE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end Facemc_ParticleSourceFactory.hpp
//---------------------------------------------------------------------------//
