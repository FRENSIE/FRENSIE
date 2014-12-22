//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardParticleSourceFactory.hpp
//! \author Alex Robinson
//! \brief  Standard particle source factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_STANDARD_PARTICLE_SOURCE_FACTORY_HPP
#define FACEMC_STANDARD_PARTICLE_SOURCE_FACTORY_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleSourceFactory.hpp"

namespace MonteCarlo{

//! The standard particle source factory
template<typename GeometryHandler>
class StandardParticleSourceFactory : public ParticleSourceFactory
{
  
public:

  //! Get an instance of the factory
  static Teuchos::RCP<ParticleSourceFactory> getInstance();

  //! Destructor
  ~StandardParticleSourceFactory()
  { /* ... */ }

  //! Create the particle source represented by the parameter list
  Teuchos::RCP<ParticleSource>
  createSource( const Teuchos::ParameterList& source_rep );

private:

  // The factory instance
  static Teuchos::RCP<ParticleSourceFactory> factory_instance;

  //! Constructor
  StandardParticleSourceFactory()
  { /* ... */ }
};

// Initialize static member data
template<typename GeometryHandler>
Teuchos::RCP<ParticleSourceFactory> 
StandardParticleSourceFactory<GeometryHandler>::factory_instance(
			new StandardParticleSourceFactory<GeometryHandler>() );

// Get an instance of the factory
template<typename GeometryHandler>
inline Teuchos::RCP<ParticleSourceFactory>
StandardParticleSourceFactory<GeometryHandler>::getInstance()
{
  return factory_instance;
}

// Create the particle source represented by the parameter list
template<typename GeometryHandler>
inline Teuchos::RCP<ParticleSource>
StandardParticleSourceFactory<GeometryHandler>::createSource( 
				     const Teuchos::ParameterList& source_rep )
{
  return ParticleSourceFactory::createSourceImpl<GeometryHandler>(source_rep);
} 

} // end MonteCarlo namespace

#endif // end FACEMC_STANDARD_PARTICLE_SOURCE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleSourceFactory.hpp
//---------------------------------------------------------------------------//
